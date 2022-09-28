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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_SELECT_OVERLAY_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_SELECT_OVERLAY_PATTERN_H

#include <utility>

#include "base/geometry/ng/rect_t.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_layout_algorithm.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_paint_method.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SelectOverlayPattern : public Pattern {
    DECLARE_ACE_TYPE(SelectOverlayPattern, Pattern);

public:
    explicit SelectOverlayPattern(std::shared_ptr<SelectOverlayInfo> info) : info_(std::move(info)) {}
    ~SelectOverlayPattern() override = default;

    bool IsMeasureBoundary() const override
    {
        return true;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<SelectOverlayLayoutAlgorithm>(info_);
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<SelectOverlayPaintMethod>(info_);
    }

    const std::shared_ptr<SelectOverlayInfo>& GetSelectOverlayInfo() const
    {
        return info_;
    }

    void UpdateFirstSelectHandleInfo(const SelectHandleInfo& info);

    void UpdateSecondSelectHandleInfo(const SelectHandleInfo& info);

    void UpdateSelectMenuInfo(const SelectMenuInfo& info);

    void UpdateShowArea(const RectF& area);

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void UpdateHandleHotZone();
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;

    void HandleOnClick(GestureEvent& info);

    void HandlePanStart(GestureEvent& info);
    void HandlePanMove(GestureEvent& info);
    void HandlePanEnd(GestureEvent& info);
    void HandlePanCancel();

    void CheckHandleReverse();

    std::shared_ptr<SelectOverlayInfo> info_;
    RefPtr<PanEvent> panEvent_;
    RefPtr<ClickEvent> clickEvent_;

    RectF firstHandleRegion_;
    RectF secondHandleRegion_;

    bool firstHandleDrag_ = false;
    bool secondHandleDrag_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PAGE_PATTERN_H
