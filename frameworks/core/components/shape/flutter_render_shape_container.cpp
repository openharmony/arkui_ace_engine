/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/core/components/shape/flutter_render_shape_container.h"

#include "frameworks/core/components/transform/flutter_render_transform.h"
#include "frameworks/core/pipeline/base/flutter_render_context.h"

namespace OHOS::Ace {

using namespace Flutter;

RefPtr<RenderNode> RenderShapeContainer::Create()
{
    return AceType::MakeRefPtr<FlutterRenderShapeContainer>();
}

RenderLayer FlutterRenderShapeContainer::GetRenderLayer()
{
    if (!transformLayer_) {
        transformLayer_ = AceType::MakeRefPtr<Flutter::TransformLayer>(Matrix4::CreateIdentity(), 0.0, 0.0);
    }
    return AceType::RawPtr(transformLayer_);
}

void FlutterRenderShapeContainer::Paint(RenderContext& context, const Offset& offset)
{
    double viewBoxWidth = NormalizePercentToPx(viewBox_.Width(), false);
    double viewBoxHeight = NormalizePercentToPx(viewBox_.Height(), true);
    double viewBoxLeft = NormalizePercentToPx(viewBox_.Left(), false);
    double viewBoxTop = NormalizePercentToPx(viewBox_.Top(), true);
    if (!GetLayoutSize().IsInfinite() && GreatNotEqual(viewBoxWidth, 0.0) && GreatNotEqual(viewBoxHeight, 0.0)) {
        double scale = std::min(GetLayoutSize().Width() / viewBoxWidth,
            GetLayoutSize().Height() / viewBoxHeight);
        double tx = GetLayoutSize().Width() * 0.5 - (viewBoxWidth * 0.5 + viewBoxLeft) * scale;
        double ty = GetLayoutSize().Height() * 0.5 - (viewBoxHeight * 0.5 + viewBoxTop) * scale;
        auto transform = Matrix4::CreateScale(static_cast<float>(scale), static_cast<float>(scale), 1.0f);
        transform = FlutterRenderTransform::GetTransformByOffset(transform, GetGlobalOffset());
        transform = Matrix4::CreateTranslate(static_cast<float>(tx), static_cast<float>(ty), 0.0f) * transform;
        transformLayer_->Update(transform);
    }
    RenderNode::Paint(context, offset);
}

} // namespace OHOS::Ace
