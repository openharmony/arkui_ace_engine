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

#include "core/components_ng/pattern/dialog/dialog_pattern.h"

namespace OHOS::Ace::NG {
void DialogPattern::OnModifyDone()
{
}

void DialogPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
}

void DialogPattern::HandleClick(const GestureEvent& info)
{
}

void DialogPattern::PopDialog(int32_t buttonIdx = -1)
{
}

// set render context properties of content frame
void DialogPattern::UpdateContentRenderContext(const RefPtr<FrameNode>& contentNode, const DialogProperties& props)
{
}

void DialogPattern::BuildChild(const DialogProperties& props)
{
}

RefPtr<FrameNode> DialogPattern::BuildTitle(const DialogProperties& dialogProperties)
{
    return nullptr;
}

RefPtr<FrameNode> DialogPattern::BuildContent(const DialogProperties& props)
{
    return nullptr;
}

// to close dialog when clicked, use button index in Prompt to trigger success callback
void DialogPattern::BindCloseCallBack(const RefPtr<GestureEventHub>& hub, int32_t buttonIdx)
{
}

RefPtr<FrameNode> DialogPattern::CreateButton(
    const ButtonInfo& params, int32_t index, bool isCancel, bool useRelativeLayout)
{
    return nullptr;
}

// alert dialog buttons
RefPtr<FrameNode> DialogPattern::BuildButtons(const std::vector<ButtonInfo>& buttons)
{
    return nullptr;
}

RefPtr<FrameNode> DialogPattern::CreateButtonText(const std::string& text, const std::string& colorStr)
{
    return nullptr;
}

RefPtr<FrameNode> DialogPattern::BuildSheetItem(const ActionSheetInfo& item)
{
    return nullptr;
}

RefPtr<FrameNode> DialogPattern::BuildSheet(const std::vector<ActionSheetInfo>& sheets)
{
    return nullptr;
}

RefPtr<FrameNode> DialogPattern::BuildMenu(const std::vector<ButtonInfo>& buttons)
{
    return nullptr;
}

// XTS inspector
void DialogPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
}

void DialogPattern::OnColorConfigurationUpdate() {}
} // namespace OHOS::Ace::NG
