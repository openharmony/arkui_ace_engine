/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef VERTICES_H
#define VERTICES_H

#include <memory>

#include "point.h"
#include "draw/color.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {

enum class VertexMode {
    TRIANGLES_VERTEXMODE = 0,
    TRIANGLESSTRIP_VERTEXMODE,
    TRIANGLEFAN_VERTEXMODE,
    LAST_VERTEXMODE = TRIANGLEFAN_VERTEXMODE,
};

enum BuilderFlags {
    HAS_TEXCOORDS_BUILDER_FLAG = 1 << 0,
    HAS_COLORS_BUILDER_FLAG = 1 << 1,
};

class Vertices {
public:
    Vertices() noexcept = default;
    virtual ~Vertices() {};

    bool MakeCopy(VertexMode mode,
        int vertexCount, const Point positions[], const Point texs[], const ColorQuad colors[],
        int indexCount, const uint16_t indices[]);
    bool MakeCopy(VertexMode mode,
        int vertexCount, const Point positions[], const Point texs[], const ColorQuad colors[]);

    class Builder {
    public:
        Builder(VertexMode mode, int vertexCount, int indexCount, uint32_t flags) {};
        virtual ~Builder() {};

        /**
         * @brief Return if builder is valid.
         */
        bool IsValid();

        /**
         * @brief Return positions data pointer in the builder.
         */
        Point* Positions();

        /**
         * @brief Return indices data pointer in the builder.
         */
        uint16_t* Indices();

        /**
         * @brief Return texture coordinate data pointer in the builder.
         */
        Point* TexCoords();

        /**
         * @brief Return color data pointer in theBuilder.
         */
        ColorQuad* Colors();

        /**
         * @brief Detach the built vertices object. After the first call, this will always return null.
         * @return Return a shared pointer of Vertices object or nullptr.
         */
        std::shared_ptr<Vertices> Detach();
    };
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
