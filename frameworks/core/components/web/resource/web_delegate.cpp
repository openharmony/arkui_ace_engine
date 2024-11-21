/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include <cctype>
#include <cfloat>
#include <iomanip>
#include <optional>
#include <sstream>

#include "event_handler.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/utils.h"
#include "base/json/json_util.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/memory/referenced.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/utils.h"
#include "base/perfmonitor/perf_monitor.h"
#include "core/accessibility/accessibility_manager.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/web/render_web.h"
#include "adapter/ohos/capability/html/span_to_html.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "core/components_ng/render/adapter/rosen_render_context.h"
#endif
#include "frameworks/bridge/js_frontend/frontend_delegate_impl.h"
#ifdef OHOS_STANDARD_SYSTEM
#include "application_env.h"
#include "iservice_registry.h"
#include "nweb_adapter_helper.h"
#include "nweb_handler.h"
#include "parameters.h"
#include "screen_manager/screen_types.h"
#include "system_ability_definition.h"
#include "unicode/ucnv.h"
#include "transaction/rs_interfaces.h"
#include "web_configuration_observer.h"
#include "web_javascript_execute_callback.h"
#include "web_javascript_result_callback.h"

#include "core/components_ng/base/ui_node.h"
#include "frameworks/base/utils/system_properties.h"
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
const std::string RESOURCE_CLIPBOARD_READ_WRITE = "TYPE_CLIPBOARD_READ_WRITE";
const std::string RESOURCE_SENSOR = "TYPE_SENSOR";
const std::string DEFAULT_CANONICAL_ENCODING_NAME = "UTF-8";

constexpr uint32_t DRAG_DELAY_MILLISECONDS = 300;
constexpr uint32_t ACCESSIBILITY_DELAY_MILLISECONDS = 100;
constexpr uint32_t DELAY_MILLISECONDS_1000 = 1000;
constexpr uint32_t NO_NATIVE_FINGER_TYPE = 100;
const std::string DEFAULT_NATIVE_EMBED_ID = "0";

const std::vector<std::string> CANONICALENCODINGNAMES = {
    "Big5",         "EUC-JP",       "EUC-KR",       "GB18030",
    "GBK",          "IBM866",       "ISO-2022-JP",  "ISO-8859-10",
    "ISO-8859-13",  "ISO-8859-14",  "ISO-8859-15",  "ISO-8859-16",
    "ISO-8859-1",   "ISO-8859-2",   "ISO-8859-3",   "ISO-8859-4",
    "ISO-8859-5",   "ISO-8859-6",   "ISO-8859-7",   "ISO-8859-8",
    "ISO-8859-8-I", "KOI8-R",       "KOI8-U",       "macintosh",
    "Shift_JIS",    "UTF-8",        "windows-1250", "windows-1251",
    "windows-1252", "windows-1253", "windows-1254", "windows-1255",
    "windows-1256", "windows-1257", "windows-1258", "windows-874" };

#define VISIBLERATIO_LENGTH 4
#define VISIBLERATIO_FLOAT_TO_INT 100

static bool IsDeviceTabletOr2in1()
{
    return OHOS::system::GetDeviceType() == "tablet" || OHOS::system::GetDeviceType() == "2in1";
}

static bool GetWebOptimizationValue()
{
    return OHOS::system::GetBoolParameter("web.optimization", true);
}
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
        return;
    }
    delegate->ClosePort(handle_);
}

void WebMessagePortOhos::PostMessage(std::string& data)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->PostPortMessage(handle_, data);
}

void WebMessagePortOhos::SetWebMessageCallback(std::function<void(const std::string&)>&& callback)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
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

void AllSslErrorResultOhos::HandleConfirm()
{
    if (result_) {
        result_->HandleConfirm();
    }
}

void AllSslErrorResultOhos::HandleCancel()
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
        if (resourcesId & OHOS::NWeb::NWebAccessRequest::Resources::CLIPBOARD_READ_WRITE) {
            resources.push_back(RESOURCE_CLIPBOARD_READ_WRITE);
        }
        if (resourcesId & OHOS::NWeb::NWebAccessRequest::Resources::SENSORS) {
            resources.push_back(RESOURCE_SENSOR);
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
            } else if (res == RESOURCE_CLIPBOARD_READ_WRITE) {
                resourcesId |= OHOS::NWeb::NWebAccessRequest::Resources::CLIPBOARD_READ_WRITE;
            } else if (res == RESOURCE_SENSOR) {
                resourcesId |= OHOS::NWeb::NWebAccessRequest::Resources::SENSORS;
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
    config_->SetMode(mode);
}

void WebScreenCaptureRequestOhos::SetSourceId(int32_t sourceId)
{
    config_->SetSourceId(sourceId);
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

void ContextMenuParamOhos::GetImageRect(int32_t& x, int32_t& y, int32_t& width, int32_t& height) const
{
    if (param_) {
        param_->GetImageRect(x, y, width, height);
    }
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

NWebScreenLockCallbackImpl::NWebScreenLockCallbackImpl(const WeakPtr<PipelineBase>& context) : context_(context) {}

void NWebScreenLockCallbackImpl::Handle(bool key)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "SetKeepScreenOn %{public}d", key);
    auto weakContext = context_.Upgrade();
    CHECK_NULL_VOID(weakContext);
    auto window = weakContext->GetWindow();
    CHECK_NULL_VOID(window);
    window->SetKeepScreenOn(key);
}

WebDelegateObserver::~WebDelegateObserver() {}

void WebDelegateObserver::NotifyDestory()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "NotifyDestory start");
    if (delegate_) {
        delegate_->UnRegisterScreenLockFunction();
    }
    auto context = context_.Upgrade();
    if (!context) {
        TAG_LOGD(AceLogTag::ACE_WEB, "NotifyDestory context is null, use EventHandler to destory");
        auto currentHandler = OHOS::AppExecFwk::EventHandler::Current();
        if (!currentHandler) {
            TAG_LOGE(AceLogTag::ACE_WEB, "NWEB webdelegateObserver EventHandler currentHandler is null");
            return;
        }
        currentHandler->PostTask(
            [weak = WeakClaim(this), currentHandler = currentHandler]() {
                auto observer = weak.Upgrade();
                if (!observer) {
                    TAG_LOGE(AceLogTag::ACE_WEB, "NotifyDestory EventHandler observer is null");
                    return;
                }
                if (observer->delegate_) {
                    TAG_LOGD(AceLogTag::ACE_WEB, "NotifyDestory EventHandler destorying delegate");
                    observer->delegate_.Reset();
                }
            }
        );
        return;
    }
    auto taskExecutor = context->GetTaskExecutor();
    if (!taskExecutor) {
        TAG_LOGE(AceLogTag::ACE_WEB, "NotifyDestory TaskExecutor is null");
        return;
    }
    taskExecutor->PostTask(
        [weak = WeakClaim(this), taskExecutor = taskExecutor]() {
            auto observer = weak.Upgrade();
            if (!observer) {
                TAG_LOGE(AceLogTag::ACE_WEB, "NotifyDestory TaskExecutor observer is null");
                return;
            }
            if (observer->delegate_) {
                TAG_LOGD(AceLogTag::ACE_WEB, "NotifyDestory TaskExecutor destorying delegate");
                observer->delegate_.Reset();
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIWebNotifyDestory");
}

void WebDelegateObserver::OnAttachContext(const RefPtr<NG::PipelineContext> &context)
{
    context_ = context;
}

void WebDelegateObserver::OnDetachContext()
{
    context_ = nullptr;
}

void GestureEventResultOhos::SetGestureEventResult(bool result)
{
    if (result_) {
        result_->SetGestureEventResult(result);
        SetSendTask();
        eventResult_ = result;
    }
}

void GestureEventResultOhos::SetGestureEventResult(bool result, bool stopPropagation)
{
    if (result_) {
        result_->SetGestureEventResultV2(result, stopPropagation);
        SetSendTask();
        eventResult_ = result;
    }
}

void WebDelegate::UnRegisterScreenLockFunction()
{
    if (nweb_) {
        nweb_->UnRegisterScreenLockFunction(instanceId_);
    }
}

void WebAvoidAreaChangedListener::OnAvoidAreaChanged(
    const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type)
{
    if (auto delegate = webDelegate_.Upgrade()) {
        delegate->OnAvoidAreaChanged(avoidArea, type);
    }
}

WebDelegate::~WebDelegate()
{
    SetAccessibilityState(false, false);
    OnNativeEmbedAllDestory();
    ReleasePlatformResource();
    if (IsDeviceTabletOr2in1() && GetWebOptimizationValue()) {
        OHOS::Rosen::RSInterfaces::GetInstance().UnRegisterSurfaceOcclusionChangeCallback(surfaceNodeId_);
    }
    if (nweb_) {
        nweb_->OnDestroy();
    }
    UnregisterSurfacePositionChangedCallback();
    UnregisterAvoidAreaChangeListener(instanceId_);
    UnRegisterConfigObserver();
}

void WebDelegate::ReleasePlatformResource()
{
    Stop();
    Release();
}

void WebGeolocationOhos::Invoke(const std::string& origin, const bool& allow, const bool& retain)
{
    if (geolocationCallback_) {
        geolocationCallback_->GeolocationCallbackInvoke(origin, allow, retain,
            incognito_);
    }
}

void WebDelegate::Stop()
{
    auto context = context_.Upgrade();
    if (!context) {
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
        }, "ArkUIWebUnregisterEvent");
    }
}

void WebDelegate::UnregisterEvent()
{
    auto context = DynamicCast<PipelineContext>(context_.Upgrade());
    if (!context) {
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
    auto pipeline = context.Upgrade();
    if (pipeline) {
        taskExecutor_ = pipeline->GetTaskExecutor();
    }
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebLoadUrl");
}

#ifdef OHOS_STANDARD_SYSTEM
void WebDelegate::Backward()
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
                delegate->nweb_->NavigateBack();
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebNavigateBack");
}

void WebDelegate::Forward()
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
                delegate->nweb_->NavigateForward();
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebNavigateForward");
}

void WebDelegate::ClearHistory()
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
                delegate->nweb_->DeleteNavigateHistory();
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebDeleteNavigateHistory");
}

void WebDelegate::ClearSslCache()
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
                delegate->nweb_->ClearSslCache();
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebClearSslCache");
}

void WebDelegate::ClearClientAuthenticationCache()
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
                delegate->nweb_->ClearClientAuthenticationCache();
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebClearClientAuthenticationCache");
}

bool WebDelegate::AccessStep(int32_t step)
{
    auto delegate = WeakClaim(this).Upgrade();
    if (!delegate) {
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
        return;
    }

    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), step] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->NavigateBackOrForward(step);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebNavigateBackOrForward");
}

bool WebDelegate::AccessBackward()
{
    auto delegate = WeakClaim(this).Upgrade();
    if (!delegate) {
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
                auto callbackImpl = std::make_shared<WebJavaScriptExecuteCallBack>(weak);
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
                                TaskExecutor::TaskType::JS, "ArkUIWebJavaScriptExecuteCallBack");
                        }
                    });
                }
                delegate->nweb_->ExecuteJavaScript(jscode, callbackImpl, false);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebExecuteJavaScript");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebLoadDataWithBaseUrl");
}

bool WebDelegate::LoadDataWithRichText()
{
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }
#ifdef NG_BUILD
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
                delegate->nweb_->LoadWithDataAndBaseUrl("resource://rawfile", data, "", "", "");
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebLoadDataWithRichText");
    return true;
#else
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
                    delegate->nweb_->LoadWithDataAndBaseUrl("resource://rawfile", data, "", "", "");
                }
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUIWebLoadDataWithRichText");
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
                delegate->nweb_->LoadWithDataAndBaseUrl("resource://rawfile", data, "", "", "");
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebLoadDataWithRichText");
    return true;
#endif
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebRefresh");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebStopLoading");
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
                // Async methods list is empty
                std::vector<std::string> asyncMethodList;
                std::string permission;
                // webcontroller not support object, so the object_id param
                // assign error code
                delegate->nweb_->RegisterArkJSfunction(
                    objectName, methodList, asyncMethodList,
                    static_cast<int32_t>(JavaScriptObjIdErrorCode::WEBCONTROLLERERROR),
                    permission);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebAddJsInterface");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebRemoveJsInterface");
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
            auto webJSResultCallBack = std::make_shared<WebJavaScriptResultCallBack>(weak);
            if (webJSResultCallBack) {
                webJSResultCallBack->SetJavaScriptCallBack(std::move(javaScriptCallBackImpl));
                delegate->nweb_->SetNWebJavaScriptResultCallBack(webJSResultCallBack);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebSetJsResultCallBack");
}

void WebDelegate::CreateWebMessagePorts(std::vector<RefPtr<WebMessagePort>>& ports)
{
    if (nweb_) {
        std::vector<std::string> portStr = nweb_->CreateWebMessagePorts();
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
        auto callbackImpl = std::make_shared<WebMessageValueCallBackImpl>(WeakClaim(this));
        if (callbackImpl && callback) {
            callbackImpl->SetCallBack([weak = WeakClaim(this), func = std::move(callback)](std::string result) {
                auto delegate = weak.Upgrade();
                if (!delegate) {
                    return;
                }
                auto context = delegate->context_.Upgrade();
                if (context) {
                    context->GetTaskExecutor()->PostTask(
                        [callback = std::move(func), result]() { callback(result); },
                        TaskExecutor::TaskType::JS, "ArkUIWebSetPortMessageCallback");
                }
            });
        }
        nweb_->SetPortMessageCallback(port, callbackImpl);
    }
}

bool WebDelegate::RequestFocus(OHOS::NWeb::NWebFocusSource source)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    bool result = false;
    context->GetTaskExecutor()->PostSyncTask(
        [weak = WeakClaim(this), &result, source]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);

            if (Container::IsCurrentUseNewPipeline()) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                if (webPattern->IsFocus()) {
                    result = true;
                    return;
                }
                auto eventHub = webPattern->GetWebEventHub();
                CHECK_NULL_VOID(eventHub);
                auto focusHub = eventHub->GetOrCreateFocusHub();
                CHECK_NULL_VOID(focusHub);
                if (source == OHOS::NWeb::NWebFocusSource::FOCUS_SOURCE_NAVIGATION &&
                    webPattern->IsDefaultFocusNodeExist() && !focusHub->IsDefaultFocus()) {
                    TAG_LOGI(AceLogTag::ACE_WEB, "there are other default focusNodes, web don't focus on navigation");
                    result = false;
                    return;
                }

                auto host = webPattern->GetHost();
                CHECK_NULL_VOID(host);
                if (host->IsOnMainTree()) {
                    focusHub->RequestFocus();
                    result = false;
                }
                return;
            }

            auto webCom = delegate->webComponent_.Upgrade();
            CHECK_NULL_VOID(webCom);
            result = webCom->RequestFocus();
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebRequestFocus");
    return result;
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebSearchAllAsync");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebClearMatches");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebSearchNext");
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
            webHitType = WebHitTestType::UNKNOWN;
            break;
    }
    return static_cast<int>(webHitType);
}

int WebDelegate::GetHitTestResult()
{
    if (nweb_) {
        std::shared_ptr<OHOS::NWeb::HitTestResult> nwebResult = nweb_->GetHitTestResult();
        if (nwebResult) {
            return ConverToWebHitTestType(nwebResult->GetType());
        }
        return ConverToWebHitTestType(OHOS::NWeb::HitTestResult::UNKNOWN_TYPE);
    }
    return static_cast<int>(WebHitTestType::UNKNOWN);
}

void WebDelegate::GetHitTestValue(HitTestResult& result)
{
    if (nweb_) {
        std::shared_ptr<OHOS::NWeb::HitTestResult> nwebResult = nweb_->GetHitTestResult();
        if (nwebResult) {
            result.SetExtraData(nwebResult->GetExtra());
            result.SetHitType(ConverToWebHitTestType(nwebResult->GetType()));
        } else {
            result.SetHitType(ConverToWebHitTestType(OHOS::NWeb::HitTestResult::UNKNOWN_TYPE));
        }
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

bool WebDelegate::SetCookie(const std::string& url,
                            const std::string& value,
                            bool incognitoMode)
{
    if (cookieManager_) {
        return cookieManager_->SetCookie(url, value, incognitoMode);
    }
    return false;
}

std::string WebDelegate::GetCookie(const std::string& url,
                                   bool incognitoMode) const
{
    if (cookieManager_) {
        bool isValid = true;
        return cookieManager_->ReturnCookie(url, isValid, incognitoMode);
    }
    return "";
}

void WebDelegate::DeleteEntirelyCookie(bool incognitoMode)
{
    if (cookieManager_) {
        cookieManager_->DeleteCookieEntirely(nullptr, incognitoMode);
    }
}

void WebDelegate::CreatePluginResource(
    const Size& size, const Offset& position, const WeakPtr<PipelineContext>& context)
{
    state_ = State::CREATING;
    auto webCom = webComponent_.Upgrade();
    if (!webCom) {
        state_ = State::CREATEFAILED;
        OnError(NTC_ERROR, "fail to call WebDelegate::Create due to webComponent is null");
        return;
    }

    auto pipelineContext = context.Upgrade();
    if (!pipelineContext) {
        state_ = State::CREATEFAILED;
        OnError(NTC_ERROR, "fail to call WebDelegate::Create due to context is null");
        return;
    }
    context_ = context;
    taskExecutor_ = pipelineContext->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor_);
    auto platformTaskExecutor =
        SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::PLATFORM);
    auto resRegister = pipelineContext->GetPlatformResRegister();
    auto weakRes = AceType::WeakClaim(AceType::RawPtr(resRegister));
    platformTaskExecutor.PostTask([weakWeb = AceType::WeakClaim(this), weakRes, size, position] {
        auto webDelegate = weakWeb.Upgrade();
        if (webDelegate == nullptr) {
            return;
        }
        auto webCom = webDelegate->webComponent_.Upgrade();
        if (!webCom) {
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
        if (webDelegate->id_ == WEB_INVALID_ID) {
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
    }, "ArkUIWebCreatePluginResource");
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

    OnActive();
    OnWebviewShow();
}

void WebDelegate::HideWebView()
{
    if (window_) {
        window_->Hide();
    }

    OnInactive();
    OnWebviewHide();
}

void WebDelegate::InitOHOSWeb(const RefPtr<PipelineBase>& context, const RefPtr<NG::RenderSurface>& surface)
{
#ifdef ENABLE_ROSEN_BACKEND
    CHECK_NULL_VOID(context);
    auto rosenRenderSurface = DynamicCast<NG::RosenRenderSurface>(surface);
    if (!rosenRenderSurface) {
        if (PrepareInitOHOSWeb(context)) {
            if (!isCreateWebView_) {
#ifndef ENABLE_ROSEN_BACKEND
                InitWebViewWithWindow();
                isCreateWebView_ = true;
#endif
            }
        }
        return;
    }
    if (renderMode_ == static_cast<int32_t>(RenderMode::SYNC_RENDER)) {
        renderSurface_ = rosenRenderSurface;
    }
    SetSurface(rosenRenderSurface->GetSurface());
    InitOHOSWeb(context);
#endif
}

bool WebDelegate::PrepareInitOHOSWeb(const WeakPtr<PipelineBase>& context)
{
    ACE_SCOPED_TRACE("PrepareInitOHOSWeb");

    state_ = State::CREATING;
    // obtain hap data path
    auto container = Container::Current();
    if (container == nullptr) {
        return false;
    }
    const std::string& bundlePath = container->GetBundlePath();
    const std::string& filesDataPath = container->GetFilesDataPath();
    std::string baseDir = "base";
    std::size_t baseIndex = filesDataPath.find(baseDir);
    if (baseIndex == std::string::npos) {
        return false;
    }
    std::string dataPath = filesDataPath.substr(0, baseIndex + baseDir.length());
    bundlePath_ = bundlePath;
    bundleDataPath_ = dataPath;
    hapPath_ = container->GetWebHapPath();
    // get app temp dir
    tempDir_ = container->GetTempDir();
    // load webview so
    OHOS::NWeb::NWebHelper::Instance().SetBundlePath(bundlePath_);
    if (!OHOS::NWeb::NWebHelper::Instance().Init()) {
        return false;
    }
    auto webCom = webComponent_.Upgrade();
    auto webPattern = webPattern_.Upgrade();
    auto eventHub = webPattern ? webPattern->GetWebEventHub() : nullptr;
    auto useNewPipe = Container::IsCurrentUseNewPipeline();
    if (useNewPipe && !webPattern && !eventHub) {
        return false;
    }
    if (!useNewPipe && !webCom) {
        return false;
    }
    incognitoMode_ =
        useNewPipe ? webPattern->GetIncognitoMode() : webCom->GetIncognitoMode();
    auto sharedRenderProcessToken =
        useNewPipe ? webPattern->GetSharedRenderProcessToken() : webCom->GetSharedRenderProcessToken();
    sharedRenderProcessToken_ = sharedRenderProcessToken ? sharedRenderProcessToken.value() : "";
    context_ = context;
    RegisterSurfacePositionChangedCallback();
    auto pipelineContext = context.Upgrade();
    if (!pipelineContext) {
        return false;
    }
    taskExecutor_ = pipelineContext->GetTaskExecutor();
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
        OnFirstMeaningfulPaintV2_ = useNewPipe ? eventHub->GetOnFirstMeaningfulPaintEvent() : nullptr;
        OnLargestContentfulPaintV2_ = useNewPipe ? eventHub->GetOnLargestContentfulPaintEvent() : nullptr;
        onSafeBrowsingCheckResultV2_ = useNewPipe ? eventHub->GetOnSafeBrowsingCheckResultEvent() : nullptr;
        onOverScrollV2_ = useNewPipe ? eventHub->GetOnOverScrollEvent()
                                     : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                         webCom->GetOverScrollId(), oldContext);
        onScreenCaptureRequestV2_ = useNewPipe ? eventHub->GetOnScreenCaptureRequestEvent() : nullptr;
        onNavigationEntryCommittedV2_ = useNewPipe ? eventHub->GetOnNavigationEntryCommittedEvent() : nullptr;
        OnNativeEmbedAllDestoryV2_ = useNewPipe ? eventHub->GetOnNativeEmbedLifecycleChangeEvent() : nullptr;
        OnNativeEmbedLifecycleChangeV2_ = useNewPipe ? eventHub->GetOnNativeEmbedLifecycleChangeEvent()
                                            : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                                webCom->GetNativeEmbedLifecycleChangeId(), oldContext);
        OnNativeEmbedVisibilityChangeV2_ = useNewPipe ? eventHub->GetOnNativeEmbedVisibilityChangeEvent()
                                            : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                                webCom->GetNativeEmbedVisibilityChangeId(), oldContext);
        OnNativeEmbedGestureEventV2_ = useNewPipe ? eventHub->GetOnNativeEmbedGestureEvent()
                                            : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                                webCom->GetNativeEmbedGestureEventId(), oldContext);
        onIntelligentTrackingPreventionResultV2_ = useNewPipe ?
            eventHub->GetOnIntelligentTrackingPreventionResultEvent() : nullptr;
        onRenderProcessNotRespondingV2_ = useNewPipe
                                              ? eventHub->GetOnRenderProcessNotRespondingEvent()
                                              : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::
                                                Create(webCom->GetRenderProcessNotRespondingId(), oldContext);
        onRenderProcessRespondingV2_ = useNewPipe ? eventHub->GetOnRenderProcessRespondingEvent()
                                                  : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::
                                                Create(webCom->GetRenderProcessRespondingId(), oldContext);
        onViewportFitChangedV2_ = useNewPipe ? eventHub->GetOnViewportFitChangedEvent()
                                       : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                           webCom->GetViewportFitChangedId(), oldContext);
        onInterceptKeyboardAttachV2_ = useNewPipe ? eventHub->GetOnInterceptKeyboardAttachEvent()
                                                  : nullptr;
        onAdsBlockedV2_ = useNewPipe ? eventHub->GetOnAdsBlockedEvent()
                                     : AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(
                                         webCom->GetAdsBlockedEventId(), oldContext);
    }
    return true;
}

void WebSurfaceCallback::OnSurfaceCreated(const sptr<OHOS::Surface>& surface) {}

void WebSurfaceCallback::OnSurfaceChanged(const sptr<OHOS::Surface>& surface, int32_t width, int32_t height)
{
    auto delegate = delegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->Resize((double)width, (double)height);
}

void WebSurfaceCallback::OnSurfaceDestroyed() {}

EGLConfig WebDelegate::GLGetConfig(int version, EGLDisplay eglDisplay)
{
    int attribList[] = { EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8, EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_NONE };
    EGLConfig configs = NULL;
    int configsNum;
    if (!eglChooseConfig(eglDisplay, attribList, &configs, 1, &configsNum)) {
        return NULL;
    }
    return configs;
}

void WebDelegate::GLContextInit(void* window)
{
    if (!window) {
        return;
    }
    mEglWindow = static_cast<EGLNativeWindowType>(window);

    // 1. create sharedcontext
    mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        return;
    }

    EGLint eglMajVers, eglMinVers;
    if (!eglInitialize(mEGLDisplay, &eglMajVers, &eglMinVers)) {
        mEGLDisplay = EGL_NO_DISPLAY;
        return;
    }

    mEGLConfig = GLGetConfig(EGLCONFIG_VERSION, mEGLDisplay);
    if (mEGLConfig == nullptr) {
        return;
    }

    // 2. Create EGL Surface from Native Window
    mEGLSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, mEglWindow, nullptr);
    if (mEGLSurface == nullptr) {
        return;
    }

    // 3. Create EGLContext from
    int attrib3_list[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

    mEGLContext = eglCreateContext(mEGLDisplay, mEGLConfig, mSharedEGLContext, attrib3_list);

    if (!eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext)) {
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
        return false;
    }
    uint32_t windowId = pipelineContext->GetWindowId();
    surfaceDelegate_ = new OHOS::SurfaceDelegate(windowId);
    if (surfaceDelegate_ == nullptr) {
        return false;
    }
    surfaceCallback_ = new WebSurfaceCallback(AceType::WeakClaim(this));
    if (surfaceCallback_ == nullptr) {
        return false;
    }
    surfaceDelegate_->AddSurfaceCallback(surfaceCallback_);
    surfaceDelegate_->CreateSurface();
    SetBoundsOrResize(drawSize_, offset_);
    needResizeAtFirst_ = true;
    auto aNativeSurface = surfaceDelegate_->GetNativeWindow();
    if (aNativeSurface == nullptr) {
        return false;
    }
    GLContextInit(aNativeSurface);
    surfaceInfo_.window = aNativeSurface;
    return true;
}

void WebDelegate::InitOHOSWeb(const WeakPtr<PipelineBase>& context)
{
    if (!PrepareInitOHOSWeb(context)) {
        return;
    }
    if (!isCreateWebView_) {
        isCreateWebView_ = true;
        if (isEnhanceSurface_) {
            if (!InitWebSurfaceDelegate(context)) {
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
        std::shared_ptr<OHOS::NWeb::NWeb> parentNWeb = OHOS::NWeb::NWebHelper::Instance().GetNWeb(parentNWebId_);
        if (parentNWeb) {
            parentNWeb->NotifyPopupWindowResult(result);
        }
    }
}

void WebDelegate::RunSetWebIdAndHapPathCallback()
{
    CHECK_NULL_VOID(nweb_);
    auto webId = nweb_->GetWebId();

#ifdef NG_BUILD
    auto pattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto setWebIdCallback = pattern->GetSetWebIdCallback();
    CHECK_NULL_VOID(setWebIdCallback);
    setWebIdCallback(webId);
    if (!hapPath_.empty()) {
        auto setHapPathCallback = pattern->GetSetHapPathCallback();
        CHECK_NULL_VOID(setHapPathCallback);
        setHapPathCallback(hapPath_);
    }
    auto onControllerAttachedCallback = pattern->GetOnControllerAttachedCallback();
    if (onControllerAttachedCallback) {
        onControllerAttachedCallback();
    }
    NotifyPopupWindowResult(true);
    return;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        auto pattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto setWebIdCallback = pattern->GetSetWebIdCallback();
        CHECK_NULL_VOID(setWebIdCallback);
        setWebIdCallback(webId);
        if (!hapPath_.empty()) {
            auto setHapPathCallback = pattern->GetSetHapPathCallback();
            CHECK_NULL_VOID(setHapPathCallback);
            setHapPathCallback(hapPath_);
        }
        auto onControllerAttachedCallback = pattern->GetOnControllerAttachedCallback();
        if (onControllerAttachedCallback) {
            onControllerAttachedCallback();
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
#endif
}

void WebDelegate::RunJsProxyCallback()
{
#ifdef NG_BUILD
    auto pattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->CallJsProxyCallback();
    return;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        auto pattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->CallJsProxyCallback();
        return;
    }
    auto webCom = webComponent_.Upgrade();
    CHECK_NULL_VOID(webCom);
    webCom->CallJsProxyCallback();
#endif
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
            auto abilityContext = OHOS::AbilityRuntime::Context::GetApplicationContext();
            CHECK_NULL_VOID(abilityContext);
            delegate->configChangeObserver_ = std::make_shared<WebConfigurationObserver>(delegate);
            if (delegate->configChangeObserver_) {
                abilityContext->RegisterEnvironmentCallback(delegate->configChangeObserver_);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebAddConfigObserver");
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
            CHECK_NULL_VOID(delegate->configChangeObserver_);
            auto abilityContext = OHOS::AbilityRuntime::Context::GetApplicationContext();
            CHECK_NULL_VOID(abilityContext);
            abilityContext->UnregisterEnvironmentCallback(delegate->configChangeObserver_);
            delegate->configChangeObserver_.reset();
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebRemoveConfigObserver");
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
            }, "ArkUIWebControllerLoadUrl");
        });
        webController->SetBackwardImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->Backward();
                }
            }, "ArkUIWebBackward");
        });
        webController->SetForwardImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->Forward();
                }
            }, "ArkUIWebForward");
        });
        webController->SetClearHistoryImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->ClearHistory();
                }
            }, "ArkUIWebClearHistory");
        });
        webController->SetClearSslCacheImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->ClearSslCache();
                }
            }, "ArkUIWebControllerClearSslCache");
        });
        webController->SetClearClientAuthenticationCacheImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->ClearClientAuthenticationCache();
                }
            }, "ArkUIWebControllerClearClientAuthnCache");
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
            }, "ArkUIWebExecuteTypeScript");
        });
        webController->SetLoadDataWithBaseUrlImpl(
            [weak = WeakClaim(this), uiTaskExecutor](std::string baseUrl, std::string data, std::string mimeType,
                std::string encoding, std::string historyUrl) {
                uiTaskExecutor.PostTask([weak, baseUrl, data, mimeType, encoding, historyUrl]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->LoadDataWithBaseUrl(baseUrl, data, mimeType, encoding, historyUrl);
                    }
                }, "ArkUIWebControllerLoadDataWithBaseUrl");
            });
        webController->SetRefreshImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->Refresh();
                }
            }, "ArkUIWebControllerRefresh");
        });
        webController->SetStopLoadingImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->StopLoading();
                }
            }, "ArkUIWebControllerStopLoading");
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
                return delegate->SetCookie(url, value, delegate->incognitoMode_);
            }
            return false;
        });
        webController->SetGetCookieImpl([weak = WeakClaim(this)](const std::string& url) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->GetCookie(url, delegate->incognitoMode_);
            }
            return std::string();
        });
        webController->SetDeleteEntirelyCookieImpl([weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->DeleteEntirelyCookie(delegate->incognitoMode_);
            }
        });
        webController->SetWebViewJavaScriptResultCallBackImpl(
            [weak = WeakClaim(this), uiTaskExecutor](WebController::JavaScriptCallBackImpl&& javaScriptCallBackImpl) {
                uiTaskExecutor.PostTask([weak, javaScriptCallBackImpl]() {
                    auto delegate = weak.Upgrade();
                    if (delegate) {
                        delegate->SetWebViewJavaScriptResultCallBack(std::move(javaScriptCallBackImpl));
                    }
                }, "ArkUIWebControllerSetJsResultCallBack");
            });
        webController->SetAddJavascriptInterfaceImpl([weak = WeakClaim(this), uiTaskExecutor](std::string objectName,
                                                         const std::vector<std::string>& methodList) {
            uiTaskExecutor.PostTask([weak, objectName, methodList]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->AddJavascriptInterface(objectName, methodList);
                }
            }, "ArkUIWebControllerAddJsInterface");
        });
        webController->LoadInitJavascriptInterface();
        webController->SetRemoveJavascriptInterfaceImpl([weak = WeakClaim(this), uiTaskExecutor](std::string objectName,
                                                            const std::vector<std::string>& methodList) {
            uiTaskExecutor.PostTask([weak, objectName, methodList]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->RemoveJavascriptInterface(objectName, methodList);
                }
            }, "ArkUIWebControllerRemoveJsInterface");
        });
        webController->SetOnInactiveImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->OnInactive();
                }
            }, "ArkUIWebInactiveCallback");
        });
        webController->SetOnActiveImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->OnActive();
                }
            }, "ArkUIWebActiveCallback");
        });
        webController->SetZoomImpl([weak = WeakClaim(this), uiTaskExecutor](float factor) {
            uiTaskExecutor.PostTask([weak, factor]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->Zoom(factor);
                }
            }, "ArkUIWebSetZoomFactor");
        });
        webController->SetZoomInImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            bool result = false;
            uiTaskExecutor.PostSyncTask([weak, &result]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    result = delegate->ZoomIn();
                }
            }, "ArkUIWebControllerZoomIn");
            return result;
        });
        webController->SetZoomOutImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            bool result = false;
            uiTaskExecutor.PostSyncTask([weak, &result]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    result = delegate->ZoomOut();
                }
            }, "ArkUIWebControllerZoomOut");
            return result;
        });
        webController->SetRequestFocusImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->RequestFocus();
                }
            }, "ArkUIWebControllerRequestFocus");
        });

        webController->SetSearchAllAsyncImpl([weak = WeakClaim(this), uiTaskExecutor](const std::string& searchStr) {
            uiTaskExecutor.PostTask([weak, searchStr]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->SearchAllAsync(searchStr);
                }
            }, "ArkUIWebControllerSearchAllAsync");
        });
        webController->SetClearMatchesImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->ClearMatches();
                }
            }, "ArkUIWebControllerClearMatches");
        });
        webController->SetSearchNextImpl([weak = WeakClaim(this), uiTaskExecutor](bool forward) {
            uiTaskExecutor.PostTask([weak, forward]() {
                auto delegate = weak.Upgrade();
                if (delegate) {
                    delegate->SearchNext(forward);
                }
            }, "ArkUIWebControllerSearchNext");
        });
        webController->SetGetUrlImpl([weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate) {
                return delegate->GetUrl();
            }
            return std::string();
        });
    } else {
        TAG_LOGW(AceLogTag::ACE_WEB, "web controller is nullptr");
    }
}

void WebDelegate::InitWebViewWithWindow()
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            std::shared_ptr<OHOS::NWeb::NWebEngineInitArgsImpl> initArgs =
                std::make_shared<OHOS::NWeb::NWebEngineInitArgsImpl>();
            std::string app_path = GetDataPath();
            if (!app_path.empty()) {
                initArgs->AddArg(std::string("--user-data-dir=").append(app_path));
            }

            delegate->window_ = delegate->CreateWindow();
            if (!delegate->window_) {
                return;
            }

            initArgs->SetSharedRenderProcessToken(delegate->sharedRenderProcessToken_);
            delegate->nweb_ =
                OHOS::NWeb::NWebAdapterHelper::Instance().CreateNWeb(
                    delegate->window_.GetRefPtr(), initArgs,
                    delegate->incognitoMode_);
            if (delegate->nweb_ == nullptr) {
                delegate->window_ = nullptr;
                return;
            }
            delegate->JavaScriptOnDocumentStart();
            delegate->JavaScriptOnDocumentEnd();
            delegate->cookieManager_ = OHOS::NWeb::NWebHelper::Instance().GetCookieManager();
            if (delegate->cookieManager_ == nullptr) {
                return;
            }
            auto webviewClient = std::make_shared<WebClientImpl>();
            webviewClient->SetWebDelegate(weak);
            delegate->nweb_->SetNWebHandler(webviewClient);

            // Set downloadListenerImpl
            auto downloadListenerImpl = std::make_shared<DownloadListenerImpl>();
            downloadListenerImpl->SetWebDelegate(weak);
            delegate->nweb_->PutDownloadCallback(downloadListenerImpl);

            auto findListenerImpl = std::make_shared<FindListenerImpl>();
            findListenerImpl->SetWebDelegate(weak);
            delegate->nweb_->PutFindCallback(findListenerImpl);

            auto spanstringConvertHtmlImpl = std::make_shared<SpanstringConvertHtmlImpl>(Container::CurrentId());
            spanstringConvertHtmlImpl->SetWebDelegate(weak);
            delegate->nweb_->PutSpanstringConvertHtmlCallback(spanstringConvertHtmlImpl);

            std::optional<std::string> src;
            auto isNewPipe = Container::IsCurrentUseNewPipeline();
            delegate->UpdateSettting(isNewPipe);
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebInitWebViewWithWindow");
}

void WebDelegate::UpdateSettting(bool useNewPipe)
{
    CHECK_NULL_VOID(nweb_);
    auto setting = nweb_->GetPreference();
    CHECK_NULL_VOID(setting);
#ifdef NG_BUILD
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
    setting->PutCacheMode(
        static_cast<OHOS::NWeb::NWebPreference::CacheModeFlag>(webPattern->GetCacheModeValue(WebCacheMode::DEFAULT)));
    setting->PutLoadWithOverviewMode(webPattern->GetOverviewModeAccessEnabledValue(true));
    setting->PutEnableRawFileAccessFromFileURLs(webPattern->GetFileFromUrlAccessEnabledValue(true));
    setting->PutDatabaseAllowed(webPattern->GetDatabaseAccessEnabledValue(false));
    setting->PutZoomingForTextFactor(webPattern->GetTextZoomRatioValue(DEFAULT_TEXT_ZOOM_RATIO));
    setting->PutWebDebuggingAccess(webPattern->GetWebDebuggingAccessEnabledValue(false));
    setting->PutMediaPlayGestureAccess(webPattern->GetMediaPlayGestureAccessValue(true));
    return;
#else
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
#endif
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

void WebDelegate::SurfaceOcclusionCallback(float visibleRatio)
{
    TAG_LOGI(AceLogTag::ACE_WEB,
        "SurfaceOcclusion changed, occlusionPoints:%{public}f, surfacenode id: %{public}" PRIu64 "", visibleRatio,
        surfaceNodeId_);
    if (fabs(visibleRatio_ - visibleRatio) <= FLT_EPSILON || (fabs(visibleRatio) > FLT_EPSILON && visibleRatio < 0.0) ||
        (fabs(visibleRatio - 1.0) > FLT_EPSILON && visibleRatio > 1.0)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "visibleRatio is ilegal or not changed.");
        return;
    }
    visibleRatio_ = visibleRatio;

    if (fabs(visibleRatio_) > FLT_EPSILON && visibleRatio_ > 0.0) {
        CHECK_NULL_VOID(nweb_);
        nweb_->OnUnoccluded();
        if (fabs(visibleRatio_ - lowerFrameRateVisibleRatio_) <= FLT_EPSILON ||
            visibleRatio_ < lowerFrameRateVisibleRatio_) {
            nweb_->SetEnableLowerFrameRate(true);
        } else {
            nweb_->SetEnableLowerFrameRate(false);
        }
    } else {
        auto context = context_.Upgrade();
        CHECK_NULL_VOID(context);
        CHECK_NULL_VOID(context->GetTaskExecutor());
        context->GetTaskExecutor()->PostDelayedTask(
            [weak = WeakClaim(this)]() {
                auto delegate = weak.Upgrade();
                CHECK_NULL_VOID(delegate);
                if (fabs(delegate->visibleRatio_) <= FLT_EPSILON) {
                    TAG_LOGI(AceLogTag::ACE_WEB, "the web is still all occluded");
                    CHECK_NULL_VOID(delegate->nweb_);
                    delegate->nweb_->OnOccluded();
                }
            },
            TaskExecutor::TaskType::UI, delayTime_, "ArkUIWebOccluded");
    }
}

void WebDelegate::ratioStrToFloat(const std::string& str)
{
    // LowerFrameRateConfig format x.xx, len is 4, [0.00, 1.00]
    if (str.size() != VISIBLERATIO_LENGTH) {
        TAG_LOGE(AceLogTag::ACE_WEB, "visibleRatio lenth is over 4.");
        return;
    }
    auto dotCount = std::count(str.begin(), str.end(), '.');
    if (dotCount != 1) {
        TAG_LOGE(AceLogTag::ACE_WEB, "visibleRatio does not have dot.");
        return;
    }
    auto pos = str.find('.', 0);
    if (pos != 1) {
        TAG_LOGE(AceLogTag::ACE_WEB, "visibleRatio dot position is wrong.");
        return;
    }
    auto notDigitCount = std::count_if(str.begin(), str.end(), [](char c) { return !isdigit(c) && c != '.'; });
    if (notDigitCount > 0) {
        TAG_LOGE(AceLogTag::ACE_WEB, "visibleRatio dot count is over 1.");
        return;
    }
    float f = std::stof(str);
    int i = f * VISIBLERATIO_FLOAT_TO_INT;
    if (i >= 0 && i <= VISIBLERATIO_FLOAT_TO_INT) {
        TAG_LOGI(AceLogTag::ACE_WEB, "visibleRatio check success.");
        lowerFrameRateVisibleRatio_ = f;
    }
}

void WebDelegate::RegisterSurfaceOcclusionChangeFun()
{
    if (!GetWebOptimizationValue()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "web optimization is close.");
        return;
    }
    if (!IsDeviceTabletOr2in1()) {
        TAG_LOGI(AceLogTag::ACE_WEB, "device type does not satisfy.");
        return;
    }
    std::string visibleAreaRatio =
        OHOS::NWeb::NWebAdapterHelper::Instance().ParsePerfConfig("LowerFrameRateConfig", "visibleAreaRatio");
    ratioStrToFloat(visibleAreaRatio);
    std::vector<float> partitionPoints;
    TAG_LOGI(AceLogTag::ACE_WEB, "max visible rate to lower frame rate:%{public}f", lowerFrameRateVisibleRatio_);
    if ((int)(lowerFrameRateVisibleRatio_ * VISIBLERATIO_FLOAT_TO_INT) == 0) {
        partitionPoints = { 0 };
    } else {
        partitionPoints = { 0, lowerFrameRateVisibleRatio_ };
    }
    auto ret = OHOS::Rosen::RSInterfaces::GetInstance().RegisterSurfaceOcclusionChangeCallback(
        surfaceNodeId_,
        [weak = WeakClaim(this)](float visibleRatio) {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto context = delegate->context_.Upgrade();
            CHECK_NULL_VOID(context);
            context->GetTaskExecutor()->PostTask(
                [weakDelegate = weak, webVisibleRatio = visibleRatio]() {
                    auto delegate = weakDelegate.Upgrade();
                    CHECK_NULL_VOID(delegate);
                    delegate->SurfaceOcclusionCallback(webVisibleRatio);
                },
                TaskExecutor::TaskType::UI, "ArkUIWebOcclusionChange");
        },
        partitionPoints);
    if (ret != Rosen::StatusCode::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_WEB,
            "RegisterSurfaceOcclusionChangeCallback failed, surfacenode id:%{public}" PRIu64 ""
            ", ret: %{public}" PRIu32 "",
            surfaceNodeId_, ret);
        return;
    }
    TAG_LOGI(AceLogTag::ACE_WEB,
            "RegisterSurfaceOcclusionChangeCallback succeed, surfacenode id:%{public}" PRIu64 ""
            ", ret: %{public}" PRIu32 "",
            surfaceNodeId_, ret);
}

void WebDelegate::RegisterAvoidAreaChangeListener(int32_t instanceId)
{
    constexpr static int32_t PLATFORM_VERSION_TEN = 10;
    auto container = AceType::DynamicCast<Platform::AceContainer>(Container::GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    if (pipeline && pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN &&
        (pipeline->GetIsAppWindow() || container->IsUIExtensionWindow())) {
        if (avoidAreaChangedListener_) return;

        systemSafeArea_ = container->GetViewSafeAreaByType(OHOS::Rosen::AvoidAreaType::TYPE_SYSTEM);
        cutoutSafeArea_ = container->GetViewSafeAreaByType(OHOS::Rosen::AvoidAreaType::TYPE_CUTOUT);
        navigationIndicatorSafeArea_ =
            container->GetViewSafeAreaByType(OHOS::Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR);
        OnSafeInsetsChange();

        avoidAreaChangedListener_ = new WebAvoidAreaChangedListener(AceType::WeakClaim(this));
        OHOS::Rosen::WMError regCode = container->RegisterAvoidAreaChangeListener(avoidAreaChangedListener_);
        TAG_LOGI(AceLogTag::ACE_WEB, "RegisterAvoidAreaChangeListener result:%{public}d", (int) regCode);
    } else {
        TAG_LOGI(AceLogTag::ACE_WEB, "CANNOT RegisterAvoidAreaChangeListener");
    }
}

class NWebAutoFillCallbackImpl : public OHOS::NWeb::NWebMessageValueCallback {
public:
    NWebAutoFillCallbackImpl(const WeakPtr<WebDelegate>& delegate) : delegate_(delegate) {}
    ~NWebAutoFillCallbackImpl() = default;

    void OnReceiveValue(std::shared_ptr<NWebMessage> result) override
    {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "called");
        auto delegate = delegate_.Upgrade();
        CHECK_NULL_VOID(delegate);
        bool ret = delegate->HandleAutoFillEvent(result);
        result->SetType(NWebValue::Type::BOOLEAN);
        result->SetBoolean(ret);
    }

private:
    WeakPtr<WebDelegate> delegate_;
};

void WebDelegate::UnregisterAvoidAreaChangeListener(int32_t instanceId)
{
    constexpr static int32_t PLATFORM_VERSION_TEN = 10;
    auto container = AceType::DynamicCast<Platform::AceContainer>(Container::GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    if (pipeline && pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN &&
        (pipeline->GetIsAppWindow() || container->IsUIExtensionWindow())) {
        if (!avoidAreaChangedListener_) return;
        OHOS::Rosen::WMError regCode = container->UnregisterAvoidAreaChangeListener(avoidAreaChangedListener_);
        avoidAreaChangedListener_ = nullptr;
        TAG_LOGI(AceLogTag::ACE_WEB, "UnregisterAvoidAreaChangeListener result:%{public}d", (int) regCode);
    } else {
        TAG_LOGI(AceLogTag::ACE_WEB, "CANNOT UnregisterAvoidAreaChangeListener");
    }
}

void WebDelegate::InitWebViewWithSurface()
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto window = context->GetWindow();
    CHECK_NULL_VOID(window);
    rosenWindowId_ = window->GetWindowId();
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), context = context_, renderMode = renderMode_, layoutMode = layoutMode_]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            std::shared_ptr<OHOS::NWeb::NWebEngineInitArgsImpl> initArgs =
                std::make_shared<OHOS::NWeb::NWebEngineInitArgsImpl>();
            initArgs->AddArg(std::string("--user-data-dir=").append(delegate->bundleDataPath_));
            initArgs->AddArg(std::string("--bundle-installation-dir=").append(delegate->bundlePath_));
            initArgs->AddArg(std::string("--lang=").append(AceApplicationInfo::GetInstance().GetLanguage() +
                    "-" + AceApplicationInfo::GetInstance().GetCountryOrRegion()));
            initArgs->AddArg(std::string("--user-api-version=").append(
                std::to_string(AceApplicationInfo::GetInstance().GetApiTargetVersion())));
            bool isEnhanceSurface = delegate->isEnhanceSurface_;
            initArgs->SetIsEnhanceSurface(isEnhanceSurface);
            initArgs->SetIsPopup(delegate->isPopup_);
            initArgs->SetSharedRenderProcessToken(delegate->sharedRenderProcessToken_);

            if (!delegate->hapPath_.empty()) {
                initArgs->AddArg(std::string("--user-hap-path=").append(delegate->hapPath_));
            }

            if (!delegate->tempDir_.empty()) {
                initArgs->AddArg(std::string("--ohos-temp-dir=").append(delegate->tempDir_));
            }

            std::string customScheme = delegate->GetCustomScheme();
            if (!customScheme.empty()) {
                initArgs->AddArg(std::string("--ohos-custom-scheme=").append(customScheme));
            }
            initArgs->AddArg(std::string("--init-background-color=")
                .append(std::to_string(delegate->backgroundColor_)));
            if (delegate->richtextData_) {
                // Created a richtext component
                initArgs->AddArg(std::string("--init-richtext-data=").append(delegate->richtextData_.value()));
            }
            if (isEnhanceSurface) {
                TAG_LOGD(AceLogTag::ACE_WEB, "Create webview with isEnhanceSurface");
                delegate->nweb_ = OHOS::NWeb::NWebAdapterHelper::Instance().CreateNWeb(
                    (void *)(&delegate->surfaceInfo_),
                    initArgs,
                    delegate->drawSize_.Width(),
                    delegate->drawSize_.Height(),
                    delegate->incognitoMode_);
                delegate->JavaScriptOnDocumentStart();
                delegate->JavaScriptOnDocumentEnd();
            } else {
#ifdef ENABLE_ROSEN_BACKEND
                wptr<Surface> surfaceWeak(delegate->surface_);
                sptr<Surface> surface = surfaceWeak.promote();
                CHECK_NULL_VOID(surface);
                delegate->nweb_ = OHOS::NWeb::NWebAdapterHelper::Instance().CreateNWeb(
                    surface,
                    initArgs,
                    delegate->drawSize_.Width(),
                    delegate->drawSize_.Height(),
                    delegate->incognitoMode_);
                delegate->JavaScriptOnDocumentStart();
                delegate->JavaScriptOnDocumentEnd();
#endif
            }
            CHECK_NULL_VOID(delegate->nweb_);
            delegate->cookieManager_ = OHOS::NWeb::NWebHelper::Instance().GetCookieManager();
            CHECK_NULL_VOID(delegate->cookieManager_);
            auto nweb_handler = std::make_shared<WebClientImpl>();
            nweb_handler->SetWebDelegate(weak);
            auto downloadListenerImpl = std::make_shared<DownloadListenerImpl>();
            downloadListenerImpl->SetWebDelegate(weak);
            delegate->nweb_->SetNWebHandler(nweb_handler);
            delegate->nweb_->PutDownloadCallback(downloadListenerImpl);
#ifdef OHOS_STANDARD_SYSTEM
            auto screenLockCallback = std::make_shared<NWebScreenLockCallbackImpl>(context);
            delegate->nweb_->RegisterScreenLockFunction(Container::CurrentId(), screenLockCallback);
            auto autoFillCallback = std::make_shared<NWebAutoFillCallbackImpl>(weak);
            delegate->nweb_->SetAutofillCallback(autoFillCallback);
#endif
            auto findListenerImpl = std::make_shared<FindListenerImpl>();
            findListenerImpl->SetWebDelegate(weak);
            delegate->nweb_->PutFindCallback(findListenerImpl);
            delegate->UpdateSettting(Container::IsCurrentUseNewPipeline());
            delegate->RunSetWebIdAndHapPathCallback();
            delegate->RunJsProxyCallback();
            auto releaseSurfaceListenerImpl = std::make_shared<ReleaseSurfaceImpl>();
            releaseSurfaceListenerImpl->SetSurfaceDelegate(delegate->GetSurfaceDelegateClient());
            releaseSurfaceListenerImpl->SetWebDelegate(weak);
            delegate->nweb_->PutReleaseSurfaceCallback(releaseSurfaceListenerImpl);
            auto upgradeContext = context.Upgrade();
            CHECK_NULL_VOID(upgradeContext);
            auto window_id = upgradeContext->GetWindowId();
            delegate->nweb_->SetWindowId(window_id);
            delegate->SetToken();
            delegate->RegisterSurfaceOcclusionChangeFun();
            delegate->nweb_->SetDrawMode(renderMode);
            delegate->nweb_->SetFitContentMode(layoutMode);
            delegate->RegisterConfigObserver();
            auto spanstringConvertHtmlImpl = std::make_shared<SpanstringConvertHtmlImpl>(Container::CurrentId());
            spanstringConvertHtmlImpl->SetWebDelegate(weak);
            delegate->nweb_->PutSpanstringConvertHtmlCallback(spanstringConvertHtmlImpl);
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebInitWebViewWithSurface");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateUserAgent");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateBackgroundColor");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateInitialScale");
}

void WebDelegate::UpdateLayoutMode(WebLayoutMode mode)
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
                delegate->nweb_->SetFitContentMode(static_cast<int32_t>(mode));
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateLayoutMode");
}

void WebDelegate::Resize(const double& width, const double& height, bool isKeyboard)
{
    if (width <= 0 || height <= 0) {
        return;
    }

    if ((resizeWidth_ == width) && (resizeHeight_ == height)) {
        return;
    }
    resizeWidth_ = width;
    resizeHeight_ = height;
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), width, height, isKeyboard]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_ && !delegate->window_) {
                // Sur need int value, greater than this value in case show black line.
                delegate->nweb_->Resize(std::ceil(width), std::ceil(height), isKeyboard);
                double offsetX = 0;
                double offsetY = 0;
                delegate->UpdateScreenOffSet(offsetX, offsetY);
                delegate->nweb_->SetScreenOffSet(offsetX, offsetY);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebResize");
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetDrawSize(width, height);
    webPattern->DestroyAnalyzerOverlay();
}


void WebDelegate::DragResize(const double& width, const double& height,
                             const double& pre_height, const double& pre_width)
{
    if (width <= 0 || height <= 0) {
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), width, height, pre_height, pre_width]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_ && !delegate->window_) {
                // Sur need int value, greater than this value in case show black line.
                delegate->nweb_->DragResize(std::ceil(width), std::ceil(height),
                                            std::ceil(pre_height), std::ceil(pre_width));
                double offsetX = 0;
                double offsetY = 0;
                delegate->UpdateScreenOffSet(offsetX, offsetY);
                delegate->nweb_->SetScreenOffSet(offsetX, offsetY);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebDragResize");
}

void WebDelegate::UpdateSmoothDragResizeEnabled(bool isSmoothDragResizeEnabled)
{
    isSmoothDragResizeEnabled_ = isSmoothDragResizeEnabled;
}

bool WebDelegate::GetIsSmoothDragResizeEnabled()
{
    return isSmoothDragResizeEnabled_;
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateJavaScriptEnabled");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateAllowFileAccess");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateBlockNetworkImage");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateLoadImageAccessEnabled");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateMixedContentMode");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateSupportZoom");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateDomStorageEnabled");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateGeolocationEnabled");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateCacheMode");
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

    current_dark_mode_ = mode;
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), mode]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
            CHECK_NULL_VOID(setting);

            if (mode == WebDarkMode::On) {
                setting->PutDarkSchemeEnabled(true);
                if (delegate->forceDarkMode_) {
                    setting->PutForceDarkModeEnabled(true);
                }
            } else if (mode == WebDarkMode::Off) {
                setting->PutDarkSchemeEnabled(false);
                setting->PutForceDarkModeEnabled(false);
            } else if (mode == WebDarkMode::Auto) {
                delegate->UpdateDarkModeAuto(delegate, setting);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateDarkMode");
}

void WebDelegate::UpdateDarkModeAuto(RefPtr<WebDelegate> delegate, std::shared_ptr<OHOS::NWeb::NWebPreference> setting)
{
    CHECK_NULL_VOID(setting);
    auto abilityContext = OHOS::AbilityRuntime::Context::GetApplicationContext();
    CHECK_NULL_VOID(abilityContext);
    auto appConfig = abilityContext->GetConfiguration();
    CHECK_NULL_VOID(appConfig);
    auto colorMode = appConfig->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateForceDarkAccess");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateAudioResumeInterval");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateAudioExclusive");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateOverviewModeEnabled");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateFileFromUrlEnabled");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateDatabaseEnabled");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateTextZoomRatio");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateDebuggingAccess");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdatePinchSmoothModeEnabled");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateMediaPlayGestureAccess");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateMultiWindowAccess");
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
                CHECK_NULL_VOID(setting);
                setting->PutIsCreateWindowsByJavaScriptAllowed(isAllowWindowOpenMethod);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateAllowWindowOpen");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateWebCursiveFont");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateWebFantasyFont");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateWebFixedFont");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateWebSansSerifFont");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateWebSerifFont");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateWebStandardFont");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateDefaultFixedFontSize");
}

void WebDelegate::OnConfigurationUpdated(const OHOS::AppExecFwk::Configuration& configuration)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);

    auto executor = context->GetTaskExecutor();
    CHECK_NULL_VOID(executor);

    std::string colorMode = configuration.GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
    std::string themeTag = configuration.GetItem(OHOS::AAFwk::GlobalConfigurationKey::THEME);
    uint8_t themeFlags = static_cast<uint8_t>(OHOS::NWeb::SystemThemeFlags::NONE);
    if (!themeTag.empty()) {
        std::unique_ptr<JsonValue> json = JsonUtil::ParseJsonString(themeTag);
        if (json->GetInt("fonts")) {
            themeFlags |= static_cast<uint8_t>(OHOS::NWeb::SystemThemeFlags::THEME_FONT);
            TAG_LOGI(AceLogTag::ACE_WEB, "OnConfigurationUpdated fonts:%{public}s", themeTag.c_str());
        }
    }

    executor->PostTask(
        [weak = WeakClaim(this), colorMode, themeFlags, dark_mode = current_dark_mode_]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto nweb = delegate->GetNweb();
            CHECK_NULL_VOID(nweb);

            std::shared_ptr<NWebSystemConfigurationImpl> configuration =
                    std::make_shared<NWebSystemConfigurationImpl>(themeFlags);
            nweb->OnConfigurationUpdated(configuration);

            auto setting = nweb->GetPreference();
            CHECK_NULL_VOID(setting);
            bool auto_dark_mode = (dark_mode == WebDarkMode::Auto);
            if (auto_dark_mode && colorMode == "dark") {
                setting->PutDarkSchemeEnabled(true);
                if (delegate->GetForceDarkMode()) {
                    setting->PutForceDarkModeEnabled(true);
                }
            } else if (auto_dark_mode && colorMode == "light") {
                setting->PutDarkSchemeEnabled(false);
                setting->PutForceDarkModeEnabled(false);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebConfigurationUpdated");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateDefaultFontSize");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateMinFontSize");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateMinLogicalFontSize");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateBlockNetwork");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebPutHorizontalScrollBarAccess");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebPutVerticalScrollBarAccess");
}

void WebDelegate::UpdateOverlayScrollbarEnabled(bool isEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutOverlayScrollbarEnabled(isEnabled);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebPutOverlayScrollbarEnabled");
}

void WebDelegate::UpdateNativeEmbedModeEnabled(bool isEmbedModeEnabled)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    isEmbedModeEnabled_ = isEmbedModeEnabled;
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isEmbedModeEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->SetNativeEmbedMode(isEmbedModeEnabled);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebSetNativeEmbedMode");
}

void WebDelegate::UpdateNativeEmbedRuleTag(const std::string& tag)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    tag_ = tag;
    if (tag_.empty() || tag_type_.empty()) {
        return;
    }

    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->RegisterNativeEmbedRule(delegate->tag_, delegate->tag_type_);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateNativeEmbedRuleTag");
}

void WebDelegate::UpdateNativeEmbedRuleType(const std::string& type)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    tag_type_ = type;
    if (tag_.empty() || tag_type_.empty()) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->RegisterNativeEmbedRule(delegate->tag_, delegate->tag_type_);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateNativeEmbedRuleType");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebPutScrollBarColor");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebLoadSrcUrl");
}

void WebDelegate::OnInactive()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDelegate::OnInactive, webId:%{public}d", GetWebId());
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebOnInactive");
}

void WebDelegate::OnActive()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDelegate::OnActive, webId:%{public}d", GetWebId());
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebOnActive");
}

void WebDelegate::GestureBackBlur()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDelegate::GestureBackBlur, webId:%{public}d", GetWebId());
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
                delegate->nweb_->WebComponentsBlur();
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebGestureBackBlur");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebOnWebviewHide");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebOnWebviewShow");
}

void WebDelegate::OnRenderToForeground()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDelegate::OnRenderToForeground");
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
                TAG_LOGD(AceLogTag::ACE_WEB, "delegate->nweb_->OnRenderToForeground");
                delegate->nweb_->OnRenderToForeground();
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebOnRenderToForeground");
}

void WebDelegate::OnRenderToBackground()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDelegate::OnRenderToBackground");
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
                TAG_LOGD(AceLogTag::ACE_WEB, "delegate->nweb_->OnRenderToBackground");
                delegate->nweb_->OnRenderToBackground();
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebOnRenderToBackground");
}

void WebDelegate::OnOnlineRenderToForeground()
{
    TAG_LOGD(AceLogTag::ACE_WEB, "WebDelegate::OnOnlineRenderToForeground");
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
                TAG_LOGD(AceLogTag::ACE_WEB, "delegate->nweb_->OnOnlineRenderToForeground");
                delegate->nweb_->OnOnlineRenderToForeground();
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebOnOnlineRenderToForeground");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebSetShouldFrameSubmissionBeforeDraw");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebNotifyMemoryLevel");
}

void WebDelegate::SetAudioMuted(bool muted)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->SetAudioMuted(muted);
    }
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
                return;
            }
            if (delegate->nweb_) {
                delegate->nweb_->Zoom(factor);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebZoom");
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
                return;
            }
            if (delegate->nweb_) {
                result = delegate->nweb_->ZoomIn();
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebZoomIn");
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
                return;
            }
            if (delegate->nweb_) {
                result = delegate->nweb_->ZoomOut();
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebZoomOut");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebReload");
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

void WebDelegate::RecordWebEvent(Recorder::EventType eventType, const std::string& param) const
{
    if (!Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        return;
    }
    auto pattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    Recorder::EventParamsBuilder builder;
    builder.SetId(host->GetInspectorIdValue(""))
        .SetType(host->GetHostTag())
        .SetEventType(eventType)
        .SetText(param)
        .SetDescription(host->GetAutoEventParamValue(""));
    Recorder::EventRecorder::Get().OnEvent(std::move(builder));
}

void WebDelegate::OnPageStarted(const std::string& param)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), param]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            webEventHub->FireOnPageStartedEvent(std::make_shared<LoadWebPageStartEvent>(param));
            delegate->RecordWebEvent(Recorder::EventType::WEB_PAGE_BEGIN, param);
        },
        TaskExecutor::TaskType::JS, "ArkUIWebPageStarted");
    auto pattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->DestroyAnalyzerOverlay();
}

void WebDelegate::OnPageFinished(const std::string& param)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), param]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            webEventHub->FireOnPageFinishedEvent(std::make_shared<LoadWebPageFinishEvent>(param));
            webPattern->OnScrollEndRecursive(std::nullopt);
            delegate->RecordWebEvent(Recorder::EventType::WEB_PAGE_END, param);
        },
        TaskExecutor::TaskType::JS, "ArkUIWebPageFinished");
}

void WebDelegate::OnProgressChanged(int param)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
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
        TaskExecutor::TaskType::JS, "ArkUIWebProgressChanged");
}

void WebDelegate::OnReceivedTitle(const std::string& param)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), param]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            // ace 2.0
            auto onTitleReceiveV2 = delegate->onTitleReceiveV2_;
            if (onTitleReceiveV2) {
                onTitleReceiveV2(std::make_shared<LoadWebTitleReceiveEvent>(param));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebReceivedTitle");
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
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto param = std::make_shared<FullScreenExitEvent>(false);
#ifdef NG_BUILD
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnFullScreenExitEvent = webEventHub->GetOnFullScreenExitEvent();
            CHECK_NULL_VOID(propOnFullScreenExitEvent);
            propOnFullScreenExitEvent(param);
            return;
#else
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
#endif
        },
        TaskExecutor::TaskType::JS, "ArkUIWebFullScreenExit");
}

void WebDelegate::OnGeolocationPermissionsHidePrompt()
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            // ace 2.0
            auto onGeolocationHideV2 = delegate->onGeolocationHideV2_;
            if (onGeolocationHideV2) {
                onGeolocationHideV2(std::make_shared<LoadWebGeolocationHideEvent>(""));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebGeolocationPermissionsHidePrompt");
}

void WebDelegate::OnGeolocationPermissionsShowPrompt(
    const std::string& origin, const std::shared_ptr<OHOS::NWeb::NWebGeolocationCallbackInterface>& callback)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), origin, callback]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            // ace 2.0
            auto onGeolocationShowV2 = delegate->onGeolocationShowV2_;
            if (onGeolocationShowV2) {
                auto geolocation =
                    AceType::MakeRefPtr<WebGeolocationOhos>(callback,
                                                            delegate->incognitoMode_);
                onGeolocationShowV2(std::make_shared<LoadWebGeolocationShowEvent>(origin, geolocation));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebGeolocationPermissionsShowPrompt");
}

void WebDelegate::OnPermissionRequestPrompt(const std::shared_ptr<OHOS::NWeb::NWebAccessRequest>& request)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), request]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            if (static_cast<uint32_t>(request->ResourceAcessId())
                & OHOS::NWeb::NWebAccessRequest::Resources::CLIPBOARD_READ_WRITE) {
                auto webPattern = delegate->webPattern_.Upgrade();
                CHECK_NULL_VOID(webPattern);
                auto clipboardCallback = webPattern->GetPermissionClipboardCallback();
                CHECK_NULL_VOID(clipboardCallback);
                clipboardCallback(std::make_shared<WebPermissionRequestEvent>(
                    AceType::MakeRefPtr<WebPermissionRequestOhos>(request)));
                return;
            }
            // ace 2.0
            auto onPermissionRequestV2 = delegate->onPermissionRequestV2_;
            if (onPermissionRequestV2) {
                onPermissionRequestV2(std::make_shared<WebPermissionRequestEvent>(
                    AceType::MakeRefPtr<WebPermissionRequestOhos>(request)));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebPermissionRequestPrompt");
}

void WebDelegate::OnScreenCaptureRequest(const std::shared_ptr<OHOS::NWeb::NWebScreenCaptureAccessRequest>& request)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), request]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            // ace 2.0
            auto onScreenCaptureRequestV2 = delegate->onScreenCaptureRequestV2_;
            if (onScreenCaptureRequestV2) {
                onScreenCaptureRequestV2(std::make_shared<WebScreenCaptureRequestEvent>(
                    AceType::MakeRefPtr<WebScreenCaptureRequestOhos>(request)));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebScreenCaptureRequest");
}

bool WebDelegate::OnConsoleLog(std::shared_ptr<OHOS::NWeb::NWebConsoleLog> message)
{
    CHECK_NULL_RETURN(taskExecutor_, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
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
            return;
        }
        auto webCom = delegate->webComponent_.Upgrade();
        CHECK_NULL_VOID(webCom);
        result = webCom->OnConsole(param.get());
        return;
    }, "ArkUIWebConsoleLog");
    return result;
}

bool WebDelegate::OnCommonDialog(const std::shared_ptr<BaseEventInfo>& info, DialogEventType dialogEventType)
{
    CHECK_NULL_RETURN(taskExecutor_, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, dialogEventType, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
#ifdef NG_BUILD
        auto webPattern = delegate->webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        auto webEventHub = webPattern->GetWebEventHub();
        CHECK_NULL_VOID(webEventHub);
        result = webEventHub->FireOnCommonDialogEvent(info, dialogEventType);
        return;
#else
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
#endif
    }, "ArkUIWebCommonDialogEvent");
    return result;
}

void WebDelegate::OnFullScreenEnter(
    std::shared_ptr<OHOS::NWeb::NWebFullScreenExitHandler> handler, int videoNaturalWidth, int videoNaturalHeight)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), handler, videoNaturalWidth, videoNaturalHeight]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto param =
                std::make_shared<FullScreenEnterEvent>(AceType::MakeRefPtr<FullScreenExitHandlerOhos>(handler, weak),
		    videoNaturalWidth, videoNaturalHeight);
#ifdef NG_BUILD
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
#else
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
#endif
        },
        TaskExecutor::TaskType::JS, "ArkUIWebFullScreenEnter");
}

bool WebDelegate::OnHttpAuthRequest(const std::shared_ptr<BaseEventInfo>& info)
{
    CHECK_NULL_RETURN(taskExecutor_, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
#ifdef NG_BUILD
        auto webPattern = delegate->webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        auto webEventHub = webPattern->GetWebEventHub();
        CHECK_NULL_VOID(webEventHub);
        auto propOnHttpAuthRequestEvent = webEventHub->GetOnHttpAuthRequestEvent();
        CHECK_NULL_VOID(propOnHttpAuthRequestEvent);
        result = propOnHttpAuthRequestEvent(info);
        return;
#else
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
#endif
    }, "ArkUIWebHttpAuthRequest");
    return result;
}

bool WebDelegate::OnSslErrorRequest(const std::shared_ptr<BaseEventInfo>& info)
{
    CHECK_NULL_RETURN(taskExecutor_, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
#ifdef NG_BUILD
        auto webPattern = delegate->webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        auto webEventHub = webPattern->GetWebEventHub();
        CHECK_NULL_VOID(webEventHub);
        auto propOnSslErrorEvent = webEventHub->GetOnSslErrorRequestEvent();
        CHECK_NULL_VOID(propOnSslErrorEvent);
        result = propOnSslErrorEvent(info);
        return;
#else
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
#endif
    }, "ArkUIWebSslErrorRequest");
    return result;
}

bool WebDelegate::OnAllSslErrorRequest(const std::shared_ptr<BaseEventInfo>& info)
{
    CHECK_NULL_RETURN(taskExecutor_, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        auto webPattern = delegate->webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        auto webEventHub = webPattern->GetWebEventHub();
        CHECK_NULL_VOID(webEventHub);
        auto propOnAllSslErrorEvent = webEventHub->GetOnAllSslErrorRequestEvent();
        CHECK_NULL_VOID(propOnAllSslErrorEvent);
        result = propOnAllSslErrorEvent(info);
        return;
    }, "ArkUIWebAllSslErrorRequest");
    return result;
}

bool WebDelegate::OnSslSelectCertRequest(const std::shared_ptr<BaseEventInfo>& info)
{
    CHECK_NULL_RETURN(taskExecutor_, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
#ifdef NG_BUILD
        auto webPattern = delegate->webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        auto webEventHub = webPattern->GetWebEventHub();
        CHECK_NULL_VOID(webEventHub);
        auto propOnSslSelectCertRequestEvent = webEventHub->GetOnSslSelectCertRequestEvent();
        CHECK_NULL_VOID(propOnSslSelectCertRequestEvent);
        result = propOnSslSelectCertRequestEvent(info);
        return;
#else
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
#endif
    }, "ArkUIWebSslSelectCertRequest");
    return result;
}

void WebDelegate::OnDownloadStart(const std::string& url, const std::string& userAgent,
    const std::string& contentDisposition, const std::string& mimetype, long contentLength)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), url, userAgent, contentDisposition, mimetype, contentLength]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onDownloadStartV2 = delegate->onDownloadStartV2_;
            if (onDownloadStartV2) {
                onDownloadStartV2(
                    std::make_shared<DownloadStartEvent>(url, userAgent, contentDisposition, mimetype, contentLength));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebDownloadStart");
}

void WebDelegate::OnAccessibilityEvent(int64_t accessibilityId, AccessibilityEventType eventType)
{
    if (!accessibilityState_) {
        return;
    }
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    AccessibilityEvent event;
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    auto accessibilityManager = context->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    if (eventType == AccessibilityEventType::ACCESSIBILITY_FOCUSED) {
        webPattern->UpdateFocusedAccessibilityId(accessibilityId);
    } else if (eventType == AccessibilityEventType::ACCESSIBILITY_FOCUS_CLEARED) {
        webPattern->ClearFocusedAccessibilityId();
    } else if (eventType == AccessibilityEventType::PAGE_CHANGE || eventType == AccessibilityEventType::SCROLL_END) {
        webPattern->UpdateFocusedAccessibilityId();
    }
    if (eventType == AccessibilityEventType::FOCUS) {
        TextBlurReportByFocusEvent(accessibilityId);
    }
    if (eventType == AccessibilityEventType::CLICK) {
        WebComponentClickReport(accessibilityId);
    }
    if (eventType == AccessibilityEventType::BLUR) {
        TextBlurReportByBlurEvent(accessibilityId);
    }
    event.nodeId = accessibilityId;
    event.type = eventType;
    accessibilityManager->SendWebAccessibilityAsyncEvent(event, webPattern);
}

void WebDelegate::TextBlurReportByFocusEvent(int64_t accessibilityId)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    auto textBlurCallback = webPattern->GetTextBlurCallback();
    CHECK_NULL_VOID(textBlurCallback);
    auto lastFocusNode = webPattern->GetAccessibilityNodeById(lastFocusInputId_);
    if (lastFocusNode && lastFocusNode->GetIsEditable() && lastFocusInputId_ != accessibilityId) {
        if (lastFocusNode->GetIsPassword()) {
            TAG_LOGW(AceLogTag::ACE_WEB, "the input type is password, do not report");
        } else {
            std::string blurText = lastFocusNode->GetContent();
            if (!blurText.empty()) {
                TAG_LOGD(AceLogTag::ACE_WEB, "report text blur, the content length is %{public}u",
                    static_cast<int32_t>(blurText.length()));
                textBlurCallback(lastFocusInputId_, blurText);
                lastFocusReportId_ = lastFocusInputId_;
            }
        }
    }
    if (accessibilityId != 0) {
        auto focusNode = webPattern->GetAccessibilityNodeById(accessibilityId);
        if (focusNode) {
            // record last editable focus id
            lastFocusInputId_ = accessibilityId;
        }
    }
}

void WebDelegate::WebComponentClickReport(int64_t accessibilityId)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    auto webAccessibilityNode = webPattern->GetAccessibilityNodeById(accessibilityId);
    CHECK_NULL_VOID(webAccessibilityNode);
    auto webComponentClickCallback = webPattern->GetWebComponentClickCallback();
    CHECK_NULL_VOID(webComponentClickCallback);
    webComponentClickCallback(accessibilityId, webAccessibilityNode->GetContent());
}

void WebDelegate::TextBlurReportByBlurEvent(int64_t accessibilityId)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    auto textBlurCallback = webPattern->GetTextBlurCallback();
    CHECK_NULL_VOID(textBlurCallback);
    auto blurNode = webPattern->GetAccessibilityNodeById(accessibilityId);
    if (blurNode && blurNode->GetIsEditable() && lastFocusReportId_ != accessibilityId) {
        std::string blurText = blurNode->GetContent();
        if (!blurNode->GetIsPassword() && !blurText.empty()) {
            TAG_LOGD(AceLogTag::ACE_WEB, "report text blur, the content length is %{public}u",
                static_cast<int32_t>(blurText.length()));
            textBlurCallback(accessibilityId, blurText);
        }
    }
}

void WebDelegate::OnErrorReceive(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceError> error)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), request, error]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            webEventHub->FireOnErrorReceiveEvent(std::make_shared<ReceivedErrorEvent>(
                    AceType::MakeRefPtr<WebRequest>(request->RequestHeaders(), request->Method(), request->Url(),
                        request->FromGesture(), request->IsAboutMainFrame(), request->IsRequestRedirect()),
                    AceType::MakeRefPtr<WebError>(error->ErrorInfo(), error->ErrorCode())));
        },
        TaskExecutor::TaskType::JS, "ArkUIWebErrorReceive");
}

void WebDelegate::ReportDynamicFrameLossEvent(const std::string& sceneId, bool isStart)
{
    if (sceneId == "") {
        TAG_LOGE(AceLogTag::ACE_WEB, "sceneId is null, do not report.");
        return;
    }
    ACE_SCOPED_TRACE("ReportDynamicFrameLossEvent, sceneId: %s, isStart: %u", sceneId.c_str(), isStart);
    if (isStart) {
        PerfMonitor::GetPerfMonitor()->Start(sceneId, PerfActionType::FIRST_MOVE, "");
    } else {
        PerfMonitor::GetPerfMonitor()->End(sceneId, false);
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
#ifdef NG_BUILD
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_RETURN(webPattern, false);
    auto webEventHub = webPattern->GetWebEventHub();
    CHECK_NULL_RETURN(webEventHub, false);
    return webEventHub->GetOnInterceptRequestEvent() == nullptr;
#else
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
#endif
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
    }, "ArkUIWebInterceptRequest");
    return result;
}

void WebDelegate::OnTooltip(const std::string& tooltip)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), tooltip]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            webPattern->OnTooltip(tooltip);
        },
        TaskExecutor::TaskType::UI, "ArkUIWebTooltip");
}

void WebDelegate::OnPopupSize(int32_t x, int32_t y, int32_t width, int32_t height)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), x, y, width, height]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            webPattern->OnPopupSize(x, y, width, height);
        },
        TaskExecutor::TaskType::UI, "ArkUIWebPopupSize");
}

void WebDelegate::OnPopupShow(bool show)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), show]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            webPattern->OnPopupShow(show);
        },
        TaskExecutor::TaskType::UI, "ArkUIWebPopupShow");
}

void WebDelegate::OnRequestFocus()
{
    if (onRequestFocusV2_) {
        onRequestFocusV2_(std::make_shared<LoadWebRequestFocusEvent>(""));
    }
}

void WebDelegate::OnRenderExited(OHOS::NWeb::RenderExitReason reason)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), reason]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onRenderExitedV2 = delegate->onRenderExitedV2_;
            if (onRenderExitedV2) {
                onRenderExitedV2(std::make_shared<RenderExitedEvent>(static_cast<int32_t>(reason)));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebRenderExited");
}

void WebDelegate::OnRefreshAccessedHistory(const std::string& url, bool isRefreshed)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), url, isRefreshed]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onRefreshAccessedHistoryV2 = delegate->onRefreshAccessedHistoryV2_;
            if (onRefreshAccessedHistoryV2) {
                onRefreshAccessedHistoryV2(std::make_shared<RefreshAccessedHistoryEvent>(url, isRefreshed));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebRefreshAccessedHistory");
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
    std::string removeQuotes = param;
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
    CHECK_NULL_RETURN(taskExecutor_, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
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
    }, "ArkUIWebFileSelectorShow");

    if (!result) {
        TAG_LOGI(AceLogTag::ACE_WEB, "default file selector show handled");
        auto jsTaskExecutor = SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
        jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, &result]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto fileSelectCallback = webPattern->GetDefaultFileSelectorShowCallback();
            CHECK_NULL_VOID(fileSelectCallback);
            fileSelectCallback(info);
            result = true;
            }, "ArkUIWebDefaultFileSelectorShow");
    }
    return result;
}

bool WebDelegate::OnContextMenuShow(const std::shared_ptr<BaseEventInfo>& info)
{
    CHECK_NULL_RETURN(taskExecutor_, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
#ifdef NG_BUILD
        auto webPattern = delegate->webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        if (delegate->richtextData_) {
            webPattern->OnContextMenuShow(info, true, true);
            result = true;
        }
        auto webEventHub = webPattern->GetWebEventHub();
        CHECK_NULL_VOID(webEventHub);
        auto propOnContextMenuShowEvent = webEventHub->GetOnContextMenuShowEvent();
        CHECK_NULL_VOID(propOnContextMenuShowEvent);
        result = propOnContextMenuShowEvent(info);
        if (!delegate->richtextData_) {
            webPattern->OnContextMenuShow(info, false, result);
        }
        return;
#else
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            if (delegate->richtextData_) {
                webPattern->OnContextMenuShow(info, true, true);
                result = true;
            }
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnContextMenuShowEvent = webEventHub->GetOnContextMenuShowEvent();
            CHECK_NULL_VOID(propOnContextMenuShowEvent);
            result = propOnContextMenuShowEvent(info);
            if (!delegate->richtextData_) {
                webPattern->OnContextMenuShow(info, false, result);
            }
            return;
        }
        auto webCom = delegate->webComponent_.Upgrade();
        CHECK_NULL_VOID(webCom);
        result = webCom->OnContextMenuShow(info.get());
#endif
    }, "ArkUIWebContextMenuShow");
    if (result) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_RETURN(webPattern, result);
        webPattern->DestroyAnalyzerOverlay();
    }
    return result;
}

void WebDelegate::OnContextMenuHide(const std::string& info)
{
    CHECK_NULL_VOID(taskExecutor_);
    auto jsTaskExecutor = SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), info]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            webPattern->OnContextMenuHide();
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnContextMenuHideEvent = webEventHub->GetOnContextMenuHideEvent();
            CHECK_NULL_VOID(propOnContextMenuHideEvent);
            propOnContextMenuHideEvent(std::make_shared<ContextMenuHideEvent>(info));
            return;
        } else {
            TAG_LOGW(AceLogTag::ACE_WEB, "current is not new pipeline");
        }
    }, "ArkUIWebContextMenuHide");
    return;
}

bool WebDelegate::OnHandleInterceptUrlLoading(const std::string& data)
{
    CHECK_NULL_RETURN(taskExecutor_, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
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
    }, "ArkUIWebHandleInterceptUrlLoading");
    return result;
}

bool WebDelegate::OnHandleInterceptLoading(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request)
{
    CHECK_NULL_RETURN(taskExecutor_, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), request, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        auto webRequest = AceType::MakeRefPtr<WebRequest>(request->RequestHeaders(), request->Method(), request->Url(),
            request->FromGesture(), request->IsAboutMainFrame(), request->IsRequestRedirect());
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
    }, "ArkUIWebHandleInterceptLoading");
    return result;
}

void WebDelegate::OnResourceLoad(const std::string& url)
{
    if (onResourceLoadV2_) {
        onResourceLoadV2_(std::make_shared<ResourceLoadEvent>(url));
    }
}

void WebDelegate::OnScaleChange(float oldScaleFactor, float newScaleFactor)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), oldScaleFactor, newScaleFactor]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onScaleChangeV2 = delegate->onScaleChangeV2_;
            if (onScaleChangeV2) {
                onScaleChangeV2(std::make_shared<ScaleChangeEvent>(oldScaleFactor, newScaleFactor));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebScaleChange");
}

void WebDelegate::OnScroll(double xOffset, double yOffset)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), xOffset, yOffset]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onScrollV2 = delegate->onScrollV2_;
            if (onScrollV2) {
                onScrollV2(std::make_shared<WebOnScrollEvent>(xOffset, yOffset));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebScroll");
}

void WebDelegate::OnSearchResultReceive(int activeMatchOrdinal, int numberOfMatches, bool isDoneCounting)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), activeMatchOrdinal, numberOfMatches, isDoneCounting]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onSearchResultReceiveV2 = delegate->onSearchResultReceiveV2_;
            if (onSearchResultReceiveV2) {
                onSearchResultReceiveV2(
                    std::make_shared<SearchResultReceiveEvent>(activeMatchOrdinal, numberOfMatches, isDoneCounting));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebSearchResultReceive");
}

bool WebDelegate::OnDragAndDropData(const void* data, size_t len, int width, int height)
{
    pixelMap_ = PixelMap::ConvertSkImageToPixmap(static_cast<const uint32_t*>(data), len, width, height);
    if (pixelMap_ == nullptr) {
        return false;
    }
    isRefreshPixelMap_ = true;

    auto webPattern = webPattern_.Upgrade();
    if (!webPattern) {
        return false;
    }
    return webPattern->NotifyStartDragTask();
}

bool WebDelegate::OnDragAndDropDataUdmf(std::shared_ptr<OHOS::NWeb::NWebDragData> dragData)
{
    const void* data = nullptr;
    size_t len = 0;
    int width = 0;
    int height = 0;
    dragData->GetPixelMapSetting(&data, len, width, height);
    pixelMap_ = PixelMap::ConvertSkImageToPixmap(static_cast<const uint32_t*>(data), len, width, height);
    CHECK_NULL_RETURN(pixelMap_, false);
    isRefreshPixelMap_ = true;

    dragData_ = dragData;
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_RETURN(webPattern, false);

    if (webPattern->IsRootNeedExportTexture()) {
        return false;
    }

    if (dragData->IsDragNewStyle() && (!webPattern->IsNewDragStyle() || !webPattern->IsPreviewImageNodeExist())) {
        TAG_LOGI(AceLogTag::ACE_WEB, "OnDragAndDropDataUdmf not a new style");
        auto context = context_.Upgrade();
        CHECK_NULL_RETURN(context, false);
        CHECK_NULL_RETURN(context->GetTaskExecutor(), false);
        context->GetTaskExecutor()->PostDelayedTask(
            [weak = WeakClaim(this)]() {
                auto delegate = weak.Upgrade();
                CHECK_NULL_VOID(delegate);
                auto pattern = delegate->webPattern_.Upgrade();
                pattern->NotifyStartDragTask(true);
            },
            TaskExecutor::TaskType::UI, DRAG_DELAY_MILLISECONDS, "OnDragAndDropDataUdmf");
        return true;
    } else if (!dragData->IsDragNewStyle()) {
        webPattern->SetNewDragStyle(false);
    }
    return webPattern->NotifyStartDragTask();
}

bool WebDelegate::IsDragging()
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_RETURN(webPattern, false);
    return webPattern->IsDragging();
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
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostSyncTask(
        [weak = WeakClaim(this), targetUrl, isAlert, isUserTrigger, handler]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            int32_t parentNWebId = (delegate->nweb_ ? static_cast<int32_t>(delegate->nweb_->GetWebId()) : -1);
            auto param = std::make_shared<WebWindowNewEvent>(
                targetUrl, isAlert, isUserTrigger, AceType::MakeRefPtr<WebWindowNewHandlerOhos>(handler, parentNWebId));
#ifdef NG_BUILD
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnWindowNewEvent = webEventHub->GetOnWindowNewEvent();
            CHECK_NULL_VOID(propOnWindowNewEvent);
            propOnWindowNewEvent(param);
            return;
#else
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
#endif
        },
        TaskExecutor::TaskType::JS, "ArkUIWebWindowNewEvent");
}

void WebDelegate::OnWindowExit()
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onWindowExitV2 = delegate->onWindowExitV2_;
            if (onWindowExitV2) {
                onWindowExitV2(std::make_shared<WebWindowExitEvent>());
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebWindowExit");
}

void WebDelegate::OnPageVisible(const std::string& url)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDelegate::OnPageVisible, web id = %{public}d", GetWebId());
    if (onPageVisibleV2_) {
        onPageVisibleV2_(std::make_shared<PageVisibleEvent>(url));
    } else {
        TAG_LOGI(AceLogTag::ACE_WEB, "The developer has not registered this OnPageVisible event");
    }

    if (isEnableHardwareComposition_) {
        return;
    }
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostDelayedTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            delegate->EnableHardware();
        },
        TaskExecutor::TaskType::UI, DELAY_MILLISECONDS_1000, "ArkUIWebEnableHardware");
}

void WebDelegate::OnFirstContentfulPaint(int64_t navigationStartTick, int64_t firstContentfulPaintMs)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDelegate::OnFirstContentfulPaint, web id = %{public}d", GetWebId());
    if (onFirstContentfulPaintV2_) {
        onFirstContentfulPaintV2_(
            std::make_shared<FirstContentfulPaintEvent>(navigationStartTick, firstContentfulPaintMs));
    }
}

void WebDelegate::OnFirstMeaningfulPaint(std::shared_ptr<OHOS::NWeb::NWebFirstMeaningfulPaintDetails> details)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDelegate::OnFirstMeaningfulPaint, web id = %{public}d", GetWebId());
    if (OnFirstMeaningfulPaintV2_) {
        OnFirstMeaningfulPaintV2_(std::make_shared<FirstMeaningfulPaintEvent>(
            details->GetNavigationStartTime(), details->GetFirstMeaningfulPaintTime()));
    }
}

void WebDelegate::OnLargestContentfulPaint(std::shared_ptr<OHOS::NWeb::NWebLargestContentfulPaintDetails> details)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDelegate::OnLargestContentfulPaint, web id = %{public}d", GetWebId());
    if (OnLargestContentfulPaintV2_) {
        OnLargestContentfulPaintV2_(std::make_shared<LargestContentfulPaintEvent>(details->GetNavigationStartTime(),
            details->GetLargestImagePaintTime(), details->GetLargestTextPaintTime(),
            details->GetLargestImageLoadStartTime(), details->GetLargestImageLoadEndTime(), details->GetImageBPP()));
    }
}

void WebDelegate::EnableHardware()
{
    if (isEnableHardwareComposition_) {
        return;
    }

    auto surfaceNode = OHOS::Rosen::RSBaseNode::ReinterpretCast<OHOS::Rosen::RSSurfaceNode>(surfaceRsNode_);
    CHECK_NULL_VOID(surfaceNode);
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDelegate::EnableHardware, web id = %{public}d", GetWebId());
    ACE_SCOPED_TRACE("WebDelegate::EnableHardware, web id = %d", GetWebId());
    surfaceNode->SetHardwareEnabled(true);
    isEnableHardwareComposition_ = true;
}

void WebDelegate::OnSafeBrowsingCheckResult(int threat_type)
{
    if (onSafeBrowsingCheckResultV2_) {
        onSafeBrowsingCheckResultV2_(
            std::make_shared<SafeBrowsingCheckResultEvent>(threat_type));
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

void WebDelegate::OnNavigationEntryCommitted(std::shared_ptr<OHOS::NWeb::NWebLoadCommittedDetails> details)
{
    if (onNavigationEntryCommittedV2_) {
        NavigationType type = static_cast<NavigationType>(details->GetNavigationType());
        onNavigationEntryCommittedV2_(std::make_shared<NavigationEntryCommittedEvent>(details->GetURL(),
            type, details->IsMainFrame(), details->IsSameDocument(),
            details->DidReplaceEntry()));
    }
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->DestroyAnalyzerOverlay();
}

void WebDelegate::OnFaviconReceived(const void* data, size_t width, size_t height, OHOS::NWeb::ImageColorType colorType,
    OHOS::NWeb::ImageAlphaType alphaType)
{
    auto param = std::make_shared<FaviconReceivedEvent>(
        AceType::MakeRefPtr<FaviconReceivedOhos>(data, width, height, colorType, alphaType));
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

void WebDelegate::OnGetTouchHandleHotZone(std::shared_ptr<OHOS::NWeb::NWebTouchHandleHotZone> hotZone)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    auto touchHandleSize = theme->GetHandleHotZoneRadius().ConvertToPx();
    if (hotZone) {
        hotZone->SetWidth(touchHandleSize);
        hotZone->SetHeight(touchHandleSize);
    }
}

RefPtr<PixelMap> WebDelegate::GetDragPixelMap()
{
    return pixelMap_;
}

#ifdef OHOS_STANDARD_SYSTEM
void WebDelegate::HandleTouchDown(const int32_t& id, const double& x, const double& y, bool from_overlay)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->OnTouchPress(id, x, y, from_overlay);
    }
}

void WebDelegate::HandleTouchUp(const int32_t& id, const double& x, const double& y, bool from_overlay)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->OnTouchRelease(id, x, y, from_overlay);
    }
}

void WebDelegate::HandleTouchMove(const int32_t& id, const double& x, const double& y, bool from_overlay)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->OnTouchMove(id, x, y, from_overlay);
    }
}

void WebDelegate::HandleTouchMove(const std::vector<std::shared_ptr<OHOS::NWeb::NWebTouchPointInfo>> &touch_point_infos,
                                  bool from_overlay)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->OnTouchMove(touch_point_infos, from_overlay);
    }
}

void WebDelegate::HandleTouchCancel()
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->OnTouchCancel();
    }
}

void WebDelegate::HandleTouchpadFlingEvent(const double& x, const double& y, const double& vx, const double& vy)
{
    if (nweb_) {
        nweb_->SendTouchpadFlingEvent(x, y, vx, vy);
    }
}

void WebDelegate::WebHandleTouchpadFlingEvent(const double& x, const double& y,
    const double& vx, const double& vy, const std::vector<int32_t>& pressedCodes)
{
    if (nweb_) {
        nweb_->WebSendTouchpadFlingEvent(x, y, vx, vy, pressedCodes);
    }
}

void WebDelegate::HandleAxisEvent(const double& x, const double& y, const double& deltaX, const double& deltaY)
{
    if (nweb_) {
        nweb_->SendMouseWheelEvent(x, y, deltaX, deltaY);
    }
}

void WebDelegate::WebHandleAxisEvent(const double& x, const double& y,
    const double& deltaX, const double& deltaY, const std::vector<int32_t>& pressedCodes)
{
    if (nweb_) {
        nweb_->WebSendMouseWheelEvent(x, y, deltaX, deltaY, pressedCodes);
    }
}

bool WebDelegate::OnKeyEvent(int32_t keyCode, int32_t keyAction)
{
    if (nweb_) {
        return nweb_->SendKeyEvent(keyCode, keyAction);
    }
    return false;
}

bool WebDelegate::WebOnKeyEvent(int32_t keyCode, int32_t keyAction,
    const std::vector<int32_t>& pressedCodes)
{
    CHECK_NULL_RETURN(nweb_, false);
    return nweb_->WebSendKeyEvent(keyCode, keyAction, pressedCodes);
}

void WebDelegate::OnMouseEvent(int32_t x, int32_t y, const MouseButton button, const MouseAction action, int count)
{
    if (nweb_) {
        nweb_->SendMouseEvent(x, y, static_cast<int>(button), static_cast<int>(action), count);
    }
}

void WebDelegate::WebOnMouseEvent(const std::shared_ptr<OHOS::NWeb::NWebMouseEvent>& mouseEvent)
{
    CHECK_NULL_VOID(nweb_);
    nweb_->WebSendMouseEvent(mouseEvent);
}

void WebDelegate::OnFocus(const OHOS::NWeb::FocusReason& reason)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->OnFocus(reason);
    }
}

bool WebDelegate::NeedSoftKeyboard()
{
    if (nweb_) {
        return nweb_->NeedSoftKeyboard();
    }
    return false;
}

void WebDelegate::OnBlur()
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->OnBlur(blurReason_);
    }
}

void WebDelegate::UpdateClippedSelectionBounds(int32_t x, int32_t y, int32_t w, int32_t h)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateClippedSelectionBounds(x, y, w, h);
}

bool WebDelegate::RunQuickMenu(std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback)
{
#ifdef NG_BUILD
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_RETURN(webPattern, false);
    return webPattern->RunQuickMenu(params, callback);
#else
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_RETURN(webPattern, false);
        return webPattern->RunQuickMenu(params, callback);
    }
    auto renderWeb = renderWeb_.Upgrade();
    if (!renderWeb || !params || !callback) {
        return false;
    }

    return renderWeb->RunQuickMenu(params, callback);
#endif
}

void WebDelegate::HideHandleAndQuickMenuIfNecessary(bool hide)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->HideHandleAndQuickMenuIfNecessary(hide);
}

void WebDelegate::ChangeVisibilityOfQuickMenu()
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->ChangeVisibilityOfQuickMenu();
}

void WebDelegate::OnQuickMenuDismissed()
{
#ifdef NG_BUILD
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnQuickMenuDismissed();
    return;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->OnQuickMenuDismissed();
        return;
    }
    auto renderWeb = renderWeb_.Upgrade();
    CHECK_NULL_VOID(renderWeb);
    renderWeb->OnQuickMenuDismissed();
#endif
}

void WebDelegate::OnTouchSelectionChanged(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
#ifdef NG_BUILD
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
    return;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
        return;
    }
    auto renderWeb = renderWeb_.Upgrade();
    CHECK_NULL_VOID(renderWeb);
    renderWeb->OnTouchSelectionChanged(insertHandle, startSelectionHandle, endSelectionHandle);
#endif
}

bool WebDelegate::OnCursorChange(const OHOS::NWeb::CursorType& type, std::shared_ptr<OHOS::NWeb::NWebCursorInfo> info)
{
#ifdef NG_BUILD
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_RETURN(webPattern, false);
    return webPattern->OnCursorChange(type, info);
#else
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_RETURN(webPattern, false);
        return webPattern->OnCursorChange(type, info);
    }
    auto renderWeb = renderWeb_.Upgrade();
    CHECK_NULL_RETURN(renderWeb, false);
    return renderWeb->OnCursorChange(type, info);
#endif
}

void WebDelegate::OnSelectPopupMenu(std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params,
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback)
{
#ifdef NG_BUILD
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnSelectPopupMenu(params, callback);
    return;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->OnSelectPopupMenu(params, callback);
        return;
    }
    auto renderWeb = renderWeb_.Upgrade();
    CHECK_NULL_VOID(renderWeb);
    return renderWeb->OnSelectPopupMenu(params, callback);
#endif
}

void WebDelegate::HandleDragEvent(int32_t x, int32_t y, const DragAction& dragAction)
{
    if (nweb_) {
        std::shared_ptr<NWebDragEventImpl> dragEvent =
	    std::make_shared<NWebDragEventImpl>(x, y, static_cast<OHOS::NWeb::DragAction>(dragAction));
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

void WebDelegate::SetDrawRect(int32_t x, int32_t y, int32_t width, int32_t height)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->SetDrawRect(x, y, width, height);
    }
}

bool WebDelegate::GetPendingSizeStatus()
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        return nweb_->GetPendingSizeStatus();
    }
    return false;
}

void WebDelegate::HandleAccessibilityHoverEvent(int32_t x, int32_t y)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->SendAccessibilityHoverEvent(x, y);
    }
}

void WebDelegate::NotifyAutoFillViewData(const std::string& jsonStr)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), jsonStr]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            auto webMessage = std::make_shared<OHOS::NWeb::NWebMessage>(NWebValue::Type::NONE);
            webMessage->SetType(NWebValue::Type::STRING);
            webMessage->SetString(jsonStr);
            delegate->nweb_->FillAutofillData(webMessage);
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebNotifyAutoFillViewData");
}

void WebDelegate::AutofillCancel(const std::string& fillContent)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), fillContent]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            delegate->nweb_->OnAutofillCancel(fillContent);
        },
        TaskExecutor::TaskType::UI, "ArkUIWebAutofillCancel");
}

bool WebDelegate::HandleAutoFillEvent(const std::shared_ptr<OHOS::NWeb::NWebMessage>& viewDataJson)
{
    auto pattern = webPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->HandleAutoFillEvent(viewDataJson);
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

void WebDelegate::SetRenderMode(RenderMode renderMode)
{
    renderMode_ = static_cast<int32_t>(renderMode);
}

void WebDelegate::SetFitContentMode(WebLayoutMode layoutMode)
{
    layoutMode_ = static_cast<int32_t>(layoutMode);
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
    isEnhanceSurface_ = isEnhanceSurface;
}

sptr<OHOS::SurfaceDelegate> WebDelegate::GetSurfaceDelegateClient()
{
    return surfaceDelegate_;
}

void WebDelegate::SetBoundsOrResize(const Size& drawSize, const Offset& offset, bool isKeyboard)
{
    if ((drawSize.Width() == 0) && (drawSize.Height() == 0)) {
        return;
    }
    if (isEnhanceSurface_) {
        if (surfaceDelegate_) {
            if (needResizeAtFirst_) {
                Resize(drawSize.Width(), drawSize.Height(), isKeyboard);
                needResizeAtFirst_ = false;
            }
            Size webSize = GetEnhanceSurfaceSize(drawSize);
            surfaceDelegate_->SetBounds(offset.GetX(), (int32_t)offset.GetY(), webSize.Width(), webSize.Height());
        }
    } else {
        Resize(drawSize.Width(), drawSize.Height(), isKeyboard);
    }
}

void WebDelegate::ResizeVisibleViewport(const Size& visibleSize, bool isKeyboard)
{
    double width = visibleSize.Width();
    double height = visibleSize.Height();
    if (NearEqual(resizeVisibleWidth_, width) && NearEqual(resizeVisibleHeight_, height)) {
        return;
    }
    resizeVisibleWidth_ = width;
    resizeVisibleHeight_ = height;
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), width, height, isKeyboard]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_ && !delegate->window_) {
                delegate->nweb_->ResizeVisibleViewport(
                    width < 0 ? 0 : std::ceil(width), height < 0 ? 0 : std::ceil(height), isKeyboard);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebResizeVisibleViewport");
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->DestroyAnalyzerOverlay();
}

Offset WebDelegate::GetWebRenderGlobalPos()
{
    return offset_;
}

Size WebDelegate::GetEnhanceSurfaceSize(const Size& drawSize)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, Size());
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
    CHECK_NULL_VOID(rsNode_);
    surfaceRsNode_ = webPattern->GetSurfaceRSNode();
    CHECK_NULL_VOID(surfaceRsNode_);
    surfaceNodeId_ = webPattern->GetWebSurfaceNodeId();
}
void WebDelegate::SetPopupSurface(const RefPtr<NG::RenderSurface>& popupSurface)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), popupSurface]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                auto rosenRenderSurface = AceType::DynamicCast<NG::RosenRenderSurface>(popupSurface);
                delegate->popupRenderSurface_ = rosenRenderSurface;
                delegate->popupSurface_ = rosenRenderSurface->GetSurface();

                CHECK_NULL_VOID(delegate->popupSurface_);
                delegate->nweb_->SetPopupSurface(reinterpret_cast<void *>(&delegate->popupSurface_));
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUISetPopupSurface");
}
#endif

void WebDelegate::UpdateScreenOffSet(double& offsetX, double& offsetY)
{
#ifdef NG_BUILD
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
#else
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
#endif
}

void WebDelegate::UpdateOverScrollMode(const int overscrollModeValue)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), overscrollModeValue]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
            CHECK_NULL_VOID(setting);
            setting->PutOverscrollMode(overscrollModeValue);
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateOverScrollMode");
}

void WebDelegate::UpdateBlurOnKeyboardHideMode(const int isBlurOnKeyboardHideEnable)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isBlurOnKeyboardHideEnable]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
            CHECK_NULL_VOID(setting);
            setting->SetBlurOnKeyboardHideMode(isBlurOnKeyboardHideEnable);
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateBlurOnKeyboardHideMode");
}

void WebDelegate::UpdateCopyOptionMode(const int copyOptionModeValue)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), copyOptionModeValue]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
            CHECK_NULL_VOID(setting);
            setting->PutCopyOptionMode(
                static_cast<OHOS::NWeb::NWebPreference::CopyOptionMode>(copyOptionModeValue));
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateCopyOptionMode");
}

void WebDelegate::UpdateTextAutosizing(bool isTextAutosizing)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isTextAutosizing]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->PutTextAutosizingEnabled(isTextAutosizing);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateTextAutosizing");
}

void WebDelegate::UpdateNativeVideoPlayerConfig(bool enable, bool shouldOverlay)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), enable, shouldOverlay]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
            CHECK_NULL_VOID(setting);
            setting->SetNativeVideoPlayerConfig(enable, shouldOverlay);
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateNativeVideoPlayerConfig");
}

void WebDelegate::RegisterSurfacePositionChangedCallback()
{
#ifdef NG_BUILD
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
            });
    }
    return;
#else
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
                });
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
            });
    }
#endif
}

void WebDelegate::UnregisterSurfacePositionChangedCallback()
{
    if (callbackId_ <= 0) {
        return;
    }
#ifdef NG_BUILD
    auto pipelineContext = DynamicCast<NG::PipelineContext>(context_.Upgrade());
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UnregisterSurfacePositionChangedCallback(callbackId_);
    callbackId_ = 0;
    return;
#else
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
#endif
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

void WebDelegate::OnDateTimeChooserPopup(std::shared_ptr<OHOS::NWeb::NWebDateTimeChooser> chooser,
    const std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>>& suggestions,
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
        TaskExecutor::TaskType::JS, "ArkUIWebOverScroll");
}

void WebDelegate::SetTouchEventInfo(std::shared_ptr<OHOS::NWeb::NWebNativeEmbedTouchEvent> touchEvent,
                                    TouchEventInfo& touchEventInfo)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    if (touchEvent) {
        TouchEvent event;
        event.SetId(touchEvent->GetId())
            .SetX(touchEvent->GetX())
            .SetY(touchEvent->GetY())
            .SetScreenX(touchEvent->GetScreenX())
            .SetScreenY(touchEvent->GetScreenY())
            .SetType(static_cast<OHOS::Ace::TouchType>(touchEvent->GetType()));
        webPattern->SetTouchEventInfo(event, touchEventInfo, touchEvent->GetEmbedId());
    } else {
        TouchEvent event;
        event.SetId(0);
        webPattern->SetTouchEventInfo(event, touchEventInfo, DEFAULT_NATIVE_EMBED_ID);
    }
}

void WebDelegate::OnNativeEmbedAllDestory()
{
    if (!isEmbedModeEnabled_) {
        return;
    }
    auto iter = embedDataInfo_.begin();
    for (; iter != embedDataInfo_.end(); iter++) {
        EmbedInfo info;
        std::shared_ptr<OHOS::NWeb::NWebNativeEmbedDataInfo> dataInfo  = iter->second;
        if (dataInfo == nullptr) {
            continue;
        }
        std::string embedId = dataInfo->GetEmbedId();
        TAG_LOGI(AceLogTag::ACE_WEB, "OnNativeEmbedAllDestory embdedid=%{public}s", embedId.c_str());
        std::string surfaceId = dataInfo->GetSurfaceId();
        auto embedInfo = dataInfo->GetNativeEmbedInfo();
        if (embedInfo) {
            info = {embedInfo->GetId(), embedInfo->GetType(), embedInfo->GetSrc(),
                embedInfo->GetUrl(), embedInfo->GetTag(), embedInfo->GetWidth(),
                embedInfo->GetHeight(), embedInfo->GetX(), embedInfo->GetY(),
                embedInfo->GetParams()};
        }
        if (OnNativeEmbedAllDestoryV2_) {
            OHOS::Ace::NativeEmbedStatus status = OHOS::Ace::NativeEmbedStatus::DESTROY;
            OnNativeEmbedAllDestoryV2_(
                std::make_shared<NativeEmbedDataInfo>(status, surfaceId, embedId, info));
        }
    }
    embedDataInfo_.clear();
}

void WebDelegate::OnNativeEmbedLifecycleChange(std::shared_ptr<OHOS::NWeb::NWebNativeEmbedDataInfo> dataInfo)
{
    if (!isEmbedModeEnabled_) {
        return;
    }

    EmbedInfo info;
    std::string embedId;
    std::string surfaceId;
    OHOS::Ace::NativeEmbedStatus status = OHOS::Ace::NativeEmbedStatus::CREATE;
    if (dataInfo) {
        embedId = dataInfo->GetEmbedId();
        surfaceId = dataInfo->GetSurfaceId();
        status = static_cast<OHOS::Ace::NativeEmbedStatus>(dataInfo->GetStatus());

        auto embedInfo = dataInfo->GetNativeEmbedInfo();
        if (embedInfo) {
            info = {embedInfo->GetId(), embedInfo->GetType(), embedInfo->GetSrc(),
                embedInfo->GetUrl(), embedInfo->GetTag(), embedInfo->GetWidth(),
                embedInfo->GetHeight(), embedInfo->GetX(), embedInfo->GetY(),
                embedInfo->GetParams()};
        }

        if (status == OHOS::Ace::NativeEmbedStatus::CREATE || status == OHOS::Ace::NativeEmbedStatus::UPDATE) {
            embedDataInfo_.insert_or_assign(embedId, dataInfo);
        } else if (status == OHOS::Ace::NativeEmbedStatus::DESTROY) {
            auto iter = embedDataInfo_.find(embedId);
            if (iter != embedDataInfo_.end()) {
                embedDataInfo_.erase(iter);
            }
        }
    }

    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), status, surfaceId, embedId, info]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto OnNativeEmbedLifecycleChangeV2_ = delegate->OnNativeEmbedLifecycleChangeV2_;
            if (OnNativeEmbedLifecycleChangeV2_) {
                OnNativeEmbedLifecycleChangeV2_(
                    std::make_shared<NativeEmbedDataInfo>(status, surfaceId, embedId, info));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebNativeEmbedLifecycleChange");
}

void WebDelegate::OnNativeEmbedVisibilityChange(const std::string& embedId, bool visibility)
{
    if (!isEmbedModeEnabled_) {
        return;
    }

    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), embedId, visibility]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto OnNativeEmbedVisibilityChangeV2_ = delegate->OnNativeEmbedVisibilityChangeV2_;
            if (OnNativeEmbedVisibilityChangeV2_) {
                OnNativeEmbedVisibilityChangeV2_(
                    std::make_shared<NativeEmbedVisibilityInfo>(visibility, embedId));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebNativeEmbedVisibilityChange");
}

void WebDelegate::OnNativeEmbedGestureEvent(std::shared_ptr<OHOS::NWeb::NWebNativeEmbedTouchEvent> event)
{
    if (event->GetId() == NO_NATIVE_FINGER_TYPE) {
        auto webPattern = webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        webPattern->RequestFocus();
        return;
    }
    CHECK_NULL_VOID(taskExecutor_);
    TouchEventInfo touchEventInfo("touchEvent");
    auto embedId = event ? event->GetEmbedId() : "";
    SetTouchEventInfo(event, touchEventInfo);
    TAG_LOGD(AceLogTag::ACE_WEB, "hit Emebed gusture event notify");
    auto param = AceType::MakeRefPtr<GestureEventResultOhos>(event->GetResult());
    auto type = event->GetType();
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), embedId, touchEventInfo, param, type]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto OnNativeEmbedGestureEventV2_ = delegate->OnNativeEmbedGestureEventV2_;
            if (OnNativeEmbedGestureEventV2_) {
                OnNativeEmbedGestureEventV2_(
                    std::make_shared<NativeEmbeadTouchInfo>(embedId, touchEventInfo, param));
                if (!param->HasSendTask()) {
                    param->SetGestureEventResult(true);
                }
                if (!param->GetEventResult() && type == OHOS::NWeb::TouchType::DOWN) {
                    auto webPattern = delegate->webPattern_.Upgrade();
                    CHECK_NULL_VOID(webPattern);
                    webPattern->RequestFocus();
                }
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebNativeEmbedGestureEvent");
}

void WebDelegate::SetToken()
{
    auto container = AceType::DynamicCast<Platform::AceContainer>(Container::Current());
    CHECK_NULL_VOID(container);
    int32_t instanceId = container->GetInstanceId();
    auto window = Platform::AceContainer::GetUIWindow(instanceId);
    CHECK_NULL_VOID(window);
    auto uiContent = window->GetUIContent();
    CHECK_NULL_VOID(nweb_);
    CHECK_NULL_VOID(uiContent);
    nweb_->SetToken(static_cast<void*>(uiContent));
    TAG_LOGD(AceLogTag::ACE_WEB, "setToken success");
}

void WebDelegate::OnOverScrollFlingVelocity(float xVelocity, float yVelocity, bool isFling)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnOverScrollFlingVelocity(xVelocity, yVelocity, isFling);
}

void WebDelegate::OnScrollState(bool scrollState)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnScrollState(scrollState);
}

void WebDelegate::OnRootLayerChanged(int width, int height)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnRootLayerChanged(width, height);
}

void WebDelegate::ReleaseResizeHold()
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->ReleaseResizeHold();
}

void WebDelegate::SetVirtualKeyBoardArg(int32_t width, int32_t height, double keyboard)
{
    if (nweb_) {
        nweb_->SetVirtualKeyBoardArg(width, height, keyboard);
    }
}

bool WebDelegate::ShouldVirtualKeyboardOverlay()
{
    if (nweb_) {
        return nweb_->ShouldVirtualKeyboardOverlay();
    }
    return false;
}

bool WebDelegate::FilterScrollEvent(const float x, const float y, const float xVelocity, const float yVelocity)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_RETURN(webPattern, false);
    return webPattern->FilterScrollEvent(x, y, xVelocity, yVelocity);
}

void WebDelegate::ScrollBy(float deltaX, float deltaY)
{
    CHECK_NULL_VOID(nweb_);
    nweb_->ScrollBy(deltaX, deltaY);
}

void WebDelegate::ScrollByRefScreen(float deltaX, float deltaY, float vx, float vy)
{
    CHECK_NULL_VOID(nweb_);
    nweb_->ScrollByRefScreen(deltaX, deltaY, vx, vy);
}

void WebDelegate::SetJavaScriptItems(const ScriptItems& scriptItems, const ScriptItemType& type)
{
    if (type == ScriptItemType::DOCUMENT_START) {
        onDocumentStartScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    } else {
        onDocumentEndScriptItems_ = std::make_optional<ScriptItems>(scriptItems);
    }
}

void WebDelegate::JavaScriptOnDocumentStart()
{
    CHECK_NULL_VOID(nweb_);
    if (onDocumentStartScriptItems_.has_value()) {
        nweb_->JavaScriptOnDocumentStart(onDocumentStartScriptItems_.value());
        onDocumentStartScriptItems_ = std::nullopt;
    }
}

void WebDelegate::JavaScriptOnDocumentEnd()
{
    CHECK_NULL_VOID(nweb_);
    if (onDocumentEndScriptItems_.has_value()) {
        nweb_->JavaScriptOnDocumentEnd(onDocumentEndScriptItems_.value());
        onDocumentEndScriptItems_ = std::nullopt;
    }
}

bool WebDelegate::ExecuteAction(int64_t accessibilityId, AceAction action,
    const std::map<std::string, std::string>& actionArguments)
{
    if (!accessibilityState_) {
        return false;
    }
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    uint32_t nwebAction = static_cast<uint32_t>(action);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), accessibilityId, nwebAction, actionArguments]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            CHECK_NULL_VOID(delegate->nweb_);
            delegate->nweb_->PerformAction(accessibilityId, nwebAction, actionArguments);
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebExecuteAction");
    return true;
}

void WebDelegate::SetAccessibilityState(bool state, bool isDelayed)
{
    if (state == accessibilityState_) {
        return;
    }
    accessibilityState_ = state;
    if (state) {
        auto context = context_.Upgrade();
        CHECK_NULL_VOID(context);
        uint32_t delayedTime = 0;
        if (isDelayed) {
            delayedTime = ACCESSIBILITY_DELAY_MILLISECONDS;
        }
        context->GetTaskExecutor()->PostDelayedTask(
            [weak = WeakClaim(this), state]() {
                auto delegate = weak.Upgrade();
                CHECK_NULL_VOID(delegate);
                CHECK_NULL_VOID(delegate->nweb_);
                delegate->nweb_->SetAccessibilityState(state);
            },
            TaskExecutor::TaskType::PLATFORM, delayedTime, "ArkUIWebSetAccessibilityState");
    } else {
        CHECK_NULL_VOID(nweb_);
        nweb_->SetAccessibilityState(state);
    }
}

std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> WebDelegate::GetFocusedAccessibilityNodeInfo(
    int64_t accessibilityId, bool isAccessibilityFocus)
{
    CHECK_NULL_RETURN(nweb_, nullptr);
    if (!accessibilityState_) {
        return nullptr;
    }
    return nweb_->GetFocusedAccessibilityNodeInfo(accessibilityId, isAccessibilityFocus);
}

std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> WebDelegate::GetAccessibilityNodeInfoById(
    int64_t accessibilityId)
{
    CHECK_NULL_RETURN(nweb_, nullptr);
    if (!accessibilityState_) {
        return nullptr;
    }
    return nweb_->GetAccessibilityNodeInfoById(accessibilityId);
}

std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> WebDelegate::GetAccessibilityNodeInfoByFocusMove(
    int64_t accessibilityId, int32_t direction)
{
    CHECK_NULL_RETURN(nweb_, nullptr);
    if (!accessibilityState_) {
        return nullptr;
    }
    return nweb_->GetAccessibilityNodeInfoByFocusMove(accessibilityId, direction);
}

OHOS::NWeb::NWebPreference::CopyOptionMode WebDelegate::GetCopyOptionMode() const
{
    CHECK_NULL_RETURN(nweb_, OHOS::NWeb::NWebPreference::CopyOptionMode::CROSS_DEVICE);
    std::shared_ptr<OHOS::NWeb::NWebPreference> setting = nweb_->GetPreference();
    CHECK_NULL_RETURN(setting, OHOS::NWeb::NWebPreference::CopyOptionMode::CROSS_DEVICE);
    auto copyOption = setting->GetCopyOptionMode();
    return copyOption;
}

bool WebDelegate::OnOpenAppLink(
    const std::string& url, std::shared_ptr<OHOS::NWeb::NWebAppLinkCallback> callback)
{
    if (!callback) {
        TAG_LOGE(AceLogTag::ACE_WEB, "open app link callback is nullptr");
        return false;
    }
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, false);
    auto jsTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), url, callback]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        auto webPattern = delegate->webPattern_.Upgrade();
        CHECK_NULL_VOID(webPattern);
        auto openAppLinkCallback = webPattern->GetOnOpenAppLinkCallback();
        CHECK_NULL_VOID(openAppLinkCallback);
        openAppLinkCallback(std::make_shared<WebAppLinkEvent>(url,
            AceType::MakeRefPtr<WebAppLinkCallbackOhos>(callback)));
        }, "ArkUIWebOnOpenAppLink");
    return true;
}

std::string WebDelegate::GetCanonicalEncodingName(const std::string& alias_name) const
{
    const char* standards[3] = { "HTML", "MIME", "IANA" };
    for (auto* standard : standards) {
        UErrorCode errorCode = U_ZERO_ERROR;
        const char* result =
            ucnv_getStandardName(alias_name.c_str(), standard, &errorCode);
        if (!U_SUCCESS(errorCode) || !result)
            continue;
        std::string canonicalName(result);
        for (const auto& encodingName : CANONICALENCODINGNAMES) {
            if (encodingName == canonicalName)
                return canonicalName;
        }
    }
    return DEFAULT_CANONICAL_ENCODING_NAME;
}

void WebDelegate::UpdateDefaultTextEncodingFormat(const std::string& textEncodingFormat)
{
    auto context = context_.Upgrade();
    if (!context || textEncodingFormat.empty()) {
        return;
    }
    auto canonicalEncodingName = GetCanonicalEncodingName(textEncodingFormat);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), canonicalEncodingName]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->PutDefaultTextEncodingFormat(canonicalEncodingName);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateDefaultTextEncodingFormat");
}

void WebDelegate::OnIntelligentTrackingPreventionResult(
    const std::string& websiteHost, const std::string& trackerHost)
{
    if (onIntelligentTrackingPreventionResultV2_) {
        onIntelligentTrackingPreventionResultV2_(
            std::make_shared<IntelligentTrackingPreventionResultEvent>(
                websiteHost, trackerHost));
    }
}

bool WebDelegate::OnHandleOverrideLoading(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request)
{
    if (!request) {
        return false;
    }
    CHECK_NULL_RETURN(taskExecutor_, false);
    bool result = false;
    auto jsTaskExecutor = SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
    jsTaskExecutor.PostSyncTask([weak = WeakClaim(this), request, &result]() {
        auto delegate = weak.Upgrade();
        CHECK_NULL_VOID(delegate);
        auto webRequest = AceType::MakeRefPtr<WebRequest>(request->RequestHeaders(), request->Method(), request->Url(),
            request->FromGesture(), request->IsAboutMainFrame(), request->IsRequestRedirect());
        auto param = std::make_shared<LoadOverrideEvent>(webRequest);
        if (Container::IsCurrentUseNewPipeline()) {
            auto webPattern = delegate->webPattern_.Upgrade();
            CHECK_NULL_VOID(webPattern);
            auto webEventHub = webPattern->GetWebEventHub();
            CHECK_NULL_VOID(webEventHub);
            auto propOnOverrideUrlLoadingEvent = webEventHub->GetOnOverrideUrlLoadingEvent();
            CHECK_NULL_VOID(propOnOverrideUrlLoadingEvent);
            result = propOnOverrideUrlLoadingEvent(param);
            return;
        }
        auto webCom = delegate->webComponent_.Upgrade();
        CHECK_NULL_VOID(webCom);
        result = webCom->OnOverrideUrlLoading(param.get());
    }, "ArkUIWebHandleOverrideLoading");
    return result;
}

void WebDelegate::OnDetachContext()
{
    UnRegisterScreenLockFunction();
    UnregisterSurfacePositionChangedCallback();
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto pipelineContext = DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddAfterRenderTask(
        [weak = WeakClaim(this), instanceId = instanceId_]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            delegate->UnregisterAvoidAreaChangeListener(instanceId);
        });
    instanceId_ = INSTANCE_ID_UNDEFINED;
}

void WebDelegate::OnAttachContext(const RefPtr<NG::PipelineContext> &context)
{
    instanceId_ = context->GetInstanceId();
    context_ = context;
    RegisterSurfacePositionChangedCallback();
    if (nweb_) {
        auto screenLockCallback = std::make_shared<NWebScreenLockCallbackImpl>(context);
        nweb_->RegisterScreenLockFunction(instanceId_, screenLockCallback);
        auto windowId = context->GetFocusWindowId();
        nweb_->SetWindowId(windowId);
    }
    auto pipelineContext = DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddAfterRenderTask(
        [weak = WeakClaim(this), instanceId = instanceId_]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            delegate->RegisterAvoidAreaChangeListener(instanceId);
        });
}

void WebDelegate::UpdateMetaViewport(bool isMetaViewportEnabled)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), isMetaViewportEnabled]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                if (setting) {
                    setting->SetViewportEnable(isMetaViewportEnabled);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebUpdateMetaViewport");
}

void WebDelegate::ScaleGestureChange(double scale, double centerX, double centerY)
{
#ifdef OHOS_STANDARD_SYSTEM
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->ScaleGestureChange(scale, centerX, centerY);
    }
#endif
}

std::vector<int8_t> WebDelegate::GetWordSelection(const std::string& text, int8_t offset)
{
    auto webPattern = webPattern_.Upgrade();
    std::vector<int8_t> vec = { -1, -1 };
    CHECK_NULL_RETURN(webPattern, vec);
    return webPattern->GetWordSelection(text, offset);
}

void WebDelegate::NotifyForNextTouchEvent()
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->NotifyForNextTouchEvent();
    }
}

void WebDelegate::OnRenderProcessNotResponding(
    const std::string& jsStack, int pid, OHOS::NWeb::RenderProcessNotRespondingReason reason)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), jsStack, pid, reason]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onRenderProcessNotRespondingV2 = delegate->onRenderProcessNotRespondingV2_;
            if (onRenderProcessNotRespondingV2) {
                onRenderProcessNotRespondingV2(std::make_shared<RenderProcessNotRespondingEvent>(
                    jsStack, pid, static_cast<int>(reason)));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebHandleRenderProcessNotResponding");
}

void WebDelegate::OnRenderProcessResponding()
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this)]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onRenderProcessRespondingV2 = delegate->onRenderProcessRespondingV2_;
            if (onRenderProcessRespondingV2) {
                onRenderProcessRespondingV2(std::make_shared<RenderProcessRespondingEvent>());
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebHandleRenderProcessResponding");
}

std::string WebDelegate::GetSelectInfo() const
{
    CHECK_NULL_RETURN(nweb_, std::string());
    return nweb_->GetSelectInfo();
}

Offset WebDelegate::GetPosition(const std::string& embedId)
{
    auto iter = embedDataInfo_.find(embedId);
    if (iter != embedDataInfo_.end()) {
        std::shared_ptr<OHOS::NWeb::NWebNativeEmbedDataInfo> dataInfo  = iter->second;
        if (dataInfo) {
            auto embedInfo = dataInfo->GetNativeEmbedInfo();
            return Offset(embedInfo->GetX(), embedInfo->GetY());
        }
    }
    return Offset();
}

void WebDelegate::OnShowAutofillPopup(
    const float offsetX, const float offsetY, const std::vector<std::string>& menu_items)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnShowAutofillPopup(offsetX, offsetY, menu_items);
}

void WebDelegate::SuggestionSelected(int32_t index)
{
    CHECK_NULL_VOID(nweb_);
    nweb_->SuggestionSelected(index);
}

void WebDelegate::OnHideAutofillPopup()
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnHideAutofillPopup();
}

void WebDelegate::OnAreaChange(const OHOS::Ace::Rect& area)
{
    if (currentArea_ == area) {
        return;
    }
    currentArea_ = area;
    if (nweb_) {
        double offsetX = 0;
        double offsetY = 0;
        UpdateScreenOffSet(offsetX, offsetY);
        nweb_->SetScreenOffSet(offsetX, offsetY);
    }
    OnSafeInsetsChange();
}

void WebDelegate::OnViewportFitChange(OHOS::NWeb::ViewportFit viewportFit)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), viewportFit]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onViewportFitChangedV2 = delegate->onViewportFitChangedV2_;
            if (onViewportFitChangedV2) {
                onViewportFitChangedV2(std::make_shared<ViewportFitChangedEvent>(static_cast<int32_t>(viewportFit)));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebViewportFitChanged");
}

void WebDelegate::OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type)
{
    bool changed = false;
    auto safeArea = ConvertAvoidArea(avoidArea);

    if (type == Rosen::AvoidAreaType::TYPE_SYSTEM) {
        changed = (systemSafeArea_ != safeArea);
        systemSafeArea_ = safeArea;
    } else if (type == Rosen::AvoidAreaType::TYPE_CUTOUT) {
        changed = (cutoutSafeArea_ != safeArea);
        cutoutSafeArea_ = safeArea;
    } else if (type == Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR) {
        changed = (navigationIndicatorSafeArea_ != safeArea);
        navigationIndicatorSafeArea_ = safeArea;
    }

    if (changed) {
        OnSafeInsetsChange();
    }
}

void WebDelegate::OnInterceptKeyboardAttach(
    const std::shared_ptr<OHOS::NWeb::NWebCustomKeyboardHandler> keyboardHandler,
    const std::map<std::string, std::string> &attributes, bool &useSystemKeyboard, int32_t &enterKeyType)
{
    CHECK_NULL_VOID(onInterceptKeyboardAttachV2_);
    CHECK_NULL_VOID(taskExecutor_);
    keyboardHandler_ = keyboardHandler;
    WebKeyboardOption keyboardOpt;
    std::function<void()> buildFunc = nullptr;
    taskExecutor_->PostSyncTask(
        [weak = WeakClaim(this), &keyboardHandler, &attributes, &keyboardOpt]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onInterceptKeyboardAttachV2_ = delegate->onInterceptKeyboardAttachV2_;
            if (onInterceptKeyboardAttachV2_) {
                auto param = AceType::MakeRefPtr<WebCustomKeyboardHandlerOhos>(keyboardHandler);
                keyboardOpt = onInterceptKeyboardAttachV2_(std::make_shared<InterceptKeyboardEvent>(param, attributes));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIWebHandleInterceptKeyboardAttach");

    useSystemKeyboard = keyboardOpt.isSystemKeyboard_;
    enterKeyType = keyboardOpt.enterKeyTpye_;
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetCustomKeyboardBuilder(keyboardOpt.customKeyboardBuilder_);
    TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard OnInterceptKeyboardAttach sync task end");
}

void WebDelegate::OnCustomKeyboardAttach()
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->AttachCustomKeyboard();
}

void WebDelegate::OnCustomKeyboardClose()
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->CloseCustomKeyboard();
}

void WebDelegate::KeyboardReDispatch(const std::shared_ptr<OHOS::NWeb::NWebKeyEvent>& event, bool isUsed)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->KeyboardReDispatch(event, isUsed);
}

void WebDelegate::OnCursorUpdate(double x, double y, double width, double height)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnCursorUpdate(x, y, width, height);
}

void WebDelegate::OnSafeInsetsChange()
{
    NG::SafeAreaInsets resultSafeArea({0, 0}, {0, 0}, {0, 0}, {0, 0});
    resultSafeArea = resultSafeArea.Combine(systemSafeArea_);
    resultSafeArea = resultSafeArea.Combine(cutoutSafeArea_);
    resultSafeArea = resultSafeArea.Combine(navigationIndicatorSafeArea_);

    int left = 0;
    if (resultSafeArea.left_.IsValid() && resultSafeArea.left_.end > currentArea_.Left()) {
        left = static_cast<int>(resultSafeArea.left_.start + resultSafeArea.left_.end);
    }
    int top = 0;
    if (resultSafeArea.top_.IsValid() && resultSafeArea.top_.end > currentArea_.Top()) {
        top = static_cast<int>(resultSafeArea.top_.end - resultSafeArea.top_.start);
    }
    int right = 0;
    if (resultSafeArea.right_.IsValid() && resultSafeArea.right_.start < currentArea_.Right()) {
        constexpr static int32_t CUTOUT_EDGES_BALANCE_FACTOR = 2;
        right = static_cast<int>(resultSafeArea.right_.end - resultSafeArea.right_.start +
                (currentArea_.Right() - resultSafeArea.right_.end) * CUTOUT_EDGES_BALANCE_FACTOR);
    }
    int bottom = 0;
    if (resultSafeArea.bottom_.IsValid() && resultSafeArea.bottom_.start < currentArea_.Bottom()) {
        bottom = static_cast<int>(resultSafeArea.bottom_.end - resultSafeArea.bottom_.start);
    }

    if (left < 0 || bottom < 0 || right < 0 || top < 0) {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebDelegate::OnSafeInsetsChange occur errors "
                "ltrb:%{public}d,%{public}d,%{public}d,%{public}d", left, top, right, bottom);
        return;
    }

    TAG_LOGD(AceLogTag::ACE_WEB,
        "WebDelegate::OnSafeInsetsChange left:%{public}d top:%{public}d right:%{public}d bottom:%{public}d "
        "systemSafeArea:%{public}s cutoutSafeArea:%{public}s navigationIndicatorSafeArea:%{public}s "
        "resultSafeArea:%{public}s currentArea:%{public}s", left, top, right, bottom,
        systemSafeArea_.ToString().c_str(), cutoutSafeArea_.ToString().c_str(),
        navigationIndicatorSafeArea_.ToString().c_str(), resultSafeArea.ToString().c_str(),
        currentArea_.ToString().c_str());

    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), left, top, right, bottom]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_ && !delegate->window_) {
                delegate->nweb_->OnSafeInsetsChange(left, top, right, bottom);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebSafeInsetsChange");
}

void WebDelegate::CreateOverlay(void* data, size_t len, int width, int height, int offsetX, int offsetY, int rectWidth,
    int rectHeight, int pointX, int pointY)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->CreateOverlay(PixelMap::ConvertSkImageToPixmap(static_cast<const uint32_t*>(data), len, width, height),
        offsetX, offsetY, rectWidth, rectHeight, pointX, pointY);
}

void WebDelegate::OnOverlayStateChanged(int offsetX, int offsetY, int rectWidth, int rectHeight)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->OnOverlayStateChanged(offsetX, offsetY, rectWidth, rectHeight);
}

void WebDelegate::OnTextSelected()
{
    auto delegate = WeakClaim(this).Upgrade();
    CHECK_NULL_VOID(delegate);
    if (delegate->nweb_) {
        OnContextMenuHide("");
        return delegate->nweb_->OnTextSelected();
    }
}

void WebDelegate::OnDestroyImageAnalyzerOverlay()
{
    CHECK_NULL_VOID(nweb_);
    nweb_->OnDestroyImageAnalyzerOverlay();
}

std::string WebDelegate::GetWebInfoType()
{
    std::string factoryLevel = NWebAdapterHelper::Instance()
        .ParsePerfConfig("factoryConfig", "factoryLevel");
    if (factoryLevel.empty()) {
        NWebAdapterHelper::Instance().ReadConfigIfNeeded();
        factoryLevel = NWebAdapterHelper::Instance().
            ParsePerfConfig("factoryConfig", "factoryLevel");
    }
    TAG_LOGD(AceLogTag::ACE_WEB, "read config factoryLevel: %{public}s ", factoryLevel.c_str());
    return factoryLevel;
}

void WebDelegate::OnAdsBlocked(const std::string& url, const std::vector<std::string>& adsBlocked)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), url, adsBlocked]() {
            auto delegate = weak.Upgrade();
            CHECK_NULL_VOID(delegate);
            auto onAdsBlockedV2 = delegate->onAdsBlockedV2_;
            if (onAdsBlockedV2) {
                onAdsBlockedV2(std::make_shared<AdsBlockedEvent>(url, adsBlocked));
            }
        },
        TaskExecutor::TaskType::JS, "ArkUiWebAdsBlocked");
}

void WebDelegate::SetSurfaceId(const std::string& surfaceId)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), surfaceId]() {
            auto delegate = weak.Upgrade();
            if (delegate && delegate->nweb_) {
                std::shared_ptr<OHOS::NWeb::NWebPreference> setting = delegate->nweb_->GetPreference();
                CHECK_NULL_VOID(setting);
                setting->SetSurfaceId(surfaceId);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIWebSetSurfaceId");
}

std::string WebDelegate::SpanstringConvertHtml(const std::vector<uint8_t> &content)
{
    std::vector<uint8_t> tempVec(content.begin(), content.end());
    std::string htmlStr = OHOS::Ace::SpanToHtml::ToHtml(tempVec);
    TAG_LOGD(AceLogTag::ACE_WEB, "pasteboard spasntring convert html success,"
        " string length = %{public}u", static_cast<int32_t>(htmlStr.length()));
    return htmlStr;
}

void WebDelegate::StartVibraFeedback(const std::string& vibratorType)
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_VOID(webPattern);
    webPattern->StartVibraFeedback(vibratorType);
}

bool WebDelegate::CloseImageOverlaySelection()
{
    auto webPattern = webPattern_.Upgrade();
    CHECK_NULL_RETURN(webPattern, false);
    return webPattern->CloseImageOverlaySelection();
}

bool WebDelegate::GetAccessibilityVisible(int64_t accessibilityId)
{
    CHECK_NULL_RETURN(nweb_, true);
    return nweb_->GetAccessibilityVisible(accessibilityId);
}

void WebDelegate::SetTransformHint(uint32_t rotation)
{
    ACE_DCHECK(nweb_ != nullptr);
    if (nweb_) {
        nweb_->SetTransformHint(rotation);
    }
}
} // namespace OHOS::Ace
