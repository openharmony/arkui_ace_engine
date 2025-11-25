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

#include "ui/view/components/stack.h"

#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "ui/base/referenced.h"
#include "ui/view_stack/view_stack_processor.h"
#include "view/frame_node_impl.h"

namespace OHOS::Ace::Kit {

Stack::Stack()
{
    node_ = AceType::MakeRefPtr<FrameNodeImpl>(
        NG::StackModelNG::CreateFrameNode(Ace::Kit::ViewStackProcessor::ClaimNodeId()));
}

Stack::Stack(RefPtr<FrameNode>& node)
{
    node_ = node;
}

Stack::~Stack() = default;

RefPtr<Stack> Stack::Create()
{
    return Referenced::MakeRefPtr<Stack>();
}

RefPtr<Stack> Stack::Create(RefPtr<FrameNode>& node)
{
    return Referenced::MakeRefPtr<Stack>(node);
}

void Stack::SetAlignment(Ace::Alignment align)
{
    NG::StackModelNG::SetAlignment(reinterpret_cast<AceNode*>(node_->GetHandle()), align);
}

} // namespace OHOS::Ace::Kit
