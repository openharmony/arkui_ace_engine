/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/custom/custom_node.h"

#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/custom/custom_node_base.h"
#include "core/components_ng/pattern/custom/custom_node_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
RefPtr<CustomNode> CustomNode::CreateCustomNode(int32_t nodeId, const std::string& viewKey)
{
    auto node = MakeRefPtr<CustomNode>(nodeId, viewKey);
    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

void CustomNode::Build(std::shared_ptr<std::list<ExtraInfo>> extraInfos)
{}

bool CustomNode::Render(int64_t deadline)
{
    return true;
}

void CustomNode::NodeDidBuild()
{
}

void CustomNode::FireCustomDisappear()
{
}

// used in HotReload to update root view @Component
void CustomNode::FlushReload()
{
}

bool CustomNode::RenderCustomChild(int64_t deadline)
{
    return true;
}

void CustomNode::SetJSViewActive(bool active, bool isLazyForEachNode, bool isReuse)
{
}

void CustomNode::AdjustLayoutWrapperTree(const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout)
{}

RefPtr<LayoutWrapperNode> CustomNode::CreateLayoutWrapper(bool forceMeasure, bool forceLayout)
{
    return nullptr;
}

void CustomNode::MarkNeedSyncRenderTree(bool needRebuild)
{
}

RefPtr<UINode> CustomNode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    return nullptr;
}

void CustomNode::DoSetActiveChildRange(
    int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache)
{
}

std::unique_ptr<JsonValue> CustomNode::GetStateInspectorInfo()
{
    return nullptr;
}

void CustomNode::DumpComponentInfo(std::unique_ptr<JsonValue>& componentInfo)
{
}

void CustomNode::DumpDecoratorInfo(std::unique_ptr<JsonValue>& decoratorInfo)
{
}

void CustomNode::DumpInfo()
{
}

void CustomNode::FireRecycleRenderFunc()
{
}

RefPtr<CustomNode> CustomNode::FindParentCustomNode() const
{
    return nullptr;
}

void CustomNode::SetDestroying(bool isDestroying, bool cleanStatus)
{
}

bool CustomNode::FireOnCleanup()
{
    return false;
}

} // namespace OHOS::Ace::NG
