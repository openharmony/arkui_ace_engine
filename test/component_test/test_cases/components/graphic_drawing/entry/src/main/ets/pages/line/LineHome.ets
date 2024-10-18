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
      Flex({
        direction: FlexDirection.Row, wrap: FlexWrap.Wrap
      }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({
          buttonName: 'LineStroke',
          buttonUrl: 'pages/line/LineStrokeSample'
        })
        CommonButton({
          buttonName: 'LineEndPoint',
          buttonUrl: 'pages/line/LineEndPointSample'
        })
        CommonButton({
          buttonName: 'LineStrokeDashOffset',
          buttonUrl: 'pages/line/LineStrokeDashOffsetSample'
        })
        CommonButton({
          buttonName: 'LineStrokeLineCap',
          buttonUrl: 'pages/line/LineStrokeLineCapSample'
        })
        CommonButton({
          buttonName: 'LineStrokeOpacity',
          buttonUrl: 'pages/line/LineStrokeOpacitySample'
        })
        CommonButton({
          buttonName: 'LineAntiAlias',
          buttonUrl: 'pages/line/LineAntiAliasSample'
        })
        CommonButton({
          buttonName: 'LineStartPoint',
          buttonUrl: 'pages/line/LineStartPointSample'
        })
        CommonButton({
          buttonName: 'LineStrokeWidth',
          buttonUrl: 'pages/line/LineStrokeWidthSample'
        })
        CommonButton({
          buttonName: 'LineStrokeDashArray',
          buttonUrl: 'pages/line/LineStrokeDashArraySample'
        })
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}