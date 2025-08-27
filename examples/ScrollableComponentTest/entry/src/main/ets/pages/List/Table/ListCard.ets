import { CommonDataSource } from './CommonDataSource'

@Component
export struct ListCard {
  itemText?: string;
  @Watch('onScrollReset') @Link scrollStart: number;
  @Watch('onScrollOffsetChange') @Link scrollOffset: number;
  private onScroll = false;
  private selfScroll = false;
  private scroller = new Scroller();
  dataSource = new CommonDataSource<Number>();

  aboutToAppear(): void {
    let arr: Number[] = [];
    for (let i = 0; i < 30; i++) {
      arr.push(i);
    }
    this.dataSource.pushDataArray(...arr);
  }

  build() {
    List({ scroller: this.scroller }) {
      LazyForEach(this.dataSource, (item: Number) => {
        ListItem() {
          Text(item.toString())
            .width(80)
            .height(45)
        }
        .borderWidth(1)
        .borderColor(Color.Gray)
      })
    }
    .width('100%')
    // 填充父组件Row剩余空间
    .layoutWeight(1)
    // 关闭边缘回弹，无法做到多个List联动回弹
    .edgeEffect(EdgeEffect.None)
    // 设置比较大到cachedCount，进入界面后未操作时可以提前预加载，提高横向滑动效率
    // 否则多个横向List联动加载新节点容易导致卡顿
    .cachedCount(10)
    .scrollBar(BarState.Off)
    .listDirection(Axis.Horizontal)
    // 在组件出现时滚动到之前记录的位置
    .onAttach(() => {
      if (this.scrollOffset) {
        this.scroller.scrollTo({ xOffset: this.scrollOffset, yOffset: 0 });
      }
    })
    // 在区域变化时调整滚动位置
    .onAreaChange(() => {
      if (this.scrollOffset != this.scroller.currentOffset().xOffset) {
        this.scroller.scrollTo({ xOffset: this.scrollOffset, yOffset: 0 });
      }
    })
    // 在即将滚动事件回调中更新偏移，触发其他横向List联动
    .onWillScroll((scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => {
      // 标记是自身触发滚动，不要再调用scrollTo
      this.selfScroll = true;
      this.updateScrollOffset(scrollOffset);
    })
    .onScrollStart(() => {
      this.scrollStart++;
      this.onScroll = true;
    })
    .onScrollStop(() => {
      this.selfScroll = false;
      this.onScroll = false;
    })
  }

  // 在滚动时更新偏移量，并确保滚动位置正确
  private updateScrollOffset(willOffset: number) {
    if (this.onScroll) {
      let offset: number = this.scroller.currentOffset().xOffset;
      if (offset != undefined) {
        this.scrollOffset = offset+willOffset;
        this.scroller.scrollTo({ xOffset: this.scrollOffset, yOffset: 0 })
      }
    }
  }

  // 处理滚动状态
  private onScrollReset() {
    this.onScroll = false
  }

  // 处理偏移量的变化
  private onScrollOffsetChange() {
    console.info('Test ',
      'onScrollOffsetChange,itemText = ' + this.itemText + ' onScroll = ' + this.onScroll + '; offset = ' +
      this.scrollOffset)
    if (!this.onScroll) {
      this.scroller.scrollTo({ xOffset: this.scrollOffset, yOffset: 0 })
    }
  }
}