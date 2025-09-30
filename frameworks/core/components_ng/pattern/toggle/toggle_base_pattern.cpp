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

#include "core/components_ng/pattern/toggle/toggle_base_pattern.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
 
namespace OHOS::Ace::NG {

constexpr char TOGGLEBASE_ETS_TAG[] = "ToggleBase";

void ToggleBasePattern::MountToHolder(RefPtr<FrameNode> child)
{
    auto holder = GetOrCreateHolderNode();
    child->MountToParent(holder);
}

RefPtr<FrameNode> ToggleBasePattern::GetOrCreateHolderNode()
{
    if (holder_ == nullptr) {
        holder_ = FrameNode::GetOrCreateFrameNode(TOGGLEBASE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwitchPattern>(); });
    }
    ViewAbstract::SetVisibility(AceType::RawPtr(holder_), VisibleType::INVISIBLE);
    return holder_;
}
} // namespace OHOS::Ace::NG