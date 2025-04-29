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
struct TextClockHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('TextClock')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({
          buttonName: 'TextClockFormat',
          buttonUrl: 'pages/text_clock/TextClockFormatSample'
        });
        CommonButton({
          buttonName: 'TextClockFontFeature',
          buttonUrl: 'pages/text_clock/TextClockFontFeatureSample'
        });
        CommonButton({
          buttonName: 'TextClockTextShadowOptionsSample',
          buttonUrl: 'pages/text_clock/TextClockTextShadowOptionsSample'
        });
        CommonButton({
          buttonName: 'TextClockFontColor',
          buttonUrl: 'pages/text_clock/TextClockFontColorSample'
        });
        CommonButton({
          buttonName: 'TextClockFontSize',
          buttonUrl: 'pages/text_clock/TextClockFontSizeSample'
        });
        CommonButton({
          buttonName: 'TextClockFontStyle',
          buttonUrl: 'pages/text_clock/TextClockFontStyleSample'
        });
        CommonButton({
          buttonName: 'TextClockFontWeight_one',
          buttonUrl: 'pages/text_clock/TextClockFontWeightSample_one'
        });
        CommonButton({
          buttonName: 'TextClockFontWeight_two',
          buttonUrl: 'pages/text_clock/TextClockFontWeightSample_two'
        });
        CommonButton({
          buttonName: 'TextClockFontFamily',
          buttonUrl: 'pages/text_clock/TextClockFontFamilySample'
        });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}