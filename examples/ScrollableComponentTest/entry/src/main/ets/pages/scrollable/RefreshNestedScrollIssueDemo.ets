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

@Entry
@Component
struct RefreshNestedScrollIssueDemo {
  @State refreshEnabled: boolean = false;
  @State refreshing: boolean = false;
  @State issueModeEnabled: boolean = true;
  @State refreshCount: number = 0;
  @State topEdgeCount: number = 0;
  @State bottomEdgeCount: number = 0;
  @State statusText: string = '初始状态：Refresh 关闭，Issue Mode 开';
  @State items: number[] = [];

  aboutToAppear(): void {
    for (let index = 0; index < 40; index++) {
      this.items.push(index);
    }
  }

  private getIssueNestedScroll(): NestedScrollOptions | undefined {
    if (!this.issueModeEnabled) {
      return undefined;
    }
    return {
      scrollForward: NestedScrollMode.SELF_ONLY,
      scrollBackward: NestedScrollMode.SELF_ONLY
    };
  }

  private resetDemo(): void {
    this.refreshEnabled = false;
    this.refreshing = false;
    this.issueModeEnabled = true;
    this.refreshCount = 0;
    this.topEdgeCount = 0;
    this.bottomEdgeCount = 0;
    this.statusText = '已重置：先在顶部多次下拉，再点击“开启下拉刷新”';
  }

  private completeRefresh(): void {
    setTimeout(() => {
      this.refreshing = false;
      this.statusText = 'Refresh 已结束';
    }, 1200);
  }

  @Builder
  private buildScrollContent() {
    Column({ space: 8 }) {
      Text('从这个滚动区域内部开始下拉')
        .fontSize(14)
        .fontColor('#344054')
        .width('100%')
        .padding({ left: 12, right: 12, top: 12 })

      ForEach(this.items, (item: number) => {
        Text('item ' + item)
          .width('100%')
          .height(52)
          .textAlign(TextAlign.Center)
          .backgroundColor(item % 2 === 0 ? '#FFFFFF' : '#F8FAFC')
          .borderRadius(8)
      }, (item: number) => item.toString())
    }
    .width('100%')
    .padding(12)
  }

  build() {
    Column({ space: 10 }) {
      Text('Pure ArkTS Refresh / Scroll 复现 Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
        .width('100%')

      Text('目标：模拟先下拉多次，再动态开启 Refresh，后续下拉仍优先触发 Scroll 越界的问题路径。')
        .fontSize(13)
        .fontColor('#475467')
        .lineHeight(19)
        .width('100%')

      Column({ space: 2 }) {
        Text('操作步骤')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .fontColor('#182230')
          .width('100%')
        Text('1. 点击“重置”')
          .fontSize(12)
          .fontColor('#667085')
          .width('100%')
        Text('2. 保持 Issue Mode：开，在下方滚动区域顶部连续下拉几次')
          .fontSize(12)
          .fontColor('#667085')
          .width('100%')
        Text('3. 点击“开启下拉刷新”')
          .fontSize(12)
          .fontColor('#667085')
          .width('100%')
        Text('4. 再次从滚动区域顶部下拉，观察 Refresh 或 Scroll 越界是否触发')
          .fontSize(12)
          .fontColor('#667085')
          .width('100%')
      }
      .width('100%')
      .padding(10)
      .backgroundColor('#FFFFFF')
      .borderRadius(10)

      Row({ space: 8 }) {
        Button('重置')
          .onClick(() => this.resetDemo())
        Button(this.refreshEnabled ? '关闭下拉刷新' : '开启下拉刷新')
          .onClick(() => {
            this.refreshEnabled = !this.refreshEnabled;
            this.refreshing = false;
            this.statusText = this.refreshEnabled ? 'Refresh 已开启：请再次从滚动区域顶部下拉' : 'Refresh 已关闭';
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button(this.issueModeEnabled ? 'Issue Mode：开' : 'Issue Mode：关')
          .onClick(() => {
            this.issueModeEnabled = !this.issueModeEnabled;
            this.statusText = this.issueModeEnabled ? 'Issue Mode 已开启' : 'Issue Mode 已关闭，子 Scroll 恢复默认 nestedScroll';
          })
        Button(this.refreshing ? '结束刷新状态' : '进入刷新状态')
          .onClick(() => {
            this.refreshing = !this.refreshing;
            this.statusText = this.refreshing ? '手动置为刷新中' : '手动结束刷新';
          })
      }
      .width('100%')

      Column({ space: 4 }) {
        Text('Refresh 开关: ' + (this.refreshEnabled ? '开' : '关'))
          .fontSize(14)
          .fontColor('#344054')
        Text('Refresh 触发次数: ' + this.refreshCount)
          .fontSize(14)
          .fontColor('#344054')
        Text('Scroll 顶部越界次数: ' + this.topEdgeCount)
          .fontSize(14)
          .fontColor('#344054')
        Text('Scroll 底部越界次数: ' + this.bottomEdgeCount)
          .fontSize(14)
          .fontColor('#344054')
        Text('当前状态: ' + this.statusText)
          .fontSize(13)
          .fontColor('#667085')
          .width('100%')
      }
      .width('100%')
      .padding(10)
      .backgroundColor('#FFFFFF')
      .borderRadius(10)

      Refresh({ refreshing: $$this.refreshing }) {
        Scroll() {
          this.buildScrollContent()
        }
        .width('100%')
        .height('100%')
        .onScrollEdge((edge: Edge) => {
          if (edge === Edge.Top) {
            this.topEdgeCount += 1;
            this.statusText = 'Scroll 顶部越界触发 ' + this.topEdgeCount + ' 次';
          } else if (edge === Edge.Bottom) {
            this.bottomEdgeCount += 1;
            this.statusText = 'Scroll 底部越界触发 ' + this.bottomEdgeCount + ' 次';
          }
        })
        .nestedScroll(this.getIssueNestedScroll())
      }
      .width('100%')
      .layoutWeight(1)
      .pullToRefresh(this.refreshEnabled)
      .refreshOffset(45)
      .onRefreshing(() => {
        this.refreshCount += 1;
        this.refreshing = true;
        this.statusText = 'Refresh 触发，第 ' + this.refreshCount + ' 次';
        this.completeRefresh();
      })
      .backgroundColor('#EAF2FF')
      .borderRadius(14)
    }
    .width('100%')
    .height('100%')
    .padding(14)
    .backgroundColor('#F5F6FA')
  }
}
