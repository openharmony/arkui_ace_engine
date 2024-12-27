/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "interfaces/inner_api/ace_kit/include/ui/view_stack/view_stack_processor.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"

#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::Kit {

int32_t ViewStackProcessor::ClaimNodeId()
{
    return NG::ViewStackProcessor::GetInstance()->ClaimNodeId();
}

void ViewStackProcessor::Push(const RefPtr<FrameNode>& node)
{
    auto nodeImpl = AceType::DynamicCast<FrameNodeImpl>(node);
    CHECK_NULL_VOID(nodeImpl);
    NG::ViewStackProcessor::GetInstance()->Push(nodeImpl->PopAceNode());
}
} // namespace OHOS::Ace::Kit
