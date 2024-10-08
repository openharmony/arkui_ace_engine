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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_HUB_H

#include <list>
#include <vector>

#include "base/geometry/ng/point_t.h"
#include "base/memory/referenced.h"
#include "core/common/interaction/interaction_data.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/event/drag_event.h"
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
        return (isBindCustomMenu && isShow && isShowPreviewMode!= MenuPreviewMode::NONE) ||
            (isBindLongPressMenu && longPressPreviewMode != MenuPreviewMode::NONE);
    }
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

    void AddGesture(const RefPtr<NG::Gesture>& gesture)
    {
        if (!recreateGesture_) {
            gestures_.clear();
            backupGestures_.clear();
        }
        gestures_.emplace_back(gesture);
        backupGestures_.emplace_back(gesture);
        recreateGesture_ = true;
    }

    // call by CAPI do distinguish with AddGesture called by ARKUI;
    void AttachGesture(const RefPtr<NG::Gesture>& gesture)
    {
        modifierGestures_.emplace_back(gesture);
        backupModifierGestures_.emplace_back(gesture);
        UpdateModifierGestureHierarchy();
    }

    void RemoveGesture(const RefPtr<NG::Gesture>& gesture)
    {
        modifierGestures_.remove(gesture);
        backupModifierGestures_.remove(gesture);
        UpdateModifierGestureHierarchy();
    }

    void RemoveGesturesByTag(const std::string& gestureTag);

    void ClearModifierGesture();

    void AddScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent)
    {
        if (!scrollableActuator_) {
            scrollableActuator_ = MakeRefPtr<ScrollableActuator>(WeakClaim(this));
        }
        scrollableActuator_->AddScrollableEvent(scrollableEvent);
    }

    void RemoveScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent)
    {
        if (!scrollableActuator_) {
            return;
        }
        scrollableActuator_->RemoveScrollableEvent(scrollableEvent);
    }

    void AddScrollEdgeEffect(const Axis& axis, RefPtr<ScrollEdgeEffect>& scrollEffect)
    {
        if (!scrollableActuator_) {
            scrollableActuator_ = MakeRefPtr<ScrollableActuator>(WeakClaim(this));
        }
        scrollableActuator_->AddScrollEdgeEffect(axis, scrollEffect);
    }

    void RemoveScrollEdgeEffect(const RefPtr<ScrollEdgeEffect>& scrollEffect)
    {
        if (!scrollableActuator_) {
            return;
        }
        scrollableActuator_->RemoveScrollEdgeEffect(scrollEffect);
    }

    void AddPreviewMenuHandleDragEnd(GestureEventFunc&& actionEnd)
    {
        if (!scrollableActuator_) {
            scrollableActuator_ = MakeRefPtr<ScrollableActuator>(WeakClaim(this));
        }
        scrollableActuator_->AddPreviewMenuHandleDragEnd(std::move(actionEnd));
    }

    // Set by user define, which will replace old one.
    void SetTouchEvent(TouchEventFunc&& touchEventFunc)
    {
        if (!touchEventActuator_) {
            touchEventActuator_ = MakeRefPtr<TouchEventActuator>();
        }
        touchEventActuator_->ReplaceTouchEvent(std::move(touchEventFunc));
    }

    // Set by node container.
    void SetOnTouchEvent(TouchEventFunc&& touchEventFunc);
    // Set by JS FrameNode.
    void SetJSFrameNodeOnTouchEvent(TouchEventFunc&& touchEventFunc);

    void AddTouchEvent(const RefPtr<TouchEventImpl>& touchEvent)
    {
        if (!touchEventActuator_) {
            touchEventActuator_ = MakeRefPtr<TouchEventActuator>();
        }
        touchEventActuator_->AddTouchEvent(touchEvent);
    }

    void AddTouchAfterEvent(const RefPtr<TouchEventImpl>& touchEvent)
    {
        if (!touchEventActuator_) {
            touchEventActuator_ = MakeRefPtr<TouchEventActuator>();
        }
        touchEventActuator_->AddTouchAfterEvent(touchEvent);
    }

    void RemoveTouchEvent(const RefPtr<TouchEventImpl>& touchEvent)
    {
        if (!touchEventActuator_) {
            return;
        }
        touchEventActuator_->RemoveTouchEvent(touchEvent);
    }

    void SetFocusClickEvent(GestureEventFunc&& clickEvent);

    bool IsClickable() const
    {
        return clickEventActuator_ != nullptr;
    }

    bool IsUserClickable() const
    {
        return clickEventActuator_ != nullptr && clickEventActuator_->IsUserClickable();
    }

    bool IsAccessibilityClickable();
    bool IsAccessibilityLongClickable();

    bool ActClick(std::shared_ptr<JsonValue> secComphandle = nullptr);

    void CheckClickActuator();
    // Set by user define, which will replace old one.
    void SetUserOnClick(GestureEventFunc&& clickEvent,
        double distanceThreshold = std::numeric_limits<double>::infinity());

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

    GestureJudgeFunc GetOnGestureJudgeBeginCallback() const
    {
        return gestureJudgeFunc_;
    }

    GestureJudgeFunc GetOnGestureJudgeNativeBeginCallback() const
    {
        return gestureJudgeNativeFunc_;
    }

    // When the event param is undefined, it will clear the callback.
    void ClearUserOnClick();
    void ClearUserOnTouch();


    void ClearJSFrameNodeOnClick();
    void ClearJSFrameNodeOnTouch();

    void AddClickEvent(const RefPtr<ClickEvent>& clickEvent,
        double distanceThreshold = std::numeric_limits<double>::infinity());
    void AddClickAfterEvent(const RefPtr<ClickEvent>& clickEvent);

    void RemoveClickEvent(const RefPtr<ClickEvent>& clickEvent)
    {
        if (!clickEventActuator_) {
            return;
        }
        clickEventActuator_->RemoveClickEvent(clickEvent);
    }

    bool IsClickEventsEmpty() const
    {
        if (!clickEventActuator_) {
            return true;
        }
        return clickEventActuator_->IsClickEventsEmpty();
    }

    GestureEventFunc GetClickEvent()
    {
        if (!IsClickable()) {
            return nullptr;
        }
        return clickEventActuator_->GetClickEvent();
    }

    void BindMenu(GestureEventFunc&& showMenu);

    bool IsLongClickable() const
    {
        return longPressEventActuator_ != nullptr;
    }

    void SetRedirectClick(bool redirectClick)
    {
        redirectClick_ = redirectClick;
    }

    bool ActLongClick();

    void SetLongPressEvent(const RefPtr<LongPressEvent>& event, bool isForDrag = false, bool isDisableMouseLeft = false,
        int32_t duration = 500)
    {
        if (!longPressEventActuator_) {
            longPressEventActuator_ = MakeRefPtr<LongPressEventActuator>(WeakClaim(this));
            longPressEventActuator_->SetOnAccessibility(GetOnAccessibilityEventFunc());
        }
        longPressEventActuator_->SetLongPressEvent(event, isForDrag, isDisableMouseLeft);
        longPressEventActuator_->SetDuration(duration);
    }

    // Set by user define, which will replace old one.
    void SetPanEvent(const RefPtr<PanEvent>& panEvent, PanDirection direction, int32_t fingers, Dimension distance)
    {
        if (!panEventActuator_) {
            panEventActuator_ =
                MakeRefPtr<PanEventActuator>(WeakClaim(this), direction, fingers, distance.ConvertToPx());
        }
        panEventActuator_->ReplacePanEvent(panEvent);
    }

    void AddPanEvent(const RefPtr<PanEvent>& panEvent, PanDirection direction, int32_t fingers, Dimension distance)
    {
        if (!panEventActuator_ || direction.type != panEventActuator_->GetDirection().type) {
            panEventActuator_ =
                MakeRefPtr<PanEventActuator>(WeakClaim(this), direction, fingers, distance.ConvertToPx());
        }
        panEventActuator_->AddPanEvent(panEvent);
    }

    void RemovePanEvent(const RefPtr<PanEvent>& panEvent)
    {
        if (!panEventActuator_) {
            return;
        }
        panEventActuator_->RemovePanEvent(panEvent);
    }

    void SetPanEventType(GestureTypeName typeName)
    {
        CHECK_NULL_VOID(panEventActuator_);
        panEventActuator_->SetPanEventType(typeName);
    }

    // Set by user define, which will replace old one.
    void SetDragEvent(const RefPtr<DragEvent>& dragEvent, PanDirection direction, int32_t fingers, Dimension distance)
    {
        if (!dragEventActuator_) {
            dragEventActuator_ =
                MakeRefPtr<DragEventActuator>(WeakClaim(this), direction, fingers, distance.ConvertToPx());
        }
        dragEventActuator_->ReplaceDragEvent(dragEvent);
    }

    void SetCustomDragEvent(
        const RefPtr<DragEvent>& dragEvent, PanDirection direction, int32_t fingers, Dimension distance)
    {
        if (!dragEventActuator_) {
            dragEventActuator_ =
                MakeRefPtr<DragEventActuator>(WeakClaim(this), direction, fingers, distance.ConvertToPx());
        }
        dragEventActuator_->SetCustomDragEvent(dragEvent);
    }

    bool HasDragEvent() const
    {
        return dragEventActuator_ && dragEventActuator_->HasDragEvent();
    }

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

    std::string GetHitTestModeStr() const;

    HitTestMode GetHitTestMode() const
    {
        return hitTestMode_;
    }

    void SetHitTestMode(HitTestMode hitTestMode)
    {
        hitTestMode_ = hitTestMode;
    }

    void RemoveDragEvent()
    {
        if (!dragEventActuator_) {
            return;
        }
        dragEventActuator_->ClearDragEvent();
    }

    void CombineIntoExclusiveRecognizer(
        const PointF& globalPoint, const PointF& localPoint, TouchTestResult& result, int32_t touchId);

    const std::vector<DimensionRect>& GetResponseRegion() const
    {
        return responseRegion_;
    }

    const std::vector<DimensionRect>& GetMouseResponseRegion() const
    {
        return mouseResponseRegion_;
    }

    void SetResponseRegionFunc(const OnReponseRegionFunc& func)
    {
        responseRegionFunc_ = func;
    }

    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion);

    void SetOnTouchTestFunc(OnChildTouchTestFunc&& callback)
    {
        onChildTouchTestFunc_ = callback;
    }

    const OnChildTouchTestFunc& GetOnTouchTestFunc()
    {
        return onChildTouchTestFunc_;
    }

    void SetMouseResponseRegion(const std::vector<DimensionRect>& mouseResponseRegion)
    {
        mouseResponseRegion_ = mouseResponseRegion;
        if (!mouseResponseRegion_.empty()) {
            isResponseRegion_ = true;
        }
    }

    void AddResponseRect(const DimensionRect& responseRect)
    {
        responseRegion_.emplace_back(responseRect);
        isResponseRegion_ = true;

        if (responseRegionFunc_) {
            responseRegionFunc_(responseRegion_);
        }
    }

    void RemoveLastResponseRect();

    bool GetTouchable() const
    {
        return touchable_;
    }

    void SetTouchable(bool touchable)
    {
        touchable_ = touchable;
    }

    void SetThumbnailCallback(std::function<void(Offset)>&& callback)
    {
        if (dragEventActuator_) {
            dragEventActuator_->SetThumbnailCallback(std::move(callback));
        }
    }

    bool IsDragForbidden();

    void SetDragForbiddenForcely(bool isDragForbidden);

    bool GetTextDraggable() const
    {
        return textDraggable_;
    }

    void SetTextDraggable(bool draggable)
    {
        textDraggable_ = draggable;
    }

    void SetIsTextDraggable(bool isTextDraggable)
    {
        isTextDraggable_ = isTextDraggable;
    }

    bool GetIsTextDraggable()
    {
        return isTextDraggable_;
    }

    void SetPreviewMode(MenuPreviewMode mode)
    {
        previewMode_ = mode;
    }

    MenuPreviewMode GetPreviewMode()
    {
        return previewMode_;
    }

    void SetContextMenuShowStatus(bool contextMenuShowStatus)
    {
        contextMenuShowStatus_ = contextMenuShowStatus;
    }

    bool GetContextMenuShowStatus()
    {
        return contextMenuShowStatus_;
    }

    void SetMenuBindingType(MenuBindingType menuBindingType)
    {
        menuBindingType_ = menuBindingType;
    }

    MenuBindingType GetMenuBindingType()
    {
        return menuBindingType_;
    }

    void SetPixelMap(RefPtr<PixelMap> pixelMap)
    {
        pixelMap_ = pixelMap;
    }

    RefPtr<PixelMap> GetPixelMap()
    {
        return pixelMap_;
    }

    void SetDragPreviewPixelMap(RefPtr<PixelMap> pixelMap)
    {
        dragPreviewPixelMap_ = pixelMap;
    }

    RefPtr<LongPressRecognizer> GetLongPressRecognizer() const
    {
        CHECK_NULL_RETURN(longPressEventActuator_, nullptr);
        return longPressEventActuator_->GetLongPressRecognizer();
    }

    void SetIsAllowMouse(bool isAllowMouse) const
    {
        CHECK_NULL_VOID(panEventActuator_);
        panEventActuator_->SetIsAllowMouse(isAllowMouse);
    }

    const RefPtr<ClickEventActuator>& GetUserClickEventActuator()
    {
        return userParallelClickEventActuator_;
    }

    int32_t SetDragData(const RefPtr<UnifiedData>& unifiedData, std::string& udKey);
    OnDragCallbackCore GetDragCallback(const RefPtr<PipelineBase>& context, const WeakPtr<EventHub>& hub);
    void GenerateMousePixelMap(const GestureEvent& info);
    OffsetF GetPixelMapOffset(const GestureEvent& info, const SizeF& size, const float scale = 1.0f,
        bool isCalculateInSubwindow = false) const;
    RefPtr<PixelMap> GetPreScaledPixelMapIfExist(float targetScale, RefPtr<PixelMap> defaultPixelMap);
    float GetPixelMapScale(const int32_t height, const int32_t width) const;
    bool IsPixelMapNeedScale() const;
    void InitDragDropEvent();
    void HandleOnDragStart(const GestureEvent& info);
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
    void HandleNotallowDrag(const GestureEvent& info);

    RefPtr<DragEventActuator> GetDragEventActuator()
    {
        return dragEventActuator_;
    }

    bool GetMonopolizeEvents() const;

    void SetMonopolizeEvents(bool monopolizeEvents);
    virtual RefPtr<NGGestureRecognizer> PackInnerRecognizer(
        const Offset& offset, std::list<RefPtr<NGGestureRecognizer>>& innerRecognizers, int32_t touchId,
        const RefPtr<TargetComponent>& targetComponent);

    void CleanExternalRecognizers()
    {
        externalParallelRecognizer_.clear();
        externalExclusiveRecognizer_.clear();
    }

    void CleanInnerRecognizer()
    {
        innerExclusiveRecognizer_ = nullptr;
    }

    void CleanNodeRecognizer()
    {
        nodeParallelRecognizer_ = nullptr;
        nodeExclusiveRecognizer_ = nullptr;
    }

    bool parallelCombineClick = false;
    RefPtr<ParallelRecognizer> innerParallelRecognizer_;

    void CopyGestures(const RefPtr<GestureEventHub>& gestureEventHub);

    void CopyEvent(const RefPtr<GestureEventHub>& gestureEventHub);

    int32_t RegisterCoordinationListener(const RefPtr<PipelineBase>& context);

    bool IsTextCategoryComponent(const std::string& frameTag);

    DragDropInfo GetDragDropInfo(const GestureEvent& info, const RefPtr<FrameNode> frameNode,
        DragDropInfo& dragPreviewInfo, const RefPtr<OHOS::Ace::DragEvent>& dragEvent);

    RefPtr<UnifiedData> GetUnifiedData(const std::string& frameTag, DragDropInfo& dragDropInfo,
        const RefPtr<OHOS::Ace::DragEvent>& dragEvent);
    int32_t GetSelectItemSize();

    bool IsNeedSwitchToSubWindow() const;
    RefPtr<PixelMap> GetDragPreviewPixelMap()
    {
        return dragPreviewPixelMap_;
    }
    void SetDragGatherPixelMaps(const GestureEvent& info);
    void SetMouseDragGatherPixelMaps();
    void SetNotMouseDragGatherPixelMaps();
    void FireCustomerOnDragEnd(const RefPtr<PipelineBase>& context, const WeakPtr<EventHub>& hub);
    void SetMouseDragMonitorState(bool state);
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
    static bool IsAllowedDrag(const RefPtr<FrameNode>& frameNode);

    void SetMenuPreviewScale(float menuPreviewScale)
    {
        menuPreviewScale_ = menuPreviewScale;
    }

    float GetMenuPreviewScale() const
    {
        return menuPreviewScale_;
    }
    
    void SetBindMenuStatus(bool setIsShow, bool isShow, MenuPreviewMode previewMode);
    const BindMenuStatus& GetBindMenuStatus() const
    {
        return bindMenuStatus_;
    }

    bool WillRecreateGesture() const
    {
        return recreateGesture_;
    }

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
    void UpdateExtraInfo(const RefPtr<FrameNode>& frameNode, std::unique_ptr<JsonValue>& arkExtraInfoJson,
        float scale);

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
    bool isDragForbidden_ = false;
    bool textDraggable_ = false;
    bool isTextDraggable_ = false;
    bool monopolizeEvents_ = false;
    float menuPreviewScale_ = DEFALUT_DRAG_PPIXELMAP_SCALE;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_HUB_H
