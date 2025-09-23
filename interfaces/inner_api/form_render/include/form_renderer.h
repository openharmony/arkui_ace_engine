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
#include "form_renderer_delegate_interface.h"
#include "form_renderer_dispatcher_impl.h"
#include "js_runtime.h"
#include "runtime.h"
#include "ui_content.h"
#include "event_handler.h"
#include "form_constants.h"
#include "core/accessibility/accessibility_manager.h"

namespace OHOS {
namespace AppExecFwk {
class Configuration;
class EventHandler;
}
namespace Ace {
/**
 * @class FormRenderer
 */
class FormRenderer : public std::enable_shared_from_this<FormRenderer> {
public:
    FormRenderer(const std::shared_ptr<OHOS::AbilityRuntime::Context> context,
        const std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime,
        std::weak_ptr<OHOS::AppExecFwk::EventHandler> eventHandler);
    ~FormRenderer();

    int32_t AddForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void PreInitAddForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    int32_t RunFormPage(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void UpdateForm(const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void ReloadForm(const std::string& url);
    void Destroy();
    void ResetRenderDelegate();
    void SetAllowUpdate(bool allowUpdate);
    bool IsAllowUpdate();

    int32_t OnSurfaceCreate(const OHOS::AppExecFwk::FormJsInfo& formJsInfo, bool isRecoverFormToHandleClickEvent);
    int32_t OnSurfaceReuse(const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void OnSurfaceDetach();
    void OnActionEvent(const std::string& action);
    void OnError(const std::string& code, const std::string& msg);
    void OnSurfaceChange(float width, float height, float borderWidth = 0.0);
    void OnFormLinkInfoUpdate(const std::vector<std::string>& formLinkInfos);
    void UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config);
    int32_t AttachForm(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void RecycleForm(std::string& statusData);
    void RecoverForm(const std::string& statusData);
    void GetRectRelativeToWindow(AccessibilityParentRectInfo& parentRectInfo) const;
    void SetVisibleChange(bool isVisible);
    void UpdateFormSize(float width, float height, float borderWidth);
    bool IsManagerDelegateValid(const OHOS::AAFwk::Want& want);

private:
    void InitUIContent(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void ParseWant(const OHOS::AAFwk::Want& want);
    void SetRenderDelegate(const sptr<IRemoteObject>& renderRemoteObj);
    void AttachUIContent(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void PreInitUIContent(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void RunFormPageInner(const OHOS::AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo);
    void RemoveFormDeathRecipient();
    std::shared_ptr<Rosen::RSSurfaceNode> GetSurfaceNode();

    bool allowUpdate_ = true;
    bool obscurationMode_ = false;
    float width_ = 0.0f;
    float height_ = 0.0f;
    float borderWidth_ = 0.0f;
    float lastBorderWidth_ = 0.0f;
    bool fontScaleFollowSystem_ = true;
    std::string backgroundColor_;
    AppExecFwk::Constants::RenderingMode renderingMode_ = AppExecFwk::Constants::RenderingMode::FULL_COLOR;
    bool enableBlurBackground_ = false;
    std::vector<std::string> cachedInfos_;
    std::shared_ptr<OHOS::AbilityRuntime::Context> context_;
    std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime_;
    std::weak_ptr<OHOS::AppExecFwk::EventHandler> eventHandler_;
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
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_H
