#ifndef _CkXml_H
#define _CkXml_H
#include "Chilkat_C.h"

HCkXml CkXml_Create(void);
void CkXml_Dispose(HCkXml handle);
BOOL CkXml_getCdata(HCkXml handle);
void CkXml_putCdata(HCkXml handle, BOOL newVal);
void CkXml_getContent(HCkXml handle, HCkString retval);
void CkXml_putContent(HCkXml handle, const char *newVal);
int CkXml_getContentInt(HCkXml handle);
void CkXml_putContentInt(HCkXml handle, int newVal);
void CkXml_getEncoding(HCkXml handle, HCkString retval);
void CkXml_putEncoding(HCkXml handle, const char *newVal);
void CkXml_getLastErrorHtml(HCkXml handle, HCkString retval);
void CkXml_getLastErrorText(HCkXml handle, HCkString retval);
void CkXml_getLastErrorXml(HCkXml handle, HCkString retval);
long CkXml_getNumAttributes(HCkXml handle);
long CkXml_getNumChildren(HCkXml handle);
BOOL CkXml_getSortCaseInsensitive(HCkXml handle);
void CkXml_putSortCaseInsensitive(HCkXml handle, BOOL newVal);
BOOL CkXml_getStandalone(HCkXml handle);
void CkXml_putStandalone(HCkXml handle, BOOL newVal);
void CkXml_getTag(HCkXml handle, HCkString retval);
void CkXml_putTag(HCkXml handle, const char *newVal);
long CkXml_getTreeId(HCkXml handle);
BOOL CkXml_getUtf8(HCkXml handle);
void CkXml_putUtf8(HCkXml handle, BOOL newVal);
BOOL CkXml_getVersion(HCkXml handle);
void CkXml_AccumulateTagContent(HCkXml handle, const char *tag, const char *skipTags, HCkString str);
BOOL CkXml_AddAttribute(HCkXml handle, const char *name, const char *value);
BOOL CkXml_AddAttributeInt(HCkXml handle, const char *name, int value);
BOOL CkXml_AddChildTree(HCkXml handle, HCkXml tree);
void CkXml_AddOrUpdateAttribute(HCkXml handle, const char *name, const char *value);
void CkXml_AddOrUpdateAttributeI(HCkXml handle, const char *name, long value);
void CkXml_AddStyleSheet(HCkXml handle, const char *styleSheet);
void CkXml_AddToAttribute(HCkXml handle, const char *name, long amount);
void CkXml_AddToChildContent(HCkXml handle, const char *tag, long amount);
void CkXml_AddToContent(HCkXml handle, long amount);
BOOL CkXml_AppendToContent(HCkXml handle, const char *str);
BOOL CkXml_BEncodeContent(HCkXml handle, const char *charset, HCkByteData db);
BOOL CkXml_ChildContentMatches(HCkXml handle, const char *tag, const char *pattern, BOOL caseSensitive);
BOOL CkXml_Clear(HCkXml handle);
BOOL CkXml_ContentMatches(HCkXml handle, const char *pattern, BOOL caseSensitive);
BOOL CkXml_DecodeContent(HCkXml handle, HCkByteData db);
BOOL CkXml_DecodeEntities(HCkXml handle, const char *str, HCkString outStr);
BOOL CkXml_DecryptContent(HCkXml handle, const char *password);
BOOL CkXml_EncryptContent(HCkXml handle, const char *password);
HCkXml CkXml_ExtractChildByIndex(HCkXml handle, long index);
HCkXml CkXml_ExtractChildByName(HCkXml handle, const char *tag, const char *attrName, const char *attrValue);
HCkXml CkXml_FindChild(HCkXml handle, const char *tag);
BOOL CkXml_FindChild2(HCkXml handle, const char *tag);
HCkXml CkXml_FindNextRecord(HCkXml handle, const char *tag, const char *contentPattern);
HCkXml CkXml_FindOrAddNewChild(HCkXml handle, const char *tag);
HCkXml CkXml_FirstChild(HCkXml handle);
BOOL CkXml_FirstChild2(HCkXml handle);
BOOL CkXml_GetAttrValue(HCkXml handle, const char *name, HCkString str);
int CkXml_GetAttrValueInt(HCkXml handle, const char *name);
BOOL CkXml_GetAttributeName(HCkXml handle, long index, HCkString str);
BOOL CkXml_GetAttributeValue(HCkXml handle, long index, HCkString str);
int CkXml_GetAttributeValueInt(HCkXml handle, int index);
BOOL CkXml_GetBinaryContent(HCkXml handle, HCkByteData data, BOOL unzipFlag, BOOL decryptFlag, const char *password);
HCkXml CkXml_GetChild(HCkXml handle, long index);
BOOL CkXml_GetChild2(HCkXml handle, long index);
BOOL CkXml_GetChildBoolValue(HCkXml handle, const char *tag);
BOOL CkXml_GetChildContent(HCkXml handle, const char *tag, HCkString str);
BOOL CkXml_GetChildContentByIndex(HCkXml handle, long index, HCkString str);
HCkXml CkXml_GetChildExact(HCkXml handle, const char *tag, const char *content);
int CkXml_GetChildIntValue(HCkXml handle, const char *tag);
BOOL CkXml_GetChildTag(HCkXml handle, long index, HCkString str);
BOOL CkXml_GetChildTagByIndex(HCkXml handle, int index, HCkString outStr);
HCkXml CkXml_GetChildWithContent(HCkXml handle, const char *content);
HCkXml CkXml_GetChildWithTag(HCkXml handle, const char *tag);
HCkXml CkXml_GetNthChildWithTag(HCkXml handle, const char *tag, long n);
BOOL CkXml_GetNthChildWithTag2(HCkXml handle, const char *tag, long n);
HCkXml CkXml_GetParent(HCkXml handle);
BOOL CkXml_GetParent2(HCkXml handle);
HCkXml CkXml_GetRoot(HCkXml handle);
void CkXml_GetRoot2(HCkXml handle);
BOOL CkXml_GetXml(HCkXml handle, HCkString str);
BOOL CkXml_HasAttrWithValue(HCkXml handle, const char *name, const char *value);
BOOL CkXml_HasAttribute(HCkXml handle, const char *name);
BOOL CkXml_HasChildWithContent(HCkXml handle, const char *content);
BOOL CkXml_HasChildWithTag(HCkXml handle, const char *tag);
BOOL CkXml_HasChildWithTagAndContent(HCkXml handle, const char *tag, const char *content);
HCkXml CkXml_HttpGet(HCkXml handle, const char *url);
HCkXml CkXml_HttpPost(HCkXml handle, const char *url);
BOOL CkXml_InsertChildTreeAfter(HCkXml handle, int index, HCkXml tree);
BOOL CkXml_InsertChildTreeBefore(HCkXml handle, int index, HCkXml tree);
HCkXml CkXml_LastChild(HCkXml handle);
BOOL CkXml_LastChild2(HCkXml handle);
BOOL CkXml_LoadXml(HCkXml handle, const char *xmlData);
BOOL CkXml_LoadXml2(HCkXml handle, const char *xmlData, BOOL autoTrim);
BOOL CkXml_LoadXmlFile(HCkXml handle, const char *fileName);
BOOL CkXml_LoadXmlFile2(HCkXml handle, const char *fileName, BOOL autoTrim);
HCkXml CkXml_NewChild(HCkXml handle, const char *tag, const char *content);
void CkXml_NewChild2(HCkXml handle, const char *tag, const char *content);
HCkXml CkXml_NewChildAfter(HCkXml handle, int index, const char *tag, const char *content);
HCkXml CkXml_NewChildBefore(HCkXml handle, int index, const char *tag, const char *content);
void CkXml_NewChildInt2(HCkXml handle, const char *tag, int value);
HCkXml CkXml_NextSibling(HCkXml handle);
BOOL CkXml_NextSibling2(HCkXml handle);
long CkXml_NumChildrenHavingTag(HCkXml handle, const char *tag);
HCkXml CkXml_PreviousSibling(HCkXml handle);
BOOL CkXml_PreviousSibling2(HCkXml handle);
BOOL CkXml_QEncodeContent(HCkXml handle, const char *charset, HCkByteData db);
BOOL CkXml_RemoveAllAttributes(HCkXml handle);
void CkXml_RemoveAllChildren(HCkXml handle);
BOOL CkXml_RemoveAttribute(HCkXml handle, const char *name);
void CkXml_RemoveChild(HCkXml handle, const char *tag);
void CkXml_RemoveChildByIndex(HCkXml handle, long index);
void CkXml_RemoveChildWithContent(HCkXml handle, const char *content);
void CkXml_RemoveFromTree(HCkXml handle);
BOOL CkXml_SaveBinaryContent(HCkXml handle, const char *filename, BOOL unzipFlag, BOOL decryptFlag, const char *password);
BOOL CkXml_SaveLastError(HCkXml handle, const char *filename);
BOOL CkXml_SaveXml(HCkXml handle, const char *fileName);
HCkXml CkXml_SearchAllForContent(HCkXml handle, HCkXml after, const char *contentPattern);
BOOL CkXml_SearchAllForContent2(HCkXml handle, HCkXml after, const char *contentPattern);
HCkXml CkXml_SearchForAttribute(HCkXml handle, HCkXml after, const char *tag, const char *attr, const char *valuePattern);
BOOL CkXml_SearchForAttribute2(HCkXml handle, HCkXml after, const char *tag, const char *attr, const char *valuePattern);
HCkXml CkXml_SearchForContent(HCkXml handle, HCkXml after, const char *tag, const char *contentPattern);
BOOL CkXml_SearchForContent2(HCkXml handle, HCkXml after, const char *tag, const char *contentPattern);
HCkXml CkXml_SearchForTag(HCkXml handle, HCkXml after, const char *tag);
BOOL CkXml_SearchForTag2(HCkXml handle, HCkXml after, const char *tag);
BOOL CkXml_SetBinaryContent(HCkXml handle, const unsigned char *data, unsigned long dataLen, BOOL zipFlag, BOOL encryptFlag, const char *password);
BOOL CkXml_SetBinaryContent2(HCkXml handle, HCkByteData data, BOOL zipFlag, BOOL encryptFlag, const char *password);
BOOL CkXml_SetBinaryContentFromFile(HCkXml handle, const char *filename, BOOL zipFlag, BOOL encryptFlag, const char *password);
void CkXml_SortByAttribute(HCkXml handle, const char *attrName, long ascending);
void CkXml_SortByAttributeInt(HCkXml handle, const char *attrName, BOOL ascending);
void CkXml_SortByContent(HCkXml handle, long ascending);
void CkXml_SortByTag(HCkXml handle, long ascending);
void CkXml_SortRecordsByAttribute(HCkXml handle, const char *sortTag, const char *attrName, long ascending);
void CkXml_SortRecordsByContent(HCkXml handle, const char *sortTag, long ascending);
BOOL CkXml_SwapNode(HCkXml handle, HCkXml node);
BOOL CkXml_SwapTree(HCkXml handle, HCkXml tree);
BOOL CkXml_TagEquals(HCkXml handle, const char *tag);
BOOL CkXml_UnzipContent(HCkXml handle);
BOOL CkXml_UnzipTree(HCkXml handle);
BOOL CkXml_UpdateAttribute(HCkXml handle, const char *attrName, const char *attrValue);
BOOL CkXml_UpdateAttributeInt(HCkXml handle, const char *attrName, int value);
void CkXml_UpdateChildContent(HCkXml handle, const char *tag, const char *value);
void CkXml_UpdateChildContentInt(HCkXml handle, const char *tag, int value);
BOOL CkXml_ZipContent(HCkXml handle);
BOOL CkXml_ZipTree(HCkXml handle);
const char *CkXml_accumulateTagContent(HCkXml handle, const char *tag, const char *skipTags);
const char *CkXml_attr(HCkXml handle, const char *name);
const char *CkXml_attrName(HCkXml handle, long index);
const char *CkXml_attrValue(HCkXml handle, long index);
const char *CkXml_childContent(HCkXml handle, const char *tag);
const char *CkXml_content(HCkXml handle);
const char *CkXml_decodeEntities(HCkXml handle, const char *str);
const char *CkXml_encoding(HCkXml handle);
const char *CkXml_getAttrValue(HCkXml handle, const char *name);
const char *CkXml_getAttributeName(HCkXml handle, long index);
const char *CkXml_getAttributeValue(HCkXml handle, long index);
const char *CkXml_getChildContent(HCkXml handle, const char *tag);
const char *CkXml_getChildContentByIndex(HCkXml handle, long index);
const char *CkXml_getChildTag(HCkXml handle, long index);
const char *CkXml_getChildTagByIndex(HCkXml handle, int index);
const char *CkXml_getXml(HCkXml handle);
const char *CkXml_lastErrorHtml(HCkXml handle);
const char *CkXml_lastErrorText(HCkXml handle);
const char *CkXml_lastErrorXml(HCkXml handle);
const char *CkXml_tag(HCkXml handle);
const char *CkXml_version(HCkXml handle);
const char *CkXml_xml(HCkXml handle);
#endif
