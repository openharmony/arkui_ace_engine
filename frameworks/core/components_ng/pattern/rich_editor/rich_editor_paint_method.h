/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_PAINT_METHOD_H

#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/text/text_content_modifier.h"
#include "core/components_ng/pattern/text/text_overlay_modifier.h"
#include "core/components_ng/pattern/text/text_paint_method.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RichEditorPaintMethod : public TextPaintMethod {
    DECLARE_ACE_TYPE(RichEditorPaintMethod, TextPaintMethod);
public:
    RichEditorPaintMethod(const WeakPtr<Pattern>& pattern, const ParagraphManager* pManager, float baselineOffset,
        const RefPtr<TextContentModifier>& contentMod, const RefPtr<TextOverlayModifier>& overlayMod);

    ~RichEditorPaintMethod() override = default;
    void UpdateContentModifier(PaintWrapper* paintWrapper) override;
    void UpdateOverlayModifier(PaintWrapper* paintWrapper) override;
    void SetCaretState(PaintWrapper* paintWrapper);
    void SetPreviewTextDecoration(PaintWrapper* paintWrapper);
    void SetCaretOffsetAndHeight(PaintWrapper* paintWrapper);

private:
    static std::vector<RectF> CalculateSelectedRect(
        const std::vector<std::pair<std::vector<RectF>, ParagraphStyle>>& selectedRects, float contentWidth);
    const ParagraphManager* pManager_;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_PAINT_METHOD_H
