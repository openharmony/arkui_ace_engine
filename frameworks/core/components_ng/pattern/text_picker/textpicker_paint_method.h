/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_PAINT_METHOD_H

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_properties.h"
#include "core/components_ng/render/node_paint_method.h"
namespace OHOS::Ace::NG {

class ACE_EXPORT TextPickerPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(TextPickerPaintMethod, NodePaintMethod)
public:
    TextPickerPaintMethod() = default;
    ~TextPickerPaintMethod() override = default;

    TextPickerPaintMethod(const WeakPtr<Pattern>& pattern)
    {
        pattern_ = pattern;
    }

    double GetDefaultPickerItemHeight() const
    {
        return defaultPickerItemHeight_;
    }

    void SetDefaultPickerItemHeight(double defaultPickerItemHeight)
    {
        defaultPickerItemHeight_ = defaultPickerItemHeight;
    }

    void SetEnabled(bool enabled)
    {
        enabled_ = enabled;
    }

    CanvasDrawFunction GetForegroundDrawFunction(PaintWrapper* paintWrapper) override;
    void PaintDividerLines(RSCanvas& canvas, const RectF& contentRect, const DividerInfo &info,
        bool isDefaultLine = true);

private:
    double defaultPickerItemHeight_ = 0.0;
    bool enabled_ = true;

    WeakPtr<Pattern> pattern_;

    bool NeedPaintDividerLines(const RectF &contentRect, const ItemDivider &divider, double dividerHeight,
        DividerInfo& info);
    void PaintDefaultDividerLines(RSCanvas& canvas, const RectF &contentRect, double dividerHeight);
    void PaintCustomDividerLines(RSCanvas& canvas, const RectF &contentRect, const RectF &frameRect,
        const ItemDivider &divider, double dividerHeight);
    void PaintLine(const OffsetF& offset, const DividerInfo &info, RSCanvas& canvas);
    bool SetStrokeWidth(const ItemDivider &divider, double dividerHeight, DividerInfo& info);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_PAINT_METHOD_H
