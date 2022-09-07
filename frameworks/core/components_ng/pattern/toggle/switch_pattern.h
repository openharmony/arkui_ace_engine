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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWITCH_SWITCH_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWITCH_SWITCH_PATTERN_H

#include "base/geometry/axis.h"
#include "base/geometry/size.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/toggle/switch_event_hub.h"
#include "core/components_ng/pattern/toggle/switch_layout_algorithm.h"
#include "core/components_ng/pattern/toggle/switch_paint_method.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"

namespace OHOS::Ace::NG {

class SwitchPattern : public Pattern {
    DECLARE_ACE_TYPE(SwitchPattern, Pattern);

public:
    SwitchPattern() = default;

    ~SwitchPattern() override = default;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<SwitchEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<SwitchLayoutAlgorithm>();
        layoutAlgorithm->SetCurrentOffset(currentOffset_);
        return layoutAlgorithm;
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<SwitchPaintProperty>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<SwitchPaintMethod>(currentOffset_);
    }

    void OnModifyDone() override;

protected:
    void UpdateCurrentOffset(float offset);

private:
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    void PlayTranslateAnimation(float startPos, float endPos);
    RefPtr<Curve> GetCurve() const;
    int32_t GetDuration() const;
    void StopTranslateAnimation();
    void FireChangeEvent() const;
    void OnChange();
    float GetSwitchWidth() const;

    // Init touch event, stop animation when touch down.
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown();
    void HandleTouchUp();

    RefPtr<Animator> controller_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<CurveAnimation<double>> translate_;
    SizeF contentSize_;
    bool isOn_ = false;
    float currentOffset_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(SwitchPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWITCH_SWITCH_PATTERN_H