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
export function PopupAnimateBuilder(name: string, param: Object) {
  PopupExample05()
}

@Extend(Text) function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Extend(Text) function componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3).padding(3)
  .borderWidth(1.0)
}

@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Entry
@Component
struct PopupExample05 {
  pathStack: NavPathStack = new NavPathStack()
  scoller: Scroller = new Scroller()
  @State handlePopup1: boolean = false
  @State popupOptions: PopupOptions = {
    showInSubWindow: true,
    mask: {
      color: '#99c1c8ac'
    },

    message: 'Popup message',
    primaryButton: {
      value: 'confirm',
      action: () => {
        this.handlePopup1 = !this.handlePopup1
        console.info('confirm Button click')
      }
    },
    // 第二个按钮
    secondaryButton: {
      value: 'cancel',
      action: () => {
        this.handlePopup1 = !this.handlePopup1
        console.info('cancel Button click')
      }
    },
    messageOptions: undefined,
    autoCancel: true,
    onWillDismiss: (e) => {
      if (e.reason == DismissReason.PRESS_BACK) {
        console.log('PRESS_BACK')
      } else if (e.reason == DismissReason.TOUCH_OUTSIDE) {
        console.log('TOUCH_OUTSIDE')
      }
      e.dismiss()
    },
    targetSpace: undefined,
    placement: undefined,
    offset: undefined,
    popupColor: '#ff6c9bd0',
    backgroundBlurStyle: BlurStyle.NONE,
    radius: undefined,
    shadow: { radius: 10, type: ShadowType.COLOR, color: '#4b3f35', offsetX: 30, offsetY: 30},

    enableArrow: true,
    arrowOffset:undefined,
    arrowPointPosition: undefined,
    arrowWidth: undefined,
    arrowHeight: undefined,

    transition: TransitionEffect.asymmetric(TransitionEffect.OPACITY
      .animation({ duration: 1000, curve: Curve.Smooth }),
      TransitionEffect.OPACITY.animation({ duration: 500, curve: Curve.Smooth })),

    onStateChange: (e) => {
      console.info(JSON.stringify(e.isVisible))
      if (!e.isVisible) {
        this.handlePopup1 = false
      }
    }
  }

  build() {
    NavDestination() {
      Scroll(this.scoller) {
        Column({ space: 3 }) {
          Text('气泡动效测试')
            .paramTextStyle()
          Column({space: 5}) {
            Text(`popup的show状态： ${this.handlePopup1}`)
              .paramTextStyle()
          }
          .columnStyle()
          Column({space: 5}) {
            Text(`normal popup`)
              .componentTextStyle()
              .bindPopup(this.handlePopup1!!, this.popupOptions)
              .onClick(()=>{
                this.handlePopup1 = !this.handlePopup1
              })
          }
          .columnStyle()
        }
        .width('100%')
      }
      .padding(12)
      .align(Alignment.TopStart)
      .width('100%')
      .height('100%')
    }
    .title('PopupAnimateTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}