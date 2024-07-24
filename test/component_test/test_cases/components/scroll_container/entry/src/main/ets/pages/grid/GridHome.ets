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
struct GridHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('GridHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({ buttonName: 'GridColumnsTemplate', buttonUrl: 'pages/grid/GridColumnsTemplateSample' });
        CommonButton({ buttonName: 'GridRowsTemplate', buttonUrl: 'pages/grid/GridRowsTemplateSample' });
        CommonButton({ buttonName: 'GridColumnsGap', buttonUrl: 'pages/grid/GridColumnsGapSample' });
        CommonButton({ buttonName: 'GridRowsGap', buttonUrl: 'pages/grid/GridRowsGapSample' });
        CommonButton({ buttonName: 'GridScrollBar', buttonUrl: 'pages/grid/GridScrollBarSample' });
        CommonButton({ buttonName: 'GridScrollBarColor', buttonUrl: 'pages/grid/GridScrollBarColorSample' });
        CommonButton({ buttonName: 'GridScrollBarWidth', buttonUrl: 'pages/grid/GridScrollBarWidthSample' });
        CommonButton({ buttonName: 'GridCachedCount', buttonUrl: 'pages/grid/GridCachedCountSample' });
        CommonButton({ buttonName: 'GridEditMode', buttonUrl: 'pages/grid/GridEditModeSample' });
        CommonButton({ buttonName: 'GridLayoutDirection', buttonUrl: 'pages/grid/GridLayoutDirectionSample' });
        CommonButton({ buttonName: 'GridMaxCount', buttonUrl: 'pages/grid/GridMaxCountSample' });
        CommonButton({ buttonName: 'GridMinCount', buttonUrl: 'pages/grid/GridMinCountSample' });
        CommonButton({ buttonName: 'GridCellLength', buttonUrl: 'pages/grid/GridCellLengthSample' });
        CommonButton({ buttonName: 'GridMultiSelectable', buttonUrl: 'pages/grid/GridMultiSelectableSample' });
        CommonButton({ buttonName: 'GridEdgeEffect', buttonUrl: 'pages/grid/GridEdgeEffectSample' });
        CommonButton({
          buttonName: 'GridEnableScrollInteraction',
          buttonUrl: 'pages/grid/GridEnableScrollInteractionSample'
        });
        CommonButton({ buttonName: 'GridNestedScroll', buttonUrl: 'pages/grid/GridNestedScrollSample' });
        CommonButton({ buttonName: 'GridFriction', buttonUrl: 'pages/grid/GridFrictionSample' });
        CommonButton({ buttonName: 'GridSupportAnimation', buttonUrl: 'pages/grid/GridSupportAnimationSample' });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}