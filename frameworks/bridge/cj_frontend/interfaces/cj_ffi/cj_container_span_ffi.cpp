/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "cj_container_span_ffi.h"
#include "core/components_ng/pattern/text/span_model.h"
#include "core/components_ng/pattern/text/span_model_ng.h"

using namespace OHOS::Ace::Framework;
using namespace OHOS::Ace;

TextBackgroundStyle ParseContainerSpanTextBackgroundStyle(uint32_t color, double radiusDouble, int32_t unit)
{
    TextBackgroundStyle textBackgroundStyle;
    Color colorVal = Color(color);
    Dimension value(radiusDouble, static_cast<DimensionUnit>(unit));
    CalcDimension radius = CalcDimension(value);
    if (radius.Unit() == DimensionUnit::PERCENT) {
        radius.Reset();
    }
    textBackgroundStyle.backgroundColor = colorVal;
    textBackgroundStyle.backgroundRadius = { radius, radius, radius, radius };
    textBackgroundStyle.backgroundRadius->multiValued = false;
    return textBackgroundStyle;
}

TextBackgroundStyle ParseContainerSpanTextBackgroundStyle(uint32_t color, CBorderRadiuses radiusValue)
{
    TextBackgroundStyle textBackgroundStyle;
    Color colorVal = Color(color);
    Dimension topLeftValue(radiusValue.topLeftRadiuses,
        static_cast<DimensionUnit>(radiusValue.topLeftUnit));
    CalcDimension topLeft = CalcDimension(topLeftValue);
    Dimension topRightValue(radiusValue.topRightRadiuses,
        static_cast<DimensionUnit>(radiusValue.topRightUnit));
    CalcDimension topRight = CalcDimension(topRightValue);
    Dimension bottomLeftValue(radiusValue.bottomLeftRadiuses,
        static_cast<DimensionUnit>(radiusValue.bottomLeftUnit));
    CalcDimension bottomLeft = CalcDimension(bottomLeftValue);
    Dimension bottomRightValue(radiusValue.bottomRightRadiuses,
        static_cast<DimensionUnit>(radiusValue.bottomRightUnit));
    CalcDimension bottomRight = CalcDimension(bottomRightValue);
    textBackgroundStyle.backgroundColor = colorVal;
    textBackgroundStyle.backgroundRadius = { topLeft, topRight, bottomRight, bottomLeft };
    textBackgroundStyle.backgroundRadius->multiValued = false;
    return textBackgroundStyle;
}

extern "C" {
void FfiOHOSAceFrameworkContainerSpanCreate()
{
    SpanModel::GetInstance()->CreateContainSpan();
}

void FfiOHOSAceFrameworkContainerSpanSetTextBackgroundStyle(uint32_t color, double radius, int32_t unit)
{
    TextBackgroundStyle textBackgroundStyle = ParseContainerSpanTextBackgroundStyle(color, radius, unit);
    SpanModel::GetInstance()->SetTextBackgroundStyle(textBackgroundStyle);
}

void FfiOHOSAceFrameworkContainerSpanSetTextBackgroundStyleBorder(uint32_t color, CBorderRadiuses radius)
{
    TextBackgroundStyle textBackgroundStyle = ParseContainerSpanTextBackgroundStyle(color, radius);
    SpanModel::GetInstance()->SetTextBackgroundStyle(textBackgroundStyle);
}
}
