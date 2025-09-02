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

#include "frameworks/core/components_ng/svg/parse/svg_path.h"

#include "frameworks/core/components_ng/svg/parse/svg_constants.h"


namespace OHOS::Ace::NG {

SvgPath::SvgPath() : SvgGraphic() {}

RefPtr<SvgNode> SvgPath::Create()
{
    return AceType::MakeRefPtr<SvgPath>();
}

bool SvgPath::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    if (name == SVG_D) {
        d_ = value;
        return true;
    }
    return false;
}

RSRecordingPath SvgPath::GetPath(const SvgLengthScaleRule& lengthRule)
{
    if (path_.has_value() && lengthRule_ == lengthRule) {
        return path_.value();
    }
    lengthRule_ = lengthRule;
    RSRecordingPath out;
    if (lengthRule.GetLengthScaleUnit() == SvgLengthScaleUnit::OBJECT_BOUNDING_BOX) {
        LOGD("SvgPath::GetobjectBoundingBox : objectBoundingBox");
        auto obb = lengthRule.GetContainerRect();
        if (GreatNotEqual(obb.Width(), 0.0) && GreatNotEqual(obb.Height(), 0.0)) {
            RSMatrix matrix;
            /* Setup matrix  for converting the points in path */
            matrix.SetScaleTranslate(obb.Width(), obb.Height(), obb.Left(), obb.Top());
            RSRecordingPath tmp;
            tmp.BuildFromSVGString(d_);
            /* convert the points in Path with the matrixs */
            tmp.TransformWithPerspectiveClip(matrix, &out, false);
            path_ = out;
            return out;
        }
    }
    out.BuildFromSVGString(d_);
    path_ = out;
    return out;
}

RSRecordingPath SvgPath::AsPath(const SvgLengthScaleRule& lengthRule)
{
    RSRecordingPath out;
    if (d_.empty()) {
        return out;
    }
    /* re-generate the Path for pathTransform(true). AsPath come from clip-path */
    out = GetPath(lengthRule);
    if (attributes_.fillState.IsEvenodd()) {
        out.SetFillStyle(RSPathFillType::EVENTODD);
    }
    /* Apply path transform for clip-path only */
    if (lengthRule.GetPathTransform()) {
        ApplyTransform(out);
    }
    return out;
}

RSRecordingPath SvgPath::AsPath(const Size& /* viewPort */) const
{
    RSRecordingPath out;
    if (!d_.empty()) {
        out.BuildFromSVGString(d_);
        if (attributes_.fillState.IsEvenodd()) {
            out.SetFillStyle(RSPathFillType::EVENTODD);
        }
    }
    return out;
}

} // namespace OHOS::Ace::NG
