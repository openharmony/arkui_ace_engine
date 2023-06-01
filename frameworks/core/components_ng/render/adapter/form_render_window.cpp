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

#include <memory>

#include "base/log/log.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/base/frame_node.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "core/components_ng/render/adapter/rosen_render_context.h"
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
std::mutex FormRenderWindow::globalMutex_;
#endif

FormRenderWindow::FormRenderWindow(RefPtr<TaskExecutor> taskExecutor, int32_t id)
    : taskExecutor_(taskExecutor), id_(id)
{
#ifdef ENABLE_ROSEN_BACKEND
    ContainerScope scope(id);
    auto container = Container::Current();
    if (receiver_ == nullptr) {
        auto& rsClient = Rosen::RSInterfaces::GetInstance();
        receiver_ = rsClient.CreateVSyncReceiver("Form");
        if (receiver_ == nullptr) {
            LOGE("Form Create VSync receiver failed.");
            return;
        }
        receiver_->Init();
    }

    int64_t refreshPeriod = static_cast<int64_t>(ONE_SECOND_IN_NANO / GetDisplayRefreshRate());
    onVsyncCallback_ = [weakTask = taskExecutor_, id = id_, refreshPeriod](int64_t timeStampNanos, void* data) {
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
            if (pipeline) {
                pipeline->OnIdle(timeStampNanos + refreshPeriod);
            }
        };

        auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::JS);
        if (uiTaskRunner.IsRunOnCurrentThread()) {
            onVsync();
            return;
        }

        uiTaskRunner.PostTask([callback = std::move(onVsync)]() {
            callback();
        });
    };

    frameCallback_.userData_ = nullptr;
    frameCallback_.callback_ = onVsyncCallback_;

    receiver_->RequestNextVSync(frameCallback_);

    rsUIDirector_ = OHOS::Rosen::RSUIDirector::Create();
    {
        std::lock_guard<std::mutex> lock(globalMutex_);
        rsUIDirector_->Init(); // Func Init Thread unsafe.
    }

    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = {.SurfaceNodeName = surfaceNodeName};
    rsSurfaceNode_ = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    rsUIDirector_->SetRSSurfaceNode(rsSurfaceNode_);

    rsUIDirector_->SetUITaskRunner([taskExecutor, id = id_](const std::function<void()>& task) {
        ContainerScope scope(id);
        CHECK_NULL_VOID_NOLOG(taskExecutor);
        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
    });
#else
    taskExecutor_ = nullptr;
    id_ = 0;
#endif
}

void FormRenderWindow::RequestFrame()
{
#ifdef ENABLE_ROSEN_BACKEND
    receiver_->RequestNextVSync(frameCallback_);
#endif
}

void FormRenderWindow::Destroy()
{
    LOG_DESTROY();
#ifdef ENABLE_ROSEN_BACKEND
    frameCallback_.userData_ = nullptr;
    frameCallback_.callback_ = nullptr;
    rsUIDirector_->Destroy();
    rsUIDirector_.reset();
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
        rsUIDirector_->SetRoot(rosenRenderContext->GetRSNode()->GetId());
    }
    rsUIDirector_->SendMessages();
#endif
}

void FormRenderWindow::OnShow()
{
#ifdef ENABLE_ROSEN_BACKEND
    Window::OnShow();
    rsUIDirector_->GoForeground();
#endif
}

void FormRenderWindow::OnHide()
{
#ifdef ENABLE_ROSEN_BACKEND
    Window::OnHide();
    rsUIDirector_->GoBackground();
    rsUIDirector_->SendMessages();
#endif
}

void FormRenderWindow::FlushTasks()
{
#ifdef ENABLE_ROSEN_BACKEND
    rsUIDirector_->SendMessages();
#endif
}
} // namespace OHOS::Ace
