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

import { Model1 } from '../base/DataModel';
import { ThemeControl } from '@kit.ArkUI';

@Builder
export function RatingLevel0Builder(name: string, param: Object) {
  RatingLevel0Example()
}

ThemeControl.setDefaultTheme(undefined);

declare interface exampleObject {
  rating?: number,
  indicator?: boolean,
  stars?: number,
  stepSize?: number,
  backgroundUri?: string,
  foregroundUri?: string,
  secondaryUri?: string
}

@Entry
@Component
struct RatingLevel0Example {
  pathStack: NavPathStack = new NavPathStack()
  @State model1: Model1 = new Model1()
  @State info?: string = undefined
  @State show: boolean = false
  @State hover: HoverEffect | undefined = undefined
  private index: number = 0
  private testCase: Array<exampleObject> = [
    {
      rating: -1,
      indicator: false,
      stars: -10,
      stepSize: -10,
      backgroundUri: 'hhh',
      foregroundUri: 'hhh',
      secondaryUri: 'hhh'
    },
    {
      rating: 0,
      indicator: false,
      stars: 4,
      stepSize: 0.01,
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png'
    },
    {
      rating: 3.5,
      indicator: false,
      stars: 2,
      stepSize: 0.1,
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png'
    },
    {
      rating: 5,
      indicator: false,
      stars: 0,
      stepSize: 0.1,
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png'
    },
    {
      rating: 5,
      indicator: false,
      stars: 8,
      stepSize: 1,
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png'
    },
    {
      rating: 6.6,
      indicator: false,
      stars: 10.5,
      stepSize: 3.3,
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png'
    },

    {
      rating: 0.4,
      indicator: false,
      stars: 5,
      backgroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      foregroundUri: '../../../../../../../AppScope/resources/base/media/app_icon.png',
      secondaryUri: '../../../../../../../AppScope/resources/base/media/app_icon.png'
    },
  ]

  private setParam(): void {
    this.model1.rating = this.testCase[this.index].rating
    this.model1.indicator = this.testCase[this.index].indicator
    this.model1.stars = this.testCase[this.index].stars
    this.model1.stepSize = this.testCase[this.index].stepSize
    this.model1.backgroundUri = this.testCase[this.index].backgroundUri
    this.model1.foregroundUri = this.testCase[this.index].foregroundUri
    this.model1.secondaryUri = this.testCase[this.index].secondaryUri
    this.info = 'Total: ' + this.testCase.length + ', CaseNumber: ' + this.index +
      '\nrating: ' + this.model1.rating + ', indicator: ' + this.model1.indicator +
      '\nstars: ' + this.model1.stars + ', stepSize: ' + this.model1.stepSize +
      '\nbackgroundUri: ' + this.model1.backgroundUri + ', foregroundUri: ' + this.model1.foregroundUri +
      ', secondaryUri: ' + this.model1.secondaryUri
  }

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Column({ space: 2 }) {
          Text('Rating组件 入参及属性事件测试')
            .fontSize(12)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ top: 10 })
          Text('Rating不传任何参数')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ top: 10 })
          Rating()
            .borderWidth(2)
            .key('rating1')
          Text('Rating不设置宽高')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ top: 10 })
          Rating({ rating: $$this.model1.rating, indicator: this.model1.indicator })
            .key('rating2')
            .margin({ top: 10 })
            .padding(10)
            .borderWidth(2)
            .borderColor(Color.Orange)
            .stars(this.model1.stars)
            .stepSize(this.model1.stepSize)
            .starStyle({
              backgroundUri: this.model1.backgroundUri,
              foregroundUri: this.model1.foregroundUri,
              secondaryUri: this.model1.secondaryUri
            })
            .onChange((value: number) => {
              console.log('hbx rating value is ' + value)
            })
          Text('Rating不设置宽高,与上面对比rating有无$$时的onChange')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ top: 10 })
          Rating({ rating: this.model1.rating, indicator: this.model1.indicator })
            .key('rating3')
            .stars(this.model1.stars)
            .margin({ top: 10 })
            .padding(10)
            .borderWidth(2)
            .borderColor(Color.Orange)
            .onChange((value: number) => {
              this.model1.rating = value
              console.log('hbx rating value is ' + value)
            })
            .hoverEffect(this.hover)
          Text('双向绑定rating: ' + this.model1.rating).margin({ top: 10 })
        }
        .width('100%')
        .height('40%')

        Divider().strokeWidth('1px')
        Text('切换参数，显示参数=' + this.show)
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .onClick(() => {
            this.show = !this.show
          })

        Row({ space: 2 }) {
          Text(`${this.testCase.length}`)
            .key('rating00_cycles')
          Text('Test++')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.setParam()
              // 控制循环
              this.index++
              if (this.index == this.testCase.length) {
                this.index = 0
              }
            })

          Text('Test--')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              // 控制循环
              this.index--
              if (this.index == -1) {
                this.index = this.testCase.length - 1
              }
              this.setParam()
            })
        }

        Text('HoverEffect验证')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
        Row({ space: 5 }) {
          Text('None')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.hover = HoverEffect.None
            })

          Text('Scale')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.hover = HoverEffect.Scale
            })

          Text('auto')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.hover = HoverEffect.Auto
            })
        }

        if (this.show) {
          Text(this.info)
        }
      }
      .borderWidth(2)
    }
    .title('RatingLevel0')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}