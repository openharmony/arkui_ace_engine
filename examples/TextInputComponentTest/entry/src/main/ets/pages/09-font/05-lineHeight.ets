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
struct lineHeightPage {
  @State value: number = 0
  @State text: string = 'A simple day in my life begins with a cup of coffee and a glimpse of the sunrise.'

  build() {
    Row() {
      Scroll() {
        Column() {
          Text() {
            Span('规格: \n')
            Span('大于0值有效果，小于等于0为非法值 \n')
          }.draggable(true).copyOption(CopyOptions.InApp)

          Text('当lineHeight大于0时设置成功 小于或等于0时设置为默认值').fontSize(10)
          TextInput({ text: this.text })
            .fontSize(20)
            .lineHeight(this.value)
          TextArea({ text: this.text })
            .fontSize(20)
            .lineHeight(this.value)
          Button('改变lineHeight为-1').onClick(() => {
            this.value = -1;
          }).fontSize(10)
          Button('改变lineHeight为0').onClick(() => {
            this.value = 0;
          }).fontSize(10)
          Button('改变lineHeight为1').onClick(() => {
            this.value = 1;
          }).fontSize(10)
          Button('改变lineHeight为10').onClick(() => {
            this.value = 10;
          }).fontSize(10)
          Button('改变lineHeight为100').onClick(() => {
            this.value = 20;
          }).fontSize(10)
          TextArea()
            .borderWidth(2)
            .height(500)
            .opacity(0)
        }
        .width('100%')
      }
    }
  }
}