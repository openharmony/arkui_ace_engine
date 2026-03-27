/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
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
} // namespace OHOS::Ace::NG
