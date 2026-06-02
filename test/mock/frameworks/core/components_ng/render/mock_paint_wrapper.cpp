/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "ui/view/draw/node_paint_method.h"

#include "core/components_ng/base/extension_handler.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
PaintWrapper::~PaintWrapper() = default;

PaintWrapper::PaintWrapper(
    WeakPtr<RenderContext> renderContext, RefPtr<GeometryNode> geometryNode, RefPtr<PaintProperty> paintProperty)
    : renderContext_(std::move(renderContext)), geometryNode_(std::move(geometryNode)),
      paintProperty_(std::move(paintProperty))
{}

RefPtr<RenderContext> PaintWrapper::GetRenderContext() const
{
    return renderContext_.Upgrade();
}

void PaintWrapper::SetNodePaintMethod(const RefPtr<NodePaintMethod>& nodePaintImpl)
{
    nodePaintImpl_ = nodePaintImpl;
}
} // namespace OHOS::Ace::NG
