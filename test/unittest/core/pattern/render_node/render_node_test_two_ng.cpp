/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include <cmath>
#include <cstdint>
#include <string>

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/common/resource/resource_object.h"
#include "core/components/theme/corner_mark_theme.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"
#include "core/components_ng/pattern/render_node/render_node_layout_property.h"
#include "core/components_ng/pattern/render_node/render_node_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/geometry_property.h"
#include "core/components_ng/property/position_property.h"
#include "core/components_ng/base/inspector.h"
#include "base/json/json_util.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const float TEST_FRAME_WIDTH = 200.0f;
const float TEST_FRAME_HEIGHT = 200.0f;
const float TEST_CONTENT_WIDTH = 100.0f;
const float TEST_CONTENT_HEIGHT = 100.0f;
const float ALIGNMENT_CENTER_HORIZONTAL = 0.5f;
constexpr char CLICK_COMMAND[] = R"({"cmd":"click"})";
constexpr char CUSTOM_COMMAND[] = R"({"cmd":"custom"})";
constexpr char SHOW_CORNER_MARK_COMMAND[] =
    R"({"cmd":"ShowCornerMark","params":{"CornerMarkIndex":88,"showCornerMarkNode":true}})";

class InjectionPattern : public Pattern {
public:
    int32_t returnCode_ = RET_FAILED;
    std::string command_;

    int32_t OnInjectionEvent(const std::string& command) override
    {
        command_ = command;
        return returnCode_;
    }
};
}

class RenderNodeTestTwoNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void RenderNodeTestTwoNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}

void RenderNodeTestTwoNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: PatternOnRecvCommand001
 * @tc.desc: Test Pattern::OnRecvCommand returns failure for invalid json.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestTwoNg, PatternOnRecvCommand001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();

    EXPECT_EQ(pattern->OnRecvCommand("invalid command"), RET_FAILED);
}

/**
 * @tc.name: PatternOnRecvCommand002
 * @tc.desc: Test Pattern::OnRecvCommand triggers click callback for click command.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestTwoNg, PatternOnRecvCommand002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = FrameNode::CreateFrameNode("pattern", 0, pattern);
    ASSERT_NE(frameNode, nullptr);

    bool clicked = false;
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(
        [&clicked](GestureEvent& info) { clicked = true; }));

    EXPECT_EQ(pattern->OnRecvCommand(CLICK_COMMAND), RET_SUCCESS);
    EXPECT_TRUE(clicked);
}

/**
 * @tc.name: PatternOnRecvCommand003
 * @tc.desc: Test Pattern::OnRecvCommand returns failure when host is disabled.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestTwoNg, PatternOnRecvCommand003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = FrameNode::CreateFrameNode("pattern", 0, pattern);
    ASSERT_NE(frameNode, nullptr);

    bool clicked = false;
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(
        [&clicked](GestureEvent& info) { clicked = true; }));
    eventHub->SetEnabled(false);

    EXPECT_EQ(pattern->OnRecvCommand(CLICK_COMMAND), RET_FAILED);
    EXPECT_FALSE(clicked);
}

/**
 * @tc.name: PatternOnRecvCommand004
 * @tc.desc: Test Pattern::OnRecvCommand falls back to OnInjectionEvent for custom command.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestTwoNg, PatternOnRecvCommand004, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<InjectionPattern>();
    pattern->returnCode_ = RET_FAILED;

    EXPECT_EQ(pattern->OnRecvCommand(CUSTOM_COMMAND), RET_FAILED);
    EXPECT_EQ(pattern->command_, CUSTOM_COMMAND);
}

/**
 * @tc.name: PatternOnRecvCommand005
 * @tc.desc: Test Pattern::OnRecvCommand handles ShowCornerMark command successfully.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestTwoNg, PatternOnRecvCommand005, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CornerMarkTheme>()));

    auto container = MockContainer::Current();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(container, nullptr);
    ASSERT_NE(pipeline, nullptr);
    container->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    pipeline->SetTaskExecutor(container->GetTaskExecutor());

    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = FrameNode::CreateFrameNode("pattern", 0, pattern);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_EQ(frameNode->GetCornerMarkNode(), nullptr);

    EXPECT_EQ(pattern->OnRecvCommand(SHOW_CORNER_MARK_COMMAND), RET_SUCCESS);

    auto cornerMarkNode = frameNode->GetCornerMarkNode();
    ASSERT_NE(cornerMarkNode, nullptr);
    auto textLayoutProperty = cornerMarkNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContent().value_or(u""), std::u16string(u"88"));
}

/**
 * @tc.name: PatternUnRegisterResource001
 * @tc.desc: Test Pattern::UnRegisterResource removes resource manager state when the last key is removed.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestTwoNg, PatternUnRegisterResource001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>("", "", -1);

    pattern->AddResObj("resource_key", resourceObject, [](const RefPtr<ResourceObject>& resObj) {});
    pattern->AddResCache("resource_key", "cache_value");
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    ASSERT_TRUE(pattern->resourceMgr_->resMap_.find("resource_key") != pattern->resourceMgr_->resMap_.end());
    ASSERT_EQ(pattern->GetResCacheMapByKey("resource_key"), "cache_value");

    pattern->UnRegisterResource("resource_key");

    EXPECT_EQ(pattern->resourceMgr_, nullptr);
    EXPECT_EQ(pattern->GetResCacheMapByKey("resource_key"), "");
}

/**
 * @tc.name: RenderNodeLayoutAlgorithmTest007
 * @tc.desc: Test Layout when GetPositionProperty returns null (branch1 false path)
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestTwoNg, RenderNodeLayoutAlgorithmTest007, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("frame", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto renderNodeLayoutAlgorithm = AceType::MakeRefPtr<RenderNodeLayoutAlgorithm>();
    
    SizeF frameSize(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    geometryNode->SetFrameSize(frameSize);
    
    layoutWrapper->GetLayoutProperty()->positionProperty_ = nullptr;
    layoutWrapper->GetGeometryNode()->content_ = nullptr;
    
    renderNodeLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->GetFrameSize(), frameSize);
}

/**
 * @tc.name: RenderNodeLayoutAlgorithmTest008
 * @tc.desc: Test Layout when content is not null (branch2 true path)
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestTwoNg, RenderNodeLayoutAlgorithmTest008, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("frame", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto renderNodeLayoutAlgorithm = AceType::MakeRefPtr<RenderNodeLayoutAlgorithm>();
    
    SizeF frameSize(TEST_FRAME_WIDTH, TEST_FRAME_HEIGHT);
    geometryNode->SetFrameSize(frameSize);
    
    layoutWrapper->GetLayoutProperty()->positionProperty_ = nullptr;
    
    auto content = std::make_unique<GeometryProperty>();
    SizeF contentSize(TEST_CONTENT_WIDTH, TEST_CONTENT_HEIGHT);
    content->SetSize(contentSize);
    layoutWrapper->GetGeometryNode()->content_ = std::move(content);
    
    renderNodeLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    
    auto contentOffset = geometryNode->GetContentOffset();
    EXPECT_EQ(contentOffset, OffsetF(0, 0));
}

/**
 * @tc.name: RenderNodeLayoutPropertyTest001
 * @tc.desc: Test ToJsonValue when filter is fast filter (branch1 true)
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestTwoNg, RenderNodeLayoutPropertyTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("frame", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<RenderNodeLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    
    InspectorFilter filter;
    filter.AddFilterAttr("id");
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_TRUE(filter.IsFastFilter());
}

/**
 * @tc.name: RenderNodeLayoutPropertyTest002
 * @tc.desc: Test ToJsonValue when filter is not fast filter and position property is null
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestTwoNg, RenderNodeLayoutPropertyTest002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("frame", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<RenderNodeLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    
    layoutProperty->positionProperty_ = nullptr;
    
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_FALSE(filter.IsFastFilter());
    auto alignContent = json->GetString("alignContent");
    EXPECT_EQ(alignContent, "Alignment.TopStart");
}

/**
 * @tc.name: RenderNodeLayoutPropertyTest003
 * @tc.desc: Test ToJsonValue when filter is not fast filter and position property exists
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestTwoNg, RenderNodeLayoutPropertyTest003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("frame", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<RenderNodeLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    
    layoutProperty->positionProperty_ = std::make_unique<PositionProperty>();
    Alignment align;
    align.horizontal_ = ALIGNMENT_CENTER_HORIZONTAL;
    layoutProperty->positionProperty_->UpdateAlignment(align);
    
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_FALSE(filter.IsFastFilter());
    auto alignContent = json->GetString("alignContent");
    EXPECT_EQ(alignContent, "Alignment.Center");
}

/**
 * @tc.name: RenderNodeLayoutPropertyTest004
 * @tc.desc: Test FromJson with different alignment values
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestTwoNg, RenderNodeLayoutPropertyTest004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("frame", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<RenderNodeLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    
    auto json = JsonUtil::Create(true);
    json->Put("alignContent", "Alignment.TopStart");
    layoutProperty->FromJson(json);
    
    ASSERT_NE(layoutProperty->positionProperty_, nullptr);
    auto alignment = layoutProperty->positionProperty_->GetAlignment();
    ASSERT_TRUE(alignment.has_value());
    EXPECT_EQ(alignment.value().horizontal_, 0.0f);
}
} // namespace OHOS::Ace::NG
