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
#include "core/components_ng/pattern/blank/blank_paint_method.h"

#include "frameworks/core/components_ng/pattern/blank/blank_paint_property.h"

namespace OHOS::Ace::NG {
namespace {} // namespace

void BlankPaintMethod::PaintRect(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<BlankPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto color = paintProperty->GetColor().value_or(Color::TRANSPARENT);
    auto layoutSize = paintWrapper->GetContentSize();
    auto offset = paintWrapper->GetContentOffset();
    canvas.Save();
    RSBrush brush;
    brush.SetColor(color.GetValue());
    canvas.AttachBrush(brush);
    // extra 1px for pixel round
    canvas.DrawRect(RSRect(offset.GetX(), offset.GetY(), layoutSize.Width() + offset.GetX() + 1,
        layoutSize.Height() + offset.GetY() + 1));
    canvas.DetachBrush();
    canvas.Restore();
}
} // namespace OHOS::Ace::NG
