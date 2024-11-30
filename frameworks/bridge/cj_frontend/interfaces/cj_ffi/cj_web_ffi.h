/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_ACE_FRAMEWORK_CJ_WEB_H
#define OHOS_ACE_FRAMEWORK_CJ_WEB_H
#include <cstdint>
#include <map>
#include <string>

#include "webview_controller_impl.h"

#include "bridge/cj_frontend/cppview/view_abstract.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_collection_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_container_base_ffi.h"
#include "core/components/web/web_component.h"

struct FfiWebEvent;
using VectorScriptItemHandle = void*;
using VectorExpandedMenuItemOptionsHandle = void*;
using VectorTextMenuItemHandle = void*;
using VectorHeaderHandle = void*;

extern "C" {
struct CPermissionRequestResult {
    CArrString permissions;
    CArrI32 authResults;
};

struct RetDataCPermissionRequestResult {
    int32_t code;
    CPermissionRequestResult data;
};

struct MapToCFFIArray {
    size_t size;
    const char** key;
    const char** value;
};

struct FfiWebResourceRequest {
    const char* url;
    bool isMainFrame;
    bool isRedirect;
    bool hasGesture;
    const char* method;
    MapToCFFIArray* mapToCFFIArray;
};

struct CPermissionRequest {
    void (*deny)(void* ptr);
    ExternalString (*getOrigin)(void* ptr);
    VectorStringHandle (*getAccessibleResource)(void* ptr);
    void (*grant)(VectorStringHandle resources, void* ptr);
    void* permissionPtr;
    void (*free)(void* ptr);
};

struct COnPermissionRequestEvent {
    CPermissionRequest request;
};

struct FfiScriptItem {
    const char* script;
    VectorStringHandle scriptRules;
};

struct FfiExpandedMenuItemOptions {
    const char* content;
    const char* startIcon;
    bool hasStartIcon;
    void (*action)(const char* value);
};

struct FfiAdsBlockedDetails {
    const char* url;
    VectorStringHandle adsBlocked;
};

struct FfiOnDownloadStartEvent {
    const char* url;
    const char* userAgent;
    const char* contentDisposition;
    const char* mimeType;
    int64_t contentLength;
};

struct FfiHeader {
    ExternalString key;
    ExternalString value;
};

typedef void (*RequestResultCallback)(void*, CArrString, void*);

CJ_EXPORT void FfiOHOSAceFrameworkWebHandleCancel(void* result);
CJ_EXPORT void FfiOHOSAceFrameworkWebHandleConfirm(void* result);
CJ_EXPORT void FfiOHOSAceFrameworkWebHandlePromptConfirm(void* result, const char* message);
CJ_EXPORT void FfiOHOSAceFrameworkWebReleaseResult(void* result);

CJ_EXPORT void FfiOHOSAceFrameworkWebCreate(const char* src, int64_t controllerId, int32_t type, bool mode);
CJ_EXPORT void FfiOHOSAceFrameworkWebFileAccessEnabled(bool isFileAccessEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkWebDomStorageAccessEnabled(bool isDomStorageAccessEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkWebImageAccessEnabled(bool isImageAccessEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkWebOnlineImageAccessEnabled(bool isImageAccessEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkWebMixedMode(int32_t mixedModeNum);
CJ_EXPORT void FfiOHOSAceFrameworkWebZoomAccessEnabled(bool isZoomAccessEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkWebGeolocationAccessEnabled(bool isGeolocationAccessEnabled);
CJ_EXPORT void FfiOHOSAceFrameworkWebVerticalScrollBarAccessEnabled(bool isVerticalScrollBarAccess);
CJ_EXPORT void FfiOHOSAceFrameworkNestedScroll(int32_t nestedScrollNum, int32_t scrollBackwardNum);
CJ_EXPORT void FfiOHOSAceFrameworkWebUserAgent(const std::string& userAgent);
CJ_EXPORT void FfiOHOSAceFrameworkWebBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkWebDarkMode(int32_t darkMode);
CJ_EXPORT void FfiOHOSAceFrameworkWebForceDarkAccess(bool access);

CJ_EXPORT void FfiOHOSAceFrameworkWebOnAlert(bool (*callback)(FfiWebEvent event));
CJ_EXPORT void FfiOHOSAceFrameworkWebOnPageStart(void (*callback)(const char* url));
CJ_EXPORT void FfiOHOSAceFrameworkWebOnPageFinish(void (*callback)(const char* url));
CJ_EXPORT void FfiOHOSAceFrameworkWebOnLoadIntercept(bool (*callback)(void* event));
CJ_EXPORT void FfiOHOSAceFrameworkWebJavaScriptProxy(
    VectorInt64Handle funcList, const char* name, VectorStringHandle methodList, int64_t controllerId);
CJ_EXPORT void FfiOHOSAceFrameworkWebSetCallback(RequestResultCallback cb);
CJ_EXPORT void FfiWebEnableNativemediaPlayer(bool enable, bool shouldOverlay);
CJ_EXPORT void FfiWebOnControllerAttached(void (*callback)());
CJ_EXPORT void FfiWebOnPermissionRequest(void (*callback)(COnPermissionRequestEvent));
CJ_EXPORT void FfiWebJavaScriptAccess(bool javaScriptAccess);
CJ_EXPORT void FfiWebOverScrollMode(int32_t overScrollMode);
CJ_EXPORT void FfiWebOverviewModeAccess(bool overviewModeAccess);
CJ_EXPORT void FfiWebDatabaseAccess(bool databaseAccess);
CJ_EXPORT void FfiWebMediaPlayGestureAccess(bool access);
CJ_EXPORT void FfiWebMultiWindowAccess(bool multiWindow);
CJ_EXPORT void FfiWebHorizontalScrollBarAccess(bool horizontalScrollBar);
CJ_EXPORT void FfiWebCacheMode(int32_t cacheMode);
CJ_EXPORT void FfiWebCopyOptions(int32_t value);
CJ_EXPORT void FfiWebTextZoomRatio(int32_t textZoomRatio);
CJ_EXPORT void FfiWebInitialScale(float percent);
CJ_EXPORT void FfiWebBlockNetwork(bool block);
CJ_EXPORT void FfiWebDefaultFixedFontSize(int32_t size);
CJ_EXPORT void FfiWebDefaultFontSize(int32_t size);
CJ_EXPORT void FfiWebMinFontSize(int32_t size);
CJ_EXPORT void FfiWebMinLogicalFontSize(int32_t size);
CJ_EXPORT void FfiWebFixedFont(const char* family);
CJ_EXPORT void FfiWebSansSerifFont(const char* family);
CJ_EXPORT void FfiWebSerifFont(const char* family);
CJ_EXPORT void FfiWebStandardFont(const char* family);
CJ_EXPORT void FfiWebFantasyFont(const char* family);
CJ_EXPORT void FfiWebCursiveFont(const char* family);
CJ_EXPORT VectorScriptItemHandle FfiVectorScriptItemCreate(int64_t size);
CJ_EXPORT void FfiVectorScriptItemSetElement(VectorScriptItemHandle handle, int64_t index, FfiScriptItem item);
CJ_EXPORT void FfiVectorScriptItemDelete(VectorScriptItemHandle handle);
CJ_EXPORT void FfiWebPinchSmooth(bool isEnabled);
CJ_EXPORT void FfiWebAllowWindowOpenMethod(bool flag);
CJ_EXPORT void FfiWebMediaOptions(int32_t resumeInterval, bool audioExclusive);
CJ_EXPORT void FfiWebJavaScriptOnDocumentStart(VectorScriptItemHandle handle);
CJ_EXPORT void FfiWebJavaScriptOnDocumentEnd(VectorScriptItemHandle handle);
CJ_EXPORT void FfiWebLayoutMode(int32_t layoutMode);
CJ_EXPORT void FfiWebEnableNativeEmbedMode(bool enable);
CJ_EXPORT void FfiWebRegisterNativeEmbedRule(const char* tag, const char* type);
CJ_EXPORT void FfiWebDefaultTextEncodingFormat(const char* format);
CJ_EXPORT void FfiWebMetaViewport(bool enabled);
CJ_EXPORT void FfiWebTextAutosizing(bool textAutosizing);
CJ_EXPORT VectorExpandedMenuItemOptionsHandle FfiVectorExpandedMenuItemOptionsCreate(int64_t size);
CJ_EXPORT void FfiVectorExpandedMenuItemOptionsSetElement(
    VectorExpandedMenuItemOptionsHandle handle, int64_t index, FfiExpandedMenuItemOptions item);
CJ_EXPORT void FfiVectorExpandedMenuItemOptionsDelete(VectorExpandedMenuItemOptionsHandle handle);
CJ_EXPORT void FfiWebSelectionMenuOptions(VectorExpandedMenuItemOptionsHandle handle);
CJ_EXPORT void FfiWebOnAdsBlocked(void (*callback)(FfiAdsBlockedDetails details));
CJ_EXPORT void FfiWebKeyboardAvoidMode(int32_t mode);
CJ_EXPORT void FfiWebEditMenuOptions(CjOnCreateMenu cjOnCreateMenu, CjOnMenuItemClick cjOnMenuItemClick);
CJ_EXPORT void FfiWebOnBeforeUnload(bool (*callback)(FfiWebEvent envent));
CJ_EXPORT void FfiWebOnConfirm(bool (*callback)(FfiWebEvent event));
CJ_EXPORT void FfiWebOnPrompt(bool (*callback)(FfiWebEvent event));
CJ_EXPORT void FfiWebOnConsole(bool (*callback)(void* event));
CJ_EXPORT int32_t FfiWebConsoleGetLineNumber(void* msg);
CJ_EXPORT ExternalString FfiWebConsoleGetMessage(void* msg);
CJ_EXPORT int32_t FfiWebConsoleGetMessageLevel(void* msg);
CJ_EXPORT ExternalString FfiWebConsoleGetSourceId(void* msg);
CJ_EXPORT void FfiWebFreeConsoleMessage(void* msg);
CJ_EXPORT void FfiWebOnDownloadStart(void (*callback)(FfiOnDownloadStartEvent event));
CJ_EXPORT void FfiWebOnErrorReceive(void (*callback)(void* request, void* error));
CJ_EXPORT ExternalString FfiWebGetErrorInfo(void* error);
CJ_EXPORT int32_t FfiWebGetErrorCode(void* error);
CJ_EXPORT void FfiWebFreeResourceError(void* error);
CJ_EXPORT VectorHeaderHandle FfiVectorHeaderCreate(int64_t size);
CJ_EXPORT FfiHeader FfiVectorHeaderGet(int64_t index, VectorHeaderHandle handle);
CJ_EXPORT int64_t FfiVectorHeaderSize(VectorHeaderHandle handle);
CJ_EXPORT void FfiVectorHeaderDelete(VectorHeaderHandle handle);
CJ_EXPORT VectorHeaderHandle FfiWebGetRequestHeader(void* ptr);
CJ_EXPORT ExternalString FfiWebGetRequestUrl(void* ptr);
CJ_EXPORT bool FfiWebIsMainFrame(void* ptr);
CJ_EXPORT bool FfiWebIsRedirect(void* ptr);
CJ_EXPORT bool FfiWebIsRequestGesture(void* ptr);
CJ_EXPORT ExternalString FfiWebGetRequestMethod(void* ptr);
CJ_EXPORT void FfiWebFreeResourceRequest(void* ptr);
CJ_EXPORT ExternalString FfiWebGetReasonMessage(void* prt);
CJ_EXPORT int32_t FfiWebGetResponseCode(void* ptr);
CJ_EXPORT ExternalString FfiWebGetResponseData(void* ptr);
CJ_EXPORT ExternalString FfiWebGetResponseEncoding(void* ptr);
CJ_EXPORT VectorHeaderHandle FfiWebGetResponseHeader(void* ptr);
CJ_EXPORT void FfiWebFreeResourceResponse(void* ptr);
};
#endif // OHOS_ACE_FRAMEWORK_CJ_WEB_H
