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
struct Index10 {
  @State isShow: boolean = false;

  private scrollModeArr:ScrollSizeMode[] = [ScrollSizeMode.FOLLOW_DETENT, ScrollSizeMode.CONTINUOUS];
  private scrollModeArrStr:string[] = ['FOLLOW_DETENT', 'CONTINUOUS'];
  @State scrollModeIndex:number = 0;

  @Builder
  myBuilder() {
    Column() {
      Column(){
        Button('content area refresh timing: ' + this.scrollModeArrStr[this.scrollModeIndex])
          .fontSize(20)
          .margin({ bottom: 10 })
          .onClick(() => {
            this.scrollModeIndex = ++this.scrollModeIndex % this.scrollModeArr.length;
          })
      }.margin({ bottom: 10 })
      Column()
        .backgroundColor(Color.Blue)
        .height(200)
        .width('100%')
      Column()
        .backgroundColor(Color.Green)
        .height(200)
        .width('100%')
    }
  }


  build() {
    Column() {
      Button('BindSheet')
        .onClick(() => {
          this.isShow = true;
        })
        .bindSheet($$this.isShow, this.myBuilder(), {
          detents: [300, 600, 900],
          uiContext: this.getUIContext(),
          mode: SheetMode.OVERLAY,
          scrollSizeMode: this.scrollModeArr[this.scrollModeIndex],
          backgroundColor: Color.Orange,
          title: { title: 'Title', subtitle: 'Subtitle' }
        })
    }
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .height('100%')
  }
}