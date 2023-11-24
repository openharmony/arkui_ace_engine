/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "web_delegate_cross.h"
#include "web_object_event.h"

#include "bridge/js_frontend/frontend_delegate_impl.h"

namespace OHOS::Ace {
namespace {
constexpr char WEB_METHOD_RELOAD[] = "reload";
constexpr char WEB_METHOD_ROUTER_BACK[] = "routerBack";
constexpr char WEB_METHOD_UPDATEURL[] = "updateUrl";
constexpr char WEB_METHOD_CHANGE_PAGE_URL[] = "changePageUrl";
constexpr char WEB_METHOD_PAGE_PATH_INVALID[] = "pagePathInvalid";

// The function name in Java and C++ must be same.
constexpr char WEB_METHOD_BACKWARD[] = "backward";
constexpr char WEB_METHOD_FORWARD[] = "forward";
constexpr char WEB_METHOD_ACCESSBACKWARD[] = "accessBackward";
constexpr char WEB_METHOD_ACCESSFORWARD[] = "accessForward";
constexpr char WEB_METHOD_ACCESS_STEP[] = "accessStep";
constexpr char WEB_METHOD_CLEAR_HISTORY[] = "clearHistory";
constexpr char WEB_METHOD_GET_HIT_TEST[] = "getHitTest";
constexpr char WEB_METHOD_ON_ACTIVE[] = "onActive";
constexpr char WEB_METHOD_ON_INACTIVE[] = "onInactive";
constexpr char WEB_METHOD_REQUEST_FOCUS[] = "requestFocus";
constexpr char WEB_METHOD_STOP[] = "stop";
constexpr char WEB_METHOD_REFRESH[] = "refresh";
constexpr char WEB_METHOD_LOAD_URL[] = "loadUrl";
constexpr char WEB_METHOD_LOAD_DATA[] = "loadData";
constexpr char WEB_METHOD_ADD_JAVASCRIPT[] = "registerJavaScriptProxy";
constexpr char WEB_METHOD_RUN_JAVASCRIPT[] = "runJavaScript";
constexpr char WEB_METHOD_REMOVE_JAVASCRIPT[] = "deleteJavaScriptRegister";
constexpr char WEB_METHOD_UPDATE_ATTRIBUTE[] = "updateAttribute";
constexpr char WEB_METHOD_SETCOOKIE[] = "setcookie";
constexpr char WEB_METHOD_SAVECOOKIESYNC[] = "savecookiesync";
constexpr char WEB_METHOD_TOUCH_DOWN[] = "touchDown";
constexpr char WEB_METHOD_TOUCH_UP[] = "touchUp";
constexpr char WEB_METHOD_TOUCH_MOVE[] = "touchMove";
constexpr char WEB_METHOD_TOUCH_CANCEL[] = "touchCancel";
constexpr char WEB_METHOD_UPDATE_LAYOUT[] = "updateLayout";
constexpr char WEB_METHOD_ZOOM[] = "zoom";
constexpr char WEB_METHOD_UPDATE_CONTENT[] = "updateWebContent";

// The parameters in Java and C++ must be same.
constexpr char NTC_PARAM_ACCESS_STEP[] = "accessStep";
constexpr char NTC_PARAM_RUN_JS_CODE[] = "runJavaScriptCode";
constexpr char NTC_PARAM_COOKIE_URL[] = "cookie_url";
constexpr char NTC_PARAM_COOKIE_VALUE[] = "cookie_value";
constexpr char NTC_PARAM_REGISTER_JS_NAME[] = "jsInterfaceName";
constexpr char NTC_PARAM_REGISTER_JS_METHODLIST[] = "jsInterfaceMethodList";
constexpr char NTC_PARAM_DEL_INTERFACE[] = "javaScriptInterfaceName";
constexpr char NTC_PARAM_LOAD_URL[] = "load_url";
constexpr char NTC_PARAM_LOADDATA_BASEURL[] = "load_data_base_url";
constexpr char NTC_PARAM_LOADDATA_DATA[] = "load_data_data";
constexpr char NTC_PARAM_LOADDATA_MIMETYPE[] = "load_data_mimetype";
constexpr char NTC_PARAM_LOADDATA_ENCODING[] = "load_data_encoding";
constexpr char NTC_PARAM_LOADDATA_HISTORY[] = "load_data_history_url";
constexpr char NTC_PARAM_ZOOM_FACTOR[] = "zoom";

constexpr char WEB_EVENT_PAGESTART[] = "onPageStarted";
constexpr char WEB_EVENT_PAGEFINISH[] = "onPageFinished";
constexpr char WEB_EVENT_DOWNLOADSTART[] = "onDownloadStart";
constexpr char WEB_EVENT_LOADINTERCEPT[] = "onLoadIntercept";
constexpr char WEB_EVENT_RUNJSCODE_RECVVALUE[] = "onRunJSRecvValue";
constexpr char WEB_EVENT_SCROLL[] = "onScroll";
constexpr char WEB_EVENT_SCALECHANGE[] = "onScaleChange";
constexpr char WEB_EVENT_JS_INVOKE_METHOD[] = "onJSInvokeMethod";
constexpr char WEB_EVENT_REFRESH_HISTORY[] = "onRefreshAccessedHistory";
constexpr char WEB_EVENT_RENDER_EXITED[] = "onRenderExited";
constexpr char WEB_EVENT_URL_LOAD_INTERCEPT[] = "onUrlLoadIntercept";
constexpr char WEB_EVENT_PAGECHANGED[] = "onProgressChanged";
constexpr char WEB_EVENT_RECVTITLE[] = "onReceivedTitle";
constexpr char WEB_EVENT_PAGEERROR[] = "onPageError";
constexpr char WEB_EVENT_ONMESSAGE[] = "onMessage";
constexpr char WEB_EVENT_ROUTERPUSH[] = "routerPush";
constexpr char WEB_EVENT_GEOHIDEPERMISSION[] = "onGeoHidePermission";
constexpr char WEB_EVENT_GEOPERMISSION[] = "onGeoPermission";
constexpr char WEB_EVENT_COMMONDIALOG[] = "onCommonDialog";
constexpr char WEB_EVENT_CONSOLEMESSAGE[] = "onConsoleMessage";
constexpr char WEB_EVENT_ERRORRECEIVE[] = "onErrorReceive";
constexpr char WEB_EVENT_ONSHOWFILECHOOSER[] = "onShowFileChooser";
constexpr char WEB_EVENT_ONHTTPERRORRECEIVE[] = "onHttpErrorReceive";

constexpr char WEB_CREATE[] = "web";
constexpr char NTC_PARAM_WEB[] = "web";
constexpr char NTC_PARAM_WIDTH[] = "width";
constexpr char NTC_PARAM_HEIGHT[] = "height";
constexpr char NTC_PARAM_LEFT[] = "left";
constexpr char NTC_PARAM_TOP[] = "top";
constexpr char NTC_ERROR[] = "create error";
constexpr char NTC_PARAM_SRC[] = "src";
constexpr char NTC_PARAM_ERROR_CODE[] = "errorCode";
constexpr char NTC_PARAM_URL[] = "url";
constexpr char NTC_PARAM_PAGE_URL[] = "pageUrl";
constexpr char NTC_PARAM_PAGE_INVALID[] = "pageInvalid";
constexpr char NTC_PARAM_DESCRIPTION[] = "description";
constexpr char WEB_ERROR_CODE_CREATEFAIL[] = "error-web-delegate-000001";
constexpr char WEB_ERROR_MSG_CREATEFAIL[] = "create web_delegate failed.";

constexpr char NTC_PARAM_X[] = "x";
constexpr char NTC_PARAM_Y[] = "y";

constexpr char WEB_ATTRIBUTE_ZOOM_ACCESS[] = "zoomAccess";
constexpr char NTC_ZOOM_ACCESS[] = "zoomAccess";
constexpr char WEB_ATTRIBUTE_JAVASCRIPT_ACCESS[] = "javascriptAccess";
constexpr char NTC_JAVASCRIPT_ACCESS[] = "javascriptAccess";
constexpr char WEB_ATTRIBUTE_MIN_FONT_SIZE[] = "minFontSize";
constexpr char NTC_MIN_FONT_SIZE[] = "minFontSize";
constexpr char WEB_ATTRIBUTE_HORIZONTAL_SCROLLBAR_ACCESS[] = "horizontalScrollBarAccess";
constexpr char NTC_HORIZONTAL_SCROLLBAR_ACCESS[] = "horizontalScrollBarAccess";
constexpr char WEB_ATTRIBUTE_VERTICAL_SCROLLBAR_ACCESS[] = "verticalScrollBarAccess";
constexpr char NTC_VERTICAL_SCROLLBAR_ACCESS[] = "verticalScrollBarAccess";
constexpr char WEB_ATTRIBUTE_BACKGROUND_COLOR[] = "backgroundColor";
constexpr char NTC_BACKGROUND_COLOR[] = "backgroundColor";
constexpr char WEB_ATTRIBUTE_MEDIA_PLAY_GESTURE_ACCESS[] = "mediaPlayGestureAccess";
constexpr char NTC_MEDIA_PLAY_GESTURE_ACCESS[] = "mediaPlayGestureAccess";

const char WEB_PARAM_NONE[] = "";
const char WEB_PARAM_AND[] = "#HWJS-&-#";
const char WEB_PARAM_VALUE[] = "value";
const char WEB_PARAM_EQUALS[] = "#HWJS-=-#";
const char WEB_PARAM_BEGIN[] = "#HWJS-?-#";
const char WEB_METHOD[] = "method";
const char WEB_EVENT[] = "event";
const char WEB_RESULT_FAIL[] = "fail";

constexpr int FONT_MIN_SIZE = 1;
constexpr int FONT_MAX_SIZE = 72;
}

std::map<std::string, std::string> WebResourceRequsetImpl::GetRequestHeader() const
{
    return std::map<std::string, std::string>();
}

std::string WebResourceRequsetImpl::GetRequestUrl() const
{
    auto obj = WebObjectEventManager::GetInstance().GetResourceRequestObject();
    if (!obj) {
        return std::string();
    }
    return obj->GetRequestUrl(object_);
}

std::string WebResourceRequsetImpl::GetMethod() const
{
    return "GET";
}

bool WebResourceRequsetImpl::IsRequestGesture() const
{
    return true;
}

bool WebResourceRequsetImpl::IsMainFrame() const
{
    return true;
}

bool WebResourceRequsetImpl::IsRedirect() const
{
    return false;
}

std::map<std::string, std::string> WebResourceResponseImpl::GetResponseHeader() const
{
    return std::map<std::string, std::string>();
}

std::string WebResourceResponseImpl::GetResponseData() const
{
    return "ResponseData";
}

std::string WebResourceResponseImpl::GetEncoding() const
{
    auto obj = WebObjectEventManager::GetInstance().GetResourceResponseObject();
    if (!obj) {
        LOGE("WebObjectEventManager get WebResourceResponseImpl encoding failed");
        return std::string();
    }
    return obj->GetEncoding(object_);
}

std::string WebResourceResponseImpl::GetMimeType() const
{
    auto obj = WebObjectEventManager::GetInstance().GetResourceResponseObject();
    if (!obj) {
        LOGE("WebObjectEventManager get WebResourceResponseImpl mimeType failed");
        return std::string();
    }
    return obj->GetMimeType(object_);
}

std::string WebResourceResponseImpl::GetReason() const
{
    return "ResponseReason";
}

int WebResourceResponseImpl::GetStatusCode() const
{
    auto obj = WebObjectEventManager::GetInstance().GetResourceResponseObject();
    if (!obj) {
        LOGE("WebObjectEventManager get WebResourceResponseImpl statusCode failed");
        return 0;
    }
    return obj->GetStatusCode(object_);
}

std::string WebResourceErrorImpl::GetErrorInfo() const
{
    auto obj = WebObjectEventManager::GetInstance().GetResourceErrorObject();
    if (!obj) {
        return std::string();
    }
    return obj->GetErrorInfo(object_);
}

int WebResourceErrorImpl::GetErrorCode() const
{
    auto obj = WebObjectEventManager::GetInstance().GetResourceErrorObject();
    if (!obj) {
        return 0;
    }
    return obj->GetErrorCode(object_); 
}

double WebOffsetImpl::GetX() const
{
    auto obj = WebObjectEventManager::GetInstance().GetScrollObject();
    if (!obj) {
        LOGE("WebObjectEventManager get WebOffsetImpl X failed");
        return 0.0;
    }
    return obj->GetX(object_);
}

double WebOffsetImpl::GetY() const
{
    auto obj = WebObjectEventManager::GetInstance().GetScrollObject();
    if (!obj) {
        LOGE("WebObjectEventManager get WebOffsetImpl Y failed");
        return 0.0;
    }
    return obj->GetY(object_);
}

std::string WebConsoleMessage::GetMessage() const
{
    auto obj = WebObjectEventManager::GetInstance().GetConsoleMessageObject();
    if (!obj) {
        LOGE("WebObjectEventManager get WebConsoleMessage Message failed");
        return std::string();
    }
    return obj->GetMessage(object_);
}

int WebConsoleMessage::GetMessageLevel() const
{
    auto obj = WebObjectEventManager::GetInstance().GetConsoleMessageObject();
    if (!obj) {
        LOGE("WebObjectEventManager get WebConsoleMessage MessageLevel failed");
        return 0;
    }
    return obj->GetMessageLevel(object_);
}

std::string WebConsoleMessage::GetSourceId() const
{
    return "SourceId";
}

int WebConsoleMessage::GetLineNumber() const
{
    return 0;
}

float WebScaleChangeImpl::GetNewScale() const
{
    auto obj = WebObjectEventManager::GetInstance().GetScaleChangeObject();
    if (!obj) {
        LOGE("WebObjectEventManager get WebScaleChangeImpl newScale failed");
        return 0.0f;
    }
    return obj->GetNewScale(object_);
}

float WebScaleChangeImpl::GetOldScale() const
{
    auto obj = WebObjectEventManager::GetInstance().GetScaleChangeObject();
    if (!obj) {
        LOGE("WebObjectEventManager get WebScaleChangeImpl oldScale failed");
        return 0.0f;
    }
    return obj->GetOldScale(object_);
}

WebDelegateCross::~WebDelegateCross()
{
    ReleasePlatformResource();
}

void WebDelegateCross::CreatePlatformResource(
    const Size& size, const Offset& position, const WeakPtr<NG::PipelineContext>& context)
{
    ReleasePlatformResource();
    context_ = context;
    CreatePluginResource(size, position, context);
}

void WebDelegateCross::ReleasePlatformResource()
{
    Release();
}

void WebDelegateCross::CreatePluginResource(
    const Size& size, const Offset& position, const WeakPtr<NG::PipelineContext>& context)
{
    state_ = State::CREATING;
    auto pipelineContext = context.Upgrade();
    if (!pipelineContext) {
        state_ = State::CREATEFAILED;
        return;
    }
    context_ = context;
    auto platformTaskExecutor =
        SingleTaskExecutor::Make(pipelineContext->GetTaskExecutor(), TaskExecutor::TaskType::PLATFORM);
    auto resRegister = pipelineContext->GetPlatformResRegister();
    auto weakRes = AceType::WeakClaim(AceType::RawPtr(resRegister));
    platformTaskExecutor.PostSyncTask([weakWeb = AceType::WeakClaim(this), weakRes, size, position] {
        auto webDelegate = weakWeb.Upgrade();
        if (webDelegate == nullptr) {
            return;
        }
        auto webPattern = webDelegate->webPattern_.Upgrade();
        if (!webPattern) {
            webDelegate->OnError(WEB_ERROR_CODE_CREATEFAIL, WEB_ERROR_MSG_CREATEFAIL);
            return;
        }
        auto resRegister = weakRes.Upgrade();
        if (!resRegister) {
            webDelegate->OnError(WEB_ERROR_CODE_CREATEFAIL, WEB_ERROR_MSG_CREATEFAIL);
            return;
        }
        auto context = webDelegate->context_.Upgrade();
        if (!context) {
            return;
        }

        std::string pageUrl;
        int32_t pageId;
        OHOS::Ace::Framework::DelegateClient::GetInstance().GetWebPageUrl(pageUrl, pageId);

        std::stringstream paramStream;
        paramStream << NTC_PARAM_WEB << WEB_PARAM_EQUALS << webDelegate->id_ << WEB_PARAM_AND << NTC_PARAM_WIDTH
                    << WEB_PARAM_EQUALS << size.Width() * context->GetViewScale() << WEB_PARAM_AND << NTC_PARAM_HEIGHT
                    << WEB_PARAM_EQUALS << size.Height() * context->GetViewScale() << WEB_PARAM_AND << NTC_PARAM_LEFT
                    << WEB_PARAM_EQUALS << position.GetX() * context->GetViewScale() << WEB_PARAM_AND << NTC_PARAM_TOP
                    << WEB_PARAM_EQUALS << position.GetY() * context->GetViewScale() << WEB_PARAM_AND << NTC_PARAM_SRC
                    << WEB_PARAM_EQUALS << webPattern->GetWebSrc().value_or("") << WEB_PARAM_AND << NTC_PARAM_PAGE_URL
                    << WEB_PARAM_EQUALS << pageUrl;

        std::string param = paramStream.str();
        webDelegate->id_ = resRegister->CreateResource(WEB_CREATE, param);

        if (webDelegate->id_ == INVALID_ID) {
            webDelegate->OnError(WEB_ERROR_CODE_CREATEFAIL, WEB_ERROR_MSG_CREATEFAIL);
            return;
        }
        webDelegate->state_ = State::CREATED;
        webDelegate->hash_ = webDelegate->MakeResourceHash();
        webDelegate->RegisterWebEvent();
        webDelegate->RegisterWebObjectEvent();
    });
}

int WebDelegateCross::GetWebId()
{
    return id_;
}

void WebDelegateCross::RegisterWebEvent()
{
    auto context = DynamicCast<NG::PipelineContext>(context_.Upgrade());
    CHECK_NULL_VOID(context);
    auto resRegister = context->GetPlatformResRegister();
    if (resRegister == nullptr) {
        return;
    }
    resRegister->RegisterEvent(MakeEventHash(WEB_EVENT_PAGESTART), [weak = WeakClaim(this)](const std::string& param) {
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->OnPageStarted(param);
        }
    });
    resRegister->RegisterEvent(MakeEventHash(WEB_EVENT_PAGEFINISH), [weak = WeakClaim(this)](const std::string& param) {
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->OnPageFinished(param);
        }
    });
    resRegister->RegisterEvent(
        MakeEventHash(WEB_EVENT_PAGECHANGED), [weak = WeakClaim(this)](const std::string& param) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->OnProgressChanged(param);
            }
        });
    resRegister->RegisterEvent(MakeEventHash(WEB_EVENT_RECVTITLE), [weak = WeakClaim(this)](const std::string& param) {
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->OnReceivedTitle(param);
        }
    });
}

void WebDelegateCross::RegisterWebObjectEvent()
{
    WebObjectEventManager::GetInstance().RegisterObjectEvent(MakeEventHash(WEB_EVENT_ERRORRECEIVE),
        [weak = WeakClaim(this)](const std::string& param, void* object) {
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->OnErrorReceive(object);
        }
    });
    WebObjectEventManager::GetInstance().RegisterObjectEvent(
        MakeEventHash(WEB_EVENT_SCROLL), [weak = WeakClaim(this)](const std::string& param, void* object) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->OnScroll(object);
            }
        });
    WebObjectEventManager::GetInstance().RegisterObjectEvent(
        MakeEventHash(WEB_EVENT_SCALECHANGE), [weak = WeakClaim(this)](const std::string& param, void* object) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->OnScaleChange(object);
            }
        });
    WebObjectEventManager::GetInstance().RegisterObjectEvent(
        MakeEventHash(WEB_EVENT_ONHTTPERRORRECEIVE), [weak = WeakClaim(this)](const std::string& param, void* object) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->OnHttpErrorReceive(object);
            }
        });
    WebObjectEventManager::GetInstance().RegisterObjectEventWithBoolReturn(MakeEventHash(WEB_EVENT_CONSOLEMESSAGE),
        [weak = WeakClaim(this)](const std::string& param, void* object) -> bool {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->OnConsoleMessage(object);
            }
            return false;
        });
    WebObjectEventManager::GetInstance().RegisterObjectEventWithBoolReturn(MakeEventHash(WEB_EVENT_LOADINTERCEPT),
        [weak = WeakClaim(this)](const std::string& param, void* object) -> bool {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->OnLoadIntercept(object);
            }
            return false;
        });
}

void WebDelegateCross::HandleTouchDown(
    const int32_t& id, const double& x, const double& y, bool from_overlay)
{
    hash_ = MakeResourceHash();
    touchDownMethod_ = MakeMethodHash(WEB_METHOD_TOUCH_DOWN);
    CallResRegisterMethod(touchDownMethod_, "", nullptr);
}

void WebDelegateCross::HandleTouchUp(
    const int32_t& id, const double& x, const double& y, bool from_overlay)
{
    hash_ = MakeResourceHash();
    touchUpMethod_ = MakeMethodHash(WEB_METHOD_TOUCH_UP);
    CallResRegisterMethod(touchUpMethod_, "", nullptr);
}

void WebDelegateCross::HandleTouchMove(
    const int32_t& id, const double& x, const double& y, bool from_overlay)
{
    hash_ = MakeResourceHash();
    touchMoveMethod_ = MakeMethodHash(WEB_METHOD_TOUCH_MOVE);
    CallResRegisterMethod(touchMoveMethod_, "", nullptr);
}

void WebDelegateCross::HandleTouchCancel()
{
    hash_ = MakeResourceHash();
    touchCancelMethod_ = MakeMethodHash(WEB_METHOD_TOUCH_CANCEL);
    CallResRegisterMethod(touchCancelMethod_, "", nullptr);
}

bool WebDelegateCross::OnKeyEvent(int32_t keyCode, int32_t keyAction)
{
    return true;
}

void WebDelegateCross::OnMouseEvent(
    int32_t x, int32_t y, const MouseButton button, const MouseAction action, int count)
{}

void WebDelegateCross::OnFocus()
{}

void WebDelegateCross::OnBlur()
{}

void WebDelegateCross::UpdateLocale()
{}

void WebDelegateCross::OnInactive()
{}

void WebDelegateCross::OnActive()
{}

void WebDelegateCross::ShowWebView()
{}

void WebDelegateCross::HideWebView()
{}

void WebDelegateCross::OnPageStarted(const std::string& param)
{
    ContainerScope scope(instanceId_);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), param]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                auto propOnPageStarted = webEventHub->GetOnPageStartedEvent();
                CHECK_NULL_VOID(propOnPageStarted);
                auto eventParam = std::make_shared<LoadWebPageStartEvent>(param);
                propOnPageStarted(eventParam);
                return;
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegateCross::OnPageFinished(const std::string& param)
{
    ContainerScope scope(instanceId_);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), param]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                auto propOnPageFinished = webEventHub->GetOnPageFinishedEvent();
                CHECK_NULL_VOID(propOnPageFinished);
                auto eventParam = std::make_shared<LoadWebPageFinishEvent>(param);
                propOnPageFinished(eventParam);
                return;
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegateCross::OnPageError(const std::string& param)
{}

void WebDelegateCross::OnProgressChanged(const std::string& param)
{
    ContainerScope scope(instanceId_);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), param]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                auto propOnProgressChange = webEventHub->GetOnProgressChangeEvent();
                CHECK_NULL_VOID(propOnProgressChange);
                auto eventParam = std::make_shared<LoadWebProgressChangeEvent>(atoi(param.c_str()));
                propOnProgressChange(eventParam);
                return;
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegateCross::OnReceivedTitle(const std::string& param)
{
    ContainerScope scope(instanceId_);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), param]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                auto propOnTitleReceive = webEventHub->GetOnTitleReceiveEvent();
                CHECK_NULL_VOID(propOnTitleReceive);
                auto eventParam = std::make_shared<LoadWebTitleReceiveEvent>(param);
                propOnTitleReceive(eventParam);
                return;
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegateCross::OnErrorReceive(void* object)
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(object);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto webResourceRequest = AceType::MakeRefPtr<WebResourceRequsetImpl>(object);
    CHECK_NULL_VOID(webResourceRequest);
    auto webResourceError = AceType::MakeRefPtr<WebResourceErrorImpl>(object);
    CHECK_NULL_VOID(webResourceError);
    auto requestHeader = webResourceRequest->GetRequestHeader();
    auto method = webResourceRequest->GetMethod();
    auto url = webResourceRequest->GetRequestUrl();
    auto hasGesture = webResourceRequest->IsRequestGesture();
    auto isMainFrame = webResourceRequest->IsMainFrame();
    auto isRedirect = webResourceRequest->IsRedirect();
    auto request = AceType::MakeRefPtr<WebRequest>(requestHeader, method, url, hasGesture, isMainFrame, isRedirect);
    auto errorInfo = webResourceError->GetErrorInfo();
    auto errorCode = webResourceError->GetErrorCode();
    auto error = AceType::MakeRefPtr<WebError>(errorInfo, errorCode);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), request, error]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                auto propOnErrorReceive = webEventHub->GetOnErrorReceiveEvent();
                CHECK_NULL_VOID(propOnErrorReceive);
                auto eventParam = std::make_shared<ReceivedErrorEvent>(request, error);
                propOnErrorReceive(eventParam);
                return;
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegateCross::OnScroll(void* object)
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(object);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto webScrollOffset = AceType::MakeRefPtr<WebOffsetImpl>(object);
    CHECK_NULL_VOID(webScrollOffset);
    auto offsetX = webScrollOffset->GetX();
    auto offsetY = webScrollOffset->GetY();
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), offsetX, offsetY]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                auto propOnScroll = webEventHub->GetOnScrollEvent();
                CHECK_NULL_VOID(propOnScroll);
                auto eventParam = std::make_shared<WebOnScrollEvent>(offsetX, offsetY);
                propOnScroll(eventParam);
                return;
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegateCross::OnScaleChange(void* object)
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(object);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto webScaleChange = AceType::MakeRefPtr<WebScaleChangeImpl>(object);
    CHECK_NULL_VOID(webScaleChange);
    auto newScale = webScaleChange->GetNewScale();
    auto oldScale = webScaleChange->GetOldScale();
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), newScale, oldScale]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                auto propOnScaleChange = webEventHub->GetOnScaleChangeEvent();
                CHECK_NULL_VOID(propOnScaleChange);
                auto eventParam = std::make_shared<ScaleChangeEvent>(oldScale, newScale);
                propOnScaleChange(eventParam);
                return;
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegateCross::OnHttpErrorReceive(void* object)
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(object);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto webResourceRequest = AceType::MakeRefPtr<WebResourceRequsetImpl>(object);
    CHECK_NULL_VOID(webResourceRequest);
    auto webResourceResponse = AceType::MakeRefPtr<WebResourceResponseImpl>(object);
    CHECK_NULL_VOID(webResourceResponse);
    auto requestHeader = webResourceRequest->GetRequestHeader();
    auto method = webResourceRequest->GetMethod();
    auto url = webResourceRequest->GetRequestUrl();
    auto hasGesture = webResourceRequest->IsRequestGesture();
    auto isMainFrame = webResourceRequest->IsMainFrame();
    auto isRedirect = webResourceRequest->IsRedirect();
    auto request = AceType::MakeRefPtr<WebRequest>(requestHeader, method, url, hasGesture, isMainFrame, isRedirect);
    auto responseHeader = webResourceResponse->GetResponseHeader();
    auto responseDate = webResourceResponse->GetResponseData();
    auto encoding = webResourceResponse->GetEncoding();
    auto mimeType = webResourceResponse->GetMimeType();
    auto reason = webResourceResponse->GetReason();
    auto statusCode = webResourceResponse->GetStatusCode();
    auto response =
        AceType::MakeRefPtr<WebResponse>(responseHeader, responseDate, encoding, mimeType, reason, statusCode);

    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), request, response]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                auto propOnHttpErrorReceive = webEventHub->GetOnHttpErrorReceiveEvent();
                CHECK_NULL_VOID(propOnHttpErrorReceive);
                auto eventParam = std::make_shared<ReceivedHttpErrorEvent>(request, response);
                propOnHttpErrorReceive(eventParam);
                return;
            }
        },
        TaskExecutor::TaskType::JS);
}

bool WebDelegateCross::OnConsoleMessage(void* object)
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_RETURN(object, false);
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    bool result = false;
    auto webConsoleMessage = AceType::MakeRefPtr<WebConsoleMessage>(object);
    CHECK_NULL_RETURN(webConsoleMessage, false);
    auto message = webConsoleMessage->GetMessage();
    auto sourceId = webConsoleMessage->GetSourceId();
    auto lineNumber = webConsoleMessage->GetLineNumber();
    auto messageLevel = webConsoleMessage->GetMessageLevel();
    auto consoleMessageParam = AceType::MakeRefPtr<WebConsoleMessageParam>(message, sourceId, lineNumber, messageLevel);

    context->GetTaskExecutor()->PostSyncTask(
        [weak = WeakClaim(this), consoleMessageParam, &result]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                auto propOnConsole = webEventHub->GetOnConsoleEvent();
                CHECK_NULL_VOID(propOnConsole);
                auto eventParam = std::make_shared<LoadWebConsoleLogEvent>(consoleMessageParam);
                result = propOnConsole(eventParam);
                return;
            }
        },
        TaskExecutor::TaskType::JS);
    return result;
}
bool WebDelegateCross::OnLoadIntercept(void* object)
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_RETURN(object, false);
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    bool result = false;
    auto webResourceRequest = AceType::MakeRefPtr<WebResourceRequsetImpl>(object);
    CHECK_NULL_RETURN(webResourceRequest, false);
    auto requestHeader = webResourceRequest->GetRequestHeader();
    auto method = webResourceRequest->GetMethod();
    auto url = webResourceRequest->GetRequestUrl();
    auto hasGesture = webResourceRequest->IsRequestGesture();
    auto isMainFrame = webResourceRequest->IsMainFrame();
    auto isRedirect = webResourceRequest->IsRedirect();
    auto request = AceType::MakeRefPtr<WebRequest>(requestHeader, method, url, hasGesture, isMainFrame, isRedirect);

    context->GetTaskExecutor()->PostSyncTask(
        [weak = WeakClaim(this), request, &result]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                auto propOnLoadIntercept = webEventHub->GetOnLoadInterceptEvent();
                CHECK_NULL_VOID(propOnLoadIntercept);
                auto eventParam = std::make_shared<LoadInterceptEvent>(request);
                result = propOnLoadIntercept(eventParam);
                return;
            }
        },
        TaskExecutor::TaskType::JS);
    return result;
}

void WebDelegateCross::UpdateUserAgent(const std::string& userAgent) {}

void WebDelegateCross::UpdateBackgroundColor(const int backgroundColor)
{
    hash_ = MakeResourceHash();
    updateBackgroundColor_ = MakeMethodHash(WEB_ATTRIBUTE_BACKGROUND_COLOR);
    std::stringstream paramStream;
    paramStream << NTC_BACKGROUND_COLOR << WEB_PARAM_EQUALS << backgroundColor;
    std::string param = paramStream.str();
    CallResRegisterMethod(updateBackgroundColor_, param, nullptr);
}

void WebDelegateCross::UpdateInitialScale(float scale) {}
void WebDelegateCross::UpdateJavaScriptEnabled(const bool& isJsEnabled)
{
    hash_ = MakeResourceHash();
    updateJavaScriptEnabled_ = MakeMethodHash(WEB_ATTRIBUTE_JAVASCRIPT_ACCESS);
    std::stringstream paramStream;
    paramStream << NTC_JAVASCRIPT_ACCESS << WEB_PARAM_EQUALS << isJsEnabled;
    std::string param = paramStream.str();
    CallResRegisterMethod(updateJavaScriptEnabled_, param, nullptr);
}

void WebDelegateCross::UpdateAllowFileAccess(const bool& isFileAccessEnabled) {}
void WebDelegateCross::UpdateBlockNetworkImage(const bool& onLineImageAccessEnabled) {}
void WebDelegateCross::UpdateLoadsImagesAutomatically(const bool& isImageAccessEnabled) {}
void WebDelegateCross::UpdateMixedContentMode(const MixedModeContent& mixedMode) {}

void WebDelegateCross::UpdateSupportZoom(const bool& isZoomAccessEnabled)
{
    hash_ = MakeResourceHash();
    updateZoomAccess_ = MakeMethodHash(WEB_ATTRIBUTE_ZOOM_ACCESS);
    std::stringstream paramStream;
    paramStream << NTC_ZOOM_ACCESS << WEB_PARAM_EQUALS << isZoomAccessEnabled;
    std::string param = paramStream.str();
    CallResRegisterMethod(updateZoomAccess_, param, nullptr);
}

void WebDelegateCross::UpdateDomStorageEnabled(const bool& isDomStorageAccessEnabled)
{}

void WebDelegateCross::UpdateGeolocationEnabled(const bool& isGeolocationAccessEnabled)
{}

void WebDelegateCross::UpdateCacheMode(const WebCacheMode& mode)
{}

void WebDelegateCross::UpdateDarkMode(const WebDarkMode& mode)
{}

void WebDelegateCross::UpdateForceDarkAccess(const bool& access)
{}

void WebDelegateCross::UpdateAudioResumeInterval(const int32_t& resumeInterval)
{}

void WebDelegateCross::UpdateAudioExclusive(const bool& audioExclusive)
{}

void WebDelegateCross::UpdateOverviewModeEnabled(const bool& isOverviewModeAccessEnabled)
{}

void WebDelegateCross::UpdateFileFromUrlEnabled(const bool& isFileFromUrlAccessEnabled)
{}

void WebDelegateCross::UpdateDatabaseEnabled(const bool& isDatabaseAccessEnabled)
{}

void WebDelegateCross::UpdateTextZoomRatio(const int32_t& textZoomRatioNum)
{}

void WebDelegateCross::UpdateWebDebuggingAccess(bool isWebDebuggingAccessEnabled)
{}

void WebDelegateCross::UpdatePinchSmoothModeEnabled(bool isPinchSmoothModeEnabled)
{}

void WebDelegateCross::UpdateMediaPlayGestureAccess(bool isNeedGestureAccess)
{
    hash_ = MakeResourceHash();
    updateMediaPlayGestureAccess_ = MakeMethodHash(WEB_ATTRIBUTE_MEDIA_PLAY_GESTURE_ACCESS);
    std::stringstream paramStream;
    paramStream << NTC_MEDIA_PLAY_GESTURE_ACCESS << WEB_PARAM_EQUALS << isNeedGestureAccess;
    std::string param = paramStream.str();
    CallResRegisterMethod(updateMediaPlayGestureAccess_, param, nullptr);
}

void WebDelegateCross::UpdateMultiWindowAccess(bool isMultiWindowAccessEnabled)
{}

void WebDelegateCross::UpdateAllowWindowOpenMethod(bool isAllowWindowOpenMethod)
{}

void WebDelegateCross::UpdateWebCursiveFont(const std::string& cursiveFontFamily)
{}

void WebDelegateCross::UpdateWebFantasyFont(const std::string& fantasyFontFamily)
{}

void WebDelegateCross::UpdateWebFixedFont(const std::string& fixedFontFamily)
{}

void WebDelegateCross::UpdateWebSansSerifFont(const std::string& sansSerifFontFamily)
{}

void WebDelegateCross::UpdateWebSerifFont(const std::string& serifFontFamily)
{}

void WebDelegateCross::UpdateWebStandardFont(const std::string& standardFontFamily)
{}

void WebDelegateCross::UpdateDefaultFixedFontSize(int32_t size)
{}

void WebDelegateCross::UpdateDefaultFontSize(int32_t defaultFontSize)
{}

void WebDelegateCross::UpdateMinFontSize(int32_t minFontSize)
{
    hash_ = MakeResourceHash();
    updateMinFontSize_ = MakeMethodHash(WEB_ATTRIBUTE_MIN_FONT_SIZE);
    std::stringstream paramStream;
    paramStream << NTC_MIN_FONT_SIZE << WEB_PARAM_EQUALS << std::clamp(minFontSize, FONT_MIN_SIZE, FONT_MAX_SIZE);
    std::string param = paramStream.str();
    CallResRegisterMethod(updateMinFontSize_, param, nullptr);
}

void WebDelegateCross::UpdateMinLogicalFontSize(int32_t minLogicalFontSize)
{}

void WebDelegateCross::UpdateBlockNetwork(bool isNetworkBlocked)
{}

void WebDelegateCross::UpdateHorizontalScrollBarAccess(bool isHorizontalScrollBarAccessEnabled)
{
    hash_ = MakeResourceHash();
    updateHorizontalScrollBarAccess_ = MakeMethodHash(WEB_ATTRIBUTE_HORIZONTAL_SCROLLBAR_ACCESS);
    std::stringstream paramStream;
    paramStream << NTC_HORIZONTAL_SCROLLBAR_ACCESS << WEB_PARAM_EQUALS << isHorizontalScrollBarAccessEnabled;
    std::string param = paramStream.str();
    CallResRegisterMethod(updateHorizontalScrollBarAccess_, param, nullptr);
}

void WebDelegateCross::UpdateVerticalScrollBarAccess(bool isVerticalScrollBarAccessEnabled)
{
    hash_ = MakeResourceHash();
    updateVerticalScrollBarAccess_ = MakeMethodHash(WEB_ATTRIBUTE_VERTICAL_SCROLLBAR_ACCESS);
    std::stringstream paramStream;
    paramStream << NTC_VERTICAL_SCROLLBAR_ACCESS << WEB_PARAM_EQUALS << isVerticalScrollBarAccessEnabled;
    std::string param = paramStream.str();
    CallResRegisterMethod(updateVerticalScrollBarAccess_, param, nullptr);
}

void WebDelegateCross::UpdateScrollBarColor(const std::string& colorValue)
{}

void WebDelegateCross::LoadUrl()
{}

bool WebDelegateCross::LoadDataWithRichText()
{}

void WebDelegateCross::SetBackgroundColor(int32_t backgroundColor)
{}

void WebDelegateCross::SetBoundsOrResize(const Size& drawSize, const Offset& offset)
{
    hash_ = MakeResourceHash();
    updateLayoutMethod_ = MakeMethodHash(WEB_METHOD_UPDATE_LAYOUT);
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    std::stringstream paramStream;
    float viewScale = context->GetViewScale();
    paramStream << NTC_PARAM_WIDTH << WEB_PARAM_EQUALS
                << drawSize.Width() * viewScale << WEB_PARAM_AND
                << NTC_PARAM_HEIGHT << WEB_PARAM_EQUALS
                << drawSize.Height() * viewScale << WEB_PARAM_AND
                << NTC_PARAM_LEFT << WEB_PARAM_EQUALS
                << offset.GetX() * viewScale << WEB_PARAM_AND
                << NTC_PARAM_TOP << WEB_PARAM_EQUALS
                << offset.GetY() * viewScale;
    std::string param = paramStream.str();
    CallResRegisterMethod(updateLayoutMethod_, param, nullptr);
}

void WebDelegateCross::SetDrawRect(int32_t x, int32_t y, int32_t width, int32_t height)
{
    // cross platform is not support now;
}
}
