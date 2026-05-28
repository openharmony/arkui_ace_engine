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
#include "core/components_ng/relaxed_interaction/parsers/content_switch_command_parser.h"
#include "core/components_ng/relaxed_interaction/executors/strict_content_switch_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const std::string VALID_CONTENT_SWITCH_TARGET_JSON = R"({
    "type": "content_switch",
    "mode":"target",
    "action_info": {
      "direction": "forward",
      "count":1,
      "coordinates": {
        "pos": {
          "x":360.0,
          "y":640.0
        }
      }
    }
})";

const std::string VALID_CONTENT_SWITCH_DEFAULT_MODE_JSON = R"({
    "type": "content_switch",
    "mode":"target",
    "action_info": {
      "direction": "forward",
      "count":1,
      "coordinates": {
        "pos": {
          "x":100.0,
          "y":200.0
        }
      }
    }
})";

const std::string INVALID_NULL_JSON = R"({})";

const std::string INVALID_MISSING_ACTION_INFO_JSON = R"({
    "type": "content_switch",
    "mode":"target",
})";

const std::string INVALID_MISSING_COORDINATES_JSON = R"({
    "type": "content_switch",
    "mode":"target",
    "action_info": {}
})";

const std::string INVALID_MISSING_POS_JSON = R"({
    "type": "content_switch",
    "mode":"target",
    "action_info": {
        "coordinates": {
        }
    }
})";

const std::string INVALID_MISSING_X_Y_JSON = R"({
    "type": "content_switch",
    "mode":"target",
    "action_info": {
        "coordinates": {
            "pos": {
            }
        }
    }
})";

const std::string INVALID_ONLY_X_JSON = R"({
    "type": "content_switch",
    "mode":"target",
    "action_info": {
        "coordinates": {
            "pos": {
                "x": 100.0,
            }
        }
    }
})";

const std::string INVALID_ONLY_Y_JSON = R"({
    "type": "content_switch",
    "mode":"target",
    "action_info": {
        "coordinates": {
            "pos": {
                "y": 200.0,
            }
        }
    }
})";

const std::string INVALID_TYPE_JSON = R"({
    "type": 1,
    "mode":"target",
    "action_info": {
        "coordinates": {
            "pos": {
                "x": 100.0,
                "y": 200.0
            }
        }
    }
})";

const std::string INVALID_MODE_JSON = R"({
    "type": "content_switch",
    "mode":"auto",
    "action_info": {
        "coordinates": {
            "pos": {
                "x": 100.0,
                "y": 200.0
            }
        }
    }
})";

const std::string INVALID_MODE_TYPE_JSON = R"({
    "type": "content_switch",
    "mode":1,
    "action_info": {
        "coordinates": {
            "pos": {
                "x": 100.0,
                "y": 200.0
            }
        }
    }
})";

const std::string INVALID_DIRECTION_JSON = R"({
    "type": "content_switch",
    "mode": "target",
    "action_info": {
        "direction": "left",
        "coordinates": {
            "pos": {
                "x": 100.0,
                "y": 200.0
            }
        }
    }
})";

const std::string INVALID_DIRECTION_TYPE_JSON = R"({
    "type": "content_switch",
    "action_info": {
        "direction": 1,
        "coordinates": {
            "pos": {
                "x": 100.0,
                "y": 200.0
            }
        }
    }
})";

const std::string VALID_ZERO_COUNT_JSON = R"({
    "type": "content_switch",
    "action_info": {
        "count": 0,
        "coordinates": {
            "pos": {
                "x": 100.0,
                "y": 200.0
            }
        }
    }
})";

const std::string INVALID_NEGATIVE_COUNT_JSON = R"({
    "type": "content_switch",
    "action_info": {
        "count": -1,
        "coordinates": {
            "pos": {
                "x": 100.0,
                "y": 200.0
            }
        }
    }
})";

const std::string INVALID_COUNT_TYPE_JSON = R"({
    "type": "content_switch",
    "action_info": {
        "count": "1",
        "coordinates": {
            "pos": {
                "x": 100.0,
                "y": 200.0
            }
        }
    }
})";

const std::string VALID_COUNT_JSON = R"({
    "type": "content_switch",
    "action_info": {
        "count": 10,
        "coordinates": {
            "pos": {
                "x": 100.0,
                "y": 200.0
            }
        }
    }
})";

const std::string VALID_NEGATIVE_COORDINATES_JSON = R"({
    "type": "content_switch",
    "action_info": {
        "count": 1,
        "coordinates": {
            "pos": {
                "x": -100.0,
                "y": -200.0
            }
        }
    }
})";

const std::string INVALID_COORDINATES_TYPE_JSON = R"({
    "type": "content_switch",
    "action_info": {
        "count": 1,
        "coordinates": {
            "pos": {
                "x": "100.0",
                "y": 200.0
            }
        }
    }
})";
}

class ContentSwitchCommandParserTest : public testing::Test {
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

class ContentSwitchCommandParserParseTest : public ContentSwitchCommandParserTest {};

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_ValidTargetMode_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CONTENT_SWITCH_TARGET_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
    EXPECT_EQ(executors[0]->GetType(), "strict_content_switch");
    EXPECT_TRUE(executors[0]->IsSingleStep());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_DefaultMode_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_CONTENT_SWITCH_DEFAULT_MODE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
    EXPECT_NE(executors[0], nullptr);
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_NullJson_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    std::unique_ptr<JsonValue> nullJson = nullptr;

    auto executors = parser.Parse(nullJson);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_InvalidJson_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_NULL_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_MissingActionInfo_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_ACTION_INFO_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_MissingCoordinates_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_COORDINATES_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_MissingPos_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_POS_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_MissingXY_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MISSING_X_Y_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_OnlyX_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_ONLY_X_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_OnlyY_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_ONLY_Y_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_InvalidType_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_TYPE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_InvalidMode_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MODE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_InvalidModeType_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_MODE_TYPE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_InvalidDirection_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_DIRECTION_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_InvalidDirectionType_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_DIRECTION_TYPE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_ValidCountZero_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_ZERO_COUNT_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_NegativeCount_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_NEGATIVE_COUNT_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_ValidCount_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_COUNT_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_ValidNegativeCoordinates_ReturnsOneExecutor, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(VALID_NEGATIVE_COORDINATES_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_EQ(executors.size(), 1);
}

HWTEST_F(ContentSwitchCommandParserParseTest, Parse_InvalidCoordinateType_ReturnsEmpty, TestSize.Level1)
{
    auto context = WeakPtr<PipelineContext>(mockPipelineContext_);
    ContentSwitchCommandParser parser(context);
    auto json = JsonUtil::ParseJsonString(INVALID_COORDINATES_TYPE_JSON);
    ASSERT_NE(json, nullptr);

    auto executors = parser.Parse(json);
    EXPECT_TRUE(executors.empty());
}
} // namespace OHOS::Ace::NG