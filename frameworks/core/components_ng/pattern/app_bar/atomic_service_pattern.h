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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ATOMIC_SERVICE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ATOMIC_SERVICE_PATTERN_H

#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

namespace OHOS::Ace::NG {
class AtomicServicePattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(AtomicServicePattern, LinearLayoutPattern);
public:
    AtomicServicePattern() : LinearLayoutPattern(true) {};
    ~AtomicServicePattern() override = default;

    void OnAttachToFrameNode() override;
    void BeforeCreateLayoutWrapper() override;
    void OnLanguageConfigurationUpdate() override;

    ACE_DISALLOW_COPY_AND_MOVE(AtomicServicePattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ATOMIC_SERVICE_PATTERN_H
