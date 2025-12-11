/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CONTAINER_PICKER_CONTAINER_PICKER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CONTAINER_PICKER_CONTAINER_PICKER_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_utils.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_method.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
struct PickerDividerPaintInfo {
    float strokeWidth = 0.0f;
    float dividerLength = 0.0f;
    Color dividerColor = Color::TRANSPARENT;
};

class ContainerPickerPaintMethod : public ScrollablePaintMethod {
    DECLARE_ACE_TYPE(ContainerPickerPaintMethod, ScrollablePaintMethod);

public:
    ContainerPickerPaintMethod() = default;
    ~ContainerPickerPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;
    CanvasDrawFunction GetForegroundDrawFunction(PaintWrapper* paintWrapper) override;

    void SetSafeAreaPadding(PaddingPropertyF& value)
    {
        safeAreaPadding_ = value;
    }

private:
    void ClipPadding(PaintWrapper* paintWrapper, RSCanvas& canvas) const;
    void PaintSelectionIndicatorBackground(PaintWrapper* paintWrapper, RSCanvas& canvas) const;
    void PaintSelectionIndicatorDivider(PaintWrapper* paintWrapper, RSCanvas& canvas) const;

    void ParseDividerMargin(PaintWrapper* paintWrapper, float& length, double& startMargin, double& endMargin) const;
    void SetDefaultIndicatorBackground(
        RefPtr<FrameNode> pickerNode, Color& backgroundColor, BorderRadiusProperty& borderRadius) const;
    void SetDefaultIndicatorDivider(RefPtr<FrameNode> pickerNode, double& strokeWidth, Color& dividerColor,
        double& startMargin, double& endMargin) const;
    void PaintLine(const OffsetF& offset, const PickerDividerPaintInfo& dividerInfo, RSCanvas& canvas) const;
    Dimension ParseRadius(std::optional<Dimension> actualRadius, float maxRadius) const;

    PaddingPropertyF safeAreaPadding_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CONTAINER_PICKER_CONTAINER_PICKER_PAINT_METHOD_H
