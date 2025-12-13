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

import { FunctionAreaPlaceholder, StyleSelectBuilder, StyleSelectTabBarBuilder, UserInteractiveTabBarBuilder } from "./UserFunctionArea"
import imageGeneration from '@ohos.arkui.intelligence.imageGeneration';
import { styleItem } from "./CanvasFramework"

@ComponentV2
export struct LandscapeSelectFuncArea {
  @Local styles?: Array<imageGeneration.ImageStyle> = undefined
  private tabBarDefaultBgColor: ResourceColor = 'rgba(0,0,0,0.05)'
  @Local tabBarStyleBgColor: ResourceColor = this.tabBarDefaultBgColor
  @Local styleItems: Array<styleItem> = []

  aboutToAppear(): void {
    for (let i = 0; this.styles && i < this.styles?.length; ++i) {
      this.styleItems.push({ name: this.styles[i].name, resourceAddr: this.styles[i].icon})
    }
  }

  build() {
    Tabs() {
      TabContent() {
        FunctionAreaPlaceholder()
      }
      .tabBar(UserInteractiveTabBarBuilder('图像'))

      TabContent() {
        StyleSelectBuilder(this.styleItems)
      }
      .tabBar(StyleSelectTabBarBuilder({name: '风格', icon: {bundleName: "", moduleName: "", id: 0}, bgColor: this.tabBarStyleBgColor}))
      .onWillShow(()=>{
        this.tabBarStyleBgColor = Color.White
      })
      .onWillHide(()=>{
        this.tabBarStyleBgColor = this.tabBarDefaultBgColor
      })

      TabContent() {
        FunctionAreaPlaceholder()
      }
      .tabBar(UserInteractiveTabBarBuilder('比例'))

      TabContent() {
        FunctionAreaPlaceholder()
      }
      .tabBar(UserInteractiveTabBarBuilder('清晰度'))
    }
    .barHeight(284)
    .scrollable(false)
    .vertical(true)
    .barPosition(BarPosition.End)
    .width(118)
    .height(386)
  }
}