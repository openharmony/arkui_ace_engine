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
#include "base/utils/feature_param.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/layout/vertical_overflow_handler.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"
 
namespace OHOS::Ace::NG {
namespace {
constexpr double MAX_FLING_VELOCITY = 9000;
} // namespace

bool VerticalOverflowHandler::IsVerticalLayout() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pattern = host->GetPattern();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->GetIsVertical();
}

bool VerticalOverflowHandler::IsVerticalReverseLayout() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pattern = host->GetPattern();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsVerticalReverseLayout();
}

void VerticalOverflowHandler::RegisterScrollableEvent()
{
    if (!IsVerticalLayout()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (!gestureHub->IsGestureHierarchyEmpty() || scrollableEvent_) {
        return;
    }
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto scrollCallback = [weak = WeakClaim(this)](double offset, int32_t source) {
        auto handler = weak.Upgrade();
        CHECK_NULL_RETURN(handler, false);
        return handler->HandleScrollImpl(static_cast<float>(offset), source);
    };
    auto scrollable = MakeRefPtr<Scrollable>(std::move(scrollCallback), Axis::VERTICAL);
    CHECK_NULL_VOID(scrollable);
    scrollable->SetNodeId(host->GetAccessibilityId());
    scrollable->SetNodeTag(host->GetTag());
    scrollable->Initialize(host);
    scrollable->SetMaxFlingVelocity(MAX_FLING_VELOCITY);
    scrollableEvent_->SetScrollable(scrollable);
    gestureHub->AddScrollableEvent(scrollableEvent_);
    gestureHub->SetOnGestureJudgeNativeBegin(
        [weak = AceType::WeakClaim(this)](const RefPtr<NG::GestureInfo>& gestureInfo,
        const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
        if (gestureInfo->IsSystemGesture() && gestureInfo->GetRecognizerType() == GestureTypeName::PAN_GESTURE) {
            auto handler = weak.Upgrade();
            CHECK_NULL_RETURN(handler, GestureJudgeResult::CONTINUE);
            auto host = handler->GetHost();
            CHECK_NULL_RETURN(host, GestureJudgeResult::CONTINUE);
            auto columnGeometry = host->GetGeometryNode();
            CHECK_NULL_RETURN(columnGeometry, GestureJudgeResult::CONTINUE);
            const auto& pan = std::static_pointer_cast<PanGestureEvent>(info);
            CHECK_NULL_RETURN(pan, GestureJudgeResult::CONTINUE);
            auto yOffset = pan->GetOffsetY();
            if (handler->OutOfBoundary(yOffset)) {
                return GestureJudgeResult::REJECT;
            }
        }
        return GestureJudgeResult::CONTINUE;
    });
}

void VerticalOverflowHandler::AdjustChildrenOffset(float offset, bool useParentAjust)
{
    if (useParentAjust) {
        hasParentAdjust_ = true;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int32_t childCount = host->GetTotalChildCount();
    auto selfExpansive = host->SelfExpansive();
    for (int32_t i = 0; i < childCount; i++) {
        auto childNode = AceType::DynamicCast<FrameNode>(host->GetChildByIndex(i));
        if (!childNode) {
            continue;
        }
        auto geometryNode = childNode->GetGeometryNode();
        auto currentOffset = geometryNode->GetMarginFrameOffset();
        if (selfExpansive && useParentAjust) {
            currentOffset += geometryNode->GetParentAdjust().GetOffset();
        }
        if (geometryNode) {
            geometryNode->SetMarginFrameOffset(OffsetF(currentOffset.GetX(), currentOffset.GetY() + offset));
            childNode->ForceSyncGeometryNode();
            childNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }
}

void VerticalOverflowHandler::CreateContentRect()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometry = host->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    auto contentSize = geometry->GetFrameSize();
    OffsetF paddingOffset;
    auto layoutProperty = host->GetLayoutProperty();
    if (layoutProperty) {
        auto padding = layoutProperty->CreatePaddingAndBorder();
        MinusPaddingToNonNegativeSize(padding, contentSize);
        paddingOffset = OffsetF(padding.left.value_or(0.0f), padding.top.value_or(0.0f));
    }
    contentRect_.SetOffset(paddingOffset);
    contentRect_.SetSize(contentSize);
}

void VerticalOverflowHandler::InitOffsetAfterLayout()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto verticalReverse = IsVerticalReverseLayout();
    if (!scrollDistance_.has_value() || preVerticalReverse_ != verticalReverse) {
        preVerticalReverse_ = verticalReverse;
        scrollDistance_ = totalChildFrameRect_.GetY() - contentRect_.GetY();
        offsetToChildFrameBottom_ = scrollDistance_.value() + totalChildFrameRect_.Height() - contentRect_.Height();
        return;
    }
    auto childFrameHeight = totalChildFrameRect_.Height();
    auto contentHeight = contentRect_.Height();
    if (verticalReverse) {
        scrollDistance_ = offsetToChildFrameBottom_ + contentRect_.Height() - childFrameHeight;
    }
    scrollDistance_ = std::clamp(scrollDistance_.value(), contentHeight - childFrameHeight, 0.0f);
    offsetToChildFrameBottom_ = scrollDistance_.value() + childFrameHeight - contentHeight;
    auto offsetAdjust = verticalReverse ? childFrameHeight - contentHeight : 0.0f;
    if ((verticalReverse && !NearEqual(offsetToChildFrameBottom_, 0.0f)) || !NearEqual(scrollDistance_.value(), 0.0f)) {
        AdjustChildrenOffset(scrollDistance_.value() + offsetAdjust);
    }
}

bool VerticalOverflowHandler::OutOfBoundary(float offset) const
{
    return (NearEqual(scrollDistance_.value_or(0.0f), 0.0f) && GreatNotEqual(offset, 0.0f)) ||
        (NearEqual(scrollDistance_.value_or(0.0f), contentRect_.Height() - totalChildFrameRect_.Height()) &&
        LessNotEqual(offset, 0.0f));
}

bool VerticalOverflowHandler::HandleScrollImpl(float offset, int32_t source)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto columnGeometry = host->GetGeometryNode();
    CHECK_NULL_RETURN(columnGeometry, false);
    if (OutOfBoundary(offset)) {
        return false;
    }
    auto currentOffsetValue = scrollDistance_.value_or(0.0f);
    currentOffsetValue += offset;
    scrollDistance_ = std::clamp(currentOffsetValue, contentRect_.Height() - totalChildFrameRect_.Height(), 0.0f);
    offsetToChildFrameBottom_ = scrollDistance_.value() + totalChildFrameRect_.Height() - contentRect_.Height();
    offset += (scrollDistance_.value() - currentOffsetValue);
    AdjustChildrenOffset(offset, !hasParentAdjust_);
    return true;
}
 
void VerticalOverflowHandler::UnRegisterScrollableEvent()
{
    if (!scrollableEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    scrollableEvent_ = nullptr;
    scrollDistance_.reset();
}

bool VerticalOverflowHandler::IsVerticalOverflow() const
{
    return GreatNotEqual(contentRect_.Top(), totalChildFrameRect_.Top()) ||
        LessNotEqual(contentRect_.Bottom(), totalChildFrameRect_.Bottom());
}
bool VerticalOverflowHandler::IsHorizontalOverflow() const
{
    return GreatNotEqual(contentRect_.Left(), totalChildFrameRect_.Left()) ||
        LessNotEqual(contentRect_.Right(), totalChildFrameRect_.Right());
}

void VerticalOverflowHandler::HandleContentOverflow()
{
    hasParentAdjust_ = false;
    AdjustTotalChildFrameRect();
    auto overflow = IsVerticalOverflow() && IsVerticalLayout();
    if (overflow && !overflowDisabled_) {
        InitOffsetAfterLayout();
        RegisterScrollableEvent();
    } else {
        UnRegisterScrollableEvent();
    }
}
} // namespace OHOS::Ace::NG