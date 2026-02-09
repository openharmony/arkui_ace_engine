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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_BRIDGE_SEARCH_CUSTOM_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_BRIDGE_SEARCH_CUSTOM_MODIFIER_H

#include <vector>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text_field/text_keyboard_common_type.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/components_ng/pattern/search/search_model.h"

namespace OHOS::Ace {

namespace NG {
class FrameNode;
} // namespace NG

struct ArkUISearchCreateResourceParams {
    void* stringValueRawPtr = nullptr;
    void* placeholderRawPtr = nullptr;
    bool parseValueResult = false;
    bool parsePlaceholderResult = false;
};

struct ArkUISearchCustomModifier {
    void (*setKeyboardAppearanceConfig)(NG::FrameNode* frameNode, NG::KeyboardAppearanceConfig config);
    void (*setTextValue)(NG::FrameNode* frameNode, const std::optional<std::string>& value);
    void (*setOnChangeEvent)(NG::FrameNode* frameNode, std::function<void(const std::u16string&)>&& onChangeEvent);
    void (*createNormalSearch)(std::optional<std::u16string>& stringValue, std::optional<std::u16string>& placeholder,
        std::optional<std::string>& iconSrc, const ArkUISearchCreateResourceParams* resParams);
    void (*setSearchSymbolIcon)(ArkUINodeHandle node, std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol);
    void (*setSearchCancelSymbolIcon)(
        ArkUINodeHandle node, std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol, ArkUI_Int32 style);
    void (*setDragPreviewOptions)(ArkUINodeHandle node, const NG::DragPreviewOption option);
    SearchModel* (*getInstance)();
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_BRIDGE_SEARCH_CUSTOM_MODIFIER_H