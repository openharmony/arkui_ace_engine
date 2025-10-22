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
struct SheetTransitionExampleCus {
  @State isShow: boolean = false;
  @State isEnableFloatingDragBar: boolean | undefined | null = false;
  @State isDrag: boolean = false;
  @State detent1: [number] | [SheetSize, number] | undefined = [SheetSize.MEDIUM, 600];

  @Builder
  myBuilder() {
    Column() {
      Button("change enableFloatingDragBar")
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.isEnableFloatingDragBar = !this.isEnableFloatingDragBar;
        })

      Button("change isDrag")
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.isDrag = !this.isDrag;
        })

      Button("close modal 1")
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.isShow = false;
        })
      Text(`isEnableFloatingDragBar: ${this.isEnableFloatingDragBar}`)
      Text(`isDrag: ${this.isDrag}`)
    }
    .width('100%')
    .height('100%').backgroundColor(Color.Orange)
  }

  @Builder titleBuildr() {
    Column() {
      Text('111111')
      Text('22222222')
      Text('33333')
      Text('4444')
      Text('55555')
      Text('66666')
      Text('7777')
      Text('88888')
      Text('99999999')
    }
    .height(200)
    .width(170)
    .backgroundColor(Color.Blue)
  }
  build() {
    Column() {
      Button("transition modal 1")
        .onClick(() => {
          this.isShow = true;
        })
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShow, this.myBuilder(), {
          height: SheetSize.LARGE,
          detents: [SheetSize.LARGE, 500],
          title: this.titleBuildr(),
          backgroundColor: Color.Green,
          dragBar: this.isDrag,
          enableFloatingDragBar: this.isEnableFloatingDragBar,
          onWillAppear: () => {
            console.log("cwc BindSheet onWillAppear.");
          },
          onAppear: () => {
            console.log("cwc BindSheet onAppear.");
          },
          onWillDisappear: () => {
            console.log("BindSheet onWillDisappear.");
          },
          onDisappear: () => {
            console.log("BindSheet onDisappear.");
          }
        })
    }
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .height('100%')
  }
}