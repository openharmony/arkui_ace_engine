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
#include "adapter/ohos/test/unittest/mock/common.h"
#include "adapter/ohos/test/unittest/mock/mock_exception_handler_wrapper.h"

using namespace testing::ext;

namespace OHOS::Ace {
class ExceptionHandlerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void ExceptionHandlerTest::SetUpTestCase() {}

void ExceptionHandlerTest::TearDownTestCase() {}

void ExceptionHandlerTest::SetUp() {}

void ExceptionHandlerTest::TearDown() {}

/**
 * @tc.name: ExceptionHandlerTest_HandleJsException_001
 * @tc.desc: Verify whether the HandleJsException function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(ExceptionHandlerTest, ExceptionHandlerTest_HandleJsException_001, TestSize.Level1)
{
    auto exceptionHandlerWrapper = AceType::MakeRefPtr<MockExceptionHandlerWrapper>();
    CHECK_PTR_NULL_VOID(exceptionHandlerWrapper);
    auto result = exceptionHandlerWrapper->HandleJsExceptionWrapper("exceptionMsg");
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace
