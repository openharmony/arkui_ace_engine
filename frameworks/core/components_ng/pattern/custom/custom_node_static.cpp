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

#include "core/components_ng/pattern/custom/custom_node_static.h"

#include "core/components_ng/pattern/custom/custom_node.h"


namespace OHOS::Ace::NG {
CustomNode* CustomNodeStatic::ConstructCustomNode(int32_t id)
{
    auto customNode = NG::CustomNode::CreateCustomNode(id, "");
    customNode->IncRefCount();
    TAG_LOGI(AceLogTag::ACE_NATIVE_NODE, "ConstructCustomNode: customNode %{public}p %{public}d", AceType::RawPtr(customNode), id);
    return AceType::RawPtr(customNode);
}
} // namespace OHOS::Ace::NG
