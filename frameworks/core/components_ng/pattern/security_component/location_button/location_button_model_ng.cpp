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
} // namespace OHOS::Ace::NG
