/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


 // xxx.ets

 /*
 Guide:
 1. build the plugin modlue refer to https://gitee.com/openharmony/applications_app_samples/tree/master/code/BasicFeature/Native/NdkXComponent
 2. Add libnativerender.so to entry/libs/arm64-v8a/libnativerender.so in your DevEco test project
 3. Use the framework-separation way to run the project
 */

interface XComponentContext {
  drawPattern(): void;
  getStatus(): XComponentContextStatus;
};

type XComponentContextStatus = {
  hasDraw: boolean,
  hasChangeColor: boolean,
};

@Entry
@Component
struct Index {
  private surfaceId : string ='';
  xcomponentController: XComponentController = new XComponentController();

  @State currentStatus: string = "init";
  private xComponentContext: XComponentContext | undefined = undefined;

  build() {
    Column() {
      Row() {
        Text('Native XComponent Sample')
          .fontSize('24fp')
          .fontWeight(500)
          .margin({
            left: 24,
            top: 12
          })
      }
      .margin({ top: 24 })
      .width('100%')
      .height(56)

      Column({ space: 10 }) {
        XComponent({
          type: XComponentType.SURFACE,
          controller: this.xcomponentController
        })
          .onLoad((xComponentContext) => {
            this.xComponentContext = xComponentContext as XComponentContext;
            this.currentStatus = "index";
          })
          .onDestroy(() => {
            console.log('onDestroy');
          })
          .id("xcomponent")

        Text(this.currentStatus)
          .fontSize('24fp')
          .fontWeight(500)
      }
      .onClick(() => {
        let hasChangeColor: boolean = false;
        if (this.xComponentContext && this.xComponentContext.getStatus()) {
          hasChangeColor = this.xComponentContext.getStatus().hasChangeColor;
        }
        if (hasChangeColor) {
          this.currentStatus = "change color";
        }
      })
      .margin({
        top: 27,
        left: 12,
        right: 12
      })
      .height('40%')
      .width('90%')

      Row() {
        Button('Draw Star')
          .fontSize('16fp')
          .fontWeight(500)
          .margin({ bottom: 24 })
          .onClick(() => {
            if (this.xComponentContext) {
              this.xComponentContext.drawPattern();
              let hasDraw: boolean = false;
              if (this.xComponentContext.getStatus()) {
                hasDraw = this.xComponentContext.getStatus().hasDraw;
              }
              if (hasDraw) {
                this.currentStatus = "draw star";
              }
            }
            this.xcomponentController.setXComponentSurfaceSize({surfaceWidth:960,surfaceHeight:540});
            this.surfaceId = this.xcomponentController.getXComponentSurfaceId();
            console.log("this.surfaceId : " + this.surfaceId);
          })
          .width('53.6%')
          .height(40)
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
      .alignItems(VerticalAlign.Bottom)
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
  }
}