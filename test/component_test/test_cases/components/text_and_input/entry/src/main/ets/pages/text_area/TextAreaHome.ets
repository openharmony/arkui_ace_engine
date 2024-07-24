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
struct TextAreaHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({
          buttonName: 'TextAreaPlaceholderColor',
          buttonUrl: 'pages/text_area/TextAreaPlaceholderColorSample'
        });
        CommonButton({ buttonName: 'TextAreaTextAlign', buttonUrl: 'pages/text_area/TextAreaTextAlignSample' });
        CommonButton({
          buttonName: 'TextAreaPlaceholderFont',
          buttonUrl: 'pages/text_area/TextAreaPlaceholderFontSample'
        });
        CommonButton({ buttonName: 'TextAreaCaretColor', buttonUrl: 'pages/text_area/TextAreaCaretColorSample' });
        CommonButton({ buttonName: 'TextAreaInputFilter', buttonUrl: 'pages/text_area/TextAreaInputFilterSample' });
        CommonButton({ buttonName: 'TextAreaCopyOption', buttonUrl: 'pages/text_area/TextAreaCopyOptionSample' });
        CommonButton({ buttonName: 'TextAreaMaxLength', buttonUrl: 'pages/text_area/TextAreaMaxLengthSample' });
        CommonButton({ buttonName: 'TextAreaShowCounter', buttonUrl: 'pages/text_area/TextAreaShowCounterSample' });
        CommonButton({ buttonName: 'TextAreaStyle', buttonUrl: 'pages/text_area/TextAreaStyleSample' });
        CommonButton({
          buttonName: 'TextAreaEnableKeyBoardOnFocus',
          buttonUrl: 'pages/text_area/TextAreaEnableKeyBoardOnFocusSample'
        });
        CommonButton({
          buttonName: 'TextAreaSelectionMenuHidden',
          buttonUrl: 'pages/text_area/TextAreaSelectionMenuHiddenSample'
        });
        CommonButton({ buttonName: 'TextAreaBarState', buttonUrl: 'pages/text_area/TextAreaBarStateSample' });
        CommonButton({ buttonName: 'TextAreaMaxLines', buttonUrl: 'pages/text_area/TextAreaMaxLinesSample' });
        CommonButton({
          buttonName: 'TextAreaCustomKeyboard',
          buttonUrl: 'pages/text_area/TextAreaCustomKeyboardSample'
        });
        CommonButton({ buttonName: 'TextAreaType', buttonUrl: 'pages/text_area/TextAreaTypeSample' });
        CommonButton({ buttonName: 'TextAreaEnterKeyType', buttonUrl: 'pages/text_area/TextAreaEnterKeyTypeSample' });
        CommonButton({ buttonName: 'TextAreaFontColor', buttonUrl: 'pages/text_area/TextAreaFontColorSample' });
        CommonButton({ buttonName: 'TextAreaFontSize', buttonUrl: 'pages/text_area/TextAreaFontSizeSample' });
        CommonButton({ buttonName: 'TextAreaFontStyle', buttonUrl: 'pages/text_area/TextAreaFontStyleSample' });
        CommonButton({ buttonName: 'TextAreaFontWeight', buttonUrl: 'pages/text_area/TextAreaFontWeightSample' });
        CommonButton({ buttonName: 'TextAreaFontFamily', buttonUrl: 'pages/text_area/TextAreaFontFamilySample' });

      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}