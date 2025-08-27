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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/text_drag/text_drag_paint_method.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_content_modifier.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_info.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RichEditorDragPaintMethod : public TextDragPaintMethod {
    DECLARE_ACE_TYPE(RichEditorDragPaintMethod, TextDragPaintMethod);
public:
    RichEditorDragPaintMethod(const WeakPtr<Pattern>& pattern,
        const RefPtr<TextDragOverlayModifier>& overlayMod, const RefPtr<RichEditorDragContentModifier>& contentMod,
        const TextDragInfo& info);

    ~RichEditorDragPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override;
    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

private:
    RefPtr<RichEditorDragContentModifier> contentModifier_;
    TextDragInfo info_;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorDragPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_DRAG_TEXT_DRAG_PAINT_METHOD_H
