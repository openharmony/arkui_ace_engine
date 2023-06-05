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

#include "frameworks/core/components_ng/pattern/rendering_context/rendering_context_model_ng.h"

namespace OHOS::Ace::NG {
void RenderingContextModelNG::GetWidth(RefPtr<AceType>& canvasPattern, double& width)
{
    auto customPaintPattern = AceType::DynamicCast<NG::CustomPaintPattern>(canvasPattern);
    if (customPaintPattern) {
        width = customPaintPattern->GetWidth();
    }
}

void RenderingContextModelNG::GetHeight(RefPtr<AceType>& canvasPattern, double& height)
{
    auto customPaintPattern = AceType::DynamicCast<NG::CustomPaintPattern>(canvasPattern);
    if (customPaintPattern) {
        height = customPaintPattern->GetHeight();
    }
}

void RenderingContextModelNG::SetTransferFromImageBitmap(RefPtr<AceType>& canvasPattern,
    RefPtr<AceType> offscreenCPattern)
{
    CHECK_NULL_VOID(canvasPattern);
    auto customPaintPattern = AceType::DynamicCast<NG::CustomPaintPattern>(canvasPattern);
    if (customPaintPattern) {
        auto offscreenCanvasPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(offscreenCPattern);
        CHECK_NULL_VOID(offscreenCanvasPattern);
        customPaintPattern->TransferFromImageBitmap(offscreenCanvasPattern);
    }
}
} // namespace OHOS::Ace::NG