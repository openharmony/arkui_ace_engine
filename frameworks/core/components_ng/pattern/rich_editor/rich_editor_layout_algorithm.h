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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_LAYOUT_ALGORITHM_H

#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RichEditorLayoutAlgorithm : public TextLayoutAlgorithm {
    DECLARE_ACE_TYPE(RichEditorLayoutAlgorithm, TextLayoutAlgorithm);

public:
    RichEditorLayoutAlgorithm() = delete;
    RichEditorLayoutAlgorithm(std::list<RefPtr<SpanItem>> spans, ParagraphManager* paragraphs);
    ~RichEditorLayoutAlgorithm() override = default;

    const OffsetF& GetParentGlobalOffset() const
    {
        return parentGlobalOffset_;
    }
    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    void Measure(LayoutWrapper* layoutWrapper) override;

private:
    void GetPlaceholderRects(std::vector<RectF>& rectF) override;
    int32_t GetPreviousLength() const override;
    ParagraphStyle GetParagraphStyle(const TextStyle& textStyle, const std::string& content) const override;

    void ApplyIndent(const TextStyle& textStyle, double width) override
    { // do nothing
    }

    std::vector<std::list<RefPtr<SpanItem>>> spans_;
    ParagraphManager* pManager_;
    OffsetF parentGlobalOffset_;

    ACE_DISALLOW_COPY_AND_MOVE(RichEditorLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_LAYOUT_ALGORITHM_H
