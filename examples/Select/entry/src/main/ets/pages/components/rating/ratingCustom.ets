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

class MyRatingStyle implements ContentModifier<RatingConfiguration> {
  public name: string = '';
  public style: number = 0;

  constructor(value1: string, value2: number) {
    this.name = value1;
    this.style = value2;
  }

  applyContent(): WrappedBuilder<[RatingConfiguration]> {
    return wrapBuilder(buildRating);
  }
}

@Builder
export function RatingCustomBuilder(name: string, param: Object) {
  RatingCustomExample()
}

@Builder
function buildRating(config: RatingConfiguration) {
  Column() {
    Row() {
      Circle({ width: 25, height: 25 })
        .fill(config.rating >= 0.4 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            if (config.stepSize == 0.5) {
              config.triggerChange(0.5);
              return
            }
            if (config.stepSize == 1) {
              config.triggerChange(1);
              return
            }
          }
        }).visibility(config.stars >= 1 ? Visibility.Visible : Visibility.Hidden)
      Circle({ width: 25, height: 25 })
        .fill(config.rating >= 0.9 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            config.triggerChange(1);
          }
        }).visibility(config.stars >= 1 ? Visibility.Visible : Visibility.Hidden)
      Circle({ width: 25, height: 25 })
        .fill(config.rating >= 1.4 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            if (config.stepSize == 0.5) {
              config.triggerChange(1.5);
              return
            }
            if (config.stepSize == 1) {
              config.triggerChange(2);
              return
            }
          }
        }).visibility(config.stars >= 2 ? Visibility.Visible : Visibility.Hidden).margin({ left: 10 })
      Circle({ width: 25, height: 25 })
        .fill(config.rating >= 1.9 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            config.triggerChange(2);
          }
        }).visibility(config.stars >= 2 ? Visibility.Visible : Visibility.Hidden)
      Circle({ width: 25, height: 25 })
        .fill(config.rating >= 2.4 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            if (config.stepSize == 0.5) {
              config.triggerChange(2.5);
              return
            }
            if (config.stepSize == 1) {
              config.triggerChange(3);
              return
            }
          }
        }).visibility(config.stars >= 3 ? Visibility.Visible : Visibility.Hidden).margin({ left: 10 })
      Circle({ width: 25, height: 25 })
        .fill(config.rating >= 2.9 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            config.triggerChange(3);
          }
        }).visibility(config.stars >= 3 ? Visibility.Visible : Visibility.Hidden)
      Circle({ width: 25, height: 25 })
        .fill(config.rating >= 3.4 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            if (config.stepSize == 0.5) {
              config.triggerChange(3.5);
              return
            }
            if (config.stepSize == 1) {
              config.triggerChange(4);
              return
            }
          }
        }).visibility(config.stars >= 4 ? Visibility.Visible : Visibility.Hidden).margin({ left: 10 })
      Circle({ width: 25, height: 25 })
        .fill(config.rating >= 3.9 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            config.triggerChange(4);
          }
        }).visibility(config.stars >= 4 ? Visibility.Visible : Visibility.Hidden)
      Circle({ width: 25, height: 25 })
        .fill(config.rating >= 4.4 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            if (config.stepSize == 0.5) {
              config.triggerChange(4.5);
              return
            }
            if (config.stepSize == 1) {
              config.triggerChange(5);
              return
            }
          }
        }).visibility(config.stars >= 5 ? Visibility.Visible : Visibility.Hidden).margin({ left: 10 })
      Circle({ width: 25, height: 25 })
        .fill(config.rating >= 4.9 ? Color.Black : Color.Red)
        .onClick((event: ClickEvent) => {
          if (!config.indicator) {
            config.triggerChange(5);
          }
        }).visibility(config.stars >= 5 ? Visibility.Visible : Visibility.Hidden)
    }

    Text('分值：' + config.rating)
  }
}

@Entry
@Component
struct RatingCustomExample {
  pathStack: NavPathStack = new NavPathStack()
  @State rating: number = 0;
  @State ratingIndicator: boolean = true;
  @State ratingStars: number = 0;
  @State ratingStepsize: number = 0.5;
  @State ratingEnabled: boolean = true;
  @State title: string = 'RatingCustom';

  build() {
    NavDestination() {
      Row() {
        Column() {
          Rating({
            rating: 0,
            indicator: this.ratingIndicator
          })
            .stepSize(this.ratingStepsize)
            .stars(this.ratingStars)
            .backgroundColor(Color.Transparent)
            .width('100%')
            .height(50)
            .onChange((value: number) => {
              console.info('Rating change is' + value);
              this.rating = value;
            })
            .contentModifier(new MyRatingStyle('hello', 3))
          Button(this.ratingIndicator ? 'ratingIndicator : true' : 'ratingIndicator : false')
            .onClick((event) => {
              if (this.ratingIndicator) {
                this.ratingIndicator = false;
              } else {
                this.ratingIndicator = true;
              }
            })
            .margin({ top: 5 })

          Button(this.ratingStars < 5 ? 'ratingStars + 1, ratingStars =' + this.ratingStars : 'ratingStars最大值为5')
            .onClick((event) => {
              if (this.ratingStars < 5) {
                this.ratingStars += 1;
              }
            })
            .margin({ top: 5 })

          Button(this.ratingStars > 0 ? 'ratingStars - 1, ratingStars =' + this.ratingStars :
            'ratingStars小于等于0时默认等于5')
            .onClick((event) => {
              if (this.ratingStars > 0) {
                this.ratingStars -= 1;
              }
            })
            .margin({ top: 5 })

          Button(this.ratingStepsize == 0.5 ? 'ratingStepsize : 0.5' : 'ratingStepsize : 1')
            .onClick((event) => {
              if (this.ratingStepsize == 0.5) {
                this.ratingStepsize = 1;
              } else {
                this.ratingStepsize = 0.5;
              }
            })
            .margin({ top: 5 })
        }
        .width('100%')
        .height('100%')
        .justifyContent(FlexAlign.Center)
      }
      .height('100%')
    }
    .title(this.title)
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}