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
import imageFillColorTest from '../MyTest/ImageFillColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageFillColorSample {
  @State fillColor: ResourceColor = Color.Green

  aboutToAppear(): void {
    loadComponentTestEntry(imageFillColorTest)
  }

  build() {
    Column() {
      Button('ImageFillColor1')
        .onClick(() => {
          this.fillColor = '#0000ff'
        })
      Button('ImageFillColor2')
        .onClick(() => {
          this.fillColor = 0x000000
        })
      Image($r('sys.media.ohos_ic_public_play_last'))
        .width('40%')
        .height(150)
        .margin(15)
        .fillColor(this.fillColor)
        .id('imageFillColor1')
      Image($r('sys.media.ohos_ic_public_play_last'))
        .width('40%')
        .height(150)
        .margin(15)
        .fillColor($r("app.color.image_fill_color"))
        .id('imageFillColor2')
    }
  }
}