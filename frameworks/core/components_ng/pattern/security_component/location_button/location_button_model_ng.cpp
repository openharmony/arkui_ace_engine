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

#include "core/components_ng/pattern/security_component/location_button/location_button_model_ng.h"

#include "core/components_ng/pattern/security_component/security_component_pattern.h"

namespace OHOS::Ace::NG {
std::unique_ptr<LocationButtonModelNG> LocationButtonModelNG::instance_ = nullptr;
std::mutex LocationButtonModelNG::mutex_;

static const std::vector<uint32_t> ICON_RESOURCE_TABLE = {
    static_cast<uint32_t>(InternalResource::ResourceId::LOCATION_BUTTON_FILLED_SVG),
    static_cast<uint32_t>(InternalResource::ResourceId::LOCATION_BUTTON_LINE_SVG)
};

LocationButtonModelNG* LocationButtonModelNG::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_.reset(new LocationButtonModelNG());
        }
    }
    return instance_.get();
}

void LocationButtonModelNG::Create(int32_t text, int32_t icon,
    int32_t backgroundType, bool isArkuiComponent)
{
    SecurityComponentModelNG::CreateCommon(V2::LOCATION_BUTTON_ETS_TAG,
        text, icon, backgroundType, []() { return AceType::MakeRefPtr<SecurityComponentPattern>(); }, isArkuiComponent);
}

bool LocationButtonModelNG::GetIconResource(int32_t iconStyle, InternalResource::ResourceId& id)
{
    if ((iconStyle < 0) || (static_cast<uint32_t>(iconStyle) >= ICON_RESOURCE_TABLE.size())) {
        return false;
    }
    id = static_cast<InternalResource::ResourceId>(ICON_RESOURCE_TABLE[iconStyle]);
    return true;
}

bool LocationButtonModelNG::GetTextResource(int32_t textStyle, std::string& text)
{
    auto theme = GetTheme();
    if (theme == nullptr) {
        return false;
    }
    text = theme->GetLocationDescriptions(textStyle);
    return true;
}

bool LocationButtonModelNG::GetIconResourceStatic(int32_t iconStyle, InternalResource::ResourceId& id)
{
    if ((iconStyle < 0) || (static_cast<uint32_t>(iconStyle) >= ICON_RESOURCE_TABLE.size())) {
        return false;
    }
    id = static_cast<InternalResource::ResourceId>(ICON_RESOURCE_TABLE[iconStyle]);
    return true;
}

bool LocationButtonModelNG::GetTextResourceStatic(int32_t textStyle, std::string& text)
{
    auto theme = GetTheme();
    if (theme == nullptr) {
        return false;
    }
    text = theme->GetLocationDescriptions(textStyle);
    return true;
}

RefPtr<FrameNode> LocationButtonModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::LOCATION_BUTTON_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SecurityComponentPattern>(); });

    return frameNode;
}

bool LocationButtonModelNG::InitLocationButton(FrameNode* frameNode,
    const LocationButtonStyle& style, bool isArkuiComponent)
{
    CHECK_NULL_RETURN(frameNode, false);

    auto text = style.text.value_or(LocationButtonLocationDescription::TEXT_NULL);
    auto icon = style.icon.value_or(LocationButtonIconStyle::ICON_NULL);
    auto backgroundType = style.backgroundType.value_or(ButtonType::CAPSULE);

    if ((text == LocationButtonLocationDescription::TEXT_NULL) && (icon == LocationButtonIconStyle::ICON_NULL)) {
        // set default values
        text = LocationButtonStyle::DEFAULT_TEXT;
        icon = LocationButtonStyle::DEFAULT_ICON;
        backgroundType = LocationButtonStyle::DEFAULT_BACKGROUND_TYPE;
    }

    SecurityComponentElementStyle secCompStyle = {
        .text = static_cast<int32_t>(text),
        .icon = static_cast<int32_t>(icon),
        .backgroundType = static_cast<int32_t>(backgroundType)
    };
    return SecurityComponentModelNG::InitSecurityComponent(frameNode, secCompStyle, isArkuiComponent,
        LocationButtonModelNG::GetIconResourceStatic, LocationButtonModelNG::GetTextResourceStatic);
}
} // namespace OHOS::Ace::NG
