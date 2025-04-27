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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "ui/resource/resource_parser.h"

#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Kit;
namespace OHOS::Ace {
class ResourceParserTest : public testing::Test {
    public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    }
    static void TearDownTestSuite()
    {
        MockContainer::Current()->pipelineContext_ = nullptr;
        NG::MockPipelineContext::TearDown();
    }
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: ResourceParserTestTest001
 * @tc.desc: Test GetDimension when option is empty
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest001, TestSize.Level1)
{
    Kit::ResourceInfo info;
    info.bundleName = "";
    info.moduleName = "";
    Ace::Dimension dimension;
    auto result = ResourceParser::GetDimension(info, dimension);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResourceParserTestTest002
 * @tc.desc: Test GetDimension when resId is unknown
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest002, TestSize.Level1)
{
    Kit::ResourceInfo info;
    info.resId = UNKNOWN_RESOURCE_ID;
    info.params.push_back("param");
    Ace::Dimension dimension;
    auto result = ResourceParser::GetDimension(info, dimension);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ResourceParserTestTest003
 * @tc.desc: Test GetDimension when resId is known
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest003, TestSize.Level1)
{
    Kit::ResourceInfo info;
    info.resId = 123;
    Ace::Dimension dimension;
    auto result = ResourceParser::GetDimension(info, dimension);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ResourceParserTestTest004
 * @tc.desc: Test GetColor when option is empty
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest004, TestSize.Level1)
{
    Kit::ResourceInfo info;
    info.bundleName = "";
    info.moduleName = "module";
    Ace::Color color;
    auto result = ResourceParser::GetColor(info, color);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResourceParserTestTest005
 * @tc.desc: Test GetColor when resource ID is unknown
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest005, TestSize.Level1)
{
    Kit::ResourceInfo info;
    info.resId = UNKNOWN_RESOURCE_ID;
    info.params.push_back("param");
    Ace::Color color;
    auto result = ResourceParser::GetColor(info, color);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ResourceParserTestTest006
 * @tc.desc: Test GetColor when resource ID is invalid
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest006, TestSize.Level1)
{
    Kit::ResourceInfo info;
    info.resId = 123;
    Ace::Color color;
    auto result = ResourceParser::GetColor(info, color);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ResourceParserTestTest007
 * @tc.desc: Test GetString when option is empty
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest007, TestSize.Level1)
{
    Kit::ResourceInfo info;
    info.resId = UNKNOWN_RESOURCE_ID;
    std::string str;
    auto result = ResourceParser::GetString(info, str);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ResourceParserTestTest008
 * @tc.desc: Test GetString when resource ID is unknown
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest008, TestSize.Level1)
{
    Kit::ResourceInfo info;
    info.resId = UNKNOWN_RESOURCE_ID;
    info.params.push_back("param");
    std::string str;
    auto result = ResourceParser::GetString(info, str);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ResourceParserTestTest009
 * @tc.desc: Test GetString when resource ID is known
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest009, TestSize.Level1)
{
    Kit::ResourceInfo info;
    info.resId = 123;
    std::string str;
    auto result = ResourceParser::GetString(info, str);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ResourceParserTestTest010
 * @tc.desc: Test GetMediaPath when different states of resource
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest010, TestSize.Level1)
{
    Kit::ResourceInfo info;
    std::string mediaPath;
    auto result = ResourceParser::GetMediaPath(info, mediaPath);
    EXPECT_FALSE(result);
    info.bundleName = "bundle";
    info.moduleName = "module";
    result = ResourceParser::GetMediaPath(info, mediaPath);
    EXPECT_TRUE(result);
    info.resId = UNKNOWN_RESOURCE_ID;
    info.params.push_back("param");
    result = ResourceParser::GetMediaPath(info, mediaPath);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResourceParserTestTest011
 * @tc.desc: Test GetInt when different states of resource
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest011, TestSize.Level1)
{
    Kit::ResourceInfo info;
    int32_t value;
    auto result = ResourceParser::GetInt(info, value);
    EXPECT_FALSE(result);
    info.bundleName = "bundle";
    info.moduleName = "module";
    result = ResourceParser::GetInt(info, value);
    EXPECT_TRUE(result);
    info.resId = UNKNOWN_RESOURCE_ID;
    info.params.push_back("param");
    result = ResourceParser::GetInt(info, value);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResourceParserTestTest012
 * @tc.desc: Test GetDouble when different states of resource
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest012, TestSize.Level1)
{
    Kit::ResourceInfo info;
    double value;
    auto result = ResourceParser::GetDouble(info, value);
    EXPECT_FALSE(result);
    info.bundleName = "bundle";
    info.moduleName = "module";
    result = ResourceParser::GetDouble(info, value);
    EXPECT_TRUE(result);
    info.resId = UNKNOWN_RESOURCE_ID;
    info.params.push_back("param");
    result = ResourceParser::GetDouble(info, value);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResourceParserTestTest013
 * @tc.desc: Test GetPluralString when different states of resource
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest013, TestSize.Level1)
{
    Kit::ResourceInfo info;
    int value = 0;
    std::string plural;
    auto result = ResourceParser::GetPluralString(info, value, plural);
    EXPECT_FALSE(result);
    info.bundleName = "bundle";
    info.moduleName = "module";
    result = ResourceParser::GetPluralString(info, value, plural);
    EXPECT_TRUE(result);
    info.resId = UNKNOWN_RESOURCE_ID;
    info.params.push_back("param");
    result = ResourceParser::GetPluralString(info, value, plural);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResourceParserTestTest014
 * @tc.desc: Test GetBoolean when different states of resource
 * @tc.type: Func
 */
HWTEST_F(ResourceParserTest, ResourceParserTestTest014, TestSize.Level1)
{
    Kit::ResourceInfo info;
    bool value;
    auto result = ResourceParser::GetBoolean(info, value);
    EXPECT_FALSE(result);
    info.bundleName = "bundle";
    info.moduleName = "module";
    result = ResourceParser::GetBoolean(info, value);
    EXPECT_TRUE(result);
    info.resId = UNKNOWN_RESOURCE_ID;
    info.params.push_back("param");
    result = ResourceParser::GetBoolean(info, value);
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace

