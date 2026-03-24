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
#include <mutex>
#include <optional>
#include <string>

#include "gtest/gtest.h"
#include "test/mock/adapter/mock_ui_session_manager.h"
#include "test/mock/base/mock_foldable_window.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_window.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const NG::BorderWidthProperty BORDER_WIDTH_TEST = { 1.0_vp, 1.0_vp, 1.0_vp, 0.0_vp };
const std::string MESSAGE = "hello world";
} // namespace

class ModalPresentationPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    static void TearDownTestCase();
    static void SetApiVersion(int32_t apiTargetVersion);
};

void ModalPresentationPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
            return sheetTheme;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void ModalPresentationPatternTestNg::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(
        [sheetTheme = AceType::WeakClaim(AceType::RawPtr(sheetTheme))](ThemeType type) -> RefPtr<Theme> {
            if (type == SheetTheme::TypeId()) {
                return sheetTheme.Upgrade();
            } else {
                return nullptr;
            }
        });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void ModalPresentationPatternTestNg::SetApiVersion(int32_t apiTargetVersion)
{
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(apiTargetVersion);
}

void ModalPresentationPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: OnInjectionEvent
 * @tc.desc: Test OnInjectionEvent Ok.
 * @tc.type: FUNC
 */
HWTEST_F(ModalPresentationPatternTestNg, OnInjectionEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    ModalPresentationPatternTestNg::SetUpTestCase();
    ModalPresentationPatternTestNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<ModalPresentationPattern>(201, ModalTransition::ALPHA, std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();

    /**
     * @tc.steps: step2. Change the SheetTheme border.
     * @tc.expected: the border is not updated successfully
     */
    SheetStyle sheetStyle;
    auto sheetPattern = sheetNode->GetPattern<ModalPresentationPattern>();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    ModalPresentationPatternTestNg::SetSheetTheme(sheetTheme);

    std::string command = R"({"cmd":"CloseContentCover"})";
    int32_t ret = sheetPattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_SUCCESS);
    ModalPresentationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: OnInjectionEvent
 * @tc.desc: Test OnInjectionEvent Failed.
 * @tc.type: FUNC
 */
HWTEST_F(ModalPresentationPatternTestNg, OnInjectionEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    ModalPresentationPatternTestNg::SetUpTestCase();
    ModalPresentationPatternTestNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<ModalPresentationPattern>(201, ModalTransition::ALPHA, std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();

    /**
     * @tc.steps: step2. Change the SheetTheme border.
     * @tc.expected: the border is not updated successfully
     */
    SheetStyle sheetStyle;
    auto sheetPattern = sheetNode->GetPattern<ModalPresentationPattern>();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    ModalPresentationPatternTestNg::SetSheetTheme(sheetTheme);

    std::string command = R"({"cmd":"OpenFullModal"})";
    int32_t ret = sheetPattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_FAILED);
    ModalPresentationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: OnAppearTest001
 * @tc.desc: Test ModalPresentationPattern OnAppear Event Report
 * @tc.type: FUNC
 */
HWTEST_F(ModalPresentationPatternTestNg, OnAppearTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ModalPresentationPattern and setup environment
     */
    ModalPresentationPatternTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto modalNode = FrameNode::CreateFrameNode(
        "Modal", 101, AceType::MakeRefPtr<ModalPresentationPattern>(201, ModalTransition::ALPHA, std::move(callback)));
    ASSERT_NE(modalNode, nullptr);

    auto modalPattern = modalNode->GetPattern<ModalPresentationPattern>();
    ASSERT_NE(modalPattern, nullptr);

    /**
     * @tc.steps: step2. Setup Mock UiSessionManager
     */
    MockUiSessionManager* mockUiSessionManager =
        reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    EXPECT_CALL(*mockUiSessionManager, GetComponentChangeEventRegistered())
        .WillRepeatedly(Return(true));

    /**
     * @tc.steps: step3. Test OnAppear event report
     * @tc.expected: OnAppear should trigger ReportComponentChangeEvent
     */
    bool onAppearCalled = false;
    modalPattern->UpdateOnAppear([&onAppearCalled]() { onAppearCalled = true; });
    modalPattern->OnAppear();
    EXPECT_TRUE(onAppearCalled);

    /**
     * @tc.steps: step4. Cleanup
     */
    ModalPresentationPatternTestNg::TearDownTestCase();
}

/**
 * @tc.name: OnDisappearTest001
 * @tc.desc: Test ModalPresentationPattern OnDisappear Event Report
 * @tc.type: FUNC
 */
HWTEST_F(ModalPresentationPatternTestNg, OnDisappearTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ModalPresentationPattern and setup environment
     */
    ModalPresentationPatternTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto modalNode = FrameNode::CreateFrameNode(
        "Modal", 101, AceType::MakeRefPtr<ModalPresentationPattern>(201, ModalTransition::ALPHA, std::move(callback)));
    ASSERT_NE(modalNode, nullptr);

    auto modalPattern = modalNode->GetPattern<ModalPresentationPattern>();
    ASSERT_NE(modalPattern, nullptr);

    /**
     * @tc.steps: step2. Setup Mock UiSessionManager
     */
    MockUiSessionManager* mockUiSessionManager =
        reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    EXPECT_CALL(*mockUiSessionManager, GetComponentChangeEventRegistered())
        .WillRepeatedly(Return(true));

    /**
     * @tc.steps: step3. Test OnDisappear event report
     * @tc.expected: OnDisappear should trigger ReportComponentChangeEvent and set isExecuteOnDisappear_
     */
    bool onDisappearCalled = false;
    modalPattern->UpdateOnDisappear([&onDisappearCalled]() { onDisappearCalled = true; });
    modalPattern->OnDisappear();
    EXPECT_TRUE(onDisappearCalled);
    EXPECT_TRUE(modalPattern->IsExecuteOnDisappear());

    /**
     * @tc.steps: step4. Cleanup
     */
    ModalPresentationPatternTestNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG