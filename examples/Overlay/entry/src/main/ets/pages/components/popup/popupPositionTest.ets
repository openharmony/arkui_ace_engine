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
export function PopupPositionBuilder(name: string, param: Object) {
  PopupExample01()
}

class A {
  public static placementToString(index: number): ResourceStr {
    if (index == 0) {
      return '左'
    } else if (index == 1) {
      return '右'
    } else if (index == 2) {
      return '上'
    } else if (index == 3) {
      return '下'
    } else if (index == 4) {
      return '上左'
    } else if (index == 5) {
      return '上右'
    } else if (index == 6) {
      return '下左'
    } else if (index == 7) {
      return '下右'
    } else if (index == 8) {
      return '左上'
    } else if (index == 9) {
      return '左下'
    } else if (index == 10) {
      return '右上'
    } else if (index == 11) {
      return '右下'
    }
    return ''
  }
}

@Entry
@Component
struct PopupExample01 {
  pathStack: NavPathStack = new NavPathStack()
  @State plIndex: number = 0
  @State x: number = 0
  @State y: number = 0
  @State ch: number = 15
  @State isShow: boolean = false
  @State angle: number = 0
  @State rate: number = 1.0
  @State popupHeight: number = 100
  @State popupWidth: number = 100

  @State pl: Placement[] = [
    Placement.Left,
    Placement.Right,
    Placement.Top,
    Placement.Bottom,
    Placement.TopLeft,
    Placement.TopRight,
    Placement.BottomLeft,
    Placement.BottomRight,
    Placement.LeftTop,
    Placement.LeftBottom,
    Placement.RightTop,
    Placement.RightBottom
  ]

  @Builder popupBuilder () {
    Scroll() {
      Column() {
        Row({ space: 2 }) {
          Image($r('app.media.app_icon'))
            .width(24)
            .height(24)
            .margin({ left: -5 })
          Text('Custom Popup')
            .fontSize(10)
        }
        .width(this.popupWidth)
        .height(this.popupHeight)
        TextInput()
          .width(this.popupWidth)
      }
    }
  }

  build() {
    NavDestination() {
      Column() {
        Text('测试气泡不同placement下位置以及避让软键盘情况')
          .textAlign(TextAlign.Center)
          .fontSize(20)
        Row() {
          Button('左移')
            .onClick(()=>{
              this.x = this.x - this.ch
            })
          Button('右移')
            .onClick(()=>{
              this.x = this.x + this.ch
            })
          Button('上移')
            .onClick(()=>{
              this.y = this.y - this.ch
            })
          Button('下移')
            .onClick(()=>{
              this.y = this.y - this.ch
            })
        }
        Row() {
          Button('慢')
            .onClick(()=>{
              this.ch = 8
            })
          Button('正常')
            .onClick(()=>{
              this.ch = 15
            })
          Button('快')
            .onClick(()=>{
              this.ch = 30
            })
          Button('旋转90度')
            .onClick(()=>{
              this.angle = (this.angle + 90) % 360
            })
          Button('缩放变化')
            .onClick(()=>{
              this.rate = (this.rate + 0.2) % 1.8
            })
        }
        Row() {
          Button('小气泡')
            .onClick(()=>{
              this.popupHeight = 100
              this.popupWidth = 100
            })
          Button('中气泡')
            .onClick(()=>{
              this.popupHeight = 150
              this.popupWidth = 150
            })
          Button('大气泡')
            .onClick(()=>{
              this.popupHeight = 150
              this.popupWidth = 300
            })
        }
        Column() {
          TextInput()
          Text('控制弹窗弹出位置')
          Slider({
            value: this.plIndex,
            min: 0,
            max: 11,
            step: 1,
            style: SliderStyle.InSet
          })
            .padding(20)
            .width('75%')
            .showSteps(true)
            .showTips(true, A.placementToString(this.plIndex))
            .onChange((v: number) => {
              this.plIndex = v
            })
        }
        .width('100%')
        .height('50%')
        .justifyContent(FlexAlign.Center)

        Column() {
          Column() {
            Text('Click')
          }
          .position({x: this.x, y: this.y})
          .width('30%')
          .height('20%')
          .justifyContent(FlexAlign.Center)
          .border({ radius: 20 })
          .backgroundColor('#207245')
          .margin({ top: 5 })
          .rotate({ angle: this.angle })
          .scale({ x: this.rate, y: this.rate })
          .onClick(() => {
            this.isShow = !this.isShow
          })
          .bindPopup(this.isShow, {
            builder: this.popupBuilder(),
            placement: this.pl[this.plIndex],
            autoCancel: false,
            mask: false,
            followTransformOfTarget: true,
            keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,
            showInSubWindow: true,
            onStateChange: (e) => {
              if(!e.isVisible) {
                this.isShow = false
              }
            }
          })
        }
        .width('100%')
        .height('50%')
        .justifyContent(FlexAlign.Center)
      }
      .width('100%')
      .height('100%')
    }
    .title('popupPositionTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}