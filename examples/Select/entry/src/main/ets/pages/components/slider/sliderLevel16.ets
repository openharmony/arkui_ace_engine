/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under * Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with * License.
 * You may obtain a copy of * License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed distributed under * License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See * License for * specific language governing permissions and
 * limitations under * License.
 */

@Builder
export function SliderLevel16Builder(name: string, param: Object) {
  SliderLevel16Example()
}

@Entry
@Component
struct SliderLevel16Example {
  pathStack: NavPathStack = new NavPathStack()
  @State sliderValue: number = 50
  @State sliderValue2: number = 30
  @State sliderValue3: number = 70
  @State sliderValue4: number = 20
  @State sliderValue5: number = 60

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 20 }) {
          Text('Slider 基础示例')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .width('100%')

          Text('默认滑块')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Slider({ value: this.sliderValue, min: 0, max: 100, step: 1 })
            .width('100%')
            .onChange((value: number) => {
              this.sliderValue = value
            })
          Text(`当前值: ${this.sliderValue}`)
            .fontSize(12)
            .fontColor(0x999999)

          Text('带步长')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Slider({ value: this.sliderValue2, min: 0, max: 100, step: 10 })
            .width('100%')
            .showSteps(true)
            .onChange((value: number) => {
              this.sliderValue2 = value
            })
          Text(`当前值: ${this.sliderValue2}`)
            .fontSize(12)
            .fontColor(0x999999)

          Text('不同样式')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Slider({ value: 50, min: 0, max: 100, step: 1, style: SliderStyle.OutSet })
              .width('100%')
            Slider({ value: 30, min: 0, max: 100, step: 1, style: SliderStyle.InSet })
              .width('100%')
          }

          Text('自定义颜色')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Slider({ value: this.sliderValue3, min: 0, max: 100, step: 1 })
            .width('100%')
            .blockColor(0x317aff)
            .trackColor(0xcccccc)
            .selectedColor(0x317aff)
            .onChange((value: number) => {
              this.sliderValue3 = value
            })

          Text('禁用状态')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Slider({ value: 50, min: 0, max: 100, step: 1 })
            .width('100%')
            .enabled(false)

          Text('不同方向')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Slider({ value: 60, min: 0, max: 100, step: 1, direction: Axis.Horizontal })
              .width('100%')
            Slider({ value: 40, min: 0, max: 100, step: 1, direction: Axis.Vertical })
              .height(200)
          }

          Text('带标签')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Row({ space: 10 }) {
              Text('音量:')
              Slider({ value: this.sliderValue4, min: 0, max: 100, step: 1 })
                .width('60%')
                .onChange((value: number) => {
                  this.sliderValue4 = value
                })
              Text(`${this.sliderValue4}%`)
            }
            Row({ space: 10 }) {
              Text('亮度:')
              Slider({ value: this.sliderValue5, min: 0, max: 100, step: 1 })
                .width('60%')
                .onChange((value: number) => {
                  this.sliderValue5 = value
                })
              Text(`${this.sliderValue5}%`)
            }
          }

          Text('不同尺寸')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Slider({ value: 50, min: 0, max: 100, step: 1 })
              .width('50%')
            Slider({ value: 30, min: 0, max: 100, step: 1 })
              .width('70%')
            Slider({ value: 70, min: 0, max: 100, step: 1 })
              .width('90%')
          }

          Text('显示步长')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Slider({ value: 40, min: 0, max: 100, step: 10 })
            .width('100%')
            .showSteps(true)

          Text('自定义滑块样式')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Slider({ value: 60, min: 0, max: 100, step: 1 })
            .width('100%')
            .blockSize({ width: 30, height: 30 })
            .blockColor(0xff6347)
        }
        .padding(20)
      }
    }
    .title('SliderLevel16')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
