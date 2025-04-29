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
struct SliderHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({ buttonName: 'BlockBorderColor', buttonUrl: 'pages/slider/SliderBlockBorderColorSample' });
        CommonButton({ buttonName: 'BlockBorderWidth', buttonUrl: 'pages/slider/SliderBlockBorderWidthSample' });
        CommonButton({ buttonName: 'BlockColor', buttonUrl: 'pages/slider/SliderBlockColorSample' });
        CommonButton({ buttonName: 'BlockSize', buttonUrl: 'pages/slider/SliderBlockSizeSample' });
        CommonButton({ buttonName: 'BlockStyle', buttonUrl: 'pages/slider/SliderBlockStyleSample' });
        CommonButton({ buttonName: 'SelectedColor', buttonUrl: 'pages/slider/SliderSelectedColorSample' });
        CommonButton({ buttonName: 'ShowSteps', buttonUrl: 'pages/slider/SliderShowStepsSample' });
        CommonButton({ buttonName: 'ShowTips', buttonUrl: 'pages/slider/SliderShowTipsSample' });
        CommonButton({ buttonName: 'StepColor', buttonUrl: 'pages/slider/SliderStepColorSample' });
        CommonButton({ buttonName: 'StepSize', buttonUrl: 'pages/slider/SliderStepSizeSample' });
        CommonButton({ buttonName: 'TrackBorderRadius', buttonUrl: 'pages/slider/SliderTrackBorderRadiusSample' });
        CommonButton({ buttonName: 'TrackColor', buttonUrl: 'pages/slider/SliderTrackColorSample' });
        CommonButton({ buttonName: 'TrackThickness', buttonUrl: 'pages/slider/SliderTrackThicknessSample' });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}