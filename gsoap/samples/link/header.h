/*	header.h

	Defines SOAP Header data structure shared by client and service modules

	Copyright (C) 2000-2002 Robert A. van Engelen. All Rights Reserved.

*/

//gsoap h schema namespace: http://websrv.cs.fsu.edu/~engelen/h.xsd

struct h__authentication
{ char *userid;
  char *passwd;
};

struct SOAP_ENV__Header
{ struct h__authentication *h__credentials;
};

