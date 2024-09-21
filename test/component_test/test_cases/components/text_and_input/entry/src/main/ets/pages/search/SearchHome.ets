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
struct SearchHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({ buttonName: 'SearchSearchButton', buttonUrl: 'pages/search/SearchSearchButtonSample' });
        CommonButton({ buttonName: 'SearchPlaceholderColor', buttonUrl: 'pages/search/SearchPlaceholderColorSample' });
        CommonButton({ buttonName: 'SearchPlaceholderFont', buttonUrl: 'pages/search/SearchPlaceholderFontSample' });
        CommonButton({ buttonName: 'SearchTextFont', buttonUrl: 'pages/search/SearchTextFontSample' });
        CommonButton({ buttonName: 'SearchTextAlign', buttonUrl: 'pages/search/SearchTextAlignSample' });
        CommonButton({ buttonName: 'SearchCopyOption', buttonUrl: 'pages/search/SearchCopyOptionSample' });
        CommonButton({ buttonName: 'SearchSearchIcon', buttonUrl: 'pages/search/SearchSearchIconSample' });
        CommonButton({ buttonName: 'SearchCancelButton', buttonUrl: 'pages/search/SearchCancelButtonSample' });
        CommonButton({ buttonName: 'SearchFontColor', buttonUrl: 'pages/search/SearchFontColorSample' });
        CommonButton({ buttonName: 'SearchCaretStyle', buttonUrl: 'pages/search/SearchCaretStyleSample' });
        CommonButton({
          buttonName: 'SearchEnableKeyboardOnFocus',
          buttonUrl: 'pages/search/SearchEnableKeyboardOnFocusSample'
        });
        CommonButton({
          buttonName: 'SearchSelectionMenuHidden',
          buttonUrl: 'pages/search/SearchSelectionMenuHiddenSample'
        });
        CommonButton({ buttonName: 'SearchCustomKeyboard', buttonUrl: 'pages/search/SearchCustomKeyboardSample' });
        CommonButton({ buttonName: 'SearchType', buttonUrl: 'pages/search/SearchTypeSample' });
        CommonButton({ buttonName: 'SearchMaxLength', buttonUrl: 'pages/search/SearchMaxLengthSample' });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}