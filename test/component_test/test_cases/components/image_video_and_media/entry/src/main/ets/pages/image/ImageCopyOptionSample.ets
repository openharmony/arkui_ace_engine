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
//测试代码路径
import imageCopyOptionTest from '../MyTest/ImageCopyOptionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageCopyOptionSample {
  @State copyOption: CopyOptions = CopyOptions.None

  aboutToAppear(): void {
    loadComponentTestEntry(imageCopyOptionTest)
  }

  build() {
    Column({ space: 8 }) {
      Image($r('app.media.run_icon'))
        .width(110)
        .height(110)
        .margin(5)
        .copyOption(this.copyOption)
        .id('imageCopyOption1')
      Button('ImageCopyOption1')
        .onClick(() => {
          this.copyOption = CopyOptions.InApp
        })
      Image($r('app.media.city_icon'))
        .width(220)
        .height(220)
        .margin(5)
        .copyOption(CopyOptions.LocalDevice)
        .id('imageCopyOption2')
      Image($r('app.media.city_icon'))
        .width(220)
        .height(220)
        .margin(5)
        .copyOption(CopyOptions.CROSS_DEVICE)
        .id('imageCopyOption3')
    }
  }
}