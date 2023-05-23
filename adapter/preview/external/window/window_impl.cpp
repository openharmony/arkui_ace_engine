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

#include "adapter/preview/external/window/window_impl.h"

#include <ui/rs_surface_node.h>

#include "base/utils/time_util.h"

namespace OHOS {
namespace Rosen {

sptr<Window> Window::Create(SendRenderDataCallback onRender)
{
    return sptr<Window>(new WindowImpl(onRender));
}

WindowImpl::WindowImpl(SendRenderDataCallback onRender)
{
    struct Rosen::RSSurfaceNodeConfig rsSurfaceNodeConfig = {
        .SurfaceNodeName = "preview_surface",
        .additionalData = reinterpret_cast<void*>(onRender),
    };
    surfaceNode_ = Rosen::RSSurfaceNode::Create(rsSurfaceNodeConfig);
}

WindowImpl::~WindowImpl()
{
    vsyncRequests_.Push(false);
    vsyncThread_->join();
}

void WindowImpl::RequestVsync(const std::shared_ptr<VsyncCallback>& vsyncCallback)
{
    {
        std::unique_lock lock(mutex_);
        pendingVsyncCallbacks_.emplace_back(std::move(vsyncCallback));
    }
    if (vsyncThread_ == nullptr) {
        auto func = [this] { VsyncThreadMain(); };
        vsyncThread_ = std::make_unique<std::thread>(func);
    }
    vsyncRequests_.Push(true);
}

std::shared_ptr<RSSurfaceNode> WindowImpl::GetSurfaceNode() const
{
    return surfaceNode_;
}

void WindowImpl::VsyncThreadMain()
{
    while (true) {
        bool next = false;
        vsyncRequests_.PopFront(next);
        if (next == false) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        {
            std::unique_lock lock(mutex_);
            vsyncCallbacks_.swap(pendingVsyncCallbacks_);
        }
        int64_t now = Ace::GetSysTimestamp();
        for (auto& callback : vsyncCallbacks_) {
            callback->onCallback(now);
        }
        vsyncCallbacks_.clear();
    }
}

} // namespace Rosen
} // namespace OHOS
