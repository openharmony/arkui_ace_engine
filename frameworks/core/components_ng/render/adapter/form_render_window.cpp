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

#include "core/components_ng/render/adapter/form_render_window.h"

#include "base/log/frame_report.h"
#include "core/common/container.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "render_service_client/core/ui/rs_root_node.h"
#include "transaction/rs_interfaces.h"
#endif

namespace {
#ifdef ENABLE_ROSEN_BACKEND
constexpr float ONE_SECOND_IN_NANO = 1000000000.0f;

float GetDisplayRefreshRate()
{
    return 60.0f;
}
#endif
} // namespace

namespace OHOS::Ace {

#ifdef ENABLE_ROSEN_BACKEND
std::recursive_mutex FormRenderWindow::globalMutex_;
#endif

FormRenderWindow::FormRenderWindow(RefPtr<TaskExecutor> taskExecutor, int32_t id)
    : taskExecutor_(taskExecutor), id_(id)
{
#ifdef ENABLE_ROSEN_BACKEND
    ContainerScope scope(id);
    auto container = Container::Current();
    if (receiver_ == nullptr) {
        auto& rsClient = Rosen::RSInterfaces::GetInstance();
        frameRateLinker_ = Rosen::RSFrameRateLinker::Create();
        receiver_ = rsClient.CreateVSyncReceiver("Form", frameRateLinker_ != nullptr ? frameRateLinker_->GetId() : 0);
        if (receiver_ == nullptr) {
            LOGE("Form Create VSync receiver failed.");
            return;
        }
        receiver_->Init();
    }

    InitOnVsyncCallback();

    receiver_->RequestNextVSync(frameCallback_);

    rsUIDirector_ = OHOS::Rosen::RSUIDirector::Create();
    {
        std::lock_guard<std::recursive_mutex> lock(globalMutex_);
        rsUIDirector_->Init(); // Func Init Thread unsafe.
    }

    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = {.SurfaceNodeName = surfaceNodeName, .isSync = true};
    rsSurfaceNode_ = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    rsUIDirector_->SetRSSurfaceNode(rsSurfaceNode_);

    rsUIDirector_->SetUITaskRunner([taskExecutor, id = id_](const std::function<void()>& task, uint32_t delay) {
        ContainerScope scope(id);
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostDelayedTask(
            task, TaskExecutor::TaskType::UI, delay, "ArkUIFormRenderServiceTask", PriorityType::HIGH);
    }, id);
#else
    taskExecutor_ = nullptr;
    id_ = 0;
#endif
}

void FormRenderWindow::RequestFrame()
{
#ifdef ENABLE_ROSEN_BACKEND
    if (receiver_ != nullptr) {
        receiver_->RequestNextVSync(frameCallback_);
    }
#endif
}

void FormRenderWindow::Destroy()
{
    TAG_LOGI(AceLogTag::ACE_FORM, "RenderWindow destroyed");
#ifdef ENABLE_ROSEN_BACKEND
    frameCallback_.userData_ = nullptr;
    frameCallback_.callback_ = nullptr;
    if (rsUIDirector_) {
        rsUIDirector_->Destroy();
        rsUIDirector_.reset();
    }
    callbacks_.clear();
#endif
}

void FormRenderWindow::SetRootFrameNode(const RefPtr<NG::FrameNode>& root)
{
    CHECK_NULL_VOID(root);
#ifdef ENABLE_ROSEN_BACKEND
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(root->GetRenderContext());
    CHECK_NULL_VOID(rosenRenderContext);
    if (rosenRenderContext->GetRSNode()) {
        auto rootSRNode = rosenRenderContext->GetRSNode();
        const auto& calcLayoutConstraint = root->GetLayoutProperty()->GetCalcLayoutConstraint();
        auto width = static_cast<float>(calcLayoutConstraint->maxSize->Width()->GetDimension().Value());
        auto height = static_cast<float>(calcLayoutConstraint->maxSize->Height()->GetDimension().Value());
        rootSRNode->SetBounds(0, 0, width, height);
        CHECK_NULL_VOID(rsUIDirector_);
        rsUIDirector_->SetRSRootNode(
            Rosen::RSNode::ReinterpretCast<Rosen::RSRootNode>(rosenRenderContext->GetRSNode()));
    }
    CHECK_NULL_VOID(rsUIDirector_);
    rsUIDirector_->SendMessages();
#endif
}

void FormRenderWindow::OnShow()
{
#ifdef ENABLE_ROSEN_BACKEND
    Window::OnShow();
    CHECK_NULL_VOID(rsUIDirector_);
    rsUIDirector_->GoForeground();
#endif
}

void FormRenderWindow::OnHide()
{
#ifdef ENABLE_ROSEN_BACKEND
    Window::OnHide();
#endif
}

void FormRenderWindow::FlushTasks(std::function<void()> callback)
{
#ifdef ENABLE_ROSEN_BACKEND
    CHECK_NULL_VOID(rsUIDirector_);
    if (!callback) {
        rsUIDirector_->SendMessages();
    } else {
        rsUIDirector_->SendMessages(callback);
    }
#endif
}

void FormRenderWindow::Lock()
{
}

void FormRenderWindow::Unlock()
{
}

int64_t FormRenderWindow::GetVSyncPeriod() const
{
    int64_t vSyncPeriod = 0;
#if defined(ENABLE_ROSEN_BACKEND) && defined(__OHOS__)
    if (receiver_) {
        receiver_->GetVSyncPeriod(vSyncPeriod);
    }
#endif

    return vSyncPeriod;
}

void FormRenderWindow::FlushFrameRate(int32_t rate, int32_t animatorExpectedFrameRate, int32_t rateType)
{
#ifdef ENABLE_ROSEN_BACKEND
    if (frameRateLinker_ == nullptr) {
        return;
    }
    decltype(frameRateData_) frameRateData{rate, animatorExpectedFrameRate, rateType};
    if (frameRateData_ != frameRateData) {
        frameRateData_ = frameRateData;
        frameRateLinker_->UpdateFrameRateRange({0, RANGE_MAX_REFRESHRATE, rate, rateType}, animatorExpectedFrameRate);
    }
#endif
}

void FormRenderWindow::InitOnVsyncCallback()
{
#ifdef ENABLE_ROSEN_BACKEND
    int64_t refreshPeriod = static_cast<int64_t>(ONE_SECOND_IN_NANO / GetDisplayRefreshRate());
    onVsyncCallback_ = [weakTask = taskExecutor_, id = id_, refreshPeriod](
                           int64_t timeStampNanos, int64_t frameCount, void* data) {
        auto taskExecutor = weakTask.Upgrade();
        CHECK_NULL_VOID(taskExecutor);
        auto onVsync = [id, timeStampNanos, frameCount, refreshPeriod] {
            int64_t ts = GetSysTimestamp();
            ContainerScope scope(id);
            // use container to get window can make sure the window is valid
            auto container = Container::Current();
            CHECK_NULL_VOID(container);
            bool isReportFrameEvent = false;
            auto containerHandler = container->GetContainerHandler();
            if (containerHandler) {
                isReportFrameEvent = containerHandler->GetHostConfig().isReportFrameEvent;
            }
            if (isReportFrameEvent) {
                FrameReport::GetInstance().ReportSchedEvent(
                    FrameSchedEvent::UI_SCB_WORKER_BEGIN, {});
            }
            auto window = container->GetWindow();
            CHECK_NULL_VOID(window);
            window->OnVsync(static_cast<uint64_t>(timeStampNanos), static_cast<uint64_t>(frameCount));
            auto pipeline = container->GetPipelineContext();
            if (pipeline) {
                pipeline->OnIdle(std::min(ts, timeStampNanos) + refreshPeriod);
            }
            if (isReportFrameEvent) {
                FrameReport::GetInstance().ReportSchedEvent(
                    FrameSchedEvent::UI_SCB_WORKER_END, {});
            }
        };

        ContainerScope scope(id);
        auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::JS);
        if (uiTaskRunner.IsRunOnCurrentThread()) {
            onVsync();
            return;
        }

        taskExecutor->PostTask(onVsync, TaskExecutor::TaskType::UI, "ArkUIFormRenderWindowVsync", PriorityType::VIP);
    };

    frameCallback_.userData_ = nullptr;
    frameCallback_.callbackWithId_ = onVsyncCallback_;
#endif
}

} // namespace OHOS::Ace
