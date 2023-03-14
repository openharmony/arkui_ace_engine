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
#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/animation/curves.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/properties/edge.h"
#include "core/components/search/search_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/search/search_layout_property.h"
#include "core/components_ng/pattern/search/search_layout_algorithm.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "frameworks/core/components_ng/base/ui_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEXTFIELD_INDEX = 0;
constexpr int32_t IMAGE_INDEX = 1;
constexpr int32_t CANCEL_IMAGE_INDEX = 2;
constexpr int32_t CANCEL_BUTTON_INDEX = 3;
constexpr int32_t BUTTON_INDEX = 4;
const std::string EMPTY_VALUE;
const std::string PLACEHOLDER = "DEFAULT PLACEHOLDER";
const std::string SEARCH_SVG = "resource:///ohos_search.svg";
}
  
class SearchModelTestNG : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void GetThemeInCreate(RefPtr<MockThemeManager> themeManager);
    void GetSearchTheme(RefPtr<MockThemeManager> themeManager);
    void GetIconTheme(RefPtr<MockThemeManager> themeManager);
};

void SearchModelTestNG::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SearchModelTestNG::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void SearchModelTestNG::SetUp() {}

void SearchModelTestNG::TearDown()
{
    ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void SearchModelTestNG::GetThemeInCreate(RefPtr<MockThemeManager> themeManager)
{
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<SearchTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<SearchTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<TextFieldTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<SearchTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<IconTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<SearchTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<SearchTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<SearchTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<TextFieldTheme>()));
}

void SearchModelTestNG::GetSearchTheme(RefPtr<MockThemeManager> themeManager)
{
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SearchTheme>()));
}

void SearchModelTestNG::GetIconTheme(RefPtr<MockThemeManager> themeManager)
{
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IconTheme>()));
}

/**
 * @tc.name: Measure001
 * @tc.desc: Measure and layout
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Measure001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    GetThemeInCreate(themeManager);
    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    GetSearchTheme(themeManager);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto searchPattern = AceType::DynamicCast<SearchPattern>(frameNode->GetPattern());
    ASSERT_NE(searchPattern, nullptr);
    auto searchLayoutAlgorithm = searchPattern->CreateLayoutAlgorithm();
    ASSERT_NE(searchLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(searchLayoutAlgorithm));

    // textField Wrapper
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    RefPtr<GeometryNode> textFieldNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> textFieldNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(textFieldFrameNode,
        textFieldNodeGeometryNode, textFieldFrameNode->GetLayoutProperty());
    ASSERT_NE(textFieldNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(textFieldNodeLayoutWrapper);

    // image Wrapper
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    ASSERT_NE(imageFrameNode, nullptr);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> imageNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> imageNodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(imageFrameNode, imageNodeGeometryNode, imageFrameNode->GetLayoutProperty());
    ASSERT_NE(imageNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(imageNodeLayoutWrapper);

    // cancelImage Wrapper
    auto cancelImageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    ASSERT_NE(cancelImageFrameNode, nullptr);
    auto cancelImageLayoutProperty = cancelImageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> cancelImageNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> cancelImageNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(cancelImageFrameNode,
        cancelImageNodeGeometryNode, cancelImageFrameNode->GetLayoutProperty());
    ASSERT_NE(cancelImageNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(cancelImageNodeLayoutWrapper);

    // cancelButton Wrapper
    auto cancelButtonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonFrameNode, nullptr);
    auto cancelButtonLayoutProperty = cancelButtonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> cancelButtonNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> cancelButtonNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(cancelButtonFrameNode,
        cancelButtonNodeGeometryNode, cancelButtonFrameNode->GetLayoutProperty());
    ASSERT_NE(cancelButtonNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(cancelButtonNodeLayoutWrapper);

    // button Wrapper
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> buttonNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> buttonNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(buttonFrameNode,
        buttonNodeGeometryNode, buttonFrameNode->GetLayoutProperty());
    ASSERT_NE(buttonNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(buttonNodeLayoutWrapper);

    LayoutConstraintF LayoutConstraintVaildSize;
    double textfieldHeight = 50;
    textFieldNodeGeometryNode->SetFrameSize(SizeF(100, textfieldHeight));
    searchModelInstance.SetSearchIconSize(Dimension(16, DimensionUnit::VP));
    double cancelButtonSize = 200;
    cancelButtonNodeGeometryNode->SetFrameSize(SizeF(100, cancelButtonSize));
    double searchButtonHeight = 300;
    buttonNodeGeometryNode->SetFrameSize(SizeF(100, searchButtonHeight));
    LayoutConstraintVaildSize.selfIdealSize.SetWidth(10000);

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_GE(geometryNode->GetFrameSize().Height(), textfieldHeight);

    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_GE(geometryNode->GetFrameSize().Height(), cancelButtonSize);

    searchModelInstance.SetSearchButton("SEARCH");
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_GE(geometryNode->GetFrameSize().Height(), searchButtonHeight);

    searchModelInstance.SetSearchButton("SEARCH");
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INVISIBLE);
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_GE(geometryNode->GetFrameSize().Height(), searchButtonHeight);

    searchModelInstance.SetSearchButton("");
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_LT(geometryNode->GetFrameSize().Height(), searchButtonHeight);
    EXPECT_GE(geometryNode->GetFrameSize().Height(), cancelButtonSize);

    double searchHeight = 100;
    LayoutConstraintVaildSize.selfIdealSize.SetHeight(searchHeight);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_GE(geometryNode->GetFrameSize().Height(), searchHeight);

    geometryNode->SetFrameSize(SizeF(10, 10));
    cancelButtonNodeGeometryNode->SetFrameSize(SizeF(40, 40));
    buttonNodeGeometryNode->SetFrameSize(SizeF(40, 40));
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(cancelButtonNodeGeometryNode->GetFrameSize().Height(), 40);
    EXPECT_EQ(buttonNodeGeometryNode->GetFrameSize().Height(), 40);

    LayoutConstraintVaildSize.selfIdealSize.SetSize(SizeF(1000000, 1000000));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    cancelButtonNodeGeometryNode->SetFrameSize(SizeF(100, 100));
    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(cancelButtonNodeGeometryNode->GetFrameSize().Height(), 100);
}

/**
 * @tc.name: Measure002
 * @tc.desc: Measure child is null
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Measure002, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::SEARCH_ETS_TAG, nodeId, AceType::MakeRefPtr<SearchPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto searchPattern = AceType::DynamicCast<SearchPattern>(frameNode->GetPattern());
    ASSERT_NE(searchPattern, nullptr);
    auto searchLayoutAlgorithm = searchPattern->CreateLayoutAlgorithm();
    ASSERT_NE(searchLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    searchLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    searchLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetTotalChildCount(), 0);
}

/**
 * @tc.name: Searcheventhub001
 * @tc.desc: Searcheventhub
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Searcheventhub001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ChangeAndSubmitEvent changeEvent = [this](const std::string str) {};
    searchModelInstance.SetOnChange(changeEvent);
    auto eventHub = frameNode->GetEventHub<SearchEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    eventHub->UpdateChangeEvent("");
    ASSERT_NE(eventHub->changeEvent_, nullptr);

    eventHub->changeEvent_ = nullptr;
    eventHub->UpdateChangeEvent("");
    ASSERT_EQ(eventHub->changeEvent_, nullptr);
}

/**
 * @tc.name: Pattern001
 * @tc.desc: ishover_ is false
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Pattern001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    MouseInfo info;
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    auto renderContext = buttonFrameNode->GetRenderContext();
    auto mouseStyle = MouseFormat::TEXT_CURSOR;
    pattern->isCancelButtonHover_ = true;
    pattern->isHover_ = false;
    pattern->UpdateChangeEvent("");
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(pattern->buttonSize_.Height(), 0);
    EXPECT_EQ(pattern->buttonSize_.Width(), 0);
    pattern->OnModifyDone();
    pattern->OnButtonTouchDown(0);
    pattern->OnButtonTouchUp(0);
    ASSERT_FALSE(pattern->isSearchButtonHover_);
    pattern->OnButtonTouchDown(3);
    pattern->OnButtonTouchUp(3);
    ASSERT_FALSE(pattern->isSearchButtonHover_);
    pattern->SetMouseStyle(mouseStyle);
    pattern->HandleHoverEvent(true);
    ASSERT_TRUE(pattern->isHover_);
    pattern->HandleHoverEvent(false);
    ASSERT_FALSE(pattern->isHover_);
    pattern->HandleMouseEvent(info);
    pattern->HandleButtonMouseEvent(true, 3);
    ASSERT_TRUE(pattern->isCancelButtonHover_);
    pattern->HandleButtonMouseEvent(true, 0);
    ASSERT_TRUE(pattern->isSearchButtonHover_);
    pattern->HandleButtonMouseEvent(false, 3);
    ASSERT_FALSE(pattern->isCancelButtonHover_);
    pattern->HandleButtonMouseEvent(false, 0);
    ASSERT_FALSE(pattern->isSearchButtonHover_);
}

/**
 * @tc.name: Pattern002
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Pattern002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    DirtySwapConfig config;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    // textField Wrapper
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFieldFrameNode, nullptr);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    RefPtr<GeometryNode> textFieldNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> textFieldNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(textFieldFrameNode,
        textFieldNodeGeometryNode, textFieldFrameNode->GetLayoutProperty());
    ASSERT_NE(textFieldNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(textFieldNodeLayoutWrapper);

    // image Wrapper
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    ASSERT_NE(imageFrameNode, nullptr);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> imageNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> imageNodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(imageFrameNode, imageNodeGeometryNode, imageFrameNode->GetLayoutProperty());
    ASSERT_NE(imageNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(imageNodeLayoutWrapper);

    // cancelImage Wrapper
    auto cancelImageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    ASSERT_NE(cancelImageFrameNode, nullptr);
    auto cancelImageLayoutProperty = cancelImageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> cancelImageNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> cancelImageNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(cancelImageFrameNode,
        cancelImageNodeGeometryNode, cancelImageFrameNode->GetLayoutProperty());
    ASSERT_NE(cancelImageNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(cancelImageNodeLayoutWrapper);

    // cancelButton Wrapper
    auto cancelButtonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonFrameNode, nullptr);
    auto cancelButtonLayoutProperty = cancelButtonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> cancelButtonNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> cancelButtonNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(cancelButtonFrameNode,
        cancelButtonNodeGeometryNode, cancelButtonFrameNode->GetLayoutProperty());
    ASSERT_NE(cancelButtonNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(cancelButtonNodeLayoutWrapper);

    // button Wrapper
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> buttonNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> buttonNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(buttonFrameNode,
        buttonNodeGeometryNode, buttonFrameNode->GetLayoutProperty());
    ASSERT_NE(buttonNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(buttonNodeLayoutWrapper);

    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(layoutWrapper->GetTotalChildCount(), 5);

    searchModelInstance.SetSearchButton("search");
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INVISIBLE);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INVISIBLE);
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(layoutWrapper->GetTotalChildCount(), 5);
}

/**
 * @tc.name: Pattern003
 * @tc.desc: UpdateChangeEvent and ToJsonValue while cancelbuttonstyle is different
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Pattern003, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    SearchModelNG searchModelInstance;
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    ASSERT_NE(pattern, nullptr);
    GetSearchTheme(themeManager);
    pattern->UpdateChangeEvent("search");
    pattern->ToJsonValue(json);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::CONSTANT);

    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INPUT);
    pattern->ToJsonValue(json);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INPUT);
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INVISIBLE);
    pattern->UpdateChangeEvent("");
    pattern->ToJsonValue(json);
    EXPECT_EQ(layoutProperty->GetCancelButtonStyle(), CancelButtonStyle::INVISIBLE);
}

/**
 * @tc.name: Pattern004
 * @tc.desc: HandleMouseEvent while mouse not in button
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Pattern004, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    pattern->isHover_ = true;
    MouseInfo info;
    const Offset offset1(-1000000.0, -1000000.0);
    info.SetLocalLocation(offset1);
    ASSERT_NE(pattern, nullptr);
    pattern->HandleMouseEvent(info);
}

/**
 * @tc.name: Pattern005
 * @tc.desc: InitTouchEvent TouchType = DOWN
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Pattern005, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    TouchTestResult result;
    pattern->InitTouchEvent();
    const Offset offset1(-1000000.0, -1000000.0);
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::DOWN);
    touchInfo1.SetLocalLocation(offset1);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    ASSERT_NE(pattern->touchListener_, nullptr);
    pattern->touchListener_->GetTouchEventCallback()(info);
}

/**
 * @tc.name: Pattern006
 * @tc.desc: InitTouchEvent TouchType = UP
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Pattern006, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    TouchTestResult result;
    pattern->InitTouchEvent();
    const Offset offset1(-1000000.0, -1000000.0);
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::UP);
    touchInfo1.SetLocalLocation(offset1);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    ASSERT_NE(pattern->touchListener_, nullptr);
    pattern->touchListener_->GetTouchEventCallback()(info);
}


/**
 * @tc.name: Pattern007
 * @tc.desc: InitButtonTouchEvent TouchType = DOWN
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Pattern007, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    TouchTestResult result;
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    pattern->InitButtonTouchEvent(touchEvent, BUTTON_INDEX);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto gesture = buttonFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    auto touchEventActuator = gesture->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto events = touchEventActuator->touchEvents_;
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    ASSERT_FALSE(events.size() == 0);
    for (auto event : events) {
        event->callback_(info);
    }
}

/**
 * @tc.name: Pattern008
 * @tc.desc: InitButtonTouchEvent TouchType = UP
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Pattern008, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    TouchTestResult result;
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    
    pattern->InitButtonTouchEvent(touchEvent, BUTTON_INDEX);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto gesture = buttonFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    auto touchEventActuator = gesture->touchEventActuator_;
    ASSERT_NE(touchEventActuator, nullptr);
    auto events = touchEventActuator->touchEvents_;
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::UP);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    ASSERT_FALSE(events.size() == 0);
    for (auto event : events) {
        event->callback_(info);
    }
}

/**
 * @tc.name: SetCaretWidth001
 * @tc.desc: Set caretwidth and CursorColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, SetCaretWidth001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textPaintProperty = textFrameNode->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(textPaintProperty, nullptr);
    searchModelInstance.SetCaretWidth(14.0_vp);
    searchModelInstance.SetCaretColor(Color::RED);
    ASSERT_TRUE(textPaintProperty->GetCursorWidth()->Value() == 14);
    ASSERT_TRUE(textPaintProperty->GetCursorColor() == Color::RED);
}

/**
 * @tc.name: SetSearchIconSize001
 * @tc.desc: Set search icon size
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, SetSearchIconSize001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    GetThemeInCreate(themeManager);

    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    GetSearchTheme(themeManager);
    auto searchLayoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    
    searchModelInstance.SetSearchIconSize(14.0_vp);
    EXPECT_EQ(searchLayoutProperty->GetSearchIconUDSize(), 14.0_vp);
}

/**
 * @tc.name: SetSearchIconColor001
 * @tc.desc: Set search icon color while search icon is svg
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, SetSearchIconColor001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
    searchModelInstance.SetSearchIconColor(Color::RED);
    ASSERT_TRUE(imageRenderProperty->GetSvgFillColor() == Color::RED);
}

/**
 * @tc.name: SetSearchIconColor002
 * @tc.desc: Set search icon color while search icon is not svg
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, SetSearchIconColor002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    GetIconTheme(themeManager);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetSearchSrcPath("/common/icon.png");
    searchModelInstance.SetSearchIconColor(Color::RED);
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "/common/icon.png");
}

/**
 * @tc.name: SetSearchSrcPath001
 * @tc.desc: Set search icon src path and src is empty
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, SetSearchSrcPath001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    GetIconTheme(themeManager);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetSearchSrcPath("");
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "resource:///ohos_test_image.svg");
}

/**
 * @tc.name: SetSearchSrcPath002
 * @tc.desc: Set search icon src path and src is not empty
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, SetSearchSrcPath002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    GetIconTheme(themeManager);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetSearchSrcPath("/common/icon.png");
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "/common/icon.png");
}

/**
 * @tc.name: SetRightIconSrcPath001
 * @tc.desc: Set search icon src path and src is empty
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, SetRightIconSrcPath001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    GetIconTheme(themeManager);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetRightIconSrcPath("");
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "resource:///ohos_test_image.svg");
}

/**
 * @tc.name: SetRightIconSrcPath002
 * @tc.desc: Set search icon src path and src is not empty
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, SetRightIconSrcPath002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    searchModelInstance.SetRightIconSrcPath("/common/icon.png");
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "/common/icon.png");
}

/**
 * @tc.name: SetCancelButtonStyle001
 * @tc.desc: Set cancel button style
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, SetCancelButtonStyle001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto searchLayoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty, nullptr);
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::CONSTANT);
    ASSERT_TRUE(searchLayoutProperty->GetCancelButtonStyle() == CancelButtonStyle::CONSTANT);
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INPUT);
    ASSERT_TRUE(searchLayoutProperty->GetCancelButtonStyle() == CancelButtonStyle::INPUT);
    searchModelInstance.SetCancelButtonStyle(CancelButtonStyle::INVISIBLE);
    ASSERT_TRUE(searchLayoutProperty->GetCancelButtonStyle() == CancelButtonStyle::INVISIBLE);
}

/**
 * @tc.name: SetCancelIconSize001
 * @tc.desc: Set cancel icon size/color/path
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, SetCancelIconSize001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    GetThemeInCreate(themeManager);

    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, SEARCH_SVG);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    GetSearchTheme(themeManager);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    auto searchLayoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    auto imageRenderProperty = imageFrameNode->GetPaintProperty<ImageRenderProperty>();
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();

    searchModelInstance.SetCancelIconSize(14.0_vp);
    ASSERT_TRUE(searchLayoutProperty->GetCancelButtonUDSize() == 14.0_vp);

    searchModelInstance.SetCancelIconColor(Color::RED);
    ASSERT_TRUE(imageRenderProperty->GetSvgFillColor() == Color::RED);
    searchModelInstance.SetRightIconSrcPath("/common/icon.png");
    ASSERT_STREQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc().c_str(), "/common/icon.png");
    searchModelInstance.SetCancelIconColor(Color::RED);
    ASSERT_TRUE(imageRenderProperty->GetSvgFillColor() == Color::RED);
}

/**
 * @tc.name: SetSearchButtonFontSize001
 * @tc.desc: Set search button font size and color
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, SetSearchButtonFontSize001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    searchModelInstance.SetSearchButtonFontSize(14.0_vp);
    ASSERT_TRUE(buttonLayoutProperty->GetFontSize() == 14.0_vp);
    searchModelInstance.SetSearchButtonFontColor(Color::RED);
    ASSERT_TRUE(buttonLayoutProperty->GetFontColor() == Color::RED);
}

/**
 * @tc.name: SetTextColor001
 * @tc.desc: Set text color
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, SetTextColor001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto textFieldChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    searchModelInstance.SetTextColor(Color::RED);
    ASSERT_TRUE(textFieldLayoutProperty->GetTextColor() == Color::RED);
}

/**
 * @tc.name: Create001
 * @tc.desc: Create
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Create001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    GetThemeInCreate(themeManager);

    searchModelInstance.Create(EMPTY_VALUE, PLACEHOLDER, EMPTY_VALUE);
    auto frameNode = AceType::DynamicCast<SearchNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    GetSearchTheme(themeManager);
    ASSERT_NE(frameNode, nullptr);
    searchModelInstance.CreateTextField(frameNode, PLACEHOLDER, EMPTY_VALUE, true);
    searchModelInstance.CreateImage(frameNode, SEARCH_SVG, true);
    searchModelInstance.CreateCancelImage(frameNode, true);
    searchModelInstance.CreateButton(frameNode, true);
    searchModelInstance.CreateCancelButton(frameNode, true);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(TEXTFIELD_INDEX));
    ASSERT_NE(textFrameNode, nullptr);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    ASSERT_NE(imageFrameNode, nullptr);
    auto cancelImageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    ASSERT_NE(cancelImageFrameNode, nullptr);
    auto cancelButtonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonFrameNode, nullptr);
    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_EQ(buttonFrameNode, nullptr);
}
} // namespace OHOS::Ace::NG
