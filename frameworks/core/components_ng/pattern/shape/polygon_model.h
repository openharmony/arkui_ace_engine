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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_POLYGON_POLYGON_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_POLYGON_POLYGON_MODEL_H

#include <memory>
#include <mutex>

#include "core/components/shape/shape_component.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT PolygonModel {
public:
    static PolygonModel* GetInstance();
    virtual ~PolygonModel() = default;

    virtual void Create(bool isPolygon);
    virtual void SetPoints(const ShapePoints& points);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_POLYGON_POLYGON_MODEL_H
