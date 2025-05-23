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
import customDialogBackgroundColorTest from '../MyTest/CustomDialogBackgroundColorTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@CustomDialog
struct CustomDialogBackgroundColorExample {
  controller: CustomDialogController = new CustomDialogController({
    builder: CustomDialogBackgroundColorExample()
  })

  build() {
    Column() {
      Text('CustomDialogBackgroundColor')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
    }.backgroundColor(Color.Pink)
  }
}

@Entry
@Component
struct CustomDialogBackgroundColorSample {
  @State index: number = 0
  dialogController: CustomDialogController[] = [new CustomDialogController({
    builder: CustomDialogBackgroundColorExample(), backgroundColor: Color.Green
  }),
    new CustomDialogController({ builder: CustomDialogBackgroundColorExample(), backgroundColor: 0xffa500 }),
    new CustomDialogController({ builder: CustomDialogBackgroundColorExample(), backgroundColor: '#ffc0cb' }),
    new CustomDialogController({
      builder: CustomDialogBackgroundColorExample(),
      backgroundColor: $r('sys.color.ohos_id_color_text_hyperlink')
    })]

  aboutToAppear(): void {
    loadComponentTestEntry(customDialogBackgroundColorTest);
  }

  build() {
    Column() {
      Button('CustomDialogBackgroundColorOpen')
        .onClick(() => {
          this.dialogController[this.index].open()
          this.index += 1
          this.index %= 4
        })
    }.width('100%').margin({ top: 5 })
  }
}