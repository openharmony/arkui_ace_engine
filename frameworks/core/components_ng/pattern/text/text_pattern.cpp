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

#include "core/components_ng/pattern/text/text_pattern.h"

#include "flutter/third_party/txt/src/txt/paragraph_txt.h"

#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/pipeline/base/render_context.h"

namespace OHOS::Ace::NG {

void TextPattern::PaintContent(RenderContext* renderContext, const OffsetF& offset)
{
    if (!textLayoutAlgorithm_) {
        LOGE("textLayoutAlgorithm is nullptr");
        return;
    }
    const auto& paragraph = textLayoutAlgorithm_->GetTxtParagraph();
    if (!paragraph) {
        LOGE("paragraph is nullptr");
        return;
    }
    // TODO: canvas adapter.
    auto* canvas = static_cast<SkCanvas*>(renderContext->GetCanvas());
    if (canvas == nullptr) {
        LOGE("canvas is nullptr");
        return;
    }
    renderContext->SetDrawContentAtLast(true);
    paragraph->Paint(canvas, offset.GetX(), offset.GetY());
}

void TextPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty)
{
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    if (!layoutAlgorithmWrapper) {
        LOGE("can not find text layout algorithm due to layoutAlgorithmWrapper is null");
        return;
    }
    auto textLayoutAlgorithm = DynamicCast<TextLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    if (!textLayoutAlgorithm) {
        LOGE("can not find text layout algorithm due to textLayoutAlgorithm is null");
        return;
    }
    textLayoutAlgorithm_ = textLayoutAlgorithm;
}

} // namespace OHOS::Ace::NG
