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

#include "core/components_ng/render/adapter/rosen_window.h"

#include "transaction/rs_interfaces.h"

#include "base/log/jank_frame_report.h"
#include "base/thread/task_executor.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/thread_checker.h"
#include "core/common/window.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace {
constexpr int32_t IDLE_TASK_DELAY_MILLISECOND = 51;
constexpr float ONE_SECOND_IN_NANO = 1000000000.0f;

#ifdef PREVIEW
float GetDisplayRefreshRate()
{
    return 30.0f;
}
#endif
} // namespace

namespace OHOS::Ace::NG {

RosenWindow::RosenWindow(const OHOS::sptr<OHOS::Rosen::Window>& window, RefPtr<TaskExecutor> taskExecutor, int32_t id)
    : rsWindow_(window), taskExecutor_(taskExecutor), id_(id)
{
#ifdef PREVIEW
    int64_t refreshPeriod = static_cast<int64_t>(ONE_SECOND_IN_NANO / GetDisplayRefreshRate());
#else
    int64_t refreshPeriod = window->GetVSyncPeriod();
#endif
    vsyncCallback_ = std::make_shared<OHOS::Rosen::VsyncCallback>();
    vsyncCallback_->onCallback = [weakTask = taskExecutor_, id = id_, refreshPeriod](int64_t timeStampNanos) {
        auto taskExecutor = weakTask.Upgrade();
        auto onVsync = [id, timeStampNanos, refreshPeriod] {
            ContainerScope scope(id);
            // use container to get window can make sure the window is valid
            auto container = Container::Current();
            CHECK_NULL_VOID(container);
            auto window = container->GetWindow();
            CHECK_NULL_VOID(window);
            window->OnVsync(static_cast<uint64_t>(timeStampNanos), 0);
            auto pipeline = container->GetPipelineContext();
            CHECK_NULL_VOID_NOLOG(pipeline);
            pipeline->OnIdle(timeStampNanos + refreshPeriod);
            JankFrameReport::JankFrameRecord(timeStampNanos);
        };
        auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::UI);
        if (uiTaskRunner.IsRunOnCurrentThread()) {
            onVsync();
            return;
        }
        uiTaskRunner.PostTask([callback = std::move(onVsync)]() { callback(); });
    };
    rsUIDirector_ = OHOS::Rosen::RSUIDirector::Create();
    if (window->GetSurfaceNode()) {
        rsUIDirector_->SetRSSurfaceNode(window->GetSurfaceNode());
    }
    rsUIDirector_->SetCacheDir(AceApplicationInfo::GetInstance().GetDataFileDirPath());
    rsUIDirector_->Init();
    rsUIDirector_->SetUITaskRunner([taskExecutor, id](const std::function<void()>& task) {
        ContainerScope scope(id);
        CHECK_NULL_VOID_NOLOG(taskExecutor);
        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
    });
}

void RosenWindow::Init()
{
    CHECK_NULL_VOID(rsWindow_);
    auto surfaceNode = rsWindow_->GetSurfaceNode();
    if (rsUIDirector_ && surfaceNode) {
        rsUIDirector_->SetRSSurfaceNode(surfaceNode);
    }
}

void RosenWindow::RequestFrame()
{
    CHECK_NULL_VOID_NOLOG(onShow_);
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID_NOLOG(!isRequestVsync_);
    LOGD("request next vsync");
    if (rsWindow_) {
        isRequestVsync_ = true;
        rsWindow_->RequestVsync(vsyncCallback_);
        lastRequestVsyncTime_ = GetSysTimestamp();
    }
    auto taskExecutor = taskExecutor_.Upgrade();
    if (taskExecutor) {
        taskExecutor->PostDelayedTask(
            [id = id_]() {
                ContainerScope scope(id);
                auto container = Container::Current();
                CHECK_NULL_VOID(container);
                auto pipeline = container->GetPipelineContext();
                CHECK_NULL_VOID_NOLOG(pipeline);
                pipeline->OnIdle(0);
            },
            TaskExecutor::TaskType::UI, IDLE_TASK_DELAY_MILLISECOND);
    }
}

void RosenWindow::OnShow()
{
    Window::OnShow();
    CHECK_NULL_VOID(rsUIDirector_);
    rsUIDirector_->GoForeground();
}

void RosenWindow::OnHide()
{
    Window::OnHide();
    CHECK_NULL_VOID(rsUIDirector_);
    rsUIDirector_->GoBackground();
    rsUIDirector_->SendMessages();
}

void RosenWindow::Destroy()
{
    LOG_DESTROY();
    rsWindow_ = nullptr;
    vsyncCallback_.reset();
    rsUIDirector_->Destroy();
    rsUIDirector_.reset();
    callbacks_.clear();
}

void RosenWindow::SetDrawTextAsBitmap(bool useBitmap)
{
    Rosen::RSSystemProperties::SetDrawTextAsBitmap(useBitmap);
}

void RosenWindow::SetRootFrameNode(const RefPtr<NG::FrameNode>& root)
{
    LOGI("Rosenwindow set root frame node");
    CHECK_NULL_VOID(root);
    auto rosenRenderContext = AceType::DynamicCast<RosenRenderContext>(root->GetRenderContext());
    CHECK_NULL_VOID(rosenRenderContext);
    if (rosenRenderContext->GetRSNode()) {
        CHECK_NULL_VOID(rsUIDirector_);
        rsUIDirector_->SetRoot(rosenRenderContext->GetRSNode()->GetId());
    }
}

void RosenWindow::RecordFrameTime(uint64_t timeStamp, const std::string& name)
{
    LOGD("Rosenwindow RecordFrameTime");
    CHECK_NULL_VOID(rsUIDirector_);
    rsUIDirector_->SetTimeStamp(timeStamp, name);
}

void RosenWindow::FlushTasks()
{
    CHECK_RUN_ON(UI);
    LOGD("Rosenwindow flush tasks");
    CHECK_NULL_VOID(rsUIDirector_);
    rsUIDirector_->SendMessages();
    JankFrameReport::JsAnimationToRsRecord();
}

float RosenWindow::GetRefreshRate() const
{
#ifdef PREVIEW
    return GetDisplayRefreshRate();
#else
    return ONE_SECOND_IN_NANO / rsWindow_->GetVSyncPeriod();
#endif
}

void RosenWindow::SetKeepScreenOn(bool keepScreenOn)
{
#ifdef OHOS_PLATFORM
    if (rsWindow_) {
        LOGD("Rosenwindow SetKeepScreenOn switch = %{public}d", keepScreenOn);
        rsWindow_->SetKeepScreenOn(keepScreenOn);
    } else {
        LOGE("SetKeepScreenOn Rosenwindow is null");
    }
#else
    LOGD("Rosenwindow unsupports the SetKeepScreenOn");
#endif
}

} // namespace OHOS::Ace::NG
