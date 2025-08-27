/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "test/mock/core/render/mock_paragraph.h"

#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
RefPtr<MockParagraph> MockParagraph::paragraph_;
bool MockParagraph::enabled_ = true;
bool MockParagraph::enableCalcCaretMetricsByPosition_ = false;

RefPtr<Paragraph> Paragraph::Create(const ParagraphStyle& paraStyle, const RefPtr<FontCollection>& fontCollection)
{
    return MockParagraph::enabled_ ? MockParagraph::paragraph_ : nullptr;
}

RefPtr<Paragraph> Paragraph::CreateRichEditorParagraph(
    const ParagraphStyle& paraStyle, const RefPtr<FontCollection>& fontCollection)
{
    return MockParagraph::enabled_ ? MockParagraph::paragraph_ : nullptr;
}

RefPtr<Paragraph> Paragraph::Create(void* paragraph)
{
    return MockParagraph::enabled_ ? MockParagraph::paragraph_ : nullptr;
}

RefPtr<MockParagraph> MockParagraph::GetOrCreateMockParagraph()
{
    if (!paragraph_) {
        paragraph_ = AceType::MakeRefPtr<MockParagraph>();
    }
    return paragraph_;
}

void MockParagraph::TearDown()
{
    if (paragraph_) {
        paragraph_ = nullptr;
    }
}

void MockParagraph::UpdateColor(size_t from, size_t to, const Color& color) {}
} // namespace OHOS::Ace::NG
