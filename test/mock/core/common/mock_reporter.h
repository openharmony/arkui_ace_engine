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

#ifndef FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_REPORTER_H
#define FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_REPORTER_H

#include "gmock/gmock-function-mocker.h"
#include "gmock/gmock.h"

#include "base/memory/ace_type.h"
#include "core/common/reporter/reporter.h"

namespace OHOS::Ace::NG {
class MockReporter : public Reporter {
    DECLARE_ACE_TYPE(MockReporter, Reporter);

public:
    MOCK_METHOD(void, HandleUISessionReporting, (const JsonReport& report), (const, override));
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_UDMF_H
