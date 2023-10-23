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
#include <stdint.h>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text_field/content_controller.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
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
    void UpdateRecordCaretIndex(int32_t index) const;

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
                   static_cast<int32_t>(contentController_->GetWideText().length());
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

    void ResetHandles();
    void UpdateHandleIndex(int32_t firstHandleIndex, int32_t secondHandleIndex);
    void UpdateCaretIndex(int32_t index);
    void UpdateCaretInfoByOffset(const Offset& localOffset);
    void UpdateSecondHandleInfoByMouseOffset(const Offset& localOffset);
    void UpdateSelectByOffset(const Offset& localOffset);
    void UpdateCaretOffset();
    void UpdateCaretOffset(const OffsetF& offset);
    void UpdateFirstHandleOffset();
    void UpdateSecondHandleOffset();
    void MoveFirstHandleToContentRect(int32_t index);
    void MoveSecondHandleToContentRect(int32_t index);
    void MoveCaretToContentRect(int32_t index, TextAffinity textAffinity = TextAffinity::UPSTREAM);
    void MoveHandleToContentRect(RectF& handleRect);
    static int32_t GetGraphemeClusterLength(const std::wstring& text, int32_t extend, bool checkPrev = false);
    void CalculateHandleOffset();
    std::vector<RectF> GetSelectedRects() const;
    RectF CalculateEmptyValueCaretRect() const;
    std::string ToString() const;

private:
    void CalcCaretMetricsByPosition(int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity);
    void CalcCaretMetricsByPositionNearTouchOffset(
        int32_t extent, CaretMetricsF& caretMetrics, const OffsetF& touchOffset);
    // The cursor needs to fit the line where the touch is located.
    void UpdateCaretRectByPositionNearTouchOffset(int32_t position, const Offset& touchOffset);
    int32_t ConvertTouchOffsetToPosition(const Offset& localOffset);
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
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_PATTERN_TEXT_SELECT_CONTROLLER_H