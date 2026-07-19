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
#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_BRIDGE_GRIDITEM_GRID_ITEM_UTILS_MODIFIER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_BRIDGE_GRIDITEM_GRID_ITEM_UTILS_MODIFIER_H

#include <cstdint>

namespace OHOS::Ace {
template<class T>
class RefPtr;
class ItemDragInfo;

namespace NG {
class FrameNode;
class ForEachBaseNode;
class Pattern;

struct GridItemCustomModifier {
    void (*initDragManager)(const RefPtr<FrameNode>& frameNode, RefPtr<ForEachBaseNode> forEach);
    void (*deInitDragManager)(const RefPtr<FrameNode>& frameNode);
    bool (*isSelected)(const RefPtr<FrameNode>& frameNode);
    bool (*isGridItemPattern)(const RefPtr<Pattern>& pattern);
};
} // namespace NG
} // namespace OHOS::Ace

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_BRIDGE_GRIDITEM_GRID_ITEM_UTILS_MODIFIER_H