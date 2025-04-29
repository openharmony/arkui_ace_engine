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
struct AlphabetIndexerHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('AlphabetIndexerHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({
          buttonName: 'AlphabetIndexerColor',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerColorSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerSelectedColor',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerSelectedColorSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerPopupColor',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerPopupColorSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerSelectedBackgroundColor',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerSelectedBackgroundColorSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerPopupBackground',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerPopupBackgroundSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerUsingPopup',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerUsingPopupSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerSelectedFont',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerSelectedFontSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerPopupFont',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerPopupFontSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerFont',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerFontSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerItemSize',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerItemSizeSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerAlignStyle',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerAlignStyleSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerSelected',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerSelectedSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerPopupPosition',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerPopupPositionSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerPopupSelectedColor',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerPopupSelectedColorSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerPopupUnselectedColor',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerPopupUnselectedColorSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerPopupItemFont',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerPopupItemFontSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerPopupItemBackgroundColor',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerPopupItemBackgroundColorSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerAutoCollapse',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerAutoCollapseSample'
        });
        CommonButton({
          buttonName: 'AlphabetIndexerAlphabetIndexerAttribute',
          buttonUrl: 'pages/alphabetindexer/AlphabetIndexerAlphabetIndexerAttributeSample'
        });
      }
      .padding('20vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}