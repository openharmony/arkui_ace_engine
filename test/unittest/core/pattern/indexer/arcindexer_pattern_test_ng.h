/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_INDEXER_ARC_INDEXER_PATTERN_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_INDEXER_ARC_INDEXER_PATTERN_TEST_NG_H

#include "core/components_ng/pattern/indexer/indexer_pattern.h"

namespace OHOS::Ace::NG {

class ArcIndexerAccessibilitySAObserverCallback : public AccessibilitySAObserverCallback {
public:
    ArcIndexerAccessibilitySAObserverCallback(
        const WeakPtr<ArcIndexerPattern>& weakPattern, int64_t accessibilityId)
        : AccessibilitySAObserverCallback(accessibilityId), weakPattern_(weakPattern) {}
    ~ArcIndexerAccessibilitySAObserverCallback() override = default;

    bool OnState(bool state) override;

private:
    WeakPtr<ArcIndexerPattern> weakPattern_;
};

} // OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_INDEXER_ARC_INDEXER_PATTERN_TEST_NG_H
