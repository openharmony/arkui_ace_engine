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
#include "core/components_ng/relaxed_interaction/base_executor.h"
#include "core/components_ng/relaxed_interaction/executors/scroll_touch_executor.h"
#include "core/components_ng/relaxed_interaction/executors/scroll_simulating_executor.h"
#include "core/components_ng/relaxed_interaction/parsers/scroll_command_parser.h"
#include "core/components_ng/relaxed_interaction/relaxed_interaction_types.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const std::string VALID_CLICK_AUTO_JSON = R"({
    "type": "scroll",
    "mode": "auto",
    "action_info": {
      "direction": "forward",
      "distance": 10.0,
      "coordinates": {
        "x1":100.0,
        "y1":200.0,
        "x2":300.0,
        "y2":300.0
      }
    }
  })";


const std::string VALID_CLICK_SIMULATING_JSON = R"({
    "type": "scroll",
    "mode": "simulating",
    "action_info": {
		"direction": "forward",
        "distance": 10.0,
        "coordinates": {
            "x1":150.0,
            "y1":250.0,
			"x2":300.0,
			"y2":300
        }
    }
})";

const std::string VALID_CLICK_TARGET_JSON = R"({
    "type": "scroll",
    "mode": "target",
    "action_info": {
		"direction": "forward",
        "distance": 10.0,
        "coordinates": {
            "x1":300.0,
            "y1":400.0,
			"x2":300.0,
			"y2":700
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

const std::string VALID_MODE_NUMBER_JSON = R"({
    "type": "scroll",
    "mode": 12.0,
    "action_info": {
        "coordinates": {
            "x1": 100.0,
            "y1": 200.0
        }
    }
})";

const std::string INVALID_NULL_JSON = R"({})";

const std::string INVALID_MISSING_ACTION_INFO_JSON = R"({
    "type": "scroll",
    "mode": "auto"
})";

const std::string INVALID_MISSING_COORDINATES_JSON = R"({
    "type": "scroll",
    "mode": "auto",
    "action_info": {}
})";

const std::string INVALID_MISSING_X1_Y1_JSON = R"({
    "type": "scroll",
    "mode": "auto",
    "action_info": {
        "coordinates": {}
    }
})";

const std::string INVALID_ONLY_X1_JSON = R"({
    "type": "scroll",
    "mode": "auto",
    "action_info": {
        "coordinates": {
            "x1": 100.0
        }
    }
})";

const std::string INVALID_ONLY_Y1_JSON = R"({
    "type": "scroll",
    "mode": "auto",
    "action_info": {
        "coordinates": {
            "y1": 200.0
        }
    }
})";
}

class ScrollCommandParserTest : public testing::Test {
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

class ScrollCommandParserConstructorTest : public ScrollCommandParserTest {};
class ScrollCommandParserParseTest : public ScrollCommandParserTest {};
class ScrollCommandParserParseModeTest : public ScrollCommandParserTest {};
class ScrollCommandParserParseCoordinatesTest : public ScrollCommandParserTest {};
class ScrollCommandParserCreateExecutorTest : public ScrollCommandParserTest {};

HWTEST_F(ScrollCommandParserConstructorTest, ScrollCommandParser_Constructor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    EXPECT_EQ(parser.context_, context);
}

HWTEST_F(ScrollCommandParserParseTest, Parse_ValidAutoMode_ReturnsTwoExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_AUTO_JSON);
    ASSERT_NE(json, nullptr);
    
    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 2);
    EXPECT_NE(executors[0], nullptr);
    EXPECT_NE(executors[1], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "scroll_touch");
    EXPECT_EQ(executors[1]->GetType(), "scroll_simulating");
}

HWTEST_F(ScrollCommandParserParseTest, Parse_ValidSimulatingMode_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_SIMULATING_JSON);
    ASSERT_NE(json, nullptr);
    
    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "scroll_simulating");
}

HWTEST_F(ScrollCommandParserParseTest, Parse_ValidTargetMode_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_TARGET_JSON);
    ASSERT_NE(json, nullptr);
    
    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "scroll_touch");
}

HWTEST_F(ScrollCommandParserParseTest, Parse_NullJson_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    std::unique_ptr<JsonValue> nullJson = nullptr;
    
    auto executors = parser.Parse(nullJson);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ScrollCommandParserParseTest, Parse_InvalidJson_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_NULL_JSON);
    ASSERT_NE(json, nullptr);
    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ScrollCommandParserParseTest, Parse_MissingActionInfo_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_ACTION_INFO_JSON);
    ASSERT_NE(json, nullptr);
    
    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ScrollCommandParserParseTest, Parse_MissingCoordinates_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_COORDINATES_JSON);
    ASSERT_NE(json, nullptr);
    
    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ScrollCommandParserParseTest, Parse_MissingX1Y1_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_X1_Y1_JSON);
    ASSERT_NE(json, nullptr);
    
    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ScrollCommandParserParseTest, Parse_OnlyX1_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_ONLY_X1_JSON);
    ASSERT_NE(json, nullptr);
    
    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ScrollCommandParserParseTest, Parse_OnlyY1_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_ONLY_Y1_JSON);
    ASSERT_NE(json, nullptr);
    
    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ScrollCommandParserParseModeTest, ParseMode_WithMode_ReturnsCorrectMode, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_AUTO_JSON);
    ASSERT_NE(json, nullptr);
    
    ExecuteMode mode = ExecuteMode::AUTO;
    parser.ParseMode(json.get(), mode);
    EXPECT_EQ(mode, ExecuteMode::AUTO);
}

HWTEST_F(ScrollCommandParserParseModeTest, ParseMode_WithoutMode_ReturnsTrue, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_DEFAULT_MODE_JSON);
    ASSERT_NE(json, nullptr);
    ExecuteMode mode = ExecuteMode::AUTO;
    EXPECT_TRUE(parser.ParseMode(json.get(), mode));
}

HWTEST_F(ScrollCommandParserParseModeTest, ParseMode_WithModeNumber_ReturnFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_MODE_NUMBER_JSON);
    ASSERT_NE(json, nullptr);
    ExecuteMode mode = ExecuteMode::AUTO;
    EXPECT_FALSE(parser.ParseMode(json.get(), mode));
}

HWTEST_F(ScrollCommandParserParseModeTest, ParseMode_WithoutMode_ReturnsDefault, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_DEFAULT_MODE_JSON);
    ASSERT_NE(json, nullptr);

    ExecuteMode mode = ExecuteMode::AUTO;
    parser.ParseMode(json.get(), mode);
    EXPECT_EQ(mode, ExecuteMode::AUTO);
}

HWTEST_F(ScrollCommandParserParseModeTest, ParseMode_SimulatingMode_ReturnsCorrectMode, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_SIMULATING_JSON);
    ASSERT_NE(json, nullptr);
    
    ExecuteMode mode = ExecuteMode::AUTO;
    parser.ParseMode(json.get(), mode);
    EXPECT_EQ(mode, ExecuteMode::SIMULATING);
}

HWTEST_F(ScrollCommandParserParseModeTest, ParseMode_TargetMode_ReturnsCorrectMode, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CLICK_TARGET_JSON);
    ASSERT_NE(json, nullptr);
    
    ExecuteMode mode = ExecuteMode::AUTO;
    parser.ParseMode(json.get(), mode);
    EXPECT_EQ(mode, ExecuteMode::TARGET);
}

HWTEST_F(ScrollCommandParserCreateExecutorTest, CreateExecutor_AutoMode_ReturnsTwoExecutors, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    Command tmpCmd;
    tmpCmd.type = "scroll";
    tmpCmd.mode = ExecuteMode::AUTO;
    tmpCmd.actionInfo.distance = 1200.0;
    tmpCmd.actionInfo.coordinates.x1 = 60.0;
    tmpCmd.actionInfo.coordinates.y1 = 60.0;
    tmpCmd.actionInfo.coordinates.x2 = 60.0;
    tmpCmd.actionInfo.coordinates.y2 = 700.0;
    tmpCmd.actionInfo.direction = RelaxedScrollDirection::FORWARD;

    auto executors = parser.CreateExecutor(tmpCmd);
    EXPECT_EQ(executors.size(), 2);
    EXPECT_EQ(executors[0]->GetType(), "scroll_touch");
    EXPECT_EQ(executors[1]->GetType(), "scroll_simulating");
}

HWTEST_F(ScrollCommandParserCreateExecutorTest, CreateExecutor_SimulatingMode_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    Command tmpCmd;
    tmpCmd.type = "scroll";
    tmpCmd.mode = ExecuteMode::SIMULATING;
    tmpCmd.actionInfo.distance = 1200.0;
    tmpCmd.actionInfo.coordinates.x1 = 60.0;
    tmpCmd.actionInfo.coordinates.y1 = 60.0;
    tmpCmd.actionInfo.coordinates.x2 = 60.0;
    tmpCmd.actionInfo.coordinates.y2 = 700.0;
    tmpCmd.actionInfo.direction = RelaxedScrollDirection::BACKWARD;
    
    auto executors = parser.CreateExecutor(tmpCmd);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_EQ(executors[0]->GetType(), "scroll_simulating");
}

HWTEST_F(ScrollCommandParserCreateExecutorTest, CreateExecutor_TargetMode_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    Command tmpCmd;
    tmpCmd.type = "scroll";
    tmpCmd.mode = ExecuteMode::TARGET;
    tmpCmd.actionInfo.distance = 1200.0;
    tmpCmd.actionInfo.coordinates.x1 = 60.0;
    tmpCmd.actionInfo.coordinates.y1 = 60.0;
    tmpCmd.actionInfo.coordinates.x2 = 60.0;
    tmpCmd.actionInfo.coordinates.y2 = 700.0;
    tmpCmd.actionInfo.direction = RelaxedScrollDirection::BACKWARD;
    
    auto executors = parser.CreateExecutor(tmpCmd);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_EQ(executors[0]->GetType(), "scroll_touch");
}

HWTEST_F(ScrollCommandParserCreateExecutorTest, CreateExecutor_UnknownMode_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    Command tmpCmd;
    tmpCmd.type = "scroll";
    tmpCmd.mode = ExecuteMode::TARGET;
    tmpCmd.actionInfo.distance = 1200.0;
    tmpCmd.actionInfo.coordinates.x1 = 60.0;
    tmpCmd.actionInfo.coordinates.y1 = 60.0;
    tmpCmd.actionInfo.coordinates.x2 = 60.0;
    tmpCmd.actionInfo.coordinates.y2 = 700.0;
    tmpCmd.actionInfo.direction = RelaxedScrollDirection::BACKWARD;
    
    auto executors = parser.CreateExecutor(tmpCmd);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_EQ(executors[0]->GetType(), "scroll_touch");
}

HWTEST_F(ScrollCommandParserParseModeTest, ParseDirection_AllDirections_Correct, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);

    RelaxedScrollDirection dir;

    auto json1 = JsonUtil::ParseJsonString(R"({
        "direction": "backward"
    })");
    ASSERT_TRUE(parser.ParseDirection(json1.get(), dir));
    EXPECT_EQ(dir, RelaxedScrollDirection::BACKWARD);

    auto json2 = JsonUtil::ParseJsonString(R"({
        "direction": "right"
    })");
    ASSERT_TRUE(parser.ParseDirection(json2.get(), dir));
    EXPECT_EQ(dir, RelaxedScrollDirection::RIGHT);

    auto json3 = JsonUtil::ParseJsonString(R"({
        "direction": "left"
    })");
    ASSERT_TRUE(parser.ParseDirection(json3.get(), dir));
    EXPECT_EQ(dir, RelaxedScrollDirection::LEFT);

    auto json4 = JsonUtil::ParseJsonString(R"({
        "direction": "up"
    })");
    ASSERT_TRUE(parser.ParseDirection(json4.get(), dir));
    EXPECT_EQ(dir, RelaxedScrollDirection::UP);

    auto json5 = JsonUtil::ParseJsonString(R"({
        "direction": "down"
    })");
    ASSERT_TRUE(parser.ParseDirection(json5.get(), dir));
    EXPECT_EQ(dir, RelaxedScrollDirection::DOWN);

    auto json6 = JsonUtil::ParseJsonString(R"({
        "direction": "forward"
    })");
    ASSERT_TRUE(parser.ParseDirection(json6.get(), dir));
    EXPECT_EQ(dir, RelaxedScrollDirection::FORWARD);
}

HWTEST_F(ScrollCommandParserParseTest, Parse_InvalidDirection_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "type": "scroll",
        "mode": "auto",
        "action_info": {
            "direction": "abc",
            "distance": 10.0,
            "coordinates": { "x1":100, "y1":200 }
        }
    })");
    ASSERT_NE(json, nullptr);
    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ScrollCommandParserParseTest, Parse_InvalidMode_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "type": "scroll",
        "mode": "abc",
        "action_info": {
            "direction": "up",
            "distance": 10.0,
            "coordinates": { "x1":100, "y1":200 }
        }
    })");
    ASSERT_NE(json, nullptr);
    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ScrollCommandParserParseTest, Parse_MissingDistance_UseDefault_OK, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "type": "scroll",
        "mode": "auto",
        "action_info": {
            "direction": "down",
            "coordinates": { "x1":100, "y1":200 }
        }
    })");
    ASSERT_NE(json, nullptr);
    auto executors = parser.Parse(json);
    EXPECT_FALSE(executors.empty());
}

HWTEST_F(ScrollCommandParserParseTest, Parse_DistanceNegative_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "type": "scroll",
        "mode": "auto",
        "action_info": {
            "direction": "up",
            "distance": -10,
            "coordinates": { "x1":100, "y1":200 }
        }
    })");
    ASSERT_NE(json, nullptr);
    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ScrollCommandParserParseTest, Parse_DistanceNotNumber_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "type": "scroll",
        "mode": "auto",
        "action_info": {
            "direction": "up",
            "distance": "abc",
            "coordinates": { "x1":100, "y1":200 }
        }
    })");
    ASSERT_NE(json, nullptr);
    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ScrollCommandParserParseTest, GetDefaultScrollDistance_Normal_ReturnsValidValue, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    float dist = parser.GetDefaultScrollDistance();
    EXPECT_LT(dist, 10000.0f);
}

HWTEST_F(ScrollCommandParserParseTest, ParseCmd_ValidFull_ReturnsTrue, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "mode": "auto",
        "action_info": {
            "direction": "up",
            "distance": 100,
            "coordinates": { "x1":10, "y1":20 }
        }
    })");
    Command cmd;
    bool ret = parser.ParseCmd(json.get(), cmd);
    EXPECT_TRUE(ret);
    EXPECT_EQ(cmd.mode, ExecuteMode::AUTO);
    EXPECT_EQ(cmd.actionInfo.direction, RelaxedScrollDirection::UP);
    EXPECT_EQ(cmd.actionInfo.distance, 100.0f);
}

HWTEST_F(ScrollCommandParserParseTest, ParseCmd_NoDistance_ReturnsTrue, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "mode": "auto",
        "action_info": {
            "direction": "up",
            "coordinates": { "x1":10, "y1":20 }
        }
    })");
    Command cmd;
    bool ret = parser.ParseCmd(json.get(), cmd);
    EXPECT_TRUE(ret);
    EXPECT_EQ(cmd.mode, ExecuteMode::AUTO);
    EXPECT_EQ(cmd.actionInfo.direction, RelaxedScrollDirection::UP);
}

HWTEST_F(ScrollCommandParserParseTest, ParseCmd_DistanceNegative_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "action_info": {
            "distance": -10,
            "coordinates": { "x1":10, "y1":20 }
        }
    })");
    Command cmd;
    bool ret = parser.ParseCmd(json.get(), cmd);
    EXPECT_FALSE(ret);
}

HWTEST_F(ScrollCommandParserParseTest, ParseCmd_Distance_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "action_info": {
            "distance": "abc",
            "coordinates": { "x1":10, "y1":20 }
        }
    })");
    Command cmd;
    bool ret = parser.ParseCmd(json.get(), cmd);
    EXPECT_FALSE(ret);
}

HWTEST_F(ScrollCommandParserParseTest, ParseCmd_Direction_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "action_info": {
            "distance": "abc",
            "direction": 10.0,
            "coordinates": { "x1":10, "y1":20 }
        }
    })");
    Command cmd;
    bool ret = parser.ParseCmd(json.get(), cmd);
    EXPECT_FALSE(ret);
}

HWTEST_F(ScrollCommandParserParseTest, ParseCmd_ActionInfo_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "actioninfos": {
            "distance": "abc",
            "coordinates": { "x1":10, "y1":20 }
        }
    })");
    Command cmd;
    bool ret = parser.ParseCmd(json.get(), cmd);
    EXPECT_FALSE(ret);
}

HWTEST_F(ScrollCommandParserParseTest, ParseCmd_MissingActionInfo_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({ "mode": "auto" })");
    Command cmd;
    bool ret = parser.ParseCmd(json.get(), cmd);
    EXPECT_FALSE(ret);
}

HWTEST_F(ScrollCommandParserParseTest, ParseCoordinates_ValidAll_ReturnsTrueAndSetsValues, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "action_info": {
            "coordinates": {
                "x1": 10,
                "y1": 20,
                "x2": 30,
                "y2": 40
            }
        }
    })");
    Command cmd;
    bool ret = parser.ParseCoordinates(json->GetValue("action_info").get(), cmd);
    EXPECT_TRUE(ret);
    EXPECT_EQ(cmd.actionInfo.coordinates.x1, 10);
    EXPECT_EQ(cmd.actionInfo.coordinates.y1, 20);
    EXPECT_EQ(cmd.actionInfo.coordinates.x2, 30);
    EXPECT_EQ(cmd.actionInfo.coordinates.y2, 40);
    EXPECT_TRUE(cmd.isY2Set);
}

HWTEST_F(ScrollCommandParserParseTest, ParseCoordinates_OnlyX1Y1_ReturnsTrueAndLogs, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "action_info": {
            "coordinates": {
                "x1": 10,
                "y1": 20
            }
        }
    })");
    Command cmd;
    bool ret = parser.ParseCoordinates(json->GetValue("action_info").get(), cmd);
    EXPECT_TRUE(ret);
    EXPECT_EQ(cmd.actionInfo.coordinates.x1, 10);
    EXPECT_EQ(cmd.actionInfo.coordinates.y1, 20);
    EXPECT_EQ(cmd.actionInfo.coordinates.x2, 0.0f);
    EXPECT_EQ(cmd.actionInfo.coordinates.y2, 0.0f);
    EXPECT_FALSE(cmd.isY2Set);
}

HWTEST_F(ScrollCommandParserParseTest, ParseCoordinates_MissingX1_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "action_info": {
            "coordinates": {
                "y1": 20
            }
        }
    })");
    Command cmd;
    bool ret = parser.ParseCoordinates(json->GetValue("action_info").get(), cmd);
    EXPECT_FALSE(ret);
}

HWTEST_F(ScrollCommandParserParseTest, ParseCoordinates_X1NotNumber_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({
        "action_info": {
            "coordinates": {
                "x1": "abc",
                "y1": 20
            }
        }
    })");
    Command cmd;
    bool ret = parser.ParseCoordinates(json->GetValue("action_info").get(), cmd);
    EXPECT_FALSE(ret);
}

HWTEST_F(ScrollCommandParserParseTest, ParseCoordinates_MissingObject_ReturnsFalse, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ScrollCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(R"({ "action_info": {} })");
    Command cmd;
    bool ret = parser.ParseCoordinates(json->GetValue("action_info").get(), cmd);
    EXPECT_FALSE(ret);
}
} // namespace OHOS::Ace::NG