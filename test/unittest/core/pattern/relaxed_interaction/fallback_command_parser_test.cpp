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

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/relaxed_interaction/parsers/fallback_command_parser.h"
#include "core/components_ng/relaxed_interaction/executors/fallback_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const std::string VALID_FALLBACK_RADIO1_TRUE_JSON = R"({
    "identity": 69,
    "body": {
        "cmd": "checked",
        "params": {
            "value": true
        }
    }
})";

const std::string VALID_FALLBACK_RADIO1_FALSE_JSON = R"({
    "identity": 69,
    "body": {
        "cmd": "checked",
        "params": {
            "value": false
        }
    }
})";

const std::string VALID_FALLBACK_RADIO2_TRUE_JSON = R"({
    "identity": 70,
    "body": {
        "cmd": "checked",
        "params": {
            "value": true
        }
    }
})";

const std::string VALID_FALLBACK_RADIO2_FALSE_JSON = R"({
    "identity": 70,
    "body": {
        "cmd": "checked",
        "params": {
            "value": false
        }
    }
})";

const std::string INVALID_NULL_JSON = R"({})";

const std::string INVALID_IDENTITY_NULL_JSON = R"({
    "identity": null
})";

const std::string INVALID_IDENTITY_JSON = R"({
    "identity": -1,
})";

const std::string INVALID_IDENTITY_STRING_JSON = R"({
    "identity": "Radio1",
})";

const std::string INVALID_MISSING_BODY_JSON = R"({
    "identity": 70,
})";

const std::string INVALID_MISSING_IDENTITY_JSON = R"({
    "body": {
        "cmd": "checked",
        "params": {
            "value": true,
        }
    }
})";

const std::string INVALID_MISSING_BODY_INFO_JSON = R"({
    "identity": 70,
})";

const std::string INVALID_BODY_NULL_JSON = R"({
    "body": null
})";

const std::string INVALID_BODY_OBJECT_JSON = R"({
    "body": "hello"
})";

const std::string INVALID_ONLY_CMD_JSON = R"({})";
}

class FallbackCommandParserTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        mockPipelineContext_ = AceType::MakeRefPtr<MockPipelineContext>();
        ASSERT_NE(mockPipelineContext_, nullptr);
    }

    static void TearDownTestCase()
    {
        mockPipelineContext_.Reset();
    }

protected:
    inline static RefPtr<MockPipelineContext> mockPipelineContext_ = nullptr;
};

class FallbackCommandParserConstructorTest : public FallbackCommandParserTest {};
class FallbackCommandParserParseTest : public FallbackCommandParserTest {};
class FallbackCommandParserParseModeTest : public FallbackCommandParserTest {};
class FallbackCommandParserParseCoordinatesTest : public FallbackCommandParserTest {};
class FallbackCommandParserCreateExecutorTest : public FallbackCommandParserTest {};

HWTEST_F(FallbackCommandParserConstructorTest, FallbackCommandParser_Constructor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    EXPECT_EQ(parser.context_, context);
}

HWTEST_F(FallbackCommandParserParseTest, Parse_ValidRadio1True_ReturnsExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_FALLBACK_RADIO1_TRUE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "fallback");
    EXPECT_TRUE(executors[0]->IsSingleStep());
}

HWTEST_F(FallbackCommandParserParseTest, Parse_ValidRadio1False_ReturnsExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_FALLBACK_RADIO1_FALSE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
}

HWTEST_F(FallbackCommandParserParseTest, Parse_ValidRadio2True_ReturnsExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_FALLBACK_RADIO2_TRUE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
}

HWTEST_F(FallbackCommandParserParseTest, Parse_ValidRadio2False_ReturnsExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_FALLBACK_RADIO2_FALSE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
}

HWTEST_F(FallbackCommandParserParseTest, Parse_NullJson_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    std::unique_ptr<JsonValue> nullJson = nullptr;

    auto executors = parser.Parse(nullJson);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(FallbackCommandParserParseTest, Parse_InvalidJson_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_NULL_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(FallbackCommandParserParseTest, Parse_MissingBody_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_BODY_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(FallbackCommandParserParseTest, Parse_MissingIdentity_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_IDENTITY_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(FallbackCommandParserParseTest, Parse_MissingBodyInfo_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_BODY_INFO_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(FallbackCommandParserParseTest, Parse_OnlyCmd_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_ONLY_CMD_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(FallbackCommandParserParseTest, Parse_NullBody_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_BODY_NULL_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(FallbackCommandParserParseTest, Parse_BodyObject_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_BODY_OBJECT_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(FallbackCommandParserParseTest, Parse_NullIdentity_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_IDENTITY_NULL_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(FallbackCommandParserParseTest, Parse_InvalidIdentity_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_IDENTITY_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(FallbackCommandParserParseTest, Parse_InvalidIdentityString_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    FallbackCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_IDENTITY_STRING_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

} // namespace OHOS::Ace::NG