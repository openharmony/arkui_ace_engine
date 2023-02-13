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

#include "ability_context.h"
#include "form_js_info.h"
#include "js_runtime.h"
#include "runtime.h"
#include "ui_content.h"

#include "form_renderer_delegate_interface.h"
#include "form_renderer_dispatcher_impl.h"

namespace OHOS {
namespace Ace {
/**
 * @class FormRenderer
 */
class FormRenderer : public std::enable_shared_from_this<FormRenderer> {
public:
    FormRenderer(const std::shared_ptr<OHOS::AbilityRuntime::Context> context,
                 const std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime);
    ~FormRenderer() = default;

    void AddForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void UpdateForm(const OHOS::AppExecFwk::FormJsInfo& formJsInfo);

    void Destroy();
    void OnActionEvent(const std::string& action);
    void OnError(const std::string& code, const std::string& msg);
    void SetAllowUpdate(bool allowUpdate);
    bool IsAllowUpdate();

private:
    void InitUiContent();

    std::shared_ptr<OHOS::AbilityRuntime::Context> context_;
    std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime_;
    std::unique_ptr<FormRendererDispatcherImpl> formRendererDispatcherImpl_;
    sptr<IFormRendererDelegate> formRendererDelegate_;
    std::shared_ptr<UIContent> uiContent_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_H
