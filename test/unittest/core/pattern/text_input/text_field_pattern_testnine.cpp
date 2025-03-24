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
  * @tc.name: IsResponseRegionExpandingNeededForStylust001
  * @tc.desc: test IsResponseRegionExpandingNeededForStylus
  * @tc.type: FUNC
  */
 HWTEST_F(TextFieldPatternTestNine, IsResponseRegionExpandingNeededForStylust001, TestSize.Level0)
 {
     CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
         model.SetType(TextInputType::VISIBLE_PASSWORD);
     });
     GetFocus();
 
     TouchEvent touchEvent;
     auto host = pattern_->GetHost();
     auto focusHub = host->GetFocusHub();
     touchEvent.sourceTool = SourceTool::PEN;
     touchEvent.type = TouchType::DOWN;
     focusHub->focusType_ = FocusType::DISABLE;
     auto ret = pattern_->IsResponseRegionExpandingNeededForStylus(touchEvent);
     EXPECT_FALSE(ret);
 
     focusHub->focusType_ = FocusType::NODE;
     focusHub->focusable_ = true;
     focusHub->parentFocusable_ = true;
     auto renderContext = host->GetRenderContext();
     renderContext->UpdateOpacity(0);
     ret = pattern_->IsResponseRegionExpandingNeededForStylus(touchEvent);
     EXPECT_FALSE(ret);
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
 } // namespace OHOS::Ace::NG,