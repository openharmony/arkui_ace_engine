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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_SWIPER_SWIPER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_SWIPER_SWIPER_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class SwiperPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(SwiperPaintMethod, NodePaintMethod)

public:
    SwiperPaintMethod(Axis axis, float mainDelta) : axis_(axis), mainDelta_(mainDelta) {};
    ~SwiperPaintMethod() override = default;

    CanvasDrawFunction GetOverlayDrawFunction(PaintWrapper* paintWrapper) override;
    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

    void SetNeedPaintFade(bool needPaintFade)
    {
        needPaintFade_ = needPaintFade;
    }

    void SetNeedClipPadding(bool needClipPadding)
    {
        needClipPadding_ = needClipPadding;
    }

private:
    void PaintFade(RSCanvas& canvas, PaintWrapper* paintWrapper) const;
    void ClipPadding(PaintWrapper* paintWrapper, RSCanvas& canvas) const;

    bool needPaintFade_ = false;
    bool needClipPadding_ = false;
    Axis axis_;
    float mainDelta_ = 0.0f;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_SWIPER_SWIPER_PAINT_METHOD_H
