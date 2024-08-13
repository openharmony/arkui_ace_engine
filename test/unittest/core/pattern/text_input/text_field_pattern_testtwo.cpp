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
#include "test/mock/core/common/mock_udmf.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldPatternTestTwo : public TextInputBases {
public:
};

class TextFieldPatternTestTwoViewDataWrap : public ViewDataWrap {
public:
    const std::string& GetBundleName() const
    {
        return str;
    }
    const std::string& GetModuleName() const
    {
        return str;
    }
    const std::string& GetAbilityName() const
    {
        return str;
    }
    const std::string& GetPageUrl() const
    {
        return str;
    }
    const std::vector<RefPtr<PageNodeInfoWrap>>& GetPageNodeInfoWraps()
    {
        return vct;
    }
    const NG::RectF& GetPageRect() const
    {
        return rect;
    }
    bool GetUserSelected() const
    {
        return true;
    }
    void SetOtherAccount(bool isOtherAccount)
    {
        isOtherAccount_ = isOtherAccount;
    }
    bool GetOtherAccount() const
    {
        return isOtherAccount_;
    }

protected:
    std::string str;
    std::vector<RefPtr<PageNodeInfoWrap>> vct;
    NG::RectF rect;
    bool isOtherAccount_ = false;
};

class TextFieldPatternTestTwoPageNodeInfoWrap : public PageNodeInfoWrap {
public:
    const std::string& GetTag() const
    {
        return str;
    }
    void SetValue(const std::string& value)
    {
        value_ = value;
    }
    const std::string& GetValue() const
    {
        return value_;
    }
    const std::string& GetPlaceholder() const
    {
        return str;
    }
    const std::string& GetMetadata() const
    {
        return str;
    }
    const std::string& GetPasswordRules() const
    {
        return str;
    }
    void SetIsFocus(bool isFocus)
    {
        isFocus_ = isFocus;
    }
    bool GetIsFocus() const
    {
        return isFocus_;
    }
    const NG::RectF& GetPageNodeRect() const
    {
        return rect;
    }

protected:
    std::string str;
    NG::RectF rect;
    bool isFocus_ = false;
    std::string value_;
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

/**
 * @tc.name: HandleCountStyle001
 * @tc.desc: test testInput text HandleCountStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, HandleCountStyle001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateShowCounter(true);
    layoutProperty->UpdateMaxLength(1024);
    layoutProperty->UpdateShowUnderline(true);

    pattern->deleteForwardOperations_.emplace(10);
    pattern->deleteBackwardOperations_.emplace(10);
    pattern->HandleCountStyle();
    pattern->deleteForwardOperations_.pop();
    pattern->deleteBackwardOperations_.pop();

    pattern->HandleCountStyle();

    layoutProperty->UpdateSetCounter(0);
    pattern->HandleCountStyle();

    layoutProperty->UpdateShowHighlightBorder(false);
    pattern->HandleCountStyle();

    layoutProperty->UpdateSetCounter(1);
    pattern->HandleCountStyle();

    pattern->showCountBorderStyle_ = true;
    layoutProperty->UpdateShowHighlightBorder(true);
    pattern->HandleCountStyle();

    EXPECT_EQ(pattern->underlineWidth_, 2.0_px);
}

/**
 * @tc.name: ProcessUnderlineColorOnModifierDone001
 * @tc.desc: test testInput text ProcessUnderlineColorOnModifierDone
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, ProcessUnderlineColorOnModifierDone001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateShowUnderline(true);
    pattern->showCountBorderStyle_ = true;
    pattern->ProcessUnderlineColorOnModifierDone();

    auto focusHub = pattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    pattern->ProcessUnderlineColorOnModifierDone();

    layoutProperty->UpdateSetCounter(1);
    pattern->ProcessUnderlineColorOnModifierDone();

    layoutProperty->UpdateShowHighlightBorder(false);
    pattern->ProcessUnderlineColorOnModifierDone();

    layoutProperty->UpdateSetCounter(0);
    pattern->ProcessUnderlineColorOnModifierDone();

    EXPECT_EQ(pattern->GetUnderlineColor(), pattern->GetTheme()->GetErrorUnderlineColor());
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: test testInput text OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, OnModifyDone001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto focusHub = pattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    pattern->contentController_->content_ = "Test";
    pattern->selectController_->UpdateHandleIndex(0, 4);

    pattern->OnModifyDone();

    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    pattern->selectOverlay_->OnBind(manager);

    SelectOverlayInfo info;
    manager->CreateNormalSelectOverlay(info, false);

    pattern->OnModifyDone();

    pattern->isTextChangedAtCreation_ = true;
    pattern->OnModifyDone();

    pattern->isTextChangedAtCreation_ = true;
    pattern->contentController_->content_ = "";
    pattern->selectController_->UpdateHandleIndex(0, 0);
    pattern->OnModifyDone();

    pattern->deleteForwardOperations_.emplace(10);
    pattern->OnModifyDone();

    auto eventHub = textFieldNode->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);
    pattern->OnModifyDone();

    pattern->barState_ = DisplayMode::ON;

    pattern->OnModifyDone();

    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateInputStyle(InputStyle::INLINE);

    pattern->isModifyDone_ = false;
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->isModifyDone_, true);
}

/**
 * @tc.name: FireOnTextChangeEvent001
 * @tc.desc: test testInput text FireOnTextChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, FireOnTextChangeEvent001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto context = textFieldNode->GetContextRefPtr();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>(false);
    ASSERT_NE(context->taskExecutor_, nullptr);

    pattern->contentController_->content_ = "Test";
    pattern->selectController_->UpdateHandleIndex(0, 4);

    EXPECT_EQ(pattern->FireOnTextChangeEvent(), true);

    auto focusHub = pattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    pattern->contentController_->content_ = "";
    pattern->selectController_->UpdateHandleIndex(0, 0);
    EXPECT_EQ(pattern->FireOnTextChangeEvent(), true);
}

/**
 * @tc.name: OnDragDrop001
 * @tc.desc: test testInput text OnDragDrop
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, OnDragDrop001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    auto focusHub = pattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    auto func = pattern->OnDragDrop();
    ASSERT_NE(func, nullptr);

    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    std::string extraParams = "Test";

    auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    std::vector<uint8_t> arr;
    auto spanString = AceType::MakeRefPtr<SpanString>("Test");
    spanString->EncodeTlv(arr);
    UdmfClient::GetInstance()->AddSpanStringRecord(unifiedData, arr);
    event->SetData(unifiedData);

    func(event, extraParams);

    EXPECT_EQ(pattern->dragRecipientStatus_, DragStatus::NONE);
}

/**
 * @tc.name: ProcBorderAndUnderlineInBlurEvent001
 * @tc.desc: test testInput text ProcBorderAndUnderlineInBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, ProcBorderAndUnderlineInBlurEvent001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->showCountBorderStyle_ = true;
    pattern->ProcBorderAndUnderlineInBlurEvent();

    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    layoutProperty->UpdateShowErrorText(true);
    layoutProperty->UpdateErrorText("ERROR");

    pattern->ProcBorderAndUnderlineInBlurEvent();

    layoutProperty->UpdateTextInputType(TextInputType::VISIBLE_PASSWORD);
    pattern->ProcBorderAndUnderlineInBlurEvent();

    layoutProperty->UpdateShowUnderline(true);
    pattern->ProcBorderAndUnderlineInBlurEvent();

    pattern->showCountBorderStyle_ = true;
    pattern->ProcBorderAndUnderlineInBlurEvent();
    EXPECT_EQ(pattern->showCountBorderStyle_, false);
}

/**
 * @tc.name: NotifyFillRequestSuccess001
 * @tc.desc: test testInput text NotifyFillRequestSuccess
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, NotifyFillRequestSuccess001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /* Create custom ViewDataWrap and PageNodeInfoWrap objects */
    auto viewDataWrap = AceType::MakeRefPtr<TextFieldPatternTestTwoViewDataWrap>();
    ASSERT_NE(viewDataWrap, nullptr);
    auto nodeWrap = AceType::MakeRefPtr<TextFieldPatternTestTwoPageNodeInfoWrap>();
    ASSERT_NE(nodeWrap, nullptr);

    pattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, AceAutoFillType::ACE_UNSPECIFIED);

    nodeWrap->SetValue("Test");
    pattern->lastAutoFillTextValue_ = "";
    pattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, AceAutoFillType::ACE_UNSPECIFIED);
    EXPECT_EQ(pattern->lastAutoFillTextValue_, "Test");

    /* Simulate contentControl_ as nullptr */
    auto contentController = pattern->contentController_;
    pattern->contentController_ = nullptr;
    pattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, AceAutoFillType::ACE_UNSPECIFIED);
    pattern->contentController_ = contentController;

    nodeWrap->SetIsFocus(true);
    pattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, AceAutoFillType::ACE_UNSPECIFIED);

    /* Give the pattern focus */
    auto focusHub = pattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    pattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, AceAutoFillType::ACE_NEW_PASSWORD);

    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTextContentType(TextContentType::NEW_PASSWORD);
    pattern->lastAutoFillTextValue_ = "";
    pattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, AceAutoFillType::ACE_NEW_PASSWORD);
    EXPECT_NE(pattern->lastAutoFillTextValue_, "Test");

    viewDataWrap->SetOtherAccount(true);
    pattern->lastAutoFillTextValue_ = "";
    pattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, AceAutoFillType::ACE_NEW_PASSWORD);
    EXPECT_NE(pattern->lastAutoFillTextValue_, "Test");
}

/**
 * @tc.name: ParseFillContentJsonValue001
 * @tc.desc: test testInput text ParseFillContentJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, ParseFillContentJsonValue001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /* Construct JSON object */
    auto jsonObject = JsonUtil::Create(true);
    auto childJsonObject = JsonUtil::Create(true);
    std::unordered_map<std::string, std::variant<std::string, bool, int32_t>> map;

    childJsonObject->Put("name", "textfieldtest");
    jsonObject->Put("child0", childJsonObject);
    jsonObject->Put("child1", "child1");
    jsonObject->Put("child2", "child2");
    jsonObject->Put("child3", "child3");
    jsonObject->Put("child4", "child4");
    jsonObject->Put("child5", "child5");
    jsonObject->Put("child6", "child6");
    jsonObject->Put("child7", "child7");

    EXPECT_EQ(pattern->ParseFillContentJsonValue(jsonObject, map), true);
    EXPECT_EQ(pattern->ParseFillContentJsonValue(jsonObject->GetChild()->GetNext(), map), false);

    /* Construct an array JSON object */
    auto arrayJsonObject = JsonUtil::CreateArray(true);
    arrayJsonObject->Put("name", "textfieldtest");

    EXPECT_EQ(pattern->ParseFillContentJsonValue(arrayJsonObject, map), false);
}

/**
 * @tc.name: GetDragUpperLeftCoordinates001
 * @tc.desc: test testInput text GetDragUpperLeftCoordinates
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestTwo, GetDragUpperLeftCoordinates001, TestSize.Level0)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    /* Set the value of contentRect_ */
    pattern->contentRect_.SetRect(100, 100, 100, 100);

    /* Make the IsSelected function return true */
    pattern->contentController_->content_ = "Test";
    pattern->selectController_->UpdateHandleIndex(0, 4);

    /* Create a paragraph and mock to return two rectangles with the same starting point */
    auto paragraph0 = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects0 { RectF(0, 0, 10, 10), RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph0, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects0));
    pattern->selectController_->paragraph_ = paragraph0;

    EXPECT_EQ(pattern->GetDragUpperLeftCoordinates(), OffsetF(100, 100));

    /* Make the IsTextArea function return false */
    auto layoutProperty = textFieldNode->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateMaxLines(1);

    EXPECT_EQ(pattern->GetDragUpperLeftCoordinates(), OffsetF(100, 100));

    /* Create a paragraph, mock and return two rectangles with different starting points */
    auto paragraph1 = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects1 { RectF(0, 0, 10, 10), RectF(10, 10, 20, 20) };
    EXPECT_CALL(*paragraph1, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects1));
    pattern->selectController_->paragraph_ = paragraph1;

    EXPECT_EQ(pattern->GetDragUpperLeftCoordinates(), OffsetF(100, 100));

    /* Make the IsTextArea function return true */
    layoutProperty->UpdateMaxLines(1024);

    EXPECT_EQ(pattern->GetDragUpperLeftCoordinates(), OffsetF(100, 100));
}
} // namespace OHOS::Ace::NG