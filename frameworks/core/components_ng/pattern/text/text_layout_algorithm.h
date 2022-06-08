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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUR_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUR_ALGORITHM_H

#include <string>

#include "flutter/lib/ui/text/paragraph_builder.h"

#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/text/text_paragraph.h"

namespace OHOS::Ace::NG {
class PipelineContext;

// TextLayoutAlgorithm acts as the underlying text layout.
class ACE_EXPORT TextLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(TextLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    TextLayoutAlgorithm();

    ~TextLayoutAlgorithm() override = default;

    void Reset() override;

    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

    const std::unique_ptr<txt::Paragraph>& GetTxtParagraph();

private:
    bool CreateParagraph(const TextStyle& textStyle, const RefPtr<PipelineContext>& context, std::string content);
    TextDirection GetTextDirection(const std::string& content);
    double GetTextWidth() const;

    // TODO: Delete the txt::Paragraph deps, use adpater.
    std::unique_ptr<txt::Paragraph> paragraph_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(TextLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUR_ALGORITHM_H
