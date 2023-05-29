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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_WINDOW_WINDOW_IMPL_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_WINDOW_WINDOW_IMPL_H

#include <mutex>
#include <thread>
#include <vector>

#include "adapter/preview/external/window/window.h"
#include "base/thread/sem_queue.h"

namespace OHOS {
namespace Rosen {

class WindowImpl : public Window {
public:
    WindowImpl(SendRenderDataCallback onRender);
    ~WindowImpl() override;

    void RequestVsync(const std::shared_ptr<VsyncCallback>& vsyncCallback) override;
    std::shared_ptr<RSSurfaceNode> GetSurfaceNode() const override;

private:
    void VsyncThreadMain();
    std::shared_ptr<RSSurfaceNode> surfaceNode_;
    std::vector<std::shared_ptr<VsyncCallback>> vsyncCallbacks_;
    std::vector<std::shared_ptr<VsyncCallback>> pendingVsyncCallbacks_;
    std::unique_ptr<std::thread> vsyncThread_;
    Ace::SemQueue<bool> vsyncRequests_;
    std::mutex mutex_;
};

} // namespace Rosen
} // namespace OHOS
#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_WINDOW_WINDOW_IMPL_H
