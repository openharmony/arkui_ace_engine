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
#include "base/utils/utils.h"
#include "base/memory/referenced.h"
#include "core/common/clipboard/clipboard.h"
#include "core/common/container.h"
#include "core/components_ng/manager/select_overlay/select_overlay_client.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paragraph.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

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

template<typename T>
void GetTextCaretMetrics(RefPtr<FrameNode>& targetNode, CaretMetricsF& caretMetrics)
{
    CHECK_NULL_VOID(targetNode);
    if (targetNode->GetTag() == V2::SEARCH_ETS_TAG) {
        auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(targetNode->GetChildren().front());
        CHECK_NULL_VOID(textFieldFrameNode);
        auto textPattern = textFieldFrameNode->GetPattern<T>();
        CHECK_NULL_VOID(textPattern);
        textPattern->GetCaretMetrics(caretMetrics);
    } else {
        auto textPattern = targetNode->GetPattern<T>();
        CHECK_NULL_VOID(textPattern);
        textPattern->GetCaretMetrics(caretMetrics);
    }
}
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

    static void SetSelectionNode(const SelectedByMouseInfo& info)
    {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto selectOverlayManager = pipeline->GetSelectOverlayManager();
        selectOverlayManager->SetSelectedNodeByMouse(info);
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
                aroundChar =
                    text[std::min(static_cast<int32_t>(text.length() ? text.length() - 1 : 0), extend)];
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
        float lastLineBottom = firstRect.Top();
        auto end = *(lineGroup.rbegin());
        for (auto const& line : lineGroup) {
            if (line == end) {
                break;
            }
            auto rect = RectF(line.second.Left(), lastLineBottom, longestLine - line.second.Left(),
                line.second.Bottom() - lastLineBottom);
            selectedRect.emplace_back(rect);
            lastLineBottom = line.second.Bottom();
        }
        selectedRect.emplace_back(RectF(end.second.Left(), lastLineBottom, end.second.Width(), end.second.Height()));
    }

    // The methods that need to be implemented for input class components
    virtual RectF GetCaretRect() const
    {
        return { 0, 0, 0, 0 };
    }

    virtual void ScrollToSafeArea() const {}

    static bool UpdateKeyboardOffset(double positionY, double height, bool foreChange = false)
    {
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, false);
        if (container->IsUIExtensionWindow()) {
            return false;
        }
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(context, false);
        auto keyboardArea = container->GetKeyboardSafeArea();
        auto keyboardLength = keyboardArea.bottom_.Length();
        Rect keyboardRect;
        keyboardRect.SetRect(0, keyboardArea.bottom_.start, 0, keyboardLength);
        context->OnVirtualKeyboardAreaChange(keyboardRect, positionY, height, nullptr, foreChange);
        return true;
    }

    static bool AvoidKeyboard(float offsetY, float height)
    {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(context, false);
        auto safeAreaManager = context->GetSafeAreaManager();
        CHECK_NULL_RETURN(safeAreaManager, false);
        auto keyboardInset = safeAreaManager->GetKeyboardInset();
        CHECK_NULL_RETURN(keyboardInset.Length() != 0, false);
        if (LessOrEqual(offsetY + height, keyboardInset.start)) {
            return false;
        }
        auto keyboardOffset = safeAreaManager->GetKeyboardOffset();
        return UpdateKeyboardOffset(offsetY - keyboardOffset, height, true);
    }

    virtual void GetCaretMetrics(CaretMetricsF& caretCaretMetric) {}

    virtual void OnVirtualKeyboardAreaChanged() {}

    const RectF& GetContentRect() const
    {
        return contentRect_;
    }

    virtual RectF GetPaintContentRect()
    {
        return contentRect_;
    }

    virtual int32_t GetContentWideTextLength()
    {
        return 0;
    }

    virtual int32_t GetCaretIndex() const
    {
        return 0;
    }

    virtual OffsetF GetCaretOffset() const
    {
        return OffsetF();
    }

    virtual OffsetF GetTextPaintOffset() const
    {
        return OffsetF();
    }

    virtual OffsetF GetFirstHandleOffset() const
    {
        return OffsetF();
    }

    virtual OffsetF GetSecondHandleOffset() const
    {
        return OffsetF();
    }

    virtual RefPtr<Clipboard> GetClipboard()
    {
        return nullptr;
    }

    TextSelector GetTextSelector() const
    {
        return textSelector_;
    }

    virtual bool CaretAvoidSoftKeyboard()
    {
        auto caretRect = GetCaretRect();
        return AvoidKeyboard(caretRect.Top() + GetTextPaintOffset().GetY(),
            caretRect.Height() + GetAvoidSoftKeyboardOffset().ConvertToPx());
    }

    virtual const Dimension& GetAvoidSoftKeyboardOffset() const
    {
        return avoidKeyboardOffset_;
    }

protected:
    TextSelector textSelector_;
    bool showSelect_ = true;
    std::vector<std::string> dragContents_;
    MouseStatus mouseStatus_ = MouseStatus::NONE;
    RectF contentRect_;
    Dimension avoidKeyboardOffset_ = 24.0_vp;
    ACE_DISALLOW_COPY_AND_MOVE(TextBase);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_BASE_H
