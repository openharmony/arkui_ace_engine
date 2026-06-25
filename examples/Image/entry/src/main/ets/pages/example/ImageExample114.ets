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
 * 图片动态切换与动画效果综合示例
 * 演示图片资源动态切换、contentTransition过渡动画、属性动画等效果
 */
@Entry
@Component
struct ImageExample114 {
  @State imageIndex: number = 0
  @State opacityValue: number = 1.0
  @State scaleValue: number = 1.0
  @State rotationValue: number = 0
  @State offsetValueX: number = 0
  @State offsetValueY: number = 0
  @State isTransitionEnabled: boolean = true
  @State animationDuration: number = 500

  private images: Resource[] = [
    $r('app.media.startIcon'),
    $r('app.media.background'),
    $r('app.media.foreground'),
    $r('app.media.svg'),
    $r('app.media.heart'),
    $r('app.media.star')
  ]

  private imageNames: string[] = [
    'startIcon', 'background', 'foreground', 'svg', 'heart', 'star'
  ]

  switchImage() {
    animateTo({ duration: this.animationDuration, curve: Curve.EaseInOut }, () => {
      this.imageIndex = (this.imageIndex + 1) % this.images.length
    })
  }

  resetAnimation() {
    animateTo({ duration: 300 }, () => {
      this.opacityValue = 1.0
      this.scaleValue = 1.0
      this.rotationValue = 0
      this.offsetValueX = 0
      this.offsetValueY = 0
    })
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片动态切换与动画效果示例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 })

        Stack() {
          Image(this.images[this.imageIndex])
            .width(250)
            .height(250)
            .objectFit(ImageFit.Cover)
            .borderRadius(12)
            .opacity(this.opacityValue)
            .scale({ x: this.scaleValue, y: this.scaleValue })
            .rotate({ angle: this.rotationValue })
            .offset({ x: this.offsetValueX, y: this.offsetValueY })
            .contentTransition(this.isTransitionEnabled ? ContentTransitionEffect.OPACITY : undefined)
            .shadow({ radius: 10, color: 0x33000000, offsetX: 0, offsetY: 4 })
            .onClick(() => {
              this.switchImage()
            })

          Text(`图片: ${this.imageNames[this.imageIndex]}`)
            .fontSize(14)
            .fontColor(Color.White)
            .padding(6)
            .backgroundColor('rgba(0,0,0,0.5)')
            .borderRadius(4)
            .position({ x: 10, y: 10 })
        }
        .width(250)
        .height(250)
        .alignContent(Alignment.Center)

        Text('点击图片切换下一张')
          .fontSize(13)
          .fontColor(0x999999)

        Column({ space: 10 }) {
          Text('图片切换:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row({ space: 8 }) {
            Button('上一张')
              .onClick(() => {
                animateTo({ duration: this.animationDuration }, () => {
                  this.imageIndex = (this.imageIndex - 1 + this.images.length) % this.images.length
                })
              })
            Button('下一张')
              .onClick(() => {
                this.switchImage()
              })
            Button('随机')
              .onClick(() => {
                animateTo({ duration: this.animationDuration }, () => {
                  this.imageIndex = Math.floor(Math.random() * this.images.length)
                })
              })
          }

          Row() {
            Text('过渡动画')
              .fontSize(14)
            Toggle({ type: ToggleType.Switch, isOn: this.isTransitionEnabled })
              .onChange((value: boolean) => {
                this.isTransitionEnabled = value
              })
              .margin({ left: 10 })
          }

          Row() {
            Text('动画时长')
              .width(70)
              .fontSize(14)
            Slider({ value: this.animationDuration, min: 100, max: 2000, step: 100 })
              .layoutWeight(1)
              .onChange((value: number) => {
                this.animationDuration = value
              })
            Text(`${this.animationDuration}ms`)
              .width(60)
              .fontSize(14)
              .textAlign(TextAlign.End)
          }
          .width('100%')
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)

        Column({ space: 10 }) {
          Text('属性动画控制:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row() {
            Text('透明度')
              .width(60)
              .fontSize(14)
            Slider({ value: this.opacityValue * 100, min: 0, max: 100, step: 5 })
              .layoutWeight(1)
              .onChange((value: number) => {
                animateTo({ duration: 300 }, () => {
                  this.opacityValue = value / 100
                })
              })
            Text(`${Math.floor(this.opacityValue * 100)}%`)
              .width(40)
              .fontSize(14)
              .textAlign(TextAlign.End)
          }

          Row() {
            Text('缩放')
              .width(60)
              .fontSize(14)
            Slider({ value: this.scaleValue, min: 0.1, max: 2.0, step: 0.1 })
              .layoutWeight(1)
              .onChange((value: number) => {
                animateTo({ duration: 300 }, () => {
                  this.scaleValue = value
                })
              })
            Text(`${this.scaleValue.toFixed(1)}x`)
              .width(40)
              .fontSize(14)
              .textAlign(TextAlign.End)
          }

          Row() {
            Text('旋转')
              .width(60)
              .fontSize(14)
            Slider({ value: this.rotationValue, min: 0, max: 360, step: 5 })
              .layoutWeight(1)
              .onChange((value: number) => {
                animateTo({ duration: 300 }, () => {
                  this.rotationValue = value
                })
              })
            Text(`${this.rotationValue}°`)
              .width(40)
              .fontSize(14)
              .textAlign(TextAlign.End)
          }

          Button('重置动画')
            .onClick(() => {
              this.resetAnimation()
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)

        Column({ space: 5 }) {
          Text('说明:')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('• contentTransition: 图片切换时的过渡动画效果')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• animateTo: 包裹状态变化实现属性动画')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• opacity/scale/rotate/offset: 图片属性动画参数')
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
