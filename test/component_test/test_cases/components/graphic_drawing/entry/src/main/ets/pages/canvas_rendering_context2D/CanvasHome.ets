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
struct CanvasRenderingContext2DHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({
          buttonName: 'CanvasRenderingContext2DImageBitmap',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DImageBitmapSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DFillStyle',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DFillStyleSample'
        });
        CommonButton({
          buttonName: 'CanvasRenderingContext2DLineWidth',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DLineWidthSample'
        });
        CommonButton({
          buttonName: 'CanvasRenderingContext2DStrokeStyle',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DStrokeStyleSample'
        });
        CommonButton({
          buttonName: 'CanvasRenderingContext2DLineCap',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DLineCapSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DLineJoin',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DLineJoinSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DFont',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DFontSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DTextAlign',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DTextAlignSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DTextBaselineCanvasTextBaseline',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DTextBaselineCanvasTextBaselineSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DGlobalAlpha',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DGlobalAlphaSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DLineDashOffset',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DLineDashOffsetSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DGlobalCompositeOperation',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DGlobalCompositeOperationSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DShadowBlur',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DShadowBlurSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DShadowColor',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DShadowColorSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DShadowOffsetX',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DShadowOffsetXSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DShadowOffsetY',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DShadowOffsetYSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DImageSmoothingEnabled',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DImageSmoothingEnabledSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DHeight',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DHeightSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DWidth',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DWidthSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DImageSmoothingQuality',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DImageSmoothingQualitySample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DDirection',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DDirectionSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DFilter',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DFilterSample'
        })
        CommonButton({
          buttonName: 'CanvasRenderingContext2DMiterLimit',
          buttonUrl: 'pages/canvas_rendering_context2D/CanvasRenderingContext2DMiterLimitSample'
        })
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}