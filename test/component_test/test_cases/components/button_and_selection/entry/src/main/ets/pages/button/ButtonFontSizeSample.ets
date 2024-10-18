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
import buttonFontSizeTest from '../MyTest/ButtonFontSizeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ButtonFontSizeSample {
  @State fontSizeText: string | Resource = '50px'

  aboutToAppear(): void {
    loadComponentTestEntry(buttonFontSizeTest)
  }

  build() {
    Column() {
      Button('ButtonFontSize1').fontSize(30).id('buttonFontSize1')
      Button('ButtonFontSize2').fontSize(this.fontSizeText).id('buttonFontSize2').onClick(() => {
        this.fontSizeText = $r('app.string.font_size')
      });
    }
  }
}