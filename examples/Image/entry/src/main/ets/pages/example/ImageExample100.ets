/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * ImageExample100 - 图片列表 / 瀑布流 / 懒加载综合示例
 *
 * 功能说明：
 * 1. 演示在 List、Grid、WaterFlow 三种典型列表容器中使用 Image 的最佳实践
 * 2. 通过 LazyForEach 实现按需加载，避免一次性创建大量图片节点
 * 3. 演示在卡片场景下使用 objectFit、borderRadius、shadow、scale 等增强视觉表现
 * 4. 演示通过 syncLoad / autoResize / interpolation 等优化列表加载性能
 * 5. 演示列表项点击、长按、滑动等多类型交互在图片列表中的应用
 *
 * 适用场景：
 * - 商品 / 壁纸 / 头像 / 缩略图 等大量图片的列表展示
 * - 信息流、瀑布流、相册等需要滚动加载的场景
 */

class ImageItem {
  id: number = 0;
  title: string = '';
  subtitle: string = '';
  ratio: number = 1;
  source: Resource = $r('app.media.startIcon');
  tag: string = '';

  constructor(id: number, title: string, subtitle: string, ratio: number,
    source: Resource, tag: string) {
    this.id = id;
    this.title = title;
    this.subtitle = subtitle;
    this.ratio = ratio;
    this.source = source;
    this.tag = tag;
  }
}

class ImageListDataSource implements IDataSource {
  private listeners: DataChangeListener[] = [];
  private items: ImageItem[] = [];

  totalCount(): number {
    return this.items.length;
  }

  getData(index: number): ImageItem {
    return this.items[index];
  }

  getAll(): ImageItem[] {
    return this.items;
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }

  setItems(items: ImageItem[]): void {
    this.items = items;
    this.listeners.forEach((listener) => listener.onDataReloaded());
  }

  appendItems(items: ImageItem[]): void {
    this.items = this.items.concat(items);
    this.listeners.forEach((listener) => listener.onDataReloaded());
  }
}

@Entry
@Component
struct ImageExample100 {
  @State currentTab: number = 0;
  @State itemCount: number = 30;
  @State cardScale: number = 1.0;
  @State cardRadius: number = 12;
  @State useLazy: boolean = true;
  @State useSyncLoad: boolean = false;
  @State useAutoResize: boolean = true;
  @State interpolationMode: ImageInterpolation = ImageInterpolation.Medium;
  @State fitMode: ImageFit = ImageFit.Cover;
  @State selectedId: number = -1;
  @State lastClicked: string = '--';
  @State headerText: string = '准备就绪';

  private data: ImageListDataSource = new ImageListDataSource();
  private fitModes: Array<{ label: string, value: ImageFit }> = [
    { label: 'Cover', value: ImageFit.Cover },
    { label: 'Contain', value: ImageFit.Contain },
    { label: 'Fill', value: ImageFit.Fill },
    { label: 'None', value: ImageFit.None },
    { label: 'ScaleDown', value: ImageFit.ScaleDown }
  ];

  aboutToAppear() {
    this.refreshAll();
  }

  refreshAll() {
    const items = this.buildItems(this.itemCount);
    this.data.setItems(items);
    this.headerText = `共加载 ${items.length} 张图片`;
  }

  buildItems(count: number): ImageItem[] {
    const items: ImageItem[] = [];
    const sources: Resource[] = [
      $r('app.media.startIcon'),
      $r('app.media.foreground'),
      $r('app.media.background'),
      $r('app.media.heart'),
      $r('app.media.star'),
      $r('app.media.svg')
    ];
    const tags: string[] = ['风景', '人物', '动物', '美食', '建筑', '夜景', '抽象', '极简'];
    for (let i = 0; i < count; i++) {
      const ratio = 0.7 + ((i * 37) % 80) / 100.0;
      const source = sources[i % sources.length];
      const tag = tags[i % tags.length];
      items.push(new ImageItem(
        i + 1,
        `作品 #${(i + 1).toString().padStart(3, '0')}`,
        `${tag} · 比例 ${ratio.toFixed(2)}`,
        ratio,
        source,
        tag
      ));
    }
    return items;
  }

  appendMore(count: number) {
    const existing = this.data.totalCount();
    const newItems = this.buildItems(existing + count).slice(existing);
    this.data.appendItems(newItems);
    this.itemCount = this.data.totalCount();
    this.headerText = `已扩展至 ${this.itemCount} 张`;
  }

  build() {
    Column({ space: 0 }) {
      this.buildHeader()
      this.buildPreviewBar()
      this.buildTabBar()
      this.buildOptionBar()
      this.buildContentForTab()
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF2F2F2)
  }

  @Builder
  buildHeader() {
    Column({ space: 6 }) {
      Text('图片列表 / 瀑布流 / 懒加载综合示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .fontColor(0x222222)
        .margin({ top: 18 })
      Text(this.headerText)
        .fontSize(12)
        .fontColor(0x888888)
      Text(`最近点击：${this.lastClicked}`)
        .fontSize(12)
        .fontColor(0x666666)
        .margin({ bottom: 8 })
    }
    .width('100%')
    .backgroundColor(0xFFFFFF)
    .padding({ left: 16, right: 16, bottom: 12 })
  }

  @Builder
  buildPreviewBar() {
    if (this.selectedId > 0) {
      Row({ space: 12 }) {
        Image(this.findSelectedItem()?.source ?? $r('app.media.startIcon'))
          .width(72)
          .height(72)
          .objectFit(ImageFit.Cover)
          .borderRadius(10)
          .border({ width: 1, color: 0x22888888 })

        Column({ space: 4 }) {
          Text(`已选中：${this.findSelectedItem()?.title ?? '--'}`)
            .fontSize(13)
            .fontWeight(FontWeight.Medium)
            .fontColor(0x222222)
          Text(this.findSelectedItem()?.subtitle ?? '')
            .fontSize(11)
            .fontColor(0x888888)
          Row({ space: 6 }) {
            Text(`objectFit: ${this.fitModeToString(this.fitMode)}`)
              .fontSize(11)
              .fontColor(0x666666)
            Text(`lazy: ${this.useLazy ? 'ON' : 'OFF'}`)
              .fontSize(11)
              .fontColor(0x666666)
            Text(`sync: ${this.useSyncLoad ? 'ON' : 'OFF'}`)
              .fontSize(11)
              .fontColor(0x666666)
          }
        }
        .layoutWeight(1)
        .alignItems(HorizontalAlign.Start)

        Button('取消')
          .fontSize(12)
          .height(28)
          .backgroundColor(0x999999)
          .onClick(() => {
            this.selectedId = -1;
          })
      }
      .width('100%')
      .padding({ left: 12, right: 12, top: 10, bottom: 10 })
      .backgroundColor(0xEAF3FF)
      .border({ width: { bottom: 1 }, color: 0xCCE0FF })
    }
  }

  findSelectedItem(): ImageItem | undefined {
    if (this.selectedId <= 0) {
      return undefined;
    }
    return this.data.getAll().find((item) => item.id === this.selectedId);
  }

  fitModeToString(mode: ImageFit): string {
    switch (mode) {
      case ImageFit.Cover:
        return 'Cover';
      case ImageFit.Contain:
        return 'Contain';
      case ImageFit.Fill:
        return 'Fill';
      case ImageFit.None:
        return 'None';
      case ImageFit.ScaleDown:
        return 'ScaleDown';
      default:
        return 'Unknown';
    }
  }

  @Builder
  buildTabBar() {
    Row({ space: 0 }) {
      this.buildTabItem('竖向 List', 0)
      this.buildTabItem('网格 Grid', 1)
      this.buildTabItem('瀑布流', 2)
    }
    .width('100%')
    .backgroundColor(0xFFFFFF)
    .border({ width: { bottom: 1 }, color: 0xEEEEEE })
  }

  @Builder
  buildTabItem(label: string, index: number) {
    Column({ space: 4 }) {
      Text(label)
        .fontSize(14)
        .fontColor(this.currentTab === index ? 0x3388FF : 0x666666)
        .fontWeight(this.currentTab === index ? FontWeight.Bold : FontWeight.Normal)
      Divider()
        .width(40)
        .strokeWidth(2)
        .color(this.currentTab === index ? 0x3388FF : Color.Transparent)
    }
    .layoutWeight(1)
    .padding({ top: 10, bottom: 10 })
    .onClick(() => {
      this.currentTab = index;
    })
  }

  @Builder
  buildOptionBar() {
    ScrollView() {
      Row({ space: 12 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.useLazy })
          .selectedColor(0x3388FF)
          .onChange((on: boolean) => {
            this.useLazy = on;
          })
        Text('LazyForEach')
          .fontSize(12)
          .fontColor(0x333333)

        Toggle({ type: ToggleType.Switch, isOn: this.useSyncLoad })
          .selectedColor(0x3388FF)
          .onChange((on: boolean) => {
            this.useSyncLoad = on;
          })
        Text('syncLoad')
          .fontSize(12)
          .fontColor(0x333333)

        Toggle({ type: ToggleType.Switch, isOn: this.useAutoResize })
          .selectedColor(0x3388FF)
          .onChange((on: boolean) => {
            this.useAutoResize = on;
          })
        Text('autoResize')
          .fontSize(12)
          .fontColor(0x333333)

        Text('|')
          .fontSize(12)
          .fontColor(0xCCCCCC)

        ForEach(this.fitModes, (item: { label: string, value: ImageFit }) => {
          Text(item.label)
            .fontSize(12)
            .fontColor(this.fitMode === item.value ? Color.White : 0x444444)
            .backgroundColor(this.fitMode === item.value ? 0x3388FF : 0xEAEAEA)
            .borderRadius(10)
            .padding({ left: 10, right: 10, top: 4, bottom: 4 })
            .margin({ left: 4, right: 4 })
            .onClick(() => {
              this.fitMode = item.value;
            })
        })
      }
      .padding({ left: 16, right: 16, top: 10, bottom: 10 })
    }
    .scrollable(ScrollDirection.Horizontal)
    .scrollBar(BarState.Off)
    .width('100%')
    .backgroundColor(0xFFFFFF)
    .border({ width: { bottom: 1 }, color: 0xEEEEEE })
  }

  @Builder
  buildContentForTab() {
    Column() {
      Stack() {
        if (this.currentTab === 0) {
          this.buildVerticalList()
        } else if (this.currentTab === 1) {
          this.buildGridLayout()
        } else {
          this.buildWaterFlow()
        }
      }
      .layoutWeight(1)
      .width('100%')

      this.buildBottomGuide()
    }
    .layoutWeight(1)
    .width('100%')
  }

  @Builder
  buildVerticalList() {
    List({ space: 12 }) {
      if (this.useLazy) {
        LazyForEach(this.data, (item: ImageItem) => {
          ListItem() {
            this.buildListCard(item)
          }
        }, (item: ImageItem) => `${item.id}`)
      } else {
        ForEach(this.data.getAll(), (item: ImageItem) => {
          ListItem() {
            this.buildListCard(item)
          }
        }, (item: ImageItem) => `${item.id}`)
      }
      ListItem() {
        this.buildLoadMoreButton()
      }
    }
    .width('100%')
    .height('100%')
    .padding({ left: 12, right: 12, top: 12, bottom: 12 })
    .layoutWeight(1)
    .cachedCount(this.useLazy ? 6 : 0)
  }

  @Builder
  buildGridLayout() {
    Grid() {
      if (this.useLazy) {
        LazyForEach(this.data, (item: ImageItem) => {
          GridItem() {
            this.buildGridCell(item)
          }
        }, (item: ImageItem) => `${item.id}`)
      } else {
        ForEach(this.data.getAll(), (item: ImageItem) => {
          GridItem() {
            this.buildGridCell(item)
          }
        }, (item: ImageItem) => `${item.id}`)
      }
    }
    .columnsTemplate('1fr 1fr')
    .rowsGap(10)
    .columnsGap(10)
    .padding(12)
    .layoutWeight(1)
    .cachedCount(this.useLazy ? 4 : 0)
  }

  @Builder
  buildWaterFlow() {
    WaterFlow() {
      if (this.useLazy) {
        LazyForEach(this.data, (item: ImageItem) => {
          FlowItem() {
            this.buildWaterFlowCell(item)
          }
        }, (item: ImageItem) => `${item.id}`)
      } else {
        ForEach(this.data.getAll(), (item: ImageItem) => {
          FlowItem() {
            this.buildWaterFlowCell(item)
          }
        }, (item: ImageItem) => `${item.id}`)
      }
    }
    .columnsTemplate('1fr 1fr')
    .padding(12)
    .layoutWeight(1)
    .backgroundColor(0xF2F2F2)
    .cachedCount(this.useLazy ? 6 : 0)
  }

  @Builder
  buildListCard(item: ImageItem) {
    Row({ space: 12 }) {
      Stack() {
        Image(item.source)
          .width(96)
          .height(96)
          .objectFit(this.fitMode)
          .borderRadius(this.cardRadius)
          .syncLoad(this.useSyncLoad)
          .autoResize(this.useAutoResize)
          .interpolation(this.interpolationMode)

        if (this.selectedId === item.id) {
          Column() {
            Text('已选')
              .fontSize(11)
              .fontColor(Color.White)
              .padding({ left: 6, right: 6, top: 2, bottom: 2 })
              .backgroundColor('rgba(0,0,0,0.5)')
              .borderRadius(8)
          }
          .position({ x: 4, y: 4 })
        }
      }
      .width(96)
      .height(96)

      Column({ space: 6 }) {
        Text(item.title)
          .fontSize(15)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x222222)
        Text(item.subtitle)
          .fontSize(12)
          .fontColor(0x888888)
        Row({ space: 6 }) {
          Text(`#${item.id}`)
            .fontSize(11)
            .fontColor(0xFFFFFF)
            .backgroundColor(0x3388FF)
            .borderRadius(8)
            .padding({ left: 6, right: 6, top: 2, bottom: 2 })
          Text(item.tag)
            .fontSize(11)
            .fontColor(0x3388FF)
            .border({ width: 1, color: 0x3388FF })
            .borderRadius(8)
            .padding({ left: 6, right: 6, top: 2, bottom: 2 })
        }
      }
      .layoutWeight(1)
      .alignItems(HorizontalAlign.Start)

      Column({ space: 6 }) {
        Button('查看')
          .fontSize(12)
          .height(28)
          .padding({ left: 12, right: 12 })
          .backgroundColor(0x33AA55)
          .onClick(() => {
            this.lastClicked = `${item.title} - 查看`;
          })
        Button('收藏')
          .fontSize(12)
          .height(28)
          .padding({ left: 12, right: 12 })
          .backgroundColor(0xFFAA00)
          .onClick(() => {
            this.lastClicked = `${item.title} - 收藏`;
          })
      }
    }
    .width('100%')
    .padding(12)
    .backgroundColor(this.selectedId === item.id ? 0xEAF3FF : 0xFFFFFF)
    .borderRadius(12)
    .shadow({ radius: 8, color: 0x22000000, offsetX: 0, offsetY: 2 })
    .scale(this.selectedId === item.id
      ? { x: this.cardScale * 1.02, y: this.cardScale * 1.02 }
      : { x: this.cardScale, y: this.cardScale })
    .onClick(() => {
      this.selectedId = this.selectedId === item.id ? -1 : item.id;
      this.lastClicked = `${item.title} - 选中/取消`;
    })
  }

  @Builder
  buildGridCell(item: ImageItem) {
    Stack({ alignContent: Alignment.BottomEnd }) {
      Column({ space: 6 }) {
        Image(item.source)
          .width('100%')
          .aspectRatio(1)
          .objectFit(this.fitMode)
          .borderRadius(this.cardRadius)
          .syncLoad(this.useSyncLoad)
          .autoResize(this.useAutoResize)
          .interpolation(ImageInterpolation.Low)

        Text(item.title)
          .fontSize(13)
          .fontColor(0x333333)
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
      }
      .width('100%')
      .padding(8)
      .backgroundColor(0xFFFFFF)
      .borderRadius(12)
      .shadow({ radius: 6, color: 0x22000000, offsetX: 0, offsetY: 2 })

      Text(`#${item.id}`)
        .fontSize(11)
        .fontColor(Color.White)
        .backgroundColor('rgba(0,0,0,0.55)')
        .borderRadius(8)
        .padding({ left: 6, right: 6, top: 2, bottom: 2 })
        .margin({ bottom: 12, right: 12 })
    }
    .width('100%')
    .aspectRatio(1)
    .onClick(() => {
      this.lastClicked = `${item.title} (Grid)`;
    })
  }

  @Builder
  buildWaterFlowCell(item: ImageItem) {
    Column({ space: 6 }) {
      Stack({ alignContent: Alignment.TopEnd }) {
        Image(item.source)
          .width('100%')
          .aspectRatio(item.ratio)
          .objectFit(this.fitMode)
          .borderRadius(this.cardRadius)
          .syncLoad(this.useSyncLoad)
          .autoResize(this.useAutoResize)
          .interpolation(this.interpolationMode)

        Text(item.tag)
          .fontSize(11)
          .fontColor(Color.White)
          .backgroundColor('rgba(51,136,255,0.85)')
          .borderRadius(8)
          .padding({ left: 6, right: 6, top: 2, bottom: 2 })
          .margin({ top: 8, right: 8 })
      }

      Column({ space: 4 }) {
        Text(item.title)
          .fontSize(13)
          .fontColor(0x222222)
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .width('100%')
        Text(item.subtitle)
          .fontSize(11)
          .fontColor(0x888888)
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .width('100%')
      }
      .width('100%')
      .padding({ left: 4, right: 4, bottom: 6 })
    }
    .width('100%')
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
    .shadow({ radius: 6, color: 0x22000000, offsetX: 0, offsetY: 2 })
    .onClick(() => {
      this.lastClicked = `${item.title} (WaterFlow)`;
    })
  }

  @Builder
  buildLoadMoreButton() {
    Row({ space: 10 }) {
      Button('追加 10 项')
        .fontSize(13)
        .backgroundColor(0x3388FF)
        .onClick(() => this.appendMore(10))
      Button('重置列表')
        .fontSize(13)
        .backgroundColor(0xFF7070)
        .onClick(() => {
          this.itemCount = 30;
          this.refreshAll();
        })
    }
    .width('100%')
    .padding({ top: 12, bottom: 16 })
    .justifyContent(FlexAlign.Center)
  }

  @Builder
  buildBottomGuide() {
    Column({ space: 10 }) {
      Text('性能与最佳实践')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      this.buildGuideRow('LazyForEach', '使用 keyGenerator 确保列表项稳定 id，避免重复创建')
      this.buildGuideRow('cachedCount', 'List/Grid/WaterFlow 设置合理的预渲染数量，平衡性能与流畅度')
      this.buildGuideRow('syncLoad', '小尺寸本地图（如图标/缩略图）建议开启同步加载')
      this.buildGuideRow('autoResize', '大图缩略显示时建议开启 autoResize 降低内存占用')
      this.buildGuideRow('interpolation', '放大显示使用 High/Medium；缩小时配合 autoResize(false) + Medium')
      this.buildGuideRow('objectFit', '根据卡片宽高比选择 Cover / Contain / ScaleDown')
      this.buildGuideRow('aspectRatio', '固定比例可避免因图片加载触发的高度抖动')
      this.buildGuideRow('alt 占位', '网络/动态加载场景务必设置 alt，提升视觉连续性')
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildGuideRow(title: string, content: string) {
    Row({ space: 10 }) {
      Column() {
        Text('•')
          .fontSize(14)
          .fontColor(0x3388FF)
      }
      .width(16)
      Column({ space: 4 }) {
        Text(title)
          .fontSize(13)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x222222)
        Text(content)
          .fontSize(12)
          .fontColor(0x666666)
      }
      .layoutWeight(1)
      .alignItems(HorizontalAlign.Start)
    }
    .width('100%')
    .alignItems(VerticalAlign.Top)
  }
}
