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

/**
 * This demo demonstrates that by setting the ChildrenMainSize property,
 * the scrollbar of the List component can smoothly move without jumping
 * when sliding in scenes where the child components are not of equal height.
 */

import { MyDataSource } from '../ListDataSource/LazyForEachDataSource'

@Entry
@Component
struct ListItemGroupScenario {
  private scroller: ListScroller = new ListScroller();
  private listDataSource_10_children: MyDataSource = new MyDataSource();
  private groupDataSource_6_children: MyDataSource = new MyDataSource();
  @State space4List: number = 10;
  @State space4Group: number = 10;
  @State listItemSize: number = 100;
  @State groupItemSize: number = 100;
  @State groupItemSizeLarge: number = 300;
  @State edgeEffect: EdgeEffect = EdgeEffect.Spring;
  @State snapAlign: ScrollSnapAlign = ScrollSnapAlign.NONE;
  @State isVisible : Visibility = Visibility.None;
  @State listChildrenSize: ChildrenMainSize = new ChildrenMainSize(100);
  // every ListItemGroup needs to be provided with a ChildrenMainSize.
  @State groupChildrenSize: Array<ChildrenMainSize> = [];


  // prepare all the dataSource and ChildrenMainSize objects.
  aboutToAppear() {
    // step1: fill in the data source.
    for (let i = 0; i < 10; i++) {
      this.listDataSource_10_children.pushData(i);
    }
    for (let i = 0; i < 6; i++) {
      this.groupDataSource_6_children.pushData(i);
    }

    // step2: create and initialize all the related ChildrenMainSize objects.
    let tempArr4ListChildrenSize: number[] = [];

    /**
     * structure: List contains 10 children.
     * index 5 and 6: ListItem.
     * others: ListItemGroup(8 identical ListItemGroup).
     *
     * To demonstrate the use of various interfaces, here we pass values to ChildMainSize based on ListItemGroup
     * firstly. Then, update the heights of two ListItems to their corresponding index positions. Of course,
     * if it is a development process, there may be a better way to initialize ChildMainSize.
     */
    for (let i = 0; i < 10; i++) {
      // every ListItemGroup needs to be provided with a ChildrenMainSize.
      let tempGroupChildrenSize: ChildrenMainSize = new ChildrenMainSize(100);
      /**
       * ListItemGroup contains 6 children:
       * index 0 - 2: groupItemSizeLarge.
       * index 3 - 5: groupItemSize.
       */

      // step1: just to call the interface of ChildrenMainSize as much as possible, it has no practical purpose here.
      tempGroupChildrenSize.update(2, 200);
      // step2: update the height information of the first three elements.
      tempGroupChildrenSize.splice(0, 3, [this.groupItemSizeLarge, this.groupItemSizeLarge, this.groupItemSizeLarge]);
      // step3: put the temporarily calculated ChildrenMainSize object into the object array.
      this.groupChildrenSize.push(tempGroupChildrenSize);
      // step4: calculate and update ListItemGroup height info. 50: header and footer height.
      let height = 50 * 2 + this.space4Group * (6 - 1) + this.groupItemSize * 3 + this.groupItemSizeLarge * 3;
      tempArr4ListChildrenSize.push(height);
    }
    // just to call the interface of ChildrenMainSize as much as possible, it has no practical purpose here.
    tempArr4ListChildrenSize.push(12);
    tempArr4ListChildrenSize.push(13);
    // 100: just for testing robustness, it is entirely possible to write 0 here during actual development.
    this.listChildrenSize.splice(0, 100, tempArr4ListChildrenSize)
    // update item 5 height info to the real height.
    this.listChildrenSize.update(5, 300)
    // update item 6 height info to the default height.
    this.listChildrenSize.splice(6, 1, [10]); // just for testing robustness.
    this.listChildrenSize.splice(6, 1, [NaN]);
  }

  @Builder
  itemHead(text: string) {
    Text(text)
      .fontSize(20)
      .backgroundColor(0xAABBCC)
      .padding(10)
      .height(50)
      .width('50%')
  }

  @Builder
  itemFoot(text: string) {
    Text(text)
      .fontSize(16)
      .backgroundColor(0xAABBCC)
      .width('100%')
      .padding(5)
      .height(50)
      .width('50%')
  }

  build() {
    Column() {
      List({ space: this.space4List, initialIndex: 1, scroller: this.scroller}) {
        LazyForEach(this.listDataSource_10_children, (item: number) => {
          if (item === 5 || item === 6) {
            ListItem() {
              Text('List child ' + item)
                .height(item === 5 ? 300 : this.listItemSize)
                .width('90%')
                .fontSize(16)
                .textAlign(TextAlign.Center)
                .borderRadius(10)
                .backgroundColor(Color.Pink)
            }
          } else {
            ListItemGroup({
              header: this.itemHead('List child ' + item + ' header'),
              footer: this.itemFoot('List child ' + item + ' footer'),
              space:this.space4Group,
            }) {
              LazyForEach(this.groupDataSource_6_children, (itemInGroup: number) => {
                ListItem() {
                  Text('List child ' + item + ', groupItem ' + itemInGroup)
                    .width('100%')
                    .height(itemInGroup <= 2 ? this.groupItemSizeLarge : this.groupItemSize)
                    .fontSize(16)
                    .textAlign(TextAlign.Center)
                    .borderRadius(10)
                    .backgroundColor(Color.Pink)
                }.width('60%')
              }, (item: string) => item)
            }
            .childrenMainSize(this.groupChildrenSize[item])
          }
        }, (item: string) => item)
      }
      .childrenMainSize(this.listChildrenSize)
      .height(500)
      .width('90%')
      .backgroundColor(Color.Brown)
      .scrollBar(BarState.On)
      .scrollBarWidth(30)
      .margin({top:20})
      .scrollSnapAlign(this.snapAlign)
      .chainAnimation(true)
      .edgeEffect(this.edgeEffect)
      .alignListItem(ListItemAlign.Center)
      .sticky(StickyStyle.Header | StickyStyle.Footer)
      Row() {
        Button() {
          Text('edgeEffect: ' + this.edgeEffect)
        }
        .onClick(() => {
          switch (this.edgeEffect) {
            case EdgeEffect.Spring:
              this.edgeEffect = EdgeEffect.Fade;
              break;
            case EdgeEffect.None:
              this.edgeEffect = EdgeEffect.Spring;
              break;
            case EdgeEffect.Fade:
              this.edgeEffect = EdgeEffect.None;
              break;
            default:
              break;
          }
        })
        .width('50%')
        .height(60)
        .type(ButtonType.Normal)
        .borderRadius(10)
        Button() {
          Text('snapAlign: ' + this.snapAlign)
        }
        .onClick(() => {
          switch (this.snapAlign) {
            case ScrollSnapAlign.START:
              this.snapAlign = ScrollSnapAlign.CENTER;
              break;
            case ScrollSnapAlign.CENTER:
              this.snapAlign = ScrollSnapAlign.NONE;
              break;
            case ScrollSnapAlign.NONE:
              this.snapAlign = ScrollSnapAlign.START;
              break;
            default:
              break;
          }
        })
        .width('50%')
        .height(60)
        .type(ButtonType.Normal)
        .borderRadius(10)
      }
      Row() {
        Button() {
          Text('ListDefault+50: ' + this.listChildrenSize.childDefaultSize)
        }
        .onClick(() => {
          this.listItemSize += 50;
          this.listChildrenSize.childDefaultSize += 50;
        })
        .width('25%')
        .height(60)
        .type(ButtonType.Normal)
        .borderRadius(10)
        Button() {
          Text('ListDefault-50: ' + this.listChildrenSize.childDefaultSize)
        }
        .onClick(() => {
          if (this.listItemSize < 50) {
            return;
          }
          this.listItemSize -= 50;
          this.listChildrenSize.childDefaultSize -= 50;
        })
        .width('25%')
        .height(60)
        .type(ButtonType.Normal)
        .borderRadius(10)
        Button() {
          Text('GroupDefault+50')
        }
        .onClick(() => {
          this.groupItemSize += 50;
          for (let i = 0; i < 10; i++) {
            let temp: ChildrenMainSize = new ChildrenMainSize(this.groupItemSize);
            temp.splice(0, 3, [this.groupItemSizeLarge, this.groupItemSizeLarge, this.groupItemSizeLarge]);
            this.groupChildrenSize[i] = temp;
            if (i === 5 || i === 6) {
              continue;
            }
          }
          for (let i = 0; i < 10; i++) {
            if (i === 5 || i === 6) {
              continue;
            }
            // recalculate and update ListItemGroup height info.
            let height = 50 * 2 + this.space4Group * (6 - 1) + this.groupItemSize * 3 + this.groupItemSizeLarge * 3;
            this.listChildrenSize.update(i, height);
          }
        })
        .width('25%')
        .height(60)
        .type(ButtonType.Normal)
        .borderRadius(10)
        Button() {
          Text('GroupDefault-50')
        }
        .onClick(() => {
          if (this.groupItemSize < 50) {
            return;
          }
          this.groupItemSize -= 50;
          for (let i = 0; i < 10; i++) {
            let temp: ChildrenMainSize = new ChildrenMainSize(this.groupItemSize);
            temp.splice(0, 3, [this.groupItemSizeLarge, this.groupItemSizeLarge, this.groupItemSizeLarge]);
            this.groupChildrenSize[i] = temp;
          }
          for (let i = 0; i < 10; i++) {
            if (i === 5 || i === 6) {
              continue;
            }
            // recalculate and update ListItemGroup height info.
            let height = 50 * 2 + this.space4Group * (6 - 1) + this.groupItemSize * 3 + this.groupItemSizeLarge * 3;
            this.listChildrenSize.update(i, height);
          }
        })
        .width('25%')
        .height(60)
        .type(ButtonType.Normal)
        .borderRadius(10)
      }
      Row() {
        Button() {
          Text('group prevItemSize+50')
        }
        .onClick(() => {
          this.groupItemSizeLarge += 50;
          for (let i = 0; i < 10; i++) {
            let temp: ChildrenMainSize = new ChildrenMainSize(this.groupItemSize);
            temp.splice(0, 3, [this.groupItemSizeLarge, this.groupItemSizeLarge, this.groupItemSizeLarge]);
            this.groupChildrenSize[i] = temp;
          }
          for (let i = 0; i < 10; i++) {
            if (i === 5 || i === 6) {
              continue;
            }
            // recalculate and update ListItemGroup height info.
            let height = 50 * 2 + this.space4Group * (6 - 1) + this.groupItemSize * 3 + this.groupItemSizeLarge * 3;
            this.listChildrenSize.update(i, height);
          }
        })
        .width('25%')
        .height(60)
        .type(ButtonType.Normal)
        .borderRadius(10)
        Button() {
          Text('group prevItemSize-50')
        }
        .onClick(() => {
          if (this.groupItemSizeLarge < 50) {
            return;
          }
          this.groupItemSizeLarge -= 50;
          for (let i = 0; i < 10; i++) {
            let temp: ChildrenMainSize = new ChildrenMainSize(this.groupItemSize);
            temp.splice(0, 3, [this.groupItemSizeLarge, this.groupItemSizeLarge, this.groupItemSizeLarge]);
            this.groupChildrenSize[i] = temp;
          }
          for (let i = 0; i < 10; i++) {
            if (i === 5 || i === 6) {
              continue;
            }
            // recalculate and update ListItemGroup height info.
            let height = 50 * 2 + this.space4Group * (6 - 1) + this.groupItemSize * 3 + this.groupItemSizeLarge * 3;
            this.listChildrenSize.update(i, height);
          }
        })
        .width('25%')
        .height(60)
        .type(ButtonType.Normal)
        .borderRadius(10)
      }
    }
    .width('100%')
    .height(1000)
    .backgroundColor(Color.Black)
  }
}
