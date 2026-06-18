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
} // namespace OHOS::Ace