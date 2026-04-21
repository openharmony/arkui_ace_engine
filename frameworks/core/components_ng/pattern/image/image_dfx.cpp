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

#include "core/components_ng/pattern/image/image_dfx.h"

namespace OHOS::Ace::NG {

ImageDfxConfig::ImageDfxConfig(
    const ImageNodeId& nodeInfo, int32_t srcType, std::string imageSrc, bool isTrimMemRecycle)
    : nodeInfo_(nodeInfo), srcType_(srcType), imageSrc_(std::move(imageSrc)), isTrimMemRecycle_(isTrimMemRecycle)
{
    InitToStringWithoutSrc();
    InitToStringWithSrc();
}

void ImageDfxConfig::InitToStringWithoutSrc()
{
    withoutSrcInfo_ = std::string("[")
                          .append(std::to_string(nodeInfo_.nodeId_))
                          .append("-")
                          .append(std::to_string(nodeInfo_.accessibilityId_))
                          .append("-")
                          .append(std::to_string(nodeInfo_.canvasNodeId_))
                          .append("-")
                          .append(std::to_string(srcType_))
                          .append("]");
}

void ImageDfxConfig::InitToStringWithSrc()
{
    withSrcInfo_ = std::string("[")
                       .append(std::to_string(nodeInfo_.nodeId_))
                       .append("-")
                       .append(std::to_string(nodeInfo_.accessibilityId_))
                       .append("-")
                       .append(std::to_string(nodeInfo_.canvasNodeId_))
                       .append("-")
                       .append(std::to_string(srcType_))
                       .append("]-[")
                       .append(imageSrc_)
                       .append("]");
}

std::string RenderedImageInfo::ToString() const
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
        .append(", Dst Rect: ")
        .append(dstRectInfo)
        .append(" }");
    return result;
}

std::string ImageDfxConfig::ToStringWithoutSrc() const
{
    return withoutSrcInfo_;
}

std::string ImageDfxConfig::ToStringWithSrc() const
{
    return withSrcInfo_;
}

bool ImageDfxConfig::GetIsTrimMemRecycle() const
{
    return isTrimMemRecycle_;
}

void ImageDfxConfig::SetAutoResize(bool autoResize)
{
    autoResize_ = autoResize;
}

bool ImageDfxConfig::GetAutoResize() const
{
    return autoResize_;
}

int32_t ImageDfxConfig::GetNodeId() const
{
    return nodeInfo_.nodeId_;
}

int64_t ImageDfxConfig::GetAccessibilityId() const
{
    return nodeInfo_.accessibilityId_;
}

std::string ImageDfxConfig::GetImageSrc() const
{
    return imageSrc_;
}

void ImageDfxConfig::SetFrameSize(float width, float height)
{
    frameSizeWidth_ = width;
    frameSizeHeight_ = height;
}

float ImageDfxConfig::GetFrameSizeWidth() const
{
    return frameSizeWidth_;
}

float ImageDfxConfig::GetFrameSizeHeight() const
{
    return frameSizeHeight_;
}

int32_t ImageDfxConfig::GetSrcType() const
{
    return srcType_;
}

} // namespace OHOS::Ace::NG