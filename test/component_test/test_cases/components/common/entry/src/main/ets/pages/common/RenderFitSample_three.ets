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
import renderFitTest_three from '../MyTest/RenderFitTest_three'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RenderFitSample_three {
  @State widthOne: number = 100;
  @State heightTwo: number = 30;
  flag: boolean = true;
  @State renderFitOne: RenderFit = RenderFit.RESIZE_COVER;

  aboutToAppear(): void {
    loadComponentTestEntry(renderFitTest_three)
  }

  build() {
    Column() {
      Row() {
        Polygon({ width: 100, height: 30 })
          .points([[0, 0], [30, 30], [100, 0]])
          .fill(Color.Green)
          .width(this.widthOne)
          .height(this.heightTwo)
          .borderWidth(1)
          .renderFit(RenderFit.RESIZE_CONTAIN_BOTTOM_RIGHT)
          .margin(20)
          .id('polygonRenderFit1')
        Polygon({ width: 100, height: 30 })
          .points([[0, 0], [30, 30], [100, 0]])
          .fill(Color.Green)
          .width(this.widthOne)
          .height(this.heightTwo)
          .borderWidth(1)
          .renderFit(this.renderFitOne)
          .margin(20)
          .id('polygonRenderFit2')
      }

      Button('ButtonPolygonRenderFit1')
        .onClick(() => {
          this.renderFitOne = RenderFit.RESIZE_COVER_TOP_LEFT
        })
      Button('ButtonPolygonRenderFit2')
        .onClick(() => {
          this.renderFitOne = RenderFit.RESIZE_COVER_BOTTOM_RIGHT
        })

      Button("ButtonPolygonRenderFit3")
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