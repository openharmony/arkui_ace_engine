/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_SELECTION_CHILD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_SELECTION_CHILD_H

#include "core/components_ng/manager/select_content_overlay/selection_container_child.h"

namespace OHOS::Ace::NG {
class TextPattern;

class TextSelectionChild : public SelectionContainerChild {
    DECLARE_ACE_TYPE(TextSelectionChild, SelectionContainerChild);

public:
    explicit TextSelectionChild(const WeakPtr<TextPattern>& pattern);
    ~TextSelectionChild() override = default;

    std::u16string GetSelectionText() override;
    RefPtr<FrameNode> GetHostNode() const override;
    std::optional<RectF> GetFirstHandleRect() override;
    std::optional<RectF> GetSecondHandleRect() override;
    RectF GetSelectionArea(SelectRectsType pos, SelectionAreaResultType& resultType) override;
    SelectionIndexRange GetSelectionIndexes() const override;
    SelectionIndexRange GetSelectionIndexesByPoints(const OffsetF& firstPoint, const OffsetF& secondPoint) override;
    int32_t GetSelectionIndexByPoint(const OffsetF& point) override;
    void SelectTextByIndex(int32_t startIndex, int32_t endIndex) override;
    void SelectAll() override;
    void UpdateSelectionHandleInfo() override;
    bool BetweenSelectedPosition(const Offset& globalOffset) override;
    bool IsSelectAll() const override;
    bool HasSelectableText() const override;
    bool CanSelect() const override;
    CopyOptions GetCopyOption() const override;
    TextSpanType GetSelectionSpanType() const override;
    bool HandleOnAskCelia(const std::u16string& selectedContent) override;
    bool IsAskCeliaSupported() const override;
    bool FireOnWillCopy(const std::u16string& selectedContent) override;
    void FireOnCopy(const std::u16string& selectedContent) override;
    SelectionCopyPayload GetSelectionCopyPayload() override;
    RefPtr<SpanString> GetSelectedSpanString() override;
    void ResetOriginCaretPosition() override;
    void ReportSelectionText() override;
    void StartVibratorByIndexChange(int32_t currentIndex, int32_t preIndex) override;
    void OnContainerPropertyUpdate(uint32_t flags) override;
    void UpdateChildHandleGlobalOffset() override;
    OffsetF GetChildHandleGlobalOffset() const override;
    bool HasOrUpdateRenderTransform();

private:
    Offset GetMovingHandleReferenceOffset(const OffsetF& point) const;
    bool GetRenderClipValue() const;
    bool CheckChildHasTransformAttr() const;
    void UpdateTransformFlag();
    OffsetF GetChildPaintOffsetWithoutTransform() const;
    bool GetClipHandleViewPortForChild(const RefPtr<FrameNode>& host, RectF& rect);

    WeakPtr<TextPattern> pattern_;
    OffsetF handleGlobalOffset_;
    bool childHasTransform_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_SELECTION_CHILD_H
