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
import textClockFontColorTest from '../MyTest/TextClockFontColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TextClockFontColorSample {
  @State fontColorStatus: ResourceColor = 0xff0000

  aboutToAppear(): void {
    loadComponentTestEntry(textClockFontColorTest)
  }

  build() {
    Column({ space: 8 }) {
      TextClock()
        .id('textClockFontColor1')
        .fontColor(this.fontColorStatus)
      TextClock()
        .id('textClockFontColor2')
        .fontColor("#ffc007f3")
      Button('TextClockFontColor1')
        .onClick(() => {
          this.fontColorStatus = Color.Blue
        })
      Button('TextClockFontColor2')
        .onClick(() => {
          this.fontColorStatus = $r('app.color.data_panel_resource_color5')
        })
    }
  }
}