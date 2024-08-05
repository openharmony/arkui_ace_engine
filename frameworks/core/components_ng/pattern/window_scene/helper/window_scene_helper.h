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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_SCENE_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_SCENE_HELPER_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Rosen {
class Session;
}
namespace OHOS::MMI {
class KeyEvent;
class PointerEvent;
}

namespace OHOS::Ace::NG {
enum class WindowPatternType : uint32_t {
    DEFAULT = 0,
    SCREEN_SCENE,
    TRANSFORM_SCENE, // no window session before transform scene
    WINDOW_SCENE, // app window, sub window
    SYSTEM_WINDOW_SCENE, // SCB system scene
    PANEL_SCENE,
    INPUT_SCENE,
};

class WindowSceneHelper : public AceType {
    DECLARE_ACE_TYPE(WindowSceneHelper, AceType);

public:
    WindowSceneHelper() = default;
    ~WindowSceneHelper() override = default;

    static RefPtr<UINode> FindWindowScene(const RefPtr<FrameNode>& targetNode);

    static bool IsWindowScene(const RefPtr<FrameNode>& focusedFrameNode);

    static int32_t GetFocusSystemWindowId(const RefPtr<FrameNode>& focusedFrameNode);

    static int32_t GetWindowIdForWindowScene(const RefPtr<FrameNode>& windowSceneNode);

    static bool IsFocusWindowSceneCloseKeyboard(const RefPtr<FrameNode>& focusedFrameNode);

    static void IsWindowSceneCloseKeyboard(const RefPtr<FrameNode>& frameNode);

    static void IsCloseKeyboard(const RefPtr<FrameNode>& frameNode);

    static void InjectPointerEvent(const std::string& targetNodeName,
        const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent);

    static void InjectPointerEvent(const RefPtr<FrameNode>& node,
        const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent);

    static bool InjectKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme = false);

    static bool IsWindowPattern(const RefPtr<FrameNode>& node);

    static bool HasWindowSession(const RefPtr<FrameNode>& node);

    static bool IsTransformScene(uint32_t type);

    static bool IsSystemWindowScene(uint32_t type);

    static bool IsPanelScene(uint32_t type);

    static bool IsScreenScene(uint32_t type);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WINDOW_SCENE_HELPER_H
