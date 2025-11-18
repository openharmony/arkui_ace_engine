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
 * Description: Grid组件支持基于断点自适应列数
 * Writer: renxiaowen
 */

import { GridDataSource } from './GridDataSource';

@Entry
@Component
struct GridExample {
  @State columnsTemplatePool: string[] = ['undefined', 'null', '1fr', '1fr 2fr', '3fr 2fr', '1fr 3fr', '1fr 1fr 1f']
  @State columnsTemplateIndex: number = 0
  @State template: string = '1fr 1fr'
  private arr1: string[] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12'];
  scroller: Scroller = new Scroller();
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12];
  @State clipContent: ContentClipMode | RectShape | undefined = undefined;
  @State stringIndex: number = 0;
  @State stringList: PresetFillType[] = [
    1, 3, 5, PresetFillType.BREAKPOINT_DEFAULT, PresetFillType.BREAKPOINT_SM1MD2LG3, PresetFillType.BREAKPOINT_SM2MD3LG5
  ]
  @State stringListStr: Array<string> = [
    '1', '3', '5', 'PresetFillType.BREAKPOINT_DEFAULT', 'PresetFillType.BREAKPOINT_SM1MD2LG3',
    'PresetFillType.BREAKPOINT_SM2MD3LG5'
  ]
  @State fileType: PresetFillType = PresetFillType.BREAKPOINT_DEFAULT;
  @State badgeColorIndex: number = 0;
  @State badgeColorIndex1: number = 0;
  @State badgeColorList: (string)[] = [
    '5%', '30%', '50%', '80%', '100%', '800'
  ]
  @State badgeColorList1: (string)[] = [
    '5%', '30%', '50%', '80%', '100%', '800'
  ]
  numbers: GridDataSource = new GridDataSource([]);

  build() {
    Scroll() {
      Column() {
        Text('columnsTemplate列宽')
        Row() {
          Text('columnsTemplate: ' + this.columnsTemplatePool[this.columnsTemplateIndex])
            .fontSize(12)
            .fontColor(0x696969)
          Button('columnsTemplate:' + this.columnsTemplateIndex).onClick(() => {
            this.columnsTemplateIndex = (this.columnsTemplateIndex + 1) % this.columnsTemplatePool.length;
            this.template = this.columnsTemplatePool[this.columnsTemplateIndex];
          })
        }

        Grid(undefined) {
          ForEach(this.arr, (item: number) => {
            GridItem() {
              Text(item.toString())
                .width('50%')
                .height(80)
                .fontSize(20)
                .textAlign(TextAlign.Center)
                .backgroundColor(Color.Grey)
            }
          }, (item: string) => item)
        }
        .backgroundColor(Color.Blue)
        .clipContent(this.clipContent)
        .scrollBar(BarState.Off)
        .friction(0.6)
        .width(300)
        .height('50%')
        .padding(10)
        .margin({ top: 20 })
        .columnsTemplate('' + this.template)

      }.width('100%').backgroundColor(0xDCDCDC)
    }
  }
}