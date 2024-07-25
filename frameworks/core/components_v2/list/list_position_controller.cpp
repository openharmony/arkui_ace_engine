/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "core/components_v2/list/list_position_controller.h"

#include "core/components_v2/list/render_list.h"

namespace OHOS::Ace::V2 {

void ListPositionController::ScrollToIndex(
    int32_t index, bool /* smooth */, ScrollAlign /* align */, std::optional<float> /* extraOffset */)
{
    auto list = AceType::DynamicCast<V2::RenderList>(scroll_.Upgrade());
    if (!list) {
        return;
    }
    list->JumpToIndex(index);
}

bool ListPositionController::AnimateTo(
    const Dimension& position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll)
{
    auto list = AceType::DynamicCast<V2::RenderList>(scroll_.Upgrade());
    if (!list) {
        return false;
    }
    list->AnimateTo(position, duration, curve);
    return true;
}

Axis ListPositionController::GetScrollDirection() const
{
    auto list = AceType::DynamicCast<V2::RenderList>(scroll_.Upgrade());
    if (!list) {
        return Axis::NONE;
    }
    return list->IsVertical() ? Axis::VERTICAL : Axis::HORIZONTAL;
}

Offset ListPositionController::GetCurrentOffset() const
{
    auto list = AceType::DynamicCast<V2::RenderList>(scroll_.Upgrade());
    if (!list) {
        return Offset::Zero();
    }
    return list->CurrentOffset();
}

void ListPositionController::ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth)
{
    auto list = AceType::DynamicCast<V2::RenderList>(scroll_.Upgrade());
    if (!list) {
        return;
    }
    return list->ScrollToEdge(scrollEdgeType, smooth);
}

void ListPositionController::ScrollPage(bool reverse, bool smooth)
{
    auto list = AceType::DynamicCast<V2::RenderList>(scroll_.Upgrade());
    if (!list) {
        return;
    }
    return list->ScrollPage(reverse, smooth);
}

void ListPositionController::ScrollBy(double pixelX, double pixelY, bool smooth)
{
    auto list = AceType::DynamicCast<V2::RenderList>(scroll_.Upgrade());
    if (!list) {
        return;
    }
    list->ScrollBy(pixelX, pixelY);
}

} // namespace OHOS::Ace::V2
