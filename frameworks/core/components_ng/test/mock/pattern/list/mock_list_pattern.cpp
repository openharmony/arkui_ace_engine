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

namespace OHOS::Ace::NG {
RefPtr<LayoutAlgorithm> ListPattern::CreateLayoutAlgorithm()
{
    return nullptr;
}

RefPtr<NodePaintMethod> ListPattern::CreateNodePaintMethod()
{
    return nullptr;
}

void ListPattern::OnModifyDone() {}

bool ListPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& /* dirty */, const DirtySwapConfig& /* config */)
{
    return false;
}

bool ListPattern::UpdateCurrentOffset(float offset, int32_t source)
{
    return true;
}

void ListPattern::UpdateScrollBarOffset() {}

bool ListPattern::OnScrollCallback(float offset, int32_t source)
{
    return true;
}

void ListPattern::OnScrollEndCallback() {}

bool ListPattern::ScrollToNode(const RefPtr<FrameNode>& focusFrameNode)
{
    return false;
}

bool ListPattern::IsAtBottom() const
{
    return false;
}

bool ListPattern::IsAtTop() const
{
    return false;
}

bool ListPattern::OutBoundaryCallback()
{
    return false;
}

void ListPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect) {}

void ListPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const {}

void ListPattern::FromJson(const std::unique_ptr<JsonValue>& json) {}

void ListPattern::SetSwiperItem(WeakPtr<ListItemPattern> swiperItem) {}

WeakPtr<FocusHub> ListPattern::GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    return nullptr;
}

OverScrollOffset ListPattern::GetOverScrollOffset(double delta) const
{
    return { 0, 0 };
}

bool ListPattern::OnScrollSnapCallback(double targetOffset, double velocity)
{
    return false;
}

void ListPattern::FireOnScrollStart() {}

void ListPattern::OnAnimateStop() {}

void ListPattern::ScrollTo(float position) {}

void ListPattern::MultiSelectWithoutKeyboard(const RectF& selectedZone) {};

void ListPattern::ClearMultiSelect() {};

bool ListPattern::IsItemSelected(const MouseInfo& info)
{
    return false;
}
} // namespace OHOS::Ace::NG
