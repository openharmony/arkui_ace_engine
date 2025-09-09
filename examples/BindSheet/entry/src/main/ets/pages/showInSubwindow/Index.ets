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
@Entry
@Component
struct SheetShowInSubwindow {
  @State isShowBottom: boolean = false
  @State isShowSide: boolean = false
  @State dragBar: boolean = true
  @State sheetHeight: number = 300;

  @Builder
  bottomBuilder() {
    Column() {
      Text('Text\n***\n***\nText')
      TextInput()
    }
    .width('100%')
    .height('auto')
  }

  build() {
    Column({space:3}) {
      Text('PC realtime follow')
        .fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
        .width('100%').height(50).backgroundColor('#2ebd82')

      Button('bindSheet-Center')
        .onClick(() => {
          this.isShowBottom = true
        })
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShowBottom, this.bottomBuilder(), {
          detents: [300, SheetSize.MEDIUM, SheetSize.LARGE],
          title: { title: 'CenterSheet', subtitle: 'realtime follow test' },
          onWillAppear: () => {
            console.log('CenterSheet onWillAppear.')
          },
          onAppear: () => {
            console.log('CenterSheet onAppear.')
          },
          onWillDisappear: () => {
            console.log('CenterSheet onWillDisappear.')
          },
          onDisappear: () => {
            console.log('CenterSheet onDisappear.')
          },
          showInSubWindow : true,
          onHeightDidChange: (height: number)=>{
            console.log('BottomSheet height change:' + height)
          },
          onTypeDidChange: (data: SheetType) => {
            console.log('BottomSheet type change:' + data)
          },
        })
    }
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .height('100%')
  }
}