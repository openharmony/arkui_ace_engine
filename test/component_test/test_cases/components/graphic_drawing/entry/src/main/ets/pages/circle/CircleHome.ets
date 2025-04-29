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

import { CommonButton } from '../../util/CommonButton'

@Entry
@Component
struct CircleHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({
          buttonName: 'CircleFill',
          buttonUrl: 'pages/circle/CircleFillSample'
        })
        CommonButton({
          buttonName: 'CircleFillOpacity',
          buttonUrl: 'pages/circle/CircleFillOpacitySample'
        })
        CommonButton({
          buttonName: 'CircleStroke',
          buttonUrl: 'pages/circle/CircleStrokeSample'
        })
        CommonButton({
          buttonName: 'CircleStrokeDashArray',
          buttonUrl: 'pages/circle/CircleStrokeDashArraySample'
        })
        CommonButton({
          buttonName: 'CircleStrokeDashOffset',
          buttonUrl: 'pages/circle/CircleStrokeDashOffsetSample'
        })
        CommonButton({
          buttonName: 'CircleStrokeLineCap',
          buttonUrl: 'pages/circle/CircleStrokeLineCapSample'
        })
        CommonButton({
          buttonName: 'CircleStrokeOpacity',
          buttonUrl: 'pages/circle/CircleStrokeOpacitySample'
        })
        CommonButton({
          buttonName: 'CircleStrokeWidth',
          buttonUrl: 'pages/circle/CircleStrokeWidthSample'
        })
        CommonButton({
          buttonName: 'CircleAntiAlias',
          buttonUrl: 'pages/circle/CircleAntiAliasSample'
        })
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}