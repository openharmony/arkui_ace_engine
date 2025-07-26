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

import { CommonAppGridLayoutUtility } from './GridLayoutOptionsUtil';
import { GridList } from './GridList.ets';

@Entry
@Component
struct Index {
  @State message: string = 'Hello World';

  build() {
    Stack() {
      GridTest()
    }
    .height('100%')
    .width('100%')
  }
}

@Component
struct GridTest {
  @State appGridList: GridListItem[] = [];
  @State gridOptions: GridLayoutOptions =
    CommonAppGridLayoutUtility.getInstance().getGridLayoutOptions(this.appGridList);
  private count: number = 0;
  @State maxRow: number = 0;
  @State maxCol: number = 0;

  @Styles
  selectStyles(): void {
    .backgroundColor('#ED6F21')
    .borderWidth(2)
  }

  @Styles
  normalStyles(): void {
    .backgroundColor(Color.Red)
    .borderWidth(0)
  }

  @Styles
  disabledStyles(): void {
    .backgroundColor('#E5E5E5')
    .borderRadius(10)
    .borderStyle(BorderStyle.Solid)
    .borderWidth(2)
    .borderColor('#2a4c1919')
    .width(90)
    .height(25)
    .opacity(1)
  }

  aboutToAppear(): void {
    // 5*8
    this.maxRow = 5;
    this.maxCol = 8;
    for (let i = 0; i < 40; i++) {
      let item = new GridListItem();
      item.data = 'test' + i;
      item.col = i % this.maxCol;
      item.row = i / this.maxCol;
      this.appGridList.push(item);
    }
  }

  onGridListUpdate(): void {
    if (this.count % 2 === 0) {
      // 4*10
      this.maxRow = 4;
      this.maxCol = 10;
    } else {
      this.maxRow = 5;
      this.maxCol = 8;
    }
    let appList: GridListItem[] = [];
    for (let i = 0; i < this.appGridList.length; i++) {
      let item = this.appGridList[i];
      item.col = i % this.maxCol;
      item.row = i / this.maxCol;
      appList.push(item);
    }
    this.appGridList = appList;
    let appCopy: GridListItem[] = new Array();
    this.appGridList.forEach((item) => {
      appCopy.push(item);
    })
    this.gridOptions = CommonAppGridLayoutUtility.getInstance().getGridLayoutOptions(appCopy);
    this.count++;
  }

  private getColumnsTemplate() {
    let columnsTemplate = '';
    for (let i = 0; i < this.maxCol; i++) {
      columnsTemplate += ' 1fr';
    }
    return columnsTemplate;
  }

  private getRowsTemplate() {
    let rowsTemplate = '';
    for (let i = 0; i < this.maxRow; i++) {
      rowsTemplate += ' 1fr';
    }
    return rowsTemplate;
  }

  private getForEachKey(item: GridListItem) {
    if (!item) {
      return 'AppGrid';
    }
    let key: string = AppGrid_${item.data}${item.row}${item.col};
    return key;
  }

  @Builder
  buildGridItem(item: GridListItem, index?: number) {
    GridItem() {
      Column() {
        Text(item.data)
          .fontSize(30)
      }
      .width('100%')
      .height('100%')
      .backgroundColor(Color.Grey)
    }
    .stateStyles({
      disabled: this.disabledStyles,
      selected: this.selectStyles,
      normal: this.normalStyles
    })
    .width(72)
    .height(72)
  }

  build() {
    Grid(undefined, this.gridOptions) {
      ForEach(this.appGridList, (item: GridListItem, index?: number) => {
        this.buildGridItem(item, index)
      }, (item: GridListItem, index: number) => this.getForEachKey(item))
    }
    .animation({ duration: 200 })
    .columnsTemplate(this.getColumnsTemplate())
    .rowsTemplate(this.getRowsTemplate())
    .columnsGap(8)
    .rowsGap(8)
    .width('100%')
    .height('100%')
    .multiSelectable(true)
    .onClick(() => {
      this.onGridListUpdate();
    })
    .backgroundColor(Color.Green)
    .padding({
      left: 10,
      top: 8,
      right: 10,
      bottom: 8
    })
  }
}