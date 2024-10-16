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
import { RadioBlock, SliderBlock, useEnabled } from 'common';

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
  @State enableDirection: boolean = false;
  @State compDirection: Direction = Direction.Auto;

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
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
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
        .direction(useEnabled(this.enableDirection, this.compDirection))
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        SliderBlock({
          title: '当前评分为',
          isEnabled: this.enableRating,
          value: this.rating,
          min: 0,
          max: this.stars
        })

        RadioBlock({
          title: '是否作为指示器使用',
          isEnabled: this.enableIndicator,
          value: this.indicator,
          dataSource: [
            { label: '是：不可进行评分', value: true },
            { label: '否：可进行评分', value: false },
          ]
        })

        RadioBlock({
          title: '评分组件布局方式',
          isEnabled: this.enableDirection,
          value: this.compDirection,
          dataSource: [
            { label: '跟随系统默认布局', value: Direction.Auto },
            { label: '从右到左', value: Direction.Rtl },
            { label: '从左到右', value: Direction.Ltr }
          ]
        })

        SliderBlock({
          title: '评分总数',
          isEnabled: this.enableStars,
          value: this.stars,
          min: 0,
          max: 20
        })

        SliderBlock({
          title: '评分步长',
          isEnabled: this.enableStepSize,
          value: this.stepSize,
          min: 0.1,
          max: this.stars
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