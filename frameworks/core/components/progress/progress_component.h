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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PROGRESS_PROGRESS_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PROGRESS_PROGRESS_COMPONENT_H

#include "core/components/common/properties/progress_data.h"
#include "core/components/progress/progress_theme.h"
#include "core/components/track/track_component.h"
#include "core/pipeline/base/render_component.h"

namespace OHOS::Ace {

enum class ProgressType {
    LINEAR = 1,
    RING = 2,
    SCALE = 3,
    CIRCLE = 4,
    GAUGE = 5,
    ARC = 6,
    MOON = 7,
};

class ProgressComponent : public RenderComponent {
    DECLARE_ACE_TYPE(ProgressComponent, RenderComponent);

public:
    ProgressComponent(double min, double value, double cachedValue, double max, ProgressType type);
    ~ProgressComponent() override = default;

    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;

    void InitStyle(const RefPtr<ProgressTheme>& theme);

    RefPtr<TrackComponent> GetTrack() const
    {
        return track_;
    }

    void SetTrack(const RefPtr<TrackComponent>& track)
    {
        track_ = track;
    }

    void SetValue(double value)
    {
        data_.SetValue(value);
    }

    double GetValue() const
    {
        return data_.GetValue();
    }

    void SetCachedValue(double cachedValue)
    {
        data_.SetCachedValue(cachedValue);
    }

    double GetCachedValue() const
    {
        return data_.GetCachedValue();
    }

    void SetMaxValue(double max)
    {
        data_.SetMaxValue(max);
    }

    double GetMaxValue() const
    {
        return data_.GetMaxValue();
    }

    void SetMinValue(double min)
    {
        data_.SetMinValue(min);
    }

    double GetMinValue() const
    {
        return data_.GetMinValue();
    }

    ProgressType GetType() const
    {
        return type_;
    }

    void SetAnimationPlay(bool playAnimation)
    {
        playAnimation_ = playAnimation;
    }

    bool GetAnimationPlay() const
    {
        return playAnimation_;
    }

private:
    ProgressData data_;
    RefPtr<TrackComponent> track_;
    ProgressType type_ = ProgressType::LINEAR;
    bool playAnimation_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PROGRESS_PROGRESS_COMPONENT_H
