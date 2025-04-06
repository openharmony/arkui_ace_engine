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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_CONTEXT_H

#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <thread>

#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "base/geometry/rect.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/resource/asset_manager.h"
#include "base/resource/data_provider_manager.h"
#include "base/thread/task_executor.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/animation/flush_event.h"
#include "core/animation/page_transition_listener.h"
#include "core/animation/schedule_task.h"
#include "core/common/event_manager.h"
#include "core/common/focus_animation_manager.h"
#include "core/common/platform_res_register.h"
#include "core/components/box/drag_drop_event.h"
#include "core/components/common/properties/color.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/page/page_component.h"
#include "core/components/text_overlay/text_overlay_manager.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/event/visible_ratio_callback.h"
#include "core/event/event_trigger.h"
#include "core/gestures/gesture_info.h"
#include "core/image/image_cache.h"
#include "core/pipeline/base/composed_component.h"
#include "core/pipeline/base/factories/render_factory.h"
#include "core/pipeline/pipeline_base.h"
#ifndef WEARABLE_PRODUCT
#include "core/event/multimodal/multimodal_manager.h"
#include "core/event/multimodal/multimodal_subscriber.h"
#endif
#include "core/common/clipboard/clipboard_proxy.h"

namespace OHOS::Rosen {
class RSUIDirector;
} // namespace OHOS::Rosen

namespace OHOS::Ace {

class CardTransitionController;
class ComposedElement;
class FontManager;
class OverlayElement;
class RenderNode;
class RenderFocusAnimation;
class RootElement;
class SharedTransitionController;
class StageElement;
class StackElement;
class Window;
class Animator;
class ManagerInterface;
class AccessibilityManager;
class RenderContext;
struct PageTarget;
class DialogComponent;
class SelectPopupComponent;
class RenderElement;

struct WindowBlurInfo {
    float progress_;
    WindowBlurStyle style_;
    RRect innerRect_;
    std::vector<RRect> coords_;
};

using OnRouterChangeCallback = bool (*)(const std::string currentRouterPath);
using SubscribeCtrlACallback = std::function<void()>;

class ACE_FORCE_EXPORT PipelineContext : public PipelineBase {
    DECLARE_ACE_TYPE(PipelineContext, PipelineBase);

public:
    static constexpr int32_t DEFAULT_HOVER_ENTER_ANIMATION_ID = -1;
    using TimeProvider = std::function<int64_t(void)>;
    using SurfaceChangedCallbackMap =
        std::unordered_map<int32_t, std::function<void(int32_t, int32_t, int32_t, int32_t, WindowSizeChangeReason)>>;
    using SurfacePositionChangedCallbackMap = std::unordered_map<int32_t, std::function<void(int32_t, int32_t)>>;

    PipelineContext(std::shared_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
        RefPtr<AssetManager> assetManager, RefPtr<PlatformResRegister> platformResRegister,
        const RefPtr<Frontend>& frontend, int32_t instanceId);
    PipelineContext(std::shared_ptr<Window> window, RefPtr<TaskExecutor>& taskExecutor,
        RefPtr<AssetManager> assetManager, const RefPtr<Frontend>& frontend);

    ~PipelineContext() override;

    void SetupRootElement() override;

    // This is used for subwindow, when the subwindow is created,a new subRootElement will be built
    RefPtr<Element> SetupSubRootElement();
    RefPtr<DialogComponent> ShowDialog(
        const DialogProperties& dialogProperties, bool isRightToLeft, const std::string& inspectorTag = "");
    void CloseContextMenu();
    void GetBoundingRectData(int32_t nodeId, Rect& rect) override;

    void PushVisibleCallback(int32_t nodeId, double ratio, std::function<void(bool, double)>&& callback);
    void RemoveVisibleChangeNode(int32_t nodeId);

    void PushPage(const RefPtr<PageComponent>& pageComponent, const RefPtr<StageElement>& stage);
    void PushPage(const RefPtr<PageComponent>& pageComponent);
    void PostponePageTransition() override;
    void LaunchPageTransition() override;

    bool CanPushPage();

    bool IsTransitionStop() const;

    void PopPage();

    void PopToPage(int32_t pageId);

    void RestorePopPage(const RefPtr<PageComponent>& pageComponent);

    bool CanPopPage();

    void ReplacePage(const RefPtr<PageComponent>& pageComponent, const RefPtr<StageElement>& stage,
        const std::function<void()>& listener = nullptr);
    void ReplacePage(const RefPtr<PageComponent>& pageComponent);

    bool CanReplacePage();

    bool ClearInvisiblePages(const std::function<void()>& listener = nullptr);

    bool CallRouterBackToPopPage() override;

    void SetSinglePageId(int32_t pageId);

    bool PopPageStackOverlay() override;

    void HideOverlays() override;

    void NotifyAppStorage(const std::string& key, const std::string& value);

    RefPtr<StackElement> GetLastStack() const;

    RefPtr<PageElement> GetLastPage() const;

    RefPtr<RenderNode> GetLastPageRender() const;

    void ScheduleUpdate(const RefPtr<ComposedComponent>& composed);

    void AddComposedElement(const ComposeId& id, const RefPtr<ComposedElement>& element);

    void RemoveComposedElement(const ComposeId& id, const RefPtr<ComposedElement>& element);

    void AddDirtyElement(const RefPtr<Element>& dirtyElement);

    void AddNeedRebuildFocusElement(const RefPtr<Element>& focusElement);

    void AddDirtyRenderNode(const RefPtr<RenderNode>& renderNode, bool overlay = false);

    void AddNeedRenderFinishNode(const RefPtr<RenderNode>& renderNode);

    void AddDirtyLayoutNode(const RefPtr<RenderNode>& renderNode);

    void AddPredictLayoutNode(const RefPtr<RenderNode>& renderNode);

    void AddGeometryChangedNode(const RefPtr<RenderNode>& renderNode);

    void AddPreFlushListener(const RefPtr<FlushEvent>& listener);

    void AddPostAnimationFlushListener(const RefPtr<FlushEvent>& listener);

    void AddPostFlushListener(const RefPtr<FlushEvent>& listener);

    void AddPageUpdateTask(std::function<void()>&& task, bool directExecute = false);

    void SetRequestedRotationNode(const WeakPtr<RenderNode>& renderNode);

    void RemoveRequestedRotationNode(const WeakPtr<RenderNode>& renderNode);

    // add schedule task and return the unique mark id.
    uint32_t AddScheduleTask(const RefPtr<ScheduleTask>& task) override;

    // remove schedule task by id.
    void RemoveScheduleTask(uint32_t id) override;

    // Called by view when touch event received.
    void OnTouchEvent(const TouchEvent& point, bool isSubPipe = false) override;

#if defined(SUPPORT_TOUCH_TARGET_TEST)
    // Used to determine whether the touched frameNode is the target
    bool OnTouchTargetHitTest(const TouchEvent& point, bool isSubPipe = false, const std::string& target = "") override;
#endif
    // Called by container when event received.
    // if return false, then this event needs platform to handle it.
    bool OnNonPointerEvent(const NonPointerEvent& event) override;

    // Called by view when mouse event received.
    void OnMouseEvent(const MouseEvent& event) override;

    // Called by view when axis event received.
    void OnAxisEvent(const AxisEvent& event) override;

    // Called by container when rotation event received.
    // if return false, then this event needs platform to handle it.
    bool OnRotationEvent(const RotationEvent& event) const override;

    // Called by view when idle event.
    void OnIdle(int64_t deadline) override;

    void OnVirtualKeyboardHeightChange(float keyboardHeight,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr, const float safeHeight = 0.0f,
        const bool supportAvoidance = false, bool forceChange = false) override;

    // Set card position for barrierFree
    void SetCardViewPosition(int id, float offsetX, float offsetY);

    void SetCardViewAccessibilityParams(const std::string& key, bool focus);

    void FlushPipelineImmediately() override;

    void FlushOnceVsyncTask() override {}

    void RegisterEventHandler(const RefPtr<AceEventHandler>& handler)
    {
        eventTrigger_.RegisterEventHandler(handler);
    }

    template<class... Args>
    void FireAsyncEvent(const EventMarker& marker, Args&&... args)
    {
        eventTrigger_.TriggerAsyncEvent(marker, std::forward<Args>(args)...);
    }

    template<class... Args>
    void FireSyncEvent(const EventMarker& marker, Args&&... args)
    {
        eventTrigger_.TriggerSyncEvent(marker, std::forward<Args>(args)...);
    }

    void OnSurfaceChanged(
        int32_t width, int32_t height, WindowSizeChangeReason type = WindowSizeChangeReason::UNDEFINED,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr) override;

    void OnSurfacePositionChanged(int32_t posX, int32_t posY) override;

    void WindowSizeChangeAnimate(int32_t width, int32_t height, WindowSizeChangeReason type,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);

    void OnSurfaceDensityChanged(double density) override;

    void OnTransformHintChanged(uint32_t transform) override {}

    void OnSystemBarHeightChanged(double statusBar, double navigationBar) override;

    void OnSurfaceDestroyed() override;

    // SemiModal and DialogModal have their own enter/exit animation and will exit after animation done.
    void Finish(bool autoFinish = true) const override;

    void RequestFullWindow(int32_t duration) override;

    // Get the font scale used to covert fp to logic px.
    double GetFontUnitScale() const
    {
        return dipScale_ * fontScale_;
    }

    RefPtr<RenderNode> DragTestAll(const TouchEvent& point);
    RefPtr<RenderNode> DragTest(const TouchEvent& point, const RefPtr<RenderNode>& renderNode, int32_t deep);

    void SetRootHeight(double rootHeight)
    {
        if (rootHeight > 0.0) {
            rootHeight_ = rootHeight;
        }
    }

    Rect GetRootRect() const;
    Rect GetStageRect() const;
    Rect GetPageRect() const;

    bool IsSurfaceReady() const
    {
        return isSurfaceReady_;
    }

    void ShowFocusAnimation(
        const RRect& rrect, const Color& color, const Offset& offset, bool isIndented = false) const;

    void ShowFocusAnimation(const RRect& rrect, const Color& color, const Offset& offset, const Rect& clipRect) const;

    void ShowShadow(const RRect& rrect, const Offset& offset) const;

    void ShowShadow(const RRect& rrect, const Offset& offset, const Rect& clipRect) const;

    RefPtr<RenderFocusAnimation> GetRenderFocusAnimation() const;

    void PushFocusAnimation(const RefPtr<Element>& element) const;

    void PushShadow(const RefPtr<Element>& element) const;

    void PopFocusAnimation() const;

    void PopRootFocusAnimation() const;

    void PopShadow() const;

    void CancelFocusAnimation() const;

    void CancelShadow() const;

    void SetUseRootAnimation(bool useRoot);

    void AddDirtyFocus(const RefPtr<FocusNode>& node);

    void RefreshStageFocus();

    void ShowContainerTitle(bool isShow, bool hasDeco = true, bool needUpdate = false) override;

    void SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose) override;

    RefPtr<StageElement> GetStageElement() const;

    RefPtr<ComposedElement> GetComposedElementById(const ComposeId& id);

    void SendCallbackMessageToFrontend(const std::string& callbackId, const std::string& data);

    void SendEventToFrontend(const EventMarker& eventMarker);

    void SendEventToFrontend(const EventMarker& eventMarker, const std::string& param);

    bool AccessibilityRequestFocus(const ComposeId& id);

    bool RequestFocus(const RefPtr<Element>& targetElement);
    bool RequestFocus(const std::string& targetNodeId, bool isSyncRequest = false) override;
    bool RequestDefaultFocus();

    bool NeedSoftKeyboard() override
    {
        return false;
    }

    void SetOnWindowFocused(const std::function<void()>& callback) override {};

    BaseId::IdType AddPageTransitionListener(const PageTransitionListenable::CallbackFuncType& funcObject);

    const RefPtr<OverlayElement> GetOverlayElement() const;

    void RemovePageTransitionListener(typename BaseId::IdType id);

    void ClearPageTransitionListeners();

    void Destroy() override;

    bool IsLastPage() override;

    RefPtr<Element> GetDeactivateElement(int32_t componentId) const;

    void ClearDeactivateElements();

    void AddDeactivateElement(int32_t id, const RefPtr<Element>& element);

    const RefPtr<RenderFactory>& GetRenderFactory() const
    {
        return renderFactory_;
    }

#ifndef WEARABLE_PRODUCT
    void SetMultimodalSubscriber(const RefPtr<MultimodalSubscriber>& multimodalSubscriber);

    const RefPtr<MultiModalManager>& GetMultiModalManager() const
    {
        return multiModalManager_;
    }
#endif

    void SetWindowOnShow();

    void SetWindowOnHide();

    void OnShow() override;

    void OnHide() override;

    void MarkForcedRefresh()
    {
        needForcedRefresh_ = true;
    }

    void SetTimeProvider(TimeProvider&& timeProvider);

    uint64_t GetTimeFromExternalTimer() override;

    void AddFontNode(const WeakPtr<RenderNode>& node);

    void RemoveFontNode(const WeakPtr<RenderNode>& node);

    void LoadSystemFont(const std::function<void()>& onFondsLoaded);

    const RefPtr<SharedTransitionController>& GetSharedTransitionController() const
    {
        return sharedTransitionController_;
    }

    const RefPtr<CardTransitionController>& GetCardTransitionController() const
    {
        return cardTransitionController_;
    }

    void SetClickPosition(const Offset& position) const;

    void RootLostFocus(BlurReason reason = BlurReason::FOCUS_SWITCH) const;

    void FlushFocus();

    void WindowFocus(bool isFocus) override;

    void ContainerModalUnFocus() override;

    void OnPageShow() override;

    double GetStatusBarHeight() const
    {
        return statusBarHeight_;
    }

    double GetNavigationBarHeight() const
    {
        return navigationBarHeight_;
    }

    void SetAppearingDuration(int32_t duration)
    {
        cardAppearingDuration_ = duration;
    }

    int32_t GetAppearingDuration() const
    {
        return cardAppearingDuration_;
    }

    void SetModalHeight(int32_t height)
    {
        modalHeight_ = height;
    }

    void SetModalColor(uint32_t color)
    {
        modalColor_ = color;
    }

    void MovePage(const Offset& rootRect, double offsetHeight);

    void SetBuildAfterCallback(const std::function<void()>& callback) override
    {
        buildAfterCallback_.emplace_back(callback);
    }

    void SetIsKeyEvent(bool isKeyEvent);

    bool IsKeyEvent() const
    {
        return isKeyEvent_;
    }

    void RefreshRootBgColor() const override;
    void AddToHoverList(const RefPtr<RenderNode>& node);

    using UpdateWindowBlurRegionHandler = std::function<void(const std::vector<std::vector<float>>&)>;

    void SetUpdateWindowBlurRegionHandler(UpdateWindowBlurRegionHandler handler)
    {
        updateWindowBlurRegionHandler_ = std::move(handler);
    }

    using DragEventHandler = std::function<void(const std::string&, const RefPtr<PixelMap>& pixmap)>;

    void SetDragEventHandler(DragEventHandler&& callback)
    {
        dragEventHandler_ = callback;
    }

    using InitDragEventListener = std::function<void()>;

    void SetInitDragListener(InitDragEventListener&& callback)
    {
        initDragEventListener_ = callback;
    }

    void UpdateWindowBlurRegion(
        int32_t id, RRect rRect, float progress, WindowBlurStyle style, const std::vector<RRect>& coords);

    void ClearWindowBlurRegion(int32_t id);

    bool IsBuildingFirstPage() const
    {
        return buildingFirstPage_;
    }

    using UpdateWindowBlurDrawOpHandler = std::function<void(void)>;

    void SetUpdateWindowBlurDrawOpHandler(UpdateWindowBlurDrawOpHandler handler)
    {
        updateWindowBlurDrawOpHandler_ = std::move(handler);
    }

    void NavigatePage(uint8_t type, const PageTarget& target, const std::string& params);

    void AddKeyFrame(
        float fraction, const RefPtr<Curve>& curve, const std::function<void()>& propertyCallback) override;

    void AddKeyFrame(float fraction, const std::function<void()>& propertyCallback) override;

    void SaveExplicitAnimationOption(const AnimationOption& option) override;

    void CreateExplicitAnimator(const std::function<void()>& onFinishEvent) override;

    void ClearExplicitAnimationOption() override;

    AnimationOption GetExplicitAnimationOption() const override;

    void FlushBuild() override;

    void SetUseLiteStyle(bool useLiteStyle)
    {
        useLiteStyle_ = useLiteStyle;
    }

    bool UseLiteStyle() const
    {
        return useLiteStyle_;
    }

    const Rect& GetDirtyRect() const
    {
        return dirtyRect_;
    }

    bool GetIsDeclarative() const override;

    bool IsForbidPlatformQuit() const
    {
        return forbidPlatformQuit_;
    }

    void SetForbidPlatformQuit(bool forbidPlatformQuit);

    void SetAppBgColor(const Color& color) override;

    void SetPhotoCachePath(const std::string& photoCachePath)
    {
        photoCachePath_ = photoCachePath;
    }

    const std::string& GetPhotoCachePath()
    {
        return photoCachePath_;
    }

    void SetScreenOnCallback(std::function<void(std::function<void()>&& func)>&& screenOnCallback)
    {
        screenOnCallback_ = std::move(screenOnCallback);
    }

    void SetScreenOffCallback(std::function<void(std::function<void()>&& func)>&& screenOffCallback)
    {
        screenOffCallback_ = std::move(screenOffCallback);
    }

    void AddScreenOnEvent(std::function<void()>&& func);
    void AddScreenOffEvent(std::function<void()>&& func);
    void AddAlignDeclarationNode(const RefPtr<RenderNode>& node);
    void AddLayoutTransitionNode(const RefPtr<RenderNode>& node);
    std::list<RefPtr<RenderNode>>& GetAlignDeclarationNodeList();
    void SetQueryIfWindowInScreenCallback(std::function<void()>&& func)
    {
        queryIfWindowInScreenCallback_ = std::move(func);
    }
    void SetIsWindowInScreen(bool isWindowInScreen)
    {
        isWindowInScreen_ = isWindowInScreen;
    }
    // This interface posts an async task to do async query and returns the result from previous query.
    bool IsWindowInScreen();
    void NotifyOnPreDraw() override;
    void AddNodesToNotifyOnPreDraw(const RefPtr<RenderNode>& renderNode);

    void UpdateNodesNeedDrawOnPixelMap();
    void SearchNodesNeedDrawOnPixelMap(const RefPtr<RenderNode>& renderNode);
    void NotifyDrawOnPixelMap();

    const RefPtr<RootElement>& GetRootElement() const
    {
        return rootElement_;
    }

    void SetAccessibilityEnabled(bool isEnabled)
    {
        isAccessibilityEnabled_ = isEnabled;
    }
    bool IsAccessibilityEnabled() const
    {
        return isAccessibilityEnabled_ || IsVisibleChangeNodeExists(-1);
    }

    bool IsVisibleChangeNodeExists(NodeId index) const;

    int32_t RegisterSurfaceChangedCallback(
        std::function<void(int32_t, int32_t, int32_t, int32_t, WindowSizeChangeReason)>&& callback)
    {
        if (callback) {
            surfaceChangedCallbackMap_.emplace(++callbackId_, std::move(callback));
            return callbackId_;
        }
        return 0;
    }

    void UnregisterSurfaceChangedCallback(int32_t callbackId)
    {
        surfaceChangedCallbackMap_.erase(callbackId);
    }

    int32_t RegisterSurfacePositionChangedCallback(std::function<void(int32_t, int32_t)>&& callback)
    {
        if (callback) {
            surfacePositionChangedCallbackMap_.emplace(++callbackId_, std::move(callback));
            return callbackId_;
        }
        return 0;
    }

    void UnregisterSurfacePositionChangedCallback(int32_t callbackId)
    {
        surfacePositionChangedCallbackMap_.erase(callbackId);
    }
    void StartSystemDrag(const std::string& str, const RefPtr<PixelMap>& pixmap);
    void InitDragListener();
    void OnDragEvent(const DragPointerEvent& pointerEvent, DragEventAction action,
        const RefPtr<NG::FrameNode>& node = nullptr) override;
    void SetPreTargetRenderNode(const RefPtr<DragDropEvent>& preDragDropNode);
    const RefPtr<DragDropEvent>& GetPreTargetRenderNode() const;
    void SetInitRenderNode(const RefPtr<RenderNode>& initRenderNode);
    const RefPtr<RenderNode>& GetInitRenderNode() const;

    void SetContextMenu(const RefPtr<Component>& contextMenu)
    {
        contextMenu_ = contextMenu;
    }

    void SetClipHole(double left, double top, double width, double height);

    const Rect& GetTransparentHole() const
    {
        return transparentHole_;
    }

    bool GetHasMeetSubWindowNode() const
    {
        return hasMeetSubWindowNode_;
    }

    void SetHasMeetSubWindowNode(bool hasMeetSubWindowNode)
    {
        hasMeetSubWindowNode_ = hasMeetSubWindowNode;
    }

    bool GetHasClipHole() const
    {
        return hasClipHole_;
    }

    void SetHasClipHole(bool hasClipHole)
    {
        hasClipHole_ = hasClipHole;
    }

    bool GetIsHoleValid() const
    {
        return isHoleValid_;
    }

    void SetRSUIDirector(std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUIDirector);

    std::shared_ptr<OHOS::Rosen::RSUIDirector> GetRSUIDirector();

    bool IsShiftDown() const
    {
        return isShiftDown_;
    }

    void MarkIsShiftDown(bool isShiftDown)
    {
        isShiftDown_ = isShiftDown;
    }

    bool IsCtrlDown() const
    {
        return isCtrlDown_;
    }

    void MarkIsCtrlDown(bool isCtrlDown)
    {
        isCtrlDown_ = isCtrlDown;
    }

    bool IsKeyboardA() const
    {
        return isKeyboardA_;
    }

    void MarkIsKeyboardA(bool isKeyboardA)
    {
        isKeyboardA_ = isKeyboardA;
    }

    void SetShortcutKey(const KeyEvent& event);

    void SetTextOverlayManager(const RefPtr<TextOverlayManager>& textOverlayManager)
    {
        textOverlayManager_ = textOverlayManager;
    }

    RefPtr<TextOverlayManager> GetTextOverlayManager() const
    {
        return textOverlayManager_;
    }

    void SubscribeCtrlA(SubscribeCtrlACallback callback)
    {
        subscribeCtrlA_ = std::move(callback);
    }

    void SetClipboardCallback(const std::function<void(const std::string&)>& callback)
    {
        clipboardCallback_ = callback;
    }

    void ProcessDragEvent(
        const RefPtr<RenderNode>& renderNode, const RefPtr<DragEvent>& event, const Point& globalPoint);
    void ProcessDragEventEnd(
        const RefPtr<RenderNode>& renderNode, const RefPtr<DragEvent>& event, const Point& globalPoint);

    // restore
    void RestoreNodeInfo(std::unique_ptr<JsonValue> nodeInfo) override;
    std::unique_ptr<JsonValue> GetStoredNodeInfo() override;
    void StoreNode(int32_t restoreId, const WeakPtr<RenderElement>& node);
    std::string GetRestoreInfo(int32_t restoreId);

    bool GetIsTabKeyPressed() const
    {
        return isTabKeyPressed_;
    }

    bool GetIsFocusingByTab() const
    {
        return isFocusingByTab_;
    }

    void SetIsFocusingByTab(bool isFocusingByTab)
    {
        isFocusingByTab_ = isFocusingByTab;
    }

    void AddVisibleAreaChangeNode(const ComposeId& nodeId, double ratio, const VisibleRatioCallback& callback);

    bool GetOnShow() const override
    {
        return onShow_;
    }

    void AddRectCallback(OutOfRectGetRectCallback& getRectCallback, OutOfRectTouchCallback& touchCallback,
        OutOfRectMouseCallback& mouseCallback)
    {
        rectCallbackList_.emplace_back(RectCallback(getRectCallback, touchCallback, mouseCallback));
    }

    void SetRootRect(double width, double height, double offset = 0.0) override
    {
        SetRootSizeWithWidthHeight(width, height, offset);
    }

    void SetAppTitle(const std::string& title) override;
    void SetAppIcon(const RefPtr<PixelMap>& icon) override;
    void FlushMessages() override;

    bool IsDensityChanged() const override
    {
        return isDensityUpdate_;
    }

protected:
    bool OnDumpInfo(const std::vector<std::string>& params) const override;
    void FlushVsync(uint64_t nanoTimestamp, uint32_t frameCount) override;
    void FlushPipelineWithoutAnimation() override;
    void DispatchDisplaySync(uint64_t nanoTimestamp) override;
    void FlushAnimation(uint64_t nanoTimestamp) override;
    void FlushReload(const ConfigurationChange& configurationChange, bool fullUpdate = true) override;
    void FlushReloadTransition() override;
    void FlushUITasks(bool triggeredByImplicitAnimation = false) override
    {
        FlushLayout();
    }

    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUIDirector_;
    bool hasIdleTasks_ = false;

private:
    void FlushLayout();
    void FlushGeometryProperties();
    void FlushRender();
    void FlushRenderFinish();
    void FireVisibleChangeEvent();
    void FlushPredictLayout(int64_t deadline);
    void FlushPostAnimation();
    void FlushPageUpdateTasks();
    void ProcessPreFlush();
    void ProcessPostFlush();
    void SetRootSizeWithWidthHeight(int32_t width, int32_t height, int32_t offset = 0);
    void FlushBuildAndLayoutBeforeSurfaceReady();
    void FlushAnimationTasks();
    void DumpAccessibility(const std::vector<std::string>& params) const;
    void FlushWindowBlur();
    void MakeThreadStuck(const std::vector<std::string>& params) const;
    void ExitAnimation();
    void CreateGeometryTransition();
    void CorrectPosition();
    void CreateTouchEventOnZoom(const AxisEvent& event);
    void HandleVisibleAreaChangeEvent();
    void FlushTouchEvents();
    bool OnKeyEvent(const NonPointerEvent& nonPointerEvent);

    template<typename T>
    struct NodeCompare {
        bool operator()(const T& nodeLeft, const T& nodeRight) const
        {
            if (nodeLeft->GetDepth() < nodeRight->GetDepth()) {
                return true;
            }
            if (nodeLeft->GetDepth() == nodeRight->GetDepth()) {
                return nodeLeft < nodeRight;
            }
            return false;
        }
    };

    template<typename T>
    struct NodeCompareWeak {
        bool operator()(const T& nodeLeftWeak, const T& nodeRightWeak) const
        {
            auto nodeLeft = nodeLeftWeak.Upgrade();
            auto nodeRight = nodeRightWeak.Upgrade();
            if (!nodeLeft || !nodeRight) {
                return true;
            }
            auto compare = NodeCompare<decltype(nodeLeft)>();
            return compare(nodeLeft, nodeRight);
        }
    };

    Rect dirtyRect_;
    uint32_t nextScheduleTaskId_ = 0;
    std::unordered_map<uint32_t, RefPtr<ScheduleTask>> scheduleTasks_;
    std::unordered_map<ComposeId, std::list<RefPtr<ComposedElement>>> composedElementMap_;
    std::set<WeakPtr<Element>, NodeCompareWeak<WeakPtr<Element>>> dirtyElements_;
    std::set<WeakPtr<Element>, NodeCompareWeak<WeakPtr<Element>>> needRebuildFocusElement_;
    std::set<RefPtr<RenderNode>, NodeCompare<RefPtr<RenderNode>>> dirtyRenderNodes_;
    std::set<RefPtr<RenderNode>, NodeCompare<RefPtr<RenderNode>>> dirtyRenderNodesInOverlay_;
    std::set<RefPtr<RenderNode>, NodeCompare<RefPtr<RenderNode>>> dirtyLayoutNodes_;
    std::set<RefPtr<RenderNode>, NodeCompare<RefPtr<RenderNode>>> predictLayoutNodes_;
    std::set<RefPtr<RenderNode>, NodeCompare<RefPtr<RenderNode>>> needPaintFinishNodes_;
    std::set<RefPtr<RenderNode>, NodeCompare<RefPtr<RenderNode>>> geometryChangedNodes_;
    std::set<RefPtr<RenderNode>> nodesToNotifyOnPreDraw_;
    std::set<RefPtr<RenderNode>> nodesNeedDrawOnPixelMap_;
    std::list<RefPtr<FlushEvent>> postFlushListeners_;
    std::list<RefPtr<FlushEvent>> postAnimationFlushListeners_;
    std::list<RefPtr<FlushEvent>> preFlushListeners_;
    RefPtr<FocusAnimationManager> focusAnimationManager_;

    RefPtr<RootElement> rootElement_;
    WeakPtr<FocusNode> dirtyFocusNode_;
    WeakPtr<FocusNode> dirtyFocusScope_;
    std::list<std::function<void()>> buildAfterCallback_;
    RefPtr<RenderFactory> renderFactory_;
    UpdateWindowBlurRegionHandler updateWindowBlurRegionHandler_;
    UpdateWindowBlurDrawOpHandler updateWindowBlurDrawOpHandler_;
    DragEventHandler dragEventHandler_;
    InitDragEventListener initDragEventListener_;
    std::vector<KeyCode> pressedKeyCodes;
    TouchEvent zoomEventA_;
    TouchEvent zoomEventB_;
    bool isOnScrollZoomEvent_ = false;
    bool isKeyCtrlPressed_ = false;

    Rect transparentHole_;
    // use for traversing clipping hole
    bool hasMeetSubWindowNode_ = false;
    // use for judge clip hole status
    bool hasClipHole_ = false;
    // judge hole is valid
    bool isHoleValid_ = false;

#ifndef WEARABLE_PRODUCT
    RefPtr<MultiModalManager> multiModalManager_ = MakeRefPtr<MultiModalManager>();
#endif
    RefPtr<SharedTransitionController> sharedTransitionController_;
    RefPtr<CardTransitionController> cardTransitionController_;
    RefPtr<TextOverlayManager> textOverlayManager_;
    EventTrigger eventTrigger_;

    WeakPtr<RenderNode> requestedRenderNode_;
    // Make page update tasks pending here to avoid block receiving vsync.
    std::queue<std::function<void()>> pageUpdateTasks_;
    // strong deactivate element and it's id.
    std::map<int32_t, RefPtr<Element>> deactivateElements_;

    RefPtr<Component> contextMenu_;

    // window blur region
    std::unordered_map<int32_t, WindowBlurInfo> windowBlurRegions_;

    std::list<RefPtr<RenderNode>> alignDeclarationNodeList_;
    std::set<RefPtr<RenderNode>> layoutTransitionNodeSet_;

    std::function<void()> queryIfWindowInScreenCallback_;
    std::atomic<bool> isWindowInScreen_ = true;

    RefPtr<DragDropEvent> preTargetRenderNode_;

    bool isSurfaceReady_ = false;

    int32_t cardAppearingDuration_ = 0;
    double statusBarHeight_ = 0.0;     // dp
    double navigationBarHeight_ = 0.0; // dp
    bool needForcedRefresh_ = false;
    bool isFlushingAnimation_ = false;
    bool isMoving_ = false;
    std::atomic<bool> onShow_ = true;
    bool isKeyEvent_ = false;
    bool needWindowBlurRegionRefresh_ = false;
    bool useLiteStyle_ = false;
    bool isFirstLoaded_ = true;
    bool isDensityUpdate_ = false;
    uint64_t flushAnimationTimestamp_ = 0;
    TimeProvider timeProvider_;
    int32_t modalHeight_ = 0;
    int32_t hoverNodeId_ = DEFAULT_HOVER_ENTER_ANIMATION_ID;
    uint32_t modalColor_ = 0x00000000;
    std::list<RefPtr<RenderNode>> hoverNodes_;
    std::function<void(std::function<void()>&&)> screenOffCallback_;
    std::function<void(std::function<void()>&&)> screenOnCallback_;
#if defined(ENABLE_NATIVE_VIEW)
    int32_t frameCount_ = 0;
#endif

    bool isFirstPage_ = true;
    bool buildingFirstPage_ = false;
    bool forbidPlatformQuit_ = false;
    std::string photoCachePath_;
    AnimationOption explicitAnimationOption_;
    std::map<int32_t, RefPtr<Animator>> explicitAnimators_;
    bool isAccessibilityEnabled_ = false;

    int32_t callbackId_ = 0;
    SurfaceChangedCallbackMap surfaceChangedCallbackMap_;
    SurfacePositionChangedCallbackMap surfacePositionChangedCallbackMap_;

    bool isShiftDown_ = false;
    bool isCtrlDown_ = false;
    bool isKeyboardA_ = false;
    bool isTabKeyPressed_ = false;
    bool isFocusingByTab_ = false;
    SubscribeCtrlACallback subscribeCtrlA_;

    std::function<void()> nextFrameLayoutCallback_ = nullptr;
    Size selectedItemSize_ { 0.0, 0.0 };
    int32_t selectedIndex_ = -1;
    int32_t insertIndex_ = -1;
    RefPtr<RenderNode> initRenderNode_;
    std::string customDragInfo_;
    std::string selectedText_;
    std::string imageSrc_;
    Offset pageOffset_;
    Offset rootOffset_;

    std::unordered_map<int32_t, WeakPtr<RenderElement>> storeNode_;
    std::unordered_map<int32_t, std::string> restoreNodeInfo_;

    std::unordered_map<ComposeId, std::list<VisibleCallbackInfo>> visibleAreaChangeNodes_;

    std::vector<RectCallback> rectCallbackList_;
    std::list<TouchEvent> touchEvents_;

    ACE_DISALLOW_COPY_AND_MOVE(PipelineContext);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_CONTEXT_H
