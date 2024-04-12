/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_MODEL_NG_H

#include <functional>
#include <string>

#include "core/components_ng/pattern/text/span_model.h"
#include "core/components_ng/pattern/text/span_node.h"
namespace OHOS::Ace::NG {
class ACE_EXPORT SpanModelNG : public SpanModel {
public:
    void Create(const std::string& content) override;
    void SetFont(const Font& value) override;
    void SetFontSize(const Dimension& value) override;
    void SetTextColor(const Color& value) override;
    void SetItalicFontStyle(Ace::FontStyle value) override;
    void SetFontWeight(FontWeight value) override;
    void SetFontFamily(const std::vector<std::string>& value) override;
    void SetTextDecoration(TextDecoration value) override;
    void SetTextDecorationStyle(TextDecorationStyle value) override;
    void SetTextDecorationColor(const Color& value) override;
    void SetTextCase(TextCase value) override;
    void SetTextShadow(const std::vector<Shadow>& value) override;
    void SetLetterSpacing(const Dimension& value) override;
    void SetLineHeight(const Dimension& value) override;
    // TODO: add extra event for span.
    void SetOnClick(std::function<void(const BaseEventInfo* info)>&& click) override;
    void ClearOnClick() override;
    

    static RefPtr<SpanNode> CreateSpanNode(int32_t nodeId, const std::string& content);
    static void InitSpan(UINode* uiNode, const std::string& content);
    static void SetFontWeight(UINode* uiNode, FontWeight value);
    static void SetTextCase(UINode* uiNode, TextCase value);
    static void SetItalicFontStyle(UINode* uiNode, Ace::FontStyle value);
    static void SetLineHeight(UINode* uiNode, const Dimension& value);
    static void SetFontSize(UINode* uiNode, const Dimension& value);
    static void SetFontFamily(UINode* uiNode, const std::vector<std::string>& value);
    static void SetTextDecoration(UINode* uiNode, TextDecoration value);
    static void SetTextDecorationStyle(UINode* uiNode, TextDecorationStyle value);
    static void SetTextDecorationColor(UINode* uiNode, const Color& value);
    static void SetTextColor(UINode* uiNode, const Color& value);
    static void SetLetterSpacing(UINode* uiNode, const Dimension& value);
    static void SetFont(UINode* uiNode, const Font& value);
    static std::string GetContent(UINode* uiNode);
    static Ace::TextDecoration GetTextDecoration(UINode* uiNode);
    static Color GetTextDecorationColor(UINode* uiNode);
    static Color GetFontColor(UINode* uiNode);
    static Dimension GetFontSize(UINode* uiNode);
    static Ace::FontStyle GetFontStyle(UINode* uiNode);
    static FontWeight GetFontWeight(UINode* uiNode);
    static Dimension GetTextLineHeight(UINode* uiNode);
    static Ace::TextCase GetTextCase(UINode* uiNode);
    static Dimension GetLetterSpacing(UINode* uiNode);
    static TextStyle GetDefaultTextStyle();
    void CreateContainSpan() override;
    void SetTextBackgroundStyle(const TextBackgroundStyle& style) override;
    static void SetTextBackgroundStyle(UINode* uiNode, const TextBackgroundStyle& style);
    static TextBackgroundStyle GetSpanTextBackgroundStyle(UINode* uiNode);
    static void SetTextShadow(UINode* uiNode, const std::vector<Shadow>& value);
    static std::vector<Shadow> GetTextShadow(UINode* uiNode);
    static void SetOnClick(UINode* uiNode, GestureEventFunc&& click);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_MODEL_NG_H
