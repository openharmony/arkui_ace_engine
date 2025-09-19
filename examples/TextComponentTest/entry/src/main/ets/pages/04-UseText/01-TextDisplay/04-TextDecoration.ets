/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct TextDecoration {
  build() {
    Text() {
      Span('我是Span1，').fontSize(16).fontColor(Color.Grey)
        .decoration({ type: TextDecorationType.LineThrough, color: Color.Red })
      Span('我是Span2').fontColor(Color.Blue).fontSize(16)
        .fontStyle(FontStyle.Italic)
        .decoration({ type: TextDecorationType.Underline, color: Color.Black })
      Span('，我是Span3').fontSize(16).fontColor(Color.Grey)
        .decoration({ type: TextDecorationType.Overline, color: Color.Green })
    }
    .borderWidth(1)
    .padding(10)
  }
}