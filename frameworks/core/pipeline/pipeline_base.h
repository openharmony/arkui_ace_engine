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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_PIPELINE_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_PIPELINE_BASE_H

#include <functional>
#include <memory>
#include <stack>
#include <string>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/resource/asset_manager.h"
#include "base/resource/data_provider_manager.h"
#include "base/resource/shared_image_manager.h"
#include "base/thread/task_executor.h"
#include "core/accessibility/accessibility_manager.h"
#include "core/animation/schedule_task.h"
#include "core/common/clipboard/clipboard_proxy.h"
#include "core/common/draw_delegate.h"
#include "core/common/event_manager.h"
#include "core/common/platform_bridge.h"
#include "core/common/platform_res_register.h"
#include "core/common/window_animation_config.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/theme/theme_manager.h"
#include "core/event/axis_event.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/rotation_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"
#include "core/image/image_cache.h"

namespace OHOS::Ace {

class Frontend;
class OffscreenCanvas;
class Window;
class FontManager;
class ManagerInterface;
enum class FrontendType;

class ACE_EXPORT PipelineBase : public AceType {
    DECLARE_ACE_TYPE(PipelineBase, AceType);

public:
    PipelineBase() = default;
    PipelineBase(std::unique_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor, RefPtr<AssetManager> assetManager,
        const RefPtr<Frontend>& frontend, int32_t instanceId);
    PipelineBase(std::unique_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor, RefPtr<AssetManager> assetManager,
        const RefPtr<Frontend>& frontend, int32_t instanceId, RefPtr<PlatformResRegister> platformResRegister);
    ~PipelineBase() override;

    static RefPtr<PipelineBase> GetCurrentContext();

    virtual void SetupRootElement() = 0;

    virtual uint64_t GetTimeFromExternalTimer();

    bool Animate(const AnimationOption& option, const RefPtr<Curve>& curve,
        const std::function<void()>& propertyCallback, const std::function<void()>& finishCallBack = nullptr);

    virtual void AddKeyFrame(
        float fraction, const RefPtr<Curve>& curve, const std::function<void()>& propertyCallback) = 0;

    virtual void AddKeyFrame(float fraction, const std::function<void()>& propertyCallback) = 0;

    void PrepareOpenImplicitAnimation();

    void OpenImplicitAnimation(const AnimationOption& option, const RefPtr<Curve>& curve,
        const std::function<void()>& finishCallBack = nullptr);

    void PrepareCloseImplicitAnimation();

    bool CloseImplicitAnimation();

    void ForceLayoutForImplicitAnimation();

    // add schedule task and return the unique mark id.
    virtual uint32_t AddScheduleTask(const RefPtr<ScheduleTask>& task) = 0;

    // remove schedule task by id.
    virtual void RemoveScheduleTask(uint32_t id) = 0;

    // Called by view when touch event received.
    virtual void OnTouchEvent(const TouchEvent& point, bool isSubPipe = false) = 0;

    // Called by container when key event received.
    // if return false, then this event needs platform to handle it.
    virtual bool OnKeyEvent(const KeyEvent& event) = 0;

    // Called by view when mouse event received.
    virtual void OnMouseEvent(const MouseEvent& event) = 0;

    // Called by view when axis event received.
    virtual void OnAxisEvent(const AxisEvent& event) = 0;

    // Called by container when rotation event received.
    // if return false, then this event needs platform to handle it.
    virtual bool OnRotationEvent(const RotationEvent& event) const = 0;

    // Called by window when received vsync signal.
    virtual void OnVsyncEvent(uint64_t nanoTimestamp, uint32_t frameCount);

    // Called by view
    virtual void OnDragEvent(int32_t x, int32_t y, DragEventAction action) = 0;

    // Called by view when idle event.
    virtual void OnIdle(int64_t deadline) = 0;

    virtual void SetBuildAfterCallback(const std::function<void()>& callback) = 0;

    virtual void FlushAnimation(uint64_t nanoTimestamp) = 0;

    virtual void SendEventToAccessibility(const AccessibilityEvent& accessibilityEvent) = 0;

    virtual void SaveExplicitAnimationOption(const AnimationOption& option) = 0;

    virtual void CreateExplicitAnimator(const std::function<void()>& onFinishEvent) = 0;

    virtual void ClearExplicitAnimationOption() = 0;

    virtual AnimationOption GetExplicitAnimationOption() const = 0;

    virtual void Destroy() = 0;

    virtual void OnShow() = 0;

    virtual void OnHide() = 0;

    virtual void WindowFocus(bool isFocus) = 0;

    virtual void OnSurfaceChanged(
        int32_t width, int32_t height, WindowSizeChangeReason type = WindowSizeChangeReason::UNDEFINED) = 0;

    virtual void OnSurfacePositionChanged(int32_t posX, int32_t posY) = 0;

    virtual void OnSurfaceDensityChanged(double density) = 0;

    virtual void OnSystemBarHeightChanged(double statusBar, double navigationBar) = 0;

    virtual void OnSurfaceDestroyed() = 0;

    virtual void NotifyOnPreDraw() = 0;

    virtual bool CallRouterBackToPopPage() = 0;

    virtual void OnPageShow() {}

    virtual void OnActionEvent(const std::string& action);

    virtual void Finish(bool autoFinish = true) const {}

    virtual void RequestFullWindow(int32_t duration) {}

    virtual bool RequestFocus(const std::string& targetNodeId)
    {
        return false;
    }

    // Called by AceAbility and UiContent.
    void DumpInfo(const std::vector<std::string>& params, std::vector<std::string>& info) const;

    // Called by AceEngine.
    bool Dump(const std::vector<std::string>& params) const;

    virtual bool IsLastPage()
    {
        return false;
    }

    virtual bool GetIsDeclarative() const
    {
        return true;
    }

    virtual void SetAppBgColor(const Color& color)
    {
        appBgColor_ = color;
    }

    const Color& GetAppBgColor() const
    {
        return appBgColor_;
    }

    virtual void RefreshRootBgColor() const {}

    virtual void PostponePageTransition() {}
    virtual void LaunchPageTransition() {}

    virtual void GetBoundingRectData(int32_t nodeId, Rect& rect) {}

    virtual RefPtr<AccessibilityManager> GetAccessibilityManager() const
    {
        return nullptr;
    }

    void SetRootSize(double density, int32_t width, int32_t height);

    void UpdateFontWeightScale();

    double NormalizeToPx(const Dimension& dimension) const;

    double ConvertPxToVp(const Dimension& dimension) const;

    using FinishEventHandler = std::function<void()>;
    void SetFinishEventHandler(FinishEventHandler&& listener)
    {
        finishEventHandler_ = std::move(listener);
    }

    using StartAbilityHandler = std::function<void(const std::string& address)>;
    void SetStartAbilityHandler(StartAbilityHandler&& listener)
    {
        startAbilityHandler_ = std::move(listener);
    }
    void HyperlinkStartAbility(const std::string& address) const;

    using ActionEventHandler = std::function<void(const std::string& action)>;
    void SetActionEventHandler(ActionEventHandler&& listener)
    {
        actionEventHandler_ = std::move(listener);
    }

    using StatusBarEventHandler = std::function<void(const Color& color)>;
    void SetStatusBarEventHandler(StatusBarEventHandler&& listener)
    {
        statusBarBgColorEventHandler_ = std::move(listener);
    }
    void NotifyStatusBarBgColor(const Color& color) const;
    using PopupEventHandler = std::function<void()>;

    void SetPopupEventHandler(PopupEventHandler&& listener)
    {
        popupEventHandler_ = std::move(listener);
    }
    void NotifyPopupDismiss() const;

    using RouterBackEventHandler = std::function<void()>;
    void SetRouterBackEventHandler(RouterBackEventHandler&& listener)
    {
        routerBackEventHandler_ = std::move(listener);
    }
    void NotifyRouterBackDismiss() const;

    using PopPageSuccessEventHandler = std::function<void(const std::string& pageUrl, const int32_t pageId)>;
    void SetPopPageSuccessEventHandler(PopPageSuccessEventHandler&& listener)
    {
        popPageSuccessEventHandler_.push_back(std::move(listener));
    }
    void NotifyPopPageSuccessDismiss(const std::string& pageUrl, int32_t pageId) const;

    using IsPagePathInvalidEventHandler = std::function<void(bool& isPageInvalid)>;
    void SetIsPagePathInvalidEventHandler(IsPagePathInvalidEventHandler&& listener)
    {
        isPagePathInvalidEventHandler_.push_back(std::move(listener));
    }
    void NotifyIsPagePathInvalidDismiss(bool isPageInvalid) const;

    using DestroyEventHandler = std::function<void()>;
    void SetDestroyHandler(DestroyEventHandler&& listener)
    {
        destroyEventHandler_.push_back(std::move(listener));
    }
    void NotifyDestroyEventDismiss() const;

    using DispatchTouchEventHandler = std::function<void(const TouchEvent& event)>;
    void SetDispatchTouchEventHandler(DispatchTouchEventHandler&& listener)
    {
        dispatchTouchEventHandler_.push_back(std::move(listener));
    }
    void NotifyDispatchTouchEventDismiss(const TouchEvent& event) const;

    using GetViewScaleCallback = std::function<bool(float&, float&)>;
    void SetGetViewScaleCallback(GetViewScaleCallback&& callback)
    {
        getViewScaleCallback_ = callback;
    }

    using OnPageShowCallBack = std::function<void()>;
    void SetOnPageShow(OnPageShowCallBack&& onPageShowCallBack)
    {
        onPageShowCallBack_ = std::move(onPageShowCallBack);
    }

    using AnimationCallback = std::function<void()>;
    void SetAnimationCallback(AnimationCallback&& callback)
    {
        animationCallback_ = std::move(callback);
    }

    using ProfilerCallback = std::function<void(const std::string&)>;
    void SetOnVsyncProfiler(const ProfilerCallback& callback)
    {
        onVsyncProfiler_ = callback;
    }

    using OnRouterChangeCallback = bool (*)(const std::string currentRouterPath);
    void AddRouterChangeCallback(const OnRouterChangeCallback& onRouterChangeCallback)
    {
        onRouterChangeCallback_ = onRouterChangeCallback;
    }

    void onRouterChange(const std::string& url);

    void ResetOnVsyncProfiler()
    {
        onVsyncProfiler_ = nullptr;
    }

    bool GetViewScale(float& scaleX, float& scaleY)
    {
        if (getViewScaleCallback_) {
            return getViewScaleCallback_(scaleX, scaleY);
        }
        return false;
    }

    RefPtr<TaskExecutor> GetTaskExecutor() const
    {
        return taskExecutor_;
    }

    RefPtr<Frontend> GetFrontend() const;

    int32_t GetInstanceId() const
    {
        return instanceId_;
    }

    void ClearImageCache();

    RefPtr<ImageCache> GetImageCache() const;

    Window* GetWindow()
    {
        return window_.get();
    }

    RefPtr<AssetManager> GetAssetManager() const
    {
        return assetManager_;
    }

    int32_t GetMinPlatformVersion() const
    {
        return minPlatformVersion_;
    }
    void SetMinPlatformVersion(int32_t minPlatformVersion)
    {
        minPlatformVersion_ = minPlatformVersion;
    }

    RefPtr<ThemeManager> GetThemeManager() const
    {
        return themeManager_;
    }
    void SetThemeManager(RefPtr<ThemeManager> theme)
    {
        themeManager_ = std::move(theme);
    }

    template<typename T>
    RefPtr<T> GetTheme() const
    {
        if (themeManager_) {
            return themeManager_->GetTheme<T>();
        }
        return {};
    }

    const RefPtr<ManagerInterface>& GetTextFieldManager()
    {
        return textFieldManager_;
    }
    void SetTextFieldManager(const RefPtr<ManagerInterface>& manager);

    const RefPtr<FontManager>& GetFontManager() const
    {
        return fontManager_;
    }

    const RefPtr<DataProviderManagerInterface>& GetDataProviderManager() const
    {
        return dataProviderManager_;
    }
    void SetDataProviderManager(const RefPtr<DataProviderManagerInterface>& dataProviderManager)
    {
        dataProviderManager_ = dataProviderManager;
    }

    const RefPtr<PlatformBridge>& GetMessageBridge() const
    {
        return messageBridge_;
    }
    void SetMessageBridge(const RefPtr<PlatformBridge>& messageBridge)
    {
        messageBridge_ = messageBridge;
    }

    void SetIsJsCard(bool isJsCard)
    {
        isJsCard_ = isJsCard;
    }

    void SetIsJsPlugin(bool isJsPlugin)
    {
        isJsPlugin_ = isJsPlugin;
    }

    void SetDrawDelegate(std::unique_ptr<DrawDelegate> delegate)
    {
        drawDelegate_ = std::move(delegate);
    }

    bool IsJsCard() const
    {
        return isJsCard_;
    }

    void SetIsEtsCard(bool isEtsCard)
    {
        isEtsCard_ = isEtsCard;
    }

    bool IsEtsCard() const
    {
        return isEtsCard_;
    }

    // Get the dp scale which used to covert dp to logic px.
    double GetDipScale() const
    {
        return dipScale_;
    }

    // Get the widnow design scale used to covert lpx to logic px.
    double GetLogicScale() const
    {
        return designWidthScale_;
    }

    float GetFontScale() const
    {
        return fontScale_;
    }
    void SetFontScale(float fontScale);

    int32_t GetWindowId() const
    {
        return windowId_;
    }

    void SetWindowId(int32_t windowId)
    {
        windowId_ = windowId;
    }

    float GetViewScale() const
    {
        return viewScale_;
    }

    double GetRootWidth() const
    {
        return rootWidth_;
    }

    double GetRootHeight() const
    {
        return rootHeight_;
    }


    // TODO:: Set up window manager class to manage window related operations
    void SetWindowModal(WindowModal modal)
    {
        windowModal_ = modal;
    }

    WindowModal GetWindowModal() const
    {
        return windowModal_;
    }

    void SetAppIconId(int32_t id)
    {
        appIconId_ = id;
    }

    int32_t GetAppIconId() const
    {
        return appIconId_;
    }

    void SetAppLabelId(int32_t id)
    {
        appLabelId_ = id;
    }

    int32_t GetAppLabelId() const
    {
        return appLabelId_;
    }

    void SetWindowMinimizeCallBack(std::function<bool(void)>&& callback)
    {
        windowMinimizeCallback_ = std::move(callback);
    }

    void SetWindowMaximizeCallBack(std::function<bool(void)>&& callback)
    {
        windowMaximizeCallback_ = std::move(callback);
    }

    void SetWindowRecoverCallBack(std::function<bool(void)>&& callback)
    {
        windowRecoverCallback_ = std::move(callback);
    }

    void SetWindowCloseCallBack(std::function<bool(void)>&& callback)
    {
        windowCloseCallback_ = std::move(callback);
    }

    void SetWindowSplitCallBack(std::function<bool(void)>&& callback)
    {
        windowSplitCallback_ = std::move(callback);
    }

    void SetWindowGetModeCallBack(std::function<WindowMode(void)>&& callback)
    {
        windowGetModeCallback_ = std::move(callback);
    }

    void SetWindowStartMoveCallBack(std::function<void(void)>&& callback)
    {
        windowStartMoveCallback_ = std::move(callback);
    }

    bool FireWindowMinimizeCallBack() const
    {
        if (windowMinimizeCallback_) {
            return windowMinimizeCallback_();
        }
        return false;
    }

    bool FireWindowMaximizeCallBack() const
    {
        if (windowMaximizeCallback_) {
            return windowMaximizeCallback_();
        }
        return false;
    }

    bool FireWindowRecoverCallBack() const
    {
        if (windowRecoverCallback_) {
            return windowRecoverCallback_();
        }
        return false;
    }

    bool FireWindowSplitCallBack() const
    {
        if (windowSplitCallback_) {
            return windowSplitCallback_();
        }
        return false;
    }

    bool FireWindowCloseCallBack() const
    {
        if (windowCloseCallback_) {
            return windowCloseCallback_();
        }
        return false;
    }

    void FireWindowStartMoveCallBack() const
    {
        if (windowStartMoveCallback_) {
            windowStartMoveCallback_();
        }
    }

    WindowMode FireWindowGetModeCallBack() const
    {
        if (windowGetModeCallback_) {
            return windowGetModeCallback_();
        }
        return WindowMode::WINDOW_MODE_UNDEFINED;
    }

    bool IsFullScreenModal() const
    {
        return windowModal_ == WindowModal::NORMAL || windowModal_ == WindowModal::SEMI_MODAL_FULL_SCREEN ||
               windowModal_ == WindowModal::CONTAINER_MODAL || isFullWindow_;
    }

    void SetIsRightToLeft(bool isRightToLeft)
    {
        isRightToLeft_ = isRightToLeft;
    }

    bool IsRightToLeft() const
    {
        return isRightToLeft_;
    }

    void SetEventManager(const RefPtr<EventManager>& eventManager)
    {
        eventManager_ = eventManager;
    }

    RefPtr<EventManager> GetEventManager() const
    {
        return eventManager_;
    }

    bool IsRebuildFinished() const
    {
        return isRebuildFinished_;
    }

    void RequestFrame();

    void RegisterFont(const std::string& familyName, const std::string& familySrc);

    void TryLoadImageInfo(const std::string& src, std::function<void(bool, int32_t, int32_t)>&& loadCallback);

    RefPtr<OffscreenCanvas> CreateOffscreenCanvas(int32_t width, int32_t height);

    void PostAsyncEvent(TaskExecutor::Task&& task, TaskExecutor::TaskType type = TaskExecutor::TaskType::UI);

    void PostAsyncEvent(const TaskExecutor::Task& task, TaskExecutor::TaskType type = TaskExecutor::TaskType::UI);

    void PostSyncEvent(const TaskExecutor::Task& task, TaskExecutor::TaskType type = TaskExecutor::TaskType::UI);

    virtual void FlushReload() {}
    virtual void FlushBuild() {}

    virtual void FlushReloadTransition() {}
    FrontendType GetFrontendType() const
    {
        return frontendType_;
    }

    double GetDensity() const
    {
        return density_;
    }

    RefPtr<PlatformResRegister> GetPlatformResRegister() const
    {
        return platformResRegister_;
    }

    void SetTouchPipeline(const WeakPtr<PipelineBase>& context);
    void RemoveTouchPipeline(const WeakPtr<PipelineBase>& context);

    void OnVirtualKeyboardAreaChange(Rect keyboardArea);

    using virtualKeyBoardCallback = std::function<bool(int32_t, int32_t, double)>;
    void SetVirtualKeyBoardCallback(virtualKeyBoardCallback&& listener)
    {
        virtualKeyBoardCallback_.push_back(std::move(listener));
    }
    bool NotifyVirtualKeyBoard(int32_t width, int32_t height, double keyboard) const
    {
        for (const auto& iterVirtualKeyBoardCallback : virtualKeyBoardCallback_) {
            if (iterVirtualKeyBoardCallback && iterVirtualKeyBoardCallback(width, height, keyboard)) {
                return true;
            }
        }
        return false;
    }

    using configChangedCallback = std::function<void()>;
    void SetConfigChangedCallback(configChangedCallback&& listener)
    {
        configChangedCallback_.push_back(std::move(listener));
    }

    void NotifyConfigurationChange()
    {
        for (const auto& callback : configChangedCallback_) {
            if (callback) {
                callback();
            }
        }
    }

    using PostRTTaskCallback = std::function<void(std::function<void()>&&)>;
    void SetPostRTTaskCallBack(PostRTTaskCallback&& callback)
    {
        postRTTaskCallback_ = std::move(callback);
    }

    void PostTaskToRT(std::function<void()>&& task)
    {
        if (postRTTaskCallback_) {
            postRTTaskCallback_(std::move(task));
        }
    }

    void SetGetWindowRectImpl(std::function<Rect()>&& callback);

    Rect GetCurrentWindowRect() const;

    void SetPluginOffset(const Offset& offset)
    {
        pluginOffset_ = offset;
    }

    Offset GetPluginOffset() const
    {
        return pluginOffset_;
    }

    void SetPluginEventOffset(const Offset& offset)
    {
        pluginEventOffset_ = offset;
    }

    Offset GetPluginEventOffset() const
    {
        return pluginEventOffset_;
    }
    virtual void NotifyMemoryLevel(int32_t level) {}

    void SetDisplayWindowRectInfo(const Rect& displayWindowRectInfo)
    {
        displayWindowRectInfo_ = displayWindowRectInfo;
    }

    // This method can get the coordinates and size of the current window,
    // which can be added to the return value of the GetGlobalOffset method to get the window coordinates of the node.
    const Rect& GetDisplayWindowRectInfo() const
    {
        return displayWindowRectInfo_;
    }
    virtual void FlushMessages() = 0;

protected:
    virtual bool OnDumpInfo(const std::vector<std::string>& params) const
    {
        return false;
    }
    virtual void FlushVsync(uint64_t nanoTimestamp, uint32_t frameCount) = 0;
    virtual void SetRootRect(double width, double height, double offset = 0.0) = 0;
    virtual void FlushPipelineWithoutAnimation() = 0;
    virtual void FlushUITasks() = 0;
    virtual void OnVirtualKeyboardHeightChange(double keyboardHeight) {}

    void UpdateRootSizeAndScale(int32_t width, int32_t height);

    std::list<configChangedCallback> configChangedCallback_;
    std::list<virtualKeyBoardCallback> virtualKeyBoardCallback_;

    bool isRebuildFinished_ = false;
    bool isJsCard_ = false;
    bool isEtsCard_ = false;
    bool isRightToLeft_ = false;
    bool isFullWindow_ = false;

    bool isJsPlugin_ = false;
    int32_t minPlatformVersion_ = 0;
    int32_t windowId_ = 0;
    float fontScale_ = 1.0f;
    float designWidthScale_ = 1.0f;
    float viewScale_ = 1.0f;
    double density_ = 1.0;
    double dipScale_ = 1.0;
    double rootHeight_ = 0.0;
    double rootWidth_ = 0.0;
    FrontendType frontendType_;
    WindowModal windowModal_ = WindowModal::NORMAL;

    Offset pluginOffset_ { 0, 0 };
    Offset pluginEventOffset_ { 0, 0 };
    Color appBgColor_ = Color::WHITE;

    std::unique_ptr<DrawDelegate> drawDelegate_;
    std::stack<bool> pendingImplicitLayout_;
    std::unique_ptr<Window> window_;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<AssetManager> assetManager_;
    WeakPtr<Frontend> weakFrontend_;
    int32_t instanceId_ = 0;
    RefPtr<EventManager> eventManager_;
    RefPtr<ImageCache> imageCache_;
    RefPtr<ThemeManager> themeManager_;
    RefPtr<DataProviderManagerInterface> dataProviderManager_;
    RefPtr<FontManager> fontManager_;
    RefPtr<ManagerInterface> textFieldManager_;
    RefPtr<PlatformBridge> messageBridge_;
    OnPageShowCallBack onPageShowCallBack_;
    AnimationCallback animationCallback_;
    ProfilerCallback onVsyncProfiler_;
    FinishEventHandler finishEventHandler_;
    StartAbilityHandler startAbilityHandler_;
    ActionEventHandler actionEventHandler_;
    RefPtr<PlatformResRegister> platformResRegister_;

    std::vector<WeakPtr<PipelineBase>> touchPluginPipelineContext_;

    RefPtr<Clipboard> clipboard_;
    std::function<void(const std::string&)> clipboardCallback_ = nullptr;
    Rect displayWindowRectInfo_;

private:
    StatusBarEventHandler statusBarBgColorEventHandler_;
    PopupEventHandler popupEventHandler_;
    RouterBackEventHandler routerBackEventHandler_;
    std::list<PopPageSuccessEventHandler> popPageSuccessEventHandler_;
    std::list<IsPagePathInvalidEventHandler> isPagePathInvalidEventHandler_;
    std::list<DestroyEventHandler> destroyEventHandler_;
    std::list<DispatchTouchEventHandler> dispatchTouchEventHandler_;
    GetViewScaleCallback getViewScaleCallback_;
    // OnRouterChangeCallback is function point, need to be initialized.
    OnRouterChangeCallback onRouterChangeCallback_ = nullptr;
    PostRTTaskCallback postRTTaskCallback_;

    // for container modal
    int32_t appLabelId_ = 0;
    int32_t appIconId_ = 0;
    std::function<bool(void)> windowMinimizeCallback_ = nullptr;
    std::function<bool(void)> windowMaximizeCallback_ = nullptr;
    std::function<bool(void)> windowRecoverCallback_ = nullptr;
    std::function<bool(void)> windowCloseCallback_ = nullptr;
    std::function<bool(void)> windowSplitCallback_ = nullptr;
    std::function<void(void)> windowStartMoveCallback_ = nullptr;
    std::function<WindowMode(void)> windowGetModeCallback_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(PipelineBase);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_PIPELINE_BASE_H
