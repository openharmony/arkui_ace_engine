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

#ifndef USE_ROSEN_DRAWING
SkPath SvgPath::AsPath(const Size& /* viewPort */) const
{
    SkPath out;
    if (!pathD.empty()) {
        SkParsePath::FromSVGString(d_.c_str(), &out);
        if (attributes_.fillState.IsEvenodd()) {
            out.setFillType(SkPathFillType::kEvenOdd);
        }
    }
    return out;
}
#else
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
#endif

} // namespace OHOS::Ace::NG
