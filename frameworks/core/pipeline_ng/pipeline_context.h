/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "base/geometry/ng/rect_t.h"
#include "base/log/frame_info.h"
#include "base/log/frame_report.h"
#include "base/memory/referenced.h"
#include "core/common/frontend.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/full_screen/full_screen_manager.h"
#include "core/components_ng/manager/safe_area/safe_area_manager.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/manager/shared_overlay/shared_overlay_manager.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/event/touch_event.h"
#include "core/pipeline/pipeline_base.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/ui_extension/ui_extension_manager.h"
#endif

namespace OHOS::Ace::NG {
class ACE_EXPORT PipelineContext : public PipelineBase {
    DECLARE_ACE_TYPE(NG::PipelineContext, PipelineBase);

public:
    using SurfaceChangedCallbackMap =
        std::unordered_map<int32_t, std::function<void(int32_t, int32_t, int32_t, int32_t, WindowSizeChangeReason)>>;
    using SurfacePositionChangedCallbackMap = std::unordered_map<int32_t, std::function<void(int32_t, int32_t)>>;
    using PredictTask = std::function<void(int64_t, bool)>;
    PipelineContext(std::shared_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
        RefPtr<AssetManager> assetManager, RefPtr<PlatformResRegister> platformResRegister,
        const RefPtr<Frontend>& frontend, int32_t instanceId);
    PipelineContext(std::shared_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
        RefPtr<AssetManager> assetManager, const RefPtr<Frontend>& frontend, int32_t instanceId);
    PipelineContext() = default;

    ~PipelineContext() override = default;

    static RefPtr<PipelineContext> GetCurrentContext();

    static float GetCurrentRootWidth();

    static float GetCurrentRootHeight();

    void SetupRootElement() override;

    void SetupSubRootElement();

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

    // Called by view when touch event received.
    void OnTouchEvent(const TouchEvent& point, bool isSubPipe = false) override;

    // Called by container when key event received.
    // if return false, then this event needs platform to handle it.
    bool OnKeyEvent(const KeyEvent& event) override;

    // Called by view when mouse event received.
    void OnMouseEvent(const MouseEvent& event) override;

    // Do mouse event actively.
    void FlushMouseEvent();

    // Called by view when axis event received.
    void OnAxisEvent(const AxisEvent& event) override;

    // Called by container when rotation event received.
    // if return false, then this event needs platform to handle it.
    bool OnRotationEvent(const RotationEvent& event) const override
    {
        return false;
    }

    void OnDragEvent(int32_t x, int32_t y, DragEventAction action) override;

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

    void AddOnAreaChangeNode(int32_t nodeId);

    void RemoveOnAreaChangeNode(int32_t nodeId);

    void HandleOnAreaChangeEvent();

    void AddVisibleAreaChangeNode(
        const RefPtr<FrameNode>& node, double ratio, const VisibleRatioCallback& callback, bool isUserCallback = true);
    void RemoveVisibleAreaChangeNode(int32_t nodeId);

    void HandleVisibleAreaChangeEvent();

    void Destroy() override;

    void OnShow() override;

    void OnHide() override;

    void WindowFocus(bool isFocus) override;

    void ShowContainerTitle(bool isShow, bool hasDeco = true) override;

    void SetAppBgColor(const Color& color) override;

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

    RefPtr<FrameNode> FindNavigationNodeToHandleBack(const RefPtr<UINode>& node);

    void AddDirtyCustomNode(const RefPtr<UINode>& dirtyNode);

    void AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty);

    void AddDirtyRenderNode(const RefPtr<FrameNode>& dirty);

    void AddPredictTask(PredictTask&& task);

    void AddAfterLayoutTask(std::function<void()>&& task);

    void AddAfterRenderTask(std::function<void()>&& task);

    void FlushDirtyNodeUpdate();

    void SetRootRect(double width, double height, double offset) override;

    void SetWindowSceneConsumed(bool isConsumed);

    bool IsWindowSceneConsumed();

    void UpdateSystemSafeArea(const SafeAreaInsets& systemSafeArea) override;
    void UpdateCutoutSafeArea(const SafeAreaInsets& cutoutSafeArea) override;
    void SetEnableKeyBoardAvoidMode(bool value) override;
    bool IsEnableKeyBoardAvoidMode() override;
    const RefPtr<SafeAreaManager>& GetSafeAreaManager() const
    {
        return safeAreaManager_;
    }
    SafeAreaInsets GetSafeArea() const;

    const RefPtr<FullScreenManager>& GetFullScreenManager();

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

    void FlushBuild() override;

    void FlushPipelineImmediately() override;

    void AddBuildFinishCallBack(std::function<void()>&& callback);

    void AddWindowStateChangedCallback(int32_t nodeId);

    void RemoveWindowStateChangedCallback(int32_t nodeId);

    void AddWindowFocusChangedCallback(int32_t nodeId);

    void RemoveWindowFocusChangedCallback(int32_t nodeId);

    void AddWindowSizeChangeCallback(int32_t nodeId);

    void RemoveWindowSizeChangeCallback(int32_t nodeId);

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
        return isFocusActive_;
    }

    bool SetIsFocusActive(bool isFocusActive);

    bool IsTabJustTriggerOnKeyEvent() const
    {
        return isTabJustTriggerOnKeyEvent_;
    }

    bool GetOnShow() const
    {
        return onShow_;
    }

    void MarkRootFocusNeedUpdate()
    {
        isRootFocusNeedUpdate_ = true;
    }

    bool ChangeMouseStyle(int32_t nodeId, MouseFormat format);

    bool RequestDefaultFocus();
    bool RequestFocus(const std::string& targetNodeId) override;
    void AddDirtyFocus(const RefPtr<FrameNode>& node);
    void AddDirtyDefaultFocus(const RefPtr<FrameNode>& node);
    void RootLostFocus(BlurReason reason = BlurReason::FOCUS_SWITCH) const;

    void SetContainerWindow(bool isShow) override;
    void SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize) override;
    void SetCloseButtonStatus(bool isEnabled);

    void AddNodesToNotifyMemoryLevel(int32_t nodeId);
    void RemoveNodesToNotifyMemoryLevel(int32_t nodeId);
    void NotifyMemoryLevel(int32_t level) override;
    void FlushMessages() override;

    void FlushUITasks() override
    {
        taskScheduler_->FlushTask();
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

    void FlushReload(const OnConfigurationChange& configurationChange) override;

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

    void SetMouseStyleHoldNode(int32_t id)
    {
        if (mouseStyleNodeId_ == -1) {
            mouseStyleNodeId_ = id;
        }
    }
    void FreeMouseStyleHoldNode(int32_t id)
    {
        if (mouseStyleNodeId_ == id) {
            mouseStyleNodeId_ = -1;
        }
    }

    void MarkNeedFlushMouseEvent()
    {
        isNeedFlushMouseEvent_ = true;
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
    void SetNeedRenderNode(const RefPtr<FrameNode>& node);

    void SetIgnoreViewSafeArea(bool value) override;
    void SetIsLayoutFullScreen(bool value) override;

    void AddAnimationClosure(std::function<void()>&& animation);
    void FlushAnimationClosure();

    void SetDragCleanTask(std::function<void()>&& task)
    {
        dragCleanTask_ = std::move(task);
    }

protected:
    void StartWindowSizeChangeAnimate(int32_t width, int32_t height, WindowSizeChangeReason type,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);
    void StartWindowMaximizeAnimation(int32_t width, int32_t height,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr);

    void FlushVsync(uint64_t nanoTimestamp, uint32_t frameCount) override;
    void FlushPipelineWithoutAnimation() override;
    void FlushFocus();
    void FlushFrameTrace();
    void FlushAnimation(uint64_t nanoTimestamp) override;
    bool OnDumpInfo(const std::vector<std::string>& params) const override;

    void OnVirtualKeyboardHeightChange(
        float keyboardHeight, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr) override;

private:
    void ExecuteSurfaceChangedCallbacks(int32_t newWidth, int32_t newHeight, WindowSizeChangeReason type);

    void FlushWindowStateChangedCallback(bool isShow);

    void FlushWindowFocusChangedCallback(bool isFocus);

    void FlushWindowSizeChangeCallback(int32_t width, int32_t height, WindowSizeChangeReason type);

    void FlushTouchEvents();

    void InspectDrew();

    void FlushBuildFinishCallbacks();

    void DumpPipelineInfo() const;

    void RegisterRootEvent();

    FrameInfo* GetCurrentFrameInfo(uint64_t recvTime, uint64_t timeStamp);

    void AnimateOnSafeAreaUpdate();
    void SyncSafeArea(bool onKeyboard = false);

    // only used for static form.
    void UpdateFormLinkInfos();

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

    std::unique_ptr<UITaskScheduler> taskScheduler_ = std::make_unique<UITaskScheduler>();

    std::unordered_map<uint32_t, WeakPtr<ScheduleTask>> scheduleTasks_;
    std::set<RefPtr<UINode>, NodeCompare<RefPtr<UINode>>> dirtyNodes_;
    std::list<std::function<void()>> buildFinishCallbacks_;

    // window on show or on hide
    std::set<int32_t> onWindowStateChangedCallbacks_;
    // window on focused or on unfocused
    std::list<int32_t> onWindowFocusChangedCallbacks_;
    // window on drag
    std::list<int32_t> onWindowSizeChangeCallbacks_;

    std::list<int32_t> nodesToNotifyMemoryLevel_;

    std::list<TouchEvent> touchEvents_;

    RefPtr<FrameNode> rootNode_;

    std::set<RefPtr<FrameNode>> needRenderNode_;

    int32_t callbackId_ = 0;
    SurfaceChangedCallbackMap surfaceChangedCallbackMap_;
    SurfacePositionChangedCallbackMap surfacePositionChangedCallbackMap_;

    std::unordered_set<int32_t> onAreaChangeNodeIds_;
    std::unordered_set<int32_t> onVisibleAreaChangeNodeIds_;

    RefPtr<StageManager> stageManager_;
    RefPtr<OverlayManager> overlayManager_;
    RefPtr<FullScreenManager> fullScreenManager_;
    RefPtr<SelectOverlayManager> selectOverlayManager_;
    RefPtr<DragDropManager> dragDropManager_;
    RefPtr<SharedOverlayManager> sharedTransitionManager_;
    RefPtr<SafeAreaManager> safeAreaManager_ = MakeRefPtr<SafeAreaManager>();
#ifdef WINDOW_SCENE_SUPPORTED
    RefPtr<UIExtensionManager> uiExtensionManager_ = MakeRefPtr<UIExtensionManager>();
#endif
    WeakPtr<FrameNode> dirtyFocusNode_;
    WeakPtr<FrameNode> dirtyFocusScope_;
    WeakPtr<FrameNode> dirtyDefaultFocusNode_;
    uint32_t nextScheduleTaskId_ = 0;
    int32_t mouseStyleNodeId_ = -1;
    bool hasIdleTasks_ = false;
    bool isFocusingByTab_ = false;
    bool isFocusActive_ = false;
    bool isTabJustTriggerOnKeyEvent_ = false;
    bool isRootFocusNeedUpdate_ = false;
    bool onShow_ = false;
    bool onFocus_ = true;
    bool isNeedFlushMouseEvent_ = false;
    bool canUseLongPredictTask_ = false;
    bool isWindowSceneConsumed_ = false;
    bool isDensityChanged_ = false;
    std::unique_ptr<MouseEvent> lastMouseEvent_;

    std::unordered_map<int32_t, WeakPtr<FrameNode>> storeNode_;
    std::unordered_map<int32_t, std::string> restoreNodeInfo_;

    std::list<FrameInfo> dumpFrameInfos_;
    std::list<std::function<void()>> animationClosuresList_;
    std::function<void()> dragCleanTask_;

    ACE_DISALLOW_COPY_AND_MOVE(PipelineContext);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_CONTEXT_H
