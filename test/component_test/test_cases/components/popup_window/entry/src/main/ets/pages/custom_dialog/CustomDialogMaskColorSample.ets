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
import customDialogMaskColorTest from '../MyTest/CustomDialogMaskColorTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@CustomDialog
struct CustomDialogMaskColorExample {
  controller: CustomDialogController = new CustomDialogController({
    builder: CustomDialogMaskColorExample()
  })

  build() {
    Column() {
      Text('CustomDialogMaskColor')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
    }
  }
}

@Entry
@Component
struct CustomDialogMaskColorSample {
  @State index: number = 0
  dialogController: CustomDialogController[] = [new CustomDialogController({
    builder: CustomDialogMaskColorExample(),
    maskColor: Color.Pink
  }), new CustomDialogController({
    builder: CustomDialogMaskColorExample(),
    maskColor: 0xffa500
  }), new CustomDialogController({
    builder: CustomDialogMaskColorExample(),
    maskColor: '#ffff00'
  }), new CustomDialogController({
    builder: CustomDialogMaskColorExample(),
    maskColor: $r('sys.color.ohos_id_color_text_hyperlink')
  })]

  aboutToAppear(): void {
    loadComponentTestEntry(customDialogMaskColorTest);
  }

  build() {
    Column() {
      Button('CustomDialogMaskColorOpen')
        .onClick(() => {
          this.dialogController[this.index].open()
          this.index += 1
          this.index %= 4
        })
    }.width('100%').margin({ top: 5 })
  }
}