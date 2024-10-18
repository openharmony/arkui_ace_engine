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
struct TextTimerHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('TextTimerHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({
          buttonName: 'TextTimerFormat',
          buttonUrl: 'pages/text_timer/TextTimerFormatSample'
        });
        CommonButton({
          buttonName: 'TextTimerFontFamily',
          buttonUrl: 'pages/text_timer/TextTimerFontFamilySample'
        });
        CommonButton({
          buttonName: 'TextTimerFontSize',
          buttonUrl: 'pages/text_timer/TextTimerFontSizeSample'
        });
        CommonButton({
          buttonName: 'TextTimerFontStyle',
          buttonUrl: 'pages/text_timer/TextTimerFontStyleSample'
        });
        CommonButton({
          buttonName: 'TextTimerFontColor',
          buttonUrl: 'pages/text_timer/TextTimerFontColorSample'
        });
        CommonButton({
          buttonName: 'TextTimerFontWeight_one',
          buttonUrl: 'pages/text_timer/TextTimerFontWeightSample_one'
        });
        CommonButton({
          buttonName: 'TextTimerFontWeight_two',
          buttonUrl: 'pages/text_timer/TextTimerFontWeightSample_two'
        });
        CommonButton({ buttonName: 'TextTimerTextShadow', buttonUrl: 'pages/text_timer/TextTimerTextShadowSample' });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}