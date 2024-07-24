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
import customDialogAlignmentTest from '../MyTest/CustomDialogAlignmentTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@CustomDialog
struct CustomDialogAlignmentExample {
  controller: CustomDialogController = new CustomDialogController({
    builder: CustomDialogAlignmentExample(),
  })

  build() {
    Column() {
      Text('CustomDialogAlignment')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
    }
  }
}

@Entry
@Component
struct CustomDialogAlignmentSample {
  @State index: number = 0
  dialogController: CustomDialogController[] = [new CustomDialogController({
    builder: CustomDialogAlignmentExample(),
    alignment: DialogAlignment.Top
  }), new CustomDialogController({
    builder: CustomDialogAlignmentExample(),
    alignment: DialogAlignment.Center
  }), new CustomDialogController({
    builder: CustomDialogAlignmentExample(),
    alignment: DialogAlignment.Bottom
  }), new CustomDialogController({
    builder: CustomDialogAlignmentExample(),
    alignment: DialogAlignment.Default
  }), new CustomDialogController({
    builder: CustomDialogAlignmentExample(),
    alignment: DialogAlignment.TopStart
  }), new CustomDialogController({
    builder: CustomDialogAlignmentExample(),
    alignment: DialogAlignment.TopEnd
  }), new CustomDialogController({
    builder: CustomDialogAlignmentExample(),
    alignment: DialogAlignment.CenterStart
  }), new CustomDialogController({
    builder: CustomDialogAlignmentExample(),
    alignment: DialogAlignment.CenterEnd
  }), new CustomDialogController({
    builder: CustomDialogAlignmentExample(),
    alignment: DialogAlignment.BottomStart
  }), new CustomDialogController({
    builder: CustomDialogAlignmentExample(),
    alignment: DialogAlignment.BottomEnd
  })]

  aboutToAppear(): void {
    loadComponentTestEntry(customDialogAlignmentTest);
  }

  build() {
    Column() {
      Button('CustomDialogAlignmentOpen')
        .onClick(() => {
          this.dialogController[this.index].open()
          this.index += 1
          this.index %= 10
        })
    }.width('100%').margin({ top: 5 })
  }
}