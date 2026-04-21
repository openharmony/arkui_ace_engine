/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components/common/layout/screen_system_manager.h"

namespace OHOS::Ace {
std::mutex ScreenSystemManager::lock;

ScreenSystemManager& ScreenSystemManager::GetInstance()
{
    static ScreenSystemManager instance;
    return instance;
}

void ScreenSystemManager::OnSurfaceChanged(double width)
{
    std::lock_guard<std::mutex> guard(lock);
    screenWidth_ = width;
}

double ScreenSystemManager::GetScreenWidth(const RefPtr<PipelineBase>& pipeline) const
{
    (void)pipeline;
    std::lock_guard<std::mutex> guard(lock);
    return screenWidth_;
}

ScreenSizeType ScreenSystemManager::GetSize(double width) const
{
    (void)width;
    return ScreenSizeType::UNDEFINED;
}
} // namespace OHOS::Ace
