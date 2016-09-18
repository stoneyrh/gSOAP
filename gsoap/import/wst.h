/*
	wst.h

	WS-Trust 2005/12 with SAML 2.0
	Generated with:
	wsdl2h -cuyx -o wst.h -t WS/WS-typemap.dat WS/WS-Trust.xsd

	- Removed //gsoapopt
	- Changed http://docs.oasis-open.org/ws-sx/ws-trust/200512 to remove trailing /
	- Changed //gsoap wst schema namespace directive to import directive
	- Added #import "wsp_appliesto.h"
	- Added #import "wstx.h" at the end of these definitions

*/

/******************************************************************************\
 *                                                                            *
 * Definitions                                                                *
 *   http://docs.oasis-open.org/ws-sx/ws-trust/200512/                        *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Import                                                                     *
 *                                                                            *
\******************************************************************************/

#import "wsse.h"	// wsse = <http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd>
#import "wsu.h"	// wsu = <http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd>
#import "wsa5.h"	// wsa5 = <http://www.w3.org/2005/08/addressing>
#import "wsp_appliesto.h"

/******************************************************************************\
 *                                                                            *
 * Schema Namespaces                                                          *
 *                                                                            *
\******************************************************************************/

#define SOAP_NAMESPACE_OF_wst	"http://docs.oasis-open.org/ws-sx/ws-trust/200512"
//gsoap wst   schema import:	http://docs.oasis-open.org/ws-sx/ws-trust/200512
//gsoap wst   schema elementForm:	qualified
//gsoap wst   schema attributeForm:	unqualified

/******************************************************************************\
 *                                                                            *
 * Built-in Schema Types and Top-Level Elements and Attributes                *
 *                                                                            *
\******************************************************************************/

// Imported XSD type ""http://www.w3.org/2005/08/addressing":EndpointReferenceType" defined by wsa5__EndpointReferenceType.
/// Imported element ""http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd":SecurityTokenReference" from typemap WS/WS-typemap.dat.

/// @brief Typedef synonym for struct wst__RequestSecurityTokenType.
typedef struct wst__RequestSecurityTokenType wst__RequestSecurityTokenType;
/// @brief Typedef synonym for struct wst__RequestSecurityTokenResponseType.
typedef struct wst__RequestSecurityTokenResponseType wst__RequestSecurityTokenResponseType;
/// Imported complexType "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedSecurityTokenType from typemap "WS/WS-typemap.dat".
#import "saml1.h"
#import "saml2.h"
typedef struct wst__RequestedSecurityTokenType
{	saml1__AssertionType *saml1__Assertion;
	saml2__AssertionType *saml2__Assertion;
        _wsse__SecurityTokenReference *wsse__SecurityTokenReference;
} wst__RequestedSecurityTokenType;

/// @brief Typedef synonym for struct wst__BinarySecretType.
typedef struct wst__BinarySecretType wst__BinarySecretType;
/// @brief Typedef synonym for struct wst__ClaimsType.
typedef struct wst__ClaimsType wst__ClaimsType;
/// Imported complexType "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":EntropyType from typemap "WS/WS-typemap.dat".
typedef struct wst__EntropyType
{	struct wst__BinarySecretType *BinarySecret;
} wst__EntropyType;

/// @brief Typedef synonym for struct wst__LifetimeType.
typedef struct wst__LifetimeType wst__LifetimeType;
/// @brief Typedef synonym for struct wst__RequestSecurityTokenCollectionType.
typedef struct wst__RequestSecurityTokenCollectionType wst__RequestSecurityTokenCollectionType;
/// @brief Typedef synonym for struct wst__RequestSecurityTokenResponseCollectionType.
typedef struct wst__RequestSecurityTokenResponseCollectionType wst__RequestSecurityTokenResponseCollectionType;
/// @brief Typedef synonym for struct wst__RequestedReferenceType.
typedef struct wst__RequestedReferenceType wst__RequestedReferenceType;
/// @brief Typedef synonym for struct wst__RequestedProofTokenType.
typedef struct wst__RequestedProofTokenType wst__RequestedProofTokenType;
/// @brief Typedef synonym for struct wst__RenewTargetType.
typedef struct wst__RenewTargetType wst__RenewTargetType;
/// @brief Typedef synonym for struct wst__AllowPostdatingType.
typedef struct wst__AllowPostdatingType wst__AllowPostdatingType;
/// @brief Typedef synonym for struct wst__RenewingType.
typedef struct wst__RenewingType wst__RenewingType;
/// @brief Typedef synonym for struct wst__CancelTargetType.
typedef struct wst__CancelTargetType wst__CancelTargetType;
/// @brief Typedef synonym for struct wst__RequestedTokenCancelledType.
typedef struct wst__RequestedTokenCancelledType wst__RequestedTokenCancelledType;
/// @brief Typedef synonym for struct wst__ValidateTargetType.
typedef struct wst__ValidateTargetType wst__ValidateTargetType;
/// @brief Typedef synonym for struct wst__StatusType.
typedef struct wst__StatusType wst__StatusType;
/// @brief Typedef synonym for struct wst__SignChallengeType.
typedef struct wst__SignChallengeType wst__SignChallengeType;
/// @brief Typedef synonym for struct wst__BinaryExchangeType.
typedef struct wst__BinaryExchangeType wst__BinaryExchangeType;
/// @brief Typedef synonym for struct wst__RequestKETType.
typedef struct wst__RequestKETType wst__RequestKETType;
/// @brief Typedef synonym for struct wst__KeyExchangeTokenType.
typedef struct wst__KeyExchangeTokenType wst__KeyExchangeTokenType;
/// Imported complexType "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":AuthenticatorType from typemap "WS/WS-typemap.dat".
typedef struct wst__AuthenticatorType
{	char *CombinedHash;
} wst__AuthenticatorType;

/// @brief Typedef synonym for struct wst__OnBehalfOfType.
typedef struct wst__OnBehalfOfType wst__OnBehalfOfType;
/// @brief Typedef synonym for struct wst__EncryptionType.
typedef struct wst__EncryptionType wst__EncryptionType;
/// @brief Typedef synonym for struct wst__ProofEncryptionType.
typedef struct wst__ProofEncryptionType wst__ProofEncryptionType;
/// @brief Typedef synonym for struct wst__UseKeyType.
typedef struct wst__UseKeyType wst__UseKeyType;
/// @brief Typedef synonym for struct wst__DelegateToType.
typedef struct wst__DelegateToType wst__DelegateToType;
/// @brief Typedef synonym for struct wst__ParticipantsType.
typedef struct wst__ParticipantsType wst__ParticipantsType;
/// @brief Typedef synonym for struct wst__ParticipantType.
typedef struct wst__ParticipantType wst__ParticipantType;

/******************************************************************************\
 *                                                                            *
 * Schema Types and Top-Level Elements and Attributes                         *
 *   http://docs.oasis-open.org/ws-sx/ws-trust/200512/                        *
 *                                                                            *
\******************************************************************************/

/// Imported simpleType "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestTypeOpenEnum from typemap "WS/WS-typemap.dat".
// simpleType definition intentionally left blank.
/// Imported simpleType "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":BinarySecretTypeOpenEnum from typemap "WS/WS-typemap.dat".
// simpleType definition intentionally left blank.
/// Imported simpleType "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ComputedKeyOpenEnum from typemap "WS/WS-typemap.dat".
// simpleType definition intentionally left blank.
/// Imported simpleType "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":StatusCodeOpenEnum from typemap "WS/WS-typemap.dat".
// simpleType definition intentionally left blank.
/// Imported simpleType "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":KeyTypeOpenEnum from typemap "WS/WS-typemap.dat".
// simpleType definition intentionally left blank.
/// Imported simpleType "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestTypeEnum from typemap "WS/WS-typemap.dat".
// simpleType definition intentionally left blank.
/// Imported simpleType "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":BinarySecretTypeEnum from typemap "WS/WS-typemap.dat".
// simpleType definition intentionally left blank.
/// Imported simpleType "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ComputedKeyEnum from typemap "WS/WS-typemap.dat".
// simpleType definition intentionally left blank.
/// Imported simpleType "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":StatusCodeEnum from typemap "WS/WS-typemap.dat".
// simpleType definition intentionally left blank.
/// Imported simpleType "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":KeyTypeEnum from typemap "WS/WS-typemap.dat".
// simpleType definition intentionally left blank.

/******************************************************************************\
 *                                                                            *
 * Schema Complex Types and Top-Level Elements                                *
 *   http://docs.oasis-open.org/ws-sx/ws-trust/200512/                        *
 *                                                                            *
\******************************************************************************/

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestSecurityTokenType is a complexType.
///
/// <PRE><BLOCKQUOTE>
///   Actual content model is non-deterministic, hence wildcard. The following shows intended content model:
///   <xs:element ref='wst:TokenType' minOccurs='0' />
///   <xs:element ref='wst:RequestType' />
///   <xs:element ref='wsp:AppliesTo' minOccurs='0' />
///   <xs:element ref='wst:Claims' minOccurs='0' />
///   <xs:element ref='wst:Entropy' minOccurs='0' />
///   <xs:element ref='wst:Lifetime' minOccurs='0' />
///   <xs:element ref='wst:AllowPostdating' minOccurs='0' />
///   <xs:element ref='wst:Renewing' minOccurs='0' />
///   <xs:element ref='wst:OnBehalfOf' minOccurs='0' />
///   <xs:element ref='wst:Issuer' minOccurs='0' />
///   <xs:element ref='wst:AuthenticationType' minOccurs='0' />
///   <xs:element ref='wst:KeyType' minOccurs='0' />
///   <xs:element ref='wst:KeySize' minOccurs='0' />
///   <xs:element ref='wst:SignatureAlgorithm' minOccurs='0' />
///   <xs:element ref='wst:Encryption' minOccurs='0' />
///   <xs:element ref='wst:EncryptionAlgorithm' minOccurs='0' />
///   <xs:element ref='wst:CanonicalizationAlgorithm' minOccurs='0' />
///   <xs:element ref='wst:ProofEncryption' minOccurs='0' />
///   <xs:element ref='wst:UseKey' minOccurs='0' />
///   <xs:element ref='wst:SignWith' minOccurs='0' />
///   <xs:element ref='wst:EncryptWith' minOccurs='0' />
///   <xs:element ref='wst:DelegateTo' minOccurs='0' />
///   <xs:element ref='wst:Forwardable' minOccurs='0' />
///   <xs:element ref='wst:Delegatable' minOccurs='0' />
///   <xs:element ref='wsp:Policy' minOccurs='0' />
///   <xs:element ref='wsp:PolicyReference' minOccurs='0' />
///   <xs:any namespace='##other' processContents='lax' minOccurs='0' maxOccurs='unbounded' />
/// </BLOCKQUOTE></PRE>
/// struct wst__RequestSecurityTokenType operations:
/// - soap_default_wst__RequestSecurityTokenType(soap*, wst__RequestSecurityTokenType*) reset members to default
/// - int soap_read_wst__RequestSecurityTokenType(soap*, wst__RequestSecurityTokenType*) deserialize from a source
/// - int soap_write_wst__RequestSecurityTokenType(soap*, wst__RequestSecurityTokenType*) serialize to a sink
/// - wst__RequestSecurityTokenType* soap_dup_wst__RequestSecurityTokenType(soap*, wst__RequestSecurityTokenType* dst, wst__RequestSecurityTokenType *src) returns deep copy of wst__RequestSecurityTokenType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__RequestSecurityTokenType(wst__RequestSecurityTokenType*) deep deletes wst__RequestSecurityTokenType data members, use only on dst after soap_dup_wst__RequestSecurityTokenType(NULL, wst__RequestSecurityTokenType *dst, wst__RequestSecurityTokenType *src) (use soapcpp2 -Ed)
struct wst__RequestSecurityTokenType
{
/// @todo <any namespace="##any" minOccurs="0" maxOccurs="unbounded">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
/// Attribute "Context" of XSD type xs:anyURI.
   @char*                                Context                        0;	///< Optional attribute.
/// @todo <anyAttribute namespace="##other">.
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this attribute.
///       Use wsdl2h option -d for xsd__anyAttribute DOM (soap_dom_attribute).
/// Member declared in WS/WS-typemap.dat
       _wsp__AppliesTo_*                    wsp__AppliesTo;
/// Member declared in WS/WS-typemap.dat
       char*                                KeyType;
/// Member declared in WS/WS-typemap.dat
       char*                                RequestType;
/// Member declared in WS/WS-typemap.dat
       char*                                TokenType;
/// Member declared in WS/WS-typemap.dat
       wst__EntropyType*                    Entropy;
/// Member declared in WS/WS-typemap.dat
       char*                                ComputedKeyAlgorithm;
/// Member declared in WS/WS-typemap.dat
       unsigned int*                        KeySize;
/// Member declared in WS/WS-typemap.dat
       struct wst__BinaryExchangeType*      BinaryExchange;
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestSecurityTokenResponseType is a complexType.
///
/// <PRE><BLOCKQUOTE>
///   Actual content model is non-deterministic, hence wildcard. The following shows intended content model:
///   <xs:element ref='wst:TokenType' minOccurs='0' />
///   <xs:element ref='wst:RequestType' />
///   <xs:element ref='wst:RequestedSecurityToken' minOccurs='0' />
///   <xs:element ref='wsp:AppliesTo' minOccurs='0' />
///   <xs:element ref='wst:RequestedAttachedReference' minOccurs='0' />
///   <xs:element ref='wst:RequestedUnattachedReference' minOccurs='0' />
///   <xs:element ref='wst:RequestedProofToken' minOccurs='0' />
///   <xs:element ref='wst:Entropy' minOccurs='0' />
///   <xs:element ref='wst:Lifetime' minOccurs='0' />
///   <xs:element ref='wst:Status' minOccurs='0' />
///   <xs:element ref='wst:AllowPostdating' minOccurs='0' />
///   <xs:element ref='wst:Renewing' minOccurs='0' />
///   <xs:element ref='wst:OnBehalfOf' minOccurs='0' />
///   <xs:element ref='wst:Issuer' minOccurs='0' />
///   <xs:element ref='wst:AuthenticationType' minOccurs='0' />
///   <xs:element ref='wst:Authenticator' minOccurs='0' />
///   <xs:element ref='wst:KeyType' minOccurs='0' />
///   <xs:element ref='wst:KeySize' minOccurs='0' />
///   <xs:element ref='wst:SignatureAlgorithm' minOccurs='0' />
///   <xs:element ref='wst:Encryption' minOccurs='0' />
///   <xs:element ref='wst:EncryptionAlgorithm' minOccurs='0' />
///   <xs:element ref='wst:CanonicalizationAlgorithm' minOccurs='0' />
///   <xs:element ref='wst:ProofEncryption' minOccurs='0' />
///   <xs:element ref='wst:UseKey' minOccurs='0' />
///   <xs:element ref='wst:SignWith' minOccurs='0' />
///   <xs:element ref='wst:EncryptWith' minOccurs='0' />
///   <xs:element ref='wst:DelegateTo' minOccurs='0' />
///   <xs:element ref='wst:Forwardable' minOccurs='0' />
///   <xs:element ref='wst:Delegatable' minOccurs='0' />
///   <xs:element ref='wsp:Policy' minOccurs='0' />
///   <xs:element ref='wsp:PolicyReference' minOccurs='0' />
///   <xs:any namespace='##other' processContents='lax' minOccurs='0' maxOccurs='unbounded' />
/// </BLOCKQUOTE></PRE>
/// struct wst__RequestSecurityTokenResponseType operations:
/// - soap_default_wst__RequestSecurityTokenResponseType(soap*, wst__RequestSecurityTokenResponseType*) reset members to default
/// - int soap_read_wst__RequestSecurityTokenResponseType(soap*, wst__RequestSecurityTokenResponseType*) deserialize from a source
/// - int soap_write_wst__RequestSecurityTokenResponseType(soap*, wst__RequestSecurityTokenResponseType*) serialize to a sink
/// - wst__RequestSecurityTokenResponseType* soap_dup_wst__RequestSecurityTokenResponseType(soap*, wst__RequestSecurityTokenResponseType* dst, wst__RequestSecurityTokenResponseType *src) returns deep copy of wst__RequestSecurityTokenResponseType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__RequestSecurityTokenResponseType(wst__RequestSecurityTokenResponseType*) deep deletes wst__RequestSecurityTokenResponseType data members, use only on dst after soap_dup_wst__RequestSecurityTokenResponseType(NULL, wst__RequestSecurityTokenResponseType *dst, wst__RequestSecurityTokenResponseType *src) (use soapcpp2 -Ed)
struct wst__RequestSecurityTokenResponseType
{
/// @todo <any namespace="##any" minOccurs="0" maxOccurs="unbounded">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
/// Attribute "Context" of XSD type xs:anyURI.
   @char*                                Context                        0;	///< Optional attribute.
/// @todo <anyAttribute namespace="##other">.
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this attribute.
///       Use wsdl2h option -d for xsd__anyAttribute DOM (soap_dom_attribute).
/// Member declared in WS/WS-typemap.dat
       _wsp__AppliesTo_*                    wsp__AppliesTo;
/// Member declared in WS/WS-typemap.dat
       struct wst__RequestedSecurityTokenType* RequestedSecurityToken;
/// Member declared in WS/WS-typemap.dat
       struct wst__RequestedReferenceType*  RequestedAttachedReference;
/// Member declared in WS/WS-typemap.dat
       struct wst__RequestedReferenceType*  RequestedUnattachedReference;
/// Member declared in WS/WS-typemap.dat
       char*                                KeyType;
/// Member declared in WS/WS-typemap.dat
       char*                                RequestType;
/// Member declared in WS/WS-typemap.dat
       char*                                TokenType;
/// Member declared in WS/WS-typemap.dat
       wst__EntropyType*                    Entropy;
/// Member declared in WS/WS-typemap.dat
       struct wst__BinaryExchangeType*      BinaryExchange;
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ClaimsType is a complexType.
///
/// struct wst__ClaimsType operations:
/// - soap_default_wst__ClaimsType(soap*, wst__ClaimsType*) reset members to default
/// - int soap_read_wst__ClaimsType(soap*, wst__ClaimsType*) deserialize from a source
/// - int soap_write_wst__ClaimsType(soap*, wst__ClaimsType*) serialize to a sink
/// - wst__ClaimsType* soap_dup_wst__ClaimsType(soap*, wst__ClaimsType* dst, wst__ClaimsType *src) returns deep copy of wst__ClaimsType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__ClaimsType(wst__ClaimsType*) deep deletes wst__ClaimsType data members, use only on dst after soap_dup_wst__ClaimsType(NULL, wst__ClaimsType *dst, wst__ClaimsType *src) (use soapcpp2 -Ed)
struct wst__ClaimsType
{
/// @todo <any namespace="##any" minOccurs="0" maxOccurs="unbounded">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
/// Attribute "Dialect" of XSD type xs:anyURI.
   @char*                                Dialect                        0;	///< Optional attribute.
/// @todo <anyAttribute namespace="##other">.
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this attribute.
///       Use wsdl2h option -d for xsd__anyAttribute DOM (soap_dom_attribute).
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":LifetimeType is a complexType.
///
/// struct wst__LifetimeType operations:
/// - soap_default_wst__LifetimeType(soap*, wst__LifetimeType*) reset members to default
/// - int soap_read_wst__LifetimeType(soap*, wst__LifetimeType*) deserialize from a source
/// - int soap_write_wst__LifetimeType(soap*, wst__LifetimeType*) serialize to a sink
/// - wst__LifetimeType* soap_dup_wst__LifetimeType(soap*, wst__LifetimeType* dst, wst__LifetimeType *src) returns deep copy of wst__LifetimeType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__LifetimeType(wst__LifetimeType*) deep deletes wst__LifetimeType data members, use only on dst after soap_dup_wst__LifetimeType(NULL, wst__LifetimeType *dst, wst__LifetimeType *src) (use soapcpp2 -Ed)
struct wst__LifetimeType
{
/// Imported element reference "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd":Created.
    char*                                wsu__Created                   0;	///< Optional element.
/// Imported element reference "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd":Expires.
    char*                                wsu__Expires                   0;	///< Optional element.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestSecurityTokenCollectionType is a complexType.
///
/// <PRE><BLOCKQUOTE>
///   The RequestSecurityTokenCollection (RSTC) element is used to provide multiple RST requests. One or more RSTR elements in an RSTRC element are returned in the response to the RequestSecurityTokenCollection.
/// </BLOCKQUOTE></PRE>
/// struct wst__RequestSecurityTokenCollectionType operations:
/// - soap_default_wst__RequestSecurityTokenCollectionType(soap*, wst__RequestSecurityTokenCollectionType*) reset members to default
/// - int soap_read_wst__RequestSecurityTokenCollectionType(soap*, wst__RequestSecurityTokenCollectionType*) deserialize from a source
/// - int soap_write_wst__RequestSecurityTokenCollectionType(soap*, wst__RequestSecurityTokenCollectionType*) serialize to a sink
/// - wst__RequestSecurityTokenCollectionType* soap_dup_wst__RequestSecurityTokenCollectionType(soap*, wst__RequestSecurityTokenCollectionType* dst, wst__RequestSecurityTokenCollectionType *src) returns deep copy of wst__RequestSecurityTokenCollectionType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__RequestSecurityTokenCollectionType(wst__RequestSecurityTokenCollectionType*) deep deletes wst__RequestSecurityTokenCollectionType data members, use only on dst after soap_dup_wst__RequestSecurityTokenCollectionType(NULL, wst__RequestSecurityTokenCollectionType *dst, wst__RequestSecurityTokenCollectionType *src) (use soapcpp2 -Ed)
struct wst__RequestSecurityTokenCollectionType
{
/// Size of array of struct wst__RequestSecurityTokenType* is 2..unbounded.
   $int                                  __sizeRequestSecurityToken     2;
/// Array struct wst__RequestSecurityTokenType* of size 2..unbounded.
    struct wst__RequestSecurityTokenType*  RequestSecurityToken           2;
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestSecurityTokenResponseCollectionType is a complexType.
///
/// <PRE><BLOCKQUOTE>
///   The <wst:RequestSecurityTokenResponseCollection> element (RSTRC) MUST be used to return a security token or response to a security token request on the final response.
/// </BLOCKQUOTE></PRE>
/// struct wst__RequestSecurityTokenResponseCollectionType operations:
/// - soap_default_wst__RequestSecurityTokenResponseCollectionType(soap*, wst__RequestSecurityTokenResponseCollectionType*) reset members to default
/// - int soap_read_wst__RequestSecurityTokenResponseCollectionType(soap*, wst__RequestSecurityTokenResponseCollectionType*) deserialize from a source
/// - int soap_write_wst__RequestSecurityTokenResponseCollectionType(soap*, wst__RequestSecurityTokenResponseCollectionType*) serialize to a sink
/// - wst__RequestSecurityTokenResponseCollectionType* soap_dup_wst__RequestSecurityTokenResponseCollectionType(soap*, wst__RequestSecurityTokenResponseCollectionType* dst, wst__RequestSecurityTokenResponseCollectionType *src) returns deep copy of wst__RequestSecurityTokenResponseCollectionType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__RequestSecurityTokenResponseCollectionType(wst__RequestSecurityTokenResponseCollectionType*) deep deletes wst__RequestSecurityTokenResponseCollectionType data members, use only on dst after soap_dup_wst__RequestSecurityTokenResponseCollectionType(NULL, wst__RequestSecurityTokenResponseCollectionType *dst, wst__RequestSecurityTokenResponseCollectionType *src) (use soapcpp2 -Ed)
struct wst__RequestSecurityTokenResponseCollectionType
{
/// Size of the dynamic array of struct wst__RequestSecurityTokenResponseType* is 1..unbounded.
   $int                                  __sizeRequestSecurityTokenResponse 1;
/// Array struct wst__RequestSecurityTokenResponseType* of size 1..unbounded.
    struct wst__RequestSecurityTokenResponseType*  RequestSecurityTokenResponse   1;
/// @todo <anyAttribute namespace="##other">.
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this attribute.
///       Use wsdl2h option -d for xsd__anyAttribute DOM (soap_dom_attribute).
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedReferenceType is a complexType.
///
/// struct wst__RequestedReferenceType operations:
/// - soap_default_wst__RequestedReferenceType(soap*, wst__RequestedReferenceType*) reset members to default
/// - int soap_read_wst__RequestedReferenceType(soap*, wst__RequestedReferenceType*) deserialize from a source
/// - int soap_write_wst__RequestedReferenceType(soap*, wst__RequestedReferenceType*) serialize to a sink
/// - wst__RequestedReferenceType* soap_dup_wst__RequestedReferenceType(soap*, wst__RequestedReferenceType* dst, wst__RequestedReferenceType *src) returns deep copy of wst__RequestedReferenceType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__RequestedReferenceType(wst__RequestedReferenceType*) deep deletes wst__RequestedReferenceType data members, use only on dst after soap_dup_wst__RequestedReferenceType(NULL, wst__RequestedReferenceType *dst, wst__RequestedReferenceType *src) (use soapcpp2 -Ed)
struct wst__RequestedReferenceType
{
/// Imported element reference "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd":SecurityTokenReference.
    _wsse__SecurityTokenReference        wsse__SecurityTokenReference   1;	///< Required element.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedProofTokenType is a complexType.
///
/// struct wst__RequestedProofTokenType operations:
/// - soap_default_wst__RequestedProofTokenType(soap*, wst__RequestedProofTokenType*) reset members to default
/// - int soap_read_wst__RequestedProofTokenType(soap*, wst__RequestedProofTokenType*) deserialize from a source
/// - int soap_write_wst__RequestedProofTokenType(soap*, wst__RequestedProofTokenType*) serialize to a sink
/// - wst__RequestedProofTokenType* soap_dup_wst__RequestedProofTokenType(soap*, wst__RequestedProofTokenType* dst, wst__RequestedProofTokenType *src) returns deep copy of wst__RequestedProofTokenType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__RequestedProofTokenType(wst__RequestedProofTokenType*) deep deletes wst__RequestedProofTokenType data members, use only on dst after soap_dup_wst__RequestedProofTokenType(NULL, wst__RequestedProofTokenType *dst, wst__RequestedProofTokenType *src) (use soapcpp2 -Ed)
struct wst__RequestedProofTokenType
{
/// @todo <any namespace="##any">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RenewTargetType is a complexType.
///
/// struct wst__RenewTargetType operations:
/// - soap_default_wst__RenewTargetType(soap*, wst__RenewTargetType*) reset members to default
/// - int soap_read_wst__RenewTargetType(soap*, wst__RenewTargetType*) deserialize from a source
/// - int soap_write_wst__RenewTargetType(soap*, wst__RenewTargetType*) serialize to a sink
/// - wst__RenewTargetType* soap_dup_wst__RenewTargetType(soap*, wst__RenewTargetType* dst, wst__RenewTargetType *src) returns deep copy of wst__RenewTargetType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__RenewTargetType(wst__RenewTargetType*) deep deletes wst__RenewTargetType data members, use only on dst after soap_dup_wst__RenewTargetType(NULL, wst__RenewTargetType *dst, wst__RenewTargetType *src) (use soapcpp2 -Ed)
struct wst__RenewTargetType
{
/// @todo <any namespace="##other" minOccurs="1" maxOccurs="1">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":AllowPostdatingType is a complexType.
///
/// struct wst__AllowPostdatingType operations:
/// - soap_default_wst__AllowPostdatingType(soap*, wst__AllowPostdatingType*) reset members to default
/// - int soap_read_wst__AllowPostdatingType(soap*, wst__AllowPostdatingType*) deserialize from a source
/// - int soap_write_wst__AllowPostdatingType(soap*, wst__AllowPostdatingType*) serialize to a sink
/// - wst__AllowPostdatingType* soap_dup_wst__AllowPostdatingType(soap*, wst__AllowPostdatingType* dst, wst__AllowPostdatingType *src) returns deep copy of wst__AllowPostdatingType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__AllowPostdatingType(wst__AllowPostdatingType*) deep deletes wst__AllowPostdatingType data members, use only on dst after soap_dup_wst__AllowPostdatingType(NULL, wst__AllowPostdatingType *dst, wst__AllowPostdatingType *src) (use soapcpp2 -Ed)
struct wst__AllowPostdatingType
{
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RenewingType is a complexType.
///
/// struct wst__RenewingType operations:
/// - soap_default_wst__RenewingType(soap*, wst__RenewingType*) reset members to default
/// - int soap_read_wst__RenewingType(soap*, wst__RenewingType*) deserialize from a source
/// - int soap_write_wst__RenewingType(soap*, wst__RenewingType*) serialize to a sink
/// - wst__RenewingType* soap_dup_wst__RenewingType(soap*, wst__RenewingType* dst, wst__RenewingType *src) returns deep copy of wst__RenewingType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__RenewingType(wst__RenewingType*) deep deletes wst__RenewingType data members, use only on dst after soap_dup_wst__RenewingType(NULL, wst__RenewingType *dst, wst__RenewingType *src) (use soapcpp2 -Ed)
struct wst__RenewingType
{
/// Attribute "Allow" of XSD type xs:boolean.
   @char*                                Allow                          0;	///< Optional attribute.
/// Attribute "OK" of XSD type xs:boolean.
   @char*                                OK                             0;	///< Optional attribute.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":CancelTargetType is a complexType.
///
/// struct wst__CancelTargetType operations:
/// - soap_default_wst__CancelTargetType(soap*, wst__CancelTargetType*) reset members to default
/// - int soap_read_wst__CancelTargetType(soap*, wst__CancelTargetType*) deserialize from a source
/// - int soap_write_wst__CancelTargetType(soap*, wst__CancelTargetType*) serialize to a sink
/// - wst__CancelTargetType* soap_dup_wst__CancelTargetType(soap*, wst__CancelTargetType* dst, wst__CancelTargetType *src) returns deep copy of wst__CancelTargetType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__CancelTargetType(wst__CancelTargetType*) deep deletes wst__CancelTargetType data members, use only on dst after soap_dup_wst__CancelTargetType(NULL, wst__CancelTargetType *dst, wst__CancelTargetType *src) (use soapcpp2 -Ed)
struct wst__CancelTargetType
{
/// @todo <any namespace="##other" minOccurs="1" maxOccurs="1">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedTokenCancelledType is a complexType.
///
/// struct wst__RequestedTokenCancelledType operations:
/// - soap_default_wst__RequestedTokenCancelledType(soap*, wst__RequestedTokenCancelledType*) reset members to default
/// - int soap_read_wst__RequestedTokenCancelledType(soap*, wst__RequestedTokenCancelledType*) deserialize from a source
/// - int soap_write_wst__RequestedTokenCancelledType(soap*, wst__RequestedTokenCancelledType*) serialize to a sink
/// - wst__RequestedTokenCancelledType* soap_dup_wst__RequestedTokenCancelledType(soap*, wst__RequestedTokenCancelledType* dst, wst__RequestedTokenCancelledType *src) returns deep copy of wst__RequestedTokenCancelledType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__RequestedTokenCancelledType(wst__RequestedTokenCancelledType*) deep deletes wst__RequestedTokenCancelledType data members, use only on dst after soap_dup_wst__RequestedTokenCancelledType(NULL, wst__RequestedTokenCancelledType *dst, wst__RequestedTokenCancelledType *src) (use soapcpp2 -Ed)
struct wst__RequestedTokenCancelledType
{
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ValidateTargetType is a complexType.
///
/// struct wst__ValidateTargetType operations:
/// - soap_default_wst__ValidateTargetType(soap*, wst__ValidateTargetType*) reset members to default
/// - int soap_read_wst__ValidateTargetType(soap*, wst__ValidateTargetType*) deserialize from a source
/// - int soap_write_wst__ValidateTargetType(soap*, wst__ValidateTargetType*) serialize to a sink
/// - wst__ValidateTargetType* soap_dup_wst__ValidateTargetType(soap*, wst__ValidateTargetType* dst, wst__ValidateTargetType *src) returns deep copy of wst__ValidateTargetType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__ValidateTargetType(wst__ValidateTargetType*) deep deletes wst__ValidateTargetType data members, use only on dst after soap_dup_wst__ValidateTargetType(NULL, wst__ValidateTargetType *dst, wst__ValidateTargetType *src) (use soapcpp2 -Ed)
struct wst__ValidateTargetType
{
/// @todo <any namespace="##other" minOccurs="1" maxOccurs="1">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":StatusType is a complexType.
///
/// struct wst__StatusType operations:
/// - soap_default_wst__StatusType(soap*, wst__StatusType*) reset members to default
/// - int soap_read_wst__StatusType(soap*, wst__StatusType*) deserialize from a source
/// - int soap_write_wst__StatusType(soap*, wst__StatusType*) serialize to a sink
/// - wst__StatusType* soap_dup_wst__StatusType(soap*, wst__StatusType* dst, wst__StatusType *src) returns deep copy of wst__StatusType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__StatusType(wst__StatusType*) deep deletes wst__StatusType data members, use only on dst after soap_dup_wst__StatusType(NULL, wst__StatusType *dst, wst__StatusType *src) (use soapcpp2 -Ed)
struct wst__StatusType
{
/// Element "Code" of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":StatusCodeOpenEnum.
    char*                                Code                           1;	///< Required element.
/// Element "Reason" of XSD type xs:string.
    char*                                Reason                         0;	///< Optional element.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":SignChallengeType is a complexType.
///
/// struct wst__SignChallengeType operations:
/// - soap_default_wst__SignChallengeType(soap*, wst__SignChallengeType*) reset members to default
/// - int soap_read_wst__SignChallengeType(soap*, wst__SignChallengeType*) deserialize from a source
/// - int soap_write_wst__SignChallengeType(soap*, wst__SignChallengeType*) serialize to a sink
/// - wst__SignChallengeType* soap_dup_wst__SignChallengeType(soap*, wst__SignChallengeType* dst, wst__SignChallengeType *src) returns deep copy of wst__SignChallengeType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__SignChallengeType(wst__SignChallengeType*) deep deletes wst__SignChallengeType data members, use only on dst after soap_dup_wst__SignChallengeType(NULL, wst__SignChallengeType *dst, wst__SignChallengeType *src) (use soapcpp2 -Ed)
struct wst__SignChallengeType
{
/// Element reference "http://docs.oasis-open.org/ws-sx/ws-trust/200512/:""http://docs.oasis-open.org/ws-sx/ws-trust/200512/":Challenge.
    char*                                Challenge                      1;	///< Required element.
/// @todo <any namespace="##any" minOccurs="0" maxOccurs="unbounded">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
/// @todo <anyAttribute namespace="##any">.
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this attribute.
///       Use wsdl2h option -d for xsd__anyAttribute DOM (soap_dom_attribute).
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestKETType is a complexType.
///
/// struct wst__RequestKETType operations:
/// - soap_default_wst__RequestKETType(soap*, wst__RequestKETType*) reset members to default
/// - int soap_read_wst__RequestKETType(soap*, wst__RequestKETType*) deserialize from a source
/// - int soap_write_wst__RequestKETType(soap*, wst__RequestKETType*) serialize to a sink
/// - wst__RequestKETType* soap_dup_wst__RequestKETType(soap*, wst__RequestKETType* dst, wst__RequestKETType *src) returns deep copy of wst__RequestKETType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__RequestKETType(wst__RequestKETType*) deep deletes wst__RequestKETType data members, use only on dst after soap_dup_wst__RequestKETType(NULL, wst__RequestKETType *dst, wst__RequestKETType *src) (use soapcpp2 -Ed)
struct wst__RequestKETType
{
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":KeyExchangeTokenType is a complexType.
///
/// struct wst__KeyExchangeTokenType operations:
/// - soap_default_wst__KeyExchangeTokenType(soap*, wst__KeyExchangeTokenType*) reset members to default
/// - int soap_read_wst__KeyExchangeTokenType(soap*, wst__KeyExchangeTokenType*) deserialize from a source
/// - int soap_write_wst__KeyExchangeTokenType(soap*, wst__KeyExchangeTokenType*) serialize to a sink
/// - wst__KeyExchangeTokenType* soap_dup_wst__KeyExchangeTokenType(soap*, wst__KeyExchangeTokenType* dst, wst__KeyExchangeTokenType *src) returns deep copy of wst__KeyExchangeTokenType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__KeyExchangeTokenType(wst__KeyExchangeTokenType*) deep deletes wst__KeyExchangeTokenType data members, use only on dst after soap_dup_wst__KeyExchangeTokenType(NULL, wst__KeyExchangeTokenType *dst, wst__KeyExchangeTokenType *src) (use soapcpp2 -Ed)
struct wst__KeyExchangeTokenType
{
/// @todo <any namespace="##any" minOccurs="0" maxOccurs="unbounded">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":OnBehalfOfType is a complexType.
///
/// struct wst__OnBehalfOfType operations:
/// - soap_default_wst__OnBehalfOfType(soap*, wst__OnBehalfOfType*) reset members to default
/// - int soap_read_wst__OnBehalfOfType(soap*, wst__OnBehalfOfType*) deserialize from a source
/// - int soap_write_wst__OnBehalfOfType(soap*, wst__OnBehalfOfType*) serialize to a sink
/// - wst__OnBehalfOfType* soap_dup_wst__OnBehalfOfType(soap*, wst__OnBehalfOfType* dst, wst__OnBehalfOfType *src) returns deep copy of wst__OnBehalfOfType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__OnBehalfOfType(wst__OnBehalfOfType*) deep deletes wst__OnBehalfOfType data members, use only on dst after soap_dup_wst__OnBehalfOfType(NULL, wst__OnBehalfOfType *dst, wst__OnBehalfOfType *src) (use soapcpp2 -Ed)
struct wst__OnBehalfOfType
{
/// @todo <any namespace="##any">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":EncryptionType is a complexType.
///
/// struct wst__EncryptionType operations:
/// - soap_default_wst__EncryptionType(soap*, wst__EncryptionType*) reset members to default
/// - int soap_read_wst__EncryptionType(soap*, wst__EncryptionType*) deserialize from a source
/// - int soap_write_wst__EncryptionType(soap*, wst__EncryptionType*) serialize to a sink
/// - wst__EncryptionType* soap_dup_wst__EncryptionType(soap*, wst__EncryptionType* dst, wst__EncryptionType *src) returns deep copy of wst__EncryptionType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__EncryptionType(wst__EncryptionType*) deep deletes wst__EncryptionType data members, use only on dst after soap_dup_wst__EncryptionType(NULL, wst__EncryptionType *dst, wst__EncryptionType *src) (use soapcpp2 -Ed)
struct wst__EncryptionType
{
/// @todo <any namespace="##any">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ProofEncryptionType is a complexType.
///
/// struct wst__ProofEncryptionType operations:
/// - soap_default_wst__ProofEncryptionType(soap*, wst__ProofEncryptionType*) reset members to default
/// - int soap_read_wst__ProofEncryptionType(soap*, wst__ProofEncryptionType*) deserialize from a source
/// - int soap_write_wst__ProofEncryptionType(soap*, wst__ProofEncryptionType*) serialize to a sink
/// - wst__ProofEncryptionType* soap_dup_wst__ProofEncryptionType(soap*, wst__ProofEncryptionType* dst, wst__ProofEncryptionType *src) returns deep copy of wst__ProofEncryptionType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__ProofEncryptionType(wst__ProofEncryptionType*) deep deletes wst__ProofEncryptionType data members, use only on dst after soap_dup_wst__ProofEncryptionType(NULL, wst__ProofEncryptionType *dst, wst__ProofEncryptionType *src) (use soapcpp2 -Ed)
struct wst__ProofEncryptionType
{
/// @todo <any namespace="##any">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":UseKeyType is a complexType.
///
/// struct wst__UseKeyType operations:
/// - soap_default_wst__UseKeyType(soap*, wst__UseKeyType*) reset members to default
/// - int soap_read_wst__UseKeyType(soap*, wst__UseKeyType*) deserialize from a source
/// - int soap_write_wst__UseKeyType(soap*, wst__UseKeyType*) serialize to a sink
/// - wst__UseKeyType* soap_dup_wst__UseKeyType(soap*, wst__UseKeyType* dst, wst__UseKeyType *src) returns deep copy of wst__UseKeyType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__UseKeyType(wst__UseKeyType*) deep deletes wst__UseKeyType data members, use only on dst after soap_dup_wst__UseKeyType(NULL, wst__UseKeyType *dst, wst__UseKeyType *src) (use soapcpp2 -Ed)
struct wst__UseKeyType
{
/// @todo <any namespace="##any" minOccurs="0">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
/// Attribute "Sig" of XSD type xs:anyURI.
   @char*                                Sig                            0;	///< Optional attribute.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":DelegateToType is a complexType.
///
/// struct wst__DelegateToType operations:
/// - soap_default_wst__DelegateToType(soap*, wst__DelegateToType*) reset members to default
/// - int soap_read_wst__DelegateToType(soap*, wst__DelegateToType*) deserialize from a source
/// - int soap_write_wst__DelegateToType(soap*, wst__DelegateToType*) serialize to a sink
/// - wst__DelegateToType* soap_dup_wst__DelegateToType(soap*, wst__DelegateToType* dst, wst__DelegateToType *src) returns deep copy of wst__DelegateToType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__DelegateToType(wst__DelegateToType*) deep deletes wst__DelegateToType data members, use only on dst after soap_dup_wst__DelegateToType(NULL, wst__DelegateToType *dst, wst__DelegateToType *src) (use soapcpp2 -Ed)
struct wst__DelegateToType
{
/// @todo <any namespace="##any">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ParticipantsType is a complexType.
///
/// struct wst__ParticipantsType operations:
/// - soap_default_wst__ParticipantsType(soap*, wst__ParticipantsType*) reset members to default
/// - int soap_read_wst__ParticipantsType(soap*, wst__ParticipantsType*) deserialize from a source
/// - int soap_write_wst__ParticipantsType(soap*, wst__ParticipantsType*) serialize to a sink
/// - wst__ParticipantsType* soap_dup_wst__ParticipantsType(soap*, wst__ParticipantsType* dst, wst__ParticipantsType *src) returns deep copy of wst__ParticipantsType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__ParticipantsType(wst__ParticipantsType*) deep deletes wst__ParticipantsType data members, use only on dst after soap_dup_wst__ParticipantsType(NULL, wst__ParticipantsType *dst, wst__ParticipantsType *src) (use soapcpp2 -Ed)
struct wst__ParticipantsType
{
/// Element "Primary" of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ParticipantType.
    struct wst__ParticipantType*         Primary                        0;	///< Optional element.
/// Size of array of struct wst__ParticipantType* is 0..unbounded.
   $int                                  __sizeParticipant              0;
/// Array struct wst__ParticipantType* of size 0..unbounded.
    struct wst__ParticipantType*         Participant                    0;
/// @todo <any namespace="##other" minOccurs="0" maxOccurs="unbounded">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ParticipantType is a complexType.
///
/// struct wst__ParticipantType operations:
/// - soap_default_wst__ParticipantType(soap*, wst__ParticipantType*) reset members to default
/// - int soap_read_wst__ParticipantType(soap*, wst__ParticipantType*) deserialize from a source
/// - int soap_write_wst__ParticipantType(soap*, wst__ParticipantType*) serialize to a sink
/// - wst__ParticipantType* soap_dup_wst__ParticipantType(soap*, wst__ParticipantType* dst, wst__ParticipantType *src) returns deep copy of wst__ParticipantType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__ParticipantType(wst__ParticipantType*) deep deletes wst__ParticipantType data members, use only on dst after soap_dup_wst__ParticipantType(NULL, wst__ParticipantType *dst, wst__ParticipantType *src) (use soapcpp2 -Ed)
struct wst__ParticipantType
{
/// @todo <any namespace="##any">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":BinarySecretType is a complexType with simpleContent.
///
/// struct wst__BinarySecretType operations:
/// - soap_default_wst__BinarySecretType(soap*, wst__BinarySecretType*) reset members to default
/// - int soap_read_wst__BinarySecretType(soap*, wst__BinarySecretType*) deserialize from a source
/// - int soap_write_wst__BinarySecretType(soap*, wst__BinarySecretType*) serialize to a sink
/// - wst__BinarySecretType* soap_dup_wst__BinarySecretType(soap*, wst__BinarySecretType* dst, wst__BinarySecretType *src) returns deep copy of wst__BinarySecretType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__BinarySecretType(wst__BinarySecretType*) deep deletes wst__BinarySecretType data members, use only on dst after soap_dup_wst__BinarySecretType(NULL, wst__BinarySecretType *dst, wst__BinarySecretType *src) (use soapcpp2 -Ed)
struct wst__BinarySecretType
{
/// __item wraps "xs:base64Binary" simpleContent.
    char*                                __item                        ;
/// Attribute "Type" of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":BinarySecretTypeOpenEnum.
   @char*                                Type                           0;	///< Optional attribute.
/// @todo <anyAttribute namespace="##other">.
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this attribute.
///       Use wsdl2h option -d for xsd__anyAttribute DOM (soap_dom_attribute).
};

/// @brief "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":BinaryExchangeType is a complexType with simpleContent.
///
/// struct wst__BinaryExchangeType operations:
/// - soap_default_wst__BinaryExchangeType(soap*, wst__BinaryExchangeType*) reset members to default
/// - int soap_read_wst__BinaryExchangeType(soap*, wst__BinaryExchangeType*) deserialize from a source
/// - int soap_write_wst__BinaryExchangeType(soap*, wst__BinaryExchangeType*) serialize to a sink
/// - wst__BinaryExchangeType* soap_dup_wst__BinaryExchangeType(soap*, wst__BinaryExchangeType* dst, wst__BinaryExchangeType *src) returns deep copy of wst__BinaryExchangeType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_wst__BinaryExchangeType(wst__BinaryExchangeType*) deep deletes wst__BinaryExchangeType data members, use only on dst after soap_dup_wst__BinaryExchangeType(NULL, wst__BinaryExchangeType *dst, wst__BinaryExchangeType *src) (use soapcpp2 -Ed)
struct wst__BinaryExchangeType
{
/// __item wraps "xs:string" simpleContent.
    char*                                __item                        ;
/// Attribute "ValueType" of XSD type xs:anyURI.
   @char*                                ValueType                      1;	///< Required attribute.
/// Attribute "EncodingType" of XSD type xs:anyURI.
   @char*                                EncodingType                   1;	///< Required attribute.
/// @todo <anyAttribute namespace="##other">.
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this attribute.
///       Use wsdl2h option -d for xsd__anyAttribute DOM (soap_dom_attribute).
};


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Elements                                              *
 *   http://docs.oasis-open.org/ws-sx/ws-trust/200512/                        *
 *                                                                            *
\******************************************************************************/

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestSecurityToken of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestSecurityTokenType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":TokenType of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestType of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestTypeOpenEnum.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestSecurityTokenResponse of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestSecurityTokenResponseType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedSecurityToken of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedSecurityTokenType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":BinarySecret of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":BinarySecretType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":Claims of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ClaimsType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":Entropy of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":EntropyType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":Lifetime of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":LifetimeType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestSecurityTokenCollection of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestSecurityTokenCollectionType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestSecurityTokenResponseCollection of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestSecurityTokenResponseCollectionType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ComputedKey of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ComputedKeyOpenEnum.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedAttachedReference of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedReferenceType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedUnattachedReference of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedReferenceType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedProofToken of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedProofTokenType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":IssuedTokens of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestSecurityTokenResponseCollectionType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RenewTarget of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RenewTargetType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":AllowPostdating of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":AllowPostdatingType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":Renewing of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RenewingType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":CancelTarget of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":CancelTargetType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedTokenCancelled of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestedTokenCancelledType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ValidateTarget of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ValidateTargetType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":Status of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":StatusType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":SignChallenge of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":SignChallengeType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":SignChallengeResponse of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":SignChallengeType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":Challenge of XSD type xs:string.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":BinaryExchange of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":BinaryExchangeType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestKET of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":RequestKETType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":KeyExchangeToken of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":KeyExchangeTokenType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":Authenticator of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":AuthenticatorType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":CombinedHash of XSD type xs:base64Binary.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":OnBehalfOf of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":OnBehalfOfType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":Issuer of XSD type "http://www.w3.org/2005/08/addressing":EndpointReferenceType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":AuthenticationType of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":KeyType of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":KeyTypeOpenEnum.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":KeySize of XSD type xs:unsignedInt.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":SignatureAlgorithm of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":EncryptionAlgorithm of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":CanonicalizationAlgorithm of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ComputedKeyAlgorithm of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":Encryption of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":EncryptionType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ProofEncryption of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ProofEncryptionType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":UseKey of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":UseKeyType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":KeyWrapAlgorithm of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":SignWith of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":EncryptWith of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":DelegateTo of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":DelegateToType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":Forwardable of XSD type xs:boolean.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":Delegatable of XSD type xs:boolean.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":Participants of XSD type "http://docs.oasis-open.org/ws-sx/ws-trust/200512/":ParticipantsType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Attributes                                            *
 *   http://docs.oasis-open.org/ws-sx/ws-trust/200512/                        *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * XML Data Binding                                                           *
 *                                                                            *
\******************************************************************************/


/**

@page page_XMLDataBinding XML Data Binding

SOAP/XML services use data bindings contractually bound by WSDL and auto-
generated by wsdl2h and soapcpp2 (see Service Bindings). Plain data bindings
are adopted from XML schemas as part of the WSDL types section or when running
wsdl2h on a set of schemas to produce non-SOAP-based XML data bindings.

The following readers and writers are C/C++ data type (de)serializers auto-
generated by wsdl2h and soapcpp2. Run soapcpp2 on this file to generate the
(de)serialization code, which is stored in soapC.c[pp]. Include "soapH.h" in
your code to import these data type and function declarations. Only use the
soapcpp2-generated files in your project build. Do not include the wsdl2h-
generated .h file in your code.

Data can be read and deserialized from:
  - an int file descriptor, using soap->recvfd = fd
  - a socket, using soap->socket = (int)...
  - a C++ stream (istream, stringstream), using soap->is = (istream*)...
  - a C string, using soap->is = (const char*)...
  - any input, using the soap->frecv() callback

Data can be serialized and written to:
  - an int file descriptor, using soap->sendfd = (int)...
  - a socket, using soap->socket = (int)...
  - a C++ stream (ostream, stringstream), using soap->os = (ostream*)...
  - a C string, using soap->os = (const char**)...
  - any output, using the soap->fsend() callback

The following options are available for (de)serialization control:
  - soap->encodingStyle = NULL; to remove SOAP 1.1/1.2 encodingStyle
  - soap_mode(soap, SOAP_XML_TREE); XML without id-ref (no cycles!)
  - soap_mode(soap, SOAP_XML_GRAPH); XML with id-ref (including cycles)
  - soap_set_namespaces(soap, struct Namespace *nsmap); to set xmlns bindings


@section wst Top-level root elements of schema "http://docs.oasis-open.org/ws-sx/ws-trust/200512/"

  - <wst:RequestSecurityToken> (use wsdl2h option -g to auto-generate type _wst__RequestSecurityToken)

  - <wst:TokenType> (use wsdl2h option -g to auto-generate type _wst__TokenType)

  - <wst:RequestType> (use wsdl2h option -g to auto-generate type _wst__RequestType)

  - <wst:RequestSecurityTokenResponse> (use wsdl2h option -g to auto-generate type _wst__RequestSecurityTokenResponse)

  - <wst:RequestedSecurityToken> (use wsdl2h option -g to auto-generate type _wst__RequestedSecurityToken)

  - <wst:BinarySecret> (use wsdl2h option -g to auto-generate type _wst__BinarySecret)

  - <wst:Claims> (use wsdl2h option -g to auto-generate type _wst__Claims)

  - <wst:Entropy> (use wsdl2h option -g to auto-generate type _wst__Entropy)

  - <wst:Lifetime> (use wsdl2h option -g to auto-generate type _wst__Lifetime)

  - <wst:RequestSecurityTokenCollection> (use wsdl2h option -g to auto-generate type _wst__RequestSecurityTokenCollection)

  - <wst:RequestSecurityTokenResponseCollection> (use wsdl2h option -g to auto-generate type _wst__RequestSecurityTokenResponseCollection)

  - <wst:ComputedKey> (use wsdl2h option -g to auto-generate type _wst__ComputedKey)

  - <wst:RequestedAttachedReference> (use wsdl2h option -g to auto-generate type _wst__RequestedAttachedReference)

  - <wst:RequestedUnattachedReference> (use wsdl2h option -g to auto-generate type _wst__RequestedUnattachedReference)

  - <wst:RequestedProofToken> (use wsdl2h option -g to auto-generate type _wst__RequestedProofToken)

  - <wst:IssuedTokens> (use wsdl2h option -g to auto-generate type _wst__IssuedTokens)

  - <wst:RenewTarget> (use wsdl2h option -g to auto-generate type _wst__RenewTarget)

  - <wst:AllowPostdating> (use wsdl2h option -g to auto-generate type _wst__AllowPostdating)

  - <wst:Renewing> (use wsdl2h option -g to auto-generate type _wst__Renewing)

  - <wst:CancelTarget> (use wsdl2h option -g to auto-generate type _wst__CancelTarget)

  - <wst:RequestedTokenCancelled> (use wsdl2h option -g to auto-generate type _wst__RequestedTokenCancelled)

  - <wst:ValidateTarget> (use wsdl2h option -g to auto-generate type _wst__ValidateTarget)

  - <wst:Status> (use wsdl2h option -g to auto-generate type _wst__Status)

  - <wst:SignChallenge> (use wsdl2h option -g to auto-generate type _wst__SignChallenge)

  - <wst:SignChallengeResponse> (use wsdl2h option -g to auto-generate type _wst__SignChallengeResponse)

  - <wst:Challenge> (use wsdl2h option -g to auto-generate type _wst__Challenge)

  - <wst:BinaryExchange> (use wsdl2h option -g to auto-generate type _wst__BinaryExchange)

  - <wst:RequestKET> (use wsdl2h option -g to auto-generate type _wst__RequestKET)

  - <wst:KeyExchangeToken> (use wsdl2h option -g to auto-generate type _wst__KeyExchangeToken)

  - <wst:Authenticator> (use wsdl2h option -g to auto-generate type _wst__Authenticator)

  - <wst:CombinedHash> (use wsdl2h option -g to auto-generate type _wst__CombinedHash)

  - <wst:OnBehalfOf> (use wsdl2h option -g to auto-generate type _wst__OnBehalfOf)

  - <wst:Issuer> (use wsdl2h option -g to auto-generate type _wst__Issuer)

  - <wst:AuthenticationType> (use wsdl2h option -g to auto-generate type _wst__AuthenticationType)

  - <wst:KeyType> (use wsdl2h option -g to auto-generate type _wst__KeyType)

  - <wst:KeySize> (use wsdl2h option -g to auto-generate type _wst__KeySize)

  - <wst:SignatureAlgorithm> (use wsdl2h option -g to auto-generate type _wst__SignatureAlgorithm)

  - <wst:EncryptionAlgorithm> (use wsdl2h option -g to auto-generate type _wst__EncryptionAlgorithm)

  - <wst:CanonicalizationAlgorithm> (use wsdl2h option -g to auto-generate type _wst__CanonicalizationAlgorithm)

  - <wst:ComputedKeyAlgorithm> (use wsdl2h option -g to auto-generate type _wst__ComputedKeyAlgorithm)

  - <wst:Encryption> (use wsdl2h option -g to auto-generate type _wst__Encryption)

  - <wst:ProofEncryption> (use wsdl2h option -g to auto-generate type _wst__ProofEncryption)

  - <wst:UseKey> (use wsdl2h option -g to auto-generate type _wst__UseKey)

  - <wst:KeyWrapAlgorithm> (use wsdl2h option -g to auto-generate type _wst__KeyWrapAlgorithm)

  - <wst:SignWith> (use wsdl2h option -g to auto-generate type _wst__SignWith)

  - <wst:EncryptWith> (use wsdl2h option -g to auto-generate type _wst__EncryptWith)

  - <wst:DelegateTo> (use wsdl2h option -g to auto-generate type _wst__DelegateTo)

  - <wst:Forwardable> (use wsdl2h option -g to auto-generate type _wst__Forwardable)

  - <wst:Delegatable> (use wsdl2h option -g to auto-generate type _wst__Delegatable)

  - <wst:Participants> (use wsdl2h option -g to auto-generate type _wst__Participants)

*/

#import "wstx.h"

/* End of wst.h */
