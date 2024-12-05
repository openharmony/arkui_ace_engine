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

#include "core/components_ng/pattern/security_component/save_button/save_button_model_ng.h"

#include "core/components_ng/pattern/security_component/security_component_pattern.h"

namespace OHOS::Ace::NG {
std::unique_ptr<SaveButtonModelNG> SaveButtonModelNG::instance_ = nullptr;
std::mutex SaveButtonModelNG::mutex_;

static const std::vector<uint32_t> ICON_RESOURCE_TABLE = {
    static_cast<uint32_t>(InternalResource::ResourceId::SAVE_BUTTON_FILLED_SVG),
    static_cast<uint32_t>(InternalResource::ResourceId::SAVE_BUTTON_LINE_SVG),
    static_cast<uint32_t>(InternalResource::ResourceId::SAVE_BUTTON_PICTURE_SVG)
};

SaveButtonModelNG* SaveButtonModelNG::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_.reset(new SaveButtonModelNG());
        }
    }
    return instance_.get();
}

void SaveButtonModelNG::Create(int32_t text, int32_t icon,
    int32_t backgroundType, bool isArkuiComponent)
{
    SecurityComponentModelNG::CreateCommon(V2::SAVE_BUTTON_ETS_TAG,
        text, icon, backgroundType, []() { return AceType::MakeRefPtr<SecurityComponentPattern>(); }, isArkuiComponent);
}

bool SaveButtonModelNG::GetIconResource(int32_t iconStyle, InternalResource::ResourceId& id)
{
    if ((iconStyle < 0) || (static_cast<uint32_t>(iconStyle) >= ICON_RESOURCE_TABLE.size())) {
        return false;
    }
    id = static_cast<InternalResource::ResourceId>(ICON_RESOURCE_TABLE[iconStyle]);
    return true;
}

bool SaveButtonModelNG::GetTextResource(int32_t textStyle, std::string& text)
{
    auto theme = GetTheme();
    if (theme == nullptr) {
        return false;
    }
    text = theme->GetSaveDescriptions(textStyle);
    return true;
}

bool SaveButtonModelNG::GetIconResourceStatic(int32_t iconStyle, InternalResource::ResourceId& id)
{
    if ((iconStyle < 0) || (static_cast<uint32_t>(iconStyle) >= ICON_RESOURCE_TABLE.size())) {
        return false;
    }
    id = static_cast<InternalResource::ResourceId>(ICON_RESOURCE_TABLE[iconStyle]);
    return true;
}

bool SaveButtonModelNG::GetTextResourceStatic(int32_t textStyle, std::string& text)
{
    auto theme = GetTheme();
    if (theme == nullptr) {
        return false;
    }
    text = theme->GetSaveDescriptions(textStyle);
    return true;
}

RefPtr<FrameNode> SaveButtonModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SAVE_BUTTON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SecurityComponentPattern>(); });

    return frameNode;
}

bool SaveButtonModelNG::InitSaveButton(FrameNode* frameNode,
    const SaveButtonStyle& style, bool isArkuiComponent)
{
    CHECK_NULL_RETURN(frameNode, false);

    auto text = style.text.value_or(SaveButtonSaveDescription::TEXT_NULL);
    auto icon = style.icon.value_or(SaveButtonIconStyle::ICON_NULL);
    auto backgroundType = style.backgroundType.value_or(ButtonType::CAPSULE);

    if ((text == SaveButtonSaveDescription::TEXT_NULL) && (icon == SaveButtonIconStyle::ICON_NULL)) {
        // set default values
        text = SaveButtonStyle::DEFAULT_TEXT;
        icon = SaveButtonStyle::DEFAULT_ICON;
        backgroundType = SaveButtonStyle::DEFAULT_BACKGROUND_TYPE;
    }

    SecurityComponentElementStyle secCompStyle = {
        .text = static_cast<int32_t>(text),
        .icon = static_cast<int32_t>(icon),
        .backgroundType = static_cast<int32_t>(backgroundType)
    };
    return SecurityComponentModelNG::InitSecurityComponent(frameNode, secCompStyle, isArkuiComponent,
        SaveButtonModelNG::GetIconResourceStatic, SaveButtonModelNG::GetTextResourceStatic);
}
} // namespace OHOS::Ace::NG
