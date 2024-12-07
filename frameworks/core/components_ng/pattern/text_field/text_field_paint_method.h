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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PAINT_METHOD_H

#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/text_field/text_field_content_modifier.h"
#include "core/components_ng/pattern/text_field/text_field_foreground_modifier.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_overlay_modifier.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextFieldPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(TextFieldPaintMethod, NodePaintMethod)
public:
    TextFieldPaintMethod(const WeakPtr<Pattern>& pattern,
        const RefPtr<TextFieldOverlayModifier>& textFieldOverlayModifier,
        const RefPtr<TextFieldContentModifier>& textFieldContentModifier,
        const RefPtr<TextFieldForegroundModifier>& textFieldForegroundModifier);

    ~TextFieldPaintMethod() override = default;

    RefPtr<Modifier> GetOverlayModifier(PaintWrapper* paintWrapper) override;
    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override;
    void UpdateOverlayModifier(PaintWrapper* paintWrapper) override;

    RefPtr<Modifier> GetForegroundModifier(PaintWrapper* paintWrapper) override;
    void UpdateForegroundModifier(PaintWrapper* paintWrapper) override;

    void SetScrollBar(WeakPtr<ScrollBar>&& scrollBar)
    {
        scrollBar_ = scrollBar;
    }

    void UpdateScrollBar();
    void SetShowUnderlineWidth();
    void SetFloatingCursor();

private:
    void UpdateTextStyleToModifier(
        const RefPtr<TextFieldLayoutProperty>& layoutProperty, const RefPtr<TextFieldTheme>& theme, bool isDisabled);
private:
    WeakPtr<Pattern> pattern_;
    RefPtr<TextFieldOverlayModifier> textFieldOverlayModifier_;
    RefPtr<TextFieldContentModifier> textFieldContentModifier_;
    RefPtr<TextFieldForegroundModifier> textFieldForegroundModifier_;
    WeakPtr<ScrollBar> scrollBar_;

    ACE_DISALLOW_COPY_AND_MOVE(TextFieldPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_PAINT_METHOD_H
