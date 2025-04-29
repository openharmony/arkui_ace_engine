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

import { CommonButton } from '../util/CommonButton';

@Entry
@Component
struct Index {
  aboutToAppear() {
  }

  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('information_display')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({ buttonName: 'DataPanel', buttonUrl: 'pages/data_panel/DataPanelHome' });
        CommonButton({ buttonName: 'Gauge', buttonUrl: 'pages/gauge/GaugeHome' });
        CommonButton({ buttonName: 'LoadingProgress', buttonUrl: 'pages/loading_progress/LoadingProgressHome' });
        CommonButton({ buttonName: 'QRCode', buttonUrl: 'pages/qr_code/QRCodeHome' });
        CommonButton({ buttonName: 'TextClock', buttonUrl: 'pages/text_clock/TextClockHome' });
        CommonButton({ buttonName: 'TextTimer', buttonUrl: 'pages/text_timer/TextTimerHome' });
        CommonButton({ buttonName: 'Marquee', buttonUrl: 'pages/marquee/MarqueeHome' });
        CommonButton({ buttonName: 'Progress', buttonUrl: 'pages/progress/ProgressHome' });
      }
      .padding('20vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}