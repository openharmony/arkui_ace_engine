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

#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/jsview/models/menu_model_impl.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
enum class SubMenuExpandingMode { SIDE = 0, EMBEDDED, STACK };
} // namespace

extern "C" {
void FfiOHOSAceFrameworkMenuCreate()
{
    MenuModel::GetInstance()->Create();
}

void FfiOHOSAceFrameworkMenuFont(double size, int32_t unit, const char* weight, const char* family, int32_t style)
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
    std::optional<CalcDimension> radiusTopLeft =
        CalcDimension(radius.topLeftRadiuses, DimensionUnit(radius.topLeftUnit));
    std::optional<CalcDimension> radiusTopRight =
        CalcDimension(radius.topRightRadiuses, DimensionUnit(radius.topRightUnit));
    std::optional<CalcDimension> radiusBottomLeft =
        CalcDimension(radius.bottomLeftRadiuses, DimensionUnit(radius.bottomLeftUnit));
    std::optional<CalcDimension> radiusBottomRight =
        CalcDimension(radius.bottomRightRadiuses, DimensionUnit(radius.bottomRightUnit));
    MenuModel::GetInstance()->SetBorderRadius(radiusTopLeft, radiusTopRight, radiusBottomLeft, radiusBottomRight);
}

void FfiOHOSAceFrameworkMenuSetItemDivider(DividerParams dividerParams, bool hasValue)
{
    V2::ItemDivider divider;
    if (hasValue) {
        divider.strokeWidth = CalcDimension(dividerParams.width, DimensionUnit(dividerParams.widthUnit));
        divider.color = Color(dividerParams.color);
        divider.startMargin = CalcDimension(dividerParams.startMargin, DimensionUnit(dividerParams.startMarginUnit));
        divider.endMargin = CalcDimension(dividerParams.endMargin, DimensionUnit(dividerParams.endMarginUnit));
        if (divider.strokeWidth.IsNegative()) {
            divider.strokeWidth.Reset();
        }
        if (divider.startMargin.IsNegative()) {
            divider.startMargin.Reset();
        }
        if (divider.endMargin.IsNegative()) {
            divider.endMargin.Reset();
        }
    }
    MenuModel::GetInstance()->SetItemDivider(divider, DividerMode::FLOATING_ABOVE_MENU);
}

void FfiOHOSAceFrameworkMenuSetItemGroupDivider(DividerParams dividerParams, bool hasValue)
{
    auto divider = V2::ItemDivider {
        .strokeWidth = Dimension(0.0f, DimensionUnit::INVALID),
        .color = Color::FOREGROUND,
    };
    if (hasValue) {
        divider.strokeWidth = CalcDimension(dividerParams.width, DimensionUnit(dividerParams.widthUnit));
        divider.color = Color(dividerParams.color);
        divider.startMargin = CalcDimension(dividerParams.startMargin, DimensionUnit(dividerParams.startMarginUnit));
        divider.endMargin = CalcDimension(dividerParams.endMargin, DimensionUnit(dividerParams.endMarginUnit));
        if (divider.strokeWidth.IsNegative() || divider.strokeWidth.Unit() < DimensionUnit::PX ||
            divider.strokeWidth.Unit() > DimensionUnit::LPX) {
            divider.strokeWidth.Reset();
            divider.strokeWidth.SetUnit(DimensionUnit::INVALID);
        }
        if (divider.startMargin.IsNegative() || divider.startMargin.Unit() < DimensionUnit::PX ||
            divider.startMargin.Unit() > DimensionUnit::LPX) {
            divider.startMargin.Reset();
            divider.startMargin.SetUnit(DimensionUnit::INVALID);
        }
        if (divider.endMargin.IsNegative() || divider.endMargin.Unit() < DimensionUnit::PX ||
            divider.endMargin.Unit() > DimensionUnit::LPX) {
            divider.endMargin.Reset();
            divider.endMargin.SetUnit(DimensionUnit::INVALID);
        }
    }
    MenuModel::GetInstance()->SetItemGroupDivider(divider, DividerMode::FLOATING_ABOVE_MENU);
}

void FfiOHOSAceFrameworkMenuSetExpandingMode(int32_t mode)
{
    auto modeVal = static_cast<SubMenuExpandingMode>(mode);
    auto expandingMode = modeVal == SubMenuExpandingMode::EMBEDDED ? NG::SubMenuExpandingMode::EMBEDDED
                         : modeVal == SubMenuExpandingMode::STACK  ? NG::SubMenuExpandingMode::STACK
                                                                   : NG::SubMenuExpandingMode::SIDE;
    MenuModel::GetInstance()->SetExpandingMode(expandingMode);
}
}