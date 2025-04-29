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
import qRCodeColorTest from '../MyTest/QRCodeColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct QRCodeColorSample {
  private value: string = 'hello world'
  @State colorStatus: ResourceColor = Color.Red

  aboutToAppear(): void {
    loadComponentTestEntry(qRCodeColorTest)
  }

  build() {
    Column({ space: 5 }) {
      QRCode(this.value)
        .color(this.colorStatus)
        .width(50)
        .height(50)
        .id('qRCodeColor1')

      QRCode(this.value)
        .color(0xFFFF00)
        .width(50)
        .height(50)
        .id('qRCodeColor2')

      Button('QRCodeColor1')
        .onClick(() => {
          this.colorStatus = "#ffc007f3"
        })
      Button('QRCodeColor2')
        .onClick(() => {
          this.colorStatus = $r('app.color.data_panel_resource_color8')
        })
    }
  }
}