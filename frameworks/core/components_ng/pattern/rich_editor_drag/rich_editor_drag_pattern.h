/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_info.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_overlay_modifier.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_paint_method.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_overlay_modifier.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/components_ng/render/drawing_forward.h"

namespace OHOS::Ace::NG {
class RichEditorDragPattern : public TextDragPattern {
    DECLARE_ACE_TYPE(RichEditorDragPattern, TextDragPattern);

public:
    explicit RichEditorDragPattern(const RefPtr<TextPattern>& hostPattern,
        const std::shared_ptr<RichEditorDragInfo> info) : info_(info), hostPattern_(hostPattern) {};
    ~RichEditorDragPattern() override = default;

    static RefPtr<FrameNode> CreateDragNode(
        const RefPtr<FrameNode>& hostNode, std::list<RefPtr<FrameNode>>& imageChildren);

    static RefPtr<FrameNode> CreateDragNode(
        const RefPtr<FrameNode>& hostNode, std::list<RefPtr<FrameNode>>& imageChildren, const RichEditorDragInfo& info);

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!overlayModifier_) {
            overlayModifier_ = AceType::MakeRefPtr<RichEditorDragOverlayModifier>(WeakClaim(this), hostPattern_);
        }

        if (!contentModifier_) {
            contentModifier_ = AceType::MakeRefPtr<RichEditorDragContentModifier>();
        }
        auto pattern = hostPattern_.Upgrade();
        if (pattern) {
            contentModifier_->SetIsCustomFont(pattern->GetIsCustomFont());
        }

        return MakeRefPtr<RichEditorDragPaintMethod>(WeakClaim(this), overlayModifier_, contentModifier_, *info_);
    }

    void Initialize(const TextDragData& data)
    {
        textDragData_ = data;
    }

    Dimension GetDragCornerRadius() override
    {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, TEXT_DRAG_RADIUS);
        auto richEditorTheme = pipeline->GetTheme<RichEditorTheme>();
        CHECK_NULL_RETURN(richEditorTheme, TEXT_DRAG_RADIUS);
        return richEditorTheme->GetDragCornerRadius();
    }

protected:
    std::shared_ptr<RichEditorDragInfo> info_;

private:
    static RefPtr<FrameNode> CreateDragNode(const RefPtr<FrameNode>& hostNode, const RichEditorDragInfo& info);

    WeakPtr<TextPattern> hostPattern_;
    RefPtr<RichEditorDragContentModifier> contentModifier_;

    ACE_DISALLOW_COPY_AND_MOVE(RichEditorDragPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_PATTERN_H
