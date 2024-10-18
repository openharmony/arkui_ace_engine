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
import customDialogCornerRadiusTest from '../MyTest/CustomDialogCornerRadiusTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@CustomDialog
struct CustomDialogCornerRadiusExample {
  controller: CustomDialogController = new CustomDialogController({
    builder: CustomDialogCornerRadiusExample()
  })

  build() {
    Column() {
      Text('CustomDialogCornerRadius')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
    }
  }
}

@Entry
@Component
struct CustomDialogCornerRadiusSample {
  @State index: number = 0
  dialogController: CustomDialogController[] = [new CustomDialogController({
    builder: CustomDialogCornerRadiusExample(),
    cornerRadius: {
      topLeft: 30,
      topRight: 30,
      bottomLeft: 30,
      bottomRight: 30
    }
  }),
    new CustomDialogController({
      builder: CustomDialogCornerRadiusExample(),
      cornerRadius: {
        topLeft: '30px',
        topRight: '30px',
        bottomLeft: '30px',
        bottomRight: '30px'
      }
    }),
    new CustomDialogController({
      builder: CustomDialogCornerRadiusExample(), cornerRadius: {
        topLeft: $r('app.string.custom_dialog_length'),
        topRight: $r('app.string.custom_dialog_length'),
        bottomLeft: $r('app.string.custom_dialog_length'),
        bottomRight: $r('app.string.custom_dialog_length')
      }
    }),
    new CustomDialogController({ builder: CustomDialogCornerRadiusExample(), cornerRadius: '10px' }),
    new CustomDialogController({ builder: CustomDialogCornerRadiusExample(), cornerRadius: '10vp' }),
    new CustomDialogController({ builder: CustomDialogCornerRadiusExample(), cornerRadius: '10fp' }),
    new CustomDialogController({ builder: CustomDialogCornerRadiusExample(), cornerRadius: '10lpx' }),
    new CustomDialogController({ builder: CustomDialogCornerRadiusExample(), cornerRadius: '10%' }),
    new CustomDialogController({
      builder: CustomDialogCornerRadiusExample(),
      cornerRadius: $r('app.string.custom_dialog_length')
    }),]

  aboutToAppear(): void {
    loadComponentTestEntry(customDialogCornerRadiusTest);
  }

  build() {
    Column() {
      Button('CustomDialogCornerRadiusOpen')
        .onClick(() => {
          this.dialogController[this.index].open()
          this.index += 1
          this.index %= 9
        })
    }.width('100%').margin({ top: 5 })
  }
}