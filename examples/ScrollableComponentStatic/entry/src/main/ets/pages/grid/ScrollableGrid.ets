'use static'

/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { ComponentCard } from '../../common/Card';
import {
  Entry,
  Component,
  State,
  NavDestination,
  Column,
  Grid,
  GridItem,
  Text,
  ForEach,
  ResourceStr,
  $r,
  ColumnOptions
} from '@kit.ArkUI';
import { common } from '@kit.AbilityKit';
// [Start build_scrollable_horizontally_grid_layouts]
@Entry
@Component
export struct ScrollableGrid {
  // [StartExclude build_scrollable_horizontally_grid_layouts]
  context: common.UIAbilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext;
  // [EndExclude build_scrollable_horizontally_grid_layouts]
  @State
  services: string[] = [] as string[];
  // [StartExclude build_scrollable_horizontally_grid_layouts]
  private bgColors: string[] = ['#3079fe', '#fea500', '#f45a43']
  aboutToAppear(): void {
    const categories = this.context.resourceManager.getStringByNameSync('Categories')
    this.services.push(categories)
    const recharge = this.context.resourceManager.getStringByNameSync('Recharge')
    this.services.push(recharge)
    const membership = this.context.resourceManager.getStringByNameSync('Membership')
    this.services.push(membership)
    const claim = this.context.resourceManager.getStringByNameSync('Claim_Coupon')
    this.services.push(claim)
    const lottery = this.context.resourceManager.getStringByNameSync('Lottery')
    this.services.push(lottery)
    const favorites = this.context.resourceManager.getStringByNameSync('Favorites')
    this.services.push(favorites)
    const points = this.context.resourceManager.getStringByNameSync('Points')
    this.services.push(points)
    const more = this.context.resourceManager.getStringByNameSync('More')
    this.services.push(more)
  }
  // [EndExclude build_scrollable_horizontally_grid_layouts]
  build(): void {
    // [StartExclude build_scrollable_horizontally_grid_layouts]
    NavDestination() {
      // [EndExclude build_scrollable_horizontally_grid_layouts]

      Column({ space: 5 } as ColumnOptions) {
        // [StartExclude build_scrollable_horizontally_grid_layouts]
        // 请将$r('app.string.ScrollableGrid_titleHorizontal')替换为实际资源文件，在本示例中该资源文件的value值为"横向可滚动网格布局示例"
        ComponentCard({ title: $r('app.string.ScrollableGrid_titleHorizontal') }) {
          // [EndExclude build_scrollable_horizontally_grid_layouts]

          Grid() {
            ForEach(this.services, (service: string, index: int) => {
              GridItem() {
                // [StartExclude build_scrollable_horizontally_grid_layouts]
                Text(service)
                // [EndExclude build_scrollable_horizontally_grid_layouts]
              }
              .width('25%')
              // [StartExclude build_scrollable_horizontally_grid_layouts]
              .backgroundColor(this.bgColors[index % this.bgColors.length])
              .borderRadius(50)
              // [EndExclude build_scrollable_horizontally_grid_layouts]
            }, (service: string): string => service)
          }
          .rowsTemplate('1fr 1fr') // 只设置rowsTemplate属性，当内容超出Grid区域时，可水平滚动。
          .rowsGap(15)

          // [StartExclude build_scrollable_horizontally_grid_layouts]
          .height(200)
          .columnsGap(10)
          // [EndExclude build_scrollable_horizontally_grid_layouts]
        }
      }
      // [StartExclude build_scrollable_horizontally_grid_layouts]
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })

    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.ScrollableGrid_title')替换为实际资源文件，在本示例中该资源文件的value值为"横向可滚动网格布局示例"
    .title($r('app.string.ScrollableGrid_title'))
  }
  // [EndExclude build_scrollable_horizontally_grid_layouts]
}
// [End build_scrollable_horizontally_grid_layouts]
