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

#include "core/components_ng/syntax/if_else_node.h"

#include <list>
#include <type_traits>

#include "base/log/ace_trace.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

RefPtr<IfElseNode> IfElseNode::GetOrCreateIfElseNode(int32_t nodeId)
{
    auto node = ElementRegister::GetInstance()->GetSpecificItemById<IfElseNode>(nodeId);
    if (node) {
        LOGD("Returning existing IfElseNode with nodeId %{public}d", nodeId);
        return node;
    }
    node = MakeRefPtr<IfElseNode>(nodeId);
    ElementRegister::GetInstance()->AddUINode(node);
    LOGD("Created new IfElseNode with nodeId %{public}d", nodeId);
    return node;
}

/*
 * how if else works:
 *
 * the transpiler generated JS code is like this(simplified, but main points shown):
 *
 * this.observeComponentCreation(..., () => {
 * If.create();
 * if (condition1) {
 *    this.ifElseBranchUpdateFunction(compilerGeneratedUniqueConstBranchId, () =>
 *          code for children first render
 *    })
 * } else if (condition2) {
 *    this.ifElseBranchUpdateFunction(compilerGeneratedUniqueConstBranchId, () =>
 *          code for children first render
 *    })
 * } else {
 *    // else added by the transpiler
 *    If.setBranchId(compilerGeneratedUniqueConstBranchId)
 * }
 * If.pop()
 *
 * - if re-renders whenever one of the variables used in 'condition' during last render has changed.
 *      - the dependent variables can change from one render of if to the next, depending if 'condition1' and
 *        'condition2' bind to different variables.
 *      - If can re-render, but the branch does not change, e.g. if 'condition1' is (this.i > 20)
 *        then If will re-render whenever i changes.
 *
 * - eDSL to JS traspiler generates a unique id for each branch of the code inside.
 *   Thereby the framework can detect that the branch has actually changed.
 *   In this case ViewPU.ifElseBranchUpdateFunction will call IfElseNode::SetBranchId to upate
 *   and it will execute the 2nd parameter lambda function to re-generate the children.
 *
 * - In case of if without else, or if ... else if ... , eDSL to JS traspiler generates
 *   an extra else clause in which to set the branchId (calls IfElseNode::SetBranchId)
 *
 * - IfElseNode::FlushUpdateAndMarkDirty is called upon If.Pop()  FIXME
 */

void IfElseNode::SetBranchId(int32_t value, std::list<int32_t>& removedElmtId)
{
    branchIdChanged_ = (branchId_ != value);
    if (branchIdChanged_) {
        LOGD("%{public}s id %{public}d, branchId changed to %{public}d", AceType::TypeName(this), GetId(), value);
        // collect elmtIds of all children and their children up to CustomNode object
        // these will be removed, but possibly with a delay if their is an animation
        // list of elmtIds is sent back to calling TS ViewPU.ifElseBranchUpdateFunction()
        CollectRemovedChildren(GetChildren(), removedElmtId);
        Clean(false, true);
        branchId_ = value;
    }
}

void IfElseNode::CollectRemovedChildren(const std::list<RefPtr<UINode>>& children, std::list<int32_t>& removedElmtId)
{
    for (auto const& child : children) {
        CollectRemovedChild(child, removedElmtId);
    }
}

void IfElseNode::CollectRemovedChild(const RefPtr<UINode>& child, std::list<int32_t>& removedElmtId)
{
    LOGD("add %{public}s elmtId %{public}d", child->GetTag().c_str(), (int32_t)child->GetId());
    removedElmtId.emplace_back(child->GetId());
    if (child->GetTag() != V2::JS_VIEW_ETS_TAG) {
        // add CustomNode but do not recurse into its children
        CollectRemovedChildren(child->GetChildren(), removedElmtId);
    }
}

void IfElseNode::FlushUpdateAndMarkDirty()
{
    if (branchIdChanged_) {
        LOGD("%{public}s id %{public}d, branchId changed, resetting with %{public}d new children",
            AceType::TypeName(this), GetId(), static_cast<int32_t>(GetChildren().size()));
        // mark parent dirty to flush measure.
        MarkNeedFrameFlushDirty(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    }
    branchIdChanged_ = false;
}

bool IfElseNode::TryRetake(const std::string& id)
{
    auto node = GetDisappearingChildById(id);
    if (node) {
        AddChild(node);
        // for geometryTransition, let all reused children call UpdateGeometryTransition.
        LayoutProperty::UpdateAllGeometryTransition(node);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG