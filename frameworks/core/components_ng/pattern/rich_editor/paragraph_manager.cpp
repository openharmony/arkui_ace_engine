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

#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"

#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
float ParagraphManager::GetHeight() const
{
    float res = 0.0f;
    for (auto&& info : paragraphs_) {
        res += info.paragraph->GetHeight();
    }
    return res;
}

int32_t ParagraphManager::GetIndex(Offset offset) const
{
    CHECK_NULL_RETURN(!paragraphs_.empty(), 0);
    int idx = 0;
    for (auto it = paragraphs_.begin(); it != paragraphs_.end(); ++it, ++idx) {
        auto&& info = *it;
        if (GreatNotEqual(offset.GetY(), info.paragraph->GetHeight())) {
            if (idx == static_cast<int>(paragraphs_.size()) - 1) {
                // in the last line
                return info.end;
            }
            // get offset relative to each paragraph
            offset.SetY(offset.GetY() - info.paragraph->GetHeight());
        } else {
            return info.paragraph->GetGlyphIndexByCoordinate(offset) + info.start;
        }
    }
    return paragraphs_.back().paragraph->GetGlyphIndexByCoordinate(offset) + paragraphs_.back().start;
}

std::vector<RectF> ParagraphManager::GetRects(int32_t start, int32_t end) const
{
    std::vector<RectF> res;
    float y = 0.0f;
    for (auto&& info : paragraphs_) {
        std::vector<RectF> rects;
        if (info.start > end) {
            break;
        }
        if (info.end > start) {
            auto relativeStart = (start < info.start) ? 0 : start - info.start;
            info.paragraph->GetRectsForRange(relativeStart, end - info.start, rects);

            for (auto&& rect : rects) {
                rect.SetTop(rect.Top() + y);
            }
            res.insert(res.end(), rects.begin(), rects.end());
        }
        y += info.paragraph->GetHeight();
    }
    return res;
}

std::vector<RectF> ParagraphManager::GetPlaceholderRects() const
{
    std::vector<RectF> res;
    float y = 0.0f;
    for (auto&& info : paragraphs_) {
        std::vector<RectF> rects;
        info.paragraph->GetRectsForPlaceholders(rects);
        for (auto& rect : rects) {
            rect.SetTop(rect.Top() + y);
        }
        y += info.paragraph->GetHeight();

        res.insert(res.end(), rects.begin(), rects.end());
    }
    return res;
}

OffsetF ParagraphManager::ComputeCursorOffset(int32_t index, float& selectLineHeight) const
{
    CHECK_NULL_RETURN(!paragraphs_.empty(), {});
    auto it = paragraphs_.begin();
    float y = 0.0f;
    while (it != paragraphs_.end()) {
        if (index >= it->start && index < it->end) {
            break;
        }
        y += it->paragraph->GetHeight();
        ++it;
    }

    if (index == paragraphs_.back().end) {
        --it;
        y -= it->paragraph->GetHeight();
    }

    CHECK_NULL_RETURN(it != paragraphs_.end(), OffsetF(0.0f, y));

    int32_t relativeIndex = index - it->start;
    auto&& paragraph = it->paragraph;
    CaretMetricsF metrics;
    auto computeSuccess = paragraph->ComputeOffsetForCaretDownstream(relativeIndex, metrics) ||
                          paragraph->ComputeOffsetForCaretUpstream(relativeIndex, metrics);
    CHECK_NULL_RETURN(computeSuccess, OffsetF(0.0f, y));

    selectLineHeight = metrics.height;
    return { static_cast<float>(metrics.offset.GetX()), static_cast<float>(metrics.offset.GetY() + y) };
}

void ParagraphManager::Reset()
{
    paragraphs_.clear();
}

std::string ParagraphManager::ParagraphInfo::ToString() const
{
    return "Paragraph start: " + std::to_string(start) + ", end: " + std::to_string(end);
}
} // namespace OHOS::Ace::NG
