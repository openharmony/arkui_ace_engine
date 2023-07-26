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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_PATTERN_H

#include "base/geometry/axis.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/patternlock/patternlock_event_hub.h"
#include "core/components_ng/pattern/patternlock/patternlock_layout_algorithm.h"
#include "core/components_ng/pattern/patternlock/patternlock_layout_property.h"
#include "core/components_ng/pattern/patternlock/patternlock_modifier.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_method.h"
#include "core/components_ng/pattern/patternlock/patternlock_paint_property.h"
#include "core/components_v2/pattern_lock/pattern_lock_controller.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class PatternLockPattern : public Pattern {
    DECLARE_ACE_TYPE(PatternLockPattern, Pattern);

public:
    PatternLockPattern() = default;
    ~PatternLockPattern() override = default;

    bool IsAtomicNode() const override
    {
        return true;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<PatternLockLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<PatternLockPaintProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<PatternLockLayoutAlgorithm>(sideLength_);
        return layoutAlgorithm;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!patternLockModifier_) {
            patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
        }
        auto paintMethod =
            MakeRefPtr<PatternLockPaintMethod>(cellCenter_, isMoveEventValid_, choosePoint_, patternLockModifier_);
        return paintMethod;
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override
    {
        return true;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<PatternLockEventHub>();
    }

    const RefPtr<V2::PatternLockController>& GetPatternLockController()
    {
        return patternLockController_;
    }

    void SetPatternLockController(const RefPtr<V2::PatternLockController>& patternLockController)
    {
        patternLockController_ = patternLockController;
    }

private:
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;

    void InitTouchEvent(RefPtr<GestureEventHub>& gestureHub, RefPtr<TouchEventImpl>& touchDownListener);
    void InitPatternLockController();
    void HandleTouchEvent(const TouchEventInfo& info);
    void OnTouchDown(const TouchEventInfo& info);
    void OnTouchUp();
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleGestureUpdate(const GestureEvent& info);

    bool CheckChoosePoint(int32_t x, int32_t y) const;
    bool AddChoosePoint(const OffsetF& offset, int32_t x, int32_t y);
    void AddPassPoint(int32_t x, int32_t y);
    void HandleReset();
    bool CheckAutoReset() const;

    RefPtr<V2::PatternLockController> patternLockController_;
    RefPtr<TouchEventImpl> touchDownListener_;
    RefPtr<TouchEventImpl> touchUpListener_;
    RefPtr<TouchEventImpl> touchMoveListener_;
    RefPtr<PanEvent> panEvent_;

    bool isMoveEventValid_ = false;
    std::vector<PatternLockCell> choosePoint_;
    int32_t passPointCount_ = 0;
    OffsetF cellCenter_;

    mutable bool autoReset_ = true;
    Dimension sideLength_ = 300.0_vp;
    Dimension circleRadius_ = 14.0_vp;

    RefPtr<PatternLockModifier> patternLockModifier_;

    ACE_DISALLOW_COPY_AND_MOVE(PatternLockPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_PATTERN_H
