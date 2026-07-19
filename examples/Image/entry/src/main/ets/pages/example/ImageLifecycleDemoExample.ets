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

import { BusinessError } from '@kit.BasicServicesKit';

/**
 * ========================================
 * 业务场景：Image 生命周期与事件演示
 * ========================================
 * 功能说明:
 * 本示例聚焦 Image 组件的加载生命周期、事件回调与加载控制类属性，
 * 直观展示从「开始加载」到「加载完成/失败」的全过程，并提供可调开关。
 *
 * 涉及的 Image API:
 * 1. onComplete - 加载成功回调，返回宽高与组件偏移
 * 2. onError - 加载失败回调
 * 3. alt(ImageAlt) - 加载中和加载失败时的占位图（placeholder / error）
 * 4. Image(src, reloadKey) - 重新加载标识，值变化时不使用缓存重载
 * 5. syncLoad - 同步/异步加载切换
 * 6. sourceSize - 解码尺寸控制
 * 7. draggable - 是否可拖拽
 * 8. copyOptions - 复制行为控制
 * 9. objectFit - 填充模式
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 内容加载反馈：占位图、错误兜底、加载耗时统计
 * - 图片刷新：服务端图片更新后强制重新拉取
 * - 内存优化：配合 sourceSize 降低解码开销
 * - 内容分享：draggable / copyOptions 控制图片可否被复制拖拽
 */

interface LoadRecord {
  index: number;
  time: string;
  result: string;
  detail: string;
}

interface CopyOptionItem {
  key: CopyOptions;
  name: string;
}

interface FitOptionItem {
  key: ImageFit;
  name: string;
}

@Entry
@Component
struct ImageLifecycleDemoExample {
  @State reloadKey: string = '';
  @State reloadCount: number = 0;
  @State syncLoadOn: boolean = false;
  @State sourceSizeOn: boolean = false;
  @State draggableOn: boolean = true;
  @State copyMode: CopyOptions = CopyOptions.InApp;
  @State fitMode: ImageFit = ImageFit.Cover;
  @State useBadSource: boolean = false;
  @State currentSource: Resource | string = $r('app.media.svg');
  @State altOn: boolean = true;
  @State loadedWidth: number = 0;
  @State loadedHeight: number = 0;
  @State loadStatus: string = '待加载';
  @State loadDuration: number = 0;
  @State loadStartTime: number = 0;
  @State records: Array<LoadRecord> = [];
  @State recordSeq: number = 0;

  private copyModes: CopyOptionItem[] = [
    { key: CopyOptions.None, name: 'None 不可复制' },
    { key: CopyOptions.InApp, name: 'InApp 应用内' },
    { key: CopyOptions.LocalDevice, name: 'LocalDevice 本设备' },
    { key: CopyOptions.CrossDevice, name: 'CrossDevice 跨设备' }
  ];

  private fitModes: FitOptionItem[] = [
    { key: ImageFit.Cover, name: 'Cover' },
    { key: ImageFit.Contain, name: 'Contain' },
    { key: ImageFit.Fill, name: 'Fill' },
    { key: ImageFit.ScaleDown, name: 'ScaleDown' },
    { key: ImageFit.None, name: 'None' }
  ];

  /**
   * 触发重新加载（变更 reloadKey 强制重载）
   */
  private triggerReload(): void {
    this.reloadCount++;
    this.reloadKey = `reload-${Date.now()}`;
    this.loadStartTime = Date.now();
    this.loadStatus = '加载中...';
    this.appendRecord('reload', `reloadKey=${this.reloadKey}`);
  }

  /**
   * 切换正常图 / 错误图源
   */
  private toggleSource(): void {
    this.useBadSource = !this.useBadSource;
    if (this.useBadSource) {
      this.currentSource = 'app.media.this_resource_does_not_exist';
    } else {
      this.currentSource = $r('app.media.svg');
    }
    this.loadStartTime = Date.now();
    this.loadStatus = '加载中...';
    this.appendRecord('switch', `源切换为 ${this.useBadSource ? '错误源' : '正常源'}`);
  }

  /**
   * 切换图片资源
   */
  private switchResource(res: Resource): void {
    this.useBadSource = false;
    this.currentSource = res;
    this.loadStartTime = Date.now();
    this.loadStatus = '加载中...';
    this.appendRecord('switch', `资源切换`);
  }

  private handleComplete(width: number, height: number): void {
    this.loadedWidth = width;
    this.loadedHeight = height;
    this.loadDuration = Date.now() - this.loadStartTime;
    this.loadStatus = '加载成功';
    this.appendRecord('success', `${width}x${height}，耗时 ${this.loadDuration}ms`);
  }

  private handleError(error: BusinessError): void {
    this.loadDuration = Date.now() - this.loadStartTime;
    this.loadStatus = '加载失败';
    this.appendRecord('error', `code=${error.code}，${error.message}`);
  }

  private appendRecord(result: string, detail: string): void {
    this.recordSeq++;
    const now = new Date();
    const time = `${now.getHours().toString().padStart(2, '0')}:${now.getMinutes().toString().padStart(2, '0')}:${now.getSeconds().toString().padStart(2, '0')}`;
    const record: LoadRecord = {
      index: this.recordSeq,
      time: time,
      result: result,
      detail: detail
    };
    this.records = [record, ...this.records].slice(0, 12);
  }

  private clearRecords(): void {
    this.records = [];
    this.recordSeq = 0;
  }

  build(): void {
    Column({ space: 0 }) {
      this.TitleBar()
      Scroll() {
        Column({ space: 14 }) {
          this.PreviewCard()
          this.StatusCard()
          this.ActionCard()
          this.SourceCard()
          this.LoadOptionCard()
          this.InteractionCard()
          this.FitCard()
          this.RecordCard()
        }
        .width('100%')
        .padding(12)
      }
      .layoutWeight(1)
      .scrollBar(BarState.Auto)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F2F3F5')
  }

  @Builder
  TitleBar(): void {
    Row({ space: 8 }) {
      Text('Image 生命周期与事件演示')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Black)
        .layoutWeight(1)
      Text(this.loadStatus)
        .fontSize(12)
        .fontColor(Color.White)
        .backgroundColor(this.statusColor())
        .borderRadius(10)
        .padding({ left: 10, right: 10, top: 4, bottom: 4 })
    }
    .width('100%')
    .height(52)
    .padding({ left: 16, right: 16 })
    .backgroundColor('#FFFFFF')
  }

  private statusColor(): string {
    if (this.loadStatus.startsWith('加载成功')) {
      return '#4CAF50';
    }
    if (this.loadStatus.startsWith('加载失败')) {
      return '#F44336';
    }
    return '#FF9800';
  }

  @Builder
  PreviewCard(): void {
    Column({ space: 10 }) {
      Text('图片预览区')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Stack({ alignContent: Alignment.Center }) {
        Image(this.currentSource, this.reloadKey)
          .width('100%')
          .height(220)
          .objectFit(this.fitMode)
          .alt(this.altOn ? {
            placeholder: $r('app.media.icon'),
            error: $r('app.media.heart')
          } : { placeholder: $r('app.media.icon') })
          .syncLoad(this.syncLoadOn)
          .sourceSize(this.sourceSizeOn ? { width: 120, height: 120 } : { width: 0, height: 0 })
          .draggable(this.draggableOn)
          .copyOptions(this.copyMode)
          .backgroundColor('#FAFAFA')
          .borderRadius(12)
          .border({ width: 1, color: '#E0E0E0' })
          .onComplete((event) => {
            if (event) {
              this.handleComplete(event.width, event.height);
            }
          })
          .onError((error) => {
            this.handleError(error as BusinessError);
          })

        if (this.loadStatus === '加载中...') {
          Column({ space: 8 }) {
            LoadingProgress().width(36).height(36).color('#007DFF')
            Text('加载中...')
              .fontSize(12)
              .fontColor(Color.White)
          }
          .width('100%')
          .height(220)
          .justifyContent(FlexAlign.Center)
          .backgroundColor('#66000000')
          .borderRadius(12)
        }
      }
      .width('100%')
      .height(220)
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  StatusCard(): void {
    Column({ space: 8 }) {
      this.StatusRow('加载状态', this.loadStatus)
      this.StatusRow('图片尺寸', this.loadedWidth > 0 ? `${this.loadedWidth} × ${this.loadedHeight}` : '—')
      this.StatusRow('加载耗时', this.loadDuration > 0 ? `${this.loadDuration} ms` : '—')
      this.StatusRow('reloadKey', this.reloadKey || '（空）')
      this.StatusRow('重载次数', `${this.reloadCount}`)
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFF8DC')
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  StatusRow(label: string, value: string): void {
    Row({ space: 8 }) {
      Text(label)
        .fontSize(11)
        .fontColor(Color.Gray)
        .width(80)
      Text(value)
        .fontSize(11)
        .fontColor(Color.Black)
        .layoutWeight(1)
        .maxLines(2)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
    }
    .width('100%')
  }

  @Builder
  ActionCard(): void {
    Row({ space: 10 }) {
      Button('reloadKey 重载')
        .fontSize(12)
        .layoutWeight(1)
        .height(40)
        .backgroundColor('#007DFF')
        .fontColor(Color.White)
        .onClick(() => {
          this.triggerReload();
        })

      Button(this.useBadSource ? '恢复正常源' : '模拟错误源')
        .fontSize(12)
        .layoutWeight(1)
        .height(40)
        .backgroundColor(this.useBadSource ? '#4CAF50' : '#FF9800')
        .fontColor(Color.White)
        .onClick(() => {
          this.toggleSource();
        })
    }
    .width('100%')
  }

  @Builder
  SourceCard(): void {
    Column({ space: 10 }) {
      Text('图片资源切换')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 10 }) {
        ForEach(
          [$r('app.media.svg'), $r('app.media.icon'), $r('app.media.heart'), $r('app.media.star')],
          (res: Resource) => {
            Image(res)
              .width(52)
              .height(52)
              .objectFit(ImageFit.Cover)
              .borderRadius(8)
              .border({
                width: this.currentSource === res ? 2 : 1,
                color: this.currentSource === res ? '#007DFF' : '#E0E0E0'
              })
              .onClick(() => {
                this.switchResource(res);
              })
          },
          (res: Resource) => `${res}`
        )
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#F3E5F5')
    .borderRadius(12)
  }

  @Builder
  LoadOptionCard(): void {
    Column({ space: 10 }) {
      Text('加载控制属性')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.altOn })
          .onChange((on: boolean) => {
            this.altOn = on;
          })
        Text('alt 占位图（含 error 兜底）')
          .fontSize(12)
          .fontColor(Color.Black)
          .layoutWeight(1)
      }
      .width('100%')

      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.syncLoadOn })
          .onChange((on: boolean) => {
            this.syncLoadOn = on;
          })
        Text('syncLoad 同步加载')
          .fontSize(12)
          .fontColor(Color.Black)
          .layoutWeight(1)
      }
      .width('100%')

      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.sourceSizeOn })
          .onChange((on: boolean) => {
            this.sourceSizeOn = on;
          })
        Text('sourceSize 解码尺寸 120×120')
          .fontSize(12)
          .fontColor(Color.Black)
          .layoutWeight(1)
      }
      .width('100%')

      Text('说明：syncLoad=true 会阻塞 UI 线程等待解码完成；sourceSize 限制解码后的像素尺寸，可降低内存。')
        .fontSize(10)
        .fontColor(Color.Gray)
        .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#E8F5E9')
    .borderRadius(12)
  }

  @Builder
  InteractionCard(): void {
    Column({ space: 10 }) {
      Text('交互属性')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.draggableOn })
          .onChange((on: boolean) => {
            this.draggableOn = on;
          })
        Text('draggable 可拖拽')
          .fontSize(12)
          .fontColor(Color.Black)
          .layoutWeight(1)
      }
      .width('100%')

      Text('copyOptions 复制行为：')
        .fontSize(12)
        .fontColor(Color.Black)
        .width('100%')

      Flex({ wrap: FlexWrap.Wrap }) {
        ForEach(
          this.copyModes,
          (item: CopyOptionItem) => {
            Button(item.name)
              .fontSize(10)
              .height(28)
              .margin({ right: 6, bottom: 6 })
              .backgroundColor(this.copyMode === item.key ? '#007DFF' : '#EDEDED')
              .fontColor(this.copyMode === item.key ? Color.White : Color.Black)
              .onClick(() => {
                this.copyMode = item.key;
              })
          },
          (item: CopyOptionItem) => `${item.key}`
        )
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#E3F2FD')
    .borderRadius(12)
  }

  @Builder
  FitCard(): void {
    Column({ space: 10 }) {
      Text('objectFit 填充模式')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 6 }) {
        ForEach(
          this.fitModes,
          (item: FitOptionItem) => {
            Button(item.name)
              .fontSize(10)
              .height(28)
              .layoutWeight(1)
              .backgroundColor(this.fitMode === item.key ? '#007DFF' : '#EDEDED')
              .fontColor(this.fitMode === item.key ? Color.White : Color.Black)
              .onClick(() => {
                this.fitMode = item.key;
              })
          },
          (item: FitOptionItem) => `${item.key}`
        )
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFF3E0')
    .borderRadius(12)
  }

  @Builder
  RecordCard(): void {
    Column({ space: 8 }) {
      Row({ space: 8 }) {
        Text('加载事件记录')
          .fontSize(13)
          .fontWeight(FontWeight.Medium)
          .fontColor(Color.Black)
          .layoutWeight(1)
        Button('清空')
          .fontSize(11)
          .height(26)
          .backgroundColor('#EDEDED')
          .fontColor(Color.Black)
          .onClick(() => {
            this.clearRecords();
          })
      }
      .width('100%')

      if (this.records.length === 0) {
        Text('暂无记录')
          .fontSize(11)
          .fontColor(Color.Gray)
          .width('100%')
      } else {
        ForEach(
          this.records,
          (record: LoadRecord) => {
            Row({ space: 8 }) {
              Text(`#${record.index}`)
                .fontSize(10)
                .fontColor(this.recordColor(record.result))
                .width(32)
              Text(record.time)
                .fontSize(10)
                .fontColor(Color.Gray)
                .width(60)
              Text(record.result)
                .fontSize(10)
                .fontColor(this.recordColor(record.result))
                .width(48)
              Text(record.detail)
                .fontSize(10)
                .fontColor(Color.Black)
                .layoutWeight(1)
                .maxLines(2)
                .textOverflow({ overflow: TextOverflow.Ellipsis })
            }
            .width('100%')
            .padding({ top: 2, bottom: 2 })
          },
          (record: LoadRecord) => `${record.index}`
        )
      }
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FAFAFA')
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  private recordColor(result: string): string {
    switch (result) {
      case 'success':
        return '#4CAF50';
      case 'error':
        return '#F44336';
      case 'reload':
        return '#007DFF';
      default:
        return '#FF9800';
    }
  }
}
