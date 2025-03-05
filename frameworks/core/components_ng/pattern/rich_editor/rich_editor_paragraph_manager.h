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
        return paragraphs_.back().bottomPos;
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

private:
    bool hasPosyRange = false;
};
} // namespace OHOS::Ace::NG
#endif
