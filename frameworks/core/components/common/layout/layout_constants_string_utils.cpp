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

#include "core/components/common/layout/layout_constants_string_utils.h"

#include "base/utils/linear_map.h"
#include "core/components/common/layout/constants.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::StringUtils {

std::string ToString(const TextAlign& textAlign)
{
    static const LinearEnumMapNode<TextAlign, std::string> table[] = {
        { TextAlign::START, "START" },
        { TextAlign::CENTER, "CENTER" },
        { TextAlign::END, "END" },
        { TextAlign::JUSTIFY, "JUSTIFY" },
        { TextAlign::LEFT, "LEFT" },
        { TextAlign::RIGHT, "RIGHT" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textAlign);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const TextVerticalAlign& textVerticalAlign)
{
    static const LinearEnumMapNode<TextVerticalAlign, std::string> table[] = {
        { TextVerticalAlign::BASELINE, "BASELINE" },
        { TextVerticalAlign::BOTTOM, "BOTTOM" },
        { TextVerticalAlign::CENTER, "CENTER" },
        { TextVerticalAlign::TOP, "TOP" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textVerticalAlign);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const TextSelectableMode& textSelectableMode)
{
    static const LinearEnumMapNode<TextSelectableMode, std::string> table[] = {
        { TextSelectableMode::SELECTABLE_UNFOCUSABLE, "SELECTABLE_UNFOCUSABLE" },
        { TextSelectableMode::SELECTABLE_FOCUSABLE, "SELECTABLE_FOCUSABLE" },
        { TextSelectableMode::UNSELECTABLE, "UNSELECTABLE" }
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textSelectableMode);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const TextOverflow& textOverflow)
{
    static const LinearEnumMapNode<TextOverflow, std::string> table[] = {
        { TextOverflow::NONE, "NONE" },
        { TextOverflow::CLIP, "CLIP" },
        { TextOverflow::ELLIPSIS, "ELLIPSIS" },
        { TextOverflow::MARQUEE, "MARQUEE" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textOverflow);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const TextDecoration& textDecoration)
{
    static const LinearEnumMapNode<TextDecoration, std::string> table[] = {
        { TextDecoration::NONE, "NONE" },
        { TextDecoration::UNDERLINE, "UNDERLINE" },
        { TextDecoration::OVERLINE, "OVERLINE" },
        { TextDecoration::LINE_THROUGH, "LINE_THROUGH" },
        { TextDecoration::INHERIT, "INHERIT" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textDecoration);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const TextDecorationStyle& textDecorationStyle)
{
    static const LinearEnumMapNode<TextDecorationStyle, std::string> table[] = {
        { TextDecorationStyle::SOLID, "SOLID" },
        { TextDecorationStyle::DOUBLE, "DOUBLE" },
        { TextDecorationStyle::DOTTED, "DOTTED" },
        { TextDecorationStyle::DASHED, "DASHED" },
        { TextDecorationStyle::WAVY, "WAVY" },
        { TextDecorationStyle::INITIAL, "INITIAL" },
        { TextDecorationStyle::INHERIT, "INHERIT" }
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), textDecorationStyle);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const ImageFit& imageFit)
{
    static const LinearEnumMapNode<ImageFit, std::string> table[] = {
        { ImageFit::FILL, "FILL" },
        { ImageFit::CONTAIN, "CONTAIN" },
        { ImageFit::COVER, "COVER" },
        { ImageFit::FITWIDTH, "FITWIDTH" },
        { ImageFit::FITHEIGHT, "FITHEIGHT" },
        { ImageFit::NONE, "NONE" },
        { ImageFit::SCALE_DOWN, "SCALE_DOWN" },
        { ImageFit::TOP_LEFT, "TOP_LEFT" },
        { ImageFit::TOP, "TOP" },
        { ImageFit::TOP_END, "TOP_END" },
        { ImageFit::START, "START" },
        { ImageFit::CENTER, "CENTER" },
        { ImageFit::END, "END" },
        { ImageFit::BOTTOM_START, "BOTTOM_START" },
        { ImageFit::BOTTOM, "BOTTOM" },
        { ImageFit::BOTTOM_END, "BOTTOM_END" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), imageFit);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const RenderStrategy& renderStrategy)
{
    static const LinearEnumMapNode<RenderStrategy, std::string> table[] = {
        { RenderStrategy::FAST, "FAST" },
        { RenderStrategy::OFFSCREEN, "OFFSCREEN" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), renderStrategy);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const VerticalAlign& verticalAlign)
{
    static const LinearEnumMapNode<VerticalAlign, std::string> table[] = {
        { VerticalAlign::TOP, "TOP" },
        { VerticalAlign::CENTER, "CENTER" },
        { VerticalAlign::BOTTOM, "BOTTOM" },
        { VerticalAlign::BASELINE, "BASELINE" },
        { VerticalAlign::NONE, "NONE" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), verticalAlign);
    return iter != -1 ? table[iter].value : "";
}

std::string ToString(const CopyOptions& copyOptions)
{
    static const LinearEnumMapNode<CopyOptions, std::string> table[] = {
        { CopyOptions::None, "None" },
        { CopyOptions::InApp, "InApp" },
        { CopyOptions::Local, "Local" },
        { CopyOptions::Distributed, "Distributed" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), copyOptions);
    return iter != -1 ? table[iter].value : "";
}

} // namespace OHOS::Ace::StringUtils
