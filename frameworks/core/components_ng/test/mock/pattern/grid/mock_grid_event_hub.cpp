/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_event_hub.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> GridEventHub::FindGridItemByPosition(float /* x */, float /* y */)
{
    return nullptr;
}

bool GridEventHub::CheckPostionInGrid(float x, float y)
{
    return false;
}

int32_t GridEventHub::GetGridItemIndex(const RefPtr<FrameNode>& /* frameNode */)
{
    return 0;
}

int GridEventHub::GetFrameNodeChildSize()
{
    return 0;
}

void GridEventHub::FireOnItemDragEnter(const ItemDragInfo& dragInfo)
{
    if (onItemDragEnter_) {
        onItemDragEnter_(dragInfo);
    }
}

void GridEventHub::FireOnItemDragLeave(const ItemDragInfo& dragInfo, int32_t itemIndex)
{
    if (onItemDragLeave_) {
        onItemDragLeave_(dragInfo, itemIndex);
    }
}

void GridEventHub::FireOnItemDrop(const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess)
{
    if (onItemDrop_) {
        onItemDrop_(dragInfo, itemIndex, insertIndex, isSuccess);
    }
}
} // namespace OHOS::Ace::NG
