/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "core/interfaces/native/node/column_split_modifier.h"

#include "core/components_ng/pattern/linear_split/linear_split_model_ng.h"

namespace OHOS::Ace::NG {
constexpr bool DEFAULT_COLUMN_SPLIT_RESIZABLE = false;
constexpr Dimension DEFAULT_DIVIDER_START = Dimension(0.0, DimensionUnit::VP);
constexpr Dimension DEFAULT_DIVIDER_END = Dimension(0.0, DimensionUnit::VP);
void SetColumnSplitResizable(ArkUINodeHandle node, ArkUI_Bool resizable)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LinearSplitModelNG::SetResizable(frameNode, NG::SplitType::COLUMN_SPLIT, resizable);
}

void ResetColumnSplitResizable(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LinearSplitModelNG::SetResizable(frameNode, NG::SplitType::COLUMN_SPLIT, DEFAULT_COLUMN_SPLIT_RESIZABLE);
}

void SetColumnSplitDivider(ArkUINodeHandle node, ArkUI_Float32 stVal, int32_t stUnit,
    ArkUI_Float32 endVal, int32_t endUnit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension startMarginDimension(stVal, static_cast<DimensionUnit>(stUnit));
    Dimension endMarginDimension(endVal, static_cast<DimensionUnit>(endUnit));
    ItemDivider divider = { startMarginDimension, endMarginDimension };
    LinearSplitModelNG::SetDivider(frameNode, SplitType::COLUMN_SPLIT, divider);
}

void ResetColumnSplitDivider(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LinearSplitModelNG::SetDivider(frameNode, SplitType::COLUMN_SPLIT, { DEFAULT_DIVIDER_START, DEFAULT_DIVIDER_END });
}

namespace NodeModifier {
const ArkUIColumnSplitModifier* GetColumnSplitModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIColumnSplitModifier modifier = {
        .setColumnSplitDivider = SetColumnSplitDivider,
        .resetColumnSplitDivider = ResetColumnSplitDivider,
        .setColumnSplitResizable = SetColumnSplitResizable,
        .resetColumnSplitResizable = ResetColumnSplitResizable,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIColumnSplitModifier* GetCJUIColumnSplitModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIColumnSplitModifier modifier = {
        .setColumnSplitDivider = SetColumnSplitDivider,
        .resetColumnSplitDivider = ResetColumnSplitDivider,
        .setColumnSplitResizable = SetColumnSplitResizable,
        .resetColumnSplitResizable = ResetColumnSplitResizable,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
} // namespace OHOS::Ace::NG
