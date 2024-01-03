/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_DRAG_BAR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_DRAG_BAR_PATTERN_H

#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_paint_method.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_paint_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
using ClickArrowCallback = std::function<void()>;

class ACE_EXPORT SheetDragBarPattern : public Pattern {
    DECLARE_ACE_TYPE(SheetDragBarPattern, Pattern);

public:
    SheetDragBarPattern() = default;
    ~SheetDragBarPattern() override = default;

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<SheetDragBarPaintProperty>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<SheetDragBarPaintMethod>();
    }

    bool HasClickArrowCallback() const
    {
        return (clickArrowCallback_ != nullptr);
    }

    void SetClickArrowCallback(const ClickArrowCallback& callback)
    {
        clickArrowCallback_ = callback;
    }

    void UpdateDrawPoint();

    void ScaleAnimation(bool isDown);
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown(const TouchLocationInfo& info);
    void HandleTouchUp();
    void MarkDirtyNode(PropertyChangeFlag extraFlag);

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;

    void InitClickEvent();
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void OnClick();
    void CreatePropertyCallback();
    void StopAnimation();

    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<ClickEvent> clickListener_;

    OffsetF dragOffset_;
    OffsetF downPoint_;
    float dragOffsetX_ = 0.0f;
    float dragOffsetY_ = 0.0f;
    bool isDown_ = false;

    ClickArrowCallback clickArrowCallback_;

    RefPtr<NodeAnimatablePropertyFloat> property_;

    ACE_DISALLOW_COPY_AND_MOVE(SheetDragBarPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_DRAG_BAR_PATTERN_H