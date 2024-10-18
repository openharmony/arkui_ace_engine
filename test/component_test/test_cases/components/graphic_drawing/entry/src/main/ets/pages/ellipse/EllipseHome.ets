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
struct EllipseHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({
          buttonName: 'EllipseFill',
          buttonUrl: 'pages/ellipse/EllipseFillSample'
        })
        CommonButton({
          buttonName: 'EllipseStrokeDashArray',
          buttonUrl: 'pages/ellipse/EllipseStrokeDashArraySample'
        })
        CommonButton({
          buttonName: 'EllipseStrokeDashOffset',
          buttonUrl: 'pages/ellipse/EllipseStrokeDashOffsetSample'
        })
        CommonButton({
          buttonName: 'EllipseStrokeLineCap',
          buttonUrl: 'pages/ellipse/EllipseStrokeLineCapSample'
        })
        CommonButton({
          buttonName: 'EllipseStrokeOpacity',
          buttonUrl: 'pages/ellipse/EllipseStrokeOpacitySample'
        })
        CommonButton({
          buttonName: 'EllipseStrokeWidth',
          buttonUrl: 'pages/ellipse/EllipseStrokeWidthSample'
        })
        CommonButton({
          buttonName: 'EllipseAntiAlias',
          buttonUrl: 'pages/ellipse/EllipseAntiAliasSample'
        })
        CommonButton({
          buttonName: 'EllipseFillOpacity',
          buttonUrl: 'pages/ellipse/EllipseFillOpacitySample'
        })
        CommonButton({
          buttonName: 'EllipseStroke',
          buttonUrl: 'pages/ellipse/EllipseStrokeSample'
        })
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}