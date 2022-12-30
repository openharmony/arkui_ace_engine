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

#include "include/vsync_station.h"

#include "core/components_ng/pattern/window_scene/container/window_pattern.h"

namespace OHOS::Ace::NG {

WindowPattern::WindowPattern(const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode)
    : surfaceNode_(surfaceNode)
{}

void WindowPattern::RequestVsync(const std::shared_ptr<Rosen::VsyncCallback>& vsyncCallback)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    // if (state_ == WindowState::STATE_DESTROYED) {
    //    LOGE("[WM] Receive Vsync Request failed, window is destroyed");
    //     return;
    // }
    Rosen::VsyncStation::GetInstance().RequestVsync(vsyncCallback);
}

} // namespace OHOS::Ace::NG
