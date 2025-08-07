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

#include "core/components_ng/manager/avoid_info/avoid_info_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
bool operator==(const ContainerModalAvoidInfo& a, const ContainerModalAvoidInfo& b)
{
    return a.needAvoid == b.needAvoid &&
           a.titleHeight == b.titleHeight &&
           a.controlBottonsRect == b.controlBottonsRect;
}

bool operator!=(const ContainerModalAvoidInfo& a, const ContainerModalAvoidInfo& b)
{
    return !(a == b);
}

namespace {
class MockAvoidInfoListener : public IAvoidInfoListener {
    DECLARE_ACE_TYPE(MockAvoidInfoListener, IAvoidInfoListener);
public:
    MockAvoidInfoListener() = default;
    ~MockAvoidInfoListener() = default;

    MOCK_METHOD1(OnAvoidInfoChange, void(const ContainerModalAvoidInfo& info));
};

RefPtr<AvoidInfoManager> GetAvoidInfoManager()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    return pipeline != nullptr ? pipeline->GetAvoidInfoManager() : nullptr;
}
} // namespace

class AvoidInfoManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp();
    void TearDown() {}
};

void AvoidInfoManagerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void AvoidInfoManagerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void AvoidInfoManagerTestNg::SetUp()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto mgr = AceType::MakeRefPtr<AvoidInfoManager>();
    ASSERT_NE(mgr, nullptr);
    mgr->SetPipelineContext(WeakPtr(pipeline));
    mgr->SetInstanceId(pipeline->GetInstanceId());
    pipeline->avoidInfoMgr_ = mgr;
}

/**
 * @tc.name: OnAvoidInfoChange001
 * @tc.desc: Test basic logic of OnAvoidInfoChange
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(AvoidInfoManagerTestNg, OnAvoidInfoChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get AvoidInfoManager.
     */
    auto manager = GetAvoidInfoManager();
    ASSERT_NE(manager, nullptr);
    ASSERT_TRUE(manager->listeners_.empty());

    /**
     * @tc.steps: step2. Create one listener, set expected input param and callTimes.
     */
    ContainerModalAvoidInfo info;
    info.needAvoid = true;
    info.titleHeight = 32;
    auto listener = AceType::MakeRefPtr<MockAvoidInfoListener>();
    ASSERT_NE(listener, nullptr);
    EXPECT_CALL(*listener, OnAvoidInfoChange(info)).Times(1);

    /**
     * @tc.steps: step3. Add listener to AvoidInfoManager, and invoke OnAvoidInfoChange with specified Param.
     * @tc.expected: Manager's input param equals to Listener input param.
     */
    manager->listeners_.emplace(listener);
    ASSERT_EQ(manager->listeners_.size(), 1);
    manager->OnAvoidInfoChange(info);
}

/**
 * @tc.name: AddAvoidInfoListener001
 * @tc.desc: Test basic logic of AddAvoidInfoListener&RemoveAvoidInfoListener
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(AvoidInfoManagerTestNg, AddAvoidInfoListener001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get AvoidInfoManager.
     */
    auto manager = GetAvoidInfoManager();
    ASSERT_NE(manager, nullptr);
    ASSERT_TRUE(manager->listeners_.empty());

    /**
     * @tc.steps: step2. Create three listeners.
     */
    auto listener1 = AceType::MakeRefPtr<MockAvoidInfoListener>();
    ASSERT_NE(listener1, nullptr);
    auto listener2 = AceType::MakeRefPtr<MockAvoidInfoListener>();
    ASSERT_NE(listener2, nullptr);
    auto listener3 = AceType::MakeRefPtr<MockAvoidInfoListener>();
    ASSERT_NE(listener3, nullptr);

    /**
     * @tc.steps: step2. Add listeners and check result.
     */
    manager->AddAvoidInfoListener(listener1);
    ASSERT_EQ(manager->listeners_.size(), 1);
    // add same listener again.
    manager->AddAvoidInfoListener(listener1);
    ASSERT_EQ(manager->listeners_.size(), 1);
    manager->AddAvoidInfoListener(listener2);
    manager->AddAvoidInfoListener(listener3);
    ASSERT_EQ(manager->listeners_.size(), 3);

    /**
     * @tc.steps: step2. Remove listeners and check result.
     */
    manager->RemoveAvoidInfoListener(listener1);
    manager->RemoveAvoidInfoListener(listener2);
    ASSERT_EQ(manager->listeners_.size(), 1);
    auto it = manager->listeners_.find(listener3);
    ASSERT_TRUE(it != manager->listeners_.end());
}

/**
 * @tc.name: GetContainerModalTitleHeight001
 * @tc.desc: Test basic logic of GetContainerModalTitleHeight
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(AvoidInfoManagerTestNg, GetContainerModalTitleHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get AvoidInfoManager, Set AvoidInfo for normal scenario and UEC scenario.
     */
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto manager = GetAvoidInfoManager();
    ASSERT_NE(manager, nullptr);
    ContainerModalAvoidInfo info;
    info.titleHeight = 32;
    ContainerModalAvoidInfo uecInfo;
    uecInfo.titleHeight = 64;
    manager->SetAvoidInfo(info);
    manager->SetAvoidInfoForUEC(uecInfo);

    /**
     * @tc.steps: step2. Set current Container is UEC Container.
     * @tc.desc: Branch: if (container->IsUIExtensionWindow()) { => true
     */
    container->SetIsUIExtensionWindow(true);
    int32_t height = manager->GetContainerModalTitleHeight();
    ASSERT_EQ(height, 64);

    /**
     * @tc.steps: step2. Set current Container is regular Container.
     * @tc.desc: Branch: if (container->IsUIExtensionWindow()) { => false
     */
    container->SetIsUIExtensionWindow(false);
    height = manager->GetContainerModalTitleHeight();
    ASSERT_EQ(height, 32);
}

/**
 * @tc.name: GetContainerModalButtonsRect001
 * @tc.desc: Test basic logic of GetContainerModalButtonsRect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(AvoidInfoManagerTestNg, GetContainerModalButtonsRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get AvoidInfoManager, Set AvoidInfo for normal scenario and UEC scenario.
     */
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto manager = GetAvoidInfoManager();
    ASSERT_NE(manager, nullptr);
    ContainerModalAvoidInfo info;
    info.controlBottonsRect = RectF(0.0f, 0.0f, 300.0f, 400.f);
    ContainerModalAvoidInfo uecInfo;
    uecInfo.controlBottonsRect = RectF(50.0f, 60.0f, 300.0f, 400.f);
    manager->SetAvoidInfo(info);
    manager->SetAvoidInfoForUEC(uecInfo);

    /**
     * @tc.steps: step2. Set current Container is UEC Container.
     * @tc.desc: Branch: if (container->IsUIExtensionWindow()) { => true
     */
    container->SetIsUIExtensionWindow(true);
    RectF containerRect;
    RectF buttonsRect;
    ASSERT_TRUE(manager->GetContainerModalButtonsRect(containerRect, buttonsRect));
    ASSERT_EQ(buttonsRect, uecInfo.controlBottonsRect);

    /**
     * @tc.steps: step2. Set current Container is regular Container.
     * @tc.desc: Branch: if (container->IsUIExtensionWindow()) { => false
     */
    container->SetIsUIExtensionWindow(false);
    ASSERT_TRUE(manager->GetContainerModalButtonsRect(containerRect, buttonsRect));
    ASSERT_EQ(buttonsRect, info.controlBottonsRect);
}

/**
 * @tc.name: NeedAvoidContainerModal001
 * @tc.desc: Test basic logic of NeedAvoidContainerModal
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(AvoidInfoManagerTestNg, NeedAvoidContainerModal001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get AvoidInfoManager, Set AvoidInfo for normal scenario and UEC scenario.
     */
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto manager = GetAvoidInfoManager();
    ASSERT_NE(manager, nullptr);
    ContainerModalAvoidInfo info;
    info.needAvoid = true;
    ContainerModalAvoidInfo uecInfo;
    uecInfo.needAvoid = false;
    manager->SetAvoidInfo(info);
    manager->SetAvoidInfoForUEC(uecInfo);

    /**
     * @tc.steps: step2. Set current Container is UEC Container.
     * @tc.desc: Branch: if (container->IsUIExtensionWindow()) { => true
     */
    container->SetIsUIExtensionWindow(true);
    ASSERT_FALSE(manager->NeedAvoidContainerModal());

    /**
     * @tc.steps: step2. Set current Container is regular Container.
     * @tc.desc: Branch: if (container->IsUIExtensionWindow()) { => false
     */
    container->SetIsUIExtensionWindow(false);
    ASSERT_TRUE(manager->NeedAvoidContainerModal());
}

/**
 * @tc.name: RegisterListenerIfNeeded001
 * @tc.desc: Test basic logic of RegisterListenerIfNeeded
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(AvoidInfoManagerTestNg, RegisterListenerIfNeeded001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get AvoidInfoManager.
     */
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto manager = GetAvoidInfoManager();
    ASSERT_NE(manager, nullptr);
    manager->hasRegisterListener_ = false;

    /**
     * @tc.steps: step2. Set current Container is regular Container.
     * @tc.desc: Branch: if (!container->IsUIExtensionWindow()) { => true
     */
    container->SetIsUIExtensionWindow(false);
    manager->RegisterListenerIfNeeded();
    ASSERT_TRUE(manager->hasRegisterListener_);

    /**
     * @tc.steps: step2. Keep the callbacks of AvoidInfoManager in an unset state,
     *                   Set current Container is UEC Container.
     * @tc.desc: Branch: if (!registerUECConsumerCallback_ || !requestAvoidInfoCallback_) { => true
     */
    manager->hasRegisterListener_ = false;
    container->SetIsUIExtensionWindow(true);
    manager->RegisterListenerIfNeeded();
    ASSERT_FALSE(manager->hasRegisterListener_);

    /**
     * @tc.steps: step2. Set callbacks to AvoidInfoManager, set current Container is UEC Container.
     * @tc.desc: Branch: if (!registerUECConsumerCallback_ || !requestAvoidInfoCallback_) { => false
     */
    bool callRegisterFunc = false;
    auto registerCallback = [&callRegisterFunc](UECAvoidInfoConsumer&& consumer) {
        callRegisterFunc = true;
    };
    bool callRequestFunc = false;
    auto requestCallback = [&callRequestFunc]() {
        callRequestFunc = true;
    };
    manager->SetRegisterUECAvoidInfoConsumerCallback(std::move(registerCallback));;
    manager->SetRequestAvoidInfoCallback(std::move(requestCallback));
    manager->RegisterListenerIfNeeded();
    ASSERT_TRUE(manager->hasRegisterListener_);
    ASSERT_TRUE(callRegisterFunc);
    ASSERT_TRUE(callRequestFunc);
}

/**
 * @tc.name: UnregisterListenerIfNeeded001
 * @tc.desc: Test basic logic of UnregisterListenerIfNeeded
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(AvoidInfoManagerTestNg, UnregisterListenerIfNeeded001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get AvoidInfoManager.
     */
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto manager = GetAvoidInfoManager();
    ASSERT_NE(manager, nullptr);
    manager->hasRegisterListener_ = true;

    /**
     * @tc.steps: step2. Set current Container is UEC Container.
     * @tc.desc: Branch: if (container->IsUIExtensionWindow()) { => true
     */
    container->SetIsUIExtensionWindow(true);
    manager->UnregisterListenerIfNeeded();
    ASSERT_FALSE(manager->hasRegisterListener_);

    /**
     * @tc.steps: step2. Set current Container is regular Container.
     * @tc.desc: Branch: if (container->IsUIExtensionWindow()) { => false
     */
    manager->hasRegisterListener_ = true;
    container->SetIsUIExtensionWindow(false);
    manager->UnregisterListenerIfNeeded();
    ASSERT_FALSE(manager->hasRegisterListener_);
}

/**
 * @tc.name: GetContainerModalAvoidInfoForUEC001
 * @tc.desc: Branch: if (context->GetContainerCustomTitleVisible() ||
 *                       !context->GetContainerControlButtonVisible()) { => false
 *                   if (!context->GetContainerModalButtonsRect(containerModal, buttonsRect)) { => false
 *                   if (height <= 0) { => false
 *                   if (!uecRect.IsIntersectWith(buttonsRect)) { => true
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(AvoidInfoManagerTestNg, GetContainerModalAvoidInfoForUEC001, TestSize.Level1)
{
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto manager = GetAvoidInfoManager();
    ASSERT_NE(manager, nullptr);
    
    bool preTitleVisible = pipeline->GetContainerCustomTitleVisible();
    bool preBtnVisible = pipeline->GetContainerControlButtonVisible();
    int32_t preHeight = pipeline->GetContainerModalTitleHeight();

    pipeline->SetContainerCustomTitleVisible(false);
    pipeline->SetContainerControlButtonVisible(true);
    pipeline->SetContainerModalButtonsRect(true);
    RectF btnRct{200.0f, 0.0f, 200.0f, 100.0f};
    pipeline->SetContainerModalButtonsRect(btnRct);
    pipeline->SetContainerModalTitleHeight(80);

    auto uecNode = FrameNode::CreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(uecNode, nullptr);
    auto geometryNode = uecNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameOffset(OffsetF(100.0f, 0.0f));
    geometryNode->SetFrameSize(SizeF(200.0f, 200.0f));

    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(geometryNode, nullptr);
    renderContext->UpdatePaintRect(RectF(100.0f, 120.0f, 200.0f, 200.0f));
    uecNode->renderContext_ = renderContext;

    ContainerModalAvoidInfo info;
    info.needAvoid = true;
    manager->GetContainerModalAvoidInfoForUEC(uecNode, info);
    EXPECT_FALSE(info.needAvoid);

    pipeline->SetContainerCustomTitleVisible(preTitleVisible);
    pipeline->SetContainerControlButtonVisible(preBtnVisible);
    pipeline->SetContainerModalTitleHeight(preHeight);
}
} // namespace OHOS::Ace::NG
