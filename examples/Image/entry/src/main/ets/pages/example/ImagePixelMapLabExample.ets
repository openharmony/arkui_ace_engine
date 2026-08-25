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
import { BusinessError } from '@kit.BasicServicesKit';

/**
 * ========================================
 * 业务场景：PixelMap 图片处理实验
 * ========================================
 * 功能说明:
 * 本示例演示如何使用 Image Kit 的 PixelMap 对图片进行编程级处理，
 * 并将处理结果作为 Image 组件的数据源进行展示。
 *
 * 涉及的 Image / Image Kit API:
 * 1. Image(src: PixelMap) - 以像素图为数据源渲染
 * 2. image.createImageSource - 从资源创建图片解码源
 * 3. image.createPixelMap(options) - 按指定参数解码为 PixelMap
 * 4. PixelMap.getImageInfo - 获取像素图尺寸与格式信息
 * 5. PixelMap.readPixelsToBuffer / writePixelsToBuffer - 像素级读写
 * 6. image.createPixelMap(opts) - 程序化动态生成像素图（渐变/棋盘）
 * 7. objectFit / interpolation - 显示优化
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 图片编辑：滤镜、马赛克、亮度调整
 * - 动态绘图：生成验证码、渐变背景、占位图
 * - 图像分析：读取像素进行二次处理
 * - 头像生成：根据用户标识动态生成图案
 */

interface DecodeOption {
  name: string;
  width: number;
  height: number;
  format: image.PixelMapFormat;
}

@Entry
@Component
struct ImagePixelMapLabExample {
  @State sourcePixelMap: PixelMap | undefined = undefined;
  @State processedPixelMap: PixelMap | undefined = undefined;
  @State generatedPixelMap: PixelMap | undefined = undefined;
  @State logText: string = '点击下方按钮开始处理图片';
  @State imageWidth: number = 0;
  @State imageHeight: number = 0;
  @State currentFilter: string = '原图';
  @State generatingType: number = 0;
  @State busy: boolean = false;
  @State decodeScale: number = 1;

  private filters: string[] = ['原图', '反色', '灰度', '暖色调', '冷色调', '高亮', '暗调', '马赛克'];
  private generateTypes: string[] = ['线性渐变', '径向渐变', '棋盘格', '彩虹条纹'];

  aboutToAppear(): void {
    this.decodeFromResource();
  }

  /**
   * 从 media 资源解码为 PixelMap
   */
  private decodeFromResource(): void {
    this.busy = true;
    this.appendLog('开始从资源解码 PixelMap...');
    const ctx = this.getUIContext().getHostContext();
    ctx?.resourceManager?.getMediaContent($r('app.media.svg').id).then((data: Uint8Array) => {
      const buffer = data.buffer.slice(data.byteOffset, data.byteOffset + data.byteLength);
      const imageSource = image.createImageSource(buffer);
      const opts: image.InitializationOptions = {
        editable: true,
        desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
        desiredSize: { width: 240, height: 240 }
      };
      imageSource.createPixelMap(opts).then((pixelMap: PixelMap) => {
        this.sourcePixelMap = pixelMap;
        this.processedPixelMap = pixelMap;
        pixelMap.getImageInfo().then((info: image.ImageInfo) => {
          this.imageWidth = info.size.width;
          this.imageHeight = info.size.height;
          this.appendLog(`解码成功，尺寸 ${info.size.width}x${info.size.height}`);
          this.busy = false;
        });
        imageSource.release();
      }).catch((err: BusinessError) => {
        this.appendLog(`解码失败: code=${err.code}, msg=${err.message}`);
        this.busy = false;
        imageSource.release();
      });
    }).catch((err: BusinessError) => {
      this.appendLog(`读取资源失败: ${err.message}`);
      this.busy = false;
    });
  }

  /**
   * 对当前像素图应用滤镜
   */
  private applyFilter(filterName: string): void {
    if (!this.sourcePixelMap) {
      this.appendLog('无可用像素图，请先解码');
      return;
    }
    this.currentFilter = filterName;
    if (filterName === '原图') {
      this.processedPixelMap = this.sourcePixelMap;
      this.appendLog('已恢复原图');
      return;
    }
    this.busy = true;
    this.appendLog(`应用滤镜: ${filterName}`);
    this.sourcePixelMap.getImageInfo().then((info: image.ImageInfo) => {
      const w = info.size.width;
      const h = info.size.height;
      const buffer = new ArrayBuffer(w * h * 4);
      this.sourcePixelMap!.readPixelsToBuffer(buffer).then(() => {
        const view = new Uint8Array(buffer);
        this.transformPixels(view, w, h, filterName);
        const opts: image.InitializationOptions = {
          editable: true,
          desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
          desiredSize: { width: w, height: h }
        };
        image.createPixelMap(opts).then((newMap: PixelMap) => {
          newMap.writePixelsToBuffer(buffer).then(() => {
            this.processedPixelMap = newMap;
            this.appendLog(`滤镜「${filterName}」应用完成`);
            this.busy = false;
          });
        });
      }).catch((err: BusinessError) => {
        this.appendLog(`读取像素失败: ${err.message}`);
        this.busy = false;
      });
    });
  }

  /**
   * 像素变换核心逻辑
   */
  private transformPixels(view: Uint8Array, w: number, h: number, filterName: string): void {
    const total = w * h * 4;
    for (let i = 0; i < total; i += 4) {
      const r = view[i];
      const g = view[i + 1];
      const b = view[i + 2];
      switch (filterName) {
        case '反色':
          view[i] = 255 - r;
          view[i + 1] = 255 - g;
          view[i + 2] = 255 - b;
          break;
        case '灰度': {
          const gray = Math.floor(0.299 * r + 0.587 * g + 0.114 * b);
          view[i] = gray;
          view[i + 1] = gray;
          view[i + 2] = gray;
          break;
        }
        case '暖色调':
          view[i] = Math.min(255, r + 40);
          view[i + 2] = Math.max(0, b - 40);
          break;
        case '冷色调':
          view[i] = Math.max(0, r - 40);
          view[i + 2] = Math.min(255, b + 40);
          break;
        case '高亮':
          view[i] = Math.min(255, r + 50);
          view[i + 1] = Math.min(255, g + 50);
          view[i + 2] = Math.min(255, b + 50);
          break;
        case '暗调':
          view[i] = Math.max(0, Math.floor(r * 0.5));
          view[i + 1] = Math.max(0, Math.floor(g * 0.5));
          view[i + 2] = Math.max(0, Math.floor(b * 0.5));
          break;
        case '马赛克': {
          const blockSize = 8;
          const x = Math.floor((Math.floor(i / 4) % w) / blockSize) * blockSize;
          const y = Math.floor(Math.floor((i / 4) / w) / blockSize) * blockSize;
          const idx = (y * w + x) * 4;
          view[i] = view[idx];
          view[i + 1] = view[idx + 1];
          view[i + 2] = view[idx + 2];
          break;
        }
        default:
          break;
      }
    }
  }

  /**
   * 程序化生成像素图
   */
  private generatePattern(typeIndex: number): void {
    this.generatingType = typeIndex;
    this.busy = true;
    const typeName = this.generateTypes[typeIndex] || '渐变';
    this.appendLog(`生成图案: ${typeName}`);
    const w = 240;
    const h = 240;
    const buffer = new ArrayBuffer(w * h * 4);
    const view = new Uint8Array(buffer);
    this.fillPattern(view, w, h, typeIndex);
    const opts: image.InitializationOptions = {
      editable: true,
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
      desiredSize: { width: w, height: h }
    };
    image.createPixelMap(opts).then((pixelMap: PixelMap) => {
      pixelMap.writePixelsToBuffer(buffer).then(() => {
        this.generatedPixelMap = pixelMap;
        this.appendLog(`图案「${typeName}」生成完成 (${w}x${h})`);
        this.busy = false;
      });
    }).catch((err: BusinessError) => {
      this.appendLog(`生成失败: ${err.message}`);
      this.busy = false;
    });
  }

  /**
   * 填充生成的像素数据
   */
  private fillPattern(view: Uint8Array, w: number, h: number, typeIndex: number): void {
    for (let y = 0; y < h; y++) {
      for (let x = 0; x < w; x++) {
        const idx = (y * w + x) * 4;
        switch (typeIndex) {
          case 0: {
            const t = x / w;
            view[idx] = Math.floor(t * 255);
            view[idx + 1] = Math.floor((1 - t) * 255);
            view[idx + 2] = Math.floor(128 + t * 100);
            view[idx + 3] = 255;
            break;
          }
          case 1: {
            const dx = x - w / 2;
            const dy = y - h / 2;
            const dist = Math.sqrt(dx * dx + dy * dy) / (w / 2);
            const c = Math.min(1, dist);
            view[idx] = Math.floor(c * 255);
            view[idx + 1] = Math.floor((1 - c) * 200);
            view[idx + 2] = Math.floor(150 + c * 100);
            view[idx + 3] = 255;
            break;
          }
          case 2: {
            const block = 20;
            const isWhite = (Math.floor(x / block) + Math.floor(y / block)) % 2 === 0;
            const v = isWhite ? 240 : 60;
            view[idx] = v;
            view[idx + 1] = v;
            view[idx + 2] = v;
            view[idx + 3] = 255;
            break;
          }
          case 3: {
            const hue = Math.floor((x / w) * 360);
            const rgb = this.hslToRgb(hue, 100, 50);
            view[idx] = rgb[0];
            view[idx + 1] = rgb[1];
            view[idx + 2] = rgb[2];
            view[idx + 3] = 255;
            break;
          }
          default:
            break;
        }
      }
    }
  }

  /**
   * HSL 转 RGB
   */
  private hslToRgb(h: number, s: number, l: number): number[] {
    const hue = h / 360;
    const sat = s / 100;
    const light = l / 100;
    let r: number;
    let g: number;
    let b: number;
    if (sat === 0) {
      r = g = b = light;
    } else {
      const hue2rgb = (p: number, q: number, t: number): number => {
        if (t < 0) {
          t += 1;
        }
        if (t > 1) {
          t -= 1;
        }
        if (t < 1 / 6) {
          return p + (q - p) * 6 * t;
        }
        if (t < 1 / 2) {
          return q;
        }
        if (t < 2 / 3) {
          return p + (q - p) * (2 / 3 - t) * 6;
        }
        return p;
      };
      const q = light < 0.5 ? light * (1 + sat) : light + sat - light * sat;
      const p = 2 * light - q;
      r = hue2rgb(p, q, hue + 1 / 3);
      g = hue2rgb(p, q, hue);
      b = hue2rgb(p, q, hue - 1 / 3);
    }
    return [Math.floor(r * 255), Math.floor(g * 255), Math.floor(b * 255)];
  }

  /**
   * 按缩放重新解码
   */
  private redecode(scale: number): void {
    this.decodeScale = scale;
    const target = Math.floor(240 * scale);
    this.busy = true;
    this.appendLog(`重新解码，目标尺寸 ${target}x${target}`);
    const ctx = this.getUIContext().getHostContext();
    ctx?.resourceManager?.getMediaContent($r('app.media.svg').id).then((data: Uint8Array) => {
      const buffer = data.buffer.slice(data.byteOffset, data.byteOffset + data.byteLength);
      const imageSource = image.createImageSource(buffer);
      const opts: image.InitializationOptions = {
        editable: true,
        desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
        desiredSize: { width: target, height: target }
      };
      imageSource.createPixelMap(opts).then((pixelMap: PixelMap) => {
        this.sourcePixelMap = pixelMap;
        this.processedPixelMap = pixelMap;
        this.currentFilter = '原图';
        pixelMap.getImageInfo().then((info: image.ImageInfo) => {
          this.imageWidth = info.size.width;
          this.imageHeight = info.size.height;
          this.appendLog(`重新解码完成 ${info.size.width}x${info.size.height}`);
          this.busy = false;
        });
        imageSource.release();
      });
    });
  }

  private appendLog(msg: string): void {
    const now = new Date();
    const time = `${now.getHours().toString().padStart(2, '0')}:${now.getMinutes().toString().padStart(2, '0')}:${now.getSeconds().toString().padStart(2, '0')}`;
    this.logText = `[${time}] ${msg}\n` + this.logText;
  }

  build(): void {
    Column({ space: 0 }) {
      this.TitleBar()
      Scroll() {
        Column({ space: 14 }) {
          this.SourcePreviewCard()
          this.FilterCard()
          this.GenerateCard()
          this.DecodeScaleCard()
          this.LogCard()
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
      Text('PixelMap 图片处理实验')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Black)
        .layoutWeight(1)
      if (this.busy) {
        LoadingProgress().width(20).height(20).color('#007DFF')
      }
    }
    .width('100%')
    .height(52)
    .padding({ left: 16, right: 16 })
    .backgroundColor('#FFFFFF')
  }

  @Builder
  SourcePreviewCard(): void {
    Column({ space: 10 }) {
      Text('像素图预览')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 16 }) {
        Column({ space: 6 }) {
          Image(this.processedPixelMap)
            .width(120)
            .height(120)
            .objectFit(ImageFit.Cover)
            .interpolation(ImageInterpolation.Medium)
            .borderRadius(10)
            .backgroundColor('#FFFFFF')
            .border({ width: 1, color: '#E0E0E0' })
          Text(`处理后 · ${this.currentFilter}`)
            .fontSize(11)
            .fontColor(Color.Gray)
        }

        Column({ space: 6 }) {
          Image(this.generatedPixelMap || this.sourcePixelMap)
            .width(120)
            .height(120)
            .objectFit(ImageFit.Cover)
            .interpolation(ImageInterpolation.Medium)
            .borderRadius(10)
            .backgroundColor('#FFFFFF')
            .border({ width: 1, color: '#E0E0E0' })
          Text(this.generatedPixelMap ? `生成图 · ${this.generateTypes[this.generatingType]}` : '生成图预览')
            .fontSize(11)
            .fontColor(Color.Gray)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Row({ space: 16 }) {
        Text(`尺寸: ${this.imageWidth}×${this.imageHeight}`)
          .fontSize(11)
          .fontColor(Color.Gray)
        Text(`格式: RGBA_8888`)
          .fontSize(11)
          .fontColor(Color.Gray)
      }
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  FilterCard(): void {
    Column({ space: 10 }) {
      Text('像素级滤镜（基于 readPixelsToBuffer / writePixelsToBuffer）')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Flex({ wrap: FlexWrap.Wrap }) {
        ForEach(
          this.filters,
          (name: string) => {
            Button(name)
              .fontSize(12)
              .height(32)
              .margin({ right: 8, bottom: 8 })
              .backgroundColor(this.currentFilter === name ? '#007DFF' : '#EDEDED')
              .fontColor(this.currentFilter === name ? Color.White : Color.Black)
              .onClick(() => {
                this.applyFilter(name);
              })
          },
          (name: string) => name
        )
      }
      .width('100%')

      Text('提示：每次处理都会读取像素缓冲区，运算后写回新的 PixelMap。')
        .fontSize(10)
        .fontColor(Color.Gray)
        .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFF8E1')
    .borderRadius(12)
  }

  @Builder
  GenerateCard(): void {
    Column({ space: 10 }) {
      Text('程序化生成像素图（无需图片源）')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 8 }) {
        ForEach(
          this.generateTypes,
          (name: string, index: number) => {
            Button(name)
              .fontSize(11)
              .height(30)
              .layoutWeight(1)
              .backgroundColor(this.generatingType === index ? '#007DFF' : '#EDEDED')
              .fontColor(this.generatingType === index ? Color.White : Color.Black)
              .onClick(() => {
                this.generatePattern(index);
              })
          },
          (name: string) => name
        )
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#E8F5E9')
    .borderRadius(12)
  }

  @Builder
  DecodeScaleCard(): void {
    Column({ space: 10 }) {
      Text('解码尺寸控制（desiredSize）')
        .fontSize(15)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 8 }) {
        ForEach(
          [0.5, 1, 1.5, 2],
          (scale: number) => {
            Button(`${scale}x`)
              .fontSize(11)
              .height(30)
              .layoutWeight(1)
              .backgroundColor(this.decodeScale === scale ? '#007DFF' : '#EDEDED')
              .fontColor(this.decodeScale === scale ? Color.White : Color.Black)
              .onClick(() => {
                this.redecode(scale);
              })
          },
          (scale: number) => `${scale}`
        )
      }
      .width('100%')

      Text('通过 desiredSize 控制解码后的像素图尺寸，可降低内存占用。')
        .fontSize(10)
        .fontColor(Color.Gray)
        .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#E3F2FD')
    .borderRadius(12)
  }

  @Builder
  LogCard(): void {
    Column({ space: 6 }) {
      Row({ space: 8 }) {
        Text('处理日志')
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
            this.logText = '日志已清空';
          })
      }
      .width('100%')

      Text(this.logText)
        .fontSize(11)
        .fontColor('#555555')
        .width('100%')
        .maxLines(12)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FAFAFA')
    .borderRadius(12)
    .alignItems(HorizontalAlign.Start)
  }
}
