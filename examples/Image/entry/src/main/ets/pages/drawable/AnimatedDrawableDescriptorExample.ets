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
 * AnimatedDrawableDescriptor 用法示例
 * 演示通过 PixelMap 数组或 ResourceStr 创建动画图片，
 * 以及 AnimationOptions(duration/iterations/autoPlay/stopMode/frameDurations)、
 * AnimationController(start/stop/pause/resume/getStatus)、
 * getAnimationController() 等完整API
 */
import { AnimatedDrawableDescriptor, AnimationOptions, AnimationController, AnimationStopMode } from '@kit.ArkUI';
import { image } from '@kit.ImageKit';
import { BusinessError } from '@kit.BasicServicesKit';
import { router } from '@kit.ArkUI';

@Entry
@Component
struct AnimatedDrawableDescriptorExample {
  @State pixelMaps: image.PixelMap[] = [];
  @State animatedFromPixelMaps: AnimatedDrawableDescriptor | undefined = undefined;
  // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
  @State animatedFromResource: AnimatedDrawableDescriptor | undefined = undefined;
  @State animationController: AnimationController | undefined = undefined;
  @State animationStatus: string = '';
  @State currentControllerId: string = '';
  @State durationValue: number = 1000;
  @State iterationsValue: number = 1;
  @State autoPlayEnabled: boolean = true;
  @State stopMode: AnimationStopMode = AnimationStopMode.FIRST_FRAME;
  @State imageWidth: number = 200;
  @State imageHeight: number = 200;
  @State loadSyncResult: string = '';
  @State loadAsyncResult: string = '';
  @State getPixelMapResult: string = '';
  @State releaseStatus: string = '';
  @State isReleased: boolean = false;
  @State invalidateStatus: string = '';
  @State showAnimationOptions: boolean = true;
  @State showAnimationController: boolean = true;
  @State showLoadTest: boolean = true;
  @State showLifecycle: boolean = true;
  @State currentSrcMode: number = 0;
  @State logMessages: string[] = [];

  private animationOptions: AnimationOptions = {
    duration: 1000,
    iterations: 1,
    autoPlay: true,
    stopMode: AnimationStopMode.FIRST_FRAME
  };

  private addLog(msg: string) {
    this.logMessages.unshift(`[${new Date().toLocaleTimeString()}] ${msg}`);
    if (this.logMessages.length > 20) {
      this.logMessages.pop();
    }
  }

  async aboutToAppear() {
    // $r('app.media.background') 需要替换为开发者所需的图像资源文件
    this.pixelMaps = await this.getPixelMapListFromMedia($r('app.media.background'));
    // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
    let frame1 = await this.getPixmapFromMedia($r('app.media.startIcon'));
    // $r('app.media.foreground') 需要替换为开发者所需的图像资源文件
    let frame2 = await this.getPixmapFromMedia($r('app.media.foreground'));
    // $r('app.media.background') 需要替换为开发者所需的图像资源文件
    let frame3 = await this.getPixmapFromMedia($r('app.media.background'));

    if (frame1) this.pixelMaps.push(frame1);
    if (frame2) this.pixelMaps.push(frame2);
    if (frame3) this.pixelMaps.push(frame3);

    if (this.pixelMaps.length > 0) {
      this.animatedFromPixelMaps = new AnimatedDrawableDescriptor(this.pixelMaps, this.animationOptions);
    }

    // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
    this.animatedFromResource = new AnimatedDrawableDescriptor($r('app.media.startIcon'), this.animationOptions);
    this.addLog('AnimatedDrawableDescriptor 初始化完成');
  }

  build() {
    Scroll() {
      Column({ space: 15 }) {
        Text('AnimatedDrawableDescriptor 示例')
          .fontSize(26)
          .fontWeight(FontWeight.Bold)
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ top: 20, bottom: 5 })

        Text('演示动画图片的创建、AnimationOptions配置及AnimationController控制')
          .fontSize(13)
          .fontColor('#666')
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ bottom: 10 })

        Divider().strokeWidth(2).color('#2196F3')

        Column({ space: 10 }) {
          Text('动画源选择')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text('AnimatedDrawableDescriptor 支持两种构造方式:')
            .fontSize(13)
            .fontColor('#666')
            .width('100%')

          Text('1. new AnimatedDrawableDescriptor(pixelMap[], options) - 通过 PixelMap 数组')
            .fontSize(13)
            .fontColor('#2196F3')
            .width('100%')

          Text('2. new AnimatedDrawableDescriptor(resourceStr, options) - 通过资源引用')
            .fontSize(13)
            .fontColor('#FF9800')
            .width('100%')

          Row({ space: 8 }) {
            Button('PixelMap 数组源')
              .onClick(() => {
                this.currentSrcMode = 0;
                this.addLog('切换: PixelMap数组源');
              })
              .fontSize(13)
              .layoutWeight(1)
              .backgroundColor(this.currentSrcMode === 0 ? '#2196F3' : '#e0e0e0')
              .fontColor(this.currentSrcMode === 0 ? Color.White : Color.Black)

            Button('ResourceStr 源')
              .onClick(() => {
                this.currentSrcMode = 1;
                this.addLog('切换: ResourceStr源');
              })
              .fontSize(13)
              .layoutWeight(1)
              .backgroundColor(this.currentSrcMode === 1 ? '#FF9800' : '#e0e0e0')
              .fontColor(this.currentSrcMode === 1 ? Color.White : Color.Black)
          }
          .width('100%')
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        Column() {
          Text('动画图片显示')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .width('100%')
            .margin({ bottom: 5 })

          if (this.currentSrcMode === 0 && this.animatedFromPixelMaps) {
            Column() {
              Text('PixelMap 数组动画')
                .fontSize(13)
                .fontColor('#2196F3')
                .margin({ bottom: 5 })
              Image(this.animatedFromPixelMaps)
                .width(this.imageWidth)
                .height(this.imageHeight)
                .objectFit(ImageFit.Cover)
                .borderRadius(12)
                .border({ width: 2, color: '#2196F3' })
                .id('animatedPixelMapsImage')
                .onFinish(() => {
                  this.animationStatus = 'PixelMap动画播放完成';
                  this.addLog('PixelMap动画 onFinish');
                })
            }
          }

          if (this.currentSrcMode === 1 && this.animatedFromResource) {
            Column() {
              Text('ResourceStr 动画')
                .fontSize(13)
                .fontColor('#FF9800')
                .margin({ bottom: 5 })
              Image(this.animatedFromResource)
                .width(this.imageWidth)
                .height(this.imageHeight)
                .objectFit(ImageFit.Cover)
                .borderRadius(12)
                .border({ width: 2, color: '#FF9800' })
                .id('animatedResourceImage')
                .onFinish(() => {
                  this.animationStatus = 'ResourceStr动画播放完成';
                  this.addLog('ResourceStr动画 onFinish');
                })
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
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        if (this.showAnimationOptions) {
          Column({ space: 10 }) {
            Row() {
              Text('AnimationOptions 配置')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showAnimationOptions })
                .onChange((value: boolean) => {
                  this.showAnimationOptions = value;
                })
            }
            .width('100%')

            Text('duration: 动画播放一次的时长(ms)')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Row({ space: 10 }) {
              Text('duration(ms):')
                .fontSize(14)
                .width(80)
              Slider({
                value: this.durationValue,
                min: 100,
                max: 5000,
                step: 100,
                style: SliderStyle.OutSet
              })
                .onChange((value: number) => {
                  this.durationValue = value;
                })
                .layoutWeight(1)
              Text(`${this.durationValue}`)
                .fontSize(14)
                .width(50)
            }
            .width('100%')

            Text('iterations: 播放次数，-1为无限循环')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Row({ space: 10 }) {
              Text('iterations:')
                .fontSize(14)
                .width(80)
              Slider({
                value: this.iterationsValue,
                min: -1,
                max: 10,
                step: 1,
                style: SliderStyle.OutSet
              })
                .onChange((value: number) => {
                  this.iterationsValue = value;
                })
                .layoutWeight(1)
              Text(`${this.iterationsValue}`)
                .fontSize(14)
                .width(50)
            }
            .width('100%')

            Text('autoPlay: 是否自动播放动画，默认 true')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Row({ space: 8 }) {
              Toggle({ type: ToggleType.Checkbox, isOn: this.autoPlayEnabled })
                .onChange((value: boolean) => {
                  this.autoPlayEnabled = value;
                })
              Text('autoPlay')
                .fontSize(14)
            }
            .width('100%')

            Text('stopMode: 动画停止时显示的帧，FIRST_FRAME 或 LAST_FRAME')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Row({ space: 8 }) {
              Toggle({ type: ToggleType.Checkbox, isOn: this.stopMode === AnimationStopMode.LAST_FRAME })
                .onChange((value: boolean) => {
                  this.stopMode = value ? AnimationStopMode.LAST_FRAME : AnimationStopMode.FIRST_FRAME;
                })
              Text(`stopMode: ${this.stopMode === AnimationStopMode.LAST_FRAME ? 'LAST_FRAME' : 'FIRST_FRAME'}`)
                .fontSize(14)
            }
            .width('100%')

            Button('应用配置并重建动画')
              .onClick(() => {
                let newOptions: AnimationOptions = {
                  duration: this.durationValue,
                  iterations: this.iterationsValue,
                  autoPlay: this.autoPlayEnabled,
                  stopMode: this.stopMode
                };
                if (this.pixelMaps.length > 0) {
                  this.animatedFromPixelMaps = new AnimatedDrawableDescriptor(this.pixelMaps, newOptions);
                }
                // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
                this.animatedFromResource = new AnimatedDrawableDescriptor($r('app.media.startIcon'), newOptions);
                this.addLog('配置已应用, 动画重建');
              })
              .width('100%')
              .backgroundColor('#4CAF50')
          }
          .padding(15)
          .backgroundColor('#fff')
          .borderRadius(12)
          .width('100%')
        }

        if (this.showAnimationController) {
          Column({ space: 10 }) {
            Row() {
              Text('AnimationController 动画控制')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showAnimationController })
                .onChange((value: boolean) => {
                  this.showAnimationController = value;
                })
            }
            .width('100%')

            Text('通过 getAnimationController(id) 获取控制器，id 为 Image 组件的 id 属性')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Text('控制器方法: start() / stop() / pause() / resume() / getStatus()')
              .fontSize(13)
              .fontColor('#666')
              .width('100%')

            Row({ space: 8 }) {
              Button('获取PM源 Controller')
                .onClick(() => {
                  if (this.animatedFromPixelMaps) {
                    this.animationController = this.animatedFromPixelMaps.getAnimationController('animatedPixelMapsImage');
                    this.currentControllerId = 'animatedPixelMapsImage';
                    this.animationStatus = '已获取 PM源 AnimationController';
                    this.addLog('获取PM源 Controller');
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#2196F3')

              Button('获取RS源 Controller')
                .onClick(() => {
                  if (this.animatedFromResource) {
                    this.animationController = this.animatedFromResource.getAnimationController('animatedResourceImage');
                    this.currentControllerId = 'animatedResourceImage';
                    this.animationStatus = '已获取 RS源 AnimationController';
                    this.addLog('获取RS源 Controller');
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#FF9800')
            }
            .width('100%')

            Text(`当前 Controller 绑定: ${this.currentControllerId}`)
              .fontSize(14)
              .fontColor('#2196F3')
              .width('100%')

            if (this.animationController) {
              Row({ space: 8 }) {
                Button('start()')
                  .onClick(() => {
                    this.animationController?.start();
                    this.animationStatus = '动画开始播放';
                    this.addLog('Controller start()');
                  })
                  .fontSize(13)
                  .layoutWeight(1)
                  .backgroundColor('#4CAF50')

                Button('pause()')
                  .onClick(() => {
                    this.animationController?.pause();
                    this.animationStatus = '动画暂停';
                    this.addLog('Controller pause()');
                  })
                  .fontSize(13)
                  .layoutWeight(1)
                  .backgroundColor('#FF9800')

                Button('resume()')
                  .onClick(() => {
                    this.animationController?.resume();
                    this.animationStatus = '动画继续播放';
                    this.addLog('Controller resume()');
                  })
                  .fontSize(13)
                  .layoutWeight(1)
                  .backgroundColor('#2196F3')
              }
              .width('100%')

              Row({ space: 8 }) {
                Button('stop()')
                  .onClick(() => {
                    this.animationController?.stop();
                    this.animationStatus = '动画停止(重置到首帧)';
                    this.addLog('Controller stop()');
                  })
                  .fontSize(13)
                  .layoutWeight(1)
                  .backgroundColor('#F44336')

                Button('getStatus()')
                  .onClick(() => {
                    let status = this.animationController?.getStatus();
                    this.animationStatus = `动画状态: ${status}`;
                    this.addLog(`Controller getStatus(): ${status}`);
                  })
                  .fontSize(13)
                  .layoutWeight(1)
                  .backgroundColor('#9C27B0')
              }
              .width('100%')
            }

            Text(this.animationStatus)
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

        if (this.showLoadTest) {
          Column({ space: 10 }) {
            Row() {
              Text('loadSync() / load() 加载测试')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showLoadTest })
                .onChange((value: boolean) => {
                  this.showLoadTest = value;
                })
            }
            .width('100%')

            Row({ space: 8 }) {
              Button('loadSync()')
                .onClick(() => {
                  if (this.animatedFromPixelMaps) {
                    try {
                      let result = this.animatedFromPixelMaps.loadSync();
                      this.loadSyncResult = `loadSync: ${result.imageWidth}x${result.imageHeight}px`;
                      this.addLog(`Animated loadSync: ${result.imageWidth}x${result.imageHeight}`);
                    } catch (e) {
                      this.loadSyncResult = `loadSync 失败: ${(e as BusinessError).message}`;
                      this.addLog(`Animated loadSync 失败`);
                    }
                  }
                })
                .fontSize(13)
                .layoutWeight(1)

              Button('load() 异步')
                .onClick(async () => {
                  if (this.animatedFromPixelMaps) {
                    try {
                      let result = await this.animatedFromPixelMaps.load();
                      this.loadAsyncResult = `load: ${result.imageWidth}x${result.imageHeight}px`;
                      this.addLog(`Animated load: ${result.imageWidth}x${result.imageHeight}`);
                    } catch (e) {
                      this.loadAsyncResult = `load 失败: ${(e as BusinessError).message}`;
                      this.addLog(`Animated load 失败`);
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

            Button('getPixelMap()')
              .onClick(() => {
                if (this.animatedFromPixelMaps) {
                  try {
                    let pm = this.animatedFromPixelMaps.getPixelMap();
                    this.getPixelMapResult = 'getPixelMap 成功';
                    this.addLog('Animated getPixelMap 成功');
                  } catch (e) {
                    this.getPixelMapResult = `getPixelMap 失败: ${(e as BusinessError).message}`;
                    this.addLog(`Animated getPixelMap 失败`);
                  }
                }
              })
              .width('100%')

            Text(this.getPixelMapResult)
              .fontSize(14)
              .fontColor(Color.Green)
              .width('100%')
          }
          .padding(15)
          .backgroundColor('#fff')
          .borderRadius(12)
          .width('100%')
        }

        if (this.showLifecycle) {
          Column({ space: 10 }) {
            Row() {
              Text('release() / isReleased() / invalidate()')
                .fontSize(18)
                .fontWeight(FontWeight.Medium)
                .layoutWeight(1)

              Toggle({ type: ToggleType.Checkbox, isOn: this.showLifecycle })
                .onChange((value: boolean) => {
                  this.showLifecycle = value;
                })
            }
            .width('100%')

            Row({ space: 8 }) {
              Button('release()')
                .onClick(() => {
                  if (this.animatedFromPixelMaps) {
                    this.animatedFromPixelMaps.release();
                    this.isReleased = this.animatedFromPixelMaps.isReleased();
                    this.releaseStatus = `isReleased=${this.isReleased}`;
                    this.addLog('Animated release()');
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#F44336')

              Button('isReleased()')
                .onClick(() => {
                  if (this.animatedFromPixelMaps) {
                    this.isReleased = this.animatedFromPixelMaps.isReleased();
                    this.releaseStatus = `isReleased=${this.isReleased}`;
                    this.addLog(`Animated isReleased=${this.isReleased}`);
                  }
                })
                .fontSize(13)
                .layoutWeight(1)
                .backgroundColor('#2196F3')
              
            }
            .width('100%')

            Text(this.releaseStatus)
              .fontSize(14)
              .fontColor(this.isReleased ? Color.Red : Color.Green)
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

  private async getPixelMapListFromMedia(resource: Resource): Promise<image.PixelMap[]> {
    let context = this.getUIContext().getHostContext();
    if (!context) {
      return [];
    }
    let unit8Array = await context.resourceManager.getMediaContent({
      bundleName: resource.bundleName,
      moduleName: resource.moduleName,
      id: resource.id
    });
    let imageSource = image.createImageSource(unit8Array?.buffer.slice(0, unit8Array.buffer.byteLength));
    let createPixelMapList: image.PixelMap[] = await imageSource.createPixelMapList({
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888
    });
    await imageSource.release();
    return createPixelMapList;
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
    let imageSource = image.createImageSource(unit8Array?.buffer.slice(0, unit8Array.buffer.byteLength));
    let createPixelMap: image.PixelMap = await imageSource.createPixelMap({
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888
    });
    await imageSource.release();
    return createPixelMap;
  }
}