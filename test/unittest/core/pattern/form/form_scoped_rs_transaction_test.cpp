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

#include "gtest/gtest.h"
#include "base/utils/system_properties.h"
#define private public
#include "core/components_ng/pattern/form/form_scoped_rs_transaction.h"
#undef private

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_INSTANCE_ID = 0;
}

class FormScopedRSTransactionTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;

private:
    static bool multiInstanceEnabledBackup_;
};

bool FormScopedRSTransactionTest::multiInstanceEnabledBackup_ = false;

void FormScopedRSTransactionTest::SetUpTestSuite()
{}
 
void FormScopedRSTransactionTest::TearDownTestSuite()
{}

void FormScopedRSTransactionTest::SetUp()
{
    FormScopedRSTransactionTest::multiInstanceEnabledBackup_ = SystemProperties::GetMultiInstanceEnabled();
}

void FormScopedRSTransactionTest::TearDown()
{
    SystemProperties::SetMultiInstanceEnabled(FormScopedRSTransactionTest::multiInstanceEnabledBackup_);
}

/**
 * @tc.name: FormScopedRSTransactionTest001
 * @tc.desc: test scoped transaction function with multi-instance enabled
 * @tc.type: FUNC
 */
HWTEST_F(FormScopedRSTransactionTest, FormScopedRSTransactionTest001, TestSize.Level0)
{
    SystemProperties::SetMultiInstanceEnabled(true);
    FormScopedRSTransaction scopedRSTransaction(DEFAULT_INSTANCE_ID);
    EXPECT_TRUE(scopedRSTransaction.isMultiInstanceEnabled_);
    EXPECT_EQ(scopedRSTransaction.transactionHandler_, nullptr);
    EXPECT_EQ(scopedRSTransaction.needCloseSync_, false);
}

/**
 * @tc.name: FormScopedRSTransactionTest002
 * @tc.desc: test scoped transaction function with multi-instance disabled
 * @tc.type: FUNC
 */
HWTEST_F(FormScopedRSTransactionTest, FormScopedRSTransactionTest002, TestSize.Level0)
{
    SystemProperties::SetMultiInstanceEnabled(false);
    FormScopedRSTransaction scopedRSTransaction(0);
    EXPECT_EQ(scopedRSTransaction.needCloseSync_, true);

    scopedRSTransaction.CloseSyncTransaction();
    EXPECT_EQ(scopedRSTransaction.needCloseSync_, false);
}
}  // namespace OHOS::Ace::NG
