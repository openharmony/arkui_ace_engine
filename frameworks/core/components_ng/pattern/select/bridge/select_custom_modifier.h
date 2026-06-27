/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_BRIDGE_SELECT_CUSTOM_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_BRIDGE_SELECT_CUSTOM_MODIFIER_H

#include "core/interfaces/native/node/node_api.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace {
class Color;
class PopupParam;
enum class AvoidanceMode;
namespace NG {
class FrameNode;
struct SelectDivider;
class MenuItemConfiguration;
using SelectEvent = std::function<void(int32_t, const std::string&)>;
using SelectMakeCallback = std::function<RefPtr<FrameNode>(const MenuItemConfiguration menuItemConfiguration)>;
} // namespace NG

struct ArkUISelectCustomModifier {
    void (*setChangeValue)(NG::FrameNode* frameNode, ArkUI_Int32 index, const std::string& convValue);
    void (*updateSelectedOptionFontFromPattern)(
        const RefPtr<NG::FrameNode>& frameNode, const RefPtr<NG::FrameNode>& host);
    void (*updateOptionFontFromPattern)(
        const RefPtr<NG::FrameNode>& frameNode, const RefPtr<NG::FrameNode>& host);
    void (*showSelectMenu)(const RefPtr<NG::FrameNode>& frameNode);
    void (*setBuilderFunc)(NG::FrameNode* frameNode, NG::SelectMakeCallback&& makeFunc);
    void (*resetBuilderFunc)(NG::FrameNode* frameNode);
    void (*setBackgroundColor)(NG::FrameNode* frameNode, const std::optional<Color>& color);
    void (*setDividerImpl)(NG::FrameNode* frameNode, const Opt_DividerOptions* options);
    void (*setOnSelect)(NG::FrameNode* frameNode, NG::SelectEvent&& onSelect);
    void (*setAvoidTarget)(RefPtr<PopupParam>& popupParam, const Opt_AvoidanceMode& src);
    void (*castAvoidTarget)(std::optional<AvoidanceMode>& dst, const Ark_AvoidanceMode& src);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_BRIDGE_SELECT_CUSTOM_MODIFIER_H