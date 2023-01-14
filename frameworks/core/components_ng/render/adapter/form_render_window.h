/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENT_FORM_FORM_RENDER_WINDOW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENT_FORM_FORM_RENDER_WINDOW_H

#include <memory>

#include "render_service_client/core/ui/rs_ui_director.h"
#include "vsync_receiver.h"

#include "base/thread/task_executor.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/common/window.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {

class ACE_EXPORT FormRenderWindow : public Window {
public:
    explicit FormRenderWindow(RefPtr<TaskExecutor> taskExecutor, int32_t id);
    FormRenderWindow() = default;
    ~FormRenderWindow() = default;

    void RequestFrame() override;

    void SetRootRenderNode(const RefPtr<RenderNode>& root) override {}

    void SetRootFrameNode(const RefPtr<NG::FrameNode>& root) override;

    std::shared_ptr<OHOS::Rosen::RSUIDirector> GetRsUIDirector() const
    {
        return rsUIDirector_;
    }

    void SetFormRSSurfaceNode(void* surfaceNode) override;
    void OnShow() override;
    void OnHide() override;
    void FlushTasks() override;

private:
    std::shared_ptr<Rosen::VSyncReceiver> receiver_ = nullptr;
    Rosen::VSyncReceiver::FrameCallback frameCallback_;
    WeakPtr<TaskExecutor> taskExecutor_ = nullptr;
    int32_t id_ = 0;
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUIDirector_;
    ACE_DISALLOW_COPY_AND_MOVE(FormRenderWindow);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENT_FORM_FORM_RENDER_WINDOW_H
