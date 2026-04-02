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

} // namespace OHOS::Ace::NG