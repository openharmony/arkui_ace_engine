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
