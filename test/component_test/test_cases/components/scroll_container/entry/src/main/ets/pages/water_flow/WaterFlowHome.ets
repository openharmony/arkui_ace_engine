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
struct WaterFlowHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('WaterFlowHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({
          buttonName: 'WaterFlowColumnsTemplate',
          buttonUrl: 'pages/water_flow/WaterFlowColumnsTemplateSample'
        });
        CommonButton({
          buttonName: 'WaterFlowRowsTemplate',
          buttonUrl: 'pages/water_flow/WaterFlowRowsTemplateSample'
        });
        CommonButton({
          buttonName: 'WaterFlowItemConstraintSizeSample',
          buttonUrl: 'pages/water_flow/WaterFlowItemConstraintSizeSample'
        });
        CommonButton({ buttonName: 'WaterFlowColumnsGap', buttonUrl: 'pages/water_flow/WaterFlowColumnsGapSample' });
        CommonButton({ buttonName: 'WaterFlowRowsGap', buttonUrl: 'pages/water_flow/WaterFlowRowsGapSample' });
        CommonButton({
          buttonName: 'WaterFlowLayoutDirection',
          buttonUrl: 'pages/water_flow/WaterFlowLayoutDirectionSample'
        });
        CommonButton({
          buttonName: 'WaterFlowEnableScrollInteraction',
          buttonUrl: 'pages/water_flow/WaterFlowEnableScrollInteractionSample'
        });
        CommonButton({
          buttonName: 'WaterFlowNestedScroll',
          buttonUrl: 'pages/water_flow/WaterFlowNestedScrollSample'
        });
        CommonButton({ buttonName: 'WaterFlowFriction', buttonUrl: 'pages/water_flow/WaterFlowFrictionSample' });
        CommonButton({ buttonName: 'WaterFlowCachedCount', buttonUrl: 'pages/water_flow/WaterFlowCachedCountSample' });
        CommonButton({ buttonName: 'WaterFlowScrollBar', buttonUrl: 'pages/water_flow/WaterFlowScrollBarSample' });
        CommonButton({
          buttonName: 'WaterFlowScrollBarWidth',
          buttonUrl: 'pages/water_flow/WaterFlowScrollBarWidthSample'
        });
        CommonButton({
          buttonName: 'WaterFlowScrollBarColor',
          buttonUrl: 'pages/water_flow/WaterFlowScrollBarColorSample'
        });
        CommonButton({ buttonName: 'WaterFlowEdgeEffect', buttonUrl: 'pages/water_flow/WaterFlowEdgeEffectSample' });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}