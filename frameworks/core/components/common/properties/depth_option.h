/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DEPTH_OPTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DEPTH_OPTION_H

#include <optional>
#include <string>

#include "base/geometry/ng/vector.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/position_param.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace {

struct ACE_EXPORT DepthVector3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    bool operator==(const DepthVector3& other) const
    {
        return NearEqual(x, other.x) && NearEqual(y, other.y) && NearEqual(z, other.z);
    }

    bool operator!=(const DepthVector3& other) const
    {
        return !(*this == other);
    }
};

struct ACE_EXPORT DepthVector4 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;

    bool operator==(const DepthVector4& other) const
    {
        return NearEqual(x, other.x) && NearEqual(y, other.y) && NearEqual(z, other.z) &&
               NearEqual(w, other.w);
    }

    bool operator!=(const DepthVector4& other) const
    {
        return !(*this == other);
    }
};

struct ACE_EXPORT DepthColorRGB {
    int32_t red = 0;
    int32_t green = 0;
    int32_t blue = 0;

    bool operator==(const DepthColorRGB& other) const
    {
        return red == other.red && green == other.green && blue == other.blue;
    }

    bool operator!=(const DepthColorRGB& other) const
    {
        return !(*this == other);
    }
};

struct ACE_EXPORT DepthPosition {
    DepthVector3 leftTop;
    DepthVector3 rightTop;
    DepthVector3 leftBottom;
    DepthVector3 rightBottom;

    bool operator==(const DepthPosition& other) const
    {
        return leftTop == other.leftTop && rightTop == other.rightTop &&
               leftBottom == other.leftBottom && rightBottom == other.rightBottom;
    }

    bool operator!=(const DepthPosition& other) const
    {
        return !(*this == other);
    }
};

struct ACE_EXPORT SpatialEffectParams {
    std::optional<DepthPosition> position;
    float occlusionWeight = 0.0f;

    bool operator==(const SpatialEffectParams& other) const
    {
        return position == other.position && NearEqual(occlusionWeight, other.occlusionWeight);
    }

    bool operator!=(const SpatialEffectParams& other) const
    {
        return !(*this == other);
    }

    void ResetValue()
    {
        position.reset();
        occlusionWeight = 0.0f;
    }
};

struct ACE_EXPORT DepthBackgroundSource {
    enum class Type {
        NONE = 0,
        IMAGE,
        GLTF,
    };

    Type type = Type::NONE;
    ImageSourceInfo imageSourceInfo;
    std::string resolvedPath;
    std::string src;
    std::string bundleName;
    std::string moduleName;

    bool operator==(const DepthBackgroundSource& other) const
    {
        return type == other.type && imageSourceInfo == other.imageSourceInfo && resolvedPath == other.resolvedPath &&
               src == other.src && bundleName == other.bundleName && moduleName == other.moduleName;
    }

    bool operator!=(const DepthBackgroundSource& other) const
    {
        return !(*this == other);
    }

    bool IsValid() const
    {
        if (type == Type::IMAGE) {
            return imageSourceInfo.IsValid();
        }
        if (type == Type::GLTF) {
            return !resolvedPath.empty();
        }
        return false;
    }

    bool IsImage() const
    {
        return type == Type::IMAGE && imageSourceInfo.IsValid();
    }

    bool IsGltf() const
    {
        return type == Type::GLTF && !resolvedPath.empty();
    }

    static DepthBackgroundSource CreateImage(
        const ImageSourceInfo& sourceInfo, const std::string& rawSrc = {}, const std::string& bundle = {},
        const std::string& module = {})
    {
        DepthBackgroundSource source;
        source.type = Type::IMAGE;
        source.imageSourceInfo = sourceInfo;
        source.src = rawSrc;
        source.bundleName = bundle;
        source.moduleName = module;
        return source;
    }

    static DepthBackgroundSource CreateGltf(const std::string& path, const std::string& rawSrc = {},
        const std::string& bundle = {}, const std::string& module = {})
    {
        DepthBackgroundSource source;
        source.type = Type::GLTF;
        source.resolvedPath = path;
        source.src = rawSrc;
        source.bundleName = bundle;
        source.moduleName = module;
        return source;
    }
};

struct ACE_EXPORT DepthBackgroundOffset {
    std::optional<NG::OffsetT<Dimension>> offset;
    std::optional<EdgesParam> offsetEdges;
    bool useLocalizedOffset = false;

    bool operator==(const DepthBackgroundOffset& other) const
    {
        return offset == other.offset && offsetEdges == other.offsetEdges &&
               useLocalizedOffset == other.useLocalizedOffset;
    }

    bool operator!=(const DepthBackgroundOffset& other) const
    {
        return !(*this == other);
    }
};

enum class ACE_EXPORT DepthSpaceType {
    INSTANCE = 0,
    GLOBAL = 1,
};

struct ACE_EXPORT DepthCameraParams {
    DepthVector3 position;
    DepthVector4 quaternion;
    float yFov = 0.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;

    bool operator==(const DepthCameraParams& other) const
    {
        return position == other.position && quaternion == other.quaternion &&
               NearEqual(yFov, other.yFov) && NearEqual(zNear, other.zNear) && NearEqual(zFar, other.zFar);
    }

    bool operator!=(const DepthCameraParams& other) const
    {
        return !(*this == other);
    }
};

struct ACE_EXPORT DepthLightParams {
    DepthVector3 direction;
    DepthColorRGB color;
    float intensity = 1.0f;

    bool operator==(const DepthLightParams& other) const
    {
        return direction == other.direction && color == other.color &&
               NearEqual(intensity, other.intensity);
    }

    bool operator!=(const DepthLightParams& other) const
    {
        return !(*this == other);
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DEPTH_OPTION_H
