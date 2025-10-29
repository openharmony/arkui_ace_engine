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
 * Description: List组件支持基于断点配置lanes
 * Writer: renxiaowen
 */

// xxx.ets
import { ListDataSource, ProjectsDataSource, TimeTable, TimeTableDataSource } from './ListDataSource';

interface getItemRect {
  getItemRect: string;
}

interface InspectorInfo {
  $attrs: getItemRect;
}

class CustomModifier1 implements AttributeModifier<ListAttribute> {
  changeLanesValueIndex: number = 0;
  changeLanesValueList: (LengthConstrain | number | undefined | null | ItemFillPolicy)[] = [
    { fillType: PresetFillType.BREAKPOINT_SM1MD2LG3 }, { fillType: PresetFillType.BREAKPOINT_SM2MD3LG5 },
    { fillType: PresetFillType.BREAKPOINT_DEFAULT }, { fillType: PresetFillType.BREAKPOINT_SM2MD3LG5 },
    { minLength: 150, maxLength: 150 }, undefined, { minLength: -40, maxLength: -40 }, 0, 1, 2, -1, 1000,
    { fillType: 1 }, { fillType: 2 }, { fillType: 0 }, { fillType: 2 }
  ]
  changeLanesGutterIndex: number = 0;
  changeLanesGutterList: (Dimension | undefined | null)[] = [
    '10px', 20, '10vp', undefined, null, '20lpx', '10fp',
  ]

  applyNormalAttribute(instance: ListAttribute): void {
    instance.lanes(this.changeLanesValueList[this.changeLanesValueIndex],
      this.changeLanesGutterList[this.changeLanesGutterIndex])
  }
}

@Entry
@Component
struct ListExample111 {
  private arr: ListDataSource = new ListDataSource([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]);
  scrollerForList: Scroller = new Scroller()
  @State arrIndex: number = 10;
  @State editFlag: boolean = false
  @State contentWidth: number = -1;
  @State contentHeight: number = -1;
  itemGroupArray: TimeTableDataSource = new TimeTableDataSource([]);
  @State dataArr: Array<string> = []; // 数据源
  @State modifier1: CustomModifier1 = new CustomModifier1()
  @State changelistChildrenSizeIndex: number = 0;
  @State changelistChildrenSizeList: (ChildrenMainSize | undefined | null)[] = [
    undefined, new ChildrenMainSize(150), new ChildrenMainSize(300)
  ]
  @State changeCachedCountIndex: number = 0;
  @State changeCachedCountList: (number | undefined | null)[] = [
    2, -2, 0, undefined, null
  ]
  @State changeCachedCountBolIndex: number = 0;
  @State changeCachedCountBolList: (boolean | undefined | null)[] = [
    true, false, undefined, null
  ]
  @State changeWidthIndex: number = 0;
  @State changeWidthList: (string | undefined | null)[] = [
    '100%', '1920px', '800px', '3000px'
  ]
  @State changelistDirectionIndex: number = 0;
  @State changelistDirectionList: (Axis | undefined | null)[] = [
    Axis.Vertical, Axis.Horizontal
  ]
  @State contentStartOffset: number = 100;
  @State contentEndOffset: number = 100;
  @State itemHeight: Length = 100;
  @State itemWidth: Length = 200;

  aboutToAppear(): void {
    let timeTable: TimeTable[] = [
      {
        title: '星期一',
        projects: ['语文', '数学', '英语', '化学', '生物']
      },
      {
        title: '星期二',
        projects: ['物理', '化学', '生物', '化学', '生物']
      },
      {
        title: '星期三',
        projects: ['历史', '地理', '政治', '化学', '生物']
      },
      {
        title: '星期四',
        projects: ['美术', '音乐', '体育', '化学', '生物']
      }
    ];
    this.itemGroupArray = new TimeTableDataSource(timeTable);
    for (let i = 0; i < 10; i++) {
      this.dataArr.push(`data_${i}`); // 为数组添加一些数据
    }
  }

  @Builder
  itemHead(text: string) {
    Text(text)
      .fontSize(20)
      .backgroundColor(0xAABBCC)
      .width('100%')
      .padding(10)
      .height(50)
  }

  @Builder
  itemFoot(num: number) {
    Text('共' + num + '节课')
      .fontSize(16)
      .backgroundColor(0xAABBCC)
      .width('100%')
      .padding(20)
      .height(50)
  }

  build() {
    Column() {
      Row() {
        Button('width')
          .onClick(() => {
            this.changeWidthIndex++;
            if (this.changeWidthIndex > this.changeWidthList.length - 1) {
              this.changeWidthIndex = 0;
            }
          })
        Button('ChildrenSize')
          .onClick(() => {
            this.changelistChildrenSizeIndex++;
            if (this.changelistChildrenSizeIndex > this.changelistChildrenSizeList.length - 1) {
              this.changelistChildrenSizeIndex = 0;
            }
          })
        Button('CachedCount')
          .onClick(() => {
            this.changeCachedCountIndex++;
            if (this.changeCachedCountIndex > this.changeCachedCountList.length - 1) {
              this.changeCachedCountIndex = 0;
            }
          })
        Button('LanesGutter')
          .onClick(() => {
            this.modifier1.changeLanesGutterIndex++;
            if (this.modifier1.changeLanesGutterIndex > this.modifier1.changeLanesGutterList.length - 1) {
              this.modifier1.changeLanesGutterIndex = 0;
            }
          })
      }

      Row() {
        Button('CachedCountBol')
          .onClick(() => {
            this.changeCachedCountBolIndex++;
            if (this.changeCachedCountBolIndex > this.changeCachedCountBolList.length - 1) {
              this.changeCachedCountBolIndex = 0;
            }
          })
        Button(`更改排列方向`).onClick(() => {
          this.changelistDirectionIndex = this.changelistDirectionIndex + 1;
          if (this.changelistDirectionIndex >= this.changelistDirectionList.length) {
            this.changelistDirectionIndex = 0;
          }

          if (this.changelistDirectionList[this.changelistDirectionIndex] == Axis.Vertical) {
            let val: Length = this.itemHeight;
            this.itemHeight = this.itemWidth;
            this.itemWidth = val;
          }

          if (this.changelistDirectionList[this.changelistDirectionIndex] == Axis.Horizontal) {
            let val: Length = this.itemHeight;
            this.itemHeight = this.itemWidth;
            this.itemWidth = val;
          }
        })
        Button('LanesValue')
          .onClick(() => {
            this.modifier1.changeLanesValueIndex++;
            if (this.modifier1.changeLanesValueIndex > this.modifier1.changeLanesValueList.length - 1) {
              this.modifier1.changeLanesValueIndex = 0;
            }
          })
      }

      Text('Index：' + this.changelistChildrenSizeIndex + '，ChildrenSize数值：' +
      this.changelistChildrenSizeList[this.changelistChildrenSizeIndex])
        .fontColor(Color.Orange)
        .height(15)
      Text('Index：' + this.changeCachedCountIndex + '，CachedCount数值：' +
      this.changeCachedCountList[this.changeCachedCountIndex])
        .fontColor(Color.Pink)
        .height(15)
      Text('Index：' + this.changeCachedCountBolIndex + '，CachedCount数值：' +
      this.changeCachedCountBolList[this.changeCachedCountBolIndex])
        .fontColor(Color.Pink)
        .height(15)
      Text('Index：' + this.changelistDirectionIndex + '，listDirection数值：' +
      this.changelistDirectionList[this.changelistDirectionIndex])
        .fontColor(Color.Blue)
        .height(15)
      Text('Index：' + this.modifier1.changeLanesValueIndex + '，LanesValue数值：' +
      this.modifier1.changeLanesValueList[this.modifier1.changeLanesValueIndex])
        .fontColor(Color.Green)
        .height(15)
      Text('Index：' + this.modifier1.changeLanesGutterIndex + '，LanesGutter数值：' +
      this.modifier1.changeLanesGutterList[this.modifier1.changeLanesGutterIndex])
        .fontColor(Color.Green)
        .height(15)
      List({ space: 10, initialIndex: 0, scroller: this.scrollerForList }) { //测试点：space
        LazyForEach(this.itemGroupArray, (item: TimeTable) => {
          ListItemGroup({ header: this.itemHead(item.title), footer: this.itemFoot(item.projects.length) }) {
            LazyForEach(new ProjectsDataSource(item.projects), (project: string) => {
              ListItem() {
                Text(project)
                  .width('100%')
                  .height('100%')
                  .fontSize(20)
                  .textAlign(TextAlign.Center)
                  .backgroundColor(0xFFFFFF)
              }.borderWidth(1)
              .height(100)
            }, (item: string) => item)
          }
          
        })
      }
      .id('List')
      .clip(false)
      .listDirection(this.changelistDirectionList[this.changelistDirectionIndex]) // 测试点：排列方向
      .scrollBar(BarState.On)
      .divider({
        strokeWidth: 2,
        color: 0xFFFFFF,
        startMargin: 20,
        endMargin: 20
      }) // 每行之间的分界线
      .edgeEffect(EdgeEffect.Spring) // 边缘效果设置为Spring
      .childrenMainSize(this.changelistChildrenSizeList[this.changelistChildrenSizeIndex])
      .padding({ top: 10, left: 10 }) //测试点：padding
      .cachedCount(this.changeCachedCountList[this.changeCachedCountIndex],
        this.changeCachedCountBolList[this.changeCachedCountBolIndex])
      .attributeModifier(this.modifier1 as CustomModifier1)
      .contentStartOffset(this.contentStartOffset)
      .contentEndOffset(this.contentEndOffset)
      .width('90%')
      .height('50%')
    }
    .width(this.changeWidthList[this.changeWidthIndex])
    .height('100%')
    .backgroundColor(0xDCDCDC)
  }
}