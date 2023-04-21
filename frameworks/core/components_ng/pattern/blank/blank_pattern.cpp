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

#include "core/components_ng/pattern/blank/blank_pattern.h"

#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/blank/blank_view.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

std::string BlankPattern::GetColorString() const
{
    std::string color;
    auto renderContext = GetHost()->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, "NA");
    return renderContext->GetBackgroundColor().value_or(Color::WHITE).ColorToString();
}

void BlankPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("color", GetColorString().c_str());
}

} // namespace OHOS::Ace::NG
