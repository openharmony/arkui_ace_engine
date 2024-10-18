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


import { CommonButton } from '../util/CommonButton';

@Entry
@Component
struct Index {
  aboutToAppear() {
  }

  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('graphic_drawing')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({ buttonName: 'Circle', buttonUrl: 'pages/circle/CircleHome' });
        CommonButton({ buttonName: 'Ellipse', buttonUrl: 'pages/ellipse/EllipseHome' });
        CommonButton({ buttonName: 'Line', buttonUrl: 'pages/line/LineHome' });
        CommonButton({ buttonName: 'Polyline', buttonUrl: 'pages/polyline/PolylineHome' });
        CommonButton({ buttonName: 'Polygon', buttonUrl: 'pages/polygon/PolygonHome' });
        CommonButton({ buttonName: 'Path', buttonUrl: 'pages/path/PathHome' });
        CommonButton({ buttonName: 'Rect', buttonUrl: 'pages/rect/RectHome' });
        CommonButton({ buttonName: 'Shape', buttonUrl: 'pages/shape/ShapeHome' });
        CommonButton({
          buttonName: 'CanvasRenderingContext2D',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasHome'
        })
        CommonButton({ buttonName: 'ImageBitmap', buttonUrl: 'pages/image_bitmap/ImageBitmapHome' })
        CommonButton({ buttonName: 'ImageData', buttonUrl: 'pages/image_data/ImageDataHome' })
        CommonButton({ buttonName: 'Matrix2D', buttonUrl: 'pages/matrix2D/Matrix2DHome' })
        CommonButton({ buttonName: 'OffscreenCanvas', buttonUrl: 'pages/offscreen_canvas/OffscreenCanvasHome' })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2D',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DHome'
        })
      }
      .padding('20vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}