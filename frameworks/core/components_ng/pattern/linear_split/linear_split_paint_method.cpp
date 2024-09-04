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

#include "core/components_ng/pattern/linear_split/linear_split_paint_method.h"

#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {

namespace {

constexpr uint32_t LINEAR_SPLIT_COLOR = 0xFF707B7C;

} // namespace

CanvasDrawFunction LinearSplitPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this)](RSCanvas& canvas) {
        auto linearSplit_ = weak.Upgrade();
        CHECK_NULL_VOID(linearSplit_);
        linearSplit_->PaintContent(canvas);
    };

    return paintFunc;
}

void LinearSplitPaintMethod::PaintContent(RSCanvas& canvas)
{
    RSPen pen;
    pen.SetColor(ToRSColor(Color(LINEAR_SPLIT_COLOR)));
    pen.SetAntiAlias(true);
    pen.SetWidth(static_cast<float>(DEFAULT_SPLIT_HEIGHT));
    canvas.AttachPen(pen);
    if (splitType_ == SplitType::ROW_SPLIT) {
        for (auto childOffset : childrenOffset_) {
            float startPointX = childOffset.GetX() + static_cast<float>(DEFAULT_SPLIT_HEIGHT) / 2;
            float startPointY = childOffset.GetY();
            float endPointX = startPointX;
            float endPointY = startPointY + splitLength_;
            canvas.DrawLine(ToRSPoint(PointF(startPointX, startPointY)), ToRSPoint(PointF(endPointX, endPointY)));
        }
    } else if (splitType_ == SplitType::COLUMN_SPLIT) {
        for (auto childOffset : childrenOffset_) {
            float startPointY = childOffset.GetY() + static_cast<float>(DEFAULT_SPLIT_HEIGHT) / 2;
            float startPointX = childOffset.GetX();
            float endPointX = startPointX + splitLength_;
            float endPointY = startPointY;
            canvas.DrawLine(ToRSPoint(PointF(startPointX, startPointY)), ToRSPoint(PointF(endPointX, endPointY)));
        }
    }
    canvas.DetachPen();
}

} // namespace OHOS::Ace::NG
