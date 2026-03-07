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

#ifndef ADAPTER_OHOS_ENTRANCE_EVENT_COMPATIBLE_COMPATIBLE_INTERFACE_H
#define ADAPTER_OHOS_ENTRANCE_EVENT_COMPATIBLE_COMPATIBLE_INTERFACE_H

#include <mutex>
#include <string>

#include "bundlemgr/bundle_mgr_interface.h"
#include "bundlemgr/bundle_mgr_proxy.h"
#include "singleton.h"

#include "adapter/ohos/entrance/event_compatible/compatible_manager_ext.h"
namespace OHOS::Ace::NG {

class CompatibleInterface : public DelayedSingleton<CompatibleInterface> {
public:
    bool MatchCompatibleCondition();
    CompatibleInfo MatchMouseTransformState();
    bool IsAppDevelopedForPC();
    CompatibleInterface() = default;
    ~CompatibleInterface() = default;

private:
    void LoadBundleInfo();
    bool QueryBundleInfo();
    void PrepareSupportPCInfo(const AppExecFwk::BundleInfo& bundleInfo);
    std::mutex compatibleBundleInfoMutex_;
    bool isQueryBundleInfo_ = false;
    std::string bundleName_;
    bool isAppDevelopedForPC_ = false;
};

} // namespace OHOS::Ace::NG
#endif // ADAPTER_OHOS_ENTRANCE_EVENT_COMPATIBLE_COMPATIBLE_INTERFACE_H
