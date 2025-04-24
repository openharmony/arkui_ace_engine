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

@Entry
@Component
struct barHeightTest {
  @State arr: number[] =
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 11, 14, 15, 16, 17, 18, 19, 20, 21, 24, 22, 23, 25, 26, 27, 28, 29, 30]
  @State barOverlap: boolean = true;
  build() {
    Column() {
      Text(`barOverlap ${this.barOverlap}`).fontSize(16)
      Button("barOverlap变化").width('100%').margin({ bottom: '12vp' })
        .onClick((event?: ClickEvent) => {
          if (this.barOverlap) {
            this.barOverlap = false;
          } else {
            this.barOverlap = true;
          }
        })
      Tabs({ barPosition: BarPosition.End }) {
        TabContent() {
          Column() {
            Grid() {
              ForEach(this.arr, (item: number) => {
                GridItem() {
                  Text("item" + item)
                    .width('80%')
                    .height(200)
                    .fontSize(16)
                    .textAlign(TextAlign.Center)
                    .backgroundColor('#fff8b81e')
                }
              }, (item: string) => item)
            }
            .width('100%')
            .height('100%')
            // 滚动组件List/Grid/WaterFlow设置不裁剪SAFE_AREA内容
            .clipContent(ContentClipMode.SAFE_AREA)
            // 滚动组件List/Grid/WaterFlow设置显示缓存节点
            .cachedCount(1, true)
            .columnsTemplate('1fr 1fr')
            // .lanes(2)
            // .alignListItem(ListItemAlign.Center)
          }.width('100%').height('100%')
          .backgroundColor(Color.Pink)
        }
        // TabContent设置safeAreaPadding为tabBar高度
        .safeAreaPadding({ bottom: $r('sys.float.ohos_id_bottomtab_height') })
        .tabBar(new BottomTabBarStyle($r('sys.media.ohos_icon_mask_svg'), '测试0'))
      }
      .scrollable(false)
      .layoutWeight(1)
      .barOverlap(this.barOverlap)
      //.safeAreaPadding({bottom:0})
    }
    .height('100%')
    // .padding({ top: '24vp', left: '24vp', right: '24vp' })
  }
}