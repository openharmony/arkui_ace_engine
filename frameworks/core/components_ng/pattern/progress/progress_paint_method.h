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

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/log_wrapper.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/progress/progress_view.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ProgressPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ProgressPaintMethod, NodePaintMethod)
public:
    explicit ProgressPaintMethod(double maxValue, double value, Color color, ProgressType progressType,
        double strokeWidth, double scaleWidth, int32_t scaleCount)
        : maxValue_(maxValue), value_(value), color_(color), strokeWidth_(strokeWidth), scaleWidth_(scaleWidth),
          scaleCount_(scaleCount), progressType_(progressType)
    {}
    ~ProgressPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override
    {
        auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
        auto offset = paintWrapper->GetContentOffset();
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

    void PaintLinear(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintScaleRing(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintMoon(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;
    void PaintVerticalCapsule(RSCanvas& canvas, const OffsetF& offset, const SizeF& frameSize) const;

private:
    double maxValue_;
    double value_;
    Color color_;
    double strokeWidth_;
    double scaleWidth_;
    int32_t scaleCount_;
    ProgressType progressType_;
    ACE_DISALLOW_COPY_AND_MOVE(ProgressPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_PAINT_METHOD_H
