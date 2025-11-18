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
  ImageRenderMode,
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
  @State txt: number = 0
  @State txt2: string = ""
  testPatternLockModifier: PatternLockModifier = new PatternLockModifier()
    .width(200)
    .height(200)
    .sideLength(150)
    .circleRadius(20)
    .regularColor(Color.Red)
    .autoReset(true)
  testPatternLockModifier2: PatternLockModifier = new PatternLockModifier()
    .width(200)
    .height(200)
    .backgroundColor(Color.Red)
    .selectedColor(Color.Blue)
    .activeColor(Color.Yellow)
    .autoReset(false)
    .onDotConnect((index: Int) => {
      this.txt = index
      console.info("onDotConnect index: " + index);
    })
  testPatternLockModifier3: PatternLockModifier = new PatternLockModifier()
    .width(200)
    .height(200)
    .pathColor(Color.Red)
    .pathStrokeWidth(20)
    .skipUnselectedPoint(true)
    .onPatternComplete((input: Array<Int>)=>{
      this.txt2 = input + ""
    })

  build() {
    Scroll() {
      Column(undefined) {
        PatternLock()
          .attributeModifier(this.testPatternLockModifier)
        PatternLock()
          .attributeModifier(this.testPatternLockModifier2)
        Text(this.txt + "")
        PatternLock()
          .attributeModifier(this.testPatternLockModifier3)
        Text(this.txt2)
      }
    }
  }
}
