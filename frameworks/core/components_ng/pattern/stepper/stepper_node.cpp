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

#include "core/components_ng/pattern/stepper/stepper_node.h"

namespace OHOS::Ace::NG {

RefPtr<StepperNode> StepperNode::GetOrCreateStepperNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto stepperNode = ElementRegister::GetInstance()->GetSpecificItemById<StepperNode>(nodeId);
    if (stepperNode) {
        if (stepperNode->GetTag() == tag) {
            return stepperNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = stepperNode->GetParent();
        if (parent) {
            parent->RemoveChild(stepperNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    stepperNode = AceType::MakeRefPtr<StepperNode>(tag, nodeId, pattern, false);
    stepperNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(stepperNode);
    return stepperNode;
}

void StepperNode::AddChildToGroup(const RefPtr<UINode>& child, int32_t slot)
{
    int32_t swiperId = GetSwiperId();
    auto swiperNode = GetChildAtIndex(GetChildIndexById(swiperId));
    if (swiperNode) {
        child->MountToParent(swiperNode, slot);
    }
}

void StepperNode::DeleteChildFromGroup(int32_t slot)
{
    int32_t swiperId = GetSwiperId();
    auto swiper = GetChildAtIndex(GetChildIndexById(swiperId));
    CHECK_NULL_VOID(swiper);
    swiper->RemoveChildAtIndex(slot);
}

} // namespace OHOS::Ace::NG