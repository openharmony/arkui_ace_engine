/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/manager/full_screen/full_screen_manager.h"

namespace OHOS::Ace::NG {
void FullScreenManager::RequestFullScreen(const RefPtr<FrameNode>& frameNode)
{
    (void)frameNode;
}

void FullScreenManager::ExitFullScreen(const RefPtr<FrameNode>& frameNode)
{
    (void)frameNode;
}

bool FullScreenManager::OnBackPressed()
{
    return false;
}
} // namespace OHOS::Ace::NG
