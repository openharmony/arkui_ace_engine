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
import spanTextBackgroundStyleTest from '../MyTest/SpanTextBackgroundStyleTest'

@Entry
@Component
struct SpanTextBackgroundStyleSample {
  @State textBackgroundStyleType1: TextBackgroundStyle = { radius: '50vp', color: 0xFF1493 }
  @State textBackgroundStyleType2: TextBackgroundStyle[] =
    [{ radius: '50%', color: 0x7FFF00 }, { radius: $r('app.string.length'), color: 0x7FFF00 },
      {
        radius: {
          topLeft: 10,
          topRight: 10,
          bottomLeft: 20,
          bottomRight: 20
        },
        color: 0x7FFF00
      }, {
        radius: {
          topLeft: '10px',
          topRight: '10px',
          bottomLeft: '20px',
          bottomRight: '20px'
        }, color: 0x7FFF00
      }, {
        radius: {
          topLeft: $r('app.string.length'),
          topRight: $r('app.string.length'),
          bottomLeft: $r('app.string.length'),
          bottomRight: $r('app.string.length')
        },
        color: 0x7FFF00
      }]
  @State index: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(spanTextBackgroundStyleTest)
  }

  build() {
    Column() {
      Text() {
        Span('TextBackgroundStyle')
          .textBackgroundStyle({ radius: '10px', color: Color.Green })
          .id('spanTextBackgroundStyle1')
      }

      Text() {
        Span('TextBackgroundStyle')
          .textBackgroundStyle(this.textBackgroundStyleType1)
          .id('spanTextBackgroundStyle2')
      }

      Text() {
        Span('TextBackgroundStyle')
          .textBackgroundStyle(this.textBackgroundStyleType2[this.index])
          .id('spanTextBackgroundStyle3')
      }

      Button('SpanTextBackgroundStyle1')
        .onClick(() => {
          this.textBackgroundStyleType1 = { radius: '10fp', color: '#7FFFD4' }
        })
      Button('SpanTextBackgroundStyle2')
        .onClick(() => {
          this.textBackgroundStyleType1 = { radius: '40lpx', color: $r('sys.color.ohos_id_color_text_hyperlink') }
        })
      Button('SpanTextBackgroundStyle3')
        .onClick(() => {
          this.index++
          this.index %= 5
        })
    }
  }
}