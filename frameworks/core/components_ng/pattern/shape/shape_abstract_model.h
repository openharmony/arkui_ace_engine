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
    virtual void SetStroke(const Color& color) = 0;
    virtual void SetFill(const Color& color) = 0;
    virtual void SetStrokeDashOffset(const Ace::Dimension& dashOffset) = 0;
    virtual void SetStrokeLineCap(int lineCapStyle) = 0;
    virtual void SetStrokeLineJoin(int lineJoinStyle) = 0;
    virtual void SetStrokeMiterLimit(double miterLimit) = 0;
    virtual void SetStrokeOpacity(double opacity) = 0;
    virtual void SetFillOpacity(double opacity) = 0;
    virtual void SetStrokeWidth(const Ace::Dimension& lineWidth) = 0;
    virtual void SetStrokeDashArray(const std::vector<Ace::Dimension>& dashArray) = 0;
    virtual void SetAntiAlias(bool antiAlias) = 0;
    virtual void SetWidth(Dimension& width) = 0;
    virtual void SetHeight(Dimension& height) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_ABSTRACT_MODEL_H
