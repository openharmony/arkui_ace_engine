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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_ALGORITHM_H

#include <string>
#include <utility>

#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
class PipelineContext;

// TextLayoutAlgorithm acts as the underlying text layout.
class ACE_EXPORT TextLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(TextLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    TextLayoutAlgorithm();

    explicit TextLayoutAlgorithm(std::list<RefPtr<SpanItem>> spanItemChildren)
        : spanItemChildren_(std::move(spanItemChildren))
    {}

    ~TextLayoutAlgorithm() override = default;

    void OnReset() override;

    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

    const std::shared_ptr<RSParagraph>& GetParagraph();
    float GetBaselineOffset() const;

private:
    bool CreateParagraph(const TextStyle& textStyle, std::string content);
    bool CreateParagraphAndLayout(
        const TextStyle& textStyle, const std::string& content, const LayoutConstraintF& contentConstraint);
    bool AdaptMinTextSize(TextStyle& textStyle, const std::string& content, const LayoutConstraintF& contentConstraint,
        const RefPtr<PipelineContext>& pipeline);
    bool DidExceedMaxLines(const LayoutConstraintF& contentConstraint);
    static TextDirection GetTextDirection(const std::string& content);
    float GetTextWidth() const;

    std::list<RefPtr<SpanItem>> spanItemChildren_;
    std::shared_ptr<RSParagraph> paragraph_;
    float baselineOffset_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(TextLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_ALGORITHM_H
