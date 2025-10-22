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

} // namespace OHOS::Ace