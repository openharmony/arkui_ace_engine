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

#include "cj_web_ffi.h"

#include "application_context.h"
#include "cj_lambda.h"

#include "core/components_ng/pattern/web/web_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;
using namespace OHOS::Webview;

struct FfiWebEvent {
    const char* url;
    const char* message;
    const char* value;
    RefPtr<Result>* result;
};

namespace OHOS::Ace::Framework {
bool g_cjWebDebuggingAccess = false;
constexpr int32_t PARENT_FIRST_VALUE = 2;
RequestResultCallback g_requestResultcb = nullptr;

class CJWebWindowNewHandler : public Referenced {
public:
    struct ChildWindowInfo {
        int32_t parentWebId_ = -1;
        WebviewControllerImpl* controller_;
    };

    void SetEvent(const WebWindowNewEvent& eventInfo)
    {
        handler_ = eventInfo.GetWebWindowNewHandler();
    }

    static WebviewControllerImpl* PopupController(int32_t id, int32_t* parentId = nullptr)
    {
        auto iter = controller_map_.find(id);
        if (iter == controller_map_.end()) {
            return nullptr;
        }
        auto controller = iter->second.controller_;
        if (parentId) {
            *parentId = iter->second.parentWebId_;
        }
        controller_map_.erase(iter);
        return controller;
    }

    static bool ExistController(WebviewControllerImpl* controller, int32_t& parentWebId)
    {
        if (controller == nullptr) {
            parentWebId = -1;
            return false;
        }

        auto webId1 = controller->GetWebId();
        for (auto iter = controller_map_.begin(); iter != controller_map_.end(); iter++) {
            auto webId2 = iter->second.controller_->GetWebId();
            if (webId1 == webId2) {
                parentWebId = iter->second.parentWebId_;
                return true;
            }
        }

        parentWebId = -1;
        return false;
    }

    void SetWebController(WebviewControllerImpl* controller)
    {
        if (handler_) {
            int32_t parentNWebId = handler_->GetParentNWebId();
            if (parentNWebId == -1) {
                return;
            }
            if (controller == nullptr) {
                WebModel::GetInstance()->NotifyPopupWindowResult(parentNWebId, false);
                return;
            }

            auto childWebId = controller->GetWebId();
            if (childWebId == parentNWebId || childWebId != -1) {
                WebModel::GetInstance()->NotifyPopupWindowResult(parentNWebId, false);
                return;
            }
            controller_map_.insert(
                std::pair<int32_t, ChildWindowInfo>(handler_->GetId(), { parentNWebId, controller }));
        }
    }

private:
    RefPtr<WebWindowNewHandler> handler_;
    static std::unordered_map<int32_t, ChildWindowInfo> controller_map_;
};

class __attribute__((visibility("default"))) CJWebPermissionRequest : public Referenced {
public:
    void SetEvent(const Ace::WebPermissionRequestEvent& eventInfo)
    {
        webPermissionRequest_ = eventInfo.GetWebPermissionRequest();
    }

    void Deny()
    {
        if (webPermissionRequest_) {
            webPermissionRequest_->Deny();
        }
    }

    std::string GetOrigin()
    {
        std::string origin;
        if (webPermissionRequest_) {
            origin = webPermissionRequest_->GetOrigin();
        }
        return origin;
    }

    std::vector<std::string> GetAccessibleResources()
    {
        std::vector<std::string> resources;
        if (webPermissionRequest_) {
            resources = webPermissionRequest_->GetResources();
        }
        return resources;
    }

    void Grant(std::vector<std::string>& args)
    {
        if (args.size() < 1) {
            if (webPermissionRequest_) {
                webPermissionRequest_->Deny();
            }
        }
        std::vector<std::string> resources;
        for (size_t i = 0; i < args.size(); i++) {
            resources.push_back(args[i]);
        }
        if (webPermissionRequest_) {
            webPermissionRequest_->Grant(resources);
        }
    }

private:
    static CJWebPermissionRequest* Construct()
    {
        auto cjWebPermissionrequest = Ace::Referenced::MakeRefPtr<CJWebPermissionRequest>();
        cjWebPermissionrequest->IncRefCount();
        return Ace::Referenced::RawPtr(cjWebPermissionrequest);
    }

    static void Destructor(CJWebPermissionRequest* cjWebPermissionRequest)
    {
        if (cjWebPermissionRequest != nullptr) {
            cjWebPermissionRequest->DecRefCount();
        }
    }
    Ace::RefPtr<Ace::WebPermissionRequest> webPermissionRequest_;
};

char* MallocCString(const std::string& origin)
{
    auto len = origin.length() + 1;
    char* res = static_cast<char*>(malloc(sizeof(char) * len));
    if (res == nullptr) {
        return nullptr;
    }
    return std::char_traits<char>::copy(res, origin.c_str(), len);
}

void RequestPermissionsFromUserWeb(CJWebPermissionRequest& request)
{
    auto abilityContext = AbilityRuntime::Context::GetApplicationContext();
    std::string permission = "ohos.permission.READ_PASTEBOARD";
    char* cPermission = MallocCString(permission);

    if (cPermission == nullptr) {
        return;
    }
    auto callBack = [&request](RetDataCPermissionRequestResult infoRef) -> void {
        if (infoRef.code == 0) {
            request.GetAccessibleResources();
        } else {
            request.Deny();
        }
    };

    std::function<void(RetDataCPermissionRequestResult)> func = callBack;
    g_requestResultcb(abilityContext.get(), CArrString { .head = &cPermission, .size = 1 }, &func);

    free(cPermission);
}

void ParseScriptItems(VectorScriptItemHandle& handle, ScriptItems& scriptItems)
{
    auto ffiScriptItemVec = *reinterpret_cast<std::vector<FfiScriptItem>*>(handle);
    for (size_t i = 0; i < ffiScriptItemVec.size(); i++) {
        auto script = ffiScriptItemVec[i].script;
        auto scriptRulesVec = ffiScriptItemVec[i].scriptRules;
        auto scriptRules = *reinterpret_cast<std::vector<std::string>*>(scriptRulesVec);
        if (scriptItems.find(script) == scriptItems.end()) {
            scriptItems.insert(std::make_pair(script, scriptRules));
        }
    }
}

void EraseSpace(std::string& data)
{
    auto iter = data.begin();
    while (iter != data.end()) {
        if (isspace(*iter)) {
            iter = data.erase(iter);
        } else {
            ++iter;
        }
    }
}
} // namespace OHOS::Ace::Framework
std::unordered_map<int32_t, CJWebWindowNewHandler::ChildWindowInfo> CJWebWindowNewHandler::controller_map_;
extern "C" {
void FfiOHOSAceFrameworkWebSetCallback(RequestResultCallback cb)
{
    if (g_requestResultcb == nullptr) {
        g_requestResultcb = cb;
    }
}

void FfiOHOSAceFrameworkWebCreate(const char* src, int64_t controllerId, int32_t type, bool mode)
{
    RenderMode renderMode = RenderMode::ASYNC_RENDER;
    renderMode = static_cast<RenderMode>(type);

    auto controller = FFIData::GetData<WebviewControllerImpl>(controllerId);
    if (controller) {
        auto setIdCallback = [controller](int32_t webId) { controller->SetWebId(webId); };
        std::function<void(const std::string&)> setHapPathCallback = nullptr;
        setHapPathCallback = [controller](const std::string& hapPath) { controller->InnerSetHapPath(hapPath); };

        std::function<void(const std::shared_ptr<BaseEventInfo>&)> requestPermissionsFromUserCallback = nullptr;
        requestPermissionsFromUserCallback = [controller](const std::shared_ptr<BaseEventInfo>& info) {
            auto* eventInfo = TypeInfoHelper::DynamicCast<WebPermissionRequestEvent>(info.get());
            auto permissionObj = OHOS::Ace::Framework::CJWebPermissionRequest();
            permissionObj.SetEvent(*eventInfo);
            OHOS::Ace::Framework::RequestPermissionsFromUserWeb(permissionObj);
        };

        int32_t parentNWebId = -1;
        bool isPopup = CJWebWindowNewHandler::ExistController(controller, parentNWebId);
        WebModel::GetInstance()->Create(
            src, std::move(setIdCallback), std::move(setHapPathCallback), parentNWebId, isPopup, renderMode, mode);
        WebModel::GetInstance()->SetPermissionClipboard(std::move(requestPermissionsFromUserCallback));
        if (!controller->customeSchemeCmdLine_.empty()) {
            WebModel::GetInstance()->SetCustomScheme(controller->customeSchemeCmdLine_);
        }
        if (controller->webDebuggingAccess_ == g_cjWebDebuggingAccess) {
            return;
        }
        WebModel::GetInstance()->SetWebDebuggingAccessEnabled(controller->webDebuggingAccess_);
        g_cjWebDebuggingAccess = controller->webDebuggingAccess_;
        return;
    } else {
        LOGI("Web controller init failed");
    }
    WebModel::GetInstance()->SetFocusable(true);
    WebModel::GetInstance()->SetFocusNode(true);
}

void FfiOHOSAceFrameworkWebHandleCancel(void* result)
{
    auto res = *reinterpret_cast<RefPtr<Result>*>(result);
    res->Cancel();
}

void FfiOHOSAceFrameworkWebHandleConfirm(void* result)
{
    auto res = *reinterpret_cast<RefPtr<Result>*>(result);
    res->Confirm();
}

void FfiOHOSAceFrameworkWebHandlePromptConfirm(void* result, const char* message)
{
    auto res = *reinterpret_cast<RefPtr<Result>*>(result);
    res->Confirm(message);
}

void FfiOHOSAceFrameworkWebReleaseResult(void* result)
{
    if (result != nullptr) {
        RefPtr<Result>* res = reinterpret_cast<RefPtr<Result>*>(result);
        delete res;
    }
}

void FfiOHOSAceFrameworkWebFileAccessEnabled(bool isFileAccessEnabled)
{
    WebModel::GetInstance()->SetFileAccessEnabled(isFileAccessEnabled);
}

void FfiOHOSAceFrameworkWebDomStorageAccessEnabled(bool isDomStorageAccessEnabled)
{
    WebModel::GetInstance()->SetDomStorageAccessEnabled(isDomStorageAccessEnabled);
}

void FfiOHOSAceFrameworkWebImageAccessEnabled(bool isImageAccessEnabled)
{
    WebModel::GetInstance()->SetImageAccessEnabled(isImageAccessEnabled);
}

void FfiOHOSAceFrameworkWebOnlineImageAccessEnabled(bool isImageAccessEnabled)
{
    WebModel::GetInstance()->SetOnLineImageAccessEnabled(isImageAccessEnabled);
}

void FfiOHOSAceFrameworkWebMixedMode(int32_t mixedModeNum)
{
    auto mixedContentMode = MixedModeContent::MIXED_CONTENT_NEVER_ALLOW;
    switch (mixedModeNum) {
        case 0:
            mixedContentMode = MixedModeContent::MIXED_CONTENT_ALWAYS_ALLOW;
            break;
        case 1:
            mixedContentMode = MixedModeContent::MIXED_CONTENT_COMPATIBILITY_MODE;
            break;
        default:
            mixedContentMode = MixedModeContent::MIXED_CONTENT_NEVER_ALLOW;
            break;
    }
    WebModel::GetInstance()->SetMixedMode(mixedContentMode);
}

void FfiOHOSAceFrameworkWebZoomAccessEnabled(bool isZoomAccessEnabled)
{
    WebModel::GetInstance()->SetZoomAccessEnabled(isZoomAccessEnabled);
}

void FfiOHOSAceFrameworkWebGeolocationAccessEnabled(bool isGeolocationAccessEnabled)
{
    WebModel::GetInstance()->SetGeolocationAccessEnabled(isGeolocationAccessEnabled);
}

void FfiOHOSAceFrameworkWebVerticalScrollBarAccessEnabled(bool isVerticalScrollBarAccess)
{
    WebModel::GetInstance()->SetVerticalScrollBarAccessEnabled(isVerticalScrollBarAccess);
}

NestedScrollMode GetNestedScrollModeValue(int32_t value)
{
    auto ret = NestedScrollMode::SELF_ONLY;
    switch (value) {
        case 0:
            ret = NestedScrollMode::SELF_ONLY;
            break;
        case 1:
            ret = NestedScrollMode::SELF_FIRST;
            break;
        case PARENT_FIRST_VALUE:
            ret = NestedScrollMode::PARENT_FIRST;
            break;
        default:
            ret = NestedScrollMode::PARALLEL;
            break;
    }
    return ret;
}

void FfiOHOSAceFrameworkNestedScroll(int32_t nestedScrollNum, int32_t scrollBackwardNum)
{
    NestedScrollOptions nestedOpt = {
        .forward = GetNestedScrollModeValue(nestedScrollNum),
        .backward = GetNestedScrollModeValue(scrollBackwardNum),
    };
    WebModel::GetInstance()->SetNestedScroll(nestedOpt);
}

void FfiOHOSAceFrameworkWebUserAgent(const std::string& userAgent)
{
    WebModel::GetInstance()->SetUserAgent(userAgent);
}

void FfiOHOSAceFrameworkWebBackgroundColor(uint32_t color)
{
    WebModel::GetInstance()->SetBackgroundColor(Color(color));
}

void OnCommonDialog(bool (*callback)(FfiWebEvent event), int64_t dialogEventType)
{
    auto instanceId = Container::CurrentId();
    auto onDialog = [webCallback = CJLambda::Create(callback), instanceId](const BaseEventInfo* info) -> bool {
        ContainerScope scope(instanceId);
        FfiWebEvent cjEvent {};
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
        cjEvent.url = eventInfo->GetUrl().c_str();
        cjEvent.message = eventInfo->GetMessage().c_str();
        if (eventInfo->GetType() == DialogEventType::DIALOG_EVENT_PROMPT) {
            cjEvent.value = eventInfo->GetValue().c_str();
        }
        auto result = new RefPtr<Result>(eventInfo->GetResult());
        cjEvent.result = result;
        auto res = webCallback(cjEvent);
        return res;
    };
    WebModel::GetInstance()->SetOnCommonDialog(std::move(onDialog), dialogEventType);
}

void FfiOHOSAceFrameworkWebOnAlert(bool (*callback)(FfiWebEvent event))
{
    OnCommonDialog(callback, DialogEventType::DIALOG_EVENT_ALERT);
}

void FfiOHOSAceFrameworkWebOnPageStart(void (*callback)(const char* url))
{
    auto instanceId = Container::CurrentId();
    auto onStart = [func = CJLambda::Create(callback), instanceId](const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageStartEvent>(info);
        func(eventInfo->GetLoadedUrl().c_str());
    };
    WebModel::GetInstance()->SetOnPageStart(std::move(onStart));
}

bool WebRequestHeadersToMapToCFFIArray(const RefPtr<WebRequest>& webRequest, MapToCFFIArray& res)
{
    std::map<std::string, std::string> header = webRequest->GetHeaders();
    auto key = (const char**)malloc(sizeof(const char*) * header.size());
    auto value = (const char**)malloc(sizeof(const char*) * header.size());
    if (key == NULL || value == NULL) {
        if (key != NULL) {
            free(key);
        }
        if (value != NULL) {
            free(value);
        }
        LOGE("FfiOHOSAceFrameworkGetHeaders fail, malloc fail");
        return false;
    }
    size_t i = 0;
    res.size = header.size();
    res.key = key;
    res.value = value;
    for (auto it = header.begin(); it != header.end(); ++it, ++i) {
        res.key[i] = it->first.c_str();
        res.value[i] = it->second.c_str();
    }
    return true;
}

void MapToCFFIArrayToFreeMemory(MapToCFFIArray& mapToCFFIArray)
{
    free(mapToCFFIArray.key);
    free(mapToCFFIArray.value);
}

void FfiOHOSAceFrameworkWebOnLoadIntercept(bool (*callback)(void* event))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(callback), node = frameNode](const BaseEventInfo* info) -> bool {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope(webNode->GetInstanceId());
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadInterceptEvent>(info);
        auto request = new RefPtr<WebRequest>(eventInfo->GetRequest());
        return func(request);
    };
    WebModel::GetInstance()->SetOnLoadIntercept(std::move(cjCallback));
}

void FfiOHOSAceFrameworkWebOnPageFinish(void (*callback)(const char* url))
{
    auto instanceId = Container::CurrentId();
    auto onFinish = [func = CJLambda::Create(callback), instanceId](const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageFinishEvent>(info);
        func(eventInfo->GetLoadedUrl().c_str());
    };
    WebModel::GetInstance()->SetOnPageFinish(std::move(onFinish));
}

CJ_EXPORT void FfiOHOSAceFrameworkWebJavaScriptProxy(
    VectorInt64Handle funcList, const char* name, VectorStringHandle methodList, int64_t controllerId)
{
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
    auto controller = FFIData::GetData<WebviewControllerImpl>(controllerId);
    if (controller) {
        auto& funcs = *reinterpret_cast<std::vector<int64_t>*>(funcList);
        std::vector<std::function<char*(const char*)>> cFuncs;
        for (int64_t i = 0; i < static_cast<int64_t>(funcs.size()); i++) {
            auto cFunc = reinterpret_cast<char* (*)(const char*)>(funcs[i]);
            auto wrapper = [lambda = CJLambda::Create(cFunc)](const char* str) -> char* { return lambda(str); };
            cFuncs.push_back(wrapper);
        }
        std::string cName = std::string(name);
        auto& methods = *reinterpret_cast<std::vector<std::string>*>(methodList);
        auto jsProxyCallback = [controller, cFuncs, cName, methods]() {
            controller->SetNWebJavaScriptResultCallBack();
            controller->RegisterJavaScriptProxy(cFuncs, cName, methods);
        };
        WebModel::GetInstance()->SetJsProxyCallback(jsProxyCallback);
    }
#endif
}

void FfiOHOSAceFrameworkWebDarkMode(int32_t darkMode)
{
    auto mode = WebDarkMode::Off;
    switch (darkMode) {
        case 0:
            mode = WebDarkMode::Off;
            break;
        case 1:
            mode = WebDarkMode::On;
            break;
        case 2:
            mode = WebDarkMode::Auto;
            break;
        default:
            mode = WebDarkMode::Off;
            break;
    }
    WebModel::GetInstance()->SetDarkMode(mode);
}

void FfiOHOSAceFrameworkWebForceDarkAccess(bool access)
{
    WebModel::GetInstance()->SetForceDarkAccess(access);
}

void FfiWebEnableNativemediaPlayer(bool enable, bool shouldOverlay)
{
    WebModel::GetInstance()->SetNativeVideoPlayerConfig(enable, shouldOverlay);
}

void FfiWebOnControllerAttached(void (*callback)())
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto lambda = [func = CJLambda::Create(callback), node = frameNode]() {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope(webNode->GetInstanceId());
        auto context = PipelineBase::GetCurrentContext();
        if (context) {
            context->UpdateCurrentActiveNode(node);
        }
        auto executor = Container::CurrentTaskExecutorSafely();
        CHECK_NULL_VOID(executor);
        executor->PostSyncTask([func]() { func(); }, TaskExecutor::TaskType::UI, "ArkUIWebControllerAttached");
    };
    WebModel::GetInstance()->SetOnControllerAttached(std::move(lambda));
}

void FfiWebOnPermissionRequest(void (*callback)(COnPermissionRequestEvent))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto lambda = [func = CJLambda::Create(callback), node = frameNode](const BaseEventInfo* info) {
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebPermissionRequestEvent>(info);
        auto permissionObj = new CJWebPermissionRequest();
        permissionObj->SetEvent(*eventInfo);

        auto denyWrapper = [](void* objPtr) {
            auto permission = reinterpret_cast<CJWebPermissionRequest*>(objPtr);
            permission->Deny();
        };
        auto getOriginWrapper = [](void* objPtr) -> ExternalString {
            auto permission = reinterpret_cast<CJWebPermissionRequest*>(objPtr);
            return Utils::MallocCString(permission->GetOrigin());
        };
        auto getAccessibleResourceWrapper = [](void* objPtr) -> VectorStringHandle {
            auto permission = reinterpret_cast<CJWebPermissionRequest*>(objPtr);
            auto result = new std::vector<std::string>;
            *result = permission->GetAccessibleResources();
            return result;
        };
        auto grantWrapper = [](VectorStringHandle resources, void* objPtr) {
            auto permission = reinterpret_cast<CJWebPermissionRequest*>(objPtr);
            auto resVec = reinterpret_cast<std::vector<std::string>*>(resources);
            permission->Grant(*resVec);
        };
        auto freeWrapper = [](void* objPtr) {
            if (objPtr) {
                auto permission = reinterpret_cast<CJWebPermissionRequest*>(objPtr);
                delete permission;
            }
        };
        CPermissionRequest cRequest { .deny = denyWrapper,
            .getOrigin = getOriginWrapper,
            .getAccessibleResource = getAccessibleResourceWrapper,
            .grant = grantWrapper,
            .permissionPtr = permissionObj,
            .free = freeWrapper };

        COnPermissionRequestEvent cEvent { .request = cRequest };
        func(cEvent);
    };
    WebModel::GetInstance()->SetPermissionRequestEventId(lambda);
}

void FfiWebJavaScriptAccess(bool javaScriptAccess)
{
    WebModel::GetInstance()->SetJsEnabled(javaScriptAccess);
}

void FfiWebOverScrollMode(int32_t overScrollMode)
{
    auto mode = OverScrollMode::NEVER;
    switch (overScrollMode) {
        case 0:
            mode = OverScrollMode::NEVER;
            break;
        case 1:
            mode = OverScrollMode::ALWAYS;
            break;
        default:
            mode = OverScrollMode::NEVER;
            break;
    }
    WebModel::GetInstance()->SetOverScrollMode(mode);
}

void FfiWebOverviewModeAccess(bool overviewModeAccess)
{
    WebModel::GetInstance()->SetOverviewModeAccessEnabled(overviewModeAccess);
}

void FfiWebDatabaseAccess(bool databaseAccess)
{
    WebModel::GetInstance()->SetDatabaseAccessEnabled(databaseAccess);
}

void FfiWebMediaPlayGestureAccess(bool access)
{
    WebModel::GetInstance()->SetMediaPlayGestureAccess(access);
}

void FfiWebMultiWindowAccess(bool multiWindow)
{
    WebModel::GetInstance()->SetMultiWindowAccessEnabled(multiWindow);
}

void FfiWebHorizontalScrollBarAccess(bool horizontalScrollBar)
{
    WebModel::GetInstance()->SetHorizontalScrollBarAccessEnabled(horizontalScrollBar);
}

void FfiWebCacheMode(int32_t cacheMode)
{
    auto mode = WebCacheMode::DEFAULT;
    switch (cacheMode) {
        case static_cast<int32_t>(WebCacheMode::DEFAULT):
            mode = WebCacheMode::DEFAULT;
            break;
        case static_cast<int32_t>(WebCacheMode::USE_CACHE_ELSE_NETWORK):
            mode = WebCacheMode::USE_CACHE_ELSE_NETWORK;
            break;
        case static_cast<int32_t>(WebCacheMode::USE_NO_CACHE):
            mode = WebCacheMode::USE_NO_CACHE;
            break;
        case static_cast<int32_t>(WebCacheMode::USE_CACHE_ONLY):
            mode = WebCacheMode::USE_CACHE_ONLY;
            break;
        default:
            mode = WebCacheMode::DEFAULT;
            break;
    }
    WebModel::GetInstance()->SetCacheMode(mode);
}

void FfiWebCopyOptions(int32_t value)
{
    auto mode = CopyOptions::Local;
    switch (value) {
        case static_cast<int32_t>(CopyOptions::None):
            mode = CopyOptions::None;
            break;
        case static_cast<int32_t>(CopyOptions::InApp):
            mode = CopyOptions::InApp;
            break;
        case static_cast<int32_t>(CopyOptions::Local):
            mode = CopyOptions::Local;
            break;
        case static_cast<int32_t>(CopyOptions::Distributed):
            mode = CopyOptions::Distributed;
            break;
        default:
            mode = CopyOptions::Local;
            break;
    }
    WebModel::GetInstance()->SetCopyOptionMode(mode);
}

void FfiWebTextZoomRatio(int32_t textZoomRatio)
{
    WebModel::GetInstance()->SetTextZoomRatio(textZoomRatio);
}

void FfiWebInitialScale(float percent)
{
    WebModel::GetInstance()->InitialScale(percent);
}

void FfiWebBlockNetwork(bool block)
{
    WebModel::GetInstance()->SetBlockNetwork(block);
}

void FfiWebDefaultFixedFontSize(int32_t size)
{
    WebModel::GetInstance()->SetDefaultFixedFontSize(size);
}

void FfiWebDefaultFontSize(int32_t size)
{
    WebModel::GetInstance()->SetDefaultFontSize(size);
}

void FfiWebMinFontSize(int32_t size)
{
    WebModel::GetInstance()->SetMinFontSize(size);
}

void FfiWebMinLogicalFontSize(int32_t size)
{
    WebModel::GetInstance()->SetMinLogicalFontSize(size);
}

void FfiWebFixedFont(const char* family)
{
    WebModel::GetInstance()->SetWebFixedFont(family);
}

void FfiWebSansSerifFont(const char* family)
{
    WebModel::GetInstance()->SetWebSansSerifFont(family);
}

void FfiWebSerifFont(const char* family)
{
    WebModel::GetInstance()->SetWebSerifFont(family);
}

void FfiWebStandardFont(const char* family)
{
    WebModel::GetInstance()->SetWebStandardFont(family);
}

void FfiWebFantasyFont(const char* family)
{
    WebModel::GetInstance()->SetWebFantasyFont(family);
}

void FfiWebCursiveFont(const char* family)
{
    WebModel::GetInstance()->SetWebCursiveFont(family);
}

VectorScriptItemHandle FfiVectorScriptItemCreate(int64_t size)
{
    return new std::vector<FfiScriptItem>(size);
}

void FfiVectorScriptItemSetElement(VectorScriptItemHandle handle, int64_t index, FfiScriptItem item)
{
    auto actualVec = reinterpret_cast<std::vector<FfiScriptItem>*>(handle);
    (*actualVec)[index] = item;
}

void FfiVectorScriptItemDelete(VectorScriptItemHandle handle)
{
    auto actualVec = reinterpret_cast<std::vector<FfiScriptItem>*>(handle);
    delete actualVec;
}

void FfiWebPinchSmooth(bool isEnabled)
{
    WebModel::GetInstance()->SetPinchSmoothModeEnabled(isEnabled);
}

void FfiWebAllowWindowOpenMethod(bool flag)
{
    WebModel::GetInstance()->SetAllowWindowOpenMethod(flag);
}

void FfiWebMediaOptions(int32_t resumeInterval, bool audioExclusive)
{
    WebModel::GetInstance()->SetAudioResumeInterval(resumeInterval);
    WebModel::GetInstance()->SetAudioExclusive(audioExclusive);
}

void FfiWebJavaScriptOnDocumentStart(VectorScriptItemHandle handle)
{
    ScriptItems scriptItems;
    ParseScriptItems(handle, scriptItems);
    WebModel::GetInstance()->JavaScriptOnDocumentStart(scriptItems);
}

void FfiWebJavaScriptOnDocumentEnd(VectorScriptItemHandle handle)
{
    ScriptItems scriptItems;
    ParseScriptItems(handle, scriptItems);
    WebModel::GetInstance()->JavaScriptOnDocumentEnd(scriptItems);
}

void FfiWebLayoutMode(int32_t layoutMode)
{
    auto mode = WebLayoutMode::NONE;
    switch (layoutMode) {
        case 0:
            mode = WebLayoutMode::NONE;
            break;
        case 1:
            mode = WebLayoutMode::FIT_CONTENT;
            break;
        default:
            mode = WebLayoutMode::NONE;
            break;
    }
    WebModel::GetInstance()->SetLayoutMode(mode);
}

void FfiWebEnableNativeEmbedMode(bool enable)
{
    WebModel::GetInstance()->SetNativeEmbedModeEnabled(enable);
}
void FfiWebRegisterNativeEmbedRule(const char* tag, const char* type)
{
    WebModel::GetInstance()->RegisterNativeEmbedRule(tag, type);
}

void FfiWebDefaultTextEncodingFormat(const char* format)
{
    std::string textEncodingFormat = std::string(format);
    EraseSpace(textEncodingFormat);
    if (textEncodingFormat.empty()) {
        WebModel::GetInstance()->SetDefaultTextEncodingFormat("UTF-8");
        return;
    }
    WebModel::GetInstance()->SetDefaultTextEncodingFormat(textEncodingFormat);
}

void FfiWebMetaViewport(bool enabled)
{
    WebModel::GetInstance()->SetMetaViewport(enabled);
}

void FfiWebTextAutosizing(bool textAutosizing)
{
    WebModel::GetInstance()->SetTextAutosizing(textAutosizing);
}

VectorExpandedMenuItemOptionsHandle FfiVectorExpandedMenuItemOptionsCreate(int64_t size)
{
    return new std::vector<FfiExpandedMenuItemOptions>(size);
}

void FfiVectorExpandedMenuItemOptionsSetElement(
    VectorExpandedMenuItemOptionsHandle handle, int64_t index, FfiExpandedMenuItemOptions item)
{
    auto actualVec = reinterpret_cast<std::vector<FfiExpandedMenuItemOptions>*>(handle);
    (*actualVec)[index] = item;
}

void FfiVectorExpandedMenuItemOptionsDelete(VectorExpandedMenuItemOptionsHandle handle)
{
    auto actualVec = reinterpret_cast<std::vector<FfiExpandedMenuItemOptions>*>(handle);
    delete actualVec;
}

void FfiWebSelectionMenuOptions(VectorExpandedMenuItemOptionsHandle handle)
{
    auto actualVec = *reinterpret_cast<std::vector<FfiExpandedMenuItemOptions>*>(handle);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    WebMenuOptionsParam optionParam;
    NG::MenuOptionsParam menuOption;
    for (size_t i = 0; i < actualVec.size(); i++) {
        auto ffiOption = actualVec[i];
        menuOption.content = ffiOption.content;
        menuOption.icon.reset();
        if (ffiOption.hasStartIcon) {
            menuOption.icon = ffiOption.startIcon;
        }
        auto actionCallback = [node = frameNode, func = CJLambda::Create(ffiOption.action)](
                                  const std::string selectInfo) {
            auto webNode = node.Upgrade();
            CHECK_NULL_VOID(webNode);
            ContainerScope(webNode->GetInstanceId());
            auto context = PipelineBase::GetCurrentContext();
            if (context) {
                context->UpdateCurrentActiveNode(node);
                context->SetCallBackNode(node);
            }
            func(selectInfo.c_str());
        };
        menuOption.action = std::move(actionCallback);
        optionParam.menuOption.push_back(menuOption);
    }
    WebModel::GetInstance()->SetSelectionMenuOptions(std::move(optionParam));
}

void FfiWebOnAdsBlocked(void (*callback)(FfiAdsBlockedDetails details))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto lambda = [func = CJLambda::Create(callback), node = frameNode](const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<AdsBlockedEvent>(info);
        auto blocked = eventInfo->GetAdsBlocked();
        auto resBlocked = new std::vector<std::string>(blocked.size());
        for (size_t i = 0; i < blocked.size(); i++) {
            (*resBlocked)[i] = blocked[i];
        }
        FfiAdsBlockedDetails details { .url = eventInfo->GetUrl().c_str(), .adsBlocked = resBlocked };
        func(details);
    };
    WebModel::GetInstance()->SetAdsBlockedEventId(lambda);
}

void FfiWebKeyboardAvoidMode(int32_t mode)
{
    if (mode < static_cast<int32_t>(WebKeyboardAvoidMode::RESIZE_VISUAL) ||
        mode > static_cast<int32_t>(WebKeyboardAvoidMode::DEFAULT)) {
        return;
    }
    WebKeyboardAvoidMode avoidMode = static_cast<WebKeyboardAvoidMode>(mode);
    WebModel::GetInstance()->SetKeyboardAvoidMode(avoidMode);
}

void FfiWebEditMenuOptions(CjOnCreateMenu cjOnCreateMenu, CjOnMenuItemClick cjOnMenuItemClick)
{
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    ViewAbstract::ParseEditMenuOptions(cjOnCreateMenu, cjOnMenuItemClick, onCreateMenuCallback, onMenuItemClick);
    WebModel::GetInstance()->SetEditMenuOptions(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

void FfiWebOnBeforeUnload(bool (*callback)(FfiWebEvent envent))
{
    OnCommonDialog(callback, DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD);
}

void FfiWebOnConfirm(bool (*callback)(FfiWebEvent event))
{
    OnCommonDialog(callback, DialogEventType::DIALOG_EVENT_CONFIRM);
}

void FfiWebOnPrompt(bool (*callback)(FfiWebEvent event))
{
    OnCommonDialog(callback, DialogEventType::DIALOG_EVENT_PROMPT);
}

void FfiWebOnConsole(bool (*callback)(void* event))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(callback), node = frameNode](const BaseEventInfo* info) -> bool {
        bool result = false;
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebConsoleLogEvent>(info);
        auto message = new RefPtr<WebConsoleLog>(eventInfo->GetMessage());
        result = func(message);
        return result;
    };
    WebModel::GetInstance()->SetOnConsoleLog(std::move(cjCallback));
}

int32_t FfiWebConsoleGetLineNumber(void* msg)
{
    auto msgPtr = *reinterpret_cast<RefPtr<WebConsoleLog>*>(msg);
    return msgPtr->GetLineNumber();
}

ExternalString FfiWebConsoleGetMessage(void* msg)
{
    auto msgPtr = *reinterpret_cast<RefPtr<WebConsoleLog>*>(msg);
    return Utils::MallocCString(msgPtr->GetLog());
}

int32_t FfiWebConsoleGetMessageLevel(void* msg)
{
    auto msgPtr = *reinterpret_cast<RefPtr<WebConsoleLog>*>(msg);
    return static_cast<int32_t>(msgPtr->GetLogLevel());
}

ExternalString FfiWebConsoleGetSourceId(void* msg)
{
    auto msgPtr = *reinterpret_cast<RefPtr<WebConsoleLog>*>(msg);
    return Utils::MallocCString(msgPtr->GetSourceId());
}

void FfiWebFreeConsoleMessage(void* msg)
{
    RefPtr<WebConsoleLog>* msgPtr = reinterpret_cast<RefPtr<WebConsoleLog>*>(msg);
    if (msgPtr) {
        delete msgPtr;
    }
}

void FfiWebOnDownloadStart(void (*callback)(FfiOnDownloadStartEvent event))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(callback), node = frameNode](const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<DownloadStartEvent>(info);
        FfiOnDownloadStartEvent event {};
        event.url = eventInfo->GetUrl().c_str();
        event.userAgent = eventInfo->GetUserAgent().c_str();
        event.contentDisposition = eventInfo->GetContentDisposition().c_str();
        event.mimeType = eventInfo->GetMimetype().c_str();
        event.contentLength = eventInfo->GetContentLength();
        func(event);
    };
    WebModel::GetInstance()->SetOnDownloadStart(std::move(cjCallback));
}

void FfiWebOnErrorReceive(void (*callback)(void* request, void* error))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(callback), node = frameNode](const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<ReceivedErrorEvent>(info);
        auto request = new RefPtr<WebRequest>(eventInfo->GetRequest());
        auto error = new RefPtr<WebError>(eventInfo->GetError());
        func(request, error);
    };
    WebModel::GetInstance()->SetOnErrorReceive(std::move(cjCallback));
}

ExternalString FfiWebGetErrorInfo(void* error)
{
    auto errPtr = *reinterpret_cast<RefPtr<WebError>*>(error);
    return Utils::MallocCString(errPtr->GetInfo());
}

int32_t FfiWebGetErrorCode(void* error)
{
    auto errPtr = *reinterpret_cast<RefPtr<WebError>*>(error);
    return errPtr->GetCode();
}

void FfiWebFreeResourceError(void* error)
{
    RefPtr<WebError>* errPtr = reinterpret_cast<RefPtr<WebError>*>(error);
    if (errPtr) {
        delete errPtr;
    }
}

VectorHeaderHandle FfiVectorHeaderCreate(int64_t size)
{
    return new std::vector<FfiHeader>(size);
}

FfiHeader FfiVectorHeaderGet(int64_t index, VectorHeaderHandle handle)
{
    auto actualVec = reinterpret_cast<std::vector<FfiHeader>*>(handle);
    return (*actualVec)[index];
}

int64_t FfiVectorHeaderSize(VectorHeaderHandle handle)
{
    auto actualVec = reinterpret_cast<std::vector<FfiHeader>*>(handle);
    return actualVec->size();
}

void FfiVectorHeaderDelete(VectorHeaderHandle handle)
{
    auto actualVec = reinterpret_cast<std::vector<FfiHeader>*>(handle);
    delete actualVec;
}

VectorHeaderHandle FfiWebGetRequestHeader(void* ptr)
{
    auto request = *reinterpret_cast<RefPtr<WebRequest>*>(ptr);
    auto header = request->GetHeaders();
    auto vecHeader = new std::vector<FfiHeader>(header.size());
    for (const auto& it : header) {
        size_t i = 0;
        (*vecHeader)[i] = FfiHeader { .key = Utils::MallocCString(it.first), .value = Utils::MallocCString(it.second) };
        i++;
    }
    return vecHeader;
}

ExternalString FfiWebGetRequestUrl(void* ptr)
{
    auto request = *reinterpret_cast<RefPtr<WebRequest>*>(ptr);
    return Utils::MallocCString(request->GetUrl());
}

bool FfiWebIsMainFrame(void* ptr)
{
    auto request = *reinterpret_cast<RefPtr<WebRequest>*>(ptr);
    return request->IsMainFrame();
}

bool FfiWebIsRedirect(void* ptr)
{
    auto request = *reinterpret_cast<RefPtr<WebRequest>*>(ptr);
    return request->IsRedirect();
}

bool FfiWebIsRequestGesture(void* ptr)
{
    auto request = *reinterpret_cast<RefPtr<WebRequest>*>(ptr);
    return request->HasGesture();
}

ExternalString FfiWebGetRequestMethod(void* ptr)
{
    auto request = *reinterpret_cast<RefPtr<WebRequest>*>(ptr);
    return Utils::MallocCString(request->GetMethod());
}

void FfiWebFreeResourceRequest(void* ptr)
{
    RefPtr<WebRequest>* request = reinterpret_cast<RefPtr<WebRequest>*>(ptr);
    if (request) {
        delete request;
    }
}

ExternalString FfiWebGetReasonMessage(void* prt)
{
    auto response = *reinterpret_cast<RefPtr<WebResponse>*>(prt);
    return Utils::MallocCString(response->GetReason());
}

int32_t FfiWebGetResponseCode(void* ptr)
{
    auto response = *reinterpret_cast<RefPtr<WebResponse>*>(ptr);
    return response->GetStatusCode();
}

ExternalString FfiWebGetResponseData(void* ptr)
{
    auto response = *reinterpret_cast<RefPtr<WebResponse>*>(ptr);
    return Utils::MallocCString(response->GetData());
}

ExternalString FfiWebGetResponseEncoding(void* ptr)
{
    auto response = *reinterpret_cast<RefPtr<WebResponse>*>(ptr);
    return Utils::MallocCString(response->GetEncoding());
}

VectorHeaderHandle FfiWebGetResponseHeader(void* ptr)
{
    auto response = *reinterpret_cast<RefPtr<WebResponse>*>(ptr);
    auto header = response->GetHeaders();
    auto vecHeader = new std::vector<FfiHeader>(header.size());
    for (const auto& it : header) {
        size_t i = 0;
        (*vecHeader)[i] = FfiHeader { .key = Utils::MallocCString(it.first), .value = Utils::MallocCString(it.second) };
        i++;
    }
    return vecHeader;
}

void FfiWebFreeResourceResponse(void* ptr)
{
    RefPtr<WebResponse>* response = reinterpret_cast<RefPtr<WebResponse>*>(ptr);
    if (response) {
        delete response;
    }
}

void FfiWebOnContextMenuShow(bool (*callback)(void* param, void* result))
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cjCallback = [func = CJLambda::Create(callback), node = frameNode](const BaseEventInfo* info) -> bool {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<ContextMenuEvent>(info);
        auto param = new RefPtr<WebContextMenuParam>(eventInfo->GetParam());
        auto result = new RefPtr<ContextMenuResult>(eventInfo->GetContextMenuResult());
        return func(param, result);
    };
    WebModel::GetInstance()->SetOnContextMenuShow(std::move(cjCallback));
}

int32_t FfiWebContextMenuParamGetXCoord(void* ptr)
{
    auto param = *reinterpret_cast<RefPtr<WebContextMenuParam>*>(ptr);
    CHECK_NULL_RETURN(param, -1);
    return param->GetXCoord();
}

int32_t FfiWebContextMenuParamGetYCoord(void* ptr)
{
    auto param = *reinterpret_cast<RefPtr<WebContextMenuParam>*>(ptr);
    CHECK_NULL_RETURN(param, -1);
    return param->GetYCoord();
}

ExternalString FfiWebContextMenuParamGetLinkUrl(void* ptr)
{
    auto param = *reinterpret_cast<RefPtr<WebContextMenuParam>*>(ptr);
    CHECK_NULL_RETURN(param, Utils::MallocCString(""));
    return Utils::MallocCString(param->GetLinkUrl());
}

ExternalString FfiWebContextMenuParamGetUnfilteredLinkUrl(void* ptr)
{
    auto param = *reinterpret_cast<RefPtr<WebContextMenuParam>*>(ptr);
    CHECK_NULL_RETURN(param, Utils::MallocCString(""));
    return Utils::MallocCString(param->GetUnfilteredLinkUrl());
}

ExternalString FfiWebContextMenuParamGetSourceUrl(void* ptr)
{
    auto param = *reinterpret_cast<RefPtr<WebContextMenuParam>*>(ptr);
    CHECK_NULL_RETURN(param, Utils::MallocCString(""));
    return Utils::MallocCString(param->GetSourceUrl());
}

bool FfiWebContextMenuParamExistsImageContents(void* ptr)
{
    auto param = *reinterpret_cast<RefPtr<WebContextMenuParam>*>(ptr);
    CHECK_NULL_RETURN(param, false);
    return param->HasImageContents();
}

int32_t FfiWebContextMenuParamGetMediaType(void* ptr)
{
    auto param = *reinterpret_cast<RefPtr<WebContextMenuParam>*>(ptr);
    CHECK_NULL_RETURN(param, 0);
    return param->GetMediaType();
}

ExternalString FfiWebContextMenuParamGetSelectionText(void* ptr)
{
    auto param = *reinterpret_cast<RefPtr<WebContextMenuParam>*>(ptr);
    CHECK_NULL_RETURN(param, Utils::MallocCString(""));
    return Utils::MallocCString(param->GetSelectionText());
}

int32_t FfiWebContextMenuParamGetSourceType(void* ptr)
{
    auto param = *reinterpret_cast<RefPtr<WebContextMenuParam>*>(ptr);
    CHECK_NULL_RETURN(param, 0);
    return param->GetSourceType();
}

int32_t FfiWebContextMenuParamGetInputFieldType(void* ptr)
{
    auto param = *reinterpret_cast<RefPtr<WebContextMenuParam>*>(ptr);
    CHECK_NULL_RETURN(param, 0);
    return param->GetInputFieldType();
}

bool FfiWebContextMenuParamIsEditable(void* ptr)
{
    auto param = *reinterpret_cast<RefPtr<WebContextMenuParam>*>(ptr);
    CHECK_NULL_RETURN(param, false);
    return param->IsEditable();
}

int32_t FfiWebContextMenuParamGetEditStateFlags(void* ptr)
{
    auto param = *reinterpret_cast<RefPtr<WebContextMenuParam>*>(ptr);
    CHECK_NULL_RETURN(param, 0);
    return param->GetEditStateFlags();
}

void FfiWebContextMenuResultCloseContextMenu(void* ptr)
{
    auto result = *reinterpret_cast<RefPtr<ContextMenuResult>*>(ptr);
    CHECK_NULL_VOID(result);
    result->Cancel();
}

void FfiWebContextMenuResultCopyImage(void* ptr)
{
    auto result = *reinterpret_cast<RefPtr<ContextMenuResult>*>(ptr);
    CHECK_NULL_VOID(result);
    result->CopyImage();
}

void FfiWebContextMenuResultCopy(void* ptr)
{
    auto result = *reinterpret_cast<RefPtr<ContextMenuResult>*>(ptr);
    CHECK_NULL_VOID(result);
    result->Copy();
}

void FfiWebContextMenuResultPaste(void* ptr)
{
    auto result = *reinterpret_cast<RefPtr<ContextMenuResult>*>(ptr);
    CHECK_NULL_VOID(result);
    result->Paste();
}

void FfiWebContextMenuResultCut(void* ptr)
{
    auto result = *reinterpret_cast<RefPtr<ContextMenuResult>*>(ptr);
    CHECK_NULL_VOID(result);
    result->Cut();
}

void FfiWebContextMenuResultSelectAll(void* ptr)
{
    auto result = *reinterpret_cast<RefPtr<ContextMenuResult>*>(ptr);
    CHECK_NULL_VOID(result);
    result->SelectAll();
}
}