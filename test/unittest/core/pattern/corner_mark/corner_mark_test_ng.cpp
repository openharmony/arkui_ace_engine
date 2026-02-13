/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/theme/corner_mark_theme.h"
#include "core/components_ng/pattern/corner_mark/corner_mark.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {} // namespace

class CornerMarkTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void CornerMarkTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CornerMarkTheme>()));
}
void CornerMarkTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ResponseShowCornerMarkEvent
 * @tc.desc: Test ResponseShowCornerMarkEvent function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, ResponseShowCornerMarkEvent, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(frameNode, nullptr);
    auto cornerMarkNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(cornerMarkNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    std::string value;
    int32_t result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_FAILED);
    value = "";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_FAILED);
    value = "{\"smarap\":{\"cornerMarkIndex\":,\"showCornerMarkNode\":true}}";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_FAILED);
    value = "{\"smarap\":{\"cornerMarkIndex\":88,\"showCornerMarkNode\":true}}";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_FAILED);
    value = "{\"smarap\":{\"cornerMarkIndex\":-1,\"showCornerMarkNode\":true}}";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_FAILED);
    value = "{\"smarap\":{\"cornerMarkIndex\":100,\"showCornerMarkNode\":true}}";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_FAILED);
    value = "{\"params\":{\"cornerMarkIndex\":\"true\",\"showCornerMarkNode\":true}}";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_SUCCESS);
    value = "{\"params\":{\"cornerMarkIndex\":true,\"showCornerMarkNode\":}}";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_FAILED);
    value = "{\"params\":{\"cornerMarkIndex\":88,\"showCornerMarkNode\":99}}";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_FAILED);
    value = "{\"params\":{\"cornerMarkIndex\":88,\"showCornerMarkNode\":true}}";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_SUCCESS);
    value = "{\"params\":{\"cornerMarkIndex\":88,\"showCornerMarkNode\":false}}";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_SUCCESS);
    frameNode->SetCornerMarkNode(cornerMarkNode);
    value = "{\"params\":{\"cornerMarkIndex\":88,\"showCornerMarkNode\":true}}";
    result = cornerMark->ResponseShowCornerMarkEvent(frameNode, value);
    EXPECT_EQ(result, RET_SUCCESS);
}

/**
 * @tc.name: AddCornerMarkNode001
 * @tc.desc: Test AddCornerMarkNode function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, AddCornerMarkNode001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    auto container = Container::CurrentSafely();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto pipelineContainer = Container::GetContainer(pipelineContext->instanceId_);
    ASSERT_NE(pipelineContainer, nullptr);
    pipelineContainer->colorMode_ = ColorMode::DARK;
    std::string index = "88";
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    frameNode->geometryNode_ = geometryNode;
    int32_t result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_NE(frameNode->GetCornerMarkNode(), nullptr);
    auto textLayoutProperty = frameNode->GetCornerMarkNode()->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto indexString = textLayoutProperty->GetContent();
    EXPECT_EQ(indexString.has_value(), true);
    std::u16string value = u"88";
    EXPECT_EQ(indexString.value(), value);
}

/**
 * @tc.name: AddCornerMarkNode002
 * @tc.desc: Test AddCornerMarkNode function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, AddCornerMarkNode002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    auto container = Container::CurrentSafely();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto pipelineContainer = Container::GetContainer(pipelineContext->instanceId_);
    ASSERT_NE(pipelineContainer, nullptr);
    pipelineContainer->colorMode_ = ColorMode::LIGHT;
    std::string index = "88";
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    auto geometryNode = nullptr;
    frameNode->geometryNode_ = geometryNode;
    int32_t result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_NE(frameNode->GetCornerMarkNode(), nullptr);
    auto textLayoutProperty = frameNode->GetCornerMarkNode()->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto indexString = textLayoutProperty->GetContent();
    EXPECT_EQ(indexString.has_value(), true);
    std::u16string value = u"88";
    EXPECT_EQ(indexString.value(), value);
}

/**
 * @tc.name: AddCornerMarkNode003
 * @tc.desc: Test AddCornerMarkNode function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, AddCornerMarkNode003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    auto container = Container::CurrentSafely();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto pipelineContainer = Container::GetContainer(pipelineContext->instanceId_);
    ASSERT_NE(pipelineContainer, nullptr);
    pipelineContainer->colorMode_ = ColorMode::LIGHT;
    std::string index = "88";
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    auto geometryNode = nullptr;
    frameNode->geometryNode_ = geometryNode;
    int32_t result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_NE(frameNode->GetCornerMarkNode(), nullptr);
    auto textLayoutProperty = frameNode->GetCornerMarkNode()->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto indexString = textLayoutProperty->GetContent();
    EXPECT_EQ(indexString.has_value(), true);
    std::u16string value = u"88";
    EXPECT_EQ(indexString.value(), value);
}

/**
 * @tc.name: UpdateCornerMarkNode
 * @tc.desc: Test UpdateCornerMarkNode function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, UpdateCornerMarkNode, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    std::string index = "88";
    int32_t result = cornerMark->UpdateCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_FAILED);
    result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    index = "66";
    result = cornerMark->UpdateCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    auto textLayoutProperty = frameNode->GetCornerMarkNode()->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto indexString = textLayoutProperty->GetContent();
    EXPECT_EQ(indexString.has_value(), true);
    std::u16string value = u"66";
    EXPECT_EQ(indexString.value(), value);
}

/**
 * @tc.name: RemoveCornerMarkNode
 * @tc.desc: Test RemoveCornerMarkNode function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, RemoveCornerMarkNode, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    int32_t result = cornerMark->RemoveCornerMarkNode(frameNode);
    EXPECT_EQ(result, RET_FAILED);
    std::string index = "88";
    result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    result = cornerMark->RemoveCornerMarkNode(frameNode);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_EQ(frameNode->GetCornerMarkNode(), nullptr);
}

/**
 * @tc.name: UpdateCornerMarkNodeLanguage001
 * @tc.desc: Test UpdateCornerMarkNodeLanguage function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, UpdateCornerMarkNodeLanguage001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    std::string index = "88";
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    frameNode->geometryNode_ = geometryNode;
    int32_t result = cornerMark->AddCornerMarkNode(frameNode, index);
    cornerMark->UpdateCornerMarkNodeLanguage(frameNode);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_NE(frameNode->GetCornerMarkNode(), nullptr);
    auto textLayoutProperty = frameNode->GetCornerMarkNode()->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto indexString = textLayoutProperty->GetContent();
    EXPECT_EQ(indexString.has_value(), true);
    std::u16string value = u"88";
    EXPECT_EQ(indexString.value(), value);
}

/**
 * @tc.name: UpdateCornerMarkNodeLanguage002
 * @tc.desc: Test UpdateCornerMarkNodeLanguage function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, UpdateCornerMarkNodeLanguage002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    std::string index = "88";
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    frameNode->geometryNode_ = nullptr;
    int32_t result = cornerMark->AddCornerMarkNode(frameNode, index);
    cornerMark->UpdateCornerMarkNodeLanguage(frameNode);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_NE(frameNode->GetCornerMarkNode(), nullptr);
    auto textLayoutProperty = frameNode->GetCornerMarkNode()->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto indexString = textLayoutProperty->GetContent();
    EXPECT_EQ(indexString.has_value(), true);
    std::u16string value = u"88";
    EXPECT_EQ(indexString.value(), value);
}

/**
 * @tc.name: UpdateCornerMarkNodeLanguage003
 * @tc.desc: Test UpdateCornerMarkNodeLanguage function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, UpdateCornerMarkNodeLanguage003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    std::string index = "88";
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    int32_t result = cornerMark->AddCornerMarkNode(frameNode, index);
    cornerMark->UpdateCornerMarkNodeLanguage(frameNode);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_NE(frameNode->GetCornerMarkNode(), nullptr);
    auto textLayoutProperty = frameNode->GetCornerMarkNode()->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto indexString = textLayoutProperty->GetContent();
    EXPECT_EQ(indexString.has_value(), true);
    std::u16string value = u"88";
    EXPECT_EQ(indexString.value(), value);
}

/**
 * @tc.name: UpdateCornerMarkNodeColorMode001
 * @tc.desc: Test UpdateCornerMarkNodeColorMode function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, UpdateCornerMarkNodeColorMode001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    auto container = Container::CurrentSafely();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto pipelineContainer = Container::GetContainer(pipelineContext->instanceId_);
    ASSERT_NE(pipelineContainer, nullptr);
    pipelineContainer->colorMode_ = ColorMode::DARK;
    std::string index = "88";
    int32_t result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_NE(frameNode->GetCornerMarkNode(), nullptr);
    auto textLayoutProperty = frameNode->GetCornerMarkNode()->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto indexString = textLayoutProperty->GetContent();
    EXPECT_EQ(indexString.has_value(), true);
    std::u16string value = u"88";
    EXPECT_EQ(indexString.value(), value);
}

/**
 * @tc.name: UpdateCornerMarkNodeColorMode002
 * @tc.desc: Test UpdateCornerMarkNodeColorMode function
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, UpdateCornerMarkNodeColorMode002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    auto container = Container::CurrentSafely();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto pipelineContainer = Container::GetContainer(pipelineContext->instanceId_);
    ASSERT_NE(pipelineContainer, nullptr);
    pipelineContainer->colorMode_ = ColorMode::LIGHT;
    std::string index = "88";
    int32_t result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    EXPECT_NE(frameNode->GetCornerMarkNode(), nullptr);
    auto textLayoutProperty = frameNode->GetCornerMarkNode()->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto indexString = textLayoutProperty->GetContent();
    EXPECT_EQ(indexString.has_value(), true);
    std::u16string value = u"88";
    EXPECT_EQ(indexString.value(), value);
}
/**
 * @tc.name: UpdateCornerMarkNodePosition001
 * @tc.desc: Test UpdateCornerMarkNodePosition in non-RTL mode, should early return
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, UpdateCornerMarkNodePosition001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    std::string index = "88";
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    int32_t result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    auto markNode = frameNode->GetCornerMarkNode();
    ASSERT_NE(markNode, nullptr);
    auto markGeometryNode = markNode->GetGeometryNode();
    ASSERT_NE(markGeometryNode, nullptr);
    auto offsetBefore = markGeometryNode->GetFrameOffset();

    // Non-RTL: should early return without changing geometry
    CornerMark::UpdateCornerMarkNodePosition(frameNode);
    EXPECT_EQ(markGeometryNode->GetFrameOffset(), offsetBefore);
}

/**
 * @tc.name: UpdateCornerMarkNodePosition002
 * @tc.desc: Test UpdateCornerMarkNodePosition in RTL mode without corner mark node
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, UpdateCornerMarkNodePosition002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    EXPECT_EQ(frameNode->GetCornerMarkNode(), nullptr);

    // RTL but no corner mark node: should not crash
    CornerMark::UpdateCornerMarkNodePosition(frameNode);
    EXPECT_EQ(frameNode->GetCornerMarkNode(), nullptr);
}

/**
 * @tc.name: UpdateCornerMarkNodePosition003
 * @tc.desc: Test UpdateCornerMarkNodePosition in RTL mode with corner mark node,
 *           verify geometry is synced to correct position in current frame
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, UpdateCornerMarkNodePosition003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);

    // Set up host geometry with a known width
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    constexpr float hostWidth = 200.0f;
    geometryNode->SetFrameSize(SizeF(hostWidth, 100.0f));
    frameNode->geometryNode_ = geometryNode;

    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    std::string index = "1";
    int32_t result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);
    auto markNode = frameNode->GetCornerMarkNode();
    ASSERT_NE(markNode, nullptr);

    // Call UpdateCornerMarkNodePosition
    CornerMark::UpdateCornerMarkNodePosition(frameNode);

    // Verify geometry was synced directly (not deferred)
    auto markGeometryNode = markNode->GetGeometryNode();
    ASSERT_NE(markGeometryNode, nullptr);
    auto container = Container::CurrentSafely();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto cornerMarkTheme = pipelineContext->GetTheme<CornerMarkTheme>();
    ASSERT_NE(cornerMarkTheme, nullptr);
    auto markWidth = cornerMarkTheme->GetWidth().ConvertToPx();
    auto markHeight = cornerMarkTheme->GetHeight().ConvertToPx();
    auto expectedLeft = hostWidth - markWidth;

    EXPECT_EQ(markGeometryNode->GetFrameOffset(), OffsetF(expectedLeft, 0.0f));
    EXPECT_EQ(markGeometryNode->GetFrameSize(), SizeF(markWidth, markHeight));

    // Verify layoutRect was also updated
    auto textLayoutProperty = markNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto layoutRect = textLayoutProperty->GetLayoutRect();
    ASSERT_TRUE(layoutRect.has_value());
    EXPECT_EQ(layoutRect.value(), RectF(expectedLeft, 0.0f, markWidth, markHeight));
}

/**
 * @tc.name: UpdateCornerMarkNodePosition004
 * @tc.desc: Test UpdateCornerMarkNodePosition in RTL mode with null geometryNode on host
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, UpdateCornerMarkNodePosition004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);
    std::string index = "1";
    int32_t result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);

    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    // Set host geometryNode to null
    frameNode->geometryNode_ = nullptr;

    // Should not crash, early return at CHECK_NULL_VOID(geometryNode)
    CornerMark::UpdateCornerMarkNodePosition(frameNode);
    EXPECT_NE(frameNode->GetCornerMarkNode(), nullptr);
}

/**
 * @tc.name: UpdateCornerMarkNodePosition005
 * @tc.desc: Test UpdateCornerMarkNodePosition updates correctly when host width changes
 * @tc.type: FUNC
 */
HWTEST_F(CornerMarkTestNg, UpdateCornerMarkNodePosition005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto cornerMark = AceType::MakeRefPtr<CornerMark>();
    ASSERT_NE(cornerMark, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    constexpr float initalWidth = 300.0f;
    geometryNode->SetFrameSize(SizeF(initalWidth, 100.0f));
    frameNode->geometryNode_ = geometryNode;

    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    std::string index = "5";
    int32_t result = cornerMark->AddCornerMarkNode(frameNode, index);
    EXPECT_EQ(result, RET_SUCCESS);

    auto container = Container::CurrentSafely();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto cornerMarkTheme = pipelineContext->GetTheme<CornerMarkTheme>();
    ASSERT_NE(cornerMarkTheme, nullptr);
    auto markWidth = cornerMarkTheme->GetWidth().ConvertToPx();
    auto markHeight = cornerMarkTheme->GetHeight().ConvertToPx();

    // First call with initial width
    CornerMark::UpdateCornerMarkNodePosition(frameNode);
    auto markNode = frameNode->GetCornerMarkNode();
    ASSERT_NE(markNode, nullptr);
    auto markGeometryNode = markNode->GetGeometryNode();
    ASSERT_NE(markGeometryNode, nullptr);
    EXPECT_EQ(markGeometryNode->GetFrameOffset(), OffsetF(initalWidth - markWidth, 0.0f));

    // Simulate host width change (e.g. during animation)
    constexpr float newWidth = 500.0f;
    geometryNode->SetFrameSize(SizeF(newWidth, 100.0f));
    CornerMark::UpdateCornerMarkNodePosition(frameNode);
    EXPECT_EQ(markGeometryNode->GetFrameOffset(), OffsetF(newWidth - markWidth, 0.0f));
    EXPECT_EQ(markGeometryNode->GetFrameSize(), SizeF(markWidth, markHeight));
}
} // namespace OHOS::Ace::NG