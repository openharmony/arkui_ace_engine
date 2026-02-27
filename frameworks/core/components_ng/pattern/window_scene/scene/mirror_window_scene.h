/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MIRROR_WINDOW_SCENE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MIRROR_WINDOW_SCENE_H

#include "session/host/include/session.h"

#include "core/common/container.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"

namespace OHOS::Ace::NG {
class MirrorWindowScene : public WindowPattern {
    DECLARE_ACE_TYPE(MirrorWindowScene, WindowPattern);

public:
    explicit MirrorWindowScene(const sptr<Rosen::Session>& session);
    ~MirrorWindowScene() override = default;

    std::optional<RenderContext::ContextParam> GetContextParam() const override
    {
        return RenderContext::ContextParam {
            .type = RenderContext::ContextType::EXTERNAL,
            .surfaceName = std::nullopt};
    }

protected:
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    bool HasStartingPage() override { return false; }

private:
    std::shared_ptr<Rosen::RSSurfaceNode> mirrorSurfaceNode_ = nullptr;

    void OnAttachToMainTree() override;
    void OnDetachFromMainTree() override;
    void AddSnapshot();

    ACE_DISALLOW_COPY_AND_MOVE(MirrorWindowScene);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MIRROR_WINDOW_SCENE_H