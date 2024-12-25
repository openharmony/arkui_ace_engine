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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_NODE_H

#include <functional>
#include <string>

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/custom/custom_node_base.h"
#include "core/components_ng/pattern/custom/custom_node_pattern.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

// CustomNode is the frame node of @Component struct.
class ACE_EXPORT CustomNode : public UINode, public CustomNodeBase {
    DECLARE_ACE_TYPE(CustomNode, UINode, CustomNodeBase);

public:
    static RefPtr<CustomNode> CreateCustomNode(int32_t nodeId, const std::string& viewKey);

    CustomNode(int32_t nodeId, const std::string& viewKey)
    : UINode(V2::JS_VIEW_ETS_TAG, nodeId, MakeRefPtr<CustomNodePattern>()), viewKey_(viewKey) {}
    ~CustomNode() override
    {
        ACE_SCOPED_TRACE("CustomNode:Destroy [%d]", GetId());
    }

    void AdjustLayoutWrapperTree(const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout) override;

    RefPtr<LayoutWrapperNode> CreateLayoutWrapper(bool forceMeasure = false, bool forceLayout = false) override;

    bool IsAtomicNode() const override
    {
        return true;
    }

    bool IsSyntaxNode() const override
    {
        return true;
    }

    void SetRenderFunction(const RenderFunction& renderFunction) override
    {
        renderFunction_ = renderFunction;
    }

    void Build(std::shared_ptr<std::list<ExtraInfo>> extraInfos) override;

    int32_t FrameCount() const override
    {
        return 1;
    }

    int32_t CurrentFrameCount() const override
    {
        return 1;
    }

    void Render();

    void SetCompleteReloadFunc(RenderFunction&& func) override
    {
        completeReloadFunc_ = std::move(func);
    }
    ACE_FORCE_EXPORT void FlushReload();

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("viewKey", viewKey_.c_str(), filter);
    }

    void FromJson(const std::unique_ptr<JsonValue>& json) override {}

    std::string GetCustomTag() override
    {
        return jsViewName_;
    }

    void MarkNeedSyncRenderTree(bool needRebuild = false) override;
    RefPtr<UINode> GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache = false,
        bool addToRenderTree = false) override;
    bool RenderCustomChild(int64_t deadline) override;
    void SetJSViewActive(bool active, bool isLazyForEachNode = false) override;

    bool GetJsActive()
    {
        return prevJsActive_;
    }

    void SetJsActive(bool active)
    {
        prevJsActive_ = active;
    }

    void SetExtraInfos(const std::list<ExtraInfo> extraInfos)
    {
        extraInfos_ = std::move(extraInfos);
    }

    const std::list<ExtraInfo> GetExtraInfos() const
    {
        return extraInfos_;
    }

    void DoSetActiveChildRange(
        int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache = false) override;

    const WeakPtr<UINode>& GetNavigationNode() const
    {
        return navigationNode_;
    }

    void SetNavigationNode(const WeakPtr<UINode>& navigationNode)
    {
        navigationNode_ = navigationNode;
    }

    std::unique_ptr<JsonValue> GetStateInspectorInfo();

    void FireCustomDisappear() override;

    // called for DFX
    void DumpInfo() override;
private:
    // for DFX
    void DumpComponentInfo(std::unique_ptr<JsonValue>& componentInfo);
    void DumpDecoratorInfo(std::unique_ptr<JsonValue>& decoratorInfo);

    std::string viewKey_;
    RenderFunction renderFunction_;
    RenderFunction completeReloadFunc_;
    bool needMarkParent_ = true;
    bool prevJsActive_ = true;
    std::list<ExtraInfo> extraInfos_;
    WeakPtr<UINode> navigationNode_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_NODE_H
