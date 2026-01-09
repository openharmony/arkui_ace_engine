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

#include "compatible/components/label/modifier/label_modifier.h"

namespace OHOS::Ace::LabelModifier {

void SetTargetNode(const RefPtr<Framework::DOMNode>& targetNode, const RefPtr<Framework::DOMNode>& idNode)
{
    auto labelNode = AceType::DynamicCast<Framework::DOMLabel>(targetNode);
    if (labelNode) {
        labelNode->SetTargetNode(idNode);
    }
}

const ArkUILabelModifierCompatible* GetLabelModifierCompatible()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUILabelModifierCompatible impl = {
        .setTargetNode = SetTargetNode,
    };
    CHECK_INITIALIZED_FIELDS_END(impl, 0, 0, 0); // don't move this line
    return &impl;
}

} // namespace OHOS::Ace::LabelModifier