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

// Index.ets
import { WaterFlowDataSource } from '../../WaterFlowDataSource';
import { image } from '@kit.ImageKit';

// 可复用组件：优化性能，减少组件创建销毁开销
@Reusable
@Component
struct ReusableFlowItem {
  @State item: number = 0;

  // 从复用缓存中加入到组件树之前调用，可在此处更新组件的状态变量以展示正确的内容
  aboutToReuse(params: Record<string, number>) {
    this.item = params.item;
  }

  build() {
    Column() {
      Text('N' + this.item).fontSize(12).height('16')
      // 注意：需要确保对应的jpg文件存在才会正常显示
      Image('res/waterFlow(' + this.item % 5 + ').jpg')
        .objectFit(ImageFit.Fill)
        .width('100%')
        .layoutWeight(1)
    }
  }
}

@Entry
@Component
struct WaterFlowDemo55 {
  @State columnIndex: number = 0;
  @State columnList: (string | ItemFillPolicy | undefined | null)[] = [
    '1fr 2fr 1fr',
    { fillType: PresetFillType.BREAKPOINT_DEFAULT },
    { fillType: PresetFillType.BREAKPOINT_SM1MD2LG3 },
    { fillType: PresetFillType.BREAKPOINT_SM2MD3LG5 },
    undefined,
    null
  ]
  @State widthIndex: number = 0;
  @State widthList: (string)[] = [
    '100%', '80%', '60%', '20%'
  ]
  @State directionIndex: number = 0;
  @State directionList: (FlexDirection)[] = [
    FlexDirection.Row,
    FlexDirection.Column,
    FlexDirection.RowReverse,
    FlexDirection.ColumnReverse
  ]
  minSize: number = 80;
  maxSize: number = 180;
  colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F];
  dataSource: WaterFlowDataSource = new WaterFlowDataSource();
  private itemWidthArray: number[] = [];
  private itemHeightArray: number[] = [];
  scroller: Scroller = new Scroller();
  @State columns: number = 2;
  @State waterFlowScale: number = 1;
  @State imageScale: number = 1;
  @State waterFlowOpacity: number = 1;
  @State waterFlowSnapshot: image.PixelMap | undefined = undefined;
  private columnChanged: boolean = false;
  private oldColumn: number = this.columns;
  private pinchTime: number = 0;
  dataCount: number = this.dataSource.totalCount();
  @State changeCachedCountIndex: number = 0;
  @State changeCachedCountList: (number | undefined | null)[] = [
    2, -2, 0, undefined, null
  ];
  @State changeCachedCountBolIndex: number = 0;
  @State changeCachedCountBolList: (boolean | undefined | null)[] = [
    true, false, undefined, null
  ];
  @State contentWidth: number = -1;
  @State contentHeight: number = -1;
  @State gapIndex: number = 0;
  @State gaps: number[] = [
    0, 10, 20
  ]
  @State paddingIndex: number = 0;
  @State paddings: number[] = [
    0, 10, 20
  ]
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

  // 计算FlowItem宽/高
  getSize() {
    let ret = Math.floor(Math.random() * this.maxSize);
    return (ret > this.minSize ? ret : this.minSize);
  }

  // 设置FlowItem的宽/高数组
  setItemSizeArray() {
    for (let i = 0; i < 100; i++) {
      this.itemWidthArray.push(this.getSize());
      this.itemHeightArray.push(this.getSize());
    }
  }

  // 组件生命周期：初始化数据和恢复上次的列数设置
  aboutToAppear() {
    // 读取上次最后切换到到列数
    let lastCount = AppStorage.get<number>('columnsCount');
    if (typeof lastCount != 'undefined') {
      this.columns = lastCount;
    }
    this.setItemSizeArray();
    // 初始化瀑布流分组信息
    let sectionOptions: SectionOptions[] = [];
    let count = 0;
    let oneOrTwo = 0;
    while (count < this.dataCount) {
      sectionOptions.push(this.twoColumnSection);
      count += this.twoColumnSection.itemsCount;
    }
    this.sections.splice(0, 0, sectionOptions);
  }

  // 根据缩放阈值改变列数，触发WaterFlow重新布局
  changeColumns(scale: number) {
    if (scale > (this.columns / (this.columns - 0.5)) && this.columns > 1) {
      this.columns--;
      this.columnChanged = true;
    } else if (scale < 1 && this.columns < 4) {
      this.columns++;
      this.columnChanged = true;
    }
  }

  build() {
    Column({ space: 2 }) {

      Row() {
        Button('column' + this.columnIndex)
          .onClick(() => {
            this.columnIndex++;
            if (this.columnIndex > this.columnList.length - 1) {
              this.columnIndex = 0;
            }
          })
        Button('width' + this.widthIndex)
          .onClick(() => {
            this.widthIndex++;
            if (this.widthIndex > this.widthList.length - 1) {
              this.widthIndex = 0;
            }
          })
        Button('direction' + this.directionIndex)
          .onClick(() => {
            this.directionIndex++;
            if (this.directionIndex > this.directionList.length - 1) {
              this.directionIndex = 0;
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
        Button('rowGap')
          .onClick(() => {
            this.gapIndex++;
            if (this.gapIndex > this.gaps.length - 1) {
              this.gapIndex = 0;
            }
          })
      }

      Row() {
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
      Text('gap：' + this.gaps[this.gapIndex])
        .fontColor(Color.Blue)
        .height(15)
      Text('padding：' + this.paddings[this.paddingIndex])
        .fontColor(Color.Green)
        .height(15)
      Stack() {
        // 用于展示缩放前的WaterFlow截图
        Image(this.waterFlowSnapshot)
          .width('100%')
          .height('100%')
          .scale({
            x: this.imageScale,
            y: this.imageScale,
            centerX: 0,
            centerY: 0
          })

        WaterFlow({
          scroller: this.scroller,
          layoutMode: WaterFlowLayoutMode.SLIDING_WINDOW,
          footer: this.itemFoot()
        }) {
          Repeat<number>(this.dataSource.dataArray)
            .each((ri: RepeatItem<number>) => {
              FlowItem() {
                // 使用可复用组件，提升性能
                Column() {
                  Text('R' + ri.item).fontSize(12).height('16')
                }
                .height(ri.item * 11)
              }
              .padding(this.paddings[this.paddingIndex])
              .width('100%')
              //.aspectRatio(this.itemHeightArray[ri.item % 100] / this.itemWidthArray[ri.item%100])
              .backgroundColor(this.colors[ri.item % this.colors.length])
            })
        }
        .clip(false)
        .syncLoad(true)
        .padding(this.paddings[this.paddingIndex])
        .rowsGap(this.gaps[this.gapIndex])
        .cachedCount(this.changeCachedCountList[this.changeCachedCountIndex],
          this.changeCachedCountBolList[this.changeCachedCountBolIndex])
        .id('waterflow') // 设置id用于截图
        .columnsTemplate(this.columnList[this.columnIndex])
        .layoutDirection(this.directionList[this.directionIndex])
        .backgroundColor(0xFAEEE0)
        .width('100%')
        .height('50%')
        .layoutWeight(1)
        .opacity(this.waterFlowOpacity)
        .scale({
          x: this.waterFlowScale,
          y: this.waterFlowScale,
          centerX: 0,
          centerY: 0
        })
        .priorityGesture(
          PinchGesture()
            .onActionStart((event: GestureEvent) => {
              // 双指捏合手势识别成功时截图
              this.pinchTime = event.timestamp;
              this.columnChanged = false;
              this.oldColumn = this.columns;
              this.getUIContext().getComponentSnapshot().get('waterflow', (error: Error, pixmap: image.PixelMap) => {
                if (error) {
                  console.info('error:' + JSON.stringify(error));
                  return;
                }
                this.waterFlowSnapshot = pixmap;
              })
            })
            .onActionUpdate((event: GestureEvent) => {
              // 手势更新：处理缩放逻辑和视觉效果
              // 边界限制：防止超出列数范围时继续缩放
              if ((this.oldColumn === 1 && event.scale > 1) || (this.oldColumn === 4 && event.scale < 1)) {
                return;
              }

              // 节流处理：避免过于频繁的更新，提升性能
              if (event.timestamp - this.pinchTime < 10000000) {
                return;
              }
              this.pinchTime = event.timestamp;

              this.waterFlowScale = event.scale;
              this.imageScale = event.scale;
              // 根据缩放比例设置WaterFlow透明度
              this.waterFlowOpacity = (this.waterFlowScale > 1) ? (this.waterFlowScale - 1) : (1 - this.waterFlowScale);
              this.waterFlowOpacity *= 3;
              if (!this.columnChanged) {
                this.changeColumns(event.scale);
              }

              // 列数改变后的缩放比例调整：避免出现空白区域
              if (this.columnChanged) {
                this.waterFlowScale = this.imageScale * this.columns / this.oldColumn;

                // 限制缩放范围，确保视觉效果自然
                if (event.scale < 1) {
                  this.waterFlowScale = this.waterFlowScale > 1 ? this.waterFlowScale : 1;
                } else {
                  this.waterFlowScale = this.waterFlowScale < 1 ? this.waterFlowScale : 1;
                }
              }
            })
            .onActionEnd((event: GestureEvent) => {
              // 手势结束：执行归位动画并保存状态
              // 执行归位动画：平滑过渡到正常状态
              this.getUIContext()?.animateTo({ duration: 300 }, () => {
                this.waterFlowScale = 1;
                this.waterFlowOpacity = 1;
              })

              // 持久化保存当前列数：下次启动时恢复
              AppStorage.setOrCreate<number>('columnsCount', this.columns);
            })
        )
      }
    }
  }
}