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

#include <gtest/gtest.h>

#define private public
#define protected public
#include "ace_data_ability.h"
#include "context_deal.h"
#include "data_ability_predicates.h"
#include "pac_map.h"
#include "values_bucket.h"
#undef private
#undef protected

using namespace testing::ext;
using namespace OHOS::AAFwk;
namespace OHOS::Ace {
class AceDataAbilityTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void AceDataAbilityTest::SetUpTestCase() {}

void AceDataAbilityTest::TearDownTestCase() {}

void AceDataAbilityTest::SetUp() {}

void AceDataAbilityTest::TearDown() {}

/**
 * @tc.name: AceDataAbilityTest_001
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_001, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    Want want;
    want.SetParam("testParam", 1);
    if (dataAbility) {
        dataAbility->OnStart(want);
    }
}

/**
 * @tc.name: AceDataAbilityTest_002
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_002, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    if (dataAbility) {
        dataAbility->OnStop();
    }
}

/**
 * @tc.name: AceDataAbilityTest_003
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_003, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    std::string value = "value";
    Uri uri(value);
    NativeRdb::ValuesBucket values;
    values.PutInt("id", 1);
    values.PutString("name", std::string("zhangsan"));
    values.PutInt("age", 18);
    values.PutDouble("salary", 100.5);
    values.PutBlob("blobType", std::vector<uint8_t> { 1, 2, 3 });
    if (dataAbility) {
        auto ret = dataAbility->Insert(uri, values);
        EXPECT_EQ(ret, 0);
    }
}

/**
 * @tc.name: AceDataAbilityTest_004
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_004, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    std::string value = "value";
    Uri uri(value);
    NativeRdb::ValuesBucket values;
    values.PutInt("id", 1);
    values.PutString("name", std::string("zhangsan"));
    values.PutInt("age", 18);
    values.PutDouble("salary", 100.5);
    values.PutBlob("blobType", std::vector<uint8_t> { 1, 2, 3 });
    if (dataAbility) {
        auto ret = dataAbility->Insert(uri, values);
        EXPECT_EQ(ret, 0);
    }

    values.Clear();
    values.PutInt("id", 1);
    values.PutString("name", std::string("lisi"));
    values.PutInt("age", 20);
    values.PutDouble("salary", 200.5);
    values.PutBlob("blobType", std::vector<uint8_t> { 4, 5, 6 });
    NativeRdb::DataAbilityPredicates predicates;
    if (dataAbility) {
        auto ret = dataAbility->Update(uri, values, predicates);
        EXPECT_EQ(ret, 0);
    }
}

/**
 * @tc.name: AceDataAbilityTest_005
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_005, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    std::string value = "value";
    Uri uri(value);
    std::vector<std::string> columns;
    NativeRdb::DataAbilityPredicates predicates;
    if (dataAbility) {
        auto ret = dataAbility->Query(uri, columns, predicates);
        EXPECT_EQ(ret, nullptr);
    }
}

/**
 * @tc.name: AceDataAbilityTest_006
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_006, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    std::string value = "value";
    Uri uri(value);
    NativeRdb::DataAbilityPredicates predicates;
    if (dataAbility) {
        auto ret = dataAbility->Delete(uri, predicates);
        EXPECT_EQ(ret, 0);
    }
}

/**
 * @tc.name: AceDataAbilityTest_007
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_007, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    std::string value = "value";
    Uri uri(value);

    std::vector<NativeRdb::ValuesBucket> valuesBucket;
    NativeRdb::ValuesBucket values;
    values.PutInt("id", 1);
    values.PutString("name", std::string("zhangsan"));
    values.PutInt("age", 18);
    values.PutDouble("salary", 100.5);
    values.PutBlob("blobType", std::vector<uint8_t> { 1, 2, 3 });
    valuesBucket.push_back(values);
    if (dataAbility) {
        auto ret = dataAbility->BatchInsert(uri, valuesBucket);
        EXPECT_EQ(ret, 0);
    }
}

/**
 * @tc.name: AceDataAbilityTest_008
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_008, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    std::string value = "value";
    Uri uri(value);
    if (dataAbility) {
        auto ret = dataAbility->GetType(uri);
        EXPECT_TRUE(ret.empty());
    }
}

/**
 * @tc.name: AceDataAbilityTest_009
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_009, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    std::string value = "value";
    Uri uri(value);
    std::string mimeTypeFilter = "TXT";
    if (dataAbility) {
        auto ret = dataAbility->GetFileTypes(uri, mimeTypeFilter);
        EXPECT_EQ(ret.size(), 0);
    }
}

/**
 * @tc.name: AceDataAbilityTest_010
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_010, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    std::string value = "value";
    Uri uri(value);
    std::string mode = "mode";
    if (dataAbility) {
        auto ret = dataAbility->OpenFile(uri, mode);
        EXPECT_EQ(ret, 0);
    }
}

/**
 * @tc.name: AceDataAbilityTest_011
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_011, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    std::string value = "value";
    Uri uri(value);
    std::string mode = "mode";
    if (dataAbility) {
        auto ret = dataAbility->OpenRawFile(uri, mode);
        EXPECT_EQ(ret, 0);
    }
}

/**
 * @tc.name: AceDataAbilityTest_012
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_012, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    std::string value = "value";
    Uri uri(value);
    if (dataAbility) {
        auto ret = dataAbility->NormalizeUri(uri);
        EXPECT_TRUE(ret.ToString().empty());
    }
}

/**
 * @tc.name: AceDataAbilityTest_013
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_013, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    std::string value = "value";
    Uri uri(value);
    if (dataAbility) {
        auto ret = dataAbility->DenormalizeUri(uri);
        EXPECT_TRUE(ret.ToString().empty());
    }
}

/**
 * @tc.name: AceDataAbilityTest_014
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_014, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    std::string value = "value";
    Uri uri(value);
    std::string method = "method";
    std::string arg = "arg";
    AppExecFwk::PacMap pacMap;
    if (dataAbility) {
        auto ret = dataAbility->Call(uri, method, arg, pacMap);
        EXPECT_EQ(ret, nullptr);
    }
}

/**
 * @tc.name: AceDataAbilityTest_015
 * @tc.desc: Verify whether the function is called successfully
 * @tc.type: FUNC
 */
HWTEST_F(AceDataAbilityTest, AceDataAbilityTest_015, TestSize.Level1)
{
    std::unique_ptr<AceDataAbility> dataAbility = std::make_unique<AceDataAbility>();
    Want want;
    want.SetParam("url", std::string("asset/test.js"));
    if (dataAbility) {
        dataAbility->OnStart(want);
    }
}
}
