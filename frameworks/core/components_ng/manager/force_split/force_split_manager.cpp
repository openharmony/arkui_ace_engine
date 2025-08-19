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

#include "core/components_ng/manager/force_split/force_split_manager.h"

#include "base/log/dump_log.h"
#include "base/utils/system_properties.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension SPLIT_THRESHOLD_WIDTH = 600.0_vp;

const char* DeviceOrientationToString(DeviceOrientation ori)
{
    switch (ori) {
        case DeviceOrientation::PORTRAIT:
            return "PORTRAIT";
        case DeviceOrientation::LANDSCAPE:
            return "LANDSCAPE";
        case DeviceOrientation::ORIENTATION_UNDEFINED:
            return "ORIENTATION_UNDEFINED";
        default:
            return "UNKNOWN";
    }
}
}

void ForceSplitManager::SetForceSplitEnable(bool isForceSplit, bool ignoreOrientation)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "%{public}s forceSplit, ignoreOrientation:%{public}d",
        (isForceSplit ? "enable" : "disable"), ignoreOrientation);
    /**
     * As long as the application supports force split, regardless of whether it is enabled or not,
     * the SetForceSplitEnable interface will be called.
     */
    isForceSplitSupported_ = true;
    if (isForceSplitEnable_ == isForceSplit && ignoreOrientation_ == ignoreOrientation) {
        return;
    }
    isForceSplitEnable_ = isForceSplit;
    ignoreOrientation_ = ignoreOrientation;
    auto context = pipeline_.Upgrade();
    CHECK_NULL_VOID(context);
    auto width = context->GetWindowOriginalWidth();
    if (width > 0) {
        UpdateIsInForceSplitMode(width);
        context->ForceUpdateDesignWidthScale(width);
        auto rootNode = context->GetRootElement();
        CHECK_NULL_VOID(rootNode);
        const auto& geometryNode = rootNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        geometryNode->ResetParentLayoutConstraint();
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}
 
void ForceSplitManager::UpdateIsInForceSplitMode(int32_t width)
{
    if (!isForceSplitSupported_) {
        return;
    }
 
    auto context = pipeline_.Upgrade();
    CHECK_NULL_VOID(context);
    auto container = Container::GetContainer(context->GetInstanceId());
    CHECK_NULL_VOID(container);
    auto windowManager = context->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    bool forceSplitSuccess = false;
    if (isForceSplitEnable_) {
        /**
         * The force split mode must meet the following conditions to take effect:
         *   1. Belonging to the main window of the application
         *   2. The application is in landscape mode or ignore orientation
         *   3. The application is not in split screen mode
         *   4. width greater than 600vp
         */
        bool isMainWindow = container->IsMainWindow();
        auto thresholdWidth = SPLIT_THRESHOLD_WIDTH.ConvertToPx();
        auto dipScale = context->GetDipScale();
        auto orientation = SystemProperties::GetDeviceOrientation();
        auto windowMode = windowManager->GetWindowMode();
        bool isInSplitScreenMode = windowMode == WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
            windowMode == WindowMode::WINDOW_MODE_SPLIT_SECONDARY;
        auto ignoreOrientation = GetIgnoreOrientation();
        forceSplitSuccess = isMainWindow &&
            (ignoreOrientation || orientation == DeviceOrientation::LANDSCAPE) &&
            thresholdWidth < width && !isInSplitScreenMode;
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "ForceSplitManager calc splitMode, isMainWindow:%{public}d, "
            "isInSplitScreenMode:%{public}d, ignoreOrientation:%{public}d, orientation: %{public}s, dipScale: "
            "%{public}f, thresholdWidth: %{public}f, curWidth: %{public}d, forceSplitSuccess:%{public}d",
            isMainWindow, isInSplitScreenMode, ignoreOrientation, DeviceOrientationToString(orientation), dipScale,
            thresholdWidth, width, forceSplitSuccess);
    }
    context->SetIsCurrentInForceSplitMode(forceSplitSuccess);
}
 
bool ForceSplitManager::GetIgnoreOrientation() const
{
    if (SystemProperties::GetForceSplitIgnoreOrientationEnabled()) {
        return true;
    }
    return ignoreOrientation_;
}
} // namespace OHOS::Ace::NG