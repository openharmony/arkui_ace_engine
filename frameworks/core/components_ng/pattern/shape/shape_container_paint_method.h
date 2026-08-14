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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_CONTAINER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_CONTAINER_PAINT_METHOD_H

#include "core/components_ng/pattern/shape/shape_container_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/pattern/shape/shape_container_modifier.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ShapeContainerPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ShapeContainerPaintMethod, NodePaintMethod);
public:
    ShapeContainerPaintMethod() = delete;
    ~ShapeContainerPaintMethod() override = default;
    explicit ShapeContainerPaintMethod(const RefPtr<class ShapeContainerModifier>& modifier)
        : shapeContainerModifier_(modifier)
    {}

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(shapeContainerModifier_);
        CHECK_NULL_VOID(paintWrapper);
        auto paintProperty = DynamicCast<ShapeContainerPaintProperty>(paintWrapper->GetPaintProperty());
        CHECK_NULL_VOID(paintProperty);
        auto mesh = paintProperty->GetImageMeshValue(ImageMesh());
        shapeContainerModifier_->SetColumn(mesh.GetColumn());
        shapeContainerModifier_->SetRow(mesh.GetRow());
        const auto& meshVector = mesh.GetMesh();
        auto linearMesh = LinearVector<float>();
        for (const float& value : meshVector) {
            linearMesh.emplace_back(value);
        }
        shapeContainerModifier_->SetMesh(linearMesh);
        auto pixelMapInfo = paintProperty->GetPixelMapInfoValue(ImageSourceInfo());
        shapeContainerModifier_->UpdatePixelMap(pixelMapInfo.GetPixmap());
    }

    RefPtr<Modifier> GetContentModifier(PaintWrapper* /* paintWrapper */) override
    {
        return shapeContainerModifier_;
    }

private:
    RefPtr<ShapeContainerModifier> shapeContainerModifier_;
    ACE_DISALLOW_COPY_AND_MOVE(ShapeContainerPaintMethod);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_CONTAINER_PAINT_METHOD_H
