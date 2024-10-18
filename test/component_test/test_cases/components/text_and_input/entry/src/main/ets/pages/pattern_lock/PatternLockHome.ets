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
struct PatternLockHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({
          buttonName: 'PatternLockSideLength',
          buttonUrl: 'pages/pattern_lock/PatternLockSideLengthSample'
        });
        CommonButton({
          buttonName: 'PatternLockCircleRadius',
          buttonUrl: 'pages/pattern_lock/PatternLockCircleRadiusSample'
        });
        CommonButton({
          buttonName: 'PatternLockRegularColor',
          buttonUrl: 'pages/pattern_lock/PatternLockRegularColorSample'
        });
        CommonButton({
          buttonName: 'PatternLockSelectedColor',
          buttonUrl: 'pages/pattern_lock/PatternLockSelectedColorSample'
        });
        CommonButton({
          buttonName: 'PatternLockActiveColor',
          buttonUrl: 'pages/pattern_lock/PatternLockActiveColorSample'
        });
        CommonButton({
          buttonName: 'PatternLockPathColor',
          buttonUrl: 'pages/pattern_lock/PatternLockPathColorSample'
        });
        CommonButton({
          buttonName: 'PatternLockPathStrokeWidth',
          buttonUrl: 'pages/pattern_lock/PatternLockPathStrokeWidthSample'
        });
        CommonButton({
          buttonName: 'PatternLockAutoReset',
          buttonUrl: 'pages/pattern_lock/PatternLockAutoResetSample'
        });

      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}