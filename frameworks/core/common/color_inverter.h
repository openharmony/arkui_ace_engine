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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_COLOR_INVERTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_COLOR_INVERTER_H
#include <functional>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/singleton.h"
#include "base/utils/utils.h"
#include "core/common/container_consts.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t PROCESS_LEVEL_ID = INSTANCE_ID_UNDEFINED;
} // namespace

typedef std::function<uint32_t(uint32_t)> ColorInvertFunc;

class ColorInvertFuncManager final : public AceType {
public:
    ColorInvertFuncManager() = default;
    ~ColorInvertFuncManager() = default;

    static RefPtr<ColorInvertFuncManager> Create();

    void SetInvertFunc(const std::string& nodeTag, ColorInvertFunc&& func);

    void DeleteInvertFunc(const std::string& nodeTag);

    ColorInvertFunc GetInvertFunc(const std::string& nodeTag);

private:
    std::unordered_map<std::string, ColorInvertFunc> colorInvertFuncMap_;
};

class ColorInverter : public Singleton<ColorInverter> {
    DECLARE_SINGLETON(ColorInverter);

public:
    static uint32_t DefaultInverter(uint32_t color);

    void EnableColorInvert(int32_t instanceId, const std::string& nodeTag, ColorInvertFunc&& func);
    void DisableColorInvert(int32_t instanceId);
    ColorInvertFunc GetInvertFunc(int32_t instanceId, const std::string& nodeTag) const;
    static Color Invert(Color color, int32_t instanceId, const std::string& nodeTag);
    RefPtr<ColorInvertFuncManager> GetManager(int32_t instanceId) const; // for user

private:
    RefPtr<ColorInvertFuncManager> GetOrCreateManager(int32_t instanceId); // for setter
    std::unordered_map<int32_t, RefPtr<ColorInvertFuncManager>> colorInvertFuncManagerMap_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_COLOR_INVERTER_H
