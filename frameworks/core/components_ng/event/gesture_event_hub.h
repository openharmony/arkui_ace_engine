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
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/event/drag_event.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/event/pan_event.h"
#include "core/components_ng/event/scrollable_event.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/gestures/recognizers/exclusive_recognizer.h"
#include "core/components_ng/gestures/recognizers/parallel_recognizer.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"

#ifdef ENABLE_DRAG_FRAMEWORK
namespace OHOS::Msdp::DeviceStatus {
struct DragNotifyMsg;
}
namespace OHOS::Ace {
class UnifiedData;
}
#endif
namespace OHOS::Ace::NG {

enum class HitTestMode {
    /**
     *  Both self and children respond to the hit test for touch events,
     *  but block hit test of the other nodes which is masked by this node.
     */
    HTMDEFAULT = 0,

    /**
     * Self respond to the hit test for touch events,
     * but block hit test of children and other nodes which is masked by this node.
     */
    HTMBLOCK,

    /**
     * Self and child respond to the hit test for touch events,
     * and allow hit test of other nodes which is masked by this node.
     */
    HTMTRANSPARENT,

    /**
     * Self not respond to the hit test for touch events,
     * but children respond to the hit test for touch events.
     */
    HTMNONE,

    /**
     * Self and child respond to the hit test for touch events,
     * when self consumed allow hit test of other nodes which is masked by this node,
     * when child consumed block hit test of other nodes.
     */
    HTMTRANSPARENT_SELF,
};

enum class HitTestResult {
    // The touch point is located outside the current component area;
    OUT_OF_REGION,
    // node consumption events and prevent bubbling;
    STOP_BUBBLING,
    // node process events and bubble;
    BUBBLING,
    // node process events and bubble;
    SELF_TRANSPARENT,
};

struct DragDropBaseInfo {
    RefPtr<AceType> node;
    RefPtr<PixelMap> pixelMap;
    std::string extraInfo;
};

using OnDragStartFunc = std::function<DragDropBaseInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>;
using OnDragDropFunc = std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>;

struct DragDropInfo {
    RefPtr<UINode> customNode;
    RefPtr<PixelMap> pixelMap;
    std::string extraInfo;
};

#ifdef ENABLE_DRAG_FRAMEWORK
using DragNotifyMsg = Msdp::DeviceStatus::DragNotifyMsg;
using OnDragCallback = std::function<void(const DragNotifyMsg&)>;
constexpr float PIXELMAP_WIDTH_RATE = -0.5f;
constexpr float PIXELMAP_HEIGHT_RATE = -0.2f;
constexpr float PIXELMAP_DEFALUT_LIMIT_SCALE = 0.5f;
constexpr float PIXELMAP_DRAG_WGR_TEXT_SCALE = 2.0f;
constexpr float PIXELMAP_DRAG_WGR_SCALE = 3.0f;
#endif
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
        }
        gestures_.emplace_back(gesture);
        recreateGesture_ = true;
    }

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

    // Set by user define, which will replace old one.
    void SetTouchEvent(TouchEventFunc&& touchEventFunc)
    {
        if (!touchEventActuator_) {
            touchEventActuator_ = MakeRefPtr<TouchEventActuator>();
        }
        touchEventActuator_->ReplaceTouchEvent(std::move(touchEventFunc));
    }

    void AddTouchEvent(const RefPtr<TouchEventImpl>& touchEvent)
    {
        if (!touchEventActuator_) {
            touchEventActuator_ = MakeRefPtr<TouchEventActuator>();
        }
        touchEventActuator_->AddTouchEvent(touchEvent);
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

    bool IsAccessibilityClickable();
    bool IsAccessibilityLongClickable();

    bool ActClick();

    void CheckClickActuator();
    // Set by user define, which will replace old one.
    void SetUserOnClick(GestureEventFunc&& clickEvent);

    // When the event param is undefined, it will clear the callback.
    void ClearUserOnClick();
    void ClearUserOnTouch();

    void AddClickEvent(const RefPtr<ClickEvent>& clickEvent);

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

    void BindMenu(GestureEventFunc&& showMenu);

    bool IsLongClickable() const
    {
        return longPressEventActuator_ != nullptr;
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

    // the return value means prevents event bubbling.
    bool ProcessTouchTestHit(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        TouchTestResult& innerTargets, TouchTestResult& finalResult, int32_t touchId, const PointF& localPoint);

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

    void CombineIntoExclusiveRecognizer(
        const PointF& globalPoint, const PointF& localPoint, TouchTestResult& result, int32_t touchId);

    bool IsResponseRegion() const
    {
        return isResponseRegion_;
    }
    void MarkResponseRegion(bool isResponseRegion)
    {
        isResponseRegion_ = isResponseRegion;
    }

    const std::vector<DimensionRect>& GetResponseRegion() const
    {
        return responseRegion_;
    }

    const std::vector<DimensionRect>& GetMouseResponseRegion() const
    {
        return mouseResponseRegion_;
    }

    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion)
    {
        responseRegion_ = responseRegion;
        if (!responseRegion_.empty()) {
            isResponseRegion_ = true;
        }
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
    }

    void RemoveLastResponseRect()
    {
        if (responseRegion_.empty()) {
            isResponseRegion_ = false;
            return;
        }
        responseRegion_.pop_back();
        if (responseRegion_.empty()) {
            isResponseRegion_ = false;
        }
    }

    bool GetTouchable() const
    {
        return touchable_;
    }

    void SetTouchable(bool touchable)
    {
        touchable_ = touchable;
    }

#ifdef ENABLE_DRAG_FRAMEWORK
    void SetThumbnailCallback(std::function<void(Offset)>&& callback)
    {
        if (dragEventActuator_) {
            dragEventActuator_->SetThumbnailCallback(std::move(callback));
        }
    }

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

    bool IsTextField() const
    {
        return isTextField_;
    }

    void SetTextField(bool isTextField)
    {
        isTextField_ = isTextField;
    }
#endif // ENABLE_DRAG_FRAMEWORK

    void SetPixelMap(RefPtr<PixelMap> pixelMap)
    {
        pixelMap_ = pixelMap;
    }

    RefPtr<PixelMap> GetPixelMap()
    {
        return pixelMap_;
    }

    RefPtr<LongPressRecognizer> GetLongPressRecognizer() const
    {
        CHECK_NULL_RETURN(longPressEventActuator_, nullptr);
        return longPressEventActuator_->GetLongPressRecognizer();
    }

#ifdef ENABLE_DRAG_FRAMEWORK
    int32_t SetDragData(const RefPtr<UnifiedData>& unifiedData, std::string& udKey);
    OnDragCallback GetDragCallback(const RefPtr<PipelineBase>& context, const WeakPtr<EventHub>& hub);

    void SetThumbnailPixelMapCallback(std::function<void()>&& callback)
    {
        callback_ = std::move(callback);
    }

    bool HasThumbnailCallback() const
    {
        return static_cast<bool>(callback_);
    }

    OffsetF GetPixelMapOffset(const GestureEvent& info, const SizeF& size, const float scale = 1.0f) const;
    float GetPixelMapScale(const int32_t height, const int32_t width) const;
#endif // ENABLE_DRAG_FRAMEWORK
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

private:
    void ProcessTouchTestHierarchy(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        std::list<RefPtr<NGGestureRecognizer>>& innerRecognizers, TouchTestResult& finalResult, int32_t touchId);

    void UpdateGestureHierarchy();

    // old path.
    void UpdateExternalNGGestureRecognizer();

    OnAccessibilityEventFunc GetOnAccessibilityEventFunc();

    void OnDragStart(const GestureEvent& info, const RefPtr<PipelineBase>& context, const RefPtr<FrameNode> frameNode,
        const DragDropInfo dragDropInfo, const RefPtr<OHOS::Ace::DragEvent>& dragEvent);

    WeakPtr<EventHub> eventHub_;
    RefPtr<ScrollableActuator> scrollableActuator_;
    RefPtr<TouchEventActuator> touchEventActuator_;
    RefPtr<ClickEventActuator> clickEventActuator_;
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
    std::list<RefPtr<NGGestureRecognizer>> gestureHierarchy_;

    // used in bindMenu, need to delete the old callback when bindMenu runs again
    RefPtr<ClickEvent> showMenu_;

    HitTestMode hitTestMode_ = HitTestMode::HTMDEFAULT;
    bool recreateGesture_ = true;
    bool isResponseRegion_ = false;
    std::vector<DimensionRect> responseRegion_;
    std::vector<DimensionRect> mouseResponseRegion_;
    bool touchable_ = true;
    RefPtr<PixelMap> pixelMap_;
    GestureEvent gestureInfoForWeb_;
    bool isReceivedDragGestureInfo_ = false;

#ifdef ENABLE_DRAG_FRAMEWORK
    bool textDraggable_ = false;
    bool isTextField_ = false;
    bool isTextDraggable_ = false;
    std::function<void()> callback_;
#endif
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_GESTURE_EVENT_HUB_H
