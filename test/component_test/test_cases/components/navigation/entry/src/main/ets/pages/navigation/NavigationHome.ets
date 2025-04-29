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
struct NavigationHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('Navigation')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({
          buttonName: 'NavigationBackButtonIcon',
          buttonUrl: 'pages/navigation/NavigationBackButtonIconSample'
        });
        CommonButton({
          buttonName: 'NavigationHideBackButton',
          buttonUrl: 'pages/navigation/NavigationHideBackButtonSample'
        });
        CommonButton({
          buttonName: 'NavigationHideTitleBar',
          buttonUrl: 'pages/navigation/NavigationHideTitleBarSample'
        });
        CommonButton({
          buttonName: 'NavigationHideToolBar',
          buttonUrl: 'pages/navigation/NavigationHideToolBarSample'
        });
        CommonButton({ buttonName: 'NavigationMenus', buttonUrl: 'pages/navigation/NavigationMenusSample' });
        CommonButton({
          buttonName: 'NavigationMinContentWidth',
          buttonUrl: 'pages/navigation/NavigationMinContentWidthSample'
        });
        CommonButton({ buttonName: 'NavigationMode', buttonUrl: 'pages/navigation/NavigationModeSample' });
        CommonButton({
          buttonName: 'NavigationNavBarPosition',
          buttonUrl: 'pages/navigation/NavigationNavBarPositionSample'
        });
        CommonButton({
          buttonName: 'NavigationNavBarWidthRange',
          buttonUrl: 'pages/navigation/NavigationNavBarWidthRangeSample'
        });
        CommonButton({
          buttonName: 'NavigationNavBarWidth',
          buttonUrl: 'pages/navigation/NavigationNavBarWidthSample'
        });
        CommonButton({
          buttonName: 'NavigationNavDestination',
          buttonUrl: 'pages/navigation/NavigationNavDestinationSample'
        });
        CommonButton({ buttonName: 'NavigationTitleMode', buttonUrl: 'pages/navigation/NavigationTitleModeSample' });
        CommonButton({ buttonName: 'NavigationTitle', buttonUrl: 'pages/navigation/NavigationTitleSample' });
        CommonButton({
          buttonName: 'NavigationToolbarConfiguration',
          buttonUrl: 'pages/navigation/NavigationToolbarConfigurationSample'
        });

      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}