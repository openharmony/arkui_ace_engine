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

#include "core/components_ng/pattern/select/select_paint_property.h"

#include "core/components/select/select_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void SelectPaintProperty::ToJsonValue(
    std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    PaintProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto theme = pipelineContext->GetTheme<SelectTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    json->PutExtAttr("backgroundColor",
        propBackgroundColor_.value_or(theme->GetButtonBackgroundColor()).ColorToString().c_str(), filter);
}
} // namespace OHOS::Ace::NG
