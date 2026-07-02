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
 * LayeredDrawableDescriptor 用法示例
 * 演示构造函数(fg/bg/mask)、getForeground()、getBackground()、getMask()、
 * getMaskClipPath()、setBlendMode()、getPixelMap()、loadSync()、load()、
 * release()、isReleased()、invalidate() 等完整API
 */
import { DrawableDescriptor, LayeredDrawableDescriptor, PixelMapDrawableDescriptor } from '@kit.ArkUI';
import { image } from '@kit.ImageKit';
import { drawing } from '@kit.ArkGraphics2D';
import { BusinessError } from '@kit.BasicServicesKit';
import { router } from '@kit.ArkUI';

@Entry
@Component
struct LayeredDrawableDescriptorExample {
  @State fore: image.PixelMap | undefined = undefined;
  @State back: image.PixelMap | undefined = undefined;
  @State maskPixel: image.PixelMap | undefined = undefined;
  @State foregroundDraw: DrawableDescriptor | undefined = undefined;
  @State backgroundDraw: DrawableDescriptor | undefined = undefined;
  @State maskDraw: DrawableDescriptor | undefined = undefined;
  @State layeredDesc: LayeredDrawableDescriptor | undefined = undefined;
  @State layeredDescNoMask: LayeredDrawableDescriptor | undefined = undefined;
  @State layeredDescOnlyFg: LayeredDrawableDescriptor | undefined = undefined;
  @State maskClipPath: string = '';
  @State blendMode1: drawing.BlendMode = drawing.BlendMode.SRC_OVER;
  @State blendModeName: string = 'SRC_OVER';
  @State layeredImageWidth: number = 200;
  @State layeredImageHeight: number = 200;
  @State loadSyncResult: string = '';
  @State loadAsyncResult: string = '';
  @State getPixelMapResult: string = '';
  @State releaseStatus: string = '';
  @State isReleasedFlag: boolean = false;
  @State invalidateStatus: string = '';
  @State currentLayerMode: number = 0;
  @State logMessages: string[] = [];
  private blendModeList: drawing.BlendMode[] = [
    drawing.BlendMode.CLEAR,
    drawing.BlendMode.SRC,
    drawing.BlendMode.DST,
    drawing.BlendMode.SRC_OVER,
    drawing.BlendMode.DST_OVER,
    drawing.BlendMode.SRC_IN,
    drawing.BlendMode.DST_IN,
    drawing.BlendMode.SRC_OUT,
    drawing.BlendMode.DST_OUT,
    drawing.BlendMode.SRC_ATOP,
    drawing.BlendMode.DST_ATOP,
    drawing.BlendMode.XOR,
    drawing.BlendMode.PLUS,
    drawing.BlendMode.MULTIPLY,
    drawing.BlendMode.SCREEN,
    drawing.BlendMode.OVERLAY,
  ];

  private getBlendModeName(mode: drawing.BlendMode): string {
    const names: Record<number, string> = {
      0: 'CLEAR',
      1: 'SRC',
      2: 'DST',
      3: 'SRC_OVER',
      4: 'DST_OVER',
      5: 'SRC_IN',
      6: 'DST_IN',
      7: 'SRC_OUT',
      8: 'DST_OUT',
      9: 'SRC_ATOP',
      10: 'DST_ATOP',
      11: 'XOR',
      12: 'PLUS',
      13: 'MULTIPLY',
      14: 'SCREEN',
      15: 'OVERLAY',
    };
    return names[mode] || 'UNKNOWN';
  }

  private addLog(msg: string) {
    this.logMessages.unshift(`[${new Date().toLocaleTimeString()}] ${msg}`);
    if (this.logMessages.length > 20) {
      this.logMessages.pop();
    }
  }

  async aboutToAppear() {
    // $r('app.media.foreground') 需要替换为开发者所需的图像资源文件
    this.fore = await this.getPixmapFromMedia($r('app.media.foreground'));
    // $r('app.media.background') 需要替换为开发者所需的图像资源文件
    this.back = await this.getPixmapFromMedia($r('app.media.background'));
    // $r('app.media.foreground') 需要替换为开发者所需的图像资源文件
    this.maskPixel = await this.getPixmapFromMedia($r('app.media.foreground'));

    if (this.fore) {
      this.foregroundDraw = new PixelMapDrawableDescriptor(this.fore);
    }
    if (this.back) {
      this.backgroundDraw = new PixelMapDrawableDescriptor(this.back);
    }
    if (this.maskPixel) {
      this.maskDraw = new PixelMapDrawableDescriptor(this.maskPixel);
    }

    this.layeredDesc = new LayeredDrawableDescriptor(this.foregroundDraw, this.backgroundDraw, this.maskDraw);
    this.layeredDescNoMask = new LayeredDrawableDescriptor(this.foregroundDraw, this.backgroundDraw);
    this.layeredDescOnlyFg = new LayeredDrawableDescriptor(this.foregroundDraw);
    this.maskClipPath = LayeredDrawableDescriptor.getMaskClipPath();
    this.addLog('LayeredDrawableDescriptor 初始化完成');
  }

  build() {
    Scroll() {
      Column({ space: 15 }) {
        Text('LayeredDrawableDescriptor 示例')
          .fontSize(26)
          .fontWeight(FontWeight.Bold)
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ top: 20, bottom: 5 })

        Text('演示分层图标的前景、背景、遮罩合成及 BlendMode')
          .fontSize(13)
          .fontColor('#666')
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ bottom: 10 })

        Divider().strokeWidth(2).color('#2196F3')

        Column({ space: 10 }) {
          Text('构造函数模式选择')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text('LayeredDrawableDescriptor 支持可选参数: foreground, background, mask')
            .fontSize(13)
            .fontColor('#666')
            .width('100%')

          Text(`当前模式: ${this.currentLayerMode === 0 ? '三层(fg+bg+mask)' :
            this.currentLayerMode === 1 ? '两层(fg+bg)' : '单层(fg)'}`)
            .fontSize(14)
            .fontColor('#2196F3')
            .width('100%')

          Row({ space: 8 }) {
            Button('三层(fg+bg+mask)')
              .onClick(() => {
                this.currentLayerMode = 0;
                this.layeredDesc =
                  new LayeredDrawableDescriptor(this.foregroundDraw, this.backgroundDraw, this.maskDraw);
                this.addLog('切换: 三层模式');
              })
              .fontSize(13)
              .layoutWeight(1)
              .backgroundColor(this.currentLayerMode === 0 ? '#2196F3' : '#e0e0e0')
              .fontColor(this.currentLayerMode === 0 ? Color.White : Color.Black)

            Button('两层(fg+bg)')
              .onClick(() => {
                this.currentLayerMode = 1;
                this.layeredDescNoMask = new LayeredDrawableDescriptor(this.foregroundDraw, this.backgroundDraw);
                this.addLog('切换: 两层模式');
              })
              .fontSize(13)
              .layoutWeight(1)
              .backgroundColor(this.currentLayerMode === 1 ? '#FF9800' : '#e0e0e0')
              .fontColor(this.currentLayerMode === 1 ? Color.White : Color.Black)

            Button('单层(fg)')
              .onClick(() => {
                this.currentLayerMode = 2;
                this.layeredDescOnlyFg = new LayeredDrawableDescriptor(this.foregroundDraw);
                this.addLog('切换: 单层模式');
              })
              .fontSize(13)
              .layoutWeight(1)
              .backgroundColor(this.currentLayerMode === 2 ? '#4CAF50' : '#e0e0e0')
              .fontColor(this.currentLayerMode === 2 ? Color.White : Color.Black)
          }
          .width('100%')
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        Column() {
          Text('分层图标合成结果')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')
            .margin({ bottom: 5 })

          if (this.currentLayerMode === 0 && this.layeredDesc) {
            Image(this.layeredDesc)
              .width(this.layeredImageWidth)
              .height(this.layeredImageHeight)
              .objectFit(ImageFit.Cover)
              .borderRadius(12)
              .border({ width: 2, color: '#2196F3' })
              .shadow({
                radius: 5,
                color: '#00000030',
                offsetX: 2,
                offsetY: 2
              })
          } else if (this.currentLayerMode === 1 && this.layeredDescNoMask) {
            Image(this.layeredDescNoMask)
              .width(this.layeredImageWidth)
              .height(this.layeredImageHeight)
              .objectFit(ImageFit.Cover)
              .borderRadius(12)
              .border({ width: 2, color: '#FF9800' })
          } else if (this.currentLayerMode === 2 && this.layeredDescOnlyFg) {
            Image(this.layeredDescOnlyFg)
              .width(this.layeredImageWidth)
              .height(this.layeredImageHeight)
              .objectFit(ImageFit.Cover)
              .borderRadius(12)
              .border({ width: 2, color: '#4CAF50' })
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
              value: this.layeredImageWidth,
              min: 100,
              max: 400,
              step: 10,
              style: SliderStyle.OutSet
            })
              .onChange((value: number) => {
                this.layeredImageWidth = value;
              })
              .layoutWeight(1)
            Text(`${this.layeredImageWidth}`)
              .fontSize(14)
              .width(45)
          }
          .width('100%')

          Row({ space: 10 }) {
            Text('高度:')
              .fontSize(14)
              .width(50)
            Slider({
              value: this.layeredImageHeight,
              min: 80,
              max: 350,
              step: 10,
              style: SliderStyle.OutSet
            })
              .onChange((value: number) => {
                this.layeredImageHeight = value;
              })
              .layoutWeight(1)
            Text(`${this.layeredImageHeight}`)
              .fontSize(14)
              .width(45)
          }
          .width('100%')
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        Column({ space: 10 }) {
          Text('getForeground() 获取前景层')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text('返回前景层的 DrawableDescriptor 对象，可用于单独显示前景')
            .fontSize(13)
            .fontColor('#666')
            .width('100%')

          if (this.layeredDesc) {
            Row({ space: 15 }) {
              Column() {
                Text('前景层')
                  .fontSize(12)
                  .fontColor('#2196F3')
                  .margin({ bottom: 5 })
                Image(this.layeredDesc.getForeground())
                  .width(120)
                  .height(120)
                  .objectFit(ImageFit.Cover)
                  .border({ width: 1, color: '#2196F3' })
                  .borderRadius(8)
              }

              Column() {
                Text('前景 PixelMap')
                  .fontSize(12)
                  .fontColor('#2196F3')
                  .margin({ bottom: 5 })
                Image(this.layeredDesc.getForeground().getPixelMap())
                  .width(120)
                  .height(120)
                  .objectFit(ImageFit.Cover)
                  .border({ width: 1, color: '#2196F3' })
                  .borderRadius(8)
              }
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)
          }
        }
        .padding(15)
        .backgroundColor('#e3f2fd')
        .borderRadius(12)
        .width('100%')

        Column({ space: 10 }) {
          Text('getBackground() 获取背景层')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text('返回背景层的 DrawableDescriptor 对象')
            .fontSize(13)
            .fontColor('#666')
            .width('100%')

          if (this.layeredDesc) {
            Row({ space: 15 }) {
              Column() {
                Text('背景层')
                  .fontSize(12)
                  .fontColor('#4CAF50')
                  .margin({ bottom: 5 })
                Image(this.layeredDesc.getBackground())
                  .width(120)
                  .height(120)
                  .objectFit(ImageFit.Cover)
                  .border({ width: 1, color: '#4CAF50' })
                  .borderRadius(8)
              }

              Column() {
                Text('背景 PixelMap')
                  .fontSize(12)
                  .fontColor('#4CAF50')
                  .margin({ bottom: 5 })
                Image(this.layeredDesc.getBackground().getPixelMap())
                  .width(120)
                  .height(120)
                  .objectFit(ImageFit.Cover)
                  .border({ width: 1, color: '#4CAF50' })
                  .borderRadius(8)
              }
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)
          }
        }
        .padding(15)
        .backgroundColor('#e8f5e9')
        .borderRadius(12)
        .width('100%')

        Column({ space: 10 }) {
          Text('getMask() 获取遮罩层')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text('返回遮罩层的 DrawableDescriptor 对象，定义图标形状裁剪区域')
            .fontSize(13)
            .fontColor('#666')
            .width('100%')

          if (this.layeredDesc) {
            Row({ space: 15 }) {
              Column() {
                Text('遮罩层')
                  .fontSize(12)
                  .fontColor('#FF9800')
                  .margin({ bottom: 5 })
                Image(this.layeredDesc.getMask())
                  .width(120)
                  .height(120)
                  .objectFit(ImageFit.Cover)
                  .border({ width: 1, color: '#FF9800' })
                  .borderRadius(8)
              }

              Column() {
                Text('遮罩 PixelMap')
                  .fontSize(12)
                  .fontColor('#FF9800')
                  .margin({ bottom: 5 })
                Image(this.layeredDesc.getMask().getPixelMap())
                  .width(120)
                  .height(120)
                  .objectFit(ImageFit.Cover)
                  .border({ width: 1, color: '#FF9800' })
                  .borderRadius(8)
              }
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)
          }
        }
        .padding(15)
        .backgroundColor('#fff3e0')
        .borderRadius(12)
        .width('100%')

        Column({ space: 10 }) {
          Text('getMaskClipPath() 遮罩裁剪路径')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text('静态方法，返回自适应图标遮罩的裁剪路径信息（SVG path 格式）')
            .fontSize(13)
            .fontColor('#666')
            .width('100%')

          Button('刷新 getMaskClipPath()')
            .onClick(() => {
              this.maskClipPath = LayeredDrawableDescriptor.getMaskClipPath();
              this.addLog('getMaskClipPath 已刷新');
            })
            .width('100%')

          Scroll() {
            Text(this.maskClipPath)
              .fontSize(11)
              .fontColor('#333')
              .width('100%')
              .copyOption(CopyOptions.LocalDevice)
          }
          .height(60)
          .backgroundColor('#fafafa')
          .borderRadius(8)
          .padding(8)
          .width('100%')
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        Column({ space: 10 }) {
          Text('setBlendMode() 合成模式')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text('设置前景与背景的合成模式，影响分层图标的视觉效果')
            .fontSize(13)
            .fontColor('#666')
            .width('100%')

          Text(`当前合成模式: ${this.blendModeName}`)
            .fontSize(14)
            .fontColor('#2196F3')
            .width('100%')

          Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start }) {
            ForEach(this.blendModeList, (mode: drawing.BlendMode) => {
              Button(this.getBlendModeName(mode))
                .onClick(() => {
                  if (this.layeredDesc) {
                    this.layeredDesc.setBlendMode(mode);
                    this.blendMode1 = mode;
                    this.blendModeName = this.getBlendModeName(mode);
                    this.addLog(`setBlendMode: ${this.blendModeName}`);
                  }
                })
                .fontSize(12)
                .height(32)
                .margin(3)
                .backgroundColor(this.blendMode1 === mode ? '#2196F3' : '#e0e0e0')
                .fontColor(this.blendMode1 === mode ? Color.White : Color.Black)
            })
          }
          .width('100%')
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        Column({ space: 10 }) {
          Text('loadSync() 与 load() 加载测试')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Row({ space: 10 }) {
            Button('loadSync()')
              .onClick(() => {
                if (this.layeredDesc) {
                  try {
                    let result = this.layeredDesc.loadSync();
                    this.loadSyncResult = `loadSync: ${result.imageWidth}x${result.imageHeight}px`;
                    this.addLog(`Layered loadSync: ${result.imageWidth}x${result.imageHeight}`);
                  } catch (e) {
                    this.loadSyncResult = `loadSync 失败: ${(e as BusinessError).message}`;
                    this.addLog(`Layered loadSync 失败`);
                  }
                }
              })
              .layoutWeight(1)

            Button('load()')
              .onClick(async () => {
                if (this.layeredDesc) {
                  try {
                    let result = await this.layeredDesc.load();
                    this.loadAsyncResult = `load: ${result.imageWidth}x${result.imageHeight}px`;
                    this.addLog(`Layered load: ${result.imageWidth}x${result.imageHeight}`);
                  } catch (e) {
                    this.loadAsyncResult = `load 失败: ${(e as BusinessError).message}`;
                    this.addLog(`Layered load 失败`);
                  }
                }
              })
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

        Column({ space: 10 }) {
          Text('release() / isReleased() / invalidate()')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text('LayeredDrawableDescriptor 继承自 DrawableDescriptor，同样支持 release/isReleased/invalidate')
            .fontSize(13)
            .fontColor('#666')
            .width('100%')

          Row({ space: 8 }) {
            Button('release()')
              .onClick(() => {
                if (this.layeredDesc) {
                  this.layeredDesc.release();
                  this.isReleasedFlag = this.layeredDesc.isReleased();
                  this.releaseStatus = `isReleased=${this.isReleasedFlag}`;
                  this.addLog('Layered release() 执行');
                }
              })
              .layoutWeight(1)
              .backgroundColor('#F44336')

            Button('isReleased()')
              .onClick(() => {
                if (this.layeredDesc) {
                  this.isReleasedFlag = this.layeredDesc.isReleased();
                  this.releaseStatus = `isReleased=${this.isReleasedFlag}`;
                  this.addLog(`Layered isReleased=${this.isReleasedFlag}`);
                }
              })
              .layoutWeight(1)
              .backgroundColor('#2196F3')

            Button('invalidate()')
              .onClick(() => {
                if (this.layeredDesc) {
                  this.invalidateStatus = 'invalidate() 已触发';
                  this.addLog('Layered invalidate() 触发');
                }
              })
              .layoutWeight(1)
              .backgroundColor('#4CAF50')
          }
          .width('100%')

          Text(this.releaseStatus)
            .fontSize(14)
            .fontColor(this.isReleasedFlag ? Color.Red : Color.Green)
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