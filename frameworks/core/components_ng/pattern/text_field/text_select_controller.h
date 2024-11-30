/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_TEXT_SELECT_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_TEXT_SELECT_CONTROLLER_H

#include <cstdint>
#include <functional>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text_field/content_controller.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
namespace {
using OnAccessibilityCallback = std::function<void()>;
} // namespace

class TextSelectController : public Property {
    DECLARE_ACE_TYPE(TextSelectController, AceType);

public:
    explicit TextSelectController(const WeakPtr<Pattern>& pattern) : pattern_(pattern) {}
    ~TextSelectController() override = default;
    void SetOnAccessibility(OnAccessibilityCallback&& onAccessibilityCallback)
    {
        if (onAccessibilityCallback) {
            onAccessibilityCallback_ = std::move(onAccessibilityCallback);
        }
    }

    void FireSelectEvent();

    void UpdateHandleIndex(int32_t handleIndex)
    {
        UpdateHandleIndex(handleIndex, handleIndex);
    }

    inline int32_t GetStartIndex() const
    {
        return std::min(firstHandleInfo_.index, secondHandleInfo_.index);
    }

    inline int32_t GetEndIndex() const
    {
        return std::max(firstHandleInfo_.index, secondHandleInfo_.index);
    }

    int32_t GetCaretIndex() const
    {
        return caretInfo_.index;
    }

    int32_t GetFirstHandleIndex() const
    {
        return firstHandleInfo_.index;
    }

    RectF GetFirstHandleRect() const
    {
        return firstHandleInfo_.rect;
    }

    int32_t GetSecondHandleIndex() const
    {
        return secondHandleInfo_.index;
    }

    RectF GetSecondHandleRect() const
    {
        return secondHandleInfo_.rect;
    }

    OffsetF GetFirstHandleOffset() const
    {
        return firstHandleInfo_.rect.GetOffset();
    }

    OffsetF GetSecondHandleOffset() const
    {
        return secondHandleInfo_.rect.GetOffset();
    }

    void UpdateCaretHeight(float height)
    {
        caretInfo_.rect.SetHeight(height);
        secondHandleInfo_.rect.SetHeight(height);
    }

    RectF GetCaretRect() const
    {
        return caretInfo_.rect;
    }

    double GetSelectHeight() const
    {
        return std::max(firstHandleInfo_.rect.Height(), secondHandleInfo_.rect.Height());
    }

    void InitContentController(const RefPtr<ContentController>& controller)
    {
        contentController_ = controller;
    }

    inline bool IsSelected() const
    {
        return firstHandleInfo_.index >= 0 && secondHandleInfo_.index >= 0 &&
               firstHandleInfo_.index != secondHandleInfo_.index;
    }

    inline bool IsSelectedAll() const
    {
        return firstHandleInfo_.index == 0 && secondHandleInfo_.index >= 0 &&
               abs(firstHandleInfo_.index - secondHandleInfo_.index) ==
                   static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
    }

    bool IsHandleSamePosition()
    {
        bool sameX = NearEqual(firstHandleInfo_.rect.GetX(), secondHandleInfo_.rect.GetX());
        bool sameY = NearEqual(firstHandleInfo_.rect.GetY(), secondHandleInfo_.rect.GetY());
        return (sameX && sameY);
    }

    void UpdateParagraph(const RefPtr<Paragraph>& paragraph)
    {
        paragraph_ = paragraph;
    }

    void UpdateContentRect(const RectF& rect)
    {
        contentRect_ = rect;
    }

    void UpdateCaretWidth(float width)
    {
        caretInfo_.rect.SetWidth(width);
        caretInfo_.originalRect.SetWidth(SelectHandleInfo::GetDefaultLineWidth().ConvertToPx());
    }

    HandleInfoNG GetFirstHandleInfo() const
    {
        return firstHandleInfo_;
    }

    HandleInfoNG GetSecondHandleInfo() const
    {
        return secondHandleInfo_;
    }

    HandleInfoNG GetCaretInfo() const
    {
        return caretInfo_;
    }

    bool HasReverse()
    {
        return firstHandleInfo_.index > secondHandleInfo_.index;
    }

    bool CaretAtLast() const
    {
        return caretInfo_.index == static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
    }
    
    int32_t ConvertTouchOffsetToPosition(const Offset& localOffset, bool isSelectionPos = false);
    void ResetHandles();
    void UpdateHandleIndex(int32_t firstHandleIndex, int32_t secondHandleIndex);
    void UpdateCaretIndex(int32_t index);
    void UpdateCaretInfoByOffset(const Offset& localOffset, bool moveContent = true);
    OffsetF CalcCaretOffsetByOffset(const Offset& localOffset);
    void UpdateSecondHandleInfoByMouseOffset(const Offset& localOffset);
    void MoveSecondHandleByKeyBoard(int32_t index, std::optional<TextAffinity> textAffinity = std::nullopt);
    void UpdateSelectByOffset(const Offset& localOffset);
    void UpdateSelectPragraphByOffset(const Offset& localOffset);
    std::pair<int32_t, int32_t> GetSelectRangeByOffset(const Offset& localOffset);
    std::pair<int32_t, int32_t> GetSelectParagraphByOffset(const Offset& localOffset);
    void UpdateCaretOffset(TextAffinity textAffinity = TextAffinity::DOWNSTREAM, bool moveHandle = true);
    void UpdateCaretOffset(const OffsetF& offset);
    void UpdateFirstHandleOffset();
    void UpdateSecondHandleOffset();
    void MoveFirstHandleToContentRect(int32_t index, bool moveHandle = true, bool moveContent = true);
    void MoveSecondHandleToContentRect(int32_t index, bool moveHandle = true, bool moveContent = true);
    void MoveCaretToContentRect(int32_t index, TextAffinity textAffinity = TextAffinity::UPSTREAM,
        bool isEditorValueChanged = true, bool moveContent = true);
    void MoveCaretAnywhere(const Offset& touchOffset);
    void MoveHandleToContentRect(RectF& handleRect, float boundaryAdjustment = 0.0f) const;
    void AdjustHandleAtEdge(RectF& handleRect) const;
    void AdjustHandleOffset(RectF& handleRect) const;
    static int32_t GetGraphemeClusterLength(const std::u16string& text, int32_t extend, bool checkPrev = false);
    void CalculateHandleOffset();
    std::vector<RectF> GetSelectedRects() const;
    RectF CalculateEmptyValueCaretRect(float width = 0.0f);
    std::string ToString() const;
    bool IsTouchAtLineEnd(const Offset& localOffset);
    void GetSubParagraphByOffset(int32_t pos, int32_t &start, int32_t &end);
    void UpdateSelectWithBlank(const Offset& localOffset);

private:
    constexpr static uint32_t SECONDS_TO_MILLISECONDS = 1000;

    void FitCaretMetricsToContentRect(CaretMetricsF& caretMetrics);
    void FitCaretMetricsToTouchPoint(CaretMetricsF& caretMetrics, const Offset& touchOffset);
    void CalcCaretMetricsByPosition(int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity);
    void CalcCaretMetricsByPositionNearTouchOffset(
        int32_t extent, CaretMetricsF& caretMetrics, const OffsetF& touchOffset);
    // The cursor needs to fit the line where the touch is located.
    void UpdateCaretRectByPositionNearTouchOffset(int32_t position, const Offset& touchOffset);

    // ai text analysis or detect
    bool NeedAIAnalysis(int32_t& index, const CaretUpdateType targetType, const Offset& touchOffset,
        std::chrono::duration<float, std::ratio<1, SECONDS_TO_MILLISECONDS>> timeout);
    bool IsLineBreakOrEndOfParagraph(int32_t pos) const;
    void AdjustCursorPosition(int32_t& index, const Offset& touchOffset);
    bool AdjustWordSelection(int32_t& index, int32_t& start, int32_t& end, const Offset& touchOffset);
    bool IsClickAtBoundary(int32_t index, const Offset& touchOffset);
    const TimeStamp& GetLastClickTime();
    void UpdateCaretOriginalRect(const OffsetF& offset);
    void SetCaretRectAtEmptyValue();

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FirstIndex, int32_t, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SecondIndex, int32_t, PROPERTY_UPDATE_RENDER);

    RectF contentRect_;
    HandleInfoNG firstHandleInfo_;
    HandleInfoNG secondHandleInfo_;
    HandleInfoNG caretInfo_;
    RefPtr<Paragraph> paragraph_;
    RefPtr<ContentController> contentController_;
    OnAccessibilityCallback onAccessibilityCallback_;
    WeakPtr<Pattern> pattern_;
    TimeStamp lastAiPosTimeStamp_;
    TextAffinity textAffinity_ = TextAffinity::DOWNSTREAM;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_TEXT_SELECT_CONTROLLER_H