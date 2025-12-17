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
  FontWeight, TextOverflow, $r, HorizontalAlign, ColumnOptions, Optional, FontStyle } from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Builder
export function SelectOptionTextModifierStaticBuilder(name: string, param: Object) {
  SelectOptionTextModifierStatic()
}

@Entry
@Component
struct SelectOptionTextModifier {
  @State text: string = 'TTTTTTTTTT'.repeat(3);
  @State index: Int = 2;
  optionTextModifier: TextModifier = new TextModifier();
  @State changeIndex: Int = 0;
  @State changeList: ( Optional<TextModifier> | undefined )[] = [
    this.optionTextModifier,
    undefined,
    this.optionTextModifier,
  ]
  aboutToAppear(): void {
    this.optionTextModifier
      .maxLines(1)
      .fontSize(24)
      .textAlign(TextAlign.Start)
      .fontColor(Color.Red)
      .fontWeight(FontWeight.Normal)
      .fontStyle(FontStyle.Italic)
      .width(200)
  }

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`只设置optionTextModifier:`)
        .fontSize(16)
        .width('100%')
      Select([
        { value: 'A very long option text that should be truncated nicely'.repeat(3),
          icon: $r('app.media.startIcon') },
        { value: 'Option B', icon: $r('app.media.startIcon') },
        { value: 'Option C', icon: $r('app.media.startIcon') },
        { value: 'Option D', icon: $r('app.media.startIcon') }
      ])
        .selected(this.index)
        .value(this.text)
        .optionTextModifier(this.optionTextModifier)
        .margin({ top: 20,left:30 })
        .borderRadius(12)
        .width(200)
        .padding(9)
        .backgroundColor(Color.White)
        .shadow({ radius: 10, color: '#888888', offsetX: 0, offsetY: 10 })
      Text(`同时设置optionFont和optionTextModifier:`)
        .fontSize(16)
        .width('100%')
      Select([
        { value: 'A very long option text that should be truncated nicely'.repeat(3),
          icon: $r('app.media.startIcon') },
        { value: 'Option B', icon: $r('app.media.startIcon') },
        { value: 'Option C', icon: $r('app.media.startIcon') },
        { value: 'Option D', icon: $r('app.media.startIcon') }
      ])
        .selected(this.index)
        .value(this.text)
        .optionFont({ size: 16, weight: 900 })
        .optionTextModifier(this.optionTextModifier)
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
        { value: 'A very long option text that should be truncated nicely'.repeat(3),
          icon: $r('app.media.startIcon') },
        { value: 'Option B', icon: $r('app.media.startIcon') },
        { value: 'Option C', icon: $r('app.media.startIcon') },
        { value: 'Option D', icon: $r('app.media.startIcon') }
      ])
        .selected(this.index)
        .value(this.text)
        .optionTextModifier(undefined)
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
        { value: 'A very long option text that should be truncated nicely'.repeat(3),
          icon: $r('app.media.startIcon') },
        { value: 'Option B', icon: $r('app.media.startIcon') },
        { value: 'Option C', icon: $r('app.media.startIcon') },
        { value: 'Option D', icon: $r('app.media.startIcon') }
      ])
        .selected(this.index)
        .value(this.text)
        .optionTextModifier(this.changeList[this.changeIndex])
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