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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_SVG_TEXT_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_SVG_TEXT_COMPONENT_H

#include "frameworks/core/components/svg/svg_sharp.h"
#include "frameworks/core/pipeline/base/component_group.h"

namespace OHOS::Ace {

class SvgTextComponent : public ComponentGroup, public SvgSharp {
    DECLARE_ACE_TYPE(SvgTextComponent, ComponentGroup);

public:
    SvgTextComponent() = default;
    explicit SvgTextComponent(const std::list<RefPtr<Component>>& children) : ComponentGroup(children) {};
    ~SvgTextComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;

    RefPtr<Element> CreateElement() override;

    const std::string& GetTextData() const
    {
        return textData_;
    }

    void SetTextData(const std::string& textData)
    {
        textData_ = textData;
    }

    void SetX(const Dimension& x)
    {
        x_ = x;
    }

    const Dimension& GetX() const
    {
        return x_;
    }

    void SetY(const Dimension& y)
    {
        y_ = y;
    }

    const Dimension& GetY() const
    {
        return y_;
    }

    void SetDx(const Dimension& dx)
    {
        dx_ = dx;
    }

    const Dimension& GetDx() const
    {
        return dx_;
    }

    void SetDy(const Dimension& dy)
    {
        dy_ = dy;
    }

    const Dimension& GetDy() const
    {
        return dy_;
    }

    void SetHasX(bool hasX)
    {
        hasX_ = hasX;
    }

    bool GetHasX() const
    {
        return hasX_;
    }

    void SetHasY(bool hasY)
    {
        hasY_ = hasY;
    }

    bool GetHasY() const
    {
        return hasY_;
    }

    void SetRotate(double rotate)
    {
        rotate_ = rotate;
    }

    double GetRotate() const
    {
        return rotate_;
    }

    void SetTextLength(const Dimension& textLength)
    {
        textLength_ = textLength;
    }

    const Dimension& GetTextLength() const
    {
        return textLength_;
    }

    void SetLengthAdjust(const std::string& lengthAdjust)
    {
        lengthAdjust_ = lengthAdjust;
    }

    const std::string& GetLengthAdjust() const
    {
        return lengthAdjust_;
    }

private:
    double rotate_ = 0.0;
    bool hasX_ = false;
    bool hasY_ = false;
    Dimension x_;
    Dimension y_;
    Dimension dx_;
    Dimension dy_;
    Dimension textLength_ = Dimension(0.0);
    std::string lengthAdjust_ = "spacing"; // Value type: spacing | spacingAndGlyphs
    std::string textData_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_SVG_TEXT_COMPONENT_H
