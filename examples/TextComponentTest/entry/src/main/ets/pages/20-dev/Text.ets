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
struct Index4263 {
  @State text: string = '测试文字'
  @State copyOptions: CopyOptions[] = [CopyOptions.LocalDevice, CopyOptions.None, CopyOptions.InApp, CopyOptions.CROSS_DEVICE]
  @State copyOptionsIndex: number = 0
  @State selectionStart: number = 0
  @State selectionEnd: number = 0
  @State selectionStart1: number = 0
  @State selectionEnd1: number = 0

  build() {
    Column({ space: 10 }) {
      Text(this.text)
        .selection(this.selectionStart,this.selectionEnd)
        .copyOption(this.copyOptions[this.copyOptionsIndex])
        .borderWidth(1)

      TextArea({ text: this.text})
        .onChange((value: string) => {
          this.text = value
        })

      Text() {
        Span('该组件从API Version 10开始支持继承父组件Text的属性，即如果子组件未设置属性且父组件设置属性，则继承父组件设置的属性。支持继承的属性仅包括：fontColor、fontSize、fontStyle、fontWeight、decoration、letterSpacing、textCase、fontfamily、textShadow。')
        ImageSpan($r('app.media.icon')).width(50).height(50)
        Span('该组件从API Version 10开始支持继承父组件Text的属性，即如果子组件未设置属性且父组件设置属性，则继承父组件设置的属性。支持继承的属性仅包括：fontColor、fontSize、fontStyle、fontWeight、decoration、letterSpacing、textCase、fontfamily、textShadow。')
        SymbolSpan($r('sys.symbol.ohos_folder_badge_plus'))
          .fontSize(50)
        ContainerSpan(){
          ImageSpan($r('app.media.icon')).width(50).height(50)
          Span('该组件从API Version 10开始支持继承父组件Text的属性，即如果子组件未设置属性且父组件设置属性，则继承父组件设置的属性。支持继承的属性仅包括：fontColor、fontSize、fontStyle、fontWeight、decoration、letterSpacing、textCase、fontfamily、textShadow。')
        }
        ImageSpan($r('app.media.icon')).width(50).height(50)
        SymbolSpan($r('sys.symbol.ohos_folder_badge_plus'))
          .fontSize(50)
      }
        .width(250)
        .height(100)
        .borderWidth(1)
        .selection(this.selectionStart1,this.selectionEnd1)
        .copyOption(this.copyOptions[this.copyOptionsIndex])

      Row() {
        Button('copyOptions: ' + this.copyOptions[this.copyOptionsIndex])
          .width('50%')
          .onClick(() => {
            this.copyOptionsIndex = (this.copyOptionsIndex + 1) % this.copyOptions.length
          })
      }

      Row(){
        Button('1、selectionStart-,' + this.selectionStart)
          .width('50%')
          .onClick((event: ClickEvent) => {
          this.selectionStart -= 5
        })
        Button('1、selectionStart+,' + this.selectionStart)
          .width('50%')
          .onClick((event: ClickEvent) => {
          this.selectionStart += 5
        })
      }

      Row(){
        Button('1、selectionEnd-,' + this.selectionEnd)
          .width('50%')
          .onClick((event: ClickEvent) => {
          this.selectionEnd -= 5
        })
        Button('1、selectionEnd+,' + this.selectionEnd)
          .width('50%')
          .onClick((event: ClickEvent) => {
          this.selectionEnd += 5
        })
      }


      Row(){
        Button('2、selectionStart-,' + this.selectionStart1)
          .width('50%')
          .onClick((event: ClickEvent) => {
          this.selectionStart1 -= 5
        })
        Button('2、selectionStart+,' + this.selectionStart1)
          .width('50%')
          .onClick((event: ClickEvent) => {
          this.selectionStart1 += 5
        })
      }

      Row(){
        Button('2、selectionEnd-,' + this.selectionEnd1)
          .width('50%')
          .onClick((event: ClickEvent) => {
          this.selectionEnd1 -= 5
        })
        Button('2、selectionEnd+,' + this.selectionEnd1)
          .width('50%')
          .onClick((event: ClickEvent) => {
          this.selectionEnd1 += 5
        })
      }
    }.width('100%').height('100%')
  }
}