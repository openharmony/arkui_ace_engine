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

#include "ui/base/utils/measure_utils.h"

#include "frameworks/base/utils/measure_util.h"

namespace OHOS::Ace::Kit {
NG::SizeF MeasureUtils::GetMeasureTextSize(const MeasureContext& context)
{
    Ace::MeasureContext aceContext;
    aceContext.textContent = context.data;
    aceContext.fontSize = context.fontSize;
    auto measuredSize = OHOS::Ace::MeasureUtil::MeasureTextSize(aceContext);
    return NG::SizeF(measuredSize.Width(), measuredSize.Height());
}
} // OHOS::Ace::Kit