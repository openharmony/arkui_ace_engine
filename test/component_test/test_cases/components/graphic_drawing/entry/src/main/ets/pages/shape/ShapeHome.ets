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
struct ShapeFillHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({
          buttonName: 'ShapeAntiAlias',
          buttonUrl: 'pages/shape/ShapeAntiAliasSample'
        })
        CommonButton({
          buttonName: 'ShapeFill',
          buttonUrl: 'pages/shape/ShapeFillSample'
        })
        CommonButton({
          buttonName: 'ShapeFillOpacity',
          buttonUrl: 'pages/shape/ShapeFillOpacitySample'
        })
        CommonButton({
          buttonName: 'ShapeStrokeDashArray',
          buttonUrl: 'pages/shape/ShapeStrokeDashArraySample'
        })
        CommonButton({
          buttonName: 'ShapeStrokeDashOffset',
          buttonUrl: 'pages/shape/ShapeStrokeDashOffsetSample'
        })
        CommonButton({
          buttonName: 'ShapeStrokeLineCap',
          buttonUrl: 'pages/shape/ShapeStrokeLineCapSample'
        })
        CommonButton({
          buttonName: 'ShapeStrokeLineJoin',
          buttonUrl: 'pages/shape/ShapeStrokeLineJoinSample'
        })
        CommonButton({
          buttonName: 'ShapeMesh',
          buttonUrl: 'pages/shape/ShapeMeshSample'
        })
        CommonButton({
          buttonName: 'ShapeStrokeWidth',
          buttonUrl: 'pages/shape/ShapeStrokeWidthSample'
        })
        CommonButton({
          buttonName: 'ShapeStrokeOpacity',
          buttonUrl: 'pages/shape/ShapeStrokeOpacitySample'
        })
        CommonButton({
          buttonName: 'ShapeStrokeMiterLimit',
          buttonUrl: 'pages/shape/ShapeStrokeMiterLimitSample'
        })
        CommonButton({
          buttonName: 'ShapeViewPort',
          buttonUrl: 'pages/shape/ShapeViewPortSample'
        })
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}