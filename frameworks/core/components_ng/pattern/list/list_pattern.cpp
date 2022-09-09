/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/list/list_pattern.h"

#include "base/geometry/axis.h"
#include "base/utils/utils.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
// TODO define as common method
float CalculateFriction(float gamma)
{
    constexpr float SCROLL_RATIO = 0.72f;
    if (GreatOrEqual(gamma, 1.0)) {
        gamma = 1.0f;
    }
    return SCROLL_RATIO * static_cast<float>(std::pow(1.0 - gamma, SQUARE));
}
}

void ListPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void ListPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(listLayoutProperty);
    auto task = [weak = WeakClaim(this)](double offset, int32_t source) {
        if (source != SCROLL_FROM_START) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->UpdateCurrentOffset(static_cast<float>(offset));
            }
        }
        return true;
    };

    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL));
    scrollableEvent_->SetScrollPositionCallback(std::move(task));
    gestureHub->AddScrollableEvent(scrollableEvent_);
}

bool ListPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure && skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto listLayoutAlgorithm = DynamicCast<ListLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(listLayoutAlgorithm, false);
    startIndex_ = listLayoutAlgorithm->GetStartIndex();
    endIndex_ = listLayoutAlgorithm->GetEndIndex();
    isInitialized_ = listLayoutAlgorithm->GetIsInitialized();
    itemPosition_ = listLayoutAlgorithm->GetItemPosition();
    if (listLayoutAlgorithm->GetMaxListItemIndex().has_value()) {
        maxListItemIndex_ = listLayoutAlgorithm->GetMaxListItemIndex().value();
    }
    auto host = GetHost();
    if (host == nullptr) {
        return false;
    }
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    // TODO: now only support spring effect
    auto edgeEffect = listLayoutProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING);
    playEdgeEffectAnimation_ = false;
    if (currentOffset_ != lastOffset_) {
        if (startIndex_ == 0 && itemPosition_[0].first >= 0) {
            if (edgeEffect == EdgeEffect::SPRING) {
                PlaySpringAnimation(0.0);
            }
        }
        if (endIndex_ == maxListItemIndex_ && itemPosition_[maxListItemIndex_].second <= MainSize()) {
            if (edgeEffect == EdgeEffect::SPRING) {
                PlaySpringAnimation(0.0);
            }
        }
    }
    return listLayoutProperty && listLayoutProperty->GetDivider().has_value();
}

void ListPattern::UpdateCurrentOffset(float offset)
{
    lastOffset_ = currentOffset_;
    currentOffset_ = currentOffset_ - offset;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void ListPattern::PlaySpringAnimation(double dragVelocity)
{
    LOGI("Play spring animation start");
    playEdgeEffectAnimation_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!SpringController_) {
        SpringController_ = AceType::MakeRefPtr<Animator>(host->GetContext());
    }
    springController_->ClearStopListeners();
    springController_->ClearInterpolators();

    // TODO: use theme.
    constexpr float SPRING_SCROLL_MASS = 0.5f;
    constexpr float SPRING_SCROLL_STIFFNESS = 100.0f;
    constexpr float SPRING_SCROLL_DAMPING = 15.55635f;
    const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY = 
        AceType::MakeRefPtr<SpringProperty>(SPRING_SCROLL_MASS, SPRING_SCROLL_STIFFNESS, SPRING_SCROLL_DAMPING);
    ExtentPair extentPair = ExtentPair(0.0, 0.0);
    float friction = CalculateFriction(std::abs(currentOffset_) / MainSize());
    auto scrollMotion = AceType::MakeRefPtr<ScrollMotion>(
        currentOffset_, dragVelocity * friction, extentPair, extentPair, DEFAULT_OVER_SPRING_PROPERTY);
    scrollMotion->AddListener([weak = AceType::WeakClaim(this)](double position) {
        auto list = weak.Upgrade();
        if (list) {
            list->UpdateCurrentOffset(list->currentOffset_ - static_cast<float>(position));
        }
    })
    springController_->AddStopListener([weak = AceType::WeakClaim(this)]() {});
    springController_->PlayMotion(scrollMotion);
}

float ListPattern::MainSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    return geometryNode->GetFrameSize().MainSize(GetDirection());
}

Axis ListPattern::GetDirection() const
{
    auto listLayoutProperty = GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listLayoutProperty, Axis::VERTICAL);
    return listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
}
} // namespace OHOS::Ace::NG
