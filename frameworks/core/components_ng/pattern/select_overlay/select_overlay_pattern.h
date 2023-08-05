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
#include "base/utils/utils.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_content_modifier.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_layout_algorithm.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_modifier.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_paint_method.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SelectOverlayPattern : public PopupBasePattern {
    DECLARE_ACE_TYPE(SelectOverlayPattern, PopupBasePattern);

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
        return MakeRefPtr<SelectOverlayLayoutAlgorithm>(info_, defaultMenuEndOffset_);
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!selectOverlayModifier_) {
            selectOverlayModifier_ = AceType::MakeRefPtr<SelectOverlayModifier>(defaultMenuEndOffset_);
        }
        if (!selectOverlayContentModifier_) {
            selectOverlayContentModifier_ = AceType::MakeRefPtr<SelectOverlayContentModifier>();
        }

        if (paintMethodCreated_) {
            return MakeRefPtr<SelectOverlayPaintMethod>(selectOverlayModifier_, selectOverlayContentModifier_, *info_,
                defaultMenuEndOffset_, hasExtensionMenu_, hasShowAnimation_, true);
        } else {
            paintMethodCreated_ = true;
            return MakeRefPtr<SelectOverlayPaintMethod>(selectOverlayModifier_, selectOverlayContentModifier_, *info_,
                defaultMenuEndOffset_, hasExtensionMenu_, hasShowAnimation_, false);
        }
    }

    const std::shared_ptr<SelectOverlayInfo>& GetSelectOverlayInfo() const
    {
        return info_;
    }

    void UpdateFirstSelectHandleInfo(const SelectHandleInfo& info);

    void UpdateSecondSelectHandleInfo(const SelectHandleInfo& info);

    void UpdateFirstAndSecondHandleInfo(const SelectHandleInfo& firstInfo, const SelectHandleInfo& secondInfo);

    void UpdateSelectMenuInfo(const SelectMenuInfo& info);

    void UpdateShowArea(const RectF& area);

    void SetHandleReverse(bool reverse);

    void SetSelectInfo(const std::string& selectInfo)
    {
        selectInfo_ = selectInfo;
    }

    const std::string& GetSelectInfo() const
    {
        return selectInfo_;
    }

    const RefPtr<SelectOverlayModifier>& GetOverlayModifier()
    {
        return selectOverlayModifier_;
    }

    const RefPtr<SelectOverlayContentModifier>& GetContentModifier()
    {
        return selectOverlayContentModifier_;
    }

    const OffsetF& GetDefaultMenuEndOffset()
    {
        return defaultMenuEndOffset_;
    }

    float GetMenuWidth() const
    {
        return menuWidth_;
    }

    const RectF& GetHandleRegion(bool isFirst) const
    {
        if (isFirst) {
            return firstHandleRegion_;
        } else {
            return secondHandleRegion_;
        }
    }

    void ShowOrHiddenMenu(bool isHidden);
    void DisableMenu(bool isDisabled);

    void SetClosedByGlobalTouchEvent(bool closedByGlobalTouch)
    {
        closedByGlobalTouchEvent_ = closedByGlobalTouch;
    }

    void SetHasShowAnimation(bool animation)
    {
        hasShowAnimation_ = animation;
    }

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void UpdateHandleHotZone();
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;

    void HandleOnClick(GestureEvent& info);
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleOnTouch(GestureEvent& info);
    void HandlePanStart(GestureEvent& info);
    void HandlePanMove(GestureEvent& info);
    void HandlePanEnd(GestureEvent& info);
    void HandlePanCancel();

    void CheckHandleReverse();

    std::shared_ptr<SelectOverlayInfo> info_;
    RefPtr<PanEvent> panEvent_;
    RefPtr<ClickEvent> clickEvent_;
    RefPtr<TouchEventImpl> touchEvent_;

    RectF firstHandleRegion_;
    RectF secondHandleRegion_;

    bool firstHandleDrag_ = false;
    bool secondHandleDrag_ = false;
    // Used to record the original menu display status when the handle is moved.
    bool orignMenuIsShow_ = false;
    bool hasExtensionMenu_ = false;
    bool hasShowAnimation_ = false;

    int32_t greatThanMaxWidthIndex_ = -1;
    float menuWidth_ = 0.0f;

    std::string selectInfo_;

    OffsetF defaultMenuEndOffset_;

    RefPtr<SelectOverlayModifier> selectOverlayModifier_;

    RefPtr<SelectOverlayContentModifier> selectOverlayContentModifier_;

    bool paintMethodCreated_ = false;

    bool closedByGlobalTouchEvent_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PAGE_PATTERN_H
