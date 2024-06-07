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

#include "rosen_window.h"
#include <chrono>

#include "base/log/log.h"

namespace OHOS::Ace {

std::unique_ptr<PlatformWindow> PlatformWindow::Create(AceView* view)
{
    if (view != nullptr) {
        return std::make_unique<Platform::RSWindow>();
    } else {
        return nullptr;
    }
}

namespace Platform {

void RSWindow::Destroy()
{
    vsyncRequests_.Push(false);
    vsyncThread_->join();
}

void RSWindow::RequestFrame()
{
    if (vsyncThread_ == nullptr) {
        auto func = std::bind(&RSWindow::VsyncThreadMain, this);
        vsyncThread_ = std::make_unique<std::thread>(func);
    }

    vsyncRequests_.Push(true);
}

void RSWindow::RegisterVsyncCallback(AceVsyncCallback&& callback)
{
    std::unique_lock lock(mutex_);
    pendingVsyncCallbacks_.emplace_back(std::move(callback));
}

void RSWindow::SetRootRenderNode(const RefPtr<RenderNode>& root)
{
}

void RSWindow::SetUiDvsyncSwitch(bool dvsyncSwitch)
{
}

void RSWindow::VsyncThreadMain()
{
    while (true) {
        bool next = false;
        vsyncRequests_.PopFront(next);
        if (!next) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        {
            std::unique_lock lock(mutex_);
            vsyncCallbacks_.swap(pendingVsyncCallbacks_);
        }
        int64_t now = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
        for (auto &callback : vsyncCallbacks_) {
            callback(now, 0);
        }
        vsyncCallbacks_.clear();
    }
}

} // namespace Platform
} // namespace OHOS::Ace
