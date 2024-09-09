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
import customDialogShowInSubWindowTest from '../MyTest/CustomDialogShowInSubWindowTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@CustomDialog
struct CustomDialogShowInSubWindowExample {
  controller: CustomDialogController = new CustomDialogController({
    builder: CustomDialogShowInSubWindowExample()
  })

  build() {
    Column() {
      Text('CustomDialogShowInSubWindow')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
    }
  }
}

@Entry
@Component
struct CustomDialogShowInSubWindowSample {
  dialogController: CustomDialogController = new CustomDialogController({
    builder: CustomDialogShowInSubWindowExample(),
    showInSubWindow: false
  })

  aboutToAppear(): void {
    loadComponentTestEntry(customDialogShowInSubWindowTest);
  }

  build() {
    Column() {
      Button('CustomDialogShowInSubWindowOpen')
        .onClick(() => {
          this.dialogController.open()
        })
      Button('CustomDialogShowInSubWindow')
        .onClick(() => {
          this.dialogController =
            new CustomDialogController({ builder: CustomDialogShowInSubWindowExample(), showInSubWindow: true })
        })
    }.width('100%').margin({ top: 5 })
  }
}