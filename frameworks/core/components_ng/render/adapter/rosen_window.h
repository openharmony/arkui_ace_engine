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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_WINDOW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_WINDOW_H

#include "render_service_client/core/ui/rs_ui_director.h"
#include "vsync_receiver.h"
#include "wm/window.h"

#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "core/common/window.h"

namespace OHOS::Ace::NG {

class RosenWindow : public Window {
public:
    RosenWindow(const OHOS::sptr<OHOS::Rosen::Window>& window, RefPtr<TaskExecutor> taskExecutor, int32_t id);
    ~RosenWindow() override = default;

    void RequestFrame() override;

    void Destroy() override;

    void SetRootRenderNode(const RefPtr<RenderNode>& root) override {}

    void SetRootFrameNode(const RefPtr<NG::FrameNode>& root) override;

    void RecordFrameTime(uint64_t timeStamp, const std::string& name) override;

    void FlushTasks() override;

    void SetTaskRunner(RefPtr<TaskExecutor> taskExecutor, int32_t id);

private:
    OHOS::sptr<OHOS::Rosen::Window> rsWindow_;
    WeakPtr<TaskExecutor> taskExecutor_;
    RefPtr<NG::FrameNode> rootNode_;
    int32_t id_ = 0;
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUIDirector_;
    std::shared_ptr<OHOS::Rosen::VsyncCallback> vsyncCallback_;

    ACE_DISALLOW_COPY_AND_MOVE(RosenWindow);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_WINDOW_H
