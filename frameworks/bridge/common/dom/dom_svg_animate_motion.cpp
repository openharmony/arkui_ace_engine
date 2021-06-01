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

#include "frameworks/bridge/common/dom/dom_svg_animate_motion.h"

#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

void DOMSvgAnimateMotion::PrepareSpecializedComponent()
{
    if (!animateComponent_) {
        animateComponent_ = AceType::MakeRefPtr<SvgAnimateComponent>(std::to_string(GetNodeId()),
            GetTag(), SvgAnimateType::MOTION);
    }
    DOMSvgAnimate::PrepareSpecializedComponent(animateComponent_);
    animateComponent_->SetKeyPoints(keyPoints_);
    animateComponent_->SetPath(path_);
    animateComponent_->SetRotate(rotate_);
}

bool DOMSvgAnimateMotion::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (DOMSvgAnimate::SetSpecializedAttr(attr)) {
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_KEY_POINTS) {
        StringUtils::StringSpliter(attr.second, ';', keyPoints_);
        return true;
    }

    if (attr.first == DOM_SVG_ANIMATION_PATH) {
        path_ = attr.second;
        return true;
    }

    if (attr.first == DOM_SVG_ANIMATION_ROTATE) {
        rotate_ = attr.second;
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::Framework
