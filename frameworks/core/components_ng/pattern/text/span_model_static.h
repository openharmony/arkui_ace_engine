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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_MODEL_STATIC_H

#include <functional>
#include <string>

#include "interfaces/native/node/styled_string.h"

#include "core/components_ng/pattern/text/span_model.h"
#include "core/components_ng/pattern/text/span_node.h"
namespace OHOS::Ace::NG {
class ACE_EXPORT SpanModelStatic {
public:
    static RefPtr<ContainerSpanNode> CreateContainerSpanNode(int32_t nodeId);
    static void InitSpan(UINode* uiNode, const std::optional<std::u16string>& content);
    static void SetFontWeight(UINode* uiNode, const std::optional<FontWeight>& value);
    static void SetTextCase(UINode* uiNode, const std::optional<TextCase>& value);
    static void SetItalicFontStyle(UINode* uiNode, const std::optional<Ace::FontStyle>& value);
    static void SetLineHeight(UINode* uiNode, const std::optional<Dimension>& value);
    static void SetFontSize(UINode* uiNode, const std::optional<Dimension>& value);
    static void SetFontFamily(UINode* uiNode, const std::optional<std::vector<std::string>>& value);
    static void SetTextDecoration(UINode* uiNode, const std::optional<TextDecoration>& value);
    static void SetTextDecorationStyle(UINode* uiNode, const std::optional<TextDecorationStyle>& value);
    static void SetTextDecorationColor(UINode* uiNode, const std::optional<Color>& value);
    static void SetTextColor(UINode* uiNode, const std::optional<Color>& value);
    static void SetLetterSpacing(UINode* uiNode, const std::optional<Dimension>& value);
    static void SetBaselineOffset(UINode* uiNode, const std::optional<Dimension>& value);
    static void SetTextShadow(UINode* uiNode, const std::optional<std::vector<Shadow>>& value);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_MODEL_STATIC_H