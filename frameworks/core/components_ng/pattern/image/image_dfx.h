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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_DFX_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_DFX_H
#include <string>
#include "base/image/pixel_map.h"
namespace OHOS::Ace::NG {
    struct ImageDfxConfig {
        int32_t nodeId_ = -1;
        int64_t accessibilityId_ = -1;
        std::string imageSrc_;
        std::string borderRadiusValue_;

        // Used in tracing functions, does not include image source information (sensitive data)
        std::string ToStringWithoutSrc() const
        {
            std::string result = std::string("[")
                                     .append(std::to_string(nodeId_))
                                     .append("-")
                                     .append(std::to_string(accessibilityId_))
                                     .append("]");
            return result;
        }

        // Includes image source, but as the image source may be sensitive, use with caution
        std::string ToStringWithSrc() const
        {
            std::string result = std::string("[")
                                     .append(std::to_string(nodeId_))
                                     .append("-")
                                     .append(std::to_string(accessibilityId_))
                                     .append("]-[")
                                     .append(imageSrc_)
                                     .append("]");
            return result;
        }
    };

    struct RenderedImageInfo {
        // Indicates whether the rendering has been successfully displayed.
        bool renderSuccess = false;
        // PixelMap info
        int32_t width = 0;
        int32_t height = 0;
        int32_t rowStride = 0;
        int32_t rowBytes = 0;
        int32_t byteCount = 0;
        bool isHdr = false;
        AlphaType alphaType = AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
        PixelFormat pixelFormat = PixelFormat::UNKNOWN;
        AllocatorType allocatorType = AllocatorType::DEFAULT;
        std::string pixelMapId;
        std::string srcInfo;

        std::string ToString() const
        {
            if (!renderSuccess) {
                return "RenderedImageInfo: { RenderStatus: NotRender }";
            }
            std::string result;
            result.append("RenderedImageInfo: {")
                .append("RenderStatus: Success")
                .append(", Width: ")
                .append(std::to_string(width))
                .append(", Height: ")
                .append(std::to_string(height))
                .append(", Row Stride: ")
                .append(std::to_string(rowStride))
                .append(", Row Bytes: ")
                .append(std::to_string(rowBytes))
                .append(", Byte Count: ")
                .append(std::to_string(byteCount))
                .append(", Is HDR: ")
                .append(isHdr ? "true" : "false")
                .append(", Alpha Type: ")
                .append(std::to_string(static_cast<int>(alphaType)))
                .append(", Pixel Format: ")
                .append(std::to_string(static_cast<int>(pixelFormat)))
                .append(", Allocator Type: ")
                .append(std::to_string(static_cast<int>(allocatorType)))
                .append(", Pixel Map ID: ")
                .append(pixelMapId)
                .append(" }");
            return result;
        }
    };
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_DFX_H
