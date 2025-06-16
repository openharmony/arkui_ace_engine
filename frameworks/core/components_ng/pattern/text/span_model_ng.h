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

#include "interfaces/native/node/styled_string.h"

#include "core/components_ng/pattern/text/span_model.h"
#include "core/components_ng/pattern/text/span_node.h"
namespace OHOS::Ace::NG {
class ACE_EXPORT SpanModelNG : public SpanModel {
public:
    void Create(const std::u16string& content) override;
    void SetFont(const Font& value) override;
    void ResetFont() override;
    void SetFontSize(const Dimension& value) override;
    void ResetFontSize() override;
    void SetTextColor(const Color& value) override;
    void ResetTextColor() override;
    void SetItalicFontStyle(Ace::FontStyle value) override;
    void ResetItalicFontStyle() override;
    void SetFontWeight(FontWeight value) override;
    void ResetFontWeight() override;
    void SetFontFamily(const std::vector<std::string>& value) override;
    void ResetFontFamily() override;
    void SetTextDecoration(TextDecoration value) override;
    void SetTextDecorationStyle(TextDecorationStyle value) override;
    void SetTextDecorationColor(const Color& value) override;
    void SetTextCase(TextCase value) override;
    void SetTextShadow(const std::vector<Shadow>& value) override;
    void SetLetterSpacing(const Dimension& value) override;
    void SetBaselineOffset(const Dimension& value) override;
    void SetLineHeight(const Dimension& value) override;
    void SetOnClick(std::function<void(BaseEventInfo* info)>&& click) override;
    void ClearOnClick() override;
    void SetAccessibilityText(const std::string& text) override;
    void SetAccessibilityDescription(const std::string& description) override;
    void SetAccessibilityImportance(const std::string& importance) override;
    void SetLineThicknessScale(float value) override;
    void SetOnHover(OnHoverFunc&& onHoverEventFunc) override;
    void ResetOnHover() override;

    static RefPtr<SpanNode> CreateSpanNode(int32_t nodeId, const std::u16string& content);
    static void InitSpan(UINode* uiNode, const std::optional<std::u16string>& content);
    static void SetFontWeight(UINode* uiNode, const std::optional<FontWeight>& value);
    static void ResetFontWeight(UINode* uiNode);
    static void SetTextCase(UINode* uiNode, const std::optional<TextCase>& value);
    static void ResetTextCase(UINode* uiNode);
    static void SetItalicFontStyle(UINode* uiNode, const std::optional<Ace::FontStyle>& value);
    static void ResetItalicFontStyle(UINode* uiNode);
    static void SetLineHeight(UINode* uiNode, const std::optional<Dimension>& value);
    static void ResetLineHeight(UINode* uiNode);
    static void SetFontSize(UINode* uiNode, const std::optional<Dimension>& value);
    static void ResetFontSize(UINode* uiNode);
    static void SetFontFamily(UINode* uiNode, const std::optional<std::vector<std::string>>& value);
    static void ResetFontFamily(UINode* uiNode);
    static void SetTextDecoration(UINode* uiNode, const std::optional<TextDecoration>& value);
    static void ResetTextDecoration(UINode* uiNode);
    static void SetTextDecorationStyle(UINode* uiNode, const std::optional<TextDecorationStyle>& value);
    static void ResetTextDecorationStyle(UINode* uiNode);
    static void SetTextDecorationColor(UINode* uiNode, const std::optional<Color>& value);
    static void ResetTextDecorationColor(UINode* uiNode);
    static void SetTextColor(UINode* uiNode, const std::optional<Color>& value);
    static void ResetTextColor(UINode* uiNode);
    static void SetLetterSpacing(UINode* uiNode, const std::optional<Dimension>& value);
    static void ResetLetterSpacing(UINode* uiNode);
    static void SetBaselineOffset(UINode* uiNode, const std::optional<Dimension>& value);
    static void SetFont(UINode* uiNode, const Font& value);
    static void ResetFont(UINode* uiNode);
    static std::u16string GetContent(UINode* uiNode);
    static Ace::TextDecoration GetTextDecoration(UINode* uiNode);
    static Color GetTextDecorationColor(UINode* uiNode);
    static Ace::TextDecorationStyle GetTextDecorationStyle(UINode* uiNode);
    static Color GetFontColor(UINode* uiNode);
    static Dimension GetFontSize(UINode* uiNode);
    static Ace::FontStyle GetFontStyle(UINode* uiNode);
    static FontWeight GetFontWeight(UINode* uiNode);
    static Dimension GetTextLineHeight(UINode* uiNode);
    static Ace::TextCase GetTextCase(UINode* uiNode);
    static Dimension GetLetterSpacing(UINode* uiNode);
    static Dimension GetBaselineOffset(UINode* uiNode);
    static TextStyle GetDefaultTextStyle(int32_t themeScopeId);
    void CreateContainSpan() override;
    void SetTextBackgroundStyle(const TextBackgroundStyle& style) override;
    static void SetTextBackgroundStyle(UINode* uiNode, const TextBackgroundStyle& style);
    static void SetTextBackgroundStyleByBaseSpan(UINode* uiNode, const TextBackgroundStyle& style);
    static TextBackgroundStyle GetSpanTextBackgroundStyle(UINode* uiNode);
    static void SetTextShadow(UINode* uiNode, const std::optional<std::vector<Shadow>>& value);
    static void ResetTextShadow(UINode* uiNode);
    static std::vector<Shadow> GetTextShadow(UINode* uiNode);
    static void SetOnClick(UINode* uiNode, GestureEventFunc&& click);
    static void ClearOnClick(UINode* uiNode);
    static void SetOnLongPress(UINode* uiNode, GestureEventFunc&& onLongPress);
    static void ClearOnLongPress(UINode* uiNode);
    static void SetAccessibilityText(UINode* uiNode, const std::string& text);
    static void SetAccessibilityDescription(UINode* uiNode, const std::string& description);
    static void SetAccessibilityImportance(UINode* uiNode, const std::string& importance);
    static void SetOnHover(UINode* uiNode, OnHoverFunc&& onHoverEventFunc);
    static void ResetOnHover(UINode* uiNode);
    static std::vector<std::string> GetSpanFontFamily(UINode* uiNode);
    // impl in render/adapter/span_model_adapter.cpp
    static RefPtr<SpanItem> CreateSpanItem(ArkUI_SpanItem* item);
    static ParagraphStyle CreateParagraphStyle(ArkUI_StyledString* styledString);
    static void SetLineThicknessScale(UINode *uiNode, float value);
    static void ResetLineThicknessScale(UINode* uiNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_MODEL_NG_H
