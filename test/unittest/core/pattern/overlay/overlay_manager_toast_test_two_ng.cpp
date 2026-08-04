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
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/frameworks/base/subwindow/mock_subwindow.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/pattern/date_picker/picker_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/sheet/sheet_theme.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_ng/pattern/toast/toast_view.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";
constexpr int32_t DURATION = 2;
} // namespace
class OverlayManagerToastTestTwoNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void OverlayManagerToastTestTwoNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockPipelineContext::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_ELEVEN);
    EXPECT_CALL(*AceType::DynamicCast<MockPipelineContext>(MockPipelineContext::GetCurrentContext()),
        GetSafeAreaWithoutProcess())
        .WillRepeatedly(Return(SafeAreaInsets {}));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == DragBarTheme::TypeId()) {
            return AceType::MakeRefPtr<DragBarTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else if (type == PickerTheme::TypeId()) {
            return AceType::MakeRefPtr<PickerTheme>();
        } else if (type == SelectTheme::TypeId()) {
            return AceType::MakeRefPtr<SelectTheme>();
        } else if (type == MenuTheme::TypeId()) {
            return AceType::MakeRefPtr<MenuTheme>();
        } else if (type == ToastTheme::TypeId()) {
            return AceType::MakeRefPtr<ToastTheme>();
        } else if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else if (type == TextTheme::TypeId()) {
            return AceType::MakeRefPtr<TextTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void OverlayManagerToastTestTwoNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: GetUIExtensionTitleBarHeight001
 * @tc.desc: Test GetUIExtensionTitleBarHeight returns host-parent top diff in UEC subwindow.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetUIExtensionTitleBarHeight001, TestSize.Level1)
{
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::TOP_MOST;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);

    constexpr int32_t parentContainerId = 20;
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    ASSERT_NE(mockSubwindow, nullptr);
    EXPECT_CALL(*mockSubwindow, GetChildContainerId()).WillRepeatedly(Return(0));
    EXPECT_CALL(*mockSubwindow, GetUIExtensionHostWindowRect()).WillRepeatedly(Return(Rect(0, 70, 100, 100)));
    EXPECT_CALL(*mockSubwindow, GetParentWindowRect()).WillRepeatedly(Return(Rect(0, 0, 100, 100)));
    SubwindowManager::GetInstance()->AddToastSubwindow(parentContainerId, mockSubwindow);

    auto height = toastPattern->GetUIExtensionTitleBarHeight(host, parentContainerId);
    EXPECT_FLOAT_EQ(height, 70.0f);

    mockSubwindow = nullptr;
    SubwindowManager::GetInstance()->subwindowMap_.clear();
    SubwindowManager::GetInstance()->instanceSubwindowMap_.clear();
}

/**
 * @tc.name: GetUIExtensionTitleBarHeight002
 * @tc.desc: Test GetUIExtensionTitleBarHeight returns absolute rect diff when host top is smaller than parent top.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetUIExtensionTitleBarHeight002, TestSize.Level1)
{
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::TOP_MOST;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);

    constexpr int32_t parentContainerId = 21;
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    ASSERT_NE(mockSubwindow, nullptr);
    EXPECT_CALL(*mockSubwindow, GetChildContainerId()).WillRepeatedly(Return(0));
    EXPECT_CALL(*mockSubwindow, GetUIExtensionHostWindowRect()).WillRepeatedly(Return(Rect(0, 0, 100, 100)));
    EXPECT_CALL(*mockSubwindow, GetParentWindowRect()).WillRepeatedly(Return(Rect(0, 70, 100, 100)));
    SubwindowManager::GetInstance()->AddToastSubwindow(parentContainerId, mockSubwindow);

    auto height = toastPattern->GetUIExtensionTitleBarHeight(host, parentContainerId);
    EXPECT_FLOAT_EQ(height, 70.0f);

    mockSubwindow = nullptr;
    SubwindowManager::GetInstance()->subwindowMap_.clear();
    SubwindowManager::GetInstance()->instanceSubwindowMap_.clear();
}

/**
 * @tc.name: GetUIExtensionTitleBarHeight003
 * @tc.desc: Test GetUIExtensionTitleBarHeight falls back to host context title height.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetUIExtensionTitleBarHeight003, TestSize.Level1)
{
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::TOP_MOST;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);

    auto hostContext = AceType::DynamicCast<MockPipelineContext>(host->GetContextRefPtr());
    ASSERT_NE(hostContext, nullptr);
    hostContext->SetContainerModalTitleHeight(48);

    auto height = toastPattern->GetUIExtensionTitleBarHeight(host, -1);
    EXPECT_FLOAT_EQ(height, 48.0f);

    hostContext->SetContainerModalTitleHeight(0);
}

/**
 * @tc.name: GetUIExtensionTitleBarHeight004
 * @tc.desc: Test GetUIExtensionTitleBarHeight returns zero when host is null and subwindow is unavailable.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetUIExtensionTitleBarHeight004, TestSize.Level1)
{
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.showMode = ToastShowMode::TOP_MOST;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    SubwindowManager::GetInstance()->subwindowMap_.clear();
    SubwindowManager::GetInstance()->instanceSubwindowMap_.clear();

    auto height = toastPattern->GetUIExtensionTitleBarHeight(nullptr, 30);
    EXPECT_FLOAT_EQ(height, 0.0f);
}

/**
 * @tc.name: GetToastParentContainerId001
 * @tc.desc: Test GetToastParentContainerId with valid host and pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetToastParentContainerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);

    /**
     * @tc.steps: step2. Set instanceId in mock pipeline.
     * @tc.expected: InstanceId is configured successfully.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto mockPipeline = AceType::DynamicCast<MockPipelineContext>(pipelineContext);
    ASSERT_NE(mockPipeline, nullptr);
    mockPipeline->SetInstanceId(10);

    /**
     * @tc.steps: step3. Call GetToastParentContainerId and verify result.
     * @tc.expected: ContainerId equals the set instanceId.
     */
    auto containerId = toastPattern->GetToastParentContainerId(host);
    EXPECT_EQ(containerId, 10);

    mockPipeline->SetInstanceId(0);
}

/**
 * @tc.name: GetToastParentContainerId002
 * @tc.desc: Test GetToastParentContainerId with nullptr host.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetToastParentContainerId002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    /**
     * @tc.steps: step2. Set container currentId and call GetToastParentContainerId with nullptr host.
     * @tc.expected: ContainerId equals the currentId.
     */
    MockContainer::UpdateCurrent(5);
    auto containerId = toastPattern->GetToastParentContainerId(nullptr);
    EXPECT_EQ(containerId, 5);

    MockContainer::UpdateCurrent(-1);
}

/**
 * @tc.name: GetTitleBarHeightFromContext001
 * @tc.desc: Test GetTitleBarHeightFromContext with valid pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetTitleBarHeightFromContext001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    /**
     * @tc.steps: step2. Set container modal title height in mock pipeline.
     * @tc.expected: Title bar height is configured successfully.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto mockPipeline = AceType::DynamicCast<MockPipelineContext>(pipelineContext);
    ASSERT_NE(mockPipeline, nullptr);
    mockPipeline->SetContainerModalTitleHeight(60);

    /**
     * @tc.steps: step3. Call GetTitleBarHeightFromContext and verify result.
     * @tc.expected: Height equals the set title bar height.
     */
    auto height = toastPattern->GetTitleBarHeightFromContext(pipelineContext);
    EXPECT_FLOAT_EQ(height, 60.0f);

    mockPipeline->SetContainerModalTitleHeight(0);
}

/**
 * @tc.name: GetTitleBarHeightFromContext002
 * @tc.desc: Test GetTitleBarHeightFromContext with nullptr pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetTitleBarHeightFromContext002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    /**
     * @tc.steps: step2. Call GetTitleBarHeightFromContext with nullptr pipeline.
     * @tc.expected: Height returns 0.
     */
    auto height = toastPattern->GetTitleBarHeightFromContext(nullptr);
    EXPECT_FLOAT_EQ(height, 0.0f);
}

/**
 * @tc.name: NeedAvoidTitleBarForSystemTopMostInUEC001
 * @tc.desc: Test NeedAvoidTitleBarForSystemTopMostInUEC with same origin.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, NeedAvoidTitleBarForSystemTopMostInUEC001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    /**
     * @tc.steps: step2. Configure mock subwindow with same origin coordinates.
     * @tc.expected: Subwindow is configured successfully.
     */
    constexpr int32_t parentContainerId = 50;
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    ASSERT_NE(mockSubwindow, nullptr);
    Rect parentRect(0, 0, 100, 100);
    EXPECT_CALL(*mockSubwindow, GetParentWindowRect()).WillRepeatedly(Return(parentRect));
    EXPECT_CALL(*mockSubwindow, GetWindowRect()).WillRepeatedly(Return(NG::RectF(0, 0, 100, 100)));
    SubwindowManager::GetInstance()->AddSystemToastWindow(parentContainerId, mockSubwindow);

    /**
     * @tc.steps: step3. Call NeedAvoidTitleBarForSystemTopMostInUEC and verify result.
     * @tc.expected: NeedAvoid returns true when origins are same.
     */
    auto needAvoid = toastPattern->NeedAvoidTitleBarForSystemTopMostInUEC(parentContainerId);
    EXPECT_TRUE(needAvoid);

    SubwindowManager::GetInstance()->ClearToastInSystemSubwindow();
}

/**
 * @tc.name: NeedAvoidTitleBarForSystemTopMostInUEC002
 * @tc.desc: Test NeedAvoidTitleBarForSystemTopMostInUEC with different origin.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, NeedAvoidTitleBarForSystemTopMostInUEC002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    /**
     * @tc.steps: step2. Configure mock subwindow with different origin coordinates.
     * @tc.expected: Subwindow is configured successfully.
     */
    constexpr int32_t parentContainerId = 51;
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    ASSERT_NE(mockSubwindow, nullptr);
    Rect parentRect(0, 0, 100, 100);
    EXPECT_CALL(*mockSubwindow, GetParentWindowRect()).WillRepeatedly(Return(parentRect));
    EXPECT_CALL(*mockSubwindow, GetWindowRect()).WillRepeatedly(Return(NG::RectF(10, 10, 100, 100)));
    SubwindowManager::GetInstance()->AddSystemToastWindow(parentContainerId, mockSubwindow);

    /**
     * @tc.steps: step3. Call NeedAvoidTitleBarForSystemTopMostInUEC and verify result.
     * @tc.expected: NeedAvoid returns false when origins are different.
     */
    auto needAvoid = toastPattern->NeedAvoidTitleBarForSystemTopMostInUEC(parentContainerId);
    EXPECT_FALSE(needAvoid);

    SubwindowManager::GetInstance()->ClearToastInSystemSubwindow();
}

/**
 * @tc.name: NeedAvoidTitleBarForSystemTopMostInUEC003
 * @tc.desc: Test NeedAvoidTitleBarForSystemTopMostInUEC with negative parentContainerId.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, NeedAvoidTitleBarForSystemTopMostInUEC003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    /**
     * @tc.steps: step2. Call NeedAvoidTitleBarForSystemTopMostInUEC with negative parentContainerId.
     * @tc.expected: NeedAvoid returns false for negative parentContainerId.
     */
    auto needAvoid = toastPattern->NeedAvoidTitleBarForSystemTopMostInUEC(-1);
    EXPECT_FALSE(needAvoid);
}

/**
 * @tc.name: GetSystemTopMostTitleBarHeightInUEC001
 * @tc.desc: Test GetSystemTopMostTitleBarHeightInUEC with valid subwindow.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetSystemTopMostTitleBarHeightInUEC001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    /**
     * @tc.steps: step2. Configure mock subwindow with parent window rect.
     * @tc.expected: Subwindow is configured successfully.
     */
    constexpr int32_t parentContainerId = 52;
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    ASSERT_NE(mockSubwindow, nullptr);
    Rect parentRect(0, 50, 100, 100);
    EXPECT_CALL(*mockSubwindow, GetParentWindowRect()).WillRepeatedly(Return(parentRect));
    EXPECT_CALL(*mockSubwindow, GetWindowRect()).WillRepeatedly(Return(NG::RectF(0, 0, 100, 100)));
    SubwindowManager::GetInstance()->AddSystemToastWindow(parentContainerId, mockSubwindow);

    /**
     * @tc.steps: step3. Call GetSystemTopMostTitleBarHeightInUEC and verify result.
     * @tc.expected: Height equals the parent rect top.
     */
    auto height = toastPattern->GetSystemTopMostTitleBarHeightInUEC(parentContainerId);
    EXPECT_FLOAT_EQ(height, 50.0f);

    SubwindowManager::GetInstance()->ClearToastInSystemSubwindow();
}

/**
 * @tc.name: GetSystemTopMostTitleBarHeightInUEC002
 * @tc.desc: Test GetSystemTopMostTitleBarHeightInUEC with negative parentContainerId.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetSystemTopMostTitleBarHeightInUEC002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    /**
     * @tc.steps: step2. Call GetSystemTopMostTitleBarHeightInUEC with negative parentContainerId.
     * @tc.expected: Height returns 0 for negative parentContainerId.
     */
    auto height = toastPattern->GetSystemTopMostTitleBarHeightInUEC(-1);
    EXPECT_FLOAT_EQ(height, 0.0f);
}

/**
 * @tc.name: GetTopMostTitleBarHeightInUEC001
 * @tc.desc: Test GetTopMostTitleBarHeightInUEC with valid subwindow.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetTopMostTitleBarHeightInUEC001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);

    /**
     * @tc.steps: step2. Configure mock pipeline and subwindow.
     * @tc.expected: Pipeline and subwindow are configured successfully.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto mockPipeline = AceType::DynamicCast<MockPipelineContext>(pipelineContext);
    ASSERT_NE(mockPipeline, nullptr);

    constexpr int32_t parentContainerId = 53;
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    ASSERT_NE(mockSubwindow, nullptr);
    Rect parentRect(0, 60, 100, 100);
    EXPECT_CALL(*mockSubwindow, GetParentWindowRect()).WillRepeatedly(Return(parentRect));
    EXPECT_CALL(*mockSubwindow, GetWindowRect()).WillRepeatedly(Return(NG::RectF(0, 0, 100, 100)));
    SubwindowManager::GetInstance()->AddToastSubwindow(parentContainerId, mockSubwindow);

    mockPipeline->SetInstanceId(parentContainerId);
    MockContainer::UpdateCurrent(parentContainerId);

    /**
     * @tc.steps: step3. Call GetTopMostTitleBarHeightInUEC and verify result.
     * @tc.expected: Height equals the parent rect top.
     */
    auto height = toastPattern->GetTopMostTitleBarHeightInUEC(host);
    EXPECT_FLOAT_EQ(height, 60.0f);

    mockPipeline->SetInstanceId(0);
    MockContainer::UpdateCurrent(-1);
    SubwindowManager::GetInstance()->subwindowMap_.clear();
    SubwindowManager::GetInstance()->instanceSubwindowMap_.clear();
}

/**
 * @tc.name: GetTopMostTitleBarHeightInUEC002
 * @tc.desc: Test GetTopMostTitleBarHeightInUEC with nullptr host.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetTopMostTitleBarHeightInUEC002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    /**
     * @tc.steps: step2. Call GetTopMostTitleBarHeightInUEC with nullptr host.
     * @tc.expected: Height returns 0 for nullptr host.
     */
    auto height = toastPattern->GetTopMostTitleBarHeightInUEC(nullptr);
    EXPECT_FLOAT_EQ(height, 0.0f);
}

/**
 * @tc.name: GetUECTitleBarHeightForTopAlignment001
 * @tc.desc: Test GetUECTitleBarHeightForTopAlignment with SYSTEM_TOP_MOST mode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetUECTitleBarHeightForTopAlignment001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);

    /**
     * @tc.steps: step2. Create layout wrapper and set showMode to SYSTEM_TOP_MOST.
     * @tc.expected: Layout wrapper and property are created successfully.
     */
    auto layoutWrapper = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto toastProp = AceType::DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(toastProp, nullptr);
    toastProp->UpdateShowMode(ToastShowMode::SYSTEM_TOP_MOST);

    /**
     * @tc.steps: step3. Configure mock pipeline and subwindow.
     * @tc.expected: Pipeline and subwindow are configured successfully.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto mockPipeline = AceType::DynamicCast<MockPipelineContext>(pipelineContext);
    ASSERT_NE(mockPipeline, nullptr);

    constexpr int32_t parentContainerId = 54;
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    ASSERT_NE(mockSubwindow, nullptr);
    Rect parentRect(0, 70, 100, 100);
    EXPECT_CALL(*mockSubwindow, GetParentWindowRect()).WillRepeatedly(Return(parentRect));
    EXPECT_CALL(*mockSubwindow, GetWindowRect()).WillRepeatedly(Return(NG::RectF(0, 0, 100, 100)));
    SubwindowManager::GetInstance()->AddSystemToastWindow(parentContainerId, mockSubwindow);

    mockPipeline->SetInstanceId(parentContainerId);
    MockContainer::UpdateCurrent(parentContainerId);

    /**
     * @tc.steps: step4. Call GetUECTitleBarHeightForTopAlignment and verify result.
     * @tc.expected: Height equals the parent rect top.
     */
    auto height = toastPattern->GetUECTitleBarHeightForTopAlignment(host, toastProp);
    EXPECT_FLOAT_EQ(height, 70.0f);

    mockPipeline->SetInstanceId(0);
    MockContainer::UpdateCurrent(-1);
    SubwindowManager::GetInstance()->ClearToastInSystemSubwindow();
}

/**
 * @tc.name: GetUECTitleBarHeightForTopAlignment002
 * @tc.desc: Test GetUECTitleBarHeightForTopAlignment with DEFAULT mode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetUECTitleBarHeightForTopAlignment002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);

    /**
     * @tc.steps: step2. Create layout wrapper and set showMode to DEFAULT.
     * @tc.expected: Layout wrapper and property are created successfully.
     */
    auto layoutWrapper = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto toastProp = AceType::DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(toastProp, nullptr);
    toastProp->UpdateShowMode(ToastShowMode::DEFAULT);

    /**
     * @tc.steps: step3. Call GetUECTitleBarHeightForTopAlignment and verify result.
     * @tc.expected: Height returns 0 for DEFAULT mode.
     */
    auto height = toastPattern->GetUECTitleBarHeightForTopAlignment(host, toastProp);
    EXPECT_FLOAT_EQ(height, 0.0f);
}

/**
 * @tc.name: GetUECTitleBarHeightForTopAlignment003
 * @tc.desc: Test GetUECTitleBarHeightForTopAlignment with nullptr host.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, GetUECTitleBarHeightForTopAlignment003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    /**
     * @tc.steps: step2. Create layout wrapper and property.
     * @tc.expected: Layout wrapper and property are created successfully.
     */
    auto layoutWrapper = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto toastProp = AceType::DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(toastProp, nullptr);

    /**
     * @tc.steps: step3. Call GetUECTitleBarHeightForTopAlignment with nullptr host.
     * @tc.expected: Height returns 0 for nullptr host.
     */
    auto height = toastPattern->GetUECTitleBarHeightForTopAlignment(nullptr, toastProp);
    EXPECT_FLOAT_EQ(height, 0.0f);
}

/**
 * @tc.name: IsToastInUIExtensionWindow001
 * @tc.desc: Test IsToastInUIExtensionWindow returns false when container is not UIExtension.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, IsToastInUIExtensionWindow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);

    /**
     * @tc.steps: step2. Configure mock container as non-UIExtension window.
     * @tc.expected: Container is configured successfully.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto mockPipeline = AceType::DynamicCast<MockPipelineContext>(pipelineContext);
    ASSERT_NE(mockPipeline, nullptr);
    mockPipeline->SetInstanceId(61);

    MockContainer::UpdateCurrent(61);
    ASSERT_NE(MockContainer::container_, nullptr);
    MockContainer::container_->SetIsUIExtensionWindow(false);
    AceEngine::Get().AddContainer(61, MockContainer::container_);

    /**
     * @tc.steps: step3. Call IsToastInUIExtensionWindow and verify result.
     * @tc.expected: IsInUEC returns false for non-UIExtension window.
     */
    auto isInUEC = toastPattern->IsToastInUIExtensionWindow(host);
    EXPECT_FALSE(isInUEC);

    AceEngine::Get().RemoveContainer(61);
    mockPipeline->SetInstanceId(0);
    MockContainer::UpdateCurrent(-1);
}

/**
 * @tc.name: IsToastInUIExtensionWindow002
 * @tc.desc: Test IsToastInUIExtensionWindow returns false with negative containerId.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, IsToastInUIExtensionWindow002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    /**
     * @tc.steps: step2. Call IsToastInUIExtensionWindow with nullptr host.
     * @tc.expected: IsInUEC returns false for nullptr host.
     */
    auto isInUEC = toastPattern->IsToastInUIExtensionWindow(nullptr);
    EXPECT_FALSE(isInUEC);
}

/**
 * @tc.name: CalculateSafeAreaTopForTopAlignment001
 * @tc.desc: Test CalculateSafeAreaTopForTopAlignment with DEFAULT mode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, CalculateSafeAreaTopForTopAlignment001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto host = toastPattern->GetHost();
    ASSERT_NE(host, nullptr);

    /**
     * @tc.steps: step2. Prepare safeAreaTop, pipelineContext and set title bar height.
     * @tc.expected: All required parameters are valid.
     */
    float safeAreaTop = 0.0f;
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto mockPipeline = AceType::DynamicCast<MockPipelineContext>(pipelineContext);
    ASSERT_NE(mockPipeline, nullptr);
    mockPipeline->SetContainerModalTitleHeight(50);
    mockPipeline->SetInstanceId(71);

    MockContainer::UpdateCurrent(71);
    ASSERT_NE(MockContainer::container_, nullptr);
    MockContainer::container_->SetIsUIExtensionWindow(false);
    AceEngine::Get().AddContainer(71, MockContainer::container_);

    /**
     * @tc.steps: step3. Create layout wrapper and set showMode to DEFAULT.
     * @tc.expected: Layout wrapper and property are created successfully.
     */
    auto layoutWrapper = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto toastProp = AceType::DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(toastProp, nullptr);
    toastProp->UpdateShowMode(ToastShowMode::DEFAULT);

    /**
     * @tc.steps: step4. Call CalculateSafeAreaTopForTopAlignment and verify result.
     * @tc.expected: safeAreaTop equals the title bar height.
     */
    toastPattern->CalculateSafeAreaTopForTopAlignment(safeAreaTop, pipelineContext, toastProp, host);
    EXPECT_FLOAT_EQ(safeAreaTop, 50.0f);

    AceEngine::Get().RemoveContainer(71);
    mockPipeline->SetContainerModalTitleHeight(0);
    mockPipeline->SetInstanceId(0);
    MockContainer::UpdateCurrent(-1);
}

/**
 * @tc.name: CalculateSafeAreaTopForTopAlignment002
 * @tc.desc: Test CalculateSafeAreaTopForTopAlignment with nullptr parameters.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerToastTestTwoNg, CalculateSafeAreaTopForTopAlignment002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create toast node and get ToastPattern.
     * @tc.expected: Toast node and pattern are created successfully.
     */
    auto toastInfo = NG::ToastInfo { .message = MESSAGE, .duration = DURATION };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);

    /**
     * @tc.steps: step2. Prepare safeAreaTop, pipelineContext and toast layout property.
     * @tc.expected: All required parameters are valid.
     */
    float safeAreaTop = 0.0f;
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto layoutWrapper = toastNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto toastProp = AceType::DynamicCast<ToastLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(toastProp, nullptr);

    /**
     * @tc.steps: step3. Call CalculateSafeAreaTopForTopAlignment with nullptr parameters.
     * @tc.expected: safeAreaTop remains 0 for nullptr parameters.
     */
    toastPattern->CalculateSafeAreaTopForTopAlignment(safeAreaTop, nullptr, toastProp, nullptr);
    EXPECT_FLOAT_EQ(safeAreaTop, 0.0f);
}
} // namespace OHOS::Ace::NG