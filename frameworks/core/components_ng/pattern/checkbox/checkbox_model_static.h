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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_MODEL_STATIC_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/checkbox/checkbox_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CheckBoxModelStatic {
public:
    static void SetSelect(FrameNode* frameNode, const std::optional<bool>& isSelected);
    static void SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetUnSelectedColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetCheckMarkColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetCheckMarkSize(FrameNode* frameNode, const std::optional<Dimension>& size);
    static void SetCheckMarkWidth(FrameNode* frameNode, const std::optional<Dimension>& width);
    static void SetBuilder(FrameNode* frameNode, std::function<void(void)>&& buildFunc);
    static void SetBuilder(FrameNode* frameNode, std::optional<std::function<void(void)>>& buildFunc);
    static void SetCheckboxStyle(FrameNode* frameNode, const std::optional<CheckBoxStyle>& checkboxStyle);
    static void SetChangeEvent(FrameNode* frameNode, ChangeEvent&& onChange);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_MODEL_STATIC_H
