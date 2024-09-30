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

#include "core/components_ng/render/path_painter.h"

#ifndef USE_ROSEN_DRAWING
#include "core/components_ng/render/adapter/sk_painter.h"
#else
#include "core/components_ng/render/adapter/rosen/drawing_painter.h"
#endif

namespace OHOS::Ace::NG {
void PathPainter::DrawPath(RSCanvas& canvas, const PathPaintProperty& pathPaintProperty)
{
    if (!pathPaintProperty.HasCommands()) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkPainter::DrawPath(canvas, pathPaintProperty.GetCommandsValue(), pathPaintProperty);
#else
    DrawingPainter::DrawPath(canvas, pathPaintProperty.GetCommandsValue(), pathPaintProperty);
#endif
}

void PathPainter::DrawPath(RSCanvas& canvas, const std::string& commands, const OffsetF& offset)
{
#ifndef USE_ROSEN_DRAWING
    SkPainter::DrawPath(canvas, commands, offset);
#else
    DrawingPainter::DrawPath(canvas, commands, offset);
#endif
}

SizeF PathPainter::GetPathSize(const std::string& commands)
{
#ifndef USE_ROSEN_DRAWING
    return SkPainter::GetPathSize(commands);
#else
    return DrawingPainter::GetPathSize(commands);
#endif
}
} // namespace OHOS::Ace::NG