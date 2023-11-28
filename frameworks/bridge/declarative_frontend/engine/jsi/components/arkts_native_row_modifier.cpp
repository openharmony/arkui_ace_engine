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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_row_modifier.h"

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "core/components/common/layout/constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"

namespace OHOS::Ace::NG {
constexpr FlexAlign DEFAULT_ROW_JUSTIFY_CONTENT = FlexAlign::FLEX_START;
constexpr FlexAlign DEFAULT_ROW_ALIGN_ITEMS = FlexAlign::CENTER;
void SetRowJustifyContent(NodeHandle node, int32_t flexAlign)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RowModelNG::SetJustifyContent(frameNode, static_cast<FlexAlign>(flexAlign));
}

void ResetRowJustifyContent(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RowModelNG::SetJustifyContent(frameNode, DEFAULT_ROW_JUSTIFY_CONTENT);
}

void SetRowAlignItems(NodeHandle node, int32_t verticalAlign)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RowModelNG::SetAlignItems(frameNode, static_cast<FlexAlign>(verticalAlign));
}

void ResetRowAlignItems(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RowModelNG::SetAlignItems(frameNode, DEFAULT_ROW_ALIGN_ITEMS);
}

ArkUIRowModifierAPI GetRowModifier()
{
    static const ArkUIRowModifierAPI modifier = { SetRowJustifyContent, ResetRowJustifyContent, SetRowAlignItems,
                                                  ResetRowAlignItems };
    return modifier;
}
}