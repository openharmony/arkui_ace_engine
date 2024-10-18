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
// 测试代码路径
import customDialogOpenAnimationTest from '../MyTest/CustomDialogOpenAnimationTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';
import Curves from '@ohos.curves'

let curve = Curves.cubicBezierCurve(0.25, 0.1, 0.25, 1.0);

@CustomDialog
struct CustomDialogOpenAnimationExample {
  controller: CustomDialogController = new CustomDialogController({
    builder: CustomDialogOpenAnimationExample()
  })

  build() {
    Column() {
      Text('CustomDialogOpenAnimation')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
    }.borderRadius(10)
  }
}

@Entry
@Component
struct CustomDialogOpenAnimationSample {
  @State CustomDialogOpenAnimationOnFish: string = ''
  @State index: number = 0
  dialogController: CustomDialogController[] = [new CustomDialogController({
    builder: CustomDialogOpenAnimationExample(),
    openAnimation: {
      duration: 500,
      tempo: 0.5,
      curve: Curve.ExtremeDeceleration,
      delay: 1000,
      iterations: 2,
      playMode: PlayMode.Normal,
      onFinish: () => {
        this.CustomDialogOpenAnimationOnFish = 'OnFish is ok'
      },
      finishCallbackType: FinishCallbackType.REMOVED,
      expectedFrameRateRange: { min: 10, max: 120, expected: 60 }
    }
  }),
    new CustomDialogController({
      builder: CustomDialogOpenAnimationExample(), openAnimation: {
        tempo: -1,
        curve: curve.interpolate(0.5),
        playMode: PlayMode.Reverse,
        onFinish: () => {
          this.CustomDialogOpenAnimationOnFish = 'OnFish is okk'
        },
        finishCallbackType: FinishCallbackType.LOGICALLY
      }
    }),
    new CustomDialogController({
      builder: CustomDialogOpenAnimationExample(),
      openAnimation: { curve: "fast-out-slow-in", playMode: PlayMode.Alternate }
    }),
    new CustomDialogController({
      builder: CustomDialogOpenAnimationExample(),
      openAnimation: { playMode: PlayMode.AlternateReverse }
    })]

  aboutToAppear(): void {
    loadComponentTestEntry(customDialogOpenAnimationTest);
  }

  build() {
    Column() {
      Button('CustomDialogOpenAnimationOpen')
        .onClick(() => {
          this.dialogController[this.index].open()
          this.index += 1
          this.index %= 4
        })
      Text(this.CustomDialogOpenAnimationOnFish)
    }.width('100%').margin({ top: 5 })
  }
}