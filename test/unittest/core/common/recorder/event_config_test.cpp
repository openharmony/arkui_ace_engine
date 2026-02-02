/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <optional>

#include "gtest/gtest.h"
#define private public
#define protected public
#include "interfaces/inner_api/ace/ui_event_observer.h"

#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/recorder/event_config.h"
#include "core/common/recorder/event_controller.h"
#include "core/common/recorder/event_definition.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/exposure_processor.h"
#include "core/common/recorder/inspector_tree_collector.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components_ng/base/simplified_inspector.h"
#include "core/components_ng/pattern/stage/page_info.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Recorder;

namespace OHOS::Ace {
namespace {
constexpr int SWITCHES_SIZE = 10;
const char* const SET_CONFIG_SWITCH =
    "{\"enable\":false,\"switch\":{\"page\":true,\"component\":true,\"exposure\":true},\"x\":[{\"pageUrl\":"
    "\"pages/"
    "Index\",\"shareNode\":[\"hahaha\",\"btn_TitleExpand\",\"btn_OpenSelf\",\"btn_Screenshot\",\"btn_inspect\","
    "\"btn_xxx\",\"\"],\"exposureCfg\":[{\"id\":\"btn_Grid\",\"ratio\":0.75,\"duration\":5000},{\"id\":\"btn_"
    "TitleExpand\",\"ratio\":0.9,\"duration\":1000}]},{\"pageUrl\":\"pages/"
    "ScrollPage\",\"shareNode\":[\"scroll_item_1\"],\"exposureCfg\":[{\"id\":\"scroll_item_2\",\"ratio\":0.85,"
    "\"duration\":5000},{\"id\":\"scroll_item_12\",\"ratio\":0.4,\"duration\":3000}]}]}";
const char* const SET_CONFIG_WITHOUT_SWITCH =
    "{\"enable\":true,\"globalSwitch\":{\"page\":true,\"component\":true,\"exposure\":true},\"config\":[{"
    "\"pageUrl\":"
    "\"pages/"
    "Index\",\"shareNode\":[\"hahaha\",\"btn_TitleExpand\",\"btn_OpenSelf\",\"btn_Screenshot\",\"btn_inspect\","
    "\"btn_xxx\",\"\"],\"exposureCfg\":[{\"id\":\"btn_Grid\",\"ratio\":0.75,\"duration\":5000},{\"id\":\"btn_"
    "TitleExpand\",\"ratio\":0.9,\"duration\":1000}]},{\"pageUrl\":\"pages/"
    "ScrollPage\",\"shareNode\":[\"scroll_item_1\"],\"exposureCfg\":[{\"id\":\"scroll_item_2\",\"ratio\":0.85,"
    "\"duration\":5000},{\"id\":\"scroll_item_12\",\"ratio\":0.4,\"duration\":3000}]}]}";
const char* const SET_CONFIG_WITH_GLOBAL_SWITCH =
    "{\"enable\":true,\"switch\":{\"page\":true,\"component\":true,\"exposure\":true,\"pageParam\":true,"
    "\"scroll\":true,\"animation\":true,\"rect\":true,\"web\":true,\"textInput\":true,\"clickGesture\":true},"
    "\"webCategory\":\"test\",\"webIdentifier\":\"abc\",\"webActionJs\":\"hello\"}";
const char* const SET_CONFIG_IS_NOT_STRING =
    "{\"enable\":true,\"globalSwitch\":{\"page\":true,\"component\":true,\"exposure\":true},\"config\":[{"
    "\"pageUrl\":"
    "\"pages/"
    "Index\",\"exposureCfg\":[{\"id\":\"btn_Grid\",\"ratio\":0.75,\"duration\":5000},{\"id\":\"btn_"
    "TitleExpand\",\"ratio\":0.9,\"duration\":1000}]},{\"pageUrl\":\"pages/"
    "ScrollPage\",\"shareNode\":[\"1\", [{\"id\":\"btn_Grid\"}]],\"exposureCfg\":[{\"id\":\"scroll_item_2\","
    "\"ratio\":0.85,\"duration\":5000},{\"id\":\"scroll_item_12\",\"ratio\":0.4,\"duration\":3000}]}]}";
const char* const SET_CONFIG_EXPROSE_CFG =
    "{\"enable\":true,\"globalSwitch\":{\"page\":true,\"component\":true,\"exposure\":true},\"config\":[{"
    "\"pageUrl\":"
    "\"pages/"
    "Index\",\"shareNode\":[\"hahaha\",\"btn_TitleExpand\",\"btn_OpenSelf\",\"btn_Screenshot\",\"btn_inspect\","
    "\"btn_xxx\",\"\"],\"exposureCfg\":[{\"id\":\"btn_Grid\",\"ratio\":0.75,\"duration\":5000},{\"id\":\"btn_"
    "TitleExpand\",\"ratio\":0.9,\"duration\":1000}]},{\"pageUrl\":\"pages/"
    "ScrollPage\",\"shareNode\":[\"scroll_item_1\"],\"exposureCfg\":[{\"id\":\"scroll_item_2\",\"ratio\":0.85,"
    "\"duration\":5000},{\"id\":\"scroll_item_12\",\"ratio\":0.4,\"duration\":3000},1]}]}";

const char* const SET_CONFIG_EXPROSE_CFG_NO_ID =
    "{\"enable\":true,\"globalSwitch\":{\"page\":true,\"component\":true,\"exposure\":true},\"config\":[{"
    "\"pageUrl\":"
    "\"pages/"
    "Index\",\"shareNode\":[\"hahaha\",\"btn_TitleExpand\",\"btn_OpenSelf\",\"btn_Screenshot\",\"btn_inspect\","
    "\"btn_xxx\",\"\"],\"exposureCfg\":[{\"id\":\"btn_Grid\",\"ratio\":0.75,\"duration\":5000},{\"id\":\"btn_"
    "TitleExpand\",\"ratio\":0.9,\"duration\":1000}]},{\"pageUrl\":\"pages/"
    "ScrollPage\",\"shareNode\":[\"scroll_item_1\"],\"exposureCfg\":[{\"id\":\"\",\"ratio\":0.85,"
    "\"duration\":5000},{\"id\":\"scroll_item_12\",\"ratio\":0.4,\"duration\":3000}]}]}";

const char* const SET_CONFIG_EXPROSE_CFG_DURATION =
    "{\"enable\":true,\"globalSwitch\":{\"page\":true,\"component\":true,\"exposure\":true},\"config\":[{"
    "\"pageUrl\":"
    "\"pages/"
    "Index\",\"shareNode\":[\"hahaha\",\"btn_TitleExpand\",\"btn_OpenSelf\",\"btn_Screenshot\",\"btn_inspect\","
    "\"btn_xxx\",\"\"],\"exposureCfg\":[{\"id\":\"btn_Grid\",\"ratio\":0.75,\"duration\":5000},{\"id\":\"btn_"
    "TitleExpand\",\"ratio\":0.9,\"duration\":1000}]},{\"pageUrl\":\"pages/"
    "ScrollPage\",\"shareNode\":[\"scroll_item_1\"],\"exposureCfg\":[{\"id\":\"\",\"ratio\":0.85,"
    "\"duration\":-5000},{\"id\":\"scroll_item_12\",\"ratio\":0.4,\"duration\":3000}]}]}";
} // namespace

class EventConfigTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: ParseSwitch001
 * @tc.desc: Test ParseSwitch.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, ParseSwitch001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get EventConfig.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string str = std::string(SET_CONFIG_SWITCH);
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with switch settings.
     * @tc.expected: Configuration string is not empty after initialization.
     */
    config->Init(str);
    EXPECT_EQ(str, std::string(SET_CONFIG_SWITCH));
    delete config;
}

/**
 * @tc.name: ParseSwitch002
 * @tc.desc: Test ParseSwitch.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, ParseSwitch002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare configuration without switch settings.
     * @tc.expected: EventConfig object is created successfully.
     */

    std::string str = std::string(SET_CONFIG_WITHOUT_SWITCH);
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config without switch settings.
     * @tc.expected: Configuration string is not empty after initialization.
     */
    config->Init(str);
    EXPECT_EQ(str, std::string(SET_CONFIG_WITHOUT_SWITCH));
    delete config;
}

/**
 * @tc.name: ParseSwitch003
 * @tc.desc: Test ParseSwitch.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, ParseSwitch003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare configuration with global switch settings.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string str = std::string(SET_CONFIG_WITH_GLOBAL_SWITCH);
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with global switch settings.
     * @tc.expected: Configuration string is not empty after initialization.
     */
    config->Init(str);
    EXPECT_EQ(str, std::string(SET_CONFIG_WITH_GLOBAL_SWITCH));
    delete config;
}

/**
 * @tc.name: ParseSwitch004
 * @tc.desc: Test ParseSwitch.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, ParseSwitch004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare configuration with invalid data format.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string str = std::string(SET_CONFIG_IS_NOT_STRING);
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with invalid data format.
     * @tc.expected: Configuration string is not empty after initialization.
     */
    config->Init(str);
    EXPECT_EQ(str, std::string(SET_CONFIG_IS_NOT_STRING));
    delete config;
}

/**
 * @tc.name: ParseExposureCfg001
 * @tc.desc: Test ParseSwitch.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, ParseExposureCfg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare configuration with exposure settings.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string str = std::string(SET_CONFIG_EXPROSE_CFG);
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with exposure settings.
     * @tc.expected: Configuration string is not empty after initialization.
     */
    config->Init(str);
    EXPECT_EQ(str, std::string(SET_CONFIG_EXPROSE_CFG));
    delete config;
}

/**
 * @tc.name: ParseExposureCfg002
 * @tc.desc: Test ParseSwitch.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, ParseExposureCfg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare configuration with exposure settings but missing ID.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string str = std::string(SET_CONFIG_EXPROSE_CFG_NO_ID);
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with exposure settings but missing ID.
     * @tc.expected: Configuration string is not empty after initialization.
     */
    config->Init(str);
    EXPECT_EQ(str, std::string(SET_CONFIG_EXPROSE_CFG_NO_ID));
    delete config;
}

/**
 * @tc.name: ParseExposureCfg003
 * @tc.desc: Test ParseSwitch.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, ParseExposureCfg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare configuration with exposure settings and invalid duration.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string str = std::string(SET_CONFIG_EXPROSE_CFG_DURATION);
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with exposure settings and invalid duration.
     * @tc.expected: Configuration string is not empty after initialization.
     */
    config->Init(str);
    EXPECT_EQ(str, std::string(SET_CONFIG_EXPROSE_CFG_DURATION));
    delete config;
}

/**
 * @tc.name: IsCategoryEnable001
 * @tc.desc: Test IsCategoryEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, IsCategoryEnable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventConfig and set up switches with alternating true/false values.
     * @tc.expected: EventConfig object is created successfully.
     */
    int32_t index = -1;
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);
    for (int i = 0; i < SWITCHES_SIZE; i++) {
        if (i % 2 == 0) {
            config->switches_[i] = true;
        } else {
            config->switches_[i] = false;
        }
    }

    /**
     * @tc.steps: step2. Test IsCategoryEnable with negative index.
     * @tc.expected: Function should return false for negative index.
     */
    auto result = config->IsCategoryEnable(index);
    EXPECT_FALSE(result);
    delete config;
}

/**
 * @tc.name: IsCategoryEnable002
 * @tc.desc: Test IsCategoryEnable.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, IsCategoryEnable002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventConfig and set up switches with alternating true/false values.
     * @tc.expected: EventConfig object is created successfully.
     */
    int32_t index = SWITCHES_SIZE + 2;
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);
    for (int i = 0; i < SWITCHES_SIZE; i++) {
        if (i % 2 == 0) {
            config->switches_[i] = true;
        } else {
            config->switches_[i] = false;
        }
    }

    /**
     * @tc.steps: step2. Test IsCategoryEnable with out of bounds index.
     * @tc.expected: Function should return false for out of bounds index.
     */
    auto result = config->IsCategoryEnable(index);
    EXPECT_FALSE(result);
    delete config;
}

/**
 * @tc.name: IsCategoryEnable003
 * @tc.desc: Test IsCategoryEnable with valid indices.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, IsCategoryEnable003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventConfig and set specific switches.
     * @tc.expected: EventConfig object is created successfully.
     */
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    // Set switches[0] = true, switches[1] = false
    config->switches_[0] = true;
    config->switches_[1] = false;

    /**
     * @tc.steps: step2. Test IsCategoryEnable with index 0.
     * @tc.expected: Should return true.
     */
    EXPECT_TRUE(config->IsCategoryEnable(0));

    /**
     * @tc.steps: step3. Test IsCategoryEnable with index 1.
     * @tc.expected: Should return false.
     */
    EXPECT_FALSE(config->IsCategoryEnable(1));
    delete config;
}

/**
 * @tc.name: InitWithInvalidJson001
 * @tc.desc: Test Init with invalid JSON string.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, InitWithInvalidJson001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare invalid JSON string.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string invalidJson = "{invalid json}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with invalid JSON.
     * @tc.expected: Config should not crash, enable should be false.
     */
    config->Init(invalidJson);
    EXPECT_FALSE(config->IsEnable());
    delete config;
}

/**
 * @tc.name: InitWithInvalidJson002
 * @tc.desc: Test Init with empty string.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, InitWithInvalidJson002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare empty JSON string.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string emptyJson = "";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with empty string.
     * @tc.expected: Config should not crash, enable should be false.
     */
    config->Init(emptyJson);
    EXPECT_FALSE(config->IsEnable());
    delete config;
}

/**
 * @tc.name: InitWithNonObjectJson
 * @tc.desc: Test Init with valid JSON but non-object type (array).
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, InitWithNonObjectJson, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare JSON array instead of object.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string arrayJson = "[1, 2, 3]";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with array JSON.
     * @tc.expected: Config should not crash, enable should be false.
     */
    config->Init(arrayJson);
    EXPECT_FALSE(config->IsEnable());
    delete config;
}

/**
 * @tc.name: InitWithoutConfigField
 * @tc.desc: Test Init with valid JSON but no config field.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, InitWithoutConfigField, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare JSON without config field.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string noConfigJson = "{\"enable\":true,\"switch\":{\"page\":true}}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config without config field.
     * @tc.expected: Enable should be true, but config map should be empty.
     */
    config->Init(noConfigJson);
    EXPECT_TRUE(config->IsEnable());
    auto cfg = config->GetConfig();
    EXPECT_TRUE(cfg->empty());
    delete config;
}

/**
 * @tc.name: InitWithInvalidConfigType
 * @tc.desc: Test Init when config field is not an array.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, InitWithInvalidConfigType, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare JSON with config as string instead of array.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string invalidConfigJson = "{\"enable\":true,\"config\":\"not an array\"}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with invalid config type.
     * @tc.expected: Enable should be true, but config map should be empty.
     */
    config->Init(invalidConfigJson);
    EXPECT_TRUE(config->IsEnable());
    auto cfg = config->GetConfig();
    EXPECT_TRUE(cfg->empty());
    delete config;
}

/**
 * @tc.name: ParseShareNodeWithNonString
 * @tc.desc: Test ParseShareNode with non-string array items.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, ParseShareNodeWithNonString, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare config with non-string shareNode items.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string nonStringShareNode = "{\"enable\":true,\"config\":[{\"pageUrl\":\"pages/Test\","
        "\"shareNode\":[\"validNode\",123,{\"obj\":\"node\"},null]}]}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with non-string shareNode items.
     * @tc.expected: Only string nodes should be parsed, non-strings skipped.
     */
    config->Init(nonStringShareNode);
    auto cfg = config->GetConfig();
    ASSERT_EQ(cfg->size(), 1u);
    auto pageCfg = cfg->at("pages/Test");
    EXPECT_EQ(pageCfg.shareNodes.size(), 1u);
    if (!pageCfg.shareNodes.empty()) {
        EXPECT_EQ(pageCfg.shareNodes.front(), "validNode");
    }
    delete config;
}

/**
 * @tc.name: ParseShareNodeWithEmptyId
 * @tc.desc: Test ParseShareNode with empty string id.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, ParseShareNodeWithEmptyId, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare config with empty string in shareNode array.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string emptyIdShareNode = "{\"enable\":true,\"config\":[{\"pageUrl\":\"pages/Test\","
        "\"shareNode\":[\"node1\",\"\",\"node2\"]}]}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with empty id.
     * @tc.expected: Empty string should be filtered out.
     */
    config->Init(emptyIdShareNode);
    auto cfg = config->GetConfig();
    ASSERT_EQ(cfg->size(), 1u);
    auto pageCfg = cfg->at("pages/Test");
    EXPECT_EQ(pageCfg.shareNodes.size(), 2u);
    delete config;
}

/**
 * @tc.name: ParseExposureCfgWithNonObject
 * @tc.desc: Test ParseExposureCfg with non-object array items.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, ParseExposureCfgWithNonObject, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare config with non-object exposureCfg items.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string nonObjectExposure = "{\"enable\":true,\"config\":[{\"pageUrl\":\"pages/Test\","
        "\"exposureCfg\":[{\"id\":\"node1\",\"ratio\":0.5,\"duration\":1000},"
        "\"string\",123,null]}]}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with non-object exposure items.
     * @tc.expected: Only valid exposure objects should be parsed.
     */
    config->Init(nonObjectExposure);
    auto cfg = config->GetConfig();
    ASSERT_EQ(cfg->size(), 1u);
    auto pageCfg = cfg->at("pages/Test");
    EXPECT_EQ(pageCfg.exposureCfgs.size(), 1u);
    delete config;
}

/**
 * @tc.name: ParseExposureCfgWithZeroRatio
 * @tc.desc: Test ParseExposureCfg with zero ratio value.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, ParseExposureCfgWithZeroRatio, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare config with zero ratio.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string zeroRatioJson = "{\"enable\":true,\"config\":[{\"pageUrl\":\"pages/Test\","
        "\"exposureCfg\":[{\"id\":\"node1\",\"ratio\":0.0,\"duration\":1000}]}]}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with zero ratio.
     * @tc.expected: Zero ratio should be accepted (only duration > 0 is checked).
     */
    config->Init(zeroRatioJson);
    auto cfg = config->GetConfig();
    ASSERT_EQ(cfg->size(), 1u);
    auto pageCfg = cfg->at("pages/Test");
    ASSERT_EQ(pageCfg.exposureCfgs.size(), 1u);
    auto exposureCfg = pageCfg.exposureCfgs.front();
    EXPECT_EQ(exposureCfg.id, "node1");
    EXPECT_DOUBLE_EQ(exposureCfg.ratio, 0.0);
    EXPECT_EQ(exposureCfg.duration, 1000);
    delete config;
}

/**
 * @tc.name: ParseExposureCfgWithNegativeRatio
 * @tc.desc: Test ParseExposureCfg with negative ratio value.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, ParseExposureCfgWithNegativeRatio, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare config with negative ratio.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string negativeRatioJson = "{\"enable\":true,\"config\":[{\"pageUrl\":\"pages/Test\","
        "\"exposureCfg\":[{\"id\":\"node1\",\"ratio\":-0.5,\"duration\":1000}]}]}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with negative ratio.
     * @tc.expected: Negative ratio should be accepted (only duration > 0 is checked).
     */
    config->Init(negativeRatioJson);
    auto cfg = config->GetConfig();
    ASSERT_EQ(cfg->size(), 1u);
    auto pageCfg = cfg->at("pages/Test");
    ASSERT_EQ(pageCfg.exposureCfgs.size(), 1u);
    auto exposureCfg = pageCfg.exposureCfgs.front();
    EXPECT_EQ(exposureCfg.id, "node1");
    EXPECT_DOUBLE_EQ(exposureCfg.ratio, -0.5);
    delete config;
}

/**
 * @tc.name: InitWithEmptyPageUrl
 * @tc.desc: Test Init with empty pageUrl in config array.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, InitWithEmptyPageUrl, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare config with empty pageUrl.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string emptyPageUrlJson = "{\"enable\":true,\"config\":[{\"pageUrl\":\"\","
        "\"shareNode\":[\"node1\"]},{\"pageUrl\":\"pages/Test\",\"shareNode\":[\"node2\"]}]}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with empty pageUrl.
     * @tc.expected: Config with empty pageUrl should be skipped.
     */
    config->Init(emptyPageUrlJson);
    auto cfg = config->GetConfig();
    EXPECT_EQ(cfg->size(), 1u);
    EXPECT_TRUE(cfg->find("") == cfg->end());
    EXPECT_TRUE(cfg->find("pages/Test") != cfg->end());
    delete config;
}

/**
 * @tc.name: InitWithNonObjectConfigItem
 * @tc.desc: Test Init when config array contains non-object items.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, InitWithNonObjectConfigItem, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare config with non-object items in config array.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string nonObjectItemJson = "{\"enable\":true,\"config\":["
        "\"string\",123,null,"
        "{\"pageUrl\":\"pages/Test\",\"shareNode\":[\"node1\"]}]}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with non-object items.
     * @tc.expected: Non-object items should be skipped.
     */
    config->Init(nonObjectItemJson);
    auto cfg = config->GetConfig();
    EXPECT_EQ(cfg->size(), 1u);
    EXPECT_TRUE(cfg->find("pages/Test") != cfg->end());
    delete config;
}

/**
 * @tc.name: InitWithEmptyConfigArray
 * @tc.desc: Test Init with empty config array.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, InitWithEmptyConfigArray, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare config with empty config array.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string emptyArrayJson = "{\"enable\":true,\"config\":[]}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config with empty config array.
     * @tc.expected: Config map should be empty.
     */
    config->Init(emptyArrayJson);
    auto cfg = config->GetConfig();
    EXPECT_TRUE(cfg->empty());
    delete config;
}

/**
 * @tc.name: GetWebInfo001
 * @tc.desc: Test getting web-related configuration.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, GetWebInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare config with web-related fields.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string webInfoJson = "{\"enable\":true,\"webCategory\":\"testCategory\","
        "\"webIdentifier\":\"testId\",\"webActionJs\":\"testJsCode\"}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config and get web info.
     * @tc.expected: Web info should match the configured values.
     */
    config->Init(webInfoJson);
    EXPECT_EQ(config->GetWebCategory(), "testCategory");
    EXPECT_EQ(config->GetWebIdentifier(), "testId");
    EXPECT_EQ(config->GetWebJsCode(), "testJsCode");
    delete config;
}

/**
 * @tc.name: GetWebInfo002
 * @tc.desc: Test getting web-related configuration when fields are missing.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, GetWebInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare config without web-related fields.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string noWebInfoJson = "{\"enable\":true}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Initialize config and get web info.
     * @tc.expected: Web info should be empty strings.
     */
    config->Init(noWebInfoJson);
    EXPECT_TRUE(config->GetWebCategory().empty());
    EXPECT_TRUE(config->GetWebIdentifier().empty());
    EXPECT_TRUE(config->GetWebJsCode().empty());
    delete config;
}

/**
 * @tc.name: IsEnable001
 * @tc.desc: Test IsEnable method.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, IsEnable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test with enable=false.
     * @tc.expected: IsEnable should return false.
     */
    std::string disabledJson = "{\"enable\":false}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);
    config->Init(disabledJson);
    EXPECT_FALSE(config->IsEnable());

    /**
     * @tc.steps: step2. Test with enable=true.
     * @tc.expected: IsEnable should return true.
     */
    std::string enabledJson = "{\"enable\":true}";
    config->Init(enabledJson);
    EXPECT_TRUE(config->IsEnable());
    delete config;
}

/**
 * @tc.name: GetConfig001
 * @tc.desc: Test GetConfig method.
 * @tc.type: FUNC
 */
HWTEST_F(EventConfigTest, GetConfig001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize config with valid data.
     * @tc.expected: EventConfig object is created successfully.
     */
    std::string validConfig = "{\"enable\":true,\"config\":[{\"pageUrl\":\"pages/Test\","
        "\"shareNode\":[\"node1\"],\"exposureCfg\":[{\"id\":\"exp1\",\"ratio\":0.8,\"duration\":2000}]}]}";
    Recorder::EventConfig* config = new Recorder::EventConfig();
    ASSERT_TRUE(config);

    /**
     * @tc.steps: step2. Get config and verify contents.
     * @tc.expected: Config should contain expected page configuration.
     */
    config->Init(validConfig);
    auto cfg = config->GetConfig();
    ASSERT_NE(cfg, nullptr);
    EXPECT_EQ(cfg->size(), 1u);
    EXPECT_TRUE(cfg->find("pages/Test") != cfg->end());

    auto pageCfg = cfg->at("pages/Test");
    EXPECT_EQ(pageCfg.shareNodes.size(), 1u);
    EXPECT_EQ(pageCfg.exposureCfgs.size(), 1u);
    delete config;
}

} // namespace OHOS::Ace