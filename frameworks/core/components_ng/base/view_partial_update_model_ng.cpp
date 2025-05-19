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

#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom/custom_title_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
#include "core/components_ng/pattern/custom/custom_app_bar_node.h"

namespace OHOS::Ace::NG {

RefPtr<AceType> ViewPartialUpdateModelNG::CreateNode(NodeInfoPU&& info)
{
    // create component, return new something, need to set proper ID
    auto viewId = NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", info.jsViewName.c_str(), viewId);
    auto viewIdStr = std::to_string(viewId);
    if (info.updateViewIdFunc) {
        info.updateViewIdFunc(viewIdStr);
    }
    auto key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(viewIdStr);
    RefPtr<NG::CustomNodeBase> customNode;
    if (info.isCustomTitle) {
        customNode = NG::CustomTitleNode::CreateCustomTitleNode(viewId, key);
    } else if (info.isCustomAppBar) {
        customNode = NG::CustomAppBarNode::CreateCustomAppBarNode(viewId, key);
    } else if (info.hasMeasureOrLayout) {
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
        customNode->SetExtraInfo(std::move(info.extraInfo));
    }

    if (info.updateNodeFunc) {
        info.updateNodeFunc(customNode);
    }
    customNode->SetAppearFunction(std::move(info.appearFunc));
    customNode->SetDidBuildFunction(std::move(info.didBuildFunc));
    auto renderFunc =
        [renderFunction = std::move(info.renderFunc)](int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        auto node = renderFunction(deadline, isTimeout);
        return AceType::DynamicCast<UINode>(node);
    };
    customNode->SetRenderFunction(std::move(renderFunc));
    customNode->SetUpdateFunction(std::move(info.updateFunc));
    customNode->SetDestroyFunction(std::move(info.removeFunc));
    customNode->SetPageTransitionFunction(std::move(info.pageTransitionFunc));
    customNode->SetForceUpdateNodeFunc(std::move(info.nodeUpdateFunc));
    customNode->SetHasNodeUpdateFunc(std::move(info.hasNodeUpdateFunc));
    customNode->SetReloadFunction(std::move(info.reloadFunc));
    customNode->SetThisFunc(std::move(info.getThisFunc));
    auto completeReloadFunc =
        [reloadFunc = std::move(info.completeReloadFunc)](int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        return AceType::DynamicCast<UINode>(reloadFunc(deadline, isTimeout));
    };
    customNode->SetCompleteReloadFunc(std::move(completeReloadFunc));
    customNode->SetJSViewName(std::move(info.jsViewName));
    customNode->SetIsV2(std::move(info.isV2));
    customNode->SetRecycleFunction(std::move(info.recycleCustomNodeFunc));
    customNode->SetSetActiveFunc(std::move(info.setActiveFunc));
    customNode->SetOnDumpInfoFunc(std::move(info.onDumpInfoFunc));
    customNode->SetOnDumpInspectorFunc(std::move(info.onDumpInspectorFunc));
    customNode->SetClearAllRecycleFunc(std::move(info.clearAllRecycleFunc));
    customNode->SetOnRecycleFunc(std::move(info.recycleFunc));
    customNode->SetOnReuseFunc(std::move(info.reuseFunc));
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

bool ViewPartialUpdateModelNG::AllowReusableV2Descendant(const WeakPtr<AceType>& viewNode)
{
    // check if this @ReusbaleV2 @ComponentV2 instance is inside RepeatVirtualScroll
    // and created within a .template builder function
    // cast to UINode as here viewNode can be instance of CustomMeasureLayoutNode
    auto weak = AceType::DynamicCast<NG::UINode>(viewNode);
    RefPtr<UINode> node = weak.Upgrade();
    CHECK_NULL_RETURN(node, false);

    while (node->GetParent() && (node->GetParent()->GetTag() != V2::JS_VIEW_ETS_TAG)) {
        if (AceType::DynamicCast<RepeatVirtualScrollNode>(node->GetParent()) != nullptr) {
            break;
        }
        if (AceType::DynamicCast<RepeatVirtualScroll2Node>(node->GetParent()) != nullptr) {
            break;
        }
        node = node->GetParent();
    }

    bool result = ((node->GetParent() == nullptr) || (node->GetParent()->GetTag() == V2::JS_VIEW_ETS_TAG) ||
                   (node->IsAllowReusableV2Descendant()));
    return result;
}
} // namespace OHOS::Ace::NG
