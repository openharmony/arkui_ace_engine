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

import { ThemeControl } from '@kit.ArkUI';

ThemeControl.setDefaultTheme(null);
// xxx.ets
//该示例实现了Slider组件通过样式Builder定制内容区。点击增加按钮，进度条会按照原Slider设置的步长增加，反之点减少按钮进度条会减少，并触发原组件的onChange事件。
interface interface1 {
  value?: number | undefined;
  min?: number | undefined;
  max?: number | undefined;
  step?: number | undefined;
}

@Builder
export function SliderLevel14Builder(name: string, param: Object) {
  Slider_Level1_4()
}

@Builder
function buildSlider(config: SliderConfiguration) {
  Row() {
    Column({ space: 30 }) {
      Progress({ value: config.value, total: config.max, type: ProgressType.Ring })
        .margin({ top: 20 })

      Button('增加')
        .onClick(() => {
          config.value = config.value + config.step
          config.triggerChange(config.value, SliderChangeMode.Click)
        })
        .width(100)
        .height(25)
        .fontSize(10)
        .key('Button1')
        .enabled(config.value < config.max)

      Button('减少')
        .onClick(() => {
          config.value = config.value - config.step
          config.triggerChange(config.value, SliderChangeMode.Click)
        })
        .width(100)
        .height(25)
        .fontSize(10)
        .key('Button2')
        .enabled(config.value > config.min)

      Slider({
        value: config.value,
        min: config.min,
        max: config.max,
        step: config.step,
      })
        .width(config.max)
        .visibility((config.contentModifier as MySliderStyle).showSlider ? Visibility.Visible : Visibility.Hidden)
        .showSteps(true)
        .onChange((value: number, mode: SliderChangeMode) => {
          config.triggerChange(value, mode)
        })
        .key('Slider1')
      Text('当前状态：' + ((config.contentModifier as MySliderStyle).sliderChangeMode == 0 ? 'Begin'
        : ((config.contentModifier as MySliderStyle).sliderChangeMode == 1 ? 'Moving'
          : ((config.contentModifier as MySliderStyle).sliderChangeMode == 2 ? 'End'
            : ((config.contentModifier as MySliderStyle).sliderChangeMode == 3 ? 'Click' : '无')))))
        .fontSize(10)
      Text('进度值：' + config.value)
        .fontSize(10)
      Text('最小值：' + config.min)
        .fontSize(10)
      Text('最大值：' + config.max)
        .fontSize(10)
      Text('步长：' + config.step)
        .fontSize(10)
    }
    .width('100%')

  }
  .width('100%')
}

@Builder
function buildSlider1(config: SliderConfiguration) {
}

class MySliderStyle implements ContentModifier<SliderConfiguration> {
  public showSlider: boolean = true
  public sliderChangeMode: number = 0

  constructor(showSlider: boolean, sliderChangeMode: number) {
    this.showSlider = showSlider
    this.sliderChangeMode = sliderChangeMode
  }

  applyContent(): WrappedBuilder<[SliderConfiguration]> {
    return wrapBuilder(buildSlider)
  }
}

class MySliderStyle1 implements ContentModifier<SliderConfiguration> {
  public showSlider: boolean = true
  public sliderChangeMode: number = 0

  constructor(showSlider: boolean, sliderChangeMode: number) {
    this.showSlider = showSlider
    this.sliderChangeMode = sliderChangeMode
  }

  applyContent(): WrappedBuilder<[SliderConfiguration]> {
    return wrapBuilder(buildSlider1)
  }
}

@Entry
@Component
struct Slider_Level1_4 {
  pathStack: NavPathStack = new NavPathStack()
  @State index: number = 0
  @State showSlider: boolean = true
  @State sliderChangeMode: number = 0
  @State value: number | undefined = undefined;
  @State checked1: boolean | undefined = undefined;
  // 配置滑动条的参数
  private testCase1: Array<interface1> = [
    {
      value: 20,
      min: 10,
      max: 110,
      step: 2,
    },
    {
      value: -10,
      min: 110,
      max: 10,
      step: 0.5,
    },
    {
      value: 10000,
      min: 10,
      max: 110,
      step: 20,
    },
    {
      value: 0.5,
      min: 10,
      max: 110,
      step: 0.5,
    },
    {
      value: 15.5,
      min: 10,
      max: 110,
      step: 2.5,
    },
    {
      value: 20,
      min: 10,
      max: 110,
      step: 10000000,
    },
    {
      value: undefined,
      min: undefined,
      max: undefined,
      step: undefined,
    },
    {
      value: 20,
      min: 10,
      max: 110,
      step: -5,
    },
    {
      value: 20,
      min: 0.1,
      max: 11.5,
      step: 2,
    },
    {
      value: 20,
      min: -100,
      max: -1,
      step: 2,
    }
  ]

  aboutToAppear(): void {
    this.value = this.testCase1[this.index].value
  }

  build() {
    NavDestination() {
      Column({ space: 8 }) {
        Divider()
        Row({ space: 2 }) {
          Text(`${this.index + 1}` + '/')
          Text(`${this.testCase1.length}`)
            .key(`totalTest1`)
          Text('Test++')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.index++
              if (this.index >= this.testCase1.length) {
                this.index = 0
              }
              this.value = this.testCase1[this.index].value
            })
          Text('Test--')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.index--
              if (this.index < 0) {
                this.index = this.testCase1.length - 1
              }
              this.value = this.testCase1[this.index].value
            })
        }

        Row({ space: 2 }) {
          Slider({
            value: this.value,
            min: this.testCase1[this.index].min,
            max: this.testCase1[this.index].max,
            step: this.testCase1[this.index].step
          })
            .showSteps(true)
            .onChange((value: number, mode: SliderChangeMode) => {
              this.value = value
              this.sliderChangeMode = mode
              console.info('【SliderLog】value:' + value + 'mode:' + mode.toString())
            })
            .contentModifier(new MySliderStyle(this.showSlider, this.sliderChangeMode))

        }

        Row({ space: 2 }) {
          Slider({
            value: this.value,
            min: this.testCase1[this.index].min,
            max: this.testCase1[this.index].max,
            step: this.testCase1[this.index].step
          })
            .showSteps(true)
            .contentModifier(new MySliderStyle1(this.showSlider, this.sliderChangeMode))
        }
      }.width('100%')
    }
    .title('SliderLevel14')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}