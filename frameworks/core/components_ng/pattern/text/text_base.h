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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_BASE_H

#include "base/memory/ace_type.h"
#include "core/components_ng/manager/select_overlay/select_overlay_client.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
using ParagraphT = std::variant<std::shared_ptr<RSParagraph>, RefPtr<Paragraph>>;

enum class MouseStatus { PRESSED, RELEASED, MOVE, NONE };

struct HandleMoveStatus {
    bool isFirsthandle = false;
    int32_t position = -1;
    OffsetF handleOffset;

    void Reset()
    {
        isFirsthandle = false;
        position = -1;
    }

    bool IsValid()
    {
        return position >= 0;
    }
};

class TextBase : public SelectOverlayClient {
    DECLARE_ACE_TYPE(TextBase, SelectOverlayClient);

public:
    TextBase() = default;
    ~TextBase() override = default;

    virtual OffsetF GetContentOffset()
    {
        return OffsetF(0, 0);
    }

    virtual bool OnBackPressed()
    {
        return false;
    }

    virtual bool IsSelected() const
    {
        return textSelector_.IsValid() && !textSelector_.StartEqualToDest();
    }

    MouseStatus GetMouseStatus() const
    {
        return mouseStatus_;
    }

    static int32_t GetGraphemeClusterLength(const std::wstring& text, int32_t extend, bool checkPrev = false)
    {
        char16_t aroundChar = 0;
        if (checkPrev) {
            if (static_cast<size_t>(extend) <= text.length()) {
                aroundChar = text[std::max(0, extend - 1)];
            }
        } else {
            if (static_cast<size_t>(extend) <= (text.length())) {
                aroundChar = text[std::min(static_cast<int32_t>(text.length() - 1), extend)];
            }
        }
        return StringUtils::NotInUtf16Bmp(aroundChar) ? 2 : 1;
    }

    static void CalculateSelectedRect(std::vector<RectF>& selectedRect, float longestLine)
    {
        if (selectedRect.size() <= 1) {
            return;
        }
        std::map<float, RectF> lineGroup;
        for (auto const& localRect : selectedRect) {
            if (NearZero(localRect.Width()) && NearZero(localRect.Height())) {
                continue;
            }
            auto it = lineGroup.find(localRect.GetY());
            if (it == lineGroup.end()) {
                lineGroup.emplace(localRect.GetY(), localRect);
            } else {
                auto lineRect = it->second;
                it->second = lineRect.CombineRectT(localRect);
            }
        }
        selectedRect.clear();
        auto firstRect = lineGroup.begin()->second;
        if (lineGroup.size() == 1) {
            selectedRect.emplace_back(firstRect);
            return;
        }
        firstRect.SetWidth(longestLine - firstRect.Left());
        selectedRect.emplace_back(firstRect);
        auto endRect = lineGroup.rbegin()->second;
        endRect.SetWidth(endRect.Right());
        endRect.SetLeft(0.0f);
        selectedRect.emplace_back(endRect);
        const int32_t drawMiddleLineNumberLimit = 2;
        if (static_cast<int32_t>(lineGroup.size()) > drawMiddleLineNumberLimit || firstRect.Left() <= endRect.Right()) {
            auto middleRect = RectF(0.0f, firstRect.Bottom(), longestLine, endRect.Top() - firstRect.Bottom());
            selectedRect.emplace_back(middleRect);
        }
    }

    // The methods that need to be implemented for input class components
    virtual RectF GetCaretRect() const
    {
        return { 0, 0, 0, 0 };
    }

    virtual void ScrollToSafeArea() const {}

protected:
    TextSelector textSelector_;
    bool showSelect_ = true;
    std::vector<std::string> dragContents_;
    MouseStatus mouseStatus_ = MouseStatus::NONE;
    ACE_DISALLOW_COPY_AND_MOVE(TextBase);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_BASE_H
