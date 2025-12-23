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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SUB_TAB_BAR_STYLE_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SUB_TAB_BAR_STYLE_PEER_IMPL_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/components_ng/pattern/tabs/tab_content_model.h"
#include "core/components_ng/property/measure_property.h"

struct SubTabBarStylePeer final : public OHOS::Ace::Referenced {
    std::optional<std::string> content = std::nullopt;
    std::optional<OHOS::Ace::IndicatorStyle> indicator = std::nullopt;
    std::optional<OHOS::Ace::SelectedMode> selectedMode = std::nullopt;
    std::optional<OHOS::Ace::BoardStyle> board = std::nullopt;
    std::optional<OHOS::Ace::LabelStyle> labelStyle = std::nullopt;
    std::optional<OHOS::Ace::NG::PaddingProperty> padding = std::nullopt;
    bool useLocalizedPadding = false;
    std::optional<std::string> id = std::nullopt;
    SubTabBarStylePeer() = default;
    ~SubTabBarStylePeer() = default;
    friend OHOS::Ace::NG::PeerUtils;
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SUB_TAB_BAR_STYLE_PEER_IMPL_H