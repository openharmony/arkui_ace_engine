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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_VIEW_H

#include <functional>
#include <optional>
#include <string>

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT MenuItemGroupView {
public:
    // createMenuItem with custom
    static void Create();
    static RefPtr<FrameNode>CreateFrameNode(int32_t nodeId);
    static void SetHeader(const RefPtr<UINode>& header);
    static void SetHeader(const std::string& headerStr);
    static void SetFooter(const RefPtr<UINode>& footer);
    static void SetFooter(const std::string& footerStr);
    static void SetHeader(FrameNode* frameNode, const std::optional<std::string>& headerStr);
    static void SetHeader(FrameNode* frameNode, std::function<RefPtr<UINode>()>&& builder);
    static void SetFooter(FrameNode* frameNode, const std::optional<std::string>& footerStr);
    static void SetFooter(FrameNode* frameNode, std::function<RefPtr<UINode>()>&& builder);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_VIEW_H
