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

@Builder
export function PopupBuilderTestBuilder(name: string, param: Object) {
  PopupBuilderExample()
}

interface BubbleEvent {
  isVisible: boolean
}

interface BubbleOption {
  width?: Dimension
  popupColor?: Color | string | Resource | number
  radius?: Dimension
  shadow?: ShadowOptions | ShadowStyle
  placement?: Placement
  enableArrow?: boolean
  autoCancel?: boolean
  onStateChange?: (event: BubbleEvent) => void
  arrowOffset?: Length
  showInSubWindow?: boolean
  mask?: boolean
  targetSpace?: Length
  offset?: Position
  arrowWidth?: Dimension
  arrowHeight?: Dimension
  backgroundBlurStyle?: BlurStyle
  focusable?: boolean
  transition?: TransitionEffect
  arrowPointPosition?: ArrowPointPosition
}

interface KSBubbleOptions {
  src?: string | PixelMap | Resource
  title?: string
  textArr?: string[]
  duration?: number
  option?: BubbleOption
}

@Builder
export function KSBubbleStyle(title: string) {
  Column() {
    Text(title)
  }
}

class KSCustomBubbleOption {
  public option: CustomPopupOptions;

  constructor(window: CustomComponent, bubbleOptions: KSBubbleOptions) {
    this.option = {
      builder: KSBubbleStyle.bind(window, (bubbleOptions.title || '这是标题文字'))
    }
    this.option.width = bubbleOptions.option ? bubbleOptions.option.width: undefined
    this.option.popupColor = bubbleOptions.option ? bubbleOptions.option.popupColor : '#FFFFFF'
    this.option.radius = bubbleOptions.option ? bubbleOptions.option.radius: 4
    this.option.shadow = bubbleOptions.option ? bubbleOptions.option.shadow: ShadowStyle.OUTER_DEFAULT_MD
    this.option.placement = bubbleOptions.option ? bubbleOptions.option.placement: undefined
    this.option.targetSpace = bubbleOptions.option ? bubbleOptions.option.targetSpace: undefined
    this.option.backgroundBlurStyle = bubbleOptions.option ?
      bubbleOptions.option.backgroundBlurStyle: BlurStyle.BACKGROUND_ULTRA_THICK
    this.option.enableArrow = bubbleOptions.option ? bubbleOptions.option.enableArrow: true
    this.option.arrowOffset = bubbleOptions.option ? bubbleOptions.option.arrowOffset: undefined
    this.option.arrowPointPosition = bubbleOptions.option ? bubbleOptions.option.arrowPointPosition: undefined

    this.option.arrowWidth = bubbleOptions.option ? bubbleOptions.option.arrowWidth: undefined
    this.option.arrowHeight = bubbleOptions.option ? bubbleOptions.option.arrowHeight: undefined
    this.option.mask = bubbleOptions.option ? bubbleOptions.option.mask: false
    this.option.autoCancel = bubbleOptions.option ? bubbleOptions.option.autoCancel: true
    this.option.showInSubWindow = bubbleOptions.option ? bubbleOptions.option.showInSubWindow: false
    this.option.focusable = bubbleOptions.option ? bubbleOptions.option.focusable: true
    this.option.onStateChange = bubbleOptions.option ? bubbleOptions.option.onStateChange: undefined
  }
}

@Entry
@Component
struct PopupBuilderExample {
  pathStack: NavPathStack = new NavPathStack()
  @State customPopup: boolean = false
  title: string = ''
  message: string = ''
  options: KSCustomBubbleOption = new KSCustomBubbleOption(this, {
    title: 'this is a popup',
    duration: 5,
    option: {
      width: 200,
      popupColor: Color.Pink,
      radius: 20,
      shadow: {
        radius: 0
      },
      placement: Placement.Bottom,
      enableArrow: true,
      autoCancel: true,
      arrowOffset: 0,
      showInSubWindow: true,
      mask: false,
      targetSpace: 8,
      offset: {
        x: 0,
        y: 0,
      },
      arrowWidth: 16,
      arrowHeight: 8,
      backgroundBlurStyle: BlurStyle.NONE,
      focusable: true,
    }
  })

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Text(this.title)
          .fontSize(16)
          .fontColor(Color.White)
          .margin({
            left: 10,
            top: 5,
            bottom: 5
          })
        Text(this.message)
          .fontSize(14)
          .fontColor(Color.Gray)
          .margin({
            left: 10,
            bottom: 10
          })
        Button('点我弹出')
          .size({
            width: '90%',
            height: 36
          })
          .fontColor(Color.White)
          .backgroundColor(Color.Blue)
          .margin({ left: 16 })
          .onClick(() => {
            this.customPopup = !this.customPopup
            if (this.customPopup) {
              setTimeout(() => {
                this.customPopup = false
              }, 2000)
            }
          })
          .bindPopup(this.customPopup, this.options.option)
      }
      .width('80%')
      .height('15%')
      .margin({ top: 5, bottom: 5 })
      .backgroundColor(Color.Gray)
    }
    .title('PopupBuilderExample')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}