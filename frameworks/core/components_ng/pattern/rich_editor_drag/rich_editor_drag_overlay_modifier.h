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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_OVERLAY_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_OVERLAY_MODIFIER_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_overlay_modifier.h"

namespace OHOS::Ace::NG {
class RichEditorDragOverlayModifier : public TextDragOverlayModifier {
    DECLARE_ACE_TYPE(RichEditorDragOverlayModifier, TextDragOverlayModifier);

public:
    RichEditorDragOverlayModifier(
        const WeakPtr<OHOS::Ace::NG::Pattern>& pattern, const WeakPtr<RichEditorPattern>& hostPattern)
        : TextDragOverlayModifier(pattern), hostPattern_(hostPattern)
    {}
    ~RichEditorDragOverlayModifier() override = default;

    void onDraw(DrawingContext& context) override;

private:
    const WeakPtr<RichEditorPattern> hostPattern_;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorDragOverlayModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_OVERLAY_MODIFIER_H
