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

#include "contrast_enhancer_image_ohos.h"

#include "contrast_enhancer_common.h"
#include "contrast_enhancer_image.h"
#include "picture.h"
#include "pixel_map.h"
#include "surface_buffer.h"

#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"

namespace OHOS::Ace {

namespace {

ContrastEnhancerErrorCode ToAceErrorCode(Media::VideoProcessingEngine::VPEAlgoErrCode code)
{
    return code == Media::VideoProcessingEngine::VPE_ALGO_ERR_OK ? ContrastEnhancerErrorCode::OK
                                                                 : ContrastEnhancerErrorCode::ERROR;
}

OHOS::Rect ConvertRect(const ContrastEnhancerRect& rect)
{
    return { rect.x, rect.y, rect.w, rect.h };
}

Media::VideoProcessingEngine::ContrastEnhancerInfo ConvertEnhancerInfo(const ContrastEnhancerInfo& info)
{
    return {
        .pixelmapId = info.pixelmapId,
        .contentId = info.contentId,
        .curRatio = info.curRatio,
        .maxRatio = info.maxRatio,
        .defaultRatio = info.defaultRatio,
        .animationDuration = info.animationDuration,
    };
}

sptr<SurfaceBuffer> PixelMapToSurfaceBuffer(const std::shared_ptr<Media::PixelMap>& pixelMap)
{
    if (!pixelMap) {
        return nullptr;
    }
    auto* fd = pixelMap->GetFd();
    if (fd == nullptr) {
        return nullptr;
    }
    return sptr<SurfaceBuffer>(static_cast<SurfaceBuffer*>(fd));
}

RefPtr<PixelMap> SurfaceBufferToAcePixelMap(sptr<SurfaceBuffer>& surfaceBuffer)
{
    if (!surfaceBuffer) {
        return nullptr;
    }
    auto mediaPixelMap = Media::Picture::SurfaceBuffer2PixelMap(surfaceBuffer);
    if (!mediaPixelMap) {
        return nullptr;
    }
    return PixelMap::Create(std::shared_ptr<Media::PixelMap>(mediaPixelMap.release()));
}

sptr<SurfaceBuffer> CreateOutputSurfaceBuffer(int32_t width, int32_t height, int32_t format, uint32_t strideAlignment)
{
    ACE_SCOPED_TRACE("CreateOutputSurfaceBuffer %dx%d", width, height);
    sptr<SurfaceBuffer> sb = SurfaceBuffer::Create();
    BufferRequestConfig requestConfig = {
        .width = static_cast<uint32_t>(width),
        .height = static_cast<uint32_t>(height),
        .strideAlignment = strideAlignment,
        .format = format,
        .usage = BUFFER_USAGE_CPU_READ | BUFFER_USAGE_CPU_WRITE | BUFFER_USAGE_MEM_DMA | BUFFER_USAGE_HW_RENDER |
                 BUFFER_USAGE_HW_TEXTURE | BUFFER_USAGE_MEM_MMZ_CACHE,
        .timeout = 0,
    };
    GSError ret = sb->Alloc(requestConfig);
    if (ret != GSERROR_OK) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "CreateOutputSurfaceBuffer alloc failed, ret=%{public}d", ret);
        return nullptr;
    }
    return sb;
}

} // namespace

ContrastEnhancerErrorCode ContrastEnhancerImageOhos::SetParameter(const ContrastEnhancerParameters& parameter)
{
    if (!enhancer_) {
        enhancer_ = Media::VideoProcessingEngine::ContrastEnhancerImage::Create();
        if (!enhancer_) {
            TAG_LOGE(AceLogTag::ACE_IMAGE, "SetParameter ContrastEnhancerImage create failed");
            return ContrastEnhancerErrorCode::ERROR;
        }
    }
    Media::VideoProcessingEngine::ContrastEnhancerParameters vpeParam = {
        .uri = parameter.uri,
        .type = static_cast<Media::VideoProcessingEngine::ContrastEnhancerType>(parameter.type),
    };
    if (parameter.type == ContrastEnhancerType::ADAPTIVE_FOV) {
        vpeParam.type = Media::VideoProcessingEngine::ADAPTIVE_FOV;
    } else if (parameter.type == ContrastEnhancerType::ADAPTIVE_FOV2) {
        vpeParam.type = Media::VideoProcessingEngine::ADAPTIVE_FOV2;
    } else {
        vpeParam.type = Media::VideoProcessingEngine::INVALID_CONTRAST_ENHANCER_TYPE;
    }
    auto errCode = enhancer_->SetParameter(vpeParam);
    if (errCode != Media::VideoProcessingEngine::VPE_ALGO_ERR_OK) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "SetParameter failed, err=%{public}d", static_cast<int32_t>(errCode));
        return ToAceErrorCode(errCode);
    }
    return ContrastEnhancerErrorCode::OK;
}

ContrastEnhancerErrorCode ContrastEnhancerImageOhos::ComposeFOVImage(ContrastEnhancerRect displayArea,
    const RefPtr<PixelMap>& oriPixelMap, const RefPtr<PixelMap>& lhdrPixelMap, RefPtr<PixelMap>& outPixelMap,
    const ContrastEnhancerInfo& info)
{
    if (!enhancer_) {
        enhancer_ = Media::VideoProcessingEngine::ContrastEnhancerImage::Create();
        if (!enhancer_) {
            TAG_LOGE(AceLogTag::ACE_IMAGE, "ContrastEnhancerImage create failed");
            return ContrastEnhancerErrorCode::ERROR;
        }
    }
    if (!oriPixelMap || !lhdrPixelMap) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "ComposeFOVImage input pixelMap is null");
        return ContrastEnhancerErrorCode::ERROR;
    }
    auto oriMediaPixelMap = oriPixelMap->GetPixelMapSharedPtr();
    auto lhdrMediaPixelMap = lhdrPixelMap->GetPixelMapSharedPtr();
    if (!oriMediaPixelMap || !lhdrMediaPixelMap) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "ComposeFOVImage media pixelMap is null");
        return ContrastEnhancerErrorCode::ERROR;
    }
    auto oriSb = PixelMapToSurfaceBuffer(oriMediaPixelMap);
    auto lhdrSb = PixelMapToSurfaceBuffer(lhdrMediaPixelMap);
    if (!oriSb || !lhdrSb) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "ComposeFOVImage PixelMapToSurfaceBuffer failed, ori=%{public}d lhdr=%{public}d",
            oriSb != nullptr, lhdrSb != nullptr);
        return ContrastEnhancerErrorCode::ERROR;
    }
    TAG_LOGD(AceLogTag::ACE_IMAGE,
        "ComposeFOVImage area=[%{public}d,%{public}d,%{public}d,%{public}d] oriSz=%{public}dx%{public}d "
        "lhdrSz=%{public}dx%{public}d fmt=%{public}d",
        displayArea.x, displayArea.y, displayArea.w, displayArea.h,
        oriMediaPixelMap->GetWidth(), oriMediaPixelMap->GetHeight(),
        lhdrMediaPixelMap->GetWidth(), lhdrMediaPixelMap->GetHeight(),
        oriSb->GetFormat());
    ACE_SCOPED_TRACE("ComposeFOVImage [%d,%d,%d,%d]", displayArea.x, displayArea.y, displayArea.w, displayArea.h);
    auto outSb = CreateOutputSurfaceBuffer(
        oriMediaPixelMap->GetWidth(), oriMediaPixelMap->GetHeight(), oriSb->GetFormat(), oriSb->GetWidth());
    if (!outSb) {
        return ContrastEnhancerErrorCode::ERROR;
    }
    auto errCode =
        enhancer_->ComposeFOVImage(ConvertRect(displayArea), oriSb, lhdrSb, outSb, ConvertEnhancerInfo(info));
    if (errCode != Media::VideoProcessingEngine::VPE_ALGO_ERR_OK) {
        TAG_LOGE(
            AceLogTag::ACE_IMAGE, "ComposeFOVImage vpe process failed, err=%{public}d", static_cast<int32_t>(errCode));
        return ToAceErrorCode(errCode);
    }
    outPixelMap = SurfaceBufferToAcePixelMap(outSb);
    if (!outPixelMap) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "ComposeFOVImage output to PixelMap failed");
        return ContrastEnhancerErrorCode::ERROR;
    }
    return ContrastEnhancerErrorCode::OK;
}

RefPtr<ContrastEnhancerImage> ContrastEnhancerImage::Create()
{
    return AceType::MakeRefPtr<ContrastEnhancerImageOhos>();
}

} // namespace OHOS::Ace
