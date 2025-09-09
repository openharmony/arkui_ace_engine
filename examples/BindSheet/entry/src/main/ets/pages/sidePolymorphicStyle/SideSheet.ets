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
struct SheetTransitionExample {
  @State isShowBottom: boolean = false
  @State isShowSide: boolean = false
  @State sheetHeight: number = 300;
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16];

  @Builder
  bottomBuilder() {
    Column() {
      Text('Text\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\n***\nText')
      TextInput()
    }
    .width('100%')
    .height('auto')
  }

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
    }
    .width('100%')
    .height('auto')
  }

  build() {
    Column({space:3}) {
      Text($r('app.string.SideSheet1'))
        .fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('100%').height(50).backgroundColor('#2ebd82')

      Button('bindSheet-Bottom')
        .onClick(() => {
          this.isShowBottom = true
        })
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShowBottom, this.bottomBuilder(), {
          title: { title: 'BottomSheet', subtitle: 'no close button' },
          backgroundColor: Color.Grey,
          onWillAppear: () => {
            console.log('BottomSheet onWillAppear.')
          },
          onAppear: () => {
            console.log('BottomSheet onAppear.')
          },
          onWillDisappear: () => {
            console.log('BottomSheet onWillDisappear.')
          },
          onDisappear: () => {
            console.log('BottomSheet onDisappear.')
          },
          preferType: SheetType.BOTTOM,
          showClose: false,
          blurStyle: BlurStyle.Regular,
          maskColor: '#4bffc62d',
          enableOutsideInteractive: false,
          borderWidth: {start: LengthMetrics.vp(2)},
          borderColor: Color.Green,
          borderStyle: BorderStyle.Dashed,
          onHeightDidChange: (height: number)=>{
            console.log('BottomSheet height change:' + height)
          },
          onTypeDidChange: (data: SheetType) => {
            console.log('BottomSheet type change:' + data)
          },
        })

      Button('bindSheet-Side')
        .onClick(() => {
          this.isShowSide = true
        })
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShowSide, this.sideBuilder(), {
          title: { title: 'SideSheet', subtitle: 'has close button' },
          backgroundColor: Color.Grey,
          onWillAppear: () => {
            console.log('SideSheet onWillAppear.')
          },
          onAppear: () => {
            console.log('SideSheet onAppear.')
          },
          onWillDisappear: () => {
            console.log('SideSheet onWillDisappear.')
          },
          onDisappear: () => {
            console.log('SideSheet onDisappear.')
          },
          preferType: SheetType.SIDE,
          showClose: true,
          blurStyle: BlurStyle.Regular,
          maskColor: '#4bffc62d',
          enableOutsideInteractive: false,
          borderWidth: {start: LengthMetrics.vp(2)},
          borderColor: Color.Green,
          borderStyle: BorderStyle.Dashed,
          onHeightDidChange: (height: number)=>{
            console.log('SideSheet height change:' + height)
          },
          onTypeDidChange: (data: SheetType) => {
            console.log('SideSheet type change:' + data)
          },
        })
    }
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .height('100%')
  }
}