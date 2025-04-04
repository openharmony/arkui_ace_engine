/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/svg/parse/svg_g.h"

namespace OHOS::Ace::NG {

SvgG::SvgG() : SvgGroup() {}

RefPtr<SvgNode> SvgG::Create()
{
    return AceType::MakeRefPtr<SvgG>();
}

RSRecordingPath SvgG::AsPath(const Size& viewPort) const
{
    RSRecordingPath path;
    for (const auto& child : children_) {
        auto childPath = child->AsPath(viewPort);
        path.Op(path, childPath, RSPathOp::UNION);
    }
    return path;
}

RSRecordingPath SvgG::AsPath(const SvgLengthScaleRule& lengthRule)
{
    RSRecordingPath path;
    for (const auto& child : children_) {
        auto childPath = child->AsPath(lengthRule);
        path.Op(path, childPath, RSPathOp::UNION);
    }
    ApplyTransform(path, lengthRule);
    return path;
}

void SvgG::ApplyOpacity(RSCanvas& canvas)
{
    if (!attributes_.hasOpacity) {
        return;
    }
    RSBrush brush;
    brush.SetAlphaF(attributes_.opacity);
    RSSaveLayerOps slo(nullptr, &brush);
    canvas.SaveLayer(slo);
}

void SvgG::OnDraw(RSCanvas& canvas, const SvgLengthScaleRule& lengthRule)
{
    ApplyOpacity(canvas);
    SvgNode::OnDraw(canvas, lengthRule);
    return;
}

} // namespace OHOS::Ace::NG
