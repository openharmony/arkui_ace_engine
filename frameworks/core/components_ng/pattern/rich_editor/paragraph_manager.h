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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_PARAGRAPH_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_PARAGRAPH_MANAGER_H
#include <list>
#include <optional>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/render/paragraph.h"
namespace OHOS::Ace::NG {
class ParagraphManager : public virtual AceType {
    DECLARE_ACE_TYPE(ParagraphManager, AceType);

public:
    struct ParagraphInfo {
        RefPtr<Paragraph> paragraph;
        int32_t start = 0;
        int32_t end = 0;

        std::string ToString() const;
    };
    std::optional<double> minParagraphFontSize;

    int32_t GetIndex(Offset offset) const;
    float GetHeight() const;

    const std::list<ParagraphInfo>& GetParagraphs() const
    {
        return paragraphs_;
    }
    void Reset();

    std::vector<Rect> GetRects(int32_t start, int32_t end) const;
    std::vector<Rect> GetPlaceholderRects() const;
    OffsetF ComputeCursorOffset(int32_t index, float& selectLineHeight) const;

    void AddParagraph(ParagraphInfo&& info)
    {
        paragraphs_.emplace_back(std::move(info));
    }

private:
    std::list<ParagraphInfo> paragraphs_;
};
} // namespace OHOS::Ace::NG
#endif
