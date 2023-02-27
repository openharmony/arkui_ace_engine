/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/window_scene/root/root_scene.h"

#include "input_manager.h"
#include "wm_common.h"

namespace OHOS::Ace::NG {

class InputEventListener : public MMI::IInputEventConsumer {
public:
    explicit InputEventListener(RootScene* rootScene): rootScene_(rootScene) {}
    virtual ~InputEventListener() = default;

    void OnInputEvent(std::shared_ptr<MMI::PointerEvent> pointerEvent) const override
    {
        rootScene_->ProcessPointerEvent(pointerEvent);
    }

    void OnInputEvent(std::shared_ptr<MMI::KeyEvent> keyEvent) const override
    {
        rootScene_->ProcessKeyEvent(keyEvent);
    }

    void OnInputEvent(std::shared_ptr<MMI::AxisEvent> axisEvent) const override
    {
        rootScene_->ProcessAxisEvent(axisEvent);
    }

private:
    RootScene* rootScene_;
};

extern "C" ACE_EXPORT void* OHOS_ACE_CreateRootScene()
{
    LOGI("Ace lib loaded, CreateRootScene.");
    return new RootScene();
}

void RootScene::LoadContent(const std::string& contentUrl, NativeEngine* engine, NativeValue* storage,
    AbilityRuntime::Context* context)
{
    RegisterInputEventListener();

    CHECK_NULL_VOID(context);
    uiContent_ = UIContent::Create(context, engine);
    CHECK_NULL_VOID(uiContent_);
    uiContent_->Initialize(this, contentUrl, storage);

    ViewportConfig config;
    config.SetPosition(0, 0);
    config.SetSize(720, 1280);
    config.SetDensity(1.5); // TODO: get display density
    UpdateViewportConfig(config, Rosen::WindowSizeChangeReason::UNDEFINED);
}

void RootScene::RegisterInputEventListener()
{
    auto listener = std::make_shared<InputEventListener>(this);
    auto mainEventRunner = AppExecFwk::EventRunner::GetMainEventRunner();
    if (mainEventRunner) {
        LOGI("MainEventRunner is available");
        eventHandler_ = std::make_shared<AppExecFwk::EventHandler>(mainEventRunner);
    } else {
        LOGI("MainEventRunner is not available");
    }
    MMI::InputManager::GetInstance()->SetWindowInputEventConsumer(listener, eventHandler_);
}

} // namespace OHOS::Ace::NG
