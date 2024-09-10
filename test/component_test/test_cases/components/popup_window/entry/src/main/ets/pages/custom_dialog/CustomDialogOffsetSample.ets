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
import customDialogOffsetTest from '../MyTest/CustomDialogOffsetTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@CustomDialog
struct CustomDialogOffsetExample {
  controller: CustomDialogController = new CustomDialogController({
    builder: CustomDialogOffsetExample(),
  })

  build() {
    Column() {
      Text('CustomDialogOffset')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
    }
  }
}

@Entry
@Component
struct CustomDialogOffsetSample {
  @State index: number = 0
  dialogController: CustomDialogController[] = [new CustomDialogController({
    builder: CustomDialogOffsetExample(),
    offset: { dx: 0, dy: -25 }
  }), new CustomDialogController({
    builder: CustomDialogOffsetExample(),
    offset: { dx: '15px', dy: '15px' }
  }), new CustomDialogController({
    builder: CustomDialogOffsetExample(),
    offset: { dx: $r('app.string.custom_dialog_length'), dy: $r('app.string.custom_dialog_length') }
  })]

  aboutToAppear(): void {
    loadComponentTestEntry(customDialogOffsetTest);
  }

  build() {
    Column() {
      Button('CustomDialogOffsetOpen')
        .onClick(() => {
          this.dialogController[this.index].open()
          this.index += 1
          this.index %= 3
        })
    }.width('100%').margin({ top: 5 })
  }
}