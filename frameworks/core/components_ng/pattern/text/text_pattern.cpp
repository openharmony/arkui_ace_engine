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

#include <stack>

#include "base/utils/utils.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/canvas.h"
#include "core/pipeline/base/render_context.h"

namespace OHOS::Ace::NG {
void TextPattern::OnModifyDone()
{
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    bool shouldClipToContent = textLayoutProperty->GetTextOverflow().value_or(TextOverflow::NONE) == TextOverflow::CLIP;
    host->GetRenderContext()->SetClipToFrame(shouldClipToContent);
}

bool TextPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto textLayoutAlgorithm = DynamicCast<TextLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(textLayoutAlgorithm, false);
    auto paragraph = textLayoutAlgorithm->GetParagraph();
    if (!paragraph) {
        LOGD("on layout process, just return");
        return false;
    }
    paragraph_ = textLayoutAlgorithm->GetParagraph();
    baselineOffset_ = textLayoutAlgorithm->GetBaselineOffset();
    return true;
}

void TextPattern::BeforeCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& layoutProperty = host->GetLayoutProperty();
    auto flag = layoutProperty ? layoutProperty->GetPropertyChangeFlag() : PROPERTY_UPDATE_NORMAL;
    if (paragraph_) {
        // When updating the scenario, needs to determine whether the SpanNode node is refreshed.
        if ((flag & PROPERTY_UPDATE_BY_CHILD_REQUEST) != PROPERTY_UPDATE_BY_CHILD_REQUEST) {
            LOGD("no need to refresh span node");
            return;
        }
    }

    // When dirty areas are marked because of child node changes, the text rendering node tree is reset.
    const auto& children = host->GetChildren();
    if (children.empty()) {
        return;
    }
    spanItemChildren_.clear();

    // Depth-first iterates through all host's child nodes to collect the SpanNode object, building a text rendering
    // tree.
    std::stack<RefPtr<UINode>> nodes;
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        nodes.push(*iter);
    }
    while (!nodes.empty()) {
        auto current = nodes.top();
        nodes.pop();
        // TODO: Add the judgment of display.
        if (!current) {
            continue;
        }
        auto spanNode = DynamicCast<SpanNode>(current);
        if (spanNode) {
            spanNode->CleanSpanItemChildren();
            spanNode->MountToParagraph();
        }
        const auto& nextChildren = current->GetChildren();
        for (auto iter = nextChildren.rbegin(); iter != nextChildren.rend(); ++iter) {
            nodes.push(*iter);
        }
    }
}
} // namespace OHOS::Ace::NG
