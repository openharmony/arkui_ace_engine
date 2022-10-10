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

#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
Dimension SelectHandleInfo::GetDefaultLineWidth()
{
    const Dimension defaultLineWidth = 1.5_vp;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, defaultLineWidth);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, defaultLineWidth);
    return theme->GetHandleLineWidth();
}
} // namespace OHOS::Ace::NG