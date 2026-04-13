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

import { typeNode } from '@kit.ArkUI';

class ArticleCard {
  public id: number;
  public title: string;
  public summary: string;
  public owner: string;
  public color: string;

  constructor(id: number, title: string, summary: string, owner: string, color: string) {
    this.id = id;
    this.title = title;
    this.summary = summary;
    this.owner = owner;
    this.color = color;
  }
}

class TaskCard {
  public id: number;
  public title: string;
  public status: string;
  public owner: string;
  public priority: string;

  constructor(id: number, title: string, status: string, owner: string, priority: string) {
    this.id = id;
    this.title = title;
    this.status = status;
    this.owner = owner;
    this.priority = priority;
  }
}

class DashboardCard {
  public id: number;
  public title: string;
  public value: string;
  public detail: string;
  public color: string;

  constructor(id: number, title: string, value: string, detail: string, color: string) {
    this.id = id;
    this.title = title;
    this.value = value;
    this.detail = detail;
    this.color = color;
  }
}

class GalleryCard {
  public id: number;
  public title: string;
  public label: string;
  public height: number;
  public color: string;

  constructor(id: number, title: string, label: string, height: number, color: string) {
    this.id = id;
    this.title = title;
    this.label = label;
    this.height = height;
    this.color = color;
  }
}

type ScrollableComponentType = 'Scroll' | 'List' | 'Grid' | 'WaterFlow';

@Entry
@Component
struct ScrollFrameNodeScenes {
  private static readonly ARTICLE_ID: string = 'scroll_frame_node_article_id';
  private static readonly TASK_ID: string = 'scroll_frame_node_task_id';
  private static readonly DASHBOARD_ID: string = 'scroll_frame_node_dashboard_id';
  private static readonly GALLERY_ID: string = 'scroll_frame_node_gallery_id';

  private pageScroller: Scroller = new Scroller();
  private articleDefaultScroller: Scroller = new Scroller();
  private articleDynamicScroller: Scroller = new Scroller();
  private taskDefaultScroller: Scroller = new Scroller();
  private taskDynamicScroller: Scroller = new Scroller();
  private dashboardDefaultScroller: Scroller = new Scroller();
  private dashboardDynamicScroller: Scroller = new Scroller();
  private galleryDefaultScroller: Scroller = new Scroller();
  private galleryDynamicScroller: Scroller = new Scroller();
  private logSeed: number = 0;

  @State private overviewText: string = 'Default controllers ready: 0/4 | Dynamic controllers ready: 0/4';

  @State private articleBindResult: string = 'Article dynamic scroller is not bound';
  @State private articleHostNodeText: string = 'Host node: pending';
  @State private articleDefaultNodeText: string = 'Default node: pending';
  @State private articleDynamicNodeText: string = 'Dynamic node: pending';
  @State private articleDefaultOffsetText: string = 'Default yOffset: 0';
  @State private articleDynamicOffsetText: string = 'Dynamic yOffset: 0';

  @State private taskBindResult: string = 'Task dynamic scroller is not bound';
  @State private taskHostNodeText: string = 'Host node: pending';
  @State private taskDefaultNodeText: string = 'Default node: pending';
  @State private taskDynamicNodeText: string = 'Dynamic node: pending';
  @State private taskDefaultOffsetText: string = 'Default yOffset: 0';
  @State private taskDynamicOffsetText: string = 'Dynamic yOffset: 0';

  @State private dashboardBindResult: string = 'Dashboard dynamic scroller is not bound';
  @State private dashboardHostNodeText: string = 'Host node: pending';
  @State private dashboardDefaultNodeText: string = 'Default node: pending';
  @State private dashboardDynamicNodeText: string = 'Dynamic node: pending';
  @State private dashboardDefaultOffsetText: string = 'Default yOffset: 0';
  @State private dashboardDynamicOffsetText: string = 'Dynamic yOffset: 0';

  @State private galleryBindResult: string = 'Gallery dynamic scroller is not bound';
  @State private galleryHostNodeText: string = 'Host node: pending';
  @State private galleryDefaultNodeText: string = 'Default node: pending';
  @State private galleryDynamicNodeText: string = 'Dynamic node: pending';
  @State private galleryDefaultOffsetText: string = 'Default yOffset: 0';
  @State private galleryDynamicOffsetText: string = 'Dynamic yOffset: 0';

  @State private articles: ArticleCard[] = [];
  @State private tasks: TaskCard[] = [];
  @State private dashboardCards: DashboardCard[] = [];
  @State private galleryCards: GalleryCard[] = [];
  @State private logs: string[] = [];

  aboutToAppear(): void {
    this.initArticles();
    this.initTasks();
    this.initDashboardCards();
    this.initGalleryCards();
    this.refreshSummaryState();
    this.pushLog('data initialized in aboutToAppear');
  }

  onDidBuild(): void {
    this.refreshAllStates('onDidBuild');
    this.pushLog('onDidBuild finished, default scrollers should already carry host FrameNode');
  }

  private initArticles(): void {
    const data: ArticleCard[] = [];
    const colors: string[] = ['#FCE4EC', '#E8F5E9', '#E3F2FD', '#FFF3E0'];
    for (let i = 0; i < 12; i++) {
      data.push(new ArticleCard(
        i,
        `Long article block ${i + 1}`,
        `This section simulates policy, protocol, or release-note reading. The business side wants to use scroller.getFrameNode() to confirm that the controller has already attached to the current scroll host before calling follow-up APIs.`,
        i % 2 === 0 ? 'Docs Team' : 'Release Team',
        colors[i % colors.length]
      ));
    }
    this.articles = data;
  }

  private initTasks(): void {
    const data: TaskCard[] = [];
    const statusList: string[] = ['Running', 'Queued', 'Blocked', 'Done'];
    const priorityList: string[] = ['P0', 'P1', 'P2', 'P3'];
    for (let i = 0; i < 24; i++) {
      data.push(new TaskCard(
        i,
        `Operation item ${i + 1}`,
        statusList[i % statusList.length],
        i % 2 === 0 ? 'Scroll QA' : 'ArkUI Dev',
        priorityList[i % priorityList.length]
      ));
    }
    this.tasks = data;
  }

  private initDashboardCards(): void {
    const data: DashboardCard[] = [];
    const colors: string[] = ['#E1F5FE', '#F1F8E9', '#FFF8E1', '#FCE4EC', '#F3E5F5', '#E8EAF6'];
    for (let i = 0; i < 18; i++) {
      data.push(new DashboardCard(
        i,
        `Metric ${i + 1}`,
        `${80 + i}%`,
        i % 2 === 0 ? 'Realtime throughput snapshot' : 'Daily regression pass rate',
        colors[i % colors.length]
      ));
    }
    this.dashboardCards = data;
  }

  private initGalleryCards(): void {
    const data: GalleryCard[] = [];
    const colors: string[] = ['#D7CCC8', '#FFECB3', '#B2DFDB', '#BBDEFB', '#D1C4E9', '#C8E6C9'];
    const heights: number[] = [100, 136, 120, 164, 108, 144];
    for (let i = 0; i < 24; i++) {
      data.push(new GalleryCard(
        i,
        `Asset ${i + 1}`,
        i % 2 === 0 ? 'Review' : 'Approved',
        heights[i % heights.length],
        colors[i % colors.length]
      ));
    }
    this.galleryCards = data;
  }

  private pushLog(message: string): void {
    this.logSeed += 1;
    const nextLogs: string[] = [`#${this.logSeed} ${message}`];
    for (let i = 0; i < this.logs.length && i < 19; i++) {
      nextLogs.push(this.logs[i]);
    }
    this.logs = nextLogs;
  }

  private clearLogs(): void {
    this.logs = [];
    this.pushLog('logs cleared');
  }

  private getOffsetText(scroller: Scroller, label: string): string {
    const yOffset = scroller.currentOffset()?.yOffset ?? 0;
    return `${label} yOffset: ${yOffset}`;
  }

  private safeGetFrameNode(scroller: Scroller) {
    if (typeof scroller.getFrameNode !== 'function') {
      return null;
    }
    return scroller.getFrameNode() ?? null;
  }

  private getDynamicStatus(scroller: Scroller): string {
    return this.safeGetFrameNode(scroller) ? 'dynamic ready' : 'dynamic empty';
  }

  private describeScrollerNode(scroller: Scroller, label: string): string {
    const frameNode = this.safeGetFrameNode(scroller);
    if (!frameNode) {
      return `${label}: empty`;
    }
    return `${label}: ${frameNode.getNodeType()} / id=${frameNode.getId()} / uid=${frameNode.getUniqueId()}`;
  }

  private describeHostNode(componentId: string, label: string): string {
    const frameNode = this.getUIContext().getFrameNodeById(componentId);
    if (!frameNode) {
      return `${label}: null`;
    }
    return `${label}: ${frameNode.getNodeType()} / id=${frameNode.getId()} / uid=${frameNode.getUniqueId()}`;
  }

  private getReadyCount(scrollers: Scroller[]): number {
    let count = 0;
    for (let i = 0; i < scrollers.length; i++) {
      if (this.safeGetFrameNode(scrollers[i])) {
        count++;
      }
    }
    return count;
  }

  private refreshSummaryState(): void {
    this.updateOverviewText();
  }

  private updateOverviewText(): void {
    const defaultReady = this.getReadyCount([
      this.articleDefaultScroller,
      this.taskDefaultScroller,
      this.dashboardDefaultScroller,
      this.galleryDefaultScroller
    ]);
    const dynamicReady = this.getReadyCount([
      this.articleDynamicScroller,
      this.taskDynamicScroller,
      this.dashboardDynamicScroller,
      this.galleryDynamicScroller
    ]);
    this.overviewText = `Default controllers ready: ${defaultReady}/4 | Dynamic controllers ready: ${dynamicReady}/4`;
  }

  private refreshArticleState(): void {
    this.articleHostNodeText = this.describeHostNode(ScrollFrameNodeScenes.ARTICLE_ID, 'Host node');
    this.articleDefaultNodeText = this.describeScrollerNode(this.articleDefaultScroller, 'Default node');
    this.articleDynamicNodeText = this.describeScrollerNode(this.articleDynamicScroller, 'Dynamic node');
    this.articleDefaultOffsetText = this.getOffsetText(this.articleDefaultScroller, 'Default');
    this.articleDynamicOffsetText = this.getOffsetText(this.articleDynamicScroller, 'Dynamic');
  }

  private refreshTaskState(): void {
    this.taskHostNodeText = this.describeHostNode(ScrollFrameNodeScenes.TASK_ID, 'Host node');
    this.taskDefaultNodeText = this.describeScrollerNode(this.taskDefaultScroller, 'Default node');
    this.taskDynamicNodeText = this.describeScrollerNode(this.taskDynamicScroller, 'Dynamic node');
    this.taskDefaultOffsetText = this.getOffsetText(this.taskDefaultScroller, 'Default');
    this.taskDynamicOffsetText = this.getOffsetText(this.taskDynamicScroller, 'Dynamic');
  }

  private refreshDashboardState(): void {
    this.dashboardHostNodeText = this.describeHostNode(ScrollFrameNodeScenes.DASHBOARD_ID, 'Host node');
    this.dashboardDefaultNodeText = this.describeScrollerNode(this.dashboardDefaultScroller, 'Default node');
    this.dashboardDynamicNodeText = this.describeScrollerNode(this.dashboardDynamicScroller, 'Dynamic node');
    this.dashboardDefaultOffsetText = this.getOffsetText(this.dashboardDefaultScroller, 'Default');
    this.dashboardDynamicOffsetText = this.getOffsetText(this.dashboardDynamicScroller, 'Dynamic');
  }

  private refreshGalleryState(): void {
    this.galleryHostNodeText = this.describeHostNode(ScrollFrameNodeScenes.GALLERY_ID, 'Host node');
    this.galleryDefaultNodeText = this.describeScrollerNode(this.galleryDefaultScroller, 'Default node');
    this.galleryDynamicNodeText = this.describeScrollerNode(this.galleryDynamicScroller, 'Dynamic node');
    this.galleryDefaultOffsetText = this.getOffsetText(this.galleryDefaultScroller, 'Default');
    this.galleryDynamicOffsetText = this.getOffsetText(this.galleryDynamicScroller, 'Dynamic');
  }

  private refreshAllStates(reason: string): void {
    this.refreshArticleState();
    this.refreshTaskState();
    this.refreshDashboardState();
    this.refreshGalleryState();
    this.refreshSummaryState();
    this.pushLog(`refresh state by ${reason}`);
  }

  private bindControllerById(
    componentId: string,
    scroller: Scroller,
    type: ScrollableComponentType,
    label: string
  ): string {
    const frameNode = this.getUIContext().getFrameNodeById(componentId);
    if (!frameNode) {
      return `${label} bind failed: FrameNode is null`;
    }
    try {
      switch (type) {
        case 'Scroll':
          typeNode.bindController(frameNode, scroller, 'Scroll');
          break;
        case 'List':
          typeNode.bindController(frameNode, scroller, 'List');
          break;
        case 'Grid':
          typeNode.bindController(frameNode, scroller, 'Grid');
          break;
        case 'WaterFlow':
          typeNode.bindController(frameNode, scroller, 'WaterFlow');
          break;
      }
      return `${label} bind success`;
    } catch (e) {
      return `${label} bind failed: code=${e.code}, msg=${e.message}`;
    }
  }

  private bindArticleDynamic(): void {
    this.articleBindResult = this.bindControllerById(
      ScrollFrameNodeScenes.ARTICLE_ID,
      this.articleDynamicScroller,
      'Scroll',
      'Article dynamic controller'
    );
    this.refreshArticleState();
    this.updateOverviewText();
    this.pushLog(this.articleBindResult);
  }

  private bindTaskDynamic(): void {
    this.taskBindResult = this.bindControllerById(
      ScrollFrameNodeScenes.TASK_ID,
      this.taskDynamicScroller,
      'List',
      'Task dynamic controller'
    );
    this.refreshTaskState();
    this.updateOverviewText();
    this.pushLog(this.taskBindResult);
  }

  private bindDashboardDynamic(): void {
    this.dashboardBindResult = this.bindControllerById(
      ScrollFrameNodeScenes.DASHBOARD_ID,
      this.dashboardDynamicScroller,
      'Grid',
      'Dashboard dynamic controller'
    );
    this.refreshDashboardState();
    this.updateOverviewText();
    this.pushLog(this.dashboardBindResult);
  }

  private bindGalleryDynamic(): void {
    this.galleryBindResult = this.bindControllerById(
      ScrollFrameNodeScenes.GALLERY_ID,
      this.galleryDynamicScroller,
      'WaterFlow',
      'Gallery dynamic controller'
    );
    this.refreshGalleryState();
    this.updateOverviewText();
    this.pushLog(this.galleryBindResult);
  }

  private bindAllDynamic(): void {
    this.bindArticleDynamic();
    this.bindTaskDynamic();
    this.bindDashboardDynamic();
    this.bindGalleryDynamic();
    this.pushLog('bindAllDynamic completed');
  }

  private compareHostAndScroller(componentId: string, scroller: Scroller, label: string): void {
    const hostNode = this.getUIContext().getFrameNodeById(componentId);
    const controllerNode = this.safeGetFrameNode(scroller);
    if (!hostNode || !controllerNode) {
      this.pushLog(`${label} compare skipped because host or controller node is missing`);
      return;
    }
    const sameNode = hostNode.getUniqueId() === controllerNode.getUniqueId();
    this.pushLog(`${label} compare result: hostUid=${hostNode.getUniqueId()} controllerUid=${controllerNode.getUniqueId()} same=${sameNode}`);
  }

  private compareAllNodes(): void {
    this.compareHostAndScroller(ScrollFrameNodeScenes.ARTICLE_ID, this.articleDefaultScroller, 'Article default');
    this.compareHostAndScroller(ScrollFrameNodeScenes.ARTICLE_ID, this.articleDynamicScroller, 'Article dynamic');
    this.compareHostAndScroller(ScrollFrameNodeScenes.TASK_ID, this.taskDefaultScroller, 'Task default');
    this.compareHostAndScroller(ScrollFrameNodeScenes.TASK_ID, this.taskDynamicScroller, 'Task dynamic');
    this.compareHostAndScroller(ScrollFrameNodeScenes.DASHBOARD_ID, this.dashboardDefaultScroller, 'Dashboard default');
    this.compareHostAndScroller(ScrollFrameNodeScenes.DASHBOARD_ID, this.dashboardDynamicScroller, 'Dashboard dynamic');
    this.compareHostAndScroller(ScrollFrameNodeScenes.GALLERY_ID, this.galleryDefaultScroller, 'Gallery default');
    this.compareHostAndScroller(ScrollFrameNodeScenes.GALLERY_ID, this.galleryDynamicScroller, 'Gallery dynamic');
  }

  private scrollByDelta(scroller: Scroller, delta: number, label: string): void {
    scroller.scrollBy(0, delta);
    this.refreshAllStates(`${label} scrollBy ${delta}`);
  }

  private scrollToTop(scroller: Scroller, label: string): void {
    scroller.scrollEdge(Edge.Top);
    this.refreshAllStates(`${label} scrollEdge Top`);
  }

  private scrollToBottom(scroller: Scroller, label: string): void {
    scroller.scrollEdge(Edge.Bottom);
    this.refreshAllStates(`${label} scrollEdge Bottom`);
  }

  private scrollAllDefaultsForward(): void {
    this.articleDefaultScroller.scrollBy(0, 180);
    this.taskDefaultScroller.scrollBy(0, 180);
    this.dashboardDefaultScroller.scrollBy(0, 180);
    this.galleryDefaultScroller.scrollBy(0, 180);
    this.refreshAllStates('scrollAllDefaultsForward');
  }

  private scrollAllDynamicsToTop(): void {
    this.articleDynamicScroller.scrollEdge(Edge.Top);
    this.taskDynamicScroller.scrollEdge(Edge.Top);
    this.dashboardDynamicScroller.scrollEdge(Edge.Top);
    this.galleryDynamicScroller.scrollEdge(Edge.Top);
    this.refreshAllStates('scrollAllDynamicsToTop');
  }

  @Builder
  buildSummaryCard(title: string, total: string, detail: string, color: string) {
    Column({ space: 6 }) {
      Text(title)
        .fontSize(14)
        .fontWeight(FontWeight.Medium)

      Text(total)
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Text(detail)
        .fontSize(12)
    }
    .width(0)
    .layoutWeight(1)
    .padding(12)
    .borderRadius(8)
    .backgroundColor(color);
  }

  @Builder
  buildActionButton(label: string, action: () => void) {
    Button(label)
      .width(0)
      .layoutWeight(1)
      .onClick(() => {
        action();
      });
  }

  @Builder
  buildHeaderSection() {
    Column({ space: 12 }) {
      Text('Scroller.getFrameNode Rich Demo')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)

      Text('This page expands the original tiny bind-controller sample into four practical scenes: article reading, operation task list, dashboard grid, and gallery waterflow. The goal is to verify when a Scroller already owns a FrameNode, when a dynamic Scroller becomes valid after bindController, and whether the node returned by scroller.getFrameNode() matches the node fetched from UIContext.')
        .fontSize(14)

      Text(this.overviewText)
        .fontSize(14)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        this.buildSummaryCard('Scroll', `${this.articles.length}`, this.getDynamicStatus(this.articleDynamicScroller), '#FFF3E0');
        this.buildSummaryCard('List', `${this.tasks.length}`, this.getDynamicStatus(this.taskDynamicScroller), '#E8F5E9');
      }

      Row({ space: 10 }) {
        this.buildSummaryCard('Grid', `${this.dashboardCards.length}`, this.getDynamicStatus(this.dashboardDynamicScroller), '#E3F2FD');
        this.buildSummaryCard('WaterFlow', `${this.galleryCards.length}`, this.getDynamicStatus(this.galleryDynamicScroller), '#FCE4EC');
      }

      Row({ space: 10 }) {
        this.buildActionButton('Bind All', () => {
          this.bindAllDynamic();
        });
        this.buildActionButton('Refresh All', () => {
          this.refreshAllStates('manual refresh all');
        });
      }

      Row({ space: 10 }) {
        this.buildActionButton('Compare All', () => {
          this.compareAllNodes();
        });
        this.buildActionButton('All Default +180', () => {
          this.scrollAllDefaultsForward();
        });
      }

      Row({ space: 10 }) {
        this.buildActionButton('All Dynamic Top', () => {
          this.scrollAllDynamicsToTop();
        });
        this.buildActionButton('Clear Logs', () => {
          this.clearLogs();
        });
      }
    }
    .width('100%')
    .padding(16)
    .borderRadius(8)
    .backgroundColor('#FFFFFF');
  }

  @Builder
  buildArticleSection() {
    Column({ space: 10 }) {
      Text('Scene 1: Long article reading')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Text('A protocol, changelog, or product guide page usually binds a default Scroller directly on the Scroll component. A second Scroller may be attached later when a floating toolbar or plug-in wants to take over control.')
        .fontSize(13)

      Text(this.articleBindResult).fontSize(13)
      Text(this.articleHostNodeText).fontSize(12)
      Text(this.articleDefaultNodeText).fontSize(12)
      Text(this.articleDynamicNodeText).fontSize(12)
      Text(this.articleDefaultOffsetText).fontSize(12)
      Text(this.articleDynamicOffsetText).fontSize(12)

      Row({ space: 8 }) {
        this.buildActionButton('Bind Article', () => {
          this.bindArticleDynamic();
        });
        this.buildActionButton('Read Nodes', () => {
          this.refreshArticleState();
          this.updateOverviewText();
          this.pushLog('Article node text refreshed');
        });
      }

      Row({ space: 8 }) {
        this.buildActionButton('Compare', () => {
          this.compareHostAndScroller(ScrollFrameNodeScenes.ARTICLE_ID, this.articleDefaultScroller, 'Article default');
          this.compareHostAndScroller(ScrollFrameNodeScenes.ARTICLE_ID, this.articleDynamicScroller, 'Article dynamic');
        });
        this.buildActionButton('Default +180', () => {
          this.scrollByDelta(this.articleDefaultScroller, 180, 'Article default');
        });
      }

      Row({ space: 8 }) {
        this.buildActionButton('Dynamic +180', () => {
          this.scrollByDelta(this.articleDynamicScroller, 180, 'Article dynamic');
        });
        this.buildActionButton('Default Top', () => {
          this.scrollToTop(this.articleDefaultScroller, 'Article default');
        });
      }

      Row({ space: 8 }) {
        this.buildActionButton('Default Bottom', () => {
          this.scrollToBottom(this.articleDefaultScroller, 'Article default');
        });
        this.buildActionButton('Dynamic Bottom', () => {
          this.scrollToBottom(this.articleDynamicScroller, 'Article dynamic');
        });
      }

      Scroll(this.articleDefaultScroller) {
        Column({ space: 10 }) {
          ForEach(this.articles, (item: ArticleCard) => {
            Column({ space: 6 }) {
              Text(item.title)
                .fontSize(16)
                .fontWeight(FontWeight.Bold)
              Text(`Owner: ${item.owner}`)
                .fontSize(12)
              Text(item.summary)
                .fontSize(13)
            }
            .width('100%')
            .padding(12)
            .borderRadius(8)
            .backgroundColor(item.color);
          }, (item: ArticleCard) => item.id.toString())
        }
        .width('100%');
      }
      .id(ScrollFrameNodeScenes.ARTICLE_ID)
      .height(300)
      .width('100%')
      .borderWidth(1)
      .borderColor('#D0D7DE');
    }
    .width('100%')
    .padding(16)
    .borderRadius(8)
    .backgroundColor('#FFFFFF');
  }

  @Builder
  buildTaskSection() {
    Column({ space: 10 }) {
      Text('Scene 2: Operation task center')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Text('A task list often needs late binding. For example, a page first renders with its own default Scroller, and later a plug-in or inspector panel asks for the same host FrameNode to reuse the scroll position.')
        .fontSize(13)

      Text(this.taskBindResult).fontSize(13)
      Text(this.taskHostNodeText).fontSize(12)
      Text(this.taskDefaultNodeText).fontSize(12)
      Text(this.taskDynamicNodeText).fontSize(12)
      Text(this.taskDefaultOffsetText).fontSize(12)
      Text(this.taskDynamicOffsetText).fontSize(12)

      Row({ space: 8 }) {
        this.buildActionButton('Bind Task', () => {
          this.bindTaskDynamic();
        });
        this.buildActionButton('Read Nodes', () => {
          this.refreshTaskState();
          this.updateOverviewText();
          this.pushLog('Task node text refreshed');
        });
      }

      Row({ space: 8 }) {
        this.buildActionButton('Compare', () => {
          this.compareHostAndScroller(ScrollFrameNodeScenes.TASK_ID, this.taskDefaultScroller, 'Task default');
          this.compareHostAndScroller(ScrollFrameNodeScenes.TASK_ID, this.taskDynamicScroller, 'Task dynamic');
        });
        this.buildActionButton('Default +180', () => {
          this.scrollByDelta(this.taskDefaultScroller, 180, 'Task default');
        });
      }

      Row({ space: 8 }) {
        this.buildActionButton('Dynamic +180', () => {
          this.scrollByDelta(this.taskDynamicScroller, 180, 'Task dynamic');
        });
        this.buildActionButton('Default Top', () => {
          this.scrollToTop(this.taskDefaultScroller, 'Task default');
        });
      }

      Row({ space: 8 }) {
        this.buildActionButton('Default Bottom', () => {
          this.scrollToBottom(this.taskDefaultScroller, 'Task default');
        });
        this.buildActionButton('Dynamic Bottom', () => {
          this.scrollToBottom(this.taskDynamicScroller, 'Task dynamic');
        });
      }

      List({ scroller: this.taskDefaultScroller, space: 8 }) {
        ForEach(this.tasks, (item: TaskCard) => {
          ListItem() {
            Row() {
              Column({ space: 4 }) {
                Text(item.title)
                  .fontSize(15)
                  .fontWeight(FontWeight.Bold)
                Text(`Owner: ${item.owner}`)
                  .fontSize(12)
                Text(`Status: ${item.status}`)
                  .fontSize(12)
              }
              .layoutWeight(1)
              .alignItems(HorizontalAlign.Start)

              Text(item.priority)
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .padding({ left: 10, right: 10, top: 6, bottom: 6 })
                .borderRadius(8)
                .backgroundColor(item.priority === 'P0' ? '#FFCDD2' : item.priority === 'P1' ? '#FFE0B2' : '#E8F5E9');
            }
            .width('100%')
            .padding(12)
            .borderRadius(8)
            .backgroundColor(item.id % 2 === 0 ? '#F7F9FB' : '#EEF3F8');
          }
        }, (item: TaskCard) => item.id.toString())
      }
      .id(ScrollFrameNodeScenes.TASK_ID)
      .height(300)
      .width('100%')
      .borderWidth(1)
      .borderColor('#D0D7DE');
    }
    .width('100%')
    .padding(16)
    .borderRadius(8)
    .backgroundColor('#FFFFFF');
  }

  @Builder
  buildDashboardSection() {
    Column({ space: 10 }) {
      Text('Scene 3: Dashboard grid')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Text('Monitoring dashboards often use Grid. A shared Scroller can be rebound to a grid after the page decides which card group becomes the active viewport. getFrameNode() is useful for tracing whether that controller is already attached to the right host.')
        .fontSize(13)

      Text(this.dashboardBindResult).fontSize(13)
      Text(this.dashboardHostNodeText).fontSize(12)
      Text(this.dashboardDefaultNodeText).fontSize(12)
      Text(this.dashboardDynamicNodeText).fontSize(12)
      Text(this.dashboardDefaultOffsetText).fontSize(12)
      Text(this.dashboardDynamicOffsetText).fontSize(12)

      Row({ space: 8 }) {
        this.buildActionButton('Bind Grid', () => {
          this.bindDashboardDynamic();
        });
        this.buildActionButton('Read Nodes', () => {
          this.refreshDashboardState();
          this.updateOverviewText();
          this.pushLog('Dashboard node text refreshed');
        });
      }

      Row({ space: 8 }) {
        this.buildActionButton('Compare', () => {
          this.compareHostAndScroller(ScrollFrameNodeScenes.DASHBOARD_ID, this.dashboardDefaultScroller, 'Dashboard default');
          this.compareHostAndScroller(ScrollFrameNodeScenes.DASHBOARD_ID, this.dashboardDynamicScroller, 'Dashboard dynamic');
        });
        this.buildActionButton('Default +180', () => {
          this.scrollByDelta(this.dashboardDefaultScroller, 180, 'Dashboard default');
        });
      }

      Row({ space: 8 }) {
        this.buildActionButton('Dynamic +180', () => {
          this.scrollByDelta(this.dashboardDynamicScroller, 180, 'Dashboard dynamic');
        });
        this.buildActionButton('Default Top', () => {
          this.scrollToTop(this.dashboardDefaultScroller, 'Dashboard default');
        });
      }

      Row({ space: 8 }) {
        this.buildActionButton('Default Bottom', () => {
          this.scrollToBottom(this.dashboardDefaultScroller, 'Dashboard default');
        });
        this.buildActionButton('Dynamic Bottom', () => {
          this.scrollToBottom(this.dashboardDynamicScroller, 'Dashboard dynamic');
        });
      }

      Grid(this.dashboardDefaultScroller, { regularSize: [1, 1] }) {
        ForEach(this.dashboardCards, (item: DashboardCard) => {
          GridItem() {
            Column({ space: 8 }) {
              Text(item.title)
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Text(item.value)
                .fontSize(24)
                .fontWeight(FontWeight.Bold)
              Text(item.detail)
                .fontSize(12)
            }
            .width('100%')
            .height('100%')
            .padding(12)
            .borderRadius(8)
            .backgroundColor(item.color);
          }
        }, (item: DashboardCard) => item.id.toString())
      }
      .id(ScrollFrameNodeScenes.DASHBOARD_ID)
      .columnsTemplate('1fr 1fr')
      .columnsGap(10)
      .rowsGap(10)
      .height(320)
      .width('100%')
      .borderWidth(1)
      .borderColor('#D0D7DE');
    }
    .width('100%')
    .padding(16)
    .borderRadius(8)
    .backgroundColor('#FFFFFF');
  }

  @Builder
  buildGallerySection() {
    Column({ space: 10 }) {
      Text('Scene 4: Asset gallery waterflow')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Text('WaterFlow is a good fit for gallery, recommendation, or audit pages. In these cases a helper controller may be bound after the host is created, and getFrameNode() becomes a direct way to check whether the dynamic controller already points at the live WaterFlow node.')
        .fontSize(13)

      Text(this.galleryBindResult).fontSize(13)
      Text(this.galleryHostNodeText).fontSize(12)
      Text(this.galleryDefaultNodeText).fontSize(12)
      Text(this.galleryDynamicNodeText).fontSize(12)
      Text(this.galleryDefaultOffsetText).fontSize(12)
      Text(this.galleryDynamicOffsetText).fontSize(12)

      Row({ space: 8 }) {
        this.buildActionButton('Bind WaterFlow', () => {
          this.bindGalleryDynamic();
        });
        this.buildActionButton('Read Nodes', () => {
          this.refreshGalleryState();
          this.updateOverviewText();
          this.pushLog('Gallery node text refreshed');
        });
      }

      Row({ space: 8 }) {
        this.buildActionButton('Compare', () => {
          this.compareHostAndScroller(ScrollFrameNodeScenes.GALLERY_ID, this.galleryDefaultScroller, 'Gallery default');
          this.compareHostAndScroller(ScrollFrameNodeScenes.GALLERY_ID, this.galleryDynamicScroller, 'Gallery dynamic');
        });
        this.buildActionButton('Default +180', () => {
          this.scrollByDelta(this.galleryDefaultScroller, 180, 'Gallery default');
        });
      }

      Row({ space: 8 }) {
        this.buildActionButton('Dynamic +180', () => {
          this.scrollByDelta(this.galleryDynamicScroller, 180, 'Gallery dynamic');
        });
        this.buildActionButton('Default Top', () => {
          this.scrollToTop(this.galleryDefaultScroller, 'Gallery default');
        });
      }

      Row({ space: 8 }) {
        this.buildActionButton('Default Bottom', () => {
          this.scrollToBottom(this.galleryDefaultScroller, 'Gallery default');
        });
        this.buildActionButton('Dynamic Bottom', () => {
          this.scrollToBottom(this.galleryDynamicScroller, 'Gallery dynamic');
        });
      }

      WaterFlow({ scroller: this.galleryDefaultScroller }) {
        ForEach(this.galleryCards, (item: GalleryCard) => {
          FlowItem() {
            Column({ space: 6 }) {
              Text(item.title)
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
              Text(item.label)
                .fontSize(12)
              Text('This card simulates a gallery tile whose host node may be controlled later by another Scroller.')
                .fontSize(12)
            }
            .width('100%')
            .height('100%')
            .padding(12)
            .justifyContent(FlexAlign.SpaceBetween);
          }
          .width('100%')
          .height(item.height)
          .borderRadius(8)
          .backgroundColor(item.color)
        }, (item: GalleryCard) => item.id.toString())
      }
      .id(ScrollFrameNodeScenes.GALLERY_ID)
      .columnsTemplate('1fr 1fr')
      .columnsGap(10)
      .rowsGap(10)
      .height(340)
      .width('100%')
      .borderWidth(1)
      .borderColor('#D0D7DE');
    }
    .width('100%')
    .padding(16)
    .borderRadius(8)
    .backgroundColor('#FFFFFF');
  }

  @Builder
  buildLogSection() {
    Column({ space: 8 }) {
      Text('Runtime log')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Text('Each operation records whether the host FrameNode exists, whether the dynamic controller already points to a node, and whether the UID returned from scroller.getFrameNode() matches the UID fetched by component id.')
        .fontSize(13)

      Column({ space: 6 }) {
        ForEach(this.logs, (item: string, index: number) => {
          Text(item)
            .width('100%')
            .padding(10)
            .borderRadius(8)
            .backgroundColor(index % 2 === 0 ? '#F7F9FB' : '#EEF3F8')
            .fontSize(12);
        }, (item: string, index: number) => `${index}_${item}`);
      }
      .width('100%')
    }
    .width('100%')
    .padding(16)
    .borderRadius(8)
    .backgroundColor('#FFFFFF');
  }

  build() {
    Scroll(this.pageScroller) {
      Column({ space: 16 }) {
        this.buildHeaderSection();
        this.buildArticleSection();
        this.buildTaskSection();
        this.buildDashboardSection();
        this.buildGallerySection();
        this.buildLogSection();
      }
      .width('100%')
      .padding(16);
    }
    .width('100%')
    .height('100%')
    .scrollBar(BarState.On)
    .backgroundColor('#F2F4F7');
  }
}
