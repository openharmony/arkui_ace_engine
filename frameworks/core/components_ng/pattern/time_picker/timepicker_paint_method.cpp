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

#include "core/components_ng/pattern/time_picker/timepicker_paint_method.h"

#include "core/components/common/properties/color.h"

namespace OHOS::Ace::NG {

namespace {

constexpr float DIVIDER_LINE_WIDTH = 2.0f;

} // namespace

CanvasDrawFunction TimePickerPaintMethod::GetForegroundDrawFunction(PaintWrapper* /*paintWrapper*/)
{
    return [dividerLineWidth = DIVIDER_LINE_WIDTH, dividerSpacingWidth = dividerSpacingWidth_,
               gradientHeight = gradientHeight_, dividerHeight = dividerHeight_](RSCanvas& canvas) {
        DividerPainter dividerPainter(dividerLineWidth, dividerSpacingWidth, false, Color::GRAY, LineCap::SQUARE);
        OffsetF offset = OffsetF(0.0f, gradientHeight);
        dividerPainter.DrawLine(canvas, offset);
        OffsetF offsetY = OffsetF(0.0f, dividerHeight);
        dividerPainter.DrawLine(canvas, offsetY);
    };
}
} // namespace OHOS::Ace::NG