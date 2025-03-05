/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components/common/layout/screen_system_manager.h"

#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
namespace {
    constexpr Dimension MAX_SCREEN_WIDTH_SM = 320.0_vp;
    constexpr Dimension MAX_SCREEN_WIDTH_MD = 600.0_vp;
    constexpr Dimension MAX_SCREEN_WIDTH_LG = 840.0_vp;
    constexpr Dimension MAX_SCREEN_WIDTH_XL = 1024.0_vp;
} // namespace

std::mutex ScreenSystemManager::lock;
void ScreenSystemManager::OnSurfaceChanged(double width)
{
    std::lock_guard<std::mutex> guard(lock);
    screenWidth_ = width;
    if (width < MAX_SCREEN_WIDTH_SM.Value() * density_) {
        currentSize_ = ScreenSizeType::XS;
    } else if (width < MAX_SCREEN_WIDTH_MD.Value() * density_) {
        currentSize_ = ScreenSizeType::SM;
    } else if (width < MAX_SCREEN_WIDTH_LG.Value() * density_) {
        currentSize_ = ScreenSizeType::MD;
    } else if (width < MAX_SCREEN_WIDTH_XL.Value() * density_) {
        currentSize_ = ScreenSizeType::LG;
    } else {
        currentSize_ = ScreenSizeType::XL;
    }
}

ScreenSizeType ScreenSystemManager::GetSize(double width) const
{
    std::lock_guard<std::mutex> guard(lock);
    ScreenSizeType size = ScreenSizeType::UNDEFINED;
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, size);
    auto dipScale = context->GetDipScale();
    if (width < MAX_SCREEN_WIDTH_SM.Value() * dipScale) {
        size = ScreenSizeType::XS;
    } else if (width < MAX_SCREEN_WIDTH_MD.Value() * dipScale) {
        size = ScreenSizeType::SM;
    } else if (width < MAX_SCREEN_WIDTH_LG.Value() * dipScale) {
        size = ScreenSizeType::MD;
    } else if (width < MAX_SCREEN_WIDTH_XL.Value() * dipScale) {
        size = ScreenSizeType::LG;
    } else {
        size = ScreenSizeType::XL;
    }
    return size;
}

double ScreenSystemManager::GetScreenWidth(const RefPtr<PipelineBase>& pipeline) const
{
    std::lock_guard<std::mutex> guard(lock);
    if (pipeline) {
        return pipeline->GetRootWidth();
    }
    return screenWidth_;
}
} // namespace OHOS::Ace
