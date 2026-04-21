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

import { promptAction } from '@kit.ArkUI'

@Builder
export function ToastAnimationBuilder(name: string, param: Object) {
  ToastAnimationExample()
}

interface toastConfig {pos: Alignment, color: string}
interface toastConfig1 { blur: BlurStyle, color: string }

@Entry
@Component
struct ToastAnimationExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 12 }) {
        Text('Toast 动画测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .textAlign(TextAlign.Center)

        Divider()

        Text('淡入淡出动画')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Text('Toast 默认使用淡入淡出动画')
          .fontSize(12)
          .fontColor('#666666')
          .width('100%')

        Row({ space: 8 }) {
          Button('短淡入淡出')
            .layoutWeight(1)
            .onClick(() => {
              promptAction.showToast({
                message: '短动画',
                duration: 1500,
                backgroundColor: '#4CAF50',
                textColor: '#FFFFFF'
              })
            })

          Button('中淡入淡出')
            .layoutWeight(1)
            .onClick(() => {
              promptAction.showToast({
                message: '中动画',
                duration: 3000,
                backgroundColor: '#2196F3',
                textColor: '#FFFFFF'
              })
            })

          Button('长淡入淡出')
            .layoutWeight(1)
            .onClick(() => {
              promptAction.showToast({
                message: '长动画',
                duration: 5000,
                backgroundColor: '#FF9800',
                textColor: '#FFFFFF'
              })
            })
        }
        .width('100%')

        Divider()

        Text('快速切换动画')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Button('连续显示5个不同颜色')
          .width('100%')
          .onClick(() => {
            let colors = ['#F44336', '#4CAF50', '#2196F3', '#FF9800', '#9C27B0']
            colors.forEach((color, index) => {
              setTimeout(() => {
                promptAction.showToast({
                  message: `动画 ${index + 1}`,
                  duration: 2000,
                  backgroundColor: color,
                  textColor: '#FFFFFF'
                })
              }, index * 800)
            })
          })

        Button('快速显示10个')
          .width('100%')
          .onClick(() => {
            for (let i = 1; i <= 10; i++) {
              setTimeout(() => {
                promptAction.showToast({
                  message: `快速 ${i}`,
                  duration: 1500
                })
              }, i * 400)
            }
          })

        Divider()

        Text('位置动画测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Button('从上到下移动')
          .width('100%')
          .onClick(() => {
            let positions = [
              Alignment.Top,
              Alignment.Center,
              Alignment.Bottom
            ]
            positions.forEach((pos, index) => {
              setTimeout(() => {
                promptAction.showToast({
                  message: `位置 ${index + 1}`,
                  duration: 2000,
                  alignment: pos,
                  backgroundColor: '#2196F3',
                  textColor: '#FFFFFF'
                })
              }, index * 1500)
            })
          })

        Button('从左到右移动')
          .width('100%')
          .onClick(() => {
            let positions = [
              Alignment.Start,
              Alignment.Center,
              Alignment.End
            ]
            positions.forEach((pos, index) => {
              setTimeout(() => {
                promptAction.showToast({
                  message: `位置 ${index + 1}`,
                  duration: 2000,
                  alignment: pos,
                  backgroundColor: '#4CAF50',
                  textColor: '#FFFFFF'
                })
              }, index * 1500)
            })
          })

        Button('四角移动')
          .width('100%')
          .onClick(() => {
            let positions = [
              Alignment.TopStart,
              Alignment.TopEnd,
              Alignment.BottomStart,
              Alignment.BottomEnd
            ]
            positions.forEach((pos, index) => {
              setTimeout(() => {
                promptAction.showToast({
                  message: `角落 ${index + 1}`,
                  duration: 2000,
                  alignment: pos,
                  backgroundColor: '#FF9800',
                  textColor: '#FFFFFF'
                })
              }, index * 1500)
            })
          })

        Divider()

        Text('颜色渐变动画')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Button('红色渐变到绿色')
          .width('100%')
          .onClick(() => {
            let colors = ['#F44336', '#FF9800', '#4CAF50']
            colors.forEach((color, index) => {
              setTimeout(() => {
                promptAction.showToast({
                  message: `颜色 ${index + 1}`,
                  duration: 2000,
                  backgroundColor: color,
                  textColor: '#FFFFFF'
                })
              }, index * 1800)
            })
          })

        Button('彩虹渐变')
          .width('100%')
          .onClick(() => {
            let colors = ['#FF0000', '#FF7F00', '#FFFF00', '#00FF00', '#0000FF', '#4B0082', '#9400D3']
            colors.forEach((color, index) => {
              setTimeout(() => {
                promptAction.showToast({
                  message: `彩虹 ${index + 1}`,
                  duration: 2000,
                  backgroundColor: color,
                  textColor: '#FFFFFF'
                })
              }, index * 1800)
            })
          })

        Divider()

        Text('透明度动画')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Button('从透明到不透明')
          .width('100%')
          .onClick(() => {
            let opacities = ['#20000000', '#40000000', '#60000000', '#80000000', '#A0000000', '#C0000000', '#E0000000']
            opacities.forEach((opacity, index) => {
              setTimeout(() => {
                promptAction.showToast({
                  message: `透明度 ${index + 1}`,
                  duration: 2000,
                  backgroundColor: opacity,
                  textColor: '#FFFFFF'
                })
              }, index * 1800)
            })
          })

        Divider()

        Text('组合动画测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Button('位置+颜色组合')
          .width('100%')
          .onClick(() => {
            let configs: Array<toastConfig> = [
              { pos: Alignment.TopStart, color: '#F44336' },
              { pos: Alignment.Top, color: '#FF9800' },
              { pos: Alignment.TopEnd, color: '#FFEB3B' },
              { pos: Alignment.Center, color: '#4CAF50' },
              { pos: Alignment.BottomStart, color: '#2196F3' },
              { pos: Alignment.Bottom, color: '#9C27B0' },
              { pos: Alignment.BottomEnd, color: '#E91E63' }
            ]
            configs.forEach((config, index) => {
              setTimeout(() => {
                promptAction.showToast({
                  message: `组合 ${index + 1}`,
                  duration: 2000,
                  alignment: config.pos,
                  backgroundColor: config.color,
                  textColor: '#FFFFFF'
                })
              }, index * 1800)
            })
          })

        Button('模糊+颜色组合')
          .width('100%')
          .onClick(() => {
            let configs: Array<toastConfig1> = [
              { blur: BlurStyle.COMPONENT_ULTRA_THIN, color: '#80F44336' },
              { blur: BlurStyle.COMPONENT_THIN, color: '#804CAF50' },
              { blur: BlurStyle.COMPONENT_REGULAR, color: '#802196F3' },
              { blur: BlurStyle.COMPONENT_THICK, color: '#80FF9800' },
              { blur: BlurStyle.COMPONENT_ULTRA_THICK, color: '#809C27B0' }
            ]
            configs.forEach((config, index) => {
              setTimeout(() => {
                promptAction.showToast({
                  message: `模糊 ${index + 1}`,
                  duration: 2000,
                  backgroundBlurStyle: config.blur,
                  backgroundColor: config.color,
                  textColor: '#FFFFFF'
                })
              }, index * 1800)
            })
          })

        Divider()

        Text('动画性能测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Button('快速连续20个')
          .width('100%')
          .onClick(() => {
            for (let i = 1; i <= 20; i++) {
              setTimeout(() => {
                promptAction.showToast({
                  message: `性能 ${i}`,
                  duration: 1000
                })
              }, i * 200)
            }
          })

        Button('极快连续50个')
          .width('100%')
          .onClick(() => {
            for (let i = 1; i <= 50; i++) {
              setTimeout(() => {
                promptAction.showToast({
                  message: `#`,
                  duration: 800
                })
              }, i * 100)
            }
          })
      }
      .width('100%')
      .height('100%')
      .padding(12)
    }
    .title('Animation Test')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
