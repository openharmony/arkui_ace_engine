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

#include "core/components_ng/pattern/shape/shape_paint_property.h"

namespace OHOS::Ace::NG {

void ShapePaintProperty::UpdateShapeProperty(const RefPtr<ShapePaintProperty>& target)
{
    CHECK_NULL_VOID(target);
    if (!HasAntiAlias() && target->HasAntiAlias()) {
        UpdateAntiAlias(target->GetAntiAliasValue());
    }
    if (!HasFill() && target->HasFill()) {
        UpdateFill(target->GetFillValue());
    }
    if (!HasFillOpacity() && target->HasFillOpacity()) {
        UpdateFillOpacity(target->GetFillOpacityValue());
    }
    if (!HasStroke() && target->HasStroke()) {
        UpdateStroke(target->GetStrokeValue());
    }
    if (!HasStrokeDashArray() && target->HasStrokeDashArray()) {
        UpdateStrokeDashArray(target->GetStrokeDashArrayValue());
    }
    if (!HasStrokeDashOffset() && target->HasStrokeDashOffset()) {
        UpdateStrokeDashOffset(target->GetStrokeDashOffsetValue());
    }
    if (!HasStrokeLineCap() && target->HasStrokeLineCap()) {
        UpdateStrokeLineCap(target->GetStrokeLineCapValue());
    }
    if (!HasStrokeLineJoin() && target->HasStrokeLineJoin()) {
        UpdateStrokeLineJoin(target->GetStrokeLineJoinValue());
    }
    if (!HasStrokeMiterLimit() && target->HasStrokeMiterLimit()) {
        UpdateStrokeMiterLimit(target->GetStrokeMiterLimitValue());
    }
    if (!HasStrokeOpacity() && target->HasStrokeOpacity()) {
        UpdateStrokeOpacity(target->GetStrokeOpacityValue());
    }
    if (!HasStrokeWidth() && target->HasStrokeWidth()) {
        UpdateStrokeWidth(target->GetStrokeWidthValue());
    }
}

} // namespace OHOS::Ace::NG
