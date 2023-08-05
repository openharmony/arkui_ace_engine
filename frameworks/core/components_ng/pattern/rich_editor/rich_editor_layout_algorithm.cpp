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

#include "core/components_ng/pattern/rich_editor/rich_editor_layout_algorithm.h"

namespace OHOS::Ace::NG {
RichEditorLayoutAlgorithm::RichEditorLayoutAlgorithm() = default;

RichEditorLayoutAlgorithm::RichEditorLayoutAlgorithm(
    std::list<RefPtr<SpanItem>> spanItemChildren, const RefPtr<Paragraph>& paragraph)
    : TextLayoutAlgorithm(spanItemChildren, paragraph)
{}

RichEditorLayoutAlgorithm::~RichEditorLayoutAlgorithm() = default;

void RichEditorLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto context = layoutWrapper->GetHostNode()->GetContext();
    CHECK_NULL_VOID(context);
    parentGlobalOffset_ = layoutWrapper->GetHostNode()->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    TextLayoutAlgorithm::Layout(layoutWrapper);
}
} // namespace OHOS::Ace::NG
