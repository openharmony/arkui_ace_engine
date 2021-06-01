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

#include "frameworks/core/components/svg/flutter_render_svg.h"

#include "frameworks/core/components/transform/flutter_render_transform.h"
#include "frameworks/core/pipeline/base/flutter_render_context.h"

namespace OHOS::Ace {

using namespace Flutter;

RefPtr<RenderNode> RenderSvg::Create()
{
    return AceType::MakeRefPtr<FlutterRenderSvg>();
}

RenderLayer FlutterRenderSvg::GetRenderLayer()
{
    if (!transformLayer_) {
        transformLayer_ = AceType::MakeRefPtr<Flutter::TransformLayer>(Matrix4::CreateIdentity(), 0.0, 0.0);
    }
    return AceType::RawPtr(transformLayer_);
}

void FlutterRenderSvg::Paint(RenderContext& context, const Offset& offset)
{
    if (GreatNotEqual(viewBox_.Width(), 0.0) && GreatNotEqual(viewBox_.Height(), 0.0)) {
        double scale = std::min(GetLayoutSize().Width() / viewBox_.Width(),
            GetLayoutSize().Height() / viewBox_.Height());
        double tx = (GetLayoutSize().Width() - (viewBox_.Width() + viewBox_.Left()) * scale) * 0.5;
        double ty = (GetLayoutSize().Height() - (viewBox_.Height() + viewBox_.Top()) * scale) * 0.5;
        auto transform = Matrix4::CreateScale(scale, scale, 1.0f);
        transform = FlutterRenderTransform::GetTransformByOffset(transform, GetGlobalOffset());
        transform = Matrix4::CreateTranslate(tx, ty, 0.0f) * transform;
        transformLayer_->Update(transform);
    }
    RenderNode::Paint(context, offset);
}

} // namespace OHOS::Ace
