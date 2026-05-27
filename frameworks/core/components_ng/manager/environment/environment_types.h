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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_ENVIRONMENT_ENVIRONMENT_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_ENVIRONMENT_ENVIRONMENT_TYPES_H

#include <optional>
#include <variant>

namespace OHOS::Ace {
enum class TextDirection;
}

namespace OHOS::Ace::NG {

inline constexpr char ENV_KEY_DIRECTION[] = "system.arkui.layout.direction";
inline constexpr char ENV_KEY_FONT_SCALE[] = "system.arkui.fontScale";

struct SystemEnvValue {
    using Storage = std::variant<std::monostate, TextDirection, double>;
    Storage value;

    static SystemEnvValue FromDirection(TextDirection value)
    {
        return { value };
    }

    static SystemEnvValue FromDouble(double value)
    {
        return { value };
    }

    std::optional<TextDirection> GetDirection() const
    {
        auto direction = std::get_if<TextDirection>(&value);
        if (!direction) {
            return std::nullopt;
        }
        return *direction;
    }

    std::optional<double> GetDouble() const
    {
        auto doubleValue = std::get_if<double>(&value);
        if (!doubleValue) {
            return std::nullopt;
        }
        return *doubleValue;
    }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_ENVIRONMENT_ENVIRONMENT_TYPES_H
