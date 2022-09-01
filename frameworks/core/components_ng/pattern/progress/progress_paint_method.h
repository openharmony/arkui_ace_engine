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

#include "base/geometry/ng/offset_t.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ProgressPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ProgressPaintMethod, NodePaintMethod)
public:
    explicit ProgressPaintMethod(double maxValue, double value, std::optional<SizeF> constrainSize)
        : maxValue_(maxValue), value_(value), constrainSize_(constrainSize)
    {}
    ~ProgressPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(maxValue_, nullptr);
        CHECK_NULL_RETURN(value_, nullptr);
        auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
        auto offset = paintWrapper->GetContentOffset();
        offset = offset+OffsetT<float>(0,constrainSize_->Height()/2);
        // auto paint = Paint::Create();
        PointF start = PointF(offset.GetX()+value_, offset.GetY()+5);
        PointF end = PointF(offset.GetX() + frameSize.Width()-value_, offset.GetY()+5);
        PointF end2 = PointF(offset.GetX() + frameSize.Width()*value_/maxValue_, offset.GetY()+5);
        LOGI("print_progress:  frameSize.Width():%{public}f frameSize.Height():%{public}f value:%{public}f", frameSize.Width(),
            frameSize.Height(), value_);
        LOGI("print_progress:  constrainSize_.Width():%{public}f frameSize.Height():%{public}f", constrainSize_->Width(),
            constrainSize_->Height());
        LOGI("print_progress:  offset.GetX():%{public}f offset.GetY():%{public}f", offset.GetX(),
            offset.GetY());
        return [frameSize, start, end, end2](RSCanvas& canvas) {
            RSPen pen;
            pen.SetAntiAlias(true);
            pen.SetWidth(10);
            pen.SetCapStyle(ToRSCapStyle(LineCap::ROUND));
            pen.SetColor(ToRSColor((Color::GRAY)));
            canvas.AttachPen(pen);
            canvas.DrawLine(ToRSPonit(end2), ToRSPonit(end));
            pen.SetColor(ToRSColor((Color::RED)));
            canvas.AttachPen(pen);
            canvas.DrawLine(ToRSPonit(start), ToRSPonit(end2));
        };
    }

private:
    float maxValue_;
    float value_;
    std::optional<SizeF> constrainSize_;
    ACE_DISALLOW_COPY_AND_MOVE(ProgressPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_PROGRESS_PAINT_METHOD_H
