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
import { CommonButton } from '../util/CommonButton';

@Entry
@Component
struct Index {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('Scroll_Container')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({ buttonName: 'WaterFlow', buttonUrl: 'pages/water_flow/WaterFlowHome' });
        CommonButton({ buttonName: 'ListItem', buttonUrl: 'pages/list_item/ListItemHome' });
        CommonButton({ buttonName: 'ListItemGroup', buttonUrl: 'pages/list_item_group/ListItemGroupHome' });
        CommonButton({ buttonName: 'GridItem', buttonUrl: 'pages/grid_item/GridItemHome' });
        CommonButton({ buttonName: 'List', buttonUrl: 'pages/list/ListHome' });
        CommonButton({ buttonName: 'Scroll', buttonUrl: 'pages/scroll/ScrollHome' });
        CommonButton({ buttonName: 'Swiper', buttonUrl: 'pages/swiper/SwiperHome' });
        CommonButton({ buttonName: 'Grid', buttonUrl: 'pages/grid/GridHome' });
      }
      .padding('20vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}