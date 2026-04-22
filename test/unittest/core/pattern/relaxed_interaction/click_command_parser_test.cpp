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
#include "core/components_ng/relaxed_interaction/parsers/click_command_parser.h"
#include "core/components_ng/relaxed_interaction/executors/strict_click_executor.h"
#include "core/components_ng/relaxed_interaction/executors/simulate_touch_executor.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const std::string VALID_CLICK_AUTO_JSON = R"({
    "type": "click",
    "mode": "auto",
    "action_info": {
        "coordinates": {
            "x1": 100.0,
            "y1": 200.0
        }
    }
})";

const std::string VALID_CLICK_SIMULATING_JSON = R"({
    "type": "click",
    "mode": "simulating",
    "action_info": {
        "coordinates": {
            "x1": 150.0,
            "y1": 250.0
        }
    }
})";

const std::string VALID_CLICK_TARGET_JSON = R"({
    "type": "click",
    "mode": "target",
    "action_info": {
        "coordinates": {
            "x1": 300.0,
            "y1": 400.0
        }
    }
})";

const std::string VALID_CLICK_DEFAULT_MODE_JSON = R"({
    "type": "click",
    "action_info": {
        "coordinates": {
            "x1": 100.0,
            "y1": 200.0
        }
    }
})";

const std::string INVALID_NULL_JSON = R"({})";

const std::string INVALID_MISSING_ACTION_INFO_JSON = R"({
    "type": "click",
    "mode": "auto"
})";

const std::string INVALID_MISSING_COORDINATES_JSON = R"({
    "type": "click",
    "mode": "auto",
    "action_info": {}
})";

const std::string INVALID_MISSING_X1_Y1_JSON = R"({
    "type": "click",
    "mode": "auto",
    "action_info": {
        "coordinates": {}
    }
})";

const std::string INVALID_ONLY_X1_JSON = R"({
    "type": "click",
    "mode": "auto",
    "action_info": {
        "coordinates": {
            "x1": 100.0
        }
    }
})";

const std::string INVALID_ONLY_Y1_JSON = R"({
    "type": "click",
    "mode": "auto",
    "action_info": {
        "coordinates": {
            "y1": 200.0
        }
    }
})";

const std::string INVALID_X1_NOT_NUMBER_JSON = R"({
    "type": "click",
    "mode": "auto",
    "action_info": {
        "coordinates": {
            "x1": "abc",
            "y1": 200.0
        }
    }
})";

const std::string INVALID_Y1_NOT_NUMBER_JSON = R"({
    "type": "click",
    "mode": "auto",
    "action_info": {
        "coordinates": {
            "x1": 100.0,
            "y1": "xyz"
        }
    }
})";

const std::string INVALID_MODE_JSON = R"({
    "type": "click",
    "mode": "invalid_mode",
    "action_info": {
        "coordinates": {
            "x1": 100.0,
            "y1": 200.0
        }
    }
})";

const std::string INVALID_MODE_EMPTY_STRING_JSON = R"({
    "type": "click",
    "mode": "",
    "action_info": {
        "coordinates": {
            "x1": 100.0,
            "y1": 200.0
        }
    }
})";
}

class ClickCommandParserTest : public testing::Test {
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

class ClickCommandParserConstructorTest : public ClickCommandParserTest {};
class ClickCommandParserParseTest : public ClickCommandParserTest {};
class ClickCommandParserParseModeTest : public ClickCommandParserTest {};
class ClickCommandParserParseCoordinatesTest : public ClickCommandParserTest {};
class ClickCommandParserCreateExecutorTest : public ClickCommandParserTest {};

HWTEST_F(ClickCommandParserConstructorTest, ClickCommandParser_Constructor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    EXPECT_EQ(parser.context_, context);
}

HWTEST_F(ClickCommandParserParseTest, Parse_ValidAutoMode_ReturnsTwoExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_AUTO_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 2);
    EXPECT_NE(executors[0], nullptr);
    EXPECT_NE(executors[1], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "strict_click");
    EXPECT_EQ(executors[1]->GetType(), "simulate_touch");
}

HWTEST_F(ClickCommandParserParseTest, Parse_ValidSimulatingMode_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_SIMULATING_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "simulate_touch");
}

HWTEST_F(ClickCommandParserParseTest, Parse_ValidTargetMode_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_TARGET_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "strict_click");
}

HWTEST_F(ClickCommandParserParseTest, Parse_DefaultMode_ReturnsTwoExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_DEFAULT_MODE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 2);
    EXPECT_NE(executors[0], nullptr);
    EXPECT_NE(executors[1], nullptr);
}

HWTEST_F(ClickCommandParserParseTest, Parse_NullJson_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    std::unique_ptr<JsonValue> nullJson = nullptr;

    auto executors = parser.Parse(nullJson);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ClickCommandParserParseTest, Parse_InvalidJson_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_NULL_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ClickCommandParserParseTest, Parse_MissingActionInfo_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_ACTION_INFO_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ClickCommandParserParseTest, Parse_MissingCoordinates_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_COORDINATES_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ClickCommandParserParseTest, Parse_MissingX1Y1_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_X1_Y1_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ClickCommandParserParseTest, Parse_OnlyX1_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_ONLY_X1_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ClickCommandParserParseTest, Parse_OnlyY1_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_ONLY_Y1_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ClickCommandParserParseTest, Parse_InvalidMode_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MODE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ClickCommandParserParseTest, Parse_X1NotNumber_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_X1_NOT_NUMBER_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ClickCommandParserParseTest, Parse_Y1NotNumber_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_Y1_NOT_NUMBER_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ClickCommandParserParseModeTest, ParseMode_WithAutoMode_ReturnsTrue, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_AUTO_JSON);
    ASSERT_NE(json, nullptr);

    ExecuteMode mode;
    EXPECT_TRUE(parser.ParseMode(json.get(), mode));
    EXPECT_EQ(mode, ExecuteMode::AUTO);
}

HWTEST_F(ClickCommandParserParseModeTest, ParseMode_WithoutMode_ReturnsTrue, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_DEFAULT_MODE_JSON);
    ASSERT_NE(json, nullptr);

    ExecuteMode mode;
    EXPECT_TRUE(parser.ParseMode(json.get(), mode));
    EXPECT_EQ(mode, ExecuteMode::AUTO);
}

HWTEST_F(ClickCommandParserParseModeTest, ParseMode_SimulatingMode_ReturnsTrue, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_SIMULATING_JSON);
    ASSERT_NE(json, nullptr);

    ExecuteMode mode;
    EXPECT_TRUE(parser.ParseMode(json.get(), mode));
    EXPECT_EQ(mode, ExecuteMode::SIMULATING);
}

HWTEST_F(ClickCommandParserParseModeTest, ParseMode_TargetMode_ReturnsTrue, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_TARGET_JSON);
    ASSERT_NE(json, nullptr);

    ExecuteMode mode;
    EXPECT_TRUE(parser.ParseMode(json.get(), mode));
    EXPECT_EQ(mode, ExecuteMode::TARGET);
}

HWTEST_F(ClickCommandParserParseModeTest, ParseMode_InvalidMode_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MODE_JSON);
    ASSERT_NE(json, nullptr);

    ExecuteMode mode;
    EXPECT_FALSE(parser.ParseMode(json.get(), mode));
}

HWTEST_F(ClickCommandParserParseModeTest, ParseMode_EmptyMode_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MODE_EMPTY_STRING_JSON);
    ASSERT_NE(json, nullptr);

    ExecuteMode mode;
    EXPECT_FALSE(parser.ParseMode(json.get(), mode));
}

HWTEST_F(ClickCommandParserParseCoordinatesTest, ParseCoordinates_ValidCoordinates_ReturnsTrue, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_AUTO_JSON);
    ASSERT_NE(json, nullptr);

    PointF coordinates(0.0f, 0.0f);
    auto result = parser.ParseCoordinates(json.get(), coordinates);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(coordinates.GetX(), 100.0f);
    EXPECT_FLOAT_EQ(coordinates.GetY(), 200.0f);
}

HWTEST_F(ClickCommandParserParseCoordinatesTest, ParseCoordinates_MissingActionInfo_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_ACTION_INFO_JSON);
    ASSERT_NE(json, nullptr);

    PointF coordinates(0.0f, 0.0f);
    auto result = parser.ParseCoordinates(json.get(), coordinates);
    EXPECT_FALSE(result);
}

HWTEST_F(ClickCommandParserParseCoordinatesTest, ParseCoordinates_MissingCoordinates_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_COORDINATES_JSON);
    ASSERT_NE(json, nullptr);

    PointF coordinates(0.0f, 0.0f);
    auto result = parser.ParseCoordinates(json.get(), coordinates);
    EXPECT_FALSE(result);
}

HWTEST_F(ClickCommandParserParseCoordinatesTest, ParseCoordinates_MissingX1Y1_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_X1_Y1_JSON);
    ASSERT_NE(json, nullptr);

    PointF coordinates(0.0f, 0.0f);
    auto result = parser.ParseCoordinates(json.get(), coordinates);
    EXPECT_FALSE(result);
}

HWTEST_F(ClickCommandParserParseCoordinatesTest, ParseCoordinates_X1NotNumber_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_X1_NOT_NUMBER_JSON);
    ASSERT_NE(json, nullptr);

    PointF coordinates(0.0f, 0.0f);
    auto result = parser.ParseCoordinates(json.get(), coordinates);
    EXPECT_FALSE(result);
}

HWTEST_F(ClickCommandParserParseCoordinatesTest, ParseCoordinates_Y1NotNumber_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_Y1_NOT_NUMBER_JSON);
    ASSERT_NE(json, nullptr);

    PointF coordinates(0.0f, 0.0f);
    auto result = parser.ParseCoordinates(json.get(), coordinates);
    EXPECT_FALSE(result);
}

HWTEST_F(ClickCommandParserCreateExecutorTest, CreateExecutor_AutoMode_ReturnsTwoExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    PointF coordinates(100.0f, 200.0f);

    auto executors = parser.CreateExecutor(ExecuteMode::AUTO, coordinates);
    EXPECT_EQ(executors.size(), 2);
    EXPECT_EQ(executors[0]->GetType(), "strict_click");
    EXPECT_EQ(executors[1]->GetType(), "simulate_touch");
}

HWTEST_F(ClickCommandParserCreateExecutorTest, CreateExecutor_SimulatingMode_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    PointF coordinates(150.0f, 250.0f);

    auto executors = parser.CreateExecutor(ExecuteMode::SIMULATING, coordinates);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_EQ(executors[0]->GetType(), "simulate_touch");
}

HWTEST_F(ClickCommandParserCreateExecutorTest, CreateExecutor_TargetMode_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ClickCommandParser parser(context);
    PointF coordinates(300.0f, 400.0f);

    auto executors = parser.CreateExecutor(ExecuteMode::TARGET, coordinates);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_EQ(executors[0]->GetType(), "strict_click");
}

} // namespace OHOS::Ace::NG
