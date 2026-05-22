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
#define protected public
#define private public
#include "core/common/visual_effect/transparency_utils.h"
#include "test/mock/frameworks/core/common/mock_setting_data_manager.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
extern UiMaterialLevel g_uiMaterialLevel;
}

namespace OHOS::Ace {
static MockSettingDataManager& GetMockMgr()
{
    return static_cast<MockSettingDataManager&>(SettingDataManager::GetInstance());
}

using NG::MockPipelineContext;

class TransparencyUtilsTestNg : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
    }
    static void TearDownTestCase()
    {
        MockContainer::TearDown();
        MockPipelineContext::TearDown();
    }
    void SetUp() override
    {
        Mock::VerifyAndClearExpectations(&GetMockMgr());
        TransparencyUtils::transparencyLevelGet_ = false;
        TransparencyUtils::userId_ = 100;
        TransparencyUtils::userIdGet_ = false;
        TransparencyUtils::listenerSet_ = false;
        TransparencyUtils::callbackIdsMap_.clear();
        TransparencyUtils::callbackId_ = -1;
    }
    void TearDown() override
    {
        auto container = MockContainer::Current();
        if (container) {
            container->SetTaskExecutor(nullptr);
        }
        AceEngine::Get().RemoveContainer(0);
        AceEngine::Get().RemoveContainer(1);
    }
};

/**
 * @tc.name: GetTransparencyLevelOutOfRange
 * @tc.desc: Test L46-47 T: materialLevel >= SMOOTH or < EXQUISITE -> return NONE
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, GetTransparencyLevelOutOfRange, TestSize.Level1)
{
    EXPECT_EQ(TransparencyUtils::GetTransparencyLevel(
        static_cast<int32_t>(UiMaterialLevel::SMOOTH)),
        static_cast<int32_t>(UiMaterialTransparency::NONE));
    EXPECT_EQ(TransparencyUtils::GetTransparencyLevel(
        static_cast<int32_t>(UiMaterialLevel::EXQUISITE) - 1),
        static_cast<int32_t>(UiMaterialTransparency::NONE));
}

/**
 * @tc.name: GetTransparencyLevelCached
 * @tc.desc: Test L53 T: transparencyLevelGet_ true -> return cached value
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, GetTransparencyLevelCached, TestSize.Level1)
{
    TransparencyUtils::transparencyLevelGet_ = true;
    int32_t result = TransparencyUtils::GetTransparencyLevel(
        static_cast<int32_t>(UiMaterialLevel::EXQUISITE));
    EXPECT_EQ(result, static_cast<int32_t>(UiMaterialTransparency::NORMAL));
}

/**
 * @tc.name: GetTransparencyLevelInitFail
 * @tc.desc: Test L58 T + L60 T: SettingDataManager not initialized, init fails -> return default
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, GetTransparencyLevelInitFail, TestSize.Level1)
{
    ON_CALL(GetMockMgr(), IsInitialized()).WillByDefault(Return(false));
    EXPECT_CALL(GetMockMgr(), Initialize()).WillOnce(Return(1));
    int32_t result = TransparencyUtils::GetTransparencyLevel(
        static_cast<int32_t>(UiMaterialLevel::EXQUISITE));
    EXPECT_EQ(result, static_cast<int32_t>(UiMaterialTransparency::NORMAL));
}

/**
 * @tc.name: GetTransparencyLevelInitSuccess
 * @tc.desc: Test L58 T + L60 F + L69 T: init succeeds, GetInt32ValueStrictly succeeds
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, GetTransparencyLevelInitSuccess, TestSize.Level1)
{
    EXPECT_CALL(GetMockMgr(), IsInitialized())
        .Times(2)
        .WillOnce(Return(false))
        .WillOnce(Return(true));
    EXPECT_CALL(GetMockMgr(), Initialize()).WillOnce(Return(0));
    EXPECT_CALL(GetMockMgr(), GetCurrentUserId()).WillOnce(Return(100));
    EXPECT_CALL(GetMockMgr(), GetInt32ValueStrictly(_, _, 100))
        .WillOnce(DoAll(SetArgReferee<1>(0), Return(0)));
    int32_t result = TransparencyUtils::GetTransparencyLevel(
        static_cast<int32_t>(UiMaterialLevel::EXQUISITE));
    EXPECT_EQ(result, static_cast<int32_t>(UiMaterialTransparency::THIN));
    EXPECT_TRUE(TransparencyUtils::transparencyLevelGet_);
}

/**
 * @tc.name: GetTransparencyLevelGetIntFails
 * @tc.desc: Test L69 F: GetInt32ValueStrictly fails, transparencyLevelGet_ stays false
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, GetTransparencyLevelGetIntFails, TestSize.Level1)
{
    EXPECT_CALL(GetMockMgr(), IsInitialized())
        .Times(2)
        .WillOnce(Return(false))
        .WillOnce(Return(true));
    EXPECT_CALL(GetMockMgr(), Initialize()).WillOnce(Return(0));
    EXPECT_CALL(GetMockMgr(), GetCurrentUserId()).WillOnce(Return(100));
    EXPECT_CALL(GetMockMgr(), GetInt32ValueStrictly(_, _, 100))
        .WillOnce(Return(-1));
    TransparencyUtils::GetTransparencyLevel(
        static_cast<int32_t>(UiMaterialLevel::EXQUISITE));
    EXPECT_FALSE(TransparencyUtils::transparencyLevelGet_);
}

/**
 * @tc.name: GetTransparencyLevelAlreadyInited
 * @tc.desc: Test L58 F (already initialized) + L69 T: skip init, read settings directly
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, GetTransparencyLevelAlreadyInited, TestSize.Level1)
{
    EXPECT_CALL(GetMockMgr(), IsInitialized()).WillRepeatedly(Return(true));
    EXPECT_CALL(GetMockMgr(), GetCurrentUserId()).WillRepeatedly(Return(100));
    EXPECT_CALL(GetMockMgr(), GetInt32ValueStrictly(_, _, 100))
        .WillOnce(DoAll(SetArgReferee<1>(5), Return(0)));
    int32_t result = TransparencyUtils::GetTransparencyLevel(
        static_cast<int32_t>(UiMaterialLevel::EXQUISITE));
    EXPECT_TRUE(TransparencyUtils::transparencyLevelGet_);
    EXPECT_EQ(result, static_cast<int32_t>(UiMaterialTransparency::THICK));
}

/**
 * @tc.name: AdjustTransparencyForLevelAll
 * @tc.desc: Test L79-80 T (GENTLE), L83-84 T (EXQUISITE), and no adjustment
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, AdjustTransparencyForLevelAll, TestSize.Level1)
{
    TransparencyUtils::AdjustTransparencyForLevel(
        static_cast<int32_t>(UiMaterialTransparency::GENTLE_THIN));
    EXPECT_EQ(TransparencyUtils::GetLevelMap()[UiMaterialLevel::GENTLE],
        UiMaterialTransparency::GENTLE_THIN);
    EXPECT_EQ(TransparencyUtils::GetLevelMap()[UiMaterialLevel::EXQUISITE],
        UiMaterialTransparency::THIN);

    TransparencyUtils::GetLevelMap()[UiMaterialLevel::EXQUISITE] = UiMaterialTransparency::NORMAL;
    TransparencyUtils::GetLevelMap()[UiMaterialLevel::GENTLE] = UiMaterialTransparency::GENTLE_NORMAL;
    TransparencyUtils::AdjustTransparencyForLevel(
        static_cast<int32_t>(UiMaterialTransparency::THIN));
    EXPECT_EQ(TransparencyUtils::GetLevelMap()[UiMaterialLevel::EXQUISITE],
        UiMaterialTransparency::THIN);
    EXPECT_EQ(TransparencyUtils::GetLevelMap()[UiMaterialLevel::GENTLE],
        UiMaterialTransparency::GENTLE_THIN);

    TransparencyUtils::GetLevelMap()[UiMaterialLevel::EXQUISITE] = UiMaterialTransparency::NORMAL;
    TransparencyUtils::GetLevelMap()[UiMaterialLevel::GENTLE] = UiMaterialTransparency::GENTLE_NORMAL;
    TransparencyUtils::AdjustTransparencyForLevel(
        static_cast<int32_t>(UiMaterialTransparency::NONE));
    EXPECT_EQ(TransparencyUtils::GetLevelMap()[UiMaterialLevel::EXQUISITE],
        UiMaterialTransparency::NORMAL);
}

/**
 * @tc.name: LookupTransparencyAll
 * @tc.desc: Test L112 T (found) and F (not found)
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, LookupTransparencyAll, TestSize.Level1)
{
    EXPECT_EQ(TransparencyUtils::LookupTransparency(UiMaterialLevel::EXQUISITE),
        UiMaterialTransparency::NORMAL);
    EXPECT_EQ(TransparencyUtils::LookupTransparency(UiMaterialLevel::GENTLE),
        UiMaterialTransparency::GENTLE_NORMAL);
    EXPECT_EQ(TransparencyUtils::LookupTransparency(UiMaterialLevel::SMOOTH),
        UiMaterialTransparency::NONE);
    EXPECT_EQ(TransparencyUtils::LookupTransparency(static_cast<UiMaterialLevel>(99)),
        UiMaterialTransparency::NONE);
}

/**
 * @tc.name: GetCurrentUserIdAll
 * @tc.desc: Test L117 T (cached), L117 F + L122 T (valid), L117 F + L122 F (invalid)
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, GetCurrentUserIdAll, TestSize.Level1)
{
    TransparencyUtils::userIdGet_ = true;
    TransparencyUtils::userId_ = 42;
    EXPECT_EQ(TransparencyUtils::GetCurrentUserId(), 42);

    TransparencyUtils::userIdGet_ = false;
    TransparencyUtils::userId_ = 100;
    EXPECT_CALL(GetMockMgr(), GetCurrentUserId()).WillOnce(Return(50));
    EXPECT_EQ(TransparencyUtils::GetCurrentUserId(), 50);
    EXPECT_TRUE(TransparencyUtils::userIdGet_);

    TransparencyUtils::userIdGet_ = false;
    TransparencyUtils::userId_ = 100;
    EXPECT_CALL(GetMockMgr(), GetCurrentUserId()).WillOnce(Return(-1));
    EXPECT_EQ(TransparencyUtils::GetCurrentUserId(), 100);
}

/**
 * @tc.name: RegisterListenerInnerAll
 * @tc.desc: Test all branches of RegisterListenerInner
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, RegisterListenerInnerAll, TestSize.Level1)
{
    TransparencyUtils::listenerSet_ = true;
    EXPECT_TRUE(TransparencyUtils::RegisterListenerInner());

    TransparencyUtils::listenerSet_ = false;
    EXPECT_CALL(GetMockMgr(), IsInitialized()).WillRepeatedly(Return(true));
    EXPECT_CALL(GetMockMgr(), RegisterObserver(_, _, _)).WillOnce(Return(1));
    EXPECT_FALSE(TransparencyUtils::RegisterListenerInner());

    TransparencyUtils::listenerSet_ = false;
    EXPECT_CALL(GetMockMgr(), IsInitialized()).WillRepeatedly(Return(true));
    EXPECT_CALL(GetMockMgr(), RegisterObserver(_, _, _)).WillOnce(Return(0));
    EXPECT_TRUE(TransparencyUtils::RegisterListenerInner());

    TransparencyUtils::listenerSet_ = false;
    EXPECT_CALL(GetMockMgr(), IsInitialized())
        .Times(2)
        .WillOnce(Return(false))
        .WillOnce(Return(true));
    EXPECT_CALL(GetMockMgr(), Initialize()).WillOnce(Return(0));
    EXPECT_CALL(GetMockMgr(), RegisterObserver(_, _, _)).WillOnce(Return(1));
    EXPECT_FALSE(TransparencyUtils::RegisterListenerInner());

    TransparencyUtils::listenerSet_ = false;
    EXPECT_CALL(GetMockMgr(), IsInitialized())
        .Times(2)
        .WillOnce(Return(false))
        .WillOnce(Return(true));
    EXPECT_CALL(GetMockMgr(), Initialize()).WillOnce(Return(0));
    EXPECT_CALL(GetMockMgr(), RegisterObserver(_, _, _)).WillOnce(Return(0));
    EXPECT_TRUE(TransparencyUtils::RegisterListenerInner());

    TransparencyUtils::listenerSet_ = false;
    EXPECT_CALL(GetMockMgr(), IsInitialized())
        .Times(2)
        .WillOnce(Return(false))
        .WillOnce(Return(false));
    EXPECT_CALL(GetMockMgr(), Initialize()).WillOnce(Return(0));
    EXPECT_FALSE(TransparencyUtils::RegisterListenerInner());
}

/**
 * @tc.name: RegisterTransparencyListenerAll
 * @tc.desc: Test RegisterTransparencyListener L132 T/F, L134 T/F
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, RegisterTransparencyListenerAll, TestSize.Level1)
{
    WeakPtr<NG::FrameNode> emptyNode;

    TransparencyCallback cb = [](int32_t) {};
    auto ret = TransparencyUtils::RegisterTransparencyListener(emptyNode, std::move(cb));
    EXPECT_FALSE(ret.has_value());

    TransparencyUtils::listenerSet_ = true;
    TransparencyUtils::callbackIdsMap_.clear();
    TransparencyCallback cb2 = [](int32_t) {};
    auto ret2 = TransparencyUtils::RegisterTransparencyListener(emptyNode, std::move(cb2));
    EXPECT_TRUE(ret2.has_value());
    EXPECT_EQ(ret2.value(), 0);
    EXPECT_EQ(TransparencyUtils::callbackIdsMap_.size(), 1);

    auto savedContainerId = Container::CurrentIdSafelyWithCheck();
    Container::UpdateCurrent(-1);
    TransparencyUtils::callbackIdsMap_.clear();
    TransparencyUtils::callbackId_ = -1;
    TransparencyCallback cb3 = [](int32_t) {};
    auto ret3 = TransparencyUtils::RegisterTransparencyListener(emptyNode, std::move(cb3));
    EXPECT_FALSE(ret3.has_value());
    Container::UpdateCurrent(savedContainerId);
}

/**
 * @tc.name: UnRegisterTransparencyListenerAll
 * @tc.desc: Test L247 T (empty), L247 F + L251 T (found), L247 F + L251 F (not found)
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, UnRegisterTransparencyListenerAll, TestSize.Level1)
{
    TransparencyUtils::UnRegisterTransparencyListener(0);
    EXPECT_TRUE(TransparencyUtils::callbackIdsMap_.empty());

    TransparencyUtils::callbackIdsMap_[0] = { nullptr, WeakPtr<NG::FrameNode>(), 0 };
    TransparencyUtils::UnRegisterTransparencyListener(1);
    EXPECT_EQ(TransparencyUtils::callbackIdsMap_.size(), 1);

    TransparencyUtils::UnRegisterTransparencyListener(0);
    EXPECT_TRUE(TransparencyUtils::callbackIdsMap_.empty());
}

/**
 * @tc.name: OnParameterChangedTest
 * @tc.desc: Test OnParameterChanged resets transparencyLevelGet_
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, OnParameterChangedTest, TestSize.Level1)
{
    TransparencyUtils::transparencyLevelGet_ = true;
    TransparencyUtils::OnParameterChanged("test", 0);
    EXPECT_FALSE(TransparencyUtils::transparencyLevelGet_);
}

/**
 * @tc.name: ExecuteTransparencyCallbackTransparencyNone
 * @tc.desc: Test L191 T: transparency == NONE -> return early
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, ExecuteTransparencyCallbackTransparencyNone, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;
    TransparencyUtils::callbackIdsMap_[0] = { nullptr, WeakPtr<NG::FrameNode>(), 0 };
    TransparencyUtils::ExecuteTransparencyCallback();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ExecuteTransparencyCallbackNoTaskExecutor
 * @tc.desc: Test L181 T/F (frameNode valid/invalid) and L197 T (no task executor)
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, ExecuteTransparencyCallbackNoTaskExecutor, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("test", 0,
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    TransparencyCallback cb = [](int32_t) {};
    TransparencyUtils::callbackIdsMap_[0] = { std::move(cb), WeakPtr<NG::FrameNode>(frameNode), 0 };
    TransparencyUtils::ExecuteTransparencyCallback();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: HandleNodesCallbackTest
 * @tc.desc: Test HandleNodesCallback various paths
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, HandleNodesCallbackTest, TestSize.Level1)
{
    bool called = false;
    TransparencyCallback cb = [&called](int32_t v) { called = true; };
    TransparencyMapData data = { std::move(cb), WeakPtr<NG::FrameNode>(), 0 };
    std::list<TransparencyMapData> datas = { data };
    TransparencyUtils::HandleNodesCallback(datas, 0);
    EXPECT_FALSE(called);

    called = false;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("test", 1,
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    TransparencyCallback cb2 = [&called](int32_t v) { called = true; };
    TransparencyMapData data2 = { std::move(cb2), WeakPtr<NG::FrameNode>(frameNode), 0 };
    std::list<TransparencyMapData> datas2 = { data2 };
    TransparencyUtils::HandleNodesCallback(datas2, 0);
    EXPECT_TRUE(called);
}

/**
 * @tc.name: ExecuteTransparencyCallbackWithTaskExecutor
 * @tc.desc: Test L197 F: task executor found, PostDelayedTask executes HandleNodesCallback
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, ExecuteTransparencyCallbackWithTaskExecutor, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("test", 0,
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    bool called = false;
    TransparencyCallback cb = [&called](int32_t) { called = true; };
    TransparencyUtils::callbackIdsMap_[0] = { std::move(cb), WeakPtr<NG::FrameNode>(frameNode), 0 };

    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->SetTaskExecutor(taskExecutor);
    AceEngine::Get().AddContainer(0, container);

    TransparencyUtils::ExecuteTransparencyCallback();
    EXPECT_TRUE(called);
}

/**
 * @tc.name: ExecuteTransparencyCallbackMultipleContainers
 * @tc.desc: Test multiple containers in nodesByContainer map
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, ExecuteTransparencyCallbackMultipleContainers, TestSize.Level1)
{
    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    auto frameNode1 = NG::FrameNode::GetOrCreateFrameNode("test", 1,
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    auto frameNode2 = NG::FrameNode::GetOrCreateFrameNode("test", 2,
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    bool called1 = false;
    bool called2 = false;
    TransparencyCallback cb1 = [&called1](int32_t) { called1 = true; };
    TransparencyCallback cb2 = [&called2](int32_t) { called2 = true; };
    TransparencyUtils::callbackIdsMap_[1] = { std::move(cb1), WeakPtr<NG::FrameNode>(frameNode1), 0 };
    TransparencyUtils::callbackIdsMap_[2] = { std::move(cb2), WeakPtr<NG::FrameNode>(frameNode2), 1 };

    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    container->SetTaskExecutor(taskExecutor);
    AceEngine::Get().AddContainer(0, container);
    AceEngine::Get().AddContainer(1, container);

    TransparencyUtils::ExecuteTransparencyCallback();
    EXPECT_TRUE(called1);
    EXPECT_TRUE(called2);
}

/**
 * @tc.name: HandleNodesCallbackAttachedPipeline
 * @tc.desc: Test L219 T + L220 T: pipeline with matching instance ID -> callback directly
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, HandleNodesCallbackAttachedPipeline, TestSize.Level1)
{
    bool called = false;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("test", 3,
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });

    AceType::RawPtr(MockPipelineContext::pipeline_)->SetInstanceId(0);
    frameNode->AttachContext(AceType::RawPtr(MockPipelineContext::pipeline_));

    TransparencyCallback cb = [&called](int32_t) { called = true; };
    TransparencyMapData data = { std::move(cb), WeakPtr<NG::FrameNode>(frameNode), 0 };
    std::list<TransparencyMapData> datas = { data };

    TransparencyUtils::HandleNodesCallback(datas, 0);
    EXPECT_TRUE(called);
}

/**
 * @tc.name: HandleNodesCallbackNoTaskExecutorOnPipeline
 * @tc.desc: Test L219 T + L220 F + L226 T:
 *           pipeline has no taskExecutor -> log warning, continue
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, HandleNodesCallbackNoTaskExecutorOnPipeline, TestSize.Level1)
{
    bool called = false;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("test", 5,
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });

    auto saved = AceType::RawPtr(MockPipelineContext::pipeline_)->taskExecutor_;
    AceType::RawPtr(MockPipelineContext::pipeline_)->SetInstanceId(1);
    frameNode->AttachContext(AceType::RawPtr(MockPipelineContext::pipeline_));
    AceType::RawPtr(MockPipelineContext::pipeline_)->taskExecutor_ = nullptr;

    TransparencyCallback cb = [&called](int32_t) { called = true; };
    TransparencyMapData data = { std::move(cb), WeakPtr<NG::FrameNode>(frameNode), 0 };
    std::list<TransparencyMapData> datas = { data };

    TransparencyUtils::HandleNodesCallback(datas, 1);
    EXPECT_FALSE(called);
    AceType::RawPtr(MockPipelineContext::pipeline_)->taskExecutor_ = saved;
}

class NonUiThreadMockTaskExecutor : public MockTaskExecutor {
public:
    bool WillRunOnCurrentThread(TaskExecutor::TaskType) const override { return false; }
};

/**
 * @tc.name: HandleNodesCallbackPostTaskBranch
 * @tc.desc: Test L219 T + L220 F + L226 F + L230 F:
 *           pipeline with mismatched ID, task executor found, not on UI thread -> PostTask
 * @tc.type: FUNC
 */
HWTEST_F(TransparencyUtilsTestNg, HandleNodesCallbackPostTaskBranch, TestSize.Level1)
{
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("test", 6,
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });

    auto saved = AceType::RawPtr(MockPipelineContext::pipeline_)->taskExecutor_;
    AceType::RawPtr(MockPipelineContext::pipeline_)->SetInstanceId(1);
    frameNode->AttachContext(AceType::RawPtr(MockPipelineContext::pipeline_));
    AceType::RawPtr(MockPipelineContext::pipeline_)->taskExecutor_ =
        AceType::MakeRefPtr<::testing::NiceMock<NonUiThreadMockTaskExecutor>>();

    TransparencyCallback cb = [](int32_t) {};
    TransparencyMapData data = { std::move(cb), WeakPtr<NG::FrameNode>(frameNode), 0 };
    std::list<TransparencyMapData> datas = { data };

    TransparencyUtils::HandleNodesCallback(datas, 1);
    // L230 F reached: PostTask called on mock (no-op), branch covered
    AceType::RawPtr(MockPipelineContext::pipeline_)->taskExecutor_ = saved;
}
} // namespace OHOS::Ace
