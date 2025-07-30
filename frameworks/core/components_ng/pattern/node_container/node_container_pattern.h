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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_NODE_CONTAINER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_NODE_CONTAINER_PATTERN_H

#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/node_container/node_container_layout_algorithm.h"
#include "core/components_ng/pattern/node_container/node_container_event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_layout_algorithm.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"

namespace OHOS::Ace::NG {
class NodeContainerPattern : virtual public Pattern {
    DECLARE_ACE_TYPE(NodeContainerPattern, Pattern);

public:
    NodeContainerPattern() = default;
    ~NodeContainerPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<StackLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<NodeContainerLayoutAlgorithm>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<NodeContainerEventHub>();
    }

    void RemakeNode();

    void CleanChild();

    void BindController(std::function<void()>&& resetFunc)
    {
        resetFunc_ = std::move(resetFunc);
    }

    void ResetController() const
    {
        CHECK_NULL_VOID(resetFunc_);
        resetFunc_();
    }

    void SetMakeFunction(std::function<RefPtr<UINode>()>&& makeFunc)
    {
        makeFunc_ = std::move(makeFunc);
    }

    RefPtr<UINode> FireMakeFunction() const
    {
        CHECK_NULL_RETURN(makeFunc_, nullptr);
        return makeFunc_();
    }

    void FireOnWillBind(int32_t containerId);

    void FireOnWillUnbind(int32_t containerId);

    void FireOnBind(int32_t containerId);

    void FireOnUnbind(int32_t containerId);

    void SetOnResize(std::function<void(const SizeF& size)>&& resizeFunc)
    {
        resizeFunc_ = std::move(resizeFunc);
    }

    void FireOnResize(const SizeF& size) const
    {
        CHECK_NULL_VOID(resizeFunc_);
        resizeFunc_(size);
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void OnAddBaseNode();

    RefPtr<FrameNode> GetExportTextureNode() const;

    uint64_t GetSurfaceId() const
    {
        return surfaceId_;
    }

    void ResetExportTextureInfo();
    void AddBaseNode(const RefPtr<UINode>& newNode);

    bool IsEnableChildrenMatchParent() override
    {
        return true;
    }

    bool IsEnableMatchParent() override
    {
        return true;
    }

    bool IsEnableFix() override
    {
        return true;
    }

private:
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnMountToParentDone() override;
    void SetExportTextureInfoIfNeeded();
    bool HandleTextureExport(bool isStop, FrameNode* frameNode);
    std::function<void()> resetFunc_;
    std::function<RefPtr<UINode>()> makeFunc_;
    std::function<void(const SizeF& size)> resizeFunc_;
    WeakPtr<UINode> exportTextureNode_;
    uint64_t surfaceId_ = 0U;
    RefPtr<NodeContainerEventHub> GetNodeContainerEventHub();

    ACE_DISALLOW_COPY_AND_MOVE(NodeContainerPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_NODE_CONTAINER_PATTERN_H
