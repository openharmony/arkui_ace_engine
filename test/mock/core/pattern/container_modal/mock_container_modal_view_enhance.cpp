/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> ContainerModalViewEnhance::Create(RefPtr<FrameNode>& content)
{
    auto containerModalNode = FrameNode::CreateFrameNode(
        "ContainerModal", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPattern>());
    return containerModalNode;
}
} // namespace OHOS::Ace::NG
