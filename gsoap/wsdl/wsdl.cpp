/*
	wsdl.cpp

	WSDL 1.1 binding schema implementation

--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2001-2009, Robert van Engelen, Genivia Inc. All Rights Reserved.
This software is released under one of the following two licenses:
GPL or Genivia's license for commercial use.
--------------------------------------------------------------------------------
GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
engelen@genivia.com / engelen@acm.org
--------------------------------------------------------------------------------
A commercial use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------

*/

#include "wsdlH.h"
#include "includes.h"

extern struct Namespace namespaces[];

const char *qname_token(const char *QName, const char *URI)
{ if (QName && QName[0] == '"' && QName[1] == '"' && QName[2] == ':')
    return QName + 3;
  if (QName && URI && *QName == '"') // QNames are stored in the format "URI":name, unless the URI is in the nsmap
  { size_t n = strlen(URI);
    if (!strncmp(QName + 1, URI, n) && QName[n + 1] == '"')
      return QName + n + 3;
  }
  return NULL;
}

int is_builtin_qname(const char *QName)
{ if (iflag)
    return 1;
  if (QName)
  { if (*QName != '"')
      return 1;	// if the QName does not start with a ", it must be in the nsmap
    const char *s = strchr(QName + 1, '"');
    if (s)
    { size_t n = s - QName - 1;
      for (SetOfString::const_iterator i = exturis.begin(); i != exturis.end(); ++i)
        if (strlen(*i) == n && !strncmp(QName + 1, *i, n))
          return 1; // QName is in exturis
    }
  }
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
//	wsdl
//
////////////////////////////////////////////////////////////////////////////////

extern "C" {
int warn_ignore(struct soap*, const char*);
int show_ignore(struct soap*, const char*);
}

wsdl__definitions::wsdl__definitions()
{ soap = soap_new1(SOAP_XML_TREE | SOAP_C_UTFSTRING);
#ifdef WITH_OPENSSL
  soap_ssl_client_context(soap, SOAP_SSL_NO_AUTHENTICATION, NULL, NULL, NULL, NULL, NULL);
#endif
  soap_set_namespaces(soap, namespaces);
  soap_default(soap);
  if (vflag)
    soap->fignore = show_ignore;
  else
    soap->fignore = warn_ignore;
  soap->encodingStyle = NULL;
  soap->proxy_host = proxy_host;
  soap->proxy_port = proxy_port;
  soap->proxy_userid = proxy_userid;
  soap->proxy_passwd = proxy_passwd;
  name = NULL;
  targetNamespace = soap_strdup(soap, "");
  documentation = NULL;
  types = NULL;
  updated = false;
  location = NULL;
  redirs = 0;
}

wsdl__definitions::wsdl__definitions(struct soap *copy, const char *cwd, const char *loc)
{ soap = soap_copy(copy);
  soap->socket = SOAP_INVALID_SOCKET;
  soap->recvfd = 0;
  soap->sendfd = 1;
  strcpy(soap->host, copy->host);
  soap_default(soap);
  soap->fignore = warn_ignore;
  soap->encodingStyle = NULL;
  updated = false;
  location = NULL;
  redirs = 0;
  read(cwd, loc);
}

wsdl__definitions::~wsdl__definitions()
{ soap_destroy(soap);
  soap_end(soap);
  soap_done(soap);
  free(soap);
}

int wsdl__definitions::get(struct soap *soap)
{ return preprocess();
}

int wsdl__definitions::read(int num, char **loc)
{ if (num <= 0)
    return read((const char*)NULL, (const char*)NULL);
  if (num == 1)
    return read((const char*)NULL, loc[0]);
  wsdl__import im;
  im.namespace_ = NULL;
  for (int i = 0; i < num; i++)
  { im.location = loc[i];
    import.push_back(im);
  }
  return preprocess();
}

int wsdl__definitions::read(const char *cwd, const char *loc)
{ const char *cwd_temp;
  if (!cwd)
    cwd = cwd_path;
  if (vflag)
    fprintf(stderr, "\nOpening WSDL/XSD '%s' from '%s'\n", loc?loc:"", cwd?cwd:"");
  if (loc)
  {
#ifdef WITH_OPENSSL
    if (!strncmp(loc, "http://", 7) || !strncmp(loc, "https://", 8))
#else
    if (!strncmp(loc, "https://", 8))
    { fprintf(stderr, "\nCannot connect to https site: no SSL support, please rebuild with SSL (default) or download the files and rerun wsdl2h\n");
      exit(1);
    }
    else if (!strncmp(loc, "http://", 7))
#endif
    { fprintf(stderr, "\nConnecting to '%s' to retrieve WSDL/XSD...\n", loc);
      location = soap_strdup(soap, loc);
      if (soap_connect_command(soap, SOAP_GET, location, NULL))
      { fprintf(stderr, "Connection failed\n");
        soap_print_fault(soap, stderr);
        exit(1);
      }
      fprintf(stderr, "Connected, receiving...\n");
    }
    else if (cwd && (!strncmp(cwd, "http://", 7) || !strncmp(cwd, "https://", 8)))
    { char *s;
      location = (char*)soap_malloc(soap, strlen(cwd) + strlen(loc) + 2);
      strcpy(location, cwd);
      s = strrchr(location, '/');
      if (s)
        *s = '\0';
      strcat(location, "/");
      strcat(location, loc);
      fprintf(stderr, "\nConnecting to '%s' to retrieve relative '%s' WSDL/XSD...\n", location, loc);
      if (soap_connect_command(soap, SOAP_GET, location, NULL))
      { fprintf(stderr, "Connection failed\n");
        exit(1);
      }
      fprintf(stderr, "Connected, receiving...\n");
    }
    else
    { soap->recvfd = open(loc, O_RDONLY, 0);
      if (soap->recvfd < 0)
      { if (cwd)
        { char *s;
          location = (char*)soap_malloc(soap, strlen(cwd) + strlen(loc) + 2);
          strcpy(location, cwd);
          s = strrchr(location, '/');
#ifdef WIN32
          if (!s)
            s = strrchr(location, '\\');
#endif
          if (s)
            *s = '\0';
          strcat(location, "/");
          strcat(location, loc);
          if (!strncmp(location, "file://", 7))
            location += 7;
          soap->recvfd = open(location, O_RDONLY, 0);
        }
        if (soap->recvfd < 0 && import_path)
        { location = (char*)soap_malloc(soap, strlen(import_path) + strlen(loc) + 2);
          strcpy(location, import_path);
          strcat(location, "/");
          strcat(location, loc);
          if (!strncmp(location, "file://", 7))
            location += 7;
          soap->recvfd = open(location, O_RDONLY, 0);
        }
        if (soap->recvfd < 0)
        { fprintf(stderr, "\nCannot open '%s'\n", loc);
          exit(1);
        }
      }
      else
        location = soap_strdup(soap, loc);
      fprintf(stderr, "\nReading file '%s'...\n", location);
    }
  }
  cwd_temp = cwd_path;
  cwd_path = location;
  if (!soap_begin_recv(soap))
    this->soap_in(soap, "wsdl:definitions", NULL);
  if (soap->error)
  { // handle sloppy WSDLs that import schemas at the top level rather than
    // importing them in <types>
    if (soap->error == SOAP_TAG_MISMATCH && soap->level == 0)
    { soap_retry(soap);
      xs__schema *schema = soap_new_xs__schema(soap, -1);
      schema->soap_in(soap, "xs:schema", NULL);
      if (soap->error)
      { fprintf(stderr, "\nAn error occurred while parsing WSDL or XSD from '%s'\n", loc?loc:"");
        soap_print_fault(soap, stderr);
        soap_print_fault_location(soap, stderr);
        exit(1);
      }
      name = NULL;
      targetNamespace = schema->targetNamespace;
      if (vflag)
        cerr << "Found schema " << (targetNamespace?targetNamespace:"") << " when expecting WSDL" << endl;
      types = soap_new_wsdl__types(soap, -1);
      types->documentation = NULL;
      types->xs__schema_.push_back(schema);
      types->preprocess(*this);
    }
    // check HTTP redirect (socket was closed)
    else if ((soap->error >= 301 && soap->error <= 303) || soap->error == 307)
    { int r = SOAP_ERR;
      fprintf(stderr, "Redirected to '%s'...\n", soap->endpoint);
      if (redirs++ < 10)
        r = read(cwd, soap->endpoint);
      else
        fprintf(stderr, "\nMax redirects exceeded\n");
      redirs--;
      return r;
    }
    else
    { fprintf(stderr, "\nAn error occurred while parsing WSDL from '%s'\n", loc?loc:"");
      soap_print_fault(soap, stderr);
      soap_print_fault_location(soap, stderr);
      exit(1);
    }
  }
  fprintf(stderr, "Done reading '%s'\n", loc?loc:"");
  soap_end_recv(soap);
  if (soap->recvfd > 2)
  { close(soap->recvfd);
    soap->recvfd = -1;
  }
  else
    soap_closesock(soap);
  cwd_path = cwd_temp;
  return SOAP_OK;
}

int wsdl__definitions::preprocess()
{ if (vflag)
    cerr << "Preprocessing wsdl definitions " << (targetNamespace?targetNamespace:"?") << endl;
  // process import
  for (vector<wsdl__import>::iterator im1 = import.begin(); im1 != import.end(); ++im1)
    (*im1).preprocess(*this);
  // merge nested imported WSDLs into single import list
again:
  for (vector<wsdl__import>::iterator im2 = import.begin(); im2 != import.end(); ++im2)
  { if ((*im2).definitionsPtr())
    { for (vector<wsdl__import>::iterator i = (*im2).definitionsPtr()->import.begin(); i != (*im2).definitionsPtr()->import.end(); ++i)
      { bool found = false;
        for (vector<wsdl__import>::iterator j = import.begin(); j != import.end(); ++j)
        { if (((*i).definitionsPtr() == (*j).definitionsPtr())
           || ((*i).location && (*j).location && !strcmp((*i).location, (*j).location)))
          { found = true;
            break;
          }
        }
        if (!found)
        { if (vflag)
            cerr << "Adding imported WSDL " << ((*i).location?(*i).location:"") << " to " << (name?name:"") << " namespace " << (targetNamespace?targetNamespace:"") << endl;
          import.push_back(*i);
          goto again;
        }
      }
    }
  }
  // merge <types>
  for (vector<wsdl__import>::iterator im3 = import.begin(); im3 != import.end(); ++im3)
  { if ((*im3).definitionsPtr() && (*im3).definitionsPtr()->types)
    { if (!types)
      { types = soap_new_wsdl__types(soap, -1);
        types->soap_default(soap);
      }
      // merge <types>, check for duplicates, add namespaces for sloppy imports
      for (vector<xs__schema*>::const_iterator i = (*im3).definitionsPtr()->types->xs__schema_.begin(); i != (*im3).definitionsPtr()->types->xs__schema_.end(); ++i)
      { bool found = false;
        vector<xs__schema*>::const_iterator j;
        if (!(*i)->targetNamespace)
        { (*i)->targetNamespace = targetNamespace;
          if (!Wflag)
	    cerr << "Warning: schema without namespace, assigning " << (targetNamespace?targetNamespace:"?") << endl;
        }
        for (j = types->xs__schema_.begin(); j != types->xs__schema_.end(); ++j)
        { if ((*j)->targetNamespace && !strcmp((*i)->targetNamespace, (*j)->targetNamespace))
          { found = true;
            break;
          }
        }
        // add new schema only if not already in <types>, otherwise merge schema components
        if (found)
        { if (vflag)
            cerr << "Warning: duplicate schema " << ((*i)->targetNamespace?(*i)->targetNamespace:"?") << " merged in WSDL " << (name?name:"") << " namespace " << (targetNamespace?targetNamespace:"?") << endl;
          (*j)->insert(*(*i));
        }
        else
        { if (vflag)
            cerr << "Adding schema " << ((*i)->targetNamespace?(*i)->targetNamespace:"?") << " to types in WSDL " << (name?name:"") << " namespace " << (targetNamespace?targetNamespace:"?") << endl;
          types->xs__schema_.push_back(*i);
        }
      }
    }
  }
  if (types)
    types->preprocess(*this);
  return SOAP_OK;
}

int wsdl__definitions::traverse()
{ if (vflag)
    cerr << "Analyzing wsdl definitions '" << (name?name:"") << "' targetNamespace " << (targetNamespace?targetNamespace:"?") << endl;
  if (updated)
    return SOAP_OK;
  updated = true;
  if (!targetNamespace)
  { if (vflag)
      fprintf(stderr, "Warning: WSDL '%s' has no targetNamespace\n", name?name:"");
    targetNamespace = soap_strdup(soap, "");
  }
  // process import first
  for (vector<wsdl__import>::iterator im = import.begin(); im != import.end(); ++im)
    (*im).traverse(*this);
  // then process the types
  if (types)
    types->traverse(*this);
  // process messages before portTypes
  for (vector<wsdl__message>::iterator mg = message.begin(); mg != message.end(); ++mg)
    (*mg).traverse(*this);
  // process portTypes before bindings
  for (vector<wsdl__portType>::iterator pt = portType.begin(); pt != portType.end(); ++pt)
    (*pt).traverse(*this);
  // process bindings
  for (vector<wsdl__binding>::iterator bg = binding.begin(); bg != binding.end(); ++bg)
    (*bg).traverse(*this);
  // process services
  for (vector<wsdl__service>::iterator sv = service.begin(); sv != service.end(); ++sv)
    (*sv).traverse(*this);
  if (vflag)
    cerr << "End of wsdl definitions '" << (name?name:"") << "' targetNamespace " << (targetNamespace?targetNamespace:"?") << endl;
  for (std::vector<wsp__Policy>::iterator p = wsp__Policy_.begin(); p != wsp__Policy_.end(); ++p)
    (*p).traverse(*this);
  return SOAP_OK;
}

const char *wsdl__definitions::sourceLocation()
{ return location;
}

int wsdl__definitions::error()
{ return soap->error;
}

void wsdl__definitions::print_fault()
{ soap_print_fault(soap, stderr);
  soap_print_fault_location(soap, stderr);
}

void wsdl__definitions::builtinType(const char *type)
{ builtinTypeSet.insert(type);
}

void wsdl__definitions::builtinTypes(const SetOfString& types)
{ for (SetOfString::const_iterator tp = types.begin(); tp != types.end(); ++tp)
    builtinTypeSet.insert(*tp);
}

void wsdl__definitions::builtinElement(const char *element)
{ builtinElementSet.insert(element);
}

void wsdl__definitions::builtinElements(const SetOfString& elements)
{ for (SetOfString::const_iterator el = elements.begin(); el != elements.end(); ++el)
   builtinElementSet.insert(*el);
}

void wsdl__definitions::builtinAttribute(const char *attribute)
{ builtinAttributeSet.insert(attribute);
}

void wsdl__definitions::builtinAttributes(const SetOfString& attributes)
{ for (SetOfString::const_iterator at = attributes.begin(); at != attributes.end(); ++at)
    builtinAttributeSet.insert(*at);
}

const SetOfString& wsdl__definitions::builtinTypes() const
{ return builtinTypeSet;
}

const SetOfString& wsdl__definitions::builtinElements() const
{ return builtinElementSet;
}

const SetOfString& wsdl__definitions::builtinAttributes() const
{ return builtinAttributeSet;
}

int wsdl__service::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl service " << (name?name:"") << endl;
  // process ports
  for (vector<wsdl__port>::iterator i = port.begin(); i != port.end(); ++i)
    (*i).traverse(definitions);
  for (vector<wsp__Policy>::iterator p = wsp__Policy_.begin(); p != wsp__Policy_.end(); ++p)
    (*p).traverse(definitions);
  for (vector<wsp__PolicyReference>::iterator r = wsp__PolicyReference_.begin(); r != wsp__PolicyReference_.end(); ++r)
    (*r).traverse(definitions);
  return SOAP_OK;
}

wsdl__port::wsdl__port()
{ bindingRef = NULL;
}

int wsdl__port::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl port" << endl;
  // search binding name
  const char *token = qname_token(binding, definitions.targetNamespace);
  bindingRef = NULL;
  if (token)
  { for (vector<wsdl__binding>::iterator binding = definitions.binding.begin(); binding != definitions.binding.end(); ++binding)
    { if ((*binding).name && !strcmp((*binding).name, token))
      { bindingRef = &(*binding);
        if (vflag)
          cerr << "Found port " << (name?name:"") << " binding " << (token?token:"") << endl;
        break;
      }
    }
  }
  if (!bindingRef)
  { for (vector<wsdl__import>::iterator import = definitions.import.begin(); import != definitions.import.end(); ++import)
    { wsdl__definitions *importdefinitions = (*import).definitionsPtr();
      if (importdefinitions)
      { token = qname_token(binding, importdefinitions->targetNamespace);
        if (token)
        { for (vector<wsdl__binding>::iterator binding = importdefinitions->binding.begin(); binding != importdefinitions->binding.end(); ++binding)
          { if ((*binding).name && !strcmp((*binding).name, token))
            { bindingRef = &(*binding);
              if (vflag)
                cerr << "Found port " << (name?name:"") << " binding " << (token?token:"") << endl;
              break;
            }
          }
        }
      }
    }
  }
  if (!bindingRef)
    if (!Wflag)
      cerr << "Warning: no port '" << (name?name:"") << "' binding '" << (binding?binding:"") << "' in WSDL definitions '" << (definitions.name?definitions.name:"") << "' namespace " << (definitions.targetNamespace?definitions.targetNamespace:"?") << endl;
  if (wsp__Policy_)
    wsp__Policy_->traverse(definitions);
  if (wsp__PolicyReference_)
    wsp__PolicyReference_->traverse(definitions);
  return SOAP_OK;
}

void wsdl__port::bindingPtr(wsdl__binding *binding)
{ bindingRef = binding;
}

wsdl__binding *wsdl__port::bindingPtr() const
{ return bindingRef;
}

wsdl__binding::wsdl__binding()
{ portTypeRef = NULL;
}

int wsdl__binding::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl bindings" << endl;
  const char *token = qname_token(type, definitions.targetNamespace);
  portTypeRef = NULL;
  if (token)
  { for (vector<wsdl__portType>::iterator portType = definitions.portType.begin(); portType != definitions.portType.end(); ++portType)
    { if ((*portType).name && !strcmp((*portType).name, token))
      { portTypeRef = &(*portType);
        if (vflag)
          cerr << "Found binding " << (name?name:"") << " portType " << (token?token:"") << endl;
        break;
      }
    }
  }
  if (!portTypeRef)
  { for (vector<wsdl__import>::iterator import = definitions.import.begin(); import != definitions.import.end(); ++import)
    { wsdl__definitions *importdefinitions = (*import).definitionsPtr();
      if (importdefinitions)
      { token = qname_token(type, importdefinitions->targetNamespace);
        if (token)
        { for (vector<wsdl__portType>::iterator portType = importdefinitions->portType.begin(); portType != importdefinitions->portType.end(); ++portType)
          { if ((*portType).name && !strcmp((*portType).name, token))
            { portTypeRef = &(*portType);
              if (vflag)
                cerr << "Found binding " << (name?name:"") << " portType " << (token?token:"") << endl;
              break;
            }
          }
        }
      }
    }
  }
  if (!portTypeRef)
    if (!Wflag)
      cerr << "Warning: no binding '" << (name?name:"") << "' portType '" << (type?type:"") << "' in WSDL definitions '" << (definitions.name?definitions.name:"") << "' namespace " << (definitions.targetNamespace?definitions.targetNamespace:"?") << endl;
  for (vector<wsdl__binding_operation>::iterator i = operation.begin(); i != operation.end(); ++i)
    (*i).traverse(definitions, portTypeRef);
  for (vector<wsp__Policy>::iterator p = wsp__Policy_.begin(); p != wsp__Policy_.end(); ++p)
    (*p).traverse(definitions);
  for (vector<wsp__PolicyReference>::iterator r = wsp__PolicyReference_.begin(); r != wsp__PolicyReference_.end(); ++r)
    (*r).traverse(definitions);
  return SOAP_OK;
}

void wsdl__binding::portTypePtr(wsdl__portType *portType)
{ portTypeRef = portType;
}

wsdl__portType *wsdl__binding::portTypePtr() const
{ return portTypeRef;
}

wsdl__binding_operation::wsdl__binding_operation()
{ operationRef = NULL;
}

int wsdl__binding_operation::traverse(wsdl__definitions& definitions, wsdl__portType *portTypeRef)
{ if (vflag)
    cerr << "Analyzing wsdl binding operation" << endl;
  if (input)
    input->traverse(definitions);
  if (output)
    output->traverse(definitions);
  for (vector<wsdl__ext_fault>::iterator i = fault.begin(); i != fault.end(); ++i)
    (*i).traverse(definitions);
  operationRef = NULL;
  if (name && portTypeRef)
  { for (vector<wsdl__operation>::iterator i = portTypeRef->operation.begin(); i != portTypeRef->operation.end(); ++i)
    { if ((*i).name && !strcmp((*i).name, name))
      { if ((!input || !input->name || ((*i).input && (*i).input->name && !strcmp((*i).input->name, input->name))) && (!output || !output->name || ((*i).output && (*i).output->name && !strcmp((*i).output->name, output->name))))
        { operationRef = &(*i);
          if (vflag)
            cerr << "Found operation " << (name?name:"") << endl;
          break;
        }
      }
    }
  }
  if (!operationRef)
  { if (!Wflag)
      cerr << "Warning: no matching portType operation '" << (name?name:"") << "' in WSDL definitions '" << (definitions.name?definitions.name:"") << "' namespace " << (definitions.targetNamespace?definitions.targetNamespace:"?") << endl;
  }
  else
  { for (vector<wsdl__ext_fault>::iterator i = fault.begin(); i != fault.end(); ++i)
    { if ((*i).name)
      { for (vector<wsdl__fault>::iterator j = operationRef->fault.begin(); j != operationRef->fault.end(); ++j)
        { if ((*j).name && !strcmp((*j).name, (*i).name))
          { (*i).messagePtr((*j).messagePtr());
            if (vflag)
              cerr << "Found fault " << ((*j).name?(*j).name:"") << " message " << endl;
            break;
          }
        }
      }
      else if ((*i).soap__fault_ && (*i).soap__fault_->name) // try the soap:fault name, this is not elegant, but neither is WSDL 1.1 
      { for (vector<wsdl__fault>::iterator j = operationRef->fault.begin(); j != operationRef->fault.end(); ++j)
        { if ((*j).name && !strcmp((*j).name, (*i).soap__fault_->name))
          { (*i).messagePtr((*j).messagePtr());
            if (vflag)
              cerr << "Found fault " << ((*j).name?(*j).name:"") << " message " << endl;
            break;
          }
        }
      }
      if (!(*i).messagePtr())
        if (!Wflag)
	  cerr << "Warning: no soap:fault message in WSDL definitions '" << (definitions.name?definitions.name:"") << "' operation '" << (name?name:"") << "' namespace " << (definitions.targetNamespace?definitions.targetNamespace:"?") << endl;
    }
  }
  if (wsp__Policy_)
    wsp__Policy_->traverse(definitions);
  if (wsp__PolicyReference_)
    wsp__PolicyReference_->traverse(definitions);
  return SOAP_OK;
}

void wsdl__binding_operation::operationPtr(wsdl__operation *operation)
{ operationRef = operation;
}

wsdl__operation *wsdl__binding_operation::operationPtr() const
{ return operationRef;
}

int wsdl__ext_input::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl ext input" << endl;
  for (vector<soap__header>::iterator hd = soap__header_.begin(); hd != soap__header_.end(); ++hd)
    (*hd).traverse(definitions);
  if (mime__multipartRelated_)
    mime__multipartRelated_->traverse(definitions);
  if (wsp__Policy_)
    wsp__Policy_->traverse(definitions);
  if (wsp__PolicyReference_)
    wsp__PolicyReference_->traverse(definitions);
  return SOAP_OK;
}

int wsdl__ext_output::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl ext output" << endl;
  for (vector<soap__header>::iterator hd = soap__header_.begin(); hd != soap__header_.end(); ++hd)
    (*hd).traverse(definitions);
  if (mime__multipartRelated_)
    mime__multipartRelated_->traverse(definitions);
  if (wsp__Policy_)
    wsp__Policy_->traverse(definitions);
  if (wsp__PolicyReference_)
    wsp__PolicyReference_->traverse(definitions);
  return SOAP_OK;
}

wsdl__ext_fault::wsdl__ext_fault()
{ messageRef = NULL;
}

int wsdl__ext_fault::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl ext fault" << endl;
  messageRef = NULL;
  if (wsp__Policy_)
    wsp__Policy_->traverse(definitions);
  if (wsp__PolicyReference_)
    wsp__PolicyReference_->traverse(definitions);
  return SOAP_OK;
}

void wsdl__ext_fault::messagePtr(wsdl__message *message)
{ messageRef = message;
}

wsdl__message *wsdl__ext_fault::messagePtr() const
{ return messageRef;
}

int wsdl__portType::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl portType" << endl;
  for (vector<wsdl__operation>::iterator i = operation.begin(); i != operation.end(); ++i)
    (*i).traverse(definitions);
  if (wsp__Policy_)
    wsp__Policy_->traverse(definitions);
  if (wsp__PolicyReference_)
    wsp__PolicyReference_->traverse(definitions);
  return SOAP_OK;
}

int wsdl__operation::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl operation" << endl;
  if (input)
    input->traverse(definitions);
  if (output)
    output->traverse(definitions);
  for (vector<wsdl__fault>::iterator i = fault.begin(); i != fault.end(); ++i)
    (*i).traverse(definitions);
  if (wsp__Policy_)
    wsp__Policy_->traverse(definitions);
  if (wsp__PolicyReference_)
    wsp__PolicyReference_->traverse(definitions);
  return SOAP_OK;
}

wsdl__input::wsdl__input()
{ messageRef = NULL;
}

int wsdl__input::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl input" << endl;
  const char *token = qname_token(message, definitions.targetNamespace);
  messageRef = NULL;
  if (token)
  { for (vector<wsdl__message>::iterator message = definitions.message.begin(); message != definitions.message.end(); ++message)
    { if ((*message).name && !strcmp((*message).name, token))
      { messageRef = &(*message);
        if (vflag)
          cerr << "Found input " << (name?name:"") << " message " << (token?token:"") << endl;
        break;
      }
    }
  }
  if (!messageRef)
  { for (vector<wsdl__import>::iterator import = definitions.import.begin(); import != definitions.import.end(); ++import)
    { wsdl__definitions *importdefinitions = (*import).definitionsPtr();
      if (importdefinitions)
      { token = qname_token(message, importdefinitions->targetNamespace);
        if (token)
        { for (vector<wsdl__message>::iterator message = importdefinitions->message.begin(); message != importdefinitions->message.end(); ++message)
          { if ((*message).name && !strcmp((*message).name, token))
            { messageRef = &(*message);
              if (vflag)
                cerr << "Found input " << (name?name:"") << " message " << (token?token:"") << endl;
              break;
            }
          }
        }
      }
    }
  }
  if (!messageRef)
    if (!Wflag)
      cerr << "Warning: no input '" << (name?name:"") << "' message '" << (message?message:"") << "' in WSDL definitions '" << (definitions.name?definitions.name:"") << "' namespace " << (definitions.targetNamespace?definitions.targetNamespace:"?") << endl;
  if (wsp__Policy_)
    wsp__Policy_->traverse(definitions);
  if (wsp__PolicyReference_)
    wsp__PolicyReference_->traverse(definitions);
  return SOAP_OK;
}

void wsdl__input::messagePtr(wsdl__message *message)
{ messageRef = message;
}

wsdl__message *wsdl__input::messagePtr() const
{ return messageRef;
}

wsdl__output::wsdl__output()
{ messageRef = NULL;
}

int wsdl__output::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl output" << endl;
  const char *token = qname_token(message, definitions.targetNamespace);
  messageRef = NULL;
  if (token)
  { for (vector<wsdl__message>::iterator message = definitions.message.begin(); message != definitions.message.end(); ++message)
    { if ((*message).name && !strcmp((*message).name, token))
      { messageRef = &(*message);
        if (vflag)
          cerr << "Found output " << (name?name:"") << " message " << (token?token:"") << endl;
        break;
      }
    }
  }
  if (!messageRef)
  { for (vector<wsdl__import>::iterator import = definitions.import.begin(); import != definitions.import.end(); ++import)
    { wsdl__definitions *importdefinitions = (*import).definitionsPtr();
      if (importdefinitions)
      { token = qname_token(message, importdefinitions->targetNamespace);
        if (token)
        { for (vector<wsdl__message>::iterator message = importdefinitions->message.begin(); message != importdefinitions->message.end(); ++message)
          { if ((*message).name && !strcmp((*message).name, token))
            { messageRef = &(*message);
              if (vflag)
                cerr << "Found output " << (name?name:"") << " message " << (token?token:"") << endl;
              break;
            }
          }
        }
      }
    }
  }
  if (!messageRef)
    if (!Wflag)
      cerr << "Warning: no output '" << (name?name:"") << "' message '" << (message?message:"") << "' in WSDL definitions '" << (definitions.name?definitions.name:"") << "' namespace " << (definitions.targetNamespace?definitions.targetNamespace:"?") << endl;
  if (wsp__Policy_)
    wsp__Policy_->traverse(definitions);
  if (wsp__PolicyReference_)
    wsp__PolicyReference_->traverse(definitions);
  return SOAP_OK;
}

void wsdl__output::messagePtr(wsdl__message *message)
{ messageRef = message;
}

wsdl__message *wsdl__output::messagePtr() const
{ return messageRef;
}

wsdl__fault::wsdl__fault()
{ messageRef = NULL;
}

int wsdl__fault::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl fault" << endl;
  const char *token = qname_token(message, definitions.targetNamespace);
  messageRef = NULL;
  if (token)
  { for (vector<wsdl__message>::iterator message = definitions.message.begin(); message != definitions.message.end(); ++message)
    { if ((*message).name && !strcmp((*message).name, token))
      { messageRef = &(*message);
        if (vflag)
          cerr << "Found fault " << (name?name:"") << " message " << (token?token:"") << endl;
        break;
      }
    }
  }
  if (!messageRef)
  { for (vector<wsdl__import>::iterator import = definitions.import.begin(); import != definitions.import.end(); ++import)
    { wsdl__definitions *importdefinitions = (*import).definitionsPtr();
      if (importdefinitions)
      { token = qname_token(message, importdefinitions->targetNamespace);
        if (token)
        { for (vector<wsdl__message>::iterator message = importdefinitions->message.begin(); message != importdefinitions->message.end(); ++message)
          { if ((*message).name && !strcmp((*message).name, token))
            { messageRef = &(*message);
              if (vflag)
                cerr << "Found output " << (name?name:"") << " message " << (token?token:"") << endl;
              break;
            }
          }
        }
      }
    }
  }
  if (!messageRef)
    if (!Wflag)
      cerr << "Warning: no fault '" << (name?name:"") << "' message '" << (message?message:"") << "' in WSDL definitions '" << (definitions.name?definitions.name:"") << "' namespace " << (definitions.targetNamespace?definitions.targetNamespace:"?") << endl;
  if (wsp__Policy_)
    wsp__Policy_->traverse(definitions);
  if (wsp__PolicyReference_)
    wsp__PolicyReference_->traverse(definitions);
  return SOAP_OK;
}

void wsdl__fault::messagePtr(wsdl__message *message)
{ messageRef = message;
}

wsdl__message *wsdl__fault::messagePtr() const
{ return messageRef;
}

int wsdl__message::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl message" << endl;
  for (vector<wsdl__part>::iterator i = part.begin(); i != part.end(); ++i)
    (*i).traverse(definitions);
  for (vector<wsp__Policy>::iterator p = wsp__Policy_.begin(); p != wsp__Policy_.end(); ++p)
    (*p).traverse(definitions);
  for (vector<wsp__PolicyReference>::iterator r = wsp__PolicyReference_.begin(); r != wsp__PolicyReference_.end(); ++r)
    (*r).traverse(definitions);
  return SOAP_OK;
}

wsdl__part::wsdl__part()
{ elementRef = NULL;
  simpleTypeRef = NULL;
  complexTypeRef = NULL;
}

int wsdl__part::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl part" << endl;
  elementRef = NULL;
  simpleTypeRef = NULL;
  complexTypeRef = NULL;
  if (definitions.types)
  { for (vector<xs__schema*>::iterator schema = definitions.types->xs__schema_.begin(); schema != definitions.types->xs__schema_.end(); ++schema)
    { const char *token = qname_token(element, (*schema)->targetNamespace);
      if (token)
      { for (vector<xs__element>::iterator element = (*schema)->element.begin(); element != (*schema)->element.end(); ++element)
        { if ((*element).name && !strcmp((*element).name, token))
          { elementRef = &(*element);
            if (vflag)
              cerr << "Found part " << (name?name:"") << " element " << (token?token:"") << endl;
            break;
          }
        }
      }
      token = qname_token(type, (*schema)->targetNamespace);
      if (token)
      { for (vector<xs__simpleType>::iterator simpleType = (*schema)->simpleType.begin(); simpleType != (*schema)->simpleType.end(); ++simpleType)
        { if ((*simpleType).name && !strcmp((*simpleType).name, token))
          { simpleTypeRef = &(*simpleType);
            if (vflag)
              cerr << "Found part " << (name?name:"") << " simpleType " << (token?token:"") << endl;
            break;
          }
        }
      }
      token = qname_token(type, (*schema)->targetNamespace);
      if (token)
      { for (vector<xs__complexType>::iterator complexType = (*schema)->complexType.begin(); complexType != (*schema)->complexType.end(); ++complexType)
        { if ((*complexType).name && !strcmp((*complexType).name, token))
          { complexTypeRef = &(*complexType);
            if (vflag)
              cerr << "Found part " << (name?name:"") << " complexType " << (token?token:"") << endl;
            break;
          }
        }
      }
    }
  }
  if (!elementRef && !simpleTypeRef && !complexTypeRef)
  { if (element)
    { if (is_builtin_qname(element))
        definitions.builtinElement(element);
      else
        if (!Wflag)
	  cerr << "Warning: no part '" << (name?name:"") << "' element '" << element << "' in WSDL definitions '" << (definitions.name?definitions.name:"") << "' namespace " << (definitions.targetNamespace?definitions.targetNamespace:"?") << endl;
    }
    else if (type)
    { if (is_builtin_qname(type))
        definitions.builtinType(type);
      else
        if (!Wflag)
	  cerr << "Warning: no part '" << (name?name:"") << "' type '" << type << "' in WSDL definitions '" << (definitions.name?definitions.name:"") << "' namespace " << (definitions.targetNamespace?definitions.targetNamespace:"?") << endl;
    }
    else
      if (!Wflag)
        cerr << "Warning: no part '" << (name?name:"") << "' element or type in WSDL definitions '" << (definitions.name?definitions.name:"") << "' namespace " << (definitions.targetNamespace?definitions.targetNamespace:"?") << endl;
  }
  return SOAP_OK;
}

void wsdl__part::elementPtr(xs__element *element)
{ elementRef = element;
}

void wsdl__part::simpleTypePtr(xs__simpleType *simpleType)
{ simpleTypeRef = simpleType;
}

void wsdl__part::complexTypePtr(xs__complexType *complexType)
{ complexTypeRef = complexType;
}

xs__element *wsdl__part::elementPtr() const
{ return elementRef;
}

xs__simpleType *wsdl__part::simpleTypePtr() const
{ return simpleTypeRef;
}

xs__complexType *wsdl__part::complexTypePtr() const
{ return complexTypeRef;
}

int wsdl__types::preprocess(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Preprocessing wsdl types" << endl;
  // set the location of each schema in <types> to the WSDL's location
  for (vector<xs__schema*>::iterator schema0 = xs__schema_.begin(); schema0 != xs__schema_.end(); ++schema0)
  { if (!(*schema0)->sourceLocation())
      (*schema0)->sourceLocation(definitions.sourceLocation());
  }
again:
  // link imported schemas, need to repeat when <types> is extended with new imported schema (from inside another schema, etc.)
  for (vector<xs__schema*>::iterator schema1 = xs__schema_.begin(); schema1 != xs__schema_.end(); ++schema1)
  { for (vector<xs__import>::iterator import = (*schema1)->import.begin(); import != (*schema1)->import.end(); ++import)
    { if ((*import).namespace_ && !(*import).schemaPtr())
      { for (vector<xs__schema*>::const_iterator schema2 = xs__schema_.begin(); schema2 != xs__schema_.end(); ++schema2)
        { if (schema2 != schema1 && (*schema2)->targetNamespace && !strcmp((*import).namespace_, (*schema2)->targetNamespace))
          { (*import).schemaPtr(*schema2);
            break;
          }
        }
      }
    }
  }
  // if a schema is imported but not in <types> then get it
  for (vector<xs__schema*>::iterator schema2 = xs__schema_.begin(); schema2 != xs__schema_.end(); ++schema2)
  { for (vector<xs__import>::iterator import = (*schema2)->import.begin(); import != (*schema2)->import.end(); ++import)
    { bool found = false;
      if ((*import).schemaPtr())
        found = true;
      if (vflag)
        fprintf(stderr, "Preprocessing schema %s import %s\n", (*schema2)->targetNamespace, (*import).namespace_?(*import).namespace_:"?");
      if (!found && (*import).namespace_)
      { if ((*import).schemaPtr())
          found = true;
        else
        { for (vector<xs__schema*>::const_iterator schema3 = xs__schema_.begin(); schema3 != xs__schema_.end(); ++schema3)
          { if (schema3 != schema2 && (*schema3)->targetNamespace && !strcmp((*import).namespace_, (*schema3)->targetNamespace))
            { found = true;
              if (vflag)
                fprintf(stderr, "Schema %s already present\n", (*schema2)->targetNamespace);
              break;
            }
          }
        }
        if (!found)
        { for (SetOfString::const_iterator i = exturis.begin(); i != exturis.end(); ++i)
          { if (!soap_tag_cmp((*import).namespace_, *i))
            { found = true;
              break;
            }
          }
        }
      }
      if (!found && !iflag) // don't import any of the schemas in the .nsmap table (or when -i option is used)
      { xs__schema *importschema;
        importschema = (*import).schemaPtr();
        if (!importschema)
        { const char *s = (*import).schemaLocation;
          if (!s)
            s = (*import).namespace_;
          if (!s)
            continue;
          importschema = new xs__schema(definitions.soap, (*schema2)->sourceLocation(), s);
          if (!(*import).namespace_)
          { if ((*schema2)->targetNamespace)
              (*import).namespace_ = (*schema2)->targetNamespace;
            else if (importschema->targetNamespace)
              (*import).namespace_ = importschema->targetNamespace;
            else
              (*import).namespace_ = soap_strdup(definitions.soap, "");
          }
          if (!importschema->targetNamespace || !*importschema->targetNamespace)
            importschema->targetNamespace = (*import).namespace_;
          else if ((*import).namespace_ && strcmp(importschema->targetNamespace, (*import).namespace_))
            cerr << "Schema import namespace " << ((*import).namespace_?(*import).namespace_:"?") << " does not correspond to imported targetNamespace " << importschema->targetNamespace << endl;
        }
        for (vector<xs__schema*>::const_iterator schema3 = xs__schema_.begin(); schema3 != xs__schema_.end(); ++schema3)
        { if (schema3 != schema2 && (*schema3)->targetNamespace && !strcmp((*import).namespace_, (*schema3)->targetNamespace))
          { found = true;
            (*import).schemaPtr(*schema3);
            break;
          }
        }
        if (!found)
        { (*import).schemaPtr(importschema);
          xs__schema_.push_back(importschema);
          if (vflag)
            fprintf(stderr, "Adding schema %s\n", importschema->targetNamespace);
          goto again;
        }
      }
    }
  }
  return SOAP_OK;
}

int wsdl__types::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl types" << endl;
  for (vector<xs__schema*>::iterator schema3 = xs__schema_.begin(); schema3 != xs__schema_.end(); ++schema3)
  { // artificially extend the <import> of each schema to include others so when we traverse schemas we can resolve references
    for (vector<xs__schema*>::iterator importschema = xs__schema_.begin(); importschema != xs__schema_.end(); ++importschema)
    { if (schema3 != importschema && (*importschema)->targetNamespace)
      { xs__import *import = soap_new_xs__import(definitions.soap, -1);
        import->namespace_ = (*importschema)->targetNamespace;
        import->schemaPtr(*importschema);
        (*schema3)->import.push_back(*import);
      }
    }
    // check and report
    for (vector<xs__import>::iterator import = (*schema3)->import.begin(); import != (*schema3)->import.end(); ++import)
    { if ((*import).namespace_)
      { bool found = false;
        for (vector<xs__schema*>::const_iterator importschema = xs__schema_.begin(); importschema != xs__schema_.end(); ++importschema)
        { if ((*importschema)->targetNamespace && !strcmp((*import).namespace_, (*importschema)->targetNamespace))
          { found = true;
            break;
          }
        }
        if (!found && vflag)
          cerr << "Schema import namespace " << (*import).namespace_ << " refers to an unknown Schema" << endl;
      }
      else if (!Wflag)
	cerr << "Warning: schema import " << ((*import).schemaLocation ? (*import).schemaLocation : "") << " has no namespace" << endl;
    }
  }
  // traverse the schemas
  for (vector<xs__schema*>::iterator schema4 = xs__schema_.begin(); schema4 != xs__schema_.end(); ++schema4)
    (*schema4)->traverse();
  // find all built-in types, elements, and attributes
  for (vector<xs__schema*>::iterator schema5 = xs__schema_.begin(); schema5 != xs__schema_.end(); ++schema5)
  { if (vflag)
      for (SetOfString::const_iterator i = (*schema5)->builtinTypes().begin(); i != (*schema5)->builtinTypes().end(); ++i)
        cerr << "Found built-in schema type: " << (*i) << endl;
    definitions.builtinTypes((*schema5)->builtinTypes());
    definitions.builtinElements((*schema5)->builtinElements());
    definitions.builtinAttributes((*schema5)->builtinAttributes());
  }
  return SOAP_OK;
}

int wsdl__import::preprocess(wsdl__definitions& definitions)
{ bool found = false;
  if (vflag)
    cerr << "Preprocess wsdl import " << (location?location:"") << endl;
  definitionsRef = NULL;
  if (namespace_)
  { for (SetOfString::const_iterator i = exturis.begin(); i != exturis.end(); ++i)
    { if (!soap_tag_cmp(namespace_, *i))
      { found = true;
        break;
      }
    }
  }
  if (!found && location)
  { // parse imported definitions
    const char *source = definitions.sourceLocation();
    if (vflag)
      cerr << "Importing wsdl for " << (source?source:"(source location not set)") << endl;
    definitionsRef = new wsdl__definitions(definitions.soap, source, location);
    if (!definitionsRef)
      return SOAP_EOF;
    if (!namespace_)
      namespace_ = definitionsRef->targetNamespace;
    else if (!definitionsRef->targetNamespace || !*definitionsRef->targetNamespace)
      definitionsRef->targetNamespace = namespace_;
    else if (strcmp(namespace_, definitionsRef->targetNamespace))
      cerr << "Error: WSDL definitions/import " << location << " namespace " << namespace_ << " does not match imported targetNamespace " << definitionsRef->targetNamespace << endl;
  }
  else if (!found)
    cerr << "WSDL definitions/import has no location attribute" << endl;
  return SOAP_OK;
}

int wsdl__import::traverse(wsdl__definitions& definitions)
{ if (vflag)
    cerr << "Analyzing wsdl import " << (location?location:"") << endl;
  if (definitionsRef)
  { for (vector<wsdl__message>::iterator mg = definitionsRef->message.begin(); mg != definitionsRef->message.end(); ++mg)
      (*mg).traverse(definitions);
    // process portTypes before bindings
    for (vector<wsdl__portType>::iterator pt = definitionsRef->portType.begin(); pt != definitionsRef->portType.end(); ++pt)
      (*pt).traverse(definitions);
    // process bindings
    for (vector<wsdl__binding>::iterator bg = definitionsRef->binding.begin(); bg != definitionsRef->binding.end(); ++bg)
      (*bg).traverse(definitions);
    // process services
    for (vector<wsdl__service>::iterator sv = definitionsRef->service.begin(); sv != definitionsRef->service.end(); ++sv)
      (*sv).traverse(definitions);
  }
  return SOAP_OK;
}

void wsdl__import::definitionsPtr(wsdl__definitions *definitions)
{ definitionsRef = definitions;
}

wsdl__definitions *wsdl__import::definitionsPtr() const
{ return definitionsRef;
}

wsdl__import::wsdl__import()
{ definitionsRef = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
//	streams
//
////////////////////////////////////////////////////////////////////////////////

ostream &operator<<(ostream &o, const wsdl__definitions &e)
{ if (!e.soap)
  { struct soap soap;
    soap_init2(&soap, SOAP_IO_DEFAULT, SOAP_XML_TREE | SOAP_C_UTFSTRING);
    soap_set_namespaces(&soap, namespaces);
    e.soap_serialize(&soap);
    soap_begin_send(&soap);
    e.soap_out(&soap, "wsdl:definitions", 0, NULL);
    soap_end_send(&soap);
    soap_destroy(&soap);
    soap_end(&soap);
    soap_done(&soap);
  }
  else
  { ostream *os = e.soap->os;
    e.soap->os = &o;
    e.soap_serialize(e.soap);
    soap_begin_send(e.soap);
    e.soap_out(e.soap, "wsdl:definitions", 0, NULL);
    soap_end_send(e.soap);
    e.soap->os = os;
  }
  return o;
}

istream &operator>>(istream &i, wsdl__definitions &e)
{ if (!e.soap)
  { e.soap = soap_new1(SOAP_XML_TREE | SOAP_C_UTFSTRING);
    soap_set_namespaces(e.soap, namespaces);
  }
  istream *is = e.soap->is;
  e.soap->is = &i;
  if (soap_begin_recv(e.soap)
   || !e.soap_in(e.soap, "wsdl:definitions", NULL)
   || soap_end_recv(e.soap))
  { // handle error? Note: e.soap->error is set and app should check
  }
  e.soap->is = is;
  return i;
}

////////////////////////////////////////////////////////////////////////////////
//
//	Miscellaneous
//
////////////////////////////////////////////////////////////////////////////////

extern "C" {

int warn_ignore(struct soap *soap, const char *tag)
{ // We don't warn if the omitted element was an annotation or a documentation in an unexpected place
  if (soap->mustUnderstand)
    fprintf(stderr, "Error: element '%s' at level %d must be understood\n", tag, soap->level);
  if (!Wflag
   && soap_match_tag(soap, tag, "xs:annotation")
   && soap_match_tag(soap, tag, "xs:documentation")
   && soap_match_tag(soap, tag, "xs:appinfo"))
    fprintf(stderr, "Warning: unexpected element '%s' at level %d is skipped (safe to ignore)\n", tag, soap->level);
  if (soap->body && !soap_string_in(soap, 0, -1, -1))
    return soap->error;
  return SOAP_OK;
}

int show_ignore(struct soap *soap, const char *tag)
{ warn_ignore(soap, tag);
  soap_print_fault_location(soap, stderr);
  return SOAP_OK;
}

} // end extern "C"
