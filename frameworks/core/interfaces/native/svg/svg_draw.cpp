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

#include "base/log/log.h"
#include "core/components_ng/image_provider/adapter/rosen/drawing_image_data.h"
#include "core/components_ng/image_provider/adapter/skia_svg_dom.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/svg/svg_dom.h"

namespace OHOS::Ace::NG {
namespace {
void Draw(RSCanvas* canvas, const uint8_t* data, size_t dataLen, const Size& size)
{
    CHECK_NULL_VOID(canvas);
#ifdef USE_ROSEN_DRAWING
    auto drawingData = std::make_shared<RSData>();
    drawingData->BuildWithCopy(data, dataLen);
    auto drawingImageData = AceType::MakeRefPtr<NG::DrawingImageData>(drawingData);
    auto svgDom = drawingImageData->MakeSvgDom(std::nullopt);
    CHECK_NULL_VOID(svgDom);
    svgDom->DrawImage(*canvas, ImageFit::COVER, size);
#endif
}
} // namespace
extern "C" {

ACE_FORCE_EXPORT void OHOS_ACE_DrawSVG(void* canvas, uint8_t* data, size_t dataLen, float width, float height)
{
#ifdef USE_ROSEN_DRAWING
    CHECK_NULL_VOID(data);
    CHECK_NULL_VOID(dataLen != 0);
    auto rsCanvas = reinterpret_cast<RSCanvas*>(canvas);
    CHECK_NULL_VOID(rsCanvas);
    Draw(rsCanvas, data, dataLen, Size(width, height));
#endif
}
}
} // namespace OHOS::Ace::NG