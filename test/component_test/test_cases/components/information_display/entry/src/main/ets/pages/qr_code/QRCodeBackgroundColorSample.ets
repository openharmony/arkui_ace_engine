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
import qRCodeBackgroundColorTest from '../MyTest/QRCodeBackgroundColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct QRCodeBackgroundColorSample {
  private value: string = 'hello world'
  @State backgroundColorsStatus: ResourceColor = Color.Orange

  aboutToAppear(): void {
    loadComponentTestEntry(qRCodeBackgroundColorTest)
  }

  build() {
    Column({ space: 5 }) {
      QRCode(this.value)
        .backgroundColor(this.backgroundColorsStatus)
        .width(100)
        .height(100)
        .id('qRCodeBackgroundColor1')

      QRCode(this.value)
        .backgroundColor(0x00FFFF)
        .width(100)
        .height(100)
        .id('qRCodeBackgroundColor2')

      Button('QRCodeBackgroundColor1')
        .onClick(() => {
          this.backgroundColorsStatus = "#ffc007f3"
        })
      Button('QRCodeBackgroundColor2')
        .onClick(() => {
          this.backgroundColorsStatus = $r('app.color.data_panel_resource_color6')
        })
    }
  }
}