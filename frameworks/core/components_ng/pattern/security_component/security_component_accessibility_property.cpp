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

#include "base/utils/utf_helper.h"
#include "core/components_ng/pattern/security_component/security_component_accessibility_property.h"

#include "core/components_ng/pattern/security_component/security_component_log.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "location_button/location_button_common.h"
#include "paste_button/paste_button_common.h"
#include "save_button/save_button_common.h"
#include "security_component_theme.h"

namespace OHOS::Ace::NG {
std::string SecurityComponentAccessibilityProperty::GetText() const
{
    std::string value = "";
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, value);
    for (const auto& child : frameNode->GetChildren()) {
        auto node = AceType::DynamicCast<FrameNode, UINode>(child);
        CHECK_NULL_RETURN(node, value);
        if (node->GetTag() == V2::TEXT_ETS_TAG) {
            auto textLayoutProperty = node->GetLayoutProperty<TextLayoutProperty>();
            if (textLayoutProperty == nullptr) {
                break;
            }
            value = UtfUtils::Str16ToStr8(textLayoutProperty->GetContentValue(std::u16string(u"")));
            break;
        }
    }
    if (value.empty()) {
        std::string nodeType = frameNode->GetTag();
        auto pipeline = frameNode->GetContextRefPtr();
        if (pipeline == nullptr) {
            SC_LOG_ERROR("Pipeline is null.");
            return std::string();
        }
        auto theme = pipeline->GetTheme<SecurityComponentTheme>();
        if (theme == nullptr) {
            SC_LOG_ERROR("Theme is null.");
            return std::string();
        }
        if (nodeType == V2::LOCATION_BUTTON_ETS_TAG) {
            value = theme->GetLocationDescriptions(
                static_cast<int32_t>(LocationButtonLocationDescription::LOCATING));
        } else if (nodeType == V2::PASTE_BUTTON_ETS_TAG) {
            value = theme->GetPasteDescriptions(
                static_cast<int32_t>(PasteButtonPasteDescription::PASTE));
        } else if (nodeType == V2::SAVE_BUTTON_ETS_TAG) {
            value = theme->GetSaveDescriptions(
                static_cast<int32_t>(SaveButtonSaveDescription::SAVE));
        }
    }
    return value;
}
} // namespace OHOS::Ace::NG
