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

#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

#include "base/json/json_util.h"

namespace OHOS::Ace {

std::string NestedScrollOptions::ToString() const
{
    return "NestedScrollOptions forward: " + std::to_string(static_cast<int32_t>(forward)) +
           ", backward: " + std::to_string(static_cast<int32_t>(backward));
}

std::string NestedScrollOptions::GetNestedScrollModeStr(NestedScrollMode mode) const
{
    switch (mode) {
        case NestedScrollMode::SELF_ONLY:
            return "NestedScrollMode.SELF_ONLY";
        case NestedScrollMode::SELF_FIRST:
            return "NestedScrollMode.SELF_FIRST";
        case NestedScrollMode::PARENT_FIRST:
            return "NestedScrollMode.PARENT_FIRST";
        case NestedScrollMode::PARALLEL:
            return "NestedScrollMode.PARALLEL";
        default:
            return "";
    }
}

std::string NestedScrollOptionsExt::ToString() const
{
    return "NestedScrollOptionsExt scrollUp: " + std::to_string(static_cast<int32_t>(scrollUp)) +
           ", scrollDown: " + std::to_string(static_cast<int32_t>(scrollDown)) +
           ", scrollLeft: " + std::to_string(static_cast<int32_t>(scrollLeft)) +
           ", scrollRight: " + std::to_string(static_cast<int32_t>(scrollRight));
}

std::string GetSourceStr(int32_t scrollSource)
{
    switch (scrollSource) {
        case SCROLL_FROM_NONE:
            return "SCROLL_FROM_NONE";
        case SCROLL_FROM_UPDATE:
            return "SCROLL_FROM_UPDATE";
        case SCROLL_FROM_ANIMATION:
            return "SCROLL_FROM_ANIMATION";
        case SCROLL_FROM_JUMP:
            return "SCROLL_FROM_JUMP";
        case SCROLL_FROM_ANIMATION_SPRING:
            return "SCROLL_FROM_ANIMATION_SPRING";
        case SCROLL_FROM_CHILD:
            return "SCROLL_FROM_CHILD";
        case SCROLL_FROM_BAR:
            return "SCROLL_FROM_BAR";
        case SCROLL_FROM_FOCUS_JUMP:
            return "SCROLL_FROM_FOCUS_JUMP";
        case SCROLL_FROM_ROTATE:
            return "SCROLL_FROM_ROTATE";
        case SCROLL_FROM_INDEXER:
            return "SCROLL_FROM_INDEXER";
        case SCROLL_FROM_START:
            return "SCROLL_FROM_START";
        case SCROLL_FROM_AXIS:
            return "SCROLL_FROM_AXIS";
        case SCROLL_FROM_ANIMATION_CONTROLLER:
            return "SCROLL_FROM_ANIMATION_CONTROLLER";
        case SCROLL_FROM_BAR_FLING:
            return "SCROLL_FROM_BAR_FLING";
        case SCROLL_FROM_BAR_OVER_DRAG:
            return "SCROLL_FROM_BAR_OVER_DRAG";
        default:
            return "";
    }
}

std::string ScrollableEventsFiredInfo::ToString() const
{
    return std::string("event type: ")
        .append(GetEventStr())
        .append(" fired in ")
        .append(std::to_string(eventFiredTime_))
        .append(", source is ")
        .append(GetSourceStr(scrollSource_));
}

std::string ScrollableEventsFiredInfo::GetEventStr() const
{
    switch (eventType_) {
        case ScrollableEventType::ON_SCROLL_START:
            return "onScrollStart";
        case ScrollableEventType::ON_SCROLL_STOP:
            return "onScrollStop";
        case ScrollableEventType::ON_SCROLL_EDGE:
            return "onScrollEdge";
        case ScrollableEventType::ON_REACH_START:
            return "onReachStart";
        case ScrollableEventType::ON_REACH_END:
            return "onReachEnd";
        default:
            return "";
    }
}

void ScrollableEventsFiredInfo::ToJson(std::unique_ptr<JsonValue>& json) const
{
    json->Put("event type", GetEventStr().c_str());
    json->Put("fired in", std::to_string(eventFiredTime_).c_str());
    json->Put("source is", GetSourceStr(scrollSource_).c_str());
}

std::string ScrollableFrameInfo::ToString() const
{
    return std::string("scroll from: ")
        .append(GetSourceStr(scrollState_))
        .append(" canOverScroll: ")
        .append(std::to_string(canOverScroll_))
        .append(" isScrollableSpringEffect: ")
        .append((canOverScrollInfo_ >> 4) & 1 ? "true" : "false")
        .append(" isScrollable: ")
        .append((canOverScrollInfo_ >> 3) & 1 ? "true" : "false")
        .append(" scrollableIdle: ")
        .append((canOverScrollInfo_ >> 2) & 1 ? "true" : "false")
        .append(" animateOverScroll: ")
        .append((canOverScrollInfo_ >> 1) & 1 ? "true" : "false")
        .append(" animateCanOverScroll: ")
        .append(canOverScrollInfo_ & 1 ? "true" : "false")
        .append(" fired in ")
        .append(std::to_string(scrollStateTime_));
}

void ScrollableFrameInfo::ToJson(std::unique_ptr<JsonValue>& json) const
{
    json->Put("scroll from", GetSourceStr(scrollState_).c_str());
    json->Put("canOverScroll", std::to_string(canOverScroll_).c_str());
    json->Put("isScrollableSpringEffect",
        (canOverScrollInfo_ >> 4) & 1 ? "true" : "false");
    json->Put("isScrollable", (canOverScrollInfo_ >> 3) & 1 ? "true" : "false");
    json->Put("scrollableIdle", (canOverScrollInfo_ >> 2) & 1 ? "true" : "false");
    json->Put("animateOverScroll", (canOverScrollInfo_ >> 1) & 1 ? "true" : "false");
    json->Put("animateCanOverScroll", canOverScrollInfo_ & 1 ? "true" : "false");
    json->Put("scroll from", std::to_string(scrollStateTime_).c_str());
}

std::string ScrollLayoutInfo::ToString() const
{
    return std::string("scrollableDistance changed, scrollableDistance: ")
        .append(std::to_string(scrollableDistance_))
        .append(" scrollSize: ")
        .append(scrollSize_.ToString())
        .append(" viewPort: ")
        .append(viewPort_.ToString())
        .append(" childSize: ")
        .append(childSize_.ToString())
        .append(" fired in ")
        .append(std::to_string(changedTime_));
}

void ScrollLayoutInfo::ToJson(std::unique_ptr<JsonValue>& json) const
{
    json->Put("scrollableDistance changed, scrollableDistance", std::to_string(scrollableDistance_).c_str());
    json->Put("scrollSize", scrollSize_.ToString().c_str());
    json->Put("viewPort", viewPort_.ToString().c_str());
    json->Put("childSize", childSize_.ToString().c_str());
    json->Put("fired in", std::to_string(changedTime_).c_str());
}

std::string ScrollMeasureInfo::ToString() const
{
    return std::string("Scroll Measure changed, parentConstraint: ")
        .append(parentConstraint_->ToString())
        .append(" childConstraint: ")
        .append(childConstraint_->ToString())
        .append(" selfSize: ")
        .append(selfSize_.ToString())
        .append(" childSize: ")
        .append(childSize_.ToString())
        .append(" fired in ")
        .append(std::to_string(changedTime_));
}

void ScrollMeasureInfo::ToJson(std::unique_ptr<JsonValue>& json) const
{
    json->Put("Scroll Measure changed, parentConstraint", parentConstraint_->ToString().c_str());
    json->Put("childConstraint", childConstraint_->ToString().c_str());
    json->Put("selfSize", selfSize_.ToString().c_str());
    json->Put("childSize", childSize_.ToString().c_str());
    json->Put("fired in", std::to_string(changedTime_).c_str());
}

std::string InnerScrollBarLayoutInfo::ToString() const
{
    return std::string("inner scrollBar layout, viewPortSize:")
        .append(viewPortSize_.ToString())
        .append(" lastOffset: ")
        .append(lastOffset_.ToString())
        .append(" estimatedHeight: ")
        .append(std::to_string(estimatedHeight_))
        .append(" outBoundary: ")
        .append(std::to_string(outBoundary_))
        .append(" activeRect: ")
        .append(activeRect_.ToString())
        .append(" fired in ")
        .append(std::to_string(layoutTime_));
}

void InnerScrollBarLayoutInfo::ToJson(std::unique_ptr<JsonValue>& json) const
{
    json->Put("inner scrollBar layout, viewPortSize", viewPortSize_.ToString().c_str());
    json->Put("lastOffset", lastOffset_.ToString().c_str());
    json->Put("estimatedHeight", estimatedHeight_);
    json->Put("outBoundary", std::to_string(outBoundary_).c_str());
    json->Put("activeRect", activeRect_.ToString().c_str());
    json->Put("fired in", std::to_string(layoutTime_).c_str());
}

std::string OuterScrollBarLayoutInfo::ToString() const
{
    return std::string("outer scrollBar layout, currentOffset:")
        .append(std::to_string(currentOffset_))
        .append(" scrollableNodeOffset: ")
        .append(std::to_string(scrollableNodeOffset_))
        .append(" fired in ")
        .append(std::to_string(layoutTime_));
}

void OuterScrollBarLayoutInfo::ToJson(std::unique_ptr<JsonValue>& json) const
{
    json->Put("outer scrollBar layout, currentOffset", std::to_string(currentOffset_).c_str());
    json->Put("scrollableNodeOffset", std::to_string(scrollableNodeOffset_).c_str());
    json->Put("fired in", std::to_string(layoutTime_).c_str());
}

} // namespace OHOS::Ace
