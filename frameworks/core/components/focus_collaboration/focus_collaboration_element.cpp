/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/focus_collaboration/focus_collaboration_element.h"

#include "core/components/focus_animation/focus_animation_component.h"
#include "core/components/shadow/shadow_component.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace {

void FocusCollaborationElement::PerformBuild()
{
    RefPtr<ComponentGroup> group = AceType::DynamicCast<ComponentGroup>(component_);
    if (group && group->GetChildren().size() == 1) {
        auto focusAnimation = AceType::MakeRefPtr<FocusAnimationComponent>(isRoot_);
        auto shadow = AceType::MakeRefPtr<ShadowComponent>();
        Component::MergeRSNode(focusAnimation);
        Component::MergeRSNode(shadow);
        group->AppendChild(focusAnimation);
        group->AppendChild(shadow);
    }
    ComponentGroupElement::PerformBuild();
}

} // namespace OHOS::Ace
