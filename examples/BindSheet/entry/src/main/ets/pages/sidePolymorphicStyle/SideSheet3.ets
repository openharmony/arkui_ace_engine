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
import { LengthMetrics } from '@kit.ArkUI';

@Entry
@Component
struct SheetTransitionExample1 {
  @State isShowSide: boolean = false
  @State enableOutsideInteractive: boolean = false
  @State borderWidths: LocalizedEdgeWidths | undefined = undefined
  @State borderColors: Resource | undefined = undefined
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16];

  @Builder
  sideBuilder() {
    Column() {
      ForEach(this.arr, (item: number) => {
        Row() {
          Text(item.toString())
            .width('80%')
            .height(60)
            .backgroundColor('#3366CC')
            .borderRadius(15)
            .fontSize(16)
            .textAlign(TextAlign.Center)
            .margin({ top: 5 })
        }
      }, (item: number) => item.toString())
      TextInput()
        .margin({ top: 5 })
      Text('changing the interaction mode of bindSheet')
        .fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('100%').height(50).backgroundColor('#2ebd82')
      Button('change enableOutsideInteractive = ' + this.enableOutsideInteractive)
        .margin({ top: 5 })
        .onClick(() => {
          this.enableOutsideInteractive = !this.enableOutsideInteractive
          if (this.enableOutsideInteractive) {
            this.borderWidths = {start : LengthMetrics.vp(1)};
            this.borderColors = $r('sys.color.comp_divider')
          } else {
            this.borderWidths = undefined;
            this.borderColors = undefined;
          }
        })
    }
    .width('100%')
    .height('auto')
  }


  build() {
    Column({space:3}) {
      Text($r('app.string.SideSheet5'))
        .fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('100%').height(50).backgroundColor('#2ebd82')
      Button('bindSheet-Side')
        .onClick(() => {
          this.isShowSide = true
        })
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShowSide, this.sideBuilder(), {
          title: { title: 'SideSheet', subtitle: 'default width' },
          backgroundColor: Color.Grey,
          onWillAppear: () => { 
            console.log('BindSheet onWillAppear.')
          },
          onAppear: () => { 
            console.log('BindSheet onAppear.')
          },
          onWillDisappear: () => { 
            console.log('BindSheet onWillDisappear.')
          },
          onDisappear: () => { 
            console.log('BindSheet onDisappear.')
          },
          preferType: SheetType.SIDE,
          blurStyle: BlurStyle.Regular,
          maskColor: '#4bffc62d',
          enableOutsideInteractive: this.enableOutsideInteractive,
          borderWidth: this.borderWidths,
          borderColor: this.borderColors,
          onHeightDidChange: (height: number)=>{
            console.log('height change:' + height)
          },
          onTypeDidChange: (data: SheetType) => {
            console.log('type change:' + data)
          },
        })
    }
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .height('100%')
  }
}