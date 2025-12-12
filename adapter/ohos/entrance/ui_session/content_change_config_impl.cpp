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
ContentChangeConfigImpl::ContentChangeConfigImpl(int32_t minReportTime, float textContentRatio)
{
    config_.minReportTime = minReportTime;
    config_.textContentRatio = textContentRatio;
}

ContentChangeConfigImpl::ContentChangeConfigImpl(const ContentChangeConfig& config)
{
    config_.minReportTime = config.minReportTime;
    config_.textContentRatio = config.textContentRatio;
}

bool ContentChangeConfigImpl::Marshalling(Parcel& parcel) const
{
    if (!parcel.WriteInt32(config_.minReportTime)) {
        return false;
    }
    if (!parcel.WriteFloat(config_.textContentRatio)) {
        return false;
    }
    return true;
}

ContentChangeConfigImpl* ContentChangeConfigImpl::Unmarshalling(Parcel& parcel)
{
    int32_t minReportTime;
    if (!parcel.ReadInt32(minReportTime)) {
        return nullptr;
    }
    float textContentRatio;
    if (!parcel.ReadFloat(textContentRatio)) {
        return nullptr;
    }
    ContentChangeConfigImpl* configImpl = new ContentChangeConfigImpl(minReportTime, textContentRatio);
    return configImpl;
}

ContentChangeConfig ContentChangeConfigImpl::GetConfig() const
{
    return config_;
}
} // namespace OHOS::Ace
