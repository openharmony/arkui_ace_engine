/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
export function ButtonLevel12Builder(name: string, param: Object) {
  ButtonLevel12Example()
}

@Entry
@Component
struct ButtonLevel12Example {
  pathStack: NavPathStack = new NavPathStack()
  @State buttonScale: number = 1.0
  @State buttonOpacity: number = 1.0
  @State isPressed: boolean = false
  @State showRipple: boolean = false

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 20 }) {
          Text('Button 动画效果示例')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .width('100%')

          Text('缩放动画按钮')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Button('点击缩放')
            .width(200)
            .height(50)
            .scale({ x: this.buttonScale, y: this.buttonScale })
            .onClick(() => {
              this.buttonScale = 0.95
              setTimeout(() => {
                this.buttonScale = 1.0
              }, 100)
            })

          Text('透明度动画按钮')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Button('点击淡入淡出')
            .width(200)
            .height(50)
            .opacity(this.buttonOpacity)
            .onClick(() => {
              this.buttonOpacity = 0.5
              setTimeout(() => {
                this.buttonOpacity = 1.0
              }, 200)
            })

          Text('按压状态按钮')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Button(this.isPressed ? '已按下' : '点击按压')
            .width(200)
            .height(50)
            .backgroundColor(this.isPressed ? 0x317aff : 0x999999)
            .stateEffect(true)
            .onClick(() => {
              this.isPressed = !this.isPressed
            })

          Text('波纹效果按钮')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Button('波纹效果')
            .width(200)
            .height(50)
            .stateEffect(true)
            .backgroundColor(0x317aff)

          Text('组合动画按钮')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Button('组合动画')
            .width(200)
            .height(50)
            .scale({ x: this.buttonScale, y: this.buttonScale })
            .opacity(this.buttonOpacity)
            .onClick(() => {
              this.buttonScale = 0.9
              this.buttonOpacity = 0.7
              setTimeout(() => {
                this.buttonScale = 1.0
                this.buttonOpacity = 1.0
              }, 150)
            })

          Text('不同状态按钮')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 10 }) {
            Button('正常')
              .stateStyles({
                normal: {
                  .backgroundColor(0x317aff)
                },
                pressed: {
                  .backgroundColor(0x2557e7)
                },
                disabled: {
                  .backgroundColor(0xcccccc)
                }
              })
            Button('禁用')
              .enabled(false)
              .stateStyles({
                normal: {
                  .backgroundColor(0x317aff)
                },
                disabled: {
                  .backgroundColor(0xcccccc)
                }
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)

          Text('渐变背景按钮')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Button('渐变按钮')
            .width(200)
            .height(50)
            .linearGradient({
              angle: 90,
              colors: [[0x317aff, 0.0], [0x00d4ff, 1.0]]
            })
            .fontColor(Color.White)

          Text('阴影效果按钮')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Button('阴影按钮')
            .width(200)
            .height(50)
            .backgroundColor(0x317aff)
            .shadow({
              radius: 10,
              color: 0x33000000,
              offsetX: 2,
              offsetY: 4
            })

          Text('圆角边框按钮')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Button('圆角边框')
            .width(200)
            .height(50)
            .backgroundColor(0x317aff)
            .borderRadius(25)
            .border({ width: 2, color: Color.White })

          Text('图标按钮')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Button() {
            Row({ space: 8 }) {
              Text('📧')
                .fontSize(20)
              Text('发送')
                .fontSize(16)
            }
          }
          .width(150)
          .height(50)
          .backgroundColor(0x317aff)
          .borderRadius(25)
        }
        .padding(20)
      }
    }
    .title('ButtonLevel12')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
