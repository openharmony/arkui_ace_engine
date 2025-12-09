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

import { promptAction } from "@kit.ArkUI"

@ComponentV2
export struct CanvasHome {
  @Local titleName: string = '灵感画布'

  @Builder
  homeTitleBuilder() {
    Column() {
      Row() {
        Row() {
          Text(this.titleName)
            .fontFamily("HarmonyHeiTi")
            .fontColor("#000000")
            .fontSize(20)
            .fontWeight(700)
        }
        .height('100%')
        .width('50%')
        .alignItems(VerticalAlign.Center)
        .justifyContent(FlexAlign.Start)

        Row() {
          Image('')
            .width(40)
            .height(40)
            .borderRadius(20)
            .backgroundColor('rgba(0,0,0,0.5)')
            .onClick(() => {
              promptAction.openToast({ message: 'full_screen clicked' })
                .then(() => {})
                .catch(() => {})
            })
            .margin({ right: 8 })

          Image('')
            .width(40)
            .height(40)
            .borderRadius(20)
            .backgroundColor('rgba(0,0,0,0.5)')
            .onClick(() => {
              promptAction.openToast({ message: 'x_icon clicked' })
                .then(() => {})
                .catch(() => {})
            })
        }
        .alignItems(VerticalAlign.Center)
        .justifyContent(FlexAlign.End)
        .height('100%')
        .width('50%')
      }
      .height(56)
      .width(618)
    }
    .height(64)
    .width('100%')
    .padding({
      left: 16,
      right: 16,
      top: 8
    })
  }

  build() {
    Navigation() {
      Column() {
        // doodle area
        Row() {
          // doodle board
          Column() {

          }
          .width(386)
          .height(386)
          .margin({
            left: 69,
            right: 54
          })
          .borderRadius(24)
          .borderWidth(2)
          .borderColor('#ffffff')
          .shadow({
            radius: 10,
          })
          // doodle function area
          Tabs() {
            TabContent() {
              FunctionAreaPlaceholder()
            }
            .tabBar(StyleSelectTabBarBuilder('图像'))

            TabContent() {
              FunctionAreaPlaceholder()
            }
            .tabBar(StyleSelectTabBarBuilder('风格'))

            TabContent() {
              FunctionAreaPlaceholder()
            }
            .tabBar(StyleSelectTabBarBuilder('比例'))

            TabContent() {
              FunctionAreaPlaceholder()
            }
            .tabBar(StyleSelectTabBarBuilder('清晰度'))
          }
          .barHeight(284)
          .scrollable(false)
          .vertical(true)
          .barPosition(BarPosition.End)
          .width(118)
          .height(386)
          .margin({
            right: 16
          })
        }
        .margin({
          top: 21,
          bottom: 28
        })
        // text input area
        Row() {
          Column()
            .height(40)
            .width(510)
            .margin({
              top: 3,
              bottom: 2,
              left: 16,
              right: 12
            })
            .borderRadius(31.11)
            .borderWidth(0.5)

          Column()
            .borderRadius(31.11)
            .borderWidth(0.5)
            .height(40)
            .width(96)
            .margin({
              top: 3,
              bottom: 2,
              right: 16
            })
        }
        .width('100%')
        .height(45)
        .margin({
          bottom: 14
        })
      }
      .height('100%')
      .width('100%')
    }
    .mode(NavigationMode.Stack)
    .titleMode(NavigationTitleMode.Mini)
    .hideBackButton(true)
    .title(this.homeTitleBuilder)
  }
}

@Component
struct FunctionAreaPlaceholder {
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

@Builder function StyleSelectTabBarBuilder(name: string) {
  UserFunctionAreaTabBar({
    name: name,
  })
}

// style select
@Component
struct UserFunctionAreaTabBar {
  name: string = '__NA__'

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