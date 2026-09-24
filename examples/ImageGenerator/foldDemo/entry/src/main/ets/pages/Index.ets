/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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

import { hilog } from '@kit.PerformanceAnalysisKit';
import { display } from '@kit.ArkUI';
import { FoldListTester } from './FoldListTester';

const DOMAIN: number = 0x0000;
const TAG: string = 'FoldDemo';

interface FoldLogEntry {
  time: string;
  msg: string;
}

interface ListItemData {
  id: number;
  title: string;
  subtitle: string;
  description: string;
  color: string;
  category: string;
  badge: string;
}

function formatTime(ts: number): string {
  let d = new Date(ts);
  let hh = d.getHours().toString().padStart(2, '0');
  let mm = d.getMinutes().toString().padStart(2, '0');
  let ss = d.getSeconds().toString().padStart(2, '0');
  let ms = d.getMilliseconds().toString().padStart(3, '0');
  return `${hh}:${mm}:${ss}.${ms}`;
}

function generateSampleData(count: number): ListItemData[] {
  let data: ListItemData[] = [];
  let categories: string[] = ['Technology', 'Design', 'Product', 'Research', 'Marketing'];
  let colors: string[] = ['#E3F2FD', '#E8F5E9', '#FFF3E0', '#F3E5F5', '#FFEBEE', '#E0F7FA', '#F1F8E9', '#FFF8E1'];
  let badges: string[] = ['New', 'Hot', 'Featured', 'Updated', 'Popular'];
  for (let i = 0; i < count; i++) {
    data.push({
      id: i,
      title: `Item ${i + 1}`,
      subtitle: `${categories[i % categories.length]} category`,
      description: `This is a detailed description for list item number ${i + 1}. It demonstrates adaptive layout across fold states.`,
      color: colors[i % colors.length],
      category: categories[i % categories.length],
      badge: badges[i % badges.length],
    });
  }
  return data;
}

@Entry
@Component
struct Index {
  @State simulatedFoldStatus: string = 'expanded';
  @State realFoldDisplayMode: string = 'UNKNOWN';
  @State realFoldStatus: string = 'UNKNOWN';
  @State screenWidth: number = 1080;
  @State screenHeight: number = 2400;
  @State isFoldable: boolean = false;
  @State columnCount: number = 2;
  @State listItemCount: number = 30;
  @State listItemHeight: number = 80;
  @State listSpacing: number = 8;
  @State showDetailPane: boolean = true;
  @State selectedItemId: number = -1;
  @State listData: ListItemData[] = generateSampleData(30);
  @State logList: FoldLogEntry[] = [];
  @State foldChangeCount: number = 0;
  @State displayModeChangeCount: number = 0;
  @State lastFoldChangeEvent: string = 'N/A';
  @State lastDisplayModeChangeEvent: string = 'N/A';
  @State enableAdaptiveLayout: boolean = true;
  @State enableListDetail: boolean = true;
  @State customColumns: number = 2;
  @State listBackgroundColor: string = '#FAFAFA';
  @State selectedColor: string = '#E3F2FD';
  @State categoryFilter: string = 'All';
  @State showBadges: boolean = true;
  @State showCategories: boolean = true;
  @State isShowDetailSheet: boolean = false;
  @State detailSheetHeight: number | string = '60%';
  @State itemSelectCount: number = 0;
  @State layoutSwitchCount: number = 0;

  private maxLogCount: number = 100;

  aboutToAppear(): void {
    this.detectFoldCapability();
    this.updateColumnCount();
    this.addLog('FoldDemo initialized');
    this.addLog(`Device foldable: ${this.isFoldable}`);
    this.addLog(`Simulated status: ${this.simulatedFoldStatus}`);
  }

  aboutToDisappear(): void {
  }

  detectFoldCapability(): void {
    try {
      let disp = display.getDefaultDisplaySync();
      this.screenWidth = disp.width;
      this.screenHeight = disp.height;
      this.isFoldable = false;
      this.addLog(`Screen: ${disp.width} x ${disp.height}`);
    } catch (e) {
      this.isFoldable = false;
      this.realFoldDisplayMode = 'N/A';
      this.realFoldStatus = 'N/A';
    }
  }

  addLog(msg: string): void {
    let entry: FoldLogEntry = { time: formatTime(Date.now()), msg: msg };
    this.logList.push(entry);
    if (this.logList.length > this.maxLogCount) {
      this.logList.shift();
    }
    hilog.info(DOMAIN, TAG, msg);
  }

  clearLog(): void {
    this.logList = [];
    this.addLog('Logs cleared');
  }

  updateFoldStatus(status: string): void {
    this.simulatedFoldStatus = status;
    this.foldChangeCount++;
    this.layoutSwitchCount++;
    this.lastFoldChangeEvent = `${formatTime(Date.now())}: ${status} (simulated)`;
    this.updateColumnCount();
    this.addLog(`Fold status changed to: ${status}`);
  }

  updateColumnCount(): void {
    if (!this.enableAdaptiveLayout) {
      this.columnCount = this.customColumns;
      return;
    }
    switch (this.simulatedFoldStatus) {
      case 'folded':
        this.columnCount = 1;
        break;
      case 'half_folded':
        this.columnCount = 1;
        break;
      case 'expanded':
        this.columnCount = 2;
        break;
      default:
        this.columnCount = 1;
    }
  }

  selectItem(item: ListItemData): void {
    this.selectedItemId = item.id;
    this.itemSelectCount++;
    this.addLog(`Selected item: ${item.title}`);
    if (this.simulatedFoldStatus === 'folded') {
      this.isShowDetailSheet = true;
    }
  }

  getFilteredData(): ListItemData[] {
    if (this.categoryFilter === 'All') {
      return this.listData;
    }
    let result: ListItemData[] = [];
    for (let i = 0; i < this.listData.length; i++) {
      if (this.listData[i].category === this.categoryFilter) {
        result.push(this.listData[i]);
      }
    }
    return result;
  }

  getSelectedItem(): ListItemData {
    if (this.selectedItemId >= 0 && this.selectedItemId < this.listData.length) {
      return this.listData[this.selectedItemId];
    }
    return {
      id: -1,
      title: 'No Selection',
      subtitle: '',
      description: 'Select an item from the list',
      color: '#F0F0F0',
      category: '',
      badge: '',
    };
  }

  build() {
    Column() {
      // Header
      Row() {
        Text('Fold Demo')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ left: 16 })
        Blank()
        Button('Clear Log')
          .height(32)
          .fontSize(12)
          .margin({ right: 16 })
          .onClick(() => {
            this.clearLog();
          })
      }
      .width('100%')
      .height(50)
      .backgroundColor('#F1F3F5')

      // Scrollable content area
      Scroll() {
        Column({ space: 8 }) {
          // Section 1: Fold Status Display
          this.buildStatusSection()

          // Section 2: Basic List Display
          this.buildBasicListSection()

          // Section 3: Multi-Column Adaptation
          this.buildMultiColumnSection()

          // Section 4: List-Detail Layout
          this.buildListDetailSection()

          // Section 5: Fold Simulation Controls
          this.buildSimulationSection()

          // Section 6: List Configuration
          this.buildListConfigSection()

          // Section 7: Advanced fold list tester
          this.buildAdvancedTesterSection()

          // Section 8: Log display
          this.buildLogSection()
        }
        .width('100%')
        .padding(8)
      }
      .layoutWeight(1)
      .width('100%')
      .bindSheet($$this.isShowDetailSheet, this.builderDetailSheet(), {
        height: this.detailSheetHeight,
        dragBar: true,
        backgroundColor: '#FFFFFF',
        detents: [300, 500, 700],
        mode: SheetMode.OVERLAY,
        showClose: true,
      })
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  builderDetailSheet() {
    Column() {
      Text(this.getSelectedItem().title)
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 16, bottom: 8 })

      Text(this.getSelectedItem().subtitle)
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 12 })

      Text(this.getSelectedItem().description)
        .fontSize(14)
        .margin({ bottom: 16 })
        .textAlign(TextAlign.Center)

      Row({ space: 12 }) {
        Text(`Category: ${this.getSelectedItem().category}`)
          .fontSize(12)
          .backgroundColor(this.getSelectedItem().color)
          .padding(8)
          .borderRadius(8)
        Text(`Badge: ${this.getSelectedItem().badge}`)
          .fontSize(12)
          .backgroundColor('#E0E0E0')
          .padding(8)
          .borderRadius(8)
      }
      .margin({ bottom: 16 })

      Button('Close Detail')
        .onClick(() => {
          this.isShowDetailSheet = false;
          this.addLog('Detail sheet closed');
        })
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  buildStatusSection() {
    Column({ space: 6 }) {
      Text('1. Fold Status Display')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)

      Row({ space: 6 }) {
        this.buildStatusCard('Simulated', this.simulatedFoldStatus, '#E3F2FD')
        this.buildStatusCard('Real Status', this.realFoldStatus, '#E8F5E9')
        this.buildStatusCard('Display Mode', this.realFoldDisplayMode, '#FFF3E0')
      }

      Row({ space: 6 }) {
        this.buildStatusCard('Foldable', this.isFoldable ? 'Yes' : 'No', '#F3E5F5')
        this.buildStatusCard('Columns', this.columnCount.toString(), '#FFEBEE')
        this.buildStatusCard('Changes', this.foldChangeCount.toString(), '#E0F7FA')
      }

      Row({ space: 6 }) {
        Text(`Screen: ${this.screenWidth} x ${this.screenHeight}`)
          .fontSize(11)
          .fontColor('#666666')
          .layoutWeight(1)
          .backgroundColor('#F0F0F0')
          .padding(6)
          .borderRadius(6)
        Text(`Detail: ${this.showDetailPane ? 'ON' : 'OFF'}`)
          .fontSize(11)
          .fontColor('#666666')
          .layoutWeight(1)
          .backgroundColor('#F0F0F0')
          .padding(6)
          .borderRadius(6)
      }
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildStatusCard(title: string, value: string, color: string) {
    Column() {
      Text(title)
        .fontSize(9)
        .fontColor('#666666')
      Text(value)
        .fontSize(13)
        .fontWeight(FontWeight.Bold)
        .fontColor('#333333')
    }
    .layoutWeight(1)
    .height(48)
    .backgroundColor(color)
    .borderRadius(8)
    .justifyContent(FlexAlign.Center)
  }

  @Builder
  buildBasicListSection() {
    Column({ space: 6 }) {
      Text('2. Basic List Display (Adapts to Fold State)')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)

      Text(`Current: ${this.simulatedFoldStatus} | ${this.columnCount} column(s)`)
        .fontSize(11)
        .fontColor('#888888')

      List({ space: this.listSpacing }) {
        ForEach(this.getFilteredData().slice(0, 10), (item: ListItemData) => {
          ListItem() {
            this.buildListItem(item)
          }
          .backgroundColor(item.color)
          .borderRadius(8)
          .onClick(() => {
            this.selectItem(item);
          })
        })
      }
      .width('100%')
      .height(this.listItemHeight * 4 + this.listSpacing * 3)
      .padding({ left: 8, right: 8 })
      .backgroundColor(this.listBackgroundColor)
      .borderRadius(8)
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildListItem(item: ListItemData) {
    Row({ space: 8 }) {
      Column() {
        Text(item.id.toString())
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .fontColor('#FFFFFF')
      }
      .width(40)
      .height(40)
      .backgroundColor('#1976D2')
      .borderRadius(20)
      .justifyContent(FlexAlign.Center)
      .alignItems(HorizontalAlign.Center)

      Column({ space: 2 }) {
        Text(item.title)
          .fontSize(14)
          .fontWeight(FontWeight.Bold)
        if (this.showCategories) {
          Text(item.category)
            .fontSize(10)
            .fontColor('#666666')
        }
      }
      .layoutWeight(1)
      .alignItems(HorizontalAlign.Start)

      if (this.showBadges) {
        Text(item.badge)
          .fontSize(9)
          .fontColor('#FFFFFF')
          .backgroundColor('#FF6D00')
          .padding({ left: 6, right: 6, top: 2, bottom: 2 })
          .borderRadius(8)
      }
    }
    .width('100%')
    .height(this.listItemHeight)
    .padding({ left: 12, right: 12 })
    .alignItems(VerticalAlign.Center)
  }

  @Builder
  buildMultiColumnSection() {
    Column({ space: 6 }) {
      Text('3. Multi-Column Adaptation')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)

      Text('List columns change based on fold state. Expanded = multi-column, Folded = single column')
        .fontSize(10)
        .fontColor('#888888')

      Row({ space: 6 }) {
        Button('1 Col')
          .layoutWeight(1)
          .height(30)
          .fontSize(10)
          .backgroundColor(this.columnCount === 1 ? '#1976D2' : '#E0E0E0')
          .fontColor(this.columnCount === 1 ? '#FFFFFF' : '#333333')
          .onClick(() => {
            this.columnCount = 1;
            this.layoutSwitchCount++;
            this.addLog('Columns: 1');
          })
        Button('2 Col')
          .layoutWeight(1)
          .height(30)
          .fontSize(10)
          .backgroundColor(this.columnCount === 2 ? '#1976D2' : '#E0E0E0')
          .fontColor(this.columnCount === 2 ? '#FFFFFF' : '#333333')
          .onClick(() => {
            this.columnCount = 2;
            this.layoutSwitchCount++;
            this.addLog('Columns: 2');
          })
        Button('3 Col')
          .layoutWeight(1)
          .height(30)
          .fontSize(10)
          .backgroundColor(this.columnCount === 3 ? '#1976D2' : '#E0E0E0')
          .fontColor(this.columnCount === 3 ? '#FFFFFF' : '#333333')
          .onClick(() => {
            this.columnCount = 3;
            this.layoutSwitchCount++;
            this.addLog('Columns: 3');
          })
      }

      GridRow({ columns: this.columnCount, gutter: { x: 8, y: 8 } }) {
        ForEach(this.getFilteredData().slice(0, 12), (item: ListItemData) => {
          GridCol() {
            this.buildGridItem(item)
          }
        })
      }
      .width('100%')
      .padding(8)
      .backgroundColor(this.listBackgroundColor)
      .borderRadius(8)
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildGridItem(item: ListItemData) {
    Column({ space: 4 }) {
      Text(item.title)
        .fontSize(13)
        .fontWeight(FontWeight.Bold)
      Text(item.subtitle)
        .fontSize(9)
        .fontColor('#666666')
      if (this.showBadges) {
        Text(item.badge)
          .fontSize(8)
          .fontColor('#FFFFFF')
          .backgroundColor('#FF6D00')
          .padding({ left: 4, right: 4, top: 1, bottom: 1 })
          .borderRadius(4)
      }
    }
    .width('100%')
    .height(this.listItemHeight)
    .backgroundColor(item.color)
    .borderRadius(8)
    .padding(8)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .onClick(() => {
      this.selectItem(item);
    })
  }

  @Builder
  buildListDetailSection() {
    Column({ space: 6 }) {
      Text('4. List-Detail Layout')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)

      Text('List + detail pane. In folded mode, detail shows as sheet. In expanded mode, side-by-side.')
        .fontSize(10)
        .fontColor('#888888')

      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.enableListDetail })
          .onChange((isOn: boolean) => {
            this.enableListDetail = isOn;
            this.addLog(`List-Detail: ${isOn}`);
          })
        Text('Enable List-Detail')
          .fontSize(11)
        Blank()
        Toggle({ type: ToggleType.Switch, isOn: this.showDetailPane })
          .onChange((isOn: boolean) => {
            this.showDetailPane = isOn;
            this.addLog(`Detail pane: ${isOn}`);
          })
        Text('Show Detail')
          .fontSize(11)
      }

      if (this.enableListDetail) {
        if (this.simulatedFoldStatus === 'expanded' && this.showDetailPane) {
          // Side-by-side
          Row({ space: 8 }) {
            Column() {
              this.buildListPanel(6)
            }
            .layoutWeight(1)
            .backgroundColor('#F5F5F5')
            .borderRadius(8)

            Column() {
              this.buildDetailPanel()
            }
            .width('50%')
            .backgroundColor('#FFFFFF')
            .borderRadius(8)
            .border({ width: 1, color: '#E0E0E0' })
          }
          .width('100%')
          .height(this.listItemHeight * 4 + 40)
        } else if (this.simulatedFoldStatus === 'half_folded' && this.showDetailPane) {
          // Half-folded: list on top, detail on bottom
          Column({ space: 8 }) {
            Column() {
              this.buildListPanel(4)
            }
            .width('100%')
            .backgroundColor('#F5F5F5')
            .borderRadius(8)

            Column() {
              this.buildDetailPanel()
            }
            .width('100%')
            .backgroundColor('#FFFFFF')
            .borderRadius(8)
            .border({ width: 1, color: '#E0E0E0' })
          }
          .width('100%')
          .height(this.listItemHeight * 4 + 80)
        } else {
          // Folded: list only, detail in sheet
          Column() {
            this.buildListPanel(6)
          }
          .width('100%')
          .backgroundColor('#F5F5F5')
          .borderRadius(8)
        }
      }
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildListPanel(count: number) {
    List({ space: this.listSpacing }) {
      ForEach(this.getFilteredData().slice(0, count), (item: ListItemData) => {
        ListItem() {
          this.buildListItem(item)
        }
        .backgroundColor(this.selectedItemId === item.id ? this.selectedColor : item.color)
        .borderRadius(8)
        .onClick(() => {
          this.selectItem(item);
        })
      })
    }
    .width('100%')
    .layoutWeight(1)
    .padding({ left: 8, right: 8, top: 8, bottom: 8 })
  }

  @Builder
  buildDetailPanel() {
    Column({ space: 8 }) {
      Text(this.getSelectedItem().title)
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
      Text(this.getSelectedItem().subtitle)
        .fontSize(12)
        .fontColor('#666666')
      Text(this.getSelectedItem().description)
        .fontSize(12)
        .textAlign(TextAlign.Center)
      Row({ space: 8 }) {
        Text(this.getSelectedItem().category)
          .fontSize(10)
          .backgroundColor(this.getSelectedItem().color)
          .padding(4)
          .borderRadius(4)
        Text(this.getSelectedItem().badge)
          .fontSize(10)
          .backgroundColor('#E0E0E0')
          .padding(4)
          .borderRadius(4)
      }
      Text(`ID: ${this.getSelectedItem().id}`)
        .fontSize(10)
        .fontColor('#999999')
    }
    .width('100%')
    .height('100%')
    .padding(12)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
  }

  @Builder
  buildSimulationSection() {
    Column({ space: 6 }) {
      Text('5. Fold Simulation Controls')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)

      Text('Simulate different fold states (for non-foldable device testing)')
        .fontSize(10)
        .fontColor('#888888')

      Row({ space: 6 }) {
        Button('Folded')
          .layoutWeight(1)
          .height(36)
          .fontSize(11)
          .backgroundColor(this.simulatedFoldStatus === 'folded' ? '#1976D2' : '#E0E0E0')
          .fontColor(this.simulatedFoldStatus === 'folded' ? '#FFFFFF' : '#333333')
          .onClick(() => {
            this.updateFoldStatus('folded');
          })
        Button('Half-Folded')
          .layoutWeight(1)
          .height(36)
          .fontSize(11)
          .backgroundColor(this.simulatedFoldStatus === 'half_folded' ? '#1976D2' : '#E0E0E0')
          .fontColor(this.simulatedFoldStatus === 'half_folded' ? '#FFFFFF' : '#333333')
          .onClick(() => {
            this.updateFoldStatus('half_folded');
          })
        Button('Expanded')
          .layoutWeight(1)
          .height(36)
          .fontSize(11)
          .backgroundColor(this.simulatedFoldStatus === 'expanded' ? '#1976D2' : '#E0E0E0')
          .fontColor(this.simulatedFoldStatus === 'expanded' ? '#FFFFFF' : '#333333')
          .onClick(() => {
            this.updateFoldStatus('expanded');
          })
      }

      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.enableAdaptiveLayout })
          .onChange((isOn: boolean) => {
            this.enableAdaptiveLayout = isOn;
            this.updateColumnCount();
            this.addLog(`Adaptive layout: ${isOn}`);
          })
        Text('Adaptive')
          .fontSize(11)
      }
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildListConfigSection() {
    Column({ space: 6 }) {
      Text('6. List Configuration')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)

      Row({ space: 6 }) {
        Text('Item Count:')
          .fontSize(11)
          .width(70)
        Slider({ value: this.listItemCount, min: 5, max: 50, step: 5 })
          .layoutWeight(1)
          .onChange((value: number) => {
            this.listItemCount = Math.round(value);
            this.listData = generateSampleData(this.listItemCount);
          })
        Text(`${this.listItemCount}`)
          .fontSize(11)
          .width(30)
      }

      Row({ space: 6 }) {
        Text('Item Height:')
          .fontSize(11)
          .width(70)
        Slider({ value: this.listItemHeight, min: 50, max: 150, step: 5 })
          .layoutWeight(1)
          .onChange((value: number) => {
            this.listItemHeight = Math.round(value);
          })
        Text(`${this.listItemHeight}`)
          .fontSize(11)
          .width(30)
      }

      Row({ space: 6 }) {
        Text('Spacing:')
          .fontSize(11)
          .width(70)
        Slider({ value: this.listSpacing, min: 0, max: 20, step: 1 })
          .layoutWeight(1)
          .onChange((value: number) => {
            this.listSpacing = Math.round(value);
          })
        Text(`${this.listSpacing}`)
          .fontSize(11)
          .width(30)
      }

      Row({ space: 6 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.showBadges })
          .onChange((isOn: boolean) => {
            this.showBadges = isOn;
          })
        Text('Badges')
          .fontSize(11)
        Blank()
        Toggle({ type: ToggleType.Switch, isOn: this.showCategories })
          .onChange((isOn: boolean) => {
            this.showCategories = isOn;
          })
        Text('Categories')
          .fontSize(11)
      }

      Row({ space: 4 }) {
        Button('All')
          .layoutWeight(1)
          .height(28)
          .fontSize(9)
          .backgroundColor(this.categoryFilter === 'All' ? '#1976D2' : '#E0E0E0')
          .fontColor(this.categoryFilter === 'All' ? '#FFFFFF' : '#333333')
          .onClick(() => {
            this.categoryFilter = 'All';
            this.addLog('Filter: All');
          })
        Button('Tech')
          .layoutWeight(1)
          .height(28)
          .fontSize(9)
          .backgroundColor(this.categoryFilter === 'Technology' ? '#1976D2' : '#E0E0E0')
          .fontColor(this.categoryFilter === 'Technology' ? '#FFFFFF' : '#333333')
          .onClick(() => {
            this.categoryFilter = 'Technology';
            this.addLog('Filter: Technology');
          })
        Button('Design')
          .layoutWeight(1)
          .height(28)
          .fontSize(9)
          .backgroundColor(this.categoryFilter === 'Design' ? '#1976D2' : '#E0E0E0')
          .fontColor(this.categoryFilter === 'Design' ? '#FFFFFF' : '#333333')
          .onClick(() => {
            this.categoryFilter = 'Design';
            this.addLog('Filter: Design');
          })
        Button('Product')
          .layoutWeight(1)
          .height(28)
          .fontSize(9)
          .backgroundColor(this.categoryFilter === 'Product' ? '#1976D2' : '#E0E0E0')
          .fontColor(this.categoryFilter === 'Product' ? '#FFFFFF' : '#333333')
          .onClick(() => {
            this.categoryFilter = 'Product';
            this.addLog('Filter: Product');
          })
      }
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildAdvancedTesterSection() {
    Column({ space: 6 }) {
      Text('7. Advanced Fold List Tester')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
      Text('Comprehensive fold list testing with multi-layout switching, list-detail, scroll metrics, and theme presets')
        .fontSize(10)
        .fontColor('#888888')

      Column({ space: 2 }) {
        Text('Test Coverage:')
          .fontSize(11)
          .fontWeight(FontWeight.Bold)
        Text('Fold state detection, Multi-column list, List-detail split, Adaptive GridRow, Fold simulation, Scroll tracking, Theme presets, Category filter, List config, Event callbacks')
          .fontSize(10)
          .fontColor('#666666')
      }
      .width('100%')
      .padding(8)
      .backgroundColor('#F0F0F0')
      .borderRadius(8)

      FoldListTester()
        .width('100%')
        .height(520)
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildLogSection() {
    Column({ space: 4 }) {
      Row() {
        Text('Event Log')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
        Blank()
        Text(`${this.logList.length} entries`)
          .fontSize(11)
          .fontColor('#888888')
      }
      .width('100%')
      Scroll() {
        Column({ space: 2 }) {
          ForEach(this.logList.slice().reverse(), (entry: FoldLogEntry) => {
            Row() {
              Text(entry.time).fontSize(9).fontColor('#888888').width(90)
              Text(entry.msg).fontSize(10).layoutWeight(1)
            }
            .width('100%')
            .padding({ left: 4, right: 4 })
          })
        }
        .width('100%')
      }
      .width('100%')
      .height(200)
      .backgroundColor('#F5F5F5')
      .borderRadius(8)
      .padding(4)
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }
}
