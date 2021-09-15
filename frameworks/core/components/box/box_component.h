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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_H

#include "core/components/box/box_base_component.h"
#include "core/components/common/properties/animatable_color.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace {

enum class HoverAnimationType : int32_t {
    NONE,
    OPACITY,
    SCALE,
};

using OnDragFunc = std::function<void(const RefPtr<DragEvent>& info)>;

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

    OnDragFunc GetOnDragId() const
    {
        if (!onDragId_) {
            return nullptr;
        }
        return *onDragId_;
    }

    void SetOnDragId(const OnDragFunc& onDragId)
    {
        onDragId_ = std::make_unique<OnDragFunc>(onDragId);
    }

    OnDragFunc GetOnDragEnterId() const
    {
        if (!onDragEnterId_) {
            return nullptr;
        }
        return *onDragEnterId_;
    }

    void SetOnDragEnterId(const OnDragFunc& onDragEnterId)
    {
        onDragEnterId_ = std::make_unique<OnDragFunc>(onDragEnterId);
    }

    OnDragFunc GetOnDragLeaveId() const
    {
        if (!onDragLeaveId_) {
            return nullptr;
        }
        return *onDragLeaveId_;
    }

    OnDragFunc GetOnDragMoveId() const
    {
        if (!onDragMoveId_) {
            return nullptr;
        }
        return *onDragMoveId_;
    }

    void SetOnDragMoveId(const OnDragFunc& onDragMoveId)
    {
        onDragMoveId_ = std::make_unique<OnDragFunc>(onDragMoveId);
    }

    void SetOnDragLeaveId(const OnDragFunc& onDragLeaveId)
    {
        onDragLeaveId_ = std::make_unique<OnDragFunc>(onDragLeaveId);
    }

    OnDragFunc GetOnDropId() const
    {
        if (!onDropId_) {
            return nullptr;
        }
        return *onDropId_;
    }

    void SetOnDropId(const OnDragFunc& onDropId)
    {
        onDropId_ = std::make_unique<OnDragFunc>(onDropId);
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

private:
    RefPtr<Decoration> backDecoration_;
    RefPtr<Decoration> frontDecoration_;
    bool decorationUpdateFlag_ = false;
    HoverAnimationType animationType_ = HoverAnimationType::NONE;
    std::unique_ptr<OnDragFunc> onDragId_;
    std::unique_ptr<OnDragFunc> onDragEnterId_;
    std::unique_ptr<OnDragFunc> onDragMoveId_;
    std::unique_ptr<OnDragFunc> onDragLeaveId_;
    std::unique_ptr<OnDragFunc> onDropId_;
    RefPtr<Gesture> onClickId_;
    std::array<RefPtr<Gesture>, 3> gestures_;
    EventMarker onDomDragEnterId_;
    EventMarker onDomDragOverId_;
    EventMarker onDomDragLeaveId_;
    EventMarker onDomDragDropId_;
    std::string geometryTransitionId_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_H
