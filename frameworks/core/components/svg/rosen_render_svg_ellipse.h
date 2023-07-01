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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_ROSEN_RENDER_SVG_ELLIPSE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_ROSEN_RENDER_SVG_ELLIPSE_H

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkPath.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

#include "frameworks/core/components/svg/render_svg_ellipse.h"

namespace OHOS::Ace {

class RosenRenderSvgEllipse : public RenderSvgEllipse {
    DECLARE_ACE_TYPE(RosenRenderSvgEllipse, RenderSvgEllipse);

public:
    void Paint(RenderContext& context, const Offset& offset) override;

    void PaintDirectly(RenderContext& context, const Offset& offset) override;

    bool HasEffectiveTransform() const override
    {
        return NeedTransform();
    }

    void UpdateMotion(const std::string& path, const std::string& rotate, double percent) override;

    Rect GetPaintBounds(const Offset& offset) override;

protected:
#ifndef USE_ROSEN_DRAWING
    void GetPath(SkPath& path);
#else
    void GetPath(RSPath& path);
#endif

private:
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SVG_ROSEN_RENDER_SVG_ELLIPSE_H
