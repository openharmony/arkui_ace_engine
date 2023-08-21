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

#include "core/components_ng/base/view_partial_update_model_ng.h"

#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"

namespace OHOS::Ace::NG {

RefPtr<AceType> ViewPartialUpdateModelNG::CreateNode(NodeInfoPU&& info)
{
    ACE_SCOPED_TRACE("JSView::CreateSpecializedComponent");
    // create component, return new something, need to set proper ID
    auto viewId = NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto viewIdStr = std::to_string(viewId);
    if (info.updateViewIdFunc) {
        info.updateViewIdFunc(viewIdStr);
    }
    auto key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewIdStr);
    LOGD("Creating CustomNode with claimed elmtId %{public}d.", viewId);
    RefPtr<NG::CustomNodeBase> customNode;
    if (info.hasMeasureOrLayout) {
        customNode = NG::CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(viewId, key);
        auto customMeasureLayoutNode = AceType::DynamicCast<NG::CustomMeasureLayoutNode>(customNode);
        if (info.measureSizeFunc && customMeasureLayoutNode) {
            customMeasureLayoutNode->SetMeasureFunction(std::move(info.measureSizeFunc));
        } else if (info.measureFunc && customMeasureLayoutNode) {
            customMeasureLayoutNode->SetMeasureFunction(std::move(info.measureFunc));
        }
        if (info.placeChildrenFunc && customMeasureLayoutNode) {
            customMeasureLayoutNode->SetLayoutFunction(std::move(info.placeChildrenFunc));
        } else if (info.layoutFunc && customMeasureLayoutNode) {
            customMeasureLayoutNode->SetLayoutFunction(std::move(info.layoutFunc));
        }
    } else {
        customNode = NG::CustomNode::CreateCustomNode(viewId, key);
    }

    if (info.updateNodeFunc) {
        info.updateNodeFunc(customNode);
    }
    customNode->SetAppearFunction(std::move(info.appearFunc));
    auto renderFunc = [renderFunction = std::move(info.renderFunc)]() -> RefPtr<UINode> {
        auto node = renderFunction();
        return AceType::DynamicCast<UINode>(node);
    };
    customNode->SetRenderFunction(std::move(renderFunc));
    customNode->SetUpdateFunction(std::move(info.updateFunc));
    customNode->SetDestroyFunction(std::move(info.removeFunc));
    customNode->SetPageTransitionFunction(std::move(info.pageTransitionFunc));
    customNode->SetForceUpdateNodeFunc(std::move(info.nodeUpdateFunc));
    customNode->SetReloadFunction(std::move(info.reloadFunc));
    auto completeReloadFunc = [reloadFunc = std::move(info.completeReloadFunc)]() -> RefPtr<UINode> {
        return AceType::DynamicCast<UINode>(reloadFunc());
    };
    customNode->SetCompleteReloadFunc(std::move(completeReloadFunc));
    customNode->SetJSViewName(std::move(info.jsViewName));
    customNode->SetRecycleFunction(std::move(info.recycleCustomNodeFunc));
    customNode->SetSetActiveFunc(std::move(info.setActiveFunc));
    return customNode;
}

bool ViewPartialUpdateModelNG::MarkNeedUpdate(const WeakPtr<AceType>& node)
{
    auto weakNode = AceType::DynamicCast<NG::CustomNodeBase>(node);
    auto customNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(customNode, false);
    customNode->MarkNeedUpdate();
    return true;
}

void ViewPartialUpdateModelNG::FinishUpdate(
    const WeakPtr<AceType>& viewNode, int32_t id, std::function<void(const UpdateTask&)>&& emplaceTaskFunc)
{
    NG::ViewStackProcessor::GetInstance()->FlushRerenderTask();
}

} // namespace OHOS::Ace::NG
