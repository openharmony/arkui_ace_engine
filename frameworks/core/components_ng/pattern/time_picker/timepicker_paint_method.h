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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_PAINT_METHOD_H

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components_ng/render/divider_painter.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/pattern/picker_utils/picker_paint_method_utils.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TimePickerPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(TimePickerPaintMethod, NodePaintMethod);

public:
    TimePickerPaintMethod() = default;
    ~TimePickerPaintMethod() override
    {
        if (circleUtils_) {
            delete circleUtils_;
        }
    }
    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;
    CanvasDrawFunction GetForegroundDrawFunction(PaintWrapper* paintWrapper) override;

    void SetEnabled(bool enabled)
    {
        enabled_ = enabled;
    }

    void SetBackgroundColor(const Color& color)
    {
        backgroundColor_ = color;
    }

private:
    bool enabled_ = true;
    Color backgroundColor_ = Color::WHITE;
    PickerPaintMethodCircleUtils *circleUtils_ = NULL;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_PAINT_METHOD_H
