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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SECURITY_COMPONENT_SECURITY_COMPONENT_PROBE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SECURITY_COMPONENT_SECURITY_COMPONENT_PROBE_H

#include <memory>
#include <mutex>
#include <string>
#include "base/thread/task_executor.h"
#include "i_sec_comp_probe.h"

namespace OHOS::Ace::NG {
class SecurityComponentProbe : public OHOS::Security::SecurityComponent::ISecCompProbe {
public:
    SecurityComponentProbe() = default;
    ~SecurityComponentProbe() = default;

    int32_t GetComponentInfo(int32_t nodeId, std::string& compInfoStr) override;
    void InitProbeTask();

private:
    std::timed_mutex tmux_;
    std::optional<SingleTaskExecutor> taskExec_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SECURITY_COMPONENT_SECURITY_COMPONENT_PROBE_H
