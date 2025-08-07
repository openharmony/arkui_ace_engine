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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_MODEL_STATIC_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/base/symbol_modifier.h"
#include "core/components_ng/pattern/select/select_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SelectModelStatic {
public:
    static void SetDivider(FrameNode* frameNode, const std::optional<NG::SelectDivider>& divider);
    static void SetArrowPosition(FrameNode* frameNode, const std::optional<ArrowPosition>& value);
    static void SetSpace(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetValue(FrameNode* frameNode, const std::optional<std::string>& value);
    static void SetSelected(FrameNode* frameNode, const std::optional<int32_t>& idx);
    static void SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value);
    static void SetItalicFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value);
    static void SetFontColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetSelectedOptionBgColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetOptionFontSize(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetOptionFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value);
    static void SetOptionItalicFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value);
    static void SetOptionFontColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetOptionBgColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetSelectedOptionFontColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetSelectedOptionFontSize(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetSelectedOptionFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value);
    static void SetSelectedOptionItalicFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value);
    static void SetOptionWidth(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetOptionHeight(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetOptionWidthFitTrigger(FrameNode* frameNode, std::optional<bool> isFitTrigger);
    static void SetMenuBackgroundColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetSelectChangeEvent(FrameNode* frameNode, NG::SelectChangeEvent&& selectChangeEvent);
    static void SetValueChangeEvent(FrameNode* frameNode, NG::ValueChangeEvent&& valueChangeEvent);
    static NG::SelectDivider GetDefaultDivider(FrameNode* frameNode);
    static void SetDividerStyle(FrameNode* frameNode,
        const std::optional<NG::SelectDivider>& divider, const std::optional<DividerMode>& mode);
    // static void SetAvoidance(FrameNode* frameNode, const std::optional<Avoidance>& avoidance);
    static void SetMenuOutline(FrameNode* frameNode, const std::optional<MenuParam>& menuParam);
    static void SetControlSize(FrameNode* frameNode, const std::optional<ControlSize>& controlSize);
    static void ResetDividerStyle(FrameNode* frameNode);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_MODEL_STATIC_H
