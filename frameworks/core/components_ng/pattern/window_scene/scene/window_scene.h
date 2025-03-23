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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_SCENE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_SCENE_H

#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"

namespace OHOS::Ace::NG {
class WindowScene : public WindowPattern {
    DECLARE_ACE_TYPE(WindowScene, WindowPattern);

public:
    explicit WindowScene(const sptr<Rosen::Session>& session);
    ~WindowScene() override;
    uint32_t GetWindowPatternType() const override;

protected:
    std::optional<RenderContext::ContextParam> GetContextParam() const override
    {
        return RenderContext::ContextParam {
            .type = RenderContext::ContextType::EXTERNAL,
            .surfaceName = std::nullopt};
    }

    bool HasStartingPage() override
    {
        return true;
    }

    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnMountToParentDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void OnActivation() override;
    void OnConnect() override;
    void OnDisconnect() override;
    void OnLayoutFinished() override;
    void OnDrawingCompleted() override;
    void OnRemoveBlank() override;
    void OnAddSnapshot() override;
    void OnRemoveSnapshot() override;
    void OnAppRemoveStartingWindow() override;

private:
    std::shared_ptr<Rosen::RSSurfaceNode> CreateLeashWindowNode();
    void BufferAvailableCallback();
    void BufferAvailableCallbackForBlank(bool fromMainThread);
    void BufferAvailableCallbackForSnapshot();
    void DisposeSnapshotAndBlankWindow();
    void OnBoundsChanged(const Rosen::Vector4f& bounds);
    bool IsWindowSizeEqual();
    void RegisterResponseRegionCallback();
    void RegisterFocusCallback();
    void CleanBlankWindow();
    void SetSubWindowBufferAvailableCallback(const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode);
    void SetOpacityAnimation(RefPtr<FrameNode>& window);
    void PostDelayTask();
    void PostDelayTaskForSnapshot();
    void CleanSnapshot();

    bool destroyed_ = false;
    OHOS::Rosen::WindowMode initWindowMode_ = OHOS::Rosen::WindowMode::WINDOW_MODE_UNDEFINED;
    CancelableCallback<void()> deleteWindowTask_;
    CancelableCallback<void()> removeStartingWindowTask_;
    CancelableCallback<void()> removeSnapshotWindowTask_;

    ACE_DISALLOW_COPY_AND_MOVE(WindowScene);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_SCENE_H
