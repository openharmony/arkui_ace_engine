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
struct TextInputHeight {
  @State message: string = 'Hello World'

  build() {
    Row() {
      Column() {
        Text('操作： 打开测试页面,观察文本框内文本').fontColor(Color.Blue)
        Text('Pass条件：大字体的文字没有被上下截断，自适应在文本框内').fontColor(Color.Red)
        TextInput({ text: '测试测试测试', placeholder: 'type传入InputType.NUMBER_DECIMAL' })
          .placeholderColor(Color.Grey)
          .placeholderFont({ size: 14, weight: 400 })
          .caretColor(Color.Blue)
          .fontSize(16)
          .fontColor(Color.Black)
          .maxLines(2)
          .minFontSize('5px')
          .maxFontSize(100)
          .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
          .textOverflow(TextOverflow.Clip)
          .style(TextContentStyle.INLINE)
          .width(200)
          .height(60)
          .lineHeight(50)
      }
      .width('100%')
    }
    .height('100%')
  }
}
