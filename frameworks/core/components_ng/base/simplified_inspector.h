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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SIMPLIFIED_INSPECTOR_INSPECTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SIMPLIFIED_INSPECTOR_INSPECTOR_H

#include <string>

#include "core/common/recorder/inspector_tree_collector.h"
#include "core/components_ng/base/frame_node.h"
#include "interfaces/inner_api/ace/ui_event_observer.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class SimplifiedInspector final : public std::enable_shared_from_this<SimplifiedInspector> {
public:
    SimplifiedInspector(int32_t containerId, const TreeParams& params);
    ~SimplifiedInspector() = default;
    std::string GetInspector();
    void GetInspectorAsync(const std::shared_ptr<Recorder::InspectorTreeCollector>& collector);
    void GetInspectorBackgroundAsync(const std::shared_ptr<Recorder::InspectorTreeCollector>& collector);

private:
    struct SimplifiedInspectorTree {
        WeakPtr<NG::UINode> node;
        std::list<std::shared_ptr<SimplifiedInspectorTree>> children;
    };
    bool GetInspectorStep1(const std::unique_ptr<JsonValue>& jsonRoot, RefPtr<FrameNode>& pageRootNode);
    bool GetInspectorStep2(const std::unique_ptr<JsonValue>& jsonRoot, const RefPtr<FrameNode>& pageRootNode);
    void GetFrameNodeChildren(const RefPtr<NG::UINode>& uiNode, std::list<RefPtr<NG::UINode>>& childrenList);
    void GetInspectorChildren(
        const RefPtr<NG::UINode>& parent, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNodeArray, bool isActive);
    void GetSpanInspector(const RefPtr<NG::UINode>& parent, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNodeArray);
    void FillInspectorAttrs(const RefPtr<NG::UINode>& parent, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNode);
    void GetWebContentIfNeed(const RefPtr<FrameNode>& node);
    bool CheckNodeRect(const RefPtr<FrameNode>& node, RectF& rect, bool isVisibleOnly);

    void GetInspectorTreeNode(const RefPtr<NG::UINode>& pageRootNode, std::shared_ptr<SimplifiedInspectorTree>& root);
    void GetInspectorTreeNodeChildren(
        const RefPtr<NG::UINode>& parent, std::shared_ptr<SimplifiedInspectorTree>& treeNode, bool isActive);
    void GetInspectorChildrenBackground(
        const std::shared_ptr<SimplifiedInspectorTree>& treeNode, std::unique_ptr<OHOS::Ace::JsonValue>& jsonNodeArray);
    RectF deviceRect_;
    int32_t containerId_;
    int pageId_ = 0;
    TreeParams params_;
    InspectorConfig inspectorCfg_;
    size_t size_ = 0;
    bool isAsync_ = false;
    bool isBackground_ = false;
    std::shared_ptr<Recorder::InspectorTreeCollector> collector_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SIMPLIFIED_INSPECTOR_INSPECTOR_H
