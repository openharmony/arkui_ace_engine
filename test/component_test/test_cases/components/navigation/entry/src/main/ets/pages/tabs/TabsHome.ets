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
struct TabsHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('Tabs')
          .padding('10vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({ buttonName: 'TabsAnimationDuration', buttonUrl: 'pages/tabs/TabsAnimationDurationSample' });
        CommonButton({
          buttonName: 'TabsBarBackgroundBlurStyle',
          buttonUrl: 'pages/tabs/TabsBarBackgroundBlurStyleSample'
        });
        CommonButton({ buttonName: 'TabsBarBackgroundColor', buttonUrl: 'pages/tabs/TabsBarBackgroundColorSample' });
        CommonButton({ buttonName: 'TabsBarGridAlign', buttonUrl: 'pages/tabs/TabsBarGridAlignSample' });
        CommonButton({ buttonName: 'TabsBarHeight', buttonUrl: 'pages/tabs/TabsBarHeightSample' });
        CommonButton({ buttonName: 'TabsBarMode', buttonUrl: 'pages/tabs/TabsBarModeSample' });
        CommonButton({ buttonName: 'TabsBarOverlap', buttonUrl: 'pages/tabs/TabsBarOverlapSample' });
        CommonButton({ buttonName: 'TabsBarWidth', buttonUrl: 'pages/tabs/TabsBarWidthSample' });
        CommonButton({ buttonName: 'TabsDivider', buttonUrl: 'pages/tabs/TabsDividerSample' });
        CommonButton({ buttonName: 'TabsFadingEdge', buttonUrl: 'pages/tabs/TabsFadingEdgeSample' });
        CommonButton({ buttonName: 'TabsScrollable', buttonUrl: 'pages/tabs/TabsScrollableSample' });
        CommonButton({ buttonName: 'TabsVertical', buttonUrl: 'pages/tabs/TabsVerticalSample' });
      }
      .padding('10vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}