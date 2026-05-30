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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_SMART_GESTURE_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_SMART_GESTURE_PROPERTY_H

#include <cstdint>
#include <memory>
#include <optional>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {
class JsonValue;
}
namespace OHOS::Ace::NG {
class InspectorFilter;

enum class SmartGestureShortcutAction : uint8_t {
    PRIMARY = 0,
};

struct SmartGestureShortcutConfig {
    SmartGestureShortcutAction action = SmartGestureShortcutAction::PRIMARY;
    bool enabled = false;
    bool selectable = false;
};

class ACE_FORCE_EXPORT SmartGestureProperty : public virtual AceType {
    DECLARE_ACE_TYPE(SmartGestureProperty, AceType);

public:
    void SetSmartGestureShortcut(const SmartGestureShortcutConfig& config)
    {
        smartGestureShortcutConfig_ = config;
    }

    void ResetSmartGestureShortcut()
    {
        smartGestureShortcutConfig_.reset();
    }

    bool IsPrimaryActionEnabled() const
    {
        return smartGestureShortcutConfig_.has_value() && smartGestureShortcutConfig_->enabled &&
               smartGestureShortcutConfig_->action == SmartGestureShortcutAction::PRIMARY;
    }

    bool IsPrimaryActionSelectable() const
    {
        return IsPrimaryActionEnabled() && smartGestureShortcutConfig_->selectable;
    }
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

private:
    std::optional<SmartGestureShortcutConfig> smartGestureShortcutConfig_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_SMART_GESTURE_PROPERTY_H
