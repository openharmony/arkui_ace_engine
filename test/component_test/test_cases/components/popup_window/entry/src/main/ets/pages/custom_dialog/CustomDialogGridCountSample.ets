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
import customDialogGridCountTest from '../MyTest/CustomDialogGridCountTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@CustomDialog
struct CustomDialogGridCountExample {
  controller: CustomDialogController = new CustomDialogController({
    builder: CustomDialogGridCountExample()
  })

  build() {
    Column() {
      Text('CustomDialogGridCount')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
    }
  }
}

@Entry
@Component
struct CustomDialogGridCountSample {
  dialogController: CustomDialogController = new CustomDialogController({
    builder: CustomDialogGridCountExample(),
    gridCount: 3
  })

  aboutToAppear(): void {
    loadComponentTestEntry(customDialogGridCountTest);
  }

  build() {
    Column() {
      Button('CustomDialogGridCountOpen')
        .onClick(() => {
          this.dialogController.open()
        })
    }.width('100%').margin({ top: 5 })
  }
}