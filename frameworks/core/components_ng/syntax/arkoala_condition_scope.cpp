/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/syntax/arkoala_condition_scope.h"

#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {

namespace {

constexpr char CONDITION_SCOPE_TAG[] = "ConditionScope";

}

ConditionScopeNode::ConditionScopeNode(int32_t nodeId) : UINode(CONDITION_SCOPE_TAG, nodeId) {}

void ConditionScopeNode::AddChild(
    const RefPtr<UINode>& child, int32_t slot, bool silently, bool addDefaultTransition, bool addModalUiextension)
{
    CHECK_NULL_VOID(child);
    UINode::AddChild(child, slot, silently, addDefaultTransition, addModalUiextension);
    // for geometryTransition, let all reused children call UpdateGeometryTransition.
    LayoutProperty::UpdateAllGeometryTransition(child);
}

} // namespace OHOS::Ace::NG
