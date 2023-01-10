/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_CONTENT_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_CONTENT_H

#include <map>
#include <memory>
#include <string>

#include "viewport_config.h"
#include "foundation/multimedia/image_framework/interfaces/innerkits/include/pixel_map.h"

namespace OHOS {

namespace AbilityRuntime {
class Context;
}

namespace AppExecFwk {
class Configuration;
class Ability;
class FormAshmem;
}

namespace Rosen {
class Window;
class ISceneSession;
class ISessionStageStateListener;
class RSSurfaceNode;
enum class WindowSizeChangeReason : uint32_t;
enum class WindowMode : uint32_t;
class RSSurfaceNode;
class RSTransaction;
}

namespace AAFwk {
class Want;
}

namespace MMI {
class PointerEvent;
class KeyEvent;
class AxisEvent;
} // namespace MMI

} // namespace OHOS

class NativeEngine;
class NativeValue;

namespace OHOS::Ace {

#ifndef ACE_EXPORT
#define ACE_EXPORT __attribute__((visibility("default")))
#endif

class ACE_EXPORT UIContent {
public:
    static std::unique_ptr<UIContent> Create(OHOS::AbilityRuntime::Context* context, NativeEngine* runtime,
                                             bool isFormRender);
    static std::unique_ptr<UIContent> Create(OHOS::AbilityRuntime::Context* context, NativeEngine* runtime);
    static std::unique_ptr<UIContent> Create(OHOS::AppExecFwk::Ability* ability);
    static std::shared_ptr<UIContent> CreateUI(OHOS::AbilityRuntime::Context* context, NativeEngine* runtime);
    static void ShowDumpHelp(std::vector<std::string>& info);

    virtual ~UIContent() = default;

    // UI content life-cycles
    virtual void Initialize(OHOS::Rosen::Window* window, const std::string& url, NativeValue* storage) = 0;
    virtual void Initialize(const std::string& url, NativeValue* storage) = 0;
    virtual void Foreground() = 0;
    virtual void Background() = 0;
    virtual void Focus() = 0;
    virtual void UnFocus() = 0;
    virtual void Destroy() = 0;
    virtual void OnNewWant(const OHOS::AAFwk::Want& want) = 0;

    // distribute
    virtual void Restore(OHOS::Rosen::Window* window, const std::string& contentInfo, NativeValue* storage) = 0;
    virtual void Restore(const std::string& contentInfo, NativeValue* storage) = 0;
    virtual std::string GetContentInfo() const = 0;
    virtual void DestroyUIDirector() = 0;

    // UI content event process
    virtual bool ProcessBackPressed() = 0;
    virtual bool ProcessPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) = 0;
    virtual bool ProcessKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent) = 0;
    virtual bool ProcessAxisEvent(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent) = 0;
    virtual bool ProcessVsyncEvent(uint64_t timeStampNanos) = 0;
    virtual void UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config) = 0;
    virtual void UpdateViewportConfig(const ViewportConfig& config, OHOS::Rosen::WindowSizeChangeReason reason,
        const std::shared_ptr<OHOS::Rosen::RSTransaction> rsTransaction) = 0;
    virtual void UpdateWindowMode(OHOS::Rosen::WindowMode mode, bool hasDeco = true) = 0;
    virtual void HideWindowTitleButton(bool hideSplit, bool hideMaximize, bool hideMinimize) = 0;

    // Window color
    virtual uint32_t GetBackgroundColor() = 0;
    virtual void SetBackgroundColor(uint32_t color) = 0;

    virtual void DumpInfo(const std::vector<std::string>& params, std::vector<std::string>& info) = 0;

    // Set UIContent callback for custom window animation
    virtual void SetNextFrameLayoutCallback(std::function<void()>&& callback) = 0;

    // Receive memory level notification
    virtual void NotifyMemoryLevel(int32_t level) = 0;

    virtual void SetAppWindowTitle(const std::string& title) = 0;
    virtual void SetAppWindowIcon(const std::shared_ptr<Media::PixelMap>& pixelMap) = 0;

    // ArkTS Form
    virtual std::shared_ptr<Rosen::RSSurfaceNode> GetFormRootNode() = 0;

    virtual void UpdateFormDate(const std::string& data) = 0;
    virtual void UpdateFormSharedImage(
        const std::map<std::string, sptr<OHOS::AppExecFwk::FormAshmem>>& imageDataMap) {}

    virtual void SetFormWidth(const float width) = 0;
    virtual void SetFormHeight(const float height) = 0;
    virtual float GetFormWidth() = 0;
    virtual float GetFormHeight() = 0;
    virtual void ReloadForm() {};

    virtual void SetActionEventHandler(
        std::function<void(const std::string&)>&& actionCallback) = 0;
    virtual void SetErrorEventHandler(
        std::function<void(const std::string&, const std::string&)>&& errorCallback) = 0;

    // window scene
    virtual void InitWindowScene(
        const sptr<Rosen::ISceneSession>& iSceneSession,
        const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode,
        const std::shared_ptr<Rosen::ISessionStageStateListener>& listener) = 0;

    virtual void Connect() = 0;
    virtual void DoForeground() = 0;
    virtual void DoBackground() = 0;
    virtual void DoDisconnect() = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_CONTENT_H
