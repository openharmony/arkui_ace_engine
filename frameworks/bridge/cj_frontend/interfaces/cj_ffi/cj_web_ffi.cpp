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
        WebModel::GetInstance()->Create(src, std::move(setIdCallback), std::move(setHapPathCallback),
            parentNWebId, isPopup, renderMode, mode);
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
    FfiOHOSAceFrameworkWebReleaseResult(result);
}

void FfiOHOSAceFrameworkWebHandleConfirm(void* result)
{
    auto res = *reinterpret_cast<RefPtr<Result>*>(result);
    res->Confirm();
    FfiOHOSAceFrameworkWebReleaseResult(result);
}

void FfiOHOSAceFrameworkWebHandlePromptConfirm(void* result, const char* message)
{
    auto res = *reinterpret_cast<RefPtr<Result>*>(result);
    res->Confirm(message);
    FfiOHOSAceFrameworkWebReleaseResult(result);
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
        delete result;
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

void FfiOHOSAceFrameworkWebOnLoadIntercept(bool (*callback)(FfiWebResourceRequest event))
{
    auto instanceId = Container::CurrentId();
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onLoadIntercept = [func = CJLambda::Create(callback), instanceId, node = frameNode](
        const BaseEventInfo* info) -> bool  {
        ContainerScope scope(instanceId);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        pipelineContext->UpdateCurrentActiveNode(node);

        FfiWebResourceRequest cjWebResourceRequest {};
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadInterceptEvent>(info);
        auto request = eventInfo->GetRequest();
        MapToCFFIArray mapToCFFIArray;
        auto wirteSuccess = WebRequestHeadersToMapToCFFIArray(request, mapToCFFIArray);
        if (!wirteSuccess) {
            return false;
        }
        cjWebResourceRequest.url = request->GetUrl().c_str();
        cjWebResourceRequest.isMainFrame = request->IsMainFrame();
        cjWebResourceRequest.isRedirect = request->IsRedirect();
        cjWebResourceRequest.hasGesture = request->HasGesture();
        cjWebResourceRequest.method = request->GetMethod().c_str();
        cjWebResourceRequest.mapToCFFIArray = &mapToCFFIArray;
        auto res = func(cjWebResourceRequest);
        MapToCFFIArrayToFreeMemory(mapToCFFIArray);
        return res;
    };
    WebModel::GetInstance()->SetOnLoadIntercept(std::move(onLoadIntercept));
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
}