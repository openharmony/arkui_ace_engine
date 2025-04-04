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

#include "frameworks/core/components_ng/svg/parse/svg_clip_path.h"

namespace OHOS::Ace::NG {

RefPtr<SvgNode> SvgClipPath::Create()
{
    return AceType::MakeRefPtr<SvgClipPath>();
}

void SvgClipPath::OnClipEffect(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext)
{
    auto context = GetContext().Upgrade();
    CHECK_NULL_VOID(context);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(attributes_.clipState.GetClipPathUnits());
    clipPathRule.SetPathTransform(true);
    auto clipPath = AsPath(clipPathRule);
    if (!clipPath.IsValid()) {
        LOGW("OnClipPath abandon, clipPath is empty");
        return;
    }
    canvas.ClipPath(clipPath, RSClipOp::INTERSECT, true);
}

RSRecordingPath SvgClipPath::AsPath(const SvgLengthScaleRule& lengthRule)
{
    RSRecordingPath path;
    for (const auto& child : children_) {
        auto childPath = child->AsPath(lengthRule);
        //clip-rule in clipPath override the fill-rule in the Path base on SVG standard
        if (attributes_.clipState.IsEvenodd()) {
            childPath.SetFillStyle(RSPathFillType::EVENTODD);
        } else {
            childPath.SetFillStyle(RSPathFillType::WINDING);
        }
        path.Op(path, childPath, RSPathOp::UNION);
    }
    return path;
}
} // namespace OHOS::Ace::NG
