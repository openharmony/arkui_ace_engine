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

#include "form_js_info.h"
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

void FormRendererGroup::AddForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    auto compId = want.GetStringParam(FORM_RENDERER_COMP_ID);
    HILOG_INFO("AddForm compId %{public}s.", compId.c_str());
    auto iter = rendererMap_.find(compId);
    if (iter != rendererMap_.end()) {
        HILOG_WARN("AddForm compId: %{public}s exist", compId.c_str());
        auto renderer = iter->second;
        renderer->Destroy();
        rendererMap_.erase(iter);
    }
    auto formRenderer = std::make_shared<FormRenderer>(context_, runtime_);
    if (!formRenderer) {
        HILOG_ERROR("AddForm create formrender failed");
        return;
    }
    rendererMap_.try_emplace(compId, formRenderer);
    formRenderer->AddForm(want, formJsInfo);
}

void FormRendererGroup::ReloadForm()
{
    auto iter = rendererMap_.begin();
    while (iter != rendererMap_.end()) {
        auto renderer = iter->second;
        renderer->ReloadForm();
        iter++;
    }
}

void FormRendererGroup::UpdateForm(const OHOS::AppExecFwk::FormJsInfo& formJsInfo)
{
    HILOG_INFO("UpdateForm compId %{public}s.", std::to_string(formJsInfo.formId).c_str());
    auto iter = rendererMap_.begin();
    while (iter!= rendererMap_.end()) {
        auto renderer = iter->second;
        renderer->UpdateForm(formJsInfo);
        iter++;
    }
}

void FormRendererGroup::DeleteForm(const std::string& compId)
{
    HILOG_INFO("DeleteForm compId %{public}s.", compId.c_str());
    auto iter = rendererMap_.find(compId);
    if (iter == rendererMap_.end()) {
        return;
    }
    auto renderer = iter->second;
    // should release the occupancy of resources of the context, runtime and ui content
    renderer->Destroy();
    rendererMap_.erase(iter);
}
}  // namespace Ace
}  // namespace OHOS
