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

import { FunctionAreaPlaceholder, StyleSelectBuilder, UserInteractiveTabBarBuilder } from "./UserFunctionArea"
import imageGeneration from '@ohos.arkui.intelligence.imageGeneration';
import { styleItem } from "./CanvasFramework"
import { PhotoSelect } from "./PhotoSelect";

@ComponentV2
export struct LandscapeSelectFuncArea {
  @Param @Require styles?: Array<imageGeneration.ImageStyle>;
  private tabBarDefaultBgColor: ResourceColor = 'rgba(0,0,0,0.05)'
  @Local tabBarStyleBgColor: ResourceColor = this.tabBarDefaultBgColor
  @Local styleItems: Array<styleItem> = []
  @Param @Require imageInfoArr: Array<imageGeneration.ImageItem>;
  @Param @Require imageMatrixArr: number[][];
  @Provider('functionAreaSelectedIndex') selectedIndex: number = 0
  aboutToAppear(): void {
    for (let i = 0; this.styles && i < this.styles?.length; ++i) {
      this.styleItems.push({ name: this.styles[i].name, resourceAddr: this.styles[i].icon})
    }
  }

  build() {
    Tabs({ index: this.selectedIndex }) {
      TabContent() {
        PhotoSelect({imageInfoArr: this.imageInfoArr, imageMatrixArr: this.imageMatrixArr })
      }
      .tabBar(UserInteractiveTabBarBuilder(0, '图像', $r('sys.symbol.style')))

      TabContent() {
        StyleSelectBuilder(this.styleItems)
      }
      .tabBar(UserInteractiveTabBarBuilder(1, '风格', $r('sys.meida.ohos_image_style')))

      TabContent() {
        FunctionAreaPlaceholder()
      }
      .tabBar(UserInteractiveTabBarBuilder(2, '比例', $r('sys.symbol.style')))

      TabContent() {
        FunctionAreaPlaceholder()
      }
      .tabBar(UserInteractiveTabBarBuilder(3, '清晰度', $r('sys.symbol.style')))
    }
    .barHeight(284)
    .scrollable(false)
    .vertical(true)
    .barPosition(BarPosition.End)
    .width(118)
    .height(386)
    .onChange((index: number) => {
      this.selectedIndex = index
    })
    .onAnimationStart((index: number, targetIndex: number, event: TabsAnimationEvent) => {
      if (index === targetIndex) {
        return
      }
      this.selectedIndex = targetIndex
    })
  }
}