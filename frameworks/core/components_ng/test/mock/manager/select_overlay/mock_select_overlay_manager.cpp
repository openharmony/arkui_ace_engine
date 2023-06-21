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

#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"

namespace OHOS::Ace::NG {
namespace {
// SELECT_OVERLAY_ID is seen as the default SELECT_OVERLAY_ID
constexpr int32_t SELECT_OVERLAY_ID = 143;
} // namespace

RefPtr<SelectOverlayProxy> SelectOverlayManager::CreateAndShowSelectOverlay(
    const SelectOverlayInfo& info, const WeakPtr<SelectionHost>& host)
{
    return MakeRefPtr<SelectOverlayProxy>(0);
}

void SelectOverlayManager::DestroySelectOverlay(const RefPtr<SelectOverlayProxy>& proxy) {}

void SelectOverlayManager::DestroySelectOverlay(int32_t overlayId) {}

void SelectOverlayManager::DestroySelectOverlay() {}

bool SelectOverlayManager::IsInSelectedOrSelectOverlayArea(const PointF& point)
{
    return true;
}

bool SelectOverlayManager::HasSelectOverlay(int32_t overlayId)
{
    return SELECT_OVERLAY_ID == overlayId;
}

RefPtr<SelectOverlayNode> SelectOverlayManager::GetSelectOverlayNode(int32_t overlayId)
{
    SelectOverlayInfo info;
    info.singleLineHeight = static_cast<float>(overlayId);
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto selectOverlayNode = DynamicCast<SelectOverlayNode>(SelectOverlayNode::CreateSelectOverlayNode(infoPtr));
    return selectOverlayNode;
}
} // namespace OHOS::Ace::NG
