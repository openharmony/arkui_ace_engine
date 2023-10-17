/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/web/resource/web_delegate.h"

#include <algorithm>
#include <iomanip>
#include <optional>
#include <sstream>

#include "base/json/json_util.h"
#include "base/log/log.h"
#include "base/log/ace_trace.h"
#include "base/memory/referenced.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/web/render_web.h"
#include "core/components/web/web_event.h"
#include "core/components/web/web_property.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/rosen_render_surface.h"
#endif
#include "core/event/ace_event_helper.h"
#include "core/event/ace_events.h"
#include "core/event/back_end_event_manager.h"
#include "frameworks/bridge/js_frontend/frontend_delegate_impl.h"
#include "core/common/ace_application_info.h"
#ifdef OHOS_STANDARD_SYSTEM
#include "application_env.h"
#include "nweb_adapter_helper.h"
#include "nweb_handler.h"
#include "parameters.h"
#include "web_configuration_observer.h"
#include "web_javascript_execute_callback.h"
#include "web_javascript_result_callback.h"
#endif

namespace OHOS::Ace {

namespace {

constexpr char WEB_METHOD_ROUTER_BACK[] = "routerBack";
constexpr char WEB_METHOD_UPDATEURL[] = "updateUrl";
constexpr char WEB_METHOD_CHANGE_PAGE_URL[] = "changePageUrl";
constexpr char WEB_METHOD_PAGE_PATH_INVALID[] = "pagePathInvalid";
constexpr char WEB_EVENT_PAGESTART[] = "onPageStarted";
constexpr char WEB_EVENT_PAGEFINISH[] = "onPageFinished";
constexpr char WEB_EVENT_PAGEERROR[] = "onPageError";
constexpr char WEB_EVENT_ONMESSAGE[] = "onMessage";
constexpr char WEB_EVENT_ROUTERPUSH[] = "routerPush";

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

const std::string RESOURCE_VIDEO_CAPTURE = "TYPE_VIDEO_CAPTURE";
const std::string RESOURCE_AUDIO_CAPTURE = "TYPE_AUDIO_CAPTURE";
const std::string RESOURCE_PROTECTED_MEDIA_ID = "TYPE_PROTECTED_MEDIA_ID";
const std::string RESOURCE_MIDI_SYSEX = "TYPE_MIDI_SYSEX";

constexpr uint32_t DESTRUCT_DELAY_MILLISECONDS = 1000;
} // namespace

#define EGLCONFIG_VERSION 3

void WebMessagePortOhos::SetPortHandle(std::string& handle)
{
    handle_ = handle;
}

std::string WebMessagePortOhos::GetPortHandle()
{
    return handle_;
}

void WebMessagePortOhos::Close()
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        LOGE("delegate its null");
        return;
    }
    delegate->ClosePort(handle_);
}

void WebMessagePortOhos::PostMessage(std::string& data)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        LOGE("delegate its null");
        return;
    }
    delegate->PostPortMessage(handle_, data);
}

void WebMessagePortOhos::SetWebMessageCallback(std::function<void(const std::string&)>&& callback)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        LOGE("delegate its null");
        return;
    }
    delegate->SetPortMessageCallback(handle_, std::move(callback));
}

int ConsoleLogOhos::GetLineNumber()
{
    if (message_) {
        return message_->LineNumer();
    }
    return -1;
}

std::string ConsoleLogOhos::GetLog()
{
    if (message_) {
        return message_->Log();
    }
    return "";
}

int ConsoleLogOhos::GetLogLevel()
{
    if (message_) {
        return message_->LogLevel();
    }
    return -1;
}

std::string ConsoleLogOhos::GetSourceId()
{
    if (message_) {
        return message_->SourceId();
    }
    return "";
}

void ResultOhos::Confirm()
{
    if (result_) {
        result_->Confirm();
    }
}

void ResultOhos::Confirm(const std::string& message)
{
    if (result_) {
        result_->Confirm(message);
    }
}

void ResultOhos::Cancel()
{
    if (result_) {
        result_->Cancel();
    }
}

void FullScreenExitHandlerOhos::ExitFullScreen()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    CHECK_NULL_VOID(handler_);
    if (Container::IsCurrentUseNewPipeline()) {
        // notify chromium to exit fullscreen mode.
        handler_->ExitFullScreen();
        // notify web component in arkui to exit fullscreen mode.
        delegate->ExitFullScreen();
    }
}

bool AuthResultOhos::Confirm(std::string& userName, std::string& pwd)
{
    if (result_) {
        return result_->Confirm(userName, pwd);
    }
    return false;
}

bool AuthResultOhos::IsHttpAuthInfoSaved()
{
    if (result_) {
        return result_->IsHttpAuthInfoSaved();
    }
    return false;
}

void AuthResultOhos::Cancel()
{
    if (result_) {
        result_->Cancel();
    }
}

void SslErrorResultOhos::HandleConfirm()
{
    if (result_) {
        result_->HandleConfirm();
    }
}

void SslErrorResultOhos::HandleCancel()
{
    if (result_) {
        result_->HandleCancel();
    }
}

void SslSelectCertResultOhos::HandleConfirm(const std::string& privateKeyFile, const std::string& certChainFile)
{
    if (result_) {
        result_->Confirm(privateKeyFile, certChainFile);
    }
}

void SslSelectCertResultOhos::HandleCancel()
{
    if (result_) {
        result_->Cancel();
    }
}

void SslSelectCertResultOhos::HandleIgnore()
{
    if (result_) {
        result_->Ignore();
    }
}

std::string FileSelectorParamOhos::GetTitle()
{
    if (param_) {
        return param_->Title();
    }
    return "";
}

int FileSelectorParamOhos::GetMode()
{
    if (param_) {
        return param_->Mode();
    }
    return 0;
}

std::string FileSelectorParamOhos::GetDefaultFileName()
{
    if (param_) {
        return param_->DefaultFilename();
    }
    return "";
}

std::vector<std::string> FileSelectorParamOhos::GetAcceptType()
{
    if (param_) {
        return param_->AcceptType();
    }
    return std::vector<std::string>();
}

bool FileSelectorParamOhos::IsCapture()
{
    if (param_) {
        return param_->IsCapture();
    }
    return false;
}

void FileSelectorResultOhos::HandleFileList(std::vector<std::string>& result)
{
    if (callback_) {
        callback_->OnReceiveValue(result);
    }
}

void WebPermissionRequestOhos::Deny() const
{
    if (request_) {
        request_->Refuse();
    }
}

std::string WebPermissionRequestOhos::GetOrigin() const
{
    if (request_) {
        return request_->Origin();
    }
    return "";
}

std::vector<std::string> WebPermissionRequestOhos::GetResources() const
{
    std::vector<std::string> resources;
    if (request_) {
        uint32_t resourcesId = static_cast<uint32_t>(request_->ResourceAcessId());
        if (resourcesId & OHOS::NWeb::NWebAccessRequest::Resources::VIDEO_CAPTURE) {
            resources.push_back(RESOURCE_VIDEO_CAPTURE);
        }
        if (resourcesId & OHOS::NWeb::NWebAccessRequest::Resources::AUDIO_CAPTURE) {
            resources.push_back(RESOURCE_AUDIO_CAPTURE);
        }
        if (resourcesId & OHOS::NWeb::NWebAccessRequest::Resources::PROTECTED_MEDIA_ID) {
            resources.push_back(RESOURCE_PROTECTED_MEDIA_ID);
        }
        if (resourcesId & OHOS::NWeb::NWebAccessRequest::Resources::MIDI_SYSEX) {
            resources.push_back(RESOURCE_MIDI_SYSEX);
        }
    }
    return resources;
}

void WebPermissionRequestOhos::Grant(std::vector<std::string>& resources) const
{
    if (request_) {
        uint32_t resourcesId = 0;
        for (auto res : resources) {
            if (res == RESOURCE_VIDEO_CAPTURE) {
                resourcesId |= OHOS::NWeb::NWebAccessRequest::Resources::VIDEO_CAPTURE;
            } else if (res == RESOURCE_AUDIO_CAPTURE) {
                resourcesId |= OHOS::NWeb::NWebAccessRequest::Resources::AUDIO_CAPTURE;
            } else if (res == RESOURCE_PROTECTED_MEDIA_ID) {
                resourcesId |= OHOS::NWeb::NWebAccessRequest::Resources::PROTECTED_MEDIA_ID;
            } else if (res == RESOURCE_MIDI_SYSEX) {
                resourcesId |= OHOS::NWeb::NWebAccessRequest::Resources::MIDI_SYSEX;
            }
        }
        request_->Agree(resourcesId);
    }
}

void WebScreenCaptureRequestOhos::Deny() const
{
    if (request_) {
        request_->Refuse();
    }
}

std::string WebScreenCaptureRequestOhos::GetOrigin() const
{
    if (request_) {
        return request_->Origin();
    }
    return "";
}

void WebScreenCaptureRequestOhos::SetCaptureMode(int32_t mode)
{
    config_.mode = mode;
}

void WebScreenCaptureRequestOhos::SetSourceId(int32_t sourceId)
{
    config_.sourceId = sourceId;
}

void WebScreenCaptureRequestOhos::Grant() const
{
    if (request_) {
        request_->Agree(config_);
    }
}

int32_t ContextMenuParamOhos::GetXCoord() const
{
    if (param_) {
        return param_->GetXCoord();
    }
    return -1;
}

int32_t ContextMenuParamOhos::GetYCoord() const
{
    if (param_) {
        return param_->GetYCoord();
    }
    return -1;
}

std::string ContextMenuParamOhos::GetLinkUrl() const
{
    if (param_) {
        return param_->GetLinkUrl();
    }
    return "";
}

std::string ContextMenuParamOhos::GetUnfilteredLinkUrl() const
{
    if (param_) {
        return param_->GetUnfilteredLinkUrl();
    }
    return "";
}

std::string ContextMenuParamOhos::GetSourceUrl() const
{
    if (param_) {
        return param_->GetSourceUrl();
    }
    return "";
}

bool ContextMenuParamOhos::HasImageContents() const
{
    if (param_) {
        return param_->HasImageContents();
    }
    return false;
}

bool ContextMenuParamOhos::IsEditable() const
{
    if (param_) {
        return param_->IsEditable();
    }
    return false;
}

int ContextMenuParamOhos::GetEditStateFlags() const
{
    if (param_) {
        return param_->GetEditStateFlags();
    }
    return OHOS::NWeb::NWebContextMenuParams::ContextMenuEditStateFlags::CM_ES_NONE;
}

int ContextMenuParamOhos::GetSourceType() const
{
    if (param_) {
        return param_->GetSourceType();
    }
    return OHOS::NWeb::NWebContextMenuParams::ContextMenuSourceType::CM_ST_NONE;
}

int ContextMenuParamOhos::GetMediaType() const
{
    if (param_) {
        return param_->GetMediaType();
    }
    return OHOS::NWeb::NWebContextMenuParams::ContextMenuMediaType::CM_MT_NONE;
}

int ContextMenuParamOhos::GetInputFieldType() const
{
    if (param_) {
        return param_->GetInputFieldType();
    }
    return OHOS::NWeb::NWebContextMenuParams::ContextMenuInputFieldType::CM_IT_NONE;
}

std::string ContextMenuParamOhos::GetSelectionText() const
{
    if (param_) {
        return param_->GetSelectionText();
    }
    return "";
}

void ContextMenuResultOhos::Cancel() const
{
    if (callback_) {
        callback_->Cancel();
    }
}

void ContextMenuResultOhos::CopyImage() const
{
    if (callback_) {
        callback_->Continue(CI_IMAGE_COPY, EF_NONE);
    }
}

void ContextMenuResultOhos::Copy() const
{
    if (callback_) {
        callback_->Continue(CI_COPY, EF_NONE);
    }
}

void ContextMenuResultOhos::Paste() const
{
    if (callback_) {
        callback_->Continue(CI_PASTE, EF_NONE);
    }
}

void ContextMenuResultOhos::Cut() const
{
    if (callback_) {
        callback_->Continue(CI_CUT, EF_NONE);
    }
}

void ContextMenuResultOhos::SelectAll() const
{
    if (callback_) {
        callback_->Continue(CI_SELECT_ALL, EF_NONE);
    }
}

void WebWindowNewHandlerOhos::SetWebController(int32_t id)
{
    if (handler_) {
        handler_->SetNWebHandlerById(id);
    }
}

bool WebWindowNewHandlerOhos::IsFrist() const
{
    if (handler_) {
        return handler_->IsFrist();
    }
    return true;
}

int32_t WebWindowNewHandlerOhos::GetId() const
{
    if (handler_) {
        return handler_->GetId();
    }
    return -1;
}

int32_t WebWindowNewHandlerOhos::GetParentNWebId() const
{
    return parentNWebId_;
}

void DataResubmittedOhos::Resend()
{
    if (handler_) {
        handler_->Resend();
    }
}

void DataResubmittedOhos::Cancel()
{
    if (handler_) {
        handler_->Cancel();
    }
}

const void* FaviconReceivedOhos::GetData()
{
    return data_;
}

size_t FaviconReceivedOhos::GetWidth()
{
    return width_;
}

size_t FaviconReceivedOhos::GetHeight()
{
    return height_;
}

int FaviconReceivedOhos::GetColorType()
{
    return static_cast<int>(colorType_);
}

int FaviconReceivedOhos::GetAlphaType()
{
    return static_cast<int>(alphaType_);
}

WebDelegateObserver::~WebDelegateObserver()
{
    LOGI("WebDelegateObserver::~WebDelegateObserver");
}

void WebDelegateObserver::NotifyDestory()
{
    LOGI("WebDelegateObserver::NotifyDestory");
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(
        [weak = WeakClaim(this)]() {
            auto observer = weak.Upgrade();
            CHECK_NULL_VOID(observer);
            if (observer->delegate_) {
                observer->delegate_.Reset();
            }
        },
        TaskExecutor::TaskType::UI, DESTRUCT_DELAY_MILLISECONDS);
}

WebDelegate::~WebDelegate()
{
    ReleasePlatformResource();
    if (nweb_) {
        nweb_->UnRegisterScreenLockFunction(GetRosenWindowId());
        nweb_->OnDestroy();
    }
    UnregisterSurfacePositionChangedCallback();
}

void WebDelegate::ReleasePlatformResource()
{
    Stop();
    Release();
}

void WebGeolocationOhos::Invoke(const std::string& origin, const bool& allow, const bool& retain)
{
    if (geolocationCallback_) {
        geolocationCallback_->GeolocationCallbackInvoke(origin, allow, retain);
    }
}

void WebDelegate::Stop()
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGI("fail to get context");
        return;
    }
    auto platformTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::PLATFORM);
    if (platformTaskExecutor.IsRunOnCurrentThread()) {
        UnregisterEvent();
    } else {
        platformTaskExecutor.PostTask([weak = WeakClaim(this)] {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->UnregisterEvent();
            }
        });
    }
}

void WebDelegate::UnregisterEvent()
{
    // TODO: add support for ng.
    auto context = DynamicCast<PipelineContext>(context_.Upgrade());
    if (!context) {
        LOGI("fail to get context");
        return;
    }
    auto resRegister = context->GetPlatformResRegister();
    if (resRegister == nullptr) {
        return;
    }
    resRegister->UnregisterEvent(MakeEventHash(WEB_EVENT_PAGESTART));
    resRegister->UnregisterEvent(MakeEventHash(WEB_EVENT_PAGEFINISH));
    resRegister->UnregisterEvent(MakeEventHash(WEB_EVENT_PAGEERROR));
    resRegister->UnregisterEvent(MakeEventHash(WEB_EVENT_ROUTERPUSH));
    resRegister->UnregisterEvent(MakeEventHash(WEB_EVENT_ONMESSAGE));
}

void WebDelegate::SetRenderWeb(const WeakPtr<RenderWeb>& renderWeb)
{
    renderWeb_ = renderWeb;
}

void WebDelegate::CreatePlatformResource(
    const Size& size, const Offset& position, const WeakPtr<PipelineContext>& context)
{
    ReleasePlatformResource();
    context_ = context;
    CreatePluginResource(size, position, context);

    auto reloadCallback = [weak = WeakClaim(this)]() {
        auto delegate = weak.Upgrade();
        if (!delegate) {
            return false;
        }
        delegate->Reload();
        return true;
    };
    WebClient::GetInstance().RegisterReloadCallback(reloadCallback);

    auto updateUrlCallback = [weak = WeakClaim(this)](const std::string& url) {
        auto delegate = weak.Upgrade();
        if (!delegate) {
            return false;
        }
        delegate->UpdateUrl(url);
        return true;
    };
    WebClient::GetInstance().RegisterUpdageUrlCallback(updateUrlCallback);
    InitWebEvent();
}

void WebDelegate::LoadUrl(const std::string& url, const std::map<std::string, std::string>& httpHeaders)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), url, httpHeaders]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->Load(
                    const_cast<std::string&>(url), const_cast<std::map<std::string, std::string>&>(httpHeaders));
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

#ifdef OHOS_STANDARD_SYSTEM
void WebDelegate::Backward()
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Get context failed, it is null.");
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                LOGE("Get delegate failed, it is null.");
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->NavigateBack();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::Forward()
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Get context failed, it is null.");
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                LOGE("Get delegate failed, it is null.");
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->NavigateForward();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::ClearHistory()
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Get context failed, it is null.");
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                LOGE("Get delegate failed, it is null.");
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->DeleteNavigateHistory();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::ClearSslCache()
{
    LOGE("WebDelegate ClearSslCache");
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Get context failed, it is null.");
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                LOGE("Get delegate failed, it is null.");
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->ClearSslCache();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::ClearClientAuthenticationCache()
{
    LOGE("WebDelegate::ClearClientAuthenticationCache");
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Get context failed, it is null.");
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                LOGE("Get delegate failed, it is null.");
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->ClearClientAuthenticationCache();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

bool WebDelegate::AccessStep(int32_t step)
{
    auto delegate = WeakClaim(this).Upgrade();
    if (!delegate) {
        LOGE("Get delegate failed, it is null.");
        return false;
    }
    if (delegate->nweb_) {
        return delegate->nweb_->CanNavigateBackOrForward(step);
    }
    return false;
}

void WebDelegate::BackOrForward(int32_t step)
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Get context failed, it is null.");
        return;
    }

    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), step] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                LOGE("Get delegate failed, it is null.");
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->NavigateBackOrForward(step);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

bool WebDelegate::AccessBackward()
{
    auto delegate = WeakClaim(this).Upgrade();
    if (!delegate) {
        LOGE("Get delegate failed, it is null.");
        return false;
    }
    if (delegate->nweb_) {
        return delegate->nweb_->IsNavigatebackwardAllowed();
    }
    return false;
}

bool WebDelegate::AccessForward()
{
    auto delegate = WeakClaim(this).Upgrade();
    if (!delegate) {
        LOGE("Get delegate failed, it is null.");
        return false;
    }
    if (delegate->nweb_) {
        return delegate->nweb_->IsNavigateForwardAllowed();
    }
    return false;
}

#endif

void WebDelegate::ExecuteTypeScript(const std::string& jscode, const std::function<void(const std::string)>&& callback)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), jscode, callback]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                auto callbackImpl = std::make_shared<WebJavaScriptExecuteCallBack>(Container::CurrentId());
                if (callbackImpl && callback) {
                    callbackImpl->SetCallBack([weak, func = std::move(callback)](std::string result) {
                        auto delegate = weak.Upgrade();
                        if (!delegate) {
                            return;
                        }
                        auto context = delegate->context_.Upgrade();
                        if (context) {
                            context->GetTaskExecutor()->PostTask(
                                [callback = std::move(func), result]() { callback(result); },
                                TaskExecutor::TaskType::JS);
                        }
                    });
                }
                delegate->nweb_->ExecuteJavaScript(jscode, callbackImpl, false);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::LoadDataWithBaseUrl(const std::string& baseUrl, const std::string& data, const std::string& mimeType,
    const std::string& encoding, const std::string& historyUrl)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), baseUrl, data, mimeType, encoding, historyUrl]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                if (baseUrl.empty() && historyUrl.empty()) {
                    delegate->nweb_->LoadWithData(data, mimeType, encoding);
                } else {
                    delegate->nweb_->LoadWithDataAndBaseUrl(baseUrl, data, mimeType, encoding, historyUrl);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

bool WebDelegate::LoadDataWithRichText()
{
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_RETURN(webPattern, false);
        auto webData = webPattern->GetWebData();
        CHECK_NULL_RETURN(webData, false);
        const std::string& data = webData.value();
        if (data.empty()) {
            return false;
        }

        context->GetTaskExecutor()->PostTask(
            [weak = WeakClaim(this), data]() {
                auto delegate = weak.Upgrade();
                if (!delegate) {
                    return;
                }
                if (delegate->nweb_) {
                    delegate->nweb_->LoadWithDataAndBaseUrl("", data, "", "", "");
                }
            },
            TaskExecutor::TaskType::PLATFORM);
        return true;
    }

    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_RETURN(webCom, false);
    if (webCom->GetData().empty()) {
        return false;
    }
    const std::string& data = webCom->GetData();
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), data]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->LoadWithDataAndBaseUrl("", data, "", "", "");
            }
        },
        TaskExecutor::TaskType::PLATFORM);
    return true;
}

void WebDelegate::Refresh()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->Reload();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::StopLoading()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->Stop();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::AddJavascriptInterface(const std::string& objectName, const std::vector<std::string>& methodList)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), objectName, methodList]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->RegisterArkJSfunction(objectName, methodList);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}
void WebDelegate::RemoveJavascriptInterface(const std::string& objectName, const std::vector<std::string>& methodList)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), objectName, methodList]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->UnregisterArkJSfunction(objectName, methodList);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::SetWebViewJavaScriptResultCallBack(
    const WebController::JavaScriptCallBackImpl&& javaScriptCallBackImpl)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), javaScriptCallBackImpl]() {
            auto delegate = weak.Upgrade();
            if (delegate == nullptr || delegate->nweb_ == nullptr) {
                return;
            }
            auto webJSResultCallBack = std::make_shared<WebJavaScriptResultCallBack>(Container::CurrentId());
            if (webJSResultCallBack) {
                LOGI("WebDelegate SetWebViewJavaScriptResultCallBack");
                webJSResultCallBack->SetJavaScriptCallBack(std::move(javaScriptCallBackImpl));
                delegate->nweb_->SetNWebJavaScriptResultCallBack(webJSResultCallBack);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::CreateWebMessagePorts(std::vector<RefPtr<WebMessagePort>>& ports)
{
    if (nweb_) {
        std::vector<std::string> portStr;
        nweb_->CreateWebMessagePorts(portStr);
        RefPtr<WebMessagePort> port0 = AceType::MakeRefPtr<WebMessagePortOhos>(WeakClaim(this));
        RefPtr<WebMessagePort> port1 = AceType::MakeRefPtr<WebMessagePortOhos>(WeakClaim(this));
        port0->SetPortHandle(portStr[0]);
        port1->SetPortHandle(portStr[1]);
        ports.push_back(port0);
        ports.push_back(port1);
    }
}

void WebDelegate::PostWebMessage(std::string& message, std::vector<RefPtr<WebMessagePort>>& ports, std::string& uri)
{
    if (nweb_) {
        std::vector<std::string> sendPorts;
        for (RefPtr<WebMessagePort> port : ports) {
            sendPorts.push_back(port->GetPortHandle());
        }
        nweb_->PostWebMessage(message, sendPorts, uri);
    }
}

void WebDelegate::ClosePort(std::string& port)
{
    if (nweb_) {
        nweb_->ClosePort(port);
    }
}

void WebDelegate::PostPortMessage(std::string& port, std::string& data)
{
    if (nweb_) {
        auto webMsg = std::make_shared<OHOS::NWeb::NWebMessage>(NWebValue::Type::NONE);
        webMsg->SetType(NWebValue::Type::STRING);
        webMsg->SetString(data);
        nweb_->PostPortMessage(port, webMsg);
    }
}

void WebDelegate::SetPortMessageCallback(std::string& port, std::function<void(const std::string&)>&& callback)
{
    if (nweb_) {
        auto callbackImpl = std::make_shared<WebMessageValueCallBackImpl>(Container::CurrentId());
        if (callbackImpl && callback) {
            callbackImpl->SetCallBack([weak = WeakClaim(this), func = std::move(callback)](std::string result) {
                auto delegate = weak.Upgrade();
                if (!delegate) {
                    return;
                }
                auto context = delegate->context_.Upgrade();
                if (context) {
                    context->GetTaskExecutor()->PostTask(
                        [callback = std::move(func), result]() { callback(result); }, TaskExecutor::TaskType::JS);
                }
            });
        }
        nweb_->SetPortMessageCallback(port, callbackImpl);
    }
}

void WebDelegate::RequestFocus()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }

            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto eventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(eventHub);
                auto focusHub = eventHub->GetOrCreateFocusHub();
                CHECK_NULL_VOID(focusHub);

                focusHub->RequestFocusImmediately();
            }

            auto webCom = delegate->webComponent_.Upgrade();
            CHECK_NULL_VOID(webCom);
            webCom->RequestFocus();
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::SearchAllAsync(const std::string& searchStr)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), searchStr]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->FindAllAsync(searchStr);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::ClearMatches()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->ClearMatches();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::SearchNext(bool forward)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), forward]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->FindNext(forward);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

int WebDelegate::ConverToWebHitTestType(int hitType)
{
    WebHitTestType webHitType;
    switch (hitType) {
        case OHOS::NWeb::HitTestResult::UNKNOWN_TYPE:
            webHitType = WebHitTestType::UNKNOWN;
            break;
        case OHOS::NWeb::HitTestResult::ANCHOR_TYPE:
            webHitType = WebHitTestType::HTTP;
            break;
        case OHOS::NWeb::HitTestResult::PHONE_TYPE:
            webHitType = WebHitTestType::PHONE;
            break;
        case OHOS::NWeb::HitTestResult::GEO_TYPE:
            webHitType = WebHitTestType::MAP;
            break;
        case OHOS::NWeb::HitTestResult::EMAIL_TYPE:
            webHitType = WebHitTestType::EMAIL;
            break;
        case OHOS::NWeb::HitTestResult::IMAGE_TYPE:
            webHitType = WebHitTestType::IMG;
            break;
        case OHOS::NWeb::HitTestResult::IMAGE_ANCHOR_TYPE:
            webHitType = WebHitTestType::HTTP_IMG;
            break;
        case OHOS::NWeb::HitTestResult::SRC_ANCHOR_TYPE:
            webHitType = WebHitTestType::HTTP;
            break;
        case OHOS::NWeb::HitTestResult::SRC_IMAGE_ANCHOR_TYPE:
            webHitType = WebHitTestType::HTTP_IMG;
            break;
        case OHOS::NWeb::HitTestResult::EDIT_TEXT_TYPE:
            webHitType = WebHitTestType::EDIT;
            break;
        default:
            LOGW("unknow hit test type:%{public}d", static_cast<int>(hitType));
            webHitType = WebHitTestType::UNKNOWN;
            break;
    }
    return static_cast<int>(webHitType);
}

int WebDelegate::GetHitTestResult()
{
    if (nweb_) {
        return ConverToWebHitTestType(nweb_->GetHitTestResult().GetType());
    }
    return static_cast<int>(WebHitTestType::UNKNOWN);
}

void WebDelegate::GetHitTestValue(HitTestResult& result)
{
    if (nweb_) {
        OHOS::NWeb::HitTestResult nwebResult = nweb_->GetHitTestResult();
        result.SetExtraData(nwebResult.GetExtra());
        result.SetHitType(ConverToWebHitTestType(nwebResult.GetType()));
    }
}

int WebDelegate::GetPageHeight()
{
    if (nweb_) {
        return nweb_->ContentHeight();
    }
    return 0;
}

int WebDelegate::GetWebId()
{
    if (nweb_) {
        return nweb_->GetWebId();
    }
    return -1;
}

std::string WebDelegate::GetTitle()
{
    if (nweb_) {
        return nweb_->Title();
    }
    return "";
}

std::string WebDelegate::GetDefaultUserAgent()
{
    if (!nweb_) {
        return "";
    }
    std::shared_ptr<OHOS::NWeb::NWebPreference> setting = nweb_->GetPreference();
    if (!setting) {
        return "";
    }
    return setting->DefaultUserAgent();
}

bool WebDelegate::SaveCookieSync()
{
    if (cookieManager_) {
        return cookieManager_->Store();
    }
    return false;
}

bool WebDelegate::SetCookie(const std::string& url, const std::string& value)
{
    if (cookieManager_) {
        return cookieManager_->SetCookie(url, value);
    }
    return false;
}

std::string WebDelegate::GetCookie(const std::string& url) const
{
    if (cookieManager_) {
        bool isValid = true;
        return cookieManager_->ReturnCookie(url, isValid);
    }
    return "";
}

void WebDelegate::DeleteEntirelyCookie()
{
    if (cookieManager_) {
        cookieManager_->DeleteCookieEntirely(nullptr);
    }
}

void WebDelegate::CreatePluginResource(
    const Size& size, const Offset& position, const WeakPtr<PipelineContext>& context)
{
    state_ = State::CREATING;
    // TODO: add ng pattern.
    auto webCom = webComponent_.Upgrade();
    if (!webCom) {
        LOGI("webCom is null");
        state_ = State::CREATEFAILED;
        OnError(NTC_ERROR, "fail to call WebDelegate::Create due to webComponent is null");
        return;
    }

    auto pipelineContext = context.Upgrade();
    if (!pipelineContext) {
        LOGI("pipelineContext is null");
        state_ = State::CREATEFAILED;
        OnError(NTC_ERROR, "fail to call WebDelegate::Create due to context is null");
        return;
    }
    context_ = context;
    auto platformTaskExecutor =
        SingleTaskExecutor::Make(pipelineContext->GetTaskExecutor(), TaskExecutor::TaskType::PLATFORM);
    auto resRegister = pipelineContext->GetPlatformResRegister();
    auto weakRes = AceType::WeakClaim(AceType::RawPtr(resRegister));
    platformTaskExecutor.PostTask([weakWeb = AceType::WeakClaim(this), weakRes, size, position] {
        auto webDelegate = weakWeb.Upgrade();
        if (webDelegate == nullptr) {
            LOGI("webDelegate is null!");
            return;
        }
        // TODO: add ng pattern.
        auto webCom = webDelegate->webComponent_.Upgrade();
        if (!webCom) {
            LOGI("webCom is null!");
            webDelegate->OnError(NTC_ERROR, "fail to call WebDelegate::SetSrc PostTask");
            return;
        }
        auto resRegister = weakRes.Upgrade();
        if (!resRegister) {
            if (webDelegate->onError_) {
                webDelegate->onError_(WEB_ERROR_CODE_CREATEFAIL, WEB_ERROR_MSG_CREATEFAIL);
            }
            return;
        }
        auto context = webDelegate->context_.Upgrade();
        if (!context) {
            LOGI("context is null");
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
                    << WEB_PARAM_EQUALS << webCom->GetSrc() << WEB_PARAM_AND << NTC_PARAM_PAGE_URL << WEB_PARAM_EQUALS
                    << pageUrl;

        std::string param = paramStream.str();
        webDelegate->id_ = resRegister->CreateResource(WEB_CREATE, param);
        if (webDelegate->id_ == INVALID_ID) {
            if (webDelegate->onError_) {
                webDelegate->onError_(WEB_ERROR_CODE_CREATEFAIL, WEB_ERROR_MSG_CREATEFAIL);
            }
            return;
        }
        webDelegate->state_ = State::CREATED;
        webDelegate->hash_ = webDelegate->MakeResourceHash();
        webDelegate->RegisterWebEvent();
        webDelegate->BindRouterBackMethod();
        webDelegate->BindPopPageSuccessMethod();
        webDelegate->BindIsPagePathInvalidMethod();
    });
}

void WebDelegate::InitWebEvent()
{
    auto webCom = webComponent_.Upgrade();
    if (!webCom) {
        state_ = State::CREATEFAILED;
        OnError(NTC_ERROR, "fail to call WebDelegate::Create due to webComponent is null");
        return;
    }
    auto context = DynamicCast<PipelineContext>(context_.Upgrade());
    if (!context) {
        state_ = State::CREATEFAILED;
        OnError(NTC_ERROR, "fail to call WebDelegate::Create due to webComponent is null");
        return;
    }
    CHECK_NULL_VOID(context);
    if (!webCom->GetPageStartedEventId().IsEmpty()) {
        onPageStarted_ = AceAsyncEvent<void(const std::string&)>::Create(webCom->GetPageStartedEventId(), context);
    }
    if (!webCom->GetPageFinishedEventId().IsEmpty()) {
        onPageFinished_ = AceAsyncEvent<void(const std::string&)>::Create(webCom->GetPageFinishedEventId(), context);
    }
    if (!webCom->GetPageErrorEventId().IsEmpty()) {
        onPageError_ = AceAsyncEvent<void(const std::string&)>::Create(webCom->GetPageErrorEventId(), context);
    }
    if (!webCom->GetMessageEventId().IsEmpty()) {
        onMessage_ = AceAsyncEvent<void(const std::string&)>::Create(webCom->GetMessageEventId(), context);
    }
}

#ifdef OHOS_STANDARD_SYSTEM
void WebDelegate::ShowWebView()
{
    if (window_) {
        window_->Show();
    }

    LOGI("OnContinue webview");
    OnActive();
    OnWebviewShow();
}

void WebDelegate::HideWebView()
{
    if (window_) {
        window_->Hide();
    }

    LOGI("OnPause webview");
    OnInactive();
    OnWebviewHide();
}

void WebDelegate::InitOHOSWeb(const RefPtr<PipelineBase>& context, const RefPtr<NG::RenderSurface>& surface)
{
#ifdef ENABLE_ROSEN_BACKEND
    CHECK_NULL_VOID(context);
    auto rosenRenderSurface = DynamicCast<NG::RosenRenderSurface>(surface);
    if (!rosenRenderSurface) {
        LOGI("source is nullptr, initialize with window");
        if (PrepareInitOHOSWeb(context)) {
            if (!isCreateWebView_) {
#ifndef ENABLE_ROSEN_BACKEND
                InitWebViewWithWindow();
                isCreateWebView_ = true;
#endif
            }
        } else {
            LOGE("prepare init web failed");
        }
        return;
    }
    SetSurface(rosenRenderSurface->GetSurface());
    InitOHOSWeb(context);
#endif
}

bool WebDelegate::PrepareInitOHOSWeb(const WeakPtr<PipelineBase>& context)
{
    ACE_SCOPED_TRACE("PrepareInitOHOSWeb");
    LOGI("PrepareInitOHOSWeb");

    state_ = State::CREATING;
    // obtain hap data path
    auto container = Container::Current();
    if (container == nullptr) {
        LOGE("Fail to get container");
        return false;
    }
    const std::string& bundlePath = container->GetBundlePath();
    const std::string& filesDataPath = container->GetFilesDataPath();
    std::string baseDir = "base";
    std::size_t baseIndex = filesDataPath.find(baseDir);
    if (baseIndex == std::string::npos) {
        LOGE("Fail to parse hap data base path");
        return false;
    }
    std::string dataPath = filesDataPath.substr(0, baseIndex + baseDir.length());
    bundlePath_ = bundlePath;
    bundleDataPath_ = dataPath;
    hapPath_ = container->GetWebHapPath();
    // load webview so
    OHOS::NWeb::NWebHelper::Instance().SetBundlePath(bundlePath_);
    if (!OHOS::NWeb::NWebHelper::Instance().Init()) {
        LOGE("Fail to init NWebHelper");
        return false;
    }
    auto webCom = webComponent_.Upgrade();
    auto webPattern = webPattern_.Upgrade();
    auto eventHub = webPattern ? webPattern->GetWebEventHub() : nullptr;
    auto useNewPipe = Container::IsCurrentUseNewPipeline();
    if (useNewPipe && !webPattern && !eventHub) {
        LOGE("fail to call WebDelegate::Create due to webComponent is null");
        return false;
    }
    if (!useNewPipe && !webCom) {
        LOGE("fail to call WebDelegate::Create due to webComponent is null");
        return false;
    }
    context_ = context;
    RegisterSurfacePositionChangedCallback();
    auto pipelineContext = context.Upgrade();
    if (!pipelineContext) {
        LOGE("fail to call WebDelegate::Create due to context is null");
        return false;
    }
    state_ = State::CREATED;

    SetWebCallBack();
    if (!pipelineContext->GetIsDeclarative()) {
        RegisterOHOSWebEventAndMethord();
    } else {
        auto oldContext = DynamicCast<PipelineContext>(pipelineContext);

        onPageFinishedV2_ = useNewPipe ? eventHub->GetOnPageFinishedEvent()
                                    : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                        webCom->GetPageFinishedEventId(), oldContext);
        onPageStartedV2_ = useNewPipe ? eventHub->GetOnPageStartedEvent()
                                    : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                        webCom->GetPageStartedEventId(), oldContext);
        onTitleReceiveV2_ = useNewPipe ? eventHub->GetOnTitleReceiveEvent()
                                    : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                        webCom->GetTitleReceiveEventId(), oldContext);
        onFullScreenExitV2_ = useNewPipe ? eventHub->GetOnFullScreenExitEvent()
                                        : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                            webCom->GetOnFullScreenExitEventId(), oldContext);
        onGeolocationHideV2_ = useNewPipe ? eventHub->GetOnGeolocationHideEvent()
                                        : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                            webCom->GetGeolocationHideEventId(), oldContext);
        onGeolocationShowV2_ = useNewPipe ? eventHub->GetOnGeolocationShowEvent()
                                        : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                            webCom->GetGeolocationShowEventId(), oldContext);
        onErrorReceiveV2_ = useNewPipe ? eventHub->GetOnErrorReceiveEvent()
                                    : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                        webCom->GetPageErrorEventId(), oldContext);
        onHttpErrorReceiveV2_ = useNewPipe ? eventHub->GetOnHttpErrorReceiveEvent()
                                        : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                            webCom->GetHttpErrorEventId(), oldContext);
        onRequestFocusV2_ = useNewPipe ? eventHub->GetOnRequestFocusEvent()
                                    : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                        webCom->GetRequestFocusEventId(), oldContext);
        onDownloadStartV2_ = useNewPipe ? eventHub->GetOnDownloadStartEvent()
                                        : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                            webCom->GetDownloadStartEventId(), oldContext);
        onRenderExitedV2_ = useNewPipe ? eventHub->GetOnRenderExitedEvent()
                                    : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                        webCom->GetRenderExitedId(), oldContext);
        onRefreshAccessedHistoryV2_ = useNewPipe ? eventHub->GetOnRefreshAccessedHistoryEvent()
                                                : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                                    webCom->GetRefreshAccessedHistoryId(), oldContext);
        onResourceLoadV2_ = useNewPipe ? eventHub->GetOnResourceLoadEvent()
                                    : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                        webCom->GetResourceLoadId(), oldContext);
        onScaleChangeV2_ = useNewPipe ? eventHub->GetOnScaleChangeEvent()
                                    : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                        webCom->GetScaleChangeId(), oldContext);
        onPermissionRequestV2_ = useNewPipe ? eventHub->GetOnPermissionRequestEvent()
                                            : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                                webCom->GetPermissionRequestEventId(), oldContext);
        onSearchResultReceiveV2_ = useNewPipe ? eventHub->GetOnSearchResultReceiveEvent()
                                            : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                                webCom->GetSearchResultReceiveEventId(), oldContext);
        onScrollV2_ = useNewPipe ? eventHub->GetOnScrollEvent()
                                : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                    webCom->GetScrollId(), oldContext);
        onWindowExitV2_ = useNewPipe ? eventHub->GetOnWindowExitEvent()
                                            : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                                webCom->GetWindowExitEventId(), oldContext);
        onPageVisibleV2_ = useNewPipe ? eventHub->GetOnPageVisibleEvent() : nullptr;
        onTouchIconUrlV2_ = useNewPipe ? eventHub->GetOnTouchIconUrlEvent() : nullptr;
        onAudioStateChangedV2_ = GetAudioStateChangedCallback(useNewPipe, eventHub);
        onFirstContentfulPaintV2_ = useNewPipe ? eventHub->GetOnFirstContentfulPaintEvent() : nullptr;
        onOverScrollV2_ = useNewPipe ? eventHub->GetOnOverScrollEvent()
                                            : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                                webCom->GetOverScrollId(), oldContext);
        onScreenCaptureRequestV2_ = useNewPipe ? eventHub->GetOnScreenCaptureRequestEvent() : nullptr;
    }
    return true;
}

void WebSurfaceCallback::OnSurfaceCreated(const sptr<OHOS::Surface>& surface)
{
    LOGI("WebSurfaceCallback::OnSurfaceCreated");
}

void WebSurfaceCallback::OnSurfaceChanged(const sptr<OHOS::Surface>& surface, int32_t width, int32_t height)
{
    auto delegate = delegate_.Upgrade();
    if (!delegate) {
        LOGE("WebSurfaceCallback::OnSurfaceChanged get delegate fail");
        return;
    }
    LOGI("OnSurfaceChanged w:%{public}d, h:%{public}d", width, height);
    delegate->Resize((double)width, (double)height);
}

void WebSurfaceCallback::OnSurfaceDestroyed()
{
    LOGI("WebSurfaceCallback::OnSurfaceDestroyed");
}

EGLConfig WebDelegate::GLGetConfig(int version, EGLDisplay eglDisplay)
{
    int attribList[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };
    EGLConfig configs = NULL;
    int configsNum;
    if (!eglChooseConfig(eglDisplay, attribList, &configs, 1, &configsNum)) {
        LOGE("eglChooseConfig ERROR");
        return NULL;
    }
    return configs;
}

void WebDelegate::GLContextInit(void* window)
{
    if (!window) {
        LOGE("unable to get EGL window.");
        return;
    }
    mEglWindow = static_cast<EGLNativeWindowType>(window);

    // 1. create sharedcontext
    mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        LOGE("unable to get EGL display.");
        return;
    }

    EGLint eglMajVers, eglMinVers;
    if (!eglInitialize(mEGLDisplay, &eglMajVers, &eglMinVers)) {
        mEGLDisplay = EGL_NO_DISPLAY;
        LOGE("unable to initialize display");
        return;
    }

    mEGLConfig = GLGetConfig(EGLCONFIG_VERSION, mEGLDisplay);
    if (mEGLConfig == nullptr) {
        LOGE("GLContextInit config ERROR");
        return;
    }

    // 2. Create EGL Surface from Native Window
    mEGLSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, mEglWindow, nullptr);
    if (mEGLSurface == nullptr) {
        LOGE("eglCreateContext eglSurface is null");
        return;
    }

    // 3. Create EGLContext from
    int attrib3_list[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    mEGLContext = eglCreateContext(mEGLDisplay, mEGLConfig, mSharedEGLContext, attrib3_list);

    if (!eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext)) {
        LOGE("eglMakeCurrent error = %{public}d", eglGetError());
        return;
    }

    glViewport(offset_.GetX(), offset_.GetY(), drawSize_.Width(), drawSize_.Height());
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
    glFinish();
    eglSwapBuffers(mEGLDisplay, mEGLSurface);

    eglDestroySurface(mEGLDisplay, mEGLSurface);
    eglDestroyContext(mEGLDisplay, mEGLContext);
}

bool WebDelegate::InitWebSurfaceDelegate(const WeakPtr<PipelineBase>& context)
{
    auto pipelineContext = context.Upgrade();
    if (!pipelineContext) {
        LOGE("fail to call WebDelegate::InitWebSurfaceDelegate Create due to context is null");
        return false;
    }
    uint32_t windowId = pipelineContext->GetWindowId();
    surfaceDelegate_ = new OHOS::SurfaceDelegate(windowId);
    if (surfaceDelegate_ == nullptr) {
        LOGE("fail to call WebDelegate::InitWebSurfaceDelegate Create surfaceDelegate is null");
        return false;
    }
    surfaceCallback_ = new WebSurfaceCallback(AceType::WeakClaim(this));
    if (surfaceCallback_ == nullptr) {
        LOGE("fail to call WebDelegate::InitWebSurfaceDelegate Create surfaceCallback is null");
        return false;
    }
    surfaceDelegate_->AddSurfaceCallback(surfaceCallback_);
    surfaceDelegate_->CreateSurface();
    SetBoundsOrResize(drawSize_, offset_);
    needResizeAtFirst_ = true;
    auto aNativeSurface = surfaceDelegate_->GetNativeWindow();
    if (aNativeSurface == nullptr) {
        LOGE("fail to call WebDelegate::InitWebSurfaceDelegate Create get NativeWindow is null");
        return false;
    }
    GLContextInit(aNativeSurface);
    surfaceInfo_.window = aNativeSurface;
    return true;
}

void WebDelegate::InitOHOSWeb(const WeakPtr<PipelineBase>& context)
{
    if (!PrepareInitOHOSWeb(context)) {
        LOGE("prepare init web failed");
        return;
    }
    if (!isCreateWebView_) {
        isCreateWebView_ = true;
        if (isEnhanceSurface_) {
            if (!InitWebSurfaceDelegate(context)) {
                LOGE("init web surfacedelegate failed");
                return;
            }
            InitWebViewWithSurface();
        } else {
#ifdef ENABLE_ROSEN_BACKEND
            InitWebViewWithSurface();
#else
            InitWebViewWithWindow();
#endif
        }
    }
}
void WebDelegate::RegisterOHOSWebEventAndMethord()
{
    auto reloadCallback = [weak = WeakClaim(this)]() {
        auto delegate = weak.Upgrade();
        if (!delegate) {
            return false;
        }
        delegate->Reload();
        return true;
    };
    WebClient::GetInstance().RegisterReloadCallback(reloadCallback);

    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_VOID(webCom);
    auto context = DynamicCast<PipelineContext>(context_.Upgrade());
    CHECK_NULL_VOID(context);
    if (!webCom->GetPageStartedEventId().IsEmpty()) {
        onPageStarted_ = AceAsyncEvent<void(const std::string&)>::Create(webCom->GetPageStartedEventId(), context);
    }
    if (!webCom->GetPageFinishedEventId().IsEmpty()) {
        onPageFinished_ = AceAsyncEvent<void(const std::string&)>::Create(webCom->GetPageFinishedEventId(), context);
    }
    if (!webCom->GetPageErrorEventId().IsEmpty()) {
        onPageError_ = AceAsyncEvent<void(const std::string&)>::Create(webCom->GetPageErrorEventId(), context);
    }
}

void WebDelegate::NotifyPopupWindowResult(bool result)
{
    if (parentNWebId_ != -1) {
        std::weak_ptr<OHOS::NWeb::NWeb> parentNWebWeak = OHOS::NWeb::NWebHelper::Instance().GetNWeb(parentNWebId_);
        auto parentNWebSptr = parentNWebWeak.lock();
        if (parentNWebSptr) {
            parentNWebSptr->NotifyPopupWindowResult(result);
        }
    }
}

void WebDelegate::RunSetWebIdAndHapPathCallback()
{
    CHECK_NULL_VOID(nweb_);
    auto webId = nweb_->GetWebId();

    if (Container::IsCurrentUseNewPipeline()) {
        auto pattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto setWebIdCallback = pattern->GetSetWebIdCallback();
        CHECK_NULL_VOID(setWebIdCallback);
        setWebIdCallback(webId);
        auto onControllerAttachedCallback = pattern->GetOnControllerAttachedCallback();
        if (onControllerAttachedCallback) {
            onControllerAttachedCallback();
        }
        if (!hapPath_.empty()) {
            auto setHapPathCallback = pattern->GetSetHapPathCallback();
            CHECK_NULL_VOID(setHapPathCallback);
            setHapPathCallback(hapPath_);
        }
        NotifyPopupWindowResult(true);
        return;
    }
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_VOID(webCom);
    auto setWebIdCallback = webCom->GetSetWebIdCallback();
    CHECK_NULL_VOID(setWebIdCallback);
    setWebIdCallback(webId);
    if (!hapPath_.empty()) {
        auto setHapPathCallback = webCom->GetSetHapPathCallback();
        CHECK_NULL_VOID(setHapPathCallback);
        setHapPathCallback(hapPath_);
    }
    NotifyPopupWindowResult(true);
}

void WebDelegate::RunJsProxyCallback()
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto pattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->CallJsProxyCallback();
        return;
    }
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_VOID(webCom);
    webCom->CallJsProxyCallback();
}

void WebDelegate::RegisterConfigObserver()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            auto appMgrClient = std::make_shared<AppExecFwk::AppMgrClient>();
            if (appMgrClient->ConnectAppMgrService()) {
                LOGE("connect to app mgr service failed");
                return;
            }
            delegate->configChangeObserver_ = sptr<AppExecFwk::IConfigurationObserver>(
                new (std::nothrow) WebConfigurationObserver(delegate));
            if (appMgrClient->RegisterConfigurationObserver(delegate->configChangeObserver_)) {
                return;
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UnRegisterConfigObserver()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            if (delegate->configChangeObserver_) {
                auto appMgrClient = std::make_shared<AppExecFwk::AppMgrClient>();
                if (appMgrClient->ConnectAppMgrService()) {
                    LOGE("connect to app mgr service failed");
                    return;
                }
                appMgrClient->UnregisterConfigurationObserver(delegate->configChangeObserver_);
                delegate->configChangeObserver_ = nullptr;
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::SetWebCallBack()
{
    RefPtr<WebController> webController;
    if (Container::IsCurrentUseNewPipeline()) {
        auto pattern = webPattern_.Upgrade();
        webController = pattern ? pattern->GetWebController() : nullptr;
    } else {
        auto webCom = webComponent_.Upgrade();
        webController = webCom ? webCom->GetController() : nullptr;
    }
    if (webController) {
        auto context = context_.Upgrade();
        if (!context) {
            return;
        }
        auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        webController->SetLoadUrlImpl([weak = WeakClaim(this), uiTaskExecutor](
                                          std::string url, const std::map<std::string, std::string>& httpHeaders) {
            uiTaskExecutor.PostTask([weak, url, httpHeaders]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->LoadUrl(url, httpHeaders);
                }
            });
        });
        webController->SetBackwardImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->Backward();
                }
            });
        });
        webController->SetForwardImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->Forward();
                }
            });
        });
        webController->SetClearHistoryImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->ClearHistory();
                }
            });
        });
        webController->SetClearSslCacheImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->ClearSslCache();
                }
            });
        });
        webController->SetClearClientAuthenticationCacheImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->ClearClientAuthenticationCache();
                }
            });
        });
        webController->SetAccessStepImpl([weak = WeakClaim(this)](int32_t step) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->AccessStep(step);
            }
            return false;
        });
        webController->SetBackOrForwardImpl([weak = WeakClaim(this)](int32_t step) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->BackOrForward(step);
            }
        });
        webController->SetAccessBackwardImpl([weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->AccessBackward();
            }
            return false;
        });
        webController->SetAccessForwardImpl([weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->AccessForward();
            }
            return false;
        });
        webController->SetExecuteTypeScriptImpl([weak = WeakClaim(this), uiTaskExecutor](std::string jscode,
                                                    std::function<void(const std::string)>&& callback) {
            uiTaskExecutor.PostTask([weak, jscode, callback]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->ExecuteTypeScript(jscode, std::move(callback));
                }
            });
        });
        webController->SetLoadDataWithBaseUrlImpl(
            [weak = WeakClaim(this), uiTaskExecutor](std::string baseUrl, std::string data, std::string mimeType,
                std::string encoding, std::string historyUrl) {
                uiTaskExecutor.PostTask([weak, baseUrl, data, mimeType, encoding, historyUrl]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->LoadDataWithBaseUrl(baseUrl, data, mimeType, encoding, historyUrl);
                    }
                });
            });
        webController->SetRefreshImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->Refresh();
                }
            });
        });
        webController->SetStopLoadingImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->StopLoading();
                }
            });
        });
        webController->SetGetHitTestResultImpl([weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->GetHitTestResult();
            }
            return 0;
        });
        webController->SetGetHitTestValueImpl([weak = WeakClaim(this)](HitTestResult& result) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->GetHitTestValue(result);
            }
        });
        webController->SetGetPageHeightImpl([weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->GetPageHeight();
            }
            return 0;
        });
        webController->SetGetWebIdImpl([weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->GetWebId();
            }
            return -1;
        });
        webController->SetGetTitleImpl([weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->GetTitle();
            }
            return std::string();
        });
        webController->SetCreateMsgPortsImpl([weak = WeakClaim(this)](std::vector<RefPtr<WebMessagePort>>& ports) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->CreateWebMessagePorts(ports);
            }
        });
        webController->SetPostWebMessageImpl([weak = WeakClaim(this)](std::string& message,
                                                 std::vector<RefPtr<WebMessagePort>>& ports, std::string& uri) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->PostWebMessage(message, ports, uri);
            }
        });
        webController->SetGetDefaultUserAgentImpl([weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->GetDefaultUserAgent();
            }
            return std::string();
        });
        webController->SetSaveCookieSyncImpl([weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->SaveCookieSync();
            }
            return false;
        });
        webController->SetSetCookieImpl([weak = WeakClaim(this)](const std::string& url, const std::string& value) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->SetCookie(url, value);
            }
            return false;
        });
        webController->SetGetCookieImpl([weak = WeakClaim(this)](const std::string& url) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->GetCookie(url);
            }
            return std::string();
        });
        webController->SetDeleteEntirelyCookieImpl([weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->DeleteEntirelyCookie();
            }
        });
        webController->SetWebViewJavaScriptResultCallBackImpl(
            [weak = WeakClaim(this), uiTaskExecutor](WebController::JavaScriptCallBackImpl&& javaScriptCallBackImpl) {
                uiTaskExecutor.PostTask([weak, javaScriptCallBackImpl]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->SetWebViewJavaScriptResultCallBack(std::move(javaScriptCallBackImpl));
                    }
                });
            });
        webController->SetAddJavascriptInterfaceImpl([weak = WeakClaim(this), uiTaskExecutor](std::string objectName,
                                                         const std::vector<std::string>& methodList) {
            uiTaskExecutor.PostTask([weak, objectName, methodList]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->AddJavascriptInterface(objectName, methodList);
                }
            });
        });
        webController->LoadInitJavascriptInterface();
        webController->SetRemoveJavascriptInterfaceImpl([weak = WeakClaim(this), uiTaskExecutor](std::string objectName,
                                                            const std::vector<std::string>& methodList) {
            uiTaskExecutor.PostTask([weak, objectName, methodList]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->RemoveJavascriptInterface(objectName, methodList);
                }
            });
        });
        webController->SetOnInactiveImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->OnInactive();
                }
            });
        });
        webController->SetOnActiveImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->OnActive();
                }
            });
        });
        webController->SetZoomImpl([weak = WeakClaim(this), uiTaskExecutor](float factor) {
            uiTaskExecutor.PostTask([weak, factor]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->Zoom(factor);
                }
            });
        });
        webController->SetZoomInImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            bool result = false;
            uiTaskExecutor.PostSyncTask([weak, &result]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    result = delegate->ZoomIn();
                }
            });
            return result;
        });
        webController->SetZoomOutImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            bool result = false;
            uiTaskExecutor.PostSyncTask([weak, &result]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    result = delegate->ZoomOut();
                }
            });
            return result;
        });
        webController->SetRequestFocusImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->RequestFocus();
                }
            });
        });

        webController->SetSearchAllAsyncImpl([weak = WeakClaim(this), uiTaskExecutor](const std::string& searchStr) {
            uiTaskExecutor.PostTask([weak, searchStr]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->SearchAllAsync(searchStr);
                }
            });
        });
        webController->SetClearMatchesImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->ClearMatches();
                }
            });
        });
        webController->SetSearchNextImpl([weak = WeakClaim(this), uiTaskExecutor](bool forward) {
            uiTaskExecutor.PostTask([weak, forward]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->SearchNext(forward);
                }
            });
        });
        webController->SetGetUrlImpl([weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->GetUrl();
            }
            return std::string();
        });

    } else {
        LOGE("web controller is nullptr");
    }
}

void WebDelegate::InitWebViewWithWindow()
{
    LOGI("Create webview with window");
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            OHOS::NWeb::NWebInitArgs initArgs;
            std::string app_path = GetDataPath();
            if (!app_path.empty()) {
                initArgs.web_engine_args_to_add.push_back(std::string("--user-data-dir=").append(app_path));
            }

            delegate->window_ = delegate->CreateWindow();
            if (!delegate->window_) {
                return;
            }
            delegate->nweb_ =
                OHOS::NWeb::NWebAdapterHelper::Instance().CreateNWeb(delegate->window_.GetRefPtr(), initArgs);
            if (delegate->nweb_ == nullptr) {
                delegate->window_ = nullptr;
                LOGE("fail to get webview instance");
                return;
            }
            delegate->cookieManager_ = OHOS::NWeb::NWebHelper::Instance().GetCookieManager();
            if (delegate->cookieManager_ == nullptr) {
                LOGE("fail to get webview instance");
                return;
            }
            auto webviewClient = std::make_shared<WebClientImpl>(Container::CurrentId());
            webviewClient->SetWebDelegate(weak);
            delegate->nweb_->SetNWebHandler(webviewClient);

            // Set downloadListenerImpl
            auto downloadListenerImpl = std::make_shared<DownloadListenerImpl>(Container::CurrentId());
            downloadListenerImpl->SetWebDelegate(weak);
            delegate->nweb_->PutDownloadCallback(downloadListenerImpl);

            auto findListenerImpl = std::make_shared<FindListenerImpl>(Container::CurrentId());
            findListenerImpl->SetWebDelegate(weak);
            delegate->nweb_->PutFindCallback(findListenerImpl);

            auto isNewPipe = Container::IsCurrentUseNewPipeline();
            delegate->UpdateSettting(isNewPipe);

            std::optional<std::string> src;
            if (isNewPipe) {
                auto webPattern = delegate->webPattern_.Upgrade();
                if (webPattern) {
                    src = webPattern->GetWebSrc();
                }
            } else {
                auto webCom = delegate->webComponent_.Upgrade();
                if (webCom) {
                    src = webCom->GetSrc();
                }
            }
            if (src) {
                delegate->nweb_->Load(src.value());
            }
            delegate->window_->Show();
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateSettting(bool useNewPipe)
{
    CHECK_NULL_VOID(nweb_);
    auto setting = nweb_->GetPreference();
    CHECK_NULL_VOID(setting);
    if (useNewPipe) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        setting->PutDomStorageEnabled(webPattern->GetDomStorageAccessEnabledValue(false));
        setting->PutJavaScriptEnabled(webPattern->GetJsEnabledValue(true));
        setting->PutEnableRawFileAccess(webPattern->GetFileAccessEnabledValue(true));
        setting->PutEnableContentAccess(true);
        setting->PutLoadImageFromNetworkDisabled(!webPattern->GetOnLineImageAccessEnabledValue(true));
        setting->PutImageLoadingAllowed(webPattern->GetImageAccessEnabledValue(true));
        setting->PutAccessModeForSecureOriginLoadFromInsecure(static_cast<OHOS::NWeb::NWebPreference::AccessMode>(
            webPattern->GetMixedModeValue(MixedModeContent::MIXED_CONTENT_NEVER_ALLOW)));
        setting->PutZoomingFunctionEnabled(webPattern->GetZoomAccessEnabledValue(true));
        setting->PutGeolocationAllowed(webPattern->GetGeolocationAccessEnabledValue(true));
        setting->PutCacheMode(static_cast<OHOS::NWeb::NWebPreference::CacheModeFlag>(
            webPattern->GetCacheModeValue(WebCacheMode::DEFAULT)));
        setting->PutLoadWithOverviewMode(webPattern->GetOverviewModeAccessEnabledValue(true));
        setting->PutEnableRawFileAccessFromFileURLs(webPattern->GetFileFromUrlAccessEnabledValue(true));
        setting->PutDatabaseAllowed(webPattern->GetDatabaseAccessEnabledValue(false));
        setting->PutZoomingForTextFactor(webPattern->GetTextZoomRatioValue(DEFAULT_TEXT_ZOOM_RATIO));
        setting->PutWebDebuggingAccess(webPattern->GetWebDebuggingAccessEnabledValue(false));
        setting->PutMediaPlayGestureAccess(webPattern->GetMediaPlayGestureAccessValue(true));
        return;
    }
    auto component = webComponent_.Upgrade();
    CHECK_NULL_VOID(component);
    setting->PutDomStorageEnabled(component->GetDomStorageAccessEnabled());
    setting->PutJavaScriptEnabled(component->GetJsEnabled());
    setting->PutEnableRawFileAccess(component->GetFileAccessEnabled());
    setting->PutEnableContentAccess(component->GetContentAccessEnabled());
    setting->PutLoadImageFromNetworkDisabled(component->GetOnLineImageAccessEnabled());
    setting->PutImageLoadingAllowed(component->GetImageAccessEnabled());
    setting->PutAccessModeForSecureOriginLoadFromInsecure(
        static_cast<OHOS::NWeb::NWebPreference::AccessMode>(component->GetMixedMode()));
    setting->PutZoomingFunctionEnabled(component->GetZoomAccessEnabled());
    setting->PutGeolocationAllowed(component->GetGeolocationAccessEnabled());
    setting->PutCacheMode(static_cast<OHOS::NWeb::NWebPreference::CacheModeFlag>(component->GetCacheMode()));
    setting->PutLoadWithOverviewMode(component->GetOverviewModeAccessEnabled());
    setting->PutEnableRawFileAccessFromFileURLs(component->GetFileFromUrlAccessEnabled());
    setting->PutDatabaseAllowed(component->GetDatabaseAccessEnabled());
    setting->PutZoomingForTextFactor(component->GetTextZoomRatio());
    setting->PutWebDebuggingAccess(component->GetWebDebuggingAccessEnabled());
    setting->PutMediaPlayGestureAccess(component->IsMediaPlayGestureAccess());
}

std::string WebDelegate::GetCustomScheme()
{
    std::string customScheme;
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        if (webPattern) {
            auto webData = webPattern->GetCustomScheme();
            if (webData) {
                customScheme = webData.value();
            }
        }
    } else {
        auto webCom = webComponent_.Upgrade();
        if (webCom) {
            customScheme = webCom->GetCustomScheme();
        }
    }
    return customScheme;
}

void WebDelegate::InitWebViewWithSurface()
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto window = context->GetWindow();
    CHECK_NULL_VOID(window);
    rosenWindowId_ = window->GetWindowId();
    LOGI("Init WebView With Surface");
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), context = context_]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            OHOS::NWeb::NWebInitArgs initArgs;
            initArgs.web_engine_args_to_add.push_back(
                std::string("--user-data-dir=").append(delegate->bundleDataPath_));
            initArgs.web_engine_args_to_add.push_back(
                std::string("--bundle-installation-dir=").append(delegate->bundlePath_));
            initArgs.web_engine_args_to_add.push_back(
                std::string("--lang=").append(AceApplicationInfo::GetInstance().GetLanguage() +
                    "-" + AceApplicationInfo::GetInstance().GetCountryOrRegion()));
            initArgs.web_engine_args_to_add.push_back(std::string("--user-api-version=").append(
                std::to_string(AceApplicationInfo::GetInstance().GetApiTargetVersion())));
            bool isEnhanceSurface = delegate->isEnhanceSurface_;
            initArgs.is_enhance_surface = isEnhanceSurface;
            initArgs.is_popup = delegate->isPopup_;
            if (!delegate->hapPath_.empty()) {
                initArgs.web_engine_args_to_add.push_back(
                    std::string("--user-hap-path=").append(delegate->hapPath_));
            }
            std::string customScheme = delegate->GetCustomScheme();
            if (!customScheme.empty()) {
                LOGI("custome scheme %{public}s", customScheme.c_str());
                initArgs.web_engine_args_to_add.push_back(
                    std::string("--ohos-custom-scheme=").append(customScheme));
            }
            initArgs.web_engine_args_to_add.push_back(
                std::string("--init-background-color=").append(std::to_string(delegate->backgroundColor_)));
            if (isEnhanceSurface) {
                LOGI("Create webview with isEnhanceSurface");
                delegate->nweb_ = OHOS::NWeb::NWebAdapterHelper::Instance().CreateNWeb(
                    (void *)(&delegate->surfaceInfo_),
                    initArgs,
                    delegate->drawSize_.Width(), delegate->drawSize_.Height());
            } else {
#ifdef ENABLE_ROSEN_BACKEND
                LOGI("Create webview with surface in");
                wptr<Surface> surfaceWeak(delegate->surface_);
                sptr<Surface> surface = surfaceWeak.promote();
                CHECK_NULL_VOID(surface);
                delegate->nweb_ = OHOS::NWeb::NWebAdapterHelper::Instance().CreateNWeb(
                    surface,
                    initArgs,
                    delegate->drawSize_.Width(), delegate->drawSize_.Height());
#endif
            }
            CHECK_NULL_VOID(delegate->nweb_);
            delegate->cookieManager_ = OHOS::NWeb::NWebHelper::Instance().GetCookieManager();
            CHECK_NULL_VOID(delegate->cookieManager_);
            auto nweb_handler = std::make_shared<WebClientImpl>(Container::CurrentId());
            nweb_handler->SetWebDelegate(weak);
            auto downloadListenerImpl = std::make_shared<DownloadListenerImpl>(Container::CurrentId());
            downloadListenerImpl->SetWebDelegate(weak);
            delegate->nweb_->SetNWebHandler(nweb_handler);
            delegate->nweb_->PutDownloadCallback(downloadListenerImpl);
#ifdef OHOS_STANDARD_SYSTEM
            delegate->nweb_->RegisterScreenLockFunction(delegate->GetRosenWindowId(), [context](bool key) {
                LOGD("SetKeepScreenOn %{public}d", key);
                auto weakContext = context.Upgrade();
                CHECK_NULL_VOID(weakContext);
                auto window = weakContext->GetWindow();
                CHECK_NULL_VOID(window);
                window->SetKeepScreenOn(key);
            });
#endif
            auto findListenerImpl = std::make_shared<FindListenerImpl>(Container::CurrentId());
            findListenerImpl->SetWebDelegate(weak);
            delegate->nweb_->PutFindCallback(findListenerImpl);
            delegate->UpdateSettting(Container::IsCurrentUseNewPipeline());
            delegate->RunSetWebIdAndHapPathCallback();
            delegate->RunJsProxyCallback();
            auto releaseSurfaceListenerImpl = std::make_shared<ReleaseSurfaceImpl>(Container::CurrentId());
            releaseSurfaceListenerImpl->SetSurfaceDelegate(delegate->GetSurfaceDelegateClient());
            delegate->nweb_->PutReleaseSurfaceCallback(releaseSurfaceListenerImpl);
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::SetKeepScreenOn(bool key)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto window = context->GetWindow();
    CHECK_NULL_VOID(window);
    window->SetKeepScreenOn(key);
}

void WebDelegate::UpdateUserAgent(const std::string& userAgent)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), userAgent]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutUserAgent(userAgent);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateBackgroundColor(const int backgroundColor)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), backgroundColor]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                delegate->nweb_->PutBackgroundColor(backgroundColor);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateInitialScale(float scale)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), scale]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                delegate->nweb_->InitialScale(scale);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::Resize(const double& width, const double& height)
{
    if (width <= 0 || height <= 0) {
        return;
    }

    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), width, height]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_ && !delegate->window_) {
                // Sur need int value, greater than this value in case show black line.
                delegate->nweb_->Resize(std::ceil(width), std::ceil(height));
                double offsetX = 0;
                double offsetY = 0;
                delegate->UpdateScreenOffSet(offsetX, offsetY);
                delegate->nweb_->SetScreenOffSet(offsetX, offsetY);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateJavaScriptEnabled(const bool& isJsEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isJsEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutJavaScriptEnabled(isJsEnabled);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateAllowFileAccess(const bool& isFileAccessEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isFileAccessEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutEnableRawFileAccess(isFileAccessEnabled);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateBlockNetworkImage(const bool& onLineImageAccessEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), onLineImageAccessEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutLoadImageFromNetworkDisabled(onLineImageAccessEnabled);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateLoadsImagesAutomatically(const bool& isImageAccessEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isImageAccessEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutImageLoadingAllowed(isImageAccessEnabled);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateMixedContentMode(const MixedModeContent& mixedMode)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), mixedMode]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutAccessModeForSecureOriginLoadFromInsecure(
                    static_cast<OHOS::NWeb::NWebPreference::AccessMode>(mixedMode));
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateSupportZoom(const bool& isZoomAccessEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isZoomAccessEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutZoomingFunctionEnabled(isZoomAccessEnabled);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}
void WebDelegate::UpdateDomStorageEnabled(const bool& isDomStorageAccessEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isDomStorageAccessEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutDomStorageEnabled(isDomStorageAccessEnabled);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}
void WebDelegate::UpdateGeolocationEnabled(const bool& isGeolocationAccessEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isGeolocationAccessEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutGeolocationAllowed(isGeolocationAccessEnabled);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateCacheMode(const WebCacheMode& mode)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), mode]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutCacheMode(static_cast<OHOS::NWeb::NWebPreference::CacheModeFlag>(mode));
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

std::shared_ptr<OHOS::NWeb::NWeb> WebDelegate::GetNweb()
{
    return nweb_;
}

bool WebDelegate::GetForceDarkMode()
{
    return forceDarkMode_;
}

void WebDelegate::UpdateDarkMode(const WebDarkMode& mode)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), mode]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
            CHECK_NULL_VOID(setting);
            if (mode == WebDarkMode::On) {
                delegate->UnRegisterConfigObserver();
                setting->PutDarkSchemeEnabled(true);
                if (delegate->forceDarkMode_) {
                    setting->PutForceDarkModeEnabled(true);
                }
                return;
            }
            if (mode == WebDarkMode::Off) {
                delegate->UnRegisterConfigObserver();
                setting->PutDarkSchemeEnabled(false);
                setting->PutForceDarkModeEnabled(false);
                return;
            }
            if (mode == WebDarkMode::Auto) {
                delegate->UpdateDarkModeAuto(delegate, setting);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateDarkModeAuto(RefPtr<WebDelegate> delegate,
    std::shared_ptr<OHOS::NWeb::NWebPreference> setting)
{
    auto appMgrClient = std::make_shared<AppExecFwk::AppMgrClient>();
    if (appMgrClient->ConnectAppMgrService()) {
        return;
    }
    auto systemConfig = OHOS::AppExecFwk::Configuration();
    appMgrClient->GetConfiguration(systemConfig);
    std::string colorMode =
        systemConfig.GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
    CHECK_NULL_VOID(setting);
    if (colorMode == "dark") {
        setting->PutDarkSchemeEnabled(true);
        if (delegate->GetForceDarkMode()) {
            setting->PutForceDarkModeEnabled(true);
        }
    }
    if (colorMode == "light") {
        setting->PutDarkSchemeEnabled(false);
        setting->PutForceDarkModeEnabled(false);
    }
    delegate->RegisterConfigObserver();
}

void WebDelegate::UpdateForceDarkAccess(const bool& access)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), access]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
            CHECK_NULL_VOID(setting);
            delegate->forceDarkMode_ = access;
            if (setting->DarkSchemeEnabled()) {
                setting->PutForceDarkModeEnabled(access);
            } else {
                setting->PutForceDarkModeEnabled(false);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateAudioResumeInterval(const int32_t& resumeInterval)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), resumeInterval]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            delegate->nweb_->SetAudioResumeInterval(resumeInterval);
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateAudioExclusive(const bool& audioExclusive)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), audioExclusive]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            delegate->nweb_->SetAudioExclusive(audioExclusive);
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateOverviewModeEnabled(const bool& isOverviewModeAccessEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isOverviewModeAccessEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutLoadWithOverviewMode(isOverviewModeAccessEnabled);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateFileFromUrlEnabled(const bool& isFileFromUrlAccessEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isFileFromUrlAccessEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutEnableRawFileAccessFromFileURLs(isFileFromUrlAccessEnabled);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateDatabaseEnabled(const bool& isDatabaseAccessEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isDatabaseAccessEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutDatabaseAllowed(isDatabaseAccessEnabled);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateTextZoomRatio(const int32_t& textZoomRatioNum)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), textZoomRatioNum]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutZoomingForTextFactor(textZoomRatioNum);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateWebDebuggingAccess(bool isWebDebuggingAccessEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isWebDebuggingAccessEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutWebDebuggingAccess(isWebDebuggingAccessEnabled);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdatePinchSmoothModeEnabled(bool isPinchSmoothModeEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isPinchSmoothModeEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutPinchSmoothMode(isPinchSmoothModeEnabled);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateMediaPlayGestureAccess(bool isNeedGestureAccess)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isNeedGestureAccess]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutMediaPlayGestureAccess(isNeedGestureAccess);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateMultiWindowAccess(bool isMultiWindowAccessEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isMultiWindowAccessEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutMultiWindowAccess(isMultiWindowAccessEnabled);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateAllowWindowOpenMethod(bool isAllowWindowOpenMethod)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isAllowWindowOpenMethod]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                setting->PutIsCreateWindowsByJavaScriptAllowed(isAllowWindowOpenMethod);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateWebCursiveFont(const std::string& cursiveFontFamily)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), cursiveFontFamily]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutCursiveFontFamilyName(cursiveFontFamily);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateWebFantasyFont(const std::string& fantasyFontFamily)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), fantasyFontFamily]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutFantasyFontFamilyName(fantasyFontFamily);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateWebFixedFont(const std::string& fixedFontFamily)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), fixedFontFamily]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutFixedFontFamilyName(fixedFontFamily);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateWebSansSerifFont(const std::string& sansSerifFontFamily)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), sansSerifFontFamily]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutSansSerifFontFamilyName(sansSerifFontFamily);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateWebSerifFont(const std::string& serifFontFamily)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), serifFontFamily]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutSerifFontFamilyName(serifFontFamily);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateWebStandardFont(const std::string& standardFontFamily)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), standardFontFamily]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutStandardFontFamilyName(standardFontFamily);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateDefaultFixedFontSize(int32_t defaultFixedFontSize)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), defaultFixedFontSize]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutDefaultFixedFontSize(defaultFixedFontSize);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateDefaultFontSize(int32_t defaultFontSize)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), defaultFontSize]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutDefaultFontSize(defaultFontSize);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateMinFontSize(int32_t minFontSize)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), minFontSize]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutFontSizeLowerLimit(minFontSize);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateMinLogicalFontSize(int32_t minLogicalFontSize)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), minLogicalFontSize]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutLogicalFontSizeLowerLimit(minLogicalFontSize);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateBlockNetwork(bool isNetworkBlocked)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isNetworkBlocked]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutBlockNetwork(isNetworkBlocked);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateHorizontalScrollBarAccess(bool isHorizontalScrollBarAccessEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isHorizontalScrollBarAccessEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutHorizontalScrollBarAccess(isHorizontalScrollBarAccessEnabled);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateVerticalScrollBarAccess(bool isVerticalScrollBarAccessEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isVerticalScrollBarAccessEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutVerticalScrollBarAccess(isVerticalScrollBarAccessEnabled);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::UpdateScrollBarColor(const std::string& colorValue)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline == nullptr) {
        return;
    }

    auto themeManager = pipeline->GetThemeManager();
    if (themeManager == nullptr) {
        return;
    }

    auto themeConstants = themeManager->GetThemeConstants();
    if (themeConstants == nullptr) {
        return;
    }
    Color color = themeConstants->GetColorByName(colorValue);
    uint32_t colorContent = color.GetValue();
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), colorContent]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutScrollBarColor(colorContent);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::LoadUrl()
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::optional<std::string> src;
                if (Container::IsCurrentUseNewPipeline()) {
                    auto webPattern = delegate->webPattern_.Upgrade();
                    if (webPattern) {
                        src = webPattern->GetWebSrc();
                    }
                } else {
                    auto webCom = delegate->webComponent_.Upgrade();
                    if (webCom) {
                        src = webCom->GetSrc();
                    }
                }
                CHECK_NULL_VOID(src);
                delegate->nweb_->Load(src.value());
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::OnInactive()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->OnPause();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::OnActive()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->OnContinue();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::OnWebviewHide()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->OnWebviewHide();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::OnWebviewShow()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->OnWebviewShow();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::SetShouldFrameSubmissionBeforeDraw(bool should)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), should]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->SetShouldFrameSubmissionBeforeDraw(should);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::NotifyMemoryLevel(int32_t level)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), level]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->NotifyMemoryLevel(level);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::Zoom(float factor)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), factor]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                LOGE("Get delegate failed, it is null.");
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->Zoom(factor);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

bool WebDelegate::ZoomIn()
{
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }
    bool result = false;
    context->GetTaskExecutor()->PostSyncTask(
        [weak = WeakClaim(this), &result]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                LOGE("Get delegate failed, it is null.");
                return;
            }
            if (delegate->nweb_) {
                result = delegate->nweb_->ZoomIn();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
    return result;
}

bool WebDelegate::ZoomOut()
{
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }
    bool result = false;
    context->GetTaskExecutor()->PostSyncTask(
        [weak = WeakClaim(this), &result]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                LOGE("Get delegate failed, it is null.");
                return;
            }
            if (delegate->nweb_) {
                result = delegate->nweb_->ZoomOut();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
    return result;
}

sptr<OHOS::Rosen::Window> WebDelegate::CreateWindow()
{
    auto context = context_.Upgrade();
    if (!context) {
        return nullptr;
    }
    float scale = context->GetViewScale();

    constexpr int DEFAULT_HEIGHT = 1600;
    int DEFAULT_HEIGHT_WITHOUT_SYSTEM_BAR = (int)(scale * context->GetRootHeight());
    int DEFAULT_STATUS_BAR_HEIGHT = (DEFAULT_HEIGHT - DEFAULT_HEIGHT_WITHOUT_SYSTEM_BAR) / 2;
    constexpr int DEFAULT_LEFT = 0;
    int DEFAULT_TOP = DEFAULT_STATUS_BAR_HEIGHT;
    int DEFAULT_WIDTH = (int)(scale * context->GetRootWidth());
    sptr<Rosen::WindowOption> option = new Rosen::WindowOption();
    option->SetWindowRect({ DEFAULT_LEFT, DEFAULT_TOP, DEFAULT_WIDTH, DEFAULT_HEIGHT_WITHOUT_SYSTEM_BAR });
    option->SetWindowType(Rosen::WindowType::WINDOW_TYPE_APP_LAUNCHING);
    option->SetWindowMode(Rosen::WindowMode::WINDOW_MODE_FLOATING);
    auto window = Rosen::Window::Create("ohos_web_window", option);
    return window;
}
#endif

void WebDelegate::RegisterWebEvent()
{
    // TODO: add support for ng.
    auto context = DynamicCast<PipelineContext>(context_.Upgrade());
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
    resRegister->RegisterEvent(MakeEventHash(WEB_EVENT_PAGEERROR), [weak = WeakClaim(this)](const std::string& param) {
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->OnPageError(param);
        }
    });
    resRegister->RegisterEvent(MakeEventHash(WEB_EVENT_ROUTERPUSH), [weak = WeakClaim(this)](const std::string& param) {
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->OnRouterPush(param);
        }
    });
    resRegister->RegisterEvent(MakeEventHash(WEB_EVENT_ONMESSAGE), [weak = WeakClaim(this)](const std::string& param) {
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->OnMessage(param);
        }
    });
}

// upper ui component which inherited from WebComponent
// could implement some curtain createdCallback to customized controller interface
// eg: web.loadurl.
void WebDelegate::AddCreatedCallback(const CreatedCallback& createdCallback)
{
    ACE_DCHECK(createdCallback != nullptr);
    ACE_DCHECK(state_ != State::RELEASED);
    createdCallbacks_.emplace_back(createdCallback);
}

void WebDelegate::RemoveCreatedCallback()
{
    ACE_DCHECK(state_ != State::RELEASED);
    createdCallbacks_.pop_back();
}

void WebDelegate::AddReleasedCallback(const ReleasedCallback& releasedCallback)
{
    ACE_DCHECK(releasedCallback != nullptr && state_ != State::RELEASED);
    releasedCallbacks_.emplace_back(releasedCallback);
}

void WebDelegate::RemoveReleasedCallback()
{
    ACE_DCHECK(state_ != State::RELEASED);
    releasedCallbacks_.pop_back();
}

void WebDelegate::Reload()
{
#ifdef OHOS_STANDARD_SYSTEM
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->Reload();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
#else
    hash_ = MakeResourceHash();
    reloadMethod_ = MakeMethodHash("reload");
    CallResRegisterMethod(reloadMethod_, WEB_PARAM_NONE, nullptr);
#endif
}

void WebDelegate::UpdateUrl(const std::string& url)
{
    hash_ = MakeResourceHash();
    updateUrlMethod_ = MakeMethodHash(WEB_METHOD_UPDATEURL);
    std::stringstream paramStream;
    paramStream << NTC_PARAM_SRC << WEB_PARAM_EQUALS << url;
    std::string param = paramStream.str();
    CallResRegisterMethod(updateUrlMethod_, param, nullptr);
}

void WebDelegate::CallWebRouterBack()
{
    hash_ = MakeResourceHash();
    routerBackMethod_ = MakeMethodHash(WEB_METHOD_ROUTER_BACK);
    CallResRegisterMethod(routerBackMethod_, WEB_PARAM_NONE, nullptr);
}

void WebDelegate::CallPopPageSuccessPageUrl(const std::string& url)
{
    hash_ = MakeResourceHash();
    changePageUrlMethod_ = MakeMethodHash(WEB_METHOD_CHANGE_PAGE_URL);
    std::stringstream paramStream;
    paramStream << NTC_PARAM_PAGE_URL << WEB_PARAM_EQUALS << url;
    std::string param = paramStream.str();
    CallResRegisterMethod(changePageUrlMethod_, param, nullptr);
}

void WebDelegate::CallIsPagePathInvalid(const bool& isPageInvalid)
{
    hash_ = MakeResourceHash();
    isPagePathInvalidMethod_ = MakeMethodHash(WEB_METHOD_PAGE_PATH_INVALID);
    std::stringstream paramStream;
    paramStream << NTC_PARAM_PAGE_INVALID << WEB_PARAM_EQUALS << isPageInvalid;
    std::string param = paramStream.str();
    CallResRegisterMethod(isPagePathInvalidMethod_, param, nullptr);
}

void WebDelegate::OnPageStarted(const std::string& param)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), param]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onPageStarted = delegate->onPageStarted_;
            if (onPageStarted) {
                std::string paramStart = std::string(R"(")").append(param).append(std::string(R"(")"));
                std::string urlParam = std::string(R"("pagestart",{"url":)").append(paramStart.append("},null"));
                onPageStarted(urlParam);
            }

            // ace 2.0
            auto onPageStartedV2 = delegate->onPageStartedV2_;
            if (onPageStartedV2) {
                onPageStartedV2(std::make_shared<LoadWebPageStartEvent>(param));
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnPageFinished(const std::string& param)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), param]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onPageFinished = delegate->onPageFinished_;
            if (onPageFinished) {
                std::string paramFinish = std::string(R"(")").append(param).append(std::string(R"(")"));
                std::string urlParam = std::string(R"("pagefinish",{"url":)").append(paramFinish.append("},null"));
                onPageFinished(urlParam);
            }
            // ace 2.0
            auto onPageFinishedV2 = delegate->onPageFinishedV2_;
            if (onPageFinishedV2) {
                onPageFinishedV2(std::make_shared<LoadWebPageFinishEvent>(param));
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnProgressChanged(int param)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), param]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto eventParam = std::make_shared<LoadWebProgressChangeEvent>(param);
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                webEventHub->FireOnProgressChangeEvent(eventParam);
                return;
            }
            auto webCom = delegate->webComponent_.Upgrade();
            CHECK_NULL_VOID(webCom);
            webCom->OnProgressChange(eventParam.get());
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnReceivedTitle(const std::string& param)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), param]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            // ace 2.0
            auto onTitleReceiveV2 = delegate->onTitleReceiveV2_;
            if (onTitleReceiveV2) {
                onTitleReceiveV2(std::make_shared<LoadWebTitleReceiveEvent>(param));
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::ExitFullScreen()
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->ExitFullScreen();
    }
}

void WebDelegate::OnFullScreenExit()
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto param = std::make_shared<FullScreenExitEvent>(false);
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                auto propOnFullScreenExitEvent = webEventHub->GetOnFullScreenExitEvent();
                CHECK_NULL_VOID(propOnFullScreenExitEvent);
                propOnFullScreenExitEvent(param);
                return;
            }
            // ace 2.0
            auto onFullScreenExitV2 = delegate->onFullScreenExitV2_;
            if (onFullScreenExitV2) {
                onFullScreenExitV2(param);
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnGeolocationPermissionsHidePrompt()
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            // ace 2.0
            auto onGeolocationHideV2 = delegate->onGeolocationHideV2_;
            if (onGeolocationHideV2) {
                onGeolocationHideV2(std::make_shared<LoadWebGeolocationHideEvent>(""));
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnGeolocationPermissionsShowPrompt(
    const std::string& origin, const std::shared_ptr<OHOS::NWeb::NWebGeolocationCallbackInterface>& callback)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), origin, callback]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            // ace 2.0
            auto onGeolocationShowV2 = delegate->onGeolocationShowV2_;
            if (onGeolocationShowV2) {
                auto geolocation = AceType::MakeRefPtr<WebGeolocationOhos>(callback);
                onGeolocationShowV2(std::make_shared<LoadWebGeolocationShowEvent>(origin, geolocation));
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnPermissionRequestPrompt(const std::shared_ptr<OHOS::NWeb::NWebAccessRequest>& request)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), request]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            // ace 2.0
            auto onPermissionRequestV2 = delegate->onPermissionRequestV2_;
            if (onPermissionRequestV2) {
                onPermissionRequestV2(
                    std::make_shared<WebPermissionRequestEvent>(
                    AceType::MakeRefPtr<WebPermissionRequestOhos>(request)));
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnScreenCaptureRequest(const std::shared_ptr<OHOS::NWeb::NWebScreenCaptureAccessRequest>& request)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), request]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            // ace 2.0
            auto onScreenCaptureRequestV2 = delegate->onScreenCaptureRequestV2_;
            if (onScreenCaptureRequestV2) {
                onScreenCaptureRequestV2(
                    std::make_shared<WebScreenCaptureRequestEvent>(
                    AceType::MakeRefPtr<WebScreenCaptureRequestOhos>(request)));
            }
        },
        TaskExecutor::TaskType::JS);
}

bool WebDelegate::OnConsoleLog(std::shared_ptr<OHOS::NWeb::NWebConsoleLog> message)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), message, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        auto param = std::make_shared<LoadWebConsoleLogEvent>(AceType::MakeRefPtr<ConsoleLogOhos>(message));
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnConsoleEvent = webEventHub->GetOnConsoleEvent();
            CHECK_NULL_VOID(propOnConsoleEvent);
            result = propOnConsoleEvent(param);
        }
        auto webCom = delegate->webComponent_.Upgrade();
        CHECK_NULL_VOID(webCom);
        result = webCom->OnConsole(param.get());
        return;
    });
    return result;
}


bool WebDelegate::OnCommonDialog(const std::shared_ptr<BaseEventInfo>& info, DialogEventType dialogEventType)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, dialogEventType, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            result = webEventHub->FireOnCommonDialogEvent(info, dialogEventType);
            return;
        }
        auto webCom = delegate->webComponent_.Upgrade();
        CHECK_NULL_VOID(webCom);
        result = webCom->OnCommonDialog(info.get(), dialogEventType);
        return;
    });
    return result;
}

void WebDelegate::OnFullScreenEnter(std::shared_ptr<OHOS::NWeb::NWebFullScreenExitHandler> handler)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), handler]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto param = std::make_shared<FullScreenEnterEvent>(
                AceType::MakeRefPtr<FullScreenExitHandlerOhos>(handler, weak));
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                webPattern->RequestFullScreen();
                webPattern->SetFullScreenExitHandler(param);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                auto propOnFullScreenEnterEvent = webEventHub->GetOnFullScreenEnterEvent();
                CHECK_NULL_VOID(propOnFullScreenEnterEvent);
                propOnFullScreenEnterEvent(param);
                return;
            }
            auto webCom = delegate->webComponent_.Upgrade();
            CHECK_NULL_VOID(webCom);
            webCom->OnFullScreenEnter(param.get());
        },
        TaskExecutor::TaskType::JS);
}

bool WebDelegate::OnHttpAuthRequest(const std::shared_ptr<BaseEventInfo>& info)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnHttpAuthRequestEvent = webEventHub->GetOnHttpAuthRequestEvent();
            CHECK_NULL_VOID(propOnHttpAuthRequestEvent);
            result = propOnHttpAuthRequestEvent(info);
            return;
        }
        auto webCom = delegate->webComponent_.Upgrade();
        CHECK_NULL_VOID(webCom);
        result = webCom->OnHttpAuthRequest(info.get());
    });
    return result;
}

bool WebDelegate::OnSslErrorRequest(const std::shared_ptr<BaseEventInfo>& info)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnSslErrorEvent = webEventHub->GetOnSslErrorRequestEvent();
            CHECK_NULL_VOID(propOnSslErrorEvent);
            result = propOnSslErrorEvent(info);
            return;
        }
        auto webCom = delegate->webComponent_.Upgrade();
        CHECK_NULL_VOID(webCom);
        result = webCom->OnSslErrorRequest(info.get());
    });
    return result;
}

bool WebDelegate::OnSslSelectCertRequest(const std::shared_ptr<BaseEventInfo>& info)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnSslSelectCertRequestEvent = webEventHub->GetOnSslSelectCertRequestEvent();
            CHECK_NULL_VOID(propOnSslSelectCertRequestEvent);
            result = propOnSslSelectCertRequestEvent(info);
            return;
        }
        auto webCom = delegate->webComponent_.Upgrade();
        CHECK_NULL_VOID(webCom);
        result = webCom->OnSslSelectCertRequest(info.get());
    });
    return result;
}

void WebDelegate::OnDownloadStart(const std::string& url, const std::string& userAgent,
    const std::string& contentDisposition, const std::string& mimetype, long contentLength)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), url, userAgent, contentDisposition,
            mimetype, contentLength]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onDownloadStartV2 = delegate->onDownloadStartV2_;
            if (onDownloadStartV2) {
                onDownloadStartV2(
                    std::make_shared<DownloadStartEvent>(url, userAgent, contentDisposition, mimetype, contentLength));
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnErrorReceive(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceError> error)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), request, error]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onPageError = delegate->onPageError_;
            if (onPageError) {
                std::string url = request->Url();
                int errorCode = error->ErrorCode();
                std::string description = error->ErrorInfo();
                std::string paramUrl = std::string(R"(")").append(url).append(std::string(R"(")")).append(",");
                std::string paramErrorCode = std::string(R"(")")
                                                .append(NTC_PARAM_ERROR_CODE)
                                                .append(std::string(R"(")"))
                                                .append(":")
                                                .append(std::to_string(errorCode))
                                                .append(",");

                std::string paramDesc = std::string(R"(")")
                                            .append(NTC_PARAM_DESCRIPTION)
                                            .append(std::string(R"(")"))
                                            .append(":")
                                            .append(std::string(R"(")")
                                            .append(description)
                                            .append(std::string(R"(")")));
                std::string errorParam =
                    std::string(R"("error",{"url":)").append((paramUrl + paramErrorCode + paramDesc).append("},null"));
                onPageError(errorParam);
            }
            auto onErrorReceiveV2 = delegate->onErrorReceiveV2_;
            if (onErrorReceiveV2) {
                onErrorReceiveV2(std::make_shared<ReceivedErrorEvent>(
                    AceType::MakeRefPtr<WebRequest>(request->RequestHeaders(), request->Method(), request->Url(),
                        request->FromGesture(), request->IsAboutMainFrame(), request->IsRequestRedirect()),
                    AceType::MakeRefPtr<WebError>(error->ErrorInfo(), error->ErrorCode())));
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnHttpErrorReceive(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> response)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), request, response]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onHttpErrorReceiveV2 = delegate->onHttpErrorReceiveV2_;
            if (onHttpErrorReceiveV2) {
                onHttpErrorReceiveV2(std::make_shared<ReceivedHttpErrorEvent>(
                    AceType::MakeRefPtr<WebRequest>(request->RequestHeaders(), request->Method(), request->Url(),
                        request->FromGesture(), request->IsAboutMainFrame(), request->IsRequestRedirect()),
                    AceType::MakeRefPtr<WebResponse>(response->ResponseHeaders(), response->ResponseData(),
                        response->ResponseEncoding(), response->ResponseMimeType(), response->ResponseStatus(),
                        response->ResponseStatusCode())));
            }
        },
        TaskExecutor::TaskType::JS);
}

bool WebDelegate::IsEmptyOnInterceptRequest()
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_RETURN(webPattern, false);
        auto webEventHub = webPattern->GetWebEventHub();
        CHECK_NULL_RETURN(webEventHub, false);
        return webEventHub->GetOnInterceptRequestEvent() == nullptr;
    }
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_RETURN(webCom, true);
    return webCom->IsEmptyOnInterceptRequest();
}

RefPtr<WebResponse> WebDelegate::OnInterceptRequest(const std::shared_ptr<BaseEventInfo>& info)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, nullptr);
    RefPtr<WebResponse> result = nullptr;
    auto jsTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnInterceptRequestEvent = webEventHub->GetOnInterceptRequestEvent();
            CHECK_NULL_VOID(propOnInterceptRequestEvent);
            result = propOnInterceptRequestEvent(info);
        }
        auto webCom = delegate->webComponent_.Upgrade();
        CHECK_NULL_VOID(webCom);
        result = webCom->OnInterceptRequest(info.get());
    });
    return result;
}

void WebDelegate::OnRequestFocus()
{
    if (onRequestFocusV2_) {
        onRequestFocusV2_(std::make_shared<LoadWebRequestFocusEvent>(""));
    }
}

void WebDelegate::OnRenderExited(OHOS::NWeb::RenderExitReason reason)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), reason]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onRenderExitedV2 = delegate->onRenderExitedV2_;
            if (onRenderExitedV2) {
                onRenderExitedV2(std::make_shared<RenderExitedEvent>(static_cast<int32_t>(reason)));
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnRefreshAccessedHistory(const std::string& url, bool isRefreshed)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), url, isRefreshed]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onRefreshAccessedHistoryV2 = delegate->onRefreshAccessedHistoryV2_;
            if (onRefreshAccessedHistoryV2) {
                onRefreshAccessedHistoryV2(std::make_shared<RefreshAccessedHistoryEvent>(url, isRefreshed));
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnPageError(const std::string& param)
{
    if (onPageError_) {
        int32_t errorCode = GetIntParam(param, NTC_PARAM_ERROR_CODE);
        std::string url = GetUrlStringParam(param, NTC_PARAM_URL);
        std::string description = GetStringParam(param, NTC_PARAM_DESCRIPTION);

        std::string paramUrl = std::string(R"(")").append(url).append(std::string(R"(")")).append(",");

        std::string paramErrorCode = std::string(R"(")")
                                         .append(NTC_PARAM_ERROR_CODE)
                                         .append(std::string(R"(")"))
                                         .append(":")
                                         .append(std::to_string(errorCode))
                                         .append(",");

        std::string paramDesc = std::string(R"(")")
                                    .append(NTC_PARAM_DESCRIPTION)
                                    .append(std::string(R"(")"))
                                    .append(":")
                                    .append(std::string(R"(")").append(description).append(std::string(R"(")")));
        std::string errorParam =
            std::string(R"("error",{"url":)").append((paramUrl + paramErrorCode + paramDesc).append("},null"));
        onPageError_(errorParam);
    }
}

void WebDelegate::OnMessage(const std::string& param)
{
    std::string removeQuotes;
    removeQuotes = param;
    removeQuotes.erase(std::remove(removeQuotes.begin(), removeQuotes.end(), '\"'), removeQuotes.end());
    if (onMessage_) {
        std::string paramMessage = std::string(R"(")").append(removeQuotes).append(std::string(R"(")"));
        std::string messageParam = std::string(R"("message",{"message":)").append(paramMessage.append("},null"));
        onMessage_(messageParam);
    }
}

void WebDelegate::OnRouterPush(const std::string& param)
{
    OHOS::Ace::Framework::DelegateClient::GetInstance().RouterPush(param);
}

bool WebDelegate::OnFileSelectorShow(const std::shared_ptr<BaseEventInfo>& info)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnFileSelectorShowEvent = webEventHub->GetOnFileSelectorShowEvent();
            CHECK_NULL_VOID(propOnFileSelectorShowEvent);
            result = propOnFileSelectorShowEvent(info);
        }
        auto webCom = delegate->webComponent_.Upgrade();
        CHECK_NULL_VOID(webCom);
        result = webCom->OnFileSelectorShow(info.get());
    });
    return result;
}

bool WebDelegate::OnContextMenuShow(const std::shared_ptr<BaseEventInfo>& info)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnContextMenuShowEvent = webEventHub->GetOnContextMenuShowEvent();
            CHECK_NULL_VOID(propOnContextMenuShowEvent);
            result = propOnContextMenuShowEvent(info);
            return;
        }
        auto webCom = delegate->webComponent_.Upgrade();
        CHECK_NULL_VOID(webCom);
        result = webCom->OnContextMenuShow(info.get());
    });
    return result;
}

void WebDelegate::OnContextMenuHide(const std::string& info)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnContextMenuHideEvent = webEventHub->GetOnContextMenuHideEvent();
            CHECK_NULL_VOID(propOnContextMenuHideEvent);
            propOnContextMenuHideEvent(std::make_shared<ContextMenuHideEvent>(info));
            return;
        } else {
            LOGE("current is not new pipeline");
        }
    });
    return;
}

bool WebDelegate::OnHandleInterceptUrlLoading(const std::string& data)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), data, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        auto param = std::make_shared<UrlLoadInterceptEvent>(data);
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnUrlLoadInterceptEvent = webEventHub->GetOnUrlLoadInterceptEvent();
            CHECK_NULL_VOID(propOnUrlLoadInterceptEvent);
            result = propOnUrlLoadInterceptEvent(param);
        }
        auto webCom = delegate->webComponent_.Upgrade();
        CHECK_NULL_VOID(webCom);
        result = webCom->OnUrlLoadIntercept(param.get());
    });
    return result;
}

bool WebDelegate::OnHandleInterceptLoading(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), request, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        auto webRequest = AceType::MakeRefPtr<WebRequest>(request->RequestHeaders(),
            request->Method(), request->Url(), request->FromGesture(),
            request->IsAboutMainFrame(), request->IsRequestRedirect());
        auto param = std::make_shared<LoadInterceptEvent>(webRequest);
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnLoadInterceptEvent = webEventHub->GetOnLoadInterceptEvent();
            CHECK_NULL_VOID(propOnLoadInterceptEvent);
            result = propOnLoadInterceptEvent(param);
        }
        auto webCom = delegate->webComponent_.Upgrade();
        CHECK_NULL_VOID(webCom);
        result = webCom->OnLoadIntercept(param.get());
    });
    return result;
}

void WebDelegate::OnResourceLoad(const std::string& url)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), url]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onResourceLoadV2 = delegate->onResourceLoadV2_;
            if (onResourceLoadV2) {
                onResourceLoadV2(std::make_shared<ResourceLoadEvent>(url));
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnScaleChange(float oldScaleFactor, float newScaleFactor)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), oldScaleFactor, newScaleFactor]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onScaleChangeV2 = delegate->onScaleChangeV2_;
            if (onScaleChangeV2) {
                onScaleChangeV2(std::make_shared<ScaleChangeEvent>(oldScaleFactor, newScaleFactor));
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnScroll(double xOffset, double yOffset)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), xOffset, yOffset]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onScrollV2 = delegate->onScrollV2_;
            if (onScrollV2) {
                onScrollV2(std::make_shared<WebOnScrollEvent>(xOffset, yOffset));
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnSearchResultReceive(int activeMatchOrdinal, int numberOfMatches, bool isDoneCounting)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), activeMatchOrdinal,
            numberOfMatches, isDoneCounting]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onSearchResultReceiveV2 = delegate->onSearchResultReceiveV2_;
            if (onSearchResultReceiveV2) {
                onSearchResultReceiveV2(
                    std::make_shared<SearchResultReceiveEvent>(activeMatchOrdinal, numberOfMatches, isDoneCounting));
            }
        },
        TaskExecutor::TaskType::JS);
}

bool WebDelegate::OnDragAndDropData(const void* data, size_t len, int width, int height)
{
    LOGI("store pixel map, len = %{public}zu, width = %{public}d, height = %{public}d", len, width, height);
    pixelMap_ = PixelMap::ConvertSkImageToPixmap(static_cast<const uint32_t*>(data), len, width, height);
    if (pixelMap_ == nullptr) {
        LOGE("convert drag image to pixel map failed");
        return false;
    }
    isRefreshPixelMap_ = true;

    auto webPattern = webPattern_.Upgrade();
    if (!webPattern) {
        LOGE("web pattern is nullptr");
        return false;
    }
    return webPattern->NotifyStartDragTask();
}

bool WebDelegate::OnDragAndDropDataUdmf(std::shared_ptr<OHOS::NWeb::NWebDragData> dragData)
{
    LOGI("DragDrop event OnDragAndDropDataUdmf");

    const void *data = nullptr;
    size_t len = 0;
    int width = 0;
    int height = 0;
    dragData->GetPixelMapSetting(&data, len, width, height);
    pixelMap_ = PixelMap::ConvertSkImageToPixmap(static_cast<const uint32_t*>(data), len, width, height);
    if (pixelMap_ == nullptr) {
        LOGE("convert drag image to pixel map failed");
        return false;
    }
    isRefreshPixelMap_ = true;

    dragData_ = dragData;
    auto webPattern = webPattern_.Upgrade();
    if (!webPattern) {
        LOGE("web pattern is nullptr");
        return false;
    }
    return webPattern->NotifyStartDragTask();
}

bool WebDelegate::IsImageDrag()
{
    if (dragData_) {
        return dragData_->IsSingleImageContent();
    }
    return false;
}

std::shared_ptr<OHOS::NWeb::NWebDragData> WebDelegate::GetOrCreateDragData()
{
    if (dragData_) {
        return dragData_;
    }

    if (nweb_) {
        dragData_ = nweb_->GetOrCreateDragData();
        return dragData_;
    }
    return nullptr;
}

void WebDelegate::OnWindowNew(const std::string& targetUrl, bool isAlert, bool isUserTrigger,
    const std::shared_ptr<OHOS::NWeb::NWebControllerHandler>& handler)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostSyncTask(
        [weak = WeakClaim(this), targetUrl, isAlert, isUserTrigger, handler]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            int32_t parentNWebId = (delegate->nweb_ ? delegate->nweb_->GetWebId() : -1);
            auto param = std::make_shared<WebWindowNewEvent>(targetUrl, isAlert, isUserTrigger,
                AceType::MakeRefPtr<WebWindowNewHandlerOhos>(handler, parentNWebId));
            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto webEventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(webEventHub);
                auto propOnWindowNewEvent = webEventHub->GetOnWindowNewEvent();
                CHECK_NULL_VOID(propOnWindowNewEvent);
                propOnWindowNewEvent(param);
                return;
            }
            auto webCom = delegate->webComponent_.Upgrade();
            CHECK_NULL_VOID(webCom);
            webCom->OnWindowNewEvent(param);
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnWindowExit()
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onWindowExitV2 = delegate->onWindowExitV2_;
            if (onWindowExitV2) {
                onWindowExitV2(std::make_shared<WebWindowExitEvent>());
            }
        },
        TaskExecutor::TaskType::JS);
}

void WebDelegate::OnPageVisible(const std::string& url)
{
    if (onPageVisibleV2_) {
        onPageVisibleV2_(std::make_shared<PageVisibleEvent>(url));
    }
}

void WebDelegate::OnFirstContentfulPaint(int64_t navigationStartTick, int64_t firstContentfulPaintMs)
{
    if (onFirstContentfulPaintV2_) {
        onFirstContentfulPaintV2_(std::make_shared<FirstContentfulPaintEvent>(navigationStartTick,
            firstContentfulPaintMs));
    }
}

void WebDelegate::OnDataResubmitted(std::shared_ptr<OHOS::NWeb::NWebDataResubmissionCallback> handler)
{
    auto param = std::make_shared<DataResubmittedEvent>(AceType::MakeRefPtr<DataResubmittedOhos>(handler));
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        auto webEventHub = webPattern->GetWebEventHub();
        CHECK_NULL_VOID(webEventHub);
        auto propOnDataResubmittedEvent = webEventHub->GetOnDataResubmittedEvent();
        CHECK_NULL_VOID(propOnDataResubmittedEvent);
        propOnDataResubmittedEvent(param);
        return;
    }
}

void WebDelegate::OnFaviconReceived(
    const void* data,
    size_t width,
    size_t height,
    OHOS::NWeb::ImageColorType colorType,
    OHOS::NWeb::ImageAlphaType alphaType)
{
    auto param = std::make_shared<FaviconReceivedEvent>(AceType::MakeRefPtr<FaviconReceivedOhos>(
                     data,
                     width,
                     height,
                     colorType,
                     alphaType));
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        auto webEventHub = webPattern->GetWebEventHub();
        CHECK_NULL_VOID(webEventHub);
        auto propOnFaviconReceivedEvent = webEventHub->GetOnFaviconReceivedEvent();
        CHECK_NULL_VOID(propOnFaviconReceivedEvent);
        propOnFaviconReceivedEvent(param);
        return;
    }
}

void WebDelegate::OnTouchIconUrl(const std::string& iconUrl, bool precomposed)
{
    if (onTouchIconUrlV2_) {
        onTouchIconUrlV2_(std::make_shared<TouchIconUrlEvent>(iconUrl, precomposed));
    }
}

void WebDelegate::OnAudioStateChanged(bool audible)
{
    if (onAudioStateChangedV2_) {
        onAudioStateChangedV2_(std::make_shared<AudioStateChangedEvent>(audible));
    }
}

void WebDelegate::OnGetTouchHandleHotZone(OHOS::NWeb::TouchHandleHotZone& hotZone)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    auto touchHandleSize = theme->GetHandleHotZoneRadius().ConvertToPx();
    hotZone.width = touchHandleSize;
    hotZone.height = touchHandleSize;
}

RefPtr<PixelMap> WebDelegate::GetDragPixelMap()
{
    return pixelMap_;
}

#ifdef OHOS_STANDARD_SYSTEM
void WebDelegate::HandleTouchDown(const int32_t& id, const double& x, const double& y,
    bool from_overlay)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        ResSchedReport::GetInstance().ResSchedDataReport("web_gesture");
        nweb_->OnTouchPress(id, x, y, from_overlay);
    }
}

void WebDelegate::HandleTouchUp(const int32_t& id, const double& x, const double& y,
    bool from_overlay)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        ResSchedReport::GetInstance().ResSchedDataReport("web_gesture");
        nweb_->OnTouchRelease(id, x, y, from_overlay);
    }
}

void WebDelegate::HandleTouchMove(const int32_t& id, const double& x, const double& y,
    bool from_overlay)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->OnTouchMove(id, x, y, from_overlay);
    }
}

void WebDelegate::HandleTouchCancel()
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->OnTouchCancel();
    }
}

void WebDelegate::HandleAxisEvent(const double& x, const double& y, const double& deltaX, const double& deltaY)
{
    if (nweb_) {
        nweb_->SendMouseWheelEvent(x, y, deltaX, deltaY);
    }
}

bool WebDelegate::OnKeyEvent(int32_t keyCode, int32_t keyAction)
{
    if (nweb_) {
        return nweb_->SendKeyEvent(keyCode, keyAction);
    }
    return false;
}

void WebDelegate::OnMouseEvent(int32_t x, int32_t y, const MouseButton button, const MouseAction action, int count)
{
    if (nweb_) {
        nweb_->SendMouseEvent(x, y, static_cast<int>(button), static_cast<int>(action), count);
    }
}

void WebDelegate::OnFocus()
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->OnFocus(OHOS::NWeb::FocusReason::EVENT_REQUEST);
    }
}

void WebDelegate::OnBlur()
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->OnBlur(blurReason_);
    }
}

bool WebDelegate::RunQuickMenu(std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_RETURN(webPattern, false);
        return webPattern->RunQuickMenu(params, callback);
    }
    auto renderWeb = renderWeb_.Upgrade();
    if (!renderWeb || !params || !callback) {
        LOGE("renderWeb is nullptr");
        return false;
    }

    return renderWeb->RunQuickMenu(params, callback);
}

void WebDelegate::OnQuickMenuDismissed()
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->OnQuickMenuDismissed();
        return;
    }
    auto renderWeb = renderWeb_.Upgrade();
    CHECK_NULL_VOID(renderWeb);
    renderWeb->OnQuickMenuDismissed();
}

void WebDelegate::OnTouchSelectionChanged(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
        return;
    }
    auto renderWeb = renderWeb_.Upgrade();
    CHECK_NULL_VOID(renderWeb);
    renderWeb->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
}

bool WebDelegate::OnCursorChange(const OHOS::NWeb::CursorType& type, const OHOS::NWeb::NWebCursorInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_RETURN(webPattern, false);
        return webPattern->OnCursorChange(type, info);
    }
    auto renderWeb = renderWeb_.Upgrade();
    CHECK_NULL_RETURN(renderWeb, false);
    return renderWeb->OnCursorChange(type, info);
}

void WebDelegate::OnSelectPopupMenu(
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params,
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->OnSelectPopupMenu(params, callback);
        return;
    }
    auto renderWeb = renderWeb_.Upgrade();
    CHECK_NULL_VOID(renderWeb);
    return renderWeb->OnSelectPopupMenu(params, callback);
}

void WebDelegate::HandleDragEvent(int32_t x, int32_t y, const DragAction& dragAction)
{
    if (nweb_) {
        OHOS::NWeb::DragEvent dragEvent;
        dragEvent.x = x;
        dragEvent.y = y;
        dragEvent.action = static_cast<OHOS::NWeb::DragAction>(dragAction);
        nweb_->SendDragEvent(dragEvent);
    }
}

std::string WebDelegate::GetUrl()
{
    if (nweb_) {
        return nweb_->GetUrl();
    }
    return "";
}

void WebDelegate::UpdateLocale()
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        std::string language = AceApplicationInfo::GetInstance().GetLanguage();
        std::string region = AceApplicationInfo::GetInstance().GetCountryOrRegion();
        if (!language.empty() || !region.empty()) {
            nweb_->UpdateLocale(language, region);
        }
    }
}
#endif

std::string WebDelegate::GetUrlStringParam(const std::string& param, const std::string& name) const
{
    size_t len = name.length();
    size_t posErrorCode = param.find(NTC_PARAM_ERROR_CODE);
    size_t pos = param.find(name);
    std::string result;

    if (pos != std::string::npos && posErrorCode != std::string::npos) {
        std::stringstream ss;

        ss << param.substr(pos + 1 + len, posErrorCode - 5);
        ss >> result;
    }
    return result;
}

void WebDelegate::BindRouterBackMethod()
{
    auto context = context_.Upgrade();
    if (context) {
        context->SetRouterBackEventHandler([weak = WeakClaim(this)] {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->CallWebRouterBack();
            }
        });
    }
}

void WebDelegate::BindPopPageSuccessMethod()
{
    auto context = context_.Upgrade();
    if (context) {
        context->SetPopPageSuccessEventHandler(
            [weak = WeakClaim(this)](const std::string& pageUrl, const int32_t pageId) {
                std::string url = pageUrl.substr(0, pageUrl.length() - 3);
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->CallPopPageSuccessPageUrl(url);
                }
            });
    }
}

void WebDelegate::BindIsPagePathInvalidMethod()
{
    auto context = context_.Upgrade();
    if (context) {
        context->SetIsPagePathInvalidEventHandler([weak = WeakClaim(this)](bool& isPageInvalid) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->CallIsPagePathInvalid(isPageInvalid);
            }
        });
    }
}

void WebDelegate::SetComponent(const RefPtr<WebComponent>& component)
{
    webComponent_ = component;
}

void WebDelegate::SetNGWebPattern(const RefPtr<NG::WebPattern>& webPattern)
{
    webPattern_ = webPattern;
}

void WebDelegate::SetDrawSize(const Size& drawSize)
{
    drawSize_ = drawSize;
}

void WebDelegate::SetEnhanceSurfaceFlag(const bool& isEnhanceSurface)
{
    LOGI("enhance flag %{public}d", isEnhanceSurface);
    isEnhanceSurface_ = isEnhanceSurface;
}

sptr<OHOS::SurfaceDelegate> WebDelegate::GetSurfaceDelegateClient()
{
    return surfaceDelegate_;
}

void WebDelegate::SetBoundsOrResize(const Size& drawSize, const Offset& offset)
{
    if ((drawSize.Width() == 0) && (drawSize.Height() == 0)) {
        LOGE("WebDelegate::SetBoundsOrResize width and height error");
        return;
    }
    if (isEnhanceSurface_) {
        if (surfaceDelegate_) {
            LOGI("WebDelegate::SetBounds: x:%{public}d, y:%{public}d, w::%{public}d, h:%{public}d",
                (int32_t)offset.GetX(), (int32_t)offset.GetY(),
                (int32_t)drawSize.Width(), (int32_t)drawSize.Height());
            if (needResizeAtFirst_) {
                LOGI("WebDelegate::SetBounds: resize at first");
                Resize(drawSize.Width(), drawSize.Height());
                needResizeAtFirst_ = false;
            }
            Size webSize = GetEnhanceSurfaceSize(drawSize);
            surfaceDelegate_->SetBounds(offset.GetX(), (int32_t)offset.GetY(), webSize.Width(), webSize.Height());
        }
    } else {
        Resize(drawSize.Width(), drawSize.Height());
    }
}

Offset WebDelegate::GetWebRenderGlobalPos()
{
    return offset_;
}

Size WebDelegate::GetEnhanceSurfaceSize(const Size& drawSize)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN_NOLOG(pipeline, Size());
    double dipScale = pipeline->GetDipScale();
    if (NearZero(dipScale)) {
        return Size();
    }
    int width = std::ceil(std::floor(drawSize.Width() / dipScale) * dipScale);
    int height = std::ceil(std::floor(drawSize.Height() / dipScale) * dipScale);
    if (width <= 0) {
        width = 1;
    }
    if (height <= 0) {
        height = 1;
    }
    return Size(width, height);
}

WebDelegate::EventCallbackV2 WebDelegate::GetAudioStateChangedCallback(
    bool useNewPipe, const RefPtr<NG::WebEventHub>& eventHub)
{
    if (eventHub && useNewPipe) {
        return eventHub->GetOnAudioStateChangedEvent();
    }
    return nullptr;
}

#ifdef ENABLE_ROSEN_BACKEND
void WebDelegate::SetSurface(const sptr<Surface>& surface)
{
    surface_ = surface;
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    auto host = webPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(renderContext);
    CHECK_NULL_VOID(rosenRenderContext);
    rsNode_ = rosenRenderContext->GetRSNode();
}
#endif

void WebDelegate::UpdateScreenOffSet(double& offsetX, double& offsetY)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        offsetX += webPattern->GetHost()->GetTransformRelativeOffset().GetX();
        offsetY += webPattern->GetHost()->GetTransformRelativeOffset().GetY();
        auto context = context_.Upgrade();
        CHECK_NULL_VOID(context);
        auto windowOffset = context->GetDisplayWindowRectInfo().GetOffset();
        offsetX += windowOffset.GetX();
        offsetY += windowOffset.GetY();
        return;
    }
    auto renderWeb = renderWeb_.Upgrade();
    CHECK_NULL_VOID(renderWeb);
    offsetX += renderWeb->GetGlobalOffset().GetX();
    offsetY += renderWeb->GetGlobalOffset().GetY();
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto windowOffset = context->GetDisplayWindowRectInfo().GetOffset();
    offsetX += windowOffset.GetX();
    offsetY += windowOffset.GetY();
    WindowMode windowMode = context->GetWindowManager()->GetWindowMode();
    if (windowMode == WindowMode::WINDOW_MODE_FLOATING) {
        offsetX += CONTAINER_BORDER_WIDTH.ConvertToPx();
        offsetY += CONTAINER_TITLE_HEIGHT.ConvertToPx();
    }
}

void WebDelegate::RegisterSurfacePositionChangedCallback()
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto pipelineContext = DynamicCast<NG::PipelineContext>(context_.Upgrade());
        CHECK_NULL_VOID(pipelineContext);
        if (callbackId_ <= 0) {
            callbackId_ = pipelineContext->RegisterSurfacePositionChangedCallback(
                [weak = WeakClaim(this)](int32_t posX, int32_t posY) {
                    auto delegate = weak.Upgrade();
                    if (delegate && delegate->nweb_ && !delegate->window_) {
                        double offsetX = 0;
                        double offsetY = 0;
                        delegate->UpdateScreenOffSet(offsetX, offsetY);
                        delegate->nweb_->SetScreenOffSet(offsetX, offsetY);
                    }
                }
            );
        }
        return;
    }
    auto pipelineContext = DynamicCast<PipelineContext>(context_.Upgrade());
    CHECK_NULL_VOID(pipelineContext);
    if (callbackId_ <= 0) {
        callbackId_ = pipelineContext->RegisterSurfacePositionChangedCallback(
            [weak = WeakClaim(this)](int32_t posX, int32_t posY) {
                auto delegate = weak.Upgrade();
                if (delegate && delegate->nweb_ && !delegate->window_) {
                    double offsetX = 0;
                    double offsetY = 0;
                    delegate->UpdateScreenOffSet(offsetX, offsetY);
                    delegate->nweb_->SetScreenOffSet(offsetX, offsetY);
                }
            }
        );
    }
}

void WebDelegate::UnregisterSurfacePositionChangedCallback()
{
    if (callbackId_ <= 0) {
        LOGE("callbackId_ = %{public}d", callbackId_);
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        auto pipelineContext = DynamicCast<NG::PipelineContext>(context_.Upgrade());
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UnregisterSurfacePositionChangedCallback(callbackId_);
        callbackId_ = 0;
        return;
    }
    auto pipelineContext = DynamicCast<PipelineContext>(context_.Upgrade());
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UnregisterSurfacePositionChangedCallback(callbackId_);
    callbackId_ = 0;
}

void WebDelegate::OnCompleteSwapWithNewSize()
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnCompleteSwapWithNewSize();
}

void WebDelegate::OnResizeNotWork()
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnResizeNotWork();
}

void WebDelegate::OnDateTimeChooserPopup(
    const OHOS::NWeb::DateTimeChooser& chooser,
    const std::vector<OHOS::NWeb::DateTimeSuggestion>& suggestions,
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserCallback> callback)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnDateTimeChooserPopup(chooser, suggestions, callback);
}

void WebDelegate::OnDateTimeChooserClose()
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnDateTimeChooserClose();
}

void WebDelegate::OnOverScroll(float xOffset, float yOffset)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), xOffset, yOffset]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onOverScrollV2 = delegate->onOverScrollV2_;
            if (onOverScrollV2) {
                onOverScrollV2(std::make_shared<WebOnOverScrollEvent>(xOffset, yOffset));
            }
        },
        TaskExecutor::TaskType::JS);
}
} // namespace OHOS::Ace