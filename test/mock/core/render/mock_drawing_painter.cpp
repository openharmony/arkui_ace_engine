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

#include "core/components_ng/render/adapter/rosen/drawing_painter.h"

namespace OHOS::Ace::NG {
void DrawingPainter::DrawPath(
    RSCanvas& canvas, const std::string& commands, const ShapePaintProperty& shapePaintProperty)
{}
bool DrawingPainter::SetPen(RSPen& pen, const ShapePaintProperty& shapePaintProperty)
{
    return false;
}
void DrawingPainter::SetBrush(RSBrush& brush, const ShapePaintProperty& shapePaintProperty) {}
void DrawingPainter::DrawPath(RSCanvas& canvas, const std::string& commands, const OffsetF& offset) {}
SizeF DrawingPainter::GetPathSize(const std::string& commands)
{
    return {};
}
void DrawingPainter::DrawPixelMapMesh(
    RSCanvas& canvas, int32_t row, int32_t column, const std::vector<float>& mesh, const RefPtr<PixelMap>& pixelMap)
{}
} // namespace OHOS::Ace::NG
