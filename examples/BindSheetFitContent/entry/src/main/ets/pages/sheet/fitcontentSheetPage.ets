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

// xxx.ets
import { window } from '@kit.ArkUI';
@Entry
@Component
struct bindSheetExample {
  @State isShow: boolean = false;
  @State preferType: SheetType = SheetType.BOTTOM
  @State isShowType: boolean = false;
  @State sheetHeight: SheetSize|number|string = SheetSize.FIT_CONTENT
  @State isShowInSubWindow: boolean = false
  @State isenableOutsideInteractive: boolean = false
  context = this.getUIContext();
  @State windowHeight:number = 0;
  @State builderHeight: number|string = 'auto'
  @Builder
  myBuilder() {
    Column() {
      Row() {
        Image($r('app.media.ditu'))
          .width(50)
          .height(50)
          .padding(5)
        Text('地图')
          .padding(5)
      }
      .height(60)
      .width('90%')
      .justifyContent(FlexAlign.Start)
      .background(Color.White)
      Row() {
        Image($r('app.media.baiduditu'))
          .width(50)
          .height(50)
          .padding(5)

        Text('百度地图')
          .padding(5)
      }
      .background(Color.White)
      .margin(10)
      .height(60)
      .width('90%')
      .justifyContent(FlexAlign.Start)
    }
    .height(this.builderHeight)
  }

  build() {
    Scroll() {
      Column() {
      Text("windowClass height: " + this.windowHeight)
        .margin(10)
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Text('是否显示蒙层'+":"+this.isenableOutsideInteractive)
      Row() {
        Button("不显示蒙层")
          .onClick(() => {
            this.isenableOutsideInteractive = true;
          })
        Button("显示蒙层")
          .onClick(() => {
            this.isenableOutsideInteractive = false;
          })
      }
      Text('show in subwindow'+":"+this.isShowInSubWindow)
      Row() {
        Button("showInSubwindow is true")
          .onClick(() => {
            this.isShowInSubWindow = true;
          })
        Button("showInSubwindow is false")
          .onClick(() => {
            this.isShowInSubWindow = false;
          })
      }
      Text('change type'+":"+this.preferType)
      Row() {
        Button("BOTTOM")
          .onClick(() => {
            this.preferType = SheetType.BOTTOM;
          })
        Button("CENTER")
          .onClick(() => {
            this.preferType = SheetType.CENTER;
          })
        Button("POPUP")
          .onClick(() => {
            this.preferType = SheetType.POPUP;
          })
        Button("SIDE")
          .onClick(() => {
            this.preferType = SheetType.SIDE;
          })
        Button("CONTENT_COVER")
          .onClick(() => {
            this.preferType = SheetType.CONTENT_COVER;
          })
      }
      Text('change builder height'+":"+this.builderHeight)
        Row() {
          Button("内容区高度：auto")
            .onClick(() => {
              this.builderHeight = 'auto';
            })
          Button("内容区高度：200")
            .onClick(() => {
              this.builderHeight = '200';
            })
        }
      Text('change height'+":"+this.sheetHeight)
      Column() {
        Row() {
          Button("枚举类型：FIT_CONTENT")
            .onClick(() => {
              this.sheetHeight = SheetSize.FIT_CONTENT;
            })

          Button("枚举类型：MEDIUM")
            .onClick(() => {
              this.sheetHeight = SheetSize.MEDIUM;
            })

          Button("枚举类型：LARGE")
            .onClick(() => {
              this.sheetHeight = SheetSize.LARGE;
            })
        }
        Row() {
          Button("固定值：-100")
            .onClick(() => {
              this.sheetHeight = -100;
            })
          Button("固定值：0")
            .onClick(() => {
              this.sheetHeight = 0;
            })
          Button("固定值：150")
            .onClick(() => {
              this.sheetHeight = 200;
            })
          Button("固定值：200")
            .onClick(() => {
              this.sheetHeight = 200;
            })
          Button("固定值：400")
            .onClick(() => {
              this.sheetHeight = 400;
            })
          Button("固定值：600")
            .onClick(() => {
              this.sheetHeight = 600;
            })
          Button("固定值：900")
            .onClick(() => {
              this.sheetHeight = 900;
            })
          Button("固定值：99999")
            .onClick(() => {
              this.sheetHeight = 99999;
            })
        }
        Row() {
          Button("百分比：'5%'")
            .onClick(() => {
              this.sheetHeight = '5%';
            })
          Button("百分比：'15%'")
            .onClick(() => {
              this.sheetHeight = '15%';
            })
          Button("百分比：'60%'")
            .onClick(() => {
              this.sheetHeight = '60%';
            })
          Button("百分比：'70%'")
            .onClick(() => {
              this.sheetHeight = '70%';
            })
          Button("百分比：'199%'")
            .onClick(() => {
              this.sheetHeight = '199%';
            })
        }
      }
      Button("open sheet")
        .onClick(() => {
          this.isShow = true;
        })
        .fontSize(20)
        .margin(10)
        .bindSheet($$this.isShow, this.myBuilder(), {
          height: this.sheetHeight,
          enableOutsideInteractive:this.isenableOutsideInteractive,
          showClose: true,
          title: { title: "选择导航方式" },
          preferType: this.preferType,
          showInSubWindow:this.isShowInSubWindow,
        })
    }
    }
    .height('100%')
    .onAreaChange(() => {
      window.getLastWindow(this.context.getHostContext()).then((data) => {
        // get window attribute
        let properties = data?.getWindowProperties();
        this.windowHeight = px2vp(properties.windowRect.height)
        // Get window width and height
        console.log("windowClass width: " + properties.windowRect.width);
        console.log("this.windowHeight: " + this.windowHeight);
        console.log("windowClass height: " + properties.windowRect.height);
      });
    })
  }
}