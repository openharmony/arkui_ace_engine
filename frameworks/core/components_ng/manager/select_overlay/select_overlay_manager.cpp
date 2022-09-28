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

#include <memory>

#include "base/utils/utils.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
RefPtr<SelectOverlayProxy> SelectOverlayManager::CreateAndShowSelectOverlay(const SelectOverlayInfo& info)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_RETURN(rootNode, nullptr);
    auto current = selectOverlayItem_.Upgrade();
    if (current) {
        DestroySelectOverlay(current->GetId());
    }
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    // mount to parent
    selectOverlayNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    auto proxy = MakeRefPtr<SelectOverlayProxy>(selectOverlayNode->GetId());
    selectOverlayItem_ = selectOverlayNode;
    return proxy;
}

void SelectOverlayManager::DestroySelectOverlay(const RefPtr<SelectOverlayProxy>& proxy)
{
    auto id = proxy->GetSelectOverlayId();
    DestroySelectOverlay(id);
}

void SelectOverlayManager::DestroySelectOverlay(int32_t overlayId)
{
    auto rootNode = rootNodeWeak_.Upgrade();
    CHECK_NULL_VOID(rootNode);
    auto current = selectOverlayItem_.Upgrade();
    if (current && (current->GetId() == overlayId)) {
        rootNode->RemoveChild(current);
        rootNode->MarkNeedSyncRenderTree();
        rootNode->RebuildRenderContextTree();
        selectOverlayItem_.Reset();
    } else {
        LOGD("current overlay id %{public}d is already destroyed.", overlayId);
    }
}

bool SelectOverlayManager::HasSelectOverlay(int32_t overlayId)
{
    auto current = selectOverlayItem_.Upgrade();
    return current && (current->GetId() == overlayId);
}

RefPtr<SelectOverlayNode> SelectOverlayManager::GetSelectOverlayNode(int32_t overlayId)
{
    auto current = selectOverlayItem_.Upgrade();
    if (current && (current->GetId() == overlayId)) {
        return DynamicCast<SelectOverlayNode>(current);
    }
    return nullptr;
}
} // namespace OHOS::Ace::NG