/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
#include "base/utils/device_config.h"

#include "parameter.h"
#include "parameters.h"

namespace OHOS::Ace {
namespace {
constexpr char PROPERTY_DEVICE_TYPE[] = "const.product.devicetype";
constexpr char PROPERTY_DEVICE_TYPE_DEFAULT[] = "default";
constexpr char PROPERTY_DEVICE_TYPE_TV[] = "tv";
constexpr char PROPERTY_DEVICE_TYPE_TABLET[] = "tablet";
constexpr char PROPERTY_DEVICE_TYPE_TWOINONE[] = "2in1";
constexpr char PROPERTY_DEVICE_TYPE_WATCH[] = "watch";
constexpr char PROPERTY_DEVICE_TYPE_CAR[] = "car";
constexpr char PROPERTY_DEVICE_TYPE_WEARABLE[] = "wearable";

DeviceType InitDeviceType()
{
    DeviceType realDeviceType { DeviceType::UNKNOWN };

    auto deviceProp = system::GetParameter(PROPERTY_DEVICE_TYPE, PROPERTY_DEVICE_TYPE_DEFAULT);
    // Properties: "default", "tv", "tablet", "watch", "car"
    if (deviceProp == PROPERTY_DEVICE_TYPE_TV) {
        realDeviceType = DeviceType::TV;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_CAR) {
        realDeviceType = DeviceType::CAR;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_WATCH) {
        realDeviceType = DeviceType::WATCH;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_TABLET) {
        realDeviceType = DeviceType::TABLET;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_TWOINONE) {
        realDeviceType = DeviceType::TWO_IN_ONE;
    } else if (deviceProp == PROPERTY_DEVICE_TYPE_WEARABLE) {
        realDeviceType = DeviceType::WEARABLE;
    } else {
        realDeviceType = DeviceType::PHONE;
    }
    return realDeviceType;
}
} // namespace
const DeviceType DeviceConfig::realDeviceType = InitDeviceType();
} // namespace OHOS::Ace
