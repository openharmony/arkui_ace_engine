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

#include <cstddef>
#include <optional>
#include <memory>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "mock/mock_form_utils.h"
#include "mock/mock_sub_container.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/form/form_node.h"
#include "core/components_ng/pattern/form/form_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MAX_CLICK_DURATION = 500000000; // ns
constexpr int32_t FORM_SHAPE_CIRCLE = 2;
}
class FormPatternTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
protected:
    static RefPtr<FormNode> CreateFromNode();
};

void FormPatternTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void FormPatternTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FormNode> FormPatternTest::CreateFromNode()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto formNode = FormNode::GetOrCreateFormNode(
        "FormComponent", stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<FormPattern>(); });
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->frameNode_ = formNode;
    return formNode;
}

/**
 * @tc.name: FormPatternTest_001
 * @tc.desc: OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_001, TestSize.Level1)
{
    RefPtr<FormNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->scopeId_, 0);
    auto  host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    pattern->frameNode_ = nullptr;
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->scopeId_, 0);
    pattern->frameNode_ = host;

    auto eventHub = host->GetEventHub<FormEventHub>();
    host->eventHub_ = nullptr;
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->scopeId_, 0);
    host->eventHub_ = eventHub;
  
    host = pattern->GetHost();
    pattern->frameNode_ = nullptr;
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->scopeId_, 0);
    pattern->frameNode_ = host;


    RefPtr<SubContainer> subContainer = pattern->subContainer_;
    pattern->subContainer_ = nullptr;
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->scopeId_, 0);
    pattern->subContainer_ = subContainer;
}

/**
 * @tc.name: FormPatternTest_002
 * @tc.desc: InitClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_002, TestSize.Level1)
{
    RefPtr<FormPattern> pattern;
    RefPtr<FrameNode>  host = pattern->GetHost();
    pattern->frameNode_ = nullptr;
    pattern->InitClickEvent();
    EXPECT_EQ(pattern->scopeId_, 0);
    pattern->frameNode_ = host;

    size_t eventNum = host->GetOrCreateGestureEventHub()->touchEventActuator_->touchEvents_.size();
    pattern->InitClickEvent();
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    size_t curEventNum = gestureEventHub->touchEventActuator_->touchEvents_.size();
    EXPECT_EQ(curEventNum, eventNum + 1);
}

/**
 * @tc.name: FormPatternTest_003
 * @tc.desc: HandleTouchDownEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_003, TestSize.Level1)
{
    RefPtr<FormNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    pattern->OnAttachToFrameNode();
    pattern->InitClickEvent();

    TouchEventInfo event("onTouchDown");
    std::list<TouchLocationInfo> touchesBak = event.GetTouches();
    ASSERT_EQ(touchesBak.empty(), true);
    std::list<TouchLocationInfo> touches;
    event.touches_ = std::move(touches);
    pattern->HandleTouchDownEvent(event);
    EXPECT_EQ(pattern->lastTouchLocation_, Offset());

    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    event.AddTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleUnTrustForm();
    pattern->UpdateBackgroundColorWhenUnTrustForm();
    pattern->HandleTouchDownEvent(event);
    ASSERT_EQ(event.GetTouches().empty(), false);
}

/**
 * @tc.name: FormPatternTest_004
 * @tc.desc: HandleTouchUpEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_004, TestSize.Level1)
{
    RefPtr<FormNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_FALSE(pattern->shouldResponseClick_);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    pattern->OnAttachToFrameNode();
    pattern->InitClickEvent();

    pattern->shouldResponseClick_ = true;
    TouchEventInfo event("onTouchUp");
    TimeStamp timeStamp = event.timeStamp_;
    std::chrono::duration<long, std::ratio<1, 1000>> millisecondDuration(MAX_CLICK_DURATION/1000000 + 10);
    event.timeStamp_ = pattern->touchDownTime_ +  millisecondDuration;
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::UP);
    event.AddTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleTouchUpEvent(event);
    ASSERT_EQ(pattern->shouldResponseClick_, false);
    event.timeStamp_ = timeStamp;
    pattern->shouldResponseClick_ = true;

    std::list<TouchLocationInfo> newTouches;
    std::list<TouchLocationInfo> touches = event.GetTouches();
    EXPECT_EQ(touches.empty(), false);
    event.touches_ = std::move(newTouches);
    pattern->HandleTouchUpEvent(event);
    ASSERT_EQ(pattern->shouldResponseClick_, true);
    event.touches_ = touches;
    pattern->shouldResponseClick_ = true;

    event.touches_.begin()->screenLocation_ += Offset(30, 30);
    pattern->HandleTouchUpEvent(event);
    ASSERT_EQ(pattern->shouldResponseClick_, false);
    pattern->shouldResponseClick_ = true;

    event.touches_.begin()->screenLocation_ -= Offset(30, 30);
    pattern->HandleTouchUpEvent(event);
    ASSERT_EQ(pattern->shouldResponseClick_, true);
    pattern->shouldResponseClick_ = false;
}

/**
 * @tc.name: FormPatternTest_005
 * @tc.desc: HandleUnTrustForm
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_005, TestSize.Level1)
{
    RefPtr<FormNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    TouchEventInfo event("onTouchDown");
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    event.AddTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleUnTrustForm();
    pattern->UpdateBackgroundColorWhenUnTrustForm();
    pattern->HandleTouchDownEvent(event);
    ASSERT_EQ(event.GetTouches().empty(), false);
}

/**
 * @tc.name: FormPatternTest_006
 * @tc.desc: UpdateBackgroundColorWhenUnTrustForm
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_006, TestSize.Level1)
{
    RefPtr<FormPattern> pattern;
    pattern->isUnTrust_ = false;
    pattern->UpdateBackgroundColorWhenUnTrustForm();
    EXPECT_FALSE(pattern->isLoaded_);

    ASSERT_EQ(pattern->colorMode, ColorMode::LIGHT);
    pattern->isUnTrust_ = true;
    pattern->UpdateBackgroundColorWhenUnTrustForm();
    EXPECT_FALSE(pattern->isLoaded_);

    pattern->colorMode = ColorMode::COLOR_MODE_UNDEFINED;
    pattern->UpdateBackgroundColorWhenUnTrustForm();
    EXPECT_TRUE(pattern->isLoaded_);
}

/**
 * @tc.name: FormPatternTest_007
 * @tc.desc: HandleSnapshot
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_007, TestSize.Level1)
{
    RefPtr<FormNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);

    int32_t delayTime = 0;
    pattern->HandleSnapshot(delayTime);
    ASSERT_EQ(delayTime, 0);
}

/**
 * @tc.name: FormPatternTest_008
 * @tc.desc: HandleStaticFormEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_008, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);

    PointF touchPoint;
    touchPoint.SetX(-5.0f);
    touchPoint.SetY(5.0f);
    std::vector<std::string> infos;
    pattern->SetFormLinkInfos(infos);
    pattern->HandleStaticFormEvent(touchPoint);
    ASSERT_EQ(pattern->formLinkInfos_.empty(), true);
    ASSERT_TRUE(pattern->isDynamic_);
    ASSERT_FALSE(pattern->shouldResponseClick_);

    pattern->isDynamic_ = false;
    pattern->SetFormLinkInfos(infos);
    ASSERT_TRUE(pattern->formLinkInfos_.empty());

    pattern->shouldResponseClick_ = false;
    pattern->HandleStaticFormEvent(touchPoint);
    ASSERT_EQ(pattern->formLinkInfos_.empty(), true);

    std::string tmpStr = "action";
    infos.emplace_back(tmpStr);
    pattern->SetFormLinkInfos(infos);
    pattern->shouldResponseClick_ = true;
    pattern->HandleStaticFormEvent(touchPoint);
    ASSERT_EQ(pattern->formLinkInfos_.empty(), false);
}

/**
 * @tc.name: FormPatternTest_009
 * @tc.desc: HandleEnableForm
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_009, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);

    auto* stack = ViewStackProcessor::GetInstance();
    auto formNode1 = FormNode::GetOrCreateFormNode(
        "FormComponent", stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<FormPattern>(); });
    
    std::vector<std::string> infos;
    std::string tmpStr = "action";
    infos.emplace_back(tmpStr);
    RequestFormInfo info;
    info.shape = FORM_SHAPE_CIRCLE;
    ASSERT_NE(pattern->formManagerBridge_, nullptr);
    pattern->SetFormLinkInfos(infos);
    pattern->HandleEnableForm(true);

    RefPtr<FrameNode> textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<OHOS::Ace::NG::LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE, columnNode);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_TEXT_NODE, textNode);
    EXPECT_EQ(pattern->formChildrenNodeMap_.size(), 2);
    pattern->HandleEnableForm(true);
    EXPECT_EQ(pattern->formChildrenNodeMap_.size(), 0);

    RefPtr<FrameNode> textNode2 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode2, nullptr);
    RefPtr<FrameNode> columnNode2 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<OHOS::Ace::NG::LinearLayoutPattern>(true));
    ASSERT_NE(columnNode2, nullptr);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE, columnNode2);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_TEXT_NODE, textNode2);
    pattern->HandleEnableForm(false);
    EXPECT_EQ(pattern->formChildrenNodeMap_.size(), 2);
}

/**
 * @tc.name: FormPatternTest_010
 * @tc.desc: TakeSurfaceCaptureForUI
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_010, TestSize.Level1)
{
    RefPtr<FrameNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);

    std::vector<std::string> infos;
    std::string tmpStr = "action";
    infos.emplace_back(tmpStr);
    pattern->SetFormLinkInfos(infos);
    pattern->HandleEnableForm(true);

    pattern->isFrsNodeDetached_ = true;
    pattern->isDynamic_ = true;
    pattern->TakeSurfaceCaptureForUI();
    ASSERT_EQ(pattern->formLinkInfos_.empty(), false);

    pattern->isFrsNodeDetached_ = false;
    pattern->isDynamic_ = true;
    pattern->TakeSurfaceCaptureForUI();
    ASSERT_EQ(pattern->formLinkInfos_.empty(), true);
}

/**
 * @tc.name: FormPatternTest_011
 * @tc.desc: SnapshotSurfaceNode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_011, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    pattern->SnapshotSurfaceNode();
    ASSERT_NE(host, nullptr);
}

/**
 * @tc.name: FormPatternTest_012
 * @tc.desc: OnSnapshot
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest, FormPatternTest_012, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->frameNode_ = formNode;
    ASSERT_NE(pattern, nullptr);

    std::vector<std::string> infos;
    std::string tmpStr = "action";
    infos.emplace_back(tmpStr);
    pattern->SetFormLinkInfos(infos);
    std::shared_ptr<Media::PixelMap> pixelMap = nullptr;
    pattern->OnSnapshot(pixelMap);
    pattern->HandleOnSnapshot(pixelMap);
    ASSERT_EQ(pattern->isSnapshot_, false);
}
} // namespace OHOS::Ace::NG