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

#include "text_input_base.h"

#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldPatternTestTwo : public TextInputBases {
public:
};

/**
 * @tc.name: InitDragDropCallBack001
 * @tc.desc: test testInput text InitDragDropCallBack
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, InitDragDropCallBack001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();

    pattern->InitDragDropCallBack();

    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string extraParams = "Test";

    auto eventHub = textFieldNode->GetEventHub<EventHub>();
    pattern->dragStatus_ = DragStatus::ON_DROP;
    pattern->isDetachFromMainTree_ = false;
    eventHub->onDragEnd_.operator()(event);
    pattern->dragStatus_ = DragStatus::ON_DROP;
    pattern->isDetachFromMainTree_ = true;
    eventHub->onDragEnd_.operator()(event);
    pattern->dragStatus_ = DragStatus::DRAGGING;
    pattern->isDetachFromMainTree_ = true;
    eventHub->onDragEnd_.operator()(event);
    pattern->dragStatus_ = DragStatus::DRAGGING;
    pattern->isDetachFromMainTree_ = false;
    eventHub->onDragEnd_.operator()(event);
    auto focusHub = pattern->GetFocusHub();
    focusHub->currentFocus_ = true;
    pattern->dragStatus_ = DragStatus::DRAGGING;
    eventHub->onDragEnd_.operator()(nullptr);
    event->SetResult(DragRet::DRAG_SUCCESS);
    pattern->dragStatus_ = DragStatus::DRAGGING;
    eventHub->onDragEnd_.operator()(event);
    event->SetResult(DragRet::DRAG_DEFAULT);
    pattern->dragValue_ = "Test";
    pattern->dragStatus_ = DragStatus::DRAGGING;
    eventHub->onDragEnd_.operator()(event);
    pattern->dragValue_= pattern->contentController_->GetSelectedValue(pattern->dragTextStart_, pattern->dragTextEnd_);
    pattern->dragStatus_ = DragStatus::DRAGGING;
    eventHub->onDragEnd_.operator()(event);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    pattern->dragStatus_ = DragStatus::DRAGGING;
    eventHub->onDragEnd_.operator()(event);
    paintProperty->UpdateInputStyle(InputStyle::DEFAULT);
    pattern->dragStatus_ = DragStatus::DRAGGING;
    eventHub->onDragEnd_.operator()(event);
    focusHub->currentFocus_ = false;
    pattern->dragStatus_ = DragStatus::DRAGGING;
    eventHub->onDragEnd_.operator()(event);
    eventHub->onDragEnter_.operator()(event, extraParams);
    pattern->dragStatus_ = DragStatus::ON_DROP;
    eventHub->onDragEnter_.operator()(event, extraParams);
    EXPECT_EQ(pattern->dragStatus_, DragStatus::NONE);
}

/**
 * @tc.name: HandleClickEvent001
 * @tc.desc: test testInput text HandleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, HandleClickEvent001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    GestureEvent info;

    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateMaxLines(0);
    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);

    pattern->obscureTickCountDown_ = 1;
    pattern->multipleClickRecognizer_->clickCountTask_.Reset([] {});
    pattern->HandleClickEvent(info);
    pattern->multipleClickRecognizer_->clickCountTask_.Reset([] {});
    pattern->HandleClickEvent(info);
    pattern->multipleClickRecognizer_->clickCountTask_.Reset([] {});
    pattern->HandleClickEvent(info);

    pattern->isFocusedBeforeClick_ = true;
    pattern->HandleClickEvent(info);
    EXPECT_EQ(pattern->isFocusedBeforeClick_, false);

    pattern->hasMousePressed_ = true;
    pattern->isFocusedBeforeClick_ = true;
    pattern->HandleClickEvent(info);
    EXPECT_EQ(pattern->isFocusedBeforeClick_, false);

    pattern->hasMousePressed_ = false;
    pattern->isFocusedBeforeClick_ = true;
    pattern->HandleClickEvent(info);
    EXPECT_EQ(pattern->isFocusedBeforeClick_, false);

    auto focusHub = pattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = false;
    focusHub->SetTabIndex(1);

    auto context = NG::PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    context->isFocusingByTab_ = true;
    pattern->isFocusedBeforeClick_ = true;
    pattern->HandleClickEvent(info);
    EXPECT_EQ(pattern->isFocusedBeforeClick_, true);

    focusHub->SetIsFocusOnTouch(false);
    pattern->isFocusedBeforeClick_ = true;
    pattern->HandleClickEvent(info);
    EXPECT_EQ(pattern->isFocusedBeforeClick_, true);
}

/**
 * @tc.name: HandleClickEvent002
 * @tc.desc: test testInput text HandleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, HandleClickEvent002, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    GestureEvent info;
    info.SetGlobalLocation(Offset(90, 90));

    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    auto holder = AceType::MakeRefPtr<SelectOverlayHolder>();
    ASSERT_NE(holder, nullptr);
    manager->selectOverlayHolder_ = holder;
    pattern->selectOverlay_->OnBind(manager);

    auto overlayManager = pattern->selectOverlay_->GetManager<SelectContentOverlayManager>();
    ASSERT_NE(overlayManager, nullptr);
    SelectOverlayInfo selectOverlayInfo;
    overlayManager->CreateHandleLevelSelectOverlay(selectOverlayInfo, false, HandleLevelMode::OVERLAY);
    auto handleNode = overlayManager->handleNode_.Upgrade();
    ASSERT_NE(handleNode, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(handleNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto geometryNode = selectOverlayNode->GetGeometryNode();
    geometryNode->frame_.rect_.SetRect(100, 100, 200, 200);

    pattern->multipleClickRecognizer_->clickCountTask_.impl_ = nullptr;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    auto oldThemeManager = PipelineBase::GetCurrentContext()->themeManager_;
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    ResValueWrapper handleOuterDiameter { .type = ThemeConstantsType::DIMENSION, .value = 100 };
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    themeStyle->SetAttr("handle_outer_diameter", handleOuterDiameter);
    ResValueWrapper resValueWrapper { .type = ThemeConstantsType::THEME, .value = themeStyle };
    std::unordered_map<std::string, ResValueWrapper> attributes;
    attributes.insert(std::pair<std::string, ResValueWrapper>(THEME_PATTERN_TEXT_OVERLAY, resValueWrapper));
    auto resourceAdapter = AceType::MakeRefPtr<MockResourceAdapterV2>();
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(resourceAdapter);
    themeConstants->currentThemeStyle_ = AceType::MakeRefPtr<ThemeStyle>();
    themeConstants->currentThemeStyle_->SetAttributes(attributes);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(TextOverlayTheme::Builder().Build(themeConstants)));

    auto selectOverlayPattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(selectOverlayPattern, nullptr);
    selectOverlayPattern->SetHandleReverse(false);

    pattern->isFocusedBeforeClick_ = true;
    pattern->HandleClickEvent(info);
    EXPECT_EQ(pattern->isFocusedBeforeClick_, true);

    PipelineBase::GetCurrentContext()->themeManager_ = oldThemeManager;
}

/**
 * @tc.name: HandleDoubleClickEvent001
 * @tc.desc: test testInput text HandleDoubleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, HandleDoubleClickEvent001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    GestureEvent info;
    info.SetGlobalLocation(Offset(10, 10));

    pattern->contentController_->content_ = "Test";
    pattern->contentRect_.SetRect(0, 0, 10, 10);

    pattern->showKeyBoardOnFocus_ = true;
    auto focusHub = pattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    pattern->customKeyboardBuilder_ = []() {};

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    auto oldThemeManager = PipelineBase::GetCurrentContext()->themeManager_;
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    auto resourceAdapter = AceType::MakeRefPtr<MockResourceAdapterV2>();
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(resourceAdapter);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(TextFieldTheme::Builder().Build(themeConstants)));

    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontSize(Dimension(10));

    pattern->isEdit_ = false;
    pattern->HandleDoubleClickEvent(info);
    EXPECT_EQ(pattern->isEdit_, true);

    PipelineBase::GetCurrentContext()->themeManager_ = oldThemeManager;
}

/**
 * @tc.name: HandleTripleClickEvent001
 * @tc.desc: test testInput text HandleTripleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, HandleTripleClickEvent001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    GestureEvent info;
    info.SetGlobalLocation(Offset(10, 10));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    auto oldThemeManager = PipelineBase::GetCurrentContext()->themeManager_;
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    auto resourceAdapter = AceType::MakeRefPtr<MockResourceAdapterV2>();
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(resourceAdapter);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(TextFieldTheme::Builder().Build(themeConstants)));

    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontSize(Dimension(10));

    ASSERT_NE(pattern->contentController_, nullptr);
    pattern->contentController_->content_ = "Test";
    ASSERT_NE(pattern->selectController_, nullptr);
    pattern->selectController_->UpdateHandleIndex(0, 4);

    pattern->selectOverlay_->SetIsSingleHandle(true);
    pattern->HandleTripleClickEvent(info);
    EXPECT_EQ(pattern->selectOverlay_->IsSingleHandle(), false);

    pattern->contentController_->content_ = "Test";
    pattern->contentRect_.SetRect(0, 0, 10, 10);

    pattern->HandleTripleClickEvent(info);
    EXPECT_EQ(pattern->selectOverlay_->IsSingleHandle(), true);

    PipelineBase::GetCurrentContext()->themeManager_ = oldThemeManager;
}

/**
 * @tc.name: ProcessNumberOfLines001
 * @tc.desc: test testInput text ProcessNumberOfLines
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, ProcessNumberOfLines001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateNumberOfLines(1024);

    pattern->ProcessNumberOfLines();

    MeasureProperty constraint;
    layoutProperty->UpdateCalcLayoutProperty(constraint);

    pattern->ProcessNumberOfLines();

    layoutProperty->UpdateLineHeight(Dimension(10));
    constraint.selfIdealSize = CalcSize(CalcLength(10), CalcLength(10));
    layoutProperty->UpdateCalcLayoutProperty(constraint);

    pattern->ProcessNumberOfLines();
    EXPECT_EQ(layoutProperty->GetCalcLayoutConstraint()->selfIdealSize->Width(), CalcLength(10));
}
} // namespace OHOS::Ace::NG