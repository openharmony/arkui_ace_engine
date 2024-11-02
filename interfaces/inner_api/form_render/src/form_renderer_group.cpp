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

#include "form_renderer_group.h"

#include "form_renderer.h"
#include "form_renderer_hilog.h"

namespace OHOS {
namespace Ace {
namespace {
constexpr char FORM_RENDERER_COMP_ID[] = "ohos.extra.param.key.form_comp_id";
constexpr char FORM_RENDER_STATE[] = "ohos.extra.param.key.form_render_state";
}
std::shared_ptr<FormRendererGroup> FormRendererGroup::Create(
    const std::shared_ptr<OHOS::AbilityRuntime::Context> context,
    const std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime,
    std::weak_ptr<OHOS::AppExecFwk::EventHandler> eventHandler)
{
    return std::make_shared<FormRendererGroup>(context, runtime, eventHandler);
}

FormRendererGroup::FormRendererGroup(
    const std::shared_ptr<OHOS::AbilityRuntime::Context> context,
    const std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime,
    std::weak_ptr<OHOS::AppExecFwk::EventHandler> eventHandler)
    : context_(context), runtime_(runtime), eventHandler_(eventHandler) {}

FormRendererGroup::~FormRendererGroup()
{
    DeleteForm();
}

void FormRendererGroup::AddForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    auto compId = want.GetStringParam(FORM_RENDERER_COMP_ID);
    currentCompId_ = compId;
    FormRequest formRequest;
    formRequest.compId = compId;
    formRequest.want = want;
    formRequest.formJsInfo = formJsInfo;
    auto info = std::find_if(
        formRequests_.begin(), formRequests_.end(), formRequest);
    if (info != formRequests_.end()) {
        *info = formRequest;
    } else {
        formRequests_.emplace_back(formRequest);
    }
    bool isVerified = want.GetBoolParam(FORM_RENDER_STATE, false);
    if (isVerified) {
        HILOG_DEBUG("The user is verified, start rendering form.");
        InnerAddForm(formRequest);
        return;
    }
    HILOG_INFO("The user is not verified at this time, can not render the form now.");
    PreInitAddForm(formRequest);
}

void FormRendererGroup::PreInitAddForm(const FormRequest& formRequest)
{
    HILOG_DEBUG("called");
    if (initState_ != FormRendererInitState::UNINITIALIZED) {
        HILOG_WARN("no need to pre init again");
        return;
    }
    auto compId = formRequest.compId;
    OHOS::AAFwk::Want want = formRequest.want;
    AppExecFwk::FormJsInfo formJsInfo = formRequest.formJsInfo;
    if (formRenderer_ != nullptr) {
        HILOG_WARN("no need to pre init");
        return;
    }
    formRenderer_ = std::make_shared<FormRenderer>(context_, runtime_, eventHandler_);
    if (!formRenderer_) {
        HILOG_ERROR("create form render failed");
        return;
    }
    HILOG_INFO("compId is %{public}s. formId is %{public}s", compId.c_str(),
        std::to_string(formJsInfo.formId).c_str());
    formRenderer_->PreInitAddForm(want, formJsInfo);
    initState_ = FormRendererInitState::PRE_INITIALIZED;
}

void FormRendererGroup::OnUnlock()
{
    HILOG_INFO("The user is verified, OnUnlock called.");
    FormRequest currentFormRequest;
    bool hasValidRequest = false;
    for (auto& formRequest : formRequests_) {
        if (currentCompId_ == formRequest.compId) {
            currentFormRequest = formRequest;
            formRequest.want.SetParam(FORM_RENDER_STATE, true);
            hasValidRequest = true;
        }
    }

    if (!hasValidRequest) {
        HILOG_ERROR("Without valid form requests, current compId is %{public}s", currentCompId_.c_str());
        return;
    }
    InnerAddForm(currentFormRequest);
}

void FormRendererGroup::SetVisibleChange(bool isVisible)
{
    if (formRenderer_ == nullptr) {
        HILOG_ERROR("SetVisibleChange failed, formRenderer is null");
        return;
    }
    formRenderer_->SetVisibleChange(isVisible);
}

void FormRendererGroup::InnerAddForm(const FormRequest& formRequest)
{
    HILOG_DEBUG("InnerAddForm called");
    auto compId = formRequest.compId;
    OHOS::AAFwk::Want want = formRequest.want;
    AppExecFwk::FormJsInfo formJsInfo = formRequest.formJsInfo;
    if (formRenderer_ == nullptr || initState_ == FormRendererInitState::UNINITIALIZED) {
        formRenderer_ = std::make_shared<FormRenderer>(context_, runtime_, eventHandler_);
        if (!formRenderer_) {
            HILOG_ERROR("InnerAddForm create form render failed");
            return;
        }
        HILOG_INFO("InnerAddForm compId is %{public}s. formId is %{public}s, formJsInfo.formData.size is %{public}zu",
            compId.c_str(),
            std::to_string(formJsInfo.formId).c_str(),
            formJsInfo.formData.size());
        formRenderer_->AddForm(want, formJsInfo);
        initState_ = FormRendererInitState::INITIALIZED;
    } else if (initState_ == FormRendererInitState::PRE_INITIALIZED) {
        HILOG_INFO("RunFormPage compId is %{public}s. formId is %{public}s, formJsInfo.formData.size is %{public}zu",
            compId.c_str(),
            std::to_string(formJsInfo.formId).c_str(),
            formJsInfo.formData.size());
        formRenderer_->RunFormPage(want, formJsInfo);
        initState_ = FormRendererInitState::INITIALIZED;
    } else { // initState_ == FormRendererInitState::INITIALIZED
        HILOG_INFO("AttachForm compId is %{public}s, formRequests size is %{public}s, \
            formJsInfo.formData.size is %{public}zu",
            compId.c_str(),
            std::to_string(formRequests_.size()).c_str(),
            formJsInfo.formData.size());
        formRenderer_->AttachForm(want, formJsInfo);
    }
}

void FormRendererGroup::ReloadForm(const AppExecFwk::FormJsInfo& formJsInfo)
{
    if (formRenderer_ == nullptr) {
        HILOG_ERROR("ReloadForm failed, formRenderer is null");
        return;
    }

    formRenderer_->ReloadForm(formJsInfo.formSrc);
    for (auto &formRequest : formRequests_) {
        bool allDynamic = formJsInfo.isDynamic && formRequest.isDynamic;
        if (!allDynamic && currentCompId_ == formRequest.compId) {
            HILOG_INFO("SurfaceReuse due to change to static card when curCompId is %{public}s.",
                formRequest.compId.c_str());
            formRenderer_->OnSurfaceReuse(formJsInfo);
        }
        formRequest.formJsInfo = formJsInfo;
        formRequest.isDynamic = formJsInfo.isDynamic;
    }
}

void FormRendererGroup::UpdateFormSizeOfFormRequests(double width, double height, float borderWidth)
{
    for (auto iter = formRequests_.begin(); iter != formRequests_.end(); ++iter) {
        iter->want.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_WIDTH_KEY, static_cast<double>(width));
        iter->want.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_HEIGHT_KEY, static_cast<double>(height));
        iter->want.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_BORDER_WIDTH_KEY, static_cast<float>(borderWidth));
    }
    if (formRenderer_ != nullptr) {
        formRenderer_->UpdateFormSize(width, height, borderWidth);
    } else {
        HILOG_WARN("formRenderer is null");
    }
}

void FormRendererGroup::UpdateForm(const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    HILOG_INFO("UpdateForm formId %{public}s.", std::to_string(formJsInfo.formId).c_str());
    if (formRenderer_ == nullptr) {
        HILOG_ERROR("UpdateForm failed, formRenderer is null");
        return;
    }
    formRenderer_->UpdateForm(formJsInfo);
}

void FormRendererGroup::DeleteForm(const std::string& compId)
{
    HILOG_INFO("DeleteForm compId is %{public}s, currentCompId is %{public}s, formRequests size is %{public}s.",
        compId.c_str(), currentCompId_.c_str(), std::to_string(formRequests_.size()).c_str());

    for (auto iter = formRequests_.begin(); iter != formRequests_.end(); ++iter) {
        if (iter->compId == compId) {
            formRequests_.erase(iter);
            break;
        }
    }

    if (compId != currentCompId_) {
        return;
    }

    if (formRequests_.empty()) {
        HILOG_INFO("Release renderer obj due to formRequests is empty.");
        DeleteForm();
        return;
    }

    FormRequest request = formRequests_.back();
    currentCompId_ = request.compId;
    HILOG_INFO("RestoreForm compId is %{public}s.", currentCompId_.c_str());
    if (formRenderer_ == nullptr) {
        HILOG_INFO("FormRenderer has destory");
        return;
    }
    formRenderer_->AttachForm(request.want, request.formJsInfo);
}

bool FormRendererGroup::IsFormRequestsEmpty()
{
    return formRequests_.empty();
}

const std::vector<FormRequest>& FormRendererGroup::GetAllRendererFormRequests() const
{
    return formRequests_;
}

std::pair<std::vector<std::string>, std::string> FormRendererGroup::GetOrderedAndCurrentCompIds() const
{
    std::vector<std::string> orderedCompIds;
    for (auto formRequest: formRequests_) {
        orderedCompIds.emplace_back(formRequest.compId);
    }
    return std::make_pair(orderedCompIds, currentCompId_);
}

void FormRendererGroup::DeleteForm()
{
    if (formRenderer_ == nullptr) {
        HILOG_INFO("FormRenderer has destory");
        return;
    }
    formRenderer_->Destroy();
    formRenderer_ = nullptr;
    formRequests_.clear();
}

void FormRendererGroup::UpdateConfiguration(
    const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config)
{
    if (!config) {
        HILOG_ERROR("UpdateConfiguration config is null");
        return;
    }
    if (formRenderer_ == nullptr) {
        HILOG_ERROR("UpdateConfiguration failed, formRenderer is null");
        return;
    }
    formRenderer_->UpdateConfiguration(config);
}

void FormRendererGroup::RecycleForm(std::string& statusData) const
{
    if (formRenderer_ == nullptr) {
        HILOG_ERROR("RecycleForm failed, formRenderer is null");
        return;
    }
    formRenderer_->RecycleForm(statusData);
}

void FormRendererGroup::RecoverRenderer(const std::vector<FormRequest>& formRequests, size_t currentCompIndex)
{
    if (currentCompIndex >= formRequests.size()) {
        HILOG_ERROR("current comp index %{public}zu invalid", currentCompIndex);
        return;
    }
    
    const FormRequest &currentComp = formRequests[currentCompIndex];
    for (auto formRequest: formRequests) {
        formRequests_.emplace_back(formRequest);
    }
    currentCompId_ = currentComp.compId;

    bool isVerified = currentComp.want.GetBoolParam(FORM_RENDER_STATE, false);
    if (isVerified) {
        HILOG_DEBUG("user verified, start recover renderer");
        InnerAddForm(currentComp);
        return;
    }
    HILOG_INFO("user not verified, delay recover renderer");
    PreInitAddForm(currentComp);
}
}  // namespace Ace
}  // namespace OHOS
