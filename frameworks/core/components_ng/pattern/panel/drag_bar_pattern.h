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

using DragBarBuilderFunc = std::function<void()>;

class DragBarPattern : public Pattern {
    DECLARE_ACE_TYPE(DragBarPattern, Pattern);

public:
    DragBarPattern() = default;
    ~DragBarPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<DragBarLayoutAlgorithm>();
        return layoutAlgorithm;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<DragBarPaintMethod>();
    }

    PanelMode GetPanelMode() const
    {
        return showMode_;
    }

    void SetFullScreenMode(bool fullScreenMode)
    {
        fullScreenMode_ = fullScreenMode;
    }

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void ShowInPanelMode(PanelMode mode);
    void UpdateDrawPoint();

    void InitTouch(const RefPtr<GestureEventHub>& gestureHub);
    void HandleTouchEvent(const TouchLocationInfo& info);

    RefPtr<TouchEventImpl> touchEvent_;
    Offset barLeftPoint_;
    Offset barCenterPoint_;
    Offset barRightPoint_;
    PanelMode showMode_ = PanelMode::HALF;
    bool fullScreenMode_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(DragBarPattern);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_DRAG_BAR_PATTERN_H