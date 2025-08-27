/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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


import { curves } from '@kit.ArkUI'

interface ItemInfo {
  index: number,
  name: string,
  label: ResourceStr,
  type?: string,
}

interface ItemGroupInfo extends ItemInfo {
  children: ItemInfo[]
}

@Entry
@Component
struct FoldExpand {

  @State expandedItems: Array<boolean> = []
  @State routes: Array<ItemGroupInfo> = []

  aboutToAppear(): void {
    for (let i = 0; i < 5; i++) {
      let child: ItemInfo = {
        name: '1',
        label: '2',
        index: 0,
      }
      let group: ItemGroupInfo = {
        name: '1',
        label: '2',
        index: i,
        children: [child, child, child, child, child]
      }
      this.routes.push(group)
      this.expandedItems.push(false)
    }
  }

  @Builder
  ListItemGroupHeader(itemGroup: ItemGroupInfo) {
    Row() {
      Text(itemGroup.label)
      Blank()
      Image($r('sys.media.ohos_ic_public_arrow_down'))
        .fillColor($r('sys.color.ohos_id_color_fourth'))
        .height(30)
        .width(30)
        .rotate({ angle: !!itemGroup.children.length ? (this.expandedItems[itemGroup.index] ? 180 : 0) : 180})
        .animation({ curve: curves.interpolatingSpring(0, 1, 228, 22) })
    }
    .width('100%')
    .padding(10)
    .animation({ curve: curves.interpolatingSpring(0, 1, 528, 39) })
    .onTouch((event) => {
      if (event.type === TouchType.Up) {
        if (itemGroup.children.length) {
          animateTo({ curve: curves.interpolatingSpring(0, 1, 528, 39) }, () => {
            this.expandedItems[itemGroup.index] = !this.expandedItems[itemGroup.index]
          })
        }
      }
    })
  }

  build() {
    Column() {
      List({ space: 10 }) {
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
                .enabled(false)
                .width('100%')
                .animation({ curve: curves.interpolatingSpring(0, 1, 528, 39) })
              })
            }
          }
          .clip(true)
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