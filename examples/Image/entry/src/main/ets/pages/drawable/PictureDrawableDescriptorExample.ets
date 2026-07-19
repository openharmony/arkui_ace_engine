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
 * PictureDrawableDescriptor 用法示例
 * 演示通过 image.Picture 创建 PictureDrawableDescriptor，
 * 以及 setHdrComposition()、loadSync()、load()、getPixelMap()、
 * release()、isReleased()、invalidate() 等方法
 */

import { image } from '@kit.ImageKit';
import { BusinessError } from '@kit.BasicServicesKit';
import { router } from '@kit.ArkUI';
import { PictureDrawableDescriptor, HdrCompositionConfig } from '@ohos.arkui.drawableDescriptor';

@Entry
@Component
struct PictureDrawableDescriptorExample {

  @State pictureDesc: PictureDrawableDescriptor | undefined = undefined;
  @State pictureDescAlt: PictureDrawableDescriptor | undefined = undefined;
  @State pictureSrc: image.Picture | undefined = undefined;
  @State pictureSrcAlt: image.Picture | undefined = undefined;
  @State loadSyncResult: string = '';
  @State loadAsyncResult: string = '';
  @State getPixelMapResult: string = '';
  @State releaseStatus: string = '';
  @State isReleasedMain: boolean = false;
  @State isReleasedAlt: boolean = false;
  @State invalidateStatus: string = '';
  @State hdrEnabled: boolean = false;
  @State hdrRectLeft: number = 0;
  @State hdrRectTop: number = 0;
  @State hdrRectWidth: number = 300;
  @State hdrRectHeight: number = 200;
  @State hdrStatus: string = '';
  @State imageWidth: number = 300;
  @State imageHeight: number = 200;
  @State objectFitMode: ImageFit = ImageFit.Cover;
  @State currentSrcIndex: number = 0;
  @State showLoadSection: boolean = true;
  @State showPixelMapSection: boolean = true;
  @State showHdrSection: boolean = true;
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
    this.pictureSrc = await this.getPictureFromMedia($r('app.media.startIcon'));
    // $r('app.media.background') 需要替换为开发者所需的图像资源文件
    this.pictureSrcAlt = await this.getPictureFromMedia($r('app.media.background'));
    if (this.pictureSrc) {
      this.pictureDesc = new PictureDrawableDescriptor(this.pictureSrc);
    }
    if (this.pictureSrcAlt) {
      this.pictureDescAlt = new PictureDrawableDescriptor(this.pictureSrcAlt);
    }
    this.addLog('PictureDrawableDescriptor 初始化完成');
  }

  build() {
    Scroll() {
      Column({ space: 15 }) {
        Text('PictureDrawableDescriptor 示例')
          .fontSize(26)
          .fontWeight(FontWeight.Bold)
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ top: 20, bottom: 5 })

        Text('演示通过 image.Picture 创建及 HDR 合成配置')
          .fontSize(13)
          .fontColor('#666')
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ bottom: 10 })

        Divider().strokeWidth(2).color('#2196F3')

        Column({ space: 10 }) {
          Text('图片源选择')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text('PictureDrawableDescriptor 通过 image.Picture 对象创建')
            .fontSize(13)
            .fontColor('#666')
            .width('100%')

          Text(`当前资源索引: ${this.currentSrcIndex}`)
            .fontSize(14)
            .fontColor('#2196F3')
            .width('100%')

          Row({ space: 8 }) {
            Button('资源0 (startIcon)')
              .onClick(async () => {
                this.currentSrcIndex = 0;
                // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
                let pic = await this.getPictureFromMedia($r('app.media.startIcon'));
                if (pic) {
                  this.pictureDesc = new PictureDrawableDescriptor(pic);
                }
                this.addLog('切换到 startIcon');
              })
              .fontSize(13)
              .layoutWeight(1)
              .backgroundColor(this.currentSrcIndex === 0 ? '#2196F3' : '#e0e0e0')
              .fontColor(this.currentSrcIndex === 0 ? Color.White : Color.Black)

            Button('资源1 (background)')
              .onClick(async () => {
                this.currentSrcIndex = 1;
                // $r('app.media.background') 需要替换为开发者所需的图像资源文件
                let pic = await this.getPictureFromMedia($r('app.media.background'));
                if (pic) {
                  this.pictureDesc = new PictureDrawableDescriptor(pic);
                }
                this.addLog('切换到 background');
              })
              .fontSize(13)
              .layoutWeight(1)
              .backgroundColor(this.currentSrcIndex === 1 ? '#FF9800' : '#e0e0e0')
              .fontColor(this.currentSrcIndex === 1 ? Color.White : Color.Black)

            Button('资源2 (foreground)')
              .onClick(async () => {
                this.currentSrcIndex = 2;
                // $r('app.media.foreground') 需要替换为开发者所需的图像资源文件
                let pic = await this.getPictureFromMedia($r('app.media.foreground'));
                if (pic) {
                  this.pictureDesc = new PictureDrawableDescriptor(pic);
                }
                this.addLog('切换到 foreground');
              })
              .fontSize(13)
              .layoutWeight(1)
              .backgroundColor(this.currentSrcIndex === 2 ? '#4CAF50' : '#e0e0e0')
              .fontColor(this.currentSrcIndex === 2 ? Color.White : Color.Black)
          }
          .width('100%')
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        if (this.pictureDesc) {
          Column() {
            Text('PictureDrawableDescriptor 图片显示')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')
              .margin({ bottom: 5 })

            Text('继承自 DrawableDescriptor，可作为 Image 组件的 src 参数')
              .fontSize(13)
              .fontColor('#666')
              .margin({ bottom: 8 })

            Image(this.pictureDesc)
              .width(this.imageWidth)
              .height(this.imageHeight)
              .objectFit(this.objectFitMode)
              .borderRadius(12)
              .border({ width: 2, color: '#2196F3' })
              .shadow({ radius: 5, color: '#00000030', offsetX: 2, offsetY: 2 })
              .id('pictureImage')
          }
          .padding(15)
          .backgroundColor('#f8f8f8')
          .borderRadius(12)
          .width('100%')
          .alignItems(HorizontalAlign.Center)
        }

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

          Text(`当前: ${this.getObjectFitName(this.objectFitMode)}`)
            .fontSize(14)
            .fontColor('#2196F3')
            .width('100%')

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
              Text('loadSync() / load() 加载测试')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showLoadSection })
                .onChange((value: boolean) => {
                  this.showLoadSection = value;
                })
            }
            .width('100%')

            Text('loadSync() 同步加载返回 DrawableDescriptorLoadedResult')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text('load() 异步加载返回 Promise<DrawableDescriptorLoadedResult>')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Row({ space: 8 }) {
              Button('loadSync() 主图')
                .onClick(() => {
                  if (this.pictureDesc) {
                    try {
                      let result = this.pictureDesc.loadSync();
                      this.loadSyncResult = `主图 loadSync: ${result.imageWidth}x${result.imageHeight}px`;
                      this.addLog(`主图 loadSync: ${result.imageWidth}x${result.imageHeight}`);
                    } catch (e) {
                      this.loadSyncResult = `loadSync 失败: ${(e as BusinessError).message}`;
                      this.addLog(`主图 loadSync 失败`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#2196F3')

              Button('loadSync() 备用图')
                .onClick(() => {
                  if (this.pictureDescAlt) {
                    try {
                      let result = this.pictureDescAlt.loadSync();
                      this.loadSyncResult = `备用 loadSync: ${result.imageWidth}x${result.imageHeight}px`;
                      this.addLog(`备用 loadSync: ${result.imageWidth}x${result.imageHeight}`);
                    } catch (e) {
                      this.loadSyncResult = `备用 loadSync 失败: ${(e as BusinessError).message}`;
                      this.addLog(`备用 loadSync 失败`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#FF9800')
            }
            .width('100%')

            Row({ space: 8 }) {
              Button('load() 主图')
                .onClick(async () => {
                  if (this.pictureDesc) {
                    try {
                      let result = await this.pictureDesc.load();
                      this.loadAsyncResult = `主图 load: ${result.imageWidth}x${result.imageHeight}px`;
                      this.addLog(`主图 load: ${result.imageWidth}x${result.imageHeight}`);
                    } catch (e) {
                      this.loadAsyncResult = `主图 load 失败: ${(e as BusinessError).message}`;
                      this.addLog(`主图 load 失败`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#2196F3')

              Button('load() 备用图')
                .onClick(async () => {
                  if (this.pictureDescAlt) {
                    try {
                      let result = await this.pictureDescAlt.load();
                      this.loadAsyncResult = `备用 load: ${result.imageWidth}x${result.imageHeight}px`;
                      this.addLog(`备用 load: ${result.imageWidth}x${result.imageHeight}`);
                    } catch (e) {
                      this.loadAsyncResult = `备用 load 失败: ${(e as BusinessError).message}`;
                      this.addLog(`备用 load 失败`);
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
              Text('getPixelMap() 获取 PixelMap')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showPixelMapSection })
                .onChange((value: boolean) => {
                  this.showPixelMapSection = value;
                })
            }
            .width('100%')

            Text('从 PictureDrawableDescriptor 中提取 PixelMap 对象')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Row({ space: 8 }) {
              Button('主图 getPixelMap()')
                .onClick(() => {
                  if (this.pictureDesc) {
                    try {
                      let pm = this.pictureDesc.getPixelMap();
                      this.getPixelMapResult = '主图 getPixelMap 成功';
                      this.addLog('主图 getPixelMap 成功');
                    } catch (e) {
                      this.getPixelMapResult = `主图 getPixelMap 失败: ${(e as BusinessError).message}`;
                      this.addLog(`主图 getPixelMap 失败`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)

              Button('备用图 getPixelMap()')
                .onClick(() => {
                  if (this.pictureDescAlt) {
                    try {
                      let pm = this.pictureDescAlt.getPixelMap();
                      this.getPixelMapResult = '备用图 getPixelMap 成功';
                      this.addLog('备用图 getPixelMap 成功');
                    } catch (e) {
                      this.getPixelMapResult = `备用图 getPixelMap 失败: ${(e as BusinessError).message}`;
                      this.addLog(`备用图 getPixelMap 失败`);
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
          }
          .padding(15)
          .backgroundColor('#fff')
          .borderRadius(12)
          .width('100%')
        }

        if (this.showHdrSection) {
          Column({ space: 10 }) {
            Row() {
              Text('setHdrComposition() HDR 合成配置')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showHdrSection })
                .onChange((value: boolean) => {
                  this.showHdrSection = value;
                })
            }
            .width('100%')

            Text('setHdrComposition() 设置 HDR 合成配置，参数为 HdrCompositionConfig')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text('HdrCompositionConfig 包含 rect 属性，指定 HDR 合成的矩形区域')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text('rect 包含 left, top, width, height 四个属性，定义合成区域范围')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Row({ space: 10 }) {
              Text('rect.left:')
                .fontSize(14)
                .width(60)
              Slider({
                value: this.hdrRectLeft,
                min: 0,
                max: 400,
                step: 10,
                style: SliderStyle.OutSet
              })
                .onChange((value: number) => {
                  this.hdrRectLeft = value;
                })
                .layoutWeight(1)
              Text(`${this.hdrRectLeft}`)
                .fontSize(14)
                .width(40)
            }
            .width('100%')

            Row({ space: 10 }) {
              Text('rect.top:')
                .fontSize(14)
                .width(60)
              Slider({
                value: this.hdrRectTop,
                min: 0,
                max: 300,
                step: 10,
                style: SliderStyle.OutSet
              })
                .onChange((value: number) => {
                  this.hdrRectTop = value;
                })
                .layoutWeight(1)
              Text(`${this.hdrRectTop}`)
                .fontSize(14)
                .width(40)
            }
            .width('100%')

            Row({ space: 10 }) {
              Text('rect.width:')
                .fontSize(14)
                .width(60)
              Slider({
                value: this.hdrRectWidth,
                min: 50,
                max: 400,
                step: 10,
                style: SliderStyle.OutSet
              })
                .onChange((value: number) => {
                  this.hdrRectWidth = value;
                })
                .layoutWeight(1)
              Text(`${this.hdrRectWidth}`)
                .fontSize(14)
                .width(40)
            }
            .width('100%')

            Row({ space: 10 }) {
              Text('rect.height:')
                .fontSize(14)
                .width(60)
              Slider({
                value: this.hdrRectHeight,
                min: 50,
                max: 300,
                step: 10,
                style: SliderStyle.OutSet
              })
                .onChange((value: number) => {
                  this.hdrRectHeight = value;
                })
                .layoutWeight(1)
              Text(`${this.hdrRectHeight}`)
                .fontSize(14)
                .width(40)
            }
            .width('100%')

            Row({ space: 8 }) {
              Toggle({ type: ToggleType.Checkbox, isOn: this.hdrEnabled })
                .onChange((value: boolean) => {
                  this.hdrEnabled = value;
                  if (this.pictureDesc) {
                    if (value) {
                      this.pictureDesc.setHdrComposition({
                        rect: { x: this.hdrRectLeft, y: this.hdrRectTop, width: this.hdrRectWidth, height: this.hdrRectHeight }
                      });
                      this.hdrStatus = `HDR 已启用: rect(${this.hdrRectLeft},${this.hdrRectTop},${this.hdrRectWidth},${this.hdrRectHeight})`;
                      this.addLog('HDR Composition 已启用');
                    } else {
                      this.pictureDesc.setHdrComposition({
                        rect: { x: 0, y: 0, width: 0, height: 0 }
                      });
                      this.hdrStatus = 'HDR 已禁用';
                      this.addLog('HDR Composition 已禁用');
                    }
                  }
                })
              Text('启用 HDR Composition')
                .fontSize(14)
            }
            .width('100%')

            Button('应用 HDR 配置')
              .onClick(() => {
                if (this.pictureDesc) {
                  let config: HdrCompositionConfig = {
                    rect: { x: this.hdrRectLeft, y: this.hdrRectTop, width: this.hdrRectWidth, height: this.hdrRectHeight }
                  };
                  this.pictureDesc.setHdrComposition(config);
                  this.hdrStatus = `HDR 已设置: rect(${this.hdrRectLeft},${this.hdrRectTop},${this.hdrRectWidth},${this.hdrRectHeight})`;
                  this.addLog(`HDR setHdrComposition: rect(${this.hdrRectLeft},${this.hdrRectTop},${this.hdrRectWidth},${this.hdrRectHeight})`);
                }
              })
              .width('100%')
              .backgroundColor('#2196F3')

            Text(this.hdrStatus)
              .fontSize(14)
              .fontColor(this.hdrEnabled ? '#2196F3' : Color.Gray)
              .width('100%')
          }
          .padding(15)
          .backgroundColor('#e3f2fd')
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

            Text('release() 释放 PictureDrawableDescriptor 对象，释放后访问内部数据的方法将失败')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text('isReleased() 返回 boolean，检查对象是否已释放')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text('invalidate() 触发重绘，如未绑定组件则不做操作')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Row({ space: 8 }) {
              Button('释放主图')
                .onClick(() => {
                  if (this.pictureDesc) {
                    this.pictureDesc.release();
                    this.isReleasedMain = this.pictureDesc.isReleased();
                    this.releaseStatus = `主图 isReleased=${this.isReleasedMain}`;
                    this.addLog('主图 release()');
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#F44336')

              Button('释放备用图')
                .onClick(() => {
                  if (this.pictureDescAlt) {
                    this.pictureDescAlt.release();
                    this.isReleasedAlt = this.pictureDescAlt.isReleased();
                    this.releaseStatus = `备用图 isReleased=${this.isReleasedAlt}`;
                    this.addLog('备用图 release()');
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#FF5722')
            }
            .width('100%')

            Row({ space: 8 }) {
              Button('检查主图 isReleased')
                .onClick(() => {
                  if (this.pictureDesc) {
                    this.isReleasedMain = this.pictureDesc.isReleased();
                    this.releaseStatus = `主图 isReleased=${this.isReleasedMain}`;
                    this.addLog(`主图 isReleased=${this.isReleasedMain}`);
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#2196F3')

              Button('检查备用图 isReleased')
                .onClick(() => {
                  if (this.pictureDescAlt) {
                    this.isReleasedAlt = this.pictureDescAlt.isReleased();
                    this.releaseStatus = `备用图 isReleased=${this.isReleasedAlt}`;
                    this.addLog(`备用图 isReleased=${this.isReleasedAlt}`);
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#03A9F4')
            }
            .width('100%')

            Row({ space: 8 }) {
              Button('主图 invalidate()')
                .onClick(() => {
                  if (this.pictureDesc) {
                    this.invalidateStatus = '主图 invalidate() 已触发';
                    this.addLog('主图 invalidate()');
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#4CAF50')

              Button('备用图 invalidate()')
                .onClick(() => {
                  if (this.pictureDescAlt) {
                    this.invalidateStatus = '备用图 invalidate() 已触发';
                    this.addLog('备用图 invalidate()');
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#4CAF50')
            }
            .width('100%')

            Button('释放后尝试 getPixelMap()（预期报错）')
              .onClick(() => {
                if (this.pictureDesc && this.pictureDesc.isReleased()) {
                  try {
                    this.pictureDesc.getPixelMap();
                    this.releaseStatus = '意外: 释放后 getPixelMap 未报错';
                  } catch (e) {
                    this.releaseStatus = `预期报错: code=${(e as BusinessError).code}`;
                    this.addLog(`释放后 getPixelMap: code=${(e as BusinessError).code}`);
                  }
                } else {
                  this.releaseStatus = '请先释放再测试';
                }
              })
              .width('100%')
              .backgroundColor('#9C27B0')

            Text(this.releaseStatus)
              .fontSize(14)
              .fontColor((this.isReleasedMain || this.isReleasedAlt) ? Color.Red : Color.Green)
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

  private async getPictureFromMedia(resource: Resource): Promise<image.Picture | undefined> {
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
    let picture: image.Picture = await imageSource.createPicture();
    await imageSource.release();
    return picture;
  }
}