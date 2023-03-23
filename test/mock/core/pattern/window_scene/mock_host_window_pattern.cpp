/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/window_scene/scene/host/host_window_pattern.h"

namespace OHOS::Ace::NG {
HostWindowPattern::HostWindowPattern() = default;

void HostWindowPattern::RegisterLifecycleListener() {}

void HostWindowPattern::InitContent() {}

void HostWindowPattern::BufferAvailableCallback() {}

bool HostWindowPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    return true;
}

void HostWindowPattern::OnAttachToFrameNode() {}

void HostWindowPattern::DispatchPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) {}
} // namespace OHOS::Ace::NG
