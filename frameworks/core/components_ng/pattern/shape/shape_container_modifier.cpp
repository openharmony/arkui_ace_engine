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

#include "core/components_ng/pattern/shape/shape_container_modifier.h"

#include "base/geometry/ng/image_mesh.h"
#include "base/utils/utils.h"
#include "core/components_ng/render/adapter/rosen/drawing_painter.h"
namespace OHOS::Ace::NG {
namespace {
std::tuple<bool, int32_t, int32_t> CheckNeedMesh(const RefPtr<PropertyInt>& propertyRow,
    const RefPtr<PropertyInt>& propertyColumn, const RefPtr<PropertyVectorFloat>& propertyMesh)
{
    std::tuple<bool, int32_t, int32_t> noMeshRet = { false, 1, 1 };
    CHECK_NULL_RETURN(propertyRow, noMeshRet);
    CHECK_NULL_RETURN(propertyColumn, noMeshRet);
    CHECK_NULL_RETURN(propertyMesh, noMeshRet);
    auto row = propertyRow->Get();
    auto column = propertyColumn->Get();
    auto verticesSize = propertyMesh->Get().size();
    int64_t tempVerticesSize = (static_cast<int64_t>(column) + 1) * (row + 1) * 2;
    if (tempVerticesSize != verticesSize) {
        return noMeshRet;
    }
    return { true, row, column };
}
} // namespace

ShapeContainerModifier::ShapeContainerModifier()
{
    row_ = AceType::MakeRefPtr<PropertyInt>(0);
    column_ = AceType::MakeRefPtr<PropertyInt>(0);
    mesh_ = AceType::MakeRefPtr<PropertyVectorFloat>(LinearVector<float>(0));
    flag_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(row_);
    AttachProperty(column_);
    AttachProperty(mesh_);
    AttachProperty(flag_);
}

void ShapeContainerModifier::UpdatePixelMap(const RefPtr<PixelMap>& pixelMap)
{
    if (((!pixelMap_) != (!pixelMap)) || (pixelMap_ && pixelMap && pixelMap_->GetPixels() != pixelMap->GetPixels())) {
        CHECK_NULL_VOID(flag_);
        flag_->Set(!flag_->Get());
    }
    pixelMap_ = pixelMap;
}

void ShapeContainerModifier::onDraw(DrawingContext& context)
{
    CHECK_NULL_VOID(pixelMap_);
    RSCanvas& canvas = context.canvas;
    RSBrush brush;
    canvas.AttachBrush(brush);
    const auto& [needMesh, row, column] = CheckNeedMesh(row_, column_, mesh_);
    std::vector<float> mesh;
    if (mesh_ && needMesh) {
        mesh = mesh_->Get();
    } else {
        const float height = static_cast<float>(pixelMap_->GetHeight());
        const float width = static_cast<float>(pixelMap_->GetWidth());
        mesh = { 0, 0, width, 0, 0, height, width, height };
    }
    DrawingPainter::DrawPixelMapMesh(canvas, row, column, mesh, pixelMap_);
    canvas.DetachBrush();
}
} // namespace OHOS::Ace::NG
