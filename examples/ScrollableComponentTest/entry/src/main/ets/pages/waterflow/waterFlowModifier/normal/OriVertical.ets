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

class waterFlowModifier implements AttributeModifier<WaterFlowAttribute> {
  index: number = 0;
  columnList: (string | ItemFillPolicy | undefined | null)[] = [
    '1fr 2fr 1fr',
    { fillType: PresetFillType.BREAKPOINT_DEFAULT },
    { fillType: PresetFillType.BREAKPOINT_SM2MD3LG5 },
    { fillType: PresetFillType.BREAKPOINT_SM1MD2LG3 },
    undefined,
    null
  ]

  applyNormalAttribute(instance: WaterFlowAttribute): void {
    instance.columnsTemplate(this.columnList[this.index])
  }
}

@Entry
@Component
struct waterExample9 {
  @State waterFlowMod: waterFlowModifier = new waterFlowModifier();
  @State widthIndex: number = 0;
  @State widthList: (string)[] = [
    '100%', '80%', '60%', '20%'
  ]
  @State arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  @State arrIndex: number = 10;
  @State editFlag: boolean = false;
  @State changeCachedCountIndex: number = 0;
  @State contentWidth: number = -1;
  @State contentHeight: number = -1;
  @State changeCachedCountList: (number | undefined | null)[] = [
    2, -2, 0, undefined, null
  ];
  @State changeCachedCountBolIndex: number = 0;
  @State changeCachedCountBolList: (boolean | undefined | null)[] = [
    true, false, undefined, null
  ];
  @State changelistDirectionIndex: number = 0;
  @State changelistDirectionList: (FlexDirection | undefined | null)[] = [
    FlexDirection.Column, FlexDirection.ColumnReverse, FlexDirection.Row, FlexDirection.RowReverse, undefined, null
  ];
  @State changelistLayoutModeIndex: number = 0;
  @State changelistLayoutModeList: (WaterFlowLayoutMode | undefined | null)[] = [
    WaterFlowLayoutMode.ALWAYS_TOP_DOWN, WaterFlowLayoutMode.SLIDING_WINDOW, undefined, null
  ];
  @State itemHeight: Length = 100;
  @State itemWidth: Length = '100%';
  minSize: number = 80;
  maxSize: number = 180;
  fontSize: number = 24;
  colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F];
  scroller: Scroller = new Scroller();
  private itemHeightArray: number[] = [];
  @State sections: WaterFlowSections = new WaterFlowSections();
  sectionMargin: Margin = {
    top: 10,
    left: 5,
    bottom: 10,
    right: 5
  };
  oneColumnSection: SectionOptions = {
    itemsCount: 4,
    crossCount: 1,
    columnsGap: '5vp',
    rowsGap: 10,
    margin: this.sectionMargin,
    onGetItemMainSizeByIndex: (index: number) => {
      return this.itemHeightArray[index % 100];
    }
  };
  twoColumnSection: SectionOptions = {
    itemsCount: 1,
    crossCount: 1,
    onGetItemMainSizeByIndex: (index: number) => {
      return 100;
    }
  };
  lastSection: SectionOptions = {
    itemsCount: 20,
    crossCount: 2,
    onGetItemMainSizeByIndex: (index: number) => {
      return this.itemHeightArray[index % 100];
    }
  };
  @State changeSyncLoadIndex: number = 0;
  @State changeSyncLoadList: (boolean | undefined | null)[] = [
    true, false, undefined, null
  ]
  @State gapIndex: number = 0;
  @State gaps: number[] = [
    0, 10, 20
  ]
  @State paddingIndex: number = 0;
  @State paddings: number[] = [
    0, 10, 20
  ]

  @Builder
  itemFoot() {
    Column() {
      Text(`Footer`)
        .fontSize(10)
        .backgroundColor(Color.Red)
        .width(50)
        .height(100)
        .align(Alignment.Center)
      // .margin({ top: 20,bottom:5 })
    }
  }

  // 计算FlowItem高度
  getSize() {
    let ret = Math.floor(Math.random() * this.maxSize);
    return (ret > this.minSize ? ret : this.minSize);
  }

  // 设置FlowItem的高度数组
  setItemSizeArray() {
    for (let i = 0; i < 100; i++) {
      this.itemHeightArray.push(this.getSize());
    }
  }

  aboutToAppear() {
  }

  build() {
    Scroll() {
      Column() {
        Row() {
          Button('column: ' + this.waterFlowMod.columnList[this.waterFlowMod.index]).onClick(() => {
            this.waterFlowMod.index++;
            this.waterFlowMod.index = this.waterFlowMod.index % this.waterFlowMod.columnList.length;
          })
          Button('width' + this.widthIndex)
            .onClick(() => {
              this.widthIndex++;
              if (this.widthIndex > this.widthList.length - 1) {
                this.widthIndex = 0;
              }
            })
        }

        Row() {
          Button('CachedCount')
            .onClick(() => {
              this.changeCachedCountIndex++;
              if (this.changeCachedCountIndex > this.changeCachedCountList.length - 1) {
                this.changeCachedCountIndex = 0;
              }
            })
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

            let value = this.changelistDirectionList[this.changelistDirectionIndex];

            if (value == FlexDirection.Column || value == FlexDirection.ColumnReverse || value == undefined ||
              value == null) {
              this.itemHeight = 100;
              this.itemWidth = '100%';
            }

            if (value == FlexDirection.Row || value == FlexDirection.RowReverse) {
              this.itemHeight = '100%';
              this.itemWidth = 100;
            }
          })
        }

        Row() {
          Button('rowGap')
            .onClick(() => {
              this.gapIndex++;
              if (this.gapIndex > this.gaps.length - 1) {
                this.gapIndex = 0;
              }
            })
          Button('padding')
            .onClick(() => {
              this.paddingIndex = (this.paddingIndex + 1) % this.paddings.length;
            })

        }

        Text('Width：' + this.contentWidth + '，Height：' + this.contentHeight)
          .fontColor(Color.Red)
          .height(15)
        Text('Index：' + this.changeCachedCountIndex + '，CachedCount数值：' +
        this.changeCachedCountList[this.changeCachedCountIndex])
          .fontColor(Color.Yellow)
          .height(15)
        Text('Index：' + this.changeCachedCountBolIndex + '，CachedCount数值：' +
        this.changeCachedCountBolList[this.changeCachedCountBolIndex])
          .fontColor(Color.Orange)
          .height(15)
        Text('Index：' + this.changelistDirectionIndex + '，listDirection数值：' +
        this.changelistDirectionList[this.changelistDirectionIndex])
          .fontColor(Color.Pink)
          .height(15)
        Text('gap：' + this.gaps[this.gapIndex])
          .fontColor(Color.Blue)
          .height(15)
        Text('padding：' + this.paddings[this.paddingIndex])
          .fontColor(Color.Green)
          .height(15)
        WaterFlow({ scroller: this.scroller, footer: this.itemFoot() }) {
          ForEach(this.arr, (item: number, index?: number) => {
            FlowItem() {
              Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
                Text('' + item)
                  .width(this.itemWidth)
                  .height(this.itemHeight)
                  .fontSize(16)
                  .textAlign(TextAlign.Center)
                  .borderRadius(10)
                  .backgroundColor(0xFFFFFF)
                if (this.editFlag) {
                  Button() {
                    Text('delete').fontSize(16)
                  }.width('30%').height(40)
                  .onClick(() => {
                    if (index != undefined) {
                      this.arr.splice(index, 1)
                      this.editFlag = false
                    }
                  }).stateEffect(true)
                }
              }
            }.padding({ top: this.paddings[this.paddingIndex] })
          }, (item: number) => item.toString())
        }
        .attributeModifier(this.waterFlowMod)
        .syncLoad(true)
        .layoutDirection(this.changelistDirectionList[this.changelistDirectionIndex]) // 测试点：排列方向
        .scrollBar(BarState.Off)
        .edgeEffect(EdgeEffect.Spring) // 边缘效果设置为Spring
        .padding(this.paddings[this.paddingIndex])
        .rowsGap(this.gaps[this.gapIndex])
        .cachedCount(this.changeCachedCountList[this.changeCachedCountIndex],
          this.changeCachedCountBolList[this.changeCachedCountBolIndex])
        .height(400)
        .width('90%')
      }
      .width(this.widthList[this.widthIndex])
      .height('100%')
      .backgroundColor(0xDCDCDC)
    }
    .height('300%')
  }
}