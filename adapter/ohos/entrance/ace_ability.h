/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CPP_ACE_ABILITY_H
#define FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CPP_ACE_ABILITY_H

#include <string>
#include <vector>

#include "ability.h"
#include "ability_loader.h"
#include "want.h"
#include "window.h"

#include "core/common/window_animation_config.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace {
class AceAbility;
class AceWindowListener : public OHOS::Rosen::IWindowDragListener,
                          public OHOS::Rosen::IWindowChangeListener,
                          public OHOS::Rosen::IOccupiedAreaChangeListener,
                          public OHOS::Rosen::IAceAbilityHandler,
                          public OHOS::Rosen::IInputEventConsumer,
                          public OHOS::Rosen::IAvoidAreaChangedListener {
public:
    explicit AceWindowListener(std::shared_ptr<AceAbility> owner) : callbackOwner_(owner) {}
    ~AceWindowListener() = default;
    // override Rosen::IWindowDragListener virtual callback function
    void OnDrag(int32_t x, int32_t y, OHOS::Rosen::DragEvent event) override;

    // override Rosen::IOccupiedAreaChangeListener virtual callback function
    void OnSizeChange(const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction = nullptr) override;

    // override Rosen::IAceAbilityHandler virtual callback function
    void SetBackgroundColor(uint32_t color) override;
    uint32_t GetBackgroundColor() override;

    // override Rosen::IWindowChangeListener virtual callback function
    void OnSizeChange(OHOS::Rosen::Rect rect, OHOS::Rosen::WindowSizeChangeReason reason,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction = nullptr) override;
    void OnModeChange(OHOS::Rosen::WindowMode mode, bool hasDeco = true) override;

    // override Rosen::IInputEventConsumer virtual callback function
    bool OnInputEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent) const override;
    bool OnInputEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) const override;
    bool OnInputEvent(const std::shared_ptr<MMI::AxisEvent>& axisEvent) const override;

    // override Rosen::IAvoidAreaChangedListener virtual callback function
    void OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type) override;

private:
    std::shared_ptr<AceAbility> callbackOwner_;
};

class AceAbility final : public OHOS::AppExecFwk::Ability {
public:
    AceAbility();
    ~AceAbility() override = default;

    void OnStart(const OHOS::AAFwk::Want& want, sptr<AAFwk::SessionInfo> sessionInfo = nullptr) override;
    void OnStop() override;
    void OnActive() override;
    void OnInactive() override;
    void OnForeground(const OHOS::AAFwk::Want& want) override;
    void OnBackground() override;
    void OnBackPressed() override;
    void OnNewWant(const OHOS::AAFwk::Want& want) override;
    void OnRestoreAbilityState(const OHOS::AppExecFwk::PacMap& inState) override;
    void OnSaveAbilityState(OHOS::AppExecFwk::PacMap& outState) override;
    void OnConfigurationUpdated(const OHOS::AppExecFwk::Configuration& configuration) override;
    void OnAbilityResult(int requestCode, int resultCode, const OHOS::AAFwk::Want& resultData) override;

    bool OnStartContinuation() override;
    bool OnSaveData(OHOS::AAFwk::WantParams& saveData) override;
    bool OnRestoreData(OHOS::AAFwk::WantParams& restoreData) override;
    void OnCompleteContinuation(int result) override;
    void OnRemoteTerminated() override;

    // handle window Rosen::IWindowDragListener
    void OnDrag(int32_t x, int32_t y, OHOS::Rosen::DragEvent event);

    // handle window Rosen::IWindowChangeListener
    void OnSizeChange(const OHOS::Rosen::Rect& rect, OHOS::Rosen::WindowSizeChangeReason reason,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction = nullptr);
    void OnModeChange(OHOS::Rosen::WindowMode mode, bool hasDeco = true);

    // handle window Rosen::IOccupiedAreaChangeListener
    void OnSizeChange(const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction = nullptr);

    // handle window Rosen::IInputEventConsumer
    bool OnInputEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent) const;
    bool OnInputEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) const;
    bool OnInputEvent(const std::shared_ptr<MMI::AxisEvent>& axisEvent) const;

    // handle window Rosen::IAceAbilityHandler
    void SetBackgroundColor(uint32_t color);
    uint32_t GetBackgroundColor();

    // handle window Rosen::IAvoidAreaChangedListener
    void OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea& avoidArea, OHOS::Rosen::AvoidAreaType type);

    void Dump(const std::vector<std::string>& params, std::vector<std::string>& info) override;

private:
    static const std::string START_PARAMS_KEY;
    static const std::string PAGE_URI;
    static const std::string CONTINUE_PARAMS_KEY;

    int32_t abilityId_ = -1;
    float density_ = 1.0f;
    std::string remotePageUrl_;
    std::string remoteData_;
    std::string pageUrl_;
    bool isFirstActive_ = true;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CPP_ACE_ABILITY_H
