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

#include "base/log/log.h"
#include "core/common/container.h"
#include "frameworks/base/json/json_util.h"
#include "frameworks/core/common/frontend.h"

#ifdef OHOS_STANDARD_SYSTEM
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
constexpr int32_t RENDER_DEAD_CODE = 16501006;
constexpr int32_t FORM_NOT_TRUST_CODE = 16501007;
constexpr char ALLOW_UPDATE[] = "allowUpdate";
constexpr char IS_DYNAMIC[] = "isDynamic";
constexpr int32_t READD_FORM_DELAY_TIME = 50;
constexpr uint32_t DELAY_TIME_FOR_FORM_SNAPSHOT_10S = 10000;
constexpr int DELAY_TIME_OF_RECYCLE_FORM_AFTER_HANDLE_CLICK_EVENT = 10000;
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
        });
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
    // dynamic add new form should release the running form first.
    if (runningCardId_ > 0) {
        TAG_LOGI(AceLogTag::ACE_FORM, "Add new form, release platform resource about old form:%{public}s.",
            std::to_string(runningCardId_).c_str());
        ReleaseForm();
        ResetForm();
    }

    OHOS::AppExecFwk::FormJsInfo formJsInfo;
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
    wantCache_.SetParam(OHOS::AppExecFwk::Constants::FORM_COMP_ID, std::to_string(info.index));
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

    if (formInfo.uiSyntax == AppExecFwk::FormType::ETS) {
        CHECK_NULL_VOID(renderDelegate_);
        wantCache_.SetParam(FORM_RENDERER_PROCESS_ON_ADD_SURFACE, renderDelegate_->AsObject());
        wantCache_.SetParam(ALLOW_UPDATE, info.allowUpdate);
        wantCache_.SetParam(IS_DYNAMIC, formInfo.isDynamic);
    }

    auto clientInstance = OHOS::AppExecFwk::FormHostClient::GetInstance();
    auto ret = OHOS::AppExecFwk::FormMgr::GetInstance().AddForm(info.id, wantCache_, clientInstance, formJsInfo);
    if (ret != 0) {
        auto errorMsg = OHOS::AppExecFwk::FormMgr::GetInstance().GetErrorMessage(ret);
        OnFormError(std::to_string(ret), errorMsg);
        return;
    }

    TAG_LOGI(AceLogTag::ACE_FORM,
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

void FormManagerDelegate::OnSurfaceCreate(const AppExecFwk::FormJsInfo& formInfo,
    const std::shared_ptr<Rosen::RSSurfaceNode>& rsSurfaceNode, const AAFwk::Want& want)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "Form OnSurfaceCreate formId: %{public}s, isDynamic: %{public}d",
        std::to_string(formInfo.formId).c_str(), formInfo.isDynamic);
    if (!rsSurfaceNode) {
        return;
    }

    if (!onFormSurfaceNodeCallback_) {
        return;
    }

    onFormSurfaceNodeCallback_(rsSurfaceNode, formInfo.isDynamic);
    if (!formRendererDispatcher_) {
        sptr<IRemoteObject> proxy = want.GetRemoteObject(FORM_RENDERER_DISPATCHER);
        formRendererDispatcher_ = iface_cast<IFormRendererDispatcher>(proxy);
    }

    isDynamic_ = formInfo.isDynamic;
    if (!formInfo.isDynamic) {
        HandleSnapshotCallback(DELAY_TIME_FOR_FORM_SNAPSHOT_10S);
    }

    bool isRecoverFormToHandleClickEvent = want.GetBoolParam(
        OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM_TO_HANDLE_CLICK_EVENT, false);
    if (isDynamic_ && isRecoverFormToHandleClickEvent) {
        HandleCachedClickEvents();
    }
}

void FormManagerDelegate::HandleCachedClickEvents()
{
    {
        std::lock_guard<std::mutex> lock(recycleMutex_);
        LOGI("process click event after recover form, pointerEventCache_.size: %{public}s",
            std::to_string(pointerEventCache_.size()).c_str());
        recycleStatus_ = RecycleStatus::RECOVERED;
        for (const auto& pointerEvent : pointerEventCache_) {
            formRendererDispatcher_->DispatchPointerEvent(pointerEvent);
        }
        pointerEventCache_.clear();
    }

    // recycle form after handle click event
    std::vector<int64_t> formIds = {runningCardId_};
    AAFwk::Want want;
    want.SetParam(OHOS::AppExecFwk::Constants::FORM_DELAY_TIME_OF_RECYCLE,
        DELAY_TIME_OF_RECYCLE_FORM_AFTER_HANDLE_CLICK_EVENT);
    OHOS::AppExecFwk::FormMgr::GetInstance().RecycleForms(formIds, want);
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
            delegate->OnFormError("internal error");
            return;
        }
        delegate->state_ = State::CREATED;
        delegate->hash_ = delegate->MakeResourceHash();
        delegate->RegisterEvent();
    });
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

void FormManagerDelegate::AddFormLinkInfoUpdateCallback(OnFormLinkInfoUpdateCallback&& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }
    onFormLinkInfoUpdateCallback_ = std::move(callback);
}

void FormManagerDelegate::AddActionEventHandle(const ActionEventHandle& callback)
{
    if (!callback || state_ == State::RELEASED) {
        return;
    }
    actionEventHandle_ = callback;
}

void FormManagerDelegate::OnActionEventHandle(const std::string& action)
{
    if (actionEventHandle_) {
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
        return false;
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
    auto&& surfaceCreateEventHandler = [weak = WeakClaim(this)](
                                           const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode,
                                           const OHOS::AppExecFwk::FormJsInfo& formInfo, const AAFwk::Want& want) {
        auto formManagerDelegate = weak.Upgrade();
        CHECK_NULL_VOID(formManagerDelegate);
        formManagerDelegate->OnSurfaceCreate(formInfo, surfaceNode, want);
    };
    renderDelegate_->SetSurfaceCreateEventHandler(std::move(surfaceCreateEventHandler));

    auto&& actionEventHandler = [weak = WeakClaim(this)](const std::string& action) {
        auto formManagerDelegate = weak.Upgrade();
        CHECK_NULL_VOID(formManagerDelegate);
        formManagerDelegate->OnActionEventHandle(action);
    };
    renderDelegate_->SetActionEventHandler(std::move(actionEventHandler));

    auto&& onErrorEventHandler = [weak = WeakClaim(this)](const std::string& code, const std::string& msg) {
        auto formManagerDelegate = weak.Upgrade();
        CHECK_NULL_VOID(formManagerDelegate);
        formManagerDelegate->OnFormError(code, msg);
    };
    renderDelegate_->SetErrorEventHandler(std::move(onErrorEventHandler));

    auto&& onSurfaceChangeHandler = [weak = WeakClaim(this)](float width, float height) {
        auto formManagerDelegate = weak.Upgrade();
        CHECK_NULL_VOID(formManagerDelegate);
        formManagerDelegate->OnFormSurfaceChange(width, height);
    };
    renderDelegate_->SetSurfaceChangeEventHandler(std::move(onSurfaceChangeHandler));

    auto&& onFormLinkInfoUpdateHandler = [weak = WeakClaim(this)](const std::vector<std::string>& formLinkInfos) {
        auto formManagerDelegate = weak.Upgrade();
        CHECK_NULL_VOID(formManagerDelegate);
        formManagerDelegate->OnFormLinkInfoUpdate(formLinkInfos);
    };
    renderDelegate_->SetFormLinkInfoUpdateHandler(std::move(onFormLinkInfoUpdateHandler));
}

void FormManagerDelegate::OnActionEvent(const std::string& action)
{
    auto eventAction = JsonUtil::ParseJsonString(action);
    if (!eventAction->IsValid()) {
        return;
    }
    auto uri = eventAction->GetValue("uri");
    auto abilityName = eventAction->GetValue("abilityName");
    if (uri->IsValid() && !abilityName->IsValid()) {
        CHECK_NULL_VOID(formUtils_);
        auto context = context_.Upgrade();
        CHECK_NULL_VOID(context);
        auto instantId = context->GetInstanceId();
        formUtils_->RouterEvent(runningCardId_, action, instantId, wantCache_.GetElement().GetBundleName());
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
        AAFwk::Want want;
        if (!ParseAction(action, type, want)) {
        } else {
            CHECK_NULL_VOID(formUtils_);
            auto context = context_.Upgrade();
            CHECK_NULL_VOID(context);
            auto instantId = context->GetInstanceId();
            formUtils_->RouterEvent(runningCardId_, action, instantId, wantCache_.GetElement().GetBundleName());
        }
        return;
    } else if (type == "call") {
        AAFwk::Want want;
        if (!ParseAction(action, type, want)) {
        } else {
            CHECK_NULL_VOID(formUtils_);
            auto context = context_.Upgrade();
            CHECK_NULL_VOID(context);
            auto instantId = context->GetInstanceId();
            formUtils_->BackgroundEvent(runningCardId_, action, instantId, wantCache_.GetElement().GetBundleName());
        }
        return;
    }

    AAFwk::Want want;
    if (!ParseAction(action, type, want)) {
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

void FormManagerDelegate::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    if (!isDynamic_) {
        return;
    }

    // if formRendererDispatcher_ is null, check if form is recycled.
    if (formRendererDispatcher_ == nullptr) {
        std::lock_guard<std::mutex> lock(recycleMutex_);
        if (recycleStatus_ == RecycleStatus::RECYCLED) {
            LOGI("form is recycled, recover it first");
            recycleStatus_ = RecycleStatus::RECOVERING;
            pointerEventCache_.emplace_back(pointerEvent);

            std::vector<int64_t> formIds = {runningCardId_};
            AAFwk::Want want;
            want.SetParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM_TO_HANDLE_CLICK_EVENT, true);
            OHOS::AppExecFwk::FormMgr::GetInstance().RecoverForms(formIds, want);
        } else if (recycleStatus_ == RecycleStatus::RECOVERING) {
            LOGI("form is recovering, cache pointer event");
            pointerEventCache_.emplace_back(pointerEvent);
        } else {
            LOGE("formRendererDispatcher_ is null");
        }
        return;
    }
    formRendererDispatcher_->DispatchPointerEvent(pointerEvent);
}

void FormManagerDelegate::SetAllowUpdate(bool allowUpdate)
{
    if (formRendererDispatcher_ == nullptr) {
        return;
    }

    formRendererDispatcher_->SetAllowUpdate(allowUpdate);
}

void FormManagerDelegate::NotifySurfaceChange(float width, float height)
{
    if (formRendererDispatcher_ == nullptr) {
        return;
    }
    formRendererDispatcher_->DispatchSurfaceChangeEvent(width, height);
}

void FormManagerDelegate::OnFormSurfaceChange(float width, float height)
{
    if (onFormSurfaceChangeCallback_) {
        onFormSurfaceChangeCallback_(width, height);
    }
}

void FormManagerDelegate::OnFormLinkInfoUpdate(const std::vector<std::string>& formLinkInfos)
{
    if (onFormLinkInfoUpdateCallback_) {
        onFormLinkInfoUpdateCallback_(formLinkInfos);
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
    if (onFormErrorCallback_) {
        onFormErrorCallback_(result["code"], result["msg"]);
    }
}

void FormManagerDelegate::OnFormError(const std::string& code, const std::string& msg)
{
    int32_t externalErrorCode = 0;
    std::string errorMsg;
    OHOS::AppExecFwk::FormMgr::GetInstance().GetExternalError(std::stoi(code), externalErrorCode, errorMsg);
    LOGI("OnFormError, code:%{public}s, msg:%{public}s, externalErrorCode:%{public}d, errorMsg: %{public}s",
        code.c_str(), msg.c_str(), externalErrorCode, errorMsg.c_str());
    switch (externalErrorCode) {
        case RENDER_DEAD_CODE:
            std::this_thread::sleep_for(std::chrono::milliseconds(READD_FORM_DELAY_TIME));
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

void FormManagerDelegate::ReAddForm()
{
    formRendererDispatcher_ = nullptr; // formRendererDispatcher_ need reset, otherwise PointerEvent will disable
    auto clientInstance = OHOS::AppExecFwk::FormHostClient::GetInstance();
    auto ret =
        OHOS::AppExecFwk::FormMgr::GetInstance().AddForm(formJsInfo_.formId, wantCache_, clientInstance, formJsInfo_);
    if (ret != 0) {
        auto errorMsg = OHOS::AppExecFwk::FormMgr::GetInstance().GetErrorMessage(ret);
        TAG_LOGW(AceLogTag::ACE_FORM, "Add form failed, ret:%{public}d detail:%{public}s", ret, errorMsg.c_str());
        OnFormError(std::to_string(ret), errorMsg);
        return;
    }
}

void FormManagerDelegate::SetVisibleChange(bool isVisible)
{
    CHECK_NULL_VOID(formRendererDispatcher_);
    formRendererDispatcher_->SetVisibleChange(isVisible);
}

#ifdef OHOS_STANDARD_SYSTEM
void FormManagerDelegate::ResetForm()
{
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
    TAG_LOGI(AceLogTag::ACE_FORM, "FormManagerDelegate releaseForm. formId: %{public}" PRId64 ", %{public}s",
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
    LOGI("ProcessRecycleForm, formId is %{public}s", std::to_string(runningCardId_).c_str());
    {
        std::lock_guard<std::mutex> lock(recycleMutex_);
        recycleStatus_ = RecycleStatus::RECYCLED;
    }
    HandleSnapshotCallback(0);
}
#endif
} // namespace OHOS::Ace
