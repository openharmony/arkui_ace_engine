/**
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/common/display_info_utils.h"

#include "display_manager.h"

#include "core/common/display_info.h"

namespace OHOS::Ace {
RefPtr<DisplayInfo> DisplayInfoUtils::GetDisplayInfo()
{
    auto displayManager = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    CHECK_NULL_RETURN(displayManager, nullptr);
    displayInfo_->SetWidth(displayManager->GetWidth());
    displayInfo_->SetHeight(displayManager->GetHeight());
    displayInfo_->SetDisplayId(displayManager->GetId());
    auto dmRotation = displayManager->GetRotation();
    displayInfo_->SetRotation(static_cast<Rotation>(static_cast<uint32_t>(dmRotation)));
    GetIsFoldable();
    GetCurrentFoldStatus();
    GetCurrentFoldCreaseRegion();
    return displayInfo_;
}

void DisplayInfoUtils::InitIsFoldable()
{
    auto isFoldable = Rosen::DisplayManager::GetInstance().IsFoldable();
    displayInfo_->SetIsFoldable(isFoldable);
}

bool DisplayInfoUtils::GetIsFoldable()
{
    if (hasInitIsFoldable_) {
        return displayInfo_->GetIsFoldable();
    }
    auto isFoldable = Rosen::DisplayManager::GetInstance().IsFoldable();
    displayInfo_->SetIsFoldable(isFoldable);
    hasInitIsFoldable_ = true;
    return isFoldable;
}

FoldStatus DisplayInfoUtils::GetCurrentFoldStatus()
{
    auto dmFoldStatus = Rosen::DisplayManager::GetInstance().GetFoldStatus();
    displayInfo_->SetFoldStatus(static_cast<FoldStatus>(static_cast<uint32_t>(dmFoldStatus)));
    return displayInfo_->GetFoldStatus();
}

std::vector<Rect> DisplayInfoUtils::GetCurrentFoldCreaseRegion()
{
    if (hasInitFoldCreaseRegion_) {
        return displayInfo_->GetCurrentFoldCreaseRegion();
    }
    std::vector<Rect> rects;
    auto foldCreaseRegion = Rosen::DisplayManager::GetInstance().GetCurrentFoldCreaseRegion();
    if (!foldCreaseRegion) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "failed to get foldCreaseRegion");
        return rects;
    }

    auto creaseRects = foldCreaseRegion->GetCreaseRects();
    if (creaseRects.empty()) {
        return rects;
    }

    for (const auto& item : creaseRects) {
        Rect rect;
        rect.SetRect(item.posX_, item.posY_, item.width_, item.height_);
        rects.insert(rects.end(), rect);
    }
    displayInfo_->SetCurrentFoldCreaseRegion(rects);
    hasInitFoldCreaseRegion_ = true;
    return rects;
}
} // namespace OHOS::Ace::DisplayInfoUtils
