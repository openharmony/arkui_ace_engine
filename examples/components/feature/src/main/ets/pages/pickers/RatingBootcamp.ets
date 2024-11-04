/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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


import { Drawer } from 'common/src/main/ets/components/Drawer';
import { ColorBlock, RadioBlock, SliderBlock, useEnabled } from 'common';

@Component
export struct RatingBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableRating: boolean = false;
  @State rating: number = 0;
  @State enableIndicator: boolean = false;
  @State indicator: boolean = false;
  @State enableStars: boolean = false;
  @State stars: number = 5;
  @State enableStepSize: boolean = false;
  @State stepSize: number = 0.5;
  @State enableStarStyle: boolean = false;
  @State compDirection: Direction = Direction.Auto;
  @State enableDirection: boolean = false;
  @State ratingWidth: number = 80;
  @State enableRatingWidth: boolean = false;
  @State ratingHeight: number = 50;
  @State enableRatingHeight: boolean = false;
  @State ratingEnabled: boolean = true;
  @State enableRatingEnabled: boolean = false;
  @State ratingBorderRadius: number = 1;
  @State enableRatingBorderRadius: boolean = false;
  @State ratingBorderColor: ResourceColor = Color.Black;
  @State enableRatingBorderColor: boolean = false;
  @State ratingBorderWidth: number = 1;
  @State enableRatingBorderWidth: boolean = false;
  @State ratingBorderStyle: BorderStyle = BorderStyle.Solid;
  @State enableRatingBorderStyle: boolean = false;
  @State ratingBackgroundColor: ResourceColor = Color.White;
  @State enableRatingBackgroundColor: boolean = false;
  @State ratingOpacity: number = 1;
  @State enableRatingOpacity: boolean = false;
  @State ratingVisibility: Visibility = Visibility.Visible;
  @State enableRatingVisibility: boolean = false;

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      Rating({
        rating: (useEnabled(this.enableRating, this.rating)),
        indicator: (useEnabled(this.enableIndicator, this.indicator)),
      })
        .stars(useEnabled(this.enableStars, this.stars))
        .stepSize(useEnabled(this.enableStepSize, this.stepSize))
        .onChange((value: number) => {
          this.rating = value;
        })
        .width(useEnabled(this.enableRatingWidth, this.ratingWidth))
        .height(useEnabled(this.enableRatingHeight, this.ratingHeight))
        .enabled(useEnabled(this.enableRatingEnabled, this.ratingEnabled))
        .borderRadius(useEnabled(this.enableRatingBorderRadius, this.ratingBorderRadius))
        .borderColor(useEnabled(this.enableRatingBorderColor, this.ratingBorderColor))
        .borderWidth(useEnabled(this.enableRatingBorderWidth, this.ratingBorderWidth))
        .borderStyle(useEnabled(this.enableRatingBorderStyle, this.ratingBorderStyle))
        .backgroundColor(useEnabled(this.enableRatingBackgroundColor, this.ratingBackgroundColor))
        .opacity(useEnabled(this.enableRatingOpacity, this.ratingOpacity))
        .visibility(useEnabled(this.enableRatingVisibility, this.ratingVisibility))
        .direction(useEnabled(this.enableDirection, this.compDirection))
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        SliderBlock({
          title: 'ratingAttribute.rating',
          isEnabled: this.enableRating,
          value: this.rating,
          min: 0,
          max: this.stars
        })

        RadioBlock({
          title: 'direction',
          isEnabled: this.enableDirection,
          value: this.compDirection,
          dataSource: [
            { label: 'Auto', value: Direction.Auto },
            { label: 'Rtl', value: Direction.Rtl },
            { label: 'Ltr', value: Direction.Ltr }
          ]
        })

        RadioBlock({
          title: 'ratingAttribute.indicator',
          isEnabled: this.enableIndicator,
          value: this.indicator,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        SliderBlock({
          title: 'stars',
          isEnabled: this.enableStars,
          value: this.stars,
          min: 0,
          max: 20
        })

        SliderBlock({
          title: 'stepSize',
          isEnabled: this.enableStepSize,
          value: this.stepSize,
          step: 0.5,
          min: 0,
          max: this.stars
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableRatingWidth,
          value: $ratingWidth,
          min: 60,
          max: 300
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableRatingHeight,
          value: $ratingHeight,
          min: 50,
          max: 80
        })

        RadioBlock({
          title: 'enabled',
          isEnabled: $enableRatingEnabled,
          value: $ratingEnabled,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        SliderBlock({
          title: 'borderWidth',
          isEnabled: $enableRatingBorderWidth,
          value: $ratingBorderWidth,
          min: 1,
          max: 5
        })

        SliderBlock({
          title: 'borderRadius',
          isEnabled: $enableRatingBorderRadius,
          value: $ratingBorderRadius,
          min: 0,
          max: 24
        })

        ColorBlock({
          title: 'borderColor',
          isEnabled: $enableRatingBorderColor,
          color: $ratingBorderColor
        })

        RadioBlock({
          title: 'borderStyle',
          isEnabled: $enableRatingBorderStyle,
          value: $ratingBorderStyle,
          dataSource: [
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
            { label: 'Solid', value: BorderStyle.Solid },
          ]
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableRatingBackgroundColor,
          color: $ratingBackgroundColor
        })

        SliderBlock({
          title: 'opacity',
          isEnabled: $enableRatingOpacity,
          value: $ratingOpacity,
          step: 0.1,
          min: 0,
          max: 1
        })

        RadioBlock({
          title: 'visibility',
          isEnabled: $enableRatingVisibility,
          value: $ratingVisibility,
          dataSource: [
            { label: 'Visible', value: Visibility.Visible },
            { label: 'Hidden', value: Visibility.Hidden },
          ]
        })

      }.width('100%')
    }
    .height('52%')
  }
}


@Preview
@Component
struct RatingBootcampPreviewer {
  build() {
    RatingBootcamp({
      title: '评分条/Rating'
    })
  }
}