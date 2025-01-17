/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_WRAPPER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_WRAPPER_PATTERN_H

#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_paint_method.h"

namespace OHOS::Ace::NG {
class SheetWrapperPattern : virtual public PopupBasePattern {
    DECLARE_ACE_TYPE(SheetWrapperPattern, PopupBasePattern);

public:
    SheetWrapperPattern() = default;

    SheetWrapperPattern(int32_t targetId, const std::string& targetTag) : targetId_(targetId), targetTag_(targetTag) {}

    ~SheetWrapperPattern() override = default;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    }

    void OnAttachToMainTree() override
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto rootNode = AceType::DynamicCast<FrameNode>(host->GetParent());
        CHECK_NULL_VOID(rootNode);
        if (rootNode->GetTag() != V2::NAVDESTINATION_VIEW_ETS_TAG) {
            return;
        }
        auto wrapperRenderContext = host->GetRenderContext();
        CHECK_NULL_VOID(wrapperRenderContext);
        auto navDestinationPattern = rootNode->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        auto zIndex = navDestinationPattern->GetTitlebarZIndex();

        // set the sheet to float on the NavDestination's titlebar when the sheet shows in NavDestination
        wrapperRenderContext->UpdateZIndex(zIndex + 1);
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<SheetWrapperPaintMethod>();
    }

    RefPtr<FrameNode> GetTargetNode() const
    {
        return FrameNode::GetFrameNode(targetTag_, targetId_);
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

    ACE_DISALLOW_COPY_AND_MOVE(SheetWrapperPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_WRAPPER_PATTERN_H
