/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FONT_CONSTANTS_CONVERTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FONT_CONSTANTS_CONVERTER_H

#include "rosen_text/typography_types.h"
#include "SkColor.h"
#include "symbol_constants.h"
#include "symbol_gradient.h"

#include "core/components/common/properties/text_style.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Rosen {
enum class FontWeight;
enum class FontStyle;
enum class TextAlign;
enum class TextRectHeightStyle;
enum class TextRectWidthStyle;
enum class TextBaseline;
enum class TextDirection;
enum class PlaceholderVerticalAlignment;
enum class TextDecorationStyle;
struct TextStyle;
struct PlaceholderSpan;
enum class SymbolType;

namespace Drawing {
class RectF;
} // namespace Drawing
} // namespace OHOS::Rosen

namespace OHOS::Ace {

enum class FontWeight;
enum class FontStyle;
enum class TextBaseline;
enum class TextAlign;
enum class TextRectHeightStyle;
enum class TextRectWidthStyle;
enum class TextDirection;
enum class TextDecoration;
enum class TextDecorationStyle;
enum class WhiteSpace;
class Color;
enum class SymbolType;

namespace Constants {

OHOS::Rosen::FontWeight ConvertTxtFontWeight(FontWeight fontWeight);

OHOS::Rosen::SymbolType ConvertTxtSymbolType(SymbolType symbolType);

OHOS::Rosen::FontStyle ConvertTxtFontStyle(FontStyle fontStyle);

OHOS::Rosen::TextBaseline ConvertTxtTextBaseline(TextBaseline textBaseline);

OHOS::Rosen::TextAlign ConvertTxtTextAlign(TextAlign textAlign);

Rosen::TextVerticalAlign ConvertTxtTextVerticalAlign(TextVerticalAlign textVerticalAlign);

OHOS::Rosen::TextRectHeightStyle ConvertTxtRectHeightStyle(RectHeightStyle heightStyle);

OHOS::Rosen::TextRectWidthStyle ConvertTxtRectWidthStyle(RectWidthStyle widthStyle);

OHOS::Rosen::TextDirection ConvertTxtTextDirection(TextDirection textDirection);

OHOS::Rosen::TextDecoration ConvertTxtTextDecoration(std::vector<TextDecoration>& textDecoration);

OHOS::Rosen::TextDecorationStyle ConvertTxtTextDecorationStyle(TextDecorationStyle textDecorationStyle);

void ConvertTxtStyle(const TextStyle &textStyle,
    const WeakPtr<PipelineBase> &context, OHOS::Rosen::TextStyle &txtStyle);
void ConvertTxtStyle(const TextStyle& textStyle, OHOS::Rosen::TextStyle& txtStyle);

void ConvertSymbolTxtStyle(const TextStyle& textStyle, OHOS::Rosen::TextStyle& txtStyle);

Rect ConvertSkRect(const Rosen::Drawing::RectF &skRect);

OHOS::Rosen::PlaceholderVerticalAlignment ConvertPlaceholderAlignment(PlaceholderAlignment textDecoration);

void ConvertPlaceholderRun(const PlaceholderRun& span, OHOS::Rosen::PlaceholderSpan& txtSpan);

SkColor ConvertSkColor(Color color);
void ConvertForegroundPaint(const TextStyle& textStyle, double width, double height, Rosen::TextStyle& txtStyle);
float GetVariableFontWeight(FontWeight fontWeight);
std::vector<Rosen::Drawing::ColorQuad> ConvertColors(const std::vector<Color>& colors);
std::shared_ptr<Rosen::SymbolGradient> CreateNativeGradient(const SymbolGradient& grad);
std::optional<Rosen::SymbolShadow> ConvertToNativeSymbolShadow(const SymbolShadow& shadow);
} // namespace Constants

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FONT_CONSTANTS_CONVERTER_H
