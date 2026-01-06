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

#include <optional>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/adapter/mock_ui_session_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/manager/content_change_manager/content_change_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INITIAL_NODE_SIZE = 5;
constexpr int32_t INITIAL_NODE_SIZE_PLUS_ONE = INITIAL_NODE_SIZE + 1;
constexpr int32_t NORMAL_NODE_ID = 0;
constexpr int32_t TEST_SCROLLING_NODE_ID = 100;
constexpr int32_t NEVER_ONCE = 0;
constexpr int32_t AT_LEAST_ONCE = 1;
constexpr int32_t AT_LEAST_TWICE = 2;
constexpr int32_t AT_LEAST_THREE_TIMES = 3;

RefPtr<ContentChangeManager> GetContentChangeManager()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    return pipeline ? pipeline->GetContentChangeManager() : nullptr;
}

MockUiSessionManager* GetMockUiSessionManager()
{
    return reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
}

std::string GetSimpleTree(const RefPtr<FrameNode>& node)
{
    auto simpleTree = JsonUtil::CreateSharedPtrJson(true);
    node->DumpSimplifyTreeWithParamConfig(0, simpleTree, false, {false, false, false});
    return simpleTree->ToString();
}

std::string GetDialogSimpleTree(const RefPtr<FrameNode>& node, bool isShow)
{
    auto simpleTree = JsonUtil::CreateSharedPtrJson(true);
    if (isShow) {
        node->DumpSimplifyTreeWithParamConfig(0, simpleTree, false, {false, false, false});
    } else {
        simpleTree->Put("$type", node->GetTag().c_str());
    }
    simpleTree->Put("show", isShow);
    return simpleTree->ToString();
}

void SetOnContentChangeNodes()
{
    auto contentChangeMgr = GetContentChangeManager();
    if (contentChangeMgr) {
        for (int32_t i = 0; i < INITIAL_NODE_SIZE; i++) {
            auto node = FrameNode::CreateFrameNode("frameNode", i, AceType::MakeRefPtr<Pattern>(), true);
            auto weak = AceType::WeakClaim(AceType::RawPtr(node));
            contentChangeMgr->onContentChangeNodes_.emplace(weak);
        }
    }
}

void ResetOnContentChangeNodes()
{
    auto contentChangeMgr = GetContentChangeManager();
    if (contentChangeMgr) {
        contentChangeMgr->onContentChangeNodes_.clear();
    }
}

void SetScrollingNodes()
{
    auto contentChangeMgr = GetContentChangeManager();
    if (contentChangeMgr) {
        contentChangeMgr->scrollingNodes_.emplace(TEST_SCROLLING_NODE_ID);
    }
}

void ResetScrollingNodes()
{
    auto contentChangeMgr = GetContentChangeManager();
    if (contentChangeMgr) {
        contentChangeMgr->scrollingNodes_.clear();
    }
}

void SetChangedSwiperNodes()
{
    auto contentChangeMgr = GetContentChangeManager();
    if (contentChangeMgr) {
        for (int32_t i = 0; i < INITIAL_NODE_SIZE; i++) {
            auto node = FrameNode::CreateFrameNode("frameNode", i, AceType::MakeRefPtr<Pattern>(), true);
            auto weak = AceType::WeakClaim(AceType::RawPtr(node));
            bool flag = (i % 2 == 0);
            contentChangeMgr->changedSwiperNodes_.emplace(std::make_pair(weak, flag));
        }
    }
}

void ResetChangedSwiperNodes()
{
    auto contentChangeMgr = GetContentChangeManager();
    if (contentChangeMgr) {
        contentChangeMgr->changedSwiperNodes_.clear();
    }
}
} // namespace

class ContentChangeManagerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ContentChangeManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void ContentChangeManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ContentChangeManagerTest001
 * @tc.desc: Test config.textContentRatio validity
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);
    const float DEFAULT_TEXT_CONTENT_RATIO = contentChangeMgr->DEFAULT_TEXT_CONTENT_RATIO;

    /**
     * @tc.steps: step2. call StartContentChangeReport when textContentRatio is less than 0.0.
     * @tc.expected: textContentRatio is set to default value.
     */
    ContentChangeConfig config;
    config.textContentRatio = -0.5f;
    contentChangeMgr->StartContentChangeReport(config);
    std::optional<ContentChangeConfig> currentConfig = contentChangeMgr->currentContentChangeConfig_;
    ASSERT_TRUE(currentConfig.has_value());
    EXPECT_FLOAT_EQ(currentConfig->textContentRatio, DEFAULT_TEXT_CONTENT_RATIO);
    EXPECT_FLOAT_EQ(contentChangeMgr->textContentRatio_, DEFAULT_TEXT_CONTENT_RATIO);

    /**
     * @tc.steps: step3. call StartContentChangeReport when textContentRatio is greater than 1.0.
     * @tc.expected: textContentRatio is set to default value.
     */
    config.textContentRatio = 1.5f;
    contentChangeMgr->StartContentChangeReport(config);
    currentConfig = contentChangeMgr->currentContentChangeConfig_;
    ASSERT_TRUE(currentConfig.has_value());
    EXPECT_FLOAT_EQ(currentConfig->textContentRatio, DEFAULT_TEXT_CONTENT_RATIO);
    EXPECT_FLOAT_EQ(contentChangeMgr->textContentRatio_, DEFAULT_TEXT_CONTENT_RATIO);

    /**
     * @tc.steps: step4. call StartContentChangeReport when textContentRatio is valid.
     * @tc.expected: textContentRatio is set accordingly.
     */
    config.textContentRatio = 0.0f;
    contentChangeMgr->StartContentChangeReport(config);
    currentConfig = contentChangeMgr->currentContentChangeConfig_;
    ASSERT_TRUE(currentConfig.has_value());
    EXPECT_FLOAT_EQ(currentConfig->textContentRatio, 0.0f);
    EXPECT_FLOAT_EQ(contentChangeMgr->textContentRatio_, 0.0f);

    config.textContentRatio = 0.1f;
    contentChangeMgr->StartContentChangeReport(config);
    currentConfig = contentChangeMgr->currentContentChangeConfig_;
    ASSERT_TRUE(currentConfig.has_value());
    EXPECT_FLOAT_EQ(currentConfig->textContentRatio, 0.1f);
    EXPECT_FLOAT_EQ(contentChangeMgr->textContentRatio_, 0.1f);

    config.textContentRatio = 1.0f;
    contentChangeMgr->StartContentChangeReport(config);
    currentConfig = contentChangeMgr->currentContentChangeConfig_;
    ASSERT_TRUE(currentConfig.has_value());
    EXPECT_FLOAT_EQ(currentConfig->textContentRatio, 1.0f);
    EXPECT_FLOAT_EQ(contentChangeMgr->textContentRatio_, 1.0f);

    /**
     * @tc.steps: step5. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
}

/**
 * @tc.name: ContentChangeManagerTest002
 * @tc.desc: Test config.minReportTime validity
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);
    const float DEFAULT_TEXT_MIN_REPORT_TIME = contentChangeMgr->DEFAULT_TEXT_MIN_REPORT_TIME;
    const uint64_t NS_PER_MS = contentChangeMgr->NS_PER_MS;

    /**
     * @tc.steps: step2. call StartContentChangeReport when minReportTime is less than 0.
     * @tc.expected: minReportTime is set to default value.
     */
    ContentChangeConfig config;
    config.minReportTime = -1;
    contentChangeMgr->StartContentChangeReport(config);
    std::optional<ContentChangeConfig> currentConfig = contentChangeMgr->currentContentChangeConfig_;
    ASSERT_TRUE(currentConfig.has_value());
    EXPECT_EQ(currentConfig->minReportTime, DEFAULT_TEXT_MIN_REPORT_TIME);
    EXPECT_EQ(contentChangeMgr->textContentInterval_, DEFAULT_TEXT_MIN_REPORT_TIME * NS_PER_MS);

    /**
     * @tc.steps: step3. call StartContentChangeReport when minReportTime is valid.
     * @tc.expected: minReportTime is set accordingly.
     */
    config.minReportTime = 200;
    contentChangeMgr->StartContentChangeReport(config);
    currentConfig = contentChangeMgr->currentContentChangeConfig_;
    ASSERT_TRUE(currentConfig.has_value());
    EXPECT_EQ(currentConfig->minReportTime, 200);
    EXPECT_EQ(contentChangeMgr->textContentInterval_, 200 * NS_PER_MS);

    /**
     * @tc.steps: step4. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
}

/**
 * @tc.name: ContentChangeManagerTest003
 * @tc.desc: Test StartContentChangeReport, StopContentChangeReport
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);

    /**
     * @tc.steps: step2. test add one node.
     * @tc.expected: size is correct.
     */
    SetOnContentChangeNodes();
    auto node = FrameNode::CreateFrameNode("frameNode", INITIAL_NODE_SIZE, AceType::MakeRefPtr<Pattern>(), true);
    auto weak = AceType::WeakClaim(AceType::RawPtr(node));
    contentChangeMgr->onContentChangeNodes_.emplace(weak);
    weak.Reset();
    auto size = static_cast<int32_t>(contentChangeMgr->onContentChangeNodes_.size());
    EXPECT_EQ(size, INITIAL_NODE_SIZE_PLUS_ONE);

    /**
     * @tc.steps: step3. test StartContentChangeReport.
     * @tc.expected: IsContentChangeDetectEnable returns true.
     */
    ContentChangeConfig config;
    contentChangeMgr->StartContentChangeReport(config);
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());

    /**
     * @tc.steps: step4. test StopContentChangeReport.
     * @tc.expected: IsContentChangeDetectEnable returns false.
     */
    contentChangeMgr->StopContentChangeReport();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());

    /**
     * @tc.steps: step5. reset.
     */
    ResetOnContentChangeNodes();
    size = static_cast<int32_t>(contentChangeMgr->onContentChangeNodes_.size());
    EXPECT_EQ(size, 0);
}

/**
 * @tc.name: ContentChangeManagerTest004
 * @tc.desc: Test AddOnContentChangeNode, RemoveOnContentChangeNode
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);

    /**
     * @tc.steps: step2. test AddOnContentChangeNode.
     * @tc.expected: size is correct.
     */
    SetOnContentChangeNodes();
    auto node = FrameNode::CreateFrameNode("frameNode", INITIAL_NODE_SIZE, AceType::MakeRefPtr<Pattern>(), true);
    auto weak = AceType::WeakClaim(AceType::RawPtr(node));
    contentChangeMgr->AddOnContentChangeNode(weak);
    auto size = static_cast<int32_t>(contentChangeMgr->onContentChangeNodes_.size());
    EXPECT_EQ(size, INITIAL_NODE_SIZE_PLUS_ONE);

    /**
     * @tc.steps: step3. test RemoveOnContentChangeNode.
     * @tc.expected: size is correct.
     */
    contentChangeMgr->RemoveOnContentChangeNode(weak);
    size = static_cast<int32_t>(contentChangeMgr->onContentChangeNodes_.size());
    EXPECT_EQ(size, INITIAL_NODE_SIZE);

    /**
     * @tc.steps: step4. when IsContentChangeDetectEnable, test AddOnContentChangeNode.
     * @tc.expected: size is correct.
     */
    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->AddOnContentChangeNode(weak);
    size = static_cast<int32_t>(contentChangeMgr->onContentChangeNodes_.size());
    EXPECT_EQ(size, INITIAL_NODE_SIZE_PLUS_ONE);

    /**
     * @tc.steps: step5. reset.
     */
    ResetOnContentChangeNodes();
    size = static_cast<int32_t>(contentChangeMgr->onContentChangeNodes_.size());
    EXPECT_EQ(size, 0);
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
}

/**
 * @tc.name: ContentChangeManagerTest005
 * @tc.desc: Test OnPageTransitionEnd
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);
    auto node = FrameNode::CreateFrameNode("frameNode", NORMAL_NODE_ID, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    auto mockUiSessionManager = GetMockUiSessionManager();
    ASSERT_NE(mockUiSessionManager, nullptr);
    auto simpleTree = GetSimpleTree(node);

    /**
     * @tc.steps: step2. call OnPageTransitionEnd under abnormal conditions.
     * @tc.expected: ReportContentChangeEvent never called.
     */
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(_, _))
        .Times(NEVER_ONCE);
    contentChangeMgr->OnPageTransitionEnd(nullptr);

    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(_, _))
        .Times(NEVER_ONCE);
    contentChangeMgr->OnPageTransitionEnd(nullptr);

    SetScrollingNodes();
    EXPECT_TRUE(contentChangeMgr->IsScrolling());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(_, _))
        .Times(NEVER_ONCE);
    contentChangeMgr->OnPageTransitionEnd(node);
    ResetScrollingNodes();

    /**
     * @tc.steps: step3. call OnPageTransitionEnd under normal conditions.
     * @tc.expected: ReportContentChangeEvent called once.
     */
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_FALSE(contentChangeMgr->IsScrolling());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::PAGE, simpleTree))
        .Times(AtLeast(AT_LEAST_ONCE));
    contentChangeMgr->OnPageTransitionEnd(node);

    /**
     * @tc.steps: step4. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
}

/**
 * @tc.name: ContentChangeManagerTest006
 * @tc.desc: Test OnScrollChangeEnd
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);
    auto node = FrameNode::CreateFrameNode("frameNode", NORMAL_NODE_ID, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    auto mockUiSessionManager = GetMockUiSessionManager();
    ASSERT_NE(mockUiSessionManager, nullptr);

    /**
     * @tc.steps: step2. call OnScrollChangeEnd under abnormal conditions.
     * @tc.expected: ReportContentChangeEvent never called.
     */
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(_, _))
        .Times(NEVER_ONCE);
    contentChangeMgr->OnScrollChangeEnd(nullptr);

    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->scrollingNodes_.emplace(node->GetId());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(_, _))
        .Times(NEVER_ONCE);
    contentChangeMgr->OnScrollChangeEnd(node);
    EXPECT_EQ(static_cast<int32_t>(contentChangeMgr->scrollingNodes_.count(node->GetId())), 0);

    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    SetScrollingNodes();
    contentChangeMgr->scrollingNodes_.emplace(node->GetId());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(_, _))
        .Times(NEVER_ONCE);
    contentChangeMgr->OnScrollChangeEnd(node);
    ResetScrollingNodes();

    /**
     * @tc.steps: step3. call OnScrollChangeEnd under normal conditions.
     * @tc.expected: ReportContentChangeEvent called once.
     */
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->scrollingNodes_.emplace(node->GetId());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SCROLL, ""))
        .Times(AtLeast(AT_LEAST_ONCE));
    contentChangeMgr->OnScrollChangeEnd(node);

    /**
     * @tc.steps: step4. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
}

/**
 * @tc.name: ContentChangeManagerTest007
 * @tc.desc: Test OnSwiperChangeEnd
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);
    auto node = FrameNode::CreateFrameNode("frameNode", NORMAL_NODE_ID, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);

    /**
     * @tc.steps: step2. call OnSwiperChangeEnd under abnormal conditions.
     * @tc.expected: changedSwiperNodes_ is empty.
     */
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->OnSwiperChangeEnd(nullptr, false);
    EXPECT_TRUE(contentChangeMgr->changedSwiperNodes_.empty());

    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->OnSwiperChangeEnd(nullptr, false);
    EXPECT_TRUE(contentChangeMgr->changedSwiperNodes_.empty());

    SetScrollingNodes();
    EXPECT_TRUE(contentChangeMgr->IsScrolling());
    contentChangeMgr->OnSwiperChangeEnd(node, false);
    ResetScrollingNodes();
    EXPECT_TRUE(contentChangeMgr->changedSwiperNodes_.empty());

    /**
     * @tc.steps: step3. call OnSwiperChangeEnd under normal conditions.
     * @tc.expected: changedSwiperNodes_ is not empty.
     */
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_FALSE(contentChangeMgr->IsScrolling());
    contentChangeMgr->OnSwiperChangeEnd(node, false);
    EXPECT_FALSE(contentChangeMgr->changedSwiperNodes_.empty());

    /**
     * @tc.steps: step4. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->changedSwiperNodes_.clear();
    EXPECT_TRUE(contentChangeMgr->changedSwiperNodes_.empty());
}

/**
 * @tc.name: ContentChangeManagerTest008
 * @tc.desc: Test OnDialogChangeEnd
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);
    auto node = FrameNode::CreateFrameNode("frameNode", NORMAL_NODE_ID, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);
    auto mockUiSessionManager = GetMockUiSessionManager();
    ASSERT_NE(mockUiSessionManager, nullptr);
    auto showSimpleTree = GetDialogSimpleTree(node, true);
    auto notShowSimpleTree = GetDialogSimpleTree(node, false);

    /**
     * @tc.steps: step2. call OnDialogChangeEnd under abnormal conditions.
     * @tc.expected: ReportContentChangeEvent never called.
     */
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(_, _))
        .Times(NEVER_ONCE);
    contentChangeMgr->OnDialogChangeEnd(nullptr, true);

    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(_, _))
        .Times(NEVER_ONCE);
    contentChangeMgr->OnDialogChangeEnd(nullptr, true);

    SetScrollingNodes();
    EXPECT_TRUE(contentChangeMgr->IsScrolling());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(_, _))
        .Times(NEVER_ONCE);
    contentChangeMgr->OnDialogChangeEnd(node, true);
    ResetScrollingNodes();

    /**
     * @tc.steps: step3. call OnDialogChangeEnd under normal conditions.
     * @tc.expected: ReportContentChangeEvent called once.
     */
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_FALSE(contentChangeMgr->IsScrolling());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::DIALOG, showSimpleTree))
        .Times(AtLeast(AT_LEAST_ONCE));
    contentChangeMgr->OnDialogChangeEnd(node, true);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::DIALOG, notShowSimpleTree))
        .Times(AtLeast(AT_LEAST_ONCE));
    contentChangeMgr->OnDialogChangeEnd(node, false);

    /**
     * @tc.steps: step4. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
}

/**
 * @tc.name: ContentChangeManagerTest009
 * @tc.desc: Test OnTextChangeEnd
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);
    RectF rect1(0.0, 0.0, 10.0, 10.0);
    RectF rect2(0.0, 0.0, 5.0, 20.0);
    RectF emptyRect(0.0, 0.0, 0.0, 0.0);

    /**
     * @tc.steps: step2. call OnTextChangeEnd under abnormal conditions.
     * @tc.expected: textAABB_ is empty.
     */
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->OnTextChangeEnd(emptyRect);
    EXPECT_TRUE(contentChangeMgr->textAABB_.IsEmpty());

    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_FALSE(contentChangeMgr->textCollecting_);
    contentChangeMgr->OnTextChangeEnd(emptyRect);
    EXPECT_TRUE(contentChangeMgr->textAABB_.IsEmpty());

    contentChangeMgr->textCollecting_ = true;
    contentChangeMgr->OnTextChangeEnd(emptyRect);
    EXPECT_TRUE(contentChangeMgr->textAABB_.IsEmpty());

    SetScrollingNodes();
    EXPECT_TRUE(contentChangeMgr->IsScrolling());
    contentChangeMgr->OnTextChangeEnd(rect1);
    EXPECT_TRUE(contentChangeMgr->textAABB_.IsEmpty());
    ResetScrollingNodes();

    /**
     * @tc.steps: step3. call OnTextChangeEnd under normal conditions.
     * @tc.expected: textAABB_ is not empty and combined correctly.
     */
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_TRUE(contentChangeMgr->textCollecting_);
    EXPECT_FALSE(contentChangeMgr->IsScrolling());
    contentChangeMgr->OnTextChangeEnd(rect1);
    EXPECT_FALSE(contentChangeMgr->textAABB_.IsEmpty());
    EXPECT_FLOAT_EQ(contentChangeMgr->textAABB_.GetX(), 0.0);
    EXPECT_FLOAT_EQ(contentChangeMgr->textAABB_.GetY(), 0.0);
    EXPECT_FLOAT_EQ(contentChangeMgr->textAABB_.Width(), 10.0);
    EXPECT_FLOAT_EQ(contentChangeMgr->textAABB_.Height(), 10.0);

    contentChangeMgr->OnTextChangeEnd(rect2);
    EXPECT_FALSE(contentChangeMgr->textAABB_.IsEmpty());
    EXPECT_FLOAT_EQ(contentChangeMgr->textAABB_.GetX(), 0.0);
    EXPECT_FLOAT_EQ(contentChangeMgr->textAABB_.GetY(), 0.0);
    EXPECT_FLOAT_EQ(contentChangeMgr->textAABB_.Width(), 10.0);
    EXPECT_FLOAT_EQ(contentChangeMgr->textAABB_.Height(), 20.0);

    /**
     * @tc.steps: step4. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->textCollecting_ = false;
    contentChangeMgr->textAABB_.Reset();
    EXPECT_TRUE(contentChangeMgr->textAABB_.IsEmpty());
}

/**
 * @tc.name: ContentChangeManagerTest010
 * @tc.desc: Test OnVsyncStart
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);

    /**
     * @tc.steps: step2. test OnVsyncStart.
     * @tc.expected: StartTextAABBCollecting called accordingly.
     */
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->OnVsyncStart();
    EXPECT_FALSE(contentChangeMgr->textCollecting_);

    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_FALSE(contentChangeMgr->textCollecting_);
    EXPECT_FALSE(contentChangeMgr->IsScrolling());
    contentChangeMgr->OnVsyncStart();
    EXPECT_TRUE(contentChangeMgr->textCollecting_);

    /**
     * @tc.steps: step3. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->textCollecting_ = false;
}

/**
 * @tc.name: ContentChangeManagerTest011
 * @tc.desc: Test OnVsyncEnd
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);
    RectF rootRect(0.0, 0.0, 100.0, 100.0);
    RectF notIntersectRect(150.0, 150.0, 10.0, 10.0);

    /**
     * @tc.steps: step2. test OnVsyncEnd when StopTextAABBCollecting called.
     * @tc.expected: StopTextAABBCollecting called accordingly.
     */
    contentChangeMgr->textAABB_ = notIntersectRect;
    contentChangeMgr->textCollecting_ = true;
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->OnVsyncEnd(rootRect);
    EXPECT_FALSE(contentChangeMgr->textAABB_.IsEmpty());
    EXPECT_TRUE(contentChangeMgr->textCollecting_);

    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_FALSE(contentChangeMgr->textAABB_.IsEmpty());
    EXPECT_FALSE(contentChangeMgr->IsScrolling());
    contentChangeMgr->OnVsyncEnd(rootRect);
    EXPECT_TRUE(contentChangeMgr->textAABB_.IsEmpty());
    EXPECT_FALSE(contentChangeMgr->textCollecting_);

    /**
     * @tc.steps: step3. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
}

/**
 * @tc.name: ContentChangeManagerTest012
 * @tc.desc: Test OnVsyncEnd
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);
    RectF rootRect(0.0, 0.0, 100.0, 100.0);
    auto mockUiSessionManager = GetMockUiSessionManager();
    ASSERT_NE(mockUiSessionManager, nullptr);

    /**
     * @tc.steps: step2. test add one node.
     * @tc.expected: size is correct.
     */
    SetChangedSwiperNodes();
    auto node = FrameNode::CreateFrameNode("frameNode", INITIAL_NODE_SIZE, AceType::MakeRefPtr<Pattern>(), true);
    auto weak = AceType::WeakClaim(AceType::RawPtr(node));
    contentChangeMgr->changedSwiperNodes_.emplace(std::make_pair(weak, false));
    weak.Reset();
    auto size = static_cast<int32_t>(contentChangeMgr->changedSwiperNodes_.size());
    EXPECT_EQ(size, INITIAL_NODE_SIZE_PLUS_ONE);

    /**
     * @tc.steps: step3. test OnVsyncEnd when changedSwiperNodes_ is not empty.
     * @tc.expected: ReportContentChangeEvent called accordingly.
     */
    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::TABS, _))
        .Times(AtLeast(AT_LEAST_THREE_TIMES));
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SWIPER, _))
        .Times(AtLeast(AT_LEAST_TWICE));
    contentChangeMgr->OnVsyncEnd(rootRect);

    /**
     * @tc.steps: step4. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    ResetChangedSwiperNodes();
    size = static_cast<int32_t>(contentChangeMgr->changedSwiperNodes_.size());
    EXPECT_EQ(size, 0);
}

/**
 * @tc.name: ContentChangeManagerTest013
 * @tc.desc: Test StartTextAABBCollecting
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);

    /**
     * @tc.steps: step2. call StartTextAABBCollecting under abnormal conditions.
     * @tc.expected: textCollecting_ is not set true.
     */
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->StartTextAABBCollecting();
    EXPECT_FALSE(contentChangeMgr->textCollecting_);

    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->textCollecting_ = true;
    contentChangeMgr->StartTextAABBCollecting();
    contentChangeMgr->textCollecting_ = false;

    SetScrollingNodes();
    EXPECT_TRUE(contentChangeMgr->IsScrolling());
    contentChangeMgr->StartTextAABBCollecting();
    EXPECT_FALSE(contentChangeMgr->textCollecting_);
    ResetScrollingNodes();

    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_FALSE(contentChangeMgr->textCollecting_);
    EXPECT_FALSE(contentChangeMgr->IsScrolling());
    contentChangeMgr->lastTextReportTime_ = GetSysTimestamp();
    EXPECT_TRUE(GetSysTimestamp() - contentChangeMgr->lastTextReportTime_ < contentChangeMgr->textContentInterval_);
    contentChangeMgr->StartTextAABBCollecting();
    EXPECT_FALSE(contentChangeMgr->textCollecting_);
    contentChangeMgr->lastTextReportTime_ = 0;

    /**
     * @tc.steps: step3. call StartTextAABBCollecting under normal conditions.
     * @tc.expected: textCollecting_ is set true.
     */
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_FALSE(contentChangeMgr->textCollecting_);
    EXPECT_FALSE(contentChangeMgr->IsScrolling());
    EXPECT_FALSE(GetSysTimestamp() - contentChangeMgr->lastTextReportTime_ < contentChangeMgr->textContentInterval_);
    contentChangeMgr->StartTextAABBCollecting();
    EXPECT_TRUE(contentChangeMgr->textCollecting_);

    /**
     * @tc.steps: step4. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->textCollecting_ = false;
}

/**
 * @tc.name: ContentChangeManagerTest014
 * @tc.desc: Test StopTextAABBCollecting
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);
    RectF rootRect(0.0, 0.0, 100.0, 100.0);
    RectF notIntersectRect(150.0, 150.0, 10.0, 10.0);

    /**
     * @tc.steps: step2. call StopTextAABBCollecting under abnormal conditions.
     * @tc.expected: textAABB_ and textCollecting_ is not reset.
     */
    contentChangeMgr->textCollecting_ = true;
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->StopTextAABBCollecting(rootRect);
    EXPECT_TRUE(contentChangeMgr->textCollecting_);

    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_TRUE(contentChangeMgr->textAABB_.IsEmpty());
    contentChangeMgr->StopTextAABBCollecting(rootRect);
    EXPECT_TRUE(contentChangeMgr->textCollecting_);

    contentChangeMgr->textAABB_ = notIntersectRect;
    EXPECT_FALSE(contentChangeMgr->textAABB_.IsEmpty());
    SetScrollingNodes();
    EXPECT_TRUE(contentChangeMgr->IsScrolling());
    contentChangeMgr->StopTextAABBCollecting(rootRect);
    EXPECT_FALSE(contentChangeMgr->textAABB_.IsEmpty());
    EXPECT_TRUE(contentChangeMgr->textCollecting_);
    ResetScrollingNodes();

    /**
     * @tc.steps: step3. call StopTextAABBCollecting under normal conditions.
     * @tc.expected: textAABB_ and textCollecting_ is reset.
     */
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_FALSE(contentChangeMgr->textAABB_.IsEmpty());
    EXPECT_FALSE(contentChangeMgr->IsScrolling());
    contentChangeMgr->StopTextAABBCollecting(rootRect);
    EXPECT_TRUE(contentChangeMgr->textAABB_.IsEmpty());
    EXPECT_FALSE(contentChangeMgr->textCollecting_);

    /**
     * @tc.steps: step4. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
}

/**
 * @tc.name: ContentChangeManagerTest015
 * @tc.desc: Test StopTextAABBCollecting
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);
    RectF rootRect(0.0, 0.0, 100.0, 100.0);
    RectF intersectRect(0.0, 0.0, 10.0, 10.0);
    auto mockUiSessionManager = GetMockUiSessionManager();
    ASSERT_NE(mockUiSessionManager, nullptr);
    auto originRatio = contentChangeMgr->textContentRatio_;

    /**
     * @tc.steps: step2. rootRect should intersect with textAABB_.
     */
    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->textAABB_ = intersectRect;
    EXPECT_FALSE(contentChangeMgr->textAABB_.IsEmpty());
    EXPECT_FALSE(contentChangeMgr->IsScrolling());
    EXPECT_TRUE(rootRect.IsIntersectWith(contentChangeMgr->textAABB_));

    /**
     * @tc.steps: step3. call StopTextAABBCollecting when below the ratio.
     * @tc.expected: textAABB_ and textCollecting_ is reset.
     */
    contentChangeMgr->textContentRatio_ = 1.0f;
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(_, _))
        .Times(NEVER_ONCE);
    contentChangeMgr->StopTextAABBCollecting(rootRect);
    EXPECT_EQ(contentChangeMgr->lastTextReportTime_, 0);
    EXPECT_TRUE(contentChangeMgr->textAABB_.IsEmpty());
    EXPECT_FALSE(contentChangeMgr->textCollecting_);

    /**
     * @tc.steps: step4. call StopTextAABBCollecting when below the ratio.
     * @tc.expected: textAABB_ and textCollecting_ is reset.
     */
    contentChangeMgr->textContentRatio_ = 0.0f;
    contentChangeMgr->textAABB_ = intersectRect;
    EXPECT_FALSE(contentChangeMgr->textAABB_.IsEmpty());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::TEXT, ""))
        .Times(AtLeast(AT_LEAST_ONCE));
    contentChangeMgr->StopTextAABBCollecting(rootRect);
    EXPECT_NE(contentChangeMgr->lastTextReportTime_, 0);
    EXPECT_TRUE(contentChangeMgr->textAABB_.IsEmpty());
    EXPECT_FALSE(contentChangeMgr->textCollecting_);

    /**
     * @tc.steps: step5. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->textContentRatio_ = originRatio;
}

/**
 * @tc.name: ContentChangeManagerTest016
 * @tc.desc: Test OnScrollChangeStart
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);
    auto node = FrameNode::CreateFrameNode("frameNode", NORMAL_NODE_ID, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(node, nullptr);

    /**
     * @tc.steps: step2. call OnScrollChangeStart under abnormal conditions.
     * @tc.expected: scrollingNodes_ is empty.
     */
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->OnScrollChangeStart(nullptr);
    EXPECT_TRUE(contentChangeMgr->scrollingNodes_.empty());

    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->OnScrollChangeStart(nullptr);
    EXPECT_TRUE(contentChangeMgr->scrollingNodes_.empty());

    /**
     * @tc.steps: step3. call OnScrollChangeStart under normal conditions.
     * @tc.expected: scrollingNodes_ is not empty.
     */
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    EXPECT_FALSE(contentChangeMgr->IsScrolling());
    contentChangeMgr->OnScrollChangeStart(node);
    EXPECT_FALSE(contentChangeMgr->scrollingNodes_.empty());

    /**
     * @tc.steps: step4. reset.
     */
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
    ResetScrollingNodes();
    EXPECT_TRUE(contentChangeMgr->scrollingNodes_.empty());
}

/**
 * @tc.name: ContentChangeManagerTest017
 * @tc.desc: Test OnScrollRemoved
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager.
     * @tc.expected: contentChangeMgr is not nullptr.
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);

    /**
     * @tc.steps: step2. test OnScrollRemoved.
     * @tc.expected: scrollingNodes_ is empty.
     */
    SetScrollingNodes();
    EXPECT_FALSE(contentChangeMgr->scrollingNodes_.empty());

    contentChangeMgr->OnScrollRemoved(NORMAL_NODE_ID);
    contentChangeMgr->OnScrollRemoved(TEST_SCROLLING_NODE_ID);
    EXPECT_TRUE(contentChangeMgr->scrollingNodes_.empty());
}
} // namespace OHOS::Ace::NG
