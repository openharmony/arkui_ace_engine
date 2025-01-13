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
#include <mutex>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/error/error_code.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "base/log/dump_log.h"
#include "base/window/foldable_window.h"
#include "core/components/common/properties/color.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components/picker/picker_data.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_paint_method.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_theme.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_ng/pattern/toast/toast_layout_algorithm.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string TEXT_TAG = "text";
const OffsetF MENU_OFFSET(10.0, 10.0);
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";
constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t SELECTED_YEAR = 2000;
constexpr int32_t END_YEAR = 2090;
const int VERSION_TWELVE = 12;
const int VERSION_ELEVEN = 11;
const Dimension ADAPT_TOAST_MIN_FONT_SIZE = 12.0_fp;
const Dimension ADAPT_TOAST_MAX_FONT_SIZE = 10.0_fp;
const Dimension ADAPT_TOAST_NORMAL_FONT_SIZE = 100.0_fp;
const Dimension ADAPT_TOAST_ZERO_FONT_SIZE = 0.0_fp;
const Dimension ADAPT_TOAST_NEG_FONT_SIZE = -12.0_fp;
const Dimension DISAPPEAR_FONT_SIZE = 0.0_fp;
const Dimension NORMAL_FONT_SIZE = 10.0_fp;
const Dimension SELECT_FONT_SIZE = 15.0_fp;
constexpr float KEYBOARD_HEIGHT = 600.0f;
} // namespace
class OverlayTestUpdate : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;

protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
    static void CreateSheetStyle(SheetStyle& sheetStyle);
    void CreateSheetBuilder();
    DatePickerSettingData GenDatePickerSettingData();
    void TestUpdateAlign(
        RefPtr<OHOS::Ace::NG::LayoutAlgorithm> toastLayoutAlgorithm, LayoutWrapper* layoutWrapper, ToastInfo toastInfo);
};

void OverlayTestUpdate::SetUpTestCase()
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
void OverlayTestUpdate::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> OverlayTestUpdate::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

void OverlayTestUpdate::CreateSheetStyle(SheetStyle& sheetStyle)
{
    if (!sheetStyle.sheetMode.has_value()) {
        sheetStyle.sheetMode = SheetMode::MEDIUM;
    }
    if (!sheetStyle.showDragBar.has_value()) {
        sheetStyle.showDragBar = true;
    }
}

void OverlayTestUpdate::CreateSheetBuilder()
{
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    builderFunc_ = builderFunc;
    titleBuilderFunc_ = buildTitleNodeFunc;
}

DatePickerSettingData OverlayTestUpdate::GenDatePickerSettingData()
{
    DatePickerSettingData datePickerSettingData;
    datePickerSettingData.isLunar = false;
    datePickerSettingData.showTime = false;
    datePickerSettingData.useMilitary = false;

    PickerTextProperties properties;
    properties.disappearTextStyle_.textColor = Color::RED;
    properties.disappearTextStyle_.fontSize = DISAPPEAR_FONT_SIZE;
    properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    properties.normalTextStyle_.textColor = Color::BLACK;
    properties.normalTextStyle_.fontSize = NORMAL_FONT_SIZE;
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    properties.selectedTextStyle_.textColor = Color::RED;
    properties.selectedTextStyle_.fontSize = SELECT_FONT_SIZE;
    properties.selectedTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    datePickerSettingData.properties = properties;
    datePickerSettingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    datePickerSettingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    datePickerSettingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    datePickerSettingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    return datePickerSettingData;
}

void OverlayTestUpdate::TestUpdateAlign(
    RefPtr<OHOS::Ace::NG::LayoutAlgorithm> toastLayoutAlgorithm, LayoutWrapper* layoutWrapper, ToastInfo toastInfo)
{
    ASSERT_NE(toastLayoutAlgorithm, nullptr);
    ASSERT_NE(layoutWrapper, nullptr);

    toastLayoutAlgorithm->Layout(layoutWrapper);
    EXPECT_EQ(toastInfo.alignment, static_cast<int32_t>(ToastAlignment::TOP_START));

    toastInfo.alignment = static_cast<int32_t>(ToastAlignment::TOP_END);
    toastLayoutAlgorithm->Layout(layoutWrapper);
    EXPECT_EQ(toastInfo.alignment, static_cast<int32_t>(ToastAlignment::TOP_END));

    toastInfo.alignment = static_cast<int32_t>(ToastAlignment::CENTER_START);
    toastLayoutAlgorithm->Layout(layoutWrapper);
    EXPECT_EQ(toastInfo.alignment, static_cast<int32_t>(ToastAlignment::CENTER_START));

    toastInfo.alignment = static_cast<int32_t>(ToastAlignment::CENTER_END);
    toastLayoutAlgorithm->Layout(layoutWrapper);
    EXPECT_EQ(toastInfo.alignment, static_cast<int32_t>(ToastAlignment::CENTER_END));

    toastInfo.alignment = static_cast<int32_t>(ToastAlignment::BOTTOM_START);
    toastLayoutAlgorithm->Layout(layoutWrapper);
    EXPECT_EQ(toastInfo.alignment, static_cast<int32_t>(ToastAlignment::BOTTOM_START));

    toastInfo.alignment = static_cast<int32_t>(ToastAlignment::BOTTOM_END);
    toastLayoutAlgorithm->Layout(layoutWrapper);
    EXPECT_EQ(toastInfo.alignment, static_cast<int32_t>(ToastAlignment::BOTTOM_END));
}

/**
 * @tc.name: ToastTest001
 * @tc.desc: Test OverlayManager::ToastView.UpdateTextLayoutPropertyChangeValue.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest001, TestSize.Level1)
{
     /**
     * @tc.steps: step1. create DimensionOffset toastInfo.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, false, ToastShowMode::TOP_MOST, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    const std::optional<Color> textColor = Color::RED;
    /**
     * @tc.steps: step2. create ToastNode toastPattern1.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. create textNode textLayoutProperty.
     */
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    /**
     * @tc.steps: step4. change version.
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    /**
     * @tc.steps: step5. save version.
     */
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step6. test UpdateTextLayoutProperty.
     */
    ToastView::UpdateTextLayoutProperty(textNode, MESSAGE, false, textColor);
    EXPECT_EQ(textLayoutProperty->GetTextOverflow(), TextOverflow::ELLIPSIS);
    EXPECT_EQ(textLayoutProperty->GetEllipsisMode(), EllipsisMode::TAIL);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest002
 * @tc.desc: Test OverlayManager::ToastView.UpdateTextLayoutPropertyChangeValue.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create DimensionOffset change toastInfo.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::TOP_MOST, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    const std::optional<Color> textColor = Color::RED;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step2. create textNode textLayoutProperty.
     */
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    /**
     * @tc.steps: step3. change version and save old version.
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step4. test VERSION_TWELVEversion and UpdateTextLayoutProperty.
     */
    ToastView::UpdateTextLayoutProperty(textNode, MESSAGE, false, textColor);
    EXPECT_EQ(textLayoutProperty->GetTextOverflow(), TextOverflow::ELLIPSIS);
    EXPECT_EQ(textLayoutProperty->GetEllipsisMode(), EllipsisMode::TAIL);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest003
 * @tc.desc: Test OverlayManager::ToastView.UpdateTextLayoutPropertyChangeValue1.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create offset toastInfo change toastInfovalue.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 1, BOTTOMSTRING, false, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    const std::optional<Color> textColor = Color::RED;
    /**
     * @tc.steps: step2. CreateToastNode toastPattern1.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. create textNode textLayoutProperty.
     */
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    /**
     * @tc.steps: step4. change VERSION_TWELVE version and save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step5. test UpdateTextLayoutProperty .
     */
    ToastView::UpdateTextLayoutProperty(textNode, MESSAGE, false, textColor);
    auto textval = textLayoutProperty->GetTextOverflow();
    auto textva2 = textLayoutProperty->GetEllipsisMode();
    EXPECT_EQ(textval, TextOverflow::ELLIPSIS);
    EXPECT_EQ(textva2, EllipsisMode::TAIL);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest004
 * @tc.desc: Test OverlayManager::UpdateTextLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ready offset toastInfo toastPattern change tosatinfo.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    const std::optional<Color> textColor = Color::RED;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    /**
     * @tc.steps: step2. create textNode textLayoutProperty.
     */
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    /**
     * @tc.steps: step3. change VERSION_TWELVE version  and save textNode.
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step4.Test UpdateTextLayoutProperty for diff toastInfo.
     */
    ToastView::UpdateTextLayoutProperty(textNode, MESSAGE, true, textColor);
    auto textval1 = textLayoutProperty->GetLayoutDirection();
    auto textval2 = textLayoutProperty->GetTextOverflow();
    auto textval3 = textLayoutProperty->GetEllipsisMode();
    auto textval4 = textLayoutProperty->GetTextColorValue(Color::BLACK);
    EXPECT_EQ(textval1, TextDirection::AUTO);
    EXPECT_EQ(textval2, TextOverflow::ELLIPSIS);
    EXPECT_EQ(textval3, EllipsisMode::TAIL);
    EXPECT_EQ(textval4, Color::RED);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest005
 * @tc.desc: Test OverlayManager::UpdateTextLayoutPropertyChangeValue.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toastInfo toastPattern.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset,
        Color::BLUE, Color::RED, 0, ShadowConfig::DefaultShadowL };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    /**
     * @tc.steps: step2. create textNode textLayoutProperty previewNode textContext.
     */
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    auto textContext = textNode->GetRenderContext();
    ASSERT_NE(textContext, nullptr);
    /**
     * @tc.steps: step3. Define VERSION_TWELVE version and save.
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step3. text textContext.
     */
    ToastView::UpdateToastContext(toastNode);
    auto toastContext = toastNode->GetRenderContext();
    ASSERT_NE(toastContext, nullptr);
    /**
     * @tc.steps: step4. GetBackBlurStyle GetBackgroundColorValue.
     */
    auto styleOption = toastContext->GetBackBlurStyle();
    auto testval1 = toastContext->GetBackgroundColorValue();
    auto shadow1 = toastContext->GetBackShadow().value();
    EXPECT_EQ(testval1, Color::BLUE);
    EXPECT_EQ(styleOption->blurStyle, BlurStyle::NO_MATERIAL);
    EXPECT_EQ(shadow1, ShadowConfig::DefaultShadowL);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest006
 * @tc.desc: Test Change toastInfo effect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toastInfo offset and change ToastShowMode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, false, ToastShowMode::TOP_MOST, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    /**
     * @tc.steps: step2. CreateToastNode GetPattern.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    /**
     * @tc.steps: step3. GetFirstChild GetLayoutProperty.
     */
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto textContext = textNode->GetRenderContext();
    ASSERT_NE(textContext, nullptr);
    /**
     * @tc.steps: step3. change version.
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step3. test UpdateToastContext.
     */
    ToastView::UpdateToastContext(toastNode);
    auto toastContext = toastNode->GetRenderContext();
    ASSERT_NE(toastContext, nullptr);
    /**
     * @tc.steps: step4. GetBackBlurStyle GetBackgroundColorValue.
     */
    auto styleOption = toastContext->GetBackBlurStyle();
    auto testval1 = toastContext->GetBackgroundColorValue();
    EXPECT_EQ(testval1, Color::TRANSPARENT);
    EXPECT_EQ(styleOption->blurStyle, BlurStyle::COMPONENT_ULTRA_THICK);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest007
 * @tc.desc: Test Change toastInfo effect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest007, TestSize.Level1)
{
     /**
      * @tc.steps: step1. create toastInfo offset.
      */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::TOP_MOST, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    /**
     * @tc.steps: step2. create FrameNode textContext.
     */
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textContext = textNode->GetRenderContext();
    ASSERT_NE(textContext, nullptr);
    /**
     * @tc.steps: step3. Get textNode and textLayoutProperty.
     */
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    /**
     * @tc.steps: step4. change version and Save.
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step5. Test UpdateToastContext.
     */
    ToastView::UpdateToastContext(toastNode);
    auto toastContext = toastNode->GetRenderContext();
    ASSERT_NE(toastContext, nullptr);
    /**
     * @tc.steps: step6. GetBackBlurStyle and GetBackgroundColorValue.
     */
    auto styleOption = toastContext->GetBackBlurStyle();
    auto testval1 = toastContext->GetBackgroundColorValue();
    EXPECT_EQ(testval1, Color::TRANSPARENT);
    EXPECT_EQ(styleOption->blurStyle, BlurStyle::COMPONENT_ULTRA_THICK);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest008
 * @tc.desc: Test OverlayManager::ToastView.Test Change toastInfo effect VERSION_TWELVE version.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textContext offset and change ToastShowMode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, false, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textContext = textNode->GetRenderContext();
    ASSERT_NE(textContext, nullptr);
    /**
     * @tc.steps: step2. create textLayoutProperty.
     */
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    /**
     * @tc.steps: step3. change version.
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    ToastView::UpdateToastContext(toastNode);
    auto toastContext = toastNode->GetRenderContext();
    ASSERT_NE(toastContext, nullptr);
    /**
     * @tc.steps: step4. text textContext.
     */
    auto styleOption = toastContext->GetBackBlurStyle();
    auto testval1 = toastContext->GetBackgroundColorValue();
    EXPECT_EQ(testval1, Color::TRANSPARENT);
    EXPECT_EQ(styleOption->blurStyle, BlurStyle::COMPONENT_ULTRA_THICK);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest009
 * @tc.desc: Test UpdateToastContext Low version change ToastView.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toastInfo toastTheme and change toastInfo.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    /**
     * @tc.steps: step2. CreateToastNode GetPattern GetFirstChild.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    /**
     * @tc.steps: step3. CreateFrameNode GetRenderContext.
     */
    auto textContext = textNode->GetRenderContext();
    ASSERT_NE(textContext, nullptr);
    /**
     * @tc.steps: step4. GetCurrentContext GetBackgroundColor.
     */
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
    ASSERT_NE(toastTheme, nullptr);
    auto toastBackgroundColor = toastTheme->GetBackgroundColor();
    /**
     * @tc.steps: step5. create textLayoutProperty.
     */
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    /**
     * @tc.steps: step6. Change low version UpdateToastContext and Save.
     */
    int32_t settingApiVersion = VERSION_ELEVEN;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step7. text low version UpdateToastContext.
     */
    ToastView::UpdateToastContext(toastNode);
    auto toastContext = toastNode->GetRenderContext();
    ASSERT_NE(toastContext, nullptr);
    EXPECT_EQ(toastContext->GetBackgroundColorValue(), toastBackgroundColor);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest010
 * @tc.desc: Test UpdateToastContext Low version change ToastView.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toastInfo toastTheme and change ToastShowMode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, false, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    /**
     * @tc.steps: step2. CreateToastNode GetPattern GetFirstChild.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    /**
     * @tc.steps: step3. CreateFrameNode GetRenderContext.
     */
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    auto textContext = textNode->GetRenderContext();
    ASSERT_NE(textContext, nullptr);
    /**
     * @tc.steps: step4. GetCurrentContext GetBackgroundColor.
     */
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
    ASSERT_NE(toastTheme, nullptr);
    auto toastBackgroundColor = toastTheme->GetBackgroundColor();
    /**
     * @tc.steps: step5. create textLayoutProperty.
     */
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    /**
     * @tc.steps: step6. Change low version UpdateToastContext and Save.
     */
    int32_t settingApiVersion = VERSION_ELEVEN;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step7. text low version UpdateToastContext.
     */
    ToastView::UpdateToastContext(toastNode);
    auto toastContext = toastNode->GetRenderContext();
    ASSERT_NE(toastContext, nullptr);
    EXPECT_EQ(toastContext->GetBackgroundColorValue(), toastBackgroundColor);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest011
 * @tc.desc: Test UpdateToastContext Low version change ToastView.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toastInfo toastTheme and change toastInfo.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, false, ToastShowMode::TOP_MOST, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    /**
     * @tc.steps: step2. CreateToastNode GetPattern GetFirstChild.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    /**
     * @tc.steps: step3. CreateFrameNode GetRenderContext.
     */
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    auto textContext = textNode->GetRenderContext();
    ASSERT_NE(textContext, nullptr);
    /**
     * @tc.steps: step4. GetCurrentContext GetBackgroundColor.
     */
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
    ASSERT_NE(toastTheme, nullptr);
    auto toastBackgroundColor = toastTheme->GetBackgroundColor();
    /**
     * @tc.steps: step5. create textLayoutProperty.
     */
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    /**
     * @tc.steps: step6. Change low version UpdateToastContext and Save.
     */
    int32_t settingApiVersion = VERSION_ELEVEN;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step7. text low version UpdateToastContext.
     */
    ToastView::UpdateToastContext(toastNode);
    auto toastContext = toastNode->GetRenderContext();
    ASSERT_NE(toastContext, nullptr);
    EXPECT_EQ(toastContext->GetBackgroundColorValue(), toastBackgroundColor);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest012
 * @tc.desc: Test UpdateToastContext Low version change ToastView.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toastInfo toastTheme and change toastInfo.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::TOP_MOST, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    /**
     * @tc.steps: step2. CreateToastNode GetPattern GetFirstChild.
     */
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto toastPattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    /**
     * @tc.steps: step3. CreateFrameNode GetRenderContext.
     */
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    auto textContext = textNode->GetRenderContext();
    ASSERT_NE(textContext, nullptr);
    /**
     * @tc.steps: step4. GetCurrentContext GetBackgroundColor.
     */
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toastTheme = pipelineContext->GetTheme<ToastTheme>();
    ASSERT_NE(toastTheme, nullptr);
    auto toastBackgroundColor = toastTheme->GetBackgroundColor();
    /**
     * @tc.steps: step5. create textLayoutProperty.
     */
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    /**
     * @tc.steps: step6. Change low version UpdateToastContext and Save.
     */
    int32_t settingApiVersion = VERSION_ELEVEN;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step7. text low version UpdateToastContext.
     */
    ToastView::UpdateToastContext(toastNode);
    auto toastContext = toastNode->GetRenderContext();
    ASSERT_NE(toastContext, nullptr);
    EXPECT_EQ(toastContext->GetBackgroundColorValue(), toastBackgroundColor);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest013
 * @tc.desc: ToastPattern::UpdateToastSize .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. DimensionOffset toastInfo toastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetTextMaxWidth GetLayoutProperty.
     */
    auto limitWidth = Dimension(toastPattern1->GetTextMaxWidth());
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    CHECK_NULL_VOID(toastProperty);
    /**
     * @tc.steps: step4. Text VERSION_TWELVE version And Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step5. Text UpdateToastSize For Diff toastInfo.
     */
    toastPattern1->UpdateToastSize(toastNode);
    auto value = toastProperty->GetCalcLayoutConstraint()->selfIdealSize->Width();
    ASSERT_NE(toastPattern1, nullptr);
    EXPECT_EQ(value, NG::CalcLength(limitWidth));
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest014
 * @tc.desc: ToastPattern::UpdateToastSize .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. DimensionOffset toastInfo toastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::TOP_MOST, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetTextMaxWidth GetLayoutProperty.
     */
    auto limitWidth = Dimension(toastPattern1->GetTextMaxWidth());
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    CHECK_NULL_VOID(toastProperty);
    /**
     * @tc.steps: step4. Text VERSION_TWELVE version And Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step5. Text UpdateToastSize For Diff toastInfo.
     */
    toastPattern1->UpdateToastSize(toastNode);
    auto value = toastProperty->GetCalcLayoutConstraint()->selfIdealSize->Width();
    ASSERT_NE(toastPattern1, nullptr);
    EXPECT_EQ(value, NG::CalcLength(limitWidth));
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest015
 * @tc.desc: ToastPattern::UpdateToastSize .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. DimensionOffset toastInfo toastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, false, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetTextMaxWidth GetLayoutProperty.
     */
    auto limitWidth = Dimension(toastPattern1->GetTextMaxWidth());
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    CHECK_NULL_VOID(toastProperty);
    /**
     * @tc.steps: step4. Text VERSION_TWELVE version And Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step5. Text UpdateToastSize For Diff toastInfo.
     */
    toastPattern1->UpdateToastSize(toastNode);
    auto value = toastProperty->GetCalcLayoutConstraint()->selfIdealSize->Width();
    ASSERT_NE(toastPattern1, nullptr);
    EXPECT_EQ(value, NG::CalcLength(limitWidth));
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest016
 * @tc.desc: ToastPattern::UpdateToastSize .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DimensionOffset toastInfo Change ToastShowMode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, false, ToastShowMode::TOP_MOST, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetTextMaxWidth GetLayoutProperty.
     */
    auto limitWidth = Dimension(toastPattern1->GetTextMaxWidth());
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    CHECK_NULL_VOID(toastProperty);
    /**
     * @tc.steps: step4. Text VERSION_TWELVE version And Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step5. Text UpdateToastSize For Diff toastInfo.
     */
    toastPattern1->UpdateToastSize(toastNode);
    auto value = toastProperty->GetCalcLayoutConstraint()->selfIdealSize->Width();
    ASSERT_NE(toastPattern1, nullptr);
    EXPECT_EQ(value, NG::CalcLength(limitWidth));
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest017
 * @tc.desc: ToastPattern::UpdateTextSizeConstraint .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. offset toastInfo CreateToastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    
    /**
     * @tc.steps: step3. GetLayoutProperty GetCurrentContext CreateToastNode.
     */
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textLayoutProperty = textNode->GetLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    /**
     * @tc.steps: step4. text VERSION_TWELVE version Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    textProperty->UpdateAdaptMinFontSize(ADAPT_TOAST_MIN_FONT_SIZE);
    auto toastMaxFontSize = toastTheme->GetTextStyle().GetFontSize();
    /**
     * @tc.steps: step5. text VERSION_TWELVE version UpdateToastContext .
     */
    Dimension text1 = 0.0_fp;
    toastPattern1->UpdateTextSizeConstraint(textNode);
    auto fontSize = textProperty->GetAdaptMinFontSizeValue(text1);
    auto fontSize1 = textProperty->GetAdaptMaxFontSizeValue(text1);
    EXPECT_EQ(fontSize, ADAPT_TOAST_MIN_FONT_SIZE);
    EXPECT_EQ(fontSize1, toastMaxFontSize);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest018
 * @tc.desc: ToastPattern::UpdateTextSizeConstraint .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. offset toastInfo CreateToastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetLayoutProperty GetCurrentContext CreateToastNode.
     */
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textLayoutProperty = textNode->GetLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    /**
     * @tc.steps: step4. text VERSION_TWELVE version Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto toastMaxFontSize = toastTheme->GetTextStyle().GetFontSize();
    /**
     * @tc.steps: step5. text VERSION_TWELVE version UpdateToastContext .
     */
    toastPattern1->UpdateTextSizeConstraint(textNode);
    textProperty->UpdateAdaptMinFontSize(ADAPT_TOAST_MAX_FONT_SIZE);
    auto fontSize = textProperty->GetAdaptMinFontSize();
    auto fontSize1 = textProperty->GetAdaptMaxFontSize();
    
    EXPECT_EQ(fontSize, ADAPT_TOAST_MAX_FONT_SIZE);
    EXPECT_EQ(fontSize1, toastMaxFontSize);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest019
 * @tc.desc: ToastPattern::UpdateTextSizeConstraint .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. offset toastInfo CreateToastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetLayoutProperty GetCurrentContext CreateToastNode.
     */
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textLayoutProperty = textNode->GetLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    /**
     * @tc.steps: step4. text VERSION_TWELVE version Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto toastMaxFontSize = toastTheme->GetTextStyle().GetFontSize();
    /**
     * @tc.steps: step5. text VERSION_TWELVE version UpdateToastContext .
     */
    toastPattern1->UpdateTextSizeConstraint(textNode);
    textProperty->UpdateAdaptMinFontSize(ADAPT_TOAST_NORMAL_FONT_SIZE);
    auto fontSize = textProperty->GetAdaptMinFontSize();
    auto fontSize1 = textProperty->GetAdaptMaxFontSize();
    EXPECT_EQ(fontSize, ADAPT_TOAST_NORMAL_FONT_SIZE);
    EXPECT_EQ(fontSize1, toastMaxFontSize);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest020
 * @tc.desc: ToastPattern::UpdateTextSizeConstraint .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. offset toastInfo CreateToastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetLayoutProperty GetCurrentContext CreateToastNode.
     */
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textLayoutProperty = textNode->GetLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    /**
     * @tc.steps: step4. text VERSION_TWELVE version Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto toastMaxFontSize = toastTheme->GetTextStyle().GetFontSize();
    /**
     * @tc.steps: step5. text VERSION_TWELVE version UpdateToastContext .
     */
    toastPattern1->UpdateTextSizeConstraint(textNode);
    textProperty->UpdateAdaptMinFontSize(ADAPT_TOAST_ZERO_FONT_SIZE);
    auto fontSize = textProperty->GetAdaptMinFontSize();
    auto fontSize1 = textProperty->GetAdaptMaxFontSize();
    EXPECT_EQ(fontSize, ADAPT_TOAST_ZERO_FONT_SIZE);
    EXPECT_EQ(fontSize1, toastMaxFontSize);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest021
 * @tc.desc: ToastPattern::UpdateTextSizeConstraint .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. offset toastInfo CreateToastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetLayoutProperty GetCurrentContext CreateToastNode.
     */
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textLayoutProperty = textNode->GetLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    /**
     * @tc.steps: step4. text VERSION_TWELVE version Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto toastMaxFontSize = toastTheme->GetTextStyle().GetFontSize();
    /**
     * @tc.steps: step5. text VERSION_TWELVE version UpdateToastContext .
     */
    toastPattern1->UpdateTextSizeConstraint(textNode);
    textProperty->UpdateAdaptMinFontSize(ADAPT_TOAST_NEG_FONT_SIZE);
    auto fontSize = textProperty->GetAdaptMinFontSize();
    auto fontSize1 = textProperty->GetAdaptMaxFontSize();
    EXPECT_EQ(fontSize, ADAPT_TOAST_NEG_FONT_SIZE);
    EXPECT_EQ(fontSize1, toastMaxFontSize);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest022
 * @tc.desc: ToastPattern::UpdateTextSizeConstraint .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. offset toastInfo CreateToastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetLayoutProperty GetCurrentContext CreateToastNode.
     */
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textLayoutProperty = textNode->GetLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    /**
     * @tc.steps: step4. text VERSION_TWELVE version Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step5. text VERSION_TWELVE version UpdateToastContext .
     */
    toastPattern1->UpdateTextSizeConstraint(textNode);
    textProperty->UpdateAdaptMinFontSize(ADAPT_TOAST_MIN_FONT_SIZE);
    textProperty->UpdateAdaptMaxFontSize(ADAPT_TOAST_MIN_FONT_SIZE);
    auto fontSize = textProperty->GetAdaptMinFontSize();
    auto fontSize1 = textProperty->GetAdaptMaxFontSize();
    EXPECT_EQ(fontSize, ADAPT_TOAST_MIN_FONT_SIZE);
    EXPECT_EQ(fontSize1, ADAPT_TOAST_MIN_FONT_SIZE);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest023
 * @tc.desc: ToastPattern::UpdateTextSizeConstraint .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. offset toastInfo CreateToastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetLayoutProperty GetCurrentContext CreateToastNode.
     */
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textLayoutProperty = textNode->GetLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    /**
     * @tc.steps: step4. text VERSION_TWELVE version Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step5. text VERSION_TWELVE version UpdateToastContext .
     */
    toastPattern1->UpdateTextSizeConstraint(textNode);
    textProperty->UpdateAdaptMinFontSize(ADAPT_TOAST_MAX_FONT_SIZE);
    textProperty->UpdateAdaptMaxFontSize(ADAPT_TOAST_MAX_FONT_SIZE);
    auto fontSize = textProperty->GetAdaptMinFontSize();
    auto fontSize1 = textProperty->GetAdaptMaxFontSize();
    EXPECT_EQ(fontSize, ADAPT_TOAST_MAX_FONT_SIZE);
    EXPECT_EQ(fontSize1, ADAPT_TOAST_MAX_FONT_SIZE);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest024
 * @tc.desc: ToastPattern::UpdateTextSizeConstraint .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. offset toastInfo CreateToastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetLayoutProperty GetCurrentContext CreateToastNode.
     */
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textLayoutProperty = textNode->GetLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    /**
     * @tc.steps: step4. text VERSION_TWELVE version Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step5. text VERSION_TWELVE version UpdateToastContext .
     */
    toastPattern1->UpdateTextSizeConstraint(textNode);
    textProperty->UpdateAdaptMinFontSize(ADAPT_TOAST_NORMAL_FONT_SIZE);
    textProperty->UpdateAdaptMaxFontSize(ADAPT_TOAST_NORMAL_FONT_SIZE);
    auto fontSize = textProperty->GetAdaptMinFontSize();
    auto fontSize1 = textProperty->GetAdaptMaxFontSize();
    EXPECT_EQ(fontSize, ADAPT_TOAST_NORMAL_FONT_SIZE);
    EXPECT_EQ(fontSize1, ADAPT_TOAST_NORMAL_FONT_SIZE);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest025
 * @tc.desc: ToastPattern::UpdateTextSizeConstraint .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. offset toastInfo CreateToastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetLayoutProperty GetCurrentContext CreateToastNode.
     */
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textLayoutProperty = textNode->GetLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    /**
     * @tc.steps: step4. text VERSION_TWELVE version Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step5. text VERSION_TWELVE version UpdateToastContext .
     */
    toastPattern1->UpdateTextSizeConstraint(textNode);
    textProperty->UpdateAdaptMinFontSize(ADAPT_TOAST_ZERO_FONT_SIZE);
    textProperty->UpdateAdaptMaxFontSize(ADAPT_TOAST_ZERO_FONT_SIZE);
    auto fontSize = textProperty->GetAdaptMinFontSize();
    auto fontSize1 = textProperty->GetAdaptMaxFontSize();
    EXPECT_EQ(fontSize, ADAPT_TOAST_ZERO_FONT_SIZE);
    EXPECT_EQ(fontSize1, ADAPT_TOAST_ZERO_FONT_SIZE);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest026
 * @tc.desc: ToastPattern::UpdateTextSizeConstraint .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. offset toastInfo CreateToastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetLayoutProperty GetCurrentContext CreateToastNode.
     */
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textLayoutProperty = textNode->GetLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    /**
     * @tc.steps: step4. text VERSION_TWELVE version Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step5. text VERSION_TWELVE version UpdateToastContext .
     */
    toastPattern1->UpdateTextSizeConstraint(textNode);
    textProperty->UpdateAdaptMinFontSize(ADAPT_TOAST_NEG_FONT_SIZE);
    textProperty->UpdateAdaptMaxFontSize(ADAPT_TOAST_NEG_FONT_SIZE);
    auto fontSize = textProperty->GetAdaptMinFontSize();
    auto fontSize1 = textProperty->GetAdaptMaxFontSize();
    EXPECT_EQ(fontSize, ADAPT_TOAST_NEG_FONT_SIZE);
    EXPECT_EQ(fontSize1, ADAPT_TOAST_NEG_FONT_SIZE);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest027
 * @tc.desc: ToastPattern::UpdateTextSizeConstraint .
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. offset toastInfo CreateToastNode.
     */
    auto offset = DimensionOffset(MENU_OFFSET);
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0, offset };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    /**
     * @tc.steps: step2. GetPattern.
     */
    auto toastPattern1 = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(toastPattern1, nullptr);
    /**
     * @tc.steps: step3. GetLayoutProperty GetCurrentContext CreateToastNode.
     */
    auto toastProperty = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProperty, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(toastNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textLayoutProperty = textNode->GetLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto toastTheme = context->GetTheme<ToastTheme>();
    CHECK_NULL_VOID(toastTheme);
    /**
     * @tc.steps: step4. text VERSION_TWELVE version Save .
     */
    int32_t settingApiVersion = VERSION_TWELVE;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    /**
     * @tc.steps: step5. text VERSION_TWELVE version UpdateToastContext .
     */
    toastPattern1->UpdateTextSizeConstraint(textNode);
    textProperty->UpdateAdaptMinFontSize(ADAPT_TOAST_MIN_FONT_SIZE);
    textProperty->UpdateAdaptMaxFontSize(ADAPT_TOAST_MAX_FONT_SIZE);
    auto fontSize = textProperty->GetAdaptMinFontSize();
    auto fontSize1 = textProperty->GetAdaptMaxFontSize();
    EXPECT_EQ(fontSize, ADAPT_TOAST_MIN_FONT_SIZE);
    EXPECT_EQ(fontSize1, ADAPT_TOAST_MAX_FONT_SIZE);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToastTest028
 * @tc.desc: Test UpdateToastAlign.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateToastNode.
     */
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0 };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);
    auto toastLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(toastLayoutAlgorithm, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(toastNode, toastNode->GetGeometryNode(), toastNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. CreateTextNode.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, textNode->GetGeometryNode(), textNode->GetLayoutProperty());
    ASSERT_NE(textLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(textLayoutWrapper);
    /**
     * @tc.steps: step3. Test left to right alignment.
     */
    TestUpdateAlign(toastLayoutAlgorithm, layoutWrapper.rawPtr_, toastInfo);

    /**
     * @tc.steps: step4. Test right to left alignment.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    TestUpdateAlign(toastLayoutAlgorithm, layoutWrapper.rawPtr_, toastInfo);
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
}

/**
 * @tc.name: ToastTest029
 * @tc.desc: Test ToastPattern::GetTextLineHeight ToastPattern::GetTextMaxWidth ToastPattern::GetTextMaxHeight.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateTextNode.
     */
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0 };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    pattern->SetTextNode(textNode);

    /**
     * @tc.steps: step2. Test GetTextLineHeight.
     */
    auto textLineHeight = pattern->GetTextLineHeight(textNode);
    EXPECT_EQ(textLineHeight, 0);

    /**
     * @tc.steps: step3. Test GetTextMaxWidth.
     */
    auto textMaxWidth = pattern->GetTextMaxWidth();
    EXPECT_EQ(textMaxWidth, 0);

    /**
     * @tc.steps: step3. Test GetTextMaxHeight.
     */
    auto textMaxHeight = pattern->GetTextMaxHeight();
    EXPECT_EQ(textMaxHeight, 832);
}

/**
 * @tc.name: ToastTest030
 * @tc.desc: Test ToastPattern::InitWrapperRect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateToastNode.
     */
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0 };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);
    auto toastProps = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProps, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(toastNode, toastNode->GetGeometryNode(), toastNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.steps: step2. Init wrapper rect.
     */
    pattern->InitWrapperRect(layoutWrapper.rawPtr_, toastProps);

    /**
     * @tc.steps: step3. Test not in hover mode, toast's wrapper rect.
     */
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    float safeAreaTop = safeAreaManager->GetSystemSafeArea().top_.Length();
    const auto& safeArea = toastProps->GetSafeAreaInsets();
    float safeAreaBottom =
        safeArea ? safeArea->bottom_.Length() : safeAreaManager->GetSafeAreaWithoutProcess().bottom_.Length();
    EXPECT_EQ(pattern->wrapperRect_.Width(), pipelineContext->GetRootWidth());
    EXPECT_EQ(pattern->wrapperRect_.Height(), pipelineContext->GetRootHeight()- safeAreaTop - safeAreaBottom);
    EXPECT_EQ(pattern->wrapperRect_.Top(), safeAreaTop);
}

/**
 * @tc.name: ToastTest031
 * @tc.desc: Test ToastPattern::InitWrapperRect ToastPattern::UpdateHoverModeRect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateToastNode, enable hover mode, hover mode area is default.
     */
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0 };
    toastInfo.enableHoverMode = true;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);
    auto toastProps = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProps, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(toastNode, toastNode->GetGeometryNode(), toastNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.steps: step2. Set in hover mode.
     */
    pipelineContext->isHalfFoldHoverStatus_ = true;

    /**
     * @tc.steps: step3. Set fold crease region.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    std::vector<Rect> rects;
    Rect rect;
    rect.SetRect(0, 1064, 2294, 171);
    rects.insert(rects.end(), rect);
    displayInfo->SetCurrentFoldCreaseRegion(rects);
    float foldCreaseBottom = 1235.0f;

    /**
     * @tc.steps: step4. Init wrapper rect.
     */
    pattern->InitWrapperRect(layoutWrapper.rawPtr_, toastProps);

    /**
     * @tc.steps: step3. Test in hover mode, hover mode area is default, toast's wrapper rect.
     */
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    const auto& safeArea = toastProps->GetSafeAreaInsets();
    float safeAreaBottom =
        safeArea ? safeArea->bottom_.Length() : safeAreaManager->GetSafeAreaWithoutProcess().bottom_.Length();
    EXPECT_EQ(pattern->wrapperRect_.Width(), pipelineContext->GetRootWidth());
    EXPECT_EQ(pattern->wrapperRect_.Height(), pipelineContext->GetRootHeight()- foldCreaseBottom - safeAreaBottom);
    EXPECT_EQ(pattern->wrapperRect_.Top(), foldCreaseBottom);
}

/**
 * @tc.name: ToastTest032
 * @tc.desc: Test ToastPattern::InitWrapperRect ToastPattern::UpdateHoverModeRect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateToastNode, enable hover mode, hover mode area is default.
     */
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0 };
    toastInfo.enableHoverMode = true;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);
    auto toastProps = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProps, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(toastNode, toastNode->GetGeometryNode(), toastNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.steps: step2. Set in hover mode.
     */
    pipelineContext->isHalfFoldHoverStatus_ = true;

    /**
     * @tc.steps: step3. Set fold crease region and keyboard safe area.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    std::vector<Rect> rects;
    Rect rect;
    rect.SetRect(0, 1064, 2294, 171);
    rects.insert(rects.end(), rect);
    displayInfo->SetCurrentFoldCreaseRegion(rects);
    float foldCreaseTop = 1064.0f;
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    auto ret = safeAreaManager->UpdateKeyboardSafeArea(KEYBOARD_HEIGHT);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step4. Init wrapper rect.
     */
    pattern->InitWrapperRect(layoutWrapper.rawPtr_, toastProps);

    /**
     * @tc.steps: step5. Test in hover mode, hover mode area is default, avoid keyboard toast's wrapper rect.
     */
    float safeAreaTop = safeAreaManager->GetSystemSafeArea().top_.Length();
    EXPECT_EQ(pattern->wrapperRect_.Width(), pipelineContext->GetRootWidth());
    EXPECT_EQ(pattern->wrapperRect_.Height(), foldCreaseTop - safeAreaTop);
    EXPECT_EQ(pattern->wrapperRect_.Top(), safeAreaTop);
    auto reset = safeAreaManager->UpdateKeyboardSafeArea(0.0f);
    EXPECT_EQ(reset, true);
}

/**
 * @tc.name: ToastTest033
 * @tc.desc: Test ToastPattern::InitWrapperRect ToastPattern::UpdateHoverModeRect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateToastNode, enable hover mode, hover mode area is TOP_SCREEN.
     */
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0 };
    toastInfo.enableHoverMode = true;
    toastInfo.hoverModeArea = HoverModeAreaType::TOP_SCREEN;
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);
    auto toastProps = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProps, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(toastNode, toastNode->GetGeometryNode(), toastNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.steps: step2. Set in hover mode.
     */
    pipelineContext->isHalfFoldHoverStatus_ = true;

    /**
     * @tc.steps: step3. Set fold crease region.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    std::vector<Rect> rects;
    Rect rect;
    rect.SetRect(0, 1064, 2294, 171);
    rects.insert(rects.end(), rect);
    displayInfo->SetCurrentFoldCreaseRegion(rects);
    float foldCreaseTop = 1064.0f;
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);

    /**
     * @tc.steps: step4. Init wrapper rect.
     */
    pattern->InitWrapperRect(layoutWrapper.rawPtr_, toastProps);

    /**
     * @tc.steps: step5. Test in hover mode, hover mode area is TOP_SCREEN.
     */
    float safeAreaTop = safeAreaManager->GetSystemSafeArea().top_.Length();
    EXPECT_EQ(pattern->wrapperRect_.Width(), pipelineContext->GetRootWidth());
    EXPECT_EQ(pattern->wrapperRect_.Height(), foldCreaseTop - safeAreaTop);
    EXPECT_EQ(pattern->wrapperRect_.Top(), safeAreaTop);
}

/**
 * @tc.name: ToastTest034
 * @tc.desc: Test Toast offset.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayTestUpdate, ToastTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateToastNode.
     */
    ToastInfo toastInfo = { MESSAGE, 0, BOTTOMSTRING, true, ToastShowMode::DEFAULT, 0 };
    auto toastNode = ToastView::CreateToastNode(toastInfo);
    ASSERT_NE(toastNode, nullptr);
    auto pattern = toastNode->GetPattern<ToastPattern>();
    ASSERT_NE(pattern, nullptr);
    auto toastProps = toastNode->GetLayoutProperty<ToastLayoutProperty>();
    ASSERT_NE(toastProps, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(toastNode, toastNode->GetGeometryNode(), toastNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);

    /**
     * @tc.steps: step2. Init wrapper rect.
     */
    pattern->InitWrapperRect(layoutWrapper.rawPtr_, toastProps);

    /**
     * @tc.steps: step3. Toast showMode and offset.
     */
    auto toastContext = toastNode->GetRenderContext();
    ASSERT_NE(toastContext, nullptr);
    EXPECT_TRUE(pattern->IsDefaultToast());
    EXPECT_TRUE(pattern->OnDirtyLayoutWrapperSwap(toastNode->CreateLayoutWrapper(), DirtySwapConfig()));
    toastContext->UpdateOffset({pattern->GetOffsetX(toastNode->CreateLayoutWrapper()),
        pattern->GetOffsetY(toastNode->CreateLayoutWrapper())});
    EXPECT_EQ(toastContext->GetOffset()->GetX().ConvertToPx(), 360.0);
    EXPECT_EQ(toastContext->GetOffset()->GetY().ConvertToPx(), 1280.0);
}
}