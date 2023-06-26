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

#include "configuration.h"
#include "form_renderer.h"
#include "form_renderer_hilog.h"

namespace OHOS {
namespace Ace {
namespace {
constexpr char FORM_RENDERER_COMP_ID[] = "ohos.extra.param.key.form_comp_id";
}
std::shared_ptr<FormRendererGroup> FormRendererGroup::Create(
    const std::shared_ptr<OHOS::AbilityRuntime::Context> context,
    const std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime)
{
    return std::make_shared<FormRendererGroup>(context, runtime);
}

FormRendererGroup::FormRendererGroup(
    const std::shared_ptr<OHOS::AbilityRuntime::Context> context,
    const std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime)
    : context_(context), runtime_(runtime) {}

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
    formRequests_.push_back(formRequest);
    if (formRenderer_ == nullptr) {
        formRenderer_ = std::make_shared<FormRenderer>(context_, runtime_);
        if (!formRenderer_) {
            HILOG_ERROR("AddForm create form render failed");
            return;
        }
        HILOG_INFO("AddForm compId is %{public}s. formId is %{public}s", compId.c_str(),
            std::to_string(formJsInfo.formId).c_str());
        formRenderer_->AddForm(want, formJsInfo);
    } else {
        HILOG_INFO("AttachForm compId is %{public}s formRequests size is :%{public}s.",
            compId.c_str(), std::to_string(formRequests_.size()).c_str());
        formRenderer_->AttachForm(want, formJsInfo);
    }
}

void FormRendererGroup::ReloadForm()
{
    if (formRenderer_ == nullptr) {
        HILOG_ERROR("ReloadForm failed, formRenderer is null");
        return;
    }
    formRenderer_->ReloadForm();
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
    formRenderer_->AttachForm(request.want, request.formJsInfo);
}

bool FormRendererGroup::IsFormRequestsEmpty()
{
    return formRequests_.empty();
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
}  // namespace Ace
}  // namespace OHOS
