/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_ABSTRACT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_ABSTRACT_MODEL_H

#include <memory>
#include <mutex>

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace {
class ShapeAbstractModel {
public:
    static ShapeAbstractModel* GetInstance();
    virtual ~ShapeAbstractModel() = default;
    virtual void SetStroke(const Color& color);
    virtual void SetFill(const Color& color);
    virtual void SetForegroundColor(const Color& color);
    virtual void SetStrokeDashOffset(const Ace::Dimension& dashOffset);
    virtual void SetStrokeLineCap(int lineCapStyle);
    virtual void SetStrokeLineJoin(int lineJoinStyle);
    virtual void SetStrokeMiterLimit(double miterLimit);
    virtual void SetStrokeOpacity(double opacity);
    virtual void SetFillOpacity(double opacity);
    virtual void SetStrokeWidth(const Ace::Dimension& lineWidth);
    virtual void SetStrokeDashArray(const std::vector<Ace::Dimension>& dashArray);
    virtual void SetAntiAlias(bool antiAlias);
    virtual void SetWidth(Dimension& width);
    virtual void SetHeight(Dimension& height);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_ABSTRACT_MODEL_H
