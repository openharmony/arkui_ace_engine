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

#include "frameworks/bridge/declarative_frontend/jsview/models/rendering_context_model_impl.h"
#include "core/components/custom_paint/custom_paint_component.h"

namespace OHOS::Ace::Framework {
void RenderingContextModelImpl::GetWidth(RefPtr<AceType>& canvasPattern, double& width)
{
    CHECK_NULL_VOID(canvasPattern);
    auto CustomPaintComponent = AceType::DynamicCast<CanvasTaskPool>(canvasPattern);
    if (CustomPaintComponent) {
        width = CustomPaintComponent->GetWidth();
        return;
    }
}

void RenderingContextModelImpl::GetHeight(RefPtr<AceType>& canvasPattern, double& height)
{
    CHECK_NULL_VOID(canvasPattern);
    auto CustomPaintComponent = AceType::DynamicCast<CanvasTaskPool>(canvasPattern);
    if (CustomPaintComponent) {
        height = CustomPaintComponent->GetHeight();
        return;
    }
}

void RenderingContextModelImpl::SetTransferFromImageBitmap(
    RefPtr<AceType>& canvasPattern, RefPtr<AceType> offscreenCPattern)
{
    CHECK_NULL_VOID(canvasPattern);
    auto pool = AceType::DynamicCast<CanvasTaskPool>(canvasPattern);
    if (pool) {
        auto offscreenCanvas = AceType::DynamicCast<OffscreenCanvas>(offscreenCPattern);
        CHECK_NULL_VOID(offscreenCanvas);
        pool->TransferFromImageBitmap(offscreenCanvas);
    }
}
} // namespace OHOS::Ace::Framework
