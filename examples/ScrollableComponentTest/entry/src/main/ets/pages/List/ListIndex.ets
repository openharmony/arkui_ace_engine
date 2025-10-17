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

import router from '@ohos.router';

interface routerInfo {
  url: string;
  info: string;
}

let routerData: routerInfo[] = [
  { url: 'pages/List/divider/dividerColor', info: 'divider_Color' },
  { url: 'pages/List/divider/dividerEndMargin', info: 'divider_EndMargin' },
  { url: 'pages/List/divider/dividerStartMargin', info: 'divider_StartMargin' },
  { url: 'pages/List/divider/dividerStrokeWidth', info: 'divider_StrokeWidth' },
  { url: 'pages/List/friction/friction', info: 'friction' },
  { url: 'pages/List/Lanes/lanesMaxLength', info: 'lanes_MaxLength' },
  { url: 'pages/List/Lanes/lanesMinLength', info: 'lanes_MinLength' },
  { url: "pages/List/swipeAction/children", info: "children"},
  { url: "pages/List/swipeAction/hIndex", info: "多列list"},
  { url: "pages/List/swipeAction/Page1", info: "cxnIndex"},
  { url: "pages/List/swipeActionPageRepeat", info: "Repeat"}
]

@Entry
@Component
struct Index {
  listScroller: Scroller = new Scroller();

  build() {
    Column({ space: 10 }) {
      List({ space: 10, scroller: this.listScroller }) {
        ForEach(routerData, (item: routerInfo) => {
          ListItem() {
            Text(item.info)
              .width('100%')
              .height('120vp')
              .fontSize('15vp')
              .backgroundColor('#ffb6c1')

              .borderRadius(10)
              .textAlign(TextAlign.Center)
              .onClick(() => {
                router.pushUrl({
                  url: item.url
                })
              })
          }
        })
      }
      .width('90%')
      .height('100%')
      .scrollBar(BarState.Off)
      .friction(0.6)
      .divider({
        strokeWidth: 2,
        color: 0xFFFFFF,
        startMargin: 20,
        endMargin: 20
      }) // 每行之间的分界线
      .edgeEffect(EdgeEffect.Spring) // 边缘效果设置为Spring
    }.width('100%').height('100%').padding({ top: 5 })
  }
}