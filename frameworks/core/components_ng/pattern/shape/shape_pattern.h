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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_PATTERN_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/shape_overlay_modifier.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"

namespace OHOS::Ace::NG {
class ShapeLayoutAlgorithm;

class ShapePattern : public Pattern {
    DECLARE_ACE_TYPE(ShapePattern, Pattern);

public:
    ShapePattern() = default;
    ~ShapePattern() override;

    bool IsEnableMatchParent() override
    {
        return true;
    }

    bool IsEnableFix() override
    {
        return true;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    RefPtr<PaintProperty> CreatePaintProperty() override;
    void OnModifyDone() override;

protected:
    RefPtr<ShapePaintProperty> GetAncestorPaintProperty();
    void OnForegroundColorUpdate() override;
    void UpdateForeground(RefPtr<FrameNode> parentFrameNode, RefPtr<FrameNode> childFrameNode);

    RefPtr<ShapeOverlayModifier> shapeOverlayModifier_;

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    ACE_DISALLOW_COPY_AND_MOVE(ShapePattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_PATTERN_H
