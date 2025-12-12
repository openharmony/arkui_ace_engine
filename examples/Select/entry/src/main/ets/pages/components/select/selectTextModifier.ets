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
export function SelectTextModifierBuilder(name: string, param: Object) {
  SelectTextModifier()
}
@Entry
@Component
struct SelectTextModifier {
  @State text: string = 'TTTTTTTTTT'.repeat(3);
  @State index: number = 2;
  textModifier: TextModifier = new TextModifier();
  @State changeIndex: number = 0;
  @State changeList: ( Optional<TextModifier> | undefined )[] = [
    this.textModifier,
    undefined,
    this.textModifier,
  ]

  aboutToAppear(): void {
    this.textModifier
      .maxLines(2)
      .fontSize(18)
      .textAlign(TextAlign.Center)
      .fontColor(Color.Red)
      .fontWeight(FontWeight.Medium)
      .textOverflow({overflow:TextOverflow.Clip})
  }

  build() {
    Column({ space: 20 }) {
      Text(`设置textModifier:`)
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
        .textModifier(this.textModifier)
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
        .textModifier(undefined)
        .borderRadius(12)
        .width(200)
        .padding(9)
        .backgroundColor(Color.White)
        .shadow({ radius: 10, color: '#888888', offsetX: 0, offsetY: 10 })
      Text(`动态延迟更新:`)
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
        .textModifier(this.changeList[this.changeIndex])
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
