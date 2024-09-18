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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_FORWARD_COMPATIBILITY_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_FORWARD_COMPATIBILITY_H

#include <string>
#include "macros.h"

namespace OHOS {
namespace Ace {
// only work in app start progress, not multi-threads safe
class ACE_FORCE_EXPORT AceForwardCompatibility final {
public:
    ~AceForwardCompatibility() = default;

    static void Init(const std::string& bundleName, const uint32_t apiCompatibleVersion, bool forceFullUpdate);
    static bool IsForceOldPipeline();
    static bool IsNewPipeline(); // true for using libace, false for using libace_compatible
    static bool IsUseNG(); // true for using newpipeline in ace engine
    static bool PipelineChanged();
    static const char* GetAceLibName();
    static void ReclaimFileCache(int32_t pid);
private:
    AceForwardCompatibility() = default;
    static inline bool isForceOldPipeline_ = true;
    static inline bool isNewPipeline_ = true;
    static inline bool isNewAppspawn_ = true;
    static inline bool isInited_ = false;
};
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_FORWARD_COMPATIBILITY_H
