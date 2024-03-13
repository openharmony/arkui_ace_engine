/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_H

#include "core/components/box/box_base_component.h"
#include "core/components/box/drag_drop_event.h"
#include "core/components/common/properties/animatable_color.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/gestures/gesture_group.h"
#include "core/gestures/raw_recognizer.h"

namespace OHOS::Ace {

using OnHoverCallback = std::function<void(bool, HoverInfo& info)>;
using OnMouseCallback = std::function<void(MouseInfo& info)>;
using OnNewDragFunc = std::function<void(const RefPtr<OHOS::Ace::DragEvent>&)>;
using OnPreDragFunc = std::function<void(const PreDragStatus)>;

enum class BoxStateAttribute {
    ASPECT_RATIO,
    BORDER,
    COLOR,
    BORDER_COLOR,
    BORDER_RADIUS,
    BORDER_STYLE,
    BORDER_WIDTH,
    GRADIENT,
    HEIGHT,
    WIDTH,
};

// A component can box others components.
class ACE_EXPORT BoxComponent : public BoxBaseComponent {
    DECLARE_ACE_TYPE(BoxComponent, BoxBaseComponent);

public:
    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;

    RefPtr<Decoration> GetBackDecoration() const
    {
        return backDecoration_;
    }

    RefPtr<Decoration> GetFrontDecoration() const
    {
        return frontDecoration_;
    }

    const Color& GetColor() const
    {
        if (backDecoration_) {
            return backDecoration_->GetBackgroundColor();
        }
        return Color::TRANSPARENT;
    }

    bool GetDecorationUpdateFlag() const
    {
        return decorationUpdateFlag_;
    }

    HoverAnimationType GetMouseAnimationType() const
    {
        return animationType_;
    }

    void SetBackDecoration(const RefPtr<Decoration>& decoration)
    {
        backDecoration_ = decoration;
        SetDecorationUpdateFlag(true);
    }

    void SetFrontDecoration(const RefPtr<Decoration>& decoration)
    {
        frontDecoration_ = decoration;
        SetDecorationUpdateFlag(true);
    }

    void SetColor(const Color& color, const AnimationOption& option = AnimationOption())
    {
        if (!backDecoration_) {
            backDecoration_ = AceType::MakeRefPtr<Decoration>();
        }
        backDecoration_->SetBackgroundColor(color, option);
    }

    void SetColor(const AnimatableColor& color)
    {
        if (!backDecoration_) {
            backDecoration_ = AceType::MakeRefPtr<Decoration>();
        }
        backDecoration_->SetBackgroundColor(color);
    }

    void SetDecorationUpdateFlag(bool flag)
    {
        decorationUpdateFlag_ = flag;
    }

    void SetMouseAnimationType(HoverAnimationType animationType)
    {
        animationType_ = animationType;
    }

    void SetInspectorDirection(TextDirection direction)
    {
        inspectorDirection_ = direction;
    }

    TextDirection GetInspectorDirection() const
    {
        return inspectorDirection_;
    }

    void SetOnHoverId(const OnHoverCallback& onHoverId)
    {
        onHoverId_ = onHoverId;
    }

    OnHoverCallback GetOnHoverId() const
    {
        return onHoverId_;
    }

    void SetOnMouseId(const OnMouseCallback& onMouseId)
    {
        onMouseId_ = onMouseId;
    }

    OnMouseCallback GetOnMouseId() const
    {
        return onMouseId_;
    }

    void SetOnTouchMoveId(const OnTouchEventCallback& onTouchMoveId)
    {
        onTouchMoveId_ = onTouchMoveId;
    }

    const OnTouchEventCallback& GetOnTouchMoveId() const
    {
        return onTouchMoveId_;
    }

    void SetOnTouchUpId(const OnTouchEventCallback& onTouchUpId)
    {
        onTouchUpId_ = onTouchUpId;
    }

    const OnTouchEventCallback& GetOnTouchUpId() const
    {
        return onTouchUpId_;
    }

    void SetOnTouchDownId(const OnTouchEventCallback& onTouchDownId)
    {
        onTouchDownId_ = onTouchDownId;
    }

    const OnTouchEventCallback& GetOnTouchDownId() const
    {
        return onTouchDownId_;
    }

    RefPtr<Gesture> GetOnClick() const
    {
        return onClickId_;
    }

    void SetOnClick(const RefPtr<Gesture>& onClickId)
    {
        onClickId_ = onClickId;
    }

    void AddGesture(GesturePriority priority, RefPtr<Gesture> gesture)
    {
        gestures_[static_cast<int32_t>(priority)] = gesture;
    }

    const std::array<RefPtr<Gesture>, 3>& GetGestures() const
    {
        return gestures_;
    }

    const EventMarker& GetOnDomDragEnter() const
    {
        return onDomDragEnterId_;
    }

    void SetOnDomDragEnter(const EventMarker& value)
    {
        onDomDragEnterId_ = value;
    }

    const EventMarker& GetOnDomDragOver() const
    {
        return onDomDragOverId_;
    }

    void SetOnDomDragOver(const EventMarker& value)
    {
        onDomDragOverId_ = value;
    }

    const EventMarker& GetOnDomDragLeave() const
    {
        return onDomDragLeaveId_;
    }

    void SetOnDomDragLeave(const EventMarker& value)
    {
        onDomDragLeaveId_ = value;
    }

    const EventMarker& GetOnDomDragDrop() const
    {
        return onDomDragDropId_;
    }

    void SetOnDomDragDrop(const EventMarker& value)
    {
        onDomDragDropId_ = value;
    }

    void SetGeometryTransitionId(const std::string& id)
    {
        geometryTransitionId_ = id;
    }

    std::string GetGeometryTransitionId() const
    {
        return geometryTransitionId_;
    }

    RefPtr<StateAttributes<BoxStateAttribute>> GetStateAttributes()
    {
        if (stateAttributeList_ == nullptr) {
            stateAttributeList_ = MakeRefPtr<StateAttributes<BoxStateAttribute>>();
        }
        return stateAttributeList_;
    }
 
    bool HasStateAttributes()
    {
        return stateAttributeList_ != nullptr;
    }

    const OnDragFunc& GetOnDragStartId() const
    {
        return onDragStartId_;
    }

    void SetOnDragStartId(const OnDragFunc& onDragStartId)
    {
        onDragStartId_ = onDragStartId;
    }

    const OnDropFunc& GetOnDragEnterId() const
    {
        return onDragEnterId_;
    }

    void SetOnDragEnterId(const OnDropFunc& onDragEnterId)
    {
        onDragEnterId_ = onDragEnterId;
    }

    const OnDropFunc& GetOnDragMoveId() const
    {
        return onDragMoveId_;
    }

    void SetOnDragMoveId(const OnDropFunc& onDragMoveId)
    {
        onDragMoveId_ = onDragMoveId;
    }

    const OnNewDragFunc& GetOnDragEndId() const
    {
        return onDragEndId_;
    }

    void SetOnDragEndId(const OnNewDragFunc& onDragEndId)
    {
        onDragEndId_ = onDragEndId;
    }

    const OnPreDragFunc& GetOnPreDragId() const
    {
        return onPreDragId_;
    }

    void SetOnPreDragId(const OnPreDragFunc& onPreDragId)
    {
        onPreDragId_ = onPreDragId;
    }

    const OnDropFunc& GetOnDragLeaveId() const
    {
        return onDragLeaveId_;
    }

    void SetOnDragLeaveId(const OnDropFunc& onDragLeaveId)
    {
        onDragLeaveId_ = onDragLeaveId;
    }

    const OnDropFunc& GetOnDropId() const
    {
        return onDropId_;
    }

    void SetOnDropId(const OnDropFunc& onDropId)
    {
        onDropId_ = onDropId;
    }

    const EventMarker& GetRemoteMessageEvent() const
    {
        return remoteMessageId_;
    }

    void SetRemoteMessageEvent(const EventMarker& eventId)
    {
        remoteMessageId_ = eventId;
    }

    RefPtr<Gesture> GetOnLongPress() const
    {
        return onLongPressId_;
    }

    void SetOnLongPress(const RefPtr<Gesture>& onLongPressId)
    {
        onLongPressId_ = onLongPressId;
    }

    bool HasBackgroundColor() const
    {
        return hasBackgroundColor_;
    }

    void SetHasBackgroundColor(bool hasBackgroundColor)
    {
        hasBackgroundColor_ = hasBackgroundColor;
    }

    void SetEnableDebugBoundary(bool enableDebugBoundary)
    {
        enableDebugBoundary_ = enableDebugBoundary;
    }

    bool GetEnableDebugBoundary()
    {
        return enableDebugBoundary_;
    }

    void SetEnableDragStart(bool enableDragStart)
    {
        enableDragStart_ = enableDragStart;
    }

    bool GetEnableDragStart() const
    {
        return enableDragStart_;
    }

    void NeedMaterial(bool needMaterial)
    {
        needMaterial_ = needMaterial;
    }

    bool GetNeedMaterial() const
    {
        return needMaterial_;
    }
private:
    RefPtr<Decoration> backDecoration_;
    RefPtr<Decoration> frontDecoration_;
    bool decorationUpdateFlag_ = false;
    HoverAnimationType animationType_ = HoverAnimationType::UNKNOWN;
    OnHoverCallback onHoverId_;
    OnMouseCallback onMouseId_;
    OnTouchEventCallback onTouchMoveId_;
    OnTouchEventCallback onTouchUpId_;
    OnTouchEventCallback onTouchDownId_;
    RefPtr<Gesture> onClickId_;
    RefPtr<Gesture> onLongPressId_;
    std::array<RefPtr<Gesture>, 3> gestures_;
    EventMarker onDomDragEnterId_;
    EventMarker onDomDragOverId_;
    EventMarker onDomDragLeaveId_;
    EventMarker onDomDragDropId_;
    std::string geometryTransitionId_;
    TextDirection inspectorDirection_ { TextDirection::LTR };
    RefPtr<StateAttributes<BoxStateAttribute>> stateAttributeList_ = nullptr;
    EventMarker remoteMessageId_;
    bool hasBackgroundColor_;
    bool enableDebugBoundary_ = false;
    bool enableDragStart_ = true;
    OnDragFunc onDragStartId_;
    OnDropFunc onDragEnterId_;
    OnDropFunc onDragMoveId_;
    OnDropFunc onDragLeaveId_;
    OnDropFunc onDropId_;
    OnNewDragFunc onDragEndId_;
    OnPreDragFunc onPreDragId_;
    bool needMaterial_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_H
