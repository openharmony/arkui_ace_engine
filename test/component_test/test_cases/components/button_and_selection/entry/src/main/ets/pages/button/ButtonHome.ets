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
struct ButtonHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('ButtonHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({ buttonName: 'Type', buttonUrl: 'pages/button/ButtonTypeSample' });
        CommonButton({ buttonName: 'FontColor', buttonUrl: 'pages/button/ButtonFontColorSample' });
        CommonButton({ buttonName: 'FontWeight', buttonUrl: 'pages/button/ButtonFontWeightSample' });
        CommonButton({ buttonName: 'FontStyle', buttonUrl: 'pages/button/ButtonFontStyleSample' });
        CommonButton({ buttonName: 'FontFamily', buttonUrl: 'pages/button/ButtonFontFamilySample' });
        CommonButton({ buttonName: 'FontSize', buttonUrl: 'pages/button/ButtonFontSizeSample' });
        CommonButton({ buttonName: 'StateEffect', buttonUrl: 'pages/button/ButtonStateEffectSample' });
        CommonButton({ buttonName: 'LabelStyle', buttonUrl: 'pages/button/ButtonLabelStyleSample' });
        CommonButton({ buttonName: 'ButtonStyle', buttonUrl: 'pages/button/ButtonButtonStyleSample' });
        CommonButton({ buttonName: 'ControlSize', buttonUrl: 'pages/button/ButtonControlSizeSample' });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}