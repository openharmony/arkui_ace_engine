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
#include "core/interfaces/native/node/row_split_modifier.h"

#include "core/components_ng/pattern/linear_split/linear_split_model_ng.h"

namespace OHOS::Ace::NG {
constexpr bool DEFAULT_ROW_SPLIT_RESIZABLE = false;
void SetRowSplitResizable(ArkUINodeHandle node, ArkUI_Bool resizable)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LinearSplitModelNG::SetResizable(frameNode, NG::SplitType::ROW_SPLIT, resizable);
}

void ResetRowSplitResizable(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LinearSplitModelNG::SetResizable(frameNode, NG::SplitType::ROW_SPLIT, DEFAULT_ROW_SPLIT_RESIZABLE);
}

namespace NodeModifier {
const ArkUIRowSplitModifier* GetRowSplitModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIRowSplitModifier modifier = {
        .setRowSplitResizable = SetRowSplitResizable,
        .resetRowSplitResizable = ResetRowSplitResizable,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIRowSplitModifier* GetCJUIRowSplitModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIRowSplitModifier modifier = {
        .setRowSplitResizable = SetRowSplitResizable,
        .resetRowSplitResizable = ResetRowSplitResizable,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
}
