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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_alphabet_indexer_ffi.h"

#include "cj_lambda.h"
#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/indexer/indexer_model.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<V2::AlignStyle> ALIGN_STYLE_ = { V2::AlignStyle::LEFT, V2::AlignStyle::RIGHT };
const std::vector<NG::AlignStyle> NG_ALIGN_STYLE_ = { NG::AlignStyle::LEFT, NG::AlignStyle::RIGHT };
}; // namespace

// Should use CJUIModifier API later
NG::IndexerModelNG* GetIndexerModel()
{
    static NG::IndexerModelNG* model = nullptr;
    if (model == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Indexer");
        if (module == nullptr) {
            LOGF("Can't find Indexer module");
            abort();
        }
        model = reinterpret_cast<NG::IndexerModelNG*>(module->GetModel());
    }
    return model;
}

extern "C" {
void FfiOHOSAceFrameworkAlphabetIndexerAutoCollapse(bool autoCollapse)
{
    GetIndexerModel()->SetAutoCollapse(autoCollapse);
}
void FfiOHOSAceFrameworkAlphabetIndexerCreate(VectorStringPtr vecContent, int32_t selected)
{
    auto actualVec = reinterpret_cast<std::vector<std::string>*>(vecContent);
    GetIndexerModel()->Create(*actualVec, selected);
}
void FfiOHOSAceFrameworkAlphabetIndexerColor(int32_t color)
{
    GetIndexerModel()->SetColor(Color(color));
}
void FfiOHOSAceFrameworkAlphabetIndexerSelectedColor(int32_t color)
{
    GetIndexerModel()->SetSelectedColor(Color(color));
}
void FfiOHOSAceFrameworkAlphabetIndexerPopupColor(int32_t color)
{
    GetIndexerModel()->SetPopupColor(Color(color));
}
void FfiOHOSAceFrameworkAlphabetIndexerSelectedBackgroundColor(int32_t color)
{
    GetIndexerModel()->SetSelectedBackgroundColor(Color(color));
}
void FfiOHOSAceFrameworkAlphabetIndexerPopupBackground(int32_t color)
{
    GetIndexerModel()->SetPopupBackground(Color(color));
}
void FfiOHOSAceFrameworkAlphabetIndexerPopupTitleBackground(int32_t color)
{
    GetIndexerModel()->SetPopupTitleBackground(Color(color));
}
void FfiOHOSAceFrameworkAlphabetIndexerPopupItemBackground(int32_t color)
{
    GetIndexerModel()->SetPopupItemBackground(Color(color));
}
void FfiOHOSAceFrameworkAlphabetIndexerPopupUnselectedColor(int32_t color)
{
    GetIndexerModel()->SetPopupUnselectedColor(Color(color));
}
void FfiOHOSAceFrameworkAlphabetIndexerPopupSelectedColor(int32_t color)
{
    GetIndexerModel()->SetPopupSelectedColor(Color(color));
}
void FfiOHOSAceFrameworkAlphabetIndexerUsingPopup(bool usingPop)
{
    GetIndexerModel()->SetUsingPopup(usingPop);
}
void FfiOHOSAceFrameworkAlphabetIndexerPopupBackgroundBlurStyle(int32_t indexerBlurStyle)
{
    BlurStyleOption styleOption;
    if (indexerBlurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
        indexerBlurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        styleOption.blurStyle = static_cast<BlurStyle>(indexerBlurStyle);
    }
    GetIndexerModel()->SetPopupBackgroundBlurStyle(styleOption);
}
void FfiOHOSAceFrameworkAlphabetIndexerSelectedFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style)
{
    std::optional<Dimension> fontSize = Dimension(size, DimensionUnit(unit));
    std::string weightVal = weight;
    std::optional<FontWeight> fontWeight = ConvertStrToFontWeight(weightVal);
    std::optional<std::vector<std::string>> fontFamily = std::vector<std::string> { family };
    std::optional<FontStyle> fontStyle = static_cast<FontStyle>(style);
    GetIndexerModel()->SetSelectedFont(fontSize, fontWeight, fontFamily, fontStyle);
}
void FfiOHOSAceFrameworkAlphabetIndexerPopupFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style)
{
    std::optional<Dimension> fontSize = Dimension(size, DimensionUnit(unit));
    std::string weightVal = weight;
    std::optional<FontWeight> fontWeight = ConvertStrToFontWeight(weightVal);
    std::optional<std::vector<std::string>> fontFamily = std::vector<std::string> { family };
    std::optional<FontStyle> fontStyle = static_cast<FontStyle>(style);
    GetIndexerModel()->SetPopupFont(fontSize, fontWeight, fontFamily, fontStyle);
}
void FfiOHOSAceFrameworkAlphabetIndexerFont(
    double size, int32_t unit, const char* weight, const char* family, int32_t style)
{
    std::optional<Dimension> fontSize = Dimension(size, DimensionUnit(unit));
    std::string weightVal = weight;
    std::optional<FontWeight> fontWeight = ConvertStrToFontWeight(weightVal);
    std::optional<std::vector<std::string>> fontFamily = std::vector<std::string> { family };
    std::optional<FontStyle> fontStyle = static_cast<FontStyle>(style);
    GetIndexerModel()->SetFont(fontSize, fontWeight, fontFamily, fontStyle);
}
void FfiOHOSAceFrameworkAlphabetIndexerPopupItemFont(double size, int32_t unit, const char* weight)
{
    Dimension fontSize(size, static_cast<DimensionUnit>(unit));
    std::string weightVal = weight;
    GetIndexerModel()->SetFontSize(fontSize);
    GetIndexerModel()->SetFontWeight(ConvertStrToFontWeight(weightVal));
}
void FfiOHOSAceFrameworkAlphabetIndexerItemSize(double size, int32_t unit)
{
    GetIndexerModel()->SetItemSize(Dimension(size, static_cast<DimensionUnit>(unit)));
}
void FfiOHOSAceFrameworkAlphabetIndexerAlignStyle(int32_t alignStyle)
{
    if (alignStyle >= 0 && alignStyle < static_cast<int32_t>(ALIGN_STYLE_.size())) {
        GetIndexerModel()->SetAlignStyle(static_cast<int32_t>(NG_ALIGN_STYLE_[alignStyle]));
    }
}
void FfiOHOSAceFrameworkAlphabetIndexerSelected(int32_t selected)
{
    GetIndexerModel()->SetSelected(selected);
}
void FfiOHOSAceFrameworkAlphabetIndexerPopupPosition(double x, double y)
{
    GetIndexerModel()->SetPopupPositionX(Dimension(x));
    GetIndexerModel()->SetPopupPositionY(Dimension(y));
}
void FfiOHOSAceFrameworkAlphabetIndexerPopupPositionWithUnit(double x, int32_t xUnit, double y, int32_t yUnit)
{
    GetIndexerModel()->SetPopupPositionX(Dimension(x, static_cast<DimensionUnit>(xUnit)));
    GetIndexerModel()->SetPopupPositionY(Dimension(y, static_cast<DimensionUnit>(yUnit)));
}
void FfiOHOSAceFrameworkAlphabetIndexerOnSelected(void (*callback)(int32_t idx))
{
    auto onSelected = [ffiCallback = CJLambda::Create(callback)](int64_t idx) { ffiCallback(idx); };
    GetIndexerModel()->SetOnSelected(std::move(onSelected));
}
void FfiOHOSAceFrameworkAlphabetIndexerOnRequestPopupData(VectorStringHandle (*callback)(int32_t idx))
{
    auto onRequestPopupData = [ffiCallback = CJLambda::Create(callback)](int64_t idx) {
        auto callbackRes = ffiCallback(idx);
        auto resPtr = reinterpret_cast<std::vector<std::string>*>(callbackRes);
        auto result = *resPtr;
        FFICJCommonVectorStringDelete(callbackRes);
        return result;
    };
    GetIndexerModel()->SetOnRequestPopupData(std::move(onRequestPopupData));
}
void FfiOHOSAceFrameworkAlphabetIndexerOnPopupSelected(void (*callback)(int32_t idx))
{
    auto onSelected = [ffiCallback = CJLambda::Create(callback)](int64_t idx) { ffiCallback(idx); };
    GetIndexerModel()->SetOnPopupSelected(std::move(onSelected));
}
void FfiOHOSAceFrameworkAlphabetIndexerItemBorderRadius(double radius)
{
    GetIndexerModel()->SetItemBorderRadius(Dimension(radius));
}
void FfiOHOSAceFrameworkAlphabetIndexerPopupItemBorderRadius(double radius)
{
    GetIndexerModel()->SetPopupItemBorderRadius(Dimension(radius));
}
void FfiOHOSAceFrameworkAlphabetIndexerEnableHapticFeedback(bool state)
{
    GetIndexerModel()->SetEnableHapticFeedback(state);
}
}
