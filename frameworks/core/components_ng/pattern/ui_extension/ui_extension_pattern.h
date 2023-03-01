/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_PATTERN_H

#include "base/log/log.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_event_hub.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_layout_algorithm.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_paint_property.h"
#include "core/components_ng/pattern/window_scene/scene/host/host_window_extension.h"

namespace OHOS::Ace::NG {
class UIExtensionPattern : public HostWindowExtension {
    DECLARE_ACE_TYPE(UIExtensionPattern, HostWindowExtension);

public:
    UIExtensionPattern(const std::string& bundleName, const std::string& abilityName)
        : HostWindowExtension(bundleName, abilityName)
    {}

    ~UIExtensionPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<UIExtensionLayoutAlgorithm>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<UIExtensionPaintProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<UIExtensionEventHub>();
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(UIExtensionPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_PATTERN_H
