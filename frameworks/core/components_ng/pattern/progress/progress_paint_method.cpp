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

#include "core/components_ng/pattern/progress/progress_paint_method.h"

#include <algorithm>
#include <optional>

#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components/picker/picker_option_component.h"
#include "core/components/progress/progress_theme.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"

namespace OHOS::Ace::NG {

void ProgressPaintMethod::GetThemeDate()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto progressTheme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(progressTheme);
    color_ = progressTheme->GetTrackSelectedColor();
    bgColor_ = progressTheme->GetTrackBgColor();
    scaleWidth_ = progressTheme->GetScaleWidth().ConvertToPx();
    scaleCount_ = progressTheme->GetScaleNumber();
    borderColor_ = progressTheme->GetBorderColor();
    capsuleBorderWidth_ = progressTheme->GetBorderWidth();
}


} // namespace OHOS::Ace::NG