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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_select_ffi.h"

#include "cj_lambda.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {

NG::SelectModelNG* GetSelectModel()
{
    static NG::SelectModelNG* model = nullptr;
    if (model == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Select");
        if (module == nullptr) {
            LOGF_ABORT("Can't find select dynamic module");
        }
        model = reinterpret_cast<NG::SelectModelNG*>(module->GetModel());
    }
    return model;
}
} // namespace OHOS::Ace

namespace {
const std::vector<TextDirection> TEXT_DIRECTIONS = { TextDirection::LTR, TextDirection::RTL, TextDirection::AUTO };
}

extern "C" {
VectorNativeSelectOptionHandle FFICJCreateVectorNativeSelectOption(int64_t size)
{
    LOGI("Create NativeSelectOption Vector");
    return new std::vector<NativeSelectOption>(size);
}

void FFICJVectorNativeSelectOptionSetElement(
    VectorNativeSelectOptionHandle vec, int64_t index, NativeSelectOption selectOption)
{
    LOGI("NativeSelectOption Vector Set Element");
    auto actualVec = reinterpret_cast<std::vector<NativeSelectOption>*>(vec);
    (*actualVec)[index] = selectOption;
    LOGI("NativeSelectOption Vector Set Element Success");
}

void FFICJVectorNativeSelectOptionDelete(VectorNativeSelectOptionHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeSelectOption>*>(vec);
    delete actualVec;
}

void FfiOHOSAceFrameworkSelectCreate(VectorStringPtr vecContent)
{
    auto nativeSelectOptionVec = *reinterpret_cast<std::vector<NativeSelectOption>*>(vecContent);
    std::vector<SelectParam> params(nativeSelectOptionVec.size());
    for (size_t i = 0; i < nativeSelectOptionVec.size(); i++) {
        params[i] = { nativeSelectOptionVec[i].value, nativeSelectOptionVec[i].icon };
    }
    GetSelectModel()->Create(params);
}

void FfiOHOSAceFrameworkSelectSetSelected(int32_t value)
{
    GetSelectModel()->SetSelected(value);
}

void FfiOHOSAceFrameworkSelectSetValue(const char* value)
{
    GetSelectModel()->SetValue(value);
}

void FfiOHOSAceFrameworkSelectSetControlSize(int32_t value)
{
    ControlSize size = ControlSize::NORMAL;
    if (value >= static_cast<int32_t>(ControlSize::SMALL) && value <= static_cast<int32_t>(ControlSize::NORMAL)) {
        size = static_cast<ControlSize>(value);
    }
    GetSelectModel()->SetControlSize(size);
}

void FfiOHOSAceFrameworkSelectSetDivider(DividerParams params)
{
    Dimension widthDime(params.width, static_cast<DimensionUnit>(params.widthUnit));
    Dimension startMarginDime(params.startMargin, static_cast<DimensionUnit>(params.startMarginUnit));
    Dimension endMarginDime(params.endMargin, static_cast<DimensionUnit>(params.endMarginUnit));

    NG::SelectDivider divider;
    divider.strokeWidth = widthDime;
    divider.color = Color(params.color);
    divider.startMargin = startMarginDime;
    divider.endMargin = endMarginDime;

    GetSelectModel()->SetDivider(divider);
}

void FfiOHOSAceFrameworkSelectSetFont(
    int32_t style, const char* weight, double size, int32_t sizeUnit, const char* family)
{
    GetSelectModel()->SetFontSize(Dimension(size, static_cast<DimensionUnit>(sizeUnit)));
    GetSelectModel()->SetFontWeight(ConvertStrToFontWeight(weight));
    GetSelectModel()->SetFontFamily(ConvertStrToFontFamilies(family));
    GetSelectModel()->SetItalicFontStyle(static_cast<FontStyle>(style));
}

void FfiOHOSAceFrameworkSelectSetFontColor(uint32_t color)
{
    GetSelectModel()->SetFontColor(Color(color));
}

void FfiOHOSAceFrameworkSelectResetFontColor()
{
    GetSelectModel()->ResetFontColor();
}

void FfiOHOSAceFrameworkSelectSetSelectedOptionBgColor(uint32_t color)
{
    GetSelectModel()->SetSelectedOptionBgColor(Color(color));
}

// reset select SelectedOptionBgColor from SelectTheme
void FfiOHOSAceFrameworkSelectResetSelectedOptionBgColor()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    Color bgColor = theme->GetSelectedColor();
    GetSelectModel()->SetSelectedOptionBgColor(bgColor);
}

void FfiOHOSAceFrameworkSelectSetSelectedOptionFont(
    int32_t style, const char* weight, double size, int32_t sizeUnit, const char* family)
{
    GetSelectModel()->SetSelectedOptionFontSize(Dimension(size, static_cast<DimensionUnit>(sizeUnit)));
    GetSelectModel()->SetSelectedOptionFontWeight(ConvertStrToFontWeight(weight));
    GetSelectModel()->SetSelectedOptionFontFamily(ConvertStrToFontFamilies(family));
    GetSelectModel()->SetSelectedOptionItalicFontStyle(static_cast<FontStyle>(style));
}

void FfiOHOSAceFrameworkSelectSetSelectedOptionFontColor(uint32_t color)
{
    GetSelectModel()->SetSelectedOptionFontColor(Color(color));
}

void FfiOHOSAceFrameworkSelectResetSelectedOptionFontColor()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    Color textColor = theme->GetSelectedColorText();
    GetSelectModel()->SetSelectedOptionFontColor(textColor);
}

void FfiOHOSAceFrameworkSelectSetOptionBgColor(uint32_t color)
{
    GetSelectModel()->SetOptionBgColor(Color(color));
}

void FfiOHOSAceFrameworkSelectSetOptionFont(
    int32_t style, const char* weight, double size, int32_t sizeUnit, const char* family)
{
    GetSelectModel()->SetOptionFontSize(Dimension(size, static_cast<DimensionUnit>(sizeUnit)));
    GetSelectModel()->SetOptionFontWeight(ConvertStrToFontWeight(weight));
    GetSelectModel()->SetOptionFontFamily(ConvertStrToFontFamilies(family));
    GetSelectModel()->SetOptionItalicFontStyle(static_cast<FontStyle>(style));
}

void FfiOHOSAceFrameworkSelectSetOptionFontColor(uint32_t color)
{
    GetSelectModel()->SetOptionFontColor(Color(color));
}

void FfiOHOSAceFrameworkSelectResetOptionFontColor()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    Color textColor = theme->GetMenuFontColor();
    GetSelectModel()->SetOptionFontColor(textColor);
}

void FfiOHOSAceFrameworkSelectSetSpace(double width, int32_t widthUnit)
{
    Dimension dimStrokeWidth(width, static_cast<DimensionUnit>(widthUnit));
    GetSelectModel()->SetSpace(dimStrokeWidth);
}

void FfiOHOSAceFrameworkSelectSetArrowPosition(int32_t value)
{
    if (static_cast<ArrowPosition>(value) != ArrowPosition::START &&
        static_cast<ArrowPosition>(value) != ArrowPosition::END) {
        value = 0;
    }
    GetSelectModel()->SetArrowPosition(static_cast<ArrowPosition>(value));
}

void FfiOHOSAceFrameworkSelectSetMenuAlign(int32_t value, double dx, int32_t dxUnit, double dy, int32_t dyUnit)
{
    Dimension dimensionX(dx, static_cast<DimensionUnit>(dxUnit));
    Dimension dimensionY(dy, static_cast<DimensionUnit>(dyUnit));

    MenuAlign menuAlignObj;
    menuAlignObj.alignType = static_cast<MenuAlignType>(value);
    menuAlignObj.offset = DimensionOffset(dimensionX, dimensionY);
    GetSelectModel()->SetMenuAlign(menuAlignObj);
}

void FfiOHOSAceFrameworkSelectSetOptionWidth(double width, int32_t widthUnit)
{
    GetSelectModel()->SetHasOptionWidth(true);
    Dimension dimStrokeWidth(width, static_cast<DimensionUnit>(widthUnit));
    GetSelectModel()->SetOptionWidth(dimStrokeWidth);
}

void FfiOHOSAceFrameworkSelectResetOptionWidth()
{
    CalcDimension value;
    GetSelectModel()->SetHasOptionWidth(false);
    GetSelectModel()->SetOptionWidth(value);
}

void FfiOHOSAceFrameworkSelectSetOptionWidthWithMode(const char* value)
{
    GetSelectModel()->SetHasOptionWidth(true);
    std::string modeFlag(value);
    if (modeFlag.compare("fit_content") == 0) {
        GetSelectModel()->SetOptionWidthFitTrigger(false);
    } else if (modeFlag.compare("fit_trigger") == 0) {
        GetSelectModel()->SetOptionWidthFitTrigger(true);
    } else {
        LOGE("OptionWidth is null or undefined");
        GetSelectModel()->SetHasOptionWidth(false);
        CalcDimension dimension;
        GetSelectModel()->SetOptionWidth(dimension);
    }
}

void FfiOHOSAceFrameworkSelectSetOptionHeight(double height, int32_t heightUnit)
{
    Dimension dimStrokeWidth(height, static_cast<DimensionUnit>(heightUnit));
    GetSelectModel()->SetOptionHeight(dimStrokeWidth);
}

void FfiOHOSAceFrameworkSelectSetMenuBackgroundColor(uint32_t color)
{
    GetSelectModel()->SetMenuBackgroundColor(Color(color));
}

void FfiOHOSAceFrameworkSelectSetMenuBackgroundBlurStyle(int32_t value)
{
    BlurStyleOption styleOption;
    if (value >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
        value <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        styleOption.blurStyle = static_cast<BlurStyle>(value);
        GetSelectModel()->SetMenuBackgroundBlurStyle(styleOption);
    }
}

void FfiOHOSAceFrameworkSelectSetBackgroundColor(uint32_t color)
{
    GetSelectModel()->BackgroundColor(Color(color));
}

void FfiOHOSAceFrameworkSelectSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    Dimension widthValue(width, static_cast<DimensionUnit>(widthUnit));
    Dimension heightValue(height, static_cast<DimensionUnit>(heightUnit));
    ViewAbstractModel::GetInstance()->SetWidth(widthValue);
    ViewAbstractModel::GetInstance()->SetHeight(heightValue);
}

void FfiOHOSAceFrameworkSelectSetPadding(double padding, uint32_t unit)
{
    Dimension value(padding, static_cast<DimensionUnit>(unit));
    NG::ViewAbstract::SetPadding(NG::CalcLength(value));
}

void FfiOHOSAceFrameworkSelectSetDirection(int32_t value)
{
    TextDirection direction = TextDirection::AUTO;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWENTY_THREE)) {
        if (Utils::CheckParamsValid(value, TEXT_DIRECTIONS.size())) {
            direction = TEXT_DIRECTIONS[value];
        }
    } else {
        if (value >= static_cast<int32_t>(TextDirection::LTR) &&
            value <= static_cast<int32_t>(TextDirection::AUTO)) {
            direction = static_cast<TextDirection>(value);
        }
    }
    GetSelectModel()->SetLayoutDirection(direction);
}

void FfiOHOSAceFrameworkSelectOnSelect(void (*callback)(int32_t index, const char* value))
{
    auto onSelect = [lambda = CJLambda::Create(callback)](
                        int32_t index, const std::string& value) -> void { lambda(index, value.c_str()); };
    GetSelectModel()->SetOnSelect(std::move(onSelect));
}
}
