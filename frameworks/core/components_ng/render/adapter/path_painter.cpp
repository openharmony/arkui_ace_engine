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

#include "core/components_ng/render/adapter/rosen/drawing_painter.h"
#include "core/components_ng/render/path_painter.h"

namespace OHOS::Ace::NG {
void PathPainter::DrawPath(RSCanvas& canvas, const PathPaintProperty& pathPaintProperty)
{
    if (!pathPaintProperty.HasCommands()) {
        return;
    }
    DrawingPainter::DrawPath(canvas, pathPaintProperty.GetCommandsValue(), pathPaintProperty);
}

void PathPainter::DrawPath(RSCanvas& canvas, const std::string& commands, const OffsetF& offset)
{
    DrawingPainter::DrawPath(canvas, commands, offset);
}

SizeF PathPainter::GetPathSize(const std::string& commands)
{
    return DrawingPainter::GetPathSize(commands);
}
} // namespace OHOS::Ace::NG