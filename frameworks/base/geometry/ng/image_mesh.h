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
 
#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_IMAGEMESH_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_IMAGEMESH_H

#include <stdint.h>
#include <vector>

namespace OHOS::Ace::NG {
class ImageMesh final {
public:
    ImageMesh() = default;
    ImageMesh(std::vector<double>& mesh, int32_t column, int32_t row) : mesh_(mesh), column_(column), row_(row) {}
    ~ImageMesh() = default;
    std::vector<double> GetMesh() const
    {
        return mesh_;
    }

    int32_t GetColumn() const
    {
        return column_;
    }

    int32_t GetRow() const
    {
        return row_;
    }

    bool operator==(const ImageMesh& imageMesh) const
    {
        return (mesh_ == imageMesh.mesh_) && (column_ == imageMesh.column_) && (row_ == imageMesh.row_);
    }

    bool operator!=(const ImageMesh& imageMesh) const
    {
        return (mesh_ != imageMesh.mesh_) || (column_ != imageMesh.column_) || (row_ != imageMesh.row_);
    }

    ImageMesh& operator=(const ImageMesh& imageMesh)
    {
        mesh_ = imageMesh.mesh_;
        column_ = imageMesh.column_;
        row_ = imageMesh.row_;
        return *this;
    }

private:
    std::vector<double> mesh_;
    int32_t column_;
    int32_t row_;
};
} // namespace OHOS::Ace::NG
#endif