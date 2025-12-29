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

#include "core/components_ng/pattern/scrollable/scrollable_controller.h"

#include "base/memory/referenced.h"
#include "base/utils/multi_thread.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"

namespace OHOS::Ace::NG {

bool ScrollableController::AnimateToMultiThread(
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
            host->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(AceType::RawPtr(pattern)),
                                                  weakPtr = AceType::WeakClaim(AceType::RawPtr(host)), position,
                                                  duration, curve, smooth, canOverScroll]() {
                auto host = weakPtr.Upgrade();
                CHECK_NULL_VOID(host);
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                ACE_SCOPED_TRACE(
                    "ScrollTo with animation, position:%f, duration:%f, smooth:%u, canOverScroll:%u, id:%d, tag:%s",
                    position.ConvertToPx(), duration, smooth, canOverScroll,
                    static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
                pattern->AnimateTo(position.ConvertToPx(), duration, curve, smooth, canOverScroll);
            });
        } else {
            host->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(AceType::RawPtr(pattern)),
                                                  weakPtr = AceType::WeakClaim(AceType::RawPtr(host)), position]() {
                auto host = weakPtr.Upgrade();
                CHECK_NULL_VOID(host);
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                ACE_SCOPED_TRACE("ScrollTo without animation, position:%f, id:%d, tag:%s", position.ConvertToPx(),
                    static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());

                pattern->ScrollTo(position.ConvertToPx());
            });
        }
        return true;
    }
    return false;
}

void ScrollableController::ScrollToEdgeMultiThread(ScrollEdgeType scrollEdgeType, bool smooth)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetAxis() == Axis::FREE && pattern->FreeScrollToEdge(scrollEdgeType, smooth, std::nullopt)) {
        return;
    }
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(AceType::RawPtr(pattern)), scrollEdgeType, smooth]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->GetAxis() != Axis::NONE) {
            pattern->ScrollToEdge(scrollEdgeType, smooth);
        }
    });
}

void ScrollableController::ScrollToEdgeMultiThread(ScrollEdgeType scrollEdgeType, float velocity)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask(
        [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), scrollEdgeType, velocity]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetIsOverScroll(false);
        pattern->SetCanStayOverScroll(false);
        pattern->SetAnimateCanOverScroll(false);
        if (scrollEdgeType == ScrollEdgeType::SCROLL_TOP) {
            pattern->ScrollAtFixedVelocity(velocity);
        } else if (scrollEdgeType == ScrollEdgeType::SCROLL_BOTTOM) {
            pattern->ScrollAtFixedVelocity(-velocity);
        }
    });
}

void ScrollableController::ScrollByMultiThread(double pixelX, double pixelY, bool /* smooth */)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetAxis() == Axis::FREE) {
        pattern->FreeScrollBy(OffsetF { -pixelX, -pixelY });
        return;
    }
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(AceType::RawPtr(pattern)),
                                          weakNode = AceType::WeakClaim(AceType::RawPtr(host)), pixelX, pixelY]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = weakNode.Upgrade();
        CHECK_NULL_VOID(host);
        pattern->StopAnimate();
        auto offset = pattern->GetAxis() == Axis::VERTICAL ? pixelY : pixelX;
        ACE_SCOPED_TRACE("ScrollBy, offset:%f, id:%d, tag:%s", static_cast<float>(-offset),
            static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
        if (pattern->GetAxis() == Axis::FREE) {
            pattern->FreeScrollBy(OffsetF { -pixelX, -pixelY });
            return;
        }
        pattern->SetIsOverScroll(false);
        pattern->UpdateCurrentOffset(static_cast<float>(-offset), SCROLL_FROM_JUMP);
    });
}

void ScrollableController::FlingMultiThread(double flingVelocity)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(AceType::RawPtr(pattern)),
                                          weakNode = AceType::WeakClaim(AceType::RawPtr(host)), flingVelocity]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = weakNode.Upgrade();
        CHECK_NULL_VOID(host);
        ACE_SCOPED_TRACE("Fling, flingVelocity:%f, id:%d, tag:%s", static_cast<float>(flingVelocity),
            static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
        pattern->Fling(flingVelocity);
    });
}

void ScrollableController::ScrollToIndexMultiThread(
    int32_t index, bool smooth, ScrollAlign align, std::optional<float> extraOffset)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(AceType::RawPtr(pattern)),
        index, smooth, align, extraOffset]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ScrollToIndex(index, smooth, align, extraOffset);
    });
}

void ScrollableController::ScrollPageMultiThread(bool reverse, bool smooth)
{
    auto pattern = scroll_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(AceType::RawPtr(pattern)),
        reverse, smooth]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
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
    });
}
} // namespace OHOS::Ace::NG
