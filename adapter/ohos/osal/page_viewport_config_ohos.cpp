/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "adapter/ohos/osal/page_viewport_config_ohos.h"

#include "adapter/ohos/entrance/utils.h"
#include "base/geometry/ng/size_t.h"

namespace OHOS::Ace {

RefPtr<PageViewportConfig> PageViewportConfigOhos::Clone() const
{
    auto ret = MakeRefPtr<PageViewportConfigOhos>();
    ret->config_ = config_;
    ret->avoidAreas_ = avoidAreas_;
    ret->pipeline_ = pipeline_;
    return ret;
}

NG::LayoutConstraintF PageViewportConfigOhos::CreateRootLayoutConstraint() const
{
    NG::LayoutConstraintF layoutConstraint;
    layoutConstraint.scaleProperty = NG::ScaleProperty::CreateScaleProperty();
    auto rootWidth = config_.Width();
    auto rootHeight = config_.Height();
    layoutConstraint.percentReference.SetWidth(rootWidth);
    layoutConstraint.percentReference.SetHeight(rootHeight);
    layoutConstraint.maxSize.SetWidth(rootWidth);
    layoutConstraint.maxSize.SetHeight(rootHeight);
    return layoutConstraint;
}

NG::SafeAreaInsets PageViewportConfigOhos::GetSafeArea() const
{
    NG::SafeAreaInsets insets;
    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_RETURN(pipeline, insets);
    auto mgr = pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(mgr, insets);
    for (auto& avoidArea : avoidAreas_) {
        auto type = avoidArea.first;
        if (type == OHOS::Rosen::AvoidAreaType::TYPE_SYSTEM ||
            type == OHOS::Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR ||
            (type == OHOS::Rosen::AvoidAreaType::TYPE_CUTOUT && mgr->GetUseCutout())) {
            auto newInsets = ConvertAvoidArea(avoidArea.second);
            insets = insets.Combine(newInsets);
        }
    }
    return insets;
}

void PageViewportConfigOhos::ApplySafeArea()
{
    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    auto mgr = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(mgr);
    BackupInfo backupInfo;
    backupInfo.rootWidth = static_cast<uint32_t>(pipeline->GetRootWidth());
    backupInfo.rootHeight = static_cast<uint32_t>(pipeline->GetRootHeight());
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "backup rootSize, width:%{public}u, height:%{public}u",
        backupInfo.rootWidth, backupInfo.rootHeight);
    for (auto& avoidArea : avoidAreas_) {
        if (avoidArea.first == OHOS::Rosen::AvoidAreaType::TYPE_SYSTEM) {
            auto insets = mgr->GetSystemSafeArea();
            backupInfo.safeAreas[OHOS::Rosen::AvoidAreaType::TYPE_SYSTEM] = insets;
            auto newInsets = ConvertAvoidArea(avoidArea.second);
            mgr->UpdateSystemSafeArea(newInsets);
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "ApplyConfig system from %{public}s to %{public}s",
                insets.ToString().c_str(), newInsets.ToString().c_str());
        } else if (avoidArea.first == OHOS::Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR) {
            auto insets = mgr->GetNavSafeArea();
            backupInfo.safeAreas[OHOS::Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR] = insets;
            auto newInsets = ConvertAvoidArea(avoidArea.second);
            mgr->UpdateNavSafeArea(newInsets);
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "ApplyConfig navigationIndicator from %{public}s to %{public}s",
                insets.ToString().c_str(), newInsets.ToString().c_str());
        } else if (avoidArea.first == OHOS::Rosen::AvoidAreaType::TYPE_CUTOUT && mgr->GetUseCutout()) {
            auto insets = mgr->GetCutoutSafeAreaWithoutProcess();
            backupInfo.safeAreas[OHOS::Rosen::AvoidAreaType::TYPE_CUTOUT] = insets;
            auto newInsets = ConvertAvoidArea(avoidArea.second);
            mgr->UpdateCutoutSafeArea(newInsets, NG::OptionalSize<uint32_t>(config_.Width(), config_.Height()));
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "ApplyConfig cutout from %{public}s to %{public}s",
                insets.ToString().c_str(), newInsets.ToString().c_str());
        }
    }
    backupInfos_.emplace(std::move(backupInfo));
}

void PageViewportConfigOhos::RestoreSafeArea()
{
    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    auto mgr = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(mgr);
    if (backupInfos_.empty()) {
        return;
    }
    auto backupInfo = std::move(backupInfos_.top());
    backupInfos_.pop();
    for (auto& avoidArea : backupInfo.safeAreas) {
        if (avoidArea.first == OHOS::Rosen::AvoidAreaType::TYPE_SYSTEM) {
            mgr->UpdateSystemSafeArea(avoidArea.second);
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "RestoreConfig system: %{public}s",
                avoidArea.second.ToString().c_str());
        } else if (avoidArea.first == OHOS::Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR) {
            mgr->UpdateNavSafeArea(avoidArea.second);
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "RestoreConfig navigationIndicator: %{public}s",
                avoidArea.second.ToString().c_str());
        } else if (avoidArea.first == OHOS::Rosen::AvoidAreaType::TYPE_CUTOUT && mgr->GetUseCutout()) {
            mgr->UpdateCutoutSafeArea(
                avoidArea.second, NG::OptionalSize<uint32_t>(backupInfo.rootWidth, backupInfo.rootHeight));
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "RestoreConfig cutout width:%{public}u, height:%{public}u, "
                "insets:%{public}s", backupInfo.rootWidth, backupInfo.rootHeight, avoidArea.second.ToString().c_str());
        }
    }
}
} // namespace OHOS::Ace