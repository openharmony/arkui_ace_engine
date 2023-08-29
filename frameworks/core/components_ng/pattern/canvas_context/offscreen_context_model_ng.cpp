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

#include "core/components_ng/pattern/canvas_context/offscreen_context_model_ng.h"

#include "frameworks/core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"

namespace OHOS::Ace::NG {
RefPtr<AceType> OffscreenContextModelNG::CreateOffscreenPattern(int width, int height)
{
    auto offscreenPattern = AceType::MakeRefPtr<NG::OffscreenCanvasPattern>(width, height);
    return offscreenPattern;
}
bool OffscreenContextModelNG::IsSucceed(RefPtr<AceType> offscreenPattern)
{
    auto tempPattern = OHOS::Ace::AceType::DynamicCast<OffscreenCanvasPattern>(offscreenPattern);
    CHECK_NULL_RETURN(tempPattern, false);
    return tempPattern->IsSucceed();
}
} // namespace OHOS::Ace::NG