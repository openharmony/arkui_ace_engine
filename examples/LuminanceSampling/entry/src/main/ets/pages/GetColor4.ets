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

import uiMaterial from '@ohos.arkui.uiMaterial';

import { UIContext, /*LuminanceSampler,*/OverlayManager,LuminanceSampler,UIInspector } from '@ohos.arkui.UIContext';
import { resourceManager } from '@kit.LocalizationKit';
import { LengthMetrics, LengthUnit } from '@kit.ArkUI';
import { Edges } from '@ohos.arkui.node';
import router from '@ohos.router';




@Entry
@Component
struct PagePicker {
  @State message: string = 'Hello World';
  @State arr: Color[] =
    [Color.White, Color.Black, Color.Blue, Color.Brown, Color.Green, Color.Orange, Color.Pink, Color.Gray];
  @State colorMode: ThemeColorMode = ThemeColorMode.SYSTEM;
  @State translate1: number = 0;
  @State myButtonWidthStr: string = '400px'
  @State myButtonWidth: number = 400
  @State myButtonHeightStr: string = '150px'
  @State myButtonHeight: number = 150
  @State myLuminanceSampler: LuminanceSampler | undefined = undefined
  @State myUIInspector: UIInspector | undefined = undefined
  @State isShow:boolean = true

  // getColorFromColorMode(color:ResourceColor, colorMode:ThemeColorMode): ResourceColor {
  //   if (colorMode == ThemeColorMode.SYSTEM) {
  //     return color;
  //   }
  //   // 从资源中读取对应模式的颜色
  // }


  build() {
    Row() {
      Stack() {
        Scroll() {
          // Column() {
          //   ForEach(this.arr, (item: Color) => {
          //     Column()
          //       .width('100%')
          //       .height(200)
          //       .backgroundColor(item)
          //   })
          //   ForEach(this.arr, (item: Color) => {
          //     Column()
          //       .width('100%')
          //       .height(200)
          //       .backgroundColor(item)
          //   })
          // }
          // .width('100%')

          Row() {
            ForEach(this.arr, (item: Color) => {
              Column()
                .width(200)
                .height('100%')
                .backgroundColor(item)
            })
            ForEach(this.arr, (item: Color) => {
              Column()
                .width(200)
                .height('100%')
                .backgroundColor(item)
            })
          }
          .height('100%')
        }
        .width('100%')
        .height('100%')
        .scrollable(ScrollDirection.Horizontal)

        Column() {
          Button('多处获取')
            .onClick(() => {
              //getLuminanceSampler可以在多处获取，且保证是同一个
              if (1) {
                console.info(" : dev --------- getLuminanceSampler可以在多处获取，且保证是同一个");
                let uiContext = this.getUIContext();
                let uniqueId = this.getUniqueId();
                let frameNode: FrameNode | null = uiContext.getFrameNodeByUniqueId(uniqueId);
                let targetId = frameNode?.getFirstChild()?.getUniqueId();
                console.info(" : dev --------- ", targetId);
                // 获取采样器
                let luminanceSampler = uiContext.getLuminanceSampler({ id: "muButton", componentId: targetId });

                // 设置采样配置
                let edges: Edges<LengthMetrics> = {
                  top: new LengthMetrics(20, LengthUnit.VP),
                  bottom: LengthMetrics.px(15),
                  left: LengthMetrics.vp(10),
                  right: LengthMetrics.fp(20)
                }

                let myFunc = (luminance: number) => {
                  console.info(" : dev myFunc ------ onBackgroundLuminanceChange: ", luminance)
                };
                let myFunc2 = (luminance: number) => {
                  console.info(" : dev myFunc2 ------ onBackgroundLuminanceChange: ", luminance)
                };
                // luminanceSampler?.onBackgroundLuminanceChange(myFunc)
                luminanceSampler?.onBackgroundLuminanceChange(myFunc2)

              }
            })
          Button('Get preLuminanceSampler')
            .onClick(() => {
              let uiContext = this.getUIContext();
              let uniqueId = this.getUniqueId();
              this.myLuminanceSampler = uiContext.getLuminanceSampler({ id: "muButton", componentId: uniqueId });
              this.myUIInspector = uiContext.getUIInspector();
            })
          Button('change show')
            .onClick(()=>{
              this.isShow=!this.isShow;
            })
          if(this.isShow){
            Button("asasd").id("muButton")
          }
          Button('use preLuminanceSampler')
            .onClick(()=> {
              console.info(" : use preLuminanceSampler 1")
              if(this.myLuminanceSampler==undefined){
                console.info(" : this.myLuminanceSampler==undefined")
              }
              this.myLuminanceSampler?.setBackgroundLuminanceSamplingConfigs({
                samplingInterval: 180,
                brightThreshold: 240,
                darkThreshold: 20,
                // region:edges
              })
              this.myLuminanceSampler?.offBackgroundLuminanceChange();
            })
          Button('update options')
            .onClick(()=> {
              this.myLuminanceSampler?.setBackgroundLuminanceSamplingConfigs({
                samplingInterval: 500,
                brightThreshold: 240,
                darkThreshold: 20,
                // region:edges
              })
            })
          Button('Get Luminance Sampler')
          // .backgroundColor(this.setColor)
            .margin({ bottom: 500 })
            .id("muButton")
            .width(this.myButtonWidthStr)
            .height(this.myButtonHeightStr)
            .onClick(() => {
              //可新增回调
              if (0) {
                console.info(" : dev --------- 可新增回调");
                let uiContext = this.getUIContext();
                let uniqueId = this.getUniqueId();
                let frameNode: FrameNode | null = uiContext.getFrameNodeByUniqueId(uniqueId);
                let targetId = frameNode?.getFirstChild()?.getUniqueId();
                console.info(" : dev --------- ", targetId);
                // 获取采样器
                let luminanceSampler = uiContext.getLuminanceSampler({ id: "muButton", componentId: targetId });

                // 设置采样配置
                let edges: Edges<LengthMetrics> = {
                  top: new LengthMetrics(20, LengthUnit.VP),
                  bottom: LengthMetrics.px(15),
                  left: LengthMetrics.vp(10),
                  right: LengthMetrics.fp(20)
                }

                let myFunc = (luminance: number) => {
                  console.info(" : dev myFunc ------ onBackgroundLuminanceChange: ", luminance)
                };
                let myFunc2 = (luminance: number) => {
                  console.info(" : dev myFunc2 ------ onBackgroundLuminanceChange: ", luminance)
                };
                // luminanceSampler?.onBackgroundLuminanceChange(undefined)
                luminanceSampler?.onBackgroundLuminanceChange(myFunc)
                luminanceSampler?.onBackgroundLuminanceChange(myFunc2)
              }
            })
        }
      }.width('100%')
      .height('100%')
      .alignContent(Alignment.Bottom)
    }
    .height('100%')
  }
}