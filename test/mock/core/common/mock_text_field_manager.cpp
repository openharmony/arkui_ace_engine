/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/common/text_field_manager.h"

namespace OHOS::Ace {
void TextFieldManager::SetClickPosition(const Offset& position)
{
    position_ = position;
}

void TextFieldManager::SetScrollElement(int32_t pageId, const WeakPtr<ScrollElement>& scrollElement)
{
    auto iter = scrollMap_.find(pageId);
    if (iter == scrollMap_.end()) {
        scrollMap_.try_emplace(pageId, scrollElement);
    }
}

void TextFieldManager::MovePage(int32_t pageId, const Offset& rootRect, double offsetHeight)
{
    hasMove_ = false;
}

void TextFieldManager::RemovePageId(int32_t pageId)
{
    scrollMap_.erase(pageId);
}

const Offset& TextFieldManager::GetClickPosition()
{
    return position_;
}

bool TextFieldManager::UpdatePanelForVirtualKeyboard(double offsetY, double fullHeight)
{
    return true;
}

bool TextFieldManager::ResetSlidingPanelParentHeight()
{
    return true;
}

void TextFieldManager::ClearOnFocusTextField()
{
    onFocusTextField_ = nullptr;
}
}; // namespace OHOS::Ace
