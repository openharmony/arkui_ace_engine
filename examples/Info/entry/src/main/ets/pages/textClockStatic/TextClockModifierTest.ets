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
  FontStyle,
  ShadowOptions,
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
  @State datavalue: number = 0

  testTextClockModifier1: TextClockModifier = new TextClockModifier()
    .format("yyyyMMdd hh")
  testTextClockModifier2: TextClockModifier = new TextClockModifier()
    .fontColor(Color.Red)
  testTextClockModifier3: TextClockModifier = new TextClockModifier()
    .fontSize(30)
  testTextClockModifier4: TextClockModifier = new TextClockModifier()
    .fontStyle(FontStyle.Italic)
  testTextClockModifier5: TextClockModifier = new TextClockModifier()
    .fontWeight(300)
  testTextClockModifier6: TextClockModifier = new TextClockModifier()
    .fontFamily("HarmonyOS Sans")
  testTextClockModifier7: TextClockModifier = new TextClockModifier()
    .textShadow({
      radius: 10,
      color: Color.Red,
      offsetX: 10,
      offsetY: 0
    } as ShadowOptions)
  testTextClockModifier8: TextClockModifier = new TextClockModifier()
    .fontFeature("")
  testTextClockModifier9: TextClockModifier = new TextClockModifier()
    .onDateChange((value: Long)=>{
      this.datavalue = value
    })


  build() {
    Scroll() {
      Column(undefined) {
        TextClock()
          .attributeModifier(this.testTextClockModifier1)
        TextClock()
          .attributeModifier(this.testTextClockModifier2)
        TextClock()
          .attributeModifier(this.testTextClockModifier3)
        TextClock()
          .attributeModifier(this.testTextClockModifier4)
        TextClock()
          .attributeModifier(this.testTextClockModifier5)
        TextClock()
          .attributeModifier(this.testTextClockModifier6)
        TextClock()
          .attributeModifier(this.testTextClockModifier7)
        TextClock()
          .attributeModifier(this.testTextClockModifier8)
        TextClock()
          .attributeModifier(this.testTextClockModifier9)
        Text(this.datavalue + "")
      }
    }
  }
}
