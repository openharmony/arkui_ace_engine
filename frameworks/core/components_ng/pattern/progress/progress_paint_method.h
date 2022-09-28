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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_PAINT_METHOD_H

#include <optional>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/pattern/progress/progress_view.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ProgressPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ProgressPaintMethod, NodePaintMethod)
public:
    ProgressPaintMethod(ProgressType progressType, float strokeWidth)
        : strokeWidth_(strokeWidth), progressType_(progressType)
    {}
    ~ProgressPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override
    {
        auto frameSize = paintWrapper->GetContentSize();
        auto offset = paintWrapper->GetContentOffset();
        auto paintProperty = DynamicCast<ProgressPaintProperty>(paintWrapper->GetPaintProperty());
        GetThemeDate();
        if (paintProperty) {
            color_ = paintProperty->GetColor().value_or(color_);
            bgColor_ = paintProperty->GetBackgroundColor().value_or(bgColor_);
            maxValue_ = paintProperty->GetMaxValue().value_or(maxValue_);
            value_ = paintProperty->GetValue().value_or(value_);
            scaleCount_ = paintProperty->GetScaleCount().value_or(scaleCount_);
            scaleWidth_ = paintProperty->GetScaleWidth().value_or(Dimension(scaleWidth_)).ConvertToPx();
        }
        if (progressType_ == ProgressType::LINEAR) {
            return [frameSize, offset, this](RSCanvas& canvas) { PaintLinear(canvas, offset, frameSize); };
        }
        if (progressType_ == ProgressType::RING) {
            return [frameSize, offset, this](RSCanvas& canvas) { PaintRing(canvas, offset, frameSize); };
        }
        if (progressType_ == ProgressType::SCALE) {
            return [frameSize, offset, this](RSCanvas& canvas) { PaintScaleRing(canvas, offset, frameSize); };
        }
        if (progressType_ == ProgressType::MOON) {
            return [frameSize, offset, this](RSCanvas& canvas) { PaintMoon(canvas, offset, frameSize); };
        }
        if (progressType_ == ProgressType::CAPSULE) {
            if (frameSize.Width() >= frameSize.Height()) {
                return [frameSize, offset, this](RSCanvas& canvas) { PaintCapsule(canvas, offset, frameSize); };
            }
            return [frameSize, offset, this](RSCanvas& canvas) { PaintVerticalCapsule(canvas, offset, frameSize); };
        }
        return [frameSize, offset, this](RSCanvas& canvas) { PaintLinear(canvas, offset, frameSize); };
    }

    void GetThemeDate();
    void PaintLinear(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintScaleRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintMoon(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintVerticalCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;

private:
    float maxValue_ = 100.0f;
    float value_ = 0.0f;
    Color color_ = Color::BLUE;
    Color bgColor_ = Color::GRAY;
    float strokeWidth_ = 2.0f;
    float scaleWidth_ = 10.0f;
    int32_t scaleCount_ = 100;
    ProgressType progressType_ = ProgressType::LINEAR;

    ACE_DISALLOW_COPY_AND_MOVE(ProgressPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_PAINT_METHOD_H
