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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_CONTROLLER_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_base_controller.h"

namespace OHOS::Ace::NG {
class RichEditorPattern;

class ACE_EXPORT RichEditorController : public RichEditorBaseController, public RichEditorControllerBase {
    DECLARE_ACE_TYPE(RichEditorController, RichEditorBaseController, RichEditorControllerBase);

public:
    int32_t AddImageSpan(const ImageSpanOptions& options) override;
    int32_t AddTextSpan(const TextSpanOptions& options) override;
    int32_t AddSymbolSpan(const SymbolSpanOptions& options) override;
    int32_t AddPlaceholderSpan(const RefPtr<UINode>& customNode, const SpanOptionBase& options) override;
    void UpdateSpanStyle(int32_t start, int32_t end, TextStyle textStyle, ImageSpanAttribute imageStyle) override;
    void SetUpdateSpanStyle(struct UpdateSpanStyle updateSpanStyle) override;
    SelectionInfo GetSpansInfo(int32_t start, int32_t end) override;
    SelectionInfo GetSelectionSpansInfo() override;
    std::vector<ParagraphInfo> GetParagraphsInfo(int32_t start, int32_t end) override;
    void DeleteSpans(const RangeOptions& options) override;
    void UpdateParagraphStyle(int32_t start, int32_t end, const struct UpdateParagraphStyle& style) override;
    RefPtr<SpanStringBase> ToStyledString(int32_t start, int32_t end) override;
    SelectionInfo FromStyledString(RefPtr<SpanStringBase> value) override;

private:
    struct UpdateSpanStyle updateSpanStyle_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_CONTROLLER_H
