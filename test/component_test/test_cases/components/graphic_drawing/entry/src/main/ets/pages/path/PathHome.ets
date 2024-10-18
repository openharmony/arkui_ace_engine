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
        CommonButton({ buttonName: 'PathCommands', buttonUrl: 'pages/path/PathCommandsSample' })
        CommonButton({ buttonName: 'PathFill', buttonUrl: 'pages/path/PathFillSample' })
        CommonButton({ buttonName: 'PathFillOpacity', buttonUrl: 'pages/path/PathFillOpacitySample' })
        CommonButton({ buttonName: 'PathStroke', buttonUrl: 'pages/path/PathStrokeSample' })
        CommonButton({ buttonName: 'PathStrokeDashArray', buttonUrl: 'pages/path/PathStrokeDashArraySample' })
        CommonButton({ buttonName: 'PathStrokeDashOffset', buttonUrl: 'pages/path/PathStrokeDashOffsetSample' })
        CommonButton({ buttonName: 'PathStrokeLineCap', buttonUrl: 'pages/path/PathStrokeLineCapSample' })
        CommonButton({ buttonName: 'PathStrokeMiterLimit', buttonUrl: 'pages/path/PathStrokeMiterLimitSample' })
        CommonButton({ buttonName: 'PathStrokeLineJoin', buttonUrl: 'pages/path/PathStrokeLineJoinSample' })
        CommonButton({ buttonName: 'PathStrokeOpacity', buttonUrl: 'pages/path/PathStrokeOpacitySample' })
        CommonButton({ buttonName: 'PathStrokeWidth', buttonUrl: 'pages/path/PathStrokeWidthSample' })
        CommonButton({ buttonName: 'PathAntiAlias', buttonUrl: 'pages/path/PathAntiAliasSample' })
      }.padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}