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

#include "core/common/color_inverter.h"

namespace OHOS::Ace {
ColorInverter::ColorInverter() = default;
ColorInverter::~ColorInverter() = default;
uint32_t ColorInverter::DefaultInverter(uint32_t color)
{
    return color;
}

Color ColorInverter::Invert(Color color, int32_t instanceId, const std::string& nodeTag)
{
    (void)instanceId;
    (void)nodeTag;
    return color;
}

template<>
ColorInverter& Singleton<ColorInverter>::GetInstance()
{
    static ColorInverter instance;
    return instance;
}
} // namespace OHOS::Ace
