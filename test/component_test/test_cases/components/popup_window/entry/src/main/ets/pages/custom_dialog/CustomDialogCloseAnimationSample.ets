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
import customDialogCloseAnimationTest from '../MyTest/CustomDialogCloseAnimationTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';
import Curves from '@ohos.curves'

let curve = Curves.cubicBezierCurve(0.25, 0.1, 0.25, 1.0);

@CustomDialog
struct CustomDialogCloseAnimationExample {
  controller: CustomDialogController = new CustomDialogController({
    builder: CustomDialogCloseAnimationExample()
  })

  build() {
    Column() {
      Text('CustomDialogCloseAnimation')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
    }.borderRadius(10)
  }
}

@Entry
@Component
struct CustomDialogCloseAnimationSample {
  @State CustomDialogCloseAnimationOnFish: string = ''
  @State index: number = 0
  dialogController: CustomDialogController[] = [new CustomDialogController({
    builder: CustomDialogCloseAnimationExample(),
    closeAnimation: {
      duration: 500,
      tempo: 0.5,
      curve: Curve.ExtremeDeceleration,
      delay: 1000,
      iterations: 2,
      playMode: PlayMode.Normal,
      onFinish: () => {
        this.CustomDialogCloseAnimationOnFish = 'OnFish is ok'
      },
      finishCallbackType: FinishCallbackType.REMOVED,
      expectedFrameRateRange: { min: 10, max: 120, expected: 60 }
    }
  }),
    new CustomDialogController({
      builder: CustomDialogCloseAnimationExample(), closeAnimation: {
        tempo: -1,
        curve: curve.interpolate(0.5),
        playMode: PlayMode.Reverse,
        onFinish: () => {
          this.CustomDialogCloseAnimationOnFish = 'OnFish is okk'
        },
        finishCallbackType: FinishCallbackType.LOGICALLY
      }
    }),
    new CustomDialogController({
      builder: CustomDialogCloseAnimationExample(),
      closeAnimation: { curve: "fast-out-slow-in", playMode: PlayMode.Alternate }
    }),
    new CustomDialogController({
      builder: CustomDialogCloseAnimationExample(),
      closeAnimation: { playMode: PlayMode.AlternateReverse }
    })]

  aboutToAppear(): void {
    loadComponentTestEntry(customDialogCloseAnimationTest);
  }

  build() {
    Column() {
      Button('CustomDialogCloseAnimationOpen')
        .onClick(() => {
          this.dialogController[this.index].open()
          this.index += 1
          this.index %= 4
        })
      Text(this.CustomDialogCloseAnimationOnFish)
    }.width('100%').margin({ top: 5 })
  }
}