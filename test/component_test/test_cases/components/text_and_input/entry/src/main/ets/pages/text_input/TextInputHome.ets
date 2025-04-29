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

import { CommonButton } from '../../util/CommonButton';

@Entry
@Component
struct TextInputHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({ buttonName: 'TextInputType', buttonUrl: 'pages/text_input/TextInputTypeSample' });
        CommonButton({
          buttonName: 'TextInputPlaceholderColor',
          buttonUrl: 'pages/text_input/TextInputPlaceholderColorSample'
        });
        CommonButton({
          buttonName: 'TextInputPlaceholderFont',
          buttonUrl: 'pages/text_input/TextInputPlaceholderFontSample'
        });
        CommonButton({
          buttonName: 'TextInputEnterKeyType',
          buttonUrl: 'pages/text_input/TextInputEnterKeyTypeSample'
        });
        CommonButton({ buttonName: 'TextInputCaretColor', buttonUrl: 'pages/text_input/TextInputCaretColorSample' });
        CommonButton({ buttonName: 'TextInputMaxLength', buttonUrl: 'pages/text_input/TextInputMaxLengthSample' });
        CommonButton({ buttonName: 'TextInputInputFilter', buttonUrl: 'pages/text_input/TextInputInputFilterSample' });
        CommonButton({ buttonName: 'TextInputCopyOption', buttonUrl: 'pages/text_input/TextInputCopyOptionSample' });
        CommonButton({
          buttonName: 'TextInputShowPasswordIcon',
          buttonUrl: 'pages/text_input/TextInputShowPasswordIconSample'
        });
        CommonButton({ buttonName: 'TextInputStyle', buttonUrl: 'pages/text_input/TextInputStyleSample' });
        CommonButton({ buttonName: 'TextInputTextAlign', buttonUrl: 'pages/text_input/TextInputTextAlignSample' });
        CommonButton({
          buttonName: 'TextInputSelectedBackgroundColor',
          buttonUrl: 'pages/text_input/TextInputSelectedBackgroundColorSample'
        });
        CommonButton({ buttonName: 'TextInputCaretStyle', buttonUrl: 'pages/text_input/TextInputCaretStyleSample' });
        CommonButton({
          buttonName: 'TextInputCaretPosition',
          buttonUrl: 'pages/text_input/TextInputCaretPositionSample'
        });
        CommonButton({ buttonName: 'TextInputShowError', buttonUrl: 'pages/text_input/TextInputShowErrorSample' });
        CommonButton({
          buttonName: 'TextInputShowUnderline',
          buttonUrl: 'pages/text_input/TextInputShowUnderlineSample'
        });
        CommonButton({ buttonName: 'TextInputShowUnit', buttonUrl: 'pages/text_input/TextInputShowUnitSample' });
        CommonButton({
          buttonName: 'TextInputPasswordIcon',
          buttonUrl: 'pages/text_input/TextInputPasswordIconSample'
        });
        CommonButton({
          buttonName: 'TextInputEnableKeyboardOnFocus',
          buttonUrl: 'pages/text_input/TextInputEnableKeyboardOnFocusSample'
        });
        CommonButton({
          buttonName: 'TextInputSelectionMenuHidden',
          buttonUrl: 'pages/text_input/TextInputSelectionMenuHiddenSample'
        });
        CommonButton({ buttonName: 'TextInputBarState', buttonUrl: 'pages/text_input/TextInputBarStateSample' });
        CommonButton({ buttonName: 'TextInputMaxLines', buttonUrl: 'pages/text_input/TextInputMaxLinesSample' });
        CommonButton({
          buttonName: 'TextInputCustomKeyboard',
          buttonUrl: 'pages/text_input/TextInputCustomKeyboardSample'
        });
        CommonButton({
          buttonName: 'TextInputEnableAutoFill',
          buttonUrl: 'pages/text_input/TextInputEnableAutoFillSample'
        });
        CommonButton({
          buttonName: 'TextInputPasswordRules',
          buttonUrl: 'pages/text_input/TextInputPasswordRulesSample'
        });
        CommonButton({
          buttonName: 'TextInputCancelButton',
          buttonUrl: 'pages/text_input/TextInputCancelButtonSample'
        });
        CommonButton({ buttonName: 'TextInputSelectAll', buttonUrl: 'pages/text_input/TextInputSelectAllSample' });
        CommonButton({ buttonName: 'TextInputFontColor', buttonUrl: 'pages/text_input/TextInputFontColorSample' });
        CommonButton({ buttonName: 'TextInputFontSize', buttonUrl: 'pages/text_input/TextInputFontSizeSample' });
        CommonButton({ buttonName: 'TextInputFontStyle', buttonUrl: 'pages/text_input/TextInputFontStyleSample' });
        CommonButton({ buttonName: 'TextInputFontWeight', buttonUrl: 'pages/text_input/TextInputFontWeightSample' });
        CommonButton({ buttonName: 'TextInputFontFamily', buttonUrl: 'pages/text_input/TextInputFontFamilySample' });
        CommonButton({ buttonName: 'TextInputShowCounter', buttonUrl: 'pages/text_input/TextInputShowCounterSample' });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}