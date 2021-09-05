/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
#include <sstream>

#include "base/log/log.h"
#include "frameworks/base/json/json_util.h"

namespace OHOS::Ace {

namespace {

constexpr char FORM_EVENT_ON_ACQUIRE_FORM[] = "onAcquireForm";
constexpr char FORM_EVENT_ON_UPDATE_FORM[] = "onUpdateForm";
constexpr char FORM_EVENT_ON_ERROR[] = "onFormError";
constexpr char FORM_ADAPTOR_RESOURCE_NAME[] = "formAdaptor";
constexpr char NTC_PARAM_RICH_TEXT[] = "formAdaptor";

} // namespace

FormManagerDelegate::~FormManagerDelegate()
{
    ReleasePlatformResource();
}

void FormManagerDelegate::ReleasePlatformResource()
{
    Stop();
    Release();
}

void FormManagerDelegate::Stop()
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("fail to get context when stop");
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
        LOGE("fail to get context when unregister event");
        return;
    }
    auto resRegister = context->GetPlatformResRegister();
    resRegister->UnregisterEvent(MakeEventHash(FORM_EVENT_ON_ACQUIRE_FORM));
    resRegister->UnregisterEvent(MakeEventHash(FORM_EVENT_ON_UPDATE_FORM));
    resRegister->UnregisterEvent(MakeEventHash(FORM_EVENT_ON_ERROR));
}

void FormManagerDelegate::AddForm(const WeakPtr<PipelineContext>& context, const RequestFormInfo& info)
{
    if (state_ == State::CREATED) {
        hash_ = MakeResourceHash();
        Method addFormMethod = MakeMethodHash("addForm");
        std::string param = ConvertRequestInfo(info);
        LOGD("addForm method:%{public}s, params:%{public}s", addFormMethod.c_str(), param.c_str());
        CallResRegisterMethod(addFormMethod, param, nullptr);
    } else {
        CreatePlatformResource(context, info);
    }
}

std::string FormManagerDelegate::ConvertRequestInfo(const RequestFormInfo& info) const
{
    std::stringstream paramStream;
    paramStream << "bundle" << FORM_MANAGER_PARAM_EQUALS << info.bundleName << FORM_MANAGER_PARAM_AND
                << "ability" << FORM_MANAGER_PARAM_EQUALS << info.abilityName << FORM_MANAGER_PARAM_AND
                << "module" << FORM_MANAGER_PARAM_EQUALS << info.moduleName << FORM_MANAGER_PARAM_AND
                << "name" << FORM_MANAGER_PARAM_EQUALS << info.cardName << FORM_MANAGER_PARAM_AND
                << "dimension" << FORM_MANAGER_PARAM_EQUALS << info.dimension << FORM_MANAGER_PARAM_AND
                << "id" << FORM_MANAGER_PARAM_EQUALS << info.id << FORM_MANAGER_PARAM_AND
                << "cardkey" << FORM_MANAGER_PARAM_EQUALS << info.ToString();
    return paramStream.str();
}

void FormManagerDelegate::CreatePlatformResource(const WeakPtr<PipelineContext>& context, const RequestFormInfo& info)
{
    context_ = context;
    state_ = State::CREATING;

    auto pipelineContext = context.Upgrade();
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
        auto resRegister = weakRes.Upgrade();
        auto context = delegate->context_.Upgrade();
        if (!delegate || !resRegister || !context) {
            LOGE("delegate is null");
            delegate->OnFormError("internal error");
            return;
        }

        delegate->id_ = CREATING_ID;

        std::stringstream paramStream;
        paramStream << NTC_PARAM_RICH_TEXT << FORM_MANAGER_PARAM_EQUALS << delegate->id_ << FORM_MANAGER_PARAM_AND
                    << "bundle" << FORM_MANAGER_PARAM_EQUALS << info.bundleName << FORM_MANAGER_PARAM_AND
                    << "ability" << FORM_MANAGER_PARAM_EQUALS << info.abilityName << FORM_MANAGER_PARAM_AND
                    << "module" << FORM_MANAGER_PARAM_EQUALS << info.moduleName << FORM_MANAGER_PARAM_AND
                    << "name" << FORM_MANAGER_PARAM_EQUALS << info.cardName << FORM_MANAGER_PARAM_AND
                    << "dimension" << FORM_MANAGER_PARAM_EQUALS << info.dimension << FORM_MANAGER_PARAM_AND
                    << "id" << FORM_MANAGER_PARAM_EQUALS << info.id << FORM_MANAGER_PARAM_AND
                    << "cardkey" << FORM_MANAGER_PARAM_EQUALS << info.ToString();

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
        LOGE("register event error due null context, will not receive form manager event");
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
        LOGE("callback is null or has released");
        return;
    }
    onFormAcquiredCallback_ = callback;
}

void FormManagerDelegate::AddFormUpdateCallback(const OnFormUpdateCallback& callback)
{
    if (!callback || state_ == State::RELEASED) {
        LOGE("callback is null or has released");
        return;
    }
    onFormUpdateCallback_ = callback;
}

void FormManagerDelegate::AddFormErrorCallback(const OnFormErrorCallback& callback)
{
    if (!callback || state_ == State::RELEASED) {
        LOGE("callback is null or has released");
        return;
    }
    onFormErrorCallback_ = callback;
}

void FormManagerDelegate::OnActionEvent(const std::string& action)
{
    auto eventAction = JsonUtil::ParseJsonString(action);
    if (!eventAction->IsValid()) {
        LOGE("get event action failed");
        return;
    }
    auto actionType = eventAction->GetValue("action");
    if (!actionType->IsValid()) {
        LOGE("get event key failed");
        return;
    }

    auto type = actionType->GetString();
    if (type != "router" && type != "message") {
        LOGE("undefined event type");
        return;
    }

    hash_ = MakeResourceHash();
    Method actionMethod = MakeMethodHash("onAction");
    std::stringstream paramStream;
    paramStream << "type" << FORM_MANAGER_PARAM_EQUALS << type << FORM_MANAGER_PARAM_AND
                << "action" << FORM_MANAGER_PARAM_EQUALS << action;
    std::string param = paramStream.str();
    LOGI("send method:%{private}s, type:%{public}s params:%{private}s",
        actionMethod.c_str(), type.c_str(), param.c_str());
    CallResRegisterMethod(actionMethod, param, nullptr);
}

void FormManagerDelegate::OnFormAcquired(const std::string& param)
{
    auto result = ParseMapFromString(param);
    if (onFormAcquiredCallback_) {
        onFormAcquiredCallback_(result["formId"], result["codePath"], result["moduleName"], result["data"]);
    }
}

void FormManagerDelegate::OnFormUpdate(const std::string& param)
{
    auto result = ParseMapFromString(param);
    if (onFormUpdateCallback_) {
        onFormUpdateCallback_(result["formId"], result["data"]);
    }
}

void FormManagerDelegate::OnFormError(const std::string& param)
{
    auto result = ParseMapFromString(param);
    if (onFormErrorCallback_) {
        onFormErrorCallback_(result["code"], result["msg"]);
    }
}

} // namespace OHOS::Ace
