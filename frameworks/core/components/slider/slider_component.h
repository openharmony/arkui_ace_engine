/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SLIDER_SLIDER_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SLIDER_SLIDER_COMPONENT_H

#include <string>

#include "core/components/box/box_component.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/progress_data.h"
#include "core/components/common/rotation/rotation_controller.h"
#include "core/components/slider/block_component.h"
#include "core/components/slider/slider_theme.h"
#include "core/components/track/track_component.h"
#include "core/pipeline/base/component_group.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/base/render_component.h"

namespace OHOS::Ace {

constexpr double HALF = 0.5;

// The slider component manages the step, value, min, max, selectColor and padding.
class SliderComponent : public RenderComponent {
    DECLARE_ACE_TYPE(SliderComponent, RenderComponent);

public:
    SliderComponent(double value, double step, double min, double max);
    ~SliderComponent() override = default;

    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;

    void SetThemeStyle(const RefPtr<SliderTheme>& theme);
    void InitStyle(const RefPtr<SliderTheme>& theme);

    double GetMinValue() const
    {
        return data_.GetMinValue();
    }

    double GetMaxValue() const
    {
        return data_.GetMaxValue();
    }

    double GetStep() const
    {
        return data_.GetStepValue();
    }

    double GetValue() const
    {
        return data_.GetValue();
    }

    RefPtr<TrackComponent> GetTrack() const
    {
        return track_;
    }

    RefPtr<BlockComponent> GetBlock() const
    {
        return block_;
    }

    const EventMarker& GetOnMoveEndEventId() const
    {
        return onMoveEndEventId_;
    }

    void SetOnMoveEndEventId(const EventMarker& methodId)
    {
        onMoveEndEventId_ = methodId;
    }

    const EventMarker& GetOnMovingEventId() const
    {
        return onMovingEventId_;
    }

    void SetOnMovingEventId(const EventMarker& methodId)
    {
        onMovingEventId_ = methodId;
    }

    void SetBlock(const RefPtr<BlockComponent>& block)
    {
        block_ = block;
    }

    void SetTrack(const RefPtr<TrackComponent>& track)
    {
        track_ = track;
    }

    void SetCurrentValue(const double newValue)
    {
        data_.SetValue(newValue);
    }

    void SetMinValue(const double minValue)
    {
        data_.SetMinValue(minValue);
    }

    void SetMaxValue(const double minValue)
    {
        data_.SetMaxValue(minValue);
    }

    void SetStepValue(const double minValue)
    {
        data_.SetStepValue(minValue);
    }

    double MoveSteps(const int32_t num)
    {
        return data_.MoveSteps(num);
    }

    void SetTextDirection(TextDirection direction) override
    {
        Component::SetTextDirection(direction);
        track_->SetTextDirection(direction);
    }

    const RefPtr<RotationController>& GetRotationController() const
    {
        return rotationController_;
    }

    void SetDisable(bool disable)
    {
        isDisable_ = disable;
    }

    bool GetDisable() const
    {
        return isDisable_;
    }

    SliderMode GetSliderMode() const
    {
        return mode_;
    }

    void SetSliderMode(SliderMode mode)
    {
        mode_ = mode;
    }

    void SetShowTips(bool showTips)
    {
        showTips_ = showTips;
    }

    bool NeedShowTips() const
    {
        return showTips_;
    }

    void SetShowSteps(bool showSteps)
    {
        showSteps_ = showSteps;
    }

    bool NeedShowSteps() const
    {
        return showSteps_;
    }

private:
    ProgressData data_;
    RefPtr<BlockComponent> block_;
    RefPtr<TrackComponent> track_;
    EventMarker onMoveEndEventId_;
    EventMarker onMovingEventId_;
    bool isDisable_ = false;
    bool showTips_ = false;
    bool showSteps_ = false;
    SliderMode mode_ = SliderMode::OUTSET;
    RefPtr<RotationController> rotationController_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SLIDER_SLIDER_COMPONENT_H
