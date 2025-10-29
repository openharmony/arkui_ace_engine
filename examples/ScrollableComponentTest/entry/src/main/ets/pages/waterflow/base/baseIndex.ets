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

 /*
  * Description: WaterFlow组件支持基于断点自适应列数
  * Writer: renxiaowen
  */
 
import router from '@ohos.router'

interface routerInfo {
  url: string;
  info: string;
}

let routerData: routerInfo[] = [
  {url: "pages/waterflow/base/AlwaysTopDown/LazyVertical", info: "AlwaysTopDown_LazyVertical"},
  {url: "pages/waterflow/base/AlwaysTopDown/LazyVerticalSections", info: "AlwaysTopDown_LazyVerticalSections"},
  {url: "pages/waterflow/base/AlwaysTopDown/OriVertical", info: "AlwaysTopDown_OriVertical"},
  {url: "pages/waterflow/base/AlwaysTopDown/OriVerticalSections", info: "AlwaysTopDown_OriVerticalSections"},
  {url: "pages/waterflow/base/AlwaysTopDown/RepeatVertical", info: "AlwaysTopDown_RepeatVertical"},
  {url: "pages/waterflow/base/AlwaysTopDown/RepeatVerticalSections", info: "AlwaysTopDown_RepeatVerticalSections"},
  {url: "pages/waterflow/base/SlidingWindow/LazyVertical", info: "SlidingWindow_LazyVertical"},
  {url: "pages/waterflow/base/SlidingWindow/LazyVerticalSections", info: "SlidingWindow_LazyVerticalSections"},
  {url: "pages/waterflow/base/SlidingWindow/OriVertical", info: "SlidingWindow_OriVertical"},
  {url: "pages/waterflow/base/SlidingWindow/OriVerticalSections", info: "SlidingWindow_OriVerticalSections"},
  {url: "pages/waterflow/base/SlidingWindow/RepeatVertical", info: "SlidingWindow_RepeatVertical"},
  {url: "pages/waterflow/base/SlidingWindow/RepeatVerticalSections", info: "SlidingWindow_RepeatVerticalSections"},
  {url: "pages/waterflow/base/normal/LazyVertical", info: "normal_LazyVertical"},
  {url: "pages/waterflow/base/normal/OriVertical", info: "normal_OriVertical"},
  {url: "pages/waterflow/base/normal/RepeatVertical", info: "normal_RepeatVertical"},
]
@Entry
@Preview
@Component
struct baseIndex {
  listScroller: Scroller = new Scroller()
  build() {
    Column({ space: 10 }) {
      List({space: 10, scroller: this.listScroller}) {
        ForEach(routerData, (item: routerInfo) => {
          ListItem() {
            Text(item.info)
              .width("100%")
              .height("50vp")
              .fontSize("20vp")
              .backgroundColor(0x6666FF)
              .borderRadius(10)
              .textAlign(TextAlign.Center)
              .onClick(() => {
                router.pushUrl({
                  url: item.url
                })
              })
          }
        })
      }.width("90%")

      .scrollBar(BarState.Off)
      .friction(0.6)
      .divider({ strokeWidth: 2, color: 0xFFFFFF, startMargin: 20, endMargin: 20 }) // 每行之间的分界线
      .edgeEffect(EdgeEffect.Spring) // 边缘效果设置为Spring
    }.width('100%').height('100%').backgroundColor(0xE0FFFF).padding({ top: 5 })
  }
}
