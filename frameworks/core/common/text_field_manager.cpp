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
#include "core/common/dynamic_module_helper.h"
#include "compatible/components/text_field/modifier/text_field_modifier.h"

namespace OHOS::Ace {

namespace {
const ArkUITextFieldModifierCompatible* GetTextFieldInnerModifier()
{
    static const ArkUITextFieldModifierCompatible* textFieldModifier_ = nullptr;
    if (textFieldModifier_) {
        return textFieldModifier_;
    }
    auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("textarea");
    if (loader) {
        textFieldModifier_ = reinterpret_cast<const ArkUITextFieldModifierCompatible*>(loader->GetCustomModifier());
        return textFieldModifier_;
    }
    return nullptr;
}
} // namespace

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
    auto iter = scrollMap_.find(pageId);
    if (iter == scrollMap_.end()) {
        return;
    }
    auto scrollElement = iter->second.Upgrade();
    CHECK_NULL_VOID(scrollElement);
    const auto& scroll = AceType::DynamicCast<RenderScroll>(scrollElement->GetRenderNode());
    CHECK_NULL_VOID(scroll);
    if (GreatNotEqual(position_.GetY(), rootRect.GetY())) {
        hasMove_ = true;
        scroll->SetNeedMove(true);
    }

    if (LessNotEqual(offsetHeight, 0) && hasMove_) {
        scroll->SetNeedMove(false);
        hasMove_ = false;
    }
}

void TextFieldManager::SetHeight(float height)
{
    height_ = height;
}

float TextFieldManager::GetHeight() const
{
    return height_;
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
    auto onFocusTextField = onFocusTextField_.Upgrade();
    CHECK_NULL_RETURN(onFocusTextField, false);
#ifndef NG_BUILD
    auto* modifier = GetTextFieldInnerModifier();
    CHECK_NULL_RETURN(modifier, false);
    if (!modifier->liftPanelForVirtualKeyboard(onFocusTextField, offsetY, fullHeight)) {
        return false;
    }
#endif
    return true;
}

bool TextFieldManager::ResetSlidingPanelParentHeight()
{
    auto onFocusTextField = onFocusTextField_.Upgrade();
    CHECK_NULL_RETURN(onFocusTextField, false);
#ifndef NG_BUILD
    auto* modifier = GetTextFieldInnerModifier();
    CHECK_NULL_RETURN(modifier, false);
    if (!modifier->updatePanelHeightByCurrentMode(onFocusTextField)) {
        return false;
    }
#endif
    return true;
}

void TextFieldManager::ClearOnFocusTextField()
{
    onFocusTextField_ = nullptr;
}

}; // namespace OHOS::Ace
