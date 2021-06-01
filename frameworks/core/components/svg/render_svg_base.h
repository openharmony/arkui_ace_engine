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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_RENDER_SVG_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_RENDER_SVG_BASE_H

#include "frameworks/core/animation/animator.h"
#include "frameworks/core/animation/keyframe_animation.h"
#include "frameworks/core/animation/svg_animate.h"
#include "frameworks/core/components/common/properties/svg_paint_state.h"
#include "frameworks/core/components/svg/svg_animate_component.h"
#include "frameworks/core/components/svg/svg_sharp.h"
#include "frameworks/core/pipeline/base/render_node.h"

namespace OHOS::Ace {

const char ATTR_NAME_WIDTH[] = "width";
const char ATTR_NAME_HEIGHT[] = "height";
const char ATTR_NAME_X[] = "x";
const char ATTR_NAME_Y[] = "y";
const char ATTR_NAME_RX[] = "rx";
const char ATTR_NAME_RY[] = "ry";
const char ATTR_NAME_OPACITY[] = "opacity";

class RenderSvgBase : public RenderNode {
    DECLARE_ACE_TYPE(RenderSvgBase, RenderNode);

public:
    ~RenderSvgBase() override;
    virtual void UpdateMotion(const std::string& path, const std::string& rotate,
        double percent, const Point& point) {};

    virtual bool GetStartPoint(Point& point)
    {
        return false;
    }

    virtual bool PrepareSelfAnimation(const RefPtr<SvgAnimate>& SvgAnimate)
    {
        return false;
    }

    const FillState& GetFillState() const
    {
        return fillState_;
    }

    const StrokeState GetStrokeState() const
    {
        return strokeState_;
    }

    const SvgTextStyle GetTextStyle() const
    {
        return textStyle_;
    }

    bool IsSvgNode() const
    {
        return isSvgNode_;
    }

protected:
    bool PrepareBaseAnimation(const RefPtr<SvgAnimate>& animateComponent);
    template<typename T>
    bool CreatePropertyAnimation(const RefPtr<SvgAnimate>& component, const T& originalValue,
        std::function<void(T value)>&& callback, const RefPtr<Evaluator<T>>& evaluator);
    template<typename T>
    bool SetPresentationProperty(const std::string& attrName, const T& val, bool isSelf = true);

    double ConvertDimensionToPx(const Dimension& value,  double baseValue);

    void SetPresentationAttrs(const RefPtr<SvgSharp>& svgSharp);

    void PrepareWeightAnimate(const RefPtr<SvgAnimate>& svgAnimate, std::vector<std::string>& valueVector,
        const std::string& originalValue, bool& isBy);

    void PrepareAnimation(const std::list<RefPtr<Component>>& componentChildren);
    bool PreparePropertyAnimation(const RefPtr<SvgAnimate>& svgAnimate);

    FillState fillState_;
    StrokeState strokeState_;
    SvgTextStyle textStyle_;
    std::unordered_map<std::string, RefPtr<Animator>> animators_;
    bool isSvgNode_ = false;

    virtual void OnNotifyRender()
    {
        MarkNeedRender(true);
    }

private:
    template<typename T>
    void PreparePresentationAnimation(const RefPtr<SvgAnimate>& svgAnimate, const T& originalValue,
        const RefPtr<Evaluator<T>>& evaluator);
    bool PrepareAnimateMotion(const RefPtr<SvgAnimate>& svgAnimate);
    template<typename T>
    void ChangeChildInheritValue(const RefPtr<RenderNode>& svgBase, const std::string& attrName, T value);
    bool IsSelfValue(const std::string& attrName);
    bool HasAnimator(const std::string& attrName);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_RENDER_SVG_BASE_H
