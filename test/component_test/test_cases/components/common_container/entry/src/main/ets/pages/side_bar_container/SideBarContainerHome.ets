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
struct SideBarContainerHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('SideBarContainerHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({
          buttonName: 'SideBarContainerShowSideBar',
          buttonUrl: 'pages/side_bar_container/SideBarContainerShowSideBarSample'
        });
        CommonButton({
          buttonName: 'SideBarContainerControlButton',
          buttonUrl: 'pages/side_bar_container/SideBarContainerControlButtonSample'
        });
        CommonButton({
          buttonName: 'SideBarContainerShowControlButton',
          buttonUrl: 'pages/side_bar_container/SideBarContainerShowControlButtonSample'
        });
        CommonButton({
          buttonName: 'SideBarContainerSideBarWidth',
          buttonUrl: 'pages/side_bar_container/SideBarContainerSideBarWidthSample'
        });
        CommonButton({
          buttonName: 'SideBarContainerMinSideBarWidth',
          buttonUrl: 'pages/side_bar_container/SideBarContainerMinSideBarWidthSample'
        });
        CommonButton({
          buttonName: 'SideBarContainerMaxSideBarWidth',
          buttonUrl: 'pages/side_bar_container/SideBarContainerMaxSideBarWidthSample'
        });
        CommonButton({
          buttonName: 'SideBarContainerAutoHide',
          buttonUrl: 'pages/side_bar_container/SideBarContainerAutoHideSample'
        });
        CommonButton({
          buttonName: 'SideBarContainerSideBarPosition',
          buttonUrl: 'pages/side_bar_container/SideBarContainerSideBarPositionSample'
        });
        CommonButton({
          buttonName: 'SideBarContainerDivider',
          buttonUrl: 'pages/side_bar_container/SideBarContainerDividerSample'
        });
        CommonButton({
          buttonName: 'SideBarContainerMinContentWidth',
          buttonUrl: 'pages/side_bar_container/SideBarContainerMinContentWidthSample'
        });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}