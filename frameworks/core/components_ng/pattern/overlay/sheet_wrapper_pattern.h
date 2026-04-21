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

#include "core/components_ng/pattern/overlay/popup_base_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_paint_method.h"
#include "core/components_ng/pattern/sheet/sheet_wrapper_accessibility_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INVALID_SUBWINDOW_ID = -1;
}
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
        ACE_UINODE_TRACE(GetHost());
        return MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        ACE_UINODE_TRACE(GetHost());
        return MakeRefPtr<SheetWrapperPaintMethod>();
    }

    RefPtr<FrameNode> GetTargetNode() const
    {
        return FrameNode::GetFrameNode(targetTag_, targetId_);
    }

    RefPtr<FrameNode> GetSheetPageNode() const
    {
        return sheetPageNode_;
    }

    RefPtr<FrameNode> GetSheetMaskNode() const
    {
        return sheetMaskNode_;
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        ACE_UINODE_TRACE(GetHost());
        return MakeRefPtr<SheetWrapperAccessibilityProperty>();
    }

    void SetSheetPageNode(RefPtr<FrameNode> node)
    {
        sheetPageNode_ = node;
    }

    void SetSheetMaskNode(RefPtr<FrameNode> node)
    {
        sheetMaskNode_ = node;
    }
    void OnAttachToFrameNode() override;
    void InitSubWindowId();
    void InitMainWindowRect(int32_t subwindowId);
    void OnAttachToMainTree() override;

    RectF GetMainWindowRect() const
    {
        return mainWindowRect_;
    }

    bool ShowInUEC() const
    {
        return isShowInUEC_;
    }

    int32_t GetSubWindowId() const
    {
        return subWindowId_;
    }

    void RegisterSheetMaskColorRes(const RefPtr<FrameNode>& maskNode,
        const RefPtr<FrameNode>& sheetNode, RefPtr<ResourceObject>& resObj);

    void UpdateSheetMaskResource(const RefPtr<FrameNode>& maskNode,
        const RefPtr<FrameNode>& sheetNode, NG::SheetStyle& sheetStyle);

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

    RefPtr<FrameNode> sheetPageNode_;
    RefPtr<FrameNode> sheetMaskNode_;
    RectF mainWindowRect_;
    bool isShowInUEC_ = false;
    int32_t subWindowId_ = -1;
    ACE_DISALLOW_COPY_AND_MOVE(SheetWrapperPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_WRAPPER_PATTERN_H
