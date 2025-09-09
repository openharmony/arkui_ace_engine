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
#include "adapter/ohos/capability/feature_config/config_xml_parser_base.h"
#include "adapter/ohos/capability/feature_config/feature_param_manager.h"
#undef private
#undef protected
using namespace testing;
using namespace testing::ext;

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
};

/**
 * @tc.name: InitTest001
 * @tc.desc: ArkUIFeatureParamManagerTest::Init
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, InitTest, TestSize.Level1)
{
    FeatureParamManager::GetInstance().Init(TEST1_HAP);
    auto& featureParser = FeatureParamManager::GetInstance().featureParser_;
    EXPECT_NE(featureParser, nullptr);

    FeatureParamManager::GetInstance().Init(TEST1_HAP);
    EXPECT_NE(featureParser, nullptr);
}

/**
 * @tc.name: ParseInternalWithBundleNameTest
 * @tc.desc: FeatureParamManager test
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseInternalWithBundleNameTest, TestSize.Level1)
{
    FeatureParamManager::GetInstance().Init(TEST1_HAP);
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
    auto featureParser = std::make_unique<ConfigXMLParserBase>();
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
    auto featureParser = std::make_unique<ConfigXMLParserBase>();
    xmlNode node;
    auto ret = featureParser->ParseXmlNodeNameWithIndex(node, 4);
    EXPECT_EQ(ret, ParseErrCode::PARSE_SIZE_ERROR);
    featureParser = nullptr;
}
}