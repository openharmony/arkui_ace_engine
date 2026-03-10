/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
struct SheetTransitionExample {
  @State isShow: boolean = false;
  @State sheetDidWidth: number = 0;

  @Builder
  myBuilder() {
    Column() {
      Button("change height")
        .margin(10)
        .fontSize(20)


      Button("Set Illegal height")
        .margin(10)
        .fontSize(20)


      Button("close modal 1")
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.isShow = false;
        })
    }
    .width('100%')
    .height('100%')
  }

  build() {
    Column() {
      Button("宽屏设备拉起半模态")
        .onClick(() => {
          this.isShow = true;
        })
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShow, this.myBuilder(), {
          backgroundColor: Color.Green,
          preferType: SheetType.SIDE,
          title: {title: 'ttttt', subtitle: 'sssss'},
          enableOutsideInteractive: true,
          onWidthDidChange: (value) => {
            console.info(`sheet width ${value}`)
            this.sheetDidWidth = value;
          },
          onWillAppear: () => {
            console.info("BindSheet onWillAppear.");
          },
          onAppear: () => {
            console.info("BindSheet onAppear.");
          },
          onWillDisappear: () => {
            console.info("BindSheet onWillDisappear.");
          },
          onDisappear: () => {
            console.info("BindSheet onDisappear.");
          }
        })
    }
    .justifyContent(FlexAlign.Center)
    .width(`calc(100% - ${this.sheetDidWidth}px)`)
    .height('100%')
    .backgroundColor(Color.Blue)
  }
}

