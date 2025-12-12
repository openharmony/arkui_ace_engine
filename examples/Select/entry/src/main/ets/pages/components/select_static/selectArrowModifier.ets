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
'use static'
import { Entry, Text, Column, Component, Button, ClickEvent, Select, TextModifier, TextAlign, Color,
  FontWeight, TextOverflow, $r, HorizontalAlign, ColumnOptions, Optional, SymbolGlyphModifier }
  from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Builder
export function SelectArrowModifierStaticBuilder(name: string, param: Object) {
  SelectArrowModifierStatic()
}
@Entry
@Component
struct SelectArrowModifierStatic {
  @State text: string = 'TTTTTTTTTT'.repeat(3);
  @State index: Int = 2;
  symbolGlyphModifier: SymbolGlyphModifier = new SymbolGlyphModifier();
  @State changeIndex: Int = 0;
  @State changeList: ( Optional<SymbolGlyphModifier> | undefined )[] = [
    this.symbolGlyphModifier,
    undefined,
    this.symbolGlyphModifier,
  ]

  aboutToAppear(): void {
    this.symbolGlyphModifier
      .fontSize(25)
      .fontColor([Color.Red])
  }

  build() {
    Column({ space: 20 } as ColumnOptions) {
      Text(`设置arrowModifier:`)
        .fontSize(16)
        .width('100%')
      Select([
        // $r('app.media.startIcon')需要替换为开发者所需的图像资源文件。
        { value: 'A very long option text that should be truncated nicely'.repeat(3),
          icon: $r('app.media.startIcon') },
        { value: 'Option B', icon: $r('app.media.startIcon') },
        { value: 'Option C', icon: $r('app.media.startIcon') },
        { value: 'Option D', icon: $r('app.media.startIcon') }
      ])
        .selected(this.index)
        .value(this.text)
        .arrowModifier(this.symbolGlyphModifier)
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
        // $r('app.media.startIcon')需要替换为开发者所需的图像资源文件。
        { value: 'A very long option text that should be truncated nicely'.repeat(3),
          icon: $r('app.media.startIcon') },
        { value: 'Option B', icon: $r('app.media.startIcon') },
        { value: 'Option C', icon: $r('app.media.startIcon') },
        { value: 'Option D', icon: $r('app.media.startIcon') }
      ])
        .selected(this.index)
        .value(this.text)
        .arrowModifier(undefined)
        .margin({ top: 20,left:30 })
        .borderRadius(12)
        .width(200)
        .padding(9)
        .backgroundColor(Color.White)
        .shadow({ radius: 10, color: '#888888', offsetX: 0, offsetY: 10 })
      Text(`动态延迟更新:`)
        .fontSize(16)
        .width('100%')
      Select([
        // $r('app.media.startIcon')需要替换为开发者所需的图像资源文件。
        { value: 'A very long option text that should be truncated nicely'.repeat(3),
          icon: $r('app.media.startIcon') },
        { value: 'Option B', icon: $r('app.media.startIcon') },
        { value: 'Option C', icon: $r('app.media.startIcon') },
        { value: 'Option D', icon: $r('app.media.startIcon') }
      ])
        .selected(this.index)
        .value(this.text)
        .arrowModifier(this.changeList[this.changeIndex])
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
