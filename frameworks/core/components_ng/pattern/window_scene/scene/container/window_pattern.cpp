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

#include "core/components_ng/pattern/window_scene/scene/container/window_pattern.h"

#include "ability_context.h"

#include "base/utils/time_util.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace {
constexpr int32_t IDLE_TASK_DELAY_MILLISECOND = 51;
constexpr float ONE_SECOND_IN_NANO = 1000000000.0f;

float GetDisplayRefreshRate()
{
#ifdef PREVIEW
    return 30.0f;
#else
    return 60.0f;
#endif
}
} // namespace

namespace OHOS::Ace::NG {
namespace {
class SizeChangeListener : public Rosen::ISizeChangeListener {
public:
    explicit SizeChangeListener(const std::weak_ptr<WindowPattern>& weakWindow) : weakWindow_(weakWindow) {}
    virtual ~SizeChangeListener() = default;

    void OnSizeChange(const Rosen::WSRect& rect, Rosen::SizeChangeReason reason) override
    {
        LOGI("OnSizeChange window rect: [%{public}d, %{public}d, %{public}u, %{public}u]",
            rect.posX_, rect.posY_, rect.width_, rect.height_);
        auto window = weakWindow_.lock();
        CHECK_NULL_VOID(window);
        auto windowRect = Rect(rect.posX_, rect.posY_, rect.width_, rect.height_);
        window->SetWindowRect(windowRect);
        window->UpdateViewportConfig(windowRect, SESSION_TO_WINDOW_MAP.at(reason));
    }

private:
    const std::map<Rosen::SizeChangeReason, Rosen::WindowSizeChangeReason> SESSION_TO_WINDOW_MAP {
        { Rosen::SizeChangeReason::SHOW, Rosen::WindowSizeChangeReason::UNDEFINED },
        { Rosen::SizeChangeReason::HIDE, Rosen::WindowSizeChangeReason::HIDE },
        { Rosen::SizeChangeReason::MAXIMIZE, Rosen::WindowSizeChangeReason::MAXIMIZE },
        { Rosen::SizeChangeReason::RECOVER, Rosen::WindowSizeChangeReason::RECOVER },
        { Rosen::SizeChangeReason::ROTATION, Rosen::WindowSizeChangeReason::ROTATION },
    };
    std::weak_ptr<WindowPattern> weakWindow_;
};

class InputEventListener : public Rosen::IInputEventListener {
public:
    explicit InputEventListener(int32_t instanceId) : instanceId_(instanceId) {}
    virtual ~InputEventListener() = default;

    void OnPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) override
    {
        ContainerScope scope(instanceId_);
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto window = static_cast<WindowPattern*>(container->GetWindow());
        CHECK_NULL_VOID(window);
        window->ProcessPointerEvent(pointerEvent);
    }

    void OnKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent) override
    {
        ContainerScope scope(instanceId_);
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto window = static_cast<WindowPattern*>(container->GetWindow());
        CHECK_NULL_VOID(window);
        window->ProcessKeyEvent(keyEvent);
    }

    void OnAxisEvent(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent) override
    {
        ContainerScope scope(instanceId_);
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto window = static_cast<WindowPattern*>(container->GetWindow());
        CHECK_NULL_VOID(window);
        window->ProcessAxisEvent(axisEvent);
    }

private:
    int32_t instanceId_ = -1;
};
} // namespace

WindowPattern::WindowPattern(const std::shared_ptr<AbilityRuntime::Context>& context)
    : context_(context)
{
    ACE_DCHECK(context_);

    auto name = context_->GetBundleName();
    auto pos = name.find_last_of('.');
    name = (pos == std::string::npos) ? name : name.substr(pos + 1); // skip '.'
    windowName_ = name + std::to_string(windowId_);
    surfaceNode_ = CreateSurfaceNode(windowName_);
}

void WindowPattern::Init()
{
    int64_t refreshPeriod = static_cast<int64_t>(ONE_SECOND_IN_NANO / GetDisplayRefreshRate());
    vsyncCallback_ = std::make_shared<Rosen::VsyncCallback>();
    vsyncCallback_->onCallback = [weakTask = taskExecutor_, instanceId = instanceId_, refreshPeriod](
                                     int64_t nanoTimestamp) {
        auto onVsync = [instanceId, nanoTimestamp, refreshPeriod] {
            ContainerScope scope(instanceId);
            // use container to get window can make sure the window is valid
            auto container = Container::Current();
            CHECK_NULL_VOID(container);
            auto window = container->GetWindow();
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
    rsUIDirector_->SetUITaskRunner(
        [taskExecutor = taskExecutor_.Upgrade(), instanceId = instanceId_](const std::function<void()>& task) {
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

std::shared_ptr<Rosen::RSSurfaceNode> WindowPattern::CreateSurfaceNode(const std::string& name)
{
    struct Rosen::RSSurfaceNodeConfig rsSurfaceNodeConfig;
    rsSurfaceNodeConfig.SurfaceNodeName = name;
    return Rosen::RSSurfaceNode::Create(rsSurfaceNodeConfig);
}

void WindowPattern::LoadContent(
    const std::string& contentUrl, NativeEngine* engine, NativeValue* storage, AbilityRuntime::Context* context)
{
    uiContent_ = UIContent::Create(context_.get(), engine);
    CHECK_NULL_VOID(uiContent_);
    uiContent_->Initialize(shared_from_this(), contentUrl, storage);

    uiContent_->Foreground();
    UpdateViewportConfig(GetWindowRect(), Rosen::WindowSizeChangeReason::UNDEFINED);

    auto inputListener = std::make_shared<InputEventListener>(instanceId_);
    RegisterInputEventListener(inputListener);
}

void WindowPattern::UpdateViewportConfig(const Rect& rect, Rosen::WindowSizeChangeReason reason)
{
    ViewportConfig config;
    config.SetPosition(rect.Left(), rect.Top());
    config.SetSize(rect.Width(), rect.Height());
    constexpr float density = 1.5; // to get display density
    config.SetDensity(density);
    CHECK_NULL_VOID(uiContent_);
    uiContent_->UpdateViewportConfig(config, reason);
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
    CHECK_NULL_VOID_NOLOG(onShow_);
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID_NOLOG(!isRequestVsync_);

    LOGD("request next vsync");
    RequestVsync(vsyncCallback_);
    lastRequestVsyncTime_ = GetSysTimestamp();
    isRequestVsync_ = true;

    auto taskExecutor = taskExecutor_.Upgrade();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(
        [id = instanceId_]() {
            ContainerScope scope(id);
            auto container = Container::Current();
            CHECK_NULL_VOID(container);
            auto pipeline = container->GetPipelineContext();
            CHECK_NULL_VOID(pipeline);
            pipeline->OnIdle(0);
        },
        TaskExecutor::TaskType::UI, IDLE_TASK_DELAY_MILLISECOND);
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

void WindowPattern::SetDrawTextAsBitmap(bool useBitmap)
{
    Rosen::RSSystemProperties::SetDrawTextAsBitmap(useBitmap);
}

float WindowPattern::GetRefreshRate() const
{
    return GetDisplayRefreshRate();
}

void WindowPattern::RegisterSessionStageStateListener(
    const std::shared_ptr<Rosen::ISessionStageStateListener>& listener)
{
    CHECK_NULL_VOID(sessionStage_);
    sessionStage_->RegisterSessionStageStateListener(listener);
}

void WindowPattern::RegisterSizeChangeListener(const std::shared_ptr<Rosen::ISizeChangeListener>& listener)
{
    CHECK_NULL_VOID(sessionStage_);
    sessionStage_->RegisterSizeChangeListener(listener);
}

void WindowPattern::RegisterInputEventListener(const std::shared_ptr<Rosen::IInputEventListener>& listener)
{
    CHECK_NULL_VOID(sessionStage_);
    sessionStage_->RegisterInputEventListener(listener);
}

void WindowPattern::ProcessPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(uiContent_);
    uiContent_->ProcessPointerEvent(pointerEvent);
}

void WindowPattern::ProcessKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_VOID(uiContent_);
    uiContent_->ProcessKeyEvent(keyEvent);
}

void WindowPattern::ProcessAxisEvent(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent)
{
    CHECK_NULL_VOID(uiContent_);
    uiContent_->ProcessAxisEvent(axisEvent);
}

void WindowPattern::Connect()
{
    auto sizeChangeListener = std::make_shared<SizeChangeListener>(weak_from_this());
    RegisterSizeChangeListener(sizeChangeListener);

    CHECK_NULL_VOID(sessionStage_);
    sessionStage_->Connect(surfaceNode_);
}

void WindowPattern::Foreground()
{
    if (uiContent_) {
        uiContent_->Foreground();
    }
    CHECK_NULL_VOID(sessionStage_);
    sessionStage_->Foreground();
}

void WindowPattern::Background()
{
    if (uiContent_) {
        uiContent_->Background();
    }
    CHECK_NULL_VOID(sessionStage_);
    sessionStage_->Background();
}

void WindowPattern::Disconnect()
{
    if (uiContent_) {
        uiContent_->Destroy();
    }
    CHECK_NULL_VOID(sessionStage_);
    sessionStage_->Disconnect();
}

void WindowPattern::OnNewWant(const AAFwk::Want& want)
{
    if (uiContent_) {
        uiContent_->OnNewWant(want);
    }
}
} // namespace OHOS::Ace::NG
