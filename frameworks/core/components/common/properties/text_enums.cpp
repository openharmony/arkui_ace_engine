/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components/common/properties/text_enums.h"

#include "core/components/common/layout/constants.h"

namespace OHOS::Ace {
namespace StringUtils {

std::string ToString(const FontStyle& fontStyle)
{
    static const LinearEnumMapNode<FontStyle, std::string> table[] = {
        { FontStyle::NORMAL, "NORMAL" },
        { FontStyle::ITALIC, "ITALIC" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), fontStyle);
    return iter != -1 ? table[iter].value : "";
}

std::string ToStringNDK(const FontStyle& fontStyle)
{
    static const LinearEnumMapNode<FontStyle, std::string> table[] = {
        { FontStyle::NORMAL, "normal" },
        { FontStyle::ITALIC, "italic" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), fontStyle);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const TextBaseline& textBaseline)
{
    static const LinearEnumMapNode<TextBaseline, std::string> table[] = {
        { TextBaseline::ALPHABETIC, "ALPHABETIC" },
        { TextBaseline::IDEOGRAPHIC, "IDEOGRAPHIC" },
        { TextBaseline::TOP, "TOP" },
        { TextBaseline::BOTTOM, "BOTTOM" },
        { TextBaseline::MIDDLE, "MIDDLE" },
        { TextBaseline::HANGING, "HANGING" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textBaseline);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const TextCase& textCase)
{
    static const LinearEnumMapNode<TextCase, std::string> table[] = {
        { TextCase::NORMAL, "NORMAL" },
        { TextCase::LOWERCASE, "LOWERCASE" },
        { TextCase::UPPERCASE, "UPPERCASE" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textCase);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const EllipsisMode& ellipsisMode)
{
    static const LinearEnumMapNode<EllipsisMode, std::string> table[] = {
        { EllipsisMode::HEAD, "HEAD" },
        { EllipsisMode::MIDDLE, "MIDDLE" },
        { EllipsisMode::TAIL, "TAIL" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), ellipsisMode);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const WordBreak& wordBreak)
{
    static const LinearEnumMapNode<WordBreak, std::string> table[] = {
        { WordBreak::NORMAL, "NORMAL" },
        { WordBreak::BREAK_ALL, "BREAK_ALL" },
        { WordBreak::BREAK_WORD, "BREAK_WORD" },
        { WordBreak::HYPHENATION, "HYPHENATION" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), wordBreak);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const PlaceholderAlignment& placeholderAlignment)
{
    static const LinearEnumMapNode<PlaceholderAlignment, std::string> table[] = {
        { PlaceholderAlignment::BASELINE, "BASELINE" },
        { PlaceholderAlignment::ABOVEBASELINE, "ABOVEBASELINE" },
        { PlaceholderAlignment::BELOWBASELINE, "BELOWBASELINE" },
        { PlaceholderAlignment::TOP, "TOP" },
        { PlaceholderAlignment::BOTTOM, "BOTTOM" },
        { PlaceholderAlignment::MIDDLE, "MIDDLE" },
        { PlaceholderAlignment::FOLLOW_PARAGRAPH, "FOLLOW_PARAGRAPH" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), placeholderAlignment);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const SpanItemType& spanItemType)
{
    static const LinearEnumMapNode<SpanItemType, std::string> table[] = {
        { SpanItemType::NORMAL, "NORMAL" },
        { SpanItemType::IMAGE, "IMAGE" },
        { SpanItemType::CustomSpan, "CustomSpan" },
        { SpanItemType::SYMBOL, "SYMBOL" },
        { SpanItemType::PLACEHOLDER, "PLACEHOLDER" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), spanItemType);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const TextFlipDirection& textFlipDirection)
{
    static const LinearEnumMapNode<TextFlipDirection, std::string> table[] = {
        { TextFlipDirection::DOWN, "down" },
        { TextFlipDirection::UP, "up" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textFlipDirection);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const TextDirection& textDirection)
{
    static const LinearEnumMapNode<TextDirection, std::string> table[] = {
        { TextDirection::LTR, "LTR" },
        { TextDirection::RTL, "RTL" },
        { TextDirection::INHERIT, "DEFAULT" },
        { TextDirection::AUTO, "AUTO" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textDirection);
    return iter != -1 ? table[iter].value : "";
}
} // namespace StringUtils
} // namespace OHOS::Ace