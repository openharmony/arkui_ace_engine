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

#include "core/common/window.h"

namespace OHOS::Ace {
Window::Window(std::unique_ptr<PlatformWindow> platformWindow) : platformWindow_(std::move(platformWindow)) {}

void Window::OnVsync(uint64_t nanoTimestamp, uint64_t frameCount) {}

void Window::RequestFrame() {}

void Window::SetForceVsyncRequests(bool forceVsyncRequests) {}

void Window::SetRootRenderNode(const RefPtr<RenderNode>& root) {}

void Window::SetVsyncCallback(AceVsyncCallback&& callback) {}

void Window::SetUiDvsyncSwitch(bool dvsyncSwitch) {}

void Window::SetBackgroundForceFlushVsync(bool enable, size_t count)
{
    static constexpr uint32_t MAX_FORCE_FLUSH_COUNT = 10;
    backgroundForceFlushEnabled_.store(enable, std::memory_order_relaxed);
    backgroundForceFlushCount_.store(
        enable ? std::min(static_cast<uint32_t>(count), MAX_FORCE_FLUSH_COUNT) : 0, std::memory_order_relaxed);
}

bool Window::HasBackgroundForceFlushQuota() const
{
    return backgroundForceFlushEnabled_.load(std::memory_order_relaxed) &&
           backgroundForceFlushCount_.load(std::memory_order_relaxed) > 0;
}

bool Window::ConsumeBackgroundForceFlushCount()
{
    if (!backgroundForceFlushEnabled_.load(std::memory_order_relaxed)) {
        return false;
    }
    uint32_t current = backgroundForceFlushCount_.load(std::memory_order_relaxed);
    while (current > 0) {
        if (backgroundForceFlushCount_.compare_exchange_weak(current, current - 1, std::memory_order_relaxed)) {
            if (current == 1) {
                backgroundForceFlushEnabled_.store(false, std::memory_order_relaxed);
            }
            return true;
        }
    }
    return false;
}
} // namespace OHOS::Ace
