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

// xxx.ets

interface DataItem {
  index: number;
  label: string;
  description: string;
  color: string;
}

class SyncLoadDataSource implements IDataSource {
  private items: DataItem[] = [];
  private listeners: DataChangeListener[] = [];

  constructor(count: number) {
    this.regenerate(count);
  }

  regenerate(count: number): void {
    const colors: string[] = [
      '#E3F2FD', '#F3E5F5', '#E8F5E9', '#FFF3E0', '#FCE4EC',
      '#E0F7FA', '#F1F8E9', '#FFFDE7', '#FBE9E7', '#E8EAF6'
    ];
    const labels: string[] = [
      'Apple', 'Banana', 'Cherry', 'Date', 'Elderberry',
      'Fig', 'Grape', 'Honeydew', 'Kiwi', 'Lemon'
    ];
    this.items = [];
    for (let i = 0; i < count; i++) {
      this.items.push({
        index: i,
        label: `${labels[i % labels.length]} #${i}`,
        description: `This is item ${i} rendered in ${i % 2 === 0 ? 'even' : 'odd'} position`,
        color: colors[i % colors.length]
      });
    }
  }

  totalCount(): number {
    return this.items.length;
  }

  getData(index: number): DataItem {
    return this.items[index];
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    this.listeners.push(listener);
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }

  notifyDataReload(): void {
    this.listeners.forEach((listener: DataChangeListener) => {
      listener.onDataReloaded();
    });
  }
}

@Entry
@Component
struct SyncLoadDemo {
  // Toggle state: true = syncLoad defaults to true (synchronous), false = explicit syncLoad(false)
  @State useSyncLoad: boolean = true;
  // Data source size selector
  @State dataCount: number = 100;
  // Status text for display
  @State statusText: string = '';
  // Scroll position tracker
  private scroller: Scroller = new Scroller();
  private dataSource: SyncLoadDataSource = new SyncLoadDataSource(100);

  private switchMode(): void {
    this.useSyncLoad = !this.useSyncLoad;
    this.dataSource.notifyDataReload();
    this.updateStatus();
  }

  private switchDataCount(): void {
    const sizes: number[] = [50, 100, 200, 500];
    const currentIndex: number = sizes.indexOf(this.dataCount);
    this.dataCount = sizes[(currentIndex + 1) % sizes.length];
    // Reuse the same dataSource instance: regenerate data and notify listeners.
    // Replacing the dataSource reference would not trigger LazyForEach rebinding
    // because dataSource is a plain member, not a @State variable.
    this.dataSource.regenerate(this.dataCount);
    this.dataSource.notifyDataReload();
    this.updateStatus();
  }

  private scrollToTop(): void {
    this.scroller.scrollTo({ xOffset: 0, yOffset: 0 });
  }

  private updateStatus(): void {
    const mode: string = this.useSyncLoad ? 'syncLoad=true (synchronous)' : 'syncLoad=false (frame-split)';
    const behavior: string = this.useSyncLoad
      ? 'All items loaded in one pass, no frame splitting'
      : 'Items deferred to subsequent frames when deadline exceeded';
    this.statusText = `Mode: ${mode}\nItems: ${this.dataCount}\nBehavior: ${behavior}`;
  }

  aboutToAppear(): void {
    this.updateStatus();
  }

  @Builder
  ItemBuilder(item: DataItem) {
    Row() {
      Column() {
        Text(item.label)
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
        Text(item.description)
          .fontSize(12)
          .fontColor(Color.Gray)
          .margin({ top: 2 })
      }
      .alignItems(HorizontalAlign.Start)
      .width('70%')

      Text(this.useSyncLoad ? 'SYNC' : 'ASYNC')
        .fontSize(11)
        .fontColor(this.useSyncLoad ? 0x424242 : 0x1976D2)
        .fontWeight(FontWeight.Bold)
        .width('30%')
        .textAlign(TextAlign.End)
    }
    .width('100%')
    .height(60)
    .padding({ left: 16, right: 16 })
    .borderRadius(8)
    .backgroundColor(item.color)
    .margin({ bottom: 6 })
  }

  @Builder
  HeaderBuilder() {
    Row() {
      Text(`syncLoad Demo — ${this.useSyncLoad ? 'Synchronous' : 'Frame-Split'}`)
        .fontSize(15)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.White)
      Text(`  ${this.dataCount} items`)
        .fontSize(13)
        .fontColor(0xE0E0E0)
    }
    .width('100%')
    .height(40)
    .padding({ left: 16, right: 16 })
    .backgroundColor(this.useSyncLoad ? 0x4CAF50 : 0x2196F3)
    .justifyContent(FlexAlign.SpaceBetween)
    .alignItems(VerticalAlign.Center)
  }

  @Builder
  FooterBuilder() {
    Text('Set syncLoad(false) to enable frame-split optimization; default is synchronous loading.')
      .fontSize(12)
      .fontColor(Color.Gray)
      .width('100%')
      .height(36)
      .textAlign(TextAlign.Center)
      .padding({ top: 8 })
  }

  @Builder
  ControlPanel() {
    Column({ space: 8 }) {
      Row({ space: 10 }) {
        Button(this.useSyncLoad ? 'Switch to Async' : 'Switch to Sync')
          .fontSize(13)
          .width(150)
          .backgroundColor(this.useSyncLoad ? 0x4CAF50 : 0x2196F3)
          .onClick(() => {
            this.switchMode();
          })
        Button(`Data: ${this.dataCount}`)
          .fontSize(13)
          .width(110)
          .backgroundColor(0x607D8B)
          .onClick(() => {
            this.switchDataCount();
          })
      }

      Row({ space: 10 }) {
        Button('Scroll to Top')
          .fontSize(13)
          .width(130)
          .backgroundColor(0x795548)
          .onClick(() => {
            this.scrollToTop();
          })
        Button('Reload Data')
          .fontSize(13)
          .width(130)
          .backgroundColor(0x9E9E9E)
          .onClick(() => {
            this.dataSource.notifyDataReload();
          })
      }

      Text(this.statusText)
        .fontSize(12)
        .fontColor(0x424242)
        .backgroundColor(0xF5F5F5)
        .padding(8)
        .borderRadius(6)
        .width('92%')
    }
    .width('100%')
    .alignItems(HorizontalAlign.Center)
    .margin({ bottom: 12, top: 8 })
  }

  build() {
    Column() {
      Text('syncLoad Default Behavior Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 12, bottom: 4 })

      Text('By default syncLoad is true (synchronous).\nSet syncLoad(false) to enable frame-split optimization.')
        .fontSize(12)
        .fontColor(Color.Gray)
        .textAlign(TextAlign.Center)
        .margin({ bottom: 4 })

      this.ControlPanel()

      // List with conditional syncLoad
      if (this.useSyncLoad) {
        // Default behavior: syncLoad is not set, defaults to true (synchronous loading).
        List({ scroller: this.scroller }) {
          ListItem() {
            this.HeaderBuilder()
          }
          LazyForEach(this.dataSource, (item: DataItem) => {
            ListItem() {
              this.ItemBuilder(item)
            }
          }, (item: DataItem) => `${item.index}`)
          ListItem() {
            this.FooterBuilder()
          }
        }
        .width('92%')
        .layoutWeight(1)
        .scrollBar(BarState.Auto)
        .divider({ strokeWidth: 1, color: 0xE0E0E0, startMargin: 16, endMargin: 16 })
        .edgeEffect(EdgeEffect.Spring)
      } else {
        // Explicit syncLoad(false): enables frame-split optimization.
        // The layout algorithm defers remaining items to subsequent frames
        // when the response deadline is exceeded (controlled by ReachResponseDeadline).
        List({ scroller: this.scroller }) {
          ListItem() {
            this.HeaderBuilder()
          }
          LazyForEach(this.dataSource, (item: DataItem) => {
            ListItem() {
              this.ItemBuilder(item)
            }
          }, (item: DataItem) => `${item.index}`)
          ListItem() {
            this.FooterBuilder()
          }
        }
        .width('92%')
        .layoutWeight(1)
        .scrollBar(BarState.Auto)
        .divider({ strokeWidth: 1, color: 0xE0E0E0, startMargin: 16, endMargin: 16 })
        .edgeEffect(EdgeEffect.Spring)
        .syncLoad(false)
      }
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF1F3F5)
  }
}
