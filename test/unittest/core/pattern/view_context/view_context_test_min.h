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

#ifndef TEST_UNITTEST_CORE_PATTERN_VIEW_CONTEXT_VIEW_CONTEXT_TEST_MIN_H
#define TEST_UNITTEST_CORE_PATTERN_VIEW_CONTEXT_VIEW_CONTEXT_TEST_MIN_H

#include "gtest/gtest.h"

// Base test class for view_context tests
class ViewContextTestBase : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

#endif // TEST_UNITTEST_CORE_PATTERN_VIEW_CONTEXT_VIEW_CONTEXT_TEST_MIN_H
