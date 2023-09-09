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

#include "core/components_ng/render/adapter/flutter_window.h"

#include "ace_shell/shell/common/window_manager.h"
#include "ace_shell/ui/compositing/scene.h"

#include "base/thread/task_executor.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/adapter/flutter_render_context.h"

namespace OHOS::Ace::NG {

FlutterWindow::FlutterWindow(RefPtr<TaskExecutor> taskExecutor, int32_t id) : taskExecutor_(taskExecutor), id_(id) {}

void FlutterWindow::RequestFrame()
{
    CHECK_NULL_VOID(onShow_);

    CHECK_RUN_ON(UI);
    auto window = flutter::ace::WindowManager::GetWindow(id_);
    if (!isRequestVsync_ && window != nullptr) {
        LOGD("request next vsync");
        window->ScheduleFrame(true);
        if (!window->HasBeginFrameCallback()) {
            window->SetBeginFrameCallback([id = id_](uint64_t nanoTimestamp) {
                // use container to get window can make sure the window is valid
                ContainerScope scope(id);
                auto container = Container::Current();
                CHECK_NULL_VOID(container);
                auto window = container->GetWindow();
                CHECK_NULL_VOID(window);
                window->OnVsync(nanoTimestamp, 0);
            });
        }
        isRequestVsync_ = true;
    }
}

void FlutterWindow::Destroy()
{
    LOG_DESTROY();
    auto window = flutter::ace::WindowManager::GetWindow(id_);
    if (window != nullptr) {
        window->SetBeginFrameCallback(nullptr);
    }
    rootNode_.Reset();
    callbacks_.clear();
}

void FlutterWindow::SetRootFrameNode(const RefPtr<NG::FrameNode>& root)
{
    LOGI("FlutterWindow set root frame node");
    CHECK_NULL_VOID(root);
    rootNode_ = root;
}

void FlutterWindow::RecordFrameTime(uint64_t timeStamp, const std::string& name)
{
    LOGD("FlutterWindow RecordFrameTime");
}

void FlutterWindow::FlushTasks()
{
    CHECK_RUN_ON(UI);
    LOGD("FlutterWindow flush tasks");
    CHECK_NULL_VOID(rootNode_);
    const auto& context = AceType::DynamicCast<FlutterRenderContext>(rootNode_->GetRenderContext());
    CHECK_NULL_VOID(context);
    const auto& node = context->GetNode();
    CHECK_NULL_VOID(node);
    auto rootLayer = node->BuildLayer(id_);
    const auto& rect = node->FrameRect();
    auto window = flutter::ace::WindowManager::GetWindow(id_);
    CHECK_NULL_VOID(window);
    LOGD("FlutterWindow Scene create rect:%{public}s", rect.ToString().c_str());
    auto scene = flutter::ace::Scene::create(
        std::move(rootLayer), SkISize::Make(rect.Width(), rect.Height()), density_, 0, false, false);
    auto client = window->client();
    if (scene && client) {
        LOGD("FlutterWindow render layertree");
        client->Render(scene->takeLayerTree());
    }
}

} // namespace OHOS::Ace::NG
