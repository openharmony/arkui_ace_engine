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
struct fontFeaturePage {
  build() {
    Row() {
      Scroll() {
        Column() {
          Text() {
            Span('规格: \n')
            Span('测试fontFeature \n')
          }.draggable(true).copyOption(CopyOptions.InApp)

          Text('测试规格 fontFeature').fontSize(15)
          Text('使用span应该无效果').fontSize(15)
          Text('Span 打开fontFeature').fontSize(15)
          Text() {
            Span('This is ss01 on : 0123456789101112')
          }
          .fontSize(20)
          .fontFeature('\'ss01\' on')

          Text('Span 关闭fontFeature').fontSize(15)
          Text() {
            Span('This is ss01 on : 0123456789101112')
          }
          .fontSize(20)
          .fontFeature('\'ss01\' off')

          Text('使用TextArea 打开fontFeature应该有效果').fontSize(15)
          Text('TextArea 打开fontFeature').fontSize(15)
          TextArea({ text: 'This is ss01 on : 0123456789101112' })
            .fontSize(20)
            .fontFeature('\'ss01\' on')

          Text('TextArea 关闭fontFeature').fontSize(15)
          TextArea({ text: 'This is ss01 on : 0123456789101112' })
            .fontSize(20)
            .fontFeature('\'ss01\' off')
          TextArea()
            .borderWidth(2)
            .height(500)
            .opacity(0)
        }.width('100%')
      }
    }
  }
}