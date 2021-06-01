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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_SVG_ANIMATE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_SVG_ANIMATE_H

#include "frameworks/bridge/common/dom/dom_node.h"
#include "frameworks/bridge/common/dom/dom_type.h"
#include "frameworks/core/components/svg/svg_animate_component.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT DOMSvgAnimate : public DOMNode {
    DECLARE_ACE_TYPE(DOMSvgAnimate, DOMNode);

public:
    DOMSvgAnimate(NodeId nodeId, const std::string& nodeName);
    ~DOMSvgAnimate() override = default;

    RefPtr<Component> GetSpecializedComponent() override
    {
        return animateComponent_;
    }

protected:
    void OnMounted(const RefPtr<DOMNode>& parentNode) override;
    void PrepareSpecializedComponent() override;
    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;
    void PrepareSpecializedComponent(const RefPtr<SvgAnimateComponent>& animateComponent);

    std::string svgId_;
    std::string attributeName_;
    int32_t begin_ = 0;
    int32_t dur_ = 0;
    int32_t end_ = 0;
    int32_t min_ = 0;
    int32_t max_ = 0;
    Restart restart_ = Restart::ALWAYS;
    int32_t repeatCount_ = 1;
    int32_t repeatDur_ = 0;
    Fill fillMode_ = Fill::REMOVE;
    CalcMode calcMode_ = CalcMode::LINEAR;
    Additive additive_ = Additive::REPLACE;
    Accumulate accumulate_ = Accumulate::NONE;
    std::vector<std::string> values_;
    std::vector<double> keyTimes_;
    std::vector<std::string> keySplines_;
    std::string from_;
    std::string to_;
    std::string by_;
    RefPtr<SvgAnimateComponent> animateComponent_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_SVG_ANIMATE_H
