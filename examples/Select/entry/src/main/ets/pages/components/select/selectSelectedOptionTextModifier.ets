/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { TextModifier } from '@kit.ArkUI';
@Builder
export function SelectSelectedOptionTextModifierBuilder(name: string, param: Object) {
  SelectSelectedOptionTextModifier()
}
@Entry
@Component
struct SelectSelectedOptionTextModifier {
  @State text: string = 'TTTTTTTTTT'.repeat(3);
  @State index: number = 2;
  selectedOptionTextModifier: TextModifier = new TextModifier();
  @State changeIndex: number = 0;
  @State changeList: ( Optional<TextModifier> | undefined )[] = [
    this.selectedOptionTextModifier,
    undefined,
    this.selectedOptionTextModifier,
  ]
  aboutToAppear(): void {
    this.selectedOptionTextModifier
      .maxLines(1)
      .fontSize(18)
      .textAlign(TextAlign.Start)
      .fontColor('#9932cc')
      .fontWeight(FontWeight.Bold)
      .width(200)
  }

  build() {
    Column({ space: 10 }) {
      Text(`只设置selectedOptionTextModifier:`)
        .fontSize(16)
        .width('100%')
      Select([
        { value: 'A very long option text that should be truncated nicely'.repeat(3), icon: $r('app.media.startIcon') },
        { value: 'Option B', icon: $r('app.media.startIcon') },
        { value: 'Option C', icon: $r('app.media.startIcon') },
        { value: 'Option D', icon: $r('app.media.startIcon') }
      ])
        .selected(this.index)
        .value(this.text)
        .selectedOptionTextModifier(this.selectedOptionTextModifier)
        .margin({ top: 20,left:30 })
        .borderRadius(12)
        .width(200)
        .padding(9)
        .backgroundColor(Color.White)
        .shadow({ radius: 10, color: '#888888', offsetX: 0, offsetY: 10 })
      Text(`同时设置selectedOptionFont,optionFont和selectedOptionTextModifier:`)
        .fontSize(16)
        .width('100%')
      Select([
        { value: 'A very long option text that should be truncated nicely'.repeat(3), icon: $r('app.media.startIcon') },
        { value: 'Option B', icon: $r('app.media.startIcon') },
        { value: 'Option C', icon: $r('app.media.startIcon') },
        { value: 'Option D', icon: $r('app.media.startIcon') }
      ])
        .selected(this.index)
        .value(this.text)
        .optionFont({ size: 16, weight: 900 })
        .selectedOptionFont({ size: 20, weight: 100 })
        .selectedOptionTextModifier(this.selectedOptionTextModifier)
        .margin({ top: 20,left:30 })
        .borderRadius(12)
        .width(200)
        .padding(9)
        .backgroundColor(Color.White)
        .shadow({ radius: 10, color: '#888888', offsetX: 0, offsetY: 10 })
      Text(`同时设置optionFont和selectedOptionTextModifier:`)
        .fontSize(16)
        .width('100%')
      Select([
        { value: 'A very long option text that should be truncated nicely'.repeat(3), icon: $r('app.media.startIcon') },
        { value: 'Option B', icon: $r('app.media.startIcon') },
        { value: 'Option C', icon: $r('app.media.startIcon') },
        { value: 'Option D', icon: $r('app.media.startIcon') }
      ])
        .selected(this.index)
        .value(this.text)
        .optionFont({ size: 16, weight: 900 })
        .selectedOptionTextModifier(this.selectedOptionTextModifier)
        .margin({ top: 20,left:30 })
        .borderRadius(12)
        .width(200)
        .padding(9)
        .backgroundColor(Color.White)
        .shadow({ radius: 10, color: '#888888', offsetX: 0, offsetY: 10 })
      Text(`设置undefined:`)
        .fontSize(16)
        .width('100%')
      Select([
        { value: 'A very long option text that should be truncated nicely'.repeat(3), icon: $r('app.media.startIcon') },
        { value: 'Option B', icon: $r('app.media.startIcon') },
        { value: 'Option C', icon: $r('app.media.startIcon') },
        { value: 'Option D', icon: $r('app.media.startIcon') }
      ])
        .selected(this.index)
        .value(this.text)
        .selectedOptionTextModifier(undefined)
        .margin({ top: 20,left:30 })
        .borderRadius(12)
        .width(200)
        .padding(9)
        .backgroundColor(Color.White)
        .shadow({ radius: 10, color: '#888888', offsetX: 0, offsetY: 10 })
      Text(`动态延迟更新:`)
        .fontSize(16)
        .width('100%')
      Text(`设置undefined:`)
        .fontSize(16)
        .width('100%')
      Select([
        { value: 'A very long option text that should be truncated nicely'.repeat(3), icon: $r('app.media.startIcon') },
        { value: 'Option B', icon: $r('app.media.startIcon') },
        { value: 'Option C', icon: $r('app.media.startIcon') },
        { value: 'Option D', icon: $r('app.media.startIcon') }
      ])
        .selected(this.index)
        .value(this.text)
        .selectedOptionTextModifier(this.changeList[this.changeIndex])
        .margin({ top: 20,left:30 })
        .borderRadius(12)
        .width(200)
        .padding(9)
        .backgroundColor(Color.White)
        .shadow({ radius: 10, color: '#888888', offsetX: 0, offsetY: 10 })
      Button('动态延迟更新:' + this.changeList[this.changeIndex])
        .onClick(()=>{
          setTimeout(()=>{
            this.changeIndex = (this.changeIndex + 1) %this.changeList.length
          },2000)
        })

    }
    .alignItems(HorizontalAlign.Start)
    .padding(10)
    .backgroundColor('#F0F2F5')
    .width('100%')
    .height('100%')
  }
}
