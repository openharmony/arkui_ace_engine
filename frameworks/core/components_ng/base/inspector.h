/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_INSPECTOR_INSPECTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_INSPECTOR_INSPECTOR_H

#include <string>
#include <unordered_map>

#include "base/utils/macros.h"
#include "bridge/common/utils/componentInfo.h"
#include "core/components_ng/base/frame_node.h"
#include "rec_node.h"

namespace OHOS::Ace::NG {
const char KEY_METHOD[] = "method";
const char KEY_PARAMS[] = "params";
const char SUPPORT_METHOD[] = "ArkUI.tree";
const uint32_t INVALID_WINDOW_ID = 0;
class InspectorFilter;
using InspectorTreeMap = std::unordered_map<int32_t, RefPtr<RecNode>>;

struct InspectorChildrenParameters {
    int32_t pageId = 0;
    bool isActive = false;
    bool isLayoutInspector = false;
};

class ACE_FORCE_EXPORT Inspector {
public:
    static RefPtr<FrameNode> GetFrameNodeByKey(const std::string& key, bool notDetach = false,
        bool skipoffscreenNodes = false);
    static std::string GetInspectorNodeByKey(const std::string& key,
        const InspectorFilter& filter = InspectorFilter());
    static bool SendEventByKey(const std::string& key, int action, const std::string& params);
    static void GetRectangleById(const std::string& key, Rectangle& rectangle);
    static std::string GetInspector(bool isLayoutInspector = false);
    static std::string GetInspector(bool isLayoutInspector, const InspectorFilter& filter, bool& needThrow);
    static std::string GetInspectorOfNode(RefPtr<NG::UINode> node);
    static std::string GetSubWindowInspector(bool isLayoutInspector = false);
    static void HideAllMenus();
    static void AddOffscreenNode(RefPtr<FrameNode> node);
    static void RemoveOffscreenNode(RefPtr<FrameNode> node);
    static void GetInspectorTree(InspectorTreeMap& treesInfo);
    static void GetOffScreenTreeNodes(InspectorTreeMap& nodes);
    static void GetRecordAllPagesNodes(InspectorTreeMap& treesInfo);
    static uint32_t ParseWindowIdFromMsg(const std::string& message);

private:
    static RefPtr<RecNode> AddInspectorTreeNode(const RefPtr<NG::UINode>& uiNode, InspectorTreeMap& recNodes);
    static void GetInspectorTreeInfo(
        std::vector<RefPtr<NG::UINode>> children, int32_t pageId, InspectorTreeMap& recNodes);
    static void GetInspectorChildrenInfo(
        const RefPtr<NG::UINode>& parent, InspectorTreeMap& recNodes, int32_t pageId, uint32_t depth = UINT32_MAX);
    static void RecordOnePageNodes(const RefPtr<NG::UINode>& pageNode, InspectorTreeMap& treesInfo);

private:
    static std::set<RefPtr<FrameNode>> offscreenNodes;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_INSPECTOR_INSPECTOR_H
