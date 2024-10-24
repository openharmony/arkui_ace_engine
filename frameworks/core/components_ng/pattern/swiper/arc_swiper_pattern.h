/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_ARC_SWIPER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_ARC_SWIPER_PATTERN_H

#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {
class ArcSwiperPattern : public SwiperPattern {
    DECLARE_ACE_TYPE(ArcSwiperPattern, SwiperPattern);
public:
    void SaveCircleDotIndicatorProperty(const RefPtr<FrameNode>& indicatorNode) override;
    void SetSwiperArcDotParameters(const SwiperArcDotParameters& swiperArcDotParameters) override;
    std::string GetArcDotIndicatorStyle() const override;
    std::shared_ptr<SwiperArcDotParameters> GetSwiperArcDotParameters() const override;

#ifdef SUPPORT_DIGITAL_CROWN
    void SetDigitalCrownSensitivity(CrownSensitivity sensitivity) override;
    void InitOnCrownEventInternal(const RefPtr<FocusHub>& focusHub) override;
    bool IsCrownSpring() const override;
    void SetIsCrownSpring(bool isCrownSpring) override;
    void HandleCrownEvent(const CrownEvent& event, const OffsetF& center, const OffsetF& offset);
#endif
private:
    std::string GradientToJson(Gradient colors) const;
    mutable std::shared_ptr<SwiperArcDotParameters> swiperArcDotParameters_;
#ifdef SUPPORT_DIGITAL_CROWN
    void HandleCrownActionBegin(double degree, double mainDelta, GestureEvent& info);
    void HandleCrownActionUpdate(double degree, double mainDelta, GestureEvent& info, const OffsetF& offset);
    void HandleCrownActionEnd(double degree, double mainDelta, GestureEvent& info, const OffsetF& offset);
    void HandleCrownActionCancel();
    double GetCrownRotatePx(const CrownEvent& event) const;
    void UpdateCrownVelocity(double degree, double mainDelta, bool isEnd = false);
#endif

#ifdef SUPPORT_DIGITAL_CROWN
    CrownSensitivity crownSensitivity_ = CrownSensitivity::MEDIUM;
    Offset accumulativeCrownPx_;
    bool isCrownSpring_ = false;
    double crownVelocity_ = 0.0;
    double crownTurnVelocity_ = 0.0;
    bool isHandleCrownActionEnd_ = false;
#endif
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_ARC_SWIPER_PATTERN_H