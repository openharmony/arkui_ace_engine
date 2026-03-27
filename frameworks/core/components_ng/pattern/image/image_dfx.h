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
struct ImageNodeId {
    ImageNodeId(int32_t nodeId, int64_t accessibilityId, uint64_t canvasNodeId)
        : nodeId_(nodeId), accessibilityId_(accessibilityId), canvasNodeId_(canvasNodeId)
    {}
    ImageNodeId() = default;
    int32_t nodeId_ = -1;
    int64_t accessibilityId_ = -1;
    uint64_t canvasNodeId_ = -1;
};
class ImageDfxConfig {
public:
    ImageDfxConfig(
        const ImageNodeId& nodeInfo, int32_t srcType, std::string imageSrc, bool isTrimMemRecycle = false)
        : nodeInfo_(nodeInfo), srcType_(srcType), imageSrc_(imageSrc), isTrimMemRecycle_(isTrimMemRecycle)
    {
        InitToStringWithoutSrc();
        InitToStringWithSrc();
    }
    ImageDfxConfig() = default;
    // Used in tracing functions, does not include image source information (sensitive data)
    std::string ToStringWithoutSrc() const
    {
        return withoutSrcInfo_;
    }

    // Includes image source, but as the image source may be sensitive, use with caution
    std::string ToStringWithSrc() const
    {
        return withSrcInfo_;
    }

    bool GetIsTrimMemRecycle() const
    {
        return isTrimMemRecycle_;
    }

    void SetAutoResize(bool autoResize)
    {
        autoResize_ = autoResize;
    }

    bool GetAutoResize() const
    {
        return autoResize_;
    }

    int32_t GetNodeId() const
    {
        return nodeInfo_.nodeId_;
    }

    int64_t GetAccessibilityId() const
    {
        return nodeInfo_.accessibilityId_;
    }

    std::string GetImageSrc() const
    {
        return imageSrc_;
    }

    void SetFrameSize(float width, float height)
    {
        frameSizeWidth_ = width;
        frameSizeHeight_ = height;
    }

    float GetFrameSizeWidth() const
    {
        return frameSizeWidth_;
    }

    float GetFrameSizeHeight() const
    {
        return frameSizeHeight_;
    }

    int32_t GetSrcType() const
    {
        return srcType_;
    }

private:
    ImageNodeId nodeInfo_ = ImageNodeId();
    int32_t srcType_ = -1;
    std::string imageSrc_;
    bool isTrimMemRecycle_ = false;
    std::string withoutSrcInfo_ = "";
    std::string withSrcInfo_ = "";
    float frameSizeWidth_ = 0.0f;
    float frameSizeHeight_ = 0.0f;
    bool autoResize_ = false;

    void InitToStringWithoutSrc();
    void InitToStringWithSrc();
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
    std::string dstRectInfo;

    std::string ToString() const;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_DFX_H
