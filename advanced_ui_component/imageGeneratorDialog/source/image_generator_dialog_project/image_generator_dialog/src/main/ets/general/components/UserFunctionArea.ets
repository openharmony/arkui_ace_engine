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

import { AIGenerateOptions } from "../utils/AIGenerateOptions";
import { styleItem } from "./CanvasFramework"

@Builder export function UserInteractiveTabBarBuilder(name: string) {
  UserInteractiveAreaTabBar({
    name: name
  })
}

class StyleSelectTabBarParams{
  name: string = '';
  icon: Resource = {bundleName: "", moduleName: "", id: 0};
  bgColor?: ResourceColor = 'rgba(0,0,0,0.05)';
}

@Builder export function StyleSelectTabBarBuilder(params: StyleSelectTabBarParams) {
  UserFunctionAreaTabBar({
    name: params.name,
    icon: params.icon,
    tabBarBgColor: params.bgColor
  })
}

@Builder export function StyleSelectBuilder(styleItems: Array<styleItem>) {
  StyleSelect({stylesArray: styleItems})
}

@ComponentV2
export struct FunctionAreaPlaceholder {
  build() {
    Column() {
      Column()
        .width('100%')
        .height('100%')
        .border({width: 0.5})
    }
    .width('100%')
    .height('100%')
    .padding({
      right: 14
    })
  }
}

// style select
@ComponentV2
struct UserFunctionAreaTabBar {
  @Param name: string = '__NA__'
  @Param icon?: Resource = undefined
  @Param tabBarBgColor: ResourceColor = 'rgba(0,0,0,0.05)';

  build() {
    Column() {
      Column() {
        Image(this.icon)
          .width(24)
          .height(24)
      }
      .padding(12)
      .width(48)
      .height(48)
      .margin({bottom: 4})
      .borderRadius(100)
      .backgroundColor(this.tabBarBgColor)
      Column() {
        Text(this.name)
          .fontFamily("HarmonyHeiTi")
          .fontColor("#000000")
          .fontSize(10)
          .fontWeight(500)
      }
      .height(10)
    }
  }
}

@ComponentV2
export struct StyleSelect {
  @Local curSelectedStyle: string | undefined = AIGenerateOptions.getInstance().style;
  @Param stylesArray: Array<styleItem> = [
    {
      name: '插画',
      resourceAddr: undefined
    },
    {
      name: '写实',
      resourceAddr: undefined
    },
    {
      name: '油画',
      resourceAddr: undefined
    },
    {
      name: '水彩',
      resourceAddr: undefined
    },
    {
      name: '线描',
      resourceAddr: undefined
    },
    {
      name: '动漫',
      resourceAddr: undefined
    },

  ]

  updateSelectIndex(newSelectedStyle: string) {
    if (this.curSelectedStyle === newSelectedStyle) {
      this.curSelectedStyle = undefined;
    } else {
      this.curSelectedStyle = newSelectedStyle;
    }
    AIGenerateOptions.getInstance().style = this.curSelectedStyle;
  }

  build() {
    Column() {
      Scroll() {
        Column({space: 12 }) {
          Repeat(this.stylesArray)
            .each((item) => {
              Column() {
                Stack() {
                  Image(item.item.resourceAddr)
                    .height(56)
                    .width(56)
                    .borderRadius(12)
                    .borderColor("#000000")
                    .linearGradient({
                      angle: 0,
                      colors: [["#000000", 0], ["#000000", 1]]
                    })
                  Column() {
                    Checkbox()
                      .select(this.curSelectedStyle === item.item.name)
                      .shape(CheckBoxShape.CIRCLE)
                      .onClick(() => {
                        let nameStr: string = ''
                        if (typeof(item.item.name) === 'string') {
                          nameStr = item.item.name
                        } else {
                          let hostContext = this.getUIContext().getHostContext()
                          if (hostContext) {
                            nameStr = hostContext.resourceManager.getStringSync(item.item.name.id)
                          }
                        }
                        this.updateSelectIndex(nameStr)
                      })
                      .height(16)
                      .width(16)
                      .unselectedColor(Color.Transparent)
                  }
                  Column() {
                    Column() {
                      Text(item.item.name)
                        .fontFamily("HarmonyHeiTi")
                        .fontColor("#FFFFFF")
                        .fontSize(12)
                        .fontWeight(500)
                        .lineHeight(14)
                        .textAlign(TextAlign.Center)
                    }
                    .width(48)
                    .height(16)
                  }
                  .padding({top: 36, bottom: 4})
                  .width('100%')
                  .height('100%')
                }
                .alignContent(Alignment.TopEnd)
              }
              .height(56)
              .width(56)
              .onClick(() => {
                let nameStr: string = ''
                if (typeof(item.item.name) === 'string') {
                  nameStr = item.item.name
                } else {
                  let hostContext = this.getUIContext().getHostContext()
                  if (hostContext) {
                    nameStr = hostContext.resourceManager.getStringSync(item.item.name.id)
                  }
                }
                this.updateSelectIndex(nameStr)
              })
            })
        }
      }
      .scrollBar(BarState.Off)
      .scrollable(ScrollDirection.Vertical)
      .height(260)
      .width(56)
    }
  }
}
// style select END

@ComponentV2
struct UserInteractiveAreaTabBar {
  @Param name: string = '__NA__'

  build() {
    Column() {
      Column() {
        Image('')
          .width(24)
          .height(24)
      }
      .padding(12)
      .width(48)
      .height(48)
      .margin({bottom: 4})
      .borderRadius(24)
      .backgroundColor('rgba(0,0,0,0.05)')
      Column() {
        Text(this.name)
          .fontFamily("HarmonyHeiTi")
          .fontColor("#000000")
          .fontSize(10)
          .fontWeight(500)
      }
      .height(10)
    }
  }
}