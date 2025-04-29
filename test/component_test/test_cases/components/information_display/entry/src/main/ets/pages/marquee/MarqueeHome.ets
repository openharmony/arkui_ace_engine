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
struct MarqueeHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('MarqueeHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({ buttonName: 'MarqueeAllowScale', buttonUrl: 'pages/marquee/MarqueeAllowScaleSample' });
        CommonButton({ buttonName: 'MarqueeFontColor', buttonUrl: 'pages/marquee/MarqueeFontColorSample' });
        CommonButton({ buttonName: 'MarqueeFontFamily', buttonUrl: 'pages/marquee/MarqueeFontFamilySample' });
        CommonButton({ buttonName: 'MarqueeFontSize', buttonUrl: 'pages/marquee/MarqueeFontSizeSample' });
        CommonButton({ buttonName: 'MarqueeFontWeight_one', buttonUrl: 'pages/marquee/MarqueeFontWeightSample_one' });
        CommonButton({ buttonName: 'MarqueeFontWeight_two', buttonUrl: 'pages/marquee/MarqueeFontWeightSample_two' });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}