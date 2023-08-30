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
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_paint_method.h"
#include "core/components_ng/pattern/text_drag/text_drag_overlay_modifier.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
class RichEditorDragPattern : public TextDragPattern {
    DECLARE_ACE_TYPE(RichEditorDragPattern, TextDragPattern);

public:
    RichEditorDragPattern() = default;
    ~RichEditorDragPattern() override = default;

    static RefPtr<FrameNode> CreateDragNode(const RefPtr<FrameNode>& hostNode);
    static RefPtr<FrameNode> CreateDragNode(
        const RefPtr<FrameNode>& hostNode, std::list<RefPtr<FrameNode>>& imageChildren);

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!overlayModifier_) {
            overlayModifier_ = AceType::MakeRefPtr<RichEditorDragOverlayModifier>(WeakClaim(this));
        }
        return MakeRefPtr<TextDragPaintMethod>(WeakClaim(this), overlayModifier_);
    }

    void Initialize(ParagraphManager* paragraph, const TextDragData& data)
    {
        paragraph_ = paragraph;
        textDragData_ = data;
    }

    const ParagraphManager* GetParagraphManager() const
    {
        return paragraph_;
    }

private:
    ParagraphManager* paragraph_;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorDragPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_PATTERN_H
