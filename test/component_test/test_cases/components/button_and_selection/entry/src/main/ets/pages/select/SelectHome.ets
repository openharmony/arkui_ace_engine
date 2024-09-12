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
struct SelectHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('SelectHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({ buttonName: 'ArrowPosition', buttonUrl: 'pages/select/SelectArrowPositionSample' });
        CommonButton({ buttonName: 'Font', buttonUrl: 'pages/select/SelectFontSample' });
        CommonButton({ buttonName: 'FontColor', buttonUrl: 'pages/select/SelectFontColorSample' });
        CommonButton({ buttonName: 'MenuAlign', buttonUrl: 'pages/select/SelectMenuAlignSample' });
        CommonButton({
          buttonName: 'MenuBackgroundBlurStyle',
          buttonUrl: 'pages/select/SelectMenuBackgroundBlurStyleSample'
        });
        CommonButton({ buttonName: 'MenuBackgroundColor', buttonUrl: 'pages/select/SelectMenuBackgroundColorSample' });
        CommonButton({ buttonName: 'OptionBgColor', buttonUrl: 'pages/select/SelectOptionBgColorSample' });
        CommonButton({ buttonName: 'OptionFont', buttonUrl: 'pages/select/SelectOptionFontSample' });
        CommonButton({ buttonName: 'OptionFontColor', buttonUrl: 'pages/select/SelectOptionFontColorSample' });
        CommonButton({ buttonName: 'OptionHeight', buttonUrl: 'pages/select/SelectOptionHeightSample' });
        CommonButton({ buttonName: 'OptionWidth', buttonUrl: 'pages/select/SelectOptionWidthSample' });
        CommonButton({ buttonName: 'Selected', buttonUrl: 'pages/select/SelectSelectedSample' });
        CommonButton({
          buttonName: 'SelectedOptionBgColor',
          buttonUrl: 'pages/select/SelectSelectedOptionBgColorSample'
        });
        CommonButton({ buttonName: 'SelectedOptionFont', buttonUrl: 'pages/select/SelectSelectedOptionFontSample' });
        CommonButton({
          buttonName: 'SelectedOptionFontColor',
          buttonUrl: 'pages/select/SelectSelectedOptionFontColorSample'
        });
        CommonButton({ buttonName: 'Space', buttonUrl: 'pages/select/SelectSpaceSample' });
        CommonButton({ buttonName: 'Value', buttonUrl: 'pages/select/SelectValueSample' });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}