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

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "bridge/common/manifest/manifest_parser.h"
#include "core/common/ace_engine.h"
#include "core/common/test/mock/mock_container.h"
#include "core/components/test/mock/mock_resource_adapter.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_interface.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t MANIFEST_WINDOW_WIDTH = 800;
constexpr int32_t DEFAULT_DESIGN_WIDTH = 720;
constexpr int32_t MANIFEST_WIDGETS_SIZE = 1;
constexpr int32_t MANIFEST_VERSION_CODE = 1000000;
constexpr int32_t MANIFEST_MINIPLATFORM_VERSION = 1;
const std::string MANIFEST_APP_NAME = "test";
const std::string MANIFEST_APP_NAMES = "$string:color";
const std::string MANIFEST_VERSION_NAME = "1.0";
const std::string MANIFEST_LOG_LEVEL = "level0";
const std::string MANIFEST_ICON = "icon";
const std::string MANIFEST_APP_ID = "dmstest";
const std::string MANIFEST_INDEX_JS = "index.js";
const std::string MANIFEST_DEFAULT_JS = ".js";
const std::string MANIFEST_WIDGETS_NAME = "timer";
const std::string MANIFEST_WIDGETS_PATH = "manifest";
const std::string MANIFEST_CUSTOM = "                                                    "
                                    "{                                                   "
                                    "  \"appName\": \"$string:color\",                   "
                                    "  \"versionName\": \"1.0\",                         "
                                    "  \"versionCode\": 1000000,                         "
                                    "  \"logLevel\": \"level0\",                         "
                                    "  \"icon\": \"icon\",                               "
                                    "  \"appID\": \"dmstest\",                           "
                                    "  \"minPlatformVersion\": 1,                        "
                                    "  \"webFeature\": true,                             "
                                    "  \"deviceType\": [                                 "
                                    "                \"liteWearable\"                    "
                                    "              ],                                    "
                                    "  \"pages\": [                                      "
                                    "                \"index\",                          "
                                    "                \"first\"                           "
                                    "              ],                                    "
                                    "  \"widgets\": [{                                   "
                                    "                \"name\" : \"photo\"                "
                                    "              },{                                   "
                                    "                \"path\" : \"manifest\"             "
                                    "              },{                                   "
                                    "                \"name\" : \"timer\",               "
                                    "                \"path\" : \"manifest\"             "
                                    "              }],                                   "
                                    "  \"window\": {                                     "
                                    "                \"designWidth\" : 800,              "
                                    "                \"autoDesignWidth\" : true          "
                                    "              }                                     "
                                    "}";

const std::string MANIFEST_DEVICE_TYPE = "                                               "
                                         "{                                              "
                                         "  \"appName\": \"$string:color\",              "
                                         "  \"webFeature\": true,                        "
                                         "  \"deviceType\": [                            "
                                         "                \"notLiteWearable\"            "
                                         "              ],                               "
                                         "  \"pages\": [                                 "
                                         "                100                            "
                                         "              ],                               "
                                         "  \"window\": {                                "
                                         "                \"designWidth\" : -800,        "
                                         "                \"autoDesignWidth\" : true     "
                                         "              }                                "
                                         "}";

const std::string MANIFEST_BAD_FORMAT = "                                                "
                                        "{                                               "
                                        "  \"appName\": \"test\",                        "
                                        "  \"webFeature\": true,                         "
                                        "  \"deviceType\": \"liteWearable\",             "
                                        "  \"pages\": \"index\",                         "
                                        "  \"widgets\": \"name\"                         "
                                        "}";
} // namespace

class ManifestParserTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void ManifestParserTest::SetUpTestCase() {}
void ManifestParserTest::TearDownTestCase() {}
void ManifestParserTest::SetUp() {}
void ManifestParserTest::TearDown() {}

/**
 * @tc.name: ManifestParserTest001
 * @tc.desc: Parse the manifest with wrong format
 * @tc.type: FUNC
 */
HWTEST_F(ManifestParserTest, ManifestParserTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Parse the empty manifest.
     * @tc.expected: step1. Get the default information as expected.
     */
    ManifestParser manifestParser;
    manifestParser.Parse("");
    EXPECT_EQ(manifestParser.IsUseLiteStyle(), false);
    EXPECT_EQ(manifestParser.GetRouter()->GetPagePath("/"), MANIFEST_DEFAULT_JS);
    EXPECT_EQ(manifestParser.GetAppInfo()->GetAppName(), "");
    EXPECT_EQ(manifestParser.GetWidget()->GetWidgetNum(), 0);
    EXPECT_EQ(manifestParser.GetWindowConfig().designWidth, DEFAULT_DESIGN_WIDTH);

    /**
     * @tc.steps: step2. Parse the manifest with wrong format.
     * @tc.expected: step2. Get the default information as expected.
     */
    manifestParser.Parse(MANIFEST_BAD_FORMAT);
    manifestParser.GetAppInfo()->ParseI18nJsonInfo();
    EXPECT_EQ(manifestParser.IsUseLiteStyle(), false);
    EXPECT_EQ(manifestParser.IsWebFeature(), true);
    EXPECT_EQ(manifestParser.GetRouter()->GetPagePath("/"), MANIFEST_DEFAULT_JS);
    EXPECT_EQ(manifestParser.GetAppInfo()->GetAppName(), MANIFEST_APP_NAME);
    EXPECT_EQ(manifestParser.GetWidget()->GetWidgetNum(), 0);
    EXPECT_EQ(manifestParser.GetWindowConfig().designWidth, DEFAULT_DESIGN_WIDTH);

    /**
     * @tc.steps: step3. Parse the manifest that lacks some information.
     * @tc.expected: step3. Get the information as expected.
     */
    manifestParser.Parse(MANIFEST_DEVICE_TYPE);
    manifestParser.GetAppInfo()->ParseI18nJsonInfo();
    EXPECT_EQ(manifestParser.IsUseLiteStyle(), false);
    EXPECT_EQ(manifestParser.IsWebFeature(), true);
    EXPECT_EQ(manifestParser.GetRouter()->GetPagePath("/"), MANIFEST_DEFAULT_JS);
    EXPECT_EQ(manifestParser.GetAppInfo()->GetAppName(), MANIFEST_APP_NAMES);
    EXPECT_EQ(manifestParser.GetWidget()->GetWidgetNum(), 0);
    EXPECT_EQ(manifestParser.GetWindowConfig().designWidth, DEFAULT_DESIGN_WIDTH);
    EXPECT_EQ(manifestParser.GetWindowConfig().autoDesignWidth, true);
}

/**
 * @tc.name: ManifestParserTest002
 * @tc.desc: Parse the manifest with correct format
 * @tc.type: FUNC
 */
HWTEST_F(ManifestParserTest, ManifestParserTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Parse the manifest with correct format .
     * @tc.expected: step1. Get the information as expected.
     */
    uint32_t resId = 0;
    std::string resourceName = "color";
    std::string str = "string";
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipelineContext = AceType::MakeRefPtr<MockPipelineBase>();
    auto container = AceType::MakeRefPtr<MockContainer>(pipelineContext);
    pipelineContext->SetThemeManager(themeManager);
    AceEngine::Get().AddContainer(-1, container);

    auto resourceAdapter = AceType::MakeRefPtr<MockResourceAdapter>();
    auto themeConstant = AceType::MakeRefPtr<ThemeConstants>(resourceAdapter);
    EXPECT_CALL(*themeManager, GetThemeConstants("", "")).WillOnce(Return(themeConstant));
    EXPECT_CALL(*resourceAdapter, GetIdByName(resourceName, str, resId)).WillOnce(Return(true));

    ManifestParser manifestParser;
    manifestParser.Parse(MANIFEST_CUSTOM);
    manifestParser.GetAppInfo()->ParseI18nJsonInfo();
    auto manifestWidget = manifestParser.GetWidget()->GetWidgetList().find(MANIFEST_WIDGETS_NAME);
    EXPECT_EQ(manifestParser.GetAppInfo()->GetAppName(), "");
    EXPECT_EQ(manifestParser.GetAppInfo()->GetVersionName(), MANIFEST_VERSION_NAME);
    EXPECT_EQ(manifestParser.GetAppInfo()->GetVersionCode(), MANIFEST_VERSION_CODE);
    EXPECT_EQ(manifestParser.GetAppInfo()->GetLogLevel(), MANIFEST_LOG_LEVEL);
    EXPECT_EQ(manifestParser.GetAppInfo()->GetIcon(), MANIFEST_ICON);
    EXPECT_EQ(manifestParser.GetAppInfo()->GetAppID(), MANIFEST_APP_ID);
    EXPECT_EQ(manifestParser.GetAppInfo()->GetMinPlatformVersion(), MANIFEST_MINIPLATFORM_VERSION);
    EXPECT_EQ(manifestParser.GetRouter()->GetPagePath("/"), MANIFEST_INDEX_JS);
    EXPECT_EQ(manifestParser.GetRouter()->GetEntry(".js"), MANIFEST_INDEX_JS);
    EXPECT_EQ(manifestParser.GetWidget()->GetWidgetNum(), MANIFEST_WIDGETS_SIZE);
    EXPECT_EQ(manifestWidget->second->GetWidgetName(), MANIFEST_WIDGETS_NAME);
    EXPECT_EQ(manifestWidget->second->GetWidgetPath(), MANIFEST_WIDGETS_PATH);
    EXPECT_EQ(manifestParser.GetWindowConfig().designWidth, MANIFEST_WINDOW_WIDTH);
    EXPECT_EQ(manifestParser.GetWindowConfig().autoDesignWidth, true);
    EXPECT_EQ(manifestParser.IsWebFeature(), true);
    EXPECT_EQ(manifestParser.IsUseLiteStyle(), true);
}
} // namespace OHOS::Ace::Framework