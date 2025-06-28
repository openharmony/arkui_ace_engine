// MyDataSource类实现IDataSource接口
class MyDataSource implements IDataSource {
  private dataArray: number[] = [];

  public pushData(data: number): void {
    this.dataArray.push(data);
  }

  // 数据源的数据总量
  public totalCount(): number {
    return this.dataArray.length;
  }

  // 返回指定索引位置的数据
  public getData(index: number): number {
    return this.dataArray[index];
  }

  registerDataChangeListener(listener: DataChangeListener): void {
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
  }
}

class MyButtonModifier implements AttributeModifier<GridAttribute> {
  public syncLoad: boolean = false;

  applyNormalAttribute(instance: GridAttribute): void {
    instance.syncLoad(this.syncLoad);
  }
}

@Entry
@Component
export struct PageGrid {
  // 数据源
  private data: MyDataSource = new MyDataSource();
  private scroller: Scroller = new Scroller();
  @State style: GridItemOptions | undefined | null = null;
  @State modifier: MyButtonModifier = new MyButtonModifier();

  aboutToAppear() {
    for (let i = 1; i < 1000; i++) {
      this.data.pushData(i);
    }
  }

  build() {
    NavDestination() {
      Column({ space: 6 }) {
        Button('scrollTo500').onClick(() => {
          this.scroller.scrollToIndex(500, false, ScrollAlign.START);
        })
        Button('scrollTo0').onClick(() => {
          this.scroller.scrollTo({ xOffset: 0, yOffset: 0 });
        })
        Button('scrollEdge').onClick(() => {
          this.scroller.scrollEdge(Edge.Bottom);
        })
        Button('PageDown').onClick(() => {
          this.scroller.scrollPage({ next: true });
        })
        Button('scrollBy').onClick(() => {
          this.scroller.scrollBy(0, 10000);
        })
        Button('PageUp').onClick(() => {
          this.scroller.scrollPage({ next: true });
        })
        Grid(this.scroller, { regularSize: [1, 1] }) {
          GridItem(this.style)
            .height(100)
            .backgroundColor(Color.Blue)
          LazyForEach(this.data, (item: number) => {
            GridItem(this.style) {
              // 使用可复用自定义组件
              ReusableChildComponent({ item: item })
            }
          }, (item: string) => item)
        }
        .syncLoad(false)
        .attributeModifier(this.modifier)
        .cachedCount(0) // 设置GridItem的缓存数量
        .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
        .columnsGap(10)
        .rowsGap(10)
        .margin(10)
        .height('100%')
        .width('100%')
        .backgroundColor(0xFAEEE0)
        .onScrollIndex((first: number, last: number) => {
          console.info(`first:${first}, last:${last}`);
        })
        .onReachStart(() => {
          console.info('onReachStart');
        })
        .onReachEnd(() => {
          console.info('onReachEnd');
        })
        .onDidScroll((scrollOffset: number, scrollState: ScrollState) => {
          console.info(`scrollOffset:${scrollOffset}, scrollState:${scrollState}`);
        })
      }
    }
  }
}

@Reusable
@Component
struct ReusableChildComponent {
  @State item: number = 0;

  // aboutToReuse从复用缓存中加入到组件树之前调用，可在此处更新组件的状态变量以展示正确的内容
  // aboutToReuse参数类型已不支持any，这里使用Record指定明确的数据类型。Record用于构造一个对象类型，其属性键为Keys，属性值为Type
  aboutToReuse(params: Record<string, number>) {
    this.item = params.item;
  }

  aboutToAppear(): void {
    let me = Date.now();
    let deadline = me + 10;
    while (true) {
      me = Date.now();
      if (me > deadline) {
        return;
      }
    }
  }

  build() {
    Column() {
      Text(`图片${this.item}`)
        .fontSize(16)
        .textAlign(TextAlign.Center)
    }
    .width('100%')
    .height(60)
    .backgroundColor(0xF9CF93)
    .onClick(() => {
      console.info(`index:${this.item} onClick`);
    })
    .onFocus(() => {
      console.info(`index:${this.item} onFocus`);
    })
    .onBlur(() => {
      console.info(`index:${this.item} onBlur`);
    })
  }
}