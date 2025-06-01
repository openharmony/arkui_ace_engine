/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_ITEM_GROUP_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_ITEM_GROUP_MODEL_STATIC_H


#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_item_group_model.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ListItemGroupModelStatic {
public:
    static void SetDivider(FrameNode* frameNode, const std::optional<V2::ItemDivider>& divider);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetHeader(FrameNode* frameNode, std::function<RefPtr<UINode>()>&& builder);
    static void SetFooter(FrameNode* frameNode, std::function<RefPtr<UINode>()>&& builder);
    static void SetSpace(FrameNode* frameNode, const std::optional<Dimension>& space);
    static void SetStyle(FrameNode* frameNode, const std::optional<V2::ListItemGroupStyle>& style);
    static RefPtr<ListChildrenMainSize> GetOrCreateListChildrenMainSize(
        FrameNode* frameNode, const std::optional<float>& defaultSize);
    static RefPtr<ListChildrenMainSize> GetOrCreateListChildrenMainSize(FrameNode* frameNode);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_ITEM_GROUP_MODEL_STATIC_H
