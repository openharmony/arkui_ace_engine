/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PARAGRAPH_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PARAGRAPH_UTIL_H

#include <list>
#include <memory>
#include <optional>
#include <string>

#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_ng/pattern/text/span_node.h"

namespace OHOS::Ace::NG {

class ParagraphUtil {
public:
    static TextDirection GetTextDirection(const std::u16string& content, LayoutWrapper* layoutWrapper);
    static TextDirection GetTextDirectionByContent(const std::u16string& content);
    static void GetSpanParagraphStyle(LayoutWrapper* layoutWrapper,
        const RefPtr<SpanItem>& spanItem, ParagraphStyle& pStyle);
    static void ConstructParagraphSpanGroup(std::list<RefPtr<SpanItem>>& spans,
        std::vector<std::list<RefPtr<SpanItem>>>& spanGroupVec,
        bool& spanStringHasMaxLines);
    static void HandleEmptyParagraph(RefPtr<Paragraph> paragraph, const std::list<RefPtr<SpanItem>>& spanGroup);
    static void ApplyIndent(ParagraphStyle& paragraphStyle, const RefPtr<Paragraph>& paragraph, double width,
        const TextStyle& textStyle, double indentMaxWidth);
    static ParagraphStyle GetParagraphStyle(const TextStyle& textStyle);
    static ImageSourceInfo CreateImageSourceInfo(const ImageSpanOptions& options);
    static PlaceholderAlignment GetPlaceHolderAlignmentFromVerticalAlign(VerticalAlign verticalAlign);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PARAGRAPH_UTIL_H