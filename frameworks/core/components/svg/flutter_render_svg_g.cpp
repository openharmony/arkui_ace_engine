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

#include "frameworks/core/components/svg/flutter_render_svg_g.h"

#include "frameworks/core/components/svg/flutter_render_svg_filter.h"

namespace OHOS::Ace {

using namespace Flutter;

RefPtr<RenderNode> RenderSvgG::Create()
{
    return AceType::MakeRefPtr<FlutterRenderSvgG>();
}

RenderLayer FlutterRenderSvgG::GetRenderLayer()
{
    if (!transformLayer_) {
        transformLayer_ = AceType::MakeRefPtr<Flutter::TransformLayer>(Matrix4::CreateIdentity(), 0.0, 0.0);
    }
    return AceType::RawPtr(transformLayer_);
}

void FlutterRenderSvgG::Paint(RenderContext& context, const Offset& offset)
{
    if (transformLayer_) {
        if (NeedTransform()) {
            transformLayer_->Update(GetTransformMatrix4());
        }
        if (!filterId_.empty()) {
            auto filter = AceType::DynamicCast<FlutterRenderSvgFilter>(GetPatternFromRoot(filterId_));
            if (filter != nullptr) {
                SkPaint skPaint = filter->OnAsPaint();
                transformLayer_->SetFilter(skPaint);
            }
        }
    }

    RenderNode::Paint(context, offset);
}

void FlutterRenderSvgG::OnGlobalPositionChanged()
{
    if (transformLayer_ && NeedTransform()) {
        transformLayer_->Update(UpdateTransformMatrix4());
    }
    RenderNode::OnGlobalPositionChanged();
}

} // namespace OHOS::Ace
