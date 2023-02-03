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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_PATTERN_H

#include <mutex>

#include "session/scene/container/include/session_stage.h"
#include "ui_content.h"
#include "ui_window.h"

#include "base/thread/task_executor.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Rosen {
class RSSurfaceNode;
class RSUIDirector;
struct VsyncCallback;
}

namespace OHOS::Ace::NG {

class WindowPattern : public UIWindow, public Pattern {
    DECLARE_ACE_TYPE(WindowPattern, Pattern);

public:
    WindowPattern(const std::shared_ptr<AbilityRuntime::Context>& context,
        const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode);
    ~WindowPattern() override = default;

    void Init();
    void Destroy();

    void InitUIContent(const std::string& contentInfo, NativeEngine* engine, NativeValue* storage) override;

    void UpdateViewportConfig(const ViewportConfig& config, Rosen::WindowSizeChangeReason reason);

    std::shared_ptr<Rosen::RSSurfaceNode> GetSurfaceNode()
    {
        return surfaceNode_;
    }

    uint32_t GetWindowId() const
    {
        return windowId_;
    }

    const std::string& GetWindowName() const
    {
        return windowName_;
    }

    uint32_t GetWindowFlags() const
    {
        return windowFlags_;
    }

    void SetWindowRect(Rect rect)
    {
        windowRect_ = rect;
    }

    Rect GetWindowRect() const
    {
        return windowRect_;
    }

    bool IsDecorEnable() const
    {
        return false;
    }

    bool IsFocused() const
    {
        return true;
    }

    void SetTaskExecutor(const RefPtr<TaskExecutor>& taskExecutor)
    {
        taskExecutor_ = taskExecutor;
    }

    void SetInstanceId(int32_t instanceId)
    {
        instanceId_ = instanceId;
    }

    using AceVsyncCallback = std::function<void(uint64_t, uint32_t)>;

    void SetVsyncCallback(AceVsyncCallback&& callback)
    {
        callbacks_.push_back(std::move(callback));
    }

    virtual void SetRootFrameNode(const RefPtr<NG::FrameNode>& root);

    std::shared_ptr<Rosen::RSUIDirector> GetRSUIDirector() const
    {
        return rsUIDirector_;
    }

    void RecordFrameTime(uint64_t timeStamp, const std::string& name);

    void FlushTasks();

    bool FlushCustomAnimation(uint64_t timeStamp);

    void OnShow();
    void OnHide();

    void RequestFrame();

    void RequestVsync(const std::shared_ptr<Rosen::VsyncCallback>& vsyncCallback);

    void OnVsync(uint64_t nanoTimestamp, uint32_t frameCount);

    // for lifecycle
    void RegisterSessionStageStateListener(const std::shared_ptr<Rosen::ISessionStageStateListener>& listener) override
    {
        CHECK_NULL_VOID(sessionStage_);
        sessionStage_->RegisterSessionStageStateListener(listener);
    }

    void RegisterSessionChangeListener(const std::shared_ptr<Rosen::ISessionChangeListener>& listener)
    {
        CHECK_NULL_VOID(sessionStage_);
        sessionStage_->RegisterSessionChangeListener(listener);
    }

    void Connect()  override;
    void Foreground()  override;
    void Background() override;
    void Disconnect() override;

protected:
    std::shared_ptr<Rosen::RSSurfaceNode> surfaceNode_;

    // for lifecycle
    sptr<Rosen::SessionStage> sessionStage_;

    // window properties
    std::string windowName_ = "example";
    uint32_t windowId_ = 100;
    uint32_t windowFlags_;
    Rect windowRect_;

    std::recursive_mutex mutex_;

private:
    std::unique_ptr<UIContent> uiContent_;
    std::shared_ptr<AbilityRuntime::Context> context_;

    bool isRequestVsync_ = false;
    bool onShow_ = true;
    std::list<AceVsyncCallback> callbacks_;

    WeakPtr<TaskExecutor> taskExecutor_;
    int32_t instanceId_ = 0;
    std::shared_ptr<Rosen::RSUIDirector> rsUIDirector_;
    std::shared_ptr<Rosen::VsyncCallback> vsyncCallback_;

    ACE_DISALLOW_COPY_AND_MOVE(WindowPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_PATTERN_H
