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
    SwiperIndicatorPaintMethod(float mainDelta, Axis axis, int32_t currentIndex, int32_t itemCount, bool showIndicator)
        : mainDelta_(mainDelta), axis_(axis), currentIndex_(currentIndex), itemCount_(itemCount),
          showIndicator_(showIndicator) {};
    ~SwiperIndicatorPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

    void CanvasDrawIndicator(RSCanvas& canvas, const Offset& offset);

    void InitIndicatorStyle();

    void SetIndicator(const RefPtr<OHOS::Ace::SwiperIndicator>& indicator)
    {
        indicator_ = indicator;
    }

    RefPtr<OHOS::Ace::SwiperIndicator> GetIndicator() const
    {
        return indicator_;
    }

    void SetCurrentIndex(int32_t index)
    {
        currentIndex_ = index;
    }

    int32_t GetCurrentIndex() const
    {
        return currentIndex_;
    }

protected:
    struct IndicatorProperties final {
        IndicatorProperties(const Offset& normalPaddingStart, const Offset& normalPaddingEnd,
            const Offset& selectedPaddingStart, const Offset& selectedPaddingEnd, const Offset& centerPadding,
            uint32_t normalColor, uint32_t selectedColor, double normalPointRadius, double selectedPointRadius,
            double indicatorPointPadding)
            : normalPaddingStart(normalPaddingStart), normalPaddingEnd(normalPaddingEnd),
              selectedPaddingStart(selectedPaddingStart), selectedPaddingEnd(selectedPaddingEnd),
              centerPadding(centerPadding), normalColor(normalColor), selectedColor(selectedColor),
              normalPointRadius(normalPointRadius), selectedPointRadius(selectedPointRadius),
              indicatorPointPadding(indicatorPointPadding)
        {}
        IndicatorProperties(IndicatorProperties&& indicatorProperties) = default;
        ~IndicatorProperties() = default;

        Offset normalPaddingStart;
        Offset normalPaddingEnd;
        Offset selectedPaddingStart;
        Offset selectedPaddingEnd;
        Offset centerPadding;
        uint32_t normalColor;
        uint32_t selectedColor;
        double normalPointRadius;
        double selectedPointRadius;
        double indicatorPointPadding;
    };

    struct IndicatorPaintData {
        double width = 0.0;
        double height = 0.0;
        double radius = 0.0;
        Color color;
        Offset position;
        Offset center;
    };

    struct SwiperIndicatorData {
        bool isDigital = false;
        bool isPressed = false;
        bool isHovered = false;
        IndicatorPaintData indicatorPaintData;
        std::unordered_map<int32_t, IndicatorPaintData> indicatorItemData;
        double pointPadding = 0.0;
        double startEndPadding = 0.0;
    };

private:
    void PaintContent(
        RSCanvas& canvas, RefPtr<SwiperIndicatorPaintProperty> paintProperty, SizeF contentSize, OffsetF contentOffset);
    IndicatorProperties PrepareIndicatorProperties(RefPtr<SwiperIndicatorPaintProperty> paintProperty);
    void PaintMask(
        RSCanvas& canvas, RefPtr<SwiperIndicatorPaintProperty> paintProperty, SizeF contentSize, OffsetF contentOffset);
    float mainDelta_ = 0.0f;
    const float radiusGap_ = 2.0f;
    double scale_ = 0.0;
    Axis axis_ = Axis::HORIZONTAL;
    RefPtr<OHOS::Ace::SwiperIndicator> indicator_;
    double swiperWidth_ = 0.0;
    double swiperHeight_ = 0.0;
    Offset indicatorPosition_;
    int32_t currentIndex_ = 0;
    int32_t itemCount_ = 1;
    bool showIndicator_ = true;

    ACE_DISALLOW_COPY_AND_MOVE(SwiperIndicatorPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_PAINT_METHOD_H