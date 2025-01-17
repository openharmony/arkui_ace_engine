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

#ifndef USE_GRAPHIC_TEXT_GINE
#include "txt/placeholder_run.h"
#include "txt/text_baseline.h"
#include "txt/text_decoration.h"
#include "txt/text_style.h"
#include "include/core/SkColor.h"
#else
#include "rosen_text/typography_types.h"
#include "third_party/skia/include/core/SkColor.h"
#endif

#include "core/components/common/properties/text_style.h"
#include "core/pipeline/pipeline_base.h"

#ifndef USE_GRAPHIC_TEXT_GINE
namespace txt {
enum class FontWeight;
enum class FontStyle;
enum class TextAlign;
enum class RectHeightStyle;
enum class RectWidthStyle;
enum class TextDirection;
enum class TextDecorationStyle;
} // namespace txt
#else
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

namespace Drawing {
class RectF;
} // namespace Drawing
} // namespace OHOS::Rosen
#endif

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

namespace Constants {

#ifndef USE_GRAPHIC_TEXT_GINE
txt::FontWeight ConvertTxtFontWeight(FontWeight fontWeight);

txt::FontStyle ConvertTxtFontStyle(FontStyle fontStyle);

txt::TextBaseline ConvertTxtTextBaseline(TextBaseline textBaseline);

txt::TextAlign ConvertTxtTextAlign(TextAlign textAlign);

txt::Paragraph::RectHeightStyle ConvertTxtRectHeightStyle(RectHeightStyle heightStyle);

txt::Paragraph::RectWidthStyle ConvertTxtRectWidthStyle(RectWidthStyle widthStyle);

txt::TextDirection ConvertTxtTextDirection(TextDirection textDirection);

txt::TextDecoration ConvertTxtTextDecoration(TextDecoration textDecoration);

txt::TextDecorationStyle ConvertTxtTextDecorationStyle(TextDecorationStyle textDecorationStyle);

void ConvertTxtStyle(const TextStyle& textStyle, const WeakPtr<PipelineBase>& context, txt::TextStyle& txtStyle);

void ConvertTxtStyle(const TextStyle& textStyle, txt::TextStyle& txtStyle);

void ConvertSymbolTxtStyle(const TextStyle& textStyle, txt::TextStyle& txtStyle);

Rect ConvertSkRect(SkRect skRect);

txt::PlaceholderAlignment ConvertPlaceholderAlignment(PlaceholderAlignment textDecoration);

void ConvertPlaceholderRun(const PlaceholderRun& span, txt::PlaceholderRun& txtSpan);

#else
OHOS::Rosen::FontWeight ConvertTxtFontWeight(FontWeight fontWeight);

OHOS::Rosen::FontStyle ConvertTxtFontStyle(FontStyle fontStyle);

OHOS::Rosen::TextBaseline ConvertTxtTextBaseline(TextBaseline textBaseline);

OHOS::Rosen::TextAlign ConvertTxtTextAlign(TextAlign textAlign);

OHOS::Rosen::TextRectHeightStyle ConvertTxtRectHeightStyle(RectHeightStyle heightStyle);

OHOS::Rosen::TextRectWidthStyle ConvertTxtRectWidthStyle(RectWidthStyle widthStyle);

OHOS::Rosen::TextDirection ConvertTxtTextDirection(TextDirection textDirection);

OHOS::Rosen::TextDecoration ConvertTxtTextDecoration(TextDecoration textDecoration);

OHOS::Rosen::TextDecorationStyle ConvertTxtTextDecorationStyle(TextDecorationStyle textDecorationStyle);

void ConvertTxtStyle(const TextStyle &textStyle,
    const WeakPtr<PipelineBase> &context, OHOS::Rosen::TextStyle &txtStyle);
void ConvertTxtStyle(const TextStyle& textStyle, OHOS::Rosen::TextStyle& txtStyle);

void ConvertSymbolTxtStyle(const TextStyle& textStyle, OHOS::Rosen::TextStyle& txtStyle);

Rect ConvertSkRect(const Rosen::Drawing::RectF &skRect);

OHOS::Rosen::PlaceholderVerticalAlignment ConvertPlaceholderAlignment(PlaceholderAlignment textDecoration);

void ConvertPlaceholderRun(const PlaceholderRun& span, OHOS::Rosen::PlaceholderSpan& txtSpan);
#endif

SkColor ConvertSkColor(Color color);

} // namespace Constants

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FONT_CONSTANTS_CONVERTER_H
