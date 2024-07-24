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
import customDialogMaskRectTest from '../MyTest/CustomDialogMaskRectTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@CustomDialog
struct CustomDialogMaskRectExample {
  controller: CustomDialogController = new CustomDialogController({
    builder: CustomDialogMaskRectExample()
  })

  build() {
    Column() {
      Text('CustomDialogMaskRect')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
    }
  }
}

@Entry
@Component
struct CustomDialogMaskRectSample {
  @State index: number = 0
  dialogController: CustomDialogController[] = [new CustomDialogController({
    builder: CustomDialogMaskRectExample(),
    maskRect: {
      x: 0,
      y: 0,
      width: 999,
      height: 999
    }
  }), new CustomDialogController({
    builder: CustomDialogMaskRectExample(),
    maskRect: {
      x: '0px',
      y: '0px',
      width: '80%',
      height: '80%'
    }
  }), new CustomDialogController({
    builder: CustomDialogMaskRectExample(),
    maskRect: {
      x: $r('app.string.custom_dialog_mask_rect_length'),
      y: $r('app.string.custom_dialog_mask_rect_length'),
      width: $r('app.string.custom_dialog_mask_rect_length'),
      height: $r('app.string.custom_dialog_mask_rect_length')
    }
  }), new CustomDialogController({
    builder: CustomDialogMaskRectExample(),
    maskRect: {
      x: '0px',
      y: '0px',
      width: '80%',
      height: '80%'
    }, showInSubWindow: true
  })]

  aboutToAppear(): void {
    loadComponentTestEntry(customDialogMaskRectTest);
  }

  build() {
    Column() {
      Button('CustomDialogMaskRectOpen')
        .onClick(() => {
          this.dialogController[this.index].open()
          this.index += 1
          this.index %= 4
        })
    }.width('100%').margin({ top: 5 })
  }
}