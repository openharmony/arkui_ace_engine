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

#include "adapter/ohos/entrance/ui_session/content_change_config_impl.h"

namespace OHOS::Ace {
ContentChangeConfigImpl::ContentChangeConfigImpl(int32_t minReportTime, float textContentRatio,
    std::string ignoreEventType, int32_t minWidth, int32_t minHeight, int32_t reportDelayTime)
{
    config_.minReportTime = minReportTime;
    config_.textContentRatio = textContentRatio;
    config_.ignoreEventType = ignoreEventType;
    config_.minWidth = minWidth;
    config_.minHeight = minHeight;
    config_.reportDelayTime = reportDelayTime;
}

ContentChangeConfigImpl::ContentChangeConfigImpl(const ContentChangeConfig& config)
{
    config_.minReportTime = config.minReportTime;
    config_.textContentRatio = config.textContentRatio;
    config_.ignoreEventType = config.ignoreEventType;
    config_.minWidth = config.minWidth;
    config_.minHeight = config.minHeight;
    config_.reportDelayTime = config.reportDelayTime;
}

bool ContentChangeConfigImpl::Marshalling(Parcel& parcel) const
{
    if (!parcel.WriteInt32(config_.minReportTime)) {
        return false;
    }
    if (!parcel.WriteFloat(config_.textContentRatio)) {
        return false;
    }
    if (!parcel.WriteString(config_.ignoreEventType)) {
        return false;
    }
    if (!parcel.WriteInt32(config_.minWidth)) {
        return false;
    }
    if (!parcel.WriteInt32(config_.minHeight)) {
        return false;
    }
    if (!parcel.WriteInt32(config_.reportDelayTime)) {
        return false;
    }
    return true;
}

ContentChangeConfigImpl* ContentChangeConfigImpl::Unmarshalling(Parcel& parcel)
{
    int32_t minReportTime = 100;
    if (!parcel.ReadInt32(minReportTime)) {
        return nullptr;
    }
    float textContentRatio = 0.15f;
    if (!parcel.ReadFloat(textContentRatio)) {
        return nullptr;
    }
    std::string ignoreEventType = "";
    if (!parcel.ReadString(ignoreEventType)) {
        return nullptr;
    }
    int32_t minWidth = 100;
    if (!parcel.ReadInt32(minWidth)) {
        return nullptr;
    }
    int32_t minHeight = 100;
    if (!parcel.ReadInt32(minHeight)) {
        return nullptr;
    }
    int32_t reportDelayTime = 600;
    if (!parcel.ReadInt32(reportDelayTime)) {
        return nullptr;
    }
    ContentChangeConfigImpl* configImpl = new ContentChangeConfigImpl(
        minReportTime, textContentRatio, ignoreEventType, minWidth, minHeight, reportDelayTime);
    return configImpl;
}

ContentChangeConfig ContentChangeConfigImpl::GetConfig() const
{
    return config_;
}
} // namespace OHOS::Ace
