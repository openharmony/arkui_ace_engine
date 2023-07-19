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

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

namespace OHOS::Ace::NG {
void ScrollablePaintProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const {}

bool ScrollablePattern::OnScrollCallback(float offset, int32_t source)
{
    return true;
}

void ScrollablePattern::SetAxis(Axis) {}

void ScrollablePattern::AddScrollEvent() {}

void ScrollablePattern::SetEdgeEffect(EdgeEffect) {}

void ScrollablePattern::SetScrollBar(DisplayMode displayMode) {}

void ScrollablePattern::SetScrollBar(const std::unique_ptr<ScrollBarProperty>&) {}

bool ScrollablePattern::HandleEdgeEffect(float, int32_t, const SizeF&)
{
    return false;
}

void ScrollablePattern::UpdateScrollBarRegion(float offset, float estimatedHeight, Size viewPort, Offset viewOffset) {}

void ScrollablePattern::AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool smooth) {}

void ScrollablePattern::ScrollTo(float position) {}

void ScrollablePattern::StopAnimate() {}

void ScrollablePattern::InitMouseEvent() {}

void ScrollablePattern::UninitMouseEvent() {}

void ScrollablePattern::DrawSelectedZone(const RectF& selectedZone) {}

void ScrollablePattern::ClearSelectedZone() {}

void ScrollablePattern::MarkSelectedItems() {}
} // namespace OHOS::Ace::NG
