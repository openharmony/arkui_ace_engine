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
#include "core/interfaces/native/node/grid_row_modifier.h"

#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/pattern/grid_row/grid_row_model_ng.h"

namespace OHOS::Ace::NG {
void SetAlignItems(NodeHandle node, int32_t alignItems)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FlexAlign alignItemsValue = static_cast<FlexAlign>(alignItems);
    GridRowModelNG::SetAlignItems(frameNode, alignItemsValue);
}

void ResetAlignItems(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FlexAlign resetValue = FlexAlign::FLEX_START;
    GridRowModelNG::SetAlignItems(frameNode, resetValue);
}

ArkUIGridRowModifierAPI GetGridRowModifier()
{
    static const ArkUIGridRowModifierAPI modifier = {SetAlignItems, ResetAlignItems};
    return modifier;
}
}
