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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PLATFORM_CONTAINER_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PLATFORM_CONTAINER_HANDLER_H

#include "base/memory/ace_type.h"
#include "core/accessibility/accessibility_manager.h"
#include "frameworks/core/common/container_handler.h"
#include "frameworks/core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

enum class DynamicContainerHandleAction : int32_t {
    ACCESSIBILITY_GET_RECT = 0,
};

class PlatformContainerHandler : public ContainerHandler {
    DECLARE_ACE_TYPE(PlatformContainerHandler, ContainerHandler);

public:
    PlatformContainerHandler() = default;
    ~PlatformContainerHandler() override = default;

    bool OnReciveData(const HandlerData& data, HandlerReply& reply) override;

    void SetContainerHostPattern(WeakPtr<Pattern> hostPattern)
    {
        hostPattern_ = hostPattern;
    }

    void UpdateAccessibilityParentRectInfo(const AccessibilityParentRectInfo& info);

    virtual void OnAccessibilityParentRectInfoUpdate() {};

private:
    bool GetAccessibilityParentRect(HandlerReply& reply);
    void GetDCAccessibilityParentRect(HandlerReply& reply);

    WeakPtr<Pattern> hostPattern_;
    AccessibilityParentRectInfo rectInfo_;
    mutable std::shared_mutex rectInfoMutex_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PLATFORM_CONTAINER_HANDLER_H
