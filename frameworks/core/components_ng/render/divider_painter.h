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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DIVIDER_PAINTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DIVIDER_PAINTER_H

#include "core/components_ng/render/canvas.h"

namespace OHOS::Ace::NG {
class DividerPainter {
public:
    DividerPainter(double constrainStrokeWidth, double dividerLength, bool vertical,
        std::optional<Color> dividerColor, std::optional<LineCap> lineCap)
        : constrainStrokeWidth_(constrainStrokeWidth), dividerLength_(dividerLength), vertical_(vertical),
        dividerColor_(dividerColor), lineCap_(lineCap)
    {}
    DividerPainter(double constrainStrokeWidth, double dividerLength, bool vertical)
        : constrainStrokeWidth_(constrainStrokeWidth), dividerLength_(dividerLength), vertical_(vertical),
        dividerColor_(std::nullopt), lineCap_(LineCap::SQUARE)
    {}
    DividerPainter(double constrainStrokeWidth, double dividerLength)
        : constrainStrokeWidth_(constrainStrokeWidth), dividerLength_(dividerLength), vertical_(false),
        dividerColor_(std::nullopt), lineCap_(LineCap::SQUARE)
    {}
    ~DividerPainter() = default;

    void DrawLine(const RefPtr<Canvas>& canvas, const OffsetF& offset) const;

private:
    double constrainStrokeWidth_;
    double dividerLength_;
    bool vertical_;

    std::optional<Color> dividerColor_;
    std::optional<LineCap> lineCap_;
};
}
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DIVIDER_PAINTER_H