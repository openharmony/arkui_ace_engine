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

#include "base/json/json_util.h"
#include "core/components_ng/pattern/web/web_agent_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class WebAgentUtilsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebAgentUtilsTest::SetUpTestCase() {}

void WebAgentUtilsTest::TearDownTestCase() {}

void WebAgentUtilsTest::SetUp() {}

void WebAgentUtilsTest::TearDown() {}

/**
 * @tc.name: IsNumber_EmptyAndAllDigits
 * @tc.desc: Test IsNumber with empty string and all digits string.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, IsNumber_EmptyAndAllDigits, TestSize.Level0)
{
    EXPECT_FALSE(WebAgentUtils::IsNumber(""));
    EXPECT_TRUE(WebAgentUtils::IsNumber("123"));
    EXPECT_TRUE(WebAgentUtils::IsNumber("0"));
    EXPECT_TRUE(WebAgentUtils::IsNumber("456789"));
}

/**
 * @tc.name: IsNumber_ContainsNonDigit
 * @tc.desc: Test IsNumber with non-digit characters returns false.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, IsNumber_ContainsNonDigit, TestSize.Level0)
{
    EXPECT_FALSE(WebAgentUtils::IsNumber("12a3"));
    EXPECT_FALSE(WebAgentUtils::IsNumber("abc"));
    EXPECT_FALSE(WebAgentUtils::IsNumber("12.3"));
    EXPECT_FALSE(WebAgentUtils::IsNumber("-123"));
    EXPECT_FALSE(WebAgentUtils::IsNumber("123 "));
}

/**
 * @tc.name: ValidateHighlightResultJson_VariousInputs
 * @tc.desc: Test ValidateHighlightResultJson with various inputs.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, ValidateHighlightResultJson_VariousInputs, TestSize.Level0)
{
    auto result1 = WebAgentUtils::ValidateHighlightResultJson("");
    EXPECT_EQ(result1, nullptr);
    auto result2 = WebAgentUtils::ValidateHighlightResultJson("invalid json");
    EXPECT_EQ(result2, nullptr);
    auto result3 = WebAgentUtils::ValidateHighlightResultJson("[]");
    EXPECT_EQ(result3, nullptr);
    auto result4 = WebAgentUtils::ValidateHighlightResultJson(R"("[{\"type\":0}]")");
    ASSERT_NE(result4, nullptr);
    EXPECT_TRUE(result4->IsArray());
    EXPECT_GT(result4->GetArraySize(), 0);
}

/**
 * @tc.name: ParseHighlightErrorItem_EmptyObject
 * @tc.desc: Test ParseHighlightErrorItem with empty object.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, ParseHighlightErrorItem_EmptyObject, TestSize.Level0)
{
    auto item = JsonUtil::ParseJsonString("{}");
    ASSERT_NE(item, nullptr);
    auto result = WebAgentUtils::ParseHighlightErrorItem(item);
    EXPECT_EQ(result.type, WebAgentUtils::HighlightErrorType::UNKNOWN);
    EXPECT_EQ(result.index, -1);
    EXPECT_TRUE(result.content.empty());
    EXPECT_TRUE(result.message.empty());
}

/**
 * @tc.name: ParseHighlightErrorItem_ValidTypes
 * @tc.desc: Test ParseHighlightErrorItem with valid type values (0-4).
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, ParseHighlightErrorItem_ValidTypes, TestSize.Level0)
{
    auto item0 = JsonUtil::ParseJsonString(R"({"type":0})");
    ASSERT_NE(item0, nullptr);
    auto result0 = WebAgentUtils::ParseHighlightErrorItem(item0);
    EXPECT_EQ(result0.type, WebAgentUtils::HighlightErrorType::SUCCESS);

    auto item1 = JsonUtil::ParseJsonString(R"({"type":1})");
    ASSERT_NE(item1, nullptr);
    auto result1 = WebAgentUtils::ParseHighlightErrorItem(item1);
    EXPECT_EQ(result1.type, WebAgentUtils::HighlightErrorType::XPATH_ERROR);

    auto item2 = JsonUtil::ParseJsonString(R"({"type":2})");
    ASSERT_NE(item2, nullptr);
    auto result2 = WebAgentUtils::ParseHighlightErrorItem(item2);
    EXPECT_EQ(result2.type, WebAgentUtils::HighlightErrorType::NODE_NOT_FOUND);

    auto item3 = JsonUtil::ParseJsonString(R"({"type":3})");
    ASSERT_NE(item3, nullptr);
    auto result3 = WebAgentUtils::ParseHighlightErrorItem(item3);
    EXPECT_EQ(result3.type, WebAgentUtils::HighlightErrorType::TEXT_NOT_MATCH);

    auto item4 = JsonUtil::ParseJsonString(R"({"type":4})");
    ASSERT_NE(item4, nullptr);
    auto result4 = WebAgentUtils::ParseHighlightErrorItem(item4);
    EXPECT_EQ(result4.type, WebAgentUtils::HighlightErrorType::UNKNOWN);
}

/**
 * @tc.name: ParseHighlightErrorItem_InvalidType
 * @tc.desc: Test ParseHighlightErrorItem with invalid type value.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, ParseHighlightErrorItem_InvalidType, TestSize.Level0)
{
    auto item = JsonUtil::ParseJsonString(R"({"type":5})");
    ASSERT_NE(item, nullptr);
    auto result = WebAgentUtils::ParseHighlightErrorItem(item);
    EXPECT_EQ(result.type, WebAgentUtils::HighlightErrorType::UNKNOWN);
}

/**
 * @tc.name: ParseHighlightErrorItem_ValidIndex
 * @tc.desc: Test ParseHighlightErrorItem with valid index value.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, ParseHighlightErrorItem_ValidIndex, TestSize.Level0)
{
    auto item = JsonUtil::ParseJsonString(R"({"index":10})");
    ASSERT_NE(item, nullptr);
    auto result = WebAgentUtils::ParseHighlightErrorItem(item);
    EXPECT_EQ(result.index, 10);
}

/**
 * @tc.name: ParseHighlightErrorItem_InvalidIndex
 * @tc.desc: Test ParseHighlightErrorItem with invalid index value (string).
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, ParseHighlightErrorItem_InvalidIndex, TestSize.Level0)
{
    auto item = JsonUtil::ParseJsonString(R"({"index":"invalid"})");
    ASSERT_NE(item, nullptr);
    auto result = WebAgentUtils::ParseHighlightErrorItem(item);
    EXPECT_EQ(result.index, -1);
}

/**
 * @tc.name: ParseHighlightErrorItem_ValidContent
 * @tc.desc: Test ParseHighlightErrorItem with valid content value.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, ParseHighlightErrorItem_ValidContent, TestSize.Level0)
{
    auto item = JsonUtil::ParseJsonString(R"({"content":"test content"})");
    ASSERT_NE(item, nullptr);
    auto result = WebAgentUtils::ParseHighlightErrorItem(item);
    EXPECT_EQ(result.content, "test content");
}

/**
 * @tc.name: ParseHighlightErrorItem_ValidMessage
 * @tc.desc: Test ParseHighlightErrorItem with valid message value.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, ParseHighlightErrorItem_ValidMessage, TestSize.Level0)
{
    auto item = JsonUtil::ParseJsonString(R"({"message":"test message"})");
    ASSERT_NE(item, nullptr);
    auto result = WebAgentUtils::ParseHighlightErrorItem(item);
    EXPECT_EQ(result.message, "test message");
}

/**
 * @tc.name: ParseHighlightErrorItem_CompleteObject
 * @tc.desc: Test ParseHighlightErrorItem with complete object.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, ParseHighlightErrorItem_CompleteObject, TestSize.Level0)
{
    auto item = JsonUtil::ParseJsonString(R"({"type":1,"index":5,"content":"test","message":"error"})");
    ASSERT_NE(item, nullptr);
    auto result = WebAgentUtils::ParseHighlightErrorItem(item);
    EXPECT_EQ(result.type, WebAgentUtils::HighlightErrorType::XPATH_ERROR);
    EXPECT_EQ(result.index, 5);
    EXPECT_EQ(result.content, "test");
    EXPECT_EQ(result.message, "error");
}

/**
 * @tc.name: GetErrorNodeFromIndex_VariousCases
 * @tc.desc: Test GetErrorNodeFromIndex with various cases.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, GetErrorNodeFromIndex_VariousCases, TestSize.Level0)
{
    std::vector<std::string> Xpaths1 = {"/html/body/div[1]", "/html/body/div[2]"};
    auto result1 = WebAgentUtils::GetErrorNodeFromIndex(-1, Xpaths1);
    EXPECT_TRUE(result1.empty());
    std::vector<std::string> Xpaths2 = {"/html/body/div[1]", "/html/body/div[2]"};
    auto result2 = WebAgentUtils::GetErrorNodeFromIndex(10, Xpaths2);
    EXPECT_TRUE(result2.empty());
    std::vector<std::string> Xpaths3 = {"/html/body/div[1]", "/html/body/div[2]", "/html/body/div[3]"};
    auto result3 = WebAgentUtils::GetErrorNodeFromIndex(1, Xpaths3);
    EXPECT_EQ(result3, "/html/body/div[2]");
    std::vector<std::string> Xpaths4;
    auto result4 = WebAgentUtils::GetErrorNodeFromIndex(0, Xpaths4);
    EXPECT_TRUE(result4.empty());
}

/**
 * @tc.name: ConvertErrorTypeToString_AllTypes
 * @tc.desc: Test ConvertErrorTypeToString with all error types.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, ConvertErrorTypeToString_AllTypes, TestSize.Level0)
{
    auto result0 = WebAgentUtils::ConvertErrorTypeToString(WebAgentUtils::HighlightErrorType::SUCCESS);
    EXPECT_EQ(result0, "SUCCESS");

    auto result1 = WebAgentUtils::ConvertErrorTypeToString(WebAgentUtils::HighlightErrorType::XPATH_ERROR);
    EXPECT_EQ(result1, "XPATH_ERROR");

    auto result2 = WebAgentUtils::ConvertErrorTypeToString(WebAgentUtils::HighlightErrorType::NODE_NOT_FOUND);
    EXPECT_EQ(result2, "NODE_NOT_FOUND");

    auto result3 = WebAgentUtils::ConvertErrorTypeToString(WebAgentUtils::HighlightErrorType::TEXT_NOT_MATCH);
    EXPECT_EQ(result3, "TEXT_NOT_MATCH");

    auto result4 = WebAgentUtils::ConvertErrorTypeToString(WebAgentUtils::HighlightErrorType::UNKNOWN);
    EXPECT_EQ(result4, "UNKNOWN");
}

/**
 * @tc.name: ParseHighlightResult_VariousInputs
 * @tc.desc: Test ParseHighlightResult with various inputs.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, ParseHighlightResult_VariousInputs, TestSize.Level0)
{
    std::vector<std::string> Xpaths1;
    auto result1 = WebAgentUtils::ParseHighlightResult("invalid json", Xpaths1);
    EXPECT_FALSE(result1);
    std::vector<std::string> Xpaths2;
    auto result2 = WebAgentUtils::ParseHighlightResult("[]", Xpaths2);
    EXPECT_FALSE(result2);
    std::vector<std::string> Xpaths3 = {"/html/body/div[1]"};
    auto result3 = WebAgentUtils::ParseHighlightResult(R"("[{\"type\":0}]")", Xpaths3);
    EXPECT_TRUE(result3);
    std::vector<std::string> Xpaths4 = {"/html/body/div[1]"};
    auto result4 = WebAgentUtils::ParseHighlightResult(R"("[null, {\"type\":0}]")", Xpaths4);
    EXPECT_TRUE(result4);
    std::vector<std::string> Xpaths5 = {"/html/body/div[1]", "/html/body/div[2]"};
    auto result5 = WebAgentUtils::ParseHighlightResult(
        R"("[{\"type\":0,\"index\":0}, {\"type\":1,\"index\":1}]")", Xpaths5);
    EXPECT_TRUE(result5);
}

/**
 * @tc.name: IsValidHighlightErrorType_AllValues
 * @tc.desc: Test IsValidHighlightErrorType with valid and invalid values.
 * @tc.type: FUNC
 */
HWTEST_F(WebAgentUtilsTest, IsValidHighlightErrorType_AllValues, TestSize.Level0)
{
    EXPECT_TRUE(WebAgentUtils::IsValidHighlightErrorType(0));
    EXPECT_TRUE(WebAgentUtils::IsValidHighlightErrorType(1));
    EXPECT_TRUE(WebAgentUtils::IsValidHighlightErrorType(2));
    EXPECT_TRUE(WebAgentUtils::IsValidHighlightErrorType(3));
    EXPECT_TRUE(WebAgentUtils::IsValidHighlightErrorType(4));

    EXPECT_FALSE(WebAgentUtils::IsValidHighlightErrorType(-1));
    EXPECT_FALSE(WebAgentUtils::IsValidHighlightErrorType(5));
    EXPECT_FALSE(WebAgentUtils::IsValidHighlightErrorType(100));
}

} // namespace OHOS::Ace::NG
