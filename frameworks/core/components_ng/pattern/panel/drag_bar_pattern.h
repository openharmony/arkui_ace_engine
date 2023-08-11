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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_DRAG_BAR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_DRAG_BAR_PATTERN_H

#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/panel/drag_bar_layout_algorithm.h"
#include "core/components_ng/pattern/panel/drag_bar_layout_property.h"
#include "core/components_ng/pattern/panel/drag_bar_paint_method.h"
#include "core/components_ng/pattern/panel/drag_bar_paint_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

using ClickArrowCallback = std::function<void()>;

class DragBarPattern : public Pattern {
    DECLARE_ACE_TYPE(DragBarPattern, Pattern);

public:
    DragBarPattern() = default;
    ~DragBarPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<DragBarLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<DragBarLayoutAlgorithm>();
        iconOffset_ = layoutAlgorithm->GetIconOffset();
        return layoutAlgorithm;
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<DragBarPaintProperty>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto paintMethod = MakeRefPtr<DragBarPaintMethod>();
        paintMethod->SetIconOffset(iconOffset_);
        paintMethod->SetScaleWidth(scaleWidth_);
        paintMethod->SetPanelMode(showMode_);
        return paintMethod;
    }

    PanelMode GetPanelMode() const
    {
        return showMode_;
    }

    float GetStatusBarHeight() const
    {
        return statusBarHeight_.Value();
    }

    bool HasClickArrowCallback() const
    {
        return (clickArrowCallback_ != nullptr);
    }

    void SetClickArrowCallback(const ClickArrowCallback& callback)
    {
        clickArrowCallback_ = callback;
    }

    void SetIsFirstUpdate(bool isFirstUpdate)
    {
        isFirstUpdate_ = isFirstUpdate;
    }

    void InitProps();
    void ShowArrow(bool show);
    void ShowInPanelMode(PanelMode mode);
    void UpdateDrawPoint();

    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown(const TouchLocationInfo& info);
    void HandleTouchMove(const TouchLocationInfo& info);
    void HandleTouchUp();
    void MarkDirtyNode(PropertyChangeFlag extraFlag);

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void InitClickEvent();
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void OnClick();
    void DoStyleAnimation(
        const OffsetT<Dimension>& left, const OffsetT<Dimension>& center, const OffsetT<Dimension>& right);

    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<ClickEvent> clickListener_;
    OffsetF iconOffset_;
    OffsetF barLeftPoint_;
    OffsetF barCenterPoint_;
    OffsetF barRightPoint_;

    Dimension statusBarHeight_ = 0.0_vp; // height in vp
    OffsetF dragOffset_;
    OffsetF downPoint_;
    float dragRangeX_ = 0.0f;
    float dragRangeY_ = 0.0f;
    float scaleWidth_ = 1.0f;

    PanelMode showMode_ = PanelMode::HALF;
    bool isFirstUpdate_ = true;
    ClickArrowCallback clickArrowCallback_;

    RefPtr<Animator> animator_;
    RefPtr<Animator> barTouchAnimator_;
    RefPtr<Animator> barRangeAnimator_;
    RefPtr<Animator> barStyleAnimator_;

    ACE_DISALLOW_COPY_AND_MOVE(DragBarPattern);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_DRAG_BAR_PATTERN_H