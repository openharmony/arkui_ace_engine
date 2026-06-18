/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/focus_state.h"
namespace OHOS::Ace::NG {
bool FocusHub::RequestFocusImmediately(FocusReason reason)
{
    (void)reason;
    return true;
}
bool FocusHub::HandleFocusTravel(const FocusEvent& event)
{
    (void)event;
    return false;
}
bool FocusHub::IsEnabled() const
{
    return true;
}
bool FocusHub::IsShow() const
{
    return true;
}
void FocusHub::LostFocus(BlurReason reason)
{
    (void)reason;
}
bool FocusHub::PaintFocusState(bool)
{
    return false;
}
void FocusHub::SetFocusable(bool focusable, bool isExplicit)
{
    (void)focusable;
    (void)isExplicit;
}

bool FocusHub::IsFocusableNode()
{
    return true;
}

std::string FocusState::GetFrameName() const
{
    return "NULL";
}

int32_t FocusState::GetFrameId() const
{
    return -1;
}

bool FocusHub::TriggerFocusScroll()
{
    return false;
}

WeakPtr<FocusHub> FocusHub::GetUnfocusableParentFocusNode()
{
    return nullptr;
}

void FocusHub::DumpFocusTree(int32_t depth, bool hasJson)
{
    (void)depth;
    (void)hasJson;
}

RefPtr<FocusManager> FocusHub::GetFocusManager() const
{
    return nullptr;
}

bool FocusHub::RequestFocusImmediatelyById(const std::string& id, bool isSyncRequest)
{
    (void)id;
    (void)isSyncRequest;
    return false;
}

RefPtr<FrameNode> FocusState::GetFrameNode() const
{
    return nullptr;
}

void FocusHub::RemoveSelf(BlurReason reason)
{
    (void)reason;
}

void FocusHub::SetFocusType(FocusType) {}

} // namespace OHOS::Ace::NG
