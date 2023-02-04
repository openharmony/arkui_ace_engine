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

#include "form_renderer.h"

namespace OHOS {
namespace Ace {
FormRenderer::FormRenderer(
    const std::shared_ptr<OHOS::AbilityRuntime::Context> context,
    const std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime) :
    context_(context), runtime_(runtime)
{
    if (!context_ || !runtime_) {
        return;
    }
    auto& nativeEngine = (static_cast<AbilityRuntime::JsRuntime&>(*runtime_.get())).GetNativeEngine();
    uiContent_ = UIContent::Create(context_.get(), &nativeEngine, true);
}

void FormRenderer::AddForm(const std::string& formUrl, const std::string& formData)
{
    if (formUrl.empty()) {
        return;
    }
    formUrl_ = formUrl;
    formData_ = formData;

    if (uiContent_) {
        uiContent_->Initialize(nullptr, formUrl_, nullptr);

        uiContent_->Foreground();
        auto rsSurfaceNode = uiContent_->GetCardRootNode();
        if (rsSurfaceNode == nullptr) {
            return;
        }
        // should set size
        // rsSurfaceNode->SetBounds(0.0f, 0.0f, uiContent->GetFormWidth(), uiContent->GetFormHeight());
        // uiContent->SetActionEventHandler(actionEventHandler);
    }
}

void FormRenderer::UpdateForm(const std::string& formData)
{
    if (formData.empty() || (formData_ == formData)) {
        return;
    }
    formData_ = formData;
    uiContent_->ProcessFormUpdate(formData);
}

void FormRenderer::Destroy() {}

int32_t FormRenderer::OnActionEvent(const std::string& action)
{
    return 0;
}
}  // namespace Ace
}  // namespace OHOS
