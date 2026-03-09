/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { http } from '@kit.NetworkKit';
import { image } from '@kit.ImageKit';
import { rcp } from '@kit.RemoteCommunicationKit';

/**
 * Image 高级特性综合示例
 * 演示 Image 组件的各种高级特性
 */
@Entry
@Component
struct ImageAdvancedFeaturesExample {
  @State currentTab: number = 0;
  @State pixelMapImg: PixelMap | undefined = undefined;
  @State loadProgress: number = 0;
  @State errorMessage: string = '';
  @State imageInfo: string = '';
  @State showBorders: boolean = true;
  @State showShadows: boolean = false;
  @State enableAnimation: boolean = true;

  tabs: string[] = ['基础加载', '网络图片', 'PixelMap', '高级特性', '动画效果'];

  imageSources: string[] = [
    'https://xxx',
    'https://xxx',
    'https://xxx',
    'https://xxx'
  ];

  aboutToAppear() {
    this.loadPixelMap();
  }

  async loadPixelMap() {
    try {
      const resManager = this.getUIContext().getHostContext()?.resourceManager;
      if (!resManager) {
        return;
      }

      const unit8Array = await resManager.getMediaContent($r('app.media.img').id);
      if (!unit8Array) {
        return;
      }

      const imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength));
      const pixelMap = await imageSource.createPixelMap({
        desiredPixelFormat: image.PixelMapFormat.RGBA_8888
      });
      await imageSource.release();

      this.pixelMapImg = pixelMap;
      this.imageInfo = `PixelMap 加载成功: ${pixelMap.getImageInfo().size.width}x${pixelMap.getImageInfo().size.height}`;
    } catch (error) {
      this.errorMessage = `PixelMap 加载失败: ${error}`;
    }
  }

  @Builder
  BasicLoadingTab() {
    Column({ space: 15 }) {
      Text('基础图片加载')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      // 本地资源图片
      Text('本地资源图片')
        .fontSize(14)
        .fontColor(0x666666)
      Image($r('app.media.img'))
        .width(200)
        .height(200)
        .border(this.showBorders ? { width: 2, color: Color.Blue } : {})
        .shadow(this.showShadows ? {
          radius: 10,
          color: 0x1A000000,
          offsetX: 5,
          offsetY: 5
        } : {})

      // PNG 格式
      Text('PNG 格式图片')
        .fontSize(14)
        .fontColor(0x666666)
      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .border(this.showBorders ? { width: 2, color: Color.Green } : {})

      // JPG 格式
      Text('JPG 格式图片')
        .fontSize(14)
        .fontColor(0x666666)
      Image($r('app.media.jpg'))
        .width(200)
        .height(200)
        .border(this.showBorders ? { width: 2, color: Color.Orange } : {})

      // SVG 格式
      Text('SVG 格式图片')
        .fontSize(14)
        .fontColor(0x666666)
      Image($r('app.media.svg'))
        .width(200)
        .height(200)
        .border(this.showBorders ? { width: 2, color: Color.Pink } : {})
        .fillColor(Color.Blue)

      // GIF 格式
      Text('GIF 格式图片')
        .fontSize(14)
        .fontColor(0x666666)
      Image($r('app.media.gif'))
        .width(200)
        .height(200)
        .border(this.showBorders ? { width: 2, color: Color.Purple } : {})
    }
    .padding(15)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  NetworkImageTab() {
    Column({ space: 15 }) {
      Text('网络图片加载')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      ForEach(this.imageSources, (url: string, index: number) => {
        Column({ space: 5 }) {
          Text(`网络图片 ${index + 1}`)
            .fontSize(14)
            .fontColor(0x666666)

          Image(url)
            .width(200)
            .height(200)
            .border(this.showBorders ? { width: 2, color: Color.Gray } : {})
            .objectFit(ImageFit.Cover)
            .alt($r('app.media.placeholder'))
            .onComplete((event) => {
              console.info(`图片 ${index + 1} 加载成功: ${event.width}x${event.height}`);
            })
            .onError((error) => {
              console.error(`图片 ${index + 1} 加载失败: ${error.message}`);
            })
        }
      })
    }
    .padding(15)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  PixelMapTab() {
    Column({ space: 15 }) {
      Text('PixelMap 图片')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      if (this.pixelMapImg) {
        Text(this.imageInfo)
          .fontSize(14)
          .fontColor(Color.Green)

        Image(this.pixelMapImg)
          .width(300)
          .height(300)
          .border(this.showBorders ? { width: 2, color: Color.Red } : {})
          .objectFit(ImageFit.Contain)

        // 使用不同 objectFit
        Row({ space: 10 }) {
          Column({ space: 5 }) {
            Text('Cover')
              .fontSize(12)
            Image(this.pixelMapImg)
              .width(150)
              .height(150)
              .objectFit(ImageFit.Cover)
              .border({ width: 1, color: Color.Gray })
          }

          Column({ space: 5 }) {
            Text('Contain')
              .fontSize(12)
            Image(this.pixelMapImg)
              .width(150)
              .height(150)
              .objectFit(ImageFit.Contain)
              .border({ width: 1, color: Color.Gray })
          }

          Column({ space: 5 }) {
            Text('Fill')
              .fontSize(12)
            Image(this.pixelMapImg)
              .width(150)
              .height(150)
              .objectFit(ImageFit.Fill)
              .border({ width: 1, color: Color.Gray })
          }
        }
      } else {
        Text('PixelMap 加载中...')
          .fontSize(14)
          .fontColor(0x999999)

        LoadingProgress()
          .width(200)
          .height(4)
          .color(0x007DFF)

        if (this.errorMessage) {
          Text(this.errorMessage)
            .fontSize(14)
            .fontColor(Color.Red)
        }
      }
    }
    .padding(15)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  AdvancedFeaturesTab() {
    Column({ space: 15 }) {
      Text('高级特性')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      // 不同 objectFit 示例
      Text('objectFit 属性')
        { .fontSize(14).fontColor(0x666666) }
      Row({ space: 10 }) {
        ForEach([ImageFit.Cover, ImageFit.Contain, ImageFit.Fill, ImageFit.None], (fit: ImageFit) => {
          Column({ space: 5 }) {
            Text(`${fit}`)
              .fontSize(12)
            Image($r('app.media.img'))
              .width(100)
              .height(100)
              .objectObjectFit(fit)
              .border({ width: 1, color: Color.Gray })
          }
        })
      }

      // 不同 interpolation 示例
      Text('interpolation 属性')
        .fontSize(14)
        .fontColor(0x666666)
      Row({ space: 10 }) {
        ForEach([ImageInterpolation.None, ImageInterpolation.Low, ImageInterpolation.Medium, ImageInterpolation.High], (interp: ImageInterpolation) => {
          Column({ space: 5 }) {
            Text(`${interp}`)
              .fontSize(12)
            Image($r('app.media.img'))
              .width(100)
              .height(100)
              .interpolation(interp)
              .border({ width: 1, color: Color.Gray })
          }
        })
      }

      // 不同 renderMode 示例
      Text('renderMode 属性')
        .fontSize(14)
        .fontColor(0x666666)
      Row({ space: 10 }) {
        Column({ space: 5 }) {
          Text('Original')
            .fontSize(12)
          Image($r('app.media.img'))
            .width(150)
            .height(150)
            .renderMode(ImageRenderMode.Original)
            .border({ width: 1, color: Color.Gray })
        }

        Column({ space: 5 }) {
          Text('Template')
            .fontSize(12)
          Image($r('app.media.img'))
            .width(150)
            .height(150)
            .renderMode(ImageRenderMode.Template)
            .border({ width: 1, color: Color.Gray })
        }
      }

      // sourceSize 示例
      Text('sourceSize 属性')
        .fontSize(14)
        .fontColor(0x666666)
      Row({ space: 10 }) {
        Column({ space: 5 }) {
          Text('原始大小')
            .fontSize(12)
          Image($r('app.media.img'))
            .width(200)
            .height(200)
            .border({ width: 1, color: Color.Gray })
        }

        Column({ space: 5 }) {
          Text('解码为 100x100')
            .fontSize(12)
          Image($r('app.media.img'))
            .width(200)
            .height(200)
            .sourceSize({ width: 100, height: 100 })
            .border({ width: 1, color: Color.Gray })
        }
      }
    }
    .padding(15)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  AnimationEffectsTab() {
    Column({ space: 15 }) {
      Text('动画效果')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      // 旋转动画
      Text('旋转动画')
        .fontSize(14)
        .fontColor(0x666666)
      Image($r('app.media.gif'))
        .width(200)
        .height(200)
        .border(this.showBorders ? { width: 2, color: Color.Blue } : {})
        .animation({
          duration: 2000,
          curve: Curve.EaseInOut
        })

      // 缩放动画
      Text('缩放动画')
        .fontSize(14)
        .fontColor(0x666666)
      Image($r('app.media.img'))
        .width(this.enableAnimation ? 200 : 150)
        .height(this.enableAnimation ? 200 : 150)
        .border(this.showBorders ? { width: 2, color: Color.Green } : {})
        .animation({
          duration: 1000,
          curve: Curve.SpringMotion
        })

      // 淡合动画
      Text('淡入淡出')
        .fontSize(14)
        .fontColor(0x666666)
      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .opacity(this.enableAnimation ? 1.0 : 0.5)
        .border(this.showBorders ? { width: 2, color: Color.Orange } : {})
        .animation({
          duration: 1500,
          curve: Curve.FastOutSlowIn
        })

      // 位移动画
      Text('位移动画')
        .fontSize(14)
        .fontColor(0x666666)
      Image($r('app.media.jpg'))
        .width(200)
        .height(200)
        .translate({ x: this.enableAnimation ? 50 : 0, y: 0 })
        .border(this.showBorders ? { width: 2, color: Color.Pink } : {})
        .animation({
          duration: 1200,
          curve: Curve.EaseInOutCubic
        })

      // 组合动画
      Text('组合动画')
        .fontSize(14)
        .fontColor(0x666666)
      Image($r('app.media.svg'))
        .width(this.enableAnimation ? 200 : 150)
        .height(this.enableAnimation ? 200 : 150)
        .rotate({ angle: this.enableAnimation ? 45 : 0 })
        .scale({ x: this.enableAnimation ? 1.2 : 1.0, y: this.enableAnimation ? 1.2 : 1.0 })
        .border(this.showBorders ? { width: 2, color: Color.Purple } : {})
        .animation({
          duration: 2000,
          curve: Curve.Smooth
        })

      Button('切换动画状态')
        .onClick(() => {
          this.enableAnimation = !this.enableAnimation;
        })
    }
    .padding(15)
    .alignItems(HorizontalAlign.Start)
  }

  build() {
    Column() {
      Text('Image 高级特性综合示例')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      // 控制面板
      Row({ space: 20 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.showBorders })
          .onChange((isOn: boolean) => {
            this.showBorders = isOn;
          })
        Text('显示边框')

        Toggle({ type: ToggleType.Switch, isOn: this.showShadows })
          .onChange((isOn: boolean) => {
            this.showShadows = isOn;
          })
        Text('显示阴影')
      }
      .margin({ bottom: 15 })

      // 标签页
      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          this.BasicLoadingTab()
        }
        .tabBar(this.tabs[0])

        TabContent() {
          this.NetworkImageTab()
        }
        .tabBar(this.tabs[1])

        TabContent() {
          this.PixelMapTab()
        }
        .tabBar(this.tabs[2])

        TabContent() {
          this.AdvancedFeaturesTab()
        }
        .tabBar(this.tabs[3])

        TabContent() {
          this.AnimationEffectsTab()
        }
        .tabBar(this.tabs[4])
      }
      .barHeight(50)
      .animationDuration(300)

      // 底部信息
      if (this.errorMessage) {
        Text(this.errorMessage)
          .fontSize(14)
          .fontColor(Color.Red)
          .padding(10)
          .backgroundColor(0xFFEBEE)
          .borderRadius(5)
          .margin({ top: 10 })
      }
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(0xF5F5F5)
  }
}
