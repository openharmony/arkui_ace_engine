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
  TextTimerController,
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
  public textTimerController: TextTimerController = new TextTimerController()

  testTextTimerModifier1: TextTimerModifier = new TextTimerModifier()
    .format("hh-mm-ss")
  testTextTimerModifier2: TextTimerModifier = new TextTimerModifier()
    .fontColor(Color.Red)
  testTextTimerModifier3: TextTimerModifier = new TextTimerModifier()
    .fontSize(30)
  testTextTimerModifier4: TextTimerModifier = new TextTimerModifier()
    .fontStyle(FontStyle.Italic)
  testTextTimerModifier5: TextTimerModifier = new TextTimerModifier()
    .fontWeight(300)
  testTextTimerModifier6: TextTimerModifier = new TextTimerModifier()
    .fontFamily("HarmonyOS Sans")
  testTextTimerModifier7: TextTimerModifier = new TextTimerModifier()
    .textShadow({
      radius: 10,
      color: Color.Red,
      offsetX: 10,
      offsetY: 0
    } as ShadowOptions)
  testTextTimerModifier8: TextTimerModifier = new TextTimerModifier()
    .onTimer((utc: Long, elapsedTime: Long)=>{
      this.datavalue = elapsedTime
    })


  build() {
    Scroll() {
      Column(undefined) {
        TextTimer()
          .attributeModifier(this.testTextTimerModifier1)
        TextTimer()
          .attributeModifier(this.testTextTimerModifier2)
        TextTimer()
          .attributeModifier(this.testTextTimerModifier3)
        TextTimer()
          .attributeModifier(this.testTextTimerModifier4)
        TextTimer()
          .attributeModifier(this.testTextTimerModifier5)
        TextTimer()
          .attributeModifier(this.testTextTimerModifier6)
        TextTimer()
          .attributeModifier(this.testTextTimerModifier7)
        TextTimer({controller: this.textTimerController})
          .attributeModifier(this.testTextTimerModifier8)
        Text(this.datavalue + "")
        Button("start")
          .onClick(()=>{
            this.textTimerController.start();
          })
      }
    }
  }
}
