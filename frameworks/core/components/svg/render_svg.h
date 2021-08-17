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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_RENDER_SVG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_RENDER_SVG_H

#include "frameworks/core/components/svg/render_svg_base.h"
#include "frameworks/core/components/svg/svg_component.h"

namespace OHOS::Ace {

class RenderSvg : public RenderSvgBase {
    DECLARE_ACE_TYPE(RenderSvg, RenderSvgBase);

public:
    static RefPtr<RenderNode> Create();
    ~RenderSvg() override;

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    bool PrepareSelfAnimation(const RefPtr<SvgAnimate>& svgAnimate) override;

    const Rect& GetViewBox() const
    {
        return viewBox_;
    }

    const Dimension& GetX() const
    {
        return x_;
    }

    const Dimension& GetY() const
    {
        return y_;
    }

    const Dimension& GetWidth() const
    {
        return width_;
    }

    const Dimension& GetHeight() const
    {
        return height_;
    }

    bool IsRoot() const
    {
        return isRoot_;
    }

    void AddMaskNode(const std::string& id, const RefPtr<RenderSvgBase>& mask)
    {
        if (id.empty() || mask == nullptr) {
            return;
        }
        svgMaskNodes_[id] = mask;
    }

    RefPtr<RenderSvgBase> GetMaskNode(const std::string& id)
    {
        if (svgMaskNodes_.find(id) == svgMaskNodes_.end()) {
            return nullptr;
        }
        return svgMaskNodes_[id];
    }

    void MarkIsFixSize(bool isFixSize)
    {
        isFixSize_ = isFixSize;
    }

protected:
    Rect viewBox_;

private:
    void PrepareAnimations();
    void AddSvgAnimations(const RefPtr<SvgComponent>& svgComponent);
    bool SetProperty(const std::string& attrName, const Dimension& value);
    bool GetProperty(const std::string& attrName, Dimension& dimension) const;
    void SetOpacityCallback();
    bool OpacityAnimation(const RefPtr<SvgAnimate>& svgAnimate);
    void UpdateTransform();

    Dimension x_;
    Dimension y_;
    Dimension width_ = Dimension(-1.0);
    Dimension height_ = Dimension(-1.0);
    bool isRoot_ = false;
    bool autoMirror_ = false;
    std::vector<RefPtr<SvgAnimate>> svgAnimates_;
    bool hasUpdated_ = false;
    std::function<void(double)> opacityCallback_;
    std::map<std::string, RefPtr<RenderSvgBase>> svgMaskNodes_;
    bool isFixSize_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_RENDER_SVG_H
