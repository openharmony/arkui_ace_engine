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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_HUB_H

#include <list>
#include <vector>

#include "base/geometry/ng/point_t.h"
#include "base/memory/referenced.h"
#include "core/common/interaction/interaction_data.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/event/drag_drop_event.h"
#include "core/components_ng/event/event_constants.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/event/pan_event.h"
#include "core/components_ng/event/scrollable_event.h"
#include "core/components_ng/event/target_component.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/gestures/recognizers/exclusive_recognizer.h"
#include "core/components_ng/gestures/recognizers/parallel_recognizer.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace {
struct DragNotifyMsg;
class UnifiedData;
class Subwindow;
}

namespace OHOS::Ace::NG {
using TouchInterceptFunc = std::function<NG::HitTestMode(TouchEventInfo&)>;

using ShouldBuiltInRecognizerParallelWithFunc = std::function<RefPtr<NGGestureRecognizer>(
    const RefPtr<NGGestureRecognizer>&, const std::vector<RefPtr<NGGestureRecognizer>>&)>;

struct TouchTestInfo {
    PointF windowPoint;
    PointF currentCmpPoint;
    PointF subCmpPoint;
    RectF subRect;
    std::string id;
};

struct TouchResult {
    TouchTestStrategy strategy;
    std::string id;
};

struct DragDropBaseInfo {
    RefPtr<AceType> node;
    RefPtr<PixelMap> pixelMap;
    std::string extraInfo;
};

struct BindMenuStatus {
    bool isBindCustomMenu = false;
    bool isBindLongPressMenu = false;
    bool isShow = false;
    MenuPreviewMode isShowPreviewMode = MenuPreviewMode::NONE;
    MenuPreviewMode longPressPreviewMode = MenuPreviewMode::NONE;
    bool IsNotNeedShowPreview() const
    {
        return (isBindCustomMenu && isShow) || isBindLongPressMenu;
    }
};

struct PreparedInfoForDrag {
    bool isMenuShow = false;
    int32_t badgeNumber = 0;
    float previewScale = 1.0f;
    bool isNeedCreateTiled = false;
    OffsetF dragPreviewOffsetToScreen = { 0.0f, 0.0f };
    OffsetF dragMovePosition = { 0.0f, 0.0f };
    RefPtr<PixelMap> pixelMap;
    RefPtr<FrameNode> imageNode;
};

struct PreparedAsyncCtxForAnimate {
    int32_t containerId = -1;
    bool hasTouchPoint = false;
    DragPointerEvent dragPointerEvent;
    DragPreviewOption dragPreviewOption;
    DimensionOffset touchPoint = DimensionOffset(0.0_vp, 0.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
};

struct DragframeNodeInfo {
    WeakPtr<FrameNode> frameNode;
    std::vector<RefPtr<FrameNode>> gatherFrameNode;
};

using OnDragStartFunc = std::function<DragDropBaseInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>;
using OnDragDropFunc = std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>;
using OnChildTouchTestFunc = std::function<TouchResult(const std::vector<TouchTestInfo>& touchInfo)>;
using OnReponseRegionFunc = std::function<void(const std::vector<DimensionRect>&)>;
struct DragDropInfo {
    RefPtr<UINode> customNode;
    RefPtr<PixelMap> pixelMap;
    std::string extraInfo;
    // The inspectorId acts as a preview surrogate identifier which is used
    // to retrieve a preview image for the item being dragged.
    std::string inspectorId;
    std::function<RefPtr<UINode>()> buildFunc;
    bool onlyForLifting = false;
    bool delayCreating = false;
};

using DragNotifyMsgCore = OHOS::Ace::DragNotifyMsg;
using OnDragCallbackCore = std::function<void(const DragNotifyMsgCore&)>;
constexpr float PIXELMAP_WIDTH_RATE = -0.5f;
constexpr float PIXELMAP_HEIGHT_RATE = -0.2f;
constexpr float PIXELMAP_DEFALUT_LIMIT_SCALE = 0.5f;
constexpr float PIXELMAP_DRAG_WGR_TEXT_SCALE = 2.0f;
constexpr float PIXELMAP_DRAG_WGR_SCALE = 3.0f;
constexpr float DEFALUT_DRAG_PPIXELMAP_SCALE = 1.05f;
constexpr float PIXELMAP_DRAG_DEFAULT_HEIGHT = -28.0f;

class EventHub;

// The gesture event hub is mainly used to handle common gesture events.
class ACE_FORCE_EXPORT GestureEventHub : public Referenced {
public:
    explicit GestureEventHub(const WeakPtr<EventHub>& eventHub);
    ~GestureEventHub() override = default;

    void AddGesture(const RefPtr<NG::Gesture>& gesture);
    // call by CAPI do distinguish with AddGesture called by ARKUI;
    void ClearGesture();
    void AttachGesture(const RefPtr<NG::Gesture>& gesture);
    void RemoveGesture(const RefPtr<NG::Gesture>& gesture);
    void RemoveGesturesByTag(const std::string& gestureTag);
    void ClearModifierGesture();
    void AddScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent);
    void RemoveScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent);
    void AddScrollEdgeEffect(const Axis& axis, RefPtr<ScrollEdgeEffect>& scrollEffect);
    void RemoveScrollEdgeEffect(const RefPtr<ScrollEdgeEffect>& scrollEffect);
    void AddPreviewMenuHandleDragEnd(GestureEventFunc&& actionEnd);
    // Set by user define, which will replace old one.
    void SetTouchEvent(TouchEventFunc&& touchEventFunc);
    // Set by node container.
    void SetOnTouchEvent(TouchEventFunc&& touchEventFunc);
    // Set by JS FrameNode.
    void SetJSFrameNodeOnTouchEvent(TouchEventFunc&& touchEventFunc);
    void AddTouchEvent(const RefPtr<TouchEventImpl>& touchEvent);
    void AddTouchAfterEvent(const RefPtr<TouchEventImpl>& touchEvent);
    void RemoveTouchEvent(const RefPtr<TouchEventImpl>& touchEvent);
    void SetFocusClickEvent(GestureEventFunc&& clickEvent);
    bool IsClickable() const;
    bool IsUserClickable() const;
    bool IsAccessibilityClickable();
    bool IsAccessibilityLongClickable();
    bool ActClick(std::shared_ptr<JsonValue> secComphandle = nullptr);
    void CheckClickActuator();
    // Set by user define, which will replace old one.
    void SetUserOnClick(GestureEventFunc&& clickEvent,
        double distanceThreshold = std::numeric_limits<double>::infinity());
    void SetNodeClickDistance(double distanceThreshold = std::numeric_limits<double>::infinity());
     // Set by JS FrameNode.
    void SetJSFrameNodeOnClick(GestureEventFunc&& clickEvent);
    void SetOnGestureJudgeBegin(GestureJudgeFunc&& gestureJudgeFunc);
    void SetOnTouchIntercept(TouchInterceptFunc&& touchInterceptFunc);
    TouchInterceptFunc GetOnTouchIntercept() const;
    void SetShouldBuildinRecognizerParallelWithFunc(ShouldBuiltInRecognizerParallelWithFunc&& parallelGestureToFunc);
    ShouldBuiltInRecognizerParallelWithFunc GetParallelInnerGestureToFunc() const;
    void SetOnGestureRecognizerJudgeBegin(GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc);
    GestureRecognizerJudgeFunc GetOnGestureRecognizerJudgeBegin() const;
    void SetOnGestureJudgeNativeBegin(GestureJudgeFunc&& gestureJudgeFunc);
    GestureJudgeFunc GetOnGestureJudgeBeginCallback() const;
    GestureJudgeFunc GetOnGestureJudgeNativeBeginCallback() const;
    // When the event param is undefined, it will clear the callback.
    void ClearUserOnClick();
    void ClearUserOnTouch();
    void ClearJSFrameNodeOnClick();
    void ClearJSFrameNodeOnTouch();
    void AddClickEvent(const RefPtr<ClickEvent>& clickEvent);
    void AddClickAfterEvent(const RefPtr<ClickEvent>& clickEvent);
    void RemoveClickEvent(const RefPtr<ClickEvent>& clickEvent);
    bool IsClickEventsEmpty() const;
    GestureEventFunc GetClickEvent();
    void BindMenu(GestureEventFunc&& showMenu);
    bool IsLongClickable() const;
    void SetRedirectClick(bool redirectClick);
    bool ActLongClick();
    void SetLongPressEvent(const RefPtr<LongPressEvent>& event, bool isForDrag = false, bool isDisableMouseLeft = false,
        int32_t duration = 500);
    // Set by user define, which will replace old one.
    void SetPanEvent(const RefPtr<PanEvent>& panEvent, PanDirection direction, int32_t fingers, Dimension distance);
    void AddPanEvent(const RefPtr<PanEvent>& panEvent, PanDirection direction, int32_t fingers, Dimension distance);
    void RemovePanEvent(const RefPtr<PanEvent>& panEvent);
    void SetPanEventType(GestureTypeName typeName);
    // Set by user define, which will replace old one.
    void SetDragEvent(const RefPtr<DragEvent>& dragEvent, PanDirection direction, int32_t fingers, Dimension distance);
    void SetDragDropEvent();
    void SetCustomDragEvent(
        const RefPtr<DragEvent>& dragEvent, PanDirection direction, int32_t fingers, Dimension distance);
    bool HasDragEvent() const;
    // the return value means prevents event bubbling.
    bool ProcessTouchTestHit(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        TouchTestResult& innerTargets, TouchTestResult& finalResult, int32_t touchId, const PointF& localPoint,
        const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult);
    bool ProcessEventTouchTestHit(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        TouchTestResult& innerTargets, TouchTestResult& finalResult, int32_t touchId, const PointF& localPoint,
        const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult);
    bool ProcessDragEventTouchTestHit(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        TouchTestResult& innerTargets, TouchTestResult& finalResult, int32_t touchId, const PointF& localPoint,
        const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult);
    RefPtr<FrameNode> GetFrameNode() const;
    void OnContextAttached() {}
    static std::string GetHitTestModeStr(const RefPtr<GestureEventHub>& GestureEventHub);
    HitTestMode GetHitTestMode() const;
    void SetHitTestMode(HitTestMode hitTestMode);
    void RemoveDragEvent();
    void CombineIntoExclusiveRecognizer(
        const PointF& globalPoint, const PointF& localPoint, TouchTestResult& result, int32_t touchId);
    const std::vector<DimensionRect>& GetResponseRegion() const;
    const std::vector<DimensionRect>& GetMouseResponseRegion() const;
    void SetResponseRegionFunc(const OnReponseRegionFunc& func);
    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion);
    void SetOnTouchTestFunc(OnChildTouchTestFunc&& callback);
    const OnChildTouchTestFunc& GetOnTouchTestFunc();
    void SetMouseResponseRegion(const std::vector<DimensionRect>& mouseResponseRegion);
    void AddResponseRect(const DimensionRect& responseRect);
    void RemoveLastResponseRect();
    bool GetTouchable() const;
    void SetTouchable(bool touchable);
    void SetThumbnailCallback(std::function<void(Offset)>&& callback);
    bool IsDragForbidden() const;
    void SetDragForbiddenForcely(bool isDragForbidden);
    bool GetTextDraggable() const;
    void SetTextDraggable(bool draggable);
    void SetIsTextDraggable(bool isTextDraggable);
    bool GetIsTextDraggable();
    void SetPreviewMode(MenuPreviewMode mode);
    MenuPreviewMode GetPreviewMode();
    void SetContextMenuShowStatus(bool contextMenuShowStatus);
    bool GetContextMenuShowStatus();
    void SetMenuBindingType(MenuBindingType menuBindingType);
    MenuBindingType GetMenuBindingType();
    void SetPixelMap(RefPtr<PixelMap> pixelMap);
    RefPtr<PixelMap> GetPixelMap();
    void SetDragPreviewPixelMap(RefPtr<PixelMap> pixelMap);
    RefPtr<LongPressRecognizer> GetLongPressRecognizer() const;
    void SetIsAllowMouse(bool isAllowMouse) const;
    const RefPtr<ClickEventActuator>& GetUserClickEventActuator();
    int32_t SetDragData(const RefPtr<UnifiedData>& unifiedData, std::string& udKey);
    OnDragCallbackCore GetDragCallback(const RefPtr<PipelineBase>& context, const WeakPtr<EventHub>& hub);
    void GenerateMousePixelMap(const GestureEvent& info);
    OffsetF GetPixelMapOffset(const GestureEvent& info, const SizeF& size, const PreparedInfoForDrag& dragInfoData,
        const float scale = 1.0f, const RectF& innerRect = RectF()) const;
    void CalcFrameNodeOffsetAndSize(const RefPtr<FrameNode> frameNode, bool isMenuShow);
    OffsetF GetDragPreviewInitPositionToScreen(const RefPtr<PipelineBase>& context, PreparedInfoForDrag& data);
    int32_t GetBadgeNumber(const RefPtr<UnifiedData>& unifiedData);
    bool TryDoDragStartAnimation(const RefPtr<PipelineBase>& context, const RefPtr<Subwindow>& subwindow,
        const GestureEvent& info, PreparedInfoForDrag& data);
    float GetDefaultPixelMapScale(
        const RefPtr<FrameNode>& frameNode, const GestureEvent& info, bool isMenuShow, RefPtr<PixelMap> pixelMap);
    RefPtr<PixelMap> GetPreScaledPixelMapIfExist(float targetScale, RefPtr<PixelMap> defaultPixelMap);
    float GetPixelMapScale(const int32_t height, const int32_t width) const;
    bool IsPixelMapNeedScale() const;
    bool CheckAllowDrag(const GestureEvent& info, const RefPtr<PipelineBase>& context,
        const RefPtr<FrameNode>& frameNode);
    RefPtr<OHOS::Ace::DragEvent> CreateDragEvent(const GestureEvent& info, const RefPtr<PipelineBase>& context,
        const RefPtr<FrameNode>& frameNode);
    void InitDragDropEvent();
    void HandleOnDragStart(const GestureEvent& info);
    void HandleDragThroughMouse(const RefPtr<FrameNode> frameNode);
    void HandleDragThroughTouch(const RefPtr<FrameNode> frameNode);
    void HandleDragEndAction(const DragframeNodeInfo& info);
    void HandleOnDragUpdate(const GestureEvent& info);
    void HandleOnDragEnd(const GestureEvent& info);
    void HandleOnDragCancel();
    void StartLongPressActionForWeb();
    void CancelDragForWeb();
    void StartDragTaskForWeb();
    void ResetDragActionForWeb();
    void OnModifyDone();
    bool KeyBoardShortCutClick(const KeyEvent& event, const WeakPtr<NG::FrameNode>& node);
    bool IsAllowedDrag(RefPtr<EventHub> eventHub);
    void HandleNotAllowDrag(const GestureEvent& info);
    RefPtr<DragEventActuator> GetDragEventActuator();
    bool GetMonopolizeEvents() const;
    void SetMonopolizeEvents(bool monopolizeEvents);
    virtual RefPtr<NGGestureRecognizer> PackInnerRecognizer(
        const Offset& offset, std::list<RefPtr<NGGestureRecognizer>>& innerRecognizers, int32_t touchId,
        const RefPtr<TargetComponent>& targetComponent);
    void CleanExternalRecognizers();
    void CleanInnerRecognizer();
    void CleanNodeRecognizer();
    void CopyGestures(const RefPtr<GestureEventHub>& gestureEventHub);
    void CopyEvent(const RefPtr<GestureEventHub>& gestureEventHub);
    int32_t RegisterCoordinationListener(const RefPtr<PipelineBase>& context);
    bool IsTextCategoryComponent(const std::string& frameTag);
    DragDropInfo GetDragDropInfo(const GestureEvent& info, const RefPtr<FrameNode> frameNode,
        DragDropInfo& dragPreviewInfo, const RefPtr<OHOS::Ace::DragEvent>& dragEvent);
    RefPtr<UnifiedData> GetUnifiedData(const std::string& frameTag, DragDropInfo& dragDropInfo,
        const RefPtr<OHOS::Ace::DragEvent>& dragEvent);
    int32_t GetSelectItemSize();
    bool IsNeedSwitchToSubWindow(const PreparedInfoForDrag& dragInfoData) const;
    RefPtr<PixelMap> GetDragPreviewPixelMap();
    void SetDragGatherPixelMaps(const GestureEvent& info);
    void SetMouseDragGatherPixelMaps();
    void SetNotMouseDragGatherPixelMaps();
    void FireCustomerOnDragEnd(const RefPtr<PipelineBase>& context, const WeakPtr<EventHub>& hub);
    void SetMouseDragMonitorState(bool state);
    bool ParsePixelMapAsync(DragDropInfo& dragDropInfo, const DragDropInfo& dragPreviewInfo,
        const GestureEvent& info);
    void DoOnDragStartHandling(const GestureEvent& info, const RefPtr<FrameNode> frameNode,
        DragDropInfo dragDropInfo, const RefPtr<OHOS::Ace::DragEvent>& event,
        DragDropInfo dragPreviewInfo, const RefPtr<PipelineContext>& pipeline);
    void HideMenu();
#if defined(PIXEL_MAP_SUPPORTED)
    static void PrintBuilderNode(const RefPtr<UINode>& customNode);
    static void PrintIfImageNode(
        const RefPtr<UINode>& builderNode, int32_t depth, bool& hasImageNode, std::list<RefPtr<FrameNode>>& imageNodes);
    static void CheckImageDecode(std::list<RefPtr<FrameNode>>& imageNodes);
    bool StartDragForCustomBuilderSync(const GestureEvent& info, const RefPtr<PipelineBase>& pipeline,
        const RefPtr<FrameNode> frameNode, DragDropInfo dragDropInfo, const RefPtr<OHOS::Ace::DragEvent>& event);
    void StartDragForCustomBuilder(const GestureEvent& info, const RefPtr<PipelineBase>& pipeline,
        const RefPtr<FrameNode> frameNode, DragDropInfo dragDropInfo, const RefPtr<OHOS::Ace::DragEvent>& event);
#endif
    void SetMenuPreviewScale(float menuPreviewScale);
    float GetMenuPreviewScale() const;
    void SetBindMenuStatus(bool setIsShow, bool isShow, MenuPreviewMode previewMode);
    const BindMenuStatus& GetBindMenuStatus() const;
    bool WillRecreateGesture() const;

    bool parallelCombineClick = false;
    RefPtr<ParallelRecognizer> innerParallelRecognizer_;

    bool IsGestureEmpty() const;

    bool IsPanEventEmpty() const;

    void SetExcludedAxisForPanEvent(bool isExcludedAxis);

    void DumpVelocityInfoFroPanEvent(int32_t fingerId);
private:
    void ProcessTouchTestHierarchy(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        std::list<RefPtr<NGGestureRecognizer>>& innerRecognizers, TouchTestResult& finalResult, int32_t touchId,
        const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult);

    void UpdateGestureHierarchy();
    void UpdateModifierGestureHierarchy();

    void AddGestureToGestureHierarchy(const RefPtr<NG::Gesture>& gesture, bool isModifier);

    // old path.
    void UpdateExternalNGGestureRecognizer();

    OnAccessibilityEventFunc GetOnAccessibilityEventFunc();

    void OnDragStart(const GestureEvent& info, const RefPtr<PipelineBase>& context, const RefPtr<FrameNode> frameNode,
        DragDropInfo dragDropInfo, const RefPtr<OHOS::Ace::DragEvent>& dragEvent);
    void StartVibratorByDrag(const RefPtr<FrameNode>& frameNode);
    void UpdateExtraInfo(const RefPtr<FrameNode>& frameNode, std::unique_ptr<JsonValue>& arkExtraInfoJson, float scale,
        const PreparedInfoForDrag& dragInfoData);
    void ProcessMenuPreviewScale(const RefPtr<FrameNode> imageNode, float& scale, float previewScale,
        float windowScale, float defaultMenuPreviewScale);

    template<typename T>
    const RefPtr<T> GetAccessibilityRecognizer();

    template<typename T>
    const RefPtr<T> AccessibilityRecursionSearchRecognizer(const RefPtr<NGGestureRecognizer>& recognizer);

    void ProcessParallelPriorityGesture(const Offset& offset, int32_t touchId,
        const RefPtr<TargetComponent>& targetComponent, const RefPtr<FrameNode>& host,
        RefPtr<NGGestureRecognizer>& current, std::list<RefPtr<NGGestureRecognizer>>& recognizers,
        int32_t& parallelIndex);

    void ProcessExternalExclusiveRecognizer(const Offset& offset, int32_t touchId,
        const RefPtr<TargetComponent>& targetComponent, const RefPtr<FrameNode>& host, GesturePriority priority,
        RefPtr<NGGestureRecognizer>& current, std::list<RefPtr<NGGestureRecognizer>>& recognizers,
        int32_t& exclusiveIndex);

    WeakPtr<EventHub> eventHub_;
    RefPtr<ScrollableActuator> scrollableActuator_;
    RefPtr<TouchEventActuator> touchEventActuator_;
    RefPtr<ClickEventActuator> clickEventActuator_;
    RefPtr<ClickEventActuator> userParallelClickEventActuator_;
    RefPtr<LongPressEventActuator> longPressEventActuator_;
    RefPtr<PanEventActuator> panEventActuator_;
    RefPtr<DragEventActuator> dragEventActuator_;
    RefPtr<ExclusiveRecognizer> innerExclusiveRecognizer_;
    RefPtr<ExclusiveRecognizer> nodeExclusiveRecognizer_;
    RefPtr<ParallelRecognizer> nodeParallelRecognizer_;
    std::vector<RefPtr<ExclusiveRecognizer>> externalExclusiveRecognizer_;
    std::vector<RefPtr<ParallelRecognizer>> externalParallelRecognizer_;
    RefPtr<DragDropProxy> dragDropProxy_;

    // Set by use gesture, priorityGesture and parallelGesture attribute function.
    std::list<RefPtr<NG::Gesture>> gestures_;
    // set by CAPI or modifier do distinguish with gestures_;
    std::list<RefPtr<NG::Gesture>> modifierGestures_;
    std::list<RefPtr<NG::Gesture>> backupGestures_;
    std::list<RefPtr<NG::Gesture>> backupModifierGestures_;
    std::list<RefPtr<NGGestureRecognizer>> gestureHierarchy_;
    std::list<RefPtr<NGGestureRecognizer>> modifierGestureHierarchy_;

    // used in bindMenu, need to delete the old callback when bindMenu runs again
    RefPtr<ClickEvent> showMenu_;

    HitTestMode hitTestMode_ = HitTestMode::HTMDEFAULT;
    bool recreateGesture_ = true;
    bool needRecollect_ = false;
    bool isResponseRegion_ = false;
    std::vector<DimensionRect> responseRegion_;
    std::vector<DimensionRect> mouseResponseRegion_;
    bool touchable_ = true;
    RefPtr<PixelMap> pixelMap_;

    // Save dragPreview pixelMap of user setting, transfer to drag framework on drag start.
    RefPtr<PixelMap> dragPreviewPixelMap_;

    OffsetF frameNodeOffset_;
    SizeF frameNodeSize_;
    std::shared_ptr<GestureEvent> gestureInfoForWeb_;
    bool isReceivedDragGestureInfo_ = false;
    OnChildTouchTestFunc onChildTouchTestFunc_;
    OnReponseRegionFunc responseRegionFunc_;
    bool redirectClick_  = false;

    GestureJudgeFunc gestureJudgeFunc_;
    GestureJudgeFunc gestureJudgeNativeFunc_;

    TouchInterceptFunc touchInterceptFunc_;

    ShouldBuiltInRecognizerParallelWithFunc shouldBuildinRecognizerParallelWithFunc_;
    GestureRecognizerJudgeFunc gestureRecognizerJudgeFunc_;

    MenuPreviewMode previewMode_ = MenuPreviewMode::NONE;
    // the value from show parameter of context menu, which is controlled by caller manually
    bool contextMenuShowStatus_  = false;
    MenuBindingType menuBindingType_  = MenuBindingType::LONG_PRESS;
    BindMenuStatus bindMenuStatus_;
    DragframeNodeInfo dragframeNodeInfo_;
    // disable drag for the node itself and its all children
    bool isDragForbiddenForWholeSubTree_ = false;
    bool textDraggable_ = false;
    bool isTextDraggable_ = false;
    bool monopolizeEvents_ = false;
    float menuPreviewScale_ = DEFALUT_DRAG_PPIXELMAP_SCALE;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_HUB_H
