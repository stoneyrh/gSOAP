/*
	saml1.h

	Generated with:
	wsdl2h -cuyx -o saml1.h -t WS/WS-typemap.dat WS/oasis-sstc-saml-schema-assertion-1.1.xsd

	- Removed //gsoapopt
	- Changed //gsoap saml1 schema namespace directive to import directive
	- Replaced #import "ds.h" with #import "xenc.h" (that imports "ds.h")
	- Commented out duplicate saml1__SubjectConfirmation member (due to choice/seq)

*/

/******************************************************************************\
 *                                                                            *
 * Definitions                                                                *
 *   urn:oasis:names:tc:SAML:1.0:assertion                                    *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Import                                                                     *
 *                                                                            *
\******************************************************************************/

#import "xenc.h"	// xenc = <http://www.w3.org/2001/04/xmlenc#>

/******************************************************************************\
 *                                                                            *
 * Schema Namespaces                                                          *
 *                                                                            *
\******************************************************************************/

/// <PRE><BLOCKQUOTE>
///   Document identifier: oasis-sstc-saml-schema-assertion-1.1
///   Location: http://www.oasis-open.org/committees/documents.php?wg_abbrev=security
///   Revision history:
///   V1.0 (November, 2002):
///   Initial standard schema.
///   V1.1 (September, 2003):
///   * Note that V1.1 of this schema has the same XML namespace as V1.0.
///   Rebased ID content directly on XML Schema types
///   Added DoNotCacheCondition element and DoNotCacheConditionType
/// </BLOCKQUOTE></PRE>
#define SOAP_NAMESPACE_OF_saml1	"urn:oasis:names:tc:SAML:1.0:assertion"
//gsoap saml1 schema import:	urn:oasis:names:tc:SAML:1.0:assertion
//gsoap saml1 schema form:	unqualified

/******************************************************************************\
 *                                                                            *
 * Built-in Schema Types and Top-Level Elements and Attributes                *
 *                                                                            *
\******************************************************************************/

// Imported element ""http://www.w3.org/2000/09/xmldsig#":KeyInfo" declared as _ds__KeyInfo.
// Imported element ""http://www.w3.org/2000/09/xmldsig#":Signature" declared as _ds__Signature.

/// @brief Typedef synonym for struct saml1__AssertionType.
typedef struct saml1__AssertionType saml1__AssertionType;
/// @brief Typedef synonym for struct saml1__ConditionsType.
typedef struct saml1__ConditionsType saml1__ConditionsType;
/// @brief Typedef synonym for struct saml1__ConditionAbstractType.
typedef struct saml1__ConditionAbstractType saml1__ConditionAbstractType;
/// @brief Typedef synonym for struct saml1__AudienceRestrictionConditionType.
typedef struct saml1__AudienceRestrictionConditionType saml1__AudienceRestrictionConditionType;
/// @brief Typedef synonym for struct saml1__DoNotCacheConditionType.
typedef struct saml1__DoNotCacheConditionType saml1__DoNotCacheConditionType;
/// @brief Typedef synonym for struct saml1__AdviceType.
typedef struct saml1__AdviceType saml1__AdviceType;
/// @brief Typedef synonym for struct saml1__StatementAbstractType.
typedef struct saml1__StatementAbstractType saml1__StatementAbstractType;
/// @brief Typedef synonym for struct saml1__SubjectStatementAbstractType.
typedef struct saml1__SubjectStatementAbstractType saml1__SubjectStatementAbstractType;
/// @brief Typedef synonym for struct saml1__SubjectType.
typedef struct saml1__SubjectType saml1__SubjectType;
/// @brief Typedef synonym for struct saml1__NameIdentifierType.
typedef struct saml1__NameIdentifierType saml1__NameIdentifierType;
/// @brief Typedef synonym for struct saml1__SubjectConfirmationType.
typedef struct saml1__SubjectConfirmationType saml1__SubjectConfirmationType;
/// @brief Typedef synonym for struct saml1__AuthenticationStatementType.
typedef struct saml1__AuthenticationStatementType saml1__AuthenticationStatementType;
/// @brief Typedef synonym for struct saml1__SubjectLocalityType.
typedef struct saml1__SubjectLocalityType saml1__SubjectLocalityType;
/// @brief Typedef synonym for struct saml1__AuthorityBindingType.
typedef struct saml1__AuthorityBindingType saml1__AuthorityBindingType;
/// @brief Typedef synonym for struct saml1__AuthorizationDecisionStatementType.
typedef struct saml1__AuthorizationDecisionStatementType saml1__AuthorizationDecisionStatementType;
/// @brief Typedef synonym for struct saml1__ActionType.
typedef struct saml1__ActionType saml1__ActionType;
/// @brief Typedef synonym for struct saml1__EvidenceType.
typedef struct saml1__EvidenceType saml1__EvidenceType;
/// @brief Typedef synonym for struct saml1__AttributeStatementType.
typedef struct saml1__AttributeStatementType saml1__AttributeStatementType;
/// @brief Typedef synonym for struct saml1__AttributeDesignatorType.
typedef struct saml1__AttributeDesignatorType saml1__AttributeDesignatorType;
/// @brief Typedef synonym for struct saml1__AttributeType.
typedef struct saml1__AttributeType saml1__AttributeType;

/******************************************************************************\
 *                                                                            *
 * Schema Types and Top-Level Elements and Attributes                         *
 *   urn:oasis:names:tc:SAML:1.0:assertion                                    *
 *                                                                            *
\******************************************************************************/

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":DecisionType is a simpleType restriction of XSD type xs:string.
///
/// @note The enum values are prefixed with "saml1__DecisionType__" to prevent name clashes: use wsdl2h option -e to omit this prefix or use option -c++11 for scoped enumerations
enum saml1__DecisionType
{
	saml1__DecisionType__Permit,	///< xs:string value="Permit"
	saml1__DecisionType__Deny,	///< xs:string value="Deny"
	saml1__DecisionType__Indeterminate,	///< xs:string value="Indeterminate"
};

/// @brief Typedef synonym for enum saml1__DecisionType.
typedef enum saml1__DecisionType saml1__DecisionType;

/******************************************************************************\
 *                                                                            *
 * Schema Complex Types and Top-Level Elements                                *
 *   urn:oasis:names:tc:SAML:1.0:assertion                                    *
 *                                                                            *
\******************************************************************************/

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":AssertionType is a complexType.
///
/// struct saml1__AssertionType operations:
/// - soap_default_saml1__AssertionType(soap*, saml1__AssertionType*) reset members to default
/// - int soap_read_saml1__AssertionType(soap*, saml1__AssertionType*) deserialize from a source
/// - int soap_write_saml1__AssertionType(soap*, saml1__AssertionType*) serialize to a sink
/// - saml1__AssertionType* soap_dup_saml1__AssertionType(soap*, saml1__AssertionType* dst, saml1__AssertionType *src) returns deep copy of saml1__AssertionType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__AssertionType(saml1__AssertionType*) deep deletes saml1__AssertionType data members, use only on dst after soap_dup_saml1__AssertionType(NULL, saml1__AssertionType *dst, saml1__AssertionType *src) (use soapcpp2 -Ed)
struct saml1__AssertionType
{
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":Conditions.
    struct saml1__ConditionsType*        saml1__Conditions              0;	///< Optional element.
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":Advice.
    struct saml1__AdviceType*            saml1__Advice                  0;	///< Optional element.
//  BEGIN CHOICE <xs:choice maxOccurs="unbounded">
   $int                                  __size_AssertionType           0;
    struct __saml1__union_AssertionType
    {
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":Statement.
    struct saml1__StatementAbstractType*  saml1__Statement              ;
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":SubjectStatement.
    struct saml1__SubjectStatementAbstractType*  saml1__SubjectStatement       ;
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":AuthenticationStatement.
    struct saml1__AuthenticationStatementType*  saml1__AuthenticationStatement;
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":AuthorizationDecisionStatement.
    struct saml1__AuthorizationDecisionStatementType*  saml1__AuthorizationDecisionStatement;
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":AttributeStatement.
    struct saml1__AttributeStatementType*  saml1__AttributeStatement     ;
    }                                   *__union_AssertionType         ;
//  END OF CHOICE
/// Imported element reference "http://www.w3.org/2000/09/xmldsig#":Signature.
    _ds__Signature*                      ds__Signature                  0;	///< Optional element.
/// Attribute "MajorVersion" of XSD type xs:integer.
   @char*                                MajorVersion                   1;	///< Required attribute.
/// Attribute "MinorVersion" of XSD type xs:integer.
   @char*                                MinorVersion                   1;	///< Required attribute.
/// Attribute "AssertionID" of XSD type xs:ID.
   @char*                                AssertionID                    1;	///< Required attribute.
/// Attribute "Issuer" of XSD type xs:string.
   @char*                                Issuer                         1;	///< Required attribute.
/// Attribute "IssueInstant" of XSD type xs:dateTime.
   @time_t                               IssueInstant                   1;	///< Required attribute.
/// Member declared in WS/WS-typemap.dat
   @char*                                wsu__Id                        1;	///< Optional attribute.
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":ConditionsType is a complexType.
///
/// struct saml1__ConditionsType operations:
/// - soap_default_saml1__ConditionsType(soap*, saml1__ConditionsType*) reset members to default
/// - int soap_read_saml1__ConditionsType(soap*, saml1__ConditionsType*) deserialize from a source
/// - int soap_write_saml1__ConditionsType(soap*, saml1__ConditionsType*) serialize to a sink
/// - saml1__ConditionsType* soap_dup_saml1__ConditionsType(soap*, saml1__ConditionsType* dst, saml1__ConditionsType *src) returns deep copy of saml1__ConditionsType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__ConditionsType(saml1__ConditionsType*) deep deletes saml1__ConditionsType data members, use only on dst after soap_dup_saml1__ConditionsType(NULL, saml1__ConditionsType *dst, saml1__ConditionsType *src) (use soapcpp2 -Ed)
struct saml1__ConditionsType
{
//  BEGIN CHOICE <xs:choice minOccurs="0" maxOccurs="unbounded">
   $int                                  __size_ConditionsType          0;
    struct __saml1__union_ConditionsType
    {
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":AudienceRestrictionCondition.
    struct saml1__AudienceRestrictionConditionType*  saml1__AudienceRestrictionCondition;
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":DoNotCacheCondition.
    struct saml1__DoNotCacheConditionType*  saml1__DoNotCacheCondition    ;
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":Condition.
    struct saml1__ConditionAbstractType*  saml1__Condition              ;
    }                                   *__union_ConditionsType        ;
//  END OF CHOICE
/// Attribute "NotBefore" of XSD type xs:dateTime.
   @time_t*                              NotBefore                      0;	///< Optional attribute.
/// Attribute "NotOnOrAfter" of XSD type xs:dateTime.
   @time_t*                              NotOnOrAfter                   0;	///< Optional attribute.
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":ConditionAbstractType is an abstract complexType.
///
/// struct saml1__ConditionAbstractType operations:
/// - soap_default_saml1__ConditionAbstractType(soap*, saml1__ConditionAbstractType*) reset members to default
/// - int soap_read_saml1__ConditionAbstractType(soap*, saml1__ConditionAbstractType*) deserialize from a source
/// - int soap_write_saml1__ConditionAbstractType(soap*, saml1__ConditionAbstractType*) serialize to a sink
/// - saml1__ConditionAbstractType* soap_dup_saml1__ConditionAbstractType(soap*, saml1__ConditionAbstractType* dst, saml1__ConditionAbstractType *src) returns deep copy of saml1__ConditionAbstractType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__ConditionAbstractType(saml1__ConditionAbstractType*) deep deletes saml1__ConditionAbstractType data members, use only on dst after soap_dup_saml1__ConditionAbstractType(NULL, saml1__ConditionAbstractType *dst, saml1__ConditionAbstractType *src) (use soapcpp2 -Ed)
struct saml1__ConditionAbstractType
{
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":AdviceType is a complexType.
///
/// struct saml1__AdviceType operations:
/// - soap_default_saml1__AdviceType(soap*, saml1__AdviceType*) reset members to default
/// - int soap_read_saml1__AdviceType(soap*, saml1__AdviceType*) deserialize from a source
/// - int soap_write_saml1__AdviceType(soap*, saml1__AdviceType*) serialize to a sink
/// - saml1__AdviceType* soap_dup_saml1__AdviceType(soap*, saml1__AdviceType* dst, saml1__AdviceType *src) returns deep copy of saml1__AdviceType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__AdviceType(saml1__AdviceType*) deep deletes saml1__AdviceType data members, use only on dst after soap_dup_saml1__AdviceType(NULL, saml1__AdviceType *dst, saml1__AdviceType *src) (use soapcpp2 -Ed)
struct saml1__AdviceType
{
//  BEGIN CHOICE <xs:choice minOccurs="0" maxOccurs="unbounded">
   $int                                  __size_AdviceType              0;
    struct __saml1__union_AdviceType
    {
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":AssertionIDReference.
    char*                                saml1__AssertionIDReference   ;
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":Assertion.
    struct saml1__AssertionType*         saml1__Assertion              ;
/// @todo <any namespace="##other">
/// @todo Schema extensibility is user-definable.
///       Consult the protocol documentation to change or insert declarations.
///       Use wsdl2h option -x to remove this element.
///       Use wsdl2h option -d for xsd__anyType DOM (soap_dom_element):
///       wsdl2h maps xsd:any to xsd__anyType, use typemap.dat to remap.
    }                                   *__union_AdviceType            ;
//  END OF CHOICE
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":StatementAbstractType is an abstract complexType.
///
/// struct saml1__StatementAbstractType operations:
/// - soap_default_saml1__StatementAbstractType(soap*, saml1__StatementAbstractType*) reset members to default
/// - int soap_read_saml1__StatementAbstractType(soap*, saml1__StatementAbstractType*) deserialize from a source
/// - int soap_write_saml1__StatementAbstractType(soap*, saml1__StatementAbstractType*) serialize to a sink
/// - saml1__StatementAbstractType* soap_dup_saml1__StatementAbstractType(soap*, saml1__StatementAbstractType* dst, saml1__StatementAbstractType *src) returns deep copy of saml1__StatementAbstractType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__StatementAbstractType(saml1__StatementAbstractType*) deep deletes saml1__StatementAbstractType data members, use only on dst after soap_dup_saml1__StatementAbstractType(NULL, saml1__StatementAbstractType *dst, saml1__StatementAbstractType *src) (use soapcpp2 -Ed)
struct saml1__StatementAbstractType
{
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":SubjectType is a complexType.
///
/// struct saml1__SubjectType operations:
/// - soap_default_saml1__SubjectType(soap*, saml1__SubjectType*) reset members to default
/// - int soap_read_saml1__SubjectType(soap*, saml1__SubjectType*) deserialize from a source
/// - int soap_write_saml1__SubjectType(soap*, saml1__SubjectType*) serialize to a sink
/// - saml1__SubjectType* soap_dup_saml1__SubjectType(soap*, saml1__SubjectType* dst, saml1__SubjectType *src) returns deep copy of saml1__SubjectType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__SubjectType(saml1__SubjectType*) deep deletes saml1__SubjectType data members, use only on dst after soap_dup_saml1__SubjectType(NULL, saml1__SubjectType *dst, saml1__SubjectType *src) (use soapcpp2 -Ed)
struct saml1__SubjectType
{
//  BEGIN CHOICE <xs:choice>
/// @note <xs:choice> with embedded <xs:sequence> or <xs:group> prevents the use of a union for <xs:choice>. Instead of being members of a union, the following members are declared optional. Only one member should be non-NULL by choice.
//  BEGIN SEQUENCE <xs:sequence>
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":NameIdentifier.
    struct saml1__NameIdentifierType*    saml1__NameIdentifier         ;
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":SubjectConfirmation.
    struct saml1__SubjectConfirmationType*  saml1__SubjectConfirmation    ;
//  END OF SEQUENCE
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":SubjectConfirmation.
//  struct saml1__SubjectConfirmationType*  saml1__SubjectConfirmation    ;
//  END OF CHOICE
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":SubjectConfirmationType is a complexType.
///
/// struct saml1__SubjectConfirmationType operations:
/// - soap_default_saml1__SubjectConfirmationType(soap*, saml1__SubjectConfirmationType*) reset members to default
/// - int soap_read_saml1__SubjectConfirmationType(soap*, saml1__SubjectConfirmationType*) deserialize from a source
/// - int soap_write_saml1__SubjectConfirmationType(soap*, saml1__SubjectConfirmationType*) serialize to a sink
/// - saml1__SubjectConfirmationType* soap_dup_saml1__SubjectConfirmationType(soap*, saml1__SubjectConfirmationType* dst, saml1__SubjectConfirmationType *src) returns deep copy of saml1__SubjectConfirmationType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__SubjectConfirmationType(saml1__SubjectConfirmationType*) deep deletes saml1__SubjectConfirmationType data members, use only on dst after soap_dup_saml1__SubjectConfirmationType(NULL, saml1__SubjectConfirmationType *dst, saml1__SubjectConfirmationType *src) (use soapcpp2 -Ed)
struct saml1__SubjectConfirmationType
{
/// Size of the dynamic array of char* * is 1..unbounded.
   $int                                  __sizeConfirmationMethod       1;
/// Array char* * of size 1..unbounded.
    char* *                              saml1__ConfirmationMethod      1;
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":SubjectConfirmationData.
    _XML                                 saml1__SubjectConfirmationData 0;	///< Optional element.
/// Imported element reference "http://www.w3.org/2000/09/xmldsig#":KeyInfo.
    _ds__KeyInfo*                        ds__KeyInfo                    0;	///< Optional element.
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":SubjectLocalityType is a complexType.
///
/// struct saml1__SubjectLocalityType operations:
/// - soap_default_saml1__SubjectLocalityType(soap*, saml1__SubjectLocalityType*) reset members to default
/// - int soap_read_saml1__SubjectLocalityType(soap*, saml1__SubjectLocalityType*) deserialize from a source
/// - int soap_write_saml1__SubjectLocalityType(soap*, saml1__SubjectLocalityType*) serialize to a sink
/// - saml1__SubjectLocalityType* soap_dup_saml1__SubjectLocalityType(soap*, saml1__SubjectLocalityType* dst, saml1__SubjectLocalityType *src) returns deep copy of saml1__SubjectLocalityType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__SubjectLocalityType(saml1__SubjectLocalityType*) deep deletes saml1__SubjectLocalityType data members, use only on dst after soap_dup_saml1__SubjectLocalityType(NULL, saml1__SubjectLocalityType *dst, saml1__SubjectLocalityType *src) (use soapcpp2 -Ed)
struct saml1__SubjectLocalityType
{
/// Attribute "IPAddress" of XSD type xs:string.
   @char*                                IPAddress                      0;	///< Optional attribute.
/// Attribute "DNSAddress" of XSD type xs:string.
   @char*                                DNSAddress                     0;	///< Optional attribute.
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":AuthorityBindingType is a complexType.
///
/// struct saml1__AuthorityBindingType operations:
/// - soap_default_saml1__AuthorityBindingType(soap*, saml1__AuthorityBindingType*) reset members to default
/// - int soap_read_saml1__AuthorityBindingType(soap*, saml1__AuthorityBindingType*) deserialize from a source
/// - int soap_write_saml1__AuthorityBindingType(soap*, saml1__AuthorityBindingType*) serialize to a sink
/// - saml1__AuthorityBindingType* soap_dup_saml1__AuthorityBindingType(soap*, saml1__AuthorityBindingType* dst, saml1__AuthorityBindingType *src) returns deep copy of saml1__AuthorityBindingType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__AuthorityBindingType(saml1__AuthorityBindingType*) deep deletes saml1__AuthorityBindingType data members, use only on dst after soap_dup_saml1__AuthorityBindingType(NULL, saml1__AuthorityBindingType *dst, saml1__AuthorityBindingType *src) (use soapcpp2 -Ed)
struct saml1__AuthorityBindingType
{
/// Attribute "AuthorityKind" of XSD type xs:QName.
   @_QName                               AuthorityKind                  1;	///< Required attribute.
/// Attribute "Location" of XSD type xs:anyURI.
   @char*                                Location                       1;	///< Required attribute.
/// Attribute "Binding" of XSD type xs:anyURI.
   @char*                                Binding                        1;	///< Required attribute.
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":EvidenceType is a complexType.
///
/// struct saml1__EvidenceType operations:
/// - soap_default_saml1__EvidenceType(soap*, saml1__EvidenceType*) reset members to default
/// - int soap_read_saml1__EvidenceType(soap*, saml1__EvidenceType*) deserialize from a source
/// - int soap_write_saml1__EvidenceType(soap*, saml1__EvidenceType*) serialize to a sink
/// - saml1__EvidenceType* soap_dup_saml1__EvidenceType(soap*, saml1__EvidenceType* dst, saml1__EvidenceType *src) returns deep copy of saml1__EvidenceType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__EvidenceType(saml1__EvidenceType*) deep deletes saml1__EvidenceType data members, use only on dst after soap_dup_saml1__EvidenceType(NULL, saml1__EvidenceType *dst, saml1__EvidenceType *src) (use soapcpp2 -Ed)
struct saml1__EvidenceType
{
//  BEGIN CHOICE <xs:choice maxOccurs="unbounded">
   $int                                  __size_EvidenceType            0;
    struct __saml1__union_EvidenceType
    {
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":AssertionIDReference.
    char*                                saml1__AssertionIDReference   ;
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":Assertion.
    struct saml1__AssertionType*         saml1__Assertion              ;
    }                                   *__union_EvidenceType          ;
//  END OF CHOICE
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":AttributeDesignatorType is a complexType.
///
/// struct saml1__AttributeDesignatorType operations:
/// - soap_default_saml1__AttributeDesignatorType(soap*, saml1__AttributeDesignatorType*) reset members to default
/// - int soap_read_saml1__AttributeDesignatorType(soap*, saml1__AttributeDesignatorType*) deserialize from a source
/// - int soap_write_saml1__AttributeDesignatorType(soap*, saml1__AttributeDesignatorType*) serialize to a sink
/// - saml1__AttributeDesignatorType* soap_dup_saml1__AttributeDesignatorType(soap*, saml1__AttributeDesignatorType* dst, saml1__AttributeDesignatorType *src) returns deep copy of saml1__AttributeDesignatorType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__AttributeDesignatorType(saml1__AttributeDesignatorType*) deep deletes saml1__AttributeDesignatorType data members, use only on dst after soap_dup_saml1__AttributeDesignatorType(NULL, saml1__AttributeDesignatorType *dst, saml1__AttributeDesignatorType *src) (use soapcpp2 -Ed)
struct saml1__AttributeDesignatorType
{
/// Attribute "AttributeName" of XSD type xs:string.
   @char*                                AttributeName                  1;	///< Required attribute.
/// Attribute "AttributeNamespace" of XSD type xs:anyURI.
   @char*                                AttributeNamespace             1;	///< Required attribute.
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":AudienceRestrictionConditionType is a complexType with complexContent extension of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":ConditionAbstractType.
///
/// struct saml1__AudienceRestrictionConditionType operations:
/// - soap_default_saml1__AudienceRestrictionConditionType(soap*, saml1__AudienceRestrictionConditionType*) reset members to default
/// - int soap_read_saml1__AudienceRestrictionConditionType(soap*, saml1__AudienceRestrictionConditionType*) deserialize from a source
/// - int soap_write_saml1__AudienceRestrictionConditionType(soap*, saml1__AudienceRestrictionConditionType*) serialize to a sink
/// - saml1__AudienceRestrictionConditionType* soap_dup_saml1__AudienceRestrictionConditionType(soap*, saml1__AudienceRestrictionConditionType* dst, saml1__AudienceRestrictionConditionType *src) returns deep copy of saml1__AudienceRestrictionConditionType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__AudienceRestrictionConditionType(saml1__AudienceRestrictionConditionType*) deep deletes saml1__AudienceRestrictionConditionType data members, use only on dst after soap_dup_saml1__AudienceRestrictionConditionType(NULL, saml1__AudienceRestrictionConditionType *dst, saml1__AudienceRestrictionConditionType *src) (use soapcpp2 -Ed)
struct saml1__AudienceRestrictionConditionType
{
/// INHERITED FROM saml1__ConditionAbstractType:
//  END OF INHERITED FROM saml1__ConditionAbstractType
/// Size of the dynamic array of char* * is 1..unbounded.
   $int                                  __sizeAudience                 1;
/// Array char* * of size 1..unbounded.
    char* *                              saml1__Audience                1;
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":DoNotCacheConditionType is a complexType with complexContent extension of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":ConditionAbstractType.
///
/// struct saml1__DoNotCacheConditionType operations:
/// - soap_default_saml1__DoNotCacheConditionType(soap*, saml1__DoNotCacheConditionType*) reset members to default
/// - int soap_read_saml1__DoNotCacheConditionType(soap*, saml1__DoNotCacheConditionType*) deserialize from a source
/// - int soap_write_saml1__DoNotCacheConditionType(soap*, saml1__DoNotCacheConditionType*) serialize to a sink
/// - saml1__DoNotCacheConditionType* soap_dup_saml1__DoNotCacheConditionType(soap*, saml1__DoNotCacheConditionType* dst, saml1__DoNotCacheConditionType *src) returns deep copy of saml1__DoNotCacheConditionType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__DoNotCacheConditionType(saml1__DoNotCacheConditionType*) deep deletes saml1__DoNotCacheConditionType data members, use only on dst after soap_dup_saml1__DoNotCacheConditionType(NULL, saml1__DoNotCacheConditionType *dst, saml1__DoNotCacheConditionType *src) (use soapcpp2 -Ed)
struct saml1__DoNotCacheConditionType
{
/// INHERITED FROM saml1__ConditionAbstractType:
//  END OF INHERITED FROM saml1__ConditionAbstractType
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":SubjectStatementAbstractType is an abstract complexType with complexContent extension of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":StatementAbstractType.
///
/// struct saml1__SubjectStatementAbstractType operations:
/// - soap_default_saml1__SubjectStatementAbstractType(soap*, saml1__SubjectStatementAbstractType*) reset members to default
/// - int soap_read_saml1__SubjectStatementAbstractType(soap*, saml1__SubjectStatementAbstractType*) deserialize from a source
/// - int soap_write_saml1__SubjectStatementAbstractType(soap*, saml1__SubjectStatementAbstractType*) serialize to a sink
/// - saml1__SubjectStatementAbstractType* soap_dup_saml1__SubjectStatementAbstractType(soap*, saml1__SubjectStatementAbstractType* dst, saml1__SubjectStatementAbstractType *src) returns deep copy of saml1__SubjectStatementAbstractType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__SubjectStatementAbstractType(saml1__SubjectStatementAbstractType*) deep deletes saml1__SubjectStatementAbstractType data members, use only on dst after soap_dup_saml1__SubjectStatementAbstractType(NULL, saml1__SubjectStatementAbstractType *dst, saml1__SubjectStatementAbstractType *src) (use soapcpp2 -Ed)
struct saml1__SubjectStatementAbstractType
{
/// INHERITED FROM saml1__StatementAbstractType:
//  END OF INHERITED FROM saml1__StatementAbstractType
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":Subject.
    struct saml1__SubjectType*           saml1__Subject                 1;	///< Required element.
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":NameIdentifierType is a complexType with simpleContent.
///
/// struct saml1__NameIdentifierType operations:
/// - soap_default_saml1__NameIdentifierType(soap*, saml1__NameIdentifierType*) reset members to default
/// - int soap_read_saml1__NameIdentifierType(soap*, saml1__NameIdentifierType*) deserialize from a source
/// - int soap_write_saml1__NameIdentifierType(soap*, saml1__NameIdentifierType*) serialize to a sink
/// - saml1__NameIdentifierType* soap_dup_saml1__NameIdentifierType(soap*, saml1__NameIdentifierType* dst, saml1__NameIdentifierType *src) returns deep copy of saml1__NameIdentifierType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__NameIdentifierType(saml1__NameIdentifierType*) deep deletes saml1__NameIdentifierType data members, use only on dst after soap_dup_saml1__NameIdentifierType(NULL, saml1__NameIdentifierType *dst, saml1__NameIdentifierType *src) (use soapcpp2 -Ed)
struct saml1__NameIdentifierType
{
/// __item wraps "xs:string" simpleContent.
    char*                                __item                        ;
/// Attribute "NameQualifier" of XSD type xs:string.
   @char*                                NameQualifier                  0;	///< Optional attribute.
/// Attribute "Format" of XSD type xs:anyURI.
   @char*                                Format                         0;	///< Optional attribute.
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":ActionType is a complexType with simpleContent.
///
/// struct saml1__ActionType operations:
/// - soap_default_saml1__ActionType(soap*, saml1__ActionType*) reset members to default
/// - int soap_read_saml1__ActionType(soap*, saml1__ActionType*) deserialize from a source
/// - int soap_write_saml1__ActionType(soap*, saml1__ActionType*) serialize to a sink
/// - saml1__ActionType* soap_dup_saml1__ActionType(soap*, saml1__ActionType* dst, saml1__ActionType *src) returns deep copy of saml1__ActionType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__ActionType(saml1__ActionType*) deep deletes saml1__ActionType data members, use only on dst after soap_dup_saml1__ActionType(NULL, saml1__ActionType *dst, saml1__ActionType *src) (use soapcpp2 -Ed)
struct saml1__ActionType
{
/// __item wraps "xs:string" simpleContent.
    char*                                __item                        ;
/// Attribute "Namespace" of XSD type xs:anyURI.
   @char*                                Namespace                      0;	///< Optional attribute.
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":AttributeType is a complexType with complexContent extension of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":AttributeDesignatorType.
///
/// struct saml1__AttributeType operations:
/// - soap_default_saml1__AttributeType(soap*, saml1__AttributeType*) reset members to default
/// - int soap_read_saml1__AttributeType(soap*, saml1__AttributeType*) deserialize from a source
/// - int soap_write_saml1__AttributeType(soap*, saml1__AttributeType*) serialize to a sink
/// - saml1__AttributeType* soap_dup_saml1__AttributeType(soap*, saml1__AttributeType* dst, saml1__AttributeType *src) returns deep copy of saml1__AttributeType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__AttributeType(saml1__AttributeType*) deep deletes saml1__AttributeType data members, use only on dst after soap_dup_saml1__AttributeType(NULL, saml1__AttributeType *dst, saml1__AttributeType *src) (use soapcpp2 -Ed)
struct saml1__AttributeType
{
/// INHERITED FROM saml1__AttributeDesignatorType:
/// Attribute "AttributeName" of XSD type xs:string.
   @char*                                AttributeName                  1;	///< Required attribute.
/// Attribute "AttributeNamespace" of XSD type xs:anyURI.
   @char*                                AttributeNamespace             1;	///< Required attribute.
//  END OF INHERITED FROM saml1__AttributeDesignatorType
/// Size of the dynamic array of _XML* is 1..unbounded.
   $int                                  __sizeAttributeValue           1;
/// Array _XML* of size 1..unbounded.
    _XML*                                saml1__AttributeValue          1;
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":AuthenticationStatementType is a complexType with complexContent extension of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":SubjectStatementAbstractType.
///
/// struct saml1__AuthenticationStatementType operations:
/// - soap_default_saml1__AuthenticationStatementType(soap*, saml1__AuthenticationStatementType*) reset members to default
/// - int soap_read_saml1__AuthenticationStatementType(soap*, saml1__AuthenticationStatementType*) deserialize from a source
/// - int soap_write_saml1__AuthenticationStatementType(soap*, saml1__AuthenticationStatementType*) serialize to a sink
/// - saml1__AuthenticationStatementType* soap_dup_saml1__AuthenticationStatementType(soap*, saml1__AuthenticationStatementType* dst, saml1__AuthenticationStatementType *src) returns deep copy of saml1__AuthenticationStatementType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__AuthenticationStatementType(saml1__AuthenticationStatementType*) deep deletes saml1__AuthenticationStatementType data members, use only on dst after soap_dup_saml1__AuthenticationStatementType(NULL, saml1__AuthenticationStatementType *dst, saml1__AuthenticationStatementType *src) (use soapcpp2 -Ed)
struct saml1__AuthenticationStatementType
{
/// INHERITED FROM saml1__StatementAbstractType:
//  END OF INHERITED FROM saml1__StatementAbstractType
/// INHERITED FROM saml1__SubjectStatementAbstractType:
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":Subject.
    struct saml1__SubjectType*           saml1__Subject                 1;	///< Required element.
//  END OF INHERITED FROM saml1__SubjectStatementAbstractType
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":SubjectLocality.
    struct saml1__SubjectLocalityType*   saml1__SubjectLocality         0;	///< Optional element.
/// Size of the dynamic array of struct saml1__AuthorityBindingType* is 0..unbounded.
   $int                                  __sizeAuthorityBinding         0;
/// Array struct saml1__AuthorityBindingType* of size 0..unbounded.
    struct saml1__AuthorityBindingType*  saml1__AuthorityBinding        0;
/// Attribute "AuthenticationMethod" of XSD type xs:anyURI.
   @char*                                AuthenticationMethod           1;	///< Required attribute.
/// Attribute "AuthenticationInstant" of XSD type xs:dateTime.
   @time_t                               AuthenticationInstant          1;	///< Required attribute.
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":AuthorizationDecisionStatementType is a complexType with complexContent extension of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":SubjectStatementAbstractType.
///
/// struct saml1__AuthorizationDecisionStatementType operations:
/// - soap_default_saml1__AuthorizationDecisionStatementType(soap*, saml1__AuthorizationDecisionStatementType*) reset members to default
/// - int soap_read_saml1__AuthorizationDecisionStatementType(soap*, saml1__AuthorizationDecisionStatementType*) deserialize from a source
/// - int soap_write_saml1__AuthorizationDecisionStatementType(soap*, saml1__AuthorizationDecisionStatementType*) serialize to a sink
/// - saml1__AuthorizationDecisionStatementType* soap_dup_saml1__AuthorizationDecisionStatementType(soap*, saml1__AuthorizationDecisionStatementType* dst, saml1__AuthorizationDecisionStatementType *src) returns deep copy of saml1__AuthorizationDecisionStatementType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__AuthorizationDecisionStatementType(saml1__AuthorizationDecisionStatementType*) deep deletes saml1__AuthorizationDecisionStatementType data members, use only on dst after soap_dup_saml1__AuthorizationDecisionStatementType(NULL, saml1__AuthorizationDecisionStatementType *dst, saml1__AuthorizationDecisionStatementType *src) (use soapcpp2 -Ed)
struct saml1__AuthorizationDecisionStatementType
{
/// INHERITED FROM saml1__StatementAbstractType:
//  END OF INHERITED FROM saml1__StatementAbstractType
/// INHERITED FROM saml1__SubjectStatementAbstractType:
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":Subject.
    struct saml1__SubjectType*           saml1__Subject                 1;	///< Required element.
//  END OF INHERITED FROM saml1__SubjectStatementAbstractType
/// Size of the dynamic array of struct saml1__ActionType* is 1..unbounded.
   $int                                  __sizeAction                   1;
/// Array struct saml1__ActionType* of size 1..unbounded.
    struct saml1__ActionType*            saml1__Action                  1;
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":Evidence.
    struct saml1__EvidenceType*          saml1__Evidence                0;	///< Optional element.
/// Attribute "Resource" of XSD type xs:anyURI.
   @char*                                Resource                       1;	///< Required attribute.
/// Attribute "Decision" of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":DecisionType.
   @enum saml1__DecisionType             Decision                       1;	///< Required attribute.
};

/// @brief "urn:oasis:names:tc:SAML:1.0:assertion":AttributeStatementType is a complexType with complexContent extension of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":SubjectStatementAbstractType.
///
/// struct saml1__AttributeStatementType operations:
/// - soap_default_saml1__AttributeStatementType(soap*, saml1__AttributeStatementType*) reset members to default
/// - int soap_read_saml1__AttributeStatementType(soap*, saml1__AttributeStatementType*) deserialize from a source
/// - int soap_write_saml1__AttributeStatementType(soap*, saml1__AttributeStatementType*) serialize to a sink
/// - saml1__AttributeStatementType* soap_dup_saml1__AttributeStatementType(soap*, saml1__AttributeStatementType* dst, saml1__AttributeStatementType *src) returns deep copy of saml1__AttributeStatementType src into dst, copies the (cyclic) graph structure when a context is provided, or (cycle-pruned) tree structure with soap_set_mode(soap, SOAP_XML_TREE) (use soapcpp2 -Ec)
/// - soap_del_saml1__AttributeStatementType(saml1__AttributeStatementType*) deep deletes saml1__AttributeStatementType data members, use only on dst after soap_dup_saml1__AttributeStatementType(NULL, saml1__AttributeStatementType *dst, saml1__AttributeStatementType *src) (use soapcpp2 -Ed)
struct saml1__AttributeStatementType
{
/// INHERITED FROM saml1__StatementAbstractType:
//  END OF INHERITED FROM saml1__StatementAbstractType
/// INHERITED FROM saml1__SubjectStatementAbstractType:
/// Element reference "urn:oasis:names:tc:SAML:1.0:assertion:""urn:oasis:names:tc:SAML:1.0:assertion":Subject.
    struct saml1__SubjectType*           saml1__Subject                 1;	///< Required element.
//  END OF INHERITED FROM saml1__SubjectStatementAbstractType
/// Size of the dynamic array of struct saml1__AttributeType* is 1..unbounded.
   $int                                  __sizeAttribute                1;
/// Array struct saml1__AttributeType* of size 1..unbounded.
    struct saml1__AttributeType*         saml1__Attribute               1;
};


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Elements                                              *
 *   urn:oasis:names:tc:SAML:1.0:assertion                                    *
 *                                                                            *
\******************************************************************************/

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":AssertionIDReference of XSD type xs:NCName.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":Assertion of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":AssertionType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":Conditions of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":ConditionsType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":Condition of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":ConditionAbstractType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":AudienceRestrictionCondition of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":AudienceRestrictionConditionType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":Audience of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":DoNotCacheCondition of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":DoNotCacheConditionType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":Advice of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":AdviceType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":Statement of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":StatementAbstractType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":SubjectStatement of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":SubjectStatementAbstractType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":Subject of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":SubjectType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":NameIdentifier of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":NameIdentifierType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":SubjectConfirmation of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":SubjectConfirmationType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":SubjectConfirmationData of XSD type xs:anyType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":ConfirmationMethod of XSD type xs:anyURI.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":AuthenticationStatement of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":AuthenticationStatementType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":SubjectLocality of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":SubjectLocalityType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":AuthorityBinding of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":AuthorityBindingType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":AuthorizationDecisionStatement of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":AuthorizationDecisionStatementType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":Action of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":ActionType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":Evidence of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":EvidenceType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":AttributeStatement of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":AttributeStatementType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":AttributeDesignator of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":AttributeDesignatorType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":Attribute of XSD type "urn:oasis:names:tc:SAML:1.0:assertion":AttributeType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.

/// @brief Top-level root element "urn:oasis:names:tc:SAML:1.0:assertion":AttributeValue of XSD type xs:anyType.
/// @note Use wsdl2h option -g to auto-generate a top-level root element declaration and processing code.


/******************************************************************************\
 *                                                                            *
 * Additional Top-Level Attributes                                            *
 *   urn:oasis:names:tc:SAML:1.0:assertion                                    *
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


@section saml1 Top-level root elements of schema "urn:oasis:names:tc:SAML:1.0:assertion"

  - <saml1:AssertionIDReference> (use wsdl2h option -g to auto-generate type _saml1__AssertionIDReference)

  - <saml1:Assertion> (use wsdl2h option -g to auto-generate type _saml1__Assertion)

  - <saml1:Conditions> (use wsdl2h option -g to auto-generate type _saml1__Conditions)

  - <saml1:Condition> (use wsdl2h option -g to auto-generate type _saml1__Condition)

  - <saml1:AudienceRestrictionCondition> (use wsdl2h option -g to auto-generate type _saml1__AudienceRestrictionCondition)

  - <saml1:Audience> (use wsdl2h option -g to auto-generate type _saml1__Audience)

  - <saml1:DoNotCacheCondition> (use wsdl2h option -g to auto-generate type _saml1__DoNotCacheCondition)

  - <saml1:Advice> (use wsdl2h option -g to auto-generate type _saml1__Advice)

  - <saml1:Statement> (use wsdl2h option -g to auto-generate type _saml1__Statement)

  - <saml1:SubjectStatement> (use wsdl2h option -g to auto-generate type _saml1__SubjectStatement)

  - <saml1:Subject> (use wsdl2h option -g to auto-generate type _saml1__Subject)

  - <saml1:NameIdentifier> (use wsdl2h option -g to auto-generate type _saml1__NameIdentifier)

  - <saml1:SubjectConfirmation> (use wsdl2h option -g to auto-generate type _saml1__SubjectConfirmation)

  - <saml1:SubjectConfirmationData> (use wsdl2h option -g to auto-generate type _saml1__SubjectConfirmationData)

  - <saml1:ConfirmationMethod> (use wsdl2h option -g to auto-generate type _saml1__ConfirmationMethod)

  - <saml1:AuthenticationStatement> (use wsdl2h option -g to auto-generate type _saml1__AuthenticationStatement)

  - <saml1:SubjectLocality> (use wsdl2h option -g to auto-generate type _saml1__SubjectLocality)

  - <saml1:AuthorityBinding> (use wsdl2h option -g to auto-generate type _saml1__AuthorityBinding)

  - <saml1:AuthorizationDecisionStatement> (use wsdl2h option -g to auto-generate type _saml1__AuthorizationDecisionStatement)

  - <saml1:Action> (use wsdl2h option -g to auto-generate type _saml1__Action)

  - <saml1:Evidence> (use wsdl2h option -g to auto-generate type _saml1__Evidence)

  - <saml1:AttributeStatement> (use wsdl2h option -g to auto-generate type _saml1__AttributeStatement)

  - <saml1:AttributeDesignator> (use wsdl2h option -g to auto-generate type _saml1__AttributeDesignator)

  - <saml1:Attribute> (use wsdl2h option -g to auto-generate type _saml1__Attribute)

  - <saml1:AttributeValue> (use wsdl2h option -g to auto-generate type _saml1__AttributeValue)

*/

/* End of saml1.h */
