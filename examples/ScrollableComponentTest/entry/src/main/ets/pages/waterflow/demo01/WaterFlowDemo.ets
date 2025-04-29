import { ImgEntity } from './ImgEntity';
import { BaseDataSource } from './BaseDataSource';
import { ProductCardWidget } from './ItemCard';

/**
 * 默认模式分组情况下缓存区布局延迟加载item高度出现重叠现象的demo，问题已修复
 */
@Entry
@Component
struct WaterFlowDemo {
  @State colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F];
  scroller: Scroller = new Scroller();
  @State itemList: BaseDataSource<ImgEntity> = new BaseDataSource();
  @State sections: WaterFlowSections = new WaterFlowSections();
  @State list1: ImgEntity[] = [];

  aboutToAppear() {
    this.initList();
    this.initSections();
  }

  initList() {
    let list = new Array<ImgEntity>(40);
    for (let i = 0; i < 39; i++) {
      list[i] = new ImgEntity(this.colors[i % 5])
    }
    list[39] = new ImgEntity(Color.Black, 0, true);
    this.itemList.addAllData(list);
  }

  initSections() {
    let sectionOptions: SectionOptions[] = [];
    let listSection: SectionOptions = {
      itemsCount: this.itemList.totalCount() - 1,
      crossCount: 2,
      columnsGap: 8,
      rowsGap: 8,
      margin: 8
    };
    sectionOptions.push(listSection);
    let dividerSection: SectionOptions = {
      itemsCount: 1,
      crossCount: 1
    }
    sectionOptions.push(dividerSection);
    this.sections.splice(0, 0, sectionOptions);

  }

  build() {
    List() {
      ListItem() {
        Column() {
          Text('Title')
            .fontColor(Color.Blue)
            .fontSize(40)
        }
        .width('100%')
        .height(100)
        .alignItems(HorizontalAlign.Center)
        .justifyContent(FlexAlign.End)
        .backgroundColor(Color.Green)
      }

      ListItem() {
        Row() {
          Text('text1')
            .width(0)
            .height('100%')
            .layoutWeight(1)
            .textAlign(TextAlign.Center)
          Text('text2')
            .width(0)
            .height('100%')
            .layoutWeight(1)
            .textAlign(TextAlign.Center)
          Text('text3')
            .width(0)
            .height('100%')
            .layoutWeight(1)
            .textAlign(TextAlign.Center)
          Text('text4')
            .width(0)
            .height('100%')
            .layoutWeight(1)
            .textAlign(TextAlign.Center)
        }
        .width('100%')
        .height(40)
        .backgroundColor(Color.Orange)
      }

      ListItem() {
        this.productListView();
      }
      .width('100%')
      .height('100%')
    }
    .width('100%')
    .height('100%')
    .edgeEffect(EdgeEffect.None)
    .scrollBar(BarState.Off)
    .backgroundColor('#f5f5f5')
  }

  @Builder
  private productListView() {
    WaterFlow({ scroller: this.scroller, sections: this.sections, layoutMode: WaterFlowLayoutMode.ALWAYS_TOP_DOWN }) {
      LazyForEach(this.itemList, (item: ImgEntity, index: number) => {
        FlowItem() {
          ProductCardWidget({
            item: item,
            index: index
          })
        }
        .width('100%')
        .height('auto')
      }, (item: string, index: number) => index.toString())
    }
    .columnsTemplate('1fr 1fr')
    .width('100%')
    .height('auto')
    .cachedCount(10)
    .edgeEffect(EdgeEffect.None)
  }
}