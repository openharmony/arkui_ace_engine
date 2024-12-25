/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/blank_modifier.h"

#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::NG {
void SetColor(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::SetColor(frameNode, Color(value));
}

void ResetColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::SetColor(frameNode, Color::TRANSPARENT);
}

void SetBlankHeight(ArkUINodeHandle node, ArkUI_Float32 heightValue, ArkUI_Int32 heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::SetHeight(frameNode, CalcDimension(heightValue, (DimensionUnit)heightUnit));
}

void ResetBlankHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
}

void SetBlankMin(ArkUINodeHandle node, ArkUI_Float32 minValue, ArkUI_Int32 minUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::SetBlankMin(frameNode, CalcDimension(minValue, (DimensionUnit)minUnit));
}

void ResetBlankMin(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::SetBlankMin(frameNode, CalcDimension(0.0, DimensionUnit::VP));
}

namespace NodeModifier {
const ArkUIBlankModifier* GetBlankModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIBlankModifier modifier = {
        .setColor = SetColor,
        .resetColor = ResetColor,
        .setBlankHeight = SetBlankHeight,
        .resetBlankHeight = ResetBlankHeight,
        .setBlankMin = SetBlankMin,
        .resetBlankMin = ResetBlankMin,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");
    return &modifier;
}

const CJUIBlankModifier* GetCJUIBlankModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUIBlankModifier modifier = {
        .setColor = SetColor,
        .resetColor = ResetColor,
        .setBlankHeight = SetBlankHeight,
        .resetBlankHeight = ResetBlankHeight,
        .setBlankMin = SetBlankMin,
        .resetBlankMin = ResetBlankMin,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");
    return &modifier;
}
}
}
