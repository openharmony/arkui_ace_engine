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
import customDialogAutoCancelTest from '../MyTest/CustomDialogAutoCancelTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@CustomDialog
struct CustomDialogAutoCancelExample {
  controller: CustomDialogController = new CustomDialogController({
    builder: CustomDialogAutoCancelExample(),
  })

  build() {
    Column() {
      Text('CustomDialogAutoCancel')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
      Button('CustomDialogAutoCancelClose')
        .onClick(() => {
          if (this.controller != undefined) {
            this.controller.close()
          }
        })
    }
  }
}

@Entry
@Component
struct CustomDialogAutoCancelSample {
  dialogController: CustomDialogController = new CustomDialogController({
    builder: CustomDialogAutoCancelExample(),
    autoCancel: true
  })

  aboutToAppear(): void {
    loadComponentTestEntry(customDialogAutoCancelTest);
  }

  build() {
    Column() {
      Button('CustomDialogAutoCancelOpen')
        .onClick(() => {
          this.dialogController.open()
        })
      Button('CustomDialogAutoCancel')
        .onClick(() => {
          this.dialogController = new CustomDialogController({
            builder: CustomDialogAutoCancelExample(),
            autoCancel: false
          })
        })
    }.width('100%').margin({ top: 5 })
  }
}