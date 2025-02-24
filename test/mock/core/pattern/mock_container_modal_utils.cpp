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

#include "base/resource/internal_resource.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/container_modal/container_modal_utils.h"
#include "core/components_ng/pattern/custom/custom_title_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"

namespace OHOS::Ace::NG {
bool ExecuteCustomTitleAbc()
{
    auto custom = CustomTitleNode::CreateCustomNode(-1, "");
    ViewStackProcessor::GetInstance()->SetCustomTitleNode(custom);
    return true;
}

bool ExecuteCustomWindowMaskAbc()
{
    return true;
}

RefPtr<FrameNode> BuildTitleNodeForCj()
{
    return FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
}

RefPtr<FrameNode> BuildControlButtonForCj(InternalResource::ResourceId icon, GestureEventFunc&& clickCallback,
    bool isCloseButton = false, bool canDrag = false)
{
    return FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
}
} // namespace OHOS::Ace::NG
