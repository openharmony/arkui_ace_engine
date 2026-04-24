/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_WINDOW_SCENE_LAYOUT_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_WINDOW_SCENE_LAYOUT_MANAGER_H

#include <event_handler.h>
#include <unordered_set>
#include <vector>

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Rosen {
struct SessionUIParam;
class RSObjAbsGeometry;
enum class RSUINodeType : uint32_t;
}

namespace OHOS::Ace::NG {
struct TraverseResult {
    uint32_t zOrderCnt = 0;
    std::unordered_map<int32_t, OHOS::Rosen::SessionUIParam> uiParams;
    uint64_t screenId = -1;
};

struct TraverseInfo;

class WindowSceneLayoutManager {
public:
    static WindowSceneLayoutManager* GetInstance();
    void FlushWindowPatternInfo(const RefPtr<FrameNode>& screenNode);
    void RegisterScreenNode(uint64_t screenId, const RefPtr<FrameNode>& node);
    void UnregisterScreenNode(uint64_t screenId);

private:
    WindowSceneLayoutManager() = default;
    ~WindowSceneLayoutManager() = default;
    void Init();
    void TraverseTree(TraverseInfo& parentInfo, TraverseResult& res);
    bool InitTraverseInfo(FrameNode& node, TraverseInfo& info);
    void FillWindowSceneInfo(TraverseInfo& info, TraverseResult& res);
    void FillTransScenePos(TraverseInfo& info, const TraverseInfo& parentInfo);
    bool IsNodeVisible(TraverseInfo& info);
    bool IsNodeDirty(Rosen::RSNode& rsNode);
    bool IsRecentContainerState(TraverseInfo& info);
    bool NoNeedSyncScenePanelGlobalPosition(TraverseInfo& info);
    std::shared_ptr<Rosen::RSNode> GetRSNode(const RefPtr<FrameNode>& node);
    std::shared_ptr<Rosen::RSObjAbsGeometry> GetGlobalGeometry(Rosen::RSNode* rsNode);
    std::shared_ptr<Rosen::RSObjAbsGeometry> GetGlobalGeometry(const RefPtr<FrameNode>& node);
    std::shared_ptr<Rosen::RSObjAbsGeometry> GetLocalGeometry(const RefPtr<FrameNode>& node);
    bool SetGeometry(TraverseInfo& info,
        std::shared_ptr<Rosen::RSObjAbsGeometry>& globalGeometry,
        std::shared_ptr<Rosen::RSObjAbsGeometry>& localGeometry);
    void UpdateRootGeometry(TraverseInfo& info);
    void UpdateGeometry(TraverseInfo& info, TraverseInfo& parentInfo);
    int32_t GetNodeZIndex(const RefPtr<FrameNode>& node);
    uint64_t GetScreenId(const RefPtr<FrameNode>& screenNode);
    uint64_t GetRSNodeId(const TraverseInfo* info);
    uint64_t GetRSNodeId(const RefPtr<FrameNode>& node);
    const std::string& GetWindowName(TraverseInfo& info);
    std::string GetWindowName(const RefPtr<FrameNode>& node);
    uint32_t GetWindowId(TraverseInfo& info);
    uint32_t GetWindowId(const RefPtr<FrameNode>& node);
    void DumpFlushInfo(uint64_t screenId, TraverseResult& res);
    void DumpNodeInfo(TraverseInfo& node, TraverseInfo* parentInfo, const char* reason);
    void GetUINodeInfo(const RefPtr<FrameNode>& node, int32_t parentId, std::ostringstream& oss);
    void GetUITreeInfo(const RefPtr<FrameNode>& node, int32_t depth, int32_t parentId, std::ostringstream& oss);
    void GetTotalUITreeInfo(std::string& info);
    void DumpRSNodeType(Rosen::RSUINodeType nodeType, std::ostringstream& oss);
    void GetRSNodeTreeInfo(const std::shared_ptr<RSNode>& rsNode, int32_t depth,
        std::ostringstream& oss);
    void GetRSNodeInfo(const std::shared_ptr<RSNode>& rsNode,
        std::ostringstream& oss);
    void IsFrameNodeAbnormal(TraverseInfo& info);
    void RemoveAbnormalId();
    void TraverseTreeFindTransformScene(const RefPtr<FrameNode>& rootNode, uint32_t targetZOrder,
        std::vector<std::pair<RefPtr<FrameNode>, uint32_t>>& scenePanelNodeArr);
    std::shared_ptr<Rosen::RSNode> FindScenePanelRsNodeByZOrder(uint64_t screenId, uint32_t targetZOrder);
    std::unordered_set<uint64_t> abnormalNodeDfxSet_;
    std::unordered_set<uint64_t> windowSceneOnTreeDfxSet_;
    std::unordered_map<uint64_t, WeakPtr<FrameNode>> screenNodeMap_;
    std::shared_ptr<AppExecFwk::EventHandler> mainHandler_;
    bool isCoreDebugEnable_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_WINDOW_SCENE_LAYOUT_MANAGER_H
