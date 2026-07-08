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

#include <vector>

#include "base/image/pixel_map.h"
#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "core/components_ng/image_provider/image_utils.h"

namespace OHOS::Ace {
namespace {
// Serialize FOV composition because the VPE contrast enhancer backend uses
// shared native resources and is not assumed to be safe for concurrent calls.
std::mutex g_vpeMutex;
} // namespace

PictureDrawableDescriptor::PictureDrawableDescriptor(const RefPtr<Picture>& picture)
    : picture_(picture)
{}

void PictureDrawableDescriptor::SetPicture(const RefPtr<Picture>& picture)
{
    std::scoped_lock<std::mutex> lock(stateMutex_);
    picture_ = picture;
}

void PictureDrawableDescriptor::SetHdrComposition(const HdrCompositionConfig& config)
{
    std::scoped_lock<std::mutex> lock(stateMutex_);
    hdrConfig_ = config;
}

RefPtr<PixelMap> PictureDrawableDescriptor::GetPixelMap()
{
    std::scoped_lock<std::mutex> lock(stateMutex_);
    return cachedPixelMap_;
}

bool PictureDrawableDescriptor::IsHdrConfigValid() const
{
    std::scoped_lock<std::mutex> lock(stateMutex_);
    return IsHdrConfigValid(hdrConfig_);
}

bool PictureDrawableDescriptor::IsHdrConfigValid(const HdrCompositionConfig& config)
{
    return config.rect.width > 0 && config.rect.height > 0;
}

PictureDrawableDescriptor::LoadSnapshot PictureDrawableDescriptor::CreateLoadSnapshot() const
{
    std::scoped_lock<std::mutex> lock(stateMutex_);
    return CreateLoadSnapshotLocked();
}

PictureDrawableDescriptor::LoadSnapshot PictureDrawableDescriptor::CreateLoadSnapshotLocked() const
{
    return { picture_, hdrConfig_ };
}

RefPtr<PixelMap> PictureDrawableDescriptor::DoComposeFOV(const LoadSnapshot& snapshot)
{
    if (!snapshot.picture) {
        return nullptr;
    }
    ACE_SCOPED_TRACE("DoComposeFOV");
    auto oriPixelMap = snapshot.picture->GetMainPixel();
    if (!oriPixelMap) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "DoComposeFOV picture is null");
        return nullptr;
    }
    if (!oriPixelMap->IsHdr()) {
        oriPixelMap = snapshot.picture->GetHdrComposedPixelMap(PixelFormat::UNKNOWN);
    }
    auto lhdrPixelMap = snapshot.picture->GetAuxPicturePixelMap(AuxiliaryPictureType::LHDR_GAINMAP);
    if (!oriPixelMap || !lhdrPixelMap) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "DoComposeFOV pixelMap is null, ori=%{public}d lhdr=%{public}d",
            oriPixelMap != nullptr, lhdrPixelMap != nullptr);
        return nullptr;
    }
    std::scoped_lock<std::mutex> vpeLock(g_vpeMutex);
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
    auto rect = snapshot.hdrConfig.rect;
    ContrastEnhancerRect displayArea = { rect.x, rect.y, rect.width, rect.height };
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

RefPtr<PixelMap> PictureDrawableDescriptor::LoadPixelMap(const LoadSnapshot& snapshot)
{
    if (!snapshot.picture) {
        return nullptr;
    }
    RefPtr<PixelMap> pixelMap;
    if (IsHdrConfigValid(snapshot.hdrConfig)) {
        pixelMap = DoComposeFOV(snapshot);
    }
    if (!pixelMap) {
        pixelMap = snapshot.picture->GetMainPixel();
    }
    return pixelMap;
}

DrawableDescriptorLoadResult PictureDrawableDescriptor::LoadSync()
{
    auto snapshot = CreateLoadSnapshot();
    auto pixelMap = LoadPixelMap(snapshot);
    if (!pixelMap) {
        return { 0, 0, -1 };
    }
    std::scoped_lock<std::mutex> lock(stateMutex_);
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
    std::scoped_lock<std::mutex> lock(stateMutex_);
    updateCallbacks_[nodeId] = std::move(callback);
}

void PictureDrawableDescriptor::UnRegisterUpdateCallback(int32_t nodeId)
{
    std::scoped_lock<std::mutex> lock(stateMutex_);
    updateCallbacks_.erase(nodeId);
}

void PictureDrawableDescriptor::Invalidate()
{
    PostInvalidateTask(EnqueueInvalidateTask());
}

CancelableCallback<void()> PictureDrawableDescriptor::EnqueueInvalidateTask()
{
    std::scoped_lock<std::mutex> lock(stateMutex_);
    auto snapshot = CreateLoadSnapshotLocked();
    if (!isInvalidateTaskInFlight_) {
        isInvalidateTaskInFlight_ = true;
        CancelableCallback<void()> task(MakeInvalidateTask(snapshot));
        return task;
    }

    // A task is already posted or running. Keep a single pending slot and
    // replace it with the newest invalidate request.
    latestPendingInvalidateTask_.Reset(MakeInvalidateTask(snapshot));
    return {};
}

std::function<void()> PictureDrawableDescriptor::MakeInvalidateTask(const LoadSnapshot& snapshot)
{
    return [weak = WeakClaim(this), snapshot]() {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->RunInvalidateTask(snapshot);
    };
}

CancelableCallback<void()> PictureDrawableDescriptor::TakeNextInvalidateTask()
{
    std::scoped_lock<std::mutex> lock(stateMutex_);
    if (!latestPendingInvalidateTask_) {
        isInvalidateTaskInFlight_ = false;
        return {};
    }
    auto pendingTask = latestPendingInvalidateTask_;
    latestPendingInvalidateTask_ = CancelableCallback<void()>();
    return pendingTask;
}

void PictureDrawableDescriptor::PostInvalidateTask(CancelableCallback<void()> task)
{
    if (!task) {
        return;
    }
    NG::ImageUtils::PostToBg(task, "PictureDrawableInvalidate");
}

void PictureDrawableDescriptor::RunInvalidateTask(const LoadSnapshot& snapshot)
{
    auto pixelMap = LoadPixelMap(snapshot);
    std::vector<UpdateCallback> callbacks;
    {
        std::scoped_lock<std::mutex> lock(stateMutex_);
        if (pixelMap) {
            cachedPixelMap_ = pixelMap;
            for (auto& [_, callback] : updateCallbacks_) {
                callbacks.emplace_back(callback);
            }
        }
    }
    for (auto& callback : callbacks) {
        if (callback) {
            callback(pixelMap);
        }
    }
    PostInvalidateTask(TakeNextInvalidateTask());
}
} // namespace OHOS::Ace
