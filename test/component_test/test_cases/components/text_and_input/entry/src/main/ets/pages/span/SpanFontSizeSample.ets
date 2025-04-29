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
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import spanFontSizeTest from '../MyTest/SpanFontSizeTest'

@Entry
@Component
struct SpanFontSizeSample {
  @State fontSizeType: string | number | Resource = '50px'

  aboutToAppear(): void {
    loadComponentTestEntry(spanFontSizeTest)
  }

  build() {
    Column() {
      Text() {
        Span('span')
          .fontSize(this.fontSizeType)
          .id('spanFontSize1')
      }

      Button('SpanFontSize1')
        .onClick(() => {
          this.fontSizeType = 50
        })
      Button('SpanFontSize2')
        .onClick(() => {
          this.fontSizeType = $r('app.string.length')
        })
    }
  }
}