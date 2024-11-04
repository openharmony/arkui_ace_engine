/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_SHAPE_CONTAINER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_SHAPE_CONTAINER_MODIFIER_H

#include "base/geometry/ng/image_mesh.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/modifier.h"

namespace OHOS::Ace::NG {
class ShapeContainerModifier : public ContentModifier {
    DECLARE_ACE_TYPE(ShapeContainerModifier, ContentModifier);

public:
    ShapeContainerModifier();
    ~ShapeContainerModifier() override = default;

    void onDraw(DrawingContext& context) override;

    void UpdatePixelMap(const RefPtr<PixelMap>& pixelMap);

    void SetRow(int32_t row)
    {
        CHECK_NULL_VOID(row_);
        row_->Set(row);
    }

    void SetColumn(int32_t column)
    {
        CHECK_NULL_VOID(column_);
        column_->Set(column);
    }

    void SetMesh(const LinearVector<float>& mesh)
    {
        CHECK_NULL_VOID(mesh_);
        mesh_->Set(mesh);
    }

private:
    RefPtr<PropertyInt> row_;
    RefPtr<PropertyInt> column_;
    RefPtr<PropertyVectorFloat> mesh_;
    // mark pixelmap is modified
    RefPtr<PropertyBool> flag_;
    RefPtr<PixelMap> pixelMap_;

    ACE_DISALLOW_COPY_AND_MOVE(ShapeContainerModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_SHAPE_CONTAINER_MODIFIER_H
