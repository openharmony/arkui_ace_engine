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

import backgroundColorTest from '../MyTest/BackgroundColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BackgroundColorSample {
  @State color: ResourceColor = Color.Blue

  aboutToAppear(): void {
    loadComponentTestEntry(backgroundColorTest)
  }

  build() {
    Column() {
      Text('Text1')
        .backgroundColor(this.color)
        .id('textAreaBackgroundColor1')
      Button('ButtonBackgroundColor')
        .onClick(() => {
          this.color = 0xAFEEEE
        })
      Text('Text2')
        .backgroundColor('rgba(246, 0, 0, 1.00)')
        .id('textAreaBackgroundColor2')
      Text('Text3')
        .backgroundColor($r('sys.color.ohos_id_color_text_hyperlink'))
        .id('textAreaBackgroundColor3')
    }
  }
}

