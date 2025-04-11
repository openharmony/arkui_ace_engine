/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_CONTEXT_H

#include <cstdint>
#include <functional>
#include <list>
#include <unordered_map>
#include <utility>

#include "interfaces/inner_api/ace/arkui_rect.h"

#include "base/geometry/ng/rect_t.h"
#include "base/log/frame_info.h"
#include "base/log/frame_report.h"
#include "base/memory/referenced.h"
#include "base/utils/device_config.h"
#include "base/view_data/view_data_wrap.h"
#include "core/accessibility/accessibility_manager_ng.h"
#include "core/common/ai/ai_write_adapter.h"
#include "core/common/frontend.h"
#include "core/common/thp_extra_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/manager/avoid_info/avoid_info_manager.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/form_event/form_event_manager.h"
#include "core/components_ng/manager/form_gesture/form_gesture_manager.h"
#include "core/components_ng/manager/form_visible/form_visible_manager.h"
#include "core/components_ng/manager/frame_rate/frame_rate_manager.h"
#include "core/components_ng/manager/full_screen/full_screen_manager.h"
#include "core/components_ng/manager/memory/memory_manager.h"
#include "core/components_ng/manager/navigation/navigation_manager.h"
#include "core/components_ng/manager/post_event/post_event_manager.h"
#include "core/components_ng/manager/privacy_sensitive/privacy_sensitive_manager.h"
#include "core/components_ng/manager/safe_area/safe_area_manager.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/manager/shared_overlay/shared_overlay_manager.h"
#include "core/components_ng/manager/toolbar/toolbar_manager.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/ui_extension/ui_extension_manager.h"
#endif
#include "core/common/ace_translate_manager.h"
#include "core/components_ng/manager/focus/focus_manager.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/recycle_view/recycle_manager.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/web/itouch_event_callback.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/pipeline/pipeline_base.h"
namespace OHOS::Ace::Kit {
class UIContext;
class UIContextImpl;
}

namespace OHOS::Ace::NG {

using VsyncCallbackFun = std::function<void()>;
using FrameCallbackFunc = std::function<void(uint64_t nanoTimestamp)>;
using FrameCallbackFuncFromCAPI = std::function<void(uint64_t nanoTimestamp, uint32_t frameCount)>;

enum class MockFlushEventType : int32_t {
    REJECT = -1,
    NONE = 0,
    EXECUTE = 1,
};
class ACE_FORCE_EXPORT PipelineContext : public PipelineBase {
    DECLARE_ACE_TYPE(NG::PipelineContext, PipelineBase);

public:
    using SurfaceChangedCallbackMap =
        std::unordered_map<int32_t, std::function<void(int32_t, int32_t, int32_t, int32_t, WindowSizeChangeReason)>>;
    using SurfacePositionChangedCallbackMap = std::unordered_map<int32_t, std::function<void(int32_t, int32_t)>>;
    using FoldStatusChangedCallbackMap = std::unordered_map<int32_t, std::function<void(FoldStatus)>>;
    using HalfFoldHoverChangedCallbackMap = std::unordered_map<int32_t, std::function<void(bool)>>;
    using FoldDisplayModeChangedCallbackMap = std::unordered_map<int32_t, std::function<void(FoldDisplayMode)>>;
    using TransformHintChangedCallbackMap = std::unordered_map<int32_t, std::function<void(uint32_t)>>;
    using PredictTask = std::function<void(int64_t, bool)>;
    using RotationEndCallbackMap = std::unordered_map<int32_t, std::function<void()>>;
    PipelineContext(std::shared_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
        RefPtr<AssetManager> assetManager, RefPtr<PlatformResRegister> platformResRegister,
        const RefPtr<Frontend>& frontend, int32_t instanceId);
    PipelineContext(std::shared_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
        RefPtr<AssetManager> assetManager, const RefPtr<Frontend>& frontend, int32_t instanceId);
    PipelineContext();

    ~PipelineContext() override = default;

    static RefPtr<PipelineContext> GetCurrentContext();

    static RefPtr<PipelineContext> GetCurrentContextSafely();

    static RefPtr<PipelineContext> GetCurrentContextSafelyWithCheck();

    static PipelineContext* GetCurrentContextPtrSafely();

    static PipelineContext* GetCurrentContextPtrSafelyWithCheck();


    static RefPtr<PipelineContext> GetMainPipelineContext();

    static RefPtr<PipelineContext> GetContextByContainerId(int32_t containerId);

    static float GetCurrentRootWidth();

    static float GetCurrentRootHeight();

    void MarkDirtyOverlay();

    void SetupRootElement() override;

    void SetupSubRootElement();

    bool NeedSoftKeyboard() override;

    void SetOnWindowFocused(const std::function<void()>& callback) override;

    const std::function<void()>& GetWindowFocusCallback() const
    {
        return focusOnNodeCallback_;
    }

    void SetSizeChangeByRotateCallback(const std::function<void(bool isRotate,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)>& callback)
    {
        sizeChangeByRotateCallback_ = callback;
    }

    void SetLinkJumpCallback(const std::function<void(const std::string& link)>& callback)
    {
        linkJumpCallback_ = callback;
    }

    void ExecuteLinkJumpCallback(const std::string& link)
    {
        linkJumpCallback_(link);
    }

    bool GetIsLinkJumpOpen()
    {
        return linkJumpCallback_ != nullptr;
    }

    void FireSizeChangeByRotateCallback(bool isRotate,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
    {
        if (sizeChangeByRotateCallback_) {
            sizeChangeByRotateCallback_(isRotate, rsTransaction);
        }
    }

    const RefPtr<FrameNode>& GetRootElement() const
    {
        return rootNode_;
    }

    void AddKeyFrame(float fraction, const RefPtr<Curve>& curve, const std::function<void()>& propertyCallback) override
    {}

    void AddKeyFrame(float fraction, const std::function<void()>& propertyCallback) override {}

    // add schedule task and return the unique mark id.
    uint32_t AddScheduleTask(const RefPtr<ScheduleTask>& task) override;

    // remove schedule task by id.
    void RemoveScheduleTask(uint32_t id) override;

    std::string GetCurrentPageNameCallback();

    void OnTouchEvent(const TouchEvent& point, const RefPtr<NG::FrameNode>& node, bool isSubPipe = false) override;

    void OnAccessibilityHoverEvent(const TouchEvent& point, const RefPtr<NG::FrameNode>& node) override;

    void OnPenHoverEvent(const TouchEvent& point, const RefPtr<NG::FrameNode>& node) override;

    void HandlePenHoverOut(const TouchEvent& point) override;

    void OnMouseMoveEventForAxisEvent(const MouseEvent& event, const RefPtr<NG::FrameNode>& node) override;

    void OnMouseEvent(const MouseEvent& event, const RefPtr<NG::FrameNode>& node) override;
    void DispatchMouseEvent(const MouseEvent& event, const RefPtr<FrameNode>& node);

    void OnAxisEvent(const AxisEvent& event, const RefPtr<NG::FrameNode>& node) override;

    // Called by view when touch event received.
    void OnTouchEvent(const TouchEvent& point, bool isSubPipe = false) override;

#if defined(SUPPORT_TOUCH_TARGET_TEST)
    // Used to determine whether the touched frameNode is the target
    bool OnTouchTargetHitTest(const TouchEvent& point, bool isSubPipe = false, const std::string& target = "") override;
#endif
    // Called by container when key event received.
    // if return false, then this event needs platform to handle it.
    bool OnNonPointerEvent(const NonPointerEvent& event) override;

    // ReDispatch KeyEvent from Web process.
    void ReDispatch(KeyEvent& keyEvent);

    // Called by view when mouse event received.
    void OnMouseEvent(const MouseEvent& event) override;

    // Do mouse event actively.
    void FlushMouseEvent();

    void HandleTouchHoverOut(const TouchEvent& point);

    void FlushMouseEventVoluntarily();

    void FlushMouseEventForHover();

    void FlushMouseEventInVsync();

    void SetDisplayWindowRectInfo(const Rect& displayWindowRectInfo) override;

    void SetWindowSizeChangeReason(WindowSizeChangeReason reason) override;

    void SetIsTransFlag(bool result);

    void OnFlushMouseEvent(TouchRestrict& touchRestrict);
    void OnFlushMouseEvent(const RefPtr<FrameNode> &node,
        const std::list<MouseEvent>& moseEvents, TouchRestrict& touchRestric);
    void DispatchMouseEvent(
        std::unordered_map<int, MouseEvent>& idToMousePoints,
        std::unordered_map<int32_t, MouseEvent> &newIdMousePoints,
        const std::list<MouseEvent> &mouseEvents,
        TouchRestrict& touchRestrict,
        const RefPtr<FrameNode> &node);
    void FlushDragEvents();
    void FlushDragEvents(const RefPtr<DragDropManager>& manager,
        std::string extraInfo,
        const RefPtr<FrameNode>& node,
        const std::list<DragPointerEvent>& pointEvent);
    void FlushDragEvents(const RefPtr<DragDropManager>& manager,
        std::unordered_map<int32_t, DragPointerEvent> newIdPoints,
        std::string& extraInfo,
        std::unordered_map<int, DragPointerEvent> &idToPoints,
        const RefPtr<FrameNode>& node);

    // Called by view when axis event received.
    void OnAxisEvent(const AxisEvent& event) override;

    // Called by container when rotation event received.
    // if return false, then this event needs platform to handle it.
    bool OnRotationEvent(const RotationEvent& event) const override
    {
        return false;
    }

    void OnDragEvent(const DragPointerEvent& pointerEvent, DragEventAction action,
        const RefPtr<NG::FrameNode>& node = nullptr) override;

    // Called by view when idle event.
    void OnIdle(int64_t deadline) override;

    void SetBuildAfterCallback(const std::function<void()>& callback) override
    {
        buildFinishCallbacks_.emplace_back(callback);
    }

    void SaveExplicitAnimationOption(const AnimationOption& option) override {}

    void CreateExplicitAnimator(const std::function<void()>& onFinishEvent) override {}

    void ClearExplicitAnimationOption() override {}

    AnimationOption GetExplicitAnimationOption() const override
    {
        return {};
    }

    bool HasOnAreaChangeNode(int32_t nodeId);

    void AddOnAreaChangeNode(int32_t nodeId);

    void RemoveOnAreaChangeNode(int32_t nodeId);

    void HandleOnAreaChangeEvent(uint64_t nanoTimestamp);

    // Just register notification, no need to update callback.
    void AddVisibleAreaChangeNode(const int32_t nodeId);

    void AddVisibleAreaChangeNode(const RefPtr<FrameNode>& node,
        const std::vector<double>& ratio, const VisibleRatioCallback& callback, bool isUserCallback = true,
        bool isCalculateInnerClip = false);
    void RemoveVisibleAreaChangeNode(int32_t nodeId);

    void HandleVisibleAreaChangeEvent(uint64_t nanoTimestamp);

    void HandleSubwindow(bool isShow);

    void Destroy() override;

    void OnShow() override;

    void OnHide() override;

    void WindowFocus(bool isFocus) override;

    void WindowActivate(bool isActive) override;

    void ContainerModalUnFocus() override;

    void ShowContainerTitle(bool isShow, bool hasDeco = true, bool needUpdate = false) override;

    void SetAppBgColor(const Color& color) override;

    void SetWindowContainerColor(const Color& activeColor, const Color& inactiveColor) override;

    void SetAppTitle(const std::string& title) override;

    void SetAppIcon(const RefPtr<PixelMap>& icon) override;

    void OnSurfaceChanged(int32_t width, int32_t height,
        WindowSizeChangeReason type = WindowSizeChangeReason::UNDEFINED,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr) override;

    void OnLayoutCompleted(const std::string& componentId);
    void OnDrawCompleted(const std::string& componentId);

    void OnSurfacePositionChanged(int32_t posX, int32_t posY) override;

    void OnSurfaceDensityChanged(double density) override;

    void OnSystemBarHeightChanged(double statusBar, double navigationBar) override {}

    void OnSurfaceDestroyed() override {}

    void NotifyOnPreDraw() override {}

    bool CallRouterBackToPopPage() override
    {
        return OnBackPressed();
    }

    bool OnBackPressed();

    RefPtr<FrameNode> FindNavigationNodeToHandleBack(const RefPtr<UINode>& node, bool& isEntry);

    void AddDirtyPropertyNode(const RefPtr<FrameNode>& dirty);

    void AddDirtyCustomNode(const RefPtr<UINode>& dirtyNode);

    void AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty);

    void AddLayoutNode(const RefPtr<FrameNode>& layoutNode);

    void AddDirtyRenderNode(const RefPtr<FrameNode>& dirty);

    void AddDirtyFreezeNode(FrameNode* node);

    void AddPredictTask(PredictTask&& task);

    void AddAfterLayoutTask(std::function<void()>&& task, bool isFlushInImplicitAnimationTask = false);

    void AddPersistAfterLayoutTask(std::function<void()>&& task);

    void AddAfterRenderTask(std::function<void()>&& task);

    void AddSafeAreaPaddingProcessTask(FrameNode* node);
    void RemoveSafeAreaPaddingProcessTask(FrameNode* node);

    void AddDragWindowVisibleTask(std::function<void()>&& task)
    {
        dragWindowVisibleCallback_ = std::move(task);
    }

    void FlushOnceVsyncTask() override;

    void FlushFreezeNode();
    void FlushDirtyPropertyNodes();
    void FlushDirtyNodeUpdate();
    void FlushSafeAreaPaddingProcess();

    void SetRootRect(double width, double height, double offset) override;

    void SetWindowSceneConsumed(bool isConsumed);

    bool IsWindowSceneConsumed();

    void UpdateSystemSafeArea(const SafeAreaInsets& systemSafeArea, bool checkSystemWindow = false) override;
    void UpdateCutoutSafeArea(const SafeAreaInsets& cutoutSafeArea, bool checkSystemWindow = false) override;
    void UpdateNavSafeArea(const SafeAreaInsets& navSafeArea, bool checkSystemWindow = false) override;

    void UpdateOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type) override;

    float GetPageAvoidOffset() override;

    bool CheckNeedAvoidInSubWindow() override;

    void CheckAndUpdateKeyboardInset(float keyboardHeight) override;

    void UpdateSizeChangeReason(
        WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);

    void UpdateDisplayAvailableRect(const Rect& displayAvailableRect)
    {
        displayAvailableRect_ = displayAvailableRect;
    }
    Rect GetDisplayAvailableRect() const
    {
        return displayAvailableRect_;
    }

    void SetEnableKeyBoardAvoidMode(KeyBoardAvoidMode value) override;

    KeyBoardAvoidMode GetEnableKeyBoardAvoidMode() override;

    bool UsingCaretAvoidMode();

    void OnCaretPositionChangeOrKeyboardHeightChange(float keyboardHeight, double positionY, double height,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr, bool forceChange = false);
    void DoKeyboardAvoidFunc(float keyboardHeight, double positionY, double height,
        bool keyboardHeightChanged);
    float CalcNewKeyboardOffset(float keyboardHeight, float positionYWithOffset,
        float height, SizeF& rootSize, bool isInline = false);
    float CalcAvoidOffset(float keyboardHeight, float positionYWithOffset,
        float height, SizeF rootSize);

    bool IsEnableKeyBoardAvoidMode() override;

    void RequireSummary() override;

    const RefPtr<SafeAreaManager>& GetSafeAreaManager() const
    {
        return safeAreaManager_;
    }
    virtual SafeAreaInsets GetSafeArea() const;

    virtual SafeAreaInsets GetSafeAreaWithoutProcess() const;

    const RefPtr<FullScreenManager>& GetFullScreenManager();

    RefPtr<AccessibilityManagerNG> GetAccessibilityManagerNG();

    void SendEventToAccessibilityWithNode(
        const AccessibilityEvent& accessibilityEvent, const RefPtr<FrameNode>& node);

    const RefPtr<StageManager>& GetStageManager();

    const RefPtr<OverlayManager>& GetOverlayManager();

    const RefPtr<SelectOverlayManager>& GetSelectOverlayManager();

    const RefPtr<SharedOverlayManager>& GetSharedOverlayManager()
    {
        return sharedTransitionManager_;
    }

#ifdef WINDOW_SCENE_SUPPORTED
    const RefPtr<UIExtensionManager>& GetUIExtensionManager()
    {
        return uiExtensionManager_;
    }
#endif

    const RefPtr<DragDropManager>& GetDragDropManager();

    const RefPtr<FocusManager>& GetFocusManager() const;

    const RefPtr<FocusManager>& GetOrCreateFocusManager();

    const RefPtr<FrameRateManager>& GetFrameRateManager()
    {
        return frameRateManager_;
    }

    void FlushBuild() override;

    void FlushPipelineImmediately() override;
    void RebuildFontNode() override;

    void AddBuildFinishCallBack(std::function<void()>&& callback);

    void AddWindowStateChangedCallback(int32_t nodeId);

    void RemoveWindowStateChangedCallback(int32_t nodeId);

    void AddWindowFocusChangedCallback(int32_t nodeId);

    void RemoveWindowFocusChangedCallback(int32_t nodeId);

    void AddWindowActivateChangedCallback(int32_t nodeId);

    void RemoveWindowActivateChangedCallback(int32_t nodeId);

    void AddWindowSizeChangeCallback(int32_t nodeId);

    void RemoveWindowSizeChangeCallback(int32_t nodeId);

    void AddWindowSizeDragEndCallback(std::function<void()>&& callback);

    void AddNavigationNode(int32_t pageId, WeakPtr<UINode> navigationNode);

    void RemoveNavigationNode(int32_t pageId, int32_t nodeId);

    void FirePageChanged(int32_t pageId, bool isOnShow);

    bool HasDifferentDirectionGesture() const;

    bool IsKeyInPressed(KeyCode tarCode) const
    {
        CHECK_NULL_RETURN(eventManager_, false);
        return eventManager_->IsKeyInPressed(tarCode);
    }

    bool GetIsFocusingByTab() const
    {
        return isFocusingByTab_;
    }

    void SetIsFocusingByTab(bool isFocusingByTab)
    {
        isFocusingByTab_ = isFocusingByTab;
    }

    bool GetIsFocusActive() const
    {
        return focusManager_ ? focusManager_->GetIsFocusActive() : false;
    }

    bool SetIsFocusActive(bool isFocusActive,
        FocusActiveReason reason = FocusActiveReason::DEFAULT, bool autoFocusInactive = true);

    void AddIsFocusActiveUpdateEvent(const RefPtr<FrameNode>& node, const std::function<void(bool)>& eventCallback);
    void RemoveIsFocusActiveUpdateEvent(const RefPtr<FrameNode>& node);

    bool IsTabJustTriggerOnKeyEvent() const
    {
        return eventManager_->IsTabJustTriggerOnKeyEvent();
    }

    bool GetOnShow() const override
    {
        return onShow_;
    }

    bool ChangeMouseStyle(int32_t nodeId, MouseFormat format, int32_t windowId = 0, bool isByPass = false,
        MouseStyleChangeReason reason = MouseStyleChangeReason::INNER_SET_MOUSESTYLE);

    bool RequestFocus(const std::string& targetNodeId, bool isSyncRequest = false) override;
    void AddDirtyFocus(const RefPtr<FrameNode>& node);
    void AddDirtyRequestFocus(const RefPtr<FrameNode>& node);
    void RootLostFocus(BlurReason reason = BlurReason::FOCUS_SWITCH) const;

    void SetContainerWindow(bool isShow, RRect& rRect);
    void SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose) override;
    void EnableContainerModalGesture(bool isEnable) override;
    void SetCloseButtonStatus(bool isEnabled);

    void AddNodesToNotifyMemoryLevel(int32_t nodeId);
    void RemoveNodesToNotifyMemoryLevel(int32_t nodeId);
    void NotifyMemoryLevel(int32_t level) override;
    void FlushModifier() override;
    void FlushMessages() override;

    void FlushUITasks(bool triggeredByImplicitAnimation = false) override;
    void FlushUITaskWithSingleDirtyNode(const RefPtr<FrameNode>& node);

    void FlushAfterLayoutCallbackInImplicitAnimationTask() override;

    bool GetIsRequestVsync()
    {
        return window_->GetIsRequestVsync();
    }

    bool IsLayouting() const override
    {
        return taskScheduler_->IsLayouting();
    }
    // end pipeline, exit app
    void Finish(bool autoFinish) const override;
    RectF GetRootRect()
    {
        CHECK_NULL_RETURN(rootNode_, RectF());
        auto geometryNode = rootNode_->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, RectF());
        return geometryNode->GetFrameRect();
    }

    void FlushReload(const ConfigurationChange& configurationChange, bool fullUpdate = true) override;
    void OnFlushReloadFinish()
    {
        auto tasks = std::move(afterReloadAnimationTasks_);
        for (const auto& task : tasks) {
            if (task) {
                task();
            }
        }
    }
    void AddAfterReloadAnimationTask(std::function<void()>&& task)
    {
        afterReloadAnimationTasks_.emplace_back(std::move(task));
    }

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

    int32_t RegisterFoldStatusChangedCallback(std::function<void(FoldStatus)>&& callback)
    {
        if (callback) {
            foldStatusChangedCallbackMap_.emplace(callbackId_, std::move(callback));
            return callbackId_;
        }
        return 0;
    }

    void UnRegisterFoldStatusChangedCallback(int32_t callbackId)
    {
        foldStatusChangedCallbackMap_.erase(callbackId);
    }

    int32_t RegisterHalfFoldHoverChangedCallback(std::function<void(bool)>&& callback)
    {
        if (callback) {
            halfFoldHoverChangedCallbackMap_.emplace(++callbackId_, std::move(callback));
            return callbackId_;
        }
        return 0;
    }

    void UnRegisterHalfFoldHoverChangedCallback(int32_t callbackId)
    {
        halfFoldHoverChangedCallbackMap_.erase(callbackId);
    }

    void UpdateHalfFoldHoverStatus(int32_t windowWidth, int32_t windowHeight);

    bool IsHalfFoldHoverStatus()
    {
        return isHalfFoldHoverStatus_;
    }

    void OnHalfFoldHoverChangedCallback();

    int32_t RegisterFoldDisplayModeChangedCallback(std::function<void(FoldDisplayMode)>&& callback)
    {
        if (callback) {
            foldDisplayModeChangedCallbackMap_.emplace(++callbackId_, std::move(callback));
            return callbackId_;
        }
        return 0;
    }

    void UnRegisterFoldDisplayModeChangedCallback(int32_t callbackId)
    {
        foldDisplayModeChangedCallbackMap_.erase(callbackId);
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

    int32_t RegisterTransformHintChangeCallback(std::function<void(uint32_t)>&& callback)
    {
        if (callback) {
            transformHintChangedCallbackMap_.emplace(++callbackId_, std::move(callback));
            return callbackId_;
        }
        return 0;
    }

    void UnregisterTransformHintChangedCallback(int32_t callbackId)
    {
        transformHintChangedCallbackMap_.erase(callbackId);
    }

    bool SetMouseStyleHoldNode(int32_t id)
    {
        CHECK_NULL_RETURN(eventManager_, false);
        auto mouseStyleManager = eventManager_->GetMouseStyleManager();
        if (mouseStyleManager) {
            return mouseStyleManager->SetMouseStyleHoldNode(id);
        }
        return false;
    }

    bool FreeMouseStyleHoldNode(int32_t id)
    {
        CHECK_NULL_RETURN(eventManager_, false);
        auto mouseStyleManager = eventManager_->GetMouseStyleManager();
        if (mouseStyleManager) {
            return mouseStyleManager->FreeMouseStyleHoldNode(id);
        }
        return false;
    }

    bool FreeMouseStyleHoldNode()
    {
        CHECK_NULL_RETURN(eventManager_, false);
        auto mouseStyleManager = eventManager_->GetMouseStyleManager();
        if (mouseStyleManager) {
            return mouseStyleManager->FreeMouseStyleHoldNode();
        }
        return false;
    }

    void MarkNeedFlushMouseEvent(MockFlushEventType type = MockFlushEventType::EXECUTE)
    {
        isNeedFlushMouseEvent_ = type;
    }

    void MarkNeedFlushAnimationStartTime()
    {
        isNeedFlushAnimationStartTime_ = true;
    }

    // font
    void AddFontNodeNG(const WeakPtr<UINode>& node);
    void RemoveFontNodeNG(const WeakPtr<UINode>& node);

    // restore
    void RestoreNodeInfo(std::unique_ptr<JsonValue> nodeInfo) override;
    std::unique_ptr<JsonValue> GetStoredNodeInfo() override;
    void StoreNode(int32_t restoreId, const WeakPtr<FrameNode>& node);
    bool GetRestoreInfo(int32_t restoreId, std::string& restoreInfo);
    void RemoveStoredNode(int32_t restoreId)
    {
        storeNode_.erase(restoreId);
    }
    void SetNeedRenderNode(const WeakPtr<FrameNode>& node);

    void SetIgnoreViewSafeArea(bool value) override;
    void SetIsLayoutFullScreen(bool value) override;
    void SetIsNeedAvoidWindow(bool value) override;

    void AddAnimationClosure(std::function<void()>&& animation);
    void FlushAnimationClosure();
    void DumpJsInfo(const std::vector<std::string>& params) const;
    void DumpUIExt() const override;

    bool DumpPageViewData(const RefPtr<FrameNode>& node, RefPtr<ViewDataWrap> viewDataWrap,
        bool skipSubAutoFillContainer = false, bool needsRecordData = false);
    bool CheckNeedAutoSave();
    bool CheckOverlayFocus();
    void NotifyFillRequestSuccess(AceAutoFillType autoFillType, RefPtr<ViewDataWrap> viewDataWrap);
    void NotifyFillRequestFailed(RefPtr<FrameNode> node, int32_t errCode,
        const std::string& fillContent = "", bool isPopup = false);

    std::shared_ptr<NavigationController> GetNavigationController(const std::string& id) override;
    void AddOrReplaceNavigationNode(const std::string& id, const WeakPtr<FrameNode>& node);
    void DeleteNavigationNode(const std::string& id);

    void AddGestureTask(const DelayedTask& task)
    {
        delayedTasks_.emplace_back(task);
    }

    void RemoveGestureTask(const DelayedTask& task)
    {
        for (auto iter = delayedTasks_.begin(); iter != delayedTasks_.end();) {
            if (iter->recognizer == task.recognizer) {
                iter = delayedTasks_.erase(iter);
            } else {
                ++iter;
            }
        }
    }

    void SetScreenNode(const RefPtr<FrameNode>& node)
    {
        CHECK_NULL_VOID(node);
        screenNode_ = AceType::WeakClaim(AceType::RawPtr(node));
    }
    RefPtr<FrameNode> GetScreenNode() const
    {
        return screenNode_.Upgrade();
    }

    void SetFocusedWindowSceneNode(const WeakPtr<FrameNode>& node)
    {
        windowSceneNode_ = node;
    }
    RefPtr<FrameNode> GetFocusedWindowSceneNode() const
    {
        return windowSceneNode_.Upgrade();
    }

    void SetJSViewActive(bool active, WeakPtr<CustomNode> custom);

    void UpdateCurrentActiveNode(const WeakPtr<FrameNode>& node) override
    {
        activeNode_ = std::move(node);
    }

    const WeakPtr<FrameNode>& GetCurrentActiveNode() const
    {
        return activeNode_;
    }

    std::string GetCurrentExtraInfo() override;
    void UpdateTitleInTargetPos(bool isShow, int32_t height) override;

    void SetCursor(int32_t cursorValue) override;

    void RestoreDefault(int32_t windowId = 0) override;

    void OnFoldStatusChange(FoldStatus foldStatus) override;
    void OnFoldDisplayModeChange(FoldDisplayMode foldDisplayMode) override;

    void OnTransformHintChanged(uint32_t transform) override;

    uint32_t GetTransformHint() const
    {
        return transform_;
    }

    // for frontend animation interface.
    void OpenFrontendAnimation(
        const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& finishCallback);
    void CloseFrontendAnimation();

    bool IsDragging() const override;
    void SetIsDragging(bool isDragging) override;

    void ResetDragging() override;
    const RefPtr<PostEventManager>& GetPostEventManager();

    void SetContainerModalTitleVisible(bool customTitleSettedShow, bool floatingTitleSettedShow);
    void SetContainerModalTitleHeight(int32_t height);
    int32_t GetContainerModalTitleHeight();
    bool GetContainerModalButtonsRect(RectF& containerModal, RectF& buttons);
    void SubscribeContainerModalButtonsRectChange(
        std::function<void(RectF& containerModal, RectF& buttons)>&& callback);
    void GetWindowPaintRectWithoutMeasureAndLayout(RectInt& rect);

    const SerializedGesture& GetSerializedGesture() const override;
    // return value means whether it has printed info
    bool PrintVsyncInfoIfNeed() const override;
    void SetUIExtensionImeShow(bool imeShow);

    void StartWindowAnimation() override
    {
        isWindowAnimation_ = true;
    }

    void StopWindowAnimation() override;

    void AddSyncGeometryNodeTask(std::function<void()>&& task) override;
    void FlushSyncGeometryNodeTasks() override;
    void SetVsyncListener(VsyncCallbackFun vsync)
    {
        vsyncListener_ = std::move(vsync);
    }

    void SetOnceVsyncListener(VsyncCallbackFun vsync)
    {
        onceVsyncListener_ = std::move(vsync);
    }

    bool HasOnceVsyncListener() {
        return onceVsyncListener_ != nullptr;
    }

    const RefPtr<MemoryManager>& GetMemoryManager() const
    {
        return memoryMgr_;
    }

    const RefPtr<NavigationManager>& GetNavigationManager() const
    {
        return navigationMgr_;
    }

    const RefPtr<FormVisibleManager>& GetFormVisibleManager() const
    {
        return formVisibleMgr_;
    }

    const RefPtr<FormEventManager>& GetFormEventManager() const
    {
        return formEventMgr_;
    }

    const RefPtr<FormGestureManager>& GetFormGestureManager() const
    {
        return formGestureMgr_;
    }

    const RefPtr<AvoidInfoManager>& GetAvoidInfoManager() const
    {
        return avoidInfoMgr_;
    }

    const std::unique_ptr<RecycleManager>& GetRecycleManager() const
    {
        return recycleManager_;
    }

    RefPtr<PrivacySensitiveManager> GetPrivacySensitiveManager() const
    {
        return privacySensitiveManager_;
    }

    const RefPtr<ToolbarManager>& GetToolbarManager() const
    {
        return toolbarManager_;
    }

    void ChangeSensitiveNodes(bool flag) override
    {
        privacySensitiveManager_->TriggerFrameNodesSensitive(flag);
    }

    void FlushRequestFocus();

    Dimension GetCustomTitleHeight();

    void SetOverlayNodePositions(std::vector<Ace::RectF> rects);

    static void SetCallBackNode(const WeakPtr<NG::FrameNode>& node);

    std::vector<Ace::RectF> GetOverlayNodePositions();

    void RegisterOverlayNodePositionsUpdateCallback(
        const std::function<void(std::vector<Ace::RectF>)>&& callback);

    void TriggerOverlayNodePositionsUpdateCallback(std::vector<Ace::RectF> rects);

    void DetachNode(RefPtr<UINode> uiNode);

    void CheckNeedUpdateBackgroundColor(Color& color);

    bool CheckNeedDisableUpdateBackgroundImage();

    void ChangeDarkModeBrightness() override;

    std::string GetResponseRegion(const RefPtr<NG::FrameNode>& rootNode) override;

    void NotifyResponseRegionChanged(const RefPtr<NG::FrameNode>& rootNode) override;

    void SetLocalColorMode(ColorMode colorMode)
    {
        auto localColorModeValue = static_cast<int32_t>(colorMode);
        localColorMode_ = localColorModeValue;
    }

    ColorMode GetLocalColorMode() const // ColorMode for WithTheme
    {
        ColorMode colorMode = static_cast<ColorMode>(localColorMode_.load());
        return colorMode;
    }

    ColorMode GetColorMode() const;

    void SetIsFreezeFlushMessage(bool isFreezeFlushMessage)
    {
        isFreezeFlushMessage_ = isFreezeFlushMessage;
    }

    bool IsFreezeFlushMessage() const
    {
        return isFreezeFlushMessage_;
    }
    bool IsContainerModalVisible() override;
    void SetDoKeyboardAvoidAnimate(bool isDoKeyboardAvoidAnimate)
    {
        isDoKeyboardAvoidAnimate_ = isDoKeyboardAvoidAnimate;
    }

    void CheckAndLogLastReceivedTouchEventInfo(int32_t eventId, TouchType type) override;

    void CheckAndLogLastConsumedTouchEventInfo(int32_t eventId, TouchType type) override;

    void CheckAndLogLastReceivedMouseEventInfo(int32_t eventId, MouseAction action) override;

    void CheckAndLogLastConsumedMouseEventInfo(int32_t eventId, MouseAction action) override;

    void CheckAndLogLastReceivedAxisEventInfo(int32_t eventId, AxisAction action) override;

    void CheckAndLogLastConsumedAxisEventInfo(int32_t eventId, AxisAction action) override;

    void AddFrameCallback(FrameCallbackFunc&& frameCallbackFunc, FrameCallbackFunc&& idleCallbackFunc,
        int64_t delayMillis);

    void FlushFrameCallback(uint64_t nanoTimestamp);
    void TriggerIdleCallback(int64_t deadline);

    void AddCAPIFrameCallback(FrameCallbackFuncFromCAPI&& frameCallbackFuncFromCAPI);
    void FlushFrameCallbackFromCAPI(uint64_t nanoTimestamp, uint32_t frameCount);

    void RegisterTouchEventListener(const std::shared_ptr<ITouchEventCallback>& listener);
    void UnregisterTouchEventListener(const WeakPtr<NG::Pattern>& pattern);

    void SetPredictNode(const RefPtr<FrameNode>& node)
    {
        predictNode_ = node;
    }

    void ResetPredictNode()
    {
        predictNode_.Reset();
    }

    void PreLayout(uint64_t nanoTimestamp, uint32_t frameCount);

    bool IsDensityChanged() const override
    {
        return isDensityChanged_;
    }

    void GetInspectorTree(bool onlyNeedVisible);
    void NotifyAllWebPattern(bool isRegister);
    void AddFrameNodeChangeListener(const WeakPtr<FrameNode>& node);
    void RemoveFrameNodeChangeListener(int32_t nodeId);
    bool AddChangedFrameNode(const WeakPtr<FrameNode>& node);
    void RemoveChangedFrameNode(int32_t nodeId);
    void SetForceSplitEnable(bool isForceSplit, const std::string& homePage)
    {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "set force split %{public}s", isForceSplit ? "enable" : "disable");
        isForceSplit_ = isForceSplit;
        homePageConfig_ = homePage;
    }

    bool GetForceSplitEnable() const
    {
        return isForceSplit_;
    }

    std::string GetHomePageConfig() const
    {
        return homePageConfig_;
    }

    bool CatchInteractiveAnimations(const std::function<void()>& animationCallback) override;

    bool IsWindowFocused() const override
    {
        return isWindowHasFocused_ && GetOnFoucs();
    }

    void CollectTouchEventsBeforeVsync(std::list<TouchEvent>& touchEvents);

    bool IsDirtyNodesEmpty() const override
    {
        return dirtyNodes_.empty();
    }

    bool IsDirtyLayoutNodesEmpty() const override
    {
        return taskScheduler_->IsDirtyLayoutNodesEmpty();
    }

    bool IsDirtyPropertyNodesEmpty() const override
    {
        return dirtyPropertyNodes_.empty();
    }

    void SyncSafeArea(SafeAreaSyncType syncType = SafeAreaSyncType::SYNC_TYPE_NONE);
    bool CheckThreadSafe();

    bool IsHoverModeChange() const
    {
        return isHoverModeChanged_;
    }

    void UpdateHalfFoldHoverProperty(int32_t windowWidth, int32_t windowHeight);

    void AnimateOnSafeAreaUpdate();
    void RegisterAttachedNode(UINode* uiNode);
    void RemoveAttachedNode(UINode* uiNode);

    bool GetContainerFloatingTitleVisible() override;

    bool GetContainerCustomTitleVisible() override;

    bool GetContainerControlButtonVisible() override;

    std::string GetBundleName();
    std::string GetModuleName();

    void SaveTranslateManager(std::shared_ptr<UiTranslateManagerImpl> uiTranslateManager)
    {
        uiTranslateManager_ = uiTranslateManager;
    }

    void RegisterListenerForTranslate(const WeakPtr<NG::FrameNode> node)
    {
        uiTranslateManager_->AddTranslateListener(node);
    }

    void UnRegisterListenerForTranslate(int32_t nodeId)
    {
        uiTranslateManager_->RemoveTranslateListener(nodeId);
    }

    void SetEnableSwipeBack(bool isEnable) override;

    Offset GetHostParentOffsetToWindow() const
    {
        return lastHostParentOffsetToWindow_;
    }

    void SetHostParentOffsetToWindow(const Offset& offset);

    RefPtr<Kit::UIContext> GetUIContext();
    void AddPendingDeleteCustomNode(const RefPtr<CustomNode>& node);
    void FlushPendingDeleteCustomNode();

    void HandleSpecialContainerNode();

    void AddPositionZNode(int32_t nodeId)
    {
        positionZNodes_.insert(nodeId);
    }

    void DeletePositionZNode(int32_t nodeId)
    {
        auto it = positionZNodes_.find(nodeId);
        if (it != positionZNodes_.end()) {
            positionZNodes_.erase(it);
        }
    }

    std::set<int32_t> GetPositionZNodes()
    {
        return positionZNodes_;
    }

    void ClearPositionZNodes()
    {
        positionZNodes_.clear();
    }
    bool IsWindowSizeDragging() const
    {
        return isWindowSizeDragging_;
    }

    void SetIsWindowSizeDragging(bool isDragging);
    void GetAllPixelMap();
    void AddPixelMap(int32_t nodeId, RefPtr<PixelMap> pixelMap)
    {
        uiTranslateManager_->AddPixelMap(nodeId, pixelMap);
    }

    WeakPtr<AIWriteAdapter> GetOrCreateAIWriteAdapter()
    {
        if (!aiWriteAdapter_) {
            aiWriteAdapter_ = MakeRefPtr<AIWriteAdapter>();
        }
        return aiWriteAdapter_;
    }

    int32_t RegisterRotationEndCallback(std::function<void()>&& callback)
    {
        if (callback) {
            rotationEndCallbackMap_.emplace(++callbackId_, std::move(callback));
            return callbackId_;
        }
        return 0;
    }

    void UnregisterRotationEndCallback(int32_t callbackId)
    {
        surfaceChangedCallbackMap_.erase(callbackId);
    }

protected:
    void StartWindowSizeChangeAnimate(int32_t width, int32_t height, WindowSizeChangeReason type,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);
    void StartWindowMaximizeAnimation(
        int32_t width, int32_t height, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);
    void StartFullToMultWindowAnimation(int32_t width, int32_t height, WindowSizeChangeReason type,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);
    void StartSplitWindowAnimation(int32_t width, int32_t height, WindowSizeChangeReason type,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);

    void FlushVsync(uint64_t nanoTimestamp, uint32_t frameCount) override;
    void FlushPipelineWithoutAnimation() override;
    void FlushFocus();
    void FlushFocusWithNode(RefPtr<FrameNode> focusNode, bool isScope);
    void DispatchDisplaySync(uint64_t nanoTimestamp) override;
    void FlushAnimation(uint64_t nanoTimestamp) override;
    bool OnDumpInfo(const std::vector<std::string>& params) const override;
    void OnDumpRecorderStart(const std::vector<std::string>& params) const;
    void TriggerFrameDumpFuncIfExist() const;

    void OnVirtualKeyboardHeightChange(float keyboardHeight,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr, const float safeHeight = 0.0f,
        const bool supportAvoidance = false, bool forceChange = false) override;
    void OnVirtualKeyboardHeightChange(float keyboardHeight, double positionY, double height,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr, bool forceChange = false) override;
    void FlushDirtyPropertyNodesWhenExist();

    void SetIsLayouting(bool layouting)
    {
        taskScheduler_->SetIsLayouting(layouting);
    }

    void AvoidanceLogic(float keyboardHeight, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr,
        const float safeHeight = 0.0f, const bool supportAvoidance = false);
    void OriginalAvoidanceLogic(
        float keyboardHeight, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);
    RefPtr<FrameNode> GetContainerModalNode();
    void DoKeyboardAvoidAnimate(const KeyboardAnimationConfig& keyboardAnimationConfig, float keyboardHeight,
        const std::function<void()>& func);
    void StartFoldStatusDelayTask(FoldStatus foldStatus);
    void PostKeyboardAvoidTask();

private:
    void ExecuteSurfaceChangedCallbacks(int32_t newWidth, int32_t newHeight, WindowSizeChangeReason type);

    void FlushWindowStateChangedCallback(bool isShow);

    void FlushWindowFocusChangedCallback(bool isFocus);

    void FlushWindowActivateChangedCallback(bool isActivate);

    void FlushWindowSizeChangeCallback(int32_t width, int32_t height, WindowSizeChangeReason type);


    uint64_t GetResampleStamp() const;
    void ConsumeTouchEvents(std::list<TouchEvent>& touchEvents, std::unordered_map<int, TouchEvent>& idToTouchPoints);
    void AccelerateConsumeTouchEvents(
        std::list<TouchEvent>& touchEvents, std::unordered_map<int, TouchEvent>& idToTouchPoints);
    void SetTouchAccelarate(bool isEnable) override
    {
        touchAccelarate_ = isEnable;
    }
    void SetTouchPassThrough(bool isEnable) override
    {
        isEventsPassThrough_ = isEnable;
    }

    void FlushTouchEvents();
    void FlushWindowPatternInfo();
    void FlushFocusView();
    void FlushFocusScroll();

    void ProcessDelayTasks();

    void InspectDrew();

    void FlushBuildFinishCallbacks();

    void DumpPipelineInfo() const;

    void RegisterRootEvent();

    void ResetDraggingStatus(const TouchEvent& touchPoint, const RefPtr<FrameNode>& node = nullptr);

    void CancelDragIfRightBtnPressed(const MouseEvent& event);

    void UpdateLastMoveEvent(const MouseEvent& event);

    void CompensateTouchMoveEvent(const TouchEvent& event);

    bool CompensateTouchMoveEventFromUnhandledEvents(const TouchEvent& event);

    void DispatchMouseToTouchEvent(const MouseEvent& event, const RefPtr<FrameNode>& node);

    void CompensateMouseMoveEvent(const MouseEvent& event, const RefPtr<FrameNode>& node);

    bool CompensateMouseMoveEventFromUnhandledEvents(const MouseEvent& event, const RefPtr<FrameNode>& node);

    void CompensatePointerMoveEvent(const DragPointerEvent& event, const RefPtr<FrameNode>& node);

    bool CompensatePointerMoveEventFromUnhandledEvents(const DragPointerEvent& event, const RefPtr<FrameNode>& node);

    FrameInfo* GetCurrentFrameInfo(uint64_t recvTime, uint64_t timeStamp);

    void DispatchAxisEventToDragDropManager(const AxisEvent& event, const RefPtr<FrameNode>& node,
        SerializedGesture& etsSerializedGesture);

    // only used for static form.
    void UpdateFormLinkInfos();

    void FlushFrameRate();

    void RegisterFocusCallback();
    void DumpFocus(bool hasJson) const;
    void DumpResLoadError() const;
    void DumpInspector(const std::vector<std::string>& params, bool hasJson) const;
    void DumpElement(const std::vector<std::string>& params, bool hasJson) const;
    void DumpData(const RefPtr<FrameNode>& node, const std::vector<std::string>& params, bool hasJson) const;
    void OnDumpInjection(const std::vector<std::string>& params) const;
    void OnRotationAnimationEnd();
    template<typename T>
    struct NodeCompare {
        bool operator()(const T& nodeLeft, const T& nodeRight) const
        {
            if (!nodeLeft || !nodeRight) {
                return false;
            }
            if (nodeLeft->GetDepth() < nodeRight->GetDepth()) {
                return true;
            }
            if (nodeLeft->GetDepth() == nodeRight->GetDepth()) {
                return nodeLeft < nodeRight;
            }
            return false;
        }
    };

    void FlushNodeChangeFlag();
    void CleanNodeChangeFlag();

    uint64_t AdjustVsyncTimeStamp(uint64_t nanoTimestamp);
    bool FlushModifierAnimation(uint64_t nanoTimestamp);

    void FlushAnimationDirtysWhenExist(const AnimationOption& option);

    std::unique_ptr<UITaskScheduler> taskScheduler_ = std::make_unique<UITaskScheduler>();

    std::unordered_map<uint32_t, WeakPtr<ScheduleTask>> scheduleTasks_;

    std::list<WeakPtr<FrameNode>> dirtyFreezeNode_; // used in freeze feature.
    std::stack<RefPtr<CustomNode>> pendingDeleteCustomNode_;
    std::set<RefPtr<FrameNode>, NodeCompare<RefPtr<FrameNode>>> dirtyPropertyNodes_; // used in node api.
    std::set<RefPtr<UINode>, NodeCompare<RefPtr<UINode>>> dirtyNodes_;
    std::list<std::function<void()>> buildFinishCallbacks_;

    // window on show or on hide
    std::set<int32_t> onWindowStateChangedCallbacks_;
    // window on focused or on unfocused
    std::set<int32_t> onWindowFocusChangedCallbacks_;
    // window on activate or on unactivate
    std::set<int32_t> onWindowActivateChangedCallbacks_;
    // window on drag
    std::list<int32_t> onWindowSizeChangeCallbacks_;
    // window size drag end
    std::list<std::function<void()>> onWindowSizeDragEndCallbacks_;

    std::list<int32_t> nodesToNotifyMemoryLevel_;

    std::list<TouchEvent> touchEvents_;

    std::map<RefPtr<FrameNode>, std::list<DragPointerEvent>> dragEvents_;
    std::map<RefPtr<FrameNode>, std::list<MouseEvent>> mouseEvents_;
    std::vector<std::function<void(const std::vector<std::string>&)>> dumpListeners_;

    RefPtr<FrameNode> rootNode_;

    int32_t curFocusNodeId_ = -1;

    bool isTransFlag_ = false;
    OHOS::Ace::WindowSizeChangeReason windowSizeChangeReason_ = WindowSizeChangeReason::UNDEFINED;
    SourceType lastSourceType_ = SourceType::NONE;
    bool preIsHalfFoldHoverStatus_ = false;
    bool isHoverModeChanged_ = false;

    std::set<WeakPtr<FrameNode>> needRenderNode_;

    int32_t callbackId_ = 0;
    SurfaceChangedCallbackMap surfaceChangedCallbackMap_;
    SurfacePositionChangedCallbackMap surfacePositionChangedCallbackMap_;
    FoldStatusChangedCallbackMap foldStatusChangedCallbackMap_;
    HalfFoldHoverChangedCallbackMap halfFoldHoverChangedCallbackMap_;
    FoldDisplayModeChangedCallbackMap foldDisplayModeChangedCallbackMap_;
    TransformHintChangedCallbackMap transformHintChangedCallbackMap_;

    bool isOnAreaChangeNodesCacheVaild_ = false;
    std::vector<FrameNode*> onAreaChangeNodesCache_;
    std::unordered_set<int32_t> onAreaChangeNodeIds_;
    std::unordered_set<int32_t> onVisibleAreaChangeNodeIds_;
    std::unordered_map<int32_t, std::vector<MouseEvent>> historyMousePointsById_;
    std::unordered_map<int32_t, std::vector<DragPointerEvent>> historyPointsEventById_;
    RefPtr<AccessibilityManagerNG> accessibilityManagerNG_;
    RefPtr<StageManager> stageManager_;
    RefPtr<OverlayManager> overlayManager_;
    RefPtr<FullScreenManager> fullScreenManager_;
    RefPtr<SelectOverlayManager> selectOverlayManager_;
    RefPtr<DragDropManager> dragDropManager_;
    RefPtr<FocusManager> focusManager_;
    RefPtr<SharedOverlayManager> sharedTransitionManager_;
#ifdef WINDOW_SCENE_SUPPORTED
    RefPtr<UIExtensionManager> uiExtensionManager_ = MakeRefPtr<UIExtensionManager>();
#endif
    RefPtr<SafeAreaManager> safeAreaManager_ = MakeRefPtr<SafeAreaManager>();
    RefPtr<FrameRateManager> frameRateManager_ = MakeRefPtr<FrameRateManager>();
    RefPtr<PrivacySensitiveManager> privacySensitiveManager_ = MakeRefPtr<PrivacySensitiveManager>();
    RefPtr<ToolbarManager> toolbarManager_ = MakeRefPtr<ToolbarManager>();
    Rect displayAvailableRect_;
    WeakPtr<FrameNode> dirtyFocusNode_;
    WeakPtr<FrameNode> dirtyFocusScope_;
    WeakPtr<FrameNode> dirtyRequestFocusNode_;
    WeakPtr<FrameNode> screenNode_;
    WeakPtr<FrameNode> windowSceneNode_;
    uint32_t nextScheduleTaskId_ = 0;
    uint64_t resampleTimeStamp_ = 0;
    bool touchAccelarate_ = false;
    bool isEventsPassThrough_ = false;
    uint64_t animationTimeStamp_ = 0;
    bool hasIdleTasks_ = false;
    bool isFocusingByTab_ = false;
    bool isWindowHasFocused_ = false;
    bool onShow_ = false;
    MockFlushEventType isNeedFlushMouseEvent_ = MockFlushEventType::NONE;
    bool isNeedFlushAnimationStartTime_ = false;
    bool canUseLongPredictTask_ = false;
    bool isWindowSceneConsumed_ = false;
    bool isDensityChanged_ = false;
    bool isBeforeDragHandleAxis_ = false;
    WeakPtr<FrameNode> activeNode_;
    bool isWindowAnimation_ = false;
    bool isWindowSizeDragging_ = false;
    KeyBoardAvoidMode prevKeyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    bool isFreezeFlushMessage_ = false;

    RefPtr<FrameNode> focusNode_;
    std::function<void()> focusOnNodeCallback_;
    std::function<void(bool isRotate,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)> sizeChangeByRotateCallback_;
    std::function<void(const std::string&)> linkJumpCallback_ = nullptr;
    std::function<void()> dragWindowVisibleCallback_;

    std::optional<bool> needSoftKeyboard_;
    std::optional<bool> windowFocus_;
    std::optional<bool> windowShow_;

    std::unique_ptr<MouseEvent> lastMouseEvent_;

    std::unordered_map<int32_t, WeakPtr<FrameNode>> storeNode_;
    std::unordered_map<int32_t, std::string> restoreNodeInfo_;
    std::unordered_map<int32_t, std::vector<WeakPtr<UINode>>> pageToNavigationNodes_;
    std::unordered_map<int32_t, std::vector<TouchEvent>> historyPointsById_;

    std::set<int32_t> positionZNodes_;

    std::list<FrameInfo> dumpFrameInfos_;
    std::list<std::function<void()>> animationClosuresList_;

    mutable std::mutex navigationMutex_;
    std::map<std::string, WeakPtr<FrameNode>> navigationNodes_;
    std::list<DelayedTask> delayedTasks_;
    RefPtr<PostEventManager> postEventManager_;

    std::map<RefPtr<FrameNode>, std::vector<MouseEvent>> nodeToMousePoints_;
    std::map<RefPtr<FrameNode>, std::vector<DragPointerEvent>> nodeToPointEvent_;
    std::vector<Ace::RectF> overlayNodePositions_;
    std::function<void(std::vector<Ace::RectF>)> overlayNodePositionUpdateCallback_;

    RefPtr<FrameNode> predictNode_;

    VsyncCallbackFun vsyncListener_;
    VsyncCallbackFun onceVsyncListener_;
    ACE_DISALLOW_COPY_AND_MOVE(PipelineContext);

    int32_t preNodeId_ = -1;

    RefPtr<AvoidInfoManager> avoidInfoMgr_ = MakeRefPtr<AvoidInfoManager>();
    RefPtr<MemoryManager> memoryMgr_ = MakeRefPtr<MemoryManager>();
    RefPtr<NavigationManager> navigationMgr_ = MakeRefPtr<NavigationManager>();
    RefPtr<FormVisibleManager> formVisibleMgr_ = MakeRefPtr<FormVisibleManager>();
    RefPtr<FormEventManager> formEventMgr_ = MakeRefPtr<FormEventManager>();
    RefPtr<FormGestureManager> formGestureMgr_ = MakeRefPtr<FormGestureManager>();
    std::unique_ptr<RecycleManager> recycleManager_ = std::make_unique<RecycleManager>();
    ColorMode colorMode_ = ColorMode::LIGHT;
    std::atomic<int32_t> localColorMode_ = static_cast<int32_t>(ColorMode::COLOR_MODE_UNDEFINED);
    std::vector<std::shared_ptr<ITouchEventCallback>> listenerVector_;
    bool customTitleSettedShow_ = true;
    bool isShowTitle_ = false;
    int32_t lastAnimatorExpectedFrameRate_ = -1;
    bool isDoKeyboardAvoidAnimate_ = true;
    bool isForceSplit_ = false;
    std::string homePageConfig_;

    std::list<FrameCallbackFuncFromCAPI> frameCallbackFuncsFromCAPI_;
    std::list<FrameCallbackFunc> frameCallbackFuncs_;
    std::list<FrameCallbackFunc> idleCallbackFuncs_;
    uint32_t transform_ = 0;
    std::list<WeakPtr<FrameNode>> changeInfoListeners_;
    std::list<WeakPtr<FrameNode>> changedNodes_;
    bool isHalfFoldHoverStatus_ = false;
    CancelableCallback<void()> foldStatusDelayTask_;
    bool isFirstRootLayout_ = true;
    bool isFirstFlushMessages_ = true;
    AxisEventChecker axisEventChecker_;
    std::unordered_set<UINode*> attachedNodeSet_;
    std::list<std::function<void()>> afterReloadAnimationTasks_;
    Offset lastHostParentOffsetToWindow_ { 0, 0 };

    RefPtr<Kit::UIContextImpl> uiContextImpl_;
    std::shared_ptr<UiTranslateManagerImpl> uiTranslateManager_;
    RotationEndCallbackMap rotationEndCallbackMap_ {};
    friend class ScopedLayout;
    friend class FormGestureManager;
    RefPtr<AIWriteAdapter> aiWriteAdapter_ = nullptr;
};

/**
 * @description: only protect isLayouting_ flag in pipeline and
 * the user needs to guarantee that current layout is not nested
 */
class ACE_FORCE_EXPORT ScopedLayout final {
public:
    ScopedLayout(PipelineContext* pipeline);
    ~ScopedLayout();

private:
    PipelineContext* pipeline_ = nullptr;
    bool isLayouting_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_CONTEXT_H
