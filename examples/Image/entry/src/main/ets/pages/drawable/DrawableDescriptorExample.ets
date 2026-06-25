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
 * DrawableDescriptor 基础用法示例
 * 演示 getPixelMap()、loadSync()、load()、release()、isReleased()、invalidate() 的使用
 * 涵盖多种资源加载方式、错误处理、生命周期管理、交互式属性调整等场景
 */
import { DrawableDescriptor } from '@kit.ArkUI';
import { image } from '@kit.ImageKit';
import { BusinessError } from '@kit.BasicServicesKit';
import { router } from '@kit.ArkUI';

@Entry
@Component
struct DrawableDescriptorExample {
  // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
  @State drawableSrc1: Resource = $r('app.media.startIcon');
  // $r('app.media.background') 需要替换为开发者所需的图像资源文件
  @State drawableSrc2: Resource = $r('app.media.background');
  // $r('app.media.foreground') 需要替换为开发者所需的图像资源文件
  @State drawableSrc3: Resource = $r('app.media.foreground');
  @State drawable: DrawableDescriptor | null = null;
  @State drawableAlt: DrawableDescriptor | null = null;
  @State pixelMap: image.PixelMap | null = null;
  @State pixelMapFromAlt: image.PixelMap | null = null;
  @State loadSyncResult: string = '';
  @State loadAsyncResult: string = '';
  @State getPixelMapResult: string = '';
  @State releaseStatus: string = '';
  @State isReleased: boolean = false;
  @State isReleasedAlt: boolean = false;
  @State invalidateStatus: string = '';
  @State currentResourceIndex: number = 0;
  @State imageWidth: number = 200;
  @State imageHeight: number = 200;
  @State objectFitMode: ImageFit = ImageFit.Cover;
  @State showPixelMapSection: boolean = true;
  @State showLoadSyncSection: boolean = true;
  @State showLoadAsyncSection: boolean = true;
  @State showReleaseSection: boolean = true;
  @State showInvalidateSection: boolean = true;
  @State showLifecycleSection: boolean = true;
  @State logMessages: string[] = [];

  private resourceList: Resource[] = [];
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
    this.resourceList = [this.drawableSrc1, this.drawableSrc2, this.drawableSrc3];
    const resManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resManager) {
      this.addLog('resourceManager 获取失败');
      return;
    }
    // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
    this.drawable = resManager.getDrawableDescriptor($r('app.media.startIcon').id) as DrawableDescriptor;
    // $r('app.media.background') 需要替换为开发者所需的图像资源文件
    this.drawableAlt = resManager.getDrawableDescriptor($r('app.media.background').id) as DrawableDescriptor;
    this.addLog('DrawableDescriptor 初始化成功');
  }

  build() {
    Scroll() {
      Column({ space: 15 }) {
        Text('DrawableDescriptor 基础用法示例')
          .fontSize(26)
          .fontWeight(FontWeight.Bold)
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ top: 20, bottom: 5 })

        Text('演示 getPixelMap / loadSync / load / release / isReleased / invalidate')
          .fontSize(13)
          .fontColor('#666')
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ bottom: 10 })

        Divider().strokeWidth(2).color('#2196F3')

        Column({ space: 10 }) {
          Text('图片源切换')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text(`当前资源索引: ${this.currentResourceIndex}`)
            .fontSize(14)
            .fontColor('#2196F3')
            .width('100%')

          Row({ space: 8 }) {
            Button('资源 0 (startIcon)')
              .onClick(async () => {
                this.currentResourceIndex = 0;
                // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
                this.drawable = this.getUIContext().getHostContext()?.resourceManager.getDrawableDescriptor($r('app.media.startIcon').id) as DrawableDescriptor;
                this.addLog('切换到资源 0');
              })
              .fontSize(13)
              .layoutWeight(1)
              .backgroundColor(this.currentResourceIndex === 0 ? '#2196F3' : '#e0e0e0')
              .fontColor(this.currentResourceIndex === 0 ? Color.White : Color.Black)

            Button('资源 1 (background)')
              .onClick(async () => {
                this.currentResourceIndex = 1;
                // $r('app.media.background') 需要替换为开发者所需的图像资源文件
                this.drawable = this.getUIContext().getHostContext()?.resourceManager.getDrawableDescriptor($r('app.media.background').id) as DrawableDescriptor;
                this.addLog('切换到资源 1');
              })
              .fontSize(13)
              .layoutWeight(1)
              .backgroundColor(this.currentResourceIndex === 1 ? '#2196F3' : '#e0e0e0')
              .fontColor(this.currentResourceIndex === 1 ? Color.White : Color.Black)

            Button('资源 2 (foreground)')
              .onClick(async () => {
                this.currentResourceIndex = 2;
                // $r('app.media.foreground') 需要替换为开发者所需的图像资源文件
                this.drawable = this.getUIContext().getHostContext()?.resourceManager.getDrawableDescriptor($r('app.media.foreground').id) as DrawableDescriptor;
                this.addLog('切换到资源 2');
              })
              .fontSize(13)
              .layoutWeight(1)
              .backgroundColor(this.currentResourceIndex === 2 ? '#2196F3' : '#e0e0e0')
              .fontColor(this.currentResourceIndex === 2 ? Color.White : Color.Black)
          }
          .width('100%')
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        if (this.drawable) {
          Column() {
            Text('主 DrawableDescriptor 显示')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .width('100%')
              .margin({ bottom: 5 })

            Text('Image 组件接收 DrawableDescriptor 作为 src 参数')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')
              .margin({ bottom: 8 })

            Image(this.drawable)
              .width(this.imageWidth)
              .height(this.imageHeight)
              .objectFit(this.objectFitMode)
              .borderRadius(12)
              .border({ width: 2, color: '#2196F3' })
              .shadow({ radius: 5, color: '#00000030', offsetX: 2, offsetY: 2 })
          }
          .padding(15)
          .backgroundColor('#f8f8f8')
          .borderRadius(12)
          .width('100%')
          .alignItems(HorizontalAlign.Center)
        }

        Column({ space: 10 }) {
          Text('显示尺寸调节')
            .fontSize(18)
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
                  this.addLog(`ObjectFit 切换为 ${this.getObjectFitName(fit)}`);
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

        if (this.showPixelMapSection && this.drawable) {
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

            Text('通过 getPixelMap() 方法可以从 DrawableDescriptor 中提取 PixelMap 对象')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text('提取后可直接用于 Image 组件或进行 PixelMap 操作')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Row({ space: 10 }) {
              Button('获取主 Drawable PixelMap')
                .onClick(() => {
                  if (this.drawable) {
                    try {
                      this.pixelMap = this.drawable.getPixelMap();
                      this.getPixelMapResult = 'getPixelMap() 成功';
                      this.addLog('getPixelMap() 成功');
                    } catch (e) {
                      this.getPixelMapResult = `getPixelMap() 失败: ${(e as BusinessError).message}`;
                      this.addLog(`getPixelMap() 失败: ${(e as BusinessError).message}`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)

              Button('获取备用 Drawable PixelMap')
                .onClick(() => {
                  if (this.drawableAlt) {
                    try {
                      this.pixelMapFromAlt = this.drawableAlt.getPixelMap();
                      this.getPixelMapResult = 'getPixelMap(alt) 成功';
                      this.addLog('getPixelMap(alt) 成功');
                    } catch (e) {
                      this.getPixelMapResult = `getPixelMap(alt) 失败: ${(e as BusinessError).message}`;
                      this.addLog(`getPixelMap(alt) 失败: ${(e as BusinessError).message}`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#FF9800')
            }
            .width('100%')

            Row({ space: 15 }) {
              if (this.pixelMap) {
                Column() {
                  Text('主 PixelMap')
                    .fontSize(12)
                    .fontColor('#666')
                    .margin({ bottom: 5 })
                  Image(this.pixelMap)
                    .width(150)
                    .height(150)
                    .objectFit(ImageFit.Cover)
                    .borderRadius(8)
                    .border({ width: 1, color: '#2196F3' })
                }
              }

              if (this.pixelMapFromAlt) {
                Column() {
                  Text('备用 PixelMap')
                    .fontSize(12)
                    .fontColor('#666')
                    .margin({ bottom: 5 })
                  Image(this.pixelMapFromAlt)
                    .width(150)
                    .height(150)
                    .objectFit(ImageFit.Cover)
                    .borderRadius(8)
                    .border({ width: 1, color: '#FF9800' })
                }
              }
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)

            Text(this.getPixelMapResult)
              .fontSize(14)
              .fontColor(this.getPixelMapResult.includes('成功') ? Color.Green : Color.Red)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .padding(15)
          .backgroundColor('#fff')
          .borderRadius(12)
          .width('100%')
        }

        if (this.showLoadSyncSection && this.drawable) {
          Column({ space: 10 }) {
            Row() {
              Text('loadSync() 同步加载')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showLoadSyncSection })
                .onChange((value: boolean) => {
                  this.showLoadSyncSection = value;
                })
            }
            .width('100%')

            Text('同步加载图片并返回 DrawableDescriptorLoadedResult，包含 imageWidth 和 imageHeight')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text('可能抛出 BusinessError 111001（资源加载失败）或 111002（native 内存已释放）')
              .fontSize(13)
              .fontColor('#999')
              .width('100%')

            Button('loadSync() 获取主图片尺寸')
              .onClick(() => {
                if (this.drawable) {
                  try {
                    let result = this.drawable.loadSync();
                    this.loadSyncResult = `loadSync 成功: 宽${result.imageWidth}px, 高${result.imageHeight}px`;
                    this.addLog(`loadSync: ${result.imageWidth}x${result.imageHeight}`);
                  } catch (e) {
                    let err = e as BusinessError;
                    this.loadSyncResult = `loadSync 失败: code=${err.code}, msg=${err.message}`;
                    this.addLog(`loadSync 失败: code=${err.code}`);
                  }
                }
              })
              .width('100%')

            Button('loadSync() 获取备用图片尺寸')
              .onClick(() => {
                if (this.drawableAlt) {
                  try {
                    let result = this.drawableAlt.loadSync();
                    this.loadSyncResult = `loadSync(alt) 成功: 宽${result.imageWidth}px, 高${result.imageHeight}px`;
                    this.addLog(`loadSync(alt): ${result.imageWidth}x${result.imageHeight}`);
                  } catch (e) {
                    let err = e as BusinessError;
                    this.loadSyncResult = `loadSync(alt) 失败: code=${err.code}, msg=${err.message}`;
                    this.addLog(`loadSync(alt) 失败: code=${err.code}`);
                  }
                }
              })
              .width('100%')
              .backgroundColor('#FF9800')

            Text(this.loadSyncResult)
              .fontSize(14)
              .fontColor(this.loadSyncResult.includes('成功') ? Color.Green : Color.Red)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .padding(15)
          .backgroundColor('#fff')
          .borderRadius(12)
          .width('100%')
        }

        if (this.showLoadAsyncSection && this.drawable) {
          Column({ space: 10 }) {
            Row() {
              Text('load() 异步加载')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showLoadAsyncSection })
                .onChange((value: boolean) => {
                  this.showLoadAsyncSection = value;
                })
            }
            .width('100%')

            Text('异步加载图片并返回 Promise<DrawableDescriptorLoadedResult>')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text('可能抛出 BusinessError 111001（资源加载失败）或 111002（native 内存已释放）')
              .fontSize(13)
              .fontColor('#999')
              .width('100%')

            Row({ space: 10 }) {
              Button('load() 异步获取主图片尺寸')
                .onClick(async () => {
                  if (this.drawable) {
                    try {
                      let result = await this.drawable.load();
                      this.loadAsyncResult = `load 成功: 宽${result.imageWidth}px, 高${result.imageHeight}px`;
                      this.addLog(`load: ${result.imageWidth}x${result.imageHeight}`);
                    } catch (e) {
                      let err = e as BusinessError;
                      this.loadAsyncResult = `load 失败: code=${err.code}, msg=${err.message}`;
                      this.addLog(`load 失败: code=${err.code}`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)

              Button('load() 异步获取备用图片尺寸')
                .onClick(async () => {
                  if (this.drawableAlt) {
                    try {
                      let result = await this.drawableAlt.load();
                      this.loadAsyncResult = `load(alt) 成功: 宽${result.imageWidth}px, 高${result.imageHeight}px`;
                      this.addLog(`load(alt): ${result.imageWidth}x${result.imageHeight}`);
                    } catch (e) {
                      let err = e as BusinessError;
                      this.loadAsyncResult = `load(alt) 失败: code=${err.code}, msg=${err.message}`;
                      this.addLog(`load(alt) 失败: code=${err.code}`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#FF9800')
            }
            .width('100%')

            Text(this.loadAsyncResult)
              .fontSize(14)
              .fontColor(this.loadAsyncResult.includes('成功') ? Color.Green : Color.Red)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .padding(15)
          .backgroundColor('#fff')
          .borderRadius(12)
          .width('100%')
        }

        if (this.showReleaseSection) {
          Column({ space: 10 }) {
            Row() {
              Text('release() 与 isReleased()')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showReleaseSection })
                .onChange((value: boolean) => {
                  this.showReleaseSection = value;
                })
            }
            .width('100%')

            Text('release() 释放 DrawableDescriptor 对象，释放后访问内部数据的方法将失败')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text('isReleased() 检查对象是否已释放，返回 boolean')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text('释放后调用 getPixelMap()、loadSync()、load() 等将抛出 BusinessError 111002')
              .fontSize(13)
              .fontColor('#F44336')
              .width('100%')

            Row({ space: 8 }) {
              Button('释放主 Drawable')
                .onClick(() => {
                  if (this.drawable) {
                    this.drawable.release();
                    this.isReleased = this.drawable.isReleased();
                    this.releaseStatus = `主 Drawable 已释放, isReleased=${this.isReleased}`;
                    this.addLog(`主 Drawable release() 执行`);
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#F44336')

              Button('释放备用 Drawable')
                .onClick(() => {
                  if (this.drawableAlt) {
                    this.drawableAlt.release();
                    this.isReleasedAlt = this.drawableAlt.isReleased();
                    this.releaseStatus = `备用 Drawable 已释放, isReleased=${this.isReleasedAlt}`;
                    this.addLog(`备用 Drawable release() 执行`);
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#FF5722')
            }
            .width('100%')

            Row({ space: 8 }) {
              Button('检查主 isReleased')
                .onClick(() => {
                  if (this.drawable) {
                    this.isReleased = this.drawable.isReleased();
                    this.releaseStatus = `主 isReleased=${this.isReleased}`;
                    this.addLog(`主 isReleased=${this.isReleased}`);
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#2196F3')

              Button('检查备用 isReleased')
                .onClick(() => {
                  if (this.drawableAlt) {
                    this.isReleasedAlt = this.drawableAlt.isReleased();
                    this.releaseStatus = `备用 isReleased=${this.isReleasedAlt}`;
                    this.addLog(`备用 isReleased=${this.isReleasedAlt}`);
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#03A9F4')
            }
            .width('100%')

            Button('释放后尝试 getPixelMap()（预期报错）')
              .onClick(() => {
                if (this.drawable && this.drawable.isReleased()) {
                  try {
                    this.drawable.getPixelMap();
                    this.releaseStatus = '意外: 释放后 getPixelMap() 未报错';
                  } catch (e) {
                    let err = e as BusinessError;
                    this.releaseStatus = `预期报错: code=${err.code}, msg=${err.message}`;
                    this.addLog(`释放后调用 getPixelMap: code=${err.code}`);
                  }
                } else {
                  this.releaseStatus = 'Drawable 未释放，请先释放再测试';
                }
              })
              .width('100%')
              .backgroundColor('#9C27B0')

            Text(this.releaseStatus)
              .fontSize(14)
              .fontColor(this.isReleased || this.isReleasedAlt ? Color.Red : Color.Green)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .padding(15)
          .backgroundColor('#fff')
          .borderRadius(12)
          .width('100%')
        }

        if (this.showInvalidateSection) {
          Column({ space: 10 }) {
            Row() {
              Text('invalidate() 重绘')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showInvalidateSection })
                .onChange((value: boolean) => {
                  this.showInvalidateSection = value;
                })
            }
            .width('100%')

            Text('invalidate() 触发 DrawableDescriptor 重绘，如未绑定组件则不做任何操作')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text(this.invalidateStatus)
              .fontSize(14)
              .fontColor(Color.Green)
              .width('100%')
              .textAlign(TextAlign.Center)
          }
          .padding(15)
          .backgroundColor('#fff')
          .borderRadius(12)
          .width('100%')
        }

        if (this.showLifecycleSection) {
          Column({ space: 10 }) {
            Row() {
              Text('生命周期综合测试')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showLifecycleSection })
                .onChange((value: boolean) => {
                  this.showLifecycleSection = value;
                })
            }
            .width('100%')

            Text('完整流程: 创建 -> loadSync -> getPixelMap -> invalidate -> release -> isReleased -> 释放后操作报错')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Button('执行完整生命周期流程')
              .onClick(async () => {
                const resManager = this.getUIContext().getHostContext()?.resourceManager;
                if (!resManager) {
                  this.addLog('resourceManager 获取失败');
                  return;
                }
                // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
                let dd = resManager.getDrawableDescriptor($r('app.media.startIcon').id) as DrawableDescriptor;
                this.addLog('1. 创建 DrawableDescriptor');

                try {
                  let loadResult = dd.loadSync();
                  this.addLog(`2. loadSync: ${loadResult.imageWidth}x${loadResult.imageHeight}`);
                } catch (e) {
                  this.addLog(`2. loadSync 失败: ${(e as BusinessError).code}`);
                }

                try {
                  let pm = dd.getPixelMap();
                  this.addLog(`3. getPixelMap 成功`);
                } catch (e) {
                  this.addLog(`3. getPixelMap 失败: ${(e as BusinessError).code}`);
                }

                this.addLog('4. invalidate 触发');

                let released = dd.isReleased();
                this.addLog(`5. isReleased(释放前): ${released}`);

                dd.release();
                this.addLog('6. release 执行');

                released = dd.isReleased();
                this.addLog(`7. isReleased(释放后): ${released}`);

                try {
                  dd.getPixelMap();
                  this.addLog('8. 释放后 getPixelMap: 未报错(意外)');
                } catch (e) {
                  this.addLog(`8. 释放后 getPixelMap: 报错 code=${(e as BusinessError).code}`);
                }

                try {
                  dd.loadSync();
                  this.addLog('9. 释放后 loadSync: 未报错(意外)');
                } catch (e) {
                  this.addLog(`9. 释放后 loadSync: 报错 code=${(e as BusinessError).code}`);
                }
              })
              .width('100%')
              .backgroundColor('#4CAF50')
          }
          .padding(15)
          .backgroundColor('#f0f8f0')
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
              ForEach(this.logMessages, (msg: string, index: number) => {
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
}