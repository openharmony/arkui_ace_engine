/*
* Copyright (c) 2025 Huawei Device Co., Ltd.
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BOTTOM_TAB_BAR_STYLE_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BOTTOM_TAB_BAR_STYLE_PEER_IMPL_H

#include "base/memory/ace_type.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/components_ng/pattern/tabs/tab_content_model.h"
#include "core/components_ng/property/measure_property.h"

struct BottomTabBarStylePeer final {
    std::optional<std::string> text = std::nullopt;
    std::optional<std::string> icon = std::nullopt;
    std::optional<OHOS::Ace::LabelStyle> labelStyle = std::nullopt;
    std::optional<OHOS::Ace::NG::PaddingProperty> padding = std::nullopt;
    bool useLocalizedPadding = false;
    std::optional<OHOS::Ace::LayoutMode> layoutMode = std::nullopt;
    std::optional<OHOS::Ace::FlexAlign> verticalAlign = std::nullopt;
    std::optional<bool> symmetricExtensible = std::nullopt;
    std::optional<std::string> id = std::nullopt;
    std::optional<OHOS::Ace::IconStyle> iconStyle = std::nullopt;
protected:
    BottomTabBarStylePeer() = default;
    ~BottomTabBarStylePeer() = default;
    friend OHOS::Ace::NG::PeerUtils;
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BOTTOM_TAB_BAR_STYLE_PEER_IMPL_H