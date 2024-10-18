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
import buttonFontColorTest from '../MyTest/ButtonFontColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ButtonFontColorSample {
  @State fontColorAll: ResourceColor = 'rgb(142, 255, 101)'

  aboutToAppear(): void {
    loadComponentTestEntry(buttonFontColorTest)
  }

  build() {
    Column() {
      Button('ButtonFontColor1').fontColor(Color.Black).id('buttonFontColor1')
      Button('ButtonFontColor2').fontColor(0x008000).id('buttonFontColor2')
      Button('ButtonFontColor3').fontColor(this.fontColorAll).id('buttonFontColor3')
        .onClick(() => {
          this.fontColorAll = $r('sys.color.ohos_fa_palette1')
        })
    }
  }
}