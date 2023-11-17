/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_PLUGIN_MOCK_MOCK_BUNDLEMGR_BUNDLE_MGR_INTERFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_PLUGIN_MOCK_MOCK_BUNDLEMGR_BUNDLE_MGR_INTERFACE_H

#include "bundle_mgr_interface.h"
#include "gmock/gmock.h"

namespace OHOS::AppExecFwk {
class MOCKIBundleMgr : public IBundleMgr {
public:
    MOCKIBundleMgr() = default;
    ~MOCKIBundleMgr() override {};

    static void ReleaseInstance();
    static void CreateInstance();
    static sptr<IBundleMgr> GetInstance();

    MOCK_METHOD4(GetBundleInfo,
        bool(const std::string& bundleName, const BundleFlag flag, BundleInfo& bundleInfo, int32_t userId));
    MOCK_METHOD4(QueryAbilityInfo, bool(const Want& want, int32_t flags, int32_t userId, AbilityInfo& abilityInfo));
    MOCK_METHOD0(AsObject, sptr<IRemoteObject>());
};
} // namespace OHOS::AppExecFwk
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_PLUGIN_MOCK_MOCK_BUNDLEMGR_BUNDLE_MGR_INTERFACE_H
