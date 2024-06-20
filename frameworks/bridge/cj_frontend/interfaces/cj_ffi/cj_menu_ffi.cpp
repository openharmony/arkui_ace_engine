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

#include "cj_menu_ffi.h"

#include "bridge/declarative_frontend/jsview/models/menu_model_impl.h"
#include "bridge/common/utils/utils.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkMenuCreate()
{
    MenuModel::GetInstance()->Create();
}

void FfiOHOSAceFrameworkMenuFont(double size, int32_t unit, const char* weight,
    const char* family, int32_t style)
{
    MenuModel::GetInstance()->SetFontStyle(static_cast<FontStyle>(style));

    std::string familyVal = family;
    auto fontFamilies = ConvertStrToFontFamilies(familyVal);
    MenuModel::GetInstance()->SetFontFamily(fontFamilies);

    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    MenuModel::GetInstance()->SetFontSize(fontSize);

    std::string weightVal = weight;
    MenuModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(weightVal));
}

void FfiOHOSAceFrameworkMenuSetFontColor(uint32_t color)
{
    std::optional<Color> colorVal = Color(color);
    MenuModel::GetInstance()->SetFontColor(colorVal);
}

void FfiOHOSAceFrameworkMenuSetWidth(double width, int32_t unit)
{
    CalcDimension widthVal = CalcDimension(width, DimensionUnit(unit));
    MenuModel::GetInstance()->SetWidth(widthVal);
}

void FfiOHOSAceFrameworkMenuSetRadiusByLength(double size, int32_t unit)
{
    CalcDimension radius = CalcDimension(size, DimensionUnit(unit));
    MenuModel::GetInstance()->SetBorderRadius(radius);
}

void FfiOHOSAceFrameworkMenuSetRadiusByBorderRadiuses(CBorderRadiuses radius)
{
    std::optional<CalcDimension> radiusTopLeft = CalcDimension(radius.topLeftRadiuses,
        DimensionUnit(radius.topLeftUnit));
    std::optional<CalcDimension> radiusTopRight = CalcDimension(radius.topRightRadiuses,
        DimensionUnit(radius.topRightUnit));
    std::optional<CalcDimension> radiusBottomLeft = CalcDimension(radius.bottomLeftRadiuses,
        DimensionUnit(radius.bottomLeftUnit));
    std::optional<CalcDimension> radiusBottomRight = CalcDimension(radius.bottomRightRadiuses,
        DimensionUnit(radius.bottomRightUnit));
    MenuModel::GetInstance()->SetBorderRadius(radiusTopLeft, radiusTopRight, radiusBottomLeft, radiusBottomRight);
}
}