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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_WINDOW_PREVIEWER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_WINDOW_PREVIEWER_H

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <refbase.h>
#include <thread>
#include <ui/rs_surface_node.h>
#include <vector>

#include "adapter/preview/entrance/rs_ace_view.h"
#include "base/thread/sem_queue.h"
#include "base/utils/time_util.h"
#include "core/common/window.h"

namespace OHOS {
namespace Rosen {

using OnCallback = std::function<void(int64_t)>;
struct VsyncCallback {
    OnCallback onCallback;
};

using SendRenderDataCallback = bool (*)(const void*, const size_t, const int32_t, const int32_t);
class Window : public RefBase {
public:
    Window(SendRenderDataCallback onRender)
    {
        struct Rosen::RSSurfaceNodeConfig rsSurfaceNodeConfig = {
            .SurfaceNodeName = "preview_surface",
            .onRender = onRender,
        };
        surfaceNode_ = Rosen::RSSurfaceNode::Create(rsSurfaceNodeConfig);
    }

    ~Window()
    {
        vsyncRequests_.Push(false);
        vsyncThread_->join();
    }
    virtual void RequestVsync(const std::shared_ptr<VsyncCallback>& vsyncCallback)
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

    std::shared_ptr<RSSurfaceNode> GetSurfaceNode() const
    {
        return surfaceNode_;
    }

    void VsyncThreadMain()
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
    std::shared_ptr<RSSurfaceNode> surfaceNode_;
    std::vector<std::shared_ptr<VsyncCallback>> vsyncCallbacks_;
    std::vector<std::shared_ptr<VsyncCallback>> pendingVsyncCallbacks_;
    std::unique_ptr<std::thread> vsyncThread_;
    Ace::SemQueue<bool> vsyncRequests_;
    std::mutex mutex_;
};

} // namespace Rosen
} // namespace OHOS
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_WINDOW_PREVIEWER_H
