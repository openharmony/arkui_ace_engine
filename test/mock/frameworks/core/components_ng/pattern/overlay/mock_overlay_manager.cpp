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

#include "core/components_ng/pattern/overlay/overlay_manager.h"

namespace OHOS::Ace::NG {
OverlayManager::OverlayManager(const RefPtr<FrameNode>& rootNode) : rootNodeWeak_(rootNode) {}
OverlayManager::~OverlayManager() = default;

void OverlayManager::DumpOverlayInfo() const {}

void OverlayManager::CloseDialog(const RefPtr<FrameNode>& dialogNode)
{
    (void)dialogNode;
}

void OverlayManager::MarkDirty(PropertyChangeFlag flag)
{
    (void)flag;
}

RefPtr<UINode> OverlayManager::FindChildNodeByKey(const RefPtr<NG::UINode>& parentNode, const std::string& key)
{
    (void)parentNode;
    (void)key;
    return nullptr;
}

void OverlayManager::HideAllMenus() {}

void OverlayManager::HideAllMenusWithoutAnimation(bool showInSubwindow)
{
    (void)showInSubwindow;
}

void OverlayManager::HideAllPopupsWithoutAnimation() {}

void OverlayManager::HideCustomPopups() {}

void OverlayManager::UpdateCustomKeyboardPosition() {}

bool OverlayManager::RemoveOverlay(bool isBackPressed, bool isPageRouter)
{
    (void)isBackPressed;
    (void)isPageRouter;
    return false;
}

void OverlayManager::ClearToastInSubwindow() {}

void OverlayManager::ReloadBuilderNodeConfig() {}

void OverlayManager::ClearUIExtensionNode() {}

void OverlayManager::OnKeyboardAvoid() {}

const WeakPtr<UINode>& OverlayManager::GetRootNode() const
{
    static WeakPtr<UINode> empty;
    return empty;
}

void OverlayManager::MountFilterToWindowScene(const RefPtr<FrameNode>& columnNode, const RefPtr<UINode>& windowScene)
{
    (void)columnNode;
    (void)windowScene;
}

void OverlayManager::MountPixelMapToWindowScene(
    const RefPtr<FrameNode>& columnNode, const RefPtr<UINode>& windowScene, bool isDragPixelMap)
{
    (void)columnNode;
    (void)windowScene;
    (void)isDragPixelMap;
}

void OverlayManager::MountEventToWindowScene(const RefPtr<FrameNode>& columnNode, const RefPtr<UINode>& windowScene)
{
    (void)columnNode;
    (void)windowScene;
}

void OverlayManager::MountPixelMapToRootNode(
    const RefPtr<FrameNode>& columnNode, bool isDragPixelMap, const RefPtr<FrameNode>& hostNode)
{
    (void)columnNode;
    (void)isDragPixelMap;
    (void)hostNode;
}

void OverlayManager::MountEventToRootNode(const RefPtr<FrameNode>& columnNode)
{
    (void)columnNode;
}

void OverlayManager::RemovePixelMap() {}

void OverlayManager::RemovePixelMapAnimation(bool startDrag, double x, double y, bool isSubwindowOverlay)
{
    (void)startDrag;
    (void)x;
    (void)y;
    (void)isSubwindowOverlay;
}

void OverlayManager::RemoveFilterAnimation() {}

void OverlayManager::RemoveEventColumn() {}

RefPtr<UINode> OverlayManager::FindWindowScene(RefPtr<FrameNode> targetNode)
{
    (void)targetNode;
    return nullptr;
}

void OverlayManager::MountGatherNodeToWindowScene(const RefPtr<FrameNode>& frameNode,
    const std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo, const RefPtr<UINode>& windowScene)
{
    (void)frameNode;
    (void)gatherNodeChildrenInfo;
    (void)windowScene;
}

void OverlayManager::RemoveGatherNode() {}

void OverlayManager::RemoveGatherNodeWithAnimation() {}

void OverlayManager::RemovePreviewBadgeNode() {}

void OverlayManager::MountGatherNodeToRootNode(
    const RefPtr<FrameNode>& frameNode, const std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo)
{
    (void)frameNode;
    (void)gatherNodeChildrenInfo;
}

bool OverlayManager::IsGatherWithMenu()
{
    return false;
}

RefPtr<FrameNode> OverlayManager::GetPixelMapContentNode(bool isSubwindowOverlay) const
{
    return nullptr;
}
} // namespace OHOS::Ace::NG
