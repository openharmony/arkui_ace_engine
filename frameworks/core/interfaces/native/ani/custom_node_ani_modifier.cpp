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

#include "custom_node_ani_modifier.h"

#include "core/components_ng/pattern/custom/custom_node.h"
#include "base/log/log.h"
 
#include <memory>

namespace OHOS::Ace::NG {

ani_long ConstructCustomNode(ani_int id)
{
    std::string key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(std::to_string(id));
    auto customNode = NG::CustomNode::CreateCustomNode(id, key);
    customNode->IncRefCount();
    TAG_LOGI(AceLogTag::ACE_NATIVE_NODE, "ConstructCustomNode: customNode %{public}p %{public}d",
        AceType::RawPtr(customNode), id);
    if (customNode) {
        return reinterpret_cast<ani_long>(AceType::RawPtr(customNode));
    }
    return 0;
}

const ArkUIAniCustomNodeModifier* GetCustomNodeAniModifier()
{
    static const ArkUIAniCustomNodeModifier impl = { .constructCustomNode = OHOS::Ace::NG::ConstructCustomNode };
    return &impl;
}

} // namespace OHOS::Ace::NG