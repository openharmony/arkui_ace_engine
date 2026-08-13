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

@Entry
@Component
struct ListItemGroupStickyHeaderWithHorizontalList {
  private readonly headerItems: string[] = [
    '推荐', '热榜', '科技', '财经', '体育', '文化', '旅行', '美食', '健康', '教育'
  ];
  private readonly contentItems: string[] = [
    '推荐内容 01', '推荐内容 02', '推荐内容 03', '推荐内容 04', '推荐内容 05',
    '推荐内容 06', '推荐内容 07', '推荐内容 08', '推荐内容 09', '推荐内容 10',
    '推荐内容 11', '推荐内容 12', '推荐内容 13', '推荐内容 14', '推荐内容 15',
    '推荐内容 16', '推荐内容 17', '推荐内容 18', '推荐内容 19', '推荐内容 20'
  ];
  private readonly headerScroller: Scroller = new Scroller();

  @State private selectedHeaderIndex: number = 0;

  private scrollHeaderTo(index: number): void {
    let targetIndex: number = index;
    if (targetIndex < 0) {
      targetIndex = 0;
    } else if (targetIndex >= this.headerItems.length) {
      targetIndex = this.headerItems.length - 1;
    }

    this.selectedHeaderIndex = targetIndex;
    this.headerScroller.scrollToIndex(targetIndex, true, ScrollAlign.CENTER);
  }

  @Builder
  private stickyHeader() {
    Column({ space: 8 }) {
      Row({ space: 8 }) {
        Text('ListItemGroup Header')
          .fontSize(18)
          .fontWeight(FontWeight.Bold)
          .fontColor('#182431')

        Blank()

        Button('上一项')
          .height(32)
          .fontSize(13)
          .onClick(() => {
            this.scrollHeaderTo(this.selectedHeaderIndex - 1);
          })

        Button('下一项')
          .height(32)
          .fontSize(13)
          .onClick(() => {
            this.scrollHeaderTo(this.selectedHeaderIndex + 1);
          })
      }
      .width('100%')

      List({ space: 8, scroller: this.headerScroller }) {
        ForEach(this.headerItems, (item: string, index: number) => {
          ListItem() {
            Text(item)
              .fontSize(15)
              .fontColor(this.selectedHeaderIndex === index ? Color.White : '#344054')
              .padding({ left: 18, right: 18 })
              .height(38)
              .textAlign(TextAlign.Center)
              .backgroundColor(this.selectedHeaderIndex === index ? '#0A59F7' : '#E8EEF7')
              .borderRadius(19)
          }
          .onClick(() => {
            this.scrollHeaderTo(index);
          })
        }, (item: string) => item)
      }
      .listDirection(Axis.Horizontal)
      .width('100%')
      .height(46)
      .edgeEffect(EdgeEffect.Spring)
    }
    .width('100%')
    .padding({ left: 16, right: 16, top: 12, bottom: 10 })
    .backgroundColor('#F7F9FC')
  }

  build() {
    List({ space: 0 }) {
      ListItemGroup({ header: this.stickyHeader() }) {
        ForEach(this.contentItems, (item: string, index: number) => {
          ListItem() {
            Row({ space: 12 }) {
              Text(`${index + 1}`)
                .width(36)
                .height(36)
                .fontSize(14)
                .fontColor('#0A59F7')
                .textAlign(TextAlign.Center)
                .backgroundColor('#EAF2FF')
                .borderRadius(18)

              Text(item)
                .fontSize(16)
                .fontColor('#182431')
            }
            .width('100%')
            .height(72)
            .padding({ left: 16, right: 16 })
            .backgroundColor(Color.White)
          }
        }, (item: string) => item)
      }
      .divider({
        strokeWidth: 1,
        color: '#E5E7EB',
        startMargin: 64,
        endMargin: 16
      })
    }
    .width('100%')
    .height('100%')
    .sticky(StickyStyle.Header)
    .backgroundColor('#F2F4F7')
  }
}
