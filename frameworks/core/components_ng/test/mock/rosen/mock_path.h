/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_PATH_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_PATH_H

#include "gmock/gmock.h"
#include "testing_path.h"

namespace OHOS::Ace::Testing {
class MockPath : public TestingPath {
public:
    MockPath() = default;
    ~MockPath() = default;

    MOCK_METHOD3(AddArc, void(Rect oval, scalar startAngle, scalar sweepAngle));
    MOCK_METHOD2(MoveTo, void(scalar x, scalar y));
    MOCK_METHOD2(LineTo, void(scalar x, scalar y));
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_PATH_H
