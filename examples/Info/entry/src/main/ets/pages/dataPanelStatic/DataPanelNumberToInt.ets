/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
'use static'

import {
  Text,
  TextAttribute,
  Column,
  Component,
  Button,
  ButtonAttribute,
  ClickEvent,
  Color,
  ImageSpan,
  TextAlign,
  Entry,
  AttributeModifier,
  Image,
  ImageAttribute,
  Progress,
  ProgressAttribute,
  PatternLock,
  LoadingProgress,
  TextClock,
  TextTimer,
  Counter,
  QRCode,
  DataPanel,
  Gauge,
  ProgressType,
  CapsuleStyleOptions,
  ResourceColor,
  Scroll,
  VoidCallback,
  DataPanelShadowOptions,
  $r
} from '@ohos.arkui.component' // TextAttribute should be insert by ui-plugins
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'
import { LengthMetrics } from "arkui.Graphics";

import {
  AttributeUpdater,
  CommonModifier,
  ButtonModifier,
  TextModifier,
  ImageModifier,
  ProgressModifier,
  PatternLockModifier,
  LoadingProgressModifier,
  TextClockModifier,
  CounterModifier,
  TextTimerModifier,
  QRCodeModifier,
  DataPanelModifier,
  GaugeModifier
} from '@ohos.arkui.modifier'

@Entry
@Component
struct MyStateSample {
  testDataPanelModifier: DataPanelModifier = new DataPanelModifier()
    .width(200)
    .height(200)
    .closeEffect(true)
  testDataPanelModifier2: DataPanelModifier = new DataPanelModifier()
    .width(200)
    .height(200)
    .valueColors([Color.Red, Color.Blue, Color.Green])
  testDataPanelModifier3: DataPanelModifier = new DataPanelModifier()
    .width(200)
    .height(200)
    .trackBackgroundColor("#88FFFF00")
  testDataPanelModifier4: DataPanelModifier = new DataPanelModifier()
    .width(200)
    .height(200)
    .strokeWidth(15)
  testDataPanelModifier5: DataPanelModifier = new DataPanelModifier()
    .width(200)
    .height(200)
    .trackShadow({
      radius: 5,
      colors: [Color.Red, Color.Blue, Color.Green],
      offsetX: 15,
      offsetY: 15
    } as DataPanelShadowOptions)

  build() {
    Scroll() {
      Column(undefined) {
        DataPanel({values: [1,2,3,4,5,6,7,8], max: 100})
          .width(300)
          .height(300)
        DataPanel({values: [1,2,3,4,5,6,7,8], max: 200})
          .width(300)
          .height(300)
      }
    }
  }
}
