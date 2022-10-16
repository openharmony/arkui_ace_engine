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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_H

#include <functional>
#include <memory>
#include <optional>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/shared_transition_option.h"
#include "core/components_ng/property/transition_property.h"
#include "core/event/ace_events.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace {

using ClickEventFunc = std::function<void(const ClickInfo* info)>;
using RemoteCallback = std::function<void(const BaseEventInfo* info)>;

class ACE_EXPORT ViewAbstractModel {
public:
    static ViewAbstractModel* GetInstance();
    virtual ~ViewAbstractModel() = default;

    // basic size
    virtual void SetWidth(const Dimension& width) = 0;
    virtual void SetHeight(const Dimension& height) = 0;
    virtual void SetMinWidth(const Dimension& minWidth) = 0;
    virtual void SetMinHeight(const Dimension& minHeight) = 0;
    virtual void SetMaxWidth(const Dimension& maxWidth) = 0;
    virtual void SetMaxHeight(const Dimension& maxHeight) = 0;

    // layout
    virtual void SetLayoutPriority(int32_t priority) = 0;
    virtual void SetLayoutWeight(int32_t value) = 0;
    virtual void SetAspectRatio(float ratio) = 0;
    virtual void SetAlign(const Alignment& alignment) = 0;

    // position
    virtual void SetPosition(const Dimension& x, const Dimension& y) = 0;
    virtual void SetOffset(const Dimension& x, const Dimension& y) = 0;
    virtual void MarkAnchor(const Dimension& x, const Dimension& y) = 0;

    // transforms
    virtual void SetScale(float x, float y, float z) = 0;
    virtual void SetPivot(const Dimension& x, const Dimension& y) = 0;
    virtual void SetTranslate(const Dimension& x, const Dimension& y, const Dimension& z) = 0;
    virtual void SetRotate(float x, float y, float z, float angle) = 0;
    virtual void SetTransformMatrix(const std::vector<float>& matrix) = 0;

    // display props
    virtual void SetOpacity(double opacity) = 0;
    virtual void SetTransition(const NG::TransitionOptions& transitionOptions) = 0;
    virtual void SetOverlay(const std::string& text, const std::optional<Alignment>& align,
        const std::optional<Dimension>& offsetX, const std::optional<Dimension>& offsetY) = 0;
    virtual void SetVisibility(VisibleType visible, std::function<void(int32_t)>&& changeEventFunc) = 0;
    virtual void SetSharedTransition(const SharedTransitionOption& option) = 0;
    virtual void SetGeometryTransition(const std::string& id) = 0;

    // flex props
    virtual void SetFlexBasis(const Dimension& value) = 0;
    virtual void SetAlignSelf(FlexAlign value) = 0;
    virtual void SetFlexShrink(float value) = 0;
    virtual void SetFlexGrow(float value) = 0;
    virtual void SetDisplayIndex(int32_t value) = 0;

    // event
    virtual void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc) = 0;
    virtual void SetOnTouch(TouchEventFunc&& touchEventFunc) = 0;
    virtual void SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback) = 0;
    virtual void SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) = 0;
    virtual void SetOnHover(OnHoverEventFunc&& onHoverEventFunc) = 0;
    virtual void SetOnDelete(std::function<void()>&& onDeleteCallback) = 0;
    virtual void SetOnAppear(std::function<void()>&& onAppearCallback) = 0;
    virtual void SetOnDisAppear(std::function<void()>&& onDisAppearCallback) = 0;
    virtual void SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback) = 0;
    virtual void SetOnRemoteMessage(RemoteCallback&& onRemoteCallback) = 0;

    // interact
    virtual void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) = 0;
    virtual void SetEnabled(bool enabled) = 0;
    virtual void SetTouchable(bool touchable) = 0;
    virtual void SetFocusable(bool focusable) = 0;
    virtual void SetFocusNode(bool focus) = 0;

private:
    static std::unique_ptr<ViewAbstractModel> instance_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_H
