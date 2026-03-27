/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"

namespace OHOS::Ace::NG {
SelectOverlayManager::~SelectOverlayManager() = default;

void SelectOverlayManager::OnFontChanged() {}

int32_t SelectOverlayManager::GetTextSelectionHolderId()
{
    return -1;
}

void SelectOverlayManager::MarkDirty(PropertyChangeFlag flag)
{
    (void)flag;
}

bool SelectOverlayManager::ResetSelectionAndDestroySelectOverlay(bool isBackPressed, bool animation)
{
    (void)isBackPressed;
    (void)animation;
    return false;
}
} // namespace OHOS::Ace::NG
