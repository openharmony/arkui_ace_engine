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

#include "text_input_base.h"

#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_udmf.h"
#include "core/common/task_executor_impl.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "core/components_ng/pattern/list/list_item_group_layout_property.h"

#include "core/text/text_emoji_processor.h"
#include "base/i18n/localization.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextFieldPatternTestNine : public TextInputBases {
public:
};

/**
 * @tc.name: TriggerAvoidOnCaretChange001
 * @tc.desc: test TriggerAvoidOnCaretChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, TriggerAvoidOnCaretChange001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    GestureEvent info;
    FingerInfo finfo;
    info.fingerList_.push_back(finfo);
    pattern_->magnifierController_ = AceType::MakeRefPtr<MagnifierController>(pattern_);
    pattern_->longPressFingerNum_ = 1;
    pattern_->contentController_ = AceType::MakeRefPtr<ContentController>(pattern_);
    std::u16string value = u"test";
    pattern_->contentController_->SetTextValue(value);
    pattern_->HandleLongPress(info);
    EXPECT_TRUE(pattern_->magnifierController_->magnifierNodeExist_);
}

/**
 * @tc.name: TriggerAvoidOnCaretChange002
 * @tc.desc: test TriggerAvoidOnCaretChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, TriggerAvoidOnCaretChange002, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    GestureEvent info;
    FingerInfo finfo;
    info.fingerList_.push_back(finfo);
    pattern_->magnifierController_ = AceType::MakeRefPtr<MagnifierController>(pattern_);
    pattern_->longPressFingerNum_ = 1;
    pattern_->contentController_ = AceType::MakeRefPtr<ContentController>(pattern_);
    std::u16string value = u"test";
    pattern_->contentController_->SetTextValue(value);
    auto host = pattern_->GetHost();
    auto pipeline = host->GetContext();
    pipeline->safeAreaManager_->keyboardInset_.start = 1;
    pipeline->safeAreaManager_->keyboardInset_.end = 2;
    pattern_->HandleLongPress(info);
    EXPECT_TRUE(pattern_->magnifierController_->magnifierNodeExist_);
}

/**
 * @tc.name: SetPreviewTextOperation001
 * @tc.desc: test SetPreviewTextOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, SetPreviewTextOperation001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto host = pattern_->GetHost();
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    auto func = [](const ChangeValueInfo& info) {
        return false;
    };
    eventHub->onWillChangeEvent_ = func;
    PreviewTextInfo info;
    info.text = u"test";
    info.isIme = false;
    pattern_->hasPreviewText_ = false;
    AceApplicationInfo::GetInstance().SetApiTargetVersion(20020);
    auto container = Container::Current();
    container->apiTargetVersion_ = 20;
    pattern_->selectController_->firstHandleInfo_.index = 1;
    pattern_->selectController_->secondHandleInfo_.index = 2;
    pattern_->contentController_->content_ = u"12";
    layoutProperty->UpdateMaxLength(1);
    pattern_->SetPreviewTextOperation(info);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN));

    info.isIme = true;
    pattern_->contentController_->content_ = u"";
    pattern_->SetPreviewTextOperation(info);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN));
}

/**
 * @tc.name: FinishTextPreviewOperation001
 * @tc.desc: test FinishTextPreviewOperation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, FinishTextPreviewOperation001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto host = pattern_->GetHost();
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    auto func = [](const ChangeValueInfo& info) {
        return false;
    };
    eventHub->onWillChangeEvent_ = func;
    pattern_->hasPreviewText_ = true;
    pattern_->FinishTextPreviewOperation();
    ChangeValueInfo changeValueInfo;
    EXPECT_FALSE(pattern_->FireOnWillChange(changeValueInfo));
}

/**
 * @tc.name: OnTextGestureSelectionUpdate001
 * @tc.desc: test OnTextGestureSelectionUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, OnTextGestureSelectionUpdate001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    int32_t start = 1;
    int32_t end = 2;
    TouchEventInfo info("unknown");
    pattern_->contentController_ = AceType::MakeRefPtr<ContentController>(pattern_);
    pattern_->contentController_->content_ = u"";
    pattern_->OnTextGestureSelectionUpdate(start, end, info);
    EXPECT_FALSE(pattern_->HasText());

    pattern_->contentController_->content_ = u"test";
    TouchLocationInfo tinfo("test", 0);
    Offset localLocation(1, 2);
    tinfo.SetLocalLocation(localLocation);
    info.touches_.push_back(tinfo);
    start = 26;
    pattern_->OnTextGestureSelectionUpdate(start, end, info);
    EXPECT_TRUE(pattern_->HasText());
}

/**
 * @tc.name: OnTextGenstureSelectionEnd001
 * @tc.desc: test OnTextGenstureSelectionEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, OnTextGenstureSelectionEnd001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    TouchLocationInfo locationInfo("test", 0);
    Offset offset(11, 22);
    locationInfo.localLocation_ = offset;
    pattern_->contentRect_.width_ = 33,
    pattern_->contentRect_.x_ = 33;
    pattern_->contentRect_.height_ = 44;
    pattern_->contentRect_.y_ = 44;
    pattern_->OnTextGenstureSelectionEnd(locationInfo);
    EXPECT_TRUE(LessNotEqual(locationInfo.localLocation_.GetX(), pattern_->contentRect_.Left()));

    pattern_->contentRect_.width_ = 1,
    pattern_->contentRect_.x_ = 1;
    pattern_->contentRect_.height_ = 2;
    pattern_->contentRect_.y_ = 2;
    pattern_->OnTextGenstureSelectionEnd(locationInfo);
    EXPECT_FALSE(LessNotEqual(locationInfo.localLocation_.GetX(), pattern_->contentRect_.Right()));
}

/**
 * @tc.name: IsShowAIWrite001
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, IsShowAIWrite001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto ret = pattern_->IsShowAIWrite();
    EXPECT_FALSE(ret);
    auto container = MockContainer::Current();
    container->SetIsScenceBoardWindow(false);
    auto host = pattern_->GetHost();
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateCopyOptions(CopyOptions::None);
    ret = pattern_->IsShowAIWrite();
    EXPECT_FALSE(ret);

    layoutProperty->UpdateCopyOptions(CopyOptions::Local);
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);
    auto textFieldTheme = pattern_->GetTheme();
    textFieldTheme->aiWriteBundleName_ = "BundleName";
    textFieldTheme->aiWriteAbilityName_ = "AbilityName";
    textFieldTheme->aiWriteIsSupport_ = "true";
    ret = pattern_->IsShowAIWrite();
    EXPECT_TRUE(ret);
    textFieldTheme->aiWriteIsSupport_ = "false";
    ret = pattern_->IsShowAIWrite();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleAIWriteResult001
 * @tc.desc: test HandleAIWriteResult
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternTestNine, HandleAIWriteResult001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    int32_t start =0;
    int32_t end = 0;
    std::vector<uint8_t> buffer;
    pattern_->HandleAIWriteResult(start, end, buffer);
    EXPECT_TRUE(buffer.empty());
}

/**
  * @tc.name: CalcAutoScrollStepOffset001
  * @tc.desc: test CalcAutoScrollStepOffset
  * @tc.type: FUNC
  */
HWTEST_F(TextFieldPatternTestNine, CalcAutoScrollStepOffset001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    Offset localOffset(1, 2);
    pattern_->axis_ = Axis::HORIZONTAL;
    pattern_->contentRect_.width_ = 10;
    pattern_->CalcAutoScrollStepOffset(localOffset);
    EXPECT_NE(pattern_->GetAxis(), Axis::VERTICAL);
}

/**
  * @tc.name: OnWillChangePreInsert001
  * @tc.desc: test OnWillChangePreInsert
  * @tc.type: FUNC
  */
HWTEST_F(TextFieldPatternTestNine, OnWillChangePreInsert001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    std::u16string insertValue = u"test";
    std::u16string oldContent = u"";
    uint32_t start = 1;
    uint32_t end = 2;
    pattern_->hasPreviewText_ = true;
    auto ret = pattern_->OnWillChangePreInsert(insertValue, oldContent, start, end);
    EXPECT_TRUE(ret);
}

/**
  * @tc.name: AddInsertCommand001
  * @tc.desc: test AddInsertCommand
  * @tc.type: FUNC
  */
HWTEST_F(TextFieldPatternTestNine, AddInsertCommand001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();
 
    std::u16string insertValue = u" ";
    InputReason reason = InputReason::NONE;
    pattern_->isEdit_ = true;
    pattern_->focusIndex_ = FocuseIndex::CANCEL;
    pattern_->AddInsertCommand(insertValue, reason);
    EXPECT_FALSE(pattern_->HandleSpaceEvent());
}

/**
  * @tc.name: ExecuteInputCommand001
  * @tc.desc: test ExecuteInputCommand
  * @tc.type: FUNC
  */
HWTEST_F(TextFieldPatternTestNine, ExecuteInputCommand001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    InputCommandInfo info;
    info.reason = InputReason::CANCEL_BUTTON;
    info.insertValue = u"test";
    info.deleteRange.end = 0;
    info.insertOffset = 0;
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdateMaxLength(123);
    auto host = pattern_->GetHost();
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    auto func = [](const ChangeValueInfo& info) {
        return false;
    };
    eventHub->onWillChangeEvent_ = func;
    pattern_->ExecuteInputCommand(info);
    ChangeValueInfo changeValueInfo;
    EXPECT_FALSE(pattern_->FireOnWillChange(changeValueInfo));
}

/**
  * @tc.name: ClearTextContent001
  * @tc.desc: test ClearTextContent
  * @tc.type: FUNC
  */
HWTEST_F(TextFieldPatternTestNine, ClearTextContent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->hasPreviewText_ = true;
    pattern_->ClearTextContent();
    EXPECT_TRUE(pattern_->GetIsPreviewText());
}

/**
  * @tc.name: GetOriginCaretPosition001
  * @tc.desc: test GetOriginCaretPosition
  * @tc.type: FUNC
  */
HWTEST_F(TextFieldPatternTestNine, GetOriginCaretPosition001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    OffsetF offset(0, 0);
    pattern_->originCaretPosition_ = offset;
    auto ret = pattern_->GetOriginCaretPosition(offset);
    EXPECT_TRUE(ret);
}

/**
  * @tc.name: GetFocusPattern001
  * @tc.desc: test GetFocusPattern
  * @tc.type: FUNC
  */
HWTEST_F(TextFieldPatternTestNine, GetFocusPattern001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    auto host = pattern_->GetHost();
    auto pipelineContext = host->GetContext();
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    theme->needFocusBox_ = true;
    pattern_->GetFocusPattern();
    EXPECT_TRUE(theme->NeedFocusBox());
}

/**
  * @tc.name: InitCancelButtonMouseEvent001
  * @tc.desc: test InitCancelButtonMouseEvent
  * @tc.type: FUNC
  */
HWTEST_F(TextFieldPatternTestNine, InitCancelButtonMouseEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();

    pattern_->cleanNodeResponseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(pattern_);
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(pattern_->cleanNodeResponseArea_);
    cleanNodeResponseArea->cleanNode_ = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    pattern_->InitCancelButtonMouseEvent();
    auto stackNode = cleanNodeResponseArea->GetFrameNode();
    auto imageInputHub = stackNode->GetOrCreateInputEventHub();
    imageInputHub->hoverEventActuator_->inputEvents_.front()->onHoverCallback_(true);
    EXPECT_TRUE(pattern_->isOnHover_);

    auto imageTouchHub = stackNode->GetOrCreateGestureEventHub();
    TouchEventInfo info("unknown");
    TouchLocationInfo tinfo("test", 0);
    tinfo.touchType_ = TouchType::DOWN;
    info.touches_.push_back(tinfo);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);

    TouchEventInfo info1("unknown");
    TouchLocationInfo tinfo1("test", 0);
    tinfo1.touchType_ = TouchType::UP;
    info1.touches_.push_back(tinfo1);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info1);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);

    TouchEventInfo info2("unknown");
    TouchLocationInfo tinfo2("test", 0);
    tinfo2.touchType_ = TouchType::CANCEL;
    info2.touches_.push_back(tinfo2);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info2);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);

    TouchEventInfo info3("unknown");
    TouchLocationInfo tinfo3("test", 0);
    tinfo3.touchType_ = TouchType::MOVE;
    info3.touches_.push_back(tinfo3);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info3);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);
}

/**
  * @tc.name: InitPasswordButtonMouseEvent001
  * @tc.desc: test InitPasswordButtonMouseEvent
  * @tc.type: FUNC
  */
HWTEST_F(TextFieldPatternTestNine, InitPasswordButtonMouseEvent001, TestSize.Level0)
{
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        model.SetType(TextInputType::VISIBLE_PASSWORD);
    });
    GetFocus();
    auto passwordResponseArea = AceType::DynamicCast<PasswordResponseArea>(pattern_->responseArea_);
    auto stackNode = passwordResponseArea->GetFrameNode();
    auto imageTouchHub = stackNode->GetOrCreateGestureEventHub();
    imageTouchHub->touchEventActuator_->touchEvents_.clear();
    pattern_->InitPasswordButtonMouseEvent();
    auto imageInputHub = stackNode->GetOrCreateInputEventHub();
    imageInputHub->hoverEventActuator_->inputEvents_.front()->onHoverCallback_(true);
    EXPECT_TRUE(pattern_->isOnHover_);

    TouchEventInfo info("unknown");
    TouchLocationInfo tinfo("test", 0);
    tinfo.touchType_ = TouchType::DOWN;
    info.touches_.push_back(tinfo);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);

    TouchEventInfo info1("unknown");
    TouchLocationInfo tinfo1("test", 0);
    tinfo1.touchType_ = TouchType::UP;
    info1.touches_.push_back(tinfo1);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info1);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);

    TouchEventInfo info2("unknown");
    TouchLocationInfo tinfo2("test", 0);
    tinfo2.touchType_ = TouchType::CANCEL;
    info2.touches_.push_back(tinfo2);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info2);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);

    TouchEventInfo info3("unknown");
    TouchLocationInfo tinfo3("test", 0);
    tinfo3.touchType_ = TouchType::MOVE;
    info3.touches_.push_back(tinfo3);
    imageTouchHub->touchEventActuator_->touchEvents_.front()->callback_(info3);
    EXPECT_NE(imageTouchHub->touchEventActuator_->touchEvents_.front(), nullptr);
}
} // namespace OHOS::Ace::NG,