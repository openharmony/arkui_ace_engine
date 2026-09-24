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

#include "adapter/ohos/entrance/event_compatible/compatible_interface.h"

namespace OHOS::Ace::NG {
// Stub for host/ohos unit tests: avoid querying the bundle manager so the real
// EventInfoConvertor translation unit can link without a live system ability.
void CompatibleInterface::LoadBundleInfo() {}

bool CompatibleInterface::MatchCompatibleCondition()
{
    return false;
}

CompatibleInfo CompatibleInterface::MatchMouseTransformState()
{
    return CompatibleInfo(false);
}

bool CompatibleInterface::IsAppDevelopedForPC()
{
    return false;
}

bool CompatibleInterface::QueryBundleInfo()
{
    return false;
}

void CompatibleInterface::PrepareSupportPCInfo(const AppExecFwk::BundleInfo& bundleInfo) {}
} // namespace OHOS::Ace::NG
