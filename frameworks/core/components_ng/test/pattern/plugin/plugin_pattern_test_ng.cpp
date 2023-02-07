/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <memory>
#include <optional>

#include "gtest/gtest.h"

#include "base/memory/referenced.h"
#define private public
#define protected public

#include "base/memory/ace_type.h"
#include "core/components/plugin/plugin_sub_container.h"
#include "core/components/plugin/resource/plugin_manager_delegate.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/plugin/plugin_layout_property.h"
#include "core/components_ng/pattern/plugin/plugin_model_ng.h"
#include "core/components_ng/pattern/plugin/plugin_node.h"
#include "core/components_ng/pattern/plugin/plugin_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct CreateProperty {
    std::optional<double> maxValue = std::nullopt;
    std::optional<double> value = std::nullopt;
};

struct TestProperty {};

namespace {
PluginModelNG pluginModel;
RequestPluginInfo pluginInfo;
} // namespace

class pluginPatternTestNg : public testing::Test {
public:
    void CheckValue(const RefPtr<FrameNode>& frameNode, const TestProperty& testProperty);
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}

protected:
    RefPtr<FrameNode> CreatePluginParagraph();
};

void pluginPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
    pluginInfo.pluginName = "plugin1";
    pluginInfo.bundleName = "com.example.plugin";
}

void pluginPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> pluginPatternTestNg::CreatePluginParagraph()
{
    pluginModel.Create(pluginInfo);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

/**
 * @tc.name: PluginNodeTest001
 * @tc.desc: Test all function of plugin_node.
 * @tc.type: FUNC
 */
HWTEST_F(pluginPatternTestNg, PluginNodeTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = PluginNode::GetOrCreatePluginNode(
        "PluginComponentNone", stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<PluginPattern>(); });
}

/**
 * @tc.name: pluginPattern001
 * @tc.desc: Test SplitString in Plugin Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(pluginPatternTestNg, SplitString, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    EXPECT_NE(pattern, nullptr);
    std::vector<std::string> strList;
    pattern->SplitString("com.example.providerTest/assets", '/', strList);
    std::vector<std::string> strList2 = { "com.example.providerTest", "assets" };
    EXPECT_EQ(strList, strList2);
}
} // namespace OHOS::Ace::NG
