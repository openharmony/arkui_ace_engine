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

#include "core/common/color_inverter.h"

#include "core/components/common/properties/color.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace {
ColorInverter::ColorInverter() = default;
ColorInverter::~ColorInverter() = default;

RefPtr<ColorInvertFuncManager> ColorInvertFuncManager::Create()
{
    return AceType::MakeRefPtr<ColorInvertFuncManager>();
}

void ColorInvertFuncManager::SetInvertFunc(const std::string& nodeTag, ColorInvertFunc&& func)
{
    colorInvertFuncMap_[nodeTag] = std::move(func);
}

void ColorInvertFuncManager::DeleteInvertFunc(const std::string& nodeTag)
{
    colorInvertFuncMap_.erase(nodeTag);
}

ColorInvertFunc ColorInvertFuncManager::GetInvertFunc(const std::string& nodeTag) const
{
    auto iter = colorInvertFuncMap_.find(nodeTag);
    if (iter == colorInvertFuncMap_.end()) {
        iter = colorInvertFuncMap_.find(V2::UNDEFINED_NODE_ETS_TAG);
    }
    CHECK_NULL_RETURN(iter != colorInvertFuncMap_.end(), nullptr);
    return iter->second;
}

RefPtr<ColorInvertFuncManager> ColorInverter::GetOrCreateManager(int32_t instanceId)
{
    auto iter = colorInvertFuncManagerMap_.find(instanceId);
    if (iter == colorInvertFuncManagerMap_.end()) {
        auto manager = ColorInvertFuncManager::Create();
        colorInvertFuncManagerMap_.emplace(instanceId, manager);
        return manager;
    }
    return iter->second;
}

void ColorInverter::EnableColorInvert(int32_t instanceId, const std::string& nodeTag, ColorInvertFunc&& func)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    auto manager = GetOrCreateManager(instanceId);
    if (manager) {
        manager->SetInvertFunc(nodeTag, std::move(func));
    }
}

void ColorInverter::DisableColorInvert(int32_t instanceId, const std::string& nodeTag)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    if (nodeTag == V2::UNDEFINED_NODE_ETS_TAG) {
        colorInvertFuncManagerMap_.erase(instanceId);
    } else {
        auto manager = GetManager(instanceId);
        CHECK_NULL_VOID(manager);
        manager->DeleteInvertFunc(nodeTag);
    }
}

ColorInvertFunc ColorInverter::GetInvertFunc(int32_t instanceId, const std::string& nodeTag)
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    auto manager = GetManager(instanceId);
    if (!manager) {
        manager = GetManager(PROCESS_LEVEL_ID);
    }
    CHECK_NULL_RETURN(manager, nullptr);
    return manager->GetInvertFunc(nodeTag);
}

RefPtr<ColorInvertFuncManager> ColorInverter::GetManager(int32_t instanceId) const
{
    auto iter = colorInvertFuncManagerMap_.find(instanceId);
    if (iter == colorInvertFuncManagerMap_.end()) {
        return nullptr;
    }
    return iter->second;
}

uint32_t ColorInverter::DefaultInverter(uint32_t color)
{
    Color curColor = Color(color);
    uint8_t full = 255;
    auto curAlpha = curColor.GetAlpha();
    Color invertColor = Color::FromARGB(curAlpha,
        full - curColor.GetRed(), full - curColor.GetGreen(), full - curColor.GetBlue());
    return invertColor.GetValue();
}

Color ColorInverter::Invert(Color color, int32_t instanceId, const std::string& nodeTag)
{
    ColorInvertFunc func = ColorInverter::GetInstance().GetInvertFunc(instanceId, nodeTag);
    return func ? Color(func(color.GetValue())) : color;
}

} // namespace OHOS::Ace
