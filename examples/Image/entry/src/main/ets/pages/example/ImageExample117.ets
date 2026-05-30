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

/**
 * 图片手势交互综合示例
 * 演示TapGesture、LongPressGesture、PanGesture、PinchGesture、RotationGesture在图片上的应用
 */
@Entry
@Component
struct ImageExample117 {
  @State offsetX: number = 0
  @State offsetY: number = 0
  @State scaleValue: number = 1.0
  @State rotationValue: number = 0
  @State imageIndex: number = 0
  @State gestureLog: string = ''
  @State isLongPressed: boolean = false
  @State brightness: number = 1.0

  private images: Resource[] = [
    $r('app.media.startIcon'),
    $r('app.media.background'),
    $r('app.media.foreground'),
    $r('app.media.heart'),
    $r('app.media.star')
  ]

  private maxLogSize: number = 8
  private logs: string[] = []

  addLog(message: string) {
    const time = new Date().toLocaleTimeString()
    this.logs.unshift(`[${time}] ${message}`)
    if (this.logs.length > this.maxLogSize) {
      this.logs.pop()
    }
    this.gestureLog = this.logs.join('\n')
  }

  resetTransform() {
    animateTo({ duration: 300, curve: Curve.EaseOut }, () => {
      this.offsetX = 0
      this.offsetY = 0
      this.scaleValue = 1.0
      this.rotationValue = 0
      this.brightness = 1.0
      this.isLongPressed = false
    })
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片手势交互综合示例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 })

        Text('双击缩放 | 长按高亮 | 拖动平移 | 双指缩放/旋转')
          .fontSize(13)
          .fontColor(0x999999)

        Stack() {
          Image(this.images[this.imageIndex])
            .width(260)
            .height(260)
            .objectFit(ImageFit.Cover)
            .borderRadius(12)
            .offset({ x: this.offsetX, y: this.offsetY })
            .scale({ x: this.scaleValue, y: this.scaleValue })
            .rotate({ angle: this.rotationValue })
            .brightness(this.brightness)
            .border({
              width: this.isLongPressed ? 3 : 0,
              color: 0xFFD700
            })
            .shadow({ radius: 10, color: 0x33000000, offsetX: 0, offsetY: 4 })
            .gesture(
              GestureGroup(GestureMode.Exclusive,
                TapGesture({ count: 2 })
                  .onAction(() => {
                    animateTo({ duration: 200 }, () => {
                      this.scaleValue = this.scaleValue > 1.2 ? 1.0 : 1.5
                    })
                    this.addLog('双击: 缩放切换')
                  }),
                LongPressGesture({ fingers: 1, repeat: false, duration: 500 })
                  .onAction(() => {
                    this.isLongPressed = true
                    this.brightness = 1.3
                    this.addLog('长按: 高亮效果')
                  })
                  .onActionEnd(() => {
                    this.isLongPressed = false
                    this.brightness = 1.0
                  }),
                PanGesture({ fingers: 1, distance: 5 })
                  .onActionUpdate((event: GestureEvent) => {
                    this.offsetX = event.offsetX
                    this.offsetY = event.offsetY
                  })
                  .onActionEnd(() => {
                    this.addLog(`拖动结束: offset(${this.offsetX.toFixed(0)}, ${this.offsetY.toFixed(0)})`)
                  }),
                PinchGesture({ fingers: 2 })
                  .onActionUpdate((event: GestureEvent) => {
                    this.scaleValue = Math.max(0.3, Math.min(3.0, event.scale))
                  })
                  .onActionEnd(() => {
                    this.addLog(`捏合缩放: scale=${this.scaleValue.toFixed(2)}`)
                  }),
                RotationGesture({ fingers: 2 })
                  .onActionUpdate((event: GestureEvent) => {
                    this.rotationValue = event.angle
                  })
                  .onActionEnd(() => {
                    this.addLog(`旋转: angle=${this.rotationValue.toFixed(1)}°`)
                  })
              )
            )

          Text(`${this.scaleValue.toFixed(1)}x | ${this.rotationValue.toFixed(0)}°`)
            .fontSize(12)
            .fontColor(Color.White)
            .padding(4)
            .backgroundColor('rgba(0,0,0,0.6)')
            .borderRadius(4)
            .position({ x: 8, y: 8 })
        }
        .width(280)
        .height(280)
        .alignContent(Alignment.Center)

        Column({ space: 8 }) {
          Text('图片切换:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row({ space: 10 }) {
            Button('上一张')
              .onClick(() => {
                this.resetTransform()
                this.imageIndex = (this.imageIndex - 1 + this.images.length) % this.images.length
                this.addLog('切换: 上一张')
              })
            Button('下一张')
              .onClick(() => {
                this.resetTransform()
                this.imageIndex = (this.imageIndex + 1) % this.images.length
                this.addLog('切换: 下一张')
              })
            Button('重置变换')
              .onClick(() => {
                this.resetTransform()
                this.addLog('重置: 所有变换')
              })
          }
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)

        Column({ space: 8 }) {
          Text('快速操作:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start }) {
            Button('放大1.5x')
              .fontSize(12)
              .margin(4)
              .onClick(() => {
                animateTo({ duration: 200 }, () => { this.scaleValue = 1.5 })
              })
            Button('缩小0.5x')
              .fontSize(12)
              .margin(4)
              .onClick(() => {
                animateTo({ duration: 200 }, () => { this.scaleValue = 0.5 })
              })
            Button('旋转90°')
              .fontSize(12)
              .margin(4)
              .onClick(() => {
                animateTo({ duration: 300 }, () => { this.rotationValue += 90 })
              })
            Button('翻转水平')
              .fontSize(12)
              .margin(4)
              .onClick(() => {
                animateTo({ duration: 300 }, () => { this.scaleValue *= -1 })
              })
          }
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)

        Column({ space: 5 }) {
          Text('手势日志:')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text(this.gestureLog || '暂无手势事件')
            .fontSize(11)
            .fontColor(0x333333)
            .lineHeight(18)
        }
        .width('100%')
        .padding(10)
        .backgroundColor(0xF5F5F5)
        .borderRadius(8)
        .alignItems(HorizontalAlign.Start)
        .minHeight(80)

        Column({ space: 5 }) {
          Text('手势说明:')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('• 双击: 切换缩放倍率')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• 长按: 触发高亮效果')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• 单指拖动: 平移图片')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• 双指捏合: 缩放图片')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• 双指旋转: 旋转图片')
            .fontSize(12)
            .fontColor(0x666666)
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }
}
