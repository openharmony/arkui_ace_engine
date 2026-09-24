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

const DOMAIN: number = 0x0000;
const TAG: string = 'FoldAdvanced';

interface AdvancedLogEntry {
  time: string;
  action: string;
  detail: string;
}

interface FoldMetrics {
  foldCount: number;
  layoutSwitchCount: number;
  selectCount: number;
  scrollCount: number;
  lastScrollOffset: number;
  totalScrollDistance: number;
  maxScrollSpeed: number;
  currentScrollSpeed: number;
  direction: string;
}

interface ThemeConfig {
  name: string;
  bgColor: string;
  itemColor: string;
  selectedColor: string;
  accentColor: string;
}

interface ListItemInfo {
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

function generateTesterData(count: number): ListItemInfo[] {
  let data: ListItemInfo[] = [];
  let categories: string[] = ['Technology', 'Design', 'Product', 'Research', 'Marketing'];
  let colors: string[] = ['#E3F2FD', '#E8F5E9', '#FFF3E0', '#F3E5F5', '#FFEBEE', '#E0F7FA', '#F1F8E9', '#FFF8E1'];
  let badges: string[] = ['New', 'Hot', 'Featured', 'Updated', 'Popular'];
  for (let i = 0; i < count; i++) {
    data.push({
      id: i,
      title: `Entry ${i + 1}`,
      subtitle: `${categories[i % categories.length]} item`,
      description: `Detailed description for tester entry ${i + 1}. Showcases fold-adaptive list layout behavior.`,
      color: colors[i % colors.length],
      category: categories[i % categories.length],
      badge: badges[i % badges.length],
    });
  }
  return data;
}

@Component
export struct FoldListTester {
  @State isShow: boolean = false;
  @State foldMetrics: FoldMetrics = {
    foldCount: 0,
    layoutSwitchCount: 0,
    selectCount: 0,
    scrollCount: 0,
    lastScrollOffset: 0,
    totalScrollDistance: 0,
    maxScrollSpeed: 0,
    currentScrollSpeed: 0,
    direction: 'none',
  };
  @State simulatedStatus: string = 'expanded';
  @State realFoldStatus: string = 'UNKNOWN';
  @State realDisplayMode: string = 'UNKNOWN';
  @State isFoldable: boolean = false;
  @State screenWidth: number = 1080;
  @State screenHeight: number = 2400;
  @State columnCount: number = 2;
  @State listItemHeight: number = 80;
  @State listSpacing: number = 8;
  @State listData: ListItemInfo[] = generateTesterData(20);
  @State logEntries: AdvancedLogEntry[] = [];
  @State selectedItemId: number = -1;
  @State enableAdaptive: boolean = true;
  @State enableListDetail: boolean = true;
  @State showDetailPane: boolean = true;
  @State enableScrollLog: boolean = true;
  @State enableFoldLog: boolean = true;
  @State currentThemeIndex: number = 0;
  @State categoryFilter: string = 'All';
  @State showBadges: boolean = true;
  @State showCategories: boolean = true;
  @State listBgColor: string = '#FAFAFA';
  @State itemBgColor: string = '#FFFFFF';
  @State selectedColor: string = '#E3F2FD';
  @State accentColor: string = '#1976D2';
  @State layoutMode: string = 'auto';
  @State customColumns: number = 2;
  @State scrollOffset: number = 0;
  @State detentLabels: string[] = ['Folded (1 col)', 'Half (1+detail)', 'Expanded (2 col)', 'Wide (3 col)'];
  @State currentDetentIndex: number = 2;

  private maxLogCount: number = 80;

  aboutToAppear(): void {
    this.detectFold();
    this.updateLayout();
    this.addLog('Init', 'FoldListTester initialized');
    this.addLog('Foldable', `${this.isFoldable}`);
    this.addLog('Status', this.simulatedStatus);
  }

  aboutToDisappear(): void {
  }

  detectFold(): void {
    try {
      let disp = display.getDefaultDisplaySync();
      this.screenWidth = disp.width;
      this.screenHeight = disp.height;
    } catch (e) {
      this.isFoldable = false;
    }
  }

  addLog(action: string, detail: string): void {
    if (!this.enableFoldLog && action.startsWith('Fold')) {
      return;
    }
    if (!this.enableScrollLog && action.startsWith('Scroll')) {
      return;
    }
    let entry: AdvancedLogEntry = { time: formatTime(Date.now()), action: action, detail: detail };
    this.logEntries.push(entry);
    if (this.logEntries.length > this.maxLogCount) {
      this.logEntries.shift();
    }
    hilog.info(DOMAIN, TAG, `${action}: ${detail}`);
  }

  resetMetrics(): void {
    this.foldMetrics = {
      foldCount: 0,
      layoutSwitchCount: 0,
      selectCount: 0,
      scrollCount: 0,
      lastScrollOffset: 0,
      totalScrollDistance: 0,
      maxScrollSpeed: 0,
      currentScrollSpeed: 0,
      direction: 'none',
    };
    this.addLog('Reset', 'All metrics reset');
  }

  applyTheme(index: number): void {
    let themes: ThemeConfig[] = [
      { name: 'Phone', bgColor: '#FAFAFA', itemColor: '#FFFFFF', selectedColor: '#E3F2FD', accentColor: '#1976D2' },
      { name: 'Phablet', bgColor: '#F5F5F5', itemColor: '#F8F8F8', selectedColor: '#E8F5E9', accentColor: '#388E3C' },
      { name: 'Tablet', bgColor: '#E3F2FD', itemColor: '#FFFFFF', selectedColor: '#BBDEFB', accentColor: '#1565C0' },
      { name: 'Dark', bgColor: '#333333', itemColor: '#444444', selectedColor: '#555555', accentColor: '#64B5F6' },
      { name: 'Colorful', bgColor: '#FFF3E0', itemColor: '#FFFFFF', selectedColor: '#FFE0B2', accentColor: '#FF6D00' },
    ];
    let theme = themes[index];
    this.currentThemeIndex = index;
    this.listBgColor = theme.bgColor;
    this.itemBgColor = theme.itemColor;
    this.selectedColor = theme.selectedColor;
    this.accentColor = theme.accentColor;
    this.addLog('Theme', theme.name);
  }

  updateLayout(): void {
    if (this.layoutMode !== 'auto') {
      this.columnCount = this.customColumns;
      return;
    }
    switch (this.simulatedStatus) {
      case 'folded':
        this.columnCount = 1;
        this.currentDetentIndex = 0;
        break;
      case 'half_folded':
        this.columnCount = 1;
        this.currentDetentIndex = 1;
        break;
      case 'expanded':
        this.columnCount = 2;
        this.currentDetentIndex = 2;
        break;
      default:
        this.columnCount = 1;
        this.currentDetentIndex = 0;
    }
  }

  setSimulatedStatus(status: string): void {
    this.simulatedStatus = status;
    this.foldMetrics.foldCount++;
    this.updateLayout();
    this.addLog('Simulate', status);
  }

  setLayoutMode(mode: string): void {
    this.layoutMode = mode;
    this.foldMetrics.layoutSwitchCount++;
    this.updateLayout();
    this.addLog('LayoutMode', mode);
  }

  selectItem(item: ListItemInfo): void {
    this.selectedItemId = item.id;
    this.foldMetrics.selectCount++;
    this.addLog('Select', `${item.title} (id=${item.id})`);
  }

  getSelectedItem(): ListItemInfo {
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

  getFilteredData(): ListItemInfo[] {
    if (this.categoryFilter === 'All') {
      return this.listData;
    }
    let result: ListItemInfo[] = [];
    for (let i = 0; i < this.listData.length; i++) {
      if (this.listData[i].category === this.categoryFilter) {
        result.push(this.listData[i]);
      }
    }
    return result;
  }

  onScroll(offset: number): void {
    this.foldMetrics.scrollCount++;
    this.foldMetrics.lastScrollOffset = offset;
    let delta = Math.abs(offset - this.scrollOffset);
    this.foldMetrics.totalScrollDistance += delta;
    this.foldMetrics.direction = offset > this.scrollOffset ? 'down' : 'up';
    this.scrollOffset = offset;
    if (this.enableScrollLog && this.foldMetrics.scrollCount % 5 === 0) {
      this.addLog('Scroll', `offset=${offset}, dist=${this.foldMetrics.totalScrollDistance.toFixed(0)}`);
    }
  }

  build() {
    Column({ space: 8 }) {
      // Title
      Text('Fold List Tester')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 8 })

      // Metrics display
      Row({ space: 6 }) {
        this.buildMetricCard('Folds', this.foldMetrics.foldCount.toString(), '#E3F2FD')
        this.buildMetricCard('Layouts', this.foldMetrics.layoutSwitchCount.toString(), '#E8F5E9')
        this.buildMetricCard('Selects', this.foldMetrics.selectCount.toString(), '#FFF3E0')
        this.buildMetricCard('Col', this.columnCount.toString(), '#F3E5F5')
      }

      // Current state
      Column({ space: 2 }) {
        Text(`Simulated: ${this.simulatedStatus}`)
          .fontSize(11)
        Text(`Real Status: ${this.realFoldStatus}`)
          .fontSize(11)
        Text(`Screen: ${this.screenWidth} x ${this.screenHeight}`)
          .fontSize(11)
        Text(`Selected: ${this.getSelectedItem().title}`)
          .fontSize(11)
      }
      .width('100%')
      .padding(8)
      .backgroundColor('#F5F5F5')
      .borderRadius(8)

      // Fold state selector
      Row({ space: 6 }) {
        ForEach([0, 1, 2], (index: number) => {
          Button(this.detentLabels[index])
            .layoutWeight(1)
            .height(28)
            .fontSize(8)
            .backgroundColor(this.currentDetentIndex === index ? this.accentColor : '#E0E0E0')
            .fontColor(this.currentDetentIndex === index ? '#FFFFFF' : '#333333')
            .onClick(() => {
              this.currentDetentIndex = index;
              let statuses = ['folded', 'half_folded', 'expanded'];
              this.setSimulatedStatus(statuses[index]);
            })
        })
      }

      // Toggle controls
      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.enableAdaptive })
          .onChange((isOn: boolean) => { this.enableAdaptive = isOn; this.updateLayout(); })
        Text('Adaptive')
          .fontSize(10)
        Blank()
        Toggle({ type: ToggleType.Switch, isOn: this.enableListDetail })
          .onChange((isOn: boolean) => { this.enableListDetail = isOn; })
        Text('ListDetail')
          .fontSize(10)
        Blank()
        Toggle({ type: ToggleType.Switch, isOn: this.showDetailPane })
          .onChange((isOn: boolean) => { this.showDetailPane = isOn; })
        Text('Detail')
          .fontSize(10)
      }

      // Theme presets
      Row({ space: 4 }) {
        Button('Light')
          .layoutWeight(1)
          .height(26)
          .fontSize(8)
          .backgroundColor(this.currentThemeIndex === 0 ? this.accentColor : '#E0E0E0')
          .fontColor(this.currentThemeIndex === 0 ? '#FFFFFF' : '#333333')
          .onClick(() => { this.applyTheme(0); })
        Button('Tablet')
          .layoutWeight(1)
          .height(26)
          .fontSize(8)
          .backgroundColor(this.currentThemeIndex === 2 ? this.accentColor : '#E0E0E0')
          .fontColor(this.currentThemeIndex === 2 ? '#FFFFFF' : '#333333')
          .onClick(() => { this.applyTheme(2); })
        Button('Dark')
          .layoutWeight(1)
          .height(26)
          .fontSize(8)
          .backgroundColor(this.currentThemeIndex === 3 ? this.accentColor : '#E0E0E0')
          .fontColor(this.currentThemeIndex === 3 ? '#FFFFFF' : '#333333')
          .onClick(() => { this.applyTheme(3); })
      }

      // Action buttons
      Row({ space: 6 }) {
        Button('Reset')
          .layoutWeight(1)
          .height(28)
          .fontSize(10)
          .onClick(() => { this.resetMetrics(); })
        Button('Clear Log')
          .layoutWeight(1)
          .height(28)
          .fontSize(10)
          .onClick(() => { this.logEntries = []; })
        Button('Show List')
          .layoutWeight(1)
          .height(28)
          .fontSize(10)
          .onClick(() => {
            this.isShow = true;
            this.addLog('Show', 'Fold list sheet opened');
          })
      }

      // Log display
      Text('Event Log:')
        .fontSize(13)
        .fontWeight(FontWeight.Bold)
        .alignSelf(ItemAlign.Start)

      Scroll() {
        Column({ space: 1 }) {
          ForEach(this.logEntries.slice().reverse(), (entry: AdvancedLogEntry) => {
            Row() {
              Text(entry.time)
                .fontSize(8)
                .fontColor('#888888')
                .width(80)
              Text(entry.action)
                .fontSize(9)
                .width(70)
                .fontColor(this.accentColor)
              Text(entry.detail)
                .fontSize(9)
                .layoutWeight(1)
            }
            .width('100%')
          })
        }
        .width('100%')
      }
      .layoutWeight(1)
      .width('100%')
      .backgroundColor('#FAFAFA')
      .borderRadius(8)
      .padding(4)
    }
    .width('100%')
    .height('100%')
    .bindSheet($$this.isShow, this.builderFoldListSheet(), {
      height: '70%',
      dragBar: true,
      backgroundColor: this.listBgColor,
      detents: [300, 500, 700],
      mode: SheetMode.OVERLAY,
      showClose: true,
    })
  }

  @Builder
  buildMetricCard(title: string, value: string, color: string) {
    Column() {
      Text(title)
        .fontSize(9)
        .fontColor('#666666')
      Text(value)
        .fontSize(16)
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
  builderFoldListSheet() {
    Column() {
      Text('Fold-Adaptive List')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 16, bottom: 4 })

      Text(`Status: ${this.simulatedStatus} | Columns: ${this.columnCount}`)
        .fontSize(13)
        .fontColor('#666666')
        .margin({ bottom: 12 })

      // Fold state buttons
      Row({ space: 8 }) {
        Button('Folded')
          .layoutWeight(1)
          .height(32)
          .fontSize(11)
          .backgroundColor(this.simulatedStatus === 'folded' ? this.accentColor : '#E0E0E0')
          .fontColor(this.simulatedStatus === 'folded' ? '#FFFFFF' : '#333333')
          .onClick(() => { this.setSimulatedStatus('folded'); })
        Button('Half')
          .layoutWeight(1)
          .height(32)
          .fontSize(11)
          .backgroundColor(this.simulatedStatus === 'half_folded' ? this.accentColor : '#E0E0E0')
          .fontColor(this.simulatedStatus === 'half_folded' ? '#FFFFFF' : '#333333')
          .onClick(() => { this.setSimulatedStatus('half_folded'); })
        Button('Expanded')
          .layoutWeight(1)
          .height(32)
          .fontSize(11)
          .backgroundColor(this.simulatedStatus === 'expanded' ? this.accentColor : '#E0E0E0')
          .fontColor(this.simulatedStatus === 'expanded' ? '#FFFFFF' : '#333333')
          .onClick(() => { this.setSimulatedStatus('expanded'); })
      }
      .margin({ bottom: 8 })

      // List-detail or list
      if (this.enableListDetail) {
        if (this.simulatedStatus === 'expanded' && this.showDetailPane) {
          Row({ space: 8 }) {
            Column() {
              this.builderScrollList(8)
            }
            .layoutWeight(1)
            .backgroundColor('#F5F5F5')
            .borderRadius(8)

            Column() {
              this.builderDetailPanel()
            }
            .width('45%')
            .backgroundColor('#FFFFFF')
            .borderRadius(8)
            .border({ width: 1, color: '#E0E0E0' })
          }
          .width('100%')
          .height(this.listItemHeight * 5 + 40)
        } else {
          Column() {
            this.builderScrollList(10)
          }
          .width('100%')
          .backgroundColor('#F5F5F5')
          .borderRadius(8)
        }
      } else {
        GridRow({ columns: this.columnCount, gutter: { x: 8, y: 8 } }) {
          ForEach(this.getFilteredData().slice(0, 12), (item: ListItemInfo) => {
            GridCol() {
              this.builderListItem(item)
            }
          })
        }
        .width('100%')
        .layoutWeight(1)
        .padding(8)
        .backgroundColor(this.listBgColor)
        .borderRadius(8)
      }

      // Close button
      Button('Close Sheet')
        .width('80%')
        .height(40)
        .fontSize(14)
        .margin({ bottom: 16 })
        .onClick(() => {
          this.isShow = false;
          this.addLog('Close', 'Fold list sheet closed');
        })
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  builderScrollList(count: number) {
    List({ space: this.listSpacing }) {
      ForEach(this.getFilteredData().slice(0, count), (item: ListItemInfo) => {
        ListItem() {
          this.builderListItem(item)
        }
        .backgroundColor(this.selectedItemId === item.id ? this.selectedColor : this.itemBgColor)
        .borderRadius(8)
        .onClick(() => { this.selectItem(item); })
      })
    }
    .width('100%')
    .layoutWeight(1)
    .padding({ left: 8, right: 8, top: 8, bottom: 8 })
    .onScrollIndex((start: number, end: number) => {
      this.onScroll(start * this.listItemHeight);
    })
  }

  @Builder
  builderListItem(item: ListItemInfo) {
    Row({ space: 8 }) {
      Column() {
        Text(item.id.toString())
          .fontSize(18)
          .fontWeight(FontWeight.Bold)
          .fontColor('#FFFFFF')
      }
      .width(36)
      .height(36)
      .backgroundColor(this.accentColor)
      .borderRadius(18)
      .justifyContent(FlexAlign.Center)
      .alignItems(HorizontalAlign.Center)

      Column({ space: 2 }) {
        Text(item.title)
          .fontSize(13)
          .fontWeight(FontWeight.Bold)
        if (this.showCategories) {
          Text(item.category)
            .fontSize(9)
            .fontColor('#666666')
        }
      }
      .layoutWeight(1)
      .alignItems(HorizontalAlign.Start)

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
    .padding({ left: 12, right: 12 })
    .alignItems(VerticalAlign.Center)
  }

  @Builder
  builderDetailPanel() {
    Column({ space: 8 }) {
      Text(this.getSelectedItem().title)
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
      Text(this.getSelectedItem().subtitle)
        .fontSize(11)
        .fontColor('#666666')
      Text(this.getSelectedItem().description)
        .fontSize(11)
        .textAlign(TextAlign.Center)
      Row({ space: 8 }) {
        Text(this.getSelectedItem().category)
          .fontSize(9)
          .backgroundColor(this.getSelectedItem().color)
          .padding(4)
          .borderRadius(4)
        Text(this.getSelectedItem().badge)
          .fontSize(9)
          .backgroundColor('#E0E0E0')
          .padding(4)
          .borderRadius(4)
      }
      Text(`ID: ${this.getSelectedItem().id}`)
        .fontSize(9)
        .fontColor('#999999')
    }
    .width('100%')
    .height('100%')
    .padding(12)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
  }
}
