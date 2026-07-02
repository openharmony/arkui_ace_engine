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
 * ImageExample094 - 图片加载全生命周期综合示例
 *
 * 功能说明：
 * 1. 演示 Image 组件完整加载生命周期的回调能力
 *    - onComplete：图片数据加载成功与解码成功时回调
 *    - onError：图片加载异常时回调，可获取错误码与错误信息
 *    - onFinish：SVG 动效播放完成时回调
 * 2. 演示 alt 占位图与错误占位图（ImageAlt）的应用
 * 3. 演示在加载、成功、失败、重试等状态间的切换体验
 * 4. 演示通过 enableAnalyzer、copyOption 等扩展属性增强图片组件能力
 *
 * 适用场景：
 * - 图片加载状态可视化监控
 * - 网络图片异常排查与重试
 * - 业务中需要根据图片加载结果进行分支处理的场景
 */

class ImageLoadRecord {
  timestamp: string = '';
  level: string = 'INFO';
  message: string = '';

  constructor(level: string, message: string) {
    const date = new Date();
    this.timestamp =
      `${date.getHours().toString().padStart(2, '0')}:` +
      `${date.getMinutes().toString().padStart(2, '0')}:` +
      `${date.getSeconds().toString().padStart(2, '0')}.` +
      `${date.getMilliseconds().toString().padStart(3, '0')}`;
    this.level = level;
    this.message = message;
  }
}

@Entry
@Component
struct ImageExample094 {
  @State currentSource: Resource | string = $r('app.media.startIcon');
  @State sourceLabel: string = 'app.media.startIcon';
  @State altSource: Resource = $r('app.media.foreground');
  @State useErrorAlt: boolean = false;
  @State loadStatus: string = 'IDLE';
  @State statusColor: number = 0x888888;
  @State lastLoadedSize: string = '--';
  @State lastComponentSize: string = '--';
  @State lastContentDraw: string = '--';
  @State lastErrorMessage: string = '--';
  @State lastErrorCode: number = 0;
  @State retryToken: number = 0;
  @State syncLoad: boolean = false;
  @State autoResize: boolean = false;
  @State interpolationMode: ImageInterpolation = ImageInterpolation.Low;
  @State enableCopy: boolean = true;
  @State logs: ImageLoadRecord[] = [];
  @State svgFinishCount: number = 0;
  @State enableAI: boolean = false;

  private maxLogSize: number = 20;
  private nextLogId: number = 0;

  private sources: Array<{ label: string, value: Resource | string }> = [
    { label: 'startIcon', value: $r('app.media.startIcon') },
    { label: 'foreground', value: $r('app.media.foreground') },
    { label: 'background', value: $r('app.media.background') },
    { label: 'heart.svg', value: $r('app.media.heart') },
    { label: 'star.svg', value: $r('app.media.star') },
    { label: 'svg.svg', value: $r('app.media.svg') },
    { label: 'invalid (触发错误)', value: 'app.media.__not_exist__' }
  ];

  aboutToAppear() {
    this.appendLog('INFO', '页面已就绪，等待图片加载。');
  }

  appendLog(level: string, message: string) {
    const record = new ImageLoadRecord(level, message);
    record.timestamp = `${record.timestamp} #${++this.nextLogId}`;
    this.logs.unshift(record);
    if (this.logs.length > this.maxLogSize) {
      this.logs.splice(this.maxLogSize);
    }
  }

  clearLogs() {
    this.logs = [];
    this.nextLogId = 0;
  }

  pickSource(item: { label: string, value: Resource | string }) {
    this.currentSource = item.value;
    this.sourceLabel = item.label;
    this.loadStatus = 'TRIGGERED';
    this.statusColor = 0xFFAA00;
    this.lastErrorMessage = '--';
    this.lastErrorCode = 0;
    this.appendLog('INFO', `切换图片源 -> ${item.label}`);
  }

  triggerReload() {
    this.retryToken += 1;
    this.loadStatus = 'TRIGGERED';
    this.statusColor = 0xFFAA00;
    this.appendLog('INFO', `手动触发重新加载（reloadKey=${this.retryToken}）`);
  }

  resetToIdle() {
    this.loadStatus = 'IDLE';
    this.statusColor = 0x888888;
    this.lastLoadedSize = '--';
    this.lastComponentSize = '--';
    this.lastContentDraw = '--';
    this.lastErrorMessage = '--';
    this.lastErrorCode = 0;
    this.appendLog('INFO', '状态已重置为 IDLE。');
  }

  build() {
    Scroll() {
      Column({ space: 16 }) {
        Text('图片加载全生命周期综合示例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 4 })
          .fontColor(0x222222)

        Text('演示 onComplete / onError / onFinish / alt 占位 / 同步加载 等能力')
          .fontSize(12)
          .fontColor(0x888888)
          .margin({ bottom: 8 })

        this.buildPreviewSection()
        this.buildStatusSection()
        this.buildSourcePicker()
        this.buildOptionSwitches()
        this.buildInterpolationPicker()
        this.buildActionButtons()
        this.buildMetricsSection()
        this.buildBestPracticeCard()
        this.buildLogSection()
      }
      .width('100%')
      .padding({ left: 16, right: 16, bottom: 24 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  @Builder
  buildPreviewSection() {
    Column({ space: 12 }) {
      Text('加载预览')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      Stack({ alignContent: Alignment.Center }) {
        if (this.useErrorAlt) {
          Image(this.currentSource, undefined, `reload-${this.retryToken}`)
            .width(260)
            .height(220)
            .objectFit(ImageFit.Cover)
            .borderRadius(12)
            .alt({
              placeholder: this.altSource,
              error: $r('app.media.background')
            })
            .interpolation(this.interpolationMode)
            .autoResize(this.autoResize)
            .syncLoad(this.syncLoad)
            .copyOption(this.enableCopy ? CopyOptions.LocalDevice : CopyOptions.None)
            .enableAnalyzer(this.enableAI)
            .onComplete((event) => {
              if (!event) {
                return;
              }
              this.loadStatus = event.loadingStatus === 0 ? 'LOADED' : 'DECODED';
              this.statusColor = event.loadingStatus === 0 ? 0x33AA55 : 0x3388FF;
              this.lastLoadedSize = `${event.width} x ${event.height} px`;
              this.lastComponentSize = `${event.componentWidth} x ${event.componentHeight} px`;
              this.lastContentDraw =
                `${event.contentWidth.toFixed(0)} x ${event.contentHeight.toFixed(0)} px ` +
                `(offset ${event.contentOffsetX.toFixed(0)}, ${event.contentOffsetY.toFixed(0)})`;
              this.appendLog(
                'SUCCESS',
                `onComplete status=${event.loadingStatus} ` +
                  `size=${event.width}x${event.height}`
              );
            })
            .onError((error) => {
              this.loadStatus = 'ERROR';
              this.statusColor = 0xDD4444;
              this.lastErrorMessage = error.message ?? 'unknown error';
              this.lastErrorCode = error?.error?.code ?? -1;
              this.appendLog(
                'ERROR',
                `onError code=${this.lastErrorCode} msg=${this.lastErrorMessage}`
              );
            })
            .onFinish(() => {
              this.svgFinishCount += 1;
              this.appendLog('INFO', `SVG 动效播放完成（已累计 ${this.svgFinishCount} 次）。`);
            })
        } else {
          Image(this.currentSource, undefined, `reload-${this.retryToken}`)
            .width(260)
            .height(220)
            .objectFit(ImageFit.Cover)
            .borderRadius(12)
            .alt(this.altSource)
            .interpolation(this.interpolationMode)
            .autoResize(this.autoResize)
            .syncLoad(this.syncLoad)
            .copyOption(this.enableCopy ? CopyOptions.LocalDevice : CopyOptions.None)
            .enableAnalyzer(this.enableAI)
            .onComplete((event) => {
              if (!event) {
                return;
              }
              this.loadStatus = event.loadingStatus === 0 ? 'LOADED' : 'DECODED';
              this.statusColor = event.loadingStatus === 0 ? 0x33AA55 : 0x3388FF;
              this.lastLoadedSize = `${event.width} x ${event.height} px`;
              this.lastComponentSize = `${event.componentWidth} x ${event.componentHeight} px`;
              this.lastContentDraw =
                `${event.contentWidth.toFixed(0)} x ${event.contentHeight.toFixed(0)} px ` +
                `(offset ${event.contentOffsetX.toFixed(0)}, ${event.contentOffsetY.toFixed(0)})`;
              this.appendLog(
                'SUCCESS',
                `onComplete status=${event.loadingStatus} ` +
                  `size=${event.width}x${event.height}`
              );
            })
            .onError((error) => {
              this.loadStatus = 'ERROR';
              this.statusColor = 0xDD4444;
              this.lastErrorMessage = error.message ?? 'unknown error';
              this.lastErrorCode = error?.error?.code ?? -1;
              this.appendLog(
                'ERROR',
                `onError code=${this.lastErrorCode} msg=${this.lastErrorMessage}`
              );
            })
            .onFinish(() => {
              this.svgFinishCount += 1;
              this.appendLog('INFO', `SVG 动效播放完成（已累计 ${this.svgFinishCount} 次）。`);
            })
        }

        Text(this.loadStatus)
          .fontSize(12)
          .fontColor(Color.White)
          .padding({ left: 10, right: 10, top: 4, bottom: 4 })
          .backgroundColor(`#A0${this.statusColor.toString(16).padStart(6, '0').slice(-6)}`)
          .borderRadius(10)
          .position({ x: 12, y: 12 })
      }
      .width('100%')
      .height(240)
      .backgroundColor(0xEAEAEA)
      .borderRadius(12)
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildStatusSection() {
    Row({ space: 12 }) {
      Column({ space: 4 }) {
        Text('当前状态')
          .fontSize(12)
          .fontColor(0x888888)
        Text(this.loadStatus)
          .fontSize(18)
          .fontWeight(FontWeight.Bold)
          .fontColor(this.statusColor)
      }
      .layoutWeight(1)
      .alignItems(HorizontalAlign.Start)

      Divider()
        .vertical(true)
        .height(36)
        .strokeWidth(1)
        .color(0xDDDDDD)

      Column({ space: 4 }) {
        Text('SVG 完成次数')
          .fontSize(12)
          .fontColor(0x888888)
        Text(`${this.svgFinishCount}`)
          .fontSize(18)
          .fontWeight(FontWeight.Bold)
          .fontColor(0x666666)
      }
      .layoutWeight(1)
      .alignItems(HorizontalAlign.Start)
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildSourcePicker() {
    Column({ space: 10 }) {
      Text('切换图片源')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      Text(`当前：${this.sourceLabel}`)
        .fontSize(13)
        .fontColor(0x666666)
        .alignSelf(ItemAlign.Start)

      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start }) {
        ForEach(this.sources, (item: { label: string, value: Resource | string }, index: number) => {
          Button(item.label)
            .fontSize(12)
            .margin(4)
            .backgroundColor(
              this.sourceLabel === item.label ? 0x3388FF : 0xEFEFEF
            )
            .fontColor(
              this.sourceLabel === item.label ? Color.White : 0x444444
            )
            .onClick(() => {
              this.pickSource(item);
              void index;
            })
        })
      }
      .width('100%')
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildOptionSwitches() {
    Column({ space: 12 }) {
      Text('加载行为开关')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      Toggle({ type: ToggleType.Switch, isOn: this.syncLoad })
        .selectedColor(0x3388FF)
        .onChange((on: boolean) => {
          this.syncLoad = on;
          this.appendLog('INFO', `syncLoad 切换为 ${on}`);
        })
      Row() {
        Text('syncLoad 同步加载')
          .fontSize(13)
          .fontColor(0x333333)
          .layoutWeight(1)
      }

      Toggle({ type: ToggleType.Switch, isOn: this.autoResize })
        .selectedColor(0x3388FF)
        .onChange((on: boolean) => {
          this.autoResize = on;
          this.appendLog('INFO', `autoResize 切换为 ${on}`);
        })
      Row() {
        Text('autoResize 解码自动缩放')
          .fontSize(13)
          .fontColor(0x333333)
          .layoutWeight(1)
      }

      Toggle({ type: ToggleType.Switch, isOn: this.enableCopy })
        .selectedColor(0x3388FF)
        .onChange((on: boolean) => {
          this.enableCopy = on;
          this.appendLog('INFO', `copyOption 切换为 ${on ? 'LocalDevice' : 'None'}`);
        })
      Row() {
        Text('copyOption 允许复制（长按/Ctrl+C）')
          .fontSize(13)
          .fontColor(0x333333)
          .layoutWeight(1)
      }

      Toggle({ type: ToggleType.Switch, isOn: this.enableAI })
        .selectedColor(0x3388FF)
        .onChange((on: boolean) => {
          this.enableAI = on;
          this.appendLog('INFO', `enableAnalyzer 切换为 ${on}`);
        })
      Row() {
        Text('enableAnalyzer AI 分析能力')
          .fontSize(13)
          .fontColor(0x333333)
          .layoutWeight(1)
      }

      Toggle({ type: ToggleType.Switch, isOn: this.useErrorAlt })
        .selectedColor(0x3388FF)
        .onChange((on: boolean) => {
          this.useErrorAlt = on;
          this.appendLog('INFO', `使用 ImageAlt (含 error 占位) 切换为 ${on}`);
        })
      Row() {
        Text('使用 ImageAlt 22+ （加载/错误 双占位图）')
          .fontSize(13)
          .fontColor(0x333333)
          .layoutWeight(1)
      }
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildInterpolationPicker() {
    Column({ space: 10 }) {
      Text('interpolation 插值模式')
        .fontSize(16)
      Row({ space: 8 }) {
        this.buildInterpolationButton('None', ImageInterpolation.None)
        this.buildInterpolationButton('Low', ImageInterpolation.Low)
        this.buildInterpolationButton('Medium', ImageInterpolation.Medium)
        this.buildInterpolationButton('High', ImageInterpolation.High)
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildInterpolationButton(label: string, mode: ImageInterpolation) {
    Button(label)
      .fontSize(12)
      .backgroundColor(this.interpolationMode === mode ? 0x3388FF : 0xEFEFEF)
      .fontColor(this.interpolationMode === mode ? Color.White : 0x444444)
      .onClick(() => {
        this.interpolationMode = mode;
        this.appendLog('INFO', `interpolation 切换为 ${label}`);
      })
  }

  @Builder
  buildActionButtons() {
    Row({ space: 10 }) {
      Button('重新加载')
        .layoutWeight(1)
        .fontSize(13)
        .backgroundColor(0x33AA55)
        .onClick(() => this.triggerReload())

      Button('重置状态')
        .layoutWeight(1)
        .fontSize(13)
        .backgroundColor(0x999999)
        .onClick(() => this.resetToIdle())

      Button('清空日志')
        .layoutWeight(1)
        .fontSize(13)
        .backgroundColor(0xFF7070)
        .onClick(() => this.clearLogs())
    }
    .width('100%')
  }

  @Builder
  buildMetricsSection() {
    Column({ space: 10 }) {
      Text('加载详情')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      this.buildMetricRow('图片原始尺寸', this.lastLoadedSize)
      this.buildMetricRow('组件尺寸', this.lastComponentSize)
      this.buildMetricRow('实际绘制区域', this.lastContentDraw)
      this.buildMetricRow('错误信息', this.lastErrorMessage)
      this.buildMetricRow('错误码', this.lastErrorCode === 0 ? '--' : `${this.lastErrorCode}`)
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
  }

  @Builder
  buildMetricRow(label: string, value: string) {
    Row({ space: 12 }) {
      Text(label)
        .fontSize(13)
        .fontColor(0x666666)
        .width(110)
      Text(value)
        .fontSize(13)
        .fontColor(0x222222)
        .layoutWeight(1)
        .maxLines(2)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
    }
    .width('100%')
  }

  @Builder
  buildLogSection() {
    Column({ space: 8 }) {
      Row() {
        Text('事件日志')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)
          .layoutWeight(1)
        Text(`共 ${this.logs.length} 条`)
          .fontSize(12)
          .fontColor(0x888888)
      }
      .width('100%')

      if (this.logs.length === 0) {
        Text('暂无事件，点击"重新加载"或切换图片源以触发回调。')
          .fontSize(13)
          .fontColor(0x888888)
          .padding(10)
      } else {
        Column({ space: 6 }) {
          ForEach(this.logs, (record: ImageLoadRecord) => {
            Row({ space: 8 }) {
              Text(record.timestamp)
                .fontSize(11)
                .fontColor(0x888888)
                .width(120)
              Text(record.level)
                .fontSize(11)
                .fontColor(this.levelToColor(record.level))
                .width(60)
              Text(record.message)
                .fontSize(12)
                .fontColor(0x333333)
                .layoutWeight(1)
                .maxLines(2)
                .textOverflow({ overflow: TextOverflow.Ellipsis })
            }
            .width('100%')
            .padding({ left: 8, right: 8, top: 6, bottom: 6 })
            .backgroundColor(0xFAFAFA)
            .borderRadius(6)
          })
        }
        .width('100%')
      }

      this.buildErrorCodeReference()
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  buildErrorCodeReference() {
    Column({ space: 8 }) {
      Divider().color(0xEEEEEE)

      Text('常见错误码参考')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      this.buildErrorCodeRow('101000', '未知图片来源类型')
      this.buildErrorCodeRow('102010/102011', '同步 HTTP 任务取消/失败')
      this.buildErrorCodeRow('102012/102013', '异步 HTTP 任务取消/失败')
      this.buildErrorCodeRow('102030/102031', 'Base64 格式错误或解码失败')
      this.buildErrorCodeRow('102050/102051', '沙箱路径过长或读取失败')
      this.buildErrorCodeRow('102070/102071', '资源名/ID 获取失败')
      this.buildErrorCodeRow('102090/102091', '包内 URI 无效或资源获取失败')
      this.buildErrorCodeRow('102110~112', '媒体库文件打开/读取失败')
      this.buildErrorCodeRow('103100', 'SVG DOM 创建失败')
      this.buildErrorCodeRow('103200', '图片数据尺寸无效')
      this.buildErrorCodeRow('111000/111001', '位图 source / pixelmap 创建失败')

      Text('提示：上述错误码可在 onError 回调中通过 error.error.code 获取')
        .fontSize(11)
        .fontColor(0x999999)
        .margin({ top: 4 })
    }
    .width('100%')
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  buildErrorCodeRow(code: string, description: string) {
    Row({ space: 10 }) {
      Text(code)
        .fontSize(11)
        .fontColor(0xDD4444)
        .width(120)
      Text(description)
        .fontSize(11)
        .fontColor(0x555555)
        .layoutWeight(1)
    }
    .width('100%')
  }

  @Builder
  buildBestPracticeCard() {
    Column({ space: 12 }) {
      Text('加载生命周期最佳实践')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
        .alignSelf(ItemAlign.Start)

      Column({ space: 8 }) {
        Text('1. 区分 loadingStatus')
          .fontSize(13)
          .fontColor(0x222222)
        Text('onComplete 会触发两次：0=数据加载完成，1=解码完成。'
          + '业务中如需基于解码后尺寸做布局，应只在 status=1 时处理。')
          .fontSize(11)
          .fontColor(0x666666)
      }
      .alignItems(HorizontalAlign.Start)
      .width('100%')

      Column({ space: 8 }) {
        Text('2. 错误码定位问题')
          .fontSize(13)
          .fontColor(0x222222)
        Text('在 onError 中通过 error.error.code 区分数据加载/解码不同阶段。'
          + '网络图片加载失败可结合 downloadInfo 字段进一步定位。')
          .fontSize(11)
          .fontColor(0x666666)
      }
      .alignItems(HorizontalAlign.Start)
      .width('100%')

      Column({ space: 8 }) {
        Text('3. 占位图与错误占位图')
          .fontSize(13)
          .fontColor(0x222222)
        Text('API 22+ 可通过 ImageAlt 同时配置 placeholder 与 error 占位图，'
          + '避免出现加载失败的白屏。')
          .fontSize(11)
          .fontColor(0x666666)
      }
      .alignItems(HorizontalAlign.Start)
      .width('100%')

      Column({ space: 8 }) {
        Text('4. 同步加载的取舍')
          .fontSize(13)
          .fontColor(0x222222)
        Text('syncLoad=true 会阻塞 UI 线程，仅推荐用于小尺寸本地图（如图标）；'
          + '大图或网络图必须异步加载，否则可能引发 AppFreeze。')
          .fontSize(11)
          .fontColor(0x666666)
      }
      .alignItems(HorizontalAlign.Start)
      .width('100%')

      Column({ space: 8 }) {
        Text('5. AnimatedDrawableDescriptor 注意事项')
          .fontSize(13)
          .fontColor(0x222222)
        Text('当 src 为 AnimatedDrawableDescriptor 时，onComplete / onError / onFinish '
          + '均不会触发，需通过其他机制管理动画生命周期。')
          .fontSize(11)
          .fontColor(0x666666)
      }
      .alignItems(HorizontalAlign.Start)
      .width('100%')

      Column({ space: 8 }) {
        Text('6. reloadKey 强制刷新')
          .fontSize(13)
          .fontColor(0x222222)
        Text('图片源不变但内容已更新（如本地图片被重写）时，可通过变更 reloadKey '
          + '使组件不使用缓存重新加载。')
          .fontSize(11)
          .fontColor(0x666666)
      }
      .alignItems(HorizontalAlign.Start)
      .width('100%')
    }
    .width('100%')
    .padding(16)
    .backgroundColor(0xFFFFFF)
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }

  levelToColor(level: string): number {
    switch (level) {
      case 'SUCCESS':
        return 0x33AA55;
      case 'ERROR':
        return 0xDD4444;
      case 'WARN':
        return 0xFFAA00;
      default:
        return 0x666666;
    }
  }
}
