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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATA_PANEL_DATA_PANEL_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATA_PANEL_DATA_PANEL_PAINT_METHOD_H
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

struct ArcData {
    Offset center;
    float progress = 0.0f;
    float radius = 0.0f;
    float thickness = 0.0f;
    double maxValue = 0.0;
    Color startColor;
    Color endColor;

    float wholeAngle = 360.0f;
    float startAngle = 0.0f;
};

class ACE_EXPORT DataPanelPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(DataPanelPaintMethod, NodePaintMethod)
public:
    DataPanelPaintMethod() = default;
    ~DataPanelPaintMethod() override = default;

    CanvasDrawFunction GetForegroundDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void Paint(RSCanvas& canvas, PaintWrapper* paintWrapper) const;
    void PaintLinearProgress(RSCanvas& canvas, PaintWrapper* paintWrapper) const;
    void PaintBackground(RSCanvas& canvas, PaintWrapper* paintWrapper, float totalWidth, float height) const;
    void PaintColorSegment(RSCanvas& canvas, PaintWrapper* paintWrapper, float segmentWidth, float xSpace,
        float height, const Color segmentStartColor, const Color segmentEndColor) const;
    void PaintSpace(
        RSCanvas& canvas, PaintWrapper* paintWrapper, float spaceWidth, float xSpace, float height) const;
    void PaintTrackBackground(RSCanvas& canvas, ArcData arcData, const Color color) const;
    void PaintProgress(RSCanvas& canvas, ArcData arcData, bool useEffect = false, bool useAnimator = false,
        float percent = 0.0f) const;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATA_PANEL_DATA_PANEL_PAINT_METHOD_H
