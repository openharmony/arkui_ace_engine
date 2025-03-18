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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_PARAGRAPH_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_PARAGRAPH_MANAGER_H

#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"

namespace OHOS::Ace::NG {

class RichEditorParagraphManager : public ParagraphManager {
    DECLARE_ACE_TYPE(RichEditorParagraphManager, ParagraphManager);

public:
    void AddParagraph(ParagraphInfo&& info)
    {
        paragraphs_.emplace_back(std::move(info));
        hasPosyRange = false;
    }

    void SetParagraphs(const std::vector<ParagraphInfo>& paragraphs)
    {
        paragraphs_ = paragraphs;
        hasPosyRange = false;
    }

    void Reset()
    {
        paragraphs_.clear();
        hasPosyRange = false;
    }

    float GetHeight()
    {
        ACE_SCOPED_TRACE("RichEditorParagraphManager::GetHeight");
        if (paragraphs_.empty()) {
            return 0.0f;
        }
        if (!hasPosyRange) {
            CalPosyRange();
        }
        auto& lastParagraph = paragraphs_.back();
        return lastParagraph.bottomPos - lastParagraph.paragraphStyle.paragraphSpacing.ConvertToPx();
    }

    void CalPosyRange()
    {
        CHECK_NULL_VOID(!hasPosyRange);
        ACE_SCOPED_TRACE("RichEditorParagraphManager::CalPosyRange");
        float cumHeight = 0;
        for (auto& paragraphInfo : paragraphs_) {
            paragraphInfo.topPos = cumHeight;
            cumHeight += paragraphInfo.paragraph->GetHeight();
            paragraphInfo.bottomPos = cumHeight;
        }
        hasPosyRange = true;
    }

    std::vector<RectF> GetRects(int32_t start, int32_t end,
            RectHeightPolicy rectHeightPolicy = RectHeightPolicy::COVER_LINE) const override
    {
        std::vector<RectF> res;
        float y = 0.0f;
        float paragraphSpacing = 0.0f;
        bool isConsiderSpacing = false;
        for (auto&& info : paragraphs_) {
            std::vector<RectF> rects;
            CHECK_NULL_BREAK(info.start <= end);
            if (info.end <= start) {
                y += info.paragraph->GetHeight();
                continue;
            }
            auto relativeStart = (start < info.start) ? 0 : start - info.start;
            if (rectHeightPolicy == RectHeightPolicy::COVER_TEXT) {
                info.paragraph->GetTightRectsForRange(relativeStart, end - info.start, rects);
            } else {
                info.paragraph->GetRectsForRange(relativeStart, end - info.start, rects);
            }
            if (!rects.empty() && !NearZero(paragraphSpacing) && isConsiderSpacing) {
                auto firstRect = rects.front();
                for (auto&& rect : rects) {
                    CHECK_NULL_CONTINUE(NearEqual(firstRect.Top(), rect.Top()));
                    rect.SetHeight(rect.Height() + paragraphSpacing);
                    rect.SetTop(rect.Top() - paragraphSpacing);
                }
            }
            for (auto&& rect : rects) {
                rect.SetTop(rect.Top() + y);
            }
            res.insert(res.end(), rects.begin(), rects.end());
            paragraphSpacing = (rects.empty() && (info.end - info.start == 1)) ? 0.0f :
                info.paragraphStyle.paragraphSpacing.ConvertToPx();
            if (info.start <= start && info.end > start) {
                isConsiderSpacing = true;
            }
            y += info.paragraph->GetHeight();
        }
        return res;
    }

private:
    bool hasPosyRange = false;
};
} // namespace OHOS::Ace::NG
#endif
