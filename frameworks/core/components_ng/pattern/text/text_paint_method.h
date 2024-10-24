/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_PAINT_METHOD_H

#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/text/text_content_modifier.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_overlay_modifier.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(TextPaintMethod, NodePaintMethod)
public:
    TextPaintMethod(const WeakPtr<Pattern>& pattern, float baselineOffset,
        RefPtr<TextContentModifier> textContentModifier, RefPtr<TextOverlayModifier> textOverlayModifier);

    ~TextPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override;
    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

    RefPtr<Modifier> GetOverlayModifier(PaintWrapper* paintWrapper) override;
    void UpdateOverlayModifier(PaintWrapper* paintWrapper) override;

protected:
    WeakPtr<Pattern> GetPattern() const
    {
        return pattern_;
    }

private:
    void UpdateParagraphAndImageSpanNodeList();
    void UpdateObscuredRects();
    static std::vector<RectF> CalculateSelectedRect(
        const std::vector<std::pair<std::vector<RectF>, ParagraphStyle>>& selectedRects, float contentWidth);

    WeakPtr<Pattern> pattern_;
    float baselineOffset_;

    RefPtr<TextContentModifier> textContentModifier_;
    RefPtr<TextOverlayModifier> textOverlayModifier_;

    ACE_DISALLOW_COPY_AND_MOVE(TextPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_PAINT_METHOD_H
