/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_STYLED_STRING_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_STYLED_STRING_CONTROLLER_H

#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_base_controller.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"


namespace OHOS::Ace::NG {
class ACE_EXPORT RichEditorStyledStringController : public RichEditorBaseController,
    virtual public RichEditorStyledStringControllerBase {
    DECLARE_ACE_TYPE(RichEditorStyledStringController, RichEditorBaseController, RichEditorStyledStringControllerBase);

public:
    void SetStyledString(const RefPtr<SpanStringBase>& value) override;
    RefPtr<SpanStringBase> GetStyledString() override;
    SelectionRangeInfo GetSelection() override;
    void SetOnWillChange(std::function<bool(const StyledStringChangeValue&)> && func) override;
    void SetOnDidChange(std::function<void(const StyledStringChangeValue&)> && func) override;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_STYLED_STRING_CONTROLLER_H