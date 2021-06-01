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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_SVG_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_SVG_COMPONENT_H

#include "frameworks/core/components/svg/svg_sharp.h"
#include "frameworks/core/pipeline/base/component_group.h"

namespace OHOS::Ace {

class SvgComponent : public ComponentGroup, public SvgSharp {
    DECLARE_ACE_TYPE(SvgComponent, ComponentGroup, SvgSharp);

public:
    SvgComponent() = default;
    explicit SvgComponent(const std::list<RefPtr<Component>>& children) : ComponentGroup(children) {};
    ~SvgComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;

    RefPtr<Element> CreateElement() override;

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

    void SetWidth(const Dimension& width)
    {
        width_ = width;
    }

    const Dimension& GetWidth() const
    {
        return width_;
    }

    void SetHeight(const Dimension& height)
    {
        height_ = height;
    }

    const Dimension& GetHeight() const
    {
        return height_;
    }

    void SetViewBox(const Rect& viewBox)
    {
        viewBox_ = viewBox;
    }

    const Rect& GetViewBox() const
    {
        return viewBox_;
    }

private:
    Dimension x_;
    Dimension y_;
    Dimension width_ = Dimension(-1.0);
    Dimension height_ = Dimension(-1.0);
    Rect viewBox_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_SVG_COMPONENT_H
