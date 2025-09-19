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
struct Decoration {
  build() {
    Column() {
      Text('This is the text')
        .decoration({
          type: TextDecorationType.LineThrough,
          color: Color.Red
        })
        .borderWidth(1).padding(15).margin(5)
      Text('This is the text')
        .decoration({
          type: TextDecorationType.Overline,
          color: Color.Red
        })
        .borderWidth(1).padding(15).margin(5)
      Text('This is the text')
        .decoration({
          type: TextDecorationType.Underline,
          color: Color.Red
        })
        .borderWidth(1).padding(15).margin(5)
      Text('This is the text')
        .decoration({
          type: TextDecorationType.Underline,
          color: Color.Blue,
          style: TextDecorationStyle.DASHED
        })
        .borderWidth(1).padding(15).margin(5)
      Text('This is the text')
        .decoration({
          type: TextDecorationType.Underline,
          color: Color.Blue,
          style: TextDecorationStyle.DOTTED
        })
        .borderWidth(1).padding(15).margin(5)
      Text('This is the text')
        .decoration({
          type: TextDecorationType.Underline,
          color: Color.Blue,
          style: TextDecorationStyle.DOUBLE
        })
        .borderWidth(1).padding(15).margin(5)
      Text('This is the text')
        .decoration({
          type: TextDecorationType.Underline,
          color: Color.Blue,
          style: TextDecorationStyle.WAVY,
          thicknessScale: 4
        })
        .borderWidth(1).padding(15).margin(5)
    }
  }
}