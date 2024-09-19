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
struct OffScreenCanvasRenderingContext2DHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DFillStyleSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DFillStyleSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DLineWidthSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DLineWidthSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DStrokeStyleSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DStrokeStyleSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DLineCapSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DLineCapSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DLineJoinSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DLineJoinSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DMiterLimitSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DMiterLimitSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DFontSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DFontSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DTextAlignSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DTextAlignSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DTextBaselineSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DTextBaselineSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DGlobalAlphaSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DGlobalAlphaSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DLineDashOffsetSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DLineDashOffsetSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DGlobalCompositeOperationSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DGlobalCompositeOperationSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DShadowColorSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DShadowColorSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DShadowOffsetXSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DShadowOffsetXSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DShadowOffsetYSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DShadowOffsetYSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DImageSmoothingEnabledSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DImageSmoothingEnabledSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DImageSmoothingQualitySample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DImageSmoothingQualitySample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DDirectionSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DDirectionSample'
        })
        CommonButton({
          buttonName: 'OffscreenCanvasRenderingContext2DFilterSample',
          buttonUrl: 'pages/offscreen_canvas_rendering_context2D/OffscreenCanvasRenderingContext2DFilterSample'
        })
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}