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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_OFFSCREEN_CANVAS_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_OFFSCREEN_CANVAS_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class OffscreenCanvasPaintMethod;
class ACE_EXPORT OffscreenCanvasPattern : public Pattern {
    DECLARE_ACE_TYPE(OffscreenCanvasPattern, Pattern);

public:
    OffscreenCanvasPattern(int32_t width, int32_t height);
    ~OffscreenCanvasPattern() override = default;

    void FillRect(const Rect& rect);
    void StrokeRect(const Rect& rect);
    std::unique_ptr<Ace::ImageData> GetImageData(double left, double top, double width, double height);

    void UpdateFillColor(const Color& color);
    int32_t GetWidth();
    int32_t GetHeight();

private:
    RefPtr<OffscreenCanvasPaintMethod> offscreenPaintMethod_;

    ACE_DISALLOW_COPY_AND_MOVE(OffscreenCanvasPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_OFFSCREEN_CANVAS_PATTERN_H
