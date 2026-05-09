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

#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/relaxed_interaction/parsers/backpress_command_parser.h"
#include "core/components_ng/relaxed_interaction/executors/backpress_executor.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const std::string VALID_BACKPRESS_JSON = R"({
    "type": "backpress"
})";

const std::string EMPTY_JSON = R"({})";

const std::string NULL_JSON_STR = "";
}

class BackpressCommandParserTest : public testing::Test {
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

class BackpressCommandParserConstructorTest : public BackpressCommandParserTest {};
class BackpressCommandParserParseTest : public BackpressCommandParserTest {};

HWTEST_F(BackpressCommandParserConstructorTest, BackpressCommandParser_Constructor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    BackpressCommandParser parser(context);
    EXPECT_EQ(parser.context_, context);
}

HWTEST_F(BackpressCommandParserConstructorTest, BackpressCommandParser_Constructor_WithNullContext, TestSize.Level1)
{
    WeakPtr<PipelineContext> nullContext;
    BackpressCommandParser parser(nullContext);
    EXPECT_EQ(parser.context_.Upgrade(), nullptr);
}

HWTEST_F(BackpressCommandParserConstructorTest, BackpressCommandParser_Constructor_WithValidContext, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    BackpressCommandParser parser(context);
    auto upgradedContext = parser.context_.Upgrade();
    EXPECT_NE(upgradedContext, nullptr);
    EXPECT_EQ(upgradedContext, mockPipelineContext_);
}

HWTEST_F(BackpressCommandParserParseTest, Parse_ValidJson_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    BackpressCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_BACKPRESS_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "backpress");
}

HWTEST_F(BackpressCommandParserParseTest, Parse_EmptyJson_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    BackpressCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(EMPTY_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "backpress");
}

HWTEST_F(BackpressCommandParserParseTest, Parse_NullJson_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    BackpressCommandParser parser(context);
    std::unique_ptr<JsonValue> nullJson = nullptr;

    auto executors = parser.Parse(nullJson);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "backpress");
}

HWTEST_F(BackpressCommandParserParseTest, Parse_InvalidJsonString_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    BackpressCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(NULL_JSON_STR);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
}

HWTEST_F(BackpressCommandParserParseTest, Parse_ComplexJson_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    BackpressCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "type": "backpress",
        "mode": "auto",
        "action_info": {
            "coordinates": {
                "x1": 100.0,
                "y1": 200.0
            }
        }
    })");
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "backpress");
}

HWTEST_F(BackpressCommandParserParseTest, Parse_ExecutorIsSingleStep, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    BackpressCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_BACKPRESS_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_TRUE(executors[0]->IsSingleStep());
}

HWTEST_F(BackpressCommandParserParseTest, Parse_ExecutorHasValidContext, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    BackpressCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_BACKPRESS_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
}

HWTEST_F(BackpressCommandParserParseTest, Parse_MultipleCalls_ReturnsSameResult, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    BackpressCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_BACKPRESS_JSON);
    ASSERT_NE(json, nullptr);

    auto executors1 = parser.Parse(json);
    auto executors2 = parser.Parse(json);
    EXPECT_EQ(executors1.size(), 1);
    EXPECT_EQ(executors2.size(), 1);
    EXPECT_EQ(executors1[0]->GetType(), "backpress");
    EXPECT_EQ(executors2[0]->GetType(), "backpress");
}

HWTEST_F(BackpressCommandParserParseTest, Parse_ExecutorDescription, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    BackpressCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_BACKPRESS_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    auto description = executors[0]->GetDescription();
    EXPECT_FALSE(description.empty());
}

} // namespace OHOS::Ace::NG