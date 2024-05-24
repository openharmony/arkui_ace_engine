/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_ANIMATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_ANIMATION_H

#include "base/utils/noncopyable.h"
#include "core/animation/svg_animate.h"
#include "frameworks/core/components_ng/svg/parse/svg_attributes_parser.h"
#include "frameworks/core/components_ng/svg/parse/svg_node.h"

namespace OHOS::Ace::NG {
class SvgAnimation : public SvgNode, public SvgAnimate {
    DECLARE_ACE_TYPE(SvgAnimation, SvgNode, SvgAnimate);

public:
    explicit SvgAnimation(SvgAnimateType svgAnimateType);
    ~SvgAnimation() override = default;

    static RefPtr<SvgNode> Create();
    static RefPtr<SvgNode> CreateAnimateMotion();
    static RefPtr<SvgNode> CreateAnimateTransform();

    void AddOnFinishCallBack(const std::function<void()>& onFinishCallback)
    {
        animator_->AddStopListener(onFinishCallback);
    }

    void SetAttr(const std::string& name, const std::string& value) override;
    void UpdateAttr();

    template<typename T>
    void CreatePropertyAnimation(const T& originalValue, std::function<void(T)>&& callback);

private:
    void OnInitStyle() override;

    static CalcMode ConvertCalcMode(const std::string& val);

    RefPtr<Animator> animator_;
    SvgAnimateAttribute animateAttr_;

    ACE_DISALLOW_COPY_AND_MOVE(SvgAnimation);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_ANIMATION_H