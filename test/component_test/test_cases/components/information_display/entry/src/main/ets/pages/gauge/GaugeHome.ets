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
struct GaugeHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('Gauge')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({ buttonName: 'GaugeValue', buttonUrl: 'pages/gauge/GaugeValueSample' });
        CommonButton({ buttonName: 'GaugeStartAngle', buttonUrl: 'pages/gauge/GaugeStartAngleSample' });
        CommonButton({ buttonName: 'GaugeEndAngle', buttonUrl: 'pages/gauge/GaugeEndAngleSample' });
        CommonButton({ buttonName: 'GaugeColors_one', buttonUrl: 'pages/gauge/GaugeColorsSample_one' });
        CommonButton({ buttonName: 'GaugeColors_two', buttonUrl: 'pages/gauge/GaugeColorsSample_two' });
        CommonButton({ buttonName: 'GaugeColors_three', buttonUrl: 'pages/gauge/GaugeColorsSample_three' });
        CommonButton({ buttonName: 'GaugeStrokeWidth', buttonUrl: 'pages/gauge/GaugeStrokeWidthSample' });
        CommonButton({ buttonName: 'GaugeDescription', buttonUrl: 'pages/gauge/GaugeDescriptionSample' });
        CommonButton({ buttonName: 'GaugeTrackShadow', buttonUrl: 'pages/gauge/GaugeTrackShadowSample' });
        CommonButton({ buttonName: 'GaugeIndicator', buttonUrl: 'pages/gauge/GaugeIndicatorSample' });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}