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

#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_algorithm.h"
#include "core/components_ng/pattern/waterflow/water_flow_paint_method.h"

namespace OHOS::Ace::NG {
bool WaterFlowPattern::UpdateCurrentOffset(float delta, int32_t /* source */)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<WaterFlowLayoutProperty>();
    if (layoutProperty->IsReverse()) {
        delta = -delta;
    }
    if (layoutInfo_.itemStart_ && delta > 0) {
        return false;
    }
    if (layoutInfo_.offsetEnd_ && delta < 0) {
        return false;
    }
    layoutInfo_.prevOffset_ = layoutInfo_.currentOffset_;
    layoutInfo_.currentOffset_ += delta;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return true;
};

bool WaterFlowPattern::IsScrollable() const
{
    return !(IsAtTop() && IsAtBottom());
}
bool WaterFlowPattern::IsAtTop() const
{
    return layoutInfo_.itemStart_;
};
bool WaterFlowPattern::IsAtBottom() const
{
    return layoutInfo_.offsetEnd_;
};
OverScrollOffset WaterFlowPattern::GetOverScrollOffset(double delta) const
{
    OverScrollOffset offset = { 0, 0 };
    if (layoutInfo_.startIndex_ == 0) {
        auto startPos = layoutInfo_.currentOffset_;
        auto newStartPos = startPos + delta;
        if (startPos > 0 && newStartPos > 0) {
            offset.start = delta;
        }
        if (startPos > 0 && newStartPos <= 0) {
            offset.start = -startPos;
        }
        if (startPos <= 0 && newStartPos > 0) {
            offset.start = newStartPos;
        }
    }
    if (layoutInfo_.itemEnd_) {
        auto endPos = layoutInfo_.currentOffset_ + layoutInfo_.maxHeight_;
        auto newEndPos = endPos + delta;
        if (endPos < layoutInfo_.lastMainSize_ && newEndPos < layoutInfo_.lastMainSize_) {
            offset.end = delta;
        }
        if (endPos < layoutInfo_.lastMainSize_ && newEndPos >= layoutInfo_.lastMainSize_) {
            offset.end = layoutInfo_.lastMainSize_ - endPos;
        }
        if (endPos >= layoutInfo_.lastMainSize_ && newEndPos < layoutInfo_.lastMainSize_) {
            offset.end = newEndPos - layoutInfo_.lastMainSize_;
        }
    }
    return offset;
}

void WaterFlowPattern::UpdateScrollBarOffset() {};

RefPtr<LayoutAlgorithm> WaterFlowPattern::CreateLayoutAlgorithm()
{
    return AceType::MakeRefPtr<WaterFlowLayoutAlgorithm>(layoutInfo_);
}

RefPtr<NodePaintMethod> WaterFlowPattern::CreateNodePaintMethod()
{
    auto paint = MakeRefPtr<WaterFlowPaintMethod>();
    if (!contentModifier_) {
        contentModifier_ = AceType::MakeRefPtr<WaterFlowContentModifier>();
    }
    paint->SetContentModifier(contentModifier_);
    return paint;
}

void WaterFlowPattern::OnModifyDone()
{
    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    // SetAxis for scroll event
    SetAxis(layoutProperty->GetAxis());
    if (!GetScrollableEvent()) {
        InitScrollableEvent();
    }
    SetAccessibilityAction();
}

bool WaterFlowPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = dirty->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<WaterFlowLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    auto layoutInfo = layoutAlgorithm->GetLayoutInfo();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto eventHub = host->GetEventHub<WaterFlowEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    if (layoutInfo.itemStart_ && !layoutInfo_.itemStart_) {
        // onReachStart
        auto onReachStart = eventHub->GetOnReachStart();
        if (onReachStart) {
            onReachStart();
        }
    }
    if (layoutInfo.offsetEnd_ && !layoutInfo_.offsetEnd_) {
        // onReachEnd
        auto onReachEnd = eventHub->GetOnReachEnd();
        if (onReachEnd) {
            onReachEnd();
        }
    }
    layoutInfo_ = std::move(layoutInfo);
    layoutInfo_.UpdateStartIndex();

    CheckScrollable();

    auto property = host->GetLayoutProperty();
    CHECK_NULL_RETURN(host, false);
    return property->GetPaddingProperty() != nullptr;
}

void WaterFlowPattern::CheckScrollable()
{
    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    SetScrollEnable(IsScrollable());
    if (!layoutProperty->GetScrollEnabled().value_or(IsScrollable())) {
        SetScrollEnable(false);
    }
}

void WaterFlowPattern::SetPositionController(RefPtr<WaterFlowPositionController> control)
{
    controller_ = control;
    if (control) {
        control->SetScrollPattern(AceType::WeakClaim<WaterFlowPattern>(this));
    }
}

void WaterFlowPattern::InitScrollableEvent()
{
    AddScrollEvent();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WaterFlowEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto scrollFrameBeginEvent = eventHub->GetOnScrollFrameBegin();
    SetScrollFrameBeginCallback(scrollFrameBeginEvent);
}

bool WaterFlowPattern::UpdateStartIndex(int32_t index)
{
    layoutInfo_.jumpIndex_ = index + layoutInfo_.footerIndex_ + 1;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return true;
}

int32_t WaterFlowPattern::GetRows() const
{
    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0);

    return layoutProperty->GetAxis() == Axis::VERTICAL ? layoutInfo_.GetMainCount() : layoutInfo_.GetCrossCount();
}

int32_t WaterFlowPattern::GetColumns() const
{
    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0);

    return layoutProperty->GetAxis() == Axis::VERTICAL ? layoutInfo_.GetCrossCount() : layoutInfo_.GetMainCount();
}

void WaterFlowPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(pattern->IsScrollable());
        pattern->ScrollPage(false);
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(pattern->IsScrollable());
        pattern->ScrollPage(true);
    });
}

void WaterFlowPattern::ScrollPage(bool reverse)
{
    CHECK_NULL_VOID(IsScrollable());

    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto axis = layoutProperty->GetAxis();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto mainContentSize = geometryNode->GetPaddingSize().MainSize(axis);

    UpdateCurrentOffset(reverse ? mainContentSize : -mainContentSize, SCROLL_FROM_JUMP);

    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
}

void WaterFlowPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("friction", GetFriction());
}

std::string WaterFlowPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    jsonObj->Put("beginIndex", GetBeginIndex());
    Dimension dimension(GetStoredOffset());
    jsonObj->Put("offset", dimension.ConvertToVp());
    return jsonObj->ToString();
}

void WaterFlowPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    UpdateStartIndex(info->GetInt("beginIndex"));
    Dimension dimension(info->GetDouble("offset"), DimensionUnit::VP);
    SetRestoreOffset(dimension.ConvertToPx());
}

Rect WaterFlowPattern::GetItemRect(int32_t index) const
{
    if (index < 0 || index < layoutInfo_.startIndex_ || index > layoutInfo_.endIndex_) {
        return Rect();
    }
    index += layoutInfo_.footerIndex_ + 1;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, Rect());
    auto item = host->GetChildByIndex(index);
    CHECK_NULL_RETURN(item, Rect());
    auto itemGeometry = item->GetGeometryNode();
    CHECK_NULL_RETURN(itemGeometry, Rect());
    return Rect(itemGeometry->GetFrameRect().GetX(), itemGeometry->GetFrameRect().GetY(),
        itemGeometry->GetFrameRect().Width(), itemGeometry->GetFrameRect().Height());
}
} // namespace OHOS::Ace::NG
