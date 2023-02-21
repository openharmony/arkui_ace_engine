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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_CONTENT_MODIFIER_H

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/slider/slider_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
class SliderContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(SliderContentModifier, ContentModifier);

public:
    SliderContentModifier();
    ~SliderContentModifier() override = default;
    struct Parameters {
        float trackThickness = 0.0f;
        float blockDiameter = 0.0f;
        float sliderLength = 0.0f;
        float borderBlank = 0.0f;
        float stepRatio = 0.0f;
        float valueRatio = 0.0f;
        float hotCircleShadowWidth = 0.0f;
        bool hotFlag = false;
        bool mouseHoverFlag_ = false;
        bool mousePressedFlag_ = false;
    };

    struct LinePenAndSize {
        RSPen pen;
        RefPtr<AnimatablePropertyOffsetF> start;
        RefPtr<AnimatablePropertyOffsetF> end;
    };

    struct MarkerPenAndPath {
        RSPen pen;
        RSPath path;
    };

    struct CirclePenAndSize {
        RSPen pen;
        RSPen shadowPen;
        RefPtr<AnimatablePropertyOffsetF> center;
        RefPtr<PropertyFloat> radius;
        RefPtr<PropertyFloat> shadowRadius;
    };

    void onDraw(DrawingContext& context) override;

    void UpdateData(const RefPtr<SliderPaintProperty>& paintProperty, const SizeF& contentSize,
        const OffsetF& contentOffset, const RefPtr<SliderTheme>& theme);

    void GetBackgroundPen(const Parameters& parameters, const OffsetF& offset, const RefPtr<SliderTheme>& theme);
    void GetMarkerPen(const Parameters& parameters, const OffsetF& offset, const RefPtr<SliderTheme>& theme);
    void GetSelectPen(const Parameters& parameters, const OffsetF& offset, const RefPtr<SliderTheme>& theme);
    void GetCirclePen(const Parameters& parameters, const OffsetF& offset, const RefPtr<SliderTheme>& theme);

    void SetTrackThickness(float trackThickness)
    {
        if (trackThickness_) {
            trackThickness_->Set(trackThickness);
        }
    }

    void SetTrackBackgroundColor(Color color)
    {
        if (trackBackgroundColor_) {
            trackBackgroundColor_->Set(LinearColor(color));
        }
    }

    void SetSelectColor(Color color)
    {
        if (selectColor_) {
            selectColor_->Set(LinearColor(color));
        }
    }

    void SetBlockColor(Color color)
    {
        if (blockColor_) {
            blockColor_->Set(LinearColor(color));
        }
    }

    void SetBoardColor(LinearColor color, int32_t duration, const RefPtr<CubicCurve>& curve)
    {
        if (boardColor_) {
            AnimationOption option = AnimationOption();
            option.SetDuration(duration);
            option.SetCurve(curve);
            AnimationUtils::Animate(option, [&]() { boardColor_->Set(color); });
        }
    }

    // LinePenAndSize backgroundPenAndSize
    void SetBackgroundSize(const PointF& start, const PointF& end)
    {
        if (backgroundPenAndSize.start) {
            backgroundPenAndSize.start->Set(start - PointF());
        }
        if (backgroundPenAndSize.end) {
            backgroundPenAndSize.end->Set(end - PointF());
        }
    }

    // LinePenAndSize selectPenAndSize
    void SetSelectSize(const PointF& start, const PointF& end, const RefPtr<SliderTheme>& theme)
    {
        if (selectPenAndSize.start) {
            selectPenAndSize.start->Set(start - PointF());
        }
        if (selectPenAndSize.end) {
            AnimationOption option = AnimationOption();
            option.SetDuration(static_cast<int32_t>(theme->GetMoveAnimationDuration()));
            option.SetCurve(Curves::MAGNETIC);
            AnimationUtils::Animate(option, [&]() { selectPenAndSize.end->Set(end - PointF()); });
        }
    }

    // CirclePenAndSize circlePenAndSize
    void SetCircleCenter(const PointF& center, const RefPtr<SliderTheme>& theme)
    {
        if (circlePenAndSize.center) {
            AnimationOption option = AnimationOption();
            option.SetDuration(static_cast<int32_t>(theme->GetMoveAnimationDuration()));
            option.SetCurve(Curves::MAGNETIC);
            AnimationUtils::Animate(option, [&]() { circlePenAndSize.center->Set(center - PointF()); });
        }
    }

    void SetCircleRadius(float radius)
    {
        if (circlePenAndSize.radius) {
            circlePenAndSize.radius->Set(radius);
        }
    }

    void SetCircleShadowRadius(float shadowRadius)
    {
        if (circlePenAndSize.shadowRadius) {
            circlePenAndSize.shadowRadius->Set(shadowRadius);
        }
    }

private:
    // non-animatable property
    LinePenAndSize backgroundPenAndSize;
    MarkerPenAndPath markerPenAndPath;
    LinePenAndSize selectPenAndSize;
    CirclePenAndSize circlePenAndSize;
    // animatable property
    RefPtr<AnimatablePropertyFloat> trackThickness_;
    RefPtr<AnimatablePropertyColor> trackBackgroundColor_;
    RefPtr<AnimatablePropertyColor> selectColor_;
    RefPtr<AnimatablePropertyColor> blockColor_;
    RefPtr<AnimatablePropertyColor> boardColor_;
    // others
    OffsetF contentOffset_;
    SizeF contentSize_;
    Axis directionAxis_ = Axis::HORIZONTAL;
    bool reverse_ = false;
    bool isShowStep_ = false;
    // Distance between slide track and Content boundary
    float centerWidth_ = 0.0f;
    ACE_DISALLOW_COPY_AND_MOVE(SliderContentModifier);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_CONTENT_MODIFIER_H
