/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/rich_editor/rich_editor_foreground_modifier.h"

#include "core/components_ng/pattern/common_text/counter_constants.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {

RichEditorForegroundModifier::RichEditorForegroundModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern)
    : CounterForegroundModifier(pattern) {}

void RichEditorForegroundModifier::onDraw(DrawingContext& context)
{
    auto richEditorPattern = DynamicCast<RichEditorPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(richEditorPattern);
    CHECK_NULL_VOID(richEditorPattern->HasInnerBorderColor());
    CHECK_NULL_VOID(innerBorderWidth_);

    auto host = richEditorPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto& canvas = context.canvas;
    RSPen pen;
    pen.SetColor(GetInnerBorderColor().GetValue());
    auto width = GetInnerBorderWidth();
    pen.SetWidth(width);
    pen.SetAntiAlias(true);
    auto frameSize = geometryNode->GetFrameSize();
    auto rsRadius = MakeRRadius(renderContext->GetBorderRadius().value_or(BorderRadiusProperty()), width);
    auto offset = width / COUNTER_BORDER_OFFSET;
    RSRoundRect rrect(
        RSRect(offset, offset, frameSize.Width() - offset,
            frameSize.Height() - offset),
        rsRadius);
    canvas.AttachPen(pen);
    canvas.DrawRoundRect(rrect);
    canvas.DetachPen();
}
} // namespace OHOS::Ace::NG
