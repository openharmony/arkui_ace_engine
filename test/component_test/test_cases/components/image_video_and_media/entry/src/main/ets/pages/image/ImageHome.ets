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
import { CommonButton } from '../../util/CommonButton';


@Entry
@Component
struct ImageHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('ObservedHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({ buttonName: 'ImageAlt', buttonUrl: 'pages/image/ImageAltSample' })
        CommonButton({ buttonName: 'ImageAutoResize', buttonUrl: 'pages/image/ImageAutoResizeSample' })
        CommonButton({ buttonName: 'ImageColorFilter', buttonUrl: 'pages/image/ImageColorFilterSample' })
        CommonButton({ buttonName: 'ImageCopyOption', buttonUrl: 'pages/image/ImageCopyOptionSample' })
        CommonButton({ buttonName: 'ImageDraggable', buttonUrl: 'pages/image/ImageDraggableSample' })
        CommonButton({ buttonName: 'ImageEnableAnalyzer', buttonUrl: 'pages/image/ImageEnableAnalyzerSample' })
        CommonButton({ buttonName: 'ImageFillColor', buttonUrl: 'pages/image/ImageFillColorSample' })
        CommonButton({ buttonName: 'ImageFitOriginalSize', buttonUrl: 'pages/image/ImageFitOriginalSizeSample' })
        CommonButton({ buttonName: 'ImageInterpolation', buttonUrl: 'pages/image/ImageInterpolationSample' })
        CommonButton({ buttonName: 'ImageMatchTextDirection', buttonUrl: 'pages/image/ImageMatchTextDirectionSample' })
        CommonButton({ buttonName: 'ImageObjectFit', buttonUrl: 'pages/image/ImageObjectFitSample' })
        CommonButton({ buttonName: 'ImageObjectRepeat', buttonUrl: 'pages/image/ImageObjectRepeatSample' })
        CommonButton({ buttonName: 'ImageRenderMode', buttonUrl: 'pages/image/ImageRenderModeSample' })
        CommonButton({ buttonName: 'ImageResizable', buttonUrl: 'pages/image/ImageResizableSample' })
        CommonButton({ buttonName: 'ImageSourceSize', buttonUrl: 'pages/image/ImageSourceSizeSample' })
        CommonButton({ buttonName: 'ImageSynLoad', buttonUrl: 'pages/image/ImageSynLoadSample' })
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}

