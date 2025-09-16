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
import { MyComponent } from './MyComponenet'

@Builder
export function PopupDoubleBorderBuilder(name: string, param: Object) {
  PopupDoubleBorder()
}

interface PopupOptions1 {
  outlineWidth?: Dimension;
  borderWidth?: Dimension;
  outlineLinearGradient?: PopupBorderLinearGradient;
  borderLinearGradient?: PopupBorderLinearGradient;
}

interface ButtonItem {
  value: string
  action: () => void
}

@Extend(Column)
function columnStyle() {
  .backgroundColor(Color.Pink)
  .width('100%')
  .padding(5)
  .borderWidth(1.0)
}

@Entry
@Component
struct PopupDoubleBorder {
  pathStack: NavPathStack = new NavPathStack()
  @State handlePopup: boolean = false
  @State index: number = 0

  private popupOptionMessageList: PopupOptions1[] = [
    {
      outlineWidth: 1,
      borderWidth: 1,
      outlineLinearGradient: {
        direction: GradientDirection.Top,
        colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
      },
      borderLinearGradient: {
        direction: GradientDirection.Bottom,
        colors: [[Color.Red, 0.0], [Color.Blue, 1.0]]
      }
    },
    {
      outlineWidth: 1,
      borderWidth: 1,
      outlineLinearGradient: undefined,
      borderLinearGradient: undefined
    },
    {
      outlineWidth: 1,
      borderWidth: 1,
      outlineLinearGradient: undefined,
      borderLinearGradient: {
        direction: GradientDirection.Bottom,
        colors: [[Color.Red, 0.0], [Color.Blue, 1.0]]
      }
    },
    {
      outlineWidth: 1,
      borderWidth: 1,
      outlineLinearGradient: {
        direction: GradientDirection.Top,
        colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
      },
      borderLinearGradient: undefined
    },
    {
      outlineWidth: 10,
      borderWidth: 1,
      outlineLinearGradient: {
        direction: GradientDirection.Top,
        colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
      },
      borderLinearGradient: {
        direction: GradientDirection.Bottom,
        colors: [[Color.Red, 0.0], [Color.Blue, 1.0]]
      }
    },
    {
      outlineWidth: 1,
      borderWidth: 10,
      outlineLinearGradient: {
        direction: GradientDirection.Top,
        colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
      },
      borderLinearGradient: {
        direction: GradientDirection.Bottom,
        colors: [[Color.Red, 0.0], [Color.Blue, 1.0]]
      }
    },
    {
      outlineWidth: 2,
      borderWidth: 2,
      outlineLinearGradient: {
        direction: GradientDirection.Top,
        colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
      },
      borderLinearGradient: {
        direction: GradientDirection.Bottom,
        colors: [[Color.Red, 0.0], [Color.Blue, 1.0]]
      }
    },
    {
      outlineWidth: 1,
      borderWidth: 1,
      outlineLinearGradient: {
        direction: GradientDirection.Right,
        colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
      },
      borderLinearGradient: {
        direction: GradientDirection.Left,
        colors: [[Color.Red, 0.0], [Color.Blue, 1.0]]
      }
    },
    {
      outlineWidth: 1,
      borderWidth: 1,
      outlineLinearGradient: {
        direction: GradientDirection.RightTop,
        colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
      },
      borderLinearGradient: {
        direction: GradientDirection.RightBottom,
        colors: [[Color.Red, 0.0], [Color.Blue, 1.0]]
      }
    },
    {
      outlineWidth: 1,
      borderWidth: 1,
      outlineLinearGradient: {
        direction: GradientDirection.Top,
        colors: [[Color.Red, 0.0], [Color.Blue, 1.0]]
      },
      borderLinearGradient: {
        direction: GradientDirection.Bottom,
        colors: [[Color.Red, 0.0], [Color.Blue, 1.0]]
      }
    },
    {
      outlineWidth: 1,
      borderWidth: 1,
      outlineLinearGradient: {
        direction: GradientDirection.Top,
        colors: [[Color.Orange, 0.0], [Color.Pink, 1.0]]
      },
      borderLinearGradient: {
        direction: GradientDirection.Bottom,
        colors: [[Color.Red, 0.0], [Color.Blue, 1.0]]
      }
    },
    {
      outlineWidth: 1,
      borderWidth: 1,
      outlineLinearGradient: {
        direction: GradientDirection.Top,
        colors: [[Color.Yellow, 0.5], [Color.Green, 0.5]]
      },
      borderLinearGradient: {
        direction: GradientDirection.Bottom,
        colors: [[Color.Red, 0.5], [Color.Blue, 0.5]]
      }
    },
    {
      outlineWidth: 2,
      borderWidth: 3,
      outlineLinearGradient: {
        direction: GradientDirection.RightBottom,
        colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
      },
      borderLinearGradient: {
        direction: GradientDirection.LeftBottom,
        colors: [[Color.Red, 0.0], [Color.Blue, 1.0]]
      }
    },
    {
      outlineWidth: 1,
      borderWidth: 1,
      outlineLinearGradient: {
        direction: GradientDirection.Top,
        colors: [[Color.Yellow, 0.3], [Color.Green, 0.7]]
      },
      borderLinearGradient: {
        direction: GradientDirection.Bottom,
        colors: [[Color.Red, 0.7], [Color.Blue, 0.3]]
      }
    },
    {
      outlineWidth: 10,
      borderWidth: 10,
      outlineLinearGradient: {
        direction: GradientDirection.Top,
        colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
      },
      borderLinearGradient: {
        direction: GradientDirection.Bottom,
        colors: [[Color.Red, 0.0], [Color.Blue, 1.0]]
      }
    },
  ]
  build() {
    NavDestination() {
      Column({ space: 5 })  {
        Text('切换测试参数：')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10 })
        Text('切换双描边参数：')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10 })

        Row({ space: 2 }) {
          Text(`${this.index + 1}` + '/')
            .fontSize(9)
            .fontColor(0xCCCCCC)
          Text(`${this.popupOptionMessageList.length}`)
            .fontSize(9)
            .fontColor(0xCCCCCC)
          MyComponent({
            title: 'Test+', func: () => {
              this.index++
              if (this.index == this.popupOptionMessageList.length) {
                this.index = 0
              }
            }
          })
          MyComponent({
            title: 'Test0+', func: () => {
              this.index--
              if (this.index <= -1) {
                this.index = this.popupOptionMessageList.length - 1
              }
            }
          })
        }

        Button('PopupOptions')
          .onClick(() => {
            this.handlePopup = !this.handlePopup
          })
          .bindPopup(this.handlePopup!!, {
            message: 'This is a popup with PopupOptions',
            autoCancel: false,
            mask: false,
            placement: Placement.Bottom,
            outlineWidth: this.popupOptionMessageList[this.index].outlineWidth,
            outlineLinearGradient: this.popupOptionMessageList[this.index].outlineLinearGradient,
            borderWidth: this.popupOptionMessageList[this.index].borderWidth,
            borderLinearGradient: this.popupOptionMessageList[this.index].borderLinearGradient
          })
          .position({ x: 100, y: 300 })
      }
      .width('100%')
      .height('100%')
      .padding(10)
    }
    .title('PopupDoubleBorder')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}