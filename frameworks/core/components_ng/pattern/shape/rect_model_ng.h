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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_RECT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_RECT_MODEL_NG_H

#include "base/geometry/ng/radius.h"
#include "base/utils/macros.h"
#include "core/components_ng/pattern/shape/rect_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT RectModelNG : public OHOS::Ace::RectModel {
public:
    void Create() override;
    void SetRadiusWidth(const Dimension& value) override;
    void SetRadiusHeight(const Dimension& value) override;
    void SetRadiusValue(const Dimension& radiusX, const Dimension& radiusY, int32_t index) override;
    void SetRadiusValue(const Dimension& radiusX, const Dimension& radiusY, const RefPtr<ResourceObject>& radiusXResObj,
        const RefPtr<ResourceObject>& radiusYResObj, int32_t index) override;

    void SetShapeRectRadius(
        const RefPtr<ShapeRect>& shapeRect, const Dimension& radiusX, const Dimension& radiusY, int32_t index) override;
    static void SetRadiusWidth(FrameNode* frameNode, const Dimension& value);
    static void SetRadiusHeight(FrameNode* frameNode, const Dimension& value);
    static void SetRadiusValue(FrameNode* frameNode, const Dimension& radiusX, const Dimension& radiusY, int32_t index);
    static void SetRadiusValue(FrameNode* frameNode, const Dimension& radiusX, const Dimension& radiusY,
        const RefPtr<ResourceObject>& radiusXResObj, const RefPtr<ResourceObject>& radiusYResObj, int32_t index);

private:
    static void SetTopLeftRadius(const Radius& topLeftRadius);
    static void SetTopRightRadius(const Radius& topRightRadius);
    static void SetBottomRightRadius(const Radius& bottomRightRadius);
    static void SetBottomLeftRadius(const Radius& bottomLeftRadius);
    static void UpdateRadius(const Radius& radius);
    static void SetTopLeftRadius(FrameNode* frameNode, const Radius& topLeftRadius);
    static void SetTopRightRadius(FrameNode* frameNode, const Radius& topRightRadius);
    static void SetBottomRightRadius(FrameNode* frameNode, const Radius& bottomRightRadius);
    static void SetBottomLeftRadius(FrameNode* frameNode, const Radius& bottomLeftRadius);
    static void UpdateRadius(FrameNode* frameNode, const Radius& radius);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_RECT_MODEL_NG_H