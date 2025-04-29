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
import renderFitTest_two from '../MyTest/RenderFitTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RenderFitSample_two {
  @State widthOne: number = 100;
  @State heightTwo: number = 30;
  flag: boolean = true;
  @State renderFitOne: RenderFit = RenderFit.BOTTOM_RIGHT;
  @State renderFitTwo: RenderFit = RenderFit.RESIZE_FILL;

  aboutToAppear(): void {
    loadComponentTestEntry(renderFitTest_two)
  }

  build() {
    Column() {
      Row() {
        Ellipse({ width: 3, height: 2 })
          .width(this.widthOne)
          .height(this.heightTwo)
          .borderWidth(1)
          .renderFit(RenderFit.TOP_RIGHT)
          .margin(20)
          .id('ellipseRenderFit1')
        Ellipse({ width: 3, height: 2 })
          .width(this.widthOne)
          .height(this.heightTwo)
          .borderWidth(1)
          .renderFit(RenderFit.BOTTOM_LEFT)
          .margin(20)
          .id('ellipseRenderFit2')
      }

      Row() {
        Ellipse({ width: 3, height: 2 })
          .width(this.widthOne)
          .height(this.heightTwo)
          .borderWidth(1)
          .renderFit(this.renderFitOne)
          .margin(20)
          .id('ellipseRenderFit3')

        Ellipse({ width: 3, height: 2 })
          .width(this.widthOne)
          .height(this.heightTwo)
          .borderWidth(1)
          .renderFit(this.renderFitTwo)
          .margin(20)
          .id('ellipseRenderFit4')
      }

      Button('ButtonEllipseRenderFit1')
        .onClick(() => {
          this.renderFitOne = RenderFit.RESIZE_CONTAIN
        })
      Button('ButtonEllipseRenderFit2')
        .onClick(() => {
          this.renderFitTwo = RenderFit.RESIZE_CONTAIN_TOP_LEFT
        })
      Button("ButtonEllipseRenderFit3")
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