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
import { BusinessError } from '@'@kit.BasicServicesKit';
import { image } from '@kit.ImageKit';

enum ImageSourceType {
  NETWORK = 'network',
  LOCAL = 'local',
  BASE64 = 'base64',
  PIXELMAP = 'pixelmap'
}

interface ImageSource {
  id: string;
  name: string;
  type: ImageSourceType;
  url?: string;
  resource?: Resource;
  base64?: string;
}

interface ImageLoadResult {
  success: boolean;
  width?: number;
  height?: number;
  format?: string;
  size?: number;
  loadTime?: number;
  error?: string;
}

@Entry
@Component
struct ImageExample104 {
  @State currentSource: ImageSource | undefined = undefined;
  @State imageSources: ImageSource[] = [];
  @State loadResults: Map<string, ImageLoadResult> = new Map();
  @State selectedType: ImageSourceType = ImageSourceType.NETWORK;
  @State autoResize: boolean = true;
  @State syncLoad: boolean = false;
  @State objectFit: ImageFit = ImageFit.Cover;
  @State interpolation: ImageInterpolation = ImageInterpolation.Medium;
  @State showDetails: boolean = true;
  @State testMode: boolean = false;
  @State testProgress: number = 0;
  @State pixelMapImage: PixelMap | undefined = undefined;

  private sourceTypes: ImageSourceType[] = [
    ImageSourceType.NETWORK,
    ImageSourceType.LOCAL,
    ImageSourceType.BASE64,
    ImageSourceType.PIXELMAP
  ];

  private objectFitOptions: ImageFit[] = [
    ImageFit.Cover, ImageFit.Contain, ImageFit.Fill, ImageFit.None,
    ImageFit.ScaleDown, ImageFit.Auto
  ];

  private interpolationOptions: ImageInterpolation[] = [
    ImageInterpolation.None, ImageInterpolation.Low,
    ImageInterpolation.Medium, ImageInterpolation.High
  ];

  aboutToAppear(): void {
    this.initializeImageSources();
  }

  initializeImageSources(): void {
    this.imageSources = [
      {
        id: 'network1',
        name: '网络图片1',
        type: ImageSourceType.NETWORK,
        url: 'https://xxx0'
      },
      {
        id: 'network2',
        name: '网络图片2',
        type: ImageSourceType.NETWORK,
        url: 'https://xxx1'
      },
      {
        id: 'local1',
        name: '本地资源1',
        type: ImageSourceType.LOCAL,
        resource: $r('app.media.example')
      },
      {
        id: 'local2',
        name: '本地资源2',
        type: ImageSourceType.LOCAL,
        resource: $r('app.media.loading')
      },
      {
        id: 'base64',
        name: 'Base64图片',
        type: ImageSourceType.BASE64,
        base64: 'data:image/png;base64,xxx'
      }
    ];

    this.currentSource = this.imageSources[0];
  }

  async loadImage(source: ImageSource): Promise<ImageLoadResult> {
    const startTime = Date.now();
    const result: ImageLoadResult = { success: false };

    try {
      switch (source.type) {
        case ImageSourceType.NETWORK:
          return await this.loadNetworkImage(source, startTime);
        case ImageSourceType.LOCAL:
          return await this.loadLocalImage(source, startTime);
        case ImageSourceType.BASE64:
          return await this.loadBase64Image(source, startTime);
        case ImageSourceType.PIXELMAP:
          return await this.loadPixelMapImage(source, startTime);
        default:
          result.error = 'Unknown source type';
          return result;
      }
    } catch (error) {
      result.error = `Load failed: ${error}`;
      return result;
    }
  }

  async loadNetworkImage(source: ImageSource, startTime: number): Promise<ImageLoadResult> {
    const result: ImageLoadResult = { success: false };

    return new Promise((resolve) => {
      http.createHttp().request(source.url!, {
        method: http.RequestMethod.GET,
        connectTimeout: 30000,
        readTimeout: 30000,
        expectDataType: http.HttpDataType.ARRAY_BUFFER
      }, (error: BusinessError, data: http.HttpResponse) => {
        if (error) {
          result.error = `HTTP error: ${error.code} - ${error.message}`;
          resolve(result);
          return;
        }

        try {
          const imgData: ArrayBuffer = data.result as ArrayBuffer;
          result.size = imgData.byteLength;

          const imgSource: image.ImageSource = image.createImageSource(imgData);
          const imgInfo = imgSource.getImageInfoSync();

          result.success = true;
          result.width = imgInfo.size.width;
          result.height = imgInfo.size.height;
          result.format = this.getImageFormat(imgInfo);
          result.loadTime = Date.now() - startTime;

          const options: image.CreatePixelMapOptions = {
            desiredPixelFormat: image.PixelMapFormat.RGBA_8888
          };

          imgSource.createPixelMap(options).then((pixelMap: PixelMap) => {
            if (source.id === this.currentSource?.id) {
              this.pixelMapImage = pixelMap;
            }
            imgSource.release();
          }).catch(() => {
            imgSource.release();
          });

          resolve(result);
        } catch (decodeError) {
          result.error = `Decode failed: ${decodeError}`;
          resolve(result);
        }
      });
    });
  }

  async loadLocalImage(source: ImageSource, startTime: number): Promise<ImageLoadResult> {
    const result: ImageLoadResult = { success: false };

    try {
      const unit8Array = await this.getUIContext()
        .getHostContext()
        ?.resourceManager
        ?.getMediaContent(source.resource!.id);

      if (!unit8Array) {
        result.error = 'Failed to get media content';
        return result;
      }

      result.size = unit8Array.buffer.byteLength;

      const imgSource: image.ImageSource = image.createImageSource(
        unit8Array.buffer.slice(0, unit8Array.buffer.byteLength)
      );

      const imgInfo = imgSource.getImageInfoSync();

      result.success = true;
      result.width = imgInfo.size.width;
      result.height = imgInfo.size.height;
      result.format = this.getImageFormat(imgInfo);
      result.loadTime = Date.now() - startTime;

      const options: image.CreatePixelMapOptions = {
        desiredPixelFormat: image.PixelMapFormat.RGBA_8888
      };

      const pixelMap = await imgSource.createPixelMap(options);
      this.pixelMapImage = pixelMap;
      await imgSource.release();

      return result;
    } catch (error) {
      result.error = `Load failed: ${error}`;
      return result;
    }
  }

  async loadBase64Image(source: ImageSource, startTime: number): Promise<ImageLoadResult> {
    const result: ImageLoadResult = { success: false };

    try {
      const base64Data = source.base64!.split(',')[1];
      const binaryString = atob(base64Data);
      const bytes = new Uint8Array(binaryString.length);

      for (let i = 0; i < binaryString.length; i++) {
        bytes[i] = binaryString.charCodeAt(i);
      }

      const imgData = bytes.buffer;
      result.size = imgData.byteLength;

      const imgSource: image.ImageSource = image.createImageSource(imgData);
      const imgInfo = imgSource.getImageInfoSync();

      result.success = true;
      result.width = imgInfo.size.width;
      result.height = imgInfo.size.height;
      result.format = this.getImageFormat(imgInfo);
      result.loadTime = Date.now() - startTime;

      const options: image.CreatePixelMapOptions = {
        desiredPixelFormat: image.PixelMapFormat.RGBA_8888
      };

      const pixelMap = await imgSource.createPixelMap(options);
      this.pixelMapImage = pixelMap;
      await imgSource.release();

      return result;
    } catch (error) {
      result.error = `Base64 decode failed: ${error}`;
      return result;
    }
  }

  async loadPixelMapImage(source: ImageSource, startTime: number): Promise<ImageLoadResult> {
    const result: ImageLoadResult = { success: false };

    try {
      if (!this.pixelMapImage) {
        result.error = 'No PixelMap available';
        return result;
      }

      result.success = true;
      result.width = this.pixelMapImage.getImageInfo().size.width;
      result.height = this.pixelMapImage.getImageInfo().size.height;
      result.format = 'RGBA_8888';
      result.loadTime = Date.now() - startTime;

      return result;
    } catch (error) {
      result.error = `PixelMap load failed: ${error}`;
      return result;
    }
  }

  getImageFormat(imageInfo: image.ImageInfo): string {
    const formatMap: Record<number, string> = {
      [image.ImageFormat.UNKNOWN]: 'UNKNOWN',
      [image.ImageFormat.JPEG]: 'JPEG',
      [image.ImageFormat.PNG]: 'PNG',
      [image.ImageFormat.GIF]: 'GIF',
      [image.ImageFormat.BMP]: 'BMP',
      [image.ImageFormat.ICO]: 'ICO',
      [image.ImageFormat.WEBP]: 'WEBP',
      [image.ImageFormat.SVG]: 'SVG'
    };

    return formatMap[imageInfo.imageFormat] || 'UNKNOWN';
  }

  selectSource(source: ImageSource): void {
    this.currentSource = source;
    this.loadImage(source).then((result) => {
      this.loadResults.set(source.id, result);
    });
  }

  startTestMode(): void {
    this.testMode = true;
    this.testProgress = 0;

    const testNext = async () => {
      if (!this.testMode) {
        return;
      }

      const index = Math.floor(this.testProgress * this.imageSources.length);
      if (index < this.imageSources.length) {
        this.selectSource(this.imageSources[index]);
        await new Promise(resolve => setTimeout(resolve, 500));
      }

      this.testProgress += 0.1;
      if (this.testProgress <= 1) {
        setTimeout(testNext, 100);
      } else {
        this.testMode = false;
        this.testProgress = 0;
      }
    };

    testNext();
  }

  getSourceTypeIcon(type: ImageSourceType): string {
    const iconMap: Record<ImageSourceType, string> = {
      [ImageSourceType.NETWORK]: '🌐',
      [ImageSourceType.LOCAL]: '📁',
      [ImageSourceType.BASE64]: '📝',
      [ImageSourceType.PIXELMAP]: '🖼️'
    };
    return iconMap[type] || '❓';
  }

  build() {
    Column() {
      this.buildHeader();
      this.buildMainContent();
      this.buildControlPanel();
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F8F9FA');
  }

  @Builder
  buildHeader() {
    Column() {
      Text('图片加载测试工具')
        .fontSize(28)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.White)
        .margin({ bottom: 8 });

      Text('支持多种图片源类型的加载测试')
        .fontSize(14)
        .fontColor('#E0E0E0')
        .margin({ bottom: 16 });

      Row() {
        Button('开始测试')
          .type(ButtonType.Normal)
          .backgroundColor('#4CAF50')
          .onClick(() => {
            this.startTestMode();
          });

        if (this.testMode) {
          Progress({ value: this.testProgress * 100, total: 100, type: ProgressType.Linear })
            .width(200)
            .height(8)
            .color('#2196F3')
            .margin({ left: 16 });
        }
      }
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#1976D2');
  }

  @Builder
  buildMainContent() {
    Row() {
      this.buildSourceList();
      this.buildImagePreview();
    }
    .width('100%')
    .layoutWeight(1)
    .padding(16);
  }

  @Builder
  buildSourceList() {
    Column() {
      Text('图片源列表')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 12 });

      List({ space: 8 }) {
        ForEach(this.imageSources, (source: ImageSource) => {
          ListItem() {
            this.buildSourceItem(source);
          }
        }, (source: ImageSource) => source.id);
      }
      .width('100%')
      .layoutWeight(1);
    }
    .width(280)
    .height('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12);
  }

  @Builder
  buildSourceItem(source: ImageSource) {
    Column() {
      Row() {
        Text(this.getSourceTypeIcon(source.type))
          .fontSize(20)
          .margin({ right: 8 });

        Text(source.name)
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .layoutWeight(1);

        if (this.loadResults.has(source.id)) {
          const result = this.loadResults.get(source.id)!;
          if (result.success) {
            Text('✓')
              .fontSize(16)
              .fontColor('#4CAF50');
          } else {
            Text('✗')
              .fontSize(16)
              .fontColor('#F44336');
          }
        }
      }
      .width('100%')
      .margin({ bottom: 4 });

      if (this.loadResults.has(source.id)) {
        const result = this.loadResults.get(source.id)!;
        this.buildLoadResultInfo(result);
      }
    }
    .width('100%')
    .padding(12)
    .backgroundColor(
      this.currentSource?.id === source.id ? '#E3F2FD' : '#F5F5F5'
    )
    .borderRadius(8)
    .onClick(() => {
      this.selectSource(source);
    });
  }

  @Builder
  buildLoadResultInfo(result: ImageLoadResult) {
    Column() {
      if (result.success) {
        Row() {
          Text('尺寸: ')
            .fontSize(12)
            .fontColor('#666666');
          Text(`${result.width}x${result.height}`)
            .fontSize(12)
            .fontColor(Color.Black)
            .margin({ left: 4 });
        }
        .margin({ bottom: 4 });

        Row() {
          Text('格式: ')
            .fontSize(12)
            .fontColor('#666666');
          Text(result.format || 'UNKNOWN')
            .fontSize(12)
            .fontColor(Color.Black)
            .margin({ left: 4 });
        }
        .margin({ bottom: 4 });

        if (result.size) {
          Row() {
            Text('大小: ')
              .fontSize(12)
              .fontColor('#666666');
            Text(`${(result.size / 1024).toFixed(2)}KB`)
              .fontSize(12)
              .fontColor(Color.Black)
              .margin({ left: 4 });
          }
          .margin({ bottom: 4 });
        }

        if (result.loadTime) {
          Row() {
            Text('耗时: ')
              .fontSize(12)
              .fontColor('#666666');
            Text(`${result.loadTime}ms`)
              .fontSize(12)
              .fontColor(Color.Black)
              .margin({ left: 4 });
          }
        }
      } else if (result.error) {
        Text(result.error)
          .fontSize(11)
          .fontColor('#F44336')
          .maxLines(2)
          .textOverflow({ overflow: TextOverflow.Ellipsis });
      }
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(4);
  }

  @Builder
  buildImagePreview() {
    Column() {
      Text('图片预览')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 12 });

      if (this.currentSource) {
        Column() {
          Image(this.pixelMapImage)
            .width('100%')
            .height('100%')
            .objectFit(this.objectFit)
            .interpolation(this.interpolation)
            .autoResize(this.autoResize)
            .syncLoad(this.syncLoad)
            .alt($r('app.media.placeholder'))
            .onComplete((event) => {
              console.info(`Image complete: ${event.width}x${event.height}`);
            })
            .onError((error) => {
              console.error(`Image error: ${error.message}`);
            })
            .borderRadius(8)
            .shadow({
              radius: 8,
              color: '#0000001A',
              offsetX: 0,
              offsetY: 2
            });

          if (this.showDetails) {
            this.buildImageDetails();
          }
        }
        .layoutWeight(1);
      } else {
        Column() {
          Text('请选择图片源')
            .fontSize(16)
            .fontColor('#999999');
        }
        .width('100%')
        .height('100%')
        .justifyContent(FlexAlign.Center);
      }
    }
    .layoutWeight(1)
    .height('100%')
    .padding(12)
    .backgroundColor(Color.White)
    .borderRadius(12);
  }

  @Builder
  buildImageDetails() {
    Column() {
      Text('当前图片源')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 8 });

      Row() {
        Text('类型: ')
          .fontSize(12)
          .fontColor('#666666');
        Text(this.currentSource!.type)
          .fontSize(12)
          .fontColor(Color.Black)
          .margin({ left: 4 });
      }
      .margin({ bottom: 4 });

      Row() {
        Text('名称: ')
          .fontSize(12)
          .fontColor('#666666');
        Text(this.currentSource!.name)
          .fontSize(12)
          .fontColor(Color.Black)
          .margin({ left: 4 });
      }
      .margin({ bottom: 4 });

      if (this.currentSource!.url) {
        Row() {
          Text('URL: ')
            .fontSize(12)
            .fontColor('#666666');
          Text(this.currentSource!.url)
            .fontSize(12)
            .fontColor(Color.Black)
            .margin({ left: 4 })
            .maxLines(1)
            .textOverflow({ overflow: TextOverflow.Ellipsis });
        }
        .margin({ bottom: 4 });
      }
    }
    .width('100%')
    .padding(12)
    .margin({ top: 12 })
    .backgroundColor('#F5F5F5')
    .borderRadius(8);
  }

  @Builder
  buildControlPanel() {
    Column() {
      Text('加载设置')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 12 });

      Row() {
        Column() {
          Text('自适应缩放')
            .fontSize(14)
            .margin({ bottom: 8 });
          Toggle({ type: ToggleType.Switch, isOn: this.autoResize })
            .onChange((isOn: boolean) => {
              this.autoResize = isOn;
            });
        }
        .layoutWeight(1);

        Column() {
          Text('同步加载')
            .fontSize(14)
            .margin({ bottom: 8 });
          Toggle({ type: ToggleType.Switch, isOn: this.syncLoad })
            .onChange((isOn: boolean) => {
              this.syncLoad = isOn;
            });
        }
        .layoutWeight(1);
      }
      .width('100%')
      .margin({ bottom: 16 });

      Row() {
        Column() {
          Text('填充模式')
            .fontSize(14)
            .margin({ bottom: 8 });
          Select(this.objectFitOptions)
            .selected(this.objectFit)
            .value('ImageFit')
            .onSelect((index: number) => {
              this.objectFit = this.objectFitOptions[index];
            });
        }
        .layoutWeight(1);

        Column() {
          Text('插值质量')
            .fontSize(14)
            .margin({ bottom: 8 });
          Select(this.interpolationOptions)
            .selected(this.interpolation)
            .value('ImageInterpolation')
            .onSelect((index: number) => {
              this.interpolation = this.interpolationOptions[index];
            });
        }
        .layoutWeight(1);
      }
      .width('100%');

      Row() {
        Toggle({ type: ToggleType.Switch, isOn: this.showDetails })
          .onChange((isOn: boolean) => {
            this.showDetails = isOn;
          });
        Text('显示详情')
          .fontSize(14)
          .margin({ left: 8 });
      }
      .margin({ top: 16 });
    }
    .width('100%')
    .padding(16)
    .backgroundColor(Color.White)
    .borderRadius({ topLeft: 16, topRight: 16 });
  }
}
