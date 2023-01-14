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

#include "core/components_ng/render/adapter/form_render_window.h"

#include <memory>

#include "base/log/log.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/base/frame_node.h"
#include "transaction/rs_interfaces.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace {
constexpr float ONE_SECOND_IN_NANO = 1000000000.0f;

float GetDisplayRefreshRate()
{
    return 60.0f;
}
} // namespace

namespace OHOS::Ace {

FormRenderWindow::FormRenderWindow(RefPtr<TaskExecutor> taskExecutor, int32_t id)
    : taskExecutor_(taskExecutor), id_(id)
{
    LOGE("Kee FormRenderWindow::FormRenderWindow id_ = %{public}d", id_);

    ContainerScope scope(id);
    auto container = Container::Current();
    LOGE("Kee FormRenderWindow::FormRenderWindow container = %{public}p", AceType::RawPtr(container));
    if (receiver_ == nullptr) {
        auto& rsClient = Rosen::RSInterfaces::GetInstance();
        receiver_ = rsClient.CreateVSyncReceiver("Form");
        if (receiver_ == nullptr) {
            LOGE("Kee Create VSync receiver failed.");
            return;
        }
        receiver_->Init();
    }

    int64_t refreshPeriod = static_cast<int64_t>(ONE_SECOND_IN_NANO / GetDisplayRefreshRate());
    auto task = [weakTask = taskExecutor_, id = id_, refreshPeriod](int64_t timeStampNanos, void* data) {
        auto taskExecutor = weakTask.Upgrade();
        auto onVsync = [id, timeStampNanos, refreshPeriod] {
            LOGE("Kee FormRenderWindow onVsync");
            ContainerScope scope(id);
            // use container to get window can make sure the window is valid
            auto container = Container::Current();
            CHECK_NULL_VOID(container);
            LOGE("Kee FormRenderWindow onVsync container = %{public}p", AceType::RawPtr(container));
            auto window = container->GetWindow();
            CHECK_NULL_VOID(window);
            window->OnVsync(static_cast<uint64_t>(timeStampNanos), 0);
            auto pipeline = container->GetPipelineContext();
            if (pipeline) {
                pipeline->OnIdle(timeStampNanos + refreshPeriod);
            }
        };

        auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::JS); // Form Pipeline use only JS thread
        if (uiTaskRunner.IsRunOnCurrentThread()) {
            LOGE("Kee excute onVsync");
            onVsync();
            return;
        }
        uiTaskRunner.PostTask([callback = std::move(onVsync)]() { 
            LOGE("Kee excute onVsync JS");
            callback(); 
        });
    };


    frameCallback_.userData_ = nullptr,
    frameCallback_.callback_ = task,

    receiver_->RequestNextVSync(frameCallback_);

    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = {.SurfaceNodeName = surfaceNodeName};
    rsSurfaceNode_ = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, false);
    LOGE("Kee FormRenderWindow::FormRenderWindow surfaceNode ptr   = %{public}p", rsSurfaceNode_.get());
    LOGE("Kee FormRenderWindow::FormRenderWindow surfaceNode name  = %{public}s", rsSurfaceNode_->GetName().c_str());
    LOGE("Kee FormRenderWindow::FormRenderWindow surfaceNode id    = %{public}llu", rsSurfaceNode_->GetId());

    rsUIDirector_ = OHOS::Rosen::RSUIDirector::Create();
    rsUIDirector_->SetRSSurfaceNode(rsSurfaceNode_);
    // rsUIDirector_->SetCacheDir(AceApplicationInfo::GetInstance().GetDataFileDirPath());
    rsUIDirector_->Init();
    rsUIDirector_->SetUITaskRunner([weakTaskExecutor = taskExecutor_, id = id_](const std::function<void()>& task) {
        ContainerScope scope(id);
        auto taskExecutor = weakTaskExecutor.Upgrade();
        CHECK_NULL_VOID_NOLOG(taskExecutor);
        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
    });

    LOGE("Kee FormRenderWindow::FormRenderWindow");
}

void FormRenderWindow::RequestFrame()
{
    LOGE("Kee FormRenderWindow::RequestFrame");
    receiver_->RequestNextVSync(frameCallback_);
}

void FormRenderWindow::SetRootFrameNode(const RefPtr<NG::FrameNode>& root)
{
    LOGE("Kee FormRenderWindow set root frame node");
    CHECK_NULL_VOID(root);
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(root->GetRenderContext());
    CHECK_NULL_VOID(rosenRenderContext);
    LOGE("Kee FormRenderWindow::SetRootFrameNode eTS Card");
    if (rosenRenderContext->GetRSNode()) {
        rsUIDirector_->SetRoot(rosenRenderContext->GetRSNode()->GetId());
    }
}

void FormRenderWindow::SetFormRSSurfaceNode(void* surfaceNode)
{
    LOGE("Kee FormRenderWindow SetFormRSSurfaceNode");
    if (!surfaceNode) {
        LOGE("Kee FormRenderWindow SetFormRSSurfaceNode surfaceNode is null !!!");
        return;
    }
    std::shared_ptr<Rosen::RSSurfaceNode> rsSurfaceNode;
    rsSurfaceNode.reset(static_cast<Rosen::RSSurfaceNode*>(surfaceNode));
    // rsUIDirector_->SetRSSurfaceNode(rsSurfaceNode);
    // // rsUIDirector_->SetCacheDir(AceApplicationInfo::GetInstance().GetDataFileDirPath());
    // rsUIDirector_->Init();
    // rsUIDirector_->SetUITaskRunner([weakTaskExecutor = taskExecutor_, id = id_](const std::function<void()>& task) {
    //     ContainerScope scope(id);
    //     auto taskExecutor = weakTaskExecutor.Upgrade();
    //     CHECK_NULL_VOID_NOLOG(taskExecutor);
    //     taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
    // });
}

void FormRenderWindow::OnShow()
{
    Window::OnShow();
    rsUIDirector_->GoForeground();
}

void FormRenderWindow::OnHide()
{
    Window::OnHide();
    rsUIDirector_->GoBackground();
    rsUIDirector_->SendMessages();
}

void FormRenderWindow::FlushTasks()
{
    LOGE("FormRenderWindow flush tasks");
    rsUIDirector_->SendMessages();
}

} // namespace OHOS::Ace
