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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_PAINT_METHOD_H

#include "core/components/common/properties/swiper_indicator.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_modifier.h"
#include "core/components_ng/pattern/swiper_indicator/swiper_indicator_paint_property.h"
#include "core/components_ng/render/canvas.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SwiperIndicatorPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(SwiperIndicatorPaintMethod, NodePaintMethod)
public:
    explicit SwiperIndicatorPaintMethod(const RefPtr<SwiperIndicatorModifier>& swiperIndicatorModifier)
        : swiperIndicatorModifier_(swiperIndicatorModifier)
    {}
    ~SwiperIndicatorPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(swiperIndicatorModifier_, nullptr);
        return swiperIndicatorModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;
    void CalculatePointCenterX(const PaintWrapper* paintWrapper);
    void CalculatePointCenterY(const PaintWrapper* paintWrapper);
    void CalculatePointRadius(const PaintWrapper* paintWrapper);

    void SetCurrentIndex(int32_t index)
    {
        currentIndex_ = index;
    }

    void SetItemCount(int32_t itemCount)
    {
        itemCount_ = itemCount;
    }

    void SetAxis(Axis axis)
    {
        axis_ = axis;
    }

    Axis GetAxis() const
    {
        return axis_;
    }

    void SetIsHover(bool isHover)
    {
        isHover_ = isHover;
    }

    void SetIsPressed(bool isPressed)
    {
        isPressed_ = isPressed;
    }

    void SetHoverPoint(const PointF& hoverPoint)
    {
        hoverPoint_ = hoverPoint;
    }

    void SetTurnPageRate(float turnPageRate)
    {
        turnPageRate_ = turnPageRate;
    }

private:
    PointF hoverPoint_;

    RefPtr<SwiperIndicatorModifier> swiperIndicatorModifier_;
    Axis axis_ = Axis::HORIZONTAL;
    int32_t currentIndex_ = 0;
    int32_t itemCount_ = 0;
    float turnPageRate_ = 0.0f;
    bool isHover_ = false;
    bool isPressed_ = false;
    // Animatable properties for updating Modifier
    LinearVector<float> vectorBlackPointCenterX_ = {};
    float longPointLeftCenterX_ = 0.0f;
    float longPointRightCenterX_ = 0.0f;
    float centerY_ = 0.0f;
    float pointRadius_ = 0.0f;
    float hoverPointRadius_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(SwiperIndicatorPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_PAINT_METHOD_H