/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_BRIDGE_GRID_GRID_UTILS_MODIFIER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_BRIDGE_GRID_GRID_UTILS_MODIFIER_H
#include <cstdint>

namespace OHOS::Ace {
template<class T>
class RefPtr;
class ItemDragInfo;

namespace NG {
class FrameNode;

struct GridCustomModifier {
    void (*fireOnItemDragEnter)(const RefPtr<FrameNode>& frameNode, const ItemDragInfo& dragInfo);
    void (*fireOnItemDragMove)(
        const RefPtr<FrameNode>& frameNode, const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex);
    void (*fireOnItemDragLeave)(const RefPtr<FrameNode>& frameNode, const ItemDragInfo& dragInfo, int32_t itemIndex);
    bool (*fireOnItemDrop)(const RefPtr<FrameNode>& frameNode, const ItemDragInfo& dragInfo, int32_t itemIndex,
        int32_t insertIndex, bool isSuccess);
    int32_t (*getInsertPosition)(const RefPtr<FrameNode>& frameNode, float x, float y);
    bool (*checkPositionInGrid)(const RefPtr<FrameNode>& frameNode, float x, float y);
    int32_t (*getFrameNodeChildSize)(const RefPtr<FrameNode>& frameNode);
    int32_t (*getGridItemIndex)(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& gridItem);
    void (*handleOnItemDragCancel)(const RefPtr<FrameNode>& frameNode);
};
} // namespace NG
} // namespace OHOS::Ace

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_BRIDGE_GRID_GRID_UTILS_MODIFIER_H