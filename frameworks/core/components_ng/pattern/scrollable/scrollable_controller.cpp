/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/scrollable_controller.h"

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"

namespace OHOS::Ace::NG {
void ScrollableController::ScrollToIndex(
    int32_t index, bool smooth, ScrollAlign align, std::optional<float> extraOffset)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->SupportScrollToIndex());
    if (align == ScrollAlign::NONE) {
        align = pattern->GetDefaultScrollAlign();
    }
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    ACE_SCOPED_TRACE("ScrollToIndex, index:%d, smooth:%u, align:%d, id:%d, tag:%s", index, smooth, align,
        static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
    pattern->ScrollToIndex(index, smooth, align, extraOffset);
}

bool ScrollableController::AnimateTo(
    const Dimension& position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    if (pattern->GetAxis() != Axis::NONE) {
        if (position.Unit() == DimensionUnit::PERCENT) {
            return false;
        }
        if (Positive(duration) || smooth) {
            ACE_SCOPED_TRACE(
                "ScrollTo with animation, position:%f, duration:%f, smooth:%u, canOverScroll:%u, id:%d, tag:%s",
                position.ConvertToPx(), duration, smooth, canOverScroll,
                static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
            pattern->AnimateTo(position.ConvertToPx(), duration, curve, smooth, canOverScroll);
        } else {
            ACE_SCOPED_TRACE("ScrollTo without animation, position:%f, id:%d, tag:%s", position.ConvertToPx(),
                static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
            pattern->ScrollTo(position.ConvertToPx());
        }
        return true;
    }
    return false;
}

void ScrollableController::SetCanStayOverScroll(bool canStayOverScroll)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetCanStayOverScroll(canStayOverScroll);
}

Offset ScrollableController::GetCurrentOffset() const
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_RETURN(pattern, Offset::Zero());
    auto axis = pattern->GetAxis();
    if (axis == Axis::NONE) {
        return Offset::Zero();
    }
    if (axis == Axis::FREE) {
        return pattern->GetFreeScrollOffset();
    }
    auto pxOffset = pattern->GetTotalOffset();
    auto vpOffset = Dimension(pxOffset, DimensionUnit::PX).ConvertToVp();
    return (axis == Axis::HORIZONTAL) ? Offset(vpOffset, 0) : Offset(0, vpOffset);
}

Axis ScrollableController::GetScrollDirection() const
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_RETURN(pattern, Axis::NONE);
    return pattern->GetAxis();
}

void ScrollableController::ScrollBy(double pixelX, double pixelY, bool /* smooth */)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->StopAnimate();
    auto offset = pattern->GetAxis() == Axis::VERTICAL ? pixelY : pixelX;
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    ACE_SCOPED_TRACE("ScrollBy, offset:%f, id:%d, tag:%s", static_cast<float>(-offset),
        static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
    if (pattern->GetAxis() == Axis::FREE && pattern->FreeScrollBy(OffsetF { -pixelX, -pixelY })) {
        return;
    }
    pattern->SetIsOverScroll(false);
    pattern->UpdateCurrentOffset(static_cast<float>(-offset), SCROLL_FROM_JUMP);
}

void ScrollableController::ScrollToEdge(ScrollEdgeType scrollEdgeType, float velocity)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetAxis() == Axis::FREE && pattern->FreeScrollToEdge(scrollEdgeType, true, velocity)) {
        return;
    }
    pattern->SetIsOverScroll(false);
    pattern->SetCanStayOverScroll(false);
    pattern->SetAnimateCanOverScroll(false);
    if (scrollEdgeType == ScrollEdgeType::SCROLL_TOP) {
        pattern->ScrollAtFixedVelocity(velocity);
    } else if (scrollEdgeType == ScrollEdgeType::SCROLL_BOTTOM) {
        pattern->ScrollAtFixedVelocity(-velocity);
    }
}

void ScrollableController::ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetAxis() == Axis::FREE && pattern->FreeScrollToEdge(scrollEdgeType, smooth, std::nullopt)) {
        return;
    }
    pattern->SetIsOverScroll(false);
    pattern->SetCanStayOverScroll(false);
    if (pattern->GetAxis() != Axis::NONE) {
        pattern->ScrollToEdge(scrollEdgeType, smooth);
    }
}

void ScrollableController::Fling(double flingVelocity)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    ACE_SCOPED_TRACE("Fling, flingVelocity:%f, id:%d, tag:%s", static_cast<float>(flingVelocity),
        static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
    pattern->Fling(flingVelocity);
}

void ScrollableController::ScrollPage(bool reverse, bool smooth)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsOverScroll(false);
    pattern->SetCanStayOverScroll(false);
    if (pattern->GetAxis() == Axis::NONE) {
        return;
    }
    if (pattern->GetAxis() == Axis::FREE && pattern->FreeScrollPage(reverse, smooth)) {
        return;
    }
    if (InstanceOf<WaterFlowPattern>(pattern)) {
        pattern->ScrollPage(reverse, smooth);
        return;
    }
    // todo: remove impl here, all types of ScrollablePattern should call ScrollPage directly
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto offset = reverse ? pattern->GetMainContentSize() : -pattern->GetMainContentSize();
    if (smooth) {
        auto position = pattern->GetTotalOffset() - offset;
        ACE_SCOPED_TRACE("ScrollPage with animation, position:%f, id:%d, tag:%s", position,
            static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
        pattern->AnimateTo(position, -1, nullptr, true, false, false);
    } else {
        pattern->StopAnimate();
        ACE_SCOPED_TRACE("ScrollPage without animation, offset:%f, id:%d, tag:%s", offset,
            static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
        pattern->UpdateCurrentOffset(offset, SCROLL_FROM_JUMP);
    }
}

bool ScrollableController::IsAtEnd() const
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsAtBottom(true);
}

Rect ScrollableController::GetItemRect(int32_t index) const
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_RETURN(pattern, Rect());
    auto pxRect = pattern->GetItemRect(index);
    auto pxOffset = pxRect.GetOffset();
    return Rect(Dimension(pxOffset.GetX(), DimensionUnit::PX).ConvertToVp(),
        Dimension(pxOffset.GetY(), DimensionUnit::PX).ConvertToVp(),
        Dimension(pxRect.Width(), DimensionUnit::PX).ConvertToVp(),
        Dimension(pxRect.Height(), DimensionUnit::PX).ConvertToVp());
}

int32_t ScrollableController::GetItemIndex(double x, double y) const
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_RETURN(pattern, -1);
    return pattern->GetItemIndex(x, y);
}

void ScrollableController::StopAnimate()
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->StopAnimate();
}

bool ScrollableController::FreeScrollTo(const ScrollToParam& param)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    pattern->FreeScrollTo(param);
    return true;
}
} // namespace OHOS::Ace::NG
