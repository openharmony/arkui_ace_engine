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
struct ListHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('ListHome')
          .padding('10vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({
          buttonName: 'ListAlignListItem',
          buttonUrl: 'pages/list/ListAlignListItemSample'
        });
        CommonButton({
          buttonName: 'ListCachedCount',
          buttonUrl: 'pages/list/ListCachedCountSample'
        });
        CommonButton({
          buttonName: 'ListChainAnimation',
          buttonUrl: 'pages/list/ListChainAnimationSample'
        });
        CommonButton({
          buttonName: 'ListContentEndOffset',
          buttonUrl: 'pages/list/ListContentEndOffsetSample'
        });
        CommonButton({
          buttonName: 'ListContentStartOffset',
          buttonUrl: 'pages/list/ListContentStartOffsetSample'
        });
        CommonButton({
          buttonName: 'ListDivider_One',
          buttonUrl: 'pages/list/ListDividerSample'
        });
        CommonButton({
          buttonName: 'ListEdgeEffect',
          buttonUrl: 'pages/list/ListEdgeEffectSample'
        });
        CommonButton({
          buttonName: 'ListEnableScrollInteraction',
          buttonUrl: 'pages/list/ListEnableScrollInteractionSample'
        });
        CommonButton({
          buttonName: 'ListFriction',
          buttonUrl: 'pages/list/ListFrictionSample'
        });
        CommonButton({
          buttonName: 'ListLanes_One',
          buttonUrl: 'pages/list/ListLanesSample_One'
        });
        CommonButton({
          buttonName: 'ListLanes_Two',
          buttonUrl: 'pages/list/ListLanesSample_Two'
        });
        CommonButton({
          buttonName: 'ListListDirection',
          buttonUrl: 'pages/list/ListListDirectionSample'
        });
        CommonButton({
          buttonName: 'ListMultiSelectable',
          buttonUrl: 'pages/list/ListMultiSelectableSample'
        });
        CommonButton({
          buttonName: 'ListNestedScroll',
          buttonUrl: 'pages/list/ListNestedScrollSample'
        });
        CommonButton({
          buttonName: 'ListScrollBarColor',
          buttonUrl: 'pages/list/ListScrollBarColorSample'
        });
        CommonButton({
          buttonName: 'ListScrollBar',
          buttonUrl: 'pages/list/ListScrollBarSample'
        });
        CommonButton({
          buttonName: 'ListScrollBarWidth',
          buttonUrl: 'pages/list/ListScrollBarWidthSample'
        });
        CommonButton({
          buttonName: 'ListScrollSnapAlign',
          buttonUrl: 'pages/list/ListScrollSnapAlignSample'
        });
        CommonButton({
          buttonName: 'ListSticky',
          buttonUrl: 'pages/list/ListStickySample'
        });


      }
      .padding('10vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}