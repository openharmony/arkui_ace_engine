/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "base/utils/measure_util.h"
#include "core/components/custom_paint/render_custom_paint.h"

namespace OHOS::Ace {
double MeasureUtil::MeasureText(const MeasureContext& context)
{
    return RenderCustomPaint::PaintMeasureText(context);
}

Size MeasureUtil::MeasureTextSize(const MeasureContext& context)
{
    return RenderCustomPaint::MeasureTextSize(context);
}
} // namespace OHOS::Ace
