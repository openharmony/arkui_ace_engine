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
struct PathHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('PolygonHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({ buttonName: 'RectRadiusWidth', buttonUrl: 'pages/rect/RectRadiusWidthSample' })
        CommonButton({ buttonName: 'RectRadiusHeight', buttonUrl: 'pages/rect/RectRadiusHeightSample' })
        CommonButton({ buttonName: 'RectRadius', buttonUrl: 'pages/rect/RectRadiusSample' })
        CommonButton({ buttonName: 'RectFill', buttonUrl: 'pages/rect/RectFillSample' })
        CommonButton({ buttonName: 'RectFillOpacity', buttonUrl: 'pages/rect/RectFillOpacitySample' })
        CommonButton({ buttonName: 'RectStroke', buttonUrl: 'pages/rect/RectStrokeSample' })
        CommonButton({ buttonName: 'RectStrokeDashArray', buttonUrl: 'pages/rect/RectStrokeDashArraySample' })
        CommonButton({ buttonName: 'RectStrokeDashOffset', buttonUrl: 'pages/rect/RectStrokeDashOffsetSample' })
        CommonButton({ buttonName: 'RectStrokeLineCap', buttonUrl: 'pages/rect/RectStrokeLineCapSample' })
        CommonButton({ buttonName: 'RectStrokeOpacity', buttonUrl: 'pages/rect/RectStrokeOpacitySample' })
        CommonButton({ buttonName: 'RectStrokeLineJoin', buttonUrl: 'pages/rect/RectStrokeLineJoinSample' })
        CommonButton({ buttonName: 'RectStrokeWidth', buttonUrl: 'pages/rect/RectStrokeWidthSample' })
        CommonButton({ buttonName: 'RectAntiAlias', buttonUrl: 'pages/rect/RectAntiAliasSample' })
        CommonButton({ buttonName: 'RectStrokeMiterLimit', buttonUrl: 'pages/rect/RectStrokeMiterLimitSample' })
      }.padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}