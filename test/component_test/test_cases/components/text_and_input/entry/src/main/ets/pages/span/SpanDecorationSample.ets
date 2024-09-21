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
import spanDecorationTest from '../MyTest/SpanDecorationTest'

@Entry
@Component
struct SpanDecorationSample {
  @State decorationValue: TextDecorationType = TextDecorationType.Overline
  @State colorValue: ResourceColor = 'rgb(255, 100, 255)'

  aboutToAppear(): void {
    loadComponentTestEntry(spanDecorationTest)
  }

  build() {
    Column() {
      Text() {
        Span('Span')
          .decoration({ type: TextDecorationType.LineThrough, color: Color.Red })
          .id('spanDecoration1')
        Span('Span')
          .decoration({ type: TextDecorationType.None, color: $r('sys.color.ohos_id_color_text_hyperlink') })
          .id('spanDecoration2')
        Span('Span')
          .decoration({ type: this.decorationValue, color: this.colorValue })
          .id('spanDecoration3')
      }

      Button('SpanDecoration')
        .onClick(() => {
          this.decorationValue = TextDecorationType.Underline
          this.colorValue = 0x0000FF
        })
    }
  }
}