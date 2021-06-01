/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/media_query/media_query_info.h"

#include "base/json/json_util.h"
#include "base/log/log.h"

namespace OHOS::Ace::Framework {

std::string MediaQueryInfo::GetDeviceType() const
{
    if (SystemProperties::GetParamDeviceType() == "tablet") {
        return "tablet";
    }
    switch (SystemProperties::GetDeviceType()) {
        case DeviceType::TV:
            return "tv";
        case DeviceType::CAR:
            return "car";
        case DeviceType::WATCH:
            return "wearable";
        default:
            return "phone";
    }
}

std::string MediaQueryInfo::GetOrientation() const
{
    switch (SystemProperties::GetDevcieOrientation()) {
        case DeviceOrientation::PORTRAIT:
            return "portrait";
        case DeviceOrientation::LANDSCAPE:
            return "landscape";
        default:
            LOGE("unsupported orientation type");
    }
    return "";
}

std::string MediaQueryInfo::GetMediaQueryInfo() const
{
    auto json = JsonUtil::Create(true);
    int32_t width = SystemProperties::GetWidth();
    int32_t height = SystemProperties::GetHeight();
    double aspectRatio = (height != 0) ? (static_cast<double>(width) / height) : 1.0;
    json->Put("width", width);
    json->Put("height", height);
    json->Put("aspectRatio", aspectRatio);
    json->Put("roundScreen", SystemProperties::GetIsScreenRound());
    json->Put("deviceWidth", SystemProperties::GetDeviceWidth());
    json->Put("deviceHeight", SystemProperties::GetDeviceHeight());
    json->Put("resolution", SystemProperties::GetResolution());
    json->Put("orientation", GetOrientation().c_str());
    json->Put("deviceType", GetDeviceType().c_str());
    json->Put("isInit", false);
    json->Put("darkMode", SystemProperties::GetColorMode() == ColorMode::DARK);
    return json->ToString();
}

} // namespace OHOS::Ace::Framework
