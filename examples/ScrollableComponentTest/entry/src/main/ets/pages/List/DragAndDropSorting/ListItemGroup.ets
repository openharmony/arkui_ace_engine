class ListBasicDataSource implements IDataSource {
  private listeners: DataChangeListener[] = [];
  private originDataArray: string[] = [];

  public totalCount(): number {
    return 0;
  }

  public getData(index: number): string {
    return this.originDataArray[index];
  }

  // 该方法为框架侧调用，为LazyForEach组件向其数据源处添加listener监听
  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      console.info('add listener');
      this.listeners.push(listener);
    }
  }

  // 该方法为框架侧调用，为对应的LazyForEach组件在数据源处去除listener监听
  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      console.info('remove listener');
      this.listeners.splice(pos, 1);
    }
  }

  // 通知LazyForEach组件需要重载所有子组件
  notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded();
    })
  }

  // 通知LazyForEach组件需要在index对应索引处添加子组件
  notifyDataAdd(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataAdd(index);
      // 写法2：listener.onDatasetChange([{type: DataOperationType.ADD, index: index}]);
    })
  }

  // 通知LazyForEach组件在index对应索引处数据有变化，需要重建该子组件
  notifyDataChange(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataChange(index);
      // 写法2：listener.onDatasetChange([{type: DataOperationType.CHANGE, index: index}]);
    })
  }

  // 通知LazyForEach组件需要在index对应索引处删除该子组件
  notifyDataDelete(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataDelete(index);
      // 写法2：listener.onDatasetChange([{type: DataOperationType.DELETE, index: index}]);
    })
  }

  // 通知LazyForEach组件将from索引和to索引处的子组件进行交换
  notifyDataMove(from: number, to: number): void {
    this.listeners.forEach(listener => {
      listener.onDataMove(from, to);
      // 写法2：listener.onDatasetChange(
      //         [{type: DataOperationType.EXCHANGE, index: {start: from, end: to}}]);
    })
  }

  notifyDatasetChange(operations: DataOperation[]): void {
    this.listeners.forEach(listener => {
      listener.onDatasetChange(operations);
    })
  }
}

class MyListDataSource extends ListBasicDataSource {
  private dataArray: string[] = [];

  public totalCount(): number {
    return this.dataArray.length;
  }

  public getData(index: number): string {
    return this.dataArray[index];
  }

  public addData(index: number, data: string): void {
    this.dataArray.splice(index, 0, data);
    this.notifyDataAdd(index);
  }

  public moveDataWithoutNotify(from: number, to: number): void {
    let tmp = this.dataArray.splice(from, 1);
    this.dataArray.splice(to, 0, tmp[0]);
  }

  public pushData(data: string): void {
    this.dataArray.push(data);
    this.notifyDataAdd(this.dataArray.length - 1);
  }

  public deleteData(index: number): void {
    this.dataArray.splice(index, 1);
    this.notifyDataDelete(index);
  }

  public getIndexOf(item: string): number {
    return this.dataArray.indexOf(item);
  }
}

@Entry
@Component
struct ParentList {
  private data: MyListDataSource = new MyListDataSource();
  @State itemHeight: number = 100;
  @State bigIndex: number = -1;

  getIndex(item: string): number {
    return this.data.getIndexOf(item);
  }

  // 注意: 示例实现只能处理占一行节点中间固定4个其他节点的场景
  needOffset(item: string): boolean {
    let index = this.getIndex(item);
    // 变大节点之前
    if (index <= this.bigIndex) {
      return false;
    }
    // 一行节点变大，后面的整体下移
    if (this.bigIndex % 5 === 0) {
      return index > this.bigIndex;
    }
    // 变大节点后面的组（中间隔了一个一行节点），整体下移
    let thisGroup = Math.floor(this.bigIndex / 5);
    let nextGroupStart = (thisGroup + 1) * 5;
    if (index >= nextGroupStart) {
      return true;
    }
    // 变大节点同组（两个1行节点中间），所在列下移
    return (index - thisGroup * 5) % 2 === (this.bigIndex - thisGroup * 5) % 2;
  }

  build() {
    Row() {
      List() {
        LazyForEach(this.data, (item: string, index: number) => {
          if (index % 5 === 0) {
            // 通过ListItemGroup和设置子节点宽度实现跨一行的节点
            ListItemGroup() {
              ListItem() {
                Text(item.toString())
                  .fontSize(16)
                  .textAlign(TextAlign.Center)
                  .size({ height: this.getIndex(item) === this.bigIndex ? 220 : 100, width: '220%' })
                  .backgroundColor('#FFFFFFFF')
                  .onClick(() => {
                    let i = this.getIndex(item);
                    if (this.bigIndex === i) {
                      this.bigIndex = -1;
                    } else {
                      this.bigIndex = i;
                    }
                  })
              }.margin(10)
              .borderRadius(10)
              .height(100)
              // 变大节点所在列下方的item加offset
              .offset({ top: (this.bigIndex >= 0 && this.needOffset(item)) ? 100 + 20 : 0 })
            }
          } else {
            ListItem() {
              Text(item.toString())
                .fontSize(16)
                .textAlign(TextAlign.Center)
                .size({ height: this.getIndex(item) === this.bigIndex ? 220 : 100, width: '100%' })
                .backgroundColor('#FFFFFFFF')
                .onClick(() => {
                  let i = this.getIndex(item);
                  if (this.bigIndex === i) {
                    this.bigIndex = -1;
                  } else {
                    this.bigIndex = i;
                  }
                })
            }
            .margin(10)
            .borderRadius(10)
            .height(100)
            // 变大节点所在列下方的item加offset
            .offset({ top: (this.bigIndex >= 0 && this.needOffset(item)) ? 100 + 20 : 0 })
          }
        }, (item: string, index: number) => item + index) // 拖拽排序
          .onMove((from: number, to: number) => {
            this.data.moveDataWithoutNotify(from, to);
          })
      }
      // 避免加offset后滚动看不到最下面的节点
      .safeAreaPadding({ bottom: this.bigIndex === -1 ? 0 : 100 })
      // 滚动组件List/Grid/WaterFlow设置不裁剪SAFE_AREA内容
      .clipContent(ContentClipMode.SAFE_AREA)
      // 滚动组件List/Grid/WaterFlow设置显示缓存节点
      .cachedCount(1, true)
      // 两列的List
      .lanes(2, 10)
      .width('100%')
      .height('100%')
      .backgroundColor('#FFDCDCDC')
    }
  }

  aboutToAppear(): void {
    for (let i = 0; i < 100; i++) {
      this.data.pushData(i.toString());
    }
  }
}