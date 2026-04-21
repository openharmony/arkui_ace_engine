/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/manager/navigation/navigation_manager.h"

namespace OHOS::Ace::NG {
NavigationManager::NavigationManager() = default;

bool NavigationManager::AddInteractiveAnimation(const std::function<void()>& addCallback)
{
    (void)addCallback;
    return false;
}

void NavigationManager::CacheNavigationNodeAnimation() {}

void NavigationManager::OnDumpInfo() {}
} // namespace OHOS::Ace::NG
