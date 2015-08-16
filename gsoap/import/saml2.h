/*
	saml2.h

	Generated with:
	wsdl2h -cuyx -o saml2.h -t WS/WS-typemap.dat WS/saml-schema-assertion-2.0.xsd

	- Removed //gsoapopt
	- Changed //gsoap saml2 schema namespace directive to import directive

*/

/******************************************************************************\
 *                                                                            *
 * Definitions                                                                *
 *   urn:oasis:names:tc:SAML:2.0:assertion                                    *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Import                                                                     *
 *                                                                            *
\******************************************************************************/

#import "ds.h"	// ds = <http://www.w3.org/2000/09/xmldsig#>
#import "xenc.h"	// xenc = <http://www.w3.org/2001/04/xmlenc#>

/******************************************************************************\
 *                                                                            *
 * Schema Namespaces                                                          *
 *                                                                            *
\******************************************************************************/


/// <PRE><BLOCKQUOTE>
///   Document identifier: saml-schema-assertion-2.0
///   Location: http://docs.oasis-open.org/security/saml/v2.0/
///   Revision history:
///   V1.0 (November, 2002):
///   Initial Standard Schema.
///   V1.1 (September, 2003):
///   Updates within the same V1.0 namespace.
///   V2.0 (March, 2005):
///   New assertion schema for SAML V2.0 namespace.
/// </BLOCKQUOTE></PRE>
#define SOAP_NAMESPACE_OF_saml2	"urn:oasis:names:tc:SAML:2.0:assertion"
//gsoap saml2 schema import:	urn:oasis:names:tc:SAML:2.0:assertion
//gsoap saml2 schema form:	unqualified

/******************************************************************************\
 *                                                                            *
 * Built-in Schema Types and Top-Level Elements and Attributes                *
 *                                                                            *
\******************************************************************************/

// Imported element ""http://www.w3.org/2000/09/xmldsig#":KeyInfo" declared as _ds__KeyInfo.
// Imported element ""http://www.w3.org/2000/09/xmldsig#":Signature" declared as _ds__Signature.
// Imported element ""http://www.w3.org/2001/04/xmlenc#":EncryptedData" declared as _xenc__EncryptedData.
// Imported element ""http://www.w3.org/2001/04/xmlenc#":EncryptedKey" declared as _xenc__EncryptedKey.

/// @brief Typedef synonym for struct saml2__BaseIDAbstractType.
typedef struct saml2__BaseIDAbstractType saml2__BaseIDAbstractType;
/// @brief Typedef synonym for struct saml2__NameIDType.
typedef struct saml2__NameIDType saml2__NameIDType;
/// @brief Typedef synonym for struct saml2__EncryptedElementType.
typedef struct saml2__EncryptedElementType saml2__EncryptedElementType;
/// @brief Typedef synonym for struct saml2__AssertionType.
typedef struct saml2__AssertionType saml2__AssertionType;
/// @brief Typedef synonym for struct saml2__SubjectType.
typedef struct saml2__SubjectType saml2__SubjectType;
/// @brief Typedef synonym for struct saml2__SubjectConfirmationType.
typedef struct saml2__SubjectConfirmationType saml2__SubjectConfirmationType;
/// @brief Typedef synonym for struct saml2__SubjectConfirmationDataType.
typedef struct saml2__SubjectConfirmationDataType saml2__SubjectConfirmationDataType;
/// @brief Typedef synonym for struct saml2__KeyInfoConfirmationDataType.
typedef struct saml2__KeyInfoConfirmationDataType saml2__KeyInfoConfirmationDataType;
/// @brief Typedef synonym for struct saml2__ConditionsType.
typedef struct saml2__ConditionsType saml2__ConditionsType;
/// @brief Typedef synonym for struct saml2__ConditionAbstractType.
typedef struct saml2__ConditionAbstractType saml2__ConditionAbstractType;
/// @brief Typedef synonym for struct saml2__AudienceRestrictionType.
typedef struct saml2__AudienceRestrictionType saml2__AudienceRestrictionType;
/// @brief Typedef synonym for struct saml2__OneTimeUseType.
typedef struct saml2__OneTimeUseType saml2__OneTimeUseType;
/// @brief Typedef synonym for struct saml2__ProxyRestrictionType.
typedef struct saml2__ProxyRestrictionType saml2__ProxyRestrictionType;
/// @brief Typedef synonym for struct saml2__AdviceType.
typedef struct saml2__AdviceType saml2__AdviceType;
/// @brief Typedef synonym for struct saml2__StatementAbstractType.
typedef struct saml2__StatementAbstractType saml2__StatementAbstractType;
/// @brief Typedef synonym for struct saml2__AuthnStatementType.
typedef struct saml2__AuthnStatementType saml2__AuthnStatementType;
/// @brief Typedef synonym for struct saml2__SubjectLocalityType.
typedef struct saml2__SubjectLocalityType saml2__SubjectLocalityType;
/// @brief Typedef synonym for struct saml2__AuthnContextType.
typedef struct saml2__AuthnContextType saml2__AuthnContextType;
/// @brief Typedef synonym for struct saml2__AuthzDecisionStatementType.
typedef struct saml2__AuthzDecisionStatementType saml2__AuthzDecisionStatementType;
/// @brief Typedef synonym for struct saml2__ActionType.
typedef struct saml2__ActionType saml2__ActionType;
/// @brief Typedef synonym for struct saml2__EvidenceType.
typedef struct saml2__EvidenceType saml2__EvidenceType;
/// @brief Typedef synonym for struct saml2__AttributeStatementType.
typedef struct saml2__AttributeStatementType saml2__AttributeStatementType;
/// @brief Typedef synonym for struct saml2__AttributeType.
typedef struct saml2__AttributeType saml2__AttributeType;

/******************************************************************************\
 *                                                                            *
 * Schema Types and Top-Level Elements and Attributes                         *
 *   urn:oasis:names:tc:SAML:2.0:assertion                                    *
 *                                                                            *
\******************************************************************************/

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":DecisionType is a simpleType restriction of XSD type xs:string.
///
/// @note The enum values are prefixed with "saml2__DecisionType__" to avoid name clashes, please use wsdl2h option -e to omit this prefix
enum saml2__DecisionType
{
	saml2__DecisionType__Permit,	///< xs:string value="Permit"
	saml2__DecisionType__Deny,	///< xs:string value="Deny"
	saml2__DecisionType__Indeterminate,	///< xs:string value="Indeterminate"
};

/// @brief Typedef synonym for enum saml2__DecisionType.
typedef enum saml2__DecisionType saml2__DecisionType;

/******************************************************************************\
 *                                                                            *
 * Schema Complex Types and Top-Level Elements                                *
 *   urn:oasis:names:tc:SAML:2.0:assertion                                    *
 *                                                                            *
\******************************************************************************/

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":BaseIDAbstractType is an abstract complexType.
///
struct saml2__BaseIDAbstractType
{
//  BEGIN ATTRIBUTEGROUP <xs:attributeGroup ref=""urn:oasis:names:tc:SAML:2.0:assertion":IDNameQualifiers">.
/// Attribute "NameQualifier" of XSD type xs:string.
   @char*                                NameQualifier                  0;	///< Optional attribute.
/// Attribute "SPNameQualifier" of XSD type xs:string.
   @char*                                SPNameQualifier                0;	///< Optional attribute.
//  END OF ATTRIBUTEGROUP
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":EncryptedElementType is a complexType.
///
struct saml2__EncryptedElementType
{
/// Imported element reference "http://www.w3.org/2001/04/xmlenc#":EncryptedData.
    _xenc__EncryptedData                 xenc__EncryptedData            1;	///< Required element.
/// Imported element reference "http://www.w3.org/2001/04/xmlenc#":EncryptedKey.
/// Size of "http://www.w3.org/2001/04/xmlenc#":EncryptedKey array is 0..unbounded.
   $int                                  __sizexenc__EncryptedKey       0;
    _xenc__EncryptedKey*                *xenc__EncryptedKey             0;
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":AssertionType is a complexType.
///
struct saml2__AssertionType
{
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":Issuer.
    struct saml2__NameIDType*            saml2__Issuer                  1;	///< Required element.
/// Imported element reference "http://www.w3.org/2000/09/xmldsig#":Signature.
    _ds__Signature*                      ds__Signature                  0;	///< Optional element.
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":Subject.
    struct saml2__SubjectType*           saml2__Subject                 0;	///< Optional element.
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":Conditions.
    struct saml2__ConditionsType*        saml2__Conditions              0;	///< Optional element.
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":Advice.
    struct saml2__AdviceType*            saml2__Advice                  0;	///< Optional element.
//  BEGIN CHOICE <xs:choice minOccurs="0" maxOccurs="unbounded">
   $int                                  __size_AssertionType           0;
    struct __saml2__union_AssertionType
    {
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":Statement.
    struct saml2__StatementAbstractType*  saml2__Statement              ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AuthnStatement.
    struct saml2__AuthnStatementType*    saml2__AuthnStatement         ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AuthzDecisionStatement.
    struct saml2__AuthzDecisionStatementType*  saml2__AuthzDecisionStatement ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AttributeStatement.
    struct saml2__AttributeStatementType*  saml2__AttributeStatement     ;
    }                                   *__union_AssertionType         ;
//  END OF CHOICE
/// Attribute "Version" of XSD type xs:string.
   @char*                                Version                        1;	///< Required attribute.
/// Attribute "ID" of XSD type xs:ID.
   @char*                                ID                             1;	///< Required attribute.
/// Attribute "IssueInstant" of XSD type xs:dateTime.
   @time_t                               IssueInstant                   1;	///< Required attribute.
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":SubjectType is a complexType.
///
struct saml2__SubjectType
{
//  BEGIN CHOICE <xs:choice>
/// @note <xs:choice> with embedded <xs:sequence> or <xs:group> prevents the use of a union for <xs:choice>. Instead of being members of a union, the following members are declared optional. Only one member should be non-NULL by choice.
//  BEGIN SEQUENCE <xs:sequence>
//  BEGIN CHOICE <xs:choice>
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":BaseID.
    struct saml2__BaseIDAbstractType*    saml2__BaseID                 ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":NameID.
    struct saml2__NameIDType*            saml2__NameID                 ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":EncryptedID.
    struct saml2__EncryptedElementType*  saml2__EncryptedID            ;
//  END OF CHOICE
/// Size of the dynamic array of struct saml2__SubjectConfirmationType* is 0..unbounded.
   $int                                  __sizeSubjectConfirmation      0;
/// Array struct saml2__SubjectConfirmationType* of size 0..unbounded.
    struct saml2__SubjectConfirmationType*  saml2__SubjectConfirmation    ;
//  END OF SEQUENCE
/// Size of the dynamic array of struct saml2__SubjectConfirmationType* is 1..unbounded.
   $int                                  __sizeSubjectConfirmation      0;
/// Array struct saml2__SubjectConfirmationType* of size 1..unbounded.
    struct saml2__SubjectConfirmationType*  saml2__SubjectConfirmation    ;
//  END OF CHOICE
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":SubjectConfirmationType is a complexType.
///
struct saml2__SubjectConfirmationType
{
//  BEGIN CHOICE <xs:choice minOccurs="0">
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":BaseID.
    struct saml2__BaseIDAbstractType*    saml2__BaseID                 ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":NameID.
    struct saml2__NameIDType*            saml2__NameID                 ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":EncryptedID.
    struct saml2__EncryptedElementType*  saml2__EncryptedID            ;
//  END OF CHOICE
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":SubjectConfirmationData.
    struct saml2__SubjectConfirmationDataType*  saml2__SubjectConfirmationData 0;	///< Optional element.
/// Attribute "Method" of XSD type xs:anyURI.
   @char*                                Method                         1;	///< Required attribute.
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":ConditionsType is a complexType.
///
struct saml2__ConditionsType
{
//  BEGIN CHOICE <xs:choice minOccurs="0" maxOccurs="unbounded">
   $int                                  __size_ConditionsType          0;
    struct __saml2__union_ConditionsType
    {
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":Condition.
    struct saml2__ConditionAbstractType*  saml2__Condition              ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AudienceRestriction.
    struct saml2__AudienceRestrictionType*  saml2__AudienceRestriction    ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":OneTimeUse.
    struct saml2__OneTimeUseType*        saml2__OneTimeUse             ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":ProxyRestriction.
    struct saml2__ProxyRestrictionType*  saml2__ProxyRestriction       ;
    }                                   *__union_ConditionsType        ;
//  END OF CHOICE
/// Attribute "NotBefore" of XSD type xs:dateTime.
   @time_t*                              NotBefore                      0;	///< Optional attribute.
/// Attribute "NotOnOrAfter" of XSD type xs:dateTime.
   @time_t*                              NotOnOrAfter                   0;	///< Optional attribute.
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":ConditionAbstractType is an abstract complexType.
///
struct saml2__ConditionAbstractType
{
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":AdviceType is a complexType.
///
struct saml2__AdviceType
{
//  BEGIN CHOICE <xs:choice minOccurs="0" maxOccurs="unbounded">
   $int                                  __size_AdviceType              0;
    struct __saml2__union_AdviceType
    {
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AssertionIDRef.
    char*                                saml2__AssertionIDRef         ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AssertionURIRef.
    char*                                saml2__AssertionURIRef        ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":Assertion.
    struct saml2__AssertionType*         saml2__Assertion              ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":EncryptedAssertion.
    struct saml2__EncryptedElementType*  saml2__EncryptedAssertion     ;
/// @todo <any namespace="##other">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element).
    }                                   *__union_AdviceType            ;
//  END OF CHOICE
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":StatementAbstractType is an abstract complexType.
///
struct saml2__StatementAbstractType
{
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":SubjectLocalityType is a complexType.
///
struct saml2__SubjectLocalityType
{
/// Attribute "Address" of XSD type xs:string.
   @char*                                Address                        0;	///< Optional attribute.
/// Attribute "DNSName" of XSD type xs:string.
   @char*                                DNSName                        0;	///< Optional attribute.
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":AuthnContextType is a complexType.
///
struct saml2__AuthnContextType
{
//  BEGIN CHOICE <xs:choice>
/// @note <xs:choice> with embedded <xs:sequence> or <xs:group> prevents the use of a union for <xs:choice>. Instead of being members of a union, the following members are declared optional. Only one member should be non-NULL by choice.
//  BEGIN SEQUENCE <xs:sequence>
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AuthnContextClassRef.
    char*                                saml2__AuthnContextClassRef   ;
//  BEGIN CHOICE <xs:choice minOccurs="0">
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AuthnContextDecl.
    _XML                                 saml2__AuthnContextDecl       ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AuthnContextDeclRef.
    char*                                saml2__AuthnContextDeclRef    ;
//  END OF CHOICE
//  END OF SEQUENCE
//  BEGIN CHOICE <xs:choice>
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AuthnContextDecl.
    _XML                                 saml2__AuthnContextDecl       ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AuthnContextDeclRef.
    char*                                saml2__AuthnContextDeclRef    ;
//  END OF CHOICE
//  END OF CHOICE
/// Size of the dynamic array of char** is 0..unbounded.
   $int                                  __sizeAuthenticatingAuthority  0;
/// Array char** of size 0..unbounded.
    char**                               saml2__AuthenticatingAuthority 0;
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":EvidenceType is a complexType.
///
struct saml2__EvidenceType
{
//  BEGIN CHOICE <xs:choice maxOccurs="unbounded">
   $int                                  __size_EvidenceType            0;
    struct __saml2__union_EvidenceType
    {
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AssertionIDRef.
    char*                                saml2__AssertionIDRef         ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AssertionURIRef.
    char*                                saml2__AssertionURIRef        ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":Assertion.
    struct saml2__AssertionType*         saml2__Assertion              ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":EncryptedAssertion.
    struct saml2__EncryptedElementType*  saml2__EncryptedAssertion     ;
    }                                   *__union_EvidenceType          ;
//  END OF CHOICE
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":AttributeType is a complexType.
///
struct saml2__AttributeType
{
/// Size of the dynamic array of _XML* is 0..unbounded.
   $int                                  __sizeAttributeValue           0;
/// Array _XML* of size 0..unbounded.
    _XML*                                saml2__AttributeValue          0;
/// Attribute "Name" of XSD type xs:string.
   @char*                                Name                           1;	///< Required attribute.
/// Attribute "NameFormat" of XSD type xs:anyURI.
   @char*                                NameFormat                     0;	///< Optional attribute.
/// Attribute "FriendlyName" of XSD type xs:string.
   @char*                                FriendlyName                   0;	///< Optional attribute.
/// @todo <anyAttribute namespace="##other">.
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this attribute.
///       Use wsdl2h option -d for xsd__anyAttribute DOM (soap_dom_attribute).
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":NameIDType is a complexType with simpleContent.
///
struct saml2__NameIDType
{
/// __item wraps "xs:string" simpleContent.
    char*                                __item                        ;
/// Attribute "Format" of XSD type xs:anyURI.
   @char*                                Format                         0;	///< Optional attribute.
/// Attribute "SPProvidedID" of XSD type xs:string.
   @char*                                SPProvidedID                   0;	///< Optional attribute.
//  BEGIN ATTRIBUTEGROUP <xs:attributeGroup ref=""urn:oasis:names:tc:SAML:2.0:assertion":IDNameQualifiers">.
/// Attribute "NameQualifier" of XSD type xs:string.
   @char*                                NameQualifier                  0;	///< Optional attribute.
/// Attribute "SPNameQualifier" of XSD type xs:string.
   @char*                                SPNameQualifier                0;	///< Optional attribute.
//  END OF ATTRIBUTEGROUP
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":SubjectConfirmationDataType is a complexType with complexContent restriction of XSD type xs:anyType.
///
struct saml2__SubjectConfirmationDataType
{
/// @todo <any namespace="##any" minOccurs="0" maxOccurs="unbounded">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element).
/// Attribute "NotBefore" of XSD type xs:dateTime.
   @time_t*                              NotBefore                      0;	///< Optional attribute.
/// Attribute "NotOnOrAfter" of XSD type xs:dateTime.
   @time_t*                              NotOnOrAfter                   0;	///< Optional attribute.
/// Attribute "Recipient" of XSD type xs:anyURI.
   @char*                                Recipient                      0;	///< Optional attribute.
/// Attribute "InResponseTo" of XSD type xs:NCName.
   @char*                                InResponseTo                   0;	///< Optional attribute.
/// Attribute "Address" of XSD type xs:string.
   @char*                                Address                        0;	///< Optional attribute.
/// @todo <anyAttribute namespace="##other">.
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this attribute.
///       Use wsdl2h option -d for xsd__anyAttribute DOM (soap_dom_attribute).
/// @todo This mixed complexType is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element).
    _XML                                 __mixed                       0;	///< Catch mixed content in XML string.
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":AudienceRestrictionType is a complexType with complexContent extension of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":ConditionAbstractType.
///
struct saml2__AudienceRestrictionType
{
/// INHERITED FROM saml2__ConditionAbstractType:
//  END OF INHERITED FROM saml2__ConditionAbstractType
/// Size of the dynamic array of char** is 1..unbounded.
   $int                                  __sizeAudience                 1;
/// Array char** of size 1..unbounded.
    char**                               saml2__Audience                1;
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":OneTimeUseType is a complexType with complexContent extension of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":ConditionAbstractType.
///
struct saml2__OneTimeUseType
{
/// INHERITED FROM saml2__ConditionAbstractType:
//  END OF INHERITED FROM saml2__ConditionAbstractType
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":ProxyRestrictionType is a complexType with complexContent extension of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":ConditionAbstractType.
///
struct saml2__ProxyRestrictionType
{
/// INHERITED FROM saml2__ConditionAbstractType:
//  END OF INHERITED FROM saml2__ConditionAbstractType
/// Size of the dynamic array of char** is 0..unbounded.
   $int                                  __sizeAudience                 0;
/// Array char** of size 0..unbounded.
    char**                               saml2__Audience                0;
/// Attribute "Count" of XSD type xs:nonNegativeInteger.
   @char*                                Count                          0;	///< Optional attribute.
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":AuthnStatementType is a complexType with complexContent extension of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":StatementAbstractType.
///
struct saml2__AuthnStatementType
{
/// INHERITED FROM saml2__StatementAbstractType:
//  END OF INHERITED FROM saml2__StatementAbstractType
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":SubjectLocality.
    struct saml2__SubjectLocalityType*   saml2__SubjectLocality         0;	///< Optional element.
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":AuthnContext.
    struct saml2__AuthnContextType*      saml2__AuthnContext            1;	///< Required element.
/// Attribute "AuthnInstant" of XSD type xs:dateTime.
   @time_t                               AuthnInstant                   1;	///< Required attribute.
/// Attribute "SessionIndex" of XSD type xs:string.
   @char*                                SessionIndex                   0;	///< Optional attribute.
/// Attribute "SessionNotOnOrAfter" of XSD type xs:dateTime.
   @time_t*                              SessionNotOnOrAfter            0;	///< Optional attribute.
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":AuthzDecisionStatementType is a complexType with complexContent extension of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":StatementAbstractType.
///
struct saml2__AuthzDecisionStatementType
{
/// INHERITED FROM saml2__StatementAbstractType:
//  END OF INHERITED FROM saml2__StatementAbstractType
/// Size of the dynamic array of struct saml2__ActionType* is 1..unbounded.
   $int                                  __sizeAction                   1;
/// Array struct saml2__ActionType* of size 1..unbounded.
    struct saml2__ActionType*            saml2__Action                  1;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":Evidence.
    struct saml2__EvidenceType*          saml2__Evidence                0;	///< Optional element.
/// Attribute "Resource" of XSD type xs:anyURI.
   @char*                                Resource                       1;	///< Required attribute.
/// Attribute "Decision" of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":DecisionType.
   @enum saml2__DecisionType             Decision                       1;	///< Required attribute.
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":ActionType is a complexType with simpleContent.
///
struct saml2__ActionType
{
/// __item wraps "xs:string" simpleContent.
    char*                                __item                        ;
/// Attribute "Namespace" of XSD type xs:anyURI.
   @char*                                Namespace                      1;	///< Required attribute.
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":AttributeStatementType is a complexType with complexContent extension of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":StatementAbstractType.
///
struct saml2__AttributeStatementType
{
/// INHERITED FROM saml2__StatementAbstractType:
//  END OF INHERITED FROM saml2__StatementAbstractType
//  BEGIN CHOICE <xs:choice maxOccurs="unbounded">
   $int                                  __size_AttributeStatementType  0;
    struct __saml2__union_AttributeStatementType
    {
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":Attribute.
    struct saml2__AttributeType*         saml2__Attribute              ;
/// Element reference "urn:oasis:names:tc:SAML:2.0:assertion:""urn:oasis:names:tc:SAML:2.0:assertion":EncryptedAttribute.
    struct saml2__EncryptedElementType*  saml2__EncryptedAttribute     ;
    }                                   *__union_AttributeStatementType;
//  END OF CHOICE
};

/// @brief "urn:oasis:names:tc:SAML:2.0:assertion":KeyInfoConfirmationDataType is a complexType with complexContent restriction of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":SubjectConfirmationDataType.
///
struct saml2__KeyInfoConfirmationDataType
{
/// Imported element reference "http://www.w3.org/2000/09/xmldsig#":KeyInfo.
/// Size of "http://www.w3.org/2000/09/xmldsig#":KeyInfo array is 1..unbounded.
   $int                                  __sizeds__KeyInfo              1;
    _ds__KeyInfo*                       *ds__KeyInfo                    1;
/*  RESTRICTED FROM saml2__SubjectConfirmationDataType:
/// Attribute "NotBefore" of XSD type xs:dateTime.
   @time_t*                              NotBefore                      0;	///< Optional attribute.
/// Attribute "NotOnOrAfter" of XSD type xs:dateTime.
   @time_t*                              NotOnOrAfter                   0;	///< Optional attribute.
/// Attribute "Recipient" of XSD type xs:anyURI.
   @char*                                Recipient                      0;	///< Optional attribute.
/// Attribute "InResponseTo" of XSD type xs:NCName.
   @char*                                InResponseTo                   0;	///< Optional attribute.
/// Attribute "Address" of XSD type xs:string.
   @char*                                Address                        0;	///< Optional attribute.
/// @todo <anyAttribute namespace="##other">.
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this attribute.
///       Use wsdl2h option -d for xsd__anyAttribute DOM (soap_dom_attribute).
    END OF RESTRICTED FROM saml2__SubjectConfirmationDataType */
};


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Elements                                              *
 *   urn:oasis:names:tc:SAML:2.0:assertion                                    *
 *                                                                            *
\******************************************************************************/

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":BaseID of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":BaseIDAbstractType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":NameID of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":NameIDType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":EncryptedID of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":EncryptedElementType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":Issuer of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":NameIDType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":AssertionIDRef of XSD type xs:NCName.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":AssertionURIRef of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":Assertion of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":AssertionType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":Subject of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":SubjectType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":SubjectConfirmation of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":SubjectConfirmationType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":SubjectConfirmationData of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":SubjectConfirmationDataType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":Conditions of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":ConditionsType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":Condition of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":ConditionAbstractType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":AudienceRestriction of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":AudienceRestrictionType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":Audience of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":OneTimeUse of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":OneTimeUseType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":ProxyRestriction of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":ProxyRestrictionType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":Advice of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":AdviceType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":EncryptedAssertion of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":EncryptedElementType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":Statement of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":StatementAbstractType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":AuthnStatement of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":AuthnStatementType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":SubjectLocality of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":SubjectLocalityType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":AuthnContext of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":AuthnContextType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":AuthnContextClassRef of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":AuthnContextDeclRef of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":AuthnContextDecl of XSD type xs:anyType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":AuthenticatingAuthority of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":AuthzDecisionStatement of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":AuthzDecisionStatementType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":Action of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":ActionType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":Evidence of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":EvidenceType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":AttributeStatement of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":AttributeStatementType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":Attribute of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":AttributeType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":AttributeValue of XSD type xs:anyType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:2.0:assertion":EncryptedAttribute of XSD type "urn:oasis:names:tc:SAML:2.0:assertion":EncryptedElementType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Attributes                                            *
 *   urn:oasis:names:tc:SAML:2.0:assertion                                    *
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

Data can be read in XML and deserialized from:
  - a file descriptor, using soap->recvfd = fd
  - a socket, using soap->socket = ...
  - a C++ stream, using soap->is = ...
  - a buffer, using the soap->frecv() callback

Data can be serialized in XML and written to:
  - a file descriptor, using soap->sendfd = fd
  - a socket, using soap->socket = ...
  - a C++ stream, using soap->os = ...
  - a buffer, using the soap->fsend() callback

The following options are available for (de)serialization control:
  - soap->encodingStyle = NULL; to remove SOAP 1.1/1.2 encodingStyle
  - soap_mode(soap, SOAP_XML_TREE); XML without id-ref (no cycles!)
  - soap_mode(soap, SOAP_XML_GRAPH); XML with id-ref (including cycles)
  - soap_set_namespaces(soap, struct Namespace *nsmap); to set xmlns bindings


@section saml2 Top-level root elements of schema "urn:oasis:names:tc:SAML:2.0:assertion"

  - <BaseID> (use wsdl2h option -g to auto-generate)

  - <NameID> (use wsdl2h option -g to auto-generate)

  - <EncryptedID> (use wsdl2h option -g to auto-generate)

  - <Issuer> (use wsdl2h option -g to auto-generate)

  - <AssertionIDRef> (use wsdl2h option -g to auto-generate)

  - <AssertionURIRef> (use wsdl2h option -g to auto-generate)

  - <Assertion> (use wsdl2h option -g to auto-generate)

  - <Subject> (use wsdl2h option -g to auto-generate)

  - <SubjectConfirmation> (use wsdl2h option -g to auto-generate)

  - <SubjectConfirmationData> (use wsdl2h option -g to auto-generate)

  - <Conditions> (use wsdl2h option -g to auto-generate)

  - <Condition> (use wsdl2h option -g to auto-generate)

  - <AudienceRestriction> (use wsdl2h option -g to auto-generate)

  - <Audience> (use wsdl2h option -g to auto-generate)

  - <OneTimeUse> (use wsdl2h option -g to auto-generate)

  - <ProxyRestriction> (use wsdl2h option -g to auto-generate)

  - <Advice> (use wsdl2h option -g to auto-generate)

  - <EncryptedAssertion> (use wsdl2h option -g to auto-generate)

  - <Statement> (use wsdl2h option -g to auto-generate)

  - <AuthnStatement> (use wsdl2h option -g to auto-generate)

  - <SubjectLocality> (use wsdl2h option -g to auto-generate)

  - <AuthnContext> (use wsdl2h option -g to auto-generate)

  - <AuthnContextClassRef> (use wsdl2h option -g to auto-generate)

  - <AuthnContextDeclRef> (use wsdl2h option -g to auto-generate)

  - <AuthnContextDecl> (use wsdl2h option -g to auto-generate)

  - <AuthenticatingAuthority> (use wsdl2h option -g to auto-generate)

  - <AuthzDecisionStatement> (use wsdl2h option -g to auto-generate)

  - <Action> (use wsdl2h option -g to auto-generate)

  - <Evidence> (use wsdl2h option -g to auto-generate)

  - <AttributeStatement> (use wsdl2h option -g to auto-generate)

  - <Attribute> (use wsdl2h option -g to auto-generate)

  - <AttributeValue> (use wsdl2h option -g to auto-generate)

  - <EncryptedAttribute> (use wsdl2h option -g to auto-generate)

*/

/* End of saml2.h */
