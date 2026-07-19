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
 * See the License for the specific language governing Permissions and
 * limitations under the License.
 */

/**
 * PixelMapDrawableDescriptor 用法示例
 * 演示通过 PixelMap 或 ResourceStr 创建 PixelMapDrawableDescriptor，
 * 以及 getPixelMap()、loadSync()、load()、release()、isReleased()、invalidate() 等方法
 */
import { DrawableDescriptor, PixelMapDrawableDescriptor } from '@kit.ArkUI';
import { image } from '@kit.ImageKit';
import { BusinessError } from '@kit.BasicServicesKit';
import { router } from '@kit.ArkUI';

@Entry
@Component
struct PixelMapDrawableDescriptorExample {
  @State pixelMap: image.PixelMap | undefined = undefined;
  @State pixelMapAlt: image.PixelMap | undefined = undefined;
  @State pixelMapDesc: PixelMapDrawableDescriptor | undefined = undefined;
  @State resourceDesc: PixelMapDrawableDescriptor | undefined = undefined;
  @State descFromPixelMap: DrawableDescriptor | undefined = undefined;
  @State descFromResource: DrawableDescriptor | undefined = undefined;
  @State loadSyncResult: string = '';
  @State loadAsyncResult: string = '';
  @State getPixelMapResult: string = '';
  @State pixelMapInfo: string = '';
  @State releaseStatus: string = '';
  @State isReleasedPm: boolean = false;
  @State isReleasedRs: boolean = false;
  @State invalidateStatus: string = '';
  @State imageWidth: number = 200;
  @State imageHeight: number = 200;
  @State objectFitMode: ImageFit = ImageFit.Cover;
  @State currentSrcIndex: number = 0;
  @State showCreateSection: boolean = true;
  @State showLoadSection: boolean = true;
  @State showPixelMapSection: boolean = true;
  @State showReleaseSection: boolean = true;
  @State logMessages: string[] = [];

  private objectFitList: ImageFit[] = [
    ImageFit.Cover,
    ImageFit.Contain,
    ImageFit.Fill,
    ImageFit.None,
    ImageFit.ScaleDown
  ];

  private getObjectFitName(fit: ImageFit): string {
    switch (fit) {
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

  private addLog(msg: string) {
    this.logMessages.unshift(`[${new Date().toLocaleTimeString()}] ${msg}`);
    if (this.logMessages.length > 20) {
      this.logMessages.pop();
    }
  }

  async aboutToAppear() {
    // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
    this.pixelMap = await this.getPixmapFromMedia($r('app.media.startIcon'));
    // $r('app.media.background') 需要替换为开发者所需的图像资源文件
    this.pixelMapAlt = await this.getPixmapFromMedia($r('app.media.background'));

    if (this.pixelMap) {
      this.pixelMapDesc = new PixelMapDrawableDescriptor(this.pixelMap);
      this.descFromPixelMap = this.pixelMapDesc;
    }

    // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
    this.resourceDesc = new PixelMapDrawableDescriptor($r('app.media.startIcon'));
    this.descFromResource = this.resourceDesc;
    this.addLog('PixelMapDrawableDescriptor 初始化完成');
  }

  build() {
    Scroll() {
      Column({ space: 15 }) {
        Text('PixelMapDrawableDescriptor 示例')
          .fontSize(26)
          .fontWeight(FontWeight.Bold)
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ top: 20, bottom: 5 })

        Text('演示通过 PixelMap / ResourceStr 创建及 API 方法')
          .fontSize(13)
          .fontColor('#666')
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ bottom: 10 })

        Divider().strokeWidth(2).color('#2196F3')

        if (this.showCreateSection) {
          Column({ space: 10 }) {
            Row() {
              Text('构造函数 - 创建方式')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showCreateSection })
                .onChange((value: boolean) => {
                  this.showCreateSection = value;
                })
            }
            .width('100%')

            Text('PixelMapDrawableDescriptor 支持两种构造方式:')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text('1. new PixelMapDrawableDescriptor(pixelMap) - 通过 PixelMap 创建')
              .fontSize(13)
              .fontColor('#2196F3')
              .width('100%')

            Text('2. new PixelMapDrawableDescriptor(resourceStr) - 通过资源引用创建')
              .fontSize(13)
              .fontColor('#FF9800')
              .width('100%')

            Row({ space: 8 }) {
              Button('切换到 PixelMap 源')
                .onClick(async () => {
                  this.currentSrcIndex = 0;
                  // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
                  let pm = await this.getPixmapFromMedia($r('app.media.startIcon'));
                  if (pm) {
                    this.pixelMapDesc = new PixelMapDrawableDescriptor(pm);
                    this.descFromPixelMap = this.pixelMapDesc;
                  }
                  this.addLog('切换: PixelMap 源');
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor(this.currentSrcIndex === 0 ? '#2196F3' : '#e0e0e0')
                .fontColor(this.currentSrcIndex === 0 ? Color.White : Color.Black)

              Button('切换到 ResourceStr 源')
                .onClick(() => {
                  this.currentSrcIndex = 1;
                  // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
                  this.resourceDesc = new PixelMapDrawableDescriptor($r('app.media.startIcon'));
                  this.descFromResource = this.resourceDesc;
                  this.addLog('切换: ResourceStr 源');
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor(this.currentSrcIndex === 1 ? '#FF9800' : '#e0e0e0')
                .fontColor(this.currentSrcIndex === 1 ? Color.White : Color.Black)
            }
            .width('100%')

            Row({ space: 8 }) {
              Button('PixelMap源 - background')
                .onClick(async () => {
                  this.currentSrcIndex = 0;
                  // $r('app.media.background') 需要替换为开发者所需的图像资源文件
                  let pm = await this.getPixmapFromMedia($r('app.media.background'));
                  if (pm) {
                    this.pixelMapDesc = new PixelMapDrawableDescriptor(pm);
                    this.descFromPixelMap = this.pixelMapDesc;
                  }
                  this.addLog('PixelMap源切换到 background');
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#4CAF50')

              Button('ResourceStr源 - background')
                .onClick(() => {
                  this.currentSrcIndex = 1;
                  // $r('app.media.background') 需要替换为开发者所需的图像资源文件
                  this.resourceDesc = new PixelMapDrawableDescriptor($r('app.media.background'));
                  this.descFromResource = this.resourceDesc;
                  this.addLog('ResourceStr源切换到 background');
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#4CAF50')
            }
            .width('100%')

            Row({ space: 8 }) {
              Button('PixelMap源 - foreground')
                .onClick(async () => {
                  this.currentSrcIndex = 0;
                  // $r('app.media.foreground') 需要替换为开发者所需的图像资源文件
                  let pm = await this.getPixmapFromMedia($r('app.media.foreground'));
                  if (pm) {
                    this.pixelMapDesc = new PixelMapDrawableDescriptor(pm);
                    this.descFromPixelMap = this.pixelMapDesc;
                  }
                  this.addLog('PixelMap源切换到 foreground');
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#9C27B0')

              Button('ResourceStr源 - foreground')
                .onClick(() => {
                  this.currentSrcIndex = 1;
                  // $r('app.media.foreground') 需要替换为开发者所需的图像资源文件
                  this.resourceDesc = new PixelMapDrawableDescriptor($r('app.media.foreground'));
                  this.descFromResource = this.resourceDesc;
                  this.addLog('ResourceStr源切换到 foreground');
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#9C27B0')
            }
            .width('100%')
          }
          .padding(15)
          .backgroundColor('#fff')
          .borderRadius(12)
          .width('100%')
        }

        Column() {
          Text('图片显示区域')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')
            .margin({ bottom: 5 })

          if (this.currentSrcIndex === 0 && this.descFromPixelMap) {
            Column() {
              Text('通过 PixelMap 创建的 PixelMapDrawableDescriptor')
                .fontSize(13)
                .fontColor('#2196F3')
                .margin({ bottom: 5 })
              Image(this.descFromPixelMap)
                .width(this.imageWidth)
                .height(this.imageHeight)
                .objectFit(this.objectFitMode)
                .borderRadius(12)
                .border({ width: 2, color: '#2196F3' })
            }
          }

          if (this.currentSrcIndex === 1 && this.descFromResource) {
            Column() {
              Text('通过 ResourceStr 创建的 PixelMapDrawableDescriptor')
                .fontSize(13)
                .fontColor('#FF9800')
                .margin({ bottom: 5 })
              Image(this.descFromResource)
                .width(this.imageWidth)
                .height(this.imageHeight)
                .objectFit(this.objectFitMode)
                .borderRadius(12)
                .border({ width: 2, color: '#FF9800' })
            }
          }
        }
        .padding(15)
        .backgroundColor('#f8f8f8')
        .borderRadius(12)
        .width('100%')
        .alignItems(HorizontalAlign.Center)

        Column({ space: 10 }) {
          Text('显示尺寸调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Row({ space: 10 }) {
            Text('宽度:')
              .fontSize(14)
              .width(50)
            Slider({
              value: this.imageWidth,
              min: 100,
              max: 400,
              step: 10,
              style: SliderStyle.OutSet
            })
              .onChange((value: number) => {
                this.imageWidth = value;
              })
              .layoutWeight(1)
            Text(`${this.imageWidth}`)
              .fontSize(14)
              .width(45)
          }
          .width('100%')

          Row({ space: 10 }) {
            Text('高度:')
              .fontSize(14)
              .width(50)
            Slider({
              value: this.imageHeight,
              min: 80,
              max: 350,
              step: 10,
              style: SliderStyle.OutSet
            })
              .onChange((value: number) => {
                this.imageHeight = value;
              })
              .layoutWeight(1)
            Text(`${this.imageHeight}`)
              .fontSize(14)
              .width(45)
          }
          .width('100%')

          Text('ObjectFit 模式')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')
            .margin({ top: 5 })

          Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start }) {
            ForEach(this.objectFitList, (fit: ImageFit) => {
              Button(this.getObjectFitName(fit))
                .onClick(() => {
                  this.objectFitMode = fit;
                  this.addLog(`ObjectFit: ${this.getObjectFitName(fit)}`);
                })
                .fontSize(12)
                .height(32)
                .margin(3)
                .backgroundColor(this.objectFitMode === fit ? '#2196F3' : '#e0e0e0')
                .fontColor(this.objectFitMode === fit ? Color.White : Color.Black)
            })
          }
          .width('100%')
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        if (this.showLoadSection) {
          Column({ space: 10 }) {
            Row() {
              Text('loadSync() 与 load() 加载测试')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showLoadSection })
                .onChange((value: boolean) => {
                  this.showLoadSection = value;
                })
            }
            .width('100%')

            Text('loadSync() 同步加载返回 DrawableDescriptorLoadedResult，包含 imageWidth 和 imageHeight')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text('load() 异步加载返回 Promise<DrawableDescriptorLoadedResult>')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Row({ space: 8 }) {
              Button('PixelMap源 loadSync()')
                .onClick(() => {
                  if (this.pixelMapDesc) {
                    try {
                      let result = this.pixelMapDesc.loadSync();
                      this.loadSyncResult = `PM loadSync: ${result.imageWidth}x${result.imageHeight}px`;
                      this.addLog(`PM loadSync: ${result.imageWidth}x${result.imageHeight}`);
                    } catch (e) {
                      this.loadSyncResult = `PM loadSync 失败: ${(e as BusinessError).message}`;
                      this.addLog(`PM loadSync 失败`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#2196F3')

              Button('ResourceStr源 loadSync()')
                .onClick(() => {
                  if (this.resourceDesc) {
                    try {
                      let result = this.resourceDesc.loadSync();
                      this.loadSyncResult = `RS loadSync: ${result.imageWidth}x${result.imageHeight}px`;
                      this.addLog(`RS loadSync: ${result.imageWidth}x${result.imageHeight}`);
                    } catch (e) {
                      this.loadSyncResult = `RS loadSync 失败: ${(e as BusinessError).message}`;
                      this.addLog(`RS loadSync 失败`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#FF9800')
            }
            .width('100%')

            Row({ space: 8 }) {
              Button('PixelMap源 load()')
                .onClick(async () => {
                  if (this.pixelMapDesc) {
                    try {
                      let result = await this.pixelMapDesc.load();
                      this.loadAsyncResult = `PM load: ${result.imageWidth}x${result.imageHeight}px`;
                      this.addLog(`PM load: ${result.imageWidth}x${result.imageHeight}`);
                    } catch (e) {
                      this.loadAsyncResult = `PM load 失败: ${(e as BusinessError).message}`;
                      this.addLog(`PM load 失败`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#2196F3')

              Button('ResourceStr源 load()')
                .onClick(async () => {
                  if (this.resourceDesc) {
                    try {
                      let result = await this.resourceDesc.load();
                      this.loadAsyncResult = `RS load: ${result.imageWidth}x${result.imageHeight}px`;
                      this.addLog(`RS load: ${result.imageWidth}x${result.imageHeight}`);
                    } catch (e) {
                      this.loadAsyncResult = `RS load 失败: ${(e as BusinessError).message}`;
                      this.addLog(`RS load 失败`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#FF9800')
            }
            .width('100%')

            Text(this.loadSyncResult)
              .fontSize(14)
              .fontColor(Color.Green)
              .width('100%')
            Text(this.loadAsyncResult)
              .fontSize(14)
              .fontColor(Color.Green)
              .width('100%')
          }
          .padding(15)
          .backgroundColor('#fff')
          .borderRadius(12)
          .width('100%')
        }

        if (this.showPixelMapSection) {
          Column({ space: 10 }) {
            Row() {
              Text('getPixelMap() 获取原始 PixelMap')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showPixelMapSection })
                .onChange((value: boolean) => {
                  this.showPixelMapSection = value;
                })
            }
            .width('100%')

            Text('getPixelMap() 可从 PixelMapDrawableDescriptor 中提取原始 PixelMap 对象')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Row({ space: 8 }) {
              Button('获取 PixelMap 源的 PixelMap')
                .onClick(async () => {
                  if (this.pixelMapDesc) {
                    try {
                      let pm = this.pixelMapDesc.getPixelMap();
                      let info = await pm.getImageInfo();
                      this.pixelMapInfo = `PM源: ${info.size.width}x${info.size.height}, format=${info.pixelFormat}`;
                      this.getPixelMapResult = 'getPixelMap(PM源) 成功';
                      this.addLog('getPixelMap(PM源) 成功');
                    } catch (e) {
                      this.getPixelMapResult = `getPixelMap(PM源) 失败: ${(e as BusinessError).message}`;
                      this.addLog(`getPixelMap(PM源) 失败`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)

              Button('获取 ResourceStr 源的 PixelMap')
                .onClick(async () => {
                  if (this.resourceDesc) {
                    try {
                      let pm = this.resourceDesc.getPixelMap();
                      let info = await pm.getImageInfo();
                      this.pixelMapInfo = `RS源: ${info.size.width}x${info.size.height}, format=${info.pixelFormat}`;
                      this.getPixelMapResult = 'getPixelMap(RS源) 成功';
                      this.addLog('getPixelMap(RS源) 成功');
                    } catch (e) {
                      this.getPixelMapResult = `getPixelMap(RS源) 失败: ${(e as BusinessError).message}`;
                      this.addLog(`getPixelMap(RS源) 失败`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#FF9800')
            }
            .width('100%')

            Text(this.getPixelMapResult)
              .fontSize(14)
              .fontColor(this.getPixelMapResult.includes('成功') ? Color.Green : Color.Red)
              .width('100%')

            Text(this.pixelMapInfo)
              .fontSize(13)
              .fontColor('#333')
              .width('100%')
          }
          .padding(15)
          .backgroundColor('#fff')
          .borderRadius(12)
          .width('100%')
        }

        if (this.showReleaseSection) {
          Column({ space: 10 }) {
            Row() {
              Text('release() / isReleased() / invalidate()')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showReleaseSection })
                .onChange((value: boolean) => {
                  this.showReleaseSection = value;
                })
            }
            .width('100%')

            Text('release() 释放后，访问内部数据的方法将抛出 BusinessError 111002')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Row({ space: 8 }) {
              Button('释放 PixelMap 源')
                .onClick(() => {
                  if (this.pixelMapDesc) {
                    this.pixelMapDesc.release();
                    this.isReleasedPm = this.pixelMapDesc.isReleased();
                    this.releaseStatus = `PM源 isReleased=${this.isReleasedPm}`;
                    this.addLog(`PM源 release()`);
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#F44336')

              Button('释放 ResourceStr 源')
                .onClick(() => {
                  if (this.resourceDesc) {
                    this.resourceDesc.release();
                    this.isReleasedRs = this.resourceDesc.isReleased();
                    this.releaseStatus = `RS源 isReleased=${this.isReleasedRs}`;
                    this.addLog(`RS源 release()`);
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#FF5722')
            }
            .width('100%')

            Row({ space: 8 }) {
              Button('检查 PM源 isReleased')
                .onClick(() => {
                  if (this.pixelMapDesc) {
                    this.isReleasedPm = this.pixelMapDesc.isReleased();
                    this.releaseStatus = `PM源 isReleased=${this.isReleasedPm}`;
                    this.addLog(`PM源 isReleased=${this.isReleasedPm}`);
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#2196F3')

              Button('检查 RS源 isReleased')
                .onClick(() => {
                  if (this.resourceDesc) {
                    this.isReleasedRs = this.resourceDesc.isReleased();
                    this.releaseStatus = `RS源 isReleased=${this.isReleasedRs}`;
                    this.addLog(`RS源 isReleased=${this.isReleasedRs}`);
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#03A9F4')
            }
            .width('100%')

            Row({ space: 8 }) {
              Button('PM源 invalidate()')
                .onClick(() => {
                  if (this.pixelMapDesc) {
                    this.invalidateStatus = 'PM源 invalidate() 已触发';
                    this.addLog('PM源 invalidate()');
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#4CAF50')

              Button('RS源 invalidate()')
                .onClick(() => {
                  if (this.resourceDesc) {
                    this.invalidateStatus = 'RS源 invalidate() 已触发';
                    this.addLog('RS源 invalidate()');
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#4CAF50')
            }
            .width('100%')

            Text(this.releaseStatus)
              .fontSize(14)
              .fontColor((this.isReleasedPm || this.isReleasedRs) ? Color.Red : Color.Green)
              .width('100%')
            Text(this.invalidateStatus)
              .fontSize(14)
              .fontColor(Color.Green)
              .width('100%')
          }
          .padding(15)
          .backgroundColor('#fff')
          .borderRadius(12)
          .width('100%')
        }

        Column({ space: 10 }) {
          Text('操作日志')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Button('清空日志')
            .onClick(() => {
              this.logMessages = [];
            })
            .width('100%')
            .backgroundColor('#9E9E9E')
            .fontSize(13)

          Scroll() {
            Column() {
              ForEach(this.logMessages, (msg: string) => {
                Text(msg)
                  .fontSize(12)
                  .fontColor('#333')
                  .width('100%')
                  .padding({ top: 2, bottom: 2 })
              })
            }
          }
          .height(120)
          .width('100%')
          .backgroundColor('#fafafa')
          .borderRadius(8)
          .padding(8)
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        Button('返回')
          .onClick(() => {
            router.back();
          })
          .width('80%')
          .margin({ bottom: 30 })
      }
      .padding({ left: 15, right: 15 })
    }
    .height('100%')
    .width('100%')
  }

  private async getPixmapFromMedia(resource: Resource): Promise<image.PixelMap | undefined> {
    let context = this.getUIContext().getHostContext();
    if (!context) {
      return undefined;
    }
    let unit8Array = await context.resourceManager.getMediaContent({
      bundleName: resource.bundleName,
      moduleName: resource.moduleName,
      id: resource.id
    });
    let imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength));
    let createPixelMap: image.PixelMap = await imageSource.createPixelMap({
      desiredPixelFormat: image.PixelMapFormat.BGRA_8888
    });
    await imageSource.release();
    return createPixelMap;
  }
}