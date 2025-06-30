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

@Builder
export function RatingLevel2Builder(name: string, param: Object) {
  RatingLevel2Example()
}

ThemeControl.setDefaultTheme(undefined);

interface exampleObject {
  rating?: number,
  indicator?: boolean,
  stars?: number,
  stepSize?: number,
}

class MyRatingStyle implements ContentModifier<RatingConfiguration> {
  public name: string = ''
  public style: number = 0

  constructor(value1: string, value2: number) {
    this.name = value1
    this.style = value2
  }

  applyContent(): WrappedBuilder<[RatingConfiguration]> {
    return wrapBuilder(buildRating)
  }
}

class MyRatingStyle1 implements ContentModifier<RatingConfiguration> {
  public name: string = ''
  public style: number = 0

  constructor(value1: string, value2: number) {
    this.name = value1
    this.style = value2
  }

  applyContent(): WrappedBuilder<[RatingConfiguration]> {
    return wrapBuilder(buildRating1)
  }
}

@Builder
function buildRating(config: RatingConfiguration) {
  Column({ space: 10 }) {
    Divider()
    Row({ space: 6 }) {
      Circle({ width: 25, height: 25 })
        .key('Circle001')
        .fill(config.rating >= 0.4 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            if (config.stepSize === 0.5) {
              config.triggerChange(0.5);
            }
            if (config.stepSize === 1) {
              config.triggerChange(1);
            }
          }
        }).visibility(config.stars >= 1 ? Visibility.Visible : Visibility.Hidden)
      Circle({ width: 25, height: 25 })
        .key('Circle002')
        .fill(config.rating >= 0.9 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            config.triggerChange(1);
          }
        }).visibility(config.stars >= 1 ? Visibility.Visible : Visibility.Hidden)
      Circle({ width: 25, height: 25 })
        .key('Circle003')
        .fill(config.rating >= 1.4 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            if (config.stepSize === 0.5) {
              config.triggerChange(1.5);
            }
            if (config.stepSize === 1) {
              config.triggerChange(2);
            }
          }
        }).visibility(config.stars >= 2 ? Visibility.Visible : Visibility.Hidden)
      Circle({ width: 25, height: 25 })
        .key('Circle004')
        .fill(config.rating >= 1.9 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            config.triggerChange(2);
          }
        }).visibility(config.stars >= 2 ? Visibility.Visible : Visibility.Hidden)
      Circle({ width: 25, height: 25 })
        .key('Circle005')
        .fill(config.rating >= 2.4 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            if (config.stepSize === 0.5) {
              config.triggerChange(2.5);
            }
            if (config.stepSize === 1) {
              config.triggerChange(3);
            }
          }
        }).visibility(config.stars >= 3 ? Visibility.Visible : Visibility.Hidden)

      Circle({ width: 25, height: 25 })
        .key('Circle006')
        .fill(config.rating >= 2.9 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            config.triggerChange(3);
          }
        }).visibility(config.stars >= 3 ? Visibility.Visible : Visibility.Hidden)
      Circle({ width: 25, height: 25 })
        .key('Circle007')
        .fill(config.rating >= 3.4 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            if (config.stepSize === 0.5) {
              config.triggerChange(3.5);
            }
            if (config.stepSize === 1) {
              config.triggerChange(4);
            }
          }
        }).visibility(config.stars >= 4 ? Visibility.Visible : Visibility.Hidden)
      Circle({ width: 25, height: 25 })
        .key('Circle008')
        .fill(config.rating >= 3.9 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            config.triggerChange(4);
          }
        }).visibility(config.stars >= 4 ? Visibility.Visible : Visibility.Hidden)
      Circle({ width: 25, height: 25 })
        .key('Circle009')
        .fill(config.rating >= 4.4 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            if (config.stepSize === 0.5) {
              config.triggerChange(4.5);
            }
            if (config.stepSize === 1) {
              config.triggerChange(5);
            }
          }
        }).visibility(config.stars >= 5 ? Visibility.Visible : Visibility.Hidden)
      Circle({ width: 25, height: 25 })
        .key('Circle010')
        .fill(config.rating >= 4.9 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            config.triggerChange(5);
          }
        }).visibility(config.stars >= 5 ? Visibility.Visible : Visibility.Hidden)
    }

    Text('分值：' + config.rating).key('Text001')
  }
}

@Builder
function buildRating1(config: RatingConfiguration) {
}

@Entry
@Component
struct RatingLevel2Example {
  pathStack: NavPathStack = new NavPathStack()
  @State index: number = 0;
  @State rating: number | undefined = 0;
  @State rating1: number | undefined = 0;
  private testCase: Array<exampleObject> = [
    {
      rating: -1,
      indicator: false,
      stars: -10,
      stepSize: -10,
    },
    {
      rating: 0,
      indicator: false,
      stars: 4,
      stepSize: 0.01,
    },
    {
      rating: 3.5,
      indicator: false,
      stars: 2,
      stepSize: 0.1,
    },
    {
      rating: 5,
      indicator: false,
      stars: 0,
      stepSize: 0.1,
    },
    {
      rating: 5,
      indicator: false,
      stars: 8,
      stepSize: 1,
    },
    {
      rating: 6.6,
      indicator: false,
      stars: 10.5,
      stepSize: 3.3,
    },
    {
      rating: 30,
      indicator: false,
      stars: 100,
      stepSize: 100,
    },
    {
      rating: 30,
      indicator: false,
      stars: 10,
      stepSize: 6,
    },
    {
      rating: 30,
      indicator: true,
      stars: 10,
      stepSize: 6,
    },
    {
      rating: undefined,
      indicator: undefined,
      stars: undefined,
      stepSize: undefined,
    },
    {
      rating: 10,
      indicator: false,
      stars: -10,
      stepSize: -10,
    },
    {
      rating: 5,
      indicator: false,
      stars: 0.4,

    },
    {
      rating: 0.4,
      indicator: false,
      stars: 5,
    },
    {
      rating: 0.4,
      indicator: true,
      stars: 5,
    },
  ]

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Divider()
        Row({ space: 4 }) {
          Text(`${this.index + 1}` + '/')
          Text(`${this.testCase.length}`)
            .key('rating00_cycles')
          Text('Test++')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              // 控制循环
              this.index++
              if (this.index == this.testCase.length) {
                this.index = 0
              }
              this.rating = this.testCase[this.index].rating
              this.rating1 = this.testCase[this.index].rating
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
              this.rating = this.testCase[this.index].rating
              this.rating1 = this.testCase[this.index].rating
            })
        }

        Rating({
          rating: this.rating,
          indicator: this.testCase[this.index].indicator
        })
          .stepSize(this.testCase[this.index].stepSize)
          .stars(this.testCase[this.index].stars)
          .backgroundColor(Color.Transparent)
          .width('100%')
          .height(150)
          .onChange((value: number) => {
            this.rating = value
            console.info('RatingModifier change is' + value)
          })
          .contentModifier(new MyRatingStyle('hello', 3))
        Rating({
          rating: this.rating1,
          indicator: this.testCase[this.index].indicator
        })
          .stepSize(this.testCase[this.index].stepSize)
          .stars(this.testCase[this.index].stars)
          .backgroundColor(Color.Transparent)
          .onChange((value: number) => {
            this.rating1 = value
            console.info('RatingModifier change is' + value)
          })
          .contentModifier(new MyRatingStyle1('hello', 3))

        Rating({
          rating: 1
        })
          .key('Rating0001')
          .contentModifier(undefined)
          .responseRegion({
            x: 0,
            y: 0,
            width: '60%',
            height: '100%'
          })
      }
    }
    .title('RatingLevel2')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}