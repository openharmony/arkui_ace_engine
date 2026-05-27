/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#include "picture_drawable_descriptor.h"

#include "base/image/pixel_map.h"
#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "core/components_ng/image_provider/image_utils.h"

namespace OHOS::Ace {
PictureDrawableDescriptor::PictureDrawableDescriptor(const RefPtr<Picture>& picture)
    : picture_(picture)
{}

void PictureDrawableDescriptor::SetPicture(const RefPtr<Picture>& picture)
{
    picture_ = picture;
}

void PictureDrawableDescriptor::SetHdrComposition(const HdrCompositionConfig& config)
{
    hdrConfig_ = config;
}

RefPtr<PixelMap> PictureDrawableDescriptor::GetPixelMap()
{
    return cachedPixelMap_;
}

bool PictureDrawableDescriptor::IsHdrConfigValid() const
{
    return hdrConfig_.rect.width > 0 && hdrConfig_.rect.height > 0;
}

RefPtr<PixelMap> PictureDrawableDescriptor::DoComposeFOV()
{
    if (!picture_) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "DoComposeFOV picture is null");
        return nullptr;
    }
    ACE_SCOPED_TRACE("DoComposeFOV");
    auto oriPixelMap = picture_->GetHdrComposedPixelMap(PixelFormat::UNKNOWN);
    auto lhdrPixelMap = picture_->GetAuxPicturePixelMap(AuxiliaryPictureType::LHDR_GAINMAP);
    if (!oriPixelMap || !lhdrPixelMap) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "DoComposeFOV pixelMap is null, ori=%{public}d lhdr=%{public}d",
            oriPixelMap != nullptr, lhdrPixelMap != nullptr);
        return nullptr;
    }
    if (!enhancer_) {
#ifdef VPE_ENABLED
        enhancer_ = ContrastEnhancerImage::Create();
#endif
        if (!enhancer_) {
            TAG_LOGE(AceLogTag::ACE_IMAGE, "DoComposeFOV ContrastEnhancerImage create failed");
            return nullptr;
        }
    }
    ContrastEnhancerParameters param;
    param.type = ContrastEnhancerType::ADAPTIVE_FOV2;
    auto setRet = enhancer_->SetParameter(param);
    if (setRet != ContrastEnhancerErrorCode::OK) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "DoComposeFOV SetParameter failed, ret=%{public}d",
            static_cast<int32_t>(setRet));
        return nullptr;
    }
    ContrastEnhancerRect displayArea = {
        hdrConfig_.rect.x, hdrConfig_.rect.y, hdrConfig_.rect.width, hdrConfig_.rect.height
    };
    ContrastEnhancerInfo info;
    RefPtr<PixelMap> outPixelMap;
    auto ret = enhancer_->ComposeFOVImage(displayArea, oriPixelMap, lhdrPixelMap, outPixelMap, info);
    if (ret != ContrastEnhancerErrorCode::OK) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "DoComposeFOV ComposeFOVImage failed, ret=%{public}d",
            static_cast<int32_t>(ret));
        return nullptr;
    }
    return outPixelMap;
}

DrawableDescriptorLoadResult PictureDrawableDescriptor::LoadSync()
{
    if (!picture_) {
        return { 0, 0, -1 };
    }
    RefPtr<PixelMap> pixelMap;
    if (IsHdrConfigValid()) {
        pixelMap = DoComposeFOV();
    }
    if (!pixelMap) {
        pixelMap = picture_->GetMainPixel();
    }
    if (!pixelMap) {
        return { 0, 0, -1 };
    }
    cachedPixelMap_ = pixelMap;
    return { pixelMap->GetWidth(), pixelMap->GetHeight(), 0 };
}

void PictureDrawableDescriptor::LoadAsync(const LoadCallback&& callback)
{
    NG::ImageUtils::PostToBg(
        [weak = WeakClaim(this), callback = std::move(callback)]() {
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self);
            auto result = self->LoadSync();
            callback(result);
        },
        "PictureDrawableLoadAsync");
}

void PictureDrawableDescriptor::RegisterUpdateCallback(int32_t nodeId, const UpdateCallback&& callback)
{
    updateCallbacks_[nodeId] = std::move(callback);
}

void PictureDrawableDescriptor::UnRegisterUpdateCallback(int32_t nodeId)
{
    updateCallbacks_.erase(nodeId);
}

void PictureDrawableDescriptor::Invalidate()
{
    NG::ImageUtils::PostToBg(
        [weak = WeakClaim(this)]() {
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self);
            self->LoadSync();
            auto pixelMap = self->GetPixelMap();
            if (!pixelMap) {
                return;
            }
            for (auto& [nodeId, callback] : self->updateCallbacks_) {
                if (callback) {
                    callback(pixelMap);
                }
            }
        },
        "PictureDrawableInvalidate");
}
} // namespace OHOS::Ace
