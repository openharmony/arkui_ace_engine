/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ABILITY_COMPONENT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ABILITY_COMPONENT_PATTERN_H

#include "frameworks/base/geometry/rect.h"
#include "frameworks/base/memory/referenced.h"
#include "frameworks/core/common/window_ng/window_extension_connection_proxy_ng.h"
#include "frameworks/core/components_ng/pattern/ability_component/ability_component_event_hub.h"
#include "frameworks/core/components_ng/pattern/ability_component/ability_component_layout_algorithm.h"
#include "frameworks/core/components_ng/pattern/ability_component/ability_component_render_property.h"
#include "frameworks/core/components_ng/pattern/pattern.h"
#include "frameworks/core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "frameworks/core/components_ng/property/property.h"
#include "frameworks/core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT AbilityComponentPattern : public WindowPattern {
    DECLARE_ACE_TYPE(AbilityComponentPattern, WindowPattern);

public:
    AbilityComponentPattern(const std::string& bundleName, const std::string& abilityName);

    ~AbilityComponentPattern() override
    {
        if (adapter_) {
            adapter_->RemoveExtension();
        }
    }

    bool HasStartingPage() override
    {
        return false;
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<AbilityComponentRenderProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<AbilityComponentEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<AbilityComponentLayoutAlgorithm>();
    }

    FocusPattern GetFocusPattern() const override;
    void FireConnect();
    void FireDisConnect();
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnAreaChangedInner() override;

private:
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;

    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitMouseEvent(const RefPtr<InputEventHub>& inputHub);
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleMouseEvent(const MouseInfo& info);
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    void HandleFocusEvent();
    void HandleBlurEvent();
    bool KeyEventConsumed(const KeyEvent& event);

    void OnVisibleChange(bool visible) override
    {
        if (!adapter_) {
            return;
        }
        if (visible && !isActive_) {
            adapter_->Show();
            isActive_ = true;
        } else if (!visible && isActive_) {
            adapter_->Hide();
            isActive_ = false;
        }
    }

    void OnActive() override
    {
        if (!isActive_) {
            if (adapter_) {
                adapter_->Show();
            }
            isActive_ = true;
        }
    }

    void OnInActive() override
    {
        if (isActive_) {
            if (adapter_) {
                adapter_->Hide();
            }
            isActive_ = false;
        }
    }

    void OnWindowShow() override
    {
        if (!isActive_) {
            if (adapter_) {
                adapter_->Show();
            }
            isActive_ = true;
        }
    }

    void OnWindowHide() override
    {
        if (isActive_) {
            if (adapter_) {
                adapter_->Hide();
            }
            isActive_ = false;
        }
    }

    void UpdateWindowRect();
    bool IsCurrentFocus() const;

    bool isActive_ = false;
    bool hasConnectionToAbility_ = false;
    Rect lastRect_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<WindowExtensionConnectionAdapterNG> adapter_;
    ACE_DISALLOW_COPY_AND_MOVE(AbilityComponentPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ABILITY_COMPONENT_PATTERN_H
