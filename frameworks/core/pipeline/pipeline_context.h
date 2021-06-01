/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "base/geometry/dimension.h"
#include "base/geometry/rect.h"
#include "base/memory/ace_type.h"
#include "base/resource/asset_manager.h"
#include "base/resource/shared_image_manager.h"
#include "base/thread/task_executor.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/accessibility/accessibility_manager.h"
#include "core/animation/flush_event.h"
#include "core/animation/page_transition_listener.h"
#include "core/animation/schedule_task.h"
#include "core/common/draw_delegate.h"
#include "core/common/event_manager.h"
#include "core/common/focus_animation_manager.h"
#include "core/common/platform_bridge.h"
#include "core/common/platform_res_register.h"
#include "core/components/common/properties/color.h"
#include "core/components/page/page_component.h"
#include "core/components/theme/theme_manager.h"
#include "core/event/event_trigger.h"
#include "core/image/image_cache.h"
#include "core/pipeline/base/composed_component.h"
#include "core/pipeline/base/factories/render_factory.h"
#ifndef WEARABLE_PRODUCT
#include "core/event/multimodal/multimodal_manager.h"
#include "core/event/multimodal/multimodal_subscriber.h"
#endif

namespace OHOS::Ace {

class CardTransitionController;
class ComposedElement;
class FontManager;
class Frontend;
enum class FrontendType;
class OverlayElement;
class RenderNode;
class RenderFocusAnimation;
class RootElement;
class SharedTransitionController;
class StageElement;
class StackElement;
class Window;
class StageElement;
class Animator;
class ManagerInterface;
class AccessibilityManager;
struct DialogProperties;

struct WindowBlurInfo {
    float progress_;
    WindowBlurStyle style_;
    RRect innerRect_;
    std::vector<RRect> coords_;
};

class ACE_EXPORT PipelineContext final : public AceType {
    DECLARE_ACE_TYPE(PipelineContext, AceType);

public:
    static constexpr int32_t DEFAULT_HOVER_ENTER_ANIMATION_ID = -1;
    using TimeProvider = std::function<int64_t(void)>;
    using OnPageShowCallBack = std::function<void()>;
    using AnimationCallback = std::function<void()>;
    PipelineContext(std::unique_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
        RefPtr<AssetManager> assetManager, RefPtr<PlatformResRegister> platformResRegister,
        const RefPtr<Frontend>& frontend, int32_t instanceId);
    ~PipelineContext() override = default;

    RefPtr<Element> SetupRootElement();

    bool ShowDialog(const DialogProperties& dialogProperties, bool isRightToLeft);

    void GetBoundingRectData(int32_t nodeId, Rect& rect);

    void PushPage(const RefPtr<PageComponent>& pageComponent);

    bool CanPushPage();

    void PopPage();

    void PopToPage(int32_t pageId);

    bool CanPopPage();

    void ReplacePage(const RefPtr<PageComponent>& pageComponent);

    bool CanReplacePage();

    bool ClearInvisiblePages();

    bool CallRouterBackToPopPage();

    void Dump(const std::vector<std::string>& params) const;

    RefPtr<StackElement> GetLastStack() const;

    RefPtr<PageElement> GetLastPage() const;

    RefPtr<RenderNode> GetLastPageRender() const;

    void ScheduleUpdate(const RefPtr<ComposedComponent>& composed);

    void AddComposedElement(const ComposeId& id, const RefPtr<ComposedElement>& element);

    void RemoveComposedElement(const ComposeId& id, const RefPtr<ComposedElement>& element);

    void AddDirtyElement(const RefPtr<Element>& dirtyElement);

    void AddNeedRebuildFocusElement(const RefPtr<Element>& focusElement);

    void AddDirtyRenderNode(const RefPtr<RenderNode>& renderNode, bool overlay = false);

    void AddDirtyLayoutNode(const RefPtr<RenderNode>& renderNode);

    void AddPredictLayoutNode(const RefPtr<RenderNode>& renderNode);

    void AddPreFlushListener(const RefPtr<FlushEvent>& listener);

    void AddPostFlushListener(const RefPtr<FlushEvent>& listener);

    void AddPageUpdateTask(std::function<void()>&& task, bool directExecute = false);

    void SetRequestedRotationNode(const WeakPtr<RenderNode>& renderNode);

    void RemoveRequestedRotationNode(const WeakPtr<RenderNode>& renderNode);

    // add schedule task and return the unique mark id.
    uint32_t AddScheduleTask(const RefPtr<ScheduleTask>& task);

    // remove schedule task by id.
    void RemoveScheduleTask(uint32_t id);

    // Called by view when touch event received.
    void OnTouchEvent(const TouchPoint& point);

    // Called by container when key event received.
    // if return false, then this event needs platform to handle it.
    bool OnKeyEvent(const KeyEvent& event);

    // Called by view when mouse event received.
    void OnMouseEvent(const MouseEvent& event);

    // Called by container when rotation event received.
    // if return false, then this event needs platform to handle it.
    bool OnRotationEvent(const RotationEvent& event) const;

    // Called by window when received vsync signal.
    void OnVsyncEvent(uint64_t nanoTimestamp, uint32_t frameCount);

    // Called by view when idle event.
    void OnIdle(int64_t deadline);

    void OnActionEvent(const std::string& action);

    // Set card position for barrierfree
    void SetCardViewPosition(int id, float offsetX, float offsetY);

    void SetCardViewAccessibilityParams(const std::string& key, bool focus);

    void FlushPipelineImmediately();

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

    void OnSurfaceChanged(int32_t width, int32_t height);

    void OnSurfaceDensityChanged(double density);

    void OnSystemBarHeightChanged(double statusBar, double navigationBar);

    void OnSurfaceDestroyed();

    RefPtr<Frontend> GetFrontend() const;

    FrontendType GetFrontendType() const
    {
        return frontendType_;
    }

    RefPtr<TaskExecutor> GetTaskExecutor() const
    {
        return taskExecutor_;
    }

    RefPtr<AssetManager> GetAssetManager() const
    {
        return assetManager_;
    }

    RefPtr<PlatformResRegister> GetPlatformResRegister() const
    {
        return platformResRegister_;
    }

    Window* GetWindow()
    {
        return window_.get();
    }

    WindowModal GetWindowModal() const
    {
        return windowModal_;
    }

    bool IsFullScreenModal() const
    {
        return windowModal_ == WindowModal::NORMAL || windowModal_ == WindowModal::SEMI_MODAL_FULL_SCREEN ||
               isFullWindow_;
    }

    using FinishEventHandler = std::function<void()>;
    void SetFinishEventHandler(FinishEventHandler&& listener)
    {
        finishEventHandler_ = std::move(listener);
    }

    using ActionEventHandler = std::function<void(const std::string& action)>;
    void SetActionEventHandler(ActionEventHandler&& listener)
    {
        actionEventHandler_ = std::move(listener);
    }

    // SemiModal and DialogModal have their own enter/exit animation and will exit after animation done.
    void Finish(bool autoFinish = true) const;

    void RequestFullWindow(int32_t duration);

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

    float GetViewScale() const
    {
        return viewScale_;
    }

    // Get the dp scale which used to covert dp to logic px.
    double GetDipScale() const
    {
        return dipScale_;
    }

    double GetRootHeight() const
    {
        return rootHeight_;
    }

    double GetRootWidth() const
    {
        return rootWidth_;
    }

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

    void ClearImageCache();

    RefPtr<ImageCache> GetImageCache() const;

    double NormalizeToPx(const Dimension& dimension) const;

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

    RefPtr<StageElement> GetStageElement() const;

    RefPtr<ComposedElement> GetComposedElementById(const ComposeId& id);

    void SendCallbackMessageToFrontend(const std::string& callbackId, const std::string& data);

    void SendEventToFrontend(const EventMarker& eventMarker);

    void SendEventToFrontend(const EventMarker& eventMarker, const std::string& param);

    bool AccessibilityRequestFocus(const ComposeId& id);

    bool RequestFocus(const RefPtr<Element>& targetElement);

    RefPtr<AccessibilityManager> GetAccessibilityManager() const;

    void SendEventToAccessibility(const AccessibilityEvent& accessibilityEvent);

    BaseId::IdType AddPageTransitionListener(const PageTransitionListenable::CallbackFuncType& funcObject);

    const RefPtr<OverlayElement> GetOverlayElement() const;

    void RemovePageTransitionListener(typename BaseId::IdType id);

    void ClearPageTransitionListeners();

    void Destroy();

    const RefPtr<FontManager>& GetFontManager() const
    {
        return fontManager_;
    }

    void RegisterFont(const std::string& familyName, const std::string& familySrc);

    void CanLoadImage(const std::string& src, const std::map<std::string, EventMarker>& callbacks);

    void SetAnimationCallback(AnimationCallback&& callback);

    bool IsLastPage();

    void SetRootSize(double density, int32_t width, int32_t height);

    RefPtr<Element> GetDeactivateElement(int32_t componentId) const;

    void ClearDeactivateElements();

    void AddDeactivateElement(const int32_t id, const RefPtr<Element>& element);

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

    void OnShow();

    void OnHide();
#endif

    void MarkForcedRefresh()
    {
        needForcedRefresh_ = true;
    }

    void SetTimeProvider(TimeProvider&& timeProvider);

    uint64_t GetTimeFromExternalTimer();

    void SetFontScale(float fontScale);

    void AddFontNode(const WeakPtr<RenderNode>& node);

    void RemoveFontNode(const WeakPtr<RenderNode>& node);

    float GetFontScale() const
    {
        return fontScale_;
    }

    void UpdateFontWeightScale();

    const RefPtr<SharedTransitionController>& GetSharedTransitionController() const
    {
        return sharedTransitionController_;
    }

    const RefPtr<CardTransitionController>& GetCardTransitionController() const
    {
        return cardTransitionController_;
    }

    void SetClickPosition(const Offset& position) const;

    void SetTextFieldManager(const RefPtr<ManagerInterface>& manager);

    void RootLostFocus() const;

    void FlushFocus();

    void SetIsRightToLeft(bool isRightToLeft)
    {
        isRightToLeft_ = isRightToLeft;
    }

    bool IsRightToLeft() const
    {
        return isRightToLeft_;
    }

    const RefPtr<PlatformBridge>& GetMessageBridge() const
    {
        return messageBridge_;
    }
    void SetMessageBridge(const RefPtr<PlatformBridge>& messageBridge)
    {
        messageBridge_ = messageBridge;
    }

    void SetOnPageShow(OnPageShowCallBack&& onPageShowCallBack);

    void OnPageShow();

    double GetStatusBarHeight() const
    {
        return statusBarHeight_;
    }

    double GetNavigationBarHeight() const
    {
        return navigationBarHeight_;
    }

    void SetWindowModal(WindowModal modal)
    {
        windowModal_ = modal;
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

    void SetDrawDelegate(std::unique_ptr<DrawDelegate> delegate)
    {
        drawDelegate_ = std::move(delegate);
    }

    void SetBuildAfterCallback(const std::function<void()>& callback)
    {
        buildAfterCallback_.emplace_back(callback);
    }

    RefPtr<ThemeManager> GetThemeManager() const
    {
        return themeManager_;
    }

    void SetIsKeyEvent(bool isKeyEvent);

    bool IsKeyEvent() const
    {
        return isKeyEvent_;
    }

    void SetIsJsCard(bool isJsCard)
    {
        isJsCard_ = isJsCard;
    }

    bool IsJsCard() const
    {
        return isJsCard_;
    }

    void RefreshRootBgColor() const;
    void AddToHoverList(const RefPtr<RenderNode>& node);

    using UpdateWindowBlurRegionHandler = std::function<void(const std::vector<std::vector<float>>&)>;

    void SetUpdateWindowBlurRegionHandler(UpdateWindowBlurRegionHandler handler)
    {
        updateWindowBlurRegionHandler_ = std::move(handler);
    }

    void UpdateWindowBlurRegion(
        int32_t id, RRect rRect, float progress, WindowBlurStyle style, const std::vector<RRect>& coords);

    void ClearWindowBlurRegion(int32_t id);

    bool IsBuildingFirstPage() const
    {
        return buildingFirstPage_;
    }

    void DrawLastFrame();

    const RefPtr<SharedImageManager>& GetSharedImageManager() const
    {
        return sharedImageManager_;
    }

    void SetSharedImageManager(const RefPtr<SharedImageManager>& sharedImageManager)
    {
        sharedImageManager_ = sharedImageManager;
    }

    using UpdateWindowBlurDrawOpHandler = std::function<void(void)>;

    void SetUpdateWindowBlurDrawOpHandler(UpdateWindowBlurDrawOpHandler handler)
    {
        updateWindowBlurDrawOpHandler_ = std::move(handler);
    }

    void NavigatePage(uint8_t type, const std::string& uri);

    int32_t GetInstanceId() const
    {
        return instanceId_;
    }

    void SetUseLiteStyle(bool useLiteStyle)
    {
        useLiteStyle_ = useLiteStyle;
    }

    bool UseLiteStyle()
    {
        return useLiteStyle_;
    }

    const Rect& GetDirtyRect() const
    {
        return dirtyRect_;
    }

    bool GetIsDeclarative() const;

    bool IsForbidePlatformQuit() const
    {
        return forbidePlatformQuit_;
    }

    void SetForbidePlatformQuit(bool forbidePlatformQuit)
    {
        forbidePlatformQuit_ = forbidePlatformQuit;
    }

    int32_t GetWindowId() const
    {
        return windowId_;
    }

    void SetWindowId(int32_t windowId)
    {
        windowId_ = windowId;
    }

private:
    void FlushPipelineWithoutAnimation();
    void FlushBuild();
    void FlushLayout();
    void FlushRender();
    void FlushPredictLayout();
    void FlushAnimation(uint64_t nanoTimestamp);
    void FlushPageUpdateTasks();
    void ProcessPreFlush();
    void ProcessPostFlush();
    void SetRootSizeWithWidthHeight(int32_t width, int32_t height);
    void SetRootRect(double width, double height) const;
    void FlushBuildAndLayoutBeforeSurfaceReady();
    void FlushAnimationTasks();
    void DumpAccessibility(const std::vector<std::string>& params) const;
    void FlushWindowBlur();
    void MakeThreadStuck(const std::vector<std::string>& params) const;
    void DumpFrontend() const;
    void HandleMouseInputEvent(const MouseEvent& event);

    template<typename T>
    struct NodeCompare {
        bool operator()(const T& nodeLeft, const T& nodeRight)
        {
            if (nodeLeft->GetDepth() < nodeRight->GetDepth()) {
                return true;
            } else if (nodeLeft->GetDepth() == nodeRight->GetDepth()) {
                return nodeLeft < nodeRight;
            }
            return false;
        }
    };

    template<typename T>
    struct NodeCompareWeak {
        bool operator()(const T& nodeLeftWeak, const T& nodeRightWeak)
        {
            auto nodeLeft = nodeLeftWeak.Upgrade();
            auto nodeRight = nodeRightWeak.Upgrade();
            if (!nodeLeft || !nodeRight) {
                return false;
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
    std::list<RefPtr<FlushEvent>> postFlushListeners_;
    std::list<RefPtr<FlushEvent>> preFlushListeners_;
    std::unique_ptr<Window> window_;
    RefPtr<FocusAnimationManager> focusAnimationManager_;
    RefPtr<TaskExecutor> taskExecutor_;
    RefPtr<AssetManager> assetManager_;
    RefPtr<PlatformResRegister> platformResRegister_;
    RefPtr<RootElement> rootElement_;
    RefPtr<FocusNode> dirtyFocusNode_;
    RefPtr<FocusNode> dirtyFocusScope_;
    WeakPtr<Frontend> weakFrontend_;
    RefPtr<ImageCache> imageCache_;
    RefPtr<FontManager> fontManager_;
    RefPtr<ThemeManager> themeManager_;
    RefPtr<SharedImageManager> sharedImageManager_;
    std::list<std::function<void()>> buildAfterCallback_;
    RefPtr<RenderFactory> renderFactory_;
    UpdateWindowBlurRegionHandler updateWindowBlurRegionHandler_;
    UpdateWindowBlurDrawOpHandler updateWindowBlurDrawOpHandler_;

#ifndef WEARABLE_PRODUCT
    RefPtr<MultiModalManager> multiModalManager_ = MakeRefPtr<MultiModalManager>();
#endif
    RefPtr<SharedTransitionController> sharedTransitionController_;
    RefPtr<CardTransitionController> cardTransitionController_;
    EventManager eventManager_;
    EventTrigger eventTrigger_;
    FinishEventHandler finishEventHandler_;
    ActionEventHandler actionEventHandler_;
    StatusBarEventHandler statusBarBgColorEventHandler_;
    PopupEventHandler popupEventHandler_;
    RouterBackEventHandler routerBackEventHandler_;
    RefPtr<ManagerInterface> textFieldManager_;
    RefPtr<PlatformBridge> messageBridge_;
    WeakPtr<RenderNode> requestedRenderNode_;
    // Make page update tasks pending here to avoid block receiving vsync.
    std::queue<std::function<void()>> pageUpdateTasks_;
    // strong deactivate element and it's id.
    std::map<int32_t, RefPtr<Element>> deactivateElements_;

    // animation frame callback
    AnimationCallback animationCallback_;

    // window blur region
    std::unordered_map<int32_t, WindowBlurInfo> windowBlurRegions_;

    bool isRightToLeft_ = false;
    bool isSurfaceReady_ = false;
    float viewScale_ = 1.0f;
    float fontScale_ = 1.0f;
    double density_ = 1.0;
    double dipScale_ = 1.0;
    double statusBarHeight_ = 0.0;     // dp
    double navigationBarHeight_ = 0.0; // dp
    double rootHeight_ = 0.0;
    double rootWidth_ = 0.0;
    bool needForcedRefresh_ = false;
    bool isFlushingAnimation_ = false;
    bool hasIdleTasks_ = false;
    bool isMoving_ = false;
    bool onShow_ = true;
    bool isKeyEvent_ = false;
    bool needWindowBlurRegionRefresh_ = false;
    bool isJsCard_ = false;
    bool useLiteStyle_ = false;
    uint64_t flushAnimationTimestamp_ = 0;
    TimeProvider timeProvider_;
    OnPageShowCallBack onPageShowCallBack_;
    WindowModal windowModal_ = WindowModal::NORMAL;
    int32_t modalHeight_ = 0;
    int32_t hoverNodeId_ = DEFAULT_HOVER_ENTER_ANIMATION_ID;
    uint32_t modalColor_ = 0x00000000;
    bool isFullWindow_ = false;
    std::list<RefPtr<RenderNode>> hoverNodes_;
    std::unique_ptr<DrawDelegate> drawDelegate_;
#if defined(ENABLE_NATIVE_VIEW)
    int32_t frameCount_ = 0;
#endif

    int32_t width_ = 0;
    int32_t height_ = 0;
    bool isFirstPage_ = true;
    bool buildingFirstPage_ = false;
    bool forbidePlatformQuit_ = false;
    FrontendType frontendType_;
    int32_t instanceId_ = 0;
    int32_t windowId_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(PipelineContext);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_CONTEXT_H
