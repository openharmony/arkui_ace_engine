/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_ARC_SWIPER_INDICATOR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_ARC_SWIPER_INDICATOR_PATTERN_H

#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
namespace OHOS::Ace::NG {
class ArcSwiperIndicatorPattern : public SwiperIndicatorPattern {
DECLARE_ACE_TYPE(ArcSwiperIndicatorPattern, SwiperIndicatorPattern);
public:
    ArcSwiperIndicatorPattern() = default;
    ~ArcSwiperIndicatorPattern() override = default;

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<CircleDotIndicatorPaintProperty>();
    }
    bool SetArcIndicatorHotRegion(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    PointF GetCenterPointF() override;
    float GetAngleWithPoint(const PointF& conter, const PointF& point) override;
    void InitAccessibilityFocusEvent() override;
    void SetAccessibilityFocusd(bool isAccessibilityFocusd)
    {
        isAccessibilityFocusd_ = isAccessibilityFocusd;
    }

private:
    bool CalculateArcIndicatorHotRegion(const RectF& frameRect, const OffsetF& contentOffset);
    float ConvertAngleWithArcDirection(SwiperArcDirection arcDirection, const float& angle);
    bool isAccessibilityFocusd_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_ARC_SWIPER_INDICATOR_PATTERN_H