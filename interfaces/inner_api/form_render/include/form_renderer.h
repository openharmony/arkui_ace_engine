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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_H

#include "form_renderer.h"

#include "ability_context.h"
#include "js_runtime.h"
#include "runtime.h"
#include "ui_content.h"

#include "form_renderer_delegate_interface.h"
#include "form_renderer_dispatcher_impl.h"

namespace OHOS {
namespace Ace {
/**
 * @class FormRenderer
 * FormRenderer interface is used to form renderer.
 */
class FormRenderer {
public:
    FormRenderer(const std::shared_ptr<OHOS::AbilityRuntime::Context> context,
                 const std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime);
    ~FormRenderer() = default;

    void AddForm(const std::string& formUrl, const std::string& formdata);
    void UpdateForm(const std::string& formdata);

    void Destroy();
    /**
     * @brief OnActionEvent.
     * @param action The action.
     */
    int32_t OnActionEvent(const std::string& action);

private:
    std::string formUrl_;
    std::string formData_;
    std::shared_ptr<OHOS::AbilityRuntime::Context> context_;
    std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime_;
    std::shared_ptr<FormRendererDispatcherImpl> formRendererDispatcherImpl_;
    std::shared_ptr<IFormRendererDelegate> formRendererDelegate_;
    std::unique_ptr<UIContent> uiContent_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_H
