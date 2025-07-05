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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RECT_RECT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RECT_RECT_MODEL_H

#include <memory>
#include <mutex>

#include "core/components/common/properties/clip_path.h"
#include "core/components/shape/shape_component.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT RectModel {
public:
    static RectModel* GetInstance();
    virtual ~RectModel() = default;

    virtual void Create();
    virtual void SetRadiusWidth(const Dimension& value);
    virtual void SetRadiusHeight(const Dimension& value);
    virtual void SetRadiusValue(const Dimension& radiusX, const Dimension& radiusY, int32_t index);
    virtual void SetRadiusValue(const Dimension& radiusX, const Dimension& radiusY,
        const RefPtr<ResourceObject>& radiusXResObj, const RefPtr<ResourceObject>& radiusYResObj, int32_t index) {};
    virtual void SetShapeRectRadius(
        const RefPtr<ShapeRect>& shapeRect, const Dimension& radiusX, const Dimension& radiusY, int32_t index);

protected:
    enum RADIUS { TOP_LEFT_RADIUS = 0, TOP_RIGHT_RADIUS = 1, BOTTOM_RIGHT_RADIUS = 2, BOTTOM_LEFT_RADIUS = 3 };
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RECT_RECT_MODEL_H
