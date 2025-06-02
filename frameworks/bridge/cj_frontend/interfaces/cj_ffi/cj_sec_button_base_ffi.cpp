/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_sec_button_base_ffi.h"
#include "ffi_remote_data.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components/common/layout/constants.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/security_component/security_component_model_ng.h"
#include "base/geometry/dimension.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;
using namespace OHOS::Ace::NG;

namespace {
    const std::vector<BorderStyle> BORDER_STYLES = {BorderStyle::SOLID, BorderStyle::DASHED, BorderStyle::DOTTED};
    const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = {OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC};
}

extern "C" {
void FfiOHOSAceFrameworkSecButtonBasePop()
{
    ViewStackModel::GetInstance()->Pop();
}

void FfiOHOSAceFrameWorkSecButtonBaseSetWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstractModel::GetInstance()->SetWidth(value);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetHeight(double height, int32_t unit)
{
    Dimension value(height, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstractModel::GetInstance()->SetHeight(value);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    Dimension widthDime(width, static_cast<DimensionUnit>(widthUnit));
    Dimension heightDime(height, static_cast<DimensionUnit>(heightUnit));
    if (LessNotEqual(widthDime.Value(), 0.0)) {
        widthDime.SetValue(0.0);
    }
    if (LessNotEqual(heightDime.Value(), 0.0)) {
        heightDime.SetValue(0.0);
    }
    ViewAbstractModel::GetInstance()->SetWidth(widthDime);
    ViewAbstractModel::GetInstance()->SetHeight(heightDime);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundColor(uint32_t color)
{
    SecurityComponentModelNG::SetBackgroundColor(Color(color));
}

void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundBorderRadius(double radius, int32_t unit)
{
    Dimension value(radius, static_cast<DimensionUnit>(unit));
    SecurityComponentModelNG::SetBackgroundBorderRadius(value);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetPosition(double x, int32_t xUnit, double y, int32_t yUnit)
{
    Dimension dx(x, static_cast<DimensionUnit>(xUnit));
    Dimension dy(y, static_cast<DimensionUnit>(yUnit));
    ViewAbstractModel::GetInstance()->SetPosition(dx, dy);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetConstraintSize(CJConstraintSize value)
{
    Dimension minWidthDime(value.minWidth, static_cast<DimensionUnit>(value.minWidthUnit));
    Dimension maxWidthDime(value.maxWidth, static_cast<DimensionUnit>(value.maxWidthUnit));
    Dimension minHeightDime(value.minHeight, static_cast<DimensionUnit>(value.minHeightUnit));
    Dimension maxHeightDime(value.maxHeight, static_cast<DimensionUnit>(value.maxHeightUnit));

    ViewAbstractModel::GetInstance()->SetMinWidth(minWidthDime);
    ViewAbstractModel::GetInstance()->SetMaxWidth(maxWidthDime);
    ViewAbstractModel::GetInstance()->SetMinHeight(minHeightDime);
    ViewAbstractModel::GetInstance()->SetMaxHeight(maxHeightDime);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundBorderWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    SecurityComponentModelNG::SetBackgroundBorderWidth(value);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundBorderColor(uint32_t color)
{
    SecurityComponentModelNG::SetBackgroundBorderColor(Color(color));
}

void FfiOHOSAceFrameWorkSecButtonBaseSetOffset(double x, int32_t xUnit, double y, int32_t yUnit)
{
    Dimension dx(x, static_cast<DimensionUnit>(xUnit));
    Dimension dy(y, static_cast<DimensionUnit>(yUnit));
    ViewAbstractModel::GetInstance()->SetOffset(dx, dy);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetFontColor(uint32_t color)
{
    SecurityComponentModelNG::SetFontColor(Color(color));
}

void FfiOHOSAceFrameWorkSecButtonBaseSetFontSize(double fontSize, int32_t unit)
{
    Dimension value(fontSize, static_cast<DimensionUnit>(unit));
    SecurityComponentModelNG::SetFontSize(value);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundBorderStyle(int32_t style)
{
    if (!Utils::CheckParamsValid(style, BORDER_STYLES.size())) {
        LOGE("invaild value for border style");
        return;
    }
    SecurityComponentModelNG::SetBackgroundBorderStyle(BORDER_STYLES[style]);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetIconSize(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    SecurityComponentModelNG::SetIconSize(value);
}

void FfiOHOSAceFrameWorkSecButtonBaseMarkAnchor(double x, int32_t xUnit, double y, int32_t yUnit)
{
    Dimension dx(x, static_cast<DimensionUnit>(xUnit));
    Dimension dy(y, static_cast<DimensionUnit>(yUnit));
    ViewAbstractModel::GetInstance()->MarkAnchor(dx, dy);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetIconColor(uint32_t color)
{
    SecurityComponentModelNG::SetIconColor(Color(color));
}

void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundPadding(double padding, int32_t unit)
{
    Dimension value(padding, static_cast<DimensionUnit>(unit));
    SecurityComponentModelNG::SetBackgroundPadding(value);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetBackgroundPaddings(CJEdge params)
{
    Dimension topDime(params.top, static_cast<DimensionUnit>(params.topUnit));
    Dimension rightDime(params.right, static_cast<DimensionUnit>(params.rightUnit));
    Dimension bottomDime(params.bottom, static_cast<DimensionUnit>(params.bottomUnit));
    Dimension leftDime(params.left, static_cast<DimensionUnit>(params.leftUnit));
    SecurityComponentModelNG::SetBackgroundPadding(topDime, rightDime, bottomDime, leftDime);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetFontWeight(const char* value)
{
    SecurityComponentModelNG::SetFontWeight(ConvertStrToFontWeight(value));
}

void FfiOHOSAceFrameWorkSecButtonBaseSetTextIconSpace(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    SecurityComponentModelNG::SetTextIconSpace(value);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetFontFamily(const char* fontFamily)
{
    std::vector<std::string> fontFamilies;
    fontFamilies = ConvertStrToFontFamilies(fontFamily);
    SecurityComponentModelNG::SetFontFamily(fontFamilies);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetFontStyle(int32_t fontstyle)
{
    if (!Utils::CheckParamsValid(fontstyle, FONT_STYLES.size())) {
        LOGE("invaild value for font style");
        return;
    }
    SecurityComponentModelNG::SetFontStyle(FONT_STYLES[fontstyle]);
}

void FfiOHOSAceFrameWorkSecButtonBaseSetLayoutDirection(int32_t value)
{
    SecurityComponentModelNG::SetTextIconLayoutDirection(static_cast<SecurityComponentLayoutDirection>(value));
}
}