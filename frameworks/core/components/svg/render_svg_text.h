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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_RENDER_SVG_TEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_RENDER_SVG_TEXT_H

#include "base/memory/ace_type.h"

#include "frameworks/core/animation/animator.h"
#include "frameworks/core/components/common/properties/svg_paint_state.h"
#include "frameworks/core/components/svg/render_svg_base.h"
#include "frameworks/core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RenderSvgText : public RenderSvgBase {
    DECLARE_ACE_TYPE(RenderSvgText, RenderSvgBase)

public:
    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    bool PrepareSelfAnimation(const RefPtr<SvgAnimate>& svgAnimate) override;

    const std::string& GetTextData() const
    {
        return textData_;
    }

    void SetTextData(const std::string& textData)
    {
        textData_ = textData;
    }

    const Dimension& GetX() const
    {
        return x_;
    }

    const Dimension& GetY() const
    {
        return y_;
    }

    const Dimension& GetDx() const
    {
        return dx_;
    }

    const Dimension& GetDy() const
    {
        return dy_;
    }

    const Dimension& GetTextLength() const
    {
        return textLength_;
    }

    const std::string& GetLengthAdjust() const
    {
        return lengthAdjust_;
    }

    double GetRotate() const
    {
        return rotate_;
    }

protected:
    Dimension x_ = Dimension(0.0);
    Dimension y_ = Dimension(0.0);
    Dimension dx_ = Dimension(0.0);
    Dimension dy_ = Dimension(0.0);
    Dimension textLength_ = Dimension(0.0);
    std::string lengthAdjust_ = "spacing"; // Value type: spacing | spacingAndGlyphs
    std::string textData_;
    double rotate_ = 0.0;
    bool hasX_ = false;
    bool hasY_ = false;

private:
    void PrepareAnimations(const RefPtr<Component>& component);
    bool SetProperty(const std::string& attributeName, const Dimension& value);
    bool GetProperty(const std::string& attrName, Dimension& dimension) const;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_RENDER_SVG_TEXT_H
