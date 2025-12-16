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

#include "adapter/ohos/entrance/ui_session/get_inspector_tree_config_impl.h"

namespace OHOS::Ace {
GetInspectorTreeConfigImpl::GetInspectorTreeConfigImpl(
    bool interactionInfo, bool accessibilityInfo, bool cacheNodes, bool withWeb)
{
    config_.interactionInfo = interactionInfo;
    config_.accessibilityInfo = accessibilityInfo;
    config_.cacheNodes = cacheNodes;
    config_.withWeb = withWeb;
}
GetInspectorTreeConfigImpl::GetInspectorTreeConfigImpl(const ParamConfig& config)
{
    config_.interactionInfo = config.interactionInfo;
    config_.accessibilityInfo = config.accessibilityInfo;
    config_.cacheNodes = config.cacheNodes;
    config_.withWeb = config.withWeb;
}
bool GetInspectorTreeConfigImpl::Marshalling(Parcel& parcel) const
{
    if (!parcel.WriteBool(config_.interactionInfo)) {
        return false;
    }
    if (!parcel.WriteBool(config_.accessibilityInfo)) {
        return false;
    }
    if (!parcel.WriteBool(config_.cacheNodes)) {
        return false;
    }
    if (!parcel.WriteBool(config_.withWeb)) {
        return false;
    }
    return true;
}
GetInspectorTreeConfigImpl* GetInspectorTreeConfigImpl::Unmarshalling(Parcel& parcel)
{
    bool interactionInfo = false;
    bool accessibilityInfo = false;
    bool cacheNodes = false;
    bool withWeb = false;
    if (!parcel.ReadBool(interactionInfo)) {
        return nullptr;
    }
    if (!parcel.ReadBool(accessibilityInfo)) {
        return nullptr;
    }
    if (!parcel.ReadBool(cacheNodes)) {
        return nullptr;
    }
    if (!parcel.ReadBool(withWeb)) {
        return nullptr;
    }
    GetInspectorTreeConfigImpl* configImpl =
        new GetInspectorTreeConfigImpl(interactionInfo, accessibilityInfo, cacheNodes, withWeb);
    return configImpl;
}
ParamConfig GetInspectorTreeConfigImpl::GetConfig() const
{
    return config_;
}
} // namespace OHOS::Ace