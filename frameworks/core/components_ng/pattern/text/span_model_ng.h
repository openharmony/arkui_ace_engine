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
    static void SetFontWeight(FrameNode* frameNode, FontWeight value);
    static void SetTextCase(FrameNode* frameNode, TextCase value);
    static void SetItalicFontStyle(FrameNode* frameNode, Ace::FontStyle value);
    static void SetLineHeight(FrameNode* frameNode, const Dimension& value);
    static void SetFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value);
    static void SetTextDecoration(FrameNode* frameNode, TextDecoration value);
    static void SetTextDecorationStyle(FrameNode* frameNode, TextDecorationStyle value);
    static void SetTextDecorationColor(FrameNode* frameNode, const Color& value);
    static void SetTextColor(FrameNode* frameNode, const Color& value);
    static void SetLetterSpacing(FrameNode* frameNode, const Dimension& value);
    static void SetFont(FrameNode* frameNode, const Font& value);

    void CreateContainSpan() override;
    void SetTextBackgroundStyle(const TextBackgroundStyle& style) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_MODEL_NG_H
