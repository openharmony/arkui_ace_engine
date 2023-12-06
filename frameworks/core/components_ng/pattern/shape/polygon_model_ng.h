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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_POLYGON_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_POLYGON_MODEL_NG_H

#include "base/utils/macros.h"
#include "core/components_ng/pattern/shape/polygon_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT PolygonModelNG : public OHOS::Ace::PolygonModel {
public:
    void Create(bool isPolygon) override;
    void SetPoints(const ShapePoints& points) override;

    static void SetPoints(FrameNode* frameNode, const ShapePoints& points);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_POLYGON_MODEL_NG_H