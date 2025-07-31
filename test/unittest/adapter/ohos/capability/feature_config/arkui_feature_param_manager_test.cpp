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
};

/**
 * @tc.name: InitTest001
 * @tc.desc: ArkUIFeatureParamManagerTest::Init
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, InitTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Parse example.hap success
     * @tc.expected: Create featureParser suc
     */
    FeatureParamManager::GetInstance().Init("example.hap");
    auto& featureParser = OHOS::Ace::FeatureParamManager::GetInstance().featureParser_;
    EXPECT_NE(featureParser, nullptr);
    EXPECT_NE(featureParser->xmlSysDocument_, nullptr);
    featureParser->Destroy();
}

/**
 * @tc.name: ParseInternalWithBundleNameTest
 * @tc.desc: FeatureParamManager test
 * @tc.type: FUNC
 */
HWTEST_F(ArkUIFeatureParamManagerTest, ParseInternalWithBundleNameTest, TestSize.Level1)
{
    FeatureParamManager::GetInstance().Init("example.hap");
    auto& featureParser = FeatureParamManager::GetInstance().featureParser_;
    xmlNode node;
    auto ret = featureParser->ParseInternalWithBundleName(node, "example.hap");
    EXPECT_EQ(ret, ParseErrCode::PARSE_XML_NAME_ERROR);

    string nodeName = "PerformanceOptConfig";
    node.name = reinterpret_cast<const xmlChar*>(nodeName.c_str());
    xmlNode childNode;
    childNode.type = xmlElementType::XML_ELEMENT_NODE;
    string childName = "bundleName";
    childNode.name = reinterpret_cast<const xmlChar*>(childName.c_str());
    xmlSetProp(&childNode, (const xmlChar*)("name"), (const xmlChar*)("example.hap"));
    node.children = &childNode;

    xmlNode childNode1;
    childNode1.type = xmlElementType::XML_ELEMENT_NODE;
    string child1Name = "feature";
    childNode1.name = reinterpret_cast<const xmlChar*>(child1Name.c_str());
    xmlSetProp(&childNode1, (const xmlChar*)("id"), (const xmlChar*)("UINodeGcParamParser"));
    childNode.children = &childNode1;
    ret = featureParser->ParseInternalWithBundleName(node, "example.hap");
    EXPECT_EQ(ret, ParseErrCode::PARSE_EXEC_SUCCESS);
    featureParser->Destroy();
}
}