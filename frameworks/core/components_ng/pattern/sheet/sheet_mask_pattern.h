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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHEET_SHEET_MASK_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHEET_SHEET_MASK_PATTERN_H

#include "core/common/ace_engine.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_paint_method.h"

namespace OHOS::Ace::NG {
class SheetMaskPattern : virtual public PopupBasePattern {
    DECLARE_ACE_TYPE(SheetMaskPattern, PopupBasePattern);

public:
    SheetMaskPattern() = default;

    SheetMaskPattern(int32_t targetId, const std::string& targetTag) : targetId_(targetId), targetTag_(targetTag) {}

    ~SheetMaskPattern() override = default;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }
    RefPtr<FrameNode> GetTargetNode() const
    {
        return FrameNode::GetFrameNode(targetTag_, targetId_);
    }

    void OnAttachToFrameNode() override
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto maskLayoutProps = host->GetLayoutProperty();
        CHECK_NULL_VOID(maskLayoutProps);
        maskLayoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT);
        maskLayoutProps->UpdateAlignment(Alignment::TOP_LEFT);
        auto maskRenderContext = host->GetRenderContext();
        CHECK_NULL_VOID(maskRenderContext);
        maskRenderContext->UpdateClipEdge(true);
    }

    bool GetIsMaskInteractive() const
    {
        return isMaskInteractive_;
    }

    void SetIsMaskInteractive(bool IsInteractive)
    {
        isMaskInteractive_ = IsInteractive;
    }

protected:
    bool AvoidKeyboard() const override
    {
        return false;
    }

    bool AvoidBottom() const override
    {
        return false;
    }

private:
    int32_t targetId_ = -1;
    std::string targetTag_;
    bool isMaskInteractive_ = true;

    ACE_DISALLOW_COPY_AND_MOVE(SheetMaskPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_WRAPPER_PATTERN_H
