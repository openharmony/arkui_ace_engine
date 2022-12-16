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

#include "session_stage.h"

#include "core/components_ng/pattern/pattern.h"
#include "interfaces/inner_api/ace/ui_content.h"

class NativeEngine;
class NativeValue;

namespace OHOS::Rosen {
struct VsyncCallback;
class RSSurfaceNode;
enum class WSError;
}

namespace OHOS::AppExecFwk {
class Ability;
}

namespace OHOS::AbilityRuntime {
class Context;
}

namespace OHOS::Ace::NG {

class WindowPattern : public Pattern {
    DECLARE_ACE_TYPE(WindowPattern, Pattern);

public:
    WindowPattern(
        const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode,
        const std::shared_ptr<AbilityRuntime::Context>& runtimeContext);
    ~WindowPattern() override = default;

    Rosen::WSError SetUIContent(const std::string& contentInfo,
        NativeEngine* engine, NativeValue* storage, bool isDistributed = false, AppExecFwk::Ability* ability = nullptr);

    void RequestVsync(const std::shared_ptr<Rosen::VsyncCallback>& vsyncCallback);

    std::shared_ptr<Rosen::RSSurfaceNode> GetSurfaceNode()
    {
        return surfaceNode_;
    }

    std::shared_ptr<Rosen::SessionStage> GetSessionStage()
    {
        return sessionStage_;
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

    Rect GetRect() const
    {
        return Rect(0, 0, 720, 1280);
    }

    bool IsDecorEnable() const
    {
        return false;
    }

    bool IsFocused() const
    {
        return true;
    }

protected:
    // for lifecycle
    std::shared_ptr<Rosen::RSSurfaceNode> surfaceNode_;
    std::shared_ptr<Rosen::SessionStage> sessionStage_;

    // window properties
    std::string windowName_ = "example";
    uint32_t windowId_ = 100;
    uint32_t windowFlags_;

    std::unique_ptr<UIContent> uiContent_;
    std::shared_ptr<AbilityRuntime::Context> runtimeContext_;

    std::recursive_mutex mutex_;

    ACE_DISALLOW_COPY_AND_MOVE(WindowPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_PATTERN_H
