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
#include "base/memory/referenced.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/web/render_web.h"
#include "core/components/web/web_event.h"
#include "core/components/web/web_property.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_surface.h"
#include "core/event/ace_event_helper.h"
#include "core/event/ace_events.h"
#include "core/event/back_end_event_manager.h"
#include "frameworks/bridge/js_frontend/frontend_delegate_impl.h"
#ifdef OHOS_STANDARD_SYSTEM
#include "application_env.h"
#include "nweb_adapter_helper.h"
#include "nweb_handler.h"
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
} // namespace

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

WebDelegate::~WebDelegate()
{
    ReleasePlatformResource();
    if (nweb_) {
        nweb_->OnDestroy();
    }
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
                delegate->nweb_->ExecuteJavaScript(jscode, callbackImpl);
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
    // TODO: add ng web pattern.
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
        nweb_->PostPortMessage(port, data);
    }
}

void WebDelegate::SetPortMessageCallback(std::string& port, std::function<void(const std::string&)>&& callback)
{
    if (nweb_) {
        auto callbackImpl = std::make_shared<WebJavaScriptExecuteCallBack>(Container::CurrentId());
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
            // TODO: add ng frameNode.
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
        return cookieManager_->ReturnCookie(url);
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
}

void WebDelegate::HideWebView()
{
    if (window_) {
        window_->Hide();
    }

    LOGI("OnPause webview");
    OnInactive();
}

void WebDelegate::InitOHOSWeb(const RefPtr<PipelineBase>& context, const RefPtr<NG::RenderSurface>& surface)
{
    CHECK_NULL_VOID(context);
    auto rosenRenderSurface = DynamicCast<NG::RosenRenderSurface>(surface);
    if (!rosenRenderSurface) {
        LOGI("source is nullptr, initialize with window");
        InitOHOSWeb(context, sptr<Surface>(nullptr));
        return;
    }
    auto rosenSurface = rosenRenderSurface->GetSurface();
    InitOHOSWeb(context, rosenSurface);
}

void WebDelegate::InitOHOSWeb(const WeakPtr<PipelineBase>& context, sptr<Surface> surface)
{
    state_ = State::CREATING;
    // obtain hap data path
    auto container = Container::Current();
    if (container == nullptr) {
        LOGE("Fail to get container");
        return;
    }
    const std::string& bundlePath = container->GetBundlePath();
    const std::string& filesDataPath = container->GetFilesDataPath();
    std::string baseDir = "base";
    std::size_t baseIndex = filesDataPath.find(baseDir);
    if (baseIndex == std::string::npos) {
        LOGE("Fail to parse hap data base path");
        return;
    }
    std::string dataPath = filesDataPath.substr(0, baseIndex + baseDir.length());
    bundlePath_ = bundlePath;
    bundleDataPath_ = dataPath;
    // load webview so
    OHOS::NWeb::NWebHelper::Instance().SetBundlePath(bundlePath_);
    if (!OHOS::NWeb::NWebHelper::Instance().Init()) {
        LOGE("Fail to init NWebHelper");
        return;
    }
    auto webCom = webComponent_.Upgrade();
    auto webPattern = webPattern_.Upgrade();
    auto eventHub = webPattern ? webPattern->GetWebEventHub() : nullptr;
    auto useNewPipe = Container::IsCurrentUseNewPipeline();
    if (useNewPipe && !webPattern && !eventHub) {
        state_ = State::CREATEFAILED;
        OnError(NTC_ERROR, "fail to call WebDelegate::Create due to webComponent is null");
        return;
    }
    if (!useNewPipe && !webCom) {
        state_ = State::CREATEFAILED;
        OnError(NTC_ERROR, "fail to call WebDelegate::Create due to webComponent is null");
        return;
    }
    context_ = context;
    auto pipelineContext = context.Upgrade();
    if (!pipelineContext) {
        state_ = State::CREATEFAILED;
        OnError(NTC_ERROR, "fail to call WebDelegate::Create due to context is null");
        return;
    }
    state_ = State::CREATED;

    if (!isCreateWebView_) {
        isCreateWebView_ = true;
        if (surface != nullptr) {
            InitWebViewWithSurface(surface);
        } else {
            InitWebViewWithWindow();
        }
    }

    SetWebCallBack();
    if (!pipelineContext->GetIsDeclarative()) {
        RegisterOHOSWebEventAndMethord();
        return;
    }
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
    // TODO: add ng impl.
    if (!useNewPipe) {
        onRequestFocusV2_ = AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
            webCom->GetRequestFocusEventId(), oldContext);
        onDownloadStartV2_ = AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
            webCom->GetDownloadStartEventId(), oldContext);
        onRenderExitedV2_ =
            AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(webCom->GetRenderExitedId(), oldContext);
        onRefreshAccessedHistoryV2_ = AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
            webCom->GetRefreshAccessedHistoryId(), oldContext);
        onResourceLoadV2_ =
            AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(webCom->GetResourceLoadId(), oldContext);
        onScaleChangeV2_ =
            AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(webCom->GetScaleChangeId(), oldContext);
        onPermissionRequestV2_ = AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
            webCom->GetPermissionRequestEventId(), oldContext);
        onSearchResultReceiveV2_ = AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
            webCom->GetSearchResultReceiveEventId(), oldContext);
        onScrollV2_ =
            AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(webCom->GetScrollId(), oldContext);
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
        webController->SetExecuteTypeScriptImpl([weak = WeakClaim(this), uiTaskExecutor](
            std::string jscode, std::function<void(const std::string)>&& callback) {
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
        webController->SetRefreshImpl(
            [weak = WeakClaim(this), uiTaskExecutor]() {
                uiTaskExecutor.PostTask([weak]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->Refresh();
                    }
                });
            });
        webController->SetStopLoadingImpl(
            [weak = WeakClaim(this), uiTaskExecutor]() {
                uiTaskExecutor.PostTask([weak]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->StopLoading();
                    }
                });
            });
        webController->SetGetHitTestResultImpl(
            [weak = WeakClaim(this)]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    return delegate->GetHitTestResult();
                }
                return 0;
            });
        webController->SetGetHitTestValueImpl(
            [weak = WeakClaim(this)](HitTestResult& result) {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->GetHitTestValue(result);
                }
            });
        webController->SetGetPageHeightImpl(
            [weak = WeakClaim(this)]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    return delegate->GetPageHeight();
                }
                return 0;
            });
        webController->SetGetWebIdImpl(
            [weak = WeakClaim(this)]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    return delegate->GetWebId();
                }
                return -1;
            });
        webController->SetGetTitleImpl(
            [weak = WeakClaim(this)]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    return delegate->GetTitle();
                }
                return std::string();
            });
        webController->SetCreateMsgPortsImpl(
            [weak = WeakClaim(this)](std::vector<RefPtr<WebMessagePort>>& ports) {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->CreateWebMessagePorts(ports);
                }
            });
        webController->SetPostWebMessageImpl(
            [weak = WeakClaim(this)](std::string& message, std::vector<RefPtr<WebMessagePort>>& ports,
                std::string& uri) {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->PostWebMessage(message, ports, uri);
                }
            });
        webController->SetGetDefaultUserAgentImpl(
            [weak = WeakClaim(this)]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    return delegate->GetDefaultUserAgent();
                }
                return std::string();
            });
        webController->SetSaveCookieSyncImpl(
            [weak = WeakClaim(this)]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    return delegate->SaveCookieSync();
                }
                return false;
            });
        webController->SetSetCookieImpl(
            [weak = WeakClaim(this)](const std::string& url, const std::string& value) {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    return delegate->SetCookie(url, value);
                }
                return false;
            });
        webController->SetGetCookieImpl(
            [weak = WeakClaim(this)](const std::string& url) {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    return delegate->GetCookie(url);
                }
                return std::string();
            });
        webController->SetDeleteEntirelyCookieImpl(
            [weak = WeakClaim(this)]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->DeleteEntirelyCookie();
                }
            });
        webController->SetWebViewJavaScriptResultCallBackImpl([weak = WeakClaim(this), uiTaskExecutor](
            WebController::JavaScriptCallBackImpl&& javaScriptCallBackImpl) {
                uiTaskExecutor.PostTask([weak, javaScriptCallBackImpl]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->SetWebViewJavaScriptResultCallBack(std::move(javaScriptCallBackImpl));
                    }
                });
            });
        webController->SetAddJavascriptInterfaceImpl([weak = WeakClaim(this), uiTaskExecutor](
            std::string objectName, const std::vector<std::string>& methodList) {
                uiTaskExecutor.PostTask([weak, objectName, methodList]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->AddJavascriptInterface(objectName, methodList);
                    }
                });
            });
        webController->LoadInitJavascriptInterface();
        webController->SetRemoveJavascriptInterfaceImpl([weak = WeakClaim(this), uiTaskExecutor](
            std::string objectName, const std::vector<std::string>& methodList) {
                uiTaskExecutor.PostTask([weak, objectName, methodList]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->RemoveJavascriptInterface(objectName, methodList);
                    }
                });
            });
        webController->SetOnInactiveImpl(
            [weak = WeakClaim(this), uiTaskExecutor]() {
                uiTaskExecutor.PostTask([weak]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->OnInactive();
                    }
                });
            });
        webController->SetOnActiveImpl(
            [weak = WeakClaim(this), uiTaskExecutor]() {
                uiTaskExecutor.PostTask([weak]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->OnActive();
                    }
                });
            });
        webController->SetZoomImpl(
            [weak = WeakClaim(this), uiTaskExecutor](float factor) {
                uiTaskExecutor.PostTask([weak, factor]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->Zoom(factor);
                    }
                });
            });
        webController->SetZoomInImpl(
            [weak = WeakClaim(this), uiTaskExecutor]() {
                bool result = false;
                uiTaskExecutor.PostSyncTask([weak, &result]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        result = delegate->ZoomIn();
                    }
                });
                return result;
            });
        webController->SetZoomOutImpl(
            [weak = WeakClaim(this), uiTaskExecutor]() {
                bool result = false;
                uiTaskExecutor.PostSyncTask([weak, &result]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        result = delegate->ZoomOut();
                    }
                });
                return result;
            });
        webController->SetRequestFocusImpl(
            [weak = WeakClaim(this), uiTaskExecutor]() {
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
    if (useNewPipe) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        setting->PutDomStorageEnabled(webPattern->GetDomStorageAccessEnabledValue(false));
        setting->PutIsCreateWindowsByJavaScriptAllowed(true);
        setting->PutJavaScriptEnabled(webPattern->GetJsEnabledValue(true));
        // TODO: add ng pattern get with default value.
        setting->PutEnableRawFileAccess(true);
        setting->PutEnableContentAccess(true);
        setting->PutLoadImageFromNetworkDisabled(false);
        setting->PutImageLoadingAllowed(true);
        setting->PutAccessModeForSecureOriginLoadFromInsecure(
            static_cast<OHOS::NWeb::NWebPreference::AccessMode>(MixedModeContent::MIXED_CONTENT_NEVER_ALLOW));
        setting->PutZoomingFunctionEnabled(true);
        setting->PutGeolocationAllowed(true);
        setting->PutCacheMode(static_cast<OHOS::NWeb::NWebPreference::CacheModeFlag>(WebCacheMode::DEFAULT));
        setting->PutLoadWithOverviewMode(true);
        setting->PutEnableRawFileAccessFromFileURLs(true);
        setting->PutDatabaseAllowed(false);
        setting->PutZoomingForTextFactor(DEFAULT_TEXT_ZOOM_RATIO);
        setting->PutWebDebuggingAccess(false);
        setting->PutMediaPlayGestureAccess(true);
        return;
    }
    auto component = webComponent_.Upgrade();
    CHECK_NULL_VOID(component);
    setting->PutDomStorageEnabled(component->GetDomStorageAccessEnabled());
    setting->PutIsCreateWindowsByJavaScriptAllowed(true);
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

#if defined(ENABLE_ROSEN_BACKEND)
void WebDelegate::InitWebViewWithSurface(sptr<Surface> surface)
{
    LOGI("Create webview with surface");
    auto context = context_.Upgrade();
    if (!context || !surface) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), surface]() {
            wptr<Surface> surfaceWeak(surface);
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            OHOS::NWeb::NWebInitArgs initArgs;
            initArgs.web_engine_args_to_add.push_back(
                std::string("--user-data-dir=").append(delegate->bundleDataPath_));
            initArgs.web_engine_args_to_add.push_back(
                std::string("--bundle-installation-dir=").append(delegate->bundlePath_));
            sptr<Surface> surface = surfaceWeak.promote();
            CHECK_NULL_VOID(surface);
            delegate->nweb_ = OHOS::NWeb::NWebAdapterHelper::Instance().CreateNWeb(surface, initArgs);
            if (delegate->nweb_ == nullptr) {
                LOGE("fail to get webview instance");
                return;
            }
            delegate->cookieManager_ = OHOS::NWeb::NWebHelper::Instance().GetCookieManager();
            if (delegate->cookieManager_ == nullptr) {
                LOGE("fail to get webview instance");
                return;
            }
            auto nweb_handler = std::make_shared<WebClientImpl>(Container::CurrentId());
            nweb_handler->SetWebDelegate(weak);
            auto downloadListenerImpl = std::make_shared<DownloadListenerImpl>(Container::CurrentId());
            downloadListenerImpl->SetWebDelegate(weak);
            delegate->nweb_->SetNWebHandler(nweb_handler);
            delegate->nweb_->PutDownloadCallback(downloadListenerImpl);

            auto findListenerImpl = std::make_shared<FindListenerImpl>(Container::CurrentId());
            findListenerImpl->SetWebDelegate(weak);
            delegate->nweb_->PutFindCallback(findListenerImpl);
            delegate->UpdateSettting(Container::IsCurrentUseNewPipeline());
        },
        TaskExecutor::TaskType::PLATFORM);
}
#endif

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
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), width, height]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_ && !delegate->window_) {
                delegate->nweb_->Resize(width, height);
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
                setting->PutCacheMode(static_cast<OHOS::NWeb::NWebPreference::CacheModeFlag>(mode));
            }
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
                setting->PutWebDebuggingAccess(isWebDebuggingAccessEnabled);
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
    if (onPageStarted_) {
        std::string paramStart = std::string(R"(")").append(param).append(std::string(R"(")"));
        std::string urlParam = std::string(R"("pagestart",{"url":)").append(paramStart.append("},null"));
        onPageStarted_(urlParam);
    }

    // ace 2.0
    if (onPageStartedV2_) {
        onPageStartedV2_(std::make_shared<LoadWebPageStartEvent>(param));
    }
}

void WebDelegate::OnPageFinished(const std::string& param)
{
    if (onPageFinished_) {
        std::string paramFinish = std::string(R"(")").append(param).append(std::string(R"(")"));
        std::string urlParam = std::string(R"("pagefinish",{"url":)").append(paramFinish.append("},null"));
        onPageFinished_(urlParam);
    }
    // ace 2.0
    if (onPageFinishedV2_) {
        onPageFinishedV2_(std::make_shared<LoadWebPageFinishEvent>(param));
    }
}

void WebDelegate::OnProgressChanged(int param)
{
    // TODO: add ng event.
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_VOID(webCom);
    auto eventParam = std::make_shared<LoadWebProgressChangeEvent>(param);
    webCom->OnProgressChange(eventParam.get());
}

void WebDelegate::OnReceivedTitle(const std::string& param)
{
    // ace 2.0
    if (onTitleReceiveV2_) {
        onTitleReceiveV2_(std::make_shared<LoadWebTitleReceiveEvent>(param));
    }
}

void WebDelegate::OnGeolocationPermissionsHidePrompt()
{
    // ace 2.0
    if (onGeolocationHideV2_) {
        onGeolocationHideV2_(std::make_shared<LoadWebGeolocationHideEvent>(""));
    }
}

void WebDelegate::OnGeolocationPermissionsShowPrompt(
    const std::string& origin, OHOS::NWeb::NWebGeolocationCallbackInterface* callback)
{
    // ace 2.0
    if (onGeolocationShowV2_) {
        auto geolocation = AceType::MakeRefPtr<WebGeolocationOhos>(callback);
        onGeolocationShowV2_(std::make_shared<LoadWebGeolocationShowEvent>(origin, geolocation));
    }
}

void WebDelegate::OnPermissionRequestPrompt(const std::shared_ptr<OHOS::NWeb::NWebAccessRequest>& request)
{
    // ace 2.0
    if (onPermissionRequestV2_) {
        onPermissionRequestV2_(
            std::make_shared<WebPermissionRequestEvent>(AceType::MakeRefPtr<WebPermissionRequestOhos>(request)));
    }
}

bool WebDelegate::OnConsoleLog(std::shared_ptr<OHOS::NWeb::NWebConsoleLog> message)
{
    auto param = std::make_shared<LoadWebConsoleLogEvent>(AceType::MakeRefPtr<ConsoleLogOhos>(message));
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_RETURN(webPattern, false);
        auto webEventHub = webPattern->GetWebEventHub();
        CHECK_NULL_RETURN(webEventHub, false);
        return webEventHub->FireOnConsole(param);
    }
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_RETURN(webCom, false);
    return webCom->OnConsole(param.get());
}

bool WebDelegate::OnCommonDialog(const BaseEventInfo* info, DialogEventType dialogEventType)
{
    // TODO: add ng event.
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_RETURN(webCom, false);
    return webCom->OnCommonDialog(info, dialogEventType);
}

bool WebDelegate::OnHttpAuthRequest(const BaseEventInfo* info)
{
    // TODO: add ng event.
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_RETURN(webCom, false);
    return webCom->OnHttpAuthRequest(info);
}

bool WebDelegate::OnSslErrorRequest(const BaseEventInfo* info)
{
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_RETURN(webCom, false);
    return webCom->OnSslErrorRequest(info);
}

void WebDelegate::OnDownloadStart(const std::string& url, const std::string& userAgent,
    const std::string& contentDisposition, const std::string& mimetype, long contentLength)
{
    if (onDownloadStartV2_) {
        onDownloadStartV2_(
            std::make_shared<DownloadStartEvent>(url, userAgent, contentDisposition, mimetype, contentLength));
    }
}

void WebDelegate::OnErrorReceive(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceError> error)
{
    if (onPageError_) {
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
                                    .append(std::string(R"(")").append(description).append(std::string(R"(")")));
        std::string errorParam =
            std::string(R"("error",{"url":)").append((paramUrl + paramErrorCode + paramDesc).append("},null"));
        onPageError_(errorParam);
    }

    if (onErrorReceiveV2_) {
        onErrorReceiveV2_(std::make_shared<ReceivedErrorEvent>(
            AceType::MakeRefPtr<WebRequest>(request->RequestHeaders(), request->Method(), request->Url(),
                request->FromGesture(), request->IsAboutMainFrame(), request->IsRequestRedirect()),
            AceType::MakeRefPtr<WebError>(error->ErrorInfo(), error->ErrorCode())));
    }
}

void WebDelegate::OnHttpErrorReceive(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> response)
{
    if (onHttpErrorReceiveV2_) {
        onHttpErrorReceiveV2_(std::make_shared<ReceivedHttpErrorEvent>(
            AceType::MakeRefPtr<WebRequest>(request->RequestHeaders(), request->Method(), request->Url(),
                request->FromGesture(), request->IsAboutMainFrame(), request->IsRequestRedirect()),
            AceType::MakeRefPtr<WebResponse>(response->ResponseHeaders(), response->ResponseData(),
                response->ResponseEncoding(), response->ResponseMimeType(), response->ResponseStatus(),
                response->ResponseStatusCode())));
    }
}

bool WebDelegate::IsEmptyOnInterceptRequest()
{
    // TODO: add ng pattern.
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_RETURN(webCom, true);
    return webCom->IsEmptyOnInterceptRequest();
}

RefPtr<WebResponse> WebDelegate::OnInterceptRequest(const BaseEventInfo* info)
{
    // TODO: add ng event.
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_RETURN(webCom, nullptr);
    return webCom->OnInterceptRequest(info);
}

void WebDelegate::OnRequestFocus()
{
    if (onRequestFocusV2_) {
        onRequestFocusV2_(std::make_shared<LoadWebRequestFocusEvent>(""));
    }
}

void WebDelegate::OnRenderExited(OHOS::NWeb::RenderExitReason reason)
{
    if (onRenderExitedV2_) {
        onRenderExitedV2_(std::make_shared<RenderExitedEvent>(static_cast<int32_t>(reason)));
    }
}

void WebDelegate::OnRefreshAccessedHistory(const std::string& url, bool isRefreshed)
{
    if (onRefreshAccessedHistoryV2_) {
        onRefreshAccessedHistoryV2_(std::make_shared<RefreshAccessedHistoryEvent>(url, isRefreshed));
    }
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

bool WebDelegate::OnFileSelectorShow(const BaseEventInfo* info)
{
    // TODO: add ng event.
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_RETURN(webCom, false);
    return webCom->OnFileSelectorShow(info);
}

bool WebDelegate::OnContextMenuShow(const BaseEventInfo* info)
{
    // TODO: add ng event.
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_RETURN(webCom, false);
    return webCom->OnContextMenuShow(info);
}

bool WebDelegate::OnHandleInterceptUrlLoading(const std::string& data)
{
    // TODO: add ng event.
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_RETURN(webCom, false);
    auto param = std::make_shared<UrlLoadInterceptEvent>(data);
    return webCom->OnUrlLoadIntercept(param.get());
}

void WebDelegate::OnResourceLoad(const std::string& url)
{
    if (onResourceLoadV2_) {
        onResourceLoadV2_(std::make_shared<ResourceLoadEvent>(url));
    }
}

void WebDelegate::OnScaleChange(float oldScaleFactor, float newScaleFactor)
{
    if (onScaleChangeV2_) {
        onScaleChangeV2_(std::make_shared<ScaleChangeEvent>(oldScaleFactor, newScaleFactor));
    }
}

void WebDelegate::OnScroll(double xOffset, double yOffset)
{
    if (onScrollV2_) {
        onScrollV2_(std::make_shared<OnScrollEvent>(xOffset, yOffset));
    }
}

void WebDelegate::OnSearchResultReceive(int activeMatchOrdinal, int numberOfMatches, bool isDoneCounting)
{
    if (onSearchResultReceiveV2_) {
        onSearchResultReceiveV2_(
            std::make_shared<SearchResultReceiveEvent>(activeMatchOrdinal, numberOfMatches, isDoneCounting));
    }
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
    return true;
}

RefPtr<PixelMap> WebDelegate::GetDragPixelMap()
{
    if (isRefreshPixelMap_) {
        isRefreshPixelMap_ = false;
        return pixelMap_;
    }

    return nullptr;
}

#ifdef OHOS_STANDARD_SYSTEM
void WebDelegate::HandleTouchDown(const int32_t& id, const double& x, const double& y)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        ResSchedReport::GetInstance().ResSchedDataReport("web_gesture");
        nweb_->OnTouchPress(id, x, y);
    }
}

void WebDelegate::HandleTouchUp(const int32_t& id, const double& x, const double& y)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        ResSchedReport::GetInstance().ResSchedDataReport("web_gesture");
        nweb_->OnTouchRelease(id, x, y);
    }
}

void WebDelegate::HandleTouchMove(const int32_t& id, const double& x, const double& y)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->OnTouchMove(id, x, y);
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
        nweb_->OnFocus();
    }
}

void WebDelegate::OnBlur()
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->OnBlur();
    }
}

bool WebDelegate::RunQuickMenu(std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback)
{
    // TODO: add ng pattern.
    auto renderWeb = renderWeb_.Upgrade();
    if (!renderWeb || !params || !callback) {
        LOGE("renderWeb is nullptr");
        return false;
    }

    return renderWeb->RunQuickMenu(params, callback);
}

void WebDelegate::OnQuickMenuDismissed()
{
    // TODO: add ng pattern.
    auto renderWeb = renderWeb_.Upgrade();
    CHECK_NULL_VOID(renderWeb);
    renderWeb->OnQuickMenuDismissed();
}

void WebDelegate::OnTouchSelectionChanged(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
    // TODO: add ng pattern.
    auto renderWeb = renderWeb_.Upgrade();
    CHECK_NULL_VOID(renderWeb);
    renderWeb->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
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

} // namespace OHOS::Ace
