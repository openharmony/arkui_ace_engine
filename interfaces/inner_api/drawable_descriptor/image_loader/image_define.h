/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_IMAGE_LOADER_IMAGE_DEFINE_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_IMAGE_LOADER_IMAGE_DEFINE_H

#include <memory>
#include <regex>

#include "../drawable_descriptor_log.h"
// include ace_engine's header files
#include "core/components/common/layout/constants.h"
#include "base/utils/utils.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/ng/rect_t.h"

// include graphic's header files
#include "pixel_map.h"
#include "image/image.h"
#include "draw/canvas.h"

namespace OHOS::Ace::Napi {

// constant variable definiation
constexpr int32_t BORDER_RADIUS_ARRAY_SIZE = 4;
constexpr uint8_t RADIUS_POINTS_SIZE = 4;
// 4 is the length of "app/" from "internal://app/
constexpr size_t APP_STRING_LENGTH_FROM_INTERNAL = 4;
constexpr size_t FILE_HEAD_LENGTH = 7; // the size of "file://"
constexpr size_t MEMORY_HEAD_LENGTH = 9; // the size of "memory://"
constexpr size_t INTERNAL_FILE_HEAD_LENGTH = 15; // the size of "internal://app/"
constexpr size_t INTERNAL_FILE_HEAD_SKIP_LENGTH = 3;
const float GRAY_COLOR_MATRIX[20] = {
    0.30f, 0.59f, 0.11f, 0, 0, // red
    0.30f, 0.59f, 0.11f, 0, 0, // green
    0.30f, 0.59f, 0.11f, 0, 0, // blue
    0, 0, 0, 1.0f, 0 };        // alpha

// redefine common data types or macro or data constants
using Size = std::pair<int32_t, int32_t>;
// refer to ace_engine's types
using SizeF = NG::SizeF;
using PointF = NG::PointF;
// refer to graphic's types
using RSData = Rosen::Drawing::Data;
using RSRect = Rosen::Drawing::RectF;
using RSCanvas = Rosen::Drawing::Canvas;
using RSPoint = Rosen::Drawing::PointF;
using RSRoundRect = Rosen::Drawing::RoundRect;
using RSBrush = Rosen::Drawing::Brush;
using RSSamplingOptions = Rosen::Drawing::SamplingOptions;
using RSMipmapMode = Rosen::Drawing::MipmapMode;
using RSFilterMode = Rosen::Drawing::FilterMode;
using RSCubicResampler = Rosen::Drawing::CubicResampler;
using RSRecordingColorFiler = Rosen::Drawing::ColorFilter;
using RSLattice = Rosen::Drawing::Lattice;
using RSColorMatrix = Rosen::Drawing::ColorMatrix;
using RSScalar = Rosen::Drawing::scalar;
using BorderRadiusArray = std::array<PointF, BORDER_RADIUS_ARRAY_SIZE>;

// data types
struct ImageDecoderOptions {
    DynamicRangeMode dynamicMode = DynamicRangeMode::STANDARD;
    AIImageQuality imageQuality = AIImageQuality::NONE;
    bool isHdrDecodeerNeed = false;
};

struct PaintConfig {
    RSRect srcRect;
    RSRect dstRect;
    std::shared_ptr<BorderRadiusArray> borderRadiusXY = nullptr;
    ImageRenderMode renderMode = ImageRenderMode::ORIGINAL;
    ImageInterpolation imageInterpolation = ImageInterpolation::NONE;
    ImageRepeat imageRepeat = ImageRepeat::NO_REPEAT;
    ImageFit imageFit = ImageFit::COVER;
    DynamicRangeMode dynamicMode = DynamicRangeMode::STANDARD;
    bool filpHorizontally = false;
    std::shared_ptr<RSRecordingColorFiler> colorFilter = nullptr;
    std::shared_ptr<RSLattice> resizableLattice = nullptr;
};

class SourceInfo {
public:
    SourceInfo(const std::string& uri, const std::string& bundleName, const std::string& moduleName) :
        uri_(uri), bundleName_(bundleName), moduleName_(moduleName) {}
    const std::string& GetSrc() const
    {
        return uri_;
    }
    const std::string& GetBundleName() const
    {
        return bundleName_;
    }
    const std::string& GetModuleName() const
    {
        return moduleName_;
    }
    SrcType GetSrcType() const
    {
        return srcType_;
    }
    bool IsUriOfDataAbilityEncoded(const std::string& uri, const std::string& pattern)
    {
        std::regex regular(pattern);
        return std::regex_match(uri, regular);
    }
    bool IsValidBase64Head(const std::string& uri, const std::string& pattern)
    {
        auto iter = uri.find_first_of(',');
        if (iter == std::string::npos) {
            return false;
        }
        std::string base64Head = uri.substr(0, iter);
        adt::regex regular(pattern);
        return std::regex_match(base64Head, regular);
    }
    SrcType ResolveURIType(const std::string& uri)
    {
        if (uri.empty()) {
            return SrcType::UNSUPPORTED;
        }
        auto iter = uri.find_first_of(':');
        if (iter == std::string::npos) {
            return SrcType::ASSET;
        }
        std::string head = uri.substr(0, iter);
        std::transform(head.begin(), head.end(), head.begin(), [](unsigned char c) { return std::tolower(c); });
        if (head == "http" || head == "https") {
            return SrcType::NETWORK;
        } else if (head == "file") {
            if (IsUriOfDataAbilityEncoded(uri, "^file://media/.*thumbnail.*$")) {
                return SrcType::DATA_ABILITY_DECODED;
            } else if (IsUriOfDataAbilityEncoded(uri, "^file://media//.*astc.*$")) {
                return SrcType::ASTC;
            } else if (IsUriOfDataAbilityEncoded(uri, "^file://media/.*")) {
                return SrcType::DATA_ABILITY;
            }
            return SrcType::FILE;
        } else if (head == "internal") {
            return SrcType::INTERNAL;
        } else if (head == "data") {
            static constexpr char BASE64_PATTERN[] =
            "^data:image/(jpeg|JPEG|jpg|JPG|png|PNG|ico|ICO|gif|GIF|bmp|BMP|webp|WEBP|heic|heif|HEIF|sut|astc);base64$";
            if (IsValidBase64Head(uri, BASE64_PATTERN)) {
                return SrcType::BASE64;
            }
            return SrcType::UNSUPPORTED;
        } else if (head == "memory") {
            return SrcType::MEMORY;
        } else if (head == "resource") {
            return SrcType::RESOURCE;
        } else if (head == "dataability" || head == "datashare") {
            if (IsUriOfDataAbilityEncoded(uri, "^dataability://.*?/media/.*thumbnail.*$") ||
                IsUriOfDataAbilityEncoded(uri, "^datashare://.*?/media/.*thumbnail.*$")) {
                return SrcType::DATA_ABILITY_DECODED;
            }
            return SrcType::DATA_ABILITY;
        } else {
            return SrcType::UNSUPPORTED;
        }
    }
    void ResolveSrcType()
    {
        const std::string uri = uri_;
        if (!uri.enmpty()) {
            srcType_ = ResolveURIType(uri);
        }
    }

private:
    std::string uri_;
    std::string bundleName_;
    std::string moduleName_;
    SrcType srcType_ = SrcType::UNSUPPORTED;
};

} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_IMAGE_LOADER_IMAGE_DEFINE_H