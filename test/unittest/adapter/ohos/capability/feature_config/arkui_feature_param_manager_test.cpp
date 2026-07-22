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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "adapter/ohos/capability/feature_config/config_parser_base.h"
#include "adapter/ohos/capability/feature_config/feature_param_manager.h"
#include "base/utils/feature_manager.h"
#include "base/utils/feature_param.h"
#include "interfaces/inner_api/ace/ui_content.h"
#undef private
#undef protected
using namespace testing;
using namespace testing::ext;

#include "bundlemgr/bundle_mgr_proxy.h"

namespace OHOS::Ace {
class ArkUIFeatureParamManagerTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() {};
    void TearDown() {};

    const std::string PERF_CONFIG = "PerformanceOptConfig";
    const std::string BUNDLE_NAME = "bundleName";
    const std::string FEATURE = "feature";
    const std::string NAME = "name";
    const std::string ID = "id";
    const std::string TEST1_HAP = "test1.hap";
    const std::string TEST2_HAP = "test2.hap";
    const std::string UI_NODE_GC_NAME = "UINodeGcParamParser";
    const std::string SYNC_LOAD_NAME = "SyncLoadParser";
    const std::string SYNC_LOAD_VALUE = "value";
    const std::string SYNC_LOAD_VALUE_TIME = "50";
    const std::string TEST_UNDEFINE = "Undefine";

    std::vector<OHOS::AppExecFwk::Metadata> metadata_ = { {"test", "test", "test"} };
};

/**
 * @tc.name: InitTest001
 * @tc.desc: ArkUIFeatureParamManagerTest::Init
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, InitTest, TestSize.Level1)
{
    FeatureParamManager::GetInstance().Init(TEST1_HAP, metadata_);
    auto& featureParser = FeatureParamManager::GetInstance().featureParser_;
    EXPECT_NE(featureParser, nullptr);

    OHOS::AppExecFwk::Metadata data = { "idle_delete", "true", "" };
    metadata_.push_back(data);
    FeatureParamManager::GetInstance().Init(TEST1_HAP, metadata_);
    EXPECT_NE(featureParser, nullptr);
}

/**
 * @tc.name: ParseEntryTest001
 * @tc.desc: ParseEntry will only init once
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseEntryTest001, TestSize.Level1)
{
    FeatureParamManager::GetInstance().FeatureParamParseEntry("");
    auto curFeatureParser1 = FeatureParamManager::GetInstance().featureParser_;
    FeatureParamManager::GetInstance().FeatureParamParseEntry("");
    auto curFeatureParser2 = FeatureParamManager::GetInstance().featureParser_;
    EXPECT_EQ(curFeatureParser1, curFeatureParser2);

    FeatureParamManager::GetInstance().UICorrectionParamParseEntry("");
    auto uiCorrectionParser1 = FeatureParamManager::GetInstance().uiCorrectionParser_;
    FeatureParamManager::GetInstance().UICorrectionParamParseEntry("");
    auto uiCorrectionParser2 = FeatureParamManager::GetInstance().uiCorrectionParser_;
    EXPECT_EQ(uiCorrectionParser1, uiCorrectionParser2);
}

/**
 * @tc.name: ParseInternalWithBundleNameTest
 * @tc.desc: FeatureParamManager test
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseInternalWithBundleNameTest, TestSize.Level1)
{
    FeatureParamManager::GetInstance().Init(TEST1_HAP, metadata_);
    auto& featureParser = FeatureParamManager::GetInstance().featureParser_;

    xmlNode featureNode1 = {
        .type = xmlElementType::XML_ELEMENT_NODE,
        .name = reinterpret_cast<const xmlChar*>(FEATURE.c_str()),
    };
    xmlSetProp(&featureNode1, (const xmlChar*)(ID.c_str()), (const xmlChar*)(UI_NODE_GC_NAME.c_str()));

    xmlNode featureNode2 = {
        .type = xmlElementType::XML_ELEMENT_NODE,
        .name = reinterpret_cast<const xmlChar*>(FEATURE.c_str()),
    };
    xmlSetProp(&featureNode2, (const xmlChar*)(ID.c_str()), (const xmlChar*)(SYNC_LOAD_NAME.c_str()));

    xmlNode featureNode3 = {
        .type = xmlElementType::XML_ELEMENT_NODE,
        .name = reinterpret_cast<const xmlChar*>(TEST_UNDEFINE.c_str()),
    };
    xmlSetProp(&featureNode3, (const xmlChar*)(ID.c_str()), (const xmlChar*)(TEST_UNDEFINE.c_str()));

    xmlNode bundleNameNode {
        .type = xmlElementType::XML_ELEMENT_NODE,
        .name = reinterpret_cast<const xmlChar*>(BUNDLE_NAME.c_str()),
    };

    xmlSetProp(&bundleNameNode, (const xmlChar*)(NAME.c_str()), (const xmlChar*)(TEST1_HAP.c_str()));
    xmlNode configNode = {
        .name = reinterpret_cast<const xmlChar*>(PERF_CONFIG.c_str()),
    };

    xmlNode rootNode;
    auto ret = featureParser->ParseInternalWithBundleName(rootNode, TEST1_HAP);
    EXPECT_EQ(ret, ParseErrCode::PARSE_GET_CHILD_FAIL);

    rootNode.children = &configNode;
    ret = featureParser->ParseInternalWithBundleName(rootNode, TEST1_HAP);
    EXPECT_EQ(ret, ParseErrCode::PARSE_GET_CHILD_FAIL);

    configNode.children = &bundleNameNode;
    ret = featureParser->ParseInternalWithBundleName(rootNode, TEST1_HAP);
    EXPECT_EQ(ret, ParseErrCode::PARSE_EXEC_SUCCESS);

    bundleNameNode.children = &featureNode1;
    ret = featureParser->ParseInternalWithBundleName(rootNode, TEST1_HAP);
    EXPECT_EQ(ret, ParseErrCode::PARSE_EXEC_SUCCESS);

    featureNode1.next = &featureNode2;
    ret = featureParser->ParseInternalWithBundleName(rootNode, TEST1_HAP);
    EXPECT_EQ(ret, ParseErrCode::PARSE_EXEC_SUCCESS);

    xmlSetProp(&featureNode2, (const xmlChar*)(SYNC_LOAD_VALUE.c_str()),
        (const xmlChar*)(SYNC_LOAD_VALUE_TIME.c_str()));
    ret = featureParser->ParseInternalWithBundleName(rootNode, TEST1_HAP);
    EXPECT_EQ(ret, ParseErrCode::PARSE_EXEC_SUCCESS);

    featureNode2.next = &featureNode3;
    ret = featureParser->ParseInternalWithBundleName(rootNode, TEST1_HAP);
    EXPECT_EQ(ret, ParseErrCode::PARSE_EXEC_SUCCESS);

    bundleNameNode.name = reinterpret_cast<const xmlChar*>(TEST_UNDEFINE.c_str());
    ret = featureParser->ParseInternalWithBundleName(rootNode, TEST1_HAP);
    EXPECT_EQ(ret, ParseErrCode::PARSE_EXEC_SUCCESS);

    featureParser->Destroy();
}

/**
 * @tc.name: ParsePerformanceConfigXMLWithBundleNameTest
 * @tc.desc: ParsePerformanceConfigXMLWithBundleName test
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParsePerformanceConfigXMLWithBundleNameTest, TestSize.Level1)
{
    auto featureParser = std::make_unique<ConfigParserBase>();
    auto ret = featureParser->ParsePerformanceConfigXMLWithBundleName(TEST1_HAP);
    EXPECT_EQ(ret, ParseErrCode::PARSE_SYS_FILE_LOAD_FAIL);
    auto doc = std::make_shared<xmlDoc>();
    featureParser->xmlSysDocument_ = doc.get();

    ret = featureParser->ParsePerformanceConfigXMLWithBundleName(TEST1_HAP);
    EXPECT_EQ(ret, ParseErrCode::PARSE_GET_ROOT_FAIL);

    xmlNode children;
    children.type = xmlElementType::XML_ELEMENT_NODE;
    doc->children = &children;
    ret = featureParser->ParsePerformanceConfigXMLWithBundleName(TEST1_HAP);
    EXPECT_EQ(ret, ParseErrCode::PARSE_GET_CHILD_FAIL);
    featureParser->xmlSysDocument_ = nullptr;
    featureParser = nullptr;
}

/**
 * @tc.name: ParseXmlNodeNameWithIndexTest
 * @tc.desc: ParseXmlNodeNameWithIndex test
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseXmlNodeNameWithIndexTest, TestSize.Level1)
{
    auto featureParser = std::make_unique<ConfigParserBase>();
    xmlNode node;
    auto ret = featureParser->ParseXmlNodeNameWithIndex(node, 5);
    EXPECT_EQ(ret, ParseErrCode::PARSE_SIZE_ERROR);
    featureParser = nullptr;
}

/**
 * @tc.name: ParseArkUICorrectionConfigFromUIContentTest001
 * @tc.desc: Test ParseArkUICorrectionConfigFromUIContent with empty config
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkUICorrectionConfigFromUIContentTest001, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkUICorrectionConfig_ = false;
    FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.reset();
    FeatureParamManager::GetInstance().dialogCorrectionEnabledFromCloud_.reset();
    FeatureParamManager::GetInstance().rnOverflowEnabledFromCloud_.reset();

    // Test with empty config (default UIContent::GetUICorrectionConfig returns empty)
    FeatureParamManager::GetInstance().ParseArkUICorrectionConfigFromUIContent();

    // Verify that cloud config values are not set (still nullopt)
    EXPECT_FALSE(FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.has_value());
    EXPECT_FALSE(FeatureParamManager::GetInstance().dialogCorrectionEnabledFromCloud_.has_value());
    EXPECT_FALSE(FeatureParamManager::GetInstance().rnOverflowEnabledFromCloud_.has_value());
}

/**
 * @tc.name: ParseArkUICorrectionConfigFromUIContentTest002
 * @tc.desc: Test ParseArkUICorrectionConfigFromUIContent with valid config
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkUICorrectionConfigFromUIContentTest002, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkUICorrectionConfig_ = false;
    FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.reset();
    FeatureParamManager::GetInstance().dialogCorrectionEnabledFromCloud_.reset();
    FeatureParamManager::GetInstance().rnOverflowEnabledFromCloud_.reset();

    // Set valid config via UIContent
    std::string validConfig =
        R"({"arkui":{
            "feature":{
                "pageOverflowEnabled":"true",
                "dialogOverflowEnabled":"false",
                "RNPageOverflowEnabled":"true"
            }}})";
    UIContent::SetUICorrectionConfig(validConfig);

    // Parse config
    FeatureParamManager::GetInstance().ParseArkUICorrectionConfigFromUIContent();

    // Verify that cloud config values are set correctly
    EXPECT_TRUE(FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.has_value());
    EXPECT_TRUE(FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.value());

    EXPECT_TRUE(FeatureParamManager::GetInstance().dialogCorrectionEnabledFromCloud_.has_value());
    EXPECT_FALSE(FeatureParamManager::GetInstance().dialogCorrectionEnabledFromCloud_.value());

    EXPECT_TRUE(FeatureParamManager::GetInstance().rnOverflowEnabledFromCloud_.has_value());
    EXPECT_TRUE(FeatureParamManager::GetInstance().rnOverflowEnabledFromCloud_.value());
    UIContent::uiCorrectionConfigJson_ = "";
}

/**
 * @tc.name: ParseArkUICorrectionConfigFromUIContentTest003
 * @tc.desc: Test ParseArkUICorrectionConfigFromUIContent idempotent behavior
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkUICorrectionConfigFromUIContentTest003, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkUICorrectionConfig_ = false;
    FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.reset();
    FeatureParamManager::GetInstance().dialogCorrectionEnabledFromCloud_.reset();
    FeatureParamManager::GetInstance().rnOverflowEnabledFromCloud_.reset();

    // Set config
    std::string config = R"({"arkui":{"feature":{"pageOverflowEnabled":"true"}}})";
    UIContent::SetUICorrectionConfig(config);

    // First call
    FeatureParamManager::GetInstance().ParseArkUICorrectionConfigFromUIContent();
    auto firstValue = FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_;

    // Second call should not change values (idempotent)
    FeatureParamManager::GetInstance().ParseArkUICorrectionConfigFromUIContent();
    auto secondValue = FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_;

    EXPECT_EQ(firstValue, secondValue);
    UIContent::uiCorrectionConfigJson_ = "";
}

/**
 * @tc.name: ParseArkUICorrectionConfigFromUIContentTest004
 * @tc.desc: Test ParseArkUICorrectionConfigFromUIContent with invalid JSON
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkUICorrectionConfigFromUIContentTest004, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkUICorrectionConfig_ = false;
    FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.reset();

    // Set invalid JSON - need to bypass SetUICorrectionConfig's validation by directly setting the static member
    FeatureParamManager::GetInstance().hasParseArkUICorrectionConfig_ = false;
    UIContent::uiCorrectionConfigJson_ = "invalid json {{{";

    // Parse should handle invalid JSON gracefully
    FeatureParamManager::GetInstance().ParseArkUICorrectionConfigFromUIContent();

    // Values should not be set
    EXPECT_FALSE(FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.has_value());
    UIContent::uiCorrectionConfigJson_ = "";
}

/**
 * @tc.name: ParseArkUICorrectionConfigFromUIContentTest005
 * @tc.desc: Test ParseArkUICorrectionConfigFromUIContent with missing arkui key
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkUICorrectionConfigFromUIContentTest005, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkUICorrectionConfig_ = false;
    FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.reset();

    // Set config without arkui key
    std::string config = R"({"other":{"feature":{"pageOverflowEnabled":"true"}}})";
    UIContent::uiCorrectionConfigJson_ = config;

    // Parse
    FeatureParamManager::GetInstance().ParseArkUICorrectionConfigFromUIContent();

    // Values should not be set as arkui key is missing
    EXPECT_FALSE(FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.has_value());
    UIContent::uiCorrectionConfigJson_ = "";
}

/**
 * @tc.name: ParseArkUICorrectionConfigFromUIContentTest006
 * @tc.desc: Test ParseArkUICorrectionConfigFromUIContent with missing feature key
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkUICorrectionConfigFromUIContentTest006, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkUICorrectionConfig_ = false;
    FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.reset();

    // Set config without feature key
    std::string config = R"({"arkui":{"other":{"pageOverflowEnabled":"true"}}})";
    UIContent::uiCorrectionConfigJson_ = config;

    // Parse
    FeatureParamManager::GetInstance().ParseArkUICorrectionConfigFromUIContent();

    // Values should not be false as feature key is missing
    EXPECT_TRUE(FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.has_value());
    EXPECT_FALSE(FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.value());

    EXPECT_TRUE(FeatureParamManager::GetInstance().dialogCorrectionEnabledFromCloud_.has_value());
    EXPECT_FALSE(FeatureParamManager::GetInstance().dialogCorrectionEnabledFromCloud_.value());

    EXPECT_TRUE(FeatureParamManager::GetInstance().rnOverflowEnabledFromCloud_.has_value());
    EXPECT_FALSE(FeatureParamManager::GetInstance().rnOverflowEnabledFromCloud_.value());
    UIContent::uiCorrectionConfigJson_ = "";
}

/**
 * @tc.name: ParseArkUICorrectionConfigFromUIContentTest007
 * @tc.desc: Test ParseArkUICorrectionConfigFromUIContent default values when arkui key exists
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkUICorrectionConfigFromUIContentTest007, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkUICorrectionConfig_ = false;
    FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.reset();
    FeatureParamManager::GetInstance().dialogCorrectionEnabledFromCloud_.reset();
    FeatureParamManager::GetInstance().rnOverflowEnabledFromCloud_.reset();

    // Set config with arkui key but empty feature
    std::string config = R"({"arkui":{}})";
    UIContent::uiCorrectionConfigJson_ = config;

    // Parse
    FeatureParamManager::GetInstance().ParseArkUICorrectionConfigFromUIContent();

    // When arkui key exists, values are initialized to false
    EXPECT_TRUE(FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.has_value());
    EXPECT_FALSE(FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.value());

    EXPECT_TRUE(FeatureParamManager::GetInstance().dialogCorrectionEnabledFromCloud_.has_value());
    EXPECT_FALSE(FeatureParamManager::GetInstance().dialogCorrectionEnabledFromCloud_.value());

    EXPECT_TRUE(FeatureParamManager::GetInstance().rnOverflowEnabledFromCloud_.has_value());
    EXPECT_FALSE(FeatureParamManager::GetInstance().rnOverflowEnabledFromCloud_.value());
    UIContent::uiCorrectionConfigJson_ = "";
}

/**
 * @tc.name: ParseArkWebAutoLayoutConfigFromUIContentTest001
 * @tc.desc: Test ParseArkWebAutoLayoutConfigFromUIContent with empty config
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkWebAutoLayoutConfigFromUIContentTest001, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkWebAutoLayoutConfig_ = false;
    FeatureParamManager::GetInstance().arkWebJsonConfigStr_ = "";

    // Test with empty config (default UIContent::GetUICorrectionConfig returns empty)
    FeatureParamManager::GetInstance().ParseArkWebAutoLayoutConfigFromUIContent();

    // Should set empty string
    EXPECT_TRUE(FeatureParamManager::GetInstance().arkWebJsonConfigStr_.empty());
}

/**
 * @tc.name: ParseArkWebAutoLayoutConfigFromUIContentTest002
 * @tc.desc: Test ParseArkWebAutoLayoutConfigFromUIContent with valid arkweb config
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkWebAutoLayoutConfigFromUIContentTest002, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkWebAutoLayoutConfig_ = false;
    FeatureParamManager::GetInstance().arkWebJsonConfigStr_ = "";

    // Set valid config with arkweb
    std::string validConfig = R"({"arkweb":{"autoLayout":"enabled","version":"1.0"}})";
    UIContent::uiCorrectionConfigJson_ = validConfig;

    // Parse config
    FeatureParamManager::GetInstance().ParseArkWebAutoLayoutConfigFromUIContent();

    // Verify config is set
    EXPECT_FALSE(FeatureParamManager::GetInstance().arkWebJsonConfigStr_.empty());
    EXPECT_NE(FeatureParamManager::GetInstance().arkWebJsonConfigStr_.find("autoLayout"), std::string::npos);
    UIContent::uiCorrectionConfigJson_ = "";
}

/**
 * @tc.name: ParseArkWebAutoLayoutConfigFromUIContentTest003
 * @tc.desc: Test ParseArkWebAutoLayoutConfigFromUIContent idempotent behavior
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkWebAutoLayoutConfigFromUIContentTest003, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkWebAutoLayoutConfig_ = false;
    FeatureParamManager::GetInstance().arkWebJsonConfigStr_ = "";

    // Set config
    std::string config = R"({"arkweb":{"test":"value"}})";
    UIContent::uiCorrectionConfigJson_ = config;

    // First call
    FeatureParamManager::GetInstance().ParseArkWebAutoLayoutConfigFromUIContent();
    auto firstConfig = FeatureParamManager::GetInstance().arkWebJsonConfigStr_;

    // Second call should not change values (idempotent)
    FeatureParamManager::GetInstance().ParseArkWebAutoLayoutConfigFromUIContent();
    auto secondConfig = FeatureParamManager::GetInstance().arkWebJsonConfigStr_;

    EXPECT_EQ(firstConfig, secondConfig);
    UIContent::uiCorrectionConfigJson_ = "";
}

/**
 * @tc.name: ParseArkWebAutoLayoutConfigFromUIContentTest004
 * @tc.desc: Test ParseArkWebAutoLayoutConfigFromUIContent with invalid JSON
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkWebAutoLayoutConfigFromUIContentTest004, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkWebAutoLayoutConfig_ = false;
    FeatureParamManager::GetInstance().arkWebJsonConfigStr_ = "";

    // Set invalid JSON
    UIContent::uiCorrectionConfigJson_ = "invalid json {{{";

    // Parse should handle invalid JSON gracefully
    FeatureParamManager::GetInstance().ParseArkWebAutoLayoutConfigFromUIContent();

    // Config should remain empty or unchanged
    EXPECT_TRUE(FeatureParamManager::GetInstance().arkWebJsonConfigStr_.empty());
    UIContent::uiCorrectionConfigJson_ = "";
}

/**
 * @tc.name: ParseArkWebAutoLayoutConfigFromUIContentTest005
 * @tc.desc: Test ParseArkWebAutoLayoutConfigFromUIContent with missing arkweb key
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkWebAutoLayoutConfigFromUIContentTest005, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkWebAutoLayoutConfig_ = false;
    FeatureParamManager::GetInstance().arkWebJsonConfigStr_ = "";

    // Set config without arkweb key
    std::string config = R"({"other":{"test":"value"}})";
    UIContent::uiCorrectionConfigJson_ = config;

    // Parse
    FeatureParamManager::GetInstance().ParseArkWebAutoLayoutConfigFromUIContent();

    // Config should remain empty as arkweb key is missing
    EXPECT_TRUE(FeatureParamManager::GetInstance().arkWebJsonConfigStr_.empty());
    UIContent::uiCorrectionConfigJson_ = "";
}

/**
 * @tc.name: ParseArkWebAutoLayoutConfigFromUIContentTest006
 * @tc.desc: Test ParseArkWebAutoLayoutConfigFromUIContent returns empty object when arkweb key exists
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkWebAutoLayoutConfigFromUIContentTest006, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkWebAutoLayoutConfig_ = false;
    FeatureParamManager::GetInstance().arkWebJsonConfigStr_ = "";

    // Set config with arkweb key but empty object
    std::string config = R"({"arkweb":{}})";
    UIContent::uiCorrectionConfigJson_ = config;

    // Parse
    FeatureParamManager::GetInstance().ParseArkWebAutoLayoutConfigFromUIContent();

    // Should return empty object representation
    EXPECT_EQ(FeatureParamManager::GetInstance().arkWebJsonConfigStr_, "{}");
    UIContent::uiCorrectionConfigJson_ = "";
}

/**
 * @tc.name: ParseArkWebAutoLayoutConfigFromUIContentTest007
 * @tc.desc: Test GetArkWebAutoLayoutConfig integrates with ParseArkWebAutoLayoutConfigFromUIContent
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkWebAutoLayoutConfigFromUIContentTest007, TestSize.Level1)
{
    // Reset state
    FeatureParamManager::GetInstance().hasParseArkWebAutoLayoutConfig_ = false;
    FeatureParamManager::GetInstance().arkWebJsonConfigStr_ = "";

    // Set valid config
    std::string config = R"({"arkweb":{"enabled":true,"mode":"auto"}})";
    UIContent::uiCorrectionConfigJson_ = config;

    // GetArkWebAutoLayoutConfig should call ParseArkWebAutoLayoutConfigFromUIContent internally
    auto result = FeatureParamManager::GetInstance().GetArkWebAutoLayoutConfig();

    // Verify result
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("enabled"), std::string::npos);
    UIContent::uiCorrectionConfigJson_ = "";
}

/**
 * @tc.name: ParseArkUICorrectionConfigAndArkWebConfigCombinedTest001
 * @tc.desc: Test both ParseArkUICorrectionConfigFromUIContent and ParseArkWebAutoLayoutConfigFromUIContent together
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkUICorrectionConfigAndArkWebConfigCombinedTest001, TestSize.Level1)
{
    // Reset both states
    FeatureParamManager::GetInstance().hasParseArkUICorrectionConfig_ = false;
    FeatureParamManager::GetInstance().hasParseArkWebAutoLayoutConfig_ = false;
    FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.reset();
    FeatureParamManager::GetInstance().arkWebJsonConfigStr_ = "";

    // Set config with both arkui and arkweb
    std::string config = R"({
        "arkui": {
            "feature": {
                "pageOverflowEnabled": "true",
                "dialogOverflowEnabled": "false"
            }
        },
        "arkweb": {
            "autoLayout": "enabled"
        }
    })";
    UIContent::uiCorrectionConfigJson_ = config;

    // Parse both configs
    FeatureParamManager::GetInstance().ParseArkUICorrectionConfigFromUIContent();
    FeatureParamManager::GetInstance().ParseArkWebAutoLayoutConfigFromUIContent();

    // Verify both are parsed correctly
    EXPECT_TRUE(FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.has_value());
    EXPECT_TRUE(FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_.value());

    EXPECT_FALSE(FeatureParamManager::GetInstance().arkWebJsonConfigStr_.empty());
    EXPECT_NE(FeatureParamManager::GetInstance().arkWebJsonConfigStr_.find("autoLayout"), std::string::npos);
    UIContent::uiCorrectionConfigJson_ = "";
}

/**
 * @tc.name: ParseArkUICorrectionConfigAndArkWebConfigCombinedTest002
 * @tc.desc: Test multiple calls don't interfere with each other
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseArkUICorrectionConfigAndArkWebConfigCombinedTest002, TestSize.Level1)
{
    // Reset both states
    FeatureParamManager::GetInstance().hasParseArkUICorrectionConfig_ = false;
    FeatureParamManager::GetInstance().hasParseArkWebAutoLayoutConfig_ = false;

    // Set config
    std::string config = R"({"arkui":{"feature":{"pageOverflowEnabled":"true"}},"arkweb":{"test":"value"}})";
    UIContent::uiCorrectionConfigJson_ = config;

    // Call in different orders
    FeatureParamManager::GetInstance().ParseArkUICorrectionConfigFromUIContent();
    FeatureParamManager::GetInstance().ParseArkWebAutoLayoutConfigFromUIContent();

    auto arkUiValue1 = FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_;
    auto arkWebValue1 = FeatureParamManager::GetInstance().arkWebJsonConfigStr_;

    // Call again in reverse order (should be idempotent)
    FeatureParamManager::GetInstance().ParseArkWebAutoLayoutConfigFromUIContent();
    FeatureParamManager::GetInstance().ParseArkUICorrectionConfigFromUIContent();

    auto arkUiValue2 = FeatureParamManager::GetInstance().pageOverflowEnabledFromCloud_;
    auto arkWebValue2 = FeatureParamManager::GetInstance().arkWebJsonConfigStr_;

    // Values should remain the same
    EXPECT_EQ(arkUiValue1, arkUiValue2);
    EXPECT_EQ(arkWebValue1, arkWebValue2);
    UIContent::uiCorrectionConfigJson_ = "";
}

namespace {
void ResetStrategyState()
{
    auto& mgr = FeatureParamManager::GetInstance();
    // Skip cloud parsing path so Is*Enabled only reflects strategy/base members.
    mgr.hasParseArkUICorrectionConfig_ = true;
    mgr.pageOverflowEnabledFromCloud_.reset();
    mgr.dialogCorrectionEnabledFromCloud_.reset();
    mgr.rnOverflowEnabledFromCloud_.reset();
    mgr.pageOverflowEnabled_ = false;
    mgr.dialogCorrectionEnabled_ = false;
    mgr.rnOverflowEnabled_ = false;
    mgr.strategyPageOverflowEnabled_ = false;
    mgr.strategyDialogOverflowEnabled_ = false;
    mgr.strategyRnOverflowEnabled_ = false;
    mgr.smartlayoutPageOverflowFix_ = FeatureParamManager::SmartLayoutFeatureConfig {};
    mgr.smartlayoutWidgetSplit_ = FeatureParamManager::SmartLayoutFeatureConfig {};
    UIContent::uiCorrectionConfigJson_ = "";
    FeatureManager::GetInstance().ClearFeatureParamForTest();
}
} // namespace

/**
 * @tc.name: ParseUICorrectionStrategyConfigTest001
 * @tc.desc: GetFeatureParam fails, strategy members keep default false.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseUICorrectionStrategyConfigTest001, TestSize.Level1)
{
    ResetStrategyState();
    FeatureManager::GetInstance().SetFeatureParamForTest(
        "UICorrectionStrategy", "", FeatureManager::KEY_NOT_FOUND);

    FeatureParamManager::GetInstance().ParseUICorrectionStrategyConfig();

    EXPECT_FALSE(FeatureParamManager::GetInstance().strategyPageOverflowEnabled_);
    EXPECT_FALSE(FeatureParamManager::GetInstance().strategyDialogOverflowEnabled_);
    EXPECT_FALSE(FeatureParamManager::GetInstance().strategyRnOverflowEnabled_);
}

/**
 * @tc.name: ParseUICorrectionStrategyConfigTest002
 * @tc.desc: GetFeatureParam succeeds but json is invalid, strategy members keep default false.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseUICorrectionStrategyConfigTest002, TestSize.Level1)
{
    ResetStrategyState();
    FeatureManager::GetInstance().SetFeatureParamForTest("UICorrectionStrategy", "invalid json {{{");

    FeatureParamManager::GetInstance().ParseUICorrectionStrategyConfig();

    EXPECT_FALSE(FeatureParamManager::GetInstance().strategyPageOverflowEnabled_);
    EXPECT_FALSE(FeatureParamManager::GetInstance().strategyDialogOverflowEnabled_);
    EXPECT_FALSE(FeatureParamManager::GetInstance().strategyRnOverflowEnabled_);
}

/**
 * @tc.name: ParseUICorrectionStrategyConfigTest003
 * @tc.desc: Valid json without smartlayout key, strategy members set and smartlayout untouched.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseUICorrectionStrategyConfigTest003, TestSize.Level1)
{
    ResetStrategyState();
    std::string config = 
        R"({"pageOverflowEnabled":true,"dialogOverflowEnabled":"true","RNPageOverflowEnabled":false})";
    FeatureManager::GetInstance().SetFeatureParamForTest("UICorrectionStrategy", config);

    FeatureParamManager::GetInstance().ParseUICorrectionStrategyConfig();

    EXPECT_TRUE(FeatureParamManager::GetInstance().strategyPageOverflowEnabled_);
    EXPECT_TRUE(FeatureParamManager::GetInstance().strategyDialogOverflowEnabled_);
    EXPECT_FALSE(FeatureParamManager::GetInstance().strategyRnOverflowEnabled_);
    EXPECT_FALSE(FeatureParamManager::GetInstance().smartlayoutPageOverflowFix_.enabled);
    EXPECT_FALSE(FeatureParamManager::GetInstance().smartlayoutWidgetSplit_.enabled);
}

/**
 * @tc.name: ParseUICorrectionStrategyConfigTest004
 * @tc.desc: Valid json with smartlayout object, strategy and smartlayout features all parsed.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseUICorrectionStrategyConfigTest004, TestSize.Level1)
{
    ResetStrategyState();
    std::string config = R"({"pageOverflowEnabled":true,"dialogOverflowEnabled":true,)"
        R"("RNPageOverflowEnabled":true,"smartlayout":)"
        R"({"PageOverflowFix":{"enabled":true,"values":["hash1","hash2"]},)"
        R"("WidgetSplit":{"enabled":true,"values":["url1"]}}})";
    FeatureManager::GetInstance().SetFeatureParamForTest("UICorrectionStrategy", config);

    FeatureParamManager::GetInstance().ParseUICorrectionStrategyConfig();

    EXPECT_TRUE(FeatureParamManager::GetInstance().strategyPageOverflowEnabled_);
    EXPECT_TRUE(FeatureParamManager::GetInstance().strategyDialogOverflowEnabled_);
    EXPECT_TRUE(FeatureParamManager::GetInstance().strategyRnOverflowEnabled_);

    const auto& pageFix = FeatureParamManager::GetInstance().smartlayoutPageOverflowFix_;
    EXPECT_TRUE(pageFix.enabled);
    EXPECT_EQ(pageFix.values.size(), 2u);
    EXPECT_TRUE(pageFix.values.count("hash1") > 0);
    EXPECT_TRUE(pageFix.values.count("hash2") > 0);

    const auto& widgetSplit = FeatureParamManager::GetInstance().smartlayoutWidgetSplit_;
    EXPECT_TRUE(widgetSplit.enabled);
    EXPECT_EQ(widgetSplit.values.size(), 1u);
    EXPECT_TRUE(widgetSplit.values.count("url1") > 0);
}

/**
 * @tc.name: ParseUICorrectionStrategyConfigTest005
 * @tc.desc: Smartlayout key present but value is not an object, smartlayout features untouched.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseUICorrectionStrategyConfigTest005, TestSize.Level1)
{
    ResetStrategyState();
    std::string config = R"({"pageOverflowEnabled":true,"smartlayout":"not_an_object"})";
    FeatureManager::GetInstance().SetFeatureParamForTest("UICorrectionStrategy", config);

    FeatureParamManager::GetInstance().ParseUICorrectionStrategyConfig();

    EXPECT_TRUE(FeatureParamManager::GetInstance().strategyPageOverflowEnabled_);
    EXPECT_FALSE(FeatureParamManager::GetInstance().smartlayoutPageOverflowFix_.enabled);
    EXPECT_FALSE(FeatureParamManager::GetInstance().smartlayoutWidgetSplit_.enabled);
}

/**
 * @tc.name: IsSmartLayoutPageOverflowFixEnabledTest001
 * @tc.desc: Feature disabled returns false regardless of pathHash.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, IsSmartLayoutPageOverflowFixEnabledTest001, TestSize.Level1)
{
    ResetStrategyState();
    auto& mgr = FeatureParamManager::GetInstance();
    mgr.smartlayoutPageOverflowFix_.enabled = false;

    EXPECT_FALSE(mgr.IsSmartLayoutPageOverflowFixEnabled("any_hash"));
}

/**
 * @tc.name: IsSmartLayoutPageOverflowFixEnabledTest002
 * @tc.desc: Feature enabled and empty pathHash returns true (global on).
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, IsSmartLayoutPageOverflowFixEnabledTest002, TestSize.Level1)
{
    ResetStrategyState();
    auto& mgr = FeatureParamManager::GetInstance();
    mgr.smartlayoutPageOverflowFix_.enabled = true;

    EXPECT_TRUE(mgr.IsSmartLayoutPageOverflowFixEnabled(""));
}

/**
 * @tc.name: IsSmartLayoutPageOverflowFixEnabledTest003
 * @tc.desc: Feature enabled and pathHash in whitelist returns true.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, IsSmartLayoutPageOverflowFixEnabledTest003, TestSize.Level1)
{
    ResetStrategyState();
    auto& mgr = FeatureParamManager::GetInstance();
    mgr.smartlayoutPageOverflowFix_.enabled = true;
    mgr.smartlayoutPageOverflowFix_.values.insert("abc123");

    EXPECT_TRUE(mgr.IsSmartLayoutPageOverflowFixEnabled("abc123"));
}

/**
 * @tc.name: IsSmartLayoutPageOverflowFixEnabledTest004
 * @tc.desc: Feature enabled but pathHash not in whitelist returns false.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, IsSmartLayoutPageOverflowFixEnabledTest004, TestSize.Level1)
{
    ResetStrategyState();
    auto& mgr = FeatureParamManager::GetInstance();
    mgr.smartlayoutPageOverflowFix_.enabled = true;

    EXPECT_FALSE(mgr.IsSmartLayoutPageOverflowFixEnabled("not_in_list"));
}

/**
 * @tc.name: IsSmartLayoutWidgetSplitEnabledTest001
 * @tc.desc: Feature disabled returns false regardless of pageUrl.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, IsSmartLayoutWidgetSplitEnabledTest001, TestSize.Level1)
{
    ResetStrategyState();
    auto& mgr = FeatureParamManager::GetInstance();
    mgr.smartlayoutWidgetSplit_.enabled = false;

    EXPECT_FALSE(mgr.IsSmartLayoutWidgetSplitEnabled("any_url"));
}

/**
 * @tc.name: IsSmartLayoutWidgetSplitEnabledTest002
 * @tc.desc: Feature enabled and empty pageUrl returns true (global on).
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, IsSmartLayoutWidgetSplitEnabledTest002, TestSize.Level1)
{
    ResetStrategyState();
    auto& mgr = FeatureParamManager::GetInstance();
    mgr.smartlayoutWidgetSplit_.enabled = true;

    EXPECT_TRUE(mgr.IsSmartLayoutWidgetSplitEnabled(""));
}

/**
 * @tc.name: IsSmartLayoutWidgetSplitEnabledTest003
 * @tc.desc: Feature enabled and pageUrl in whitelist returns true.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, IsSmartLayoutWidgetSplitEnabledTest003, TestSize.Level1)
{
    ResetStrategyState();
    auto& mgr = FeatureParamManager::GetInstance();
    mgr.smartlayoutWidgetSplit_.enabled = true;
    mgr.smartlayoutWidgetSplit_.values.insert("pages/index");

    EXPECT_TRUE(mgr.IsSmartLayoutWidgetSplitEnabled("pages/index"));
}

/**
 * @tc.name: IsSmartLayoutWidgetSplitEnabledTest004
 * @tc.desc: Feature enabled but pageUrl not in whitelist returns false.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, IsSmartLayoutWidgetSplitEnabledTest004, TestSize.Level1)
{
    ResetStrategyState();
    auto& mgr = FeatureParamManager::GetInstance();
    mgr.smartlayoutWidgetSplit_.enabled = true;

    EXPECT_FALSE(mgr.IsSmartLayoutWidgetSplitEnabled("not_in_list"));
}

/**
 * @tc.name: StrategyAwareIsOverflowEnabledTest001
 * @tc.desc: IsPageOverflowEnabled returns true when strategyPageOverflowEnabled_ is true.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, StrategyAwareIsOverflowEnabledTest001, TestSize.Level1)
{
    ResetStrategyState();
    auto& mgr = FeatureParamManager::GetInstance();
    mgr.strategyPageOverflowEnabled_ = true;

    EXPECT_TRUE(mgr.IsPageOverflowEnabled());
}

/**
 * @tc.name: StrategyAwareIsOverflowEnabledTest002
 * @tc.desc: IsPageOverflowEnabled returns false when all sources are false.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, StrategyAwareIsOverflowEnabledTest002, TestSize.Level1)
{
    ResetStrategyState();

    EXPECT_FALSE(FeatureParamManager::GetInstance().IsPageOverflowEnabled());
}

/**
 * @tc.name: StrategyAwareIsOverflowEnabledTest003
 * @tc.desc: IsDialogCorrectionEnabled returns true when strategy flag is true.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, StrategyAwareIsOverflowEnabledTest003, TestSize.Level1)
{
    ResetStrategyState();
    auto& mgr = FeatureParamManager::GetInstance();
    mgr.strategyDialogOverflowEnabled_ = true;

    EXPECT_TRUE(mgr.IsDialogCorrectionEnabled());
}

/**
 * @tc.name: StrategyAwareIsOverflowEnabledTest004
 * @tc.desc: IsRnOverflowEnable returns true when strategy flag is true.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, StrategyAwareIsOverflowEnabledTest004, TestSize.Level1)
{
    ResetStrategyState();
    auto& mgr = FeatureParamManager::GetInstance();
    mgr.strategyRnOverflowEnabled_ = true;

    EXPECT_TRUE(mgr.IsRnOverflowEnable());
}

/**
 * @tc.name: SmartLayoutEnabledTest001
 * @tc.desc: SetSmartLayoutEnabled toggles IsSmartLayoutEnabled.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, SmartLayoutEnabledTest001, TestSize.Level1)
{
    FeatureParamManager::GetInstance().SetSmartLayoutEnabled(true);
    EXPECT_TRUE(FeatureParamManager::GetInstance().IsSmartLayoutEnabled());

    FeatureParamManager::GetInstance().SetSmartLayoutEnabled(false);
    EXPECT_FALSE(FeatureParamManager::GetInstance().IsSmartLayoutEnabled());
}

/**
 * @tc.name: FeatureParamForwardPageOverflowFixTest001
 * @tc.desc: FeatureParam::IsSmartLayoutPageOverflowFixEnabled forwards to FeatureParamManager.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, FeatureParamForwardPageOverflowFixTest001, TestSize.Level1)
{
    ResetStrategyState();
    auto& mgr = FeatureParamManager::GetInstance();
    mgr.smartlayoutPageOverflowFix_.enabled = true;

    // No pathHash means global switch, mirrors the FeatureParam default argument.
    EXPECT_TRUE(FeatureParam::IsSmartLayoutPageOverflowFixEnabled());

    mgr.smartlayoutPageOverflowFix_.values.insert("hash_a");
    EXPECT_TRUE(FeatureParam::IsSmartLayoutPageOverflowFixEnabled("hash_a"));
    EXPECT_FALSE(FeatureParam::IsSmartLayoutPageOverflowFixEnabled("hash_missing"));
}

/**
 * @tc.name: FeatureParamForwardPageOverflowFixTest002
 * @tc.desc: Forwarding returns false when the feature is disabled regardless of pathHash.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, FeatureParamForwardPageOverflowFixTest002, TestSize.Level1)
{
    ResetStrategyState();
    EXPECT_FALSE(FeatureParam::IsSmartLayoutPageOverflowFixEnabled());
    EXPECT_FALSE(FeatureParam::IsSmartLayoutPageOverflowFixEnabled("any"));
}

/**
 * @tc.name: FeatureParamForwardWidgetSplitTest001
 * @tc.desc: FeatureParam::IsSmartLayoutWidgetSplitEnabled forwards to FeatureParamManager.
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, FeatureParamForwardWidgetSplitTest001, TestSize.Level1)
{
    ResetStrategyState();
    auto& mgr = FeatureParamManager::GetInstance();
    mgr.smartlayoutWidgetSplit_.enabled = true;

    EXPECT_TRUE(FeatureParam::IsSmartLayoutWidgetSplitEnabled());

    mgr.smartlayoutWidgetSplit_.values.insert("pages/index");
    EXPECT_TRUE(FeatureParam::IsSmartLayoutWidgetSplitEnabled("pages/index"));
    EXPECT_FALSE(FeatureParam::IsSmartLayoutWidgetSplitEnabled("pages/other"));
}
} // namespace OHOS::Ace