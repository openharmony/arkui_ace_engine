/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H

#include <optional>

#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
class SwiperIndicatorModifier : public ContentModifier {
    DECLARE_ACE_TYPE(SwiperIndicatorModifier, ContentModifier);

public:
    SwiperIndicatorModifier()
        : vectorBlackPointCenterX_(AceType::MakeRefPtr<AnimatablePropertyVectorFloat>(LinearVector<float>(0))),
          longPointLeftCenterX_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          longPointRightCenterX_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          centerY_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          pointRadius_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          hoverPointRadius_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0))
    {
        AttachProperty(vectorBlackPointCenterX_);
        AttachProperty(longPointLeftCenterX_);
        AttachProperty(longPointRightCenterX_);
        AttachProperty(centerY_);
        AttachProperty(pointRadius_);
        AttachProperty(hoverPointRadius_);
    }
    ~SwiperIndicatorModifier() override = default;

    struct ContentProperty {
        LinearVector<float> vectorBlackPointCenterX;
        float longPointLeftCenterX = 0;
        float longPointRightCenterX = 0;
        float centerY = 0;
        float pointRadius = 0;
        float hoverPointRadius = 0;
    };

    void onDraw(DrawingContext& context) override;

    void PaintContent(DrawingContext& context, ContentProperty& contentProperty);
    void PaintUnselectedIndicator(RSCanvas& canvas, const OffsetF& center, float radius);
    void PaintSelectedIndicator(RSCanvas& canvas, const OffsetF& leftCenter, const OffsetF& rightCenter, float radius);
    bool isHoverPoint(const OffsetF& leftCenter, const OffsetF& rightCenter, float radius);
    void PaintMask(DrawingContext& context);

    void UpdateVectorBlackPointCenterX(const LinearVector<float>& vectorBlackPointCenterX);
    void UpdateLongPointLeftCenterX(float longPointLeftCenterX, bool isAnimation);
    void UpdateLongPointRightCenterX(float longPointRightCenterX, bool isAnimation);
    void UpdateCenterY(float centerY);
    void UpdatePointRadius(float pointRadius);
    void UpdateHoverPointRadius(float startHoverPointRadius, float endHoverPointRadius);

    void SetAxis(Axis axis)
    {
        axis_ = axis;
    }

    void SetUnselectedColor(const Color& unselectedColor)
    {
        unselectedColor_ = unselectedColor;
    }

    void SetSelectedColor(const Color& selectedColor)
    {
        selectedColor_ = selectedColor;
    }

    void SetHoverPoint(const PointF& hoverPoint)
    {
        hoverPoint_ = hoverPoint;
    }

    void SetIndicatorMask(bool indicatorMask)
    {
        indicatorMask_ = indicatorMask;
    }

    void SetOffset(const OffsetF& offset)
    {
        offset_ = offset;
    }

private:
    RefPtr<AnimatablePropertyVectorFloat> vectorBlackPointCenterX_;
    RefPtr<AnimatablePropertyFloat> longPointLeftCenterX_;
    RefPtr<AnimatablePropertyFloat> longPointRightCenterX_;
    RefPtr<AnimatablePropertyFloat> centerY_;
    RefPtr<AnimatablePropertyFloat> pointRadius_;
    RefPtr<AnimatablePropertyFloat> hoverPointRadius_;

    Axis axis_ = Axis::HORIZONTAL;
    Color unselectedColor_ = Color::TRANSPARENT;
    Color selectedColor_ = Color::TRANSPARENT;
    std::optional<PointF> hoverPoint_ = std::nullopt;
    bool indicatorMask_ = false;
    OffsetF offset_;
    ACE_DISALLOW_COPY_AND_MOVE(SwiperIndicatorModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H
