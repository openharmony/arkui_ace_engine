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

#include "core/components_ng/pattern/window_scene/scene/container/window_pattern.h"

#include "include/vsync_station.h"
#include "render_service_client/core/ui/rs_ui_director.h"

#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace {
constexpr int32_t IDLE_TASK_DELAY_MILLISECOND = 51;
constexpr float ONE_SECOND_IN_NANO = 1000000000.0f;

float GetDisplayRefreshRate()
{
    return 60.0f;
}
} // namespace

namespace OHOS::Ace::NG {

void WindowPattern::Init()
{
    int64_t refreshPeriod = static_cast<int64_t>(ONE_SECOND_IN_NANO / GetDisplayRefreshRate());
    vsyncCallback_ = std::make_shared<Rosen::VsyncCallback>();
    vsyncCallback_->onCallback = [weakTask = taskExecutor_, instanceId = instanceId_, refreshPeriod]
        (int64_t nanoTimestamp) {
        auto onVsync = [instanceId, nanoTimestamp, refreshPeriod] {
            ContainerScope scope(instanceId);
            // use container to get window can make sure the window is valid
            auto container = Container::Current();
            CHECK_NULL_VOID(container);
            auto window = container->GetWindowPattern();
            CHECK_NULL_VOID(window);
            window->OnVsync(static_cast<uint64_t>(nanoTimestamp), 0);
            auto pipeline = container->GetPipelineContext();
            if (pipeline) {
                pipeline->OnIdle(nanoTimestamp + refreshPeriod);
            }
        };
        auto taskExecutor = weakTask.Upgrade();
        CHECK_NULL_VOID(taskExecutor);
        auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::UI);
        if (uiTaskRunner.IsRunOnCurrentThread()) {
            onVsync();
            return;
        }
        uiTaskRunner.PostTask([callback = std::move(onVsync)]() { callback(); });
    };
    rsUIDirector_ = Rosen::RSUIDirector::Create();
    rsUIDirector_->SetRSSurfaceNode(GetSurfaceNode());
    rsUIDirector_->SetCacheDir(AceApplicationInfo::GetInstance().GetDataFileDirPath());
    rsUIDirector_->Init();
    rsUIDirector_->SetUITaskRunner([taskExecutor = taskExecutor_.Upgrade(), instanceId = instanceId_]
        (const std::function<void()>& task) {
        ContainerScope scope(instanceId);
        if (taskExecutor) {
            taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
        }
    });
}

void WindowPattern::Destroy()
{
    vsyncCallback_.reset();
    rsUIDirector_->Destroy();
    rsUIDirector_.reset();
    callbacks_.clear();
}

void WindowPattern::SetRootFrameNode(const RefPtr<NG::FrameNode>& root)
{
    LOGI("WindowPattern set root frame node");
    CHECK_NULL_VOID(root);
    auto rosenRenderContext = AceType::DynamicCast<RosenRenderContext>(root->GetRenderContext());
    CHECK_NULL_VOID(rosenRenderContext);
    if (rosenRenderContext->GetRSNode()) {
        rsUIDirector_->SetRoot(rosenRenderContext->GetRSNode()->GetId());
    }
}

void WindowPattern::RequestFrame()
{
    if (!onShow_) {
        LOGD("window is not show, stop request frame");
        return;
    }
    CHECK_RUN_ON(UI);
    if (isRequestVsync_) {
        return;
    }
    LOGD("request next vsync");
    RequestVsync(vsyncCallback_);
    isRequestVsync_ = true;
    auto taskExecutor = taskExecutor_.Upgrade();
    if (taskExecutor) {
        taskExecutor->PostDelayedTask(
            [id = instanceId_]() {
                ContainerScope scope(id);
                auto container = Container::Current();
                CHECK_NULL_VOID(container);
                auto pipeline = container->GetPipelineContext();
                if (pipeline) {
                    pipeline->OnIdle(0);
                }
            },
            TaskExecutor::TaskType::UI, IDLE_TASK_DELAY_MILLISECOND);
    }
}

void WindowPattern::RecordFrameTime(uint64_t timeStamp, const std::string& name)
{
    LOGD("WindowPattern RecordFrameTime");
    rsUIDirector_->SetTimeStamp(timeStamp, name);
}

bool WindowPattern::FlushCustomAnimation(uint64_t timeStamp)
{
    return rsUIDirector_->RunningCustomAnimation(timeStamp);
}

void WindowPattern::FlushTasks()
{
    CHECK_RUN_ON(UI);
    LOGD("WindowPattern flush tasks");
    rsUIDirector_->SendMessages();
}

void WindowPattern::RequestVsync(const std::shared_ptr<Rosen::VsyncCallback>& vsyncCallback)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    Rosen::VsyncStation::GetInstance().RequestVsync(vsyncCallback);
}

void WindowPattern::OnVsync(uint64_t nanoTimestamp, uint32_t frameCount)
{
    isRequestVsync_ = false;
    for (auto& callback : callbacks_) {
        if (callback) {
            callback(nanoTimestamp, frameCount);
        }
    }
}

void WindowPattern::OnShow()
{
    onShow_ = true;
    rsUIDirector_->GoForeground();
    rsUIDirector_->SendMessages();
}

void WindowPattern::OnHide()
{
    onShow_ = false;
    rsUIDirector_->GoBackground();
    rsUIDirector_->SendMessages();
}

void WindowPattern::Connect()
{
    CHECK_NULL_VOID(sessionStage_);
    sessionStage_->Connect();
}

void WindowPattern::Foreground()
{
    CHECK_NULL_VOID(sessionStage_);
    sessionStage_->Foreground();
}

void WindowPattern::Background()
{
    CHECK_NULL_VOID(sessionStage_);
    sessionStage_->Background();
}

void WindowPattern::Disconnect()
{
    CHECK_NULL_VOID(sessionStage_);
    sessionStage_->Disconnect();
}

} // namespace OHOS::Ace::NG
