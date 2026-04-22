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

import { image } from '@kit.ImageKit';
import { matrix4 } from '@kit.ArkGraphics2D';

/**
 * Image 性能优化示例
 * 演示如何优化 Image 组件的性能
 */
@Entry
@Component
struct ImagePerformanceExample {
  @State useSourceSize: boolean = true;
  @State useAutoResize: boolean = true;
  @State useSyncLoad: boolean = false;
  @State useLowInterpolation: boolean = true;
  @State currentStrategy: string = 'balanced';
  @State cacheEnabled: boolean = true;
  @State lazyLoadEnabled: boolean = true;
  @State imageCount: number = 10;
  @State loadTime: number = 0;
  @State memoryUsage: string = '';

  performanceStrategies: string[] = [
    'balanced',
    'quality',
    'speed'
  ];

  strategyDescriptions: Record<string, string> = {
    'balanced': '平衡模式 - 在质量和性能之间取得平衡',
    'quality': '质量优先 - 使用高质量渲染，适合高清图片',
    'speed': '速度优先 - 使用快速渲染，适合大量小图'
  };

  aboutToAppear() {
    this.testPerformance();
  }

  async testPerformance() {
    const startTime = Date.now();

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

      const info = pixelMap.getImageInfo();
      const estimatedMemory = info.size.width * info.size.height * 4;
      this.memoryUsage = `预估内存使用: ${(estimatedMemory / 1024).toFixed(2)} KB`;

      await pixelMap.release();

      const endTime = Date.now();
      this.loadTime = endTime - startTime;
    } catch (error) {
      console.error(`性能测试失败: ${error}`);
    }
  }

  @Builder
  PerformanceImageCard(index: number, strategy: string) {
    Column({ space: 8 }) {
      Text(`图片 ${index + 1}`)
        .fontSize(12)
        .fontColor(0x666666)

      Image($r(`app.media.img`))
        .width(100)
        .height(100)
        .borderRadius(8)
        .objectFit(ImageFit.Cover)
        .sourceSize(this.useSourceSize ? { width: 100, height: 100 } : undefined)
        .autoResize(this.useAutoResize)
        .syncLoad(this.useSyncLoad)
        .interpolation(this.useLowInterpolation ? ImageInterpolation.Low : ImageInterpolation.High)
        .alt($r('app.media.placeholder'))
        .onComplete((event) => {
          console.info(`图片 ${index + 1} 加载完成: ${event.width}x${event.height}`);
        })
        .onError((error) => {
          console.error(`图片 ${index + 1} 加载失败: ${error.message}`);
        })
    }
    .padding(10)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
    .shadow({ radius: 4, color: 0x1A000000, offsetX: 0, offsetY: 2 })
  }

  @Builder
  OptimizationTip(title: string, description: string, benefitText: string) {
    Column({ space: 5 }) {
      Text(title)
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)

      Text(description)
        .fontSize(12)
        .fontColor(0x666666)
        .lineHeight(18)

      Text(benefitText)
        .fontSize(12)
        .fontColor(0x007DFF)
        .fontWeight(FontWeight.Medium)
    }
    .padding(12)
    .backgroundColor(0xF0F8FF)
    .borderRadius(8)
    .border({ width: 1, color: 0x007DFF })
  }

  build() {
    Column() {
      Text('Image 性能优化示例')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Scroll() {
        Column({ space: 20 }) {
          // 性能统计
          Column({ space: 10 }) {
            Text('性能统计')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)

            Row({ space: 20 }) {
              Column({ space: 5 }) {
                Text('加载时间')
                  .fontSize(12)
                  .fontColor(0x666666)
                Text(`${this.loadTime} ms`)
                  .fontSize(20)
                  .fontWeight(FontWeight.Bold)
                  .fontColor(Color.Green)
              }

              Column({ space: 5 }) {
                Text('内存使用')
                  .fontSize(12)
                  .fontColor(0x666666)
                Text(this.memoryUsage)
                  .fontSize(14)
                  .fontWeight(FontWeight.Medium)
                  .fontColor(Color.Orange)
              }
            }
          }
          .padding(15)
          .backgroundColor(0xFFFFFF)
          .borderRadius(10)
          .shadow({ radius: 8, color: 0x1A000000, offsetX: 0, offsetY: 4 })

          // 优化策略
          Column({ space: 15 }) {
            Text('优化策略')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)

            // sourceSize 优化
            this.OptimizationTip(
              '使用 sourceSize',
              '指定图片解码尺寸，避免解码过大图片',
              '减少内存占用，提升加载速度'
            )

            // autoResize 优化
            this.OptimizationTip(
              '启用 autoResize',
              '根据显示区域自动调整图片大小',
              '节省内存，提升渲染性能'
            )

            // interpolation 优化
            this.OptimizationTip(
              '使用低质量插值',
              '对于小图或缩略图使用 Low 插值',
              '减少 GPU 负担，提升滚动性能'
            )

            // syncLoad 优化
            this.OptimizationTip(
              '同步加载',
              '对于关键图片使用同步加载',
              '避免闪烁，提升用户体验'
            )

            // 缓存策略
            this.OptimizationTip(
              '启用图片缓存',
              '系统自动缓存已加载的图片',
              '避免重复加载，减少网络请求'
            )
          }
          .padding(15)
          .backgroundColor(0xF5F5F5)
          .borderRadius(10)

          // 当前策略配置
          Column({ space: 15 }) {
            Text('当前配置')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)

            Row({ space: 20 }) {
              Toggle({ type: ToggleType.Switch, isOn: this.useSourceSize })
                .onChange((isOn: boolean) => {
                  this.useSourceSize = isOn;
                })
              Text('使用 sourceSize')
                .fontSize(14)
            }

            Row({ space: 20 }) {
              Toggle({ type: ToggleType.Switch, isOn: this.useAutoResize })
                .onChange((isOn: boolean) => {
                  this.useAutoResize = isOn;
                })
              Text('使用 autoResize')
                .fontSize(14)
            }

            Row({ space: 20 }) {
              Toggle({ type: ToggleType.Switch, isOn: this.useLowInterpolation })
                .onChange((isOn: boolean) => {
                  this.useLowInterpolation = isOn;
                })
              Text('使用低质量插值')
                .fontSize(14)
            }

            Row({ space: 20 }) {
              Toggle({ type: ToggleType.Switch, isOn: this.useSyncLoad })
                .onChange((isOn: boolean) => {
                  this.useSyncLoad = isOn;
                })
              Text('使用同步加载')
                .fontSize(14)
            }

            Row({ space: 20 }) {
              Toggle({ type: ToggleType.Switch, isOn: this.cacheEnabled })
                .onChange((isOn: boolean) => {
                  this.cacheEnabled = isOn;
                })
              Text('启用缓存')
                .fontSize(14)
            }

            Row({ space: 20 }) {
              Toggle({ type: ToggleType.Switch, isOn: this.lazyLoadEnabled })
                .onChange((isOn: boolean) => {
                  this.lazyLoadEnabled = isOn;
                })
              Text('懒加载')
                .fontSize(14)
            }
          }
          .padding(15)
          .backgroundColor(0xFFFFFF)
          .borderRadius(10)
          .shadow({ radius: 8, color: 0x1A000000, offsetX: 0, offsetY: 4 })

          // 图片数量控制
          Column({ space: 10 }) {
            Text('图片数量: ' + this.imageCount)
              .fontSize(16)
              .fontWeight(FontWeight.Medium)

            Slider({
              value: this.imageCount,
              min: 1,
              max: 50,
              step: 1
            })
              .width('100%')
              .onChange((value: number) => {
                this.imageCount = value;
              })
          }
          .padding(15)
          .backgroundColor(0xF0F8FF)
          .borderRadius(10)

          // 性能测试结果
          Column({ space: 10 }) {
            Text('性能测试结果')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)

            Text(`当前策略: ${this.strategyDescriptions[this.currentStrategy]}`)
              .fontSize(14)
              .lineHeight(20)

            if (this.loadTime > 0) {
              Text(`平均加载时间: ${(this.loadTime / this.imageCount).toFixed(2)} ms/张`)
                .fontSize(14)
                .fontColor(Color.Green)
            }

            if (this.memoryUsage) {
              Text(this.memoryUsage)
                .fontSize(14)
                .fontColor(Color.Orange)
            }
          }
          .padding(15)
          .backgroundColor(0xE8F5E9)
          .borderRadius(10)

          // 图片网格
          Column({ space: 10 }) {
            Text('图片网格 (应用当前优化配置)')
              .fontSize(16)
              .fontWeight(FontWeight.Medium)

            Grid() {
              ForEach(Array.from({ length: this.imageCount }, (_: number, index: number) => {
                GridItem() {
                  this.PerformanceImageCard(index, this.currentStrategy)
                }
              })
            }
            .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
            .rowsGap(10)
            .columnsGap(10)
            .padding(10)
          }
          .backgroundColor(0xFAFAFA)
          .borderRadius(10)
          .shadow({ radius: 8, color: 0x1A000000, offsetX: 0, offsetY: 4 })

          // 重新测试按钮
          Button('重新测试性能')
            .width('100%')
            .height(50)
            .fontSize(16)
            .backgroundColor(0x007DFF)
            .onClick(() => {
              this.testPerformance();
            })
        }
        .padding(20)
      }
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(0xF5F5F5)
  }
}
