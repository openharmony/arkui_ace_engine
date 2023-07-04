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
namespace AppExecFwk {
class Configuration;
}
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
    void ReloadForm(const std::string& url);
    void Destroy();
    void ResetRenderDelegate();
    void SetAllowUpdate(bool allowUpdate);
    bool IsAllowUpdate();

    void OnSurfaceCreate(const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void OnSurfaceReuse(const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void OnActionEvent(const std::string& action);
    void OnError(const std::string& code, const std::string& msg);
    void OnSurfaceChange(float width, float height);
    void UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config);
    void AttachForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo);

private:
    void InitUIContent(const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void ParseWant(const OHOS::AAFwk::Want& want);
    void SetRenderDelegate(const sptr<IRemoteObject> &renderRemoteObj);
    void AttachUIContent(const OHOS::AppExecFwk::FormJsInfo& formJsInfo);

    bool allowUpdate_ = true;
    float width_ = 0.0f;
    float height_ = 0.0f;
    std::shared_ptr<OHOS::AbilityRuntime::Context> context_;
    std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime_;
    sptr<FormRendererDispatcherImpl> formRendererDispatcherImpl_;
    sptr<IFormRendererDelegate> formRendererDelegate_;
    std::shared_ptr<UIContent> uiContent_;
    sptr<IRemoteObject::DeathRecipient> renderDelegateDeathRecipient_;
    sptr<IRemoteObject> proxy_;
};

/**
 * @class FormRenderDelegateRecipient
 * FormRenderDelegateRecipient notices IRemoteBroker died.
 */
class FormRenderDelegateRecipient : public IRemoteObject::DeathRecipient {
public:
    using RemoteDiedHandler = std::function<void()>;
    explicit FormRenderDelegateRecipient(RemoteDiedHandler handler) : handler_(std::move(handler)) {}

    ~FormRenderDelegateRecipient() override = default;

    void OnRemoteDied(const wptr<IRemoteObject>& remote) override;

private:
    RemoteDiedHandler handler_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_H
