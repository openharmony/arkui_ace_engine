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
    ContainerScope scope(id);
    auto container = Container::Current();
    LOGI("FormRenderWindow::FormRenderWindow container = %{public}p", AceType::RawPtr(container));
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

    frameCallback_.userData_ = nullptr,
    frameCallback_.callback_ = onVsyncCallback_,

    receiver_->RequestNextVSync(frameCallback_);

    rsUIDirector_ = OHOS::Rosen::RSUIDirector::Create();
    rsUIDirector_->Init();

    std::string surfaceNodeName = "ArkTSCardNode";
    struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = {.SurfaceNodeName = surfaceNodeName};
    rsSurfaceNode_ = OHOS::Rosen::RSSurfaceNode::Create(surfaceNodeConfig, true);
    rsUIDirector_->SetRSSurfaceNode(rsSurfaceNode_);

    rsUIDirector_->SetUITaskRunner([weakTaskExecutor = taskExecutor_, id = id_](const std::function<void()>& task) {
        ContainerScope scope(id);
        auto taskExecutor = weakTaskExecutor.Upgrade();
        CHECK_NULL_VOID_NOLOG(taskExecutor);
        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
    });
}

void FormRenderWindow::RequestFrame()
{
    receiver_->RequestNextVSync(frameCallback_);
}

void FormRenderWindow::SetRootFrameNode(const RefPtr<NG::FrameNode>& root)
{
    CHECK_NULL_VOID(root);
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
}

void FormRenderWindow::SetFormRSSurfaceNode(void* surfaceNode)
{
    if (!surfaceNode) {
        LOGE("FormRenderWindow SetFormRSSurfaceNode surfaceNode is null !!!");
        return;
    }
    std::shared_ptr<Rosen::RSSurfaceNode> rsSurfaceNode;
    rsSurfaceNode.reset(static_cast<Rosen::RSSurfaceNode*>(surfaceNode));
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
    rsUIDirector_->SendMessages();
}
} // namespace OHOS::Ace
