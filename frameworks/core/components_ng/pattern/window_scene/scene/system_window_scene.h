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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SYSTEM_WINDOW_SCENE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SYSTEM_WINDOW_SCENE_H

#include "common/rs_vector4.h"
#include "session/host/include/session.h"

#include "core/common/container.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"

namespace OHOS::Ace::NG {
class SystemWindowScene : public StackPattern, public FocusView {
    DECLARE_ACE_TYPE(SystemWindowScene, StackPattern, FocusView);

public:
    explicit SystemWindowScene(const sptr<Rosen::Session>& session);
    ~SystemWindowScene() override = default;

    std::optional<RenderContext::ContextParam> GetContextParam() const override
    {
        return RenderContext::ContextParam {
            .type = RenderContext::ContextType::EXTERNAL,
            .surfaceName = std::nullopt};
    }

    sptr<Rosen::Session> GetSession();

    void OnVisibleChange(bool visible) override;

    std::list<int32_t> GetRouteOfFirstScope() override
    {
        return { 0 };
    }

    void LostViewFocus() override;

    void RegisterVisibleChangeCallback(int32_t nodeId, const std::function<void(bool)>& callback);
    void UnRegisterVisibleChangeCallback(int32_t nodeId);
    void HandleVisibleChangeCallback(bool visible);

    void CreateOverlayManager(bool isShow, const RefPtr<FrameNode>& target)
    {
        if (!overlayManager_ && isShow) {
            overlayManager_ = MakeRefPtr<OverlayManager>(target);
            overlayManager_->SetIsAttachToCustomNode(true);
        }
    }

    const RefPtr<OverlayManager>& GetOverlayManager()
    {
        return overlayManager_;
    }

    void DeleteOverlayManager()
    {
        overlayManager_.Reset();
    }
    uint32_t GetWindowPatternType() const override;

protected:
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    std::function<void(const Rosen::Vector4f&)> boundsChangedCallback_;
    sptr<Rosen::Session> session_;

private:
    void OnAttachToMainTree() override;
    void OnDetachFromMainTree() override;

    void OnBoundsChanged(const Rosen::Vector4f& bounds);
    void RegisterFocusCallback();
    void RegisterEventCallback();
    void RegisterResponseRegionCallback();
    void PostCheckContextTransparentTask();
    void PostFaultInjectTask();
    void SetWindowScenePosition();
    void InsertSurfaceNodeId(uint64_t nodeId);
    void ClearSurfaceNodeId(uint64_t nodeId);

    int32_t instanceId_ = Container::CurrentId();

    CancelableCallback<void()> checkContextTransparentTask_;
    RefPtr<OverlayManager> overlayManager_;
    std::map<int32_t, std::function<void(bool)>> visibleChangeCallbackMap_;

    ACE_DISALLOW_COPY_AND_MOVE(SystemWindowScene);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SYSTEM_WINDOW_SCENE_H
