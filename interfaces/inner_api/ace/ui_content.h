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

#include <functional>
#include <map>
#include <memory>
#include <refbase.h>
#include <string>
#include <vector>
#include <list>

#include "arkui_rect.h"
#include "macros.h"
#include "modal_ui_extension_config.h"
#include "popup_ui_extension_config.h"
#include "serialized_gesture.h"
#include "serializeable_object.h"
#include "viewport_config.h"
#include "constants.h"
namespace OHOS {

namespace AbilityRuntime {
class Context;
} // namespace AbilityRuntime

namespace AppExecFwk {
class Configuration;
class Ability;
class FormAshmem;
} // namespace AppExecFwk

namespace Accessibility {
class AccessibilityElementInfo;
}
namespace Rosen {
class Window;
struct Rect;
enum class WindowSizeChangeReason : uint32_t;
enum class WindowMode : uint32_t;
enum class MaximizeMode : uint32_t;
class RSSurfaceNode;
class RSTransaction;
class Transform;
enum class AvoidAreaType : uint32_t;
class AvoidArea;
struct DecorButtonStyle;
} // namespace Rosen

namespace AAFwk {
class Want;
} // namespace AAFwk

namespace MMI {
class PointerEvent;
class KeyEvent;
class AxisEvent;
} // namespace MMI

namespace Media {
class PixelMap;
} // namespace Media

namespace AbilityBase {
struct ViewData;
enum class AutoFillType;
} // namespace AbilityBase

class RefBase;
class Parcelable;
class IRemoteObject;

} // namespace OHOS

namespace OHOS::Ace {
struct AccessibilityParentRectInfo;
} // namespace OHOS::Ace

class NativeEngine;
typedef struct napi_value__* napi_value;

namespace OHOS::Ace {
class ACE_FORCE_EXPORT UIContent {
public:
    static std::unique_ptr<UIContent> Create(
        OHOS::AbilityRuntime::Context* context, NativeEngine* runtime, bool isFormRender);
    static std::unique_ptr<UIContent> Create(OHOS::AbilityRuntime::Context* context, NativeEngine* runtime);
    static std::unique_ptr<UIContent> Create(OHOS::AppExecFwk::Ability* ability);
    static void ShowDumpHelp(std::vector<std::string>& info);
    static UIContent* GetUIContent(int32_t instanceId);
    static std::string GetCurrentUIStackInfo();

    virtual ~UIContent() = default;

    // UI content life-cycles
    virtual UIContentErrorCode Initialize(OHOS::Rosen::Window* window, const std::string& url, napi_value storage) = 0;
    virtual UIContentErrorCode Initialize(
        OHOS::Rosen::Window* window, const std::shared_ptr<std::vector<uint8_t>>& content, napi_value storage) = 0;
    virtual UIContentErrorCode Initialize(OHOS::Rosen::Window* window,
        const std::shared_ptr<std::vector<uint8_t>>& content, napi_value storage, const std::string& contentName)
    {
        return UIContentErrorCode::NO_ERRORS;
    }
    virtual UIContentErrorCode InitializeByName(OHOS::Rosen::Window *window, const std::string &name,
                                                napi_value storage) = 0;
    virtual void InitializeByName(OHOS::Rosen::Window *window,
        const std::string &name, napi_value storage, uint32_t focusWindowId) {};
    virtual void InitializeDynamic(int32_t hostInstanceId, const std::string& hapPath, const std::string& abcPath,
        const std::string& entryPoint, const std::vector<std::string>& registerComponents) {};

    // UIExtensionAbility initialize for focusWindow ID
    virtual void Initialize(
        OHOS::Rosen::Window* window, const std::string& url, napi_value storage, uint32_t focusWindowID) = 0;
    virtual void Foreground() = 0;
    virtual void Background() = 0;
    virtual void Focus() = 0;
    virtual void UnFocus() = 0;
    virtual void Destroy() = 0;
    virtual void OnNewWant(const OHOS::AAFwk::Want& want) = 0;

    // restore
    virtual UIContentErrorCode Restore(
        OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage,
        ContentInfoType type = ContentInfoType::CONTINUATION) = 0;
    virtual std::string GetContentInfo(ContentInfoType type = ContentInfoType::CONTINUATION) const = 0;
    virtual void DestroyUIDirector() = 0;

    // UI content event process
    virtual bool ProcessBackPressed() = 0;
    virtual bool ProcessPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) = 0;
    virtual bool ProcessKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme = false) = 0;
    virtual bool ProcessAxisEvent(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent) = 0;
    virtual bool ProcessVsyncEvent(uint64_t timeStampNanos) = 0;
    virtual void SetIsFocusActive(bool isFocusActive) = 0;
    virtual void UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config) = 0;
    virtual void UpdateViewportConfig(const ViewportConfig& config, OHOS::Rosen::WindowSizeChangeReason reason,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction = nullptr,
        const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas = {}) {};
    virtual void UpdateWindowMode(OHOS::Rosen::WindowMode mode, bool hasDeco = true) = 0;
    virtual void NotifyWindowMode(OHOS::Rosen::WindowMode mode) {};
    virtual void HideWindowTitleButton(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose) = 0;
    virtual void SetIgnoreViewSafeArea(bool ignoreViewSafeArea) = 0;
    virtual void UpdateMaximizeMode(OHOS::Rosen::MaximizeMode mode) {};
    virtual void ProcessFormVisibleChange(bool isVisible) {};
    virtual void NotifyRotationAnimationEnd() {};

    // only vaild in ContainerModalPatternEnhance
    virtual void UpdateTitleInTargetPos(bool isShow, int32_t height) = 0;

    // Window color
    virtual uint32_t GetBackgroundColor() = 0;
    virtual void SetBackgroundColor(uint32_t color) = 0;
    virtual void SetUIContentType(UIContentType uIContentType) {};
    virtual void SetWindowContainerColor(uint32_t activeColor, uint32_t inactiveColor) = 0;

    // Judge whether window need soft keyboard or not
    virtual bool NeedSoftKeyboard()
    {
        return false;
    }

    virtual void ChangeSensitiveNodes(bool isSensitive) {}

    virtual void SetOnWindowFocused(const std::function<void()>& callback) {};

    virtual void DumpInfo(const std::vector<std::string>& params, std::vector<std::string>& info) = 0;

    // Set UIContent callback for custom window animation
    virtual void SetNextFrameLayoutCallback(std::function<void()>&& callback) = 0;

    // Receive memory level notification
    virtual void NotifyMemoryLevel(int32_t level) = 0;

    virtual void SetAppWindowTitle(const std::string& title) = 0;
    virtual void SetAppWindowIcon(const std::shared_ptr<Media::PixelMap>& pixelMap) = 0;

    // ArkTS Form
    virtual void PreInitializeForm(OHOS::Rosen::Window* window, const std::string& url, napi_value storage) = 0;
    virtual void RunFormPage() = 0;
    virtual std::shared_ptr<Rosen::RSSurfaceNode> GetFormRootNode() = 0;

    virtual void UpdateFormData(const std::string& data) = 0;
    virtual void UpdateFormSharedImage(const std::map<std::string, sptr<OHOS::AppExecFwk::FormAshmem>>& imageDataMap) {}

    virtual void SetFormWidth(const float width) = 0;
    virtual void SetFormHeight(const float height) = 0;
    virtual float GetFormWidth() = 0;
    virtual float GetFormHeight() = 0;
    virtual void ReloadForm(const std::string& url) {};
    virtual void OnFormSurfaceChange(float width, float height,
        OHOS::Rosen::WindowSizeChangeReason type = static_cast<OHOS::Rosen::WindowSizeChangeReason>(0),
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr) {}

    virtual void SetFormBackgroundColor(const std::string& color) {};
    virtual void SetFontScaleFollowSystem(const bool fontScaleFollowSystem) {};
    virtual void SetFormRenderingMode(int8_t renderMode) {};

    virtual void SetActionEventHandler(std::function<void(const std::string&)>&& actionCallback) {};
    virtual void SetErrorEventHandler(std::function<void(const std::string&, const std::string&)>&& errorCallback) {};
    virtual void SetFormLinkInfoUpdateHandler(std::function<void(const std::vector<std::string>&)>&& callback) {};
    virtual void RegisterAccessibilityChildTree(
        uint32_t parentWindowId, int32_t parentTreeId, int64_t parentElementId) {};
    virtual void SetAccessibilityGetParentRectHandler(std::function<void(int32_t&, int32_t&)>&& callback) {};
    virtual void SetAccessibilityGetParentRectHandler(std::function<void(AccessibilityParentRectInfo&)>&& callback) {};
    virtual void DeregisterAccessibilityChildTree() {};
    virtual void AccessibilityDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info) {};

    // for distribute UI source
    virtual SerializeableObjectArray DumpUITree()
    {
        return SerializeableObjectArray();
    };
    virtual void SubscribeUpdate(const std::function<void(int32_t, SerializeableObjectArray&)>& onUpdate) {}
    virtual void UnSubscribeUpdate() {}
    virtual void ProcessSerializeableInputEvent(const SerializeableObjectArray& array) {}
    // for distribute UI sink
    virtual void RestoreUITree(const SerializeableObjectArray& array) {}
    virtual void UpdateUITree(const SerializeableObjectArray& array) {}
    virtual void SubscribeInputEventProcess(const std::function<void(SerializeableObjectArray&)>& onEvent) {}
    virtual void UnSubscribeInputEventProcess() {}

    virtual void GetResourcePaths(std::vector<std::string>& resourcesPaths, std::string& assetRootPath,
        std::vector<std::string>& assetBasePaths, std::string& resFolderName) {};
    virtual void SetResourcePaths(const std::vector<std::string>& resourcesPaths, const std::string& assetRootPath,
        const std::vector<std::string>& assetBasePaths) {};

    virtual void UpdateResource() {}

    virtual napi_value GetUINapiContext()
    {
        napi_value result = nullptr;
        return result;
    }

    /**
     * @description: Create a full-window modal UIExtensionComponent.
     * @param want Indicates the want of UIExtensionAbility.
     * @param callbacks Indicates the UIExtensionComponent callbacks.
     * @param config Indicates the Modal page configs.
     * @return The return value is the ID of the session held by the UIExtensionComponent
     * if creation is not successful, it returns 0 by default.
     */
    virtual int32_t CreateModalUIExtension(
        const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks, const ModalUIExtensionConfig& config) = 0;

    /**
     * @description: Close the full-window modal.
     * @param sessionId Indicates the sessionId of UIExtensionAbility.
     * If the sessionId is 0, refuse to close
     */
    virtual void CloseModalUIExtension(int32_t sessionId) = 0;

    virtual void UpdateModalUIExtensionConfig(
        int32_t sessionId, const ModalUIExtensionAllowedUpdateConfig& config) {};

    /**
     * @description: Set parent ability token.
     * @param token ability token.
     */
    virtual void SetParentToken(sptr<IRemoteObject> token);

    /**
     * @description: Get parent ability token.
     * @return return parent ability token.
     */
    virtual sptr<IRemoteObject> GetParentToken();

    virtual bool DumpViewData(AbilityBase::ViewData& viewData, AbilityBase::AutoFillType& type)
    {
        return false;
    }

    virtual bool CheckNeedAutoSave()
    {
        return false;
    }

    virtual int32_t GetInstanceId()
    {
        return -1;
    }

    /**
     * @description: Recycle form.
     * @return return Json string of status data of ArkTS form.
     */
    virtual std::string RecycleForm()
    {
        return "";
    }

    /**
     * @description: Recover form.
     * @param statusData Indicates json string of status data of ArkTS form.
     */
    virtual void RecoverForm(const std::string &statusData) {}

    virtual void SetContainerModalTitleVisible(bool customTitleSettedShow, bool floatingTitleSettedShow) {}

    virtual void SetContainerModalTitleHeight(int height) {}

    virtual int32_t GetContainerModalTitleHeight()
    {
        return -1;
    }

    virtual bool GetContainerModalButtonsRect(Rosen::Rect& containerModal, Rosen::Rect& buttons)
    {
        return false;
    }

    virtual void SubscribeContainerModalButtonsRectChange(
        std::function<void(Rosen::Rect& containerModal, Rosen::Rect& buttons)>&& callback) {}

    virtual void SetUIExtensionSubWindow(bool isUIExtensionSubWindow) {}

    virtual bool IsUIExtensionSubWindow()
    {
        return false;
    }

    virtual void SetUIExtensionAbilityProcess(bool isUIExtensionAbilityProcess) {}

    virtual bool IsUIExtensionAbilityProcess()
    {
        return false;
    }

    virtual void SetUIExtensionAbilityHost(bool isUIExtensionAbilityHost) {}

    virtual bool IsUIExtensionAbilityHost()
    {
        return false;
    }

#ifndef PREVIEW
    virtual void SearchElementInfoByAccessibilityId(
        int64_t elementId, int32_t mode,
        int64_t baseParent, std::list<Accessibility::AccessibilityElementInfo>& output) {};

    virtual void SearchElementInfosByText(
        int64_t elementId, const std::string& text, int64_t baseParent,
        std::list<Accessibility::AccessibilityElementInfo>& output) {};

    virtual void FindFocusedElementInfo(
        int64_t elementId, int32_t focusType,
        int64_t baseParent, Accessibility::AccessibilityElementInfo& output) {};

    virtual void FocusMoveSearch(
        int64_t elementId, int32_t direction,
        int64_t baseParent, Accessibility::AccessibilityElementInfo& output) {};

    virtual bool NotifyExecuteAction(int64_t elementId, const std::map<std::string, std::string>& actionArguments,
        int32_t action, int64_t offset)
    {
        return false;
    }

    virtual void HandleAccessibilityHoverEvent(float pointX, float pointY, int32_t sourceType,
        int32_t eventType, int64_t timeMs) {}
#endif

    /**
     * @description: Set UIContent callback after layout finish.
     * @param callback callback func.
     */
    virtual void SetFrameLayoutFinishCallback(std::function<void()>&& callback) {};

    // Current paintSize of window
    virtual void GetAppPaintSize(OHOS::Rosen::Rect& paintrect) {};

    // Get paintSize of window by calculating
    virtual void GetWindowPaintSize(OHOS::Rosen::Rect& paintrect) {};

    /**
     * @description: Create a custom popup with UIExtensionComponent.
     * @param want Indicates the want of UIExtensionAbility.
     * @param callbacks Indicates the UIExtensionComponent callbacks.
     * @param config Indicates the custom popup configs.
     * @return The return value is the ID of the UI node which bind the pupop
     * if creation is not successful, it returns 0 by default.
     */
    virtual int32_t CreateCustomPopupUIExtension(
        const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks, const CustomPopupUIExtensionConfig& config)
    {
        return 0;
    }

    /**
     * @description: Destroy the custom popup.
     * @param config Indicates the ID of the UI node which bind the pupop
     */
    virtual void DestroyCustomPopupUIExtension(int32_t nodeId) {}

    /**
     * @description: Update the custom popup.
     * @param config Indicates the custom popup configs.
      */
    virtual void UpdateCustomPopupUIExtension(const CustomPopupUIExtensionConfig& config) {}

    virtual SerializedGesture GetFormSerializedGesture()
    {
        return SerializedGesture();
    }

    virtual bool ProcessPointerEventWithCallback(
        const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent, const std::function<void()>& callback)
    {
        return true;
    };

    virtual void UpdateTransform(const OHOS::Rosen::Transform& transform) {};

    virtual void UpdateDecorVisible(bool visible, bool hasDeco = true) {};

    virtual std::vector<Ace::RectF> GetOverlayNodePositions() const
    {
        return {};
    };

    virtual void RegisterOverlayNodePositionsUpdateCallback(
        const std::function<void(std::vector<Ace::RectF>)>& callback) const {};

    virtual void SetContentNodeGrayScale(float grayscale) {};

    virtual sptr<IRemoteObject> GetRemoteObj()
    {
        return {};
    }

    virtual void PreLayout() {};

    virtual void SetStatusBarItemColor(uint32_t color) {};

    virtual void SetForceSplitEnable(bool isForceSplit, const std::string& homePage) {};

    virtual void EnableContainerModalGesture(bool isEnable) {};

    virtual bool GetContainerFloatingTitleVisible()
    {
        return false;
    }

    virtual bool GetContainerCustomTitleVisible()
    {
        return false;
    }

    virtual bool GetContainerControlButtonVisible()
    {
        return false;
    }

    virtual void OnContainerModalEvent(const std::string& name, const std::string& value) {}
    virtual void UpdateConfigurationSyncForAll(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config) {}

    virtual void SetContainerButtonStyle(const Rosen::DecorButtonStyle& decorButtonStyle) {}

    virtual int32_t AddFocusActiveChangeCallback(const std::function<void(bool isFocusAvtive)>& callback)
    {
        return 0;
    }

    virtual void RemoveFocusActiveChangeCallback(int32_t handler) {};

    virtual bool ProcessPointerEvent(
        const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent, const std::function<void(bool)>& callback)
    {
        return false;
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_CONTENT_H
