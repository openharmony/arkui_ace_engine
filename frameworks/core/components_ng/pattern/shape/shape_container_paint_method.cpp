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

#include "core/components_ng/pattern/shape/shape_container_paint_method.h"

namespace OHOS::Ace::NG {

void ShapeContainerPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
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

RefPtr<Modifier> ShapeContainerPaintMethod::GetContentModifier(PaintWrapper* /* paintWrapper */)
{
    return shapeContainerModifier_;
}
} // namespace OHOS::Ace::NG
