/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/form/resource/form_manager_delegate.h"

#include <algorithm>
#include <iomanip>
#include <memory>
#include <sstream>

#include "form_info_base.h"
#include "transaction/rs_sync_transaction_controller.h"
#include "transaction/rs_transaction.h"

#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/components_ng/gestures/gesture_group.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/gestures/gesture_info.h"
#include "frameworks/base/json/json_util.h"
#include "render_service_client/core/ui/rs_ui_context.h"

#ifdef OHOS_STANDARD_SYSTEM
#include "form_mgr_errors.h"
#include "form_callback_client.h"
#include "form_host_client.h"
#include "form_info.h"
#include "form_js_info.h"
#include "form_mgr.h"
#include "pointer_event.h"

#include "core/common/form_manager.h"
#include "core/components/form/resource/form_utils.h"
#endif

namespace OHOS::Ace {
namespace {
constexpr char FORM_EVENT_ON_ACQUIRE_FORM[] = "onAcquireForm";
constexpr char FORM_EVENT_ON_UPDATE_FORM[] = "onUpdateForm";
constexpr char FORM_EVENT_ON_ERROR[] = "onFormError";
constexpr char FORM_ADAPTOR_RESOURCE_NAME[] = "formAdaptor";
constexpr char NTC_PARAM_RICH_TEXT[] = "formAdaptor";
constexpr char FORM_RENDERER_PROCESS_ON_ADD_SURFACE[] = "ohos.extra.param.key.process_on_add_surface";
constexpr char FORM_RENDERER_DISPATCHER[] = "ohos.extra.param.key.process_on_form_renderer_dispatcher";
constexpr char PARAM_FORM_MIGRATE_FORM_KEY[] = "ohos.extra.param.key.migrate_form";
constexpr int32_t RENDER_DEAD_CODE = 16501006;
constexpr int32_t FORM_NOT_TRUST_CODE = 16501007;
constexpr int32_t FORM_STATUS_TIME_OUT = 16501009;
constexpr char ALLOW_UPDATE[] = "allowUpdate";
constexpr char IS_DYNAMIC[] = "isDynamic";
constexpr uint32_t DELAY_TIME_FOR_FORM_SNAPSHOT_10S = 10000;
} // namespace

FormManagerDelegate::~FormManagerDelegate()
{
    ReleasePlatformResource();
}

void FormManagerDelegate::ReleasePlatformResource()
{
#ifdef OHOS_STANDARD_SYSTEM
    ReleaseForm();
#else
    Stop();
    Release();
#endif
}

void FormManagerDelegate::Stop()
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
        }, "ArkUIFormUnregisterEvent");
    }
}

void FormManagerDelegate::UnregisterEvent()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto resRegister = context->GetPlatformResRegister();
    resRegister->UnregisterEvent(MakeEventHash(FORM_EVENT_ON_ACQUIRE_FORM));
    resRegister->UnregisterEvent(MakeEventHash(FORM_EVENT_ON_UPDATE_FORM));
    resRegister->UnregisterEvent(MakeEventHash(FORM_EVENT_ON_ERROR));
}

#if OHOS_STANDARD_SYSTEM
void FormManagerDelegate::AddForm(const WeakPtr<PipelineBase>& context, const RequestFormInfo& info,
    const AppExecFwk::FormInfo& formInfo)
#else
void FormManagerDelegate::AddForm(const WeakPtr<PipelineBase>& context, const RequestFormInfo& info)
#endif
{
#ifdef OHOS_STANDARD_SYSTEM
    std::lock_guard<std::mutex> lock(recycleMutex_);
    // dynamic add new form should release the running form first.
    if (runningCardId_ > 0) {
        TAG_LOGI(AceLogTag::ACE_FORM, "Add new form, release platform resource about old form:%{public}s.",
            std::to_string(runningCardId_).c_str());
        ReleaseForm();
        ResetForm();
    }

    SetParamForWant(info, formInfo);
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    auto clientInstance = OHOS::AppExecFwk::FormHostClient::GetInstance();
    TAG_LOGI(AceLogTag::ACE_FORM, "Before FormMgr adding form, info.id: %{public}" PRId64, info.id);
    std::lock_guard<std::mutex> wantCacheLock(wantCacheMutex_);
    auto ret = OHOS::AppExecFwk::FormMgr::GetInstance().AddForm(info.id, wantCache_, clientInstance, formJsInfo);
    if (ret != 0) {
        auto errorMsg = OHOS::AppExecFwk::FormMgr::GetInstance().GetErrorMessage(ret);
        TAG_LOGW(AceLogTag::ACE_FORM, "Add form failed, ret:%{public}d detail:%{public}s", ret, errorMsg.c_str());
        OnFormError(std::to_string(ret), errorMsg);
        return;
    }

    TAG_LOGW(AceLogTag::ACE_FORM,
        "Add form success, formId: %{public}s, type: %{public}d, uiSyntax: %{public}d, isDynamic: %{public}d",
        std::to_string(formJsInfo.formId).c_str(), static_cast<int>(formJsInfo.type),
        static_cast<int>(formJsInfo.uiSyntax), isDynamic_);
    if (formCallbackClient_ == nullptr) {
        formCallbackClient_ = std::make_shared<FormCallbackClient>();
        formCallbackClient_->SetInstanceId(Container::CurrentId());
    }
    formCallbackClient_->SetFormManagerDelegate(AceType::WeakClaim(this));
    clientInstance->AddForm(formCallbackClient_, formJsInfo);

    runningCardId_ = formJsInfo.formId;
    runningCompId_ = std::to_string(info.index);
    ProcessFormUpdate(formJsInfo);
#else
    if (state_ == State::CREATED) {
        hash_ = MakeResourceHash();
        Method addFormMethod = MakeMethodHash("addForm");
        std::string param = ConvertRequestInfo(info);
        CallResRegisterMethod(addFormMethod, param, nullptr);
    } else {
        CreatePlatformResource(context, info);
    }
#endif
}

void FormManagerDelegate::SetRSUIContext(std::shared_ptr<Rosen::RSUIContext>& rsUIContext)
{
    if (rsUIContext == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "FormManagerDelegate: rsUIContext is nullptr");
        return;
    }
    rsUIContext_ = rsUIContext;
}

int32_t FormManagerDelegate::OnSurfaceCreate(const AppExecFwk::FormJsInfo& formInfo,
    const std::shared_ptr<Rosen::RSSurfaceNode>& rsSurfaceNode, const AAFwk::Want& want)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "Form OnSurfaceCreate formId: %{public}s, isDynamic: %{public}d",
        std::to_string(formInfo.formId).c_str(), formInfo.isDynamic);
    if (!rsSurfaceNode) {
        TAG_LOGE(AceLogTag::ACE_FORM, "rsSurfaceNode is null");
        return ERR_APPEXECFWK_FORM_INVALID_PARAM;
    }

    if (!onFormSurfaceNodeCallback_) {
        TAG_LOGE(AceLogTag::ACE_FORM, "onFormSurfaceNodeCallback is null");
        return ERR_APPEXECFWK_FORM_COMMON_CODE;
    }

    bool needHandleCachedClick =
        want.GetBoolParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM_TO_HANDLE_CLICK_EVENT, false);
    bool isRecover = recycleStatus_ != RecycleStatus::RECOVERED || needHandleCachedClick;
    AAFwk::Want newWant;
    newWant.SetParam(OHOS::AppExecFwk::Constants::FORM_IS_DYNAMIC, formInfo.isDynamic);
    newWant.SetParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM, isRecover);
    newWant.SetParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM_TO_HANDLE_CLICK_EVENT, needHandleCachedClick);

    std::lock_guard<std::mutex> lock(accessibilityChildTreeRegisterMutex_);
    onFormSurfaceNodeCallback_(rsSurfaceNode, newWant);

    sptr<IRemoteObject> proxy = want.GetRemoteObject(FORM_RENDERER_DISPATCHER);
    if (proxy != nullptr) {
        formRendererDispatcher_ = iface_cast<IFormRendererDispatcher>(proxy);
        CheckWhetherSurfaceChangeFailed();
    } else {
        TAG_LOGE(AceLogTag::ACE_FORM, "want renderer dispatcher null");
    }
    {
        std::lock_guard<std::mutex> lock(recycleMutex_);
        recycleStatus_ = RecycleStatus::RECOVERED;
    }
    isDynamic_ = formInfo.isDynamic;
    if (!formInfo.isDynamic) {
        HandleSnapshotCallback(DELAY_TIME_FOR_FORM_SNAPSHOT_10S);
    }
    if (formRendererDispatcher_) {
        formRendererDispatcher_->SetMultiInstanceEnabled(SystemProperties::GetMultiInstanceEnabled());
    }
    return ERR_OK;
}

void FormManagerDelegate::CheckWhetherSurfaceChangeFailed()
{
    OHOS::AppExecFwk::FormSurfaceInfo formSurfaceInfo;
    bool needRedispatch = false;
    {
        std::lock_guard<std::mutex> lock(surfaceChangeFailedRecordMutex_);
        if (notifySurfaceChangeFailedRecord_.isfailed == true) {
            TAG_LOGI(AceLogTag::ACE_FORM, "redispatch surface change event");
            needRedispatch = true;
            notifySurfaceChangeFailedRecord_.isfailed = false;
            formSurfaceInfo.width = notifySurfaceChangeFailedRecord_.expectedWidth;
            formSurfaceInfo.height = notifySurfaceChangeFailedRecord_.expectedHeight;
            formSurfaceInfo.borderWidth = notifySurfaceChangeFailedRecord_.expectedBorderWidth;
            formSurfaceInfo.layoutWidth = notifySurfaceChangeFailedRecord_.expectedLayoutWidth;
            formSurfaceInfo.layoutHeight = notifySurfaceChangeFailedRecord_.expectedLayoutHeight;
        }
    }
    if (needRedispatch) {
        uint32_t reason = static_cast<uint32_t>(WindowSizeChangeReason::UNDEFINED);
        formRendererDispatcher_->DispatchSurfaceChangeEvent(formSurfaceInfo, reason, nullptr);
    }
}

void FormManagerDelegate::HandleCachedClickEvents()
{
    if (formRendererDispatcher_ == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "dispatcher is null, formId:%{public}" PRId64, runningCardId_);
        return;
    }
    if (!isDynamic_) {
        TAG_LOGE(AceLogTag::ACE_FORM, "failed to handle cached click, not dynamic card");
        return;
    }
    {
        std::lock_guard<std::mutex> lock(recycleMutex_);
        TAG_LOGI(AceLogTag::ACE_FORM, "process click event after recover form, pointerEventCache_.size: %{public}s",
            std::to_string(pointerEventCache_.size()).c_str());
        for (const auto& pointerEvent : pointerEventCache_) {
            SerializedGesture serializedGesture;
            formRendererDispatcher_->DispatchPointerEvent(pointerEvent, serializedGesture);
        }
        pointerEventCache_.clear();
    }
}

std::string FormManagerDelegate::ConvertRequestInfo(const RequestFormInfo& info) const
{
    std::stringstream paramStream;
    paramStream << "bundle" << FORM_MANAGER_PARAM_EQUALS << info.bundleName << FORM_MANAGER_PARAM_AND << "ability"
                << FORM_MANAGER_PARAM_EQUALS << info.abilityName << FORM_MANAGER_PARAM_AND << "module"
                << FORM_MANAGER_PARAM_EQUALS << info.moduleName << FORM_MANAGER_PARAM_AND << "name"
                << FORM_MANAGER_PARAM_EQUALS << info.cardName << FORM_MANAGER_PARAM_AND << "dimension"
                << FORM_MANAGER_PARAM_EQUALS << info.dimension << FORM_MANAGER_PARAM_AND << "id"
                << FORM_MANAGER_PARAM_EQUALS << info.id << FORM_MANAGER_PARAM_AND << "temporary"
                << FORM_MANAGER_PARAM_EQUALS << info.temporary << FORM_MANAGER_PARAM_AND << "cardkey"
                << FORM_MANAGER_PARAM_EQUALS << info.ToString();
    return paramStream.str();
}

void FormManagerDelegate::CreatePlatformResource(const WeakPtr<PipelineBase>& context, const RequestFormInfo& info)
{
    context_ = context;
    state_ = State::CREATING;

    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        state_ = State::CREATEFAILED;
        TAG_LOGE(AceLogTag::ACE_FORM, "OnFormError CREATEFAILED");
        OnFormError("internal error");
        return;
    }
    auto platformTaskExecutor =
        SingleTaskExecutor::Make(pipelineContext->GetTaskExecutor(), TaskExecutor::TaskType::PLATFORM);
    auto resRegister = pipelineContext->GetPlatformResRegister();
    auto weakRes = AceType::WeakClaim(AceType::RawPtr(resRegister));
    platformTaskExecutor.PostTask([weak = WeakClaim(this), weakRes, info] {
        auto delegate = weak.Upgrade();
        if (!delegate) {
            return;
        }
        auto resRegister = weakRes.Upgrade();
        auto context = delegate->context_.Upgrade();
        if (!resRegister || !context) {
            TAG_LOGE(AceLogTag::ACE_FORM, "OnFormError resRegister or context error");
            delegate->OnFormError("internal error");
            return;
        }

        delegate->id_ = CREATING_ID;

        std::stringstream paramStream;
        paramStream << NTC_PARAM_RICH_TEXT << FORM_MANAGER_PARAM_EQUALS << delegate->id_ << FORM_MANAGER_PARAM_AND
                    << "bundle" << FORM_MANAGER_PARAM_EQUALS << info.bundleName << FORM_MANAGER_PARAM_AND << "ability"
                    << FORM_MANAGER_PARAM_EQUALS << info.abilityName << FORM_MANAGER_PARAM_AND << "module"
                    << FORM_MANAGER_PARAM_EQUALS << info.moduleName << FORM_MANAGER_PARAM_AND << "name"
                    << FORM_MANAGER_PARAM_EQUALS << info.cardName << FORM_MANAGER_PARAM_AND << "dimension"
                    << FORM_MANAGER_PARAM_EQUALS << info.dimension << FORM_MANAGER_PARAM_AND << "id"
                    << FORM_MANAGER_PARAM_EQUALS << info.id << FORM_MANAGER_PARAM_AND << "temporary"
                    << FORM_MANAGER_PARAM_EQUALS << info.temporary << FORM_MANAGER_PARAM_AND << "cardkey"
                    << FORM_MANAGER_PARAM_EQUALS << info.ToString();

        std::string param = paramStream.str();
        delegate->id_ = resRegister->CreateResource(FORM_ADAPTOR_RESOURCE_NAME, param);
        if (delegate->id_ == INVALID_ID) {
            TAG_LOGE(AceLogTag::ACE_FORM, "OnFormError INVALID_ID");
            delegate->OnFormError("internal error");
            return;
        }
        delegate->state_ = State::CREATED;
        delegate->hash_ = delegate->MakeResourceHash();
        delegate->RegisterEvent();
    }, "ArkUIFormCreatePlatformResource");
}

void FormManagerDelegate::RegisterEvent()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto resRegister = context->GetPlatformResRegister();
    resRegister->RegisterEvent(
        MakeEventHash(FORM_EVENT_ON_ACQUIRE_FORM), [weak = WeakClaim(this)](const std::string& param) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->OnFormAcquired(param);
            }
        });
    resRegister->RegisterEvent(
        MakeEventHash(FORM_EVENT_ON_UPDATE_FORM), [weak = WeakClaim(this)](const std::string& param) {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->OnFormUpdate(param);
            }
        });
    resRegister->RegisterEvent(MakeEventHash(FORM_EVENT_ON_ERROR), [weak = WeakClaim(this)](const std::string& param) {
        auto delegate = weak.Upgrade();
        if (delegate) {
            delegate->OnFormError(param);
        }
    });
}

void FormManagerDelegate::AddFormAcquireCallback(const OnFormAcquiredCallback& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }
    onFormAcquiredCallback_ = callback;
}

void FormManagerDelegate::AddFormUpdateCallback(const OnFormUpdateCallback& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }
    onFormUpdateCallback_ = callback;
}

void FormManagerDelegate::AddFormErrorCallback(const OnFormErrorCallback& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }
    onFormErrorCallback_ = callback;
}

void FormManagerDelegate::AddFormUninstallCallback(const OnFormUninstallCallback& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }
    onFormUninstallCallback_ = callback;
}

void FormManagerDelegate::AddFormSurfaceNodeCallback(const OnFormSurfaceNodeCallback& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }
    onFormSurfaceNodeCallback_ = callback;
}

void FormManagerDelegate::AddFormSurfaceChangeCallback(OnFormSurfaceChangeCallback&& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }
    onFormSurfaceChangeCallback_ = std::move(callback);
}

void FormManagerDelegate::AddFormSurfaceDetachCallback(OnFormSurfaceDetachCallback&& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }
    onFormSurfaceDetachCallback_ = std::move(callback);
}

void FormManagerDelegate::AddFormLinkInfoUpdateCallback(OnFormLinkInfoUpdateCallback&& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }
    onFormLinkInfoUpdateCallback_ = std::move(callback);
}

void FormManagerDelegate::AddGetRectRelativeToWindowCallback(OnGetRectRelativeToWindowCallback&& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }
    onGetRectRelativeToWindowCallback_ = std::move(callback);
}

void FormManagerDelegate::AddActionEventHandle(const ActionEventHandle& callback)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "EventHandle - AddActionEventHandle");
    if (!callback || state_ == State::RELEASED) {
        TAG_LOGI(AceLogTag::ACE_FORM, "EventHandle - state_ is RELEASED");
        return;
    }
    actionEventHandle_ = callback;
}

void FormManagerDelegate::AddEnableFormCallback(EnableFormCallback&& callback)
{
    if (!callback || state_ == State::RELEASED) {
        TAG_LOGE(AceLogTag::ACE_FORM, "EnableFormCallback is null");
        return;
    }
    enableFormCallback_ = std::move(callback);
}


void FormManagerDelegate::AddLockFormCallback(LockFormCallback&& callback)
{
    if (!callback || state_ == State::RELEASED) {
        TAG_LOGE(AceLogTag::ACE_FORM, "EnableFormCallback is null");
        return;
    }
    lockFormCallback_ = std::move(callback);
}

void FormManagerDelegate::AddFormUpdateDoneCallback(UpdateFormDoneCallback&& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }
    updateFormDoneCallback_ = std::move(callback);
}

void FormManagerDelegate::OnActionEventHandle(const std::string& action)
{
    if (actionEventHandle_) {
        TAG_LOGI(AceLogTag::ACE_FORM, "EventHandle - OnActionEventHandle ,formId: %{public}" PRId64,
            runningCardId_);
        actionEventHandle_(action);
    }
}

void FormManagerDelegate::AddUnTrustFormCallback(const UnTrustFormCallback& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }
    unTrustFormCallback_ = callback;
}

void FormManagerDelegate::AddSnapshotCallback(SnapshotCallback&& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }

    snapshotCallback_ = std::move(callback);
}

bool FormManagerDelegate::ParseAction(const std::string& action, const std::string& type, AAFwk::Want& want)
{
    auto eventAction = JsonUtil::ParseJsonString(action);
    auto bundleName = eventAction->GetValue("bundleName");
    auto abilityName = eventAction->GetValue("abilityName");
    auto params = eventAction->GetValue("params");
    auto bundle = bundleName->GetString();
    auto ability = abilityName->GetString();
    if (type == "message") {
        params->Put("params", params);
        params->Put("action", type.c_str());
        want.SetParam(OHOS::AppExecFwk::Constants::PARAM_MESSAGE_KEY, params->ToString());
        return true;
    }

    if (bundle.empty()) {
        bundle = wantCache_.GetElement().GetBundleName();
    }
    if (ability.empty()) {
        if (type != "router") {
            return false;
        }
        auto uri = eventAction->GetValue("uri");
        if (!uri->IsValid()) {
            return false;
        }
    }

    want.SetElementName(bundle, ability);
    if (params->IsValid()) {
        auto child = params->GetChild();
        while (child->IsValid()) {
            auto key = child->GetKey();
            if (child->IsNull()) {
                want.SetParam(key, std::string());
            } else if (child->IsString()) {
                want.SetParam(key, child->GetString());
            } else if (child->IsNumber()) {
                want.SetParam(key, child->GetInt());
            } else {
                want.SetParam(key, std::string());
            }
            child = child->GetNext();
        }
    }
    want.SetParam("params", params->ToString());
    return true;
}

void FormManagerDelegate::AddRenderDelegate()
{
    if (renderDelegate_) {
        return;
    }
    renderDelegate_ = new FormRendererDelegateImpl();
}

void FormManagerDelegate::RegisterRenderDelegateEvent()
{
    CHECK_NULL_VOID(renderDelegate_);
    auto &&surfaceCreateEventHandler = [weak = WeakClaim(this)](
                                           const std::shared_ptr<Rosen::RSSurfaceNode> &surfaceNode,
                                           const OHOS::AppExecFwk::FormJsInfo &formInfo,
                                           const AAFwk::Want &want) -> int32_t {
        auto formManagerDelegate = weak.Upgrade();
        if (!formManagerDelegate) {
            TAG_LOGE(AceLogTag::ACE_FORM,
                "SurfaceCreateEventHandle - formManagerDelegate is null, formId:%{public}" PRId64, formInfo.formId);
            return ERR_APPEXECFWK_FORM_FORM_NODE_RELEASED;
        }
        return formManagerDelegate->OnSurfaceCreate(formInfo, surfaceNode, want);
    };
    renderDelegate_->SetSurfaceCreateEventHandler(std::move(surfaceCreateEventHandler));

    auto&& actionEventHandler = [weak = WeakClaim(this)](const std::string& action) {
        auto formManagerDelegate = weak.Upgrade();
        TAG_LOGI(AceLogTag::ACE_FORM, "ActionEventHandle - AddActionEventHandle");
        if (!formManagerDelegate) {
            TAG_LOGE(AceLogTag::ACE_FORM, "ActionEventHandle - formManagerDelegate is null");
            return;
        }
        formManagerDelegate->OnActionEventHandle(action);
    };
    renderDelegate_->SetActionEventHandler(std::move(actionEventHandler));

    auto&& onErrorEventHandler = [weak = WeakClaim(this)](const std::string& code, const std::string& msg) -> int32_t {
        auto formManagerDelegate = weak.Upgrade();
        if (!formManagerDelegate) {
            TAG_LOGE(AceLogTag::ACE_FORM, "ErrorEventHandle - formManagerDelegate is null");
            return ERR_APPEXECFWK_FORM_FORM_NODE_RELEASED;
        }
        formManagerDelegate->OnFormError(code, msg);
        return ERR_OK;
    };
    renderDelegate_->SetErrorEventHandler(std::move(onErrorEventHandler));

    auto&& onSurfaceChangeHandler = [weak = WeakClaim(this)](float width, float height, float borderWidth) {
        auto formManagerDelegate = weak.Upgrade();
        CHECK_NULL_VOID(formManagerDelegate);
        formManagerDelegate->OnFormSurfaceChange(width, height, borderWidth);
    };
    renderDelegate_->SetSurfaceChangeEventHandler(std::move(onSurfaceChangeHandler));

    auto&& onSurfaceDetachHandler = [weak = WeakClaim(this)]() {
        auto formManagerDelegate = weak.Upgrade();
        CHECK_NULL_VOID(formManagerDelegate);
        formManagerDelegate->OnFormSurfaceDetach();
    };
    renderDelegate_->SetSurfaceDetachEventHandler(std::move(onSurfaceDetachHandler));

    auto&& onFormLinkInfoUpdateHandler = [weak = WeakClaim(this)](const std::vector<std::string>& formLinkInfos) {
        auto formManagerDelegate = weak.Upgrade();
        CHECK_NULL_VOID(formManagerDelegate);
        formManagerDelegate->OnFormLinkInfoUpdate(formLinkInfos);
    };
    renderDelegate_->SetFormLinkInfoUpdateHandler(std::move(onFormLinkInfoUpdateHandler));

    auto &&onGetRectRelativeToWindowHandler = [weak = WeakClaim(this)](AccessibilityParentRectInfo& parentRectInfo) {
        auto formManagerDelegate = weak.Upgrade();
        CHECK_NULL_VOID(formManagerDelegate);
        formManagerDelegate->OnGetRectRelativeToWindow(parentRectInfo);
    };
    renderDelegate_->SetGetRectRelativeToWindowHandler(onGetRectRelativeToWindowHandler);

    auto &&onCheckManagerDelegate = [weak = WeakClaim(this)](bool &checkFlag) {
        auto formManagerDelegate = weak.Upgrade();
        if (!formManagerDelegate) {
            TAG_LOGE(AceLogTag::ACE_FORM, "CheckManagerDelegateEventHandle - formManagerDelegate is null");
            checkFlag = false;
        }
    };
    renderDelegate_->SetCheckManagerDelegate(onCheckManagerDelegate);

    auto &&onUpdateFormDoneEventHandler = [weak = WeakClaim(this)](const int64_t formId) {
        auto formManagerDelegate = weak.Upgrade();
        CHECK_NULL_VOID(formManagerDelegate);
        TAG_LOGD(AceLogTag::ACE_FORM, "UpdateFormEventHandle - formId:%{public}" PRId64, formId);
        formManagerDelegate->OnFormUpdateDone(formId);
    };
    renderDelegate_->SetUpdateFormEventHandler(onUpdateFormDoneEventHandler);
}

void FormManagerDelegate::OnActionEvent(const std::string& action)
{
    auto eventAction = JsonUtil::ParseJsonString(action);
    if (!eventAction->IsValid()) {
        return;
    }
    
    auto actionType = eventAction->GetValue("action");
    if (!actionType->IsValid()) {
        return;
    }

    auto type = actionType->GetString();
    if (type != "router" && type != "message" && type != "call") {
        return;
    }

#ifdef OHOS_STANDARD_SYSTEM
    if (type == "router") {
        OnRouterActionEvent(action);
        return;
    } else if (type == "call") {
        OnCallActionEvent(action);
        return;
    }

    AAFwk::Want want;
    if (!ParseAction(action, type, want)) {
        TAG_LOGE(AceLogTag::ACE_FORM, "action parse failed, detail action:%{public}s", action.c_str());
        return;
    }
    want.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_IDENTITY_KEY, (int64_t)runningCardId_);
    if (AppExecFwk::FormMgr::GetRecoverStatus() == OHOS::AppExecFwk::Constants::IN_RECOVERING) {
        return;
    }

    // requestForm request to fms
    AppExecFwk::FormMgr::GetInstance().MessageEvent(runningCardId_, want, AppExecFwk::FormHostClient::GetInstance());
#else
    hash_ = MakeResourceHash();
    Method actionMethod = MakeMethodHash("onAction");
    std::stringstream paramStream;
    paramStream << "type" << FORM_MANAGER_PARAM_EQUALS << type << FORM_MANAGER_PARAM_AND << "action"
                << FORM_MANAGER_PARAM_EQUALS << action;
    std::string param = paramStream.str();
    TAG_LOGI(AceLogTag::ACE_FORM, "send method:%{private}s, type:%{public}s params:%{private}s", actionMethod.c_str(),
        type.c_str(), param.c_str());
    CallResRegisterMethod(actionMethod, param, nullptr);
#endif
}

void FormManagerDelegate::DispatchPointerEvent(const
    std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    SerializedGesture& serializedGesture)
{
    if (!isDynamic_ || !pointerEvent) {
        return;
    }

    // if formRendererDispatcher_ is null, check if form is recycled.
    if (formRendererDispatcher_ == nullptr) {
        std::lock_guard<std::mutex> lock(recycleMutex_);
        if (recycleStatus_ == RecycleStatus::RECYCLED) {
            SetGestureInnerFlag();
            TAG_LOGI(AceLogTag::ACE_FORM,
                "form is recycled, recover it first, action=%{public}d, formId=%{public}" PRId64 "",
                pointerEvent->GetPointerAction(), runningCardId_);
            recycleStatus_ = RecycleStatus::RECOVERING;
            pointerEventCache_.emplace_back(pointerEvent);

            std::vector<int64_t> formIds = {runningCardId_};
            AAFwk::Want want;
            want.SetParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM_TO_HANDLE_CLICK_EVENT, true);
            OHOS::AppExecFwk::FormMgr::GetInstance().RecoverForms(formIds, want);
        } else if (recycleStatus_ == RecycleStatus::RECOVERING) {
            TAG_LOGI(AceLogTag::ACE_FORM, "form is recovering, cache pointer event, action=%{public}d",
                pointerEvent->GetPointerAction());
            pointerEventCache_.emplace_back(pointerEvent);
        } else {
            TAG_LOGE(AceLogTag::ACE_FORM, "formRendererDispatcher_ is null");
        }
        return;
    }

    if (pointerEvent->GetPointerAction() == OHOS::MMI::PointerEvent::POINTER_ACTION_DOWN) {
        TAG_LOGI(AceLogTag::ACE_FORM, "dispatch down event to renderer");
    }
    
    bool disablePanGesture;
    {
        std::lock_guard<std::mutex> wantCacheLock(wantCacheMutex_);
        disablePanGesture = wantCache_.GetBoolParam(OHOS::AppExecFwk::Constants::FORM_DISABLE_GESTURE_KEY, false);
    }
    if (!disablePanGesture) {
        formRendererDispatcher_->DispatchPointerEvent(pointerEvent, serializedGesture);
        return;
    }

    // pan gesture disabled, not dispatch move event, not concat serialized gesture
    auto pointAction = pointerEvent->GetPointerAction();
    if (pointAction == OHOS::MMI::PointerEvent::POINTER_ACTION_MOVE ||
        pointAction == OHOS::MMI::PointerEvent::POINTER_ACTION_AXIS_UPDATE) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_FORM, "form pan gesture disabled, dispatch event action=%{public}d",
        pointerEvent->GetPointerAction());
    SerializedGesture ignoredGesture;
    formRendererDispatcher_->DispatchPointerEvent(pointerEvent, ignoredGesture);
    SetGestureInnerFlag();
}

void FormManagerDelegate::SetGestureInnerFlag()
{
    auto pipelineContext = context_.Upgrade();
    if (pipelineContext && pipelineContext->GetEventManager()) {
        // avoid context dispatch mocked cancel event
        pipelineContext->GetEventManager()->SetInnerFlag(true);
        TAG_LOGI(AceLogTag::ACE_FORM, "set event manager inner flag");
    }
}

void FormManagerDelegate::SetAllowUpdate(bool allowUpdate)
{
    if (formRendererDispatcher_ == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "formRendererDispatcher_ is null");
        return;
    }

    formRendererDispatcher_->SetAllowUpdate(allowUpdate);
}

void FormManagerDelegate::NotifySurfaceChange(const OHOS::AppExecFwk::FormSurfaceInfo &formSurfaceInfo)
{
    OHOS::AppExecFwk::FormMgr::GetInstance().UpdateFormSize(runningCardId_, formSurfaceInfo.width,
        formSurfaceInfo.height, formSurfaceInfo.borderWidth);
    UpdateFormSizeWantCache(formSurfaceInfo.width, formSurfaceInfo.height, formSurfaceInfo.layoutWidth,
        formSurfaceInfo.layoutHeight, formSurfaceInfo.borderWidth);
    {
        std::lock_guard<std::mutex> lock(surfaceChangeFailedRecordMutex_);
        if (formRendererDispatcher_ == nullptr) {
            TAG_LOGW(AceLogTag::ACE_FORM, "formRendererDispatcher_ is nullptr");
            notifySurfaceChangeFailedRecord_.isfailed = true;
            notifySurfaceChangeFailedRecord_.expectedWidth = formSurfaceInfo.width;
            notifySurfaceChangeFailedRecord_.expectedHeight = formSurfaceInfo.height;
            notifySurfaceChangeFailedRecord_.expectedBorderWidth = formSurfaceInfo.borderWidth;
            notifySurfaceChangeFailedRecord_.expectedLayoutWidth = formSurfaceInfo.layoutWidth;
            notifySurfaceChangeFailedRecord_.expectedLayoutHeight = formSurfaceInfo.layoutHeight;
            return;
        }
    }
    WindowSizeChangeReason sizeChangeReason = WindowSizeChangeReason::UNDEFINED;
    if (FormManager::GetInstance().IsSizeChangeByRotate()) {
        sizeChangeReason = WindowSizeChangeReason::ROTATION;
    }
    bool isMultiInstanceEnabled = SystemProperties::GetMultiInstanceEnabled();
    std::shared_ptr<Rosen::RSTransaction> transaction = nullptr;
    std::shared_ptr<Rosen::RSSyncTransactionHandler> transactionControllerHandler = nullptr;
    Rosen::RSSyncTransactionController* transactionController = nullptr;
    if (isMultiInstanceEnabled) {
        if (rsUIContext_ == nullptr) {
            TAG_LOGE(AceLogTag::ACE_FORM, "NotifySurfaceChange: rsUIContext_ is nullptr");
            return;
        }
        transactionControllerHandler = rsUIContext_->GetSyncTransactionHandler();
    } else {
        transactionController = Rosen::RSSyncTransactionController::GetInstance();
    }

    if (FormManager::GetInstance().GetRSTransaction().lock()) {
        transaction = FormManager::GetInstance().GetRSTransaction().lock();
    } else if (transactionController != nullptr) {
        transaction = transactionController->GetRSTransaction();
    } else if (transactionControllerHandler != nullptr) {
        transaction = transactionControllerHandler->GetRSTransaction();
    }
    formRendererDispatcher_->DispatchSurfaceChangeEvent(formSurfaceInfo, static_cast<uint32_t>(sizeChangeReason),
        transaction);
}

void FormManagerDelegate::UpdateFormSizeWantCache(float width, float height, float layoutWidth, float layoutHeight,
    float borderWidth)
{
    std::lock_guard<std::mutex> lock(wantCacheMutex_);
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_WIDTH_KEY, static_cast<double>(width));
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_HEIGHT_KEY, static_cast<double>(height));
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_LAYOUT_WIDTH_KEY, static_cast<double>(layoutWidth));
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_LAYOUT_HEIGHT_KEY, static_cast<double>(layoutHeight));
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_BORDER_WIDTH_KEY, borderWidth);
}

void FormManagerDelegate::OnFormSurfaceChange(float width, float height, float borderWidth)
{
    if (onFormSurfaceChangeCallback_) {
        onFormSurfaceChangeCallback_(width, height, borderWidth);
    }
}

void FormManagerDelegate::OnFormSurfaceDetach()
{
    if (onFormSurfaceDetachCallback_) {
        onFormSurfaceDetachCallback_();
    }
}

void FormManagerDelegate::OnFormLinkInfoUpdate(const std::vector<std::string>& formLinkInfos)
{
    if (onFormLinkInfoUpdateCallback_) {
        onFormLinkInfoUpdateCallback_(formLinkInfos);
    }
}

void FormManagerDelegate::OnGetRectRelativeToWindow(AccessibilityParentRectInfo& parentRectInfo)
{
    if (onGetRectRelativeToWindowCallback_) {
        onGetRectRelativeToWindowCallback_(parentRectInfo);
    }
}

void FormManagerDelegate::OnFormAcquired(const std::string& param)
{
    auto result = ParseMapFromString(param);
    if (onFormAcquiredCallbackForJava_) {
        onFormAcquiredCallbackForJava_(
            StringUtils::StringToLongInt(result["formId"]), result["codePath"], result["moduleName"], result["data"]);
    }
}

void FormManagerDelegate::OnFormUpdate(const std::string& param)
{
    auto result = ParseMapFromString(param);
    if (onFormUpdateCallbackForJava_) {
        onFormUpdateCallbackForJava_(StringUtils::StringToLongInt(result["formId"]), result["data"]);
    }
}

void FormManagerDelegate::OnFormError(const std::string& param)
{
    auto result = ParseMapFromString(param);
    TAG_LOGW(AceLogTag::ACE_FORM,
        "OnFormError, code:%{public}s, msg:%{public}s", result["code"].c_str(), result["msg"].c_str());
    if (onFormErrorCallback_) {
        onFormErrorCallback_(result["code"], result["msg"]);
    }
}

void FormManagerDelegate::OnFormError(const std::string& code, const std::string& msg)
{
    int32_t externalErrorCode = 0;
    std::string errorMsg;
    int64_t parsedRequestCode = static_cast<int64_t>(StringUtils::StringToLongInt(code.c_str()));
    OHOS::AppExecFwk::FormMgr::GetInstance().GetExternalError(parsedRequestCode, externalErrorCode, errorMsg);
    TAG_LOGW(AceLogTag::ACE_FORM,
        "OnFormError, code:%{public}s, msg:%{public}s, externalErrorCode:%{public}d, errorMsg: %{public}s",
        code.c_str(), msg.c_str(), externalErrorCode, errorMsg.c_str());
    switch (externalErrorCode) {
        case RENDER_DEAD_CODE:
            ReAddForm();
            break;
        case FORM_STATUS_TIME_OUT:
            ReAddForm();
            break;
        case FORM_NOT_TRUST_CODE:
            HandleUnTrustFormCallback();
            break;
        default:
            if (onFormErrorCallback_) {
                onFormErrorCallback_(std::to_string(externalErrorCode), errorMsg);
            }
            break;
    }
}

void FormManagerDelegate::OnFormUpdateDone(const int64_t formId)
{
    if (updateFormDoneCallback_) {
        updateFormDoneCallback_(formId);
    }
}

void FormManagerDelegate::HandleUnTrustFormCallback()
{
    TAG_LOGI(AceLogTag::ACE_FORM, "HandleUnTrustFormCallback.");
    if (unTrustFormCallback_) {
        unTrustFormCallback_();
    }
}

void FormManagerDelegate::HandleSnapshotCallback(const uint32_t& delayTime)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "HandleSnapshotCallback.");
    if (snapshotCallback_) {
        snapshotCallback_(delayTime);
    }
}

void FormManagerDelegate::HandleEnableFormCallback(const bool enable)
{
    if (!enableFormCallback_) {
        TAG_LOGE(AceLogTag::ACE_FORM, "enableFormCallback_. is null");
        return;
    }
    enableFormCallback_(enable);
}

void FormManagerDelegate::HandleLockFormCallback(bool lock)
{
    if (!lockFormCallback_) {
        TAG_LOGE(AceLogTag::ACE_FORM, "lockFormCallback_. is null");
        return;
    }
    lockFormCallback_(lock);
}

void FormManagerDelegate::ReAddForm()
{
    std::lock_guard<std::mutex> lock(wantCacheMutex_);
    formRendererDispatcher_ = nullptr; // formRendererDispatcher_ need reset, otherwise PointerEvent will disable
    if (wantCache_.HasParameter(PARAM_FORM_MIGRATE_FORM_KEY)) {
        TAG_LOGW(AceLogTag::ACE_FORM, "Remove migrate form key.");
        wantCache_.RemoveParam(PARAM_FORM_MIGRATE_FORM_KEY);
    }
    auto clientInstance = OHOS::AppExecFwk::FormHostClient::GetInstance();
    wantCache_.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate_->AsObject());
    auto ret =
        OHOS::AppExecFwk::FormMgr::GetInstance().AddForm(formJsInfo_.formId, wantCache_, clientInstance, formJsInfo_);
    if (ret != 0) {
        auto errorMsg = OHOS::AppExecFwk::FormMgr::GetInstance().GetErrorMessage(ret);
        TAG_LOGW(AceLogTag::ACE_FORM, "Re-add form failed, ret:%{public}d detail:%{public}s", ret, errorMsg.c_str());
        OnFormError(std::to_string(ret), errorMsg);
        return;
    }
}

void FormManagerDelegate::SetObscured(bool isObscured)
{
    CHECK_NULL_VOID(formRendererDispatcher_);
    formRendererDispatcher_->SetObscured(isObscured);
}

void FormManagerDelegate::OnAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId, int64_t accessibilityId)
{
    std::lock_guard<std::mutex> lock(accessibilityChildTreeRegisterMutex_);
    CHECK_NULL_VOID(formRendererDispatcher_);
    formRendererDispatcher_->OnAccessibilityChildTreeRegister(windowId, treeId, accessibilityId);
}

void FormManagerDelegate::OnAccessibilityChildTreeDeregister()
{
    CHECK_NULL_VOID(formRendererDispatcher_);
    formRendererDispatcher_->OnAccessibilityChildTreeDeregister();
}

void FormManagerDelegate::OnAccessibilityDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info)
{
    CHECK_NULL_VOID(formRendererDispatcher_);
    formRendererDispatcher_->OnAccessibilityDumpChildInfo(params, info);
}

void FormManagerDelegate::OnAccessibilityTransferHoverEvent(float pointX, float pointY, int32_t sourceType,
    int32_t eventType, int64_t timeMs)
{
    CHECK_NULL_VOID(formRendererDispatcher_);
    formRendererDispatcher_->OnAccessibilityTransferHoverEvent(pointX, pointY, sourceType, eventType, timeMs);
}

bool FormManagerDelegate::CheckFormBundleForbidden(const std::string& bundleName)
{
    return OHOS::AppExecFwk::FormMgr::GetInstance().IsFormBundleForbidden(bundleName);
}

bool FormManagerDelegate::IsFormBundleExempt(int64_t formId)
{
    return OHOS::AppExecFwk::FormMgr::GetInstance().IsFormBundleExempt(formId);
}

bool FormManagerDelegate::IsFormBundleProtected(const std::string& bundleName, int64_t formId)
{
    return OHOS::AppExecFwk::FormMgr::GetInstance().IsFormBundleProtected(bundleName, formId);
}

void FormManagerDelegate::NotifyFormDump(const std::vector<std::string>& params,
    std::vector<std::string>& info)
{
    CHECK_NULL_VOID(formRendererDispatcher_);
    formRendererDispatcher_->OnNotifyDumpInfo(params, info);
}

#ifdef OHOS_STANDARD_SYSTEM
void FormManagerDelegate::ResetForm()
{
    TAG_LOGI(AceLogTag::ACE_FORM, "Reset form id is %{public}" PRId64 "", runningCardId_);
    runningCardId_ = -1;
    runningCompId_.clear();
    formRendererDispatcher_ = nullptr;
}

void FormManagerDelegate::ReleaseForm()
{
    TAG_LOGI(AceLogTag::ACE_FORM, "FormManagerDelegate releaseForm. formId: %{public}" PRId64 ", %{public}s",
        runningCardId_, runningCompId_.c_str());
    if (runningCardId_ <= 0) {
        return;
    }

    if (!runningCompId_.empty()) {
        OHOS::AppExecFwk::FormMgr::GetInstance().StopRenderingForm(runningCardId_, runningCompId_);
    }

    auto clientInstance = OHOS::AppExecFwk::FormHostClient::GetInstance();
    clientInstance->RemoveForm(formCallbackClient_, runningCardId_);
}

void FormManagerDelegate::ProcessFormUpdate(const AppExecFwk::FormJsInfo& formJsInfo)
{
    if (formJsInfo.formId != runningCardId_) {
        return;
    }
    if (!hasCreated_) {
        if (formJsInfo.jsFormCodePath.empty() || formJsInfo.formName.empty()) {
            return;
        }
        if (!onFormAcquiredCallback_) {
            return;
        }
        hasCreated_ = true;
        OHOS::Ace::FrontendType type = OHOS::Ace::FrontendType::JS_CARD;
        if (formJsInfo.type == AppExecFwk::FormType::ETS) {
            type = OHOS::Ace::FrontendType::ETS_CARD;
        }
        OHOS::Ace::FrontendType uiSyntax = OHOS::Ace::FrontendType::JS_CARD;
        if (formJsInfo.uiSyntax == AppExecFwk::FormType::ETS) {
            uiSyntax = OHOS::Ace::FrontendType::ETS_CARD;
        }
        formJsInfo_ = formJsInfo;
        onFormAcquiredCallback_(runningCardId_, formJsInfo.jsFormCodePath, formJsInfo.formName, formJsInfo.formData,
            formJsInfo.imageDataMap, formJsInfo, type, uiSyntax);
    } else {
        if (formJsInfo.formData.empty()) {
            return;
        }
        if (!onFormUpdateCallback_) {
            return;
        }
        formJsInfo_ = formJsInfo;
        onFormUpdateCallback_(formJsInfo.formId, formJsInfo.formData, formJsInfo.imageDataMap);
    }
}

void FormManagerDelegate::ReleaseRenderer()
{
    TAG_LOGI(AceLogTag::ACE_FORM, "FormManagerDelegate releaseRenderer. formId: %{public}" PRId64 ", %{public}s",
        runningCardId_, runningCompId_.c_str());
    if (runningCardId_ <= 0) {
        return;
    }

    OHOS::AppExecFwk::FormMgr::GetInstance().ReleaseRenderer(runningCardId_, runningCompId_);
    formRendererDispatcher_ = nullptr;
}

void FormManagerDelegate::ProcessFormUninstall(const int64_t formId)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "ProcessFormUninstall formId:%{public}s", std::to_string(formId).c_str());
    if (onFormUninstallCallback_) {
        onFormUninstallCallback_(formId);
    }
}

void FormManagerDelegate::OnDeathReceived()
{
    AppExecFwk::FormJsInfo formJsInfo;
    std::lock_guard<std::mutex> lock(wantCacheMutex_);
    OHOS::AppExecFwk::FormMgr::GetInstance().AddForm(
        runningCardId_, wantCache_, OHOS::AppExecFwk::FormHostClient::GetInstance(), formJsInfo);
}

void FormManagerDelegate::SetFormUtils(const std::shared_ptr<FormUtils>& formUtils)
{
    if (formUtils) {
        formUtils_ = formUtils;
    }
}

bool FormManagerDelegate::GetFormInfo(const std::string& bundleName, const std::string& moduleName,
    const std::string& cardName, AppExecFwk::FormInfo& formInfo)
{
    std::string bundle(bundleName);
    std::string module(moduleName);
    std::vector<OHOS::AppExecFwk::FormInfo> formInfos;
    auto result = OHOS::AppExecFwk::FormMgr::GetInstance().GetFormsInfoByModule(bundle, module, formInfos);
    if (result != 0) {
        LOGW("Query FormInfo failed.");
        return false;
    }

    auto iter = formInfos.begin();
    while (iter != formInfos.end()) {
        if (cardName == iter->name) {
            formInfo = *iter;
            return true;
        }
        iter++;
    }
    return false;
}

void FormManagerDelegate::ProcessRecycleForm()
{
    TAG_LOGI(AceLogTag::ACE_FORM, "ProcessRecycleForm, formId is %{public}s",
        std::to_string(runningCardId_).c_str());
    {
        std::lock_guard<std::mutex> lock(recycleMutex_);
        recycleStatus_ = RecycleStatus::RECYCLED;
    }
    HandleSnapshotCallback(0);
}

void FormManagerDelegate::ProcessEnableForm(bool enable)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "ProcessEnableForm, formId is %{public}s",
        std::to_string(runningCardId_).c_str());
    HandleEnableFormCallback(enable);
}

void FormManagerDelegate::SetParamForWant(const RequestFormInfo& info)
{
    std::lock_guard<std::mutex> lock(wantCacheMutex_);
    wantCache_.SetElementName(info.bundleName, info.abilityName);

    if (info.wantWrap) {
        info.wantWrap->SetWantParamsFromWantWrap(reinterpret_cast<void*>(&wantCache_));
    }

    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_IDENTITY_KEY, info.id);
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_MODULE_NAME_KEY, info.moduleName);
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_NAME_KEY, info.cardName);
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_TEMPORARY_KEY, info.temporary);
    wantCache_.SetParam(
        OHOS::AppExecFwk::Constants::ACQUIRE_TYPE, OHOS::AppExecFwk::Constants::ACQUIRE_TYPE_CREATE_FORM);
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_WIDTH_KEY, info.width.Value());
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_HEIGHT_KEY, info.height.Value());
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_LAYOUT_WIDTH_KEY, static_cast<double>(info.layoutWidth));
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_LAYOUT_HEIGHT_KEY, static_cast<double>(info.layoutHeight));
    if (runningCompId_.empty()) {
        wantCache_.SetParam(OHOS::AppExecFwk::Constants::FORM_COMP_ID, std::to_string(info.index));
    } else {
        // if form component not new create, just reuse runningCompId_
        wantCache_.SetParam(OHOS::AppExecFwk::Constants::FORM_COMP_ID, runningCompId_);
    }
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_BORDER_WIDTH_KEY, info.borderWidth);
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_OBSCURED_KEY, info.obscuredMode);
    auto pipelineContext = context_.Upgrade();
    if (pipelineContext) {
        auto density = pipelineContext->GetDensity();
        // 在OHOS::AppExecFwk::Constants中加类似常量
        wantCache_.SetParam("ohos.extra.param.key.form_density", density);
    }
    if (info.dimension != -1) {
        wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_DIMENSION_KEY, info.dimension);
    }
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_RENDERINGMODE_KEY, info.renderingMode);
}

void FormManagerDelegate::SetParamForWant(const RequestFormInfo& info, const AppExecFwk::FormInfo& formInfo)
{
    this->SetParamForWant(info);
    std::lock_guard<std::mutex> lock(wantCacheMutex_);
    if (formInfo.uiSyntax == AppExecFwk::FormType::ETS) {
        CHECK_NULL_VOID(renderDelegate_);
        wantCache_.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate_->AsObject());
        wantCache_.SetParam(ALLOW_UPDATE, info.allowUpdate);
        wantCache_.SetParam(IS_DYNAMIC, formInfo.isDynamic);
    }
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FONT_FOLLOW_SYSTEM_KEY, formInfo.fontScaleFollowSystem);
    auto disableBlurBackground = wantCache_.GetBoolParam(OHOS::AppExecFwk::Constants::FORM_DISABLE_BLUR_BACKGROUND,
        false);
    if (disableBlurBackground) {
        wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_ENABLE_BLUR_BACKGROUND_KEY, false);
    } else {
        wantCache_.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_ENABLE_BLUR_BACKGROUND_KEY,
            formInfo.enableBlurBackground);
    }
}


void FormManagerDelegate::OnRouterActionEvent(const std::string& action)
{
    AAFwk::Want want;
    if (!ParseAction(action, "router", want)) {
        TAG_LOGE(AceLogTag::ACE_FORM, "action parse failed, detail action:%{public}s", action.c_str());
    } else {
        CHECK_NULL_VOID(formUtils_);
        auto context = context_.Upgrade();
        CHECK_NULL_VOID(context);
        auto instantId = context->GetInstanceId();
        formUtils_->RouterEvent(runningCardId_, action, instantId, wantCache_.GetElement().GetBundleName());
    }
}

void FormManagerDelegate::OnCallActionEvent(const std::string& action)
{
    AAFwk::Want want;
    if (!ParseAction(action, "call", want)) {
        TAG_LOGE(AceLogTag::ACE_FORM, "action parse failed, detail action:%{public}s", action.c_str());
    } else {
        CHECK_NULL_VOID(formUtils_);
        auto context = context_.Upgrade();
        CHECK_NULL_VOID(context);
        auto instantId = context->GetInstanceId();
        formUtils_->BackgroundEvent(runningCardId_, action, instantId, wantCache_.GetElement().GetBundleName());
    }
}

void FormManagerDelegate::ProcessLockForm(bool lock)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "ProcessLockForm, formId is %{public}" PRId64, runningCardId_);
    HandleLockFormCallback(lock);
}
#endif
} // namespace OHOS::Ace
