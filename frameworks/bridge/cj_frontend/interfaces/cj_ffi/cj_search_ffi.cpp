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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_search_ffi.h"

#include "cj_lambda.h"

#include "bridge/cj_frontend/cppview/search_controller.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/search/search_model.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<FontStyle> FONT_STYLE = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<BorderStyle> BORDER_STYLES = { BorderStyle::SOLID, BorderStyle::DASHED, BorderStyle::DOTTED };
const std::vector<CopyOptions> COPY_OPTION = {
    CopyOptions::None,
    CopyOptions::InApp,
    CopyOptions::Local,
    CopyOptions::Distributed,
};

void handleFont(double fontSize,
    int32_t sizeUnit,
    const char* fontWeight,
    int32_t fontStyle,
    const char* fontFamily,
    Font& font)
{
    Dimension fontSizeDim(fontSize, static_cast<DimensionUnit>(sizeUnit));
    font.fontSize = fontSizeDim;
    font.fontWeight = ConvertStrToFontWeight(fontWeight);
    font.fontFamilies = ConvertStrToFontFamilies(fontFamily);
    font.fontStyle = FONT_STYLE[fontStyle];
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkSearchCreateByIconID(SearchCreateParam value)
{
    std::string iconUrl = "";
    std::optional<std::string> key = value.value;
    std::optional<std::string> tip = value.placeholder;
    std::optional<std::string> src = iconUrl;
    if (!ParseCjMedia(value.iconID, static_cast<ResourceType>(value.iconType), value.iconParams, iconUrl)) {
        LOGI("icon url not found");
    }
    if (value.controllerID == -1) {
        SearchModel::GetInstance()->Create(key, tip, src);
    } else {
        auto self_ = FFIData::GetData<SearchController>(value.controllerID);
        if (self_ != nullptr) {
                auto controller = SearchModel::GetInstance()->Create(key, tip, src);
                self_->SetController(controller);
        } else {
            LOGE("invalid scrollerID");
        }
    }
    std::string bundleName;
    std::string moduleName;
    SearchModel::GetInstance()->SetSearchSrcPath(iconUrl, bundleName, moduleName);
}

void FfiOHOSAceFrameworkSearchSetSearchButton(const char* text)
{
    SearchModel::GetInstance()->SetSearchButton(text);
}

void FfiOHOSAceFrameworkSearchSetPlaceholderColor(uint32_t color)
{
    SearchModel::GetInstance()->SetPlaceholderColor(Color(color));
}

void FfiOHOSAceFrameworkSearchSetPlaceholderFont(
    double fontSize, int32_t sizeUnit, const char* fontWeight, int32_t fontStyle, const char* fontFamily)
{
    if (!Utils::CheckParamsValid(fontStyle, FONT_STYLE.size())) {
        LOGE("invalid value for fontStyle");
        return;
    }
    Font font;
    handleFont(fontSize, sizeUnit, fontWeight, fontStyle, fontFamily, font);
    SearchModel::GetInstance()->SetPlaceholderFont(font);
}

void FfiOHOSAceFrameworkSearchSetTextFont(
    double fontSize, int32_t sizeUnit, const char* fontWeight, int32_t fontStyle, const char* fontFamily)
{
    if (!Utils::CheckParamsValid(fontStyle, FONT_STYLE.size())) {
        LOGE("invalid value for fontStyle");
        return;
    }
    Font font;
    handleFont(fontSize, sizeUnit, fontWeight, fontStyle, fontFamily, font);
    SearchModel::GetInstance()->SetTextFont(font);
}

void FfiOHOSAceFrameworkSearchSetBorder(SearchSetBorder value)
{
    if (!Utils::CheckParamsValid(value.style, BORDER_STYLES.size())) {
        LOGE("invalid value for style");
        return;
    }
    FfiOHOSAceFrameworkViewAbstractSetBorder(CJBorder({
        value.width, value.widthUnit, value.color, value.radius, value.radiusUnit, value.style }));
    SearchModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkSearchSetBorderWidth(double width, int32_t widthUnit)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderWidth(width, widthUnit);
    SearchModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkSearchSetBorderColor(uint32_t color)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderColor(color);
    SearchModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkSearchSetBorderStyle(int32_t style)
{
    if (!Utils::CheckParamsValid(style, BORDER_STYLES.size())) {
        LOGE("invalid value for style");
        return;
    }
    FfiOHOSAceFrameworkViewAbstractSetBorderStyle(style);
    SearchModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkSearchSetBorderRadius(double radius, int32_t radiusUnit)
{
    FfiOHOSAceFrameworkViewAbstractSetBorderRadius(radius, radiusUnit);
    SearchModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkSearchSetHeight(double height, int32_t heightUnit)
{
    Dimension heightDim(height, static_cast<DimensionUnit>(heightUnit));
    NG::ViewAbstract::SetHeight(NG::CalcLength(heightDim));
    if (LessNotEqual(heightDim.Value(), 0.0)) {
        heightDim.SetValue(0.0);
    }
    SearchModel::GetInstance()->SetHeight(heightDim);
}

void FfiOHOSAceFrameworkSearchSetCopyOption(int32_t copyOption)
{
    if (!Utils::CheckParamsValid(copyOption, COPY_OPTION.size())) {
        LOGE("invalid value for style");
        return;
    }
    SearchModel::GetInstance()->SetCopyOption(COPY_OPTION[copyOption]);
}

void FfiOHOSAceFrameworkSearchOnSubmit(void (*callback)(const char* value))
{
    auto onSubmit = [lambda = CJLambda::Create(callback)](const std::string& value) -> void { lambda(value.c_str()); };
    SearchModel::GetInstance()->SetOnSubmit(std::move(onSubmit));
}

void FfiOHOSAceFrameworkSearchOnChange(void (*callback)(const char* value))
{
    auto onChange = [lambda = CJLambda::Create(callback)](const std::string& value,
        PreviewText& previewText) -> void { lambda(value.c_str()); };
    SearchModel::GetInstance()->SetOnChange(std::move(onChange));
}

void FfiOHOSAceFrameworkSearchOnCopy(void (*callback)(const char* value))
{
    auto onCopy = [lambda = CJLambda::Create(callback)](const std::string& value) -> void { lambda(value.c_str()); };
    SearchModel::GetInstance()->SetOnCopy(std::move(onCopy));
}

void FfiOHOSAceFrameworkSearchOnCut(void (*callback)(const char* value))
{
    auto onCut = [lambda = CJLambda::Create(callback)](const std::string& value) -> void { lambda(value.c_str()); };
    SearchModel::GetInstance()->SetOnCut(std::move(onCut));
}

void FfiOHOSAceFrameworkSearchOnPaste(void (*callback)(const char* value))
{
    auto onPaste = [lambda = CJLambda::Create(callback)](const std::string& val, NG::TextCommonEvent& info) -> void {
        LOGI("OnPaste called.");
        lambda(val.c_str());
    };
    SearchModel::GetInstance()->SetOnPasteWithEvent(std::move(onPaste));
}

int64_t FfiOHOSAceFrameworkSearchController()
{
    auto ret_ = FFIData::Create<SearchController>();
    if (ret_ == nullptr) {
        return FFI_ERROR_CODE;
    }
    return ret_->GetID();
}

void FfiOHOSAceFrameworkSearchCaretPosition(int64_t selfID, int32_t carePosition)
{
    auto self_ = FFIData::GetData<SearchController>(selfID);
    if (self_ != nullptr) {
        self_->CaretPosition(carePosition);
    } else {
        LOGE("invalid SearchControllerID");
    }
}
}
