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
#include <sstream>

#include "base/json/json_util.h"
#include "base/log/log.h"
#include "core/components/web/web_event.h"
#include "core/event/ace_event_helper.h"
#include "core/event/back_end_event_manager.h"
#include "frameworks/bridge/js_frontend/frontend_delegate_impl.h"
#ifdef OHOS_STANDARD_SYSTEM
#include "application_env.h"
#include "webview_adapter_helper.h"
#include "web_javascript_execute_callback.h"
#endif

namespace OHOS::Ace {

namespace {

constexpr char WEB_METHOD_RELOAD[] = "reload";
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

} // namespace

WebDelegate::~WebDelegate()
{
    ReleasePlatformResource();
}

void WebDelegate::ReleasePlatformResource()
{
    auto delegate = WeakClaim(this).Upgrade();
    if (delegate) {
        delegate->Stop();
        delegate->Release();
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
    auto context = context_.Upgrade();
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
            if (delegate->webview_) {
                delegate->webview_->LoadUrl(
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
            if (delegate->webview_) {
                delegate->webview_->GoBack();
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
            if (delegate->webview_) {
                delegate->webview_->GoForward();
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
    if (delegate->webview_) {
        return delegate->webview_->CanGoBackOrForward(step);
    }
    return false;
}

bool WebDelegate::AccessBackward()
{
    auto delegate = WeakClaim(this).Upgrade();
    if (!delegate) {
        LOGE("Get delegate failed, it is null.");
        return false;
    }
    if (delegate->webview_) {
        return delegate->webview_->CanGoBack();
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
    if (delegate->webview_) {
        return delegate->webview_->CanGoForward();
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
    context->GetTaskExecutor()->PostTask([weak = WeakClaim(this), jscode, callback]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->webview_) {
                auto callbackImpl = std::make_shared<WebJavaScriptExecuteCallBack>();
                if (callbackImpl && callback) {
                    callbackImpl->SetCallBack([weak, func = std::move(callback)](std::string result) {
                        auto delegate = weak.Upgrade();
                        if (!delegate) {
                            return;
                        }
                        auto context = delegate->context_.Upgrade();
                        if (context) {
                            context->GetTaskExecutor()->PostTask([callback = std::move(func), result]() {
                                callback(result);
                                }, TaskExecutor::TaskType::JS);
                        }
                    });
                }
                delegate->webview_->ExecuteJavaScript(jscode, callbackImpl);
            }
        }, TaskExecutor::TaskType::PLATFORM);
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
            if (delegate->webview_) {
                if (baseUrl.empty() && historyUrl.empty()) {
                    delegate->webview_->LoadData(data, mimeType, encoding);
                } else {
                    delegate->webview_->LoadDataWithBaseURL(baseUrl, data, mimeType, encoding, historyUrl);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
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
            if (delegate->webview_) {
                delegate->webview_->Reload();
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
            if (delegate->webview_) {
                delegate->webview_->StopLoading();
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

    context->GetTaskExecutor()->PostTask([weak = WeakClaim(this), objectName, methodList]() {
        auto delegate = weak.Upgrade();
        if (!delegate) {
            return;
        }
        if (delegate->webview_) {
            delegate->webview_->AddJavascriptInterface(objectName, methodList);
        }
        }, TaskExecutor::TaskType::PLATFORM);
}
void WebDelegate::RemoveJavascriptInterface(const std::string& objectName, const std::vector<std::string>& methodList)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    context->GetTaskExecutor()->PostTask([weak = WeakClaim(this), objectName, methodList]() {
        auto delegate = weak.Upgrade();
        if (!delegate) {
            return;
        }
        if (delegate->webview_) {
            delegate->webview_->RemoveJavascriptInterface(objectName, methodList);
        }
        }, TaskExecutor::TaskType::PLATFORM);
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
            if (delegate->webComponent_) {
                delegate->webComponent_->RequestFocus();
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

int WebDelegate::GetHitTestResult()
{
    if (webview_) {
        return webview_->GetHitTestResult().GetType();
    }
    return 0;
}

void WebDelegate::CreatePluginResource(
    const Size& size, const Offset& position, const WeakPtr<PipelineContext>& context)
{
    state_ = State::CREATING;

    auto webCom = webComponent_;
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
        auto webCom = webDelegate->webComponent_;
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
    auto webCom = webComponent_;
    if (!webCom) {
        state_ = State::CREATEFAILED;
        OnError(NTC_ERROR, "fail to call WebDelegate::Create due to webComponent is null");
        return;
    }
    if (!webCom->GetPageStartedEventId().IsEmpty()) {
        onPageStarted_ = AceAsyncEvent<void(const std::string&)>::Create(webCom->GetPageStartedEventId(), context_);
    }
    if (!webCom->GetPageFinishedEventId().IsEmpty()) {
        onPageFinished_ = AceAsyncEvent<void(const std::string&)>::Create(webCom->GetPageFinishedEventId(), context_);
    }
    if (!webCom->GetPageErrorEventId().IsEmpty()) {
        onPageError_ = AceAsyncEvent<void(const std::string&)>::Create(webCom->GetPageErrorEventId(), context_);
    }
    if (!webCom->GetMessageEventId().IsEmpty()) {
        onMessage_ = AceAsyncEvent<void(const std::string&)>::Create(webCom->GetMessageEventId(), context_);
    }
}

#ifdef OHOS_STANDARD_SYSTEM
void WebDelegate::InitOHOSWeb(const WeakPtr<PipelineContext>& context, sptr<Surface> surface)
{
    state_ = State::CREATING;
    // load webview so
    if (!OHOS::WebView::WebViewHelper::Instance().Init()) {
        LOGE("Fail to init WebViewHelper");
        return;
    }

    auto webCom = webComponent_;
    if (!webCom) {
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
    onPageFinishedV2_ = AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
        webComponent_->GetPageFinishedEventId(), pipelineContext);
    onRequestFocusV2_ = AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
        webComponent_->GetRequestFocusEventId(), pipelineContext);
}

void WebDelegate::SetWebCallBack()
{
    auto webController = webComponent_->GetController();
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
        webController->SetAccessStepImpl([weak = WeakClaim(this)](int32_t step) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->AccessStep(step);
            }
            return false;
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
        webController->SetAddJavascriptInterfaceImpl([weak = WeakClaim(this), uiTaskExecutor](
            std::string objectName, const std::vector<std::string>& methodList) {
                uiTaskExecutor.PostTask([weak, objectName, methodList]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->AddJavascriptInterface(objectName, methodList);
                    }
                });
            });
        webController->SetRemoveJavascriptInterfaceImpl([weak = WeakClaim(this), uiTaskExecutor](
            std::string objectName, const std::vector<std::string>& methodList) {
                uiTaskExecutor.PostTask([weak, objectName, methodList]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->RemoveJavascriptInterface(objectName, methodList);
                    }
                });
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
    }
}

void WebDelegate::InitWebViewWithWindow()
{
    LOGI("Create webview with window");
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
            OHOS::WebView::WebViewInitArgs initArgs;
            std::string app_path = GetDataPath();
            if (!app_path.empty()) {
                initArgs.web_engine_args_to_add.push_back(std::string("--user-data-dir=").append(app_path));
            }

            delegate->window_ = delegate->CreateWindow();
            if (!delegate->window_) {
                return;
            }
            delegate->webview_ =
                OHOS::WebView::WebViewAdapterHelper::Instance().CreateWebView(delegate->window_.GetRefPtr(), initArgs);
            if (delegate->webview_ == nullptr) {
                delegate->window_ = nullptr;
                LOGE("fail to get webview instance");
                return;
            }
            auto component = delegate->webComponent_;
            if (!component) {
                return;
            }
            bool isJsEnabled = component->GetJsEnabled();
            bool isContentAccessEnabled = component->GetContentAccessEnabled();
            bool isFileAccessEnabled = component->GetFileAccessEnabled();

            auto webviewClient = std::make_shared<WebClientImpl>();
            webviewClient->SetWebDelegate(weak);
            delegate->webview_->SetWebViewClient(webviewClient);
            std::shared_ptr<OHOS::WebView::WebSettings> setting = delegate->webview_->GetSettings();
            setting->SetDomStorageEnabled(true);
            setting->SetJavaScriptCanOpenWindowsAutomatically(true);
            setting->SetJavaScriptEnabled(isJsEnabled);
            setting->SetAllowFileAccess(isFileAccessEnabled);
            setting->SetAllowContentAccess(isContentAccessEnabled);

            delegate->webview_->LoadURL(component->GetSrc());
            delegate->window_->Show();
        },
        TaskExecutor::TaskType::PLATFORM);
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
            if (!delegate) {
                return;
            }
            OHOS::WebView::WebViewInitArgs initArgs;
            const std::string& app_path = GetDataPath();
            if (!app_path.empty()) {
                initArgs.web_engine_args_to_add.push_back(std::string("--user-data-dir=").append(app_path));
            }

            sptr<Surface> surface = surfaceWeak.promote();
            if (surface == nullptr) {
                LOGE("surface is nullptr or has expired");
                return;
            }
            delegate->webview_ =
                OHOS::WebView::WebViewAdapterHelper::Instance().CreateWebView(surface, initArgs);
            if (delegate->webview_ == nullptr) {
                LOGE("fail to get webview instance");
                return;
            }
            auto component = delegate->webComponent_;
            if (component == nullptr) {
                return;
            }
            auto webviewClient = std::make_shared<WebClientImpl>();
            webviewClient->SetWebDelegate(weak);
            delegate->webview_->SetWebViewClient(webviewClient);
            std::shared_ptr<OHOS::WebView::WebSettings> setting = delegate->webview_->GetSettings();
            setting->SetDomStorageEnabled(true);
            setting->SetJavaScriptCanOpenWindowsAutomatically(true);
            setting->SetJavaScriptEnabled(component->GetJsEnabled());
            setting->SetAllowFileAccess(component->GetFileAccessEnabled());
            setting->SetAllowContentAccess(component->GetContentAccessEnabled());
        },
        TaskExecutor::TaskType::PLATFORM);
}
#endif

void WebDelegate::Resize(const double& width, const double& height)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), width, height] () {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->webview_ && !delegate->window_) {
                delegate->webview_->Resize(width, height);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void WebDelegate::LoadUrl()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)] () {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->webview_) {
                delegate->webview_->LoadURL(delegate->webComponent_->GetSrc());
            }
        },
        TaskExecutor::TaskType::PLATFORM);
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
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
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

// upper ui componnet which inherite from WebComponent
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
    hash_ = MakeResourceHash();
    reloadMethod_ = MakeMethodHash(WEB_METHOD_RELOAD);
    CallResRegisterMethod(reloadMethod_, WEB_PARAM_NONE, nullptr);
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

void WebDelegate::OnRequestFocus()
{
    if (onRequestFocusV2_) {
        onRequestFocusV2_(std::make_shared<LoadWebRequestFocusEvent>(""));
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

#ifdef OHOS_STANDARD_SYSTEM
void WebDelegate::HandleTouchDown(const int32_t& id, const double& x, const double& y)
{
    ACE_DCHECK(webview_ != nullptr);
    webview_->OnTouchPress(id, x, y);
}

void WebDelegate::HandleTouchUp(const int32_t& id, const double& x, const double& y)
{
    ACE_DCHECK(webview_ != nullptr);
    webview_->OnTouchRelease(id, x, y);
}

void WebDelegate::HandleTouchMove(const int32_t& id, const double& x, const double& y)
{
    ACE_DCHECK(webview_ != nullptr);
    webview_->OnTouchMove(id, x, y);
}

void WebDelegate::HandleTouchCancel()
{
    ACE_DCHECK(webview_ != nullptr);
    webview_->OnTouchCancel();
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

} // namespace OHOS::Ace
