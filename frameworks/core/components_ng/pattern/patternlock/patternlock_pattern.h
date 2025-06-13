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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_PATTERN_H

#include "base/geometry/axis.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/patternlock/patternlock_challenge.h"
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
        auto layoutAlgorithm = MakeRefPtr<PatternLockLayoutAlgorithm>();
        return layoutAlgorithm;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!patternLockModifier_) {
            patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
        }
        if (!isInitVirtualNode_ && AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
            isInitVirtualNode_ = InitVirtualNode();
        }
        CalculateCellCenter();
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

    FocusPattern GetFocusPattern() const override
    {
        FocusPaintParam focusPaintParams;
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, FocusPattern());
        auto patternLockTheme = pipelineContext->GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_RETURN(patternLockTheme, FocusPattern());
        auto focusColor = patternLockTheme->GetFocusColor();
        auto focusPaintWidth = patternLockTheme->GetFocusPaintWidth();
        focusPaintParams.SetPaintWidth(Dimension(focusPaintWidth));
        focusPaintParams.SetPaintColor(focusColor);
        return { FocusType::NODE, true, FocusStyleType::CUSTOM_REGION, focusPaintParams };
    }

    void UpdateSelectedColor(const Color& color, bool isFristLoad = false);
    void UpdatePathColor(const Color& color, bool isFristLoad = false);
    void UpdateActiveColor(const Color& color, bool isFristLoad = false);
    void UpdateRegularColor(const Color& color, bool isFristLoad = false);
    void UpdateCircleRadius(const CalcDimension& radius, bool isFristLoad = false);
    void UpdateSideLength(const CalcDimension& sideLength, bool isFristLoad = false);
    void UpdateActiveCircleColor(const Color& color, bool isFristLoad = false);
private:
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;

    void InitTouchEvent(RefPtr<GestureEventHub>& gestureHub, RefPtr<TouchEventImpl>& touchDownListener);
    void InitPatternLockController();
    void InitAccessibilityHoverEvent();
    void HandleAccessibilityHoverEvent(bool state, AccessibilityHoverInfo& info);
    bool InitVirtualNode();
    RefPtr<FrameNode> AddTextNodeIntoVirtual(int32_t x, int32_t y, float handleCircleRadius);
    void HandleTextOnAccessibilityFocusCallback(int32_t x, int32_t y);
    void ModifyAccessibilityVirtualNode();
    bool GetHandleCircleRadius(float& handleCircleRadius);
    std::string ReplacePlaceHolder(const std::string& str, int32_t number);
    void UpdateAccessibilityTextNode(RefPtr<FrameNode> frameNode, float handleCircleRadius, int32_t x, int32_t y);
    void HandleTouchEvent(const TouchEventInfo& info);
    void OnTouchDown(const TouchLocationInfo& info);
    void OnTouchMove(const TouchLocationInfo& info);
    void AddPointEnd();
    void OnTouchUp();
    void HandleGestureUpdate(const GestureEvent& info);

    bool CheckChoosePoint(int32_t x, int32_t y) const;
    bool CheckInHotSpot(const OffsetF& offset, int32_t x, int32_t y);
    void UpdateDotConnectEvent();
    void AddPassPointToChoosePoint(int32_t lastCode, int32_t nowCode, std::vector<PatternLockCell> passPointVec);
    bool AddChoosePoint(const OffsetF& offset, int32_t x, int32_t y);
    void AddPassPoint(int32_t x, int32_t y);
    void HandleReset();
    void SetChallengeResult(V2::PatternLockChallengeResult challengeResult);
    bool CheckAutoReset() const;

    void InitFocusEvent();
    void HandleFocusEvent();
    void HandleBlurEvent();
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    void OnFocusClick();
    void PaintFocusState();
    void OnKeyDrapUp();
    void OnKeyDrapDown();
    void OnKeyDrapLeft();
    void OnKeyDrapRight();
    bool OnKeyEvent(const KeyEvent& event);
    void InitMouseEvent();
    void HandleHoverEvent(bool isHover);
    void HandleMouseEvent(const MouseInfo& info);
    void StartModifierConnectedAnimate(int32_t x, int32_t y);
    void StartModifierAddPassPointAnimate(int32_t x, int32_t y);
    void StartModifierCanceledAnimate();
    OffsetF GetLastChoosePointOffset();
    void CalculateCellCenter();
    OffsetF GetTouchOffsetToNode();
    void InitSkipUnselectedPoint();
    void OnColorConfigurationUpdate() override;
    RefPtr<V2::PatternLockController> patternLockController_;
    RefPtr<TouchEventImpl> touchDownListener_;
    RefPtr<TouchEventImpl> touchUpListener_;
    RefPtr<TouchEventImpl> touchMoveListener_;
    RefPtr<PanEvent> panEvent_;
    OffsetF screenTouchPoint_;
    std::vector<RefPtr<AccessibilityProperty>> accessibilityPropertyVec_;
    std::vector<RefPtr<FrameNode>> textAccessibilityNodeVec_;
    bool isInitVirtualNode_ = false;

    bool isMoveEventValid_ = false;
    bool isOnKeyEventState_ = false;
    std::vector<PatternLockCell> choosePoint_;
    int32_t passPointCount_ = 0;
    OffsetF cellCenter_;
    int32_t fingerId_ = -1;

    mutable bool autoReset_ = true;
    bool skipUnselectedPoint_ = false;
    Dimension circleRadius_;

    RefPtr<PatternLockModifier> patternLockModifier_;
    std::pair<int32_t, int32_t> currentPoint_;

    ACE_DISALLOW_COPY_AND_MOVE(PatternLockPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PATTERNLOCK_PATTERNLOCK_PATTERN_H
