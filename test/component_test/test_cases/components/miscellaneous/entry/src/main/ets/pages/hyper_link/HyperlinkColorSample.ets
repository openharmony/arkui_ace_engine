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
import hyperLinkColorTest from '../MyTest/HyperlinkColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct HyperlinkColorSample {
  @State hyperlinkColor: ResourceColor = Color.Green

  aboutToAppear(): void {
    loadComponentTestEntry(hyperLinkColorTest)
  }

  build() {
    Column() {
      Hyperlink('https://example.com/', 'hello word')
        .color(this.hyperlinkColor)
        .id('hyperlinkColor1')
      Hyperlink('https://example.com/', 'hello word')
        .color(0x808080)
        .id('hyperlinkColor2')
      Button('HyperlinkColor1')
        .onClick(() => {
          this.hyperlinkColor = 'rgb(255, 100, 255)'
        })
      Button('HyperlinkColor2')
        .onClick(() => {
          this.hyperlinkColor = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}