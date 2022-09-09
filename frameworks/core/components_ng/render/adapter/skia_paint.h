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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_PAINT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_PAINT_H

#include "third_party/skia/include/core/SkPaint.h"

#ifdef NG_BUILD
#include "third_party/skia/include/core/SkSamplingOptions.h"
#endif

#include "core/components/common/properties/color.h"
#include "core/components_ng/render/paint.h"

namespace OHOS::Ace::NG {

// Paint is interface for drawing styles.
class SkiaPaint : public Paint {
    DECLARE_ACE_TYPE(NG::SkiaPaint, NG::Paint)

public:
    static RefPtr<Paint> Create();
    SkiaPaint() = default;
    ~SkiaPaint() = default;

    void Reset() override;

    void EnableAntiAlias() override;
    void SetFilterQuality(FilterQuality quality) override;

    void SetStyle(PaintStyle style) override;
    void SetColor(const Color& color) override;
    void SetStrokeWidth(float width) override;
    void SetAlphaf(float alpha) override;
    void SetBlendMode(BlendMode blendMode) override;
    void SetStrokeCap(LineCap lineCap) override;
    void SetColorFilter(const RefPtr<ColorFilter>& colorFilter) override;

    const SkPaint& GetRawPaint()
    {
        return rawPaint_;
    }

#ifdef NG_BUILD
    const SkSamplingOptions& GetSamplingOptions()
    {
        return options_;
    }
#endif

private:
    SkPaint rawPaint_;
#ifdef NG_BUILD
    SkSamplingOptions options_;
#endif
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_PAINT_H
