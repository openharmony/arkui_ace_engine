/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_UTILS_H

#include <string>
#include <vector>

#include "base/utils/linear_map.h"
#include "core/components/common/layout/align_declaration.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text_overlay/text_overlay_manager.h"

namespace OHOS::Ace::V2 {

namespace {

const char* AXIS_TYPE[] = {
    "Axis.VERTICAL",
    "Axis.HORIZONTAL",
    "Axis.FREE",
    "Axis.NONE",
};
const FontWeight FONT_WEIGHT_CONVERT_MAP[] = {
    FontWeight::W100,
    FontWeight::W200,
    FontWeight::W300,
    FontWeight::W400,
    FontWeight::W500,
    FontWeight::W600,
    FontWeight::W700,
    FontWeight::W800,
    FontWeight::W900,
    FontWeight::W700,       // FontWeight::BOLD
    FontWeight::W400,       // FontWeight::NORMAL
    FontWeight::W900,       // FontWeight::BOLDER,
    FontWeight::W100,       // FontWeight::LIGHTER
    FontWeight::W500,       // FontWeight::MEDIUM
    FontWeight::W400,       // FontWeight::REGULAR
};
} // namespace

inline std::string ConvertStackFitToString(StackFit stackFit)
{
    std::string result = "";
    switch (stackFit) {
        case StackFit::STRETCH:
            result = "StackFit.Stretch";
            break;
        case StackFit::INHERIT:
            result = "StackFit.Inherit";
            break;
        case StackFit::FIRST_CHILD:
            result = "StackFit.FirstChild";
            break;
        case StackFit::KEEP:
        default:
            result = "StackFit.Keep";
            break;
    }
    return result;
}

inline std::string ConvertOverflowToString(Overflow overflow)
{
    std::string result = "";
    switch (overflow) {
        case Overflow::CLIP:
            result = "Overflow.Clip";
            break;
        case Overflow::SCROLL:
            result = "Overflow.Scroll";
            break;
        case Overflow::FORCE_CLIP:
            result = "Overflow.ForceClip";
            break;
        case Overflow::OBSERVABLE:
        default:
            result = "Overflow.Observable";
            break;
    }
    return result;
}

inline std::string ConvertBoolToString(bool flag)
{
    return flag ? "true" : "false";
}

inline bool ConvertStringToBool(const std::string& str)
{
    if (str == "true") {
        return true;
    } else {
        return false;
    }
}

inline std::string ConvertTabBarModeToString(TabBarMode barMode)
{
    std::string result = "";
    switch (barMode) {
        case TabBarMode::SCROLLABLE:
            result = "BarMode.Scrollable";
            break;
        case TabBarMode::FIXED_START:
            result = "BarMode.FixedStart";
            break;
        case TabBarMode::FIXED:
        default:
            result = "BarMode.Fixed";
            break;
    }
    return result;
}

inline std::string ConvertBarPositionToString(BarPosition barPosition)
{
    std::string result = "";
    switch (barPosition) {
        case BarPosition::END:
            result = "BarPosition.End";
            break;
        case BarPosition::START:
        default:
            result = "BarPosition.Start";
            break;
    }
    return result;
}

inline std::string ConvertFlexDirectionToStirng(FlexDirection direction)
{
    if (direction == FlexDirection::ROW) {
        return "FlexDirection.Row";
    } else if (direction == FlexDirection::ROW_REVERSE) {
        return "FlexDirection.RowReverse";
    } else if (direction == FlexDirection::COLUMN) {
        return "FlexDirection.Column";
    } else {
        return "FlexDirection.ColumnReverse";
    }
}

inline FlexDirection ConvertStringToFlexDirection(const std::string& str)
{
    static const std::unordered_map<std::string, FlexDirection> uMap {
        { "FlexDirection.Row", FlexDirection::ROW },
        { "FlexDirection.RowReverse", FlexDirection::ROW_REVERSE },
        { "FlexDirection.Column", FlexDirection::COLUMN },
        { "FlexDirection.ColumnReverse", FlexDirection::COLUMN_REVERSE },
    };

    auto iter = uMap.find(str);
    if (iter != uMap.end()) {
        return iter->second;
    }
    return FlexDirection::ROW;
}

inline std::string ConvertWrapDirectionToStirng(WrapDirection direction)
{
    if (direction == WrapDirection::HORIZONTAL) {
        return "FlexDirection.Row";
    } else if (direction == WrapDirection::HORIZONTAL_REVERSE) {
        return "FlexDirection.RowReverse";
    } else if (direction == WrapDirection::VERTICAL) {
        return "FlexDirection.Column";
    } else {
        return "FlexDirection.ColumnReverse";
    }
}

inline std::string ConvertFlexAlignToStirng(FlexAlign align)
{
    if (align == FlexAlign::FLEX_START) {
        return "FlexAlign.Start";
    } else if (align == FlexAlign::CENTER) {
        return "FlexAlign.Center";
    } else if (align == FlexAlign::FLEX_END) {
        return "FlexAlign.End";
    } else if (align == FlexAlign::SPACE_BETWEEN) {
        return "FlexAlign.SpaceBetween";
    } else if (align == FlexAlign::SPACE_AROUND) {
        return "FlexAlign.SpaceAround";
    } else if (align == FlexAlign::BASELINE) {
        return "FlexAlign.Baseline";
    } else if (align == FlexAlign::STRETCH) {
        return "FlexAlign.Stretch";
    } else {
        return "FlexAlign.SpaceEvenly";
    }
}

inline FlexAlign ConvertStringToFlexAlign(const std::string& str)
{
    static const std::unordered_map<std::string, FlexAlign> uMap {
        { "FlexAlign.Start", FlexAlign::FLEX_START },
        { "FlexAlign.Center", FlexAlign::CENTER },
        { "FlexAlign.End", FlexAlign::FLEX_END },
        { "FlexAlign.SpaceBetween", FlexAlign::SPACE_BETWEEN },
        { "FlexAlign.SpaceAround", FlexAlign::SPACE_AROUND },
        { "FlexAlign.Baseline", FlexAlign::BASELINE },
        { "FlexAlign.Stretch", FlexAlign::STRETCH },
        { "FlexAlign.SpaceEvenly", FlexAlign::SPACE_EVENLY },
    };

    auto iter = uMap.find(str);
    if (iter != uMap.end()) {
        return iter->second;
    }
    return FlexAlign::FLEX_START;
}

inline std::string ConvertItemAlignToStirng(FlexAlign align)
{
    if (align == FlexAlign::FLEX_START) {
        return "ItemAlign.Start";
    }
    if (align == FlexAlign::CENTER) {
        return "ItemAlign.Center";
    }
    if (align == FlexAlign::FLEX_END) {
        return "ItemAlign.End";
    }
    if (align == FlexAlign::BASELINE) {
        return "ItemAlign.Baseline";
    }
    if (align == FlexAlign::STRETCH) {
        return "ItemAlign.Stretch";
    }
    return "ItemAlign.Auto";
}

inline FlexAlign ConvertStringToItemAlign(const std::string& str)
{
    static const std::unordered_map<std::string, FlexAlign> uMap {
        { "ItemAlign.Start", FlexAlign::FLEX_START },
        { "ItemAlign.Center", FlexAlign::CENTER },
        { "ItemAlign.End", FlexAlign::FLEX_END },
        { "ItemAlign.Baseline", FlexAlign::BASELINE },
        { "ItemAlign.Stretch", FlexAlign::STRETCH },
    };

    auto iter = uMap.find(str);
    if (iter != uMap.end()) {
        return iter->second;
    }
    return FlexAlign::AUTO;
}

inline std::string ConvertItemAlignToStirng(WrapAlignment align)
{
    static const LinearEnumMapNode<WrapAlignment, std::string> itemAlignTable[] = {
        { WrapAlignment::START, "ItemAlign.Start" },
        { WrapAlignment::CENTER, "ItemAlign.Center" },
        { WrapAlignment::END, "ItemAlign.End" },
        { WrapAlignment::STRETCH, "ItemAlign.Stretch" },
        { WrapAlignment::BASELINE, "ItemAlign.Baseline" },
    };

    auto index = BinarySearchFindIndex(itemAlignTable, ArraySize(itemAlignTable), align);
    return index < 0 ? "ItemAlign.Auto" : itemAlignTable[index].value;
}

inline std::string ConvertWrapAlignmentToStirng(WrapAlignment align)
{
    if (align == WrapAlignment::START) {
        return "FlexAlign.Start";
    } else if (align == WrapAlignment::CENTER) {
        return "FlexAlign.Center";
    } else if (align == WrapAlignment::END) {
        return "FlexAlign.End";
    } else if (align == WrapAlignment::SPACE_BETWEEN) {
        return "FlexAlign.SpaceBetween";
    } else if (align == WrapAlignment::SPACE_AROUND) {
        return "FlexAlign.SpaceAround";
    } else if (align == WrapAlignment::STRETCH) {
        return "FlexAlign.Stretch";
    } else if (align == WrapAlignment::BASELINE) {
        return "FlexAlign.Baseline";
    } else {
        return "FlexAlign.SpaceEvenly";
    }
}

inline std::string ConvertWrapTextDecorationToStirng(TextDecoration decoration)
{
    static const LinearEnumMapNode<TextDecoration, std::string> decorationTable[] = {
        { TextDecoration::NONE, "TextDecorationType.None" },
        { TextDecoration::UNDERLINE, "TextDecorationType.Underline" },
        { TextDecoration::OVERLINE, "TextDecorationType.Overline" },
        { TextDecoration::LINE_THROUGH, "TextDecorationType.LineThrough" },
        { TextDecoration::INHERIT, "TextDecorationType.Inherit" },
    };

    auto index = BinarySearchFindIndex(decorationTable, ArraySize(decorationTable), decoration);
    return index < 0 ? "TextDecorationType.None" : decorationTable[index].value;
}

inline std::string ConvertWrapTextDecorationToStirng(std::vector<TextDecoration> decorations)
{
    if (decorations.size() == 0) {
        return ConvertWrapTextDecorationToStirng(TextDecoration::NONE);
    }
    std::string ret = "";
    for (TextDecoration decoration: decorations) {
        ret += ConvertWrapTextDecorationToStirng(decoration) + ",";
    }
    ret.pop_back();
    return ret;
}

inline std::string ConvertWrapTextDecorationStyleToString(TextDecorationStyle decorationStyle)
{
    static const LinearEnumMapNode<TextDecorationStyle, std::string> decorationStyleTable[] = {
        { TextDecorationStyle::SOLID, "TextDecorationStyle.SOLID" },
        { TextDecorationStyle::DOUBLE, "TextDecorationStyle.DOUBLE" },
        { TextDecorationStyle::DOTTED, "TextDecorationStyle.DOTTED" },
        { TextDecorationStyle::DASHED, "TextDecorationStyle.DASHED" },
        { TextDecorationStyle::WAVY, "TextDecorationStyle.WAVY" },
    };

    auto index = BinarySearchFindIndex(decorationStyleTable, ArraySize(decorationStyleTable), decorationStyle);
    return index < 0 ? "TextDecorationStyle.SOLID" : decorationStyleTable[index].value;
}

inline std::string ConvertWrapTextCaseToStirng(TextCase textCase)
{
    static const LinearEnumMapNode<TextCase, std::string> textCaseTable[] = {
        { TextCase::NORMAL, "TextCase.Normal" },
        { TextCase::LOWERCASE, "TextCase.LowerCase" },
        { TextCase::UPPERCASE, "TextCase.UpperCase" },
    };

    auto index = BinarySearchFindIndex(textCaseTable, ArraySize(textCaseTable), textCase);
    return index < 0 ? "TextCase.Normal" : textCaseTable[index].value;
}

inline std::string ConvertWrapImageFitToString(ImageFit imageFit)
{
    static const LinearEnumMapNode<ImageFit, std::string> imageFitTable[] = {
        { ImageFit::COVER, "ImageFit.Cover" },
        { ImageFit::FILL, "ImageFit.Fill" },
        { ImageFit::CONTAIN, "ImageFit.Contain" },
        { ImageFit::FITWIDTH, "ImageFit.FitWidth" },
        { ImageFit::FITHEIGHT, "ImageFit.FitHeight" },
        { ImageFit::NONE, "ImageFit.None" },
        { ImageFit::SCALE_DOWN, "ImageFit.ScaleDown" },
    };

    auto index = BinarySearchFindIndex(imageFitTable, ArraySize(imageFitTable), imageFit);
    return index < 0 ? "ImageFit.Cover" : imageFitTable[index].value;
}

inline std::string ConvertWrapImageRepeatToString(ImageRepeat repeat)
{
    static const LinearEnumMapNode<ImageRepeat, std::string> imageRepeatTable[] = {
        { ImageRepeat::NO_REPEAT, "ImageRepeat.NoRepeat" },
        { ImageRepeat::REPEAT, "ImageRepeat.XY" },
        { ImageRepeat::REPEAT_X, "ImageRepeat.X" },
        { ImageRepeat::REPEAT_Y, "ImageRepeat.Y" },
    };

    auto index = BinarySearchFindIndex(imageRepeatTable, ArraySize(imageRepeatTable), repeat);
    return index < 0 ? "ImageRepeat.NoRepeat" : imageRepeatTable[index].value;
}

inline std::string ConvertWrapImageInterpolationToString(ImageInterpolation imageInterpolation)
{
    static const LinearEnumMapNode<ImageInterpolation, std::string> imageInterpolationTable[] = {
        { ImageInterpolation::NONE, "ImageInterpolation.None" },
        { ImageInterpolation::LOW, "ImageInterpolation.Low" },
        { ImageInterpolation::MEDIUM, "ImageInterpolation.Medium" },
        { ImageInterpolation::HIGH, "ImageInterpolation.High" },
    };

    auto index = BinarySearchFindIndex(imageInterpolationTable, ArraySize(imageInterpolationTable), imageInterpolation);
    return index < 0 ? "ImageInterpolation.None" : imageInterpolationTable[index].value;
}

inline std::string ConvertWrapImageRenderModeToString(ImageRenderMode imageRenderMode)
{
    static const LinearEnumMapNode<ImageRenderMode, std::string> imageRenderModeTable[] = {
        { ImageRenderMode::ORIGINAL, "ImageRenderMode.Original" },
        { ImageRenderMode::TEMPLATE, "ImageRenderMode.Template" },
    };

    auto index = BinarySearchFindIndex(imageRenderModeTable, ArraySize(imageRenderModeTable), imageRenderMode);
    return index < 0 ? "ImageRenderMode.Original" : imageRenderModeTable[index].value;
}

inline std::string ConvertWrapTextAlignToString(TextAlign textAlign)
{
    static const LinearEnumMapNode<TextAlign, std::string> textAlignTable[] = {
        { TextAlign::START, "TextAlign.Start" },
        { TextAlign::CENTER, "TextAlign.Center" },
        { TextAlign::END, "TextAlign.End" },
        { TextAlign::JUSTIFY, "TextAlign.Justify" },
        { TextAlign::LEFT, "TextAlign.Left" },
        { TextAlign::RIGHT, "TextAlign.Right" },
    };

    auto index = BinarySearchFindIndex(textAlignTable, ArraySize(textAlignTable), textAlign);
    return index < 0 ? "TextAlign.Start" : textAlignTable[index].value;
}

inline TextAlign ConvertWrapStringToTextAlign(const std::string& str)
{
    static const std::unordered_map<std::string, TextAlign> uMap {
        { "TextAlign.Left", TextAlign::LEFT },
        { "TextAlign.Right", TextAlign::RIGHT },
        { "TextAlign.Center", TextAlign::CENTER },
        { "TextAlign.Justify", TextAlign::JUSTIFY },
        { "TextAlign.Start", TextAlign::START },
        { "TextAlign.End", TextAlign::END },
    };

    auto iter = uMap.find(str);
    if (iter != uMap.end()) {
        return iter->second;
    }
    return TextAlign::START;
}

inline std::string ConvertWrapTextOverflowToString(TextOverflow textOverflow)
{
    static const LinearEnumMapNode<TextOverflow, std::string> textOverflowTable[] = {
        { TextOverflow::NONE, "TextOverflow.None" },
        { TextOverflow::CLIP, "TextOverflow.Clip" },
        { TextOverflow::ELLIPSIS, "TextOverflow.Ellipsis" },
        { TextOverflow::MARQUEE, "TextOverflow.Marquee" },
    };

    auto index = BinarySearchFindIndex(textOverflowTable, ArraySize(textOverflowTable), textOverflow);
    return index < 0 ? "TextOverflow.Clip" : textOverflowTable[index].value;
}

inline TextOverflow ConvertWrapStringToTextOverflow(const std::string& str)
{
    static const std::unordered_map<std::string, TextOverflow> uMap {
        { "TextOverflow.Clip", TextOverflow::CLIP },
        { "TextOverflow.Ellipsis", TextOverflow::ELLIPSIS },
        { "TextOverflow.None", TextOverflow::NONE },
    };

    auto iter = uMap.find(str);
    if (iter != uMap.end()) {
        return iter->second;
    }
    return TextOverflow::CLIP;
}

inline MarqueeDirection ConvertWrapStringToMarqueeDirection(const std::string& str)
{
    static const std::unordered_map<std::string, MarqueeDirection> uMap {
        { "MarqueeDirection.LEFT", MarqueeDirection::LEFT },
        { "MarqueeDirection.RIGHT", MarqueeDirection::RIGHT },
    };

    return uMap.count(str) ? uMap.at(str) : MarqueeDirection::LEFT;
}

inline MarqueeStartPolicy ConvertWrapStringToMarqueeStartPolicy(const std::string& str)
{
    static const std::unordered_map<std::string, MarqueeStartPolicy> uMap {
        { "MarqueeStartPolicy.DEFAULT", MarqueeStartPolicy::DEFAULT },
        { "MarqueeStartPolicy.ON_FOCUS", MarqueeStartPolicy::ON_FOCUS },
    };

    return uMap.count(str) ? uMap.at(str) : MarqueeStartPolicy::DEFAULT;
}

inline std::string ConvertWrapFontStyleToStirng(FontStyle fontStyle)
{
    static const LinearEnumMapNode<FontStyle, std::string> fontStyleTable[] = {
        { FontStyle::NORMAL, "FontStyle.Normal" },
        { FontStyle::ITALIC, "FontStyle.Italic" },
    };

    auto index = BinarySearchFindIndex(fontStyleTable, ArraySize(fontStyleTable), fontStyle);
    return index < 0 ? "FontStyle.Normal" : fontStyleTable[index].value;
}

inline FontWeight ConvertFontWeight(FontWeight fontWeight)
{
    return FONT_WEIGHT_CONVERT_MAP[static_cast<int>(fontWeight)];
}

inline std::string ConvertWrapFontWeightToStirng(FontWeight fontWeight)
{
    static const LinearEnumMapNode<FontWeight, std::string> fontWeightTable[] = {
        { FontWeight::W100, "100" },
        { FontWeight::W200, "200" },
        { FontWeight::W300, "300" },
        { FontWeight::W400, "400" },
        { FontWeight::W500, "500" },
        { FontWeight::W600, "600" },
        { FontWeight::W700, "700" },
        { FontWeight::W800, "800" },
        { FontWeight::W900, "900" },
        { FontWeight::BOLD, "FontWeight.Bold" },
        { FontWeight::NORMAL, "FontWeight.Normal" },
        { FontWeight::BOLDER, "FontWeight.Bolder" },
        { FontWeight::LIGHTER, "FontWeight.Lighter" },
        { FontWeight::MEDIUM, "FontWeight.Medium" },
        { FontWeight::REGULAR, "FontWeight.Regular" },
    };

    auto index = BinarySearchFindIndex(fontWeightTable, ArraySize(fontWeightTable), fontWeight);
    return index < 0 ? "FontWeight.Normal" : fontWeightTable[index].value;
}

inline FontWeight ConvertWrapStringToFontWeight(const std::string& str)
{
    static const std::unordered_map<std::string, FontWeight> uMap {
        { "FontWeight.100", FontWeight::W100 },
        { "FontWeight.200", FontWeight::W200 },
        { "FontWeight.300", FontWeight::W300 },
        { "FontWeight.400", FontWeight::W400 },
        { "FontWeight.500", FontWeight::W500 },
        { "FontWeight.600", FontWeight::W600 },
        { "FontWeight.700", FontWeight::W700 },
        { "FontWeight.800", FontWeight::W800 },
        { "FontWeight.900", FontWeight::W900 },
        { "FontWeight.Bold", FontWeight::BOLD },
        { "FontWeight.Normal", FontWeight::NORMAL },
        { "FontWeight.Bolder", FontWeight::BOLDER },
        { "FontWeight.Lighter", FontWeight::LIGHTER },
        { "FontWeight.Medium", FontWeight::MEDIUM },
        { "FontWeight.Regular", FontWeight::REGULAR },
    };

    auto iter = uMap.find(str);
    if (iter != uMap.end()) {
        return iter->second;
    }
    return FontWeight::NORMAL;
}

inline std::string ConvertWrapCopyOptionToString(CopyOptions copyOptions)
{
    static const LinearEnumMapNode<CopyOptions, std::string> copyOptionsTable[] = {
        { CopyOptions::None, "CopyOptions::None" },
        { CopyOptions::InApp, "CopyOptions:InApp" },
        { CopyOptions::Local, "CopyOptions:Local" },
        { CopyOptions::Distributed, "CopyOptions:Distributed" },
    };

    auto index = BinarySearchFindIndex(copyOptionsTable, ArraySize(copyOptionsTable), copyOptions);
    return index < 0 ? "CopyOptions::None" : copyOptionsTable[index].value;
}

inline std::string ConvertWrapWordBreakToString(WordBreak wordBreak)
{
    static const LinearEnumMapNode<WordBreak, std::string> wordBreakTable[] = {
        { WordBreak::NORMAL, "normal" },
        { WordBreak::BREAK_ALL, "break-all" },
        { WordBreak::BREAK_WORD, "break-word" },
        { WordBreak::HYPHENATION, "hyphenation" },
    };

    auto index = BinarySearchFindIndex(wordBreakTable, ArraySize(wordBreakTable), wordBreak);
    return index < 0 ? "break-word" : wordBreakTable[index].value;
}

inline std::string ConvertTextDirectionToString(TextDirection direction)
{
    static const LinearEnumMapNode<TextDirection, std::string> textDirectionTable[] = {
        { TextDirection::LTR, "LTR" },
        { TextDirection::RTL, "RTL" },
        { TextDirection::INHERIT, "INHERIT" },
        { TextDirection::AUTO, "AUTO" },
    };

    auto index = BinarySearchFindIndex(textDirectionTable, ArraySize(textDirectionTable), direction);
    return index < 0 ? "AUTO" : textDirectionTable[index].value;
}

inline std::string ConvertEllipsisModeToString(EllipsisMode value)
{
    static const LinearEnumMapNode<EllipsisMode, std::string> modalTable[] = {
        { EllipsisMode::HEAD, "EllipsisMode.START" },
        { EllipsisMode::MIDDLE, "EllipsisMode.CENTER" },
        { EllipsisMode::TAIL, "EllipsisMode.END" },
    };
    auto index = BinarySearchFindIndex(modalTable, ArraySize(modalTable), value);
    return index < 0 ? "EllipsisMode.END" : modalTable[index].value;
}

inline std::string ConvertWrapLineBreakStrategyToString(LineBreakStrategy lineBreakStrategy)
{
    static const LinearEnumMapNode<LineBreakStrategy, std::string> lineBreakStrategyTable[] = {
        { LineBreakStrategy::GREEDY, "greedy" },
        { LineBreakStrategy::HIGH_QUALITY, "high-quality" },
        { LineBreakStrategy::BALANCED, "balanced" }
    };

    auto index = BinarySearchFindIndex(lineBreakStrategyTable, ArraySize(lineBreakStrategyTable), lineBreakStrategy);
    return index < 0 ? "line-break-strategy" : lineBreakStrategyTable[index].value;
}

inline std::string ConvertWrapTextSelectableToString(TextSelectableMode textSelectable)
{
    static const LinearEnumMapNode<TextSelectableMode, std::string> textSelectableTable[] = {
        { TextSelectableMode::SELECTABLE_UNFOCUSABLE, "selectable-unfocusable" },
        { TextSelectableMode::SELECTABLE_FOCUSABLE, "selectable-focusable" },
        { TextSelectableMode::UNSELECTABLE, "unselectable" }
    };

    auto index = BinarySearchFindIndex(textSelectableTable, ArraySize(textSelectableTable), textSelectable);
    return index < 0 ? "text-selectable" : textSelectableTable[index].value;
}

inline std::string ConvertColorToString(Color color)
{
    return color.ColorToString();
}

inline std::string ConvertAxisToString(Axis axis)
{
    return AXIS_TYPE[static_cast<int32_t>(axis)];
}

inline std::string ConvertSideToString(AlignDeclaration::Edge edge)
{
    if (edge == AlignDeclaration::Edge::TOP) {
        return "Edge::Top";
    } else if (edge == AlignDeclaration::Edge::CENTER) {
        return "Edge::Center";
    } else if (edge == AlignDeclaration::Edge::BOTTOM) {
        return "Edge::Bottom";
    } else if (edge == AlignDeclaration::Edge::BASELINE) {
        return "Edge::Baseline";
    } else if (edge == AlignDeclaration::Edge::START) {
        return "Edge::Start";
    } else if (edge == AlignDeclaration::Edge::MIDDLE) {
        return "Edge::Middle";
    } else if (edge == AlignDeclaration::Edge::END) {
        return "Edge::End";
    } else {
        return "Edge::Center";
    }
}

inline std::string ConvertFontFamily(const std::vector<std::string>& fontFamily)
{
    CHECK_NULL_RETURN(!fontFamily.empty(), "");
    std::string result;
    for (const auto& item : fontFamily) {
        result += item;
        result += ",";
    }
    result = result.substr(0, result.size() - 1);
    return result;
}

std::string GetTextStyleInJson(const TextStyle& textStyle);

inline std::string ConvertWrapTextHeightAdaptivePolicyToString(TextHeightAdaptivePolicy heightAdaptivePolicy)
{
    static const LinearEnumMapNode<TextHeightAdaptivePolicy, std::string> heightAdaptivePolicytTable[] = {
        { TextHeightAdaptivePolicy::MAX_LINES_FIRST, "TextHeightAdaptivePolicy.MAX_LINES_FIRST" },
        { TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, "TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST" },
        { TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST, "TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST" },
    };

    auto index =
        BinarySearchFindIndex(heightAdaptivePolicytTable, ArraySize(heightAdaptivePolicytTable), heightAdaptivePolicy);
    return index < 0 ? "TextHeightAdaptivePolicy.MAX_LINES_FIRST" : heightAdaptivePolicytTable[index].value;
}

inline std::string ConvertWrapMarqueeUpdateStrategyToStirng(MarqueeUpdateStrategy marqueeUpdateStrategy)
{
    static const LinearEnumMapNode<MarqueeUpdateStrategy, std::string> marqueeUpdateStrategyTable[] = {
        { MarqueeUpdateStrategy::DEFAULT, "MarqueeUpdateStrategy.DEFAULT" },
        { MarqueeUpdateStrategy::PRESERVE_POSITION, "MarqueeUpdateStrategy.PRESERVE_POSITION" },
    };

    auto index = BinarySearchFindIndex(
        marqueeUpdateStrategyTable, ArraySize(marqueeUpdateStrategyTable), marqueeUpdateStrategy);
    return index < 0 ? "MarqueeUpdateStrategy.DEFAULT" : marqueeUpdateStrategyTable[index].value;
}

inline std::string ConvertSymbolColorToString(const std::vector<Color>& colors)
{
    if (colors.size() <= 0) {
        return "";
    }
    auto colorStr = std::string("[");
    for (auto color : colors) {
        colorStr.append(color.ColorToString());
        colorStr.append(",");
    }
    colorStr.append("]");
    return colorStr;
}

inline bool IsValidTextDecorations(const std::vector<TextDecoration>& decorations)
{
    if (decorations.size() <= 0) {
        return false;
    }
    for (TextDecoration decoration : decorations) {
        if (decoration != TextDecoration::NONE) {
            return true;
        }
    }
    return false;
}

inline bool HasTextDecoration(const std::vector<TextDecoration>& decorations, TextDecoration value)
{
    auto iter = std::find(decorations.begin(), decorations.end(), value);
    return iter != decorations.end();
}

inline bool IsEqualTextDecorations(
    const std::vector<TextDecoration>& left, const std::vector<TextDecoration>& right)
{
    if (left.size() != right.size()) {
        return false;
    }
    for (int index = 0; index < static_cast<int>(left.size()); index++) {
        if (!HasTextDecoration(right, left[index])) {
            return false;
        }
    }
    return true;
}
} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_UTILS_H