/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUT_OVERFLOW_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUT_OVERFLOW_HANDLER_H

#include "base/geometry/ng/rect_t.h"
#include "base/log/dump_log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/scrollable_event.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT VerticalOverflowHandler : public AceType {
    DECLARE_ACE_TYPE(VerticalOverflowHandler, AceType);

public:
    VerticalOverflowHandler() = default;

    VerticalOverflowHandler(WeakPtr<FrameNode> node) : frameNode_(std::move(node)) {}

    ~VerticalOverflowHandler() override = default;

    bool IsVerticalLayout() const;

    bool IsVerticalReverseLayout() const;

    void RegisterScrollableEvent();
 
    void UnRegisterScrollableEvent();
 
    bool HandleScrollImpl(float offset, int32_t source);
    
    bool OutOfBoundary(float offset) const;

    void SetTotalChildFrameRect(const RectF &childrenRect)
    {
        totalChildFrameRect_ = childrenRect;
        preComputedReady_ = true;
    }

    void SetContentRect(const RectF &rect)
    {
        contentRect_ = rect;
    }

    void CreateContentRect();
    void AdjustChildrenOffset(float offset, bool useParentAjust = false);
    void InitOffsetAfterLayout();
    bool IsVerticalOverflow() const;
    bool IsHorizontalOverflow() const;
    void HandleContentOverflow();
    bool IsTotalChildFrameRectPrecomputed() const
    {
        return preComputedReady_;
    }
    void ResetTotalChildFrameRectPrecomputed()
    {
        preComputedReady_ = false;
    }
    bool IsOverflowDisabled() const
    {
        return overflowDisabled_;
    }
    void SetOverflowDisabledFlag(bool flag)
    {
        overflowDisabled_ = flag;
    }
    RefPtr<FrameNode> GetHost() const
    {
        return frameNode_.Upgrade();
    }
    std::string ToString() const
    {
        std::string result = "overflow: ";
        result.append(scrollableEvent_ ? "true" : "false");
        result.append(std::string(" scrollDistance_: "));
        result.append(scrollDistance_.has_value() ? std::to_string(scrollDistance_.value()) : "NA");
        result.append(std::string(" totalChildFrameRect_: "));
        result.append(totalChildFrameRect_.ToString());
        result.append(std::string(" contentRect_: "));
        result.append(contentRect_.ToString());
        result.append(std::string(" offsetToChildFrameBottom_: "));
        result.append(std::to_string(offsetToChildFrameBottom_));
        return result;
    }
    void AdjustTotalChildFrameRect()
    {
        RectF adjustRect;
        if (GreatNotEqual(totalChildFrameRect_.Top(), contentRect_.Top())) {
            adjustRect.SetTop(contentRect_.Top() - totalChildFrameRect_.Top());
            adjustRect += SizeF(0.0, totalChildFrameRect_.Top() - contentRect_.Top());
        }
        if (LessNotEqual(totalChildFrameRect_.Bottom(), contentRect_.Bottom())) {
            adjustRect += SizeF(0.0, contentRect_.Bottom() - totalChildFrameRect_.Bottom());
        }
        totalChildFrameRect_ += adjustRect;
    }
private:
    float offsetToChildFrameBottom_ = 0.0f;
    RefPtr<ScrollableEvent> scrollableEvent_;
    std::optional<float> scrollDistance_;
    RectF totalChildFrameRect_;
    RectF contentRect_;
    bool overflowDisabled_ = false;
    bool preVerticalReverse_ = false;
    bool hasParentAdjust_ = false;
    bool preComputedReady_ = false;
    WeakPtr<FrameNode> frameNode_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUT_OVERFLOW_HANDLER_H
