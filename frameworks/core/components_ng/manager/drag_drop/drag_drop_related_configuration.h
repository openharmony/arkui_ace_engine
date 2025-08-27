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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_RELATED_CONFIGURATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_RELATED_CONFIGURATION_H

#include "base/memory/ace_type.h"
#include "core/components_ng/gestures/gesture_info.h"

namespace OHOS::Ace::NG {
constexpr int32_t DEFAULT_STILL_TIME_LIMIT = 500;
constexpr int32_t DEFAULT_UPDATE_INTERVAL = 100;
constexpr int32_t DEFAULT_UPDATE_NOTIFY_COUNT = 3;
constexpr int32_t DEFAULT_UPDATE_TO_FINISH_INTERVAL = 100;

struct DragSpringLoadingConfiguration : public AceType {
    DECLARE_ACE_TYPE(DragSpringLoadingConfiguration, AceType);

public:
    DragSpringLoadingConfiguration() = default;
    ~DragSpringLoadingConfiguration() override = default;
    int32_t stillTimeLimit = DEFAULT_STILL_TIME_LIMIT;
    int32_t updateInterval = DEFAULT_UPDATE_INTERVAL;
    int32_t updateNotifyCount = DEFAULT_UPDATE_NOTIFY_COUNT;
    int32_t updateToFinishInterval = DEFAULT_UPDATE_TO_FINISH_INTERVAL;
};

class DragDropRelatedConfigurations : public AceType {
    DECLARE_ACE_TYPE(DragDropRelatedConfigurations, AceType);

public:
    RefPtr<DragSpringLoadingConfiguration> GetOrCreateDragSpringLoadingConfiguration();

    void SetDragSpringLoadingConfiguration(
        const RefPtr<DragSpringLoadingConfiguration>& dragSpringLoadingConfiguration);
    
    DragPreviewOption GetOrCreateDragPreviewOption();
    void SetOptionsAfterApplied(const OptionsAfterApplied& optionsAfterApplied);
    void SetDragPreviewOption(const DragPreviewOption& previewOption, bool isResetOptions);

private:
    RefPtr<DragSpringLoadingConfiguration> dragSpringLoadingConfiguration_;
    std::unique_ptr<DragPreviewOption> previewOption_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_RELATED_CONFIGURATION_H