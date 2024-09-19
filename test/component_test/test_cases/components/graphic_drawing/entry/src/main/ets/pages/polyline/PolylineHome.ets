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
struct PolylineHomeSample {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({
          buttonName: 'PolylinePoints',
          buttonUrl: 'pages/polyline/PolylinePointsSample'
        })
        CommonButton({
          buttonName: 'PolylineFill',
          buttonUrl: 'pages/polyline/PolylineFillSample'
        })

        CommonButton({
          buttonName: 'PolylineFillOpacity',
          buttonUrl: 'pages/polyline/PolylineFillOpacitySample'
        })

        CommonButton({
          buttonName: 'PolylineStroke',
          buttonUrl: 'pages/polyline/PolylineStrokeSample'
        })

        CommonButton({
          buttonName: 'PolylineStrokeDashArray',
          buttonUrl: 'pages/polyline/PolylineStrokeDashArraySample'
        })
        CommonButton({
          buttonName: 'PolylineStrokeDashOffset',
          buttonUrl: 'pages/polyline/PolylineStrokeDashOffsetSample'
        })
        CommonButton({
          buttonName: 'PolylineStrokeLineCap',
          buttonUrl: 'pages/polyline/PolylineStrokeLineCapSample'
        })

        CommonButton({
          buttonName: 'PolylineStrokeLineJoin',
          buttonUrl: 'pages/polyline/PolylineStrokeLineJoinSample'
        })
        CommonButton({
          buttonName: 'PolylineStrokeMiterLimit',
          buttonUrl: 'pages/polyline/PolylineStrokeMiterLimitSample'
        })
        CommonButton({
          buttonName: 'PolylineStrokeOpacity',
          buttonUrl: 'pages/polyline/PolylineStrokeOpacitySample'
        })
        CommonButton({
          buttonName: 'PolylineStrokeWidth',
          buttonUrl: 'pages/polyline/PolylineStrokeWidthSample'
        })
        CommonButton({
          buttonName: 'PolylineAntiAlias',
          buttonUrl: 'pages/polyline/PolylineAntiAliasSample'
        })
        CommonButton({
          buttonName: 'PolylineStrokeDashArray',
          buttonUrl: 'pages/polyline/PolylineStrokeDashArraySample'
        })
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}