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

#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "frameworks/core/components_ng/pattern/pattern.h"
#include "frameworks/core/components_ng/pattern/select_overlay/select_overlay_node.h"
namespace OHOS::Ace::NG {
SelectOverlayNode::SelectOverlayNode(const std::shared_ptr<SelectOverlayInfo>& info)
    : FrameNode("SelectOverlay", static_cast<int32_t>(info->singleLineHeight), MakeRefPtr<SelectOverlayPattern>(info))
{}

RefPtr<FrameNode> SelectOverlayNode::CreateSelectOverlayNode(const std::shared_ptr<SelectOverlayInfo>& info)
{
    auto selectOverlayNode = AceType::MakeRefPtr<SelectOverlayNode>(info);
    return selectOverlayNode;
}

void SelectOverlayNode::CreateToolBar() {}

RefPtr<FrameNode> SelectOverlayNode::CreateMenuNode(const std::shared_ptr<SelectOverlayInfo>& info)
{
    return nullptr;
}

void SelectOverlayNode::UpdateToolBar(bool menuItemChanged) {}

bool SelectOverlayNode::IsInSelectedOrSelectOverlayArea(const PointF& point)
{
    return true;
}

void SelectOverlayNode::SetClosedByGlobalEvent(bool closedByGlobalEvent) {}
} // namespace OHOS::Ace::NG
