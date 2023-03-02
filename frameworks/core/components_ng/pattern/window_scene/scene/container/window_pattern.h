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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_PATTERN_H

#include <mutex>

#include "ui_window.h"

#include "core/common/window.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Rosen {
class RSUIDirector;
struct VsyncCallback;
class SessionStage;
class ISizeChangeListener;
enum class WindowSizeChangeReason : uint32_t;
}

namespace OHOS::Ace::NG {

class WindowPattern : public UIWindow, public Pattern, public Window,
                      public std::enable_shared_from_this<WindowPattern> {
    DECLARE_ACE_TYPE(WindowPattern, Pattern);

public:
    WindowPattern() = default;
    WindowPattern(const std::shared_ptr<AbilityRuntime::Context>& context,
        const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode);
    virtual ~WindowPattern() = default;

    void Init() override;
    void Destroy() override;

    void LoadContent(const std::string& contentUrl, NativeEngine* engine, NativeValue* storage,
        AbilityRuntime::Context* context = nullptr) override;

    void UpdateViewportConfig(const ViewportConfig& config, Rosen::WindowSizeChangeReason reason);

    std::shared_ptr<Rosen::RSSurfaceNode> GetSurfaceNode()
    {
        return surfaceNode_;
    }

    Rect GetCurrentWindowRect() const override
    {
        return GetWindowRect();
    }

    void SetTaskExecutor(const RefPtr<TaskExecutor>& taskExecutor) override
    {
        taskExecutor_ = taskExecutor;
    }

    void SetInstanceId(int32_t instanceId) override
    {
        instanceId_ = instanceId;
    }

    void SetRootRenderNode(const RefPtr<RenderNode>& root) override {}

    void SetRootFrameNode(const RefPtr<NG::FrameNode>& root) override;

    std::shared_ptr<Rosen::RSUIDirector> GetRSUIDirector() const override
    {
        return rsUIDirector_;
    }

    void RecordFrameTime(uint64_t timeStamp, const std::string& name) override;

    void FlushTasks() override;

    bool FlushCustomAnimation(uint64_t timeStamp) override;

    void OnShow() override;
    void OnHide() override;

    void SetDrawTextAsBitmap(bool useBitmap) override;

    float GetRefreshRate() const override;

    void RequestFrame() override;

    void RequestVsync(const std::shared_ptr<Rosen::VsyncCallback>& vsyncCallback);

    void RegisterSessionStageStateListener(const std::shared_ptr<Rosen::ISessionStageStateListener>& listener) override;
    void RegisterSizeChangeListener(const std::shared_ptr<Rosen::ISizeChangeListener>& listener);

    void Connect()  override;
    void Foreground()  override;
    void Background() override;
    void Disconnect() override;

protected:
    std::shared_ptr<Rosen::RSSurfaceNode> surfaceNode_;

    std::unique_ptr<UIContent> uiContent_;
    std::shared_ptr<AbilityRuntime::Context> context_;

    sptr<Rosen::SessionStage> sessionStage_;

private:
    std::recursive_mutex mutex_;

    WeakPtr<TaskExecutor> taskExecutor_;
    int32_t instanceId_ = 0;
    std::shared_ptr<Rosen::RSUIDirector> rsUIDirector_;
    std::shared_ptr<Rosen::VsyncCallback> vsyncCallback_;

    ACE_DISALLOW_COPY_AND_MOVE(WindowPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_PATTERN_H
