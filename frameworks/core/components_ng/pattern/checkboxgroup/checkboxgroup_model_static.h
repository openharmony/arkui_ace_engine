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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_MODEL_STATIC_H

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CheckBoxGroupModelStatic {
public:
    static void SetSelectAll(FrameNode* frameNode, const std::optional<bool> isSelected);
    static void SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetUnSelectedColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetCheckMarkColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetCheckMarkSize(FrameNode* frameNode, const std::optional<Dimension>& size);
    static void SetCheckMarkWidth(FrameNode* frameNode, const std::optional<Dimension>& width);
    static void SetCheckboxGroupStyle(FrameNode* frameNode, const std::optional<CheckBoxStyle>& checkboxGroupStyle);
    static void SetChangeEvent(FrameNode* frameNode, GroupChangeEvent&& changeEvent);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_MODEL_STATIC_H
