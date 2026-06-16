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
  Builder,
  Column,
  List,
  ListItem,
  ListItemGroup,
  Row,
  Text,
  Image,
  Blank,
  ForEach,
  NavDestination,
  ListItemGroupStyle,
  ListItemStyle,
  FlexAlign,
  ResourceStr
} from '@kit.ArkUI';
import { ColumnOptions, ListOptions } from '@kit.ArkUI';
import { State } from '@ohos.arkui.stateManagement';
import { $r } from '@kit.ArkUI';
import curves from '@ohos.curves';

export interface ItemInfo {
  index: int,
  name: ResourceStr,
  label: ResourceStr,
  type?: string,
}

export interface ItemGroupInfo extends ItemInfo {
  children: ItemInfo[]
}

@Entry
@Component
export struct CollapseAndExpand {
  @State routes: ItemGroupInfo[] = [
    {
      index: 0,
      name: 'basicInfo',
      // The value of app.string.Personal_Basic_Information in resource file is 'Personal Basic Information'
      label: $r('app.string.Personal_Basic_Information'),
      children: [
        {
          index: 0,
          // The value of app.string.nick_name in resource file is 'Nickname'
          name: $r('app.string.nick_name'),
          label: 'xxxx',
          type: 'Text'
        },
        {
          index: 1,
          // The value of app.string.avatar in resource file is 'Avatar'
          name: $r('app.string.avatar'),
          label: $r('sys.media.ohos_user_auth_icon_face'),
          type: 'Image'
        },
        {
          index: 2,
          // The value of app.string.age in resource file is 'Age'
          name: $r('app.string.age'),
          label: 'xxxx',
          type: 'Text'
        },
        {
          index: 3,
          // The value of app.string.birthday in resource file is 'Birthday'
          name: $r('app.string.birthday'),
          label: 'xxxxxxxxx',
          type: 'Text'
        },
        {
          index: 4,
          // The value of app.string.gender in resource file is 'Gender'
          name: $r('app.string.gender'),
          label: 'xxxxxxxx',
          type: 'Text'
        },
      ]
    },
    {
      index: 1,
      name: 'equipInfo',
      // The value of app.string.Device_Information in resource file is 'Device Information'
      label: $r('app.string.Device_Information'),
      children: []
    },
    {
      index: 2,
      name: 'appInfo',
      // The value of app.string.Application_usage_information in resource file is 'Application Usage Information'
      label: $r('app.string.Application_usage_information'),
      children: []
    },
    {
      index: 3,
      name: 'uploadInfo',
      // The value of app.string.data_you_voluntarily_uploaded in resource file is 'Data You Voluntarily Uploaded'
      label: $r('app.string.data_you_voluntarily_uploaded'),
      children: []
    },
    {
      index: 4,
      name: 'tradeInfo',
      // The value of app.string.Trading_and_asset_information in resource file is 'Trading and Asset Information'
      label: $r('app.string.Trading_and_asset_information'),
      children: []
    },
    {
      index: 5,
      name: 'otherInfo',
      // The value of app.string.Other_materials in resource file is 'Other Materials'
      label: $r('app.string.Other_materials'),
      children: []
    },
  ] as ItemGroupInfo[];
  @State expandedItems: boolean[] = [] as boolean[];
  @State selection: string | null = null;

  aboutToAppear(): void {
    for (let i: int = 0; i < this.routes.length; i++) {
      this.expandedItems.push(false);
    }
  }

  @Builder
  ListItemGroupHeader(itemGroup: ItemGroupInfo): void {
    Row() {
      Text(itemGroup.label)
      Blank()
      Image($r('sys.media.ohos_ic_public_arrow_down'))
        .fillColor($r('sys.color.ohos_id_color_fourth'))
        .height(30)
        .width(30)
        .rotate({ angle: !!itemGroup.children.length ? (this.expandedItems[itemGroup.index] ? 180 : 0) : 180 })
        .animation({ curve: curves.interpolatingSpring(0, 1, 228, 22) })
    }
    .width('100%')
    .padding(10)
    .animation({ curve: curves.interpolatingSpring(0, 1, 528, 39) })
    .onClick(() => {
      if (itemGroup.children.length) {
        this.getUIContext().animateTo({ curve: curves.interpolatingSpring(0, 1, 528, 39) }, () => {
          this.expandedItems[itemGroup.index] = !this.expandedItems[itemGroup.index];
        })
      }
    })
  }

  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // Please replace $r('app.string.CollapseAndExpand_title') with the actual resource file.
        // In this example, the value of this resource file is "Collapse and Expand"
        ComponentCard({ title: $r('app.string.CollapseAndExpand_title') }) {
          Column() {
            List({ space: 10 } as ListOptions) {
              ForEach(this.routes, (itemGroup: ItemGroupInfo) => {
                ListItemGroup({
                  header: this.ListItemGroupHeader(itemGroup),
                  style: ListItemGroupStyle.CARD,
                }) {
                  if (this.expandedItems[itemGroup.index] && itemGroup.children) {
                    ForEach(itemGroup.children, (item: ItemInfo) => {
                      ListItem({ style: ListItemStyle.CARD }) {
                        Row() {
                          Text(item.name)
                          Blank()
                          if (item.type === 'Image') {
                            Image(item.label)
                              .height(20)
                              .width(20)
                          } else {
                            Text(item.label)
                          }
                          Image($r('sys.media.ohos_ic_public_arrow_right'))
                            .fillColor($r('sys.color.ohos_id_color_fourth'))
                            .height(30)
                            .width(30)
                        }
                        .width('100%')
                      }
                      .width('100%')
                      .animation({ curve: curves.interpolatingSpring(0, 1, 528, 39) })
                    })
                  }
                }.clip(true)
              })
            }
            .width('100%')
          }
          .width('100%')
          .height('100%')
          .justifyContent(FlexAlign.Start)
          .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // Please replace $r('app.string.CollapseAndExpand_title') with the actual resource file.
    // In this example, the value of this resource file is "Collapse and Expand"
    .title($r('app.string.CollapseAndExpand_title'))
  }
}
