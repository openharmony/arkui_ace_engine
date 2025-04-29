/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import renderFitTest_one from '../MyTest/RenderFitTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RenderFitSample_one {
  @State widthOne: number = 100;
  @State heightTwo: number = 30;
  flag: boolean = true;
  @State renderFitOne: RenderFit = RenderFit.BOTTOM;
  @State renderFitTwo: RenderFit = RenderFit.LEFT;

  aboutToAppear(): void {
    loadComponentTestEntry(renderFitTest_one)
  }

  build() {
    Column() {
      Row() {
        Text("RenderFit")
          .width(this.widthOne)
          .height(this.heightTwo)
          .borderWidth(1)
          .textAlign(TextAlign.Start)
          .renderFit(RenderFit.CENTER)
          .margin(20)
          .id('textRenderFit1')
        Text("RenderFit")
          .width(this.widthOne)
          .height(this.heightTwo)
          .borderWidth(1)
          .textAlign(TextAlign.Start)
          .renderFit(RenderFit.TOP)
          .margin(20)
          .id('textRenderFit2')
      }

      Row() {
        Circle({ width: 3, height: 3 })
          .width(this.widthOne)
          .height(this.heightTwo)
          .borderWidth(1)
          .renderFit(this.renderFitOne)
          .margin(20)
          .id('circleRenderFit1')

        Circle({ width: 3, height: 3 })
          .width(this.widthOne)
          .height(this.heightTwo)
          .borderWidth(1)
          .renderFit(this.renderFitTwo)
          .margin(20)
          .id('circleRenderFit2')
      }

      Button('ButtonCircleRenderFit1')
        .onClick(() => {
          this.renderFitOne = RenderFit.RIGHT
        })
      Button('ButtonCircleRenderFit2')
        .onClick(() => {
          this.renderFitTwo = RenderFit.TOP_LEFT
        })
      Button("ButtonRenderFit3")
        .onClick(() => {
          animateTo({ curve: Curve.Ease }, () => {
            if (this.flag) {
              this.widthOne = 150;
              this.heightTwo = 50;
            } else {
              this.widthOne = 100;
              this.heightTwo = 30;
            }
            this.flag = !this.flag;
          })
        })
    }.width("100%").height("100%").alignItems(HorizontalAlign.Center)
  }
}