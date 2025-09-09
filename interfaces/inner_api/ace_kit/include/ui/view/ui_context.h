/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_UI_CONTEXT_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_UI_CONTEXT_H

#include <functional>

#include "ui/base/ace_type.h"
#include "ui/base/geometry/ng/offset_t.h"
#include "ui/base/utils/system_param.h"
#include "ui/view/frame_node.h"
#include "ui/view/overlay/overlay_manager.h"

namespace OHOS {
class IRemoteObject;
template<typename T>
class sptr;
} // namespace OHOS
namespace OHOS::Ace {
class DisplayInfo;
enum class FoldStatus : uint32_t;
enum class WindowMode : uint32_t;
enum class WindowSizeChangeReason : uint32_t;
}; // namespace OHOS::Ace

namespace OHOS::Ace::Kit {

using Task = std::function<void()>;
using ArkUIObjectLifecycleCallback = std::function<void(void*)>;
class OverlayManager;

class ACE_FORCE_EXPORT UIContext : public AceType {
    DECLARE_ACE_TYPE(UIContext, AceType);
public:
    static RefPtr<UIContext> Current();

    // task schedule
    virtual void RunScopeUITaskSync(Task&& task, const std::string& name) = 0;
    virtual void RunScopeUITask(Task&& task, const std::string& name) = 0;
    virtual void RunScopeUIDelayedTask(Task&& task, const std::string& name, uint32_t delayTime) = 0;

    // page operation
    virtual void OnBackPressed() = 0;

    // ui infos
    virtual ColorMode GetLocalColorMode() = 0;
    virtual ColorMode GetColorMode() = 0;
    virtual float GetFontScale() = 0;

    // overlay manager
    virtual RefPtr<OverlayManager> GetOverlayManager() = 0;

    // pipeline tasks
    virtual void AddAfterLayoutTask(Task&& task, bool isFlushInImplicitAnimationTask = false) = 0;
    virtual void RequestFrame() = 0;

    // API version
    virtual int32_t GetApiTargetVersion() = 0;
    virtual bool GreatOrEqualTargetAPIVersion(int32_t version) = 0;
    virtual int32_t GetContainerModalTitleHeight() = 0;
    virtual int32_t GetContainerModalButtonsWidth() = 0;
    virtual NG::OffsetF GetContainerModalButtonsOffset() = 0;
    virtual void RegisterArkUIObjectLifecycleCallback(ArkUIObjectLifecycleCallback&& callback) = 0;
    virtual void UnregisterArkUIObjectLifecycleCallback() = 0;

    virtual sptr<IRemoteObject> GetToken() = 0;

    // Display Info
    virtual RefPtr<DisplayInfo> GetDisplayInfo() = 0;
    virtual WindowMode GetWindowMode() = 0;
    virtual bool GetIsMidScene() = 0;
    virtual bool IsAccessibilityEnabled() = 0;

    virtual int32_t RegisterSurfaceChangedCallback(
        std::function<void(int32_t, int32_t, int32_t, int32_t, WindowSizeChangeReason)>&& callback) = 0;
    virtual void UnregisterSurfaceChangedCallback(int32_t callbackId) = 0;
    virtual int32_t RegisterFoldStatusChangedCallback(std::function<void(FoldStatus)>&& callback) = 0;
    virtual void UnRegisterFoldStatusChangedCallback(int32_t callbackId) = 0;
    virtual int32_t RegisterRotationEndCallback(std::function<void()>&& callback) = 0;
    virtual void UnregisterRotationEndCallback(int32_t callbackId) = 0;
    virtual void AddWindowSizeChangeCallback(int32_t nodeId) = 0;
};

}
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_UI_CONTEXT_H
