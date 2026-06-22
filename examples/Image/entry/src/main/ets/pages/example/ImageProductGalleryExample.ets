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
 * 业务场景：商品图片画廊示例
 * ========================================
 * 功能说明:
 * 本示例模拟电商商品详情页的图片画廊场景，综合运用 Image 组件的各种能力。
 * 包含：主图展示、缩略图切换、图片放大预览、加载占位、错误处理、内存优化等。
 *
 * 涉及的 Image API 和特性:
 * 1. Image(src: Resource | PixelMap) - 多种数据源
 * 2. alt(ImageAlt) - 加载中和失败的占位图
 * 3. objectFit(ImageFit) - 填充模式切换
 * 4. syncLoad / autoResize / interpolation - 加载优化
 * 5. onComplete / onError - 事件回调
 * 6. enableAnalyzer - 图像 AI 分析（API 11+）
 * 7. borderRadius / border / shadow - 视觉样式
 * 8. image.createImageSource - 图片处理
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 电商应用：商品详情页图片画廊
 * - 资讯应用：新闻配图浏览
 * - 旅游应用：景点图片展示
 * - 教育应用：课程封面浏览
 */

interface ProductImage {
  id: number;
  src: Resource;
  title: string;
  desc: string;
}

@Entry
@Component
struct ImageProductGalleryExample {
  @State productImages: Array<ProductImage> = [];
  @State currentIndex: number = 0;
  @State mainFit: ImageFit = ImageFit.Cover;
  @State autoResizeOn: boolean = true;
  @State syncLoadOn: boolean = true;
  @State interpolation: ImageInterpolation = ImageInterpolation.Medium;
  @State zoomScale: number = 1.0;
  @State zoomAngle: number = 0;
  @State loading: boolean = false;
  @State lastError: string = '';
  @State lastLoadedSize: string = '';
  @State switchCount: number = 0;

  aboutToAppear(): void {
    this.initProducts();
  }

  /**
   * 初始化商品图片列表
   */
  private initProducts(): void {
    this.productImages = [
      { id: 1, src: $r('app.media.startIcon'), title: '主图', desc: '商品主视觉图' },
      { id: 2, src: $r('app.media.svg'), title: '细节图', desc: '材质细节展示' },
      { id: 3, src: $r('app.media.icon'), title: '场景图', desc: '使用场景展示' },
      { id: 4, src: $r('app.media.star'), title: '包装图', desc: '产品包装展示' },
      { id: 5, src: $r('app.media.heart'), title: '配件图', desc: '配件清单展示' }
    ];
  }

  /**
   * 切换到指定图片
   */
  private switchTo(index: number): void {
    if (index === this.currentIndex || index < 0 || index >= this.productImages.length) {
      return;
    }
    this.currentIndex = index;
    this.switchCount++;
    this.zoomScale = 1.0;
    this.zoomAngle = 0;
    this.loading = true;
    this.lastError = '';
  }

  /**
   * 放大图片
   */
  private zoomIn(): void {
    this.zoomScale = Math.min(3.0, this.zoomScale + 0.2);
  }

  /**
   * 缩小图片
   */
  private zoomOut(): void {
    this.zoomScale = Math.max(0.5, this.zoomScale - 0.2);
  }

  /**
   * 旋转图片
   */
  private rotate(): void {
    this.zoomAngle = (this.zoomAngle + 90) % 360;
  }

  /**
   * 重置变换
   */
  private resetTransform(): void {
    this.zoomScale = 1.0;
    this.zoomAngle = 0;
  }

  build(): void {
    Column({ space: 0 }) {
      // 顶部标题栏
      Row({ space: 8 }) {
        Text('←')
          .fontSize(20)
          .fontColor(Color.Black)
          .onClick(() => {
          })
        Column({ space: 2 }) {
          Text('商品图片画廊')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.Black)
          Text(`电商场景综合示例 · ${this.productImages.length} 张`)
            .fontSize(10)
            .fontColor(Color.Gray)
        }
        .alignItems(HorizontalAlign.Start)
        .layoutWeight(1)

        Text(`${this.currentIndex + 1}/${this.productImages.length}`)
          .fontSize(12)
          .fontColor(Color.White)
          .backgroundColor('#000000')
          .borderRadius(10)
          .padding({ left: 8, right: 8, top: 4, bottom: 4 })
      }
      .width('100%')
      .height(56)
      .padding({ left: 16, right: 16 })
      .backgroundColor('#FFFFFF')
      .border({ width: 0, color: '#E0E0E0' })

      Scroll() {
        Column({ space: 12 }) {
          // 主图区
          this.MainImageArea()

          // 缩略图列表
          this.ThumbnailList()

          // 图片信息
          this.ImageInfoCard()

          // 操作工具栏
          this.Toolbar()

          // 加载优化设置
          this.LoadOptionsCard()

          // objectFit 选择
          this.FitModeCard()
        }
        .width('100%')
        .padding(12)
      }
      .layoutWeight(1)
      .scrollBar(BarState.Auto)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }

  @Builder
  MainImageArea(): void {
    Column({ space: 10 }) {
      Stack({ alignContent: Alignment.BottomEnd }) {
        // 主图
        Image(this.productImages[this.currentIndex].src)
          .width('100%')
          .height(320)
          .objectFit(this.mainFit)
          .scale({ x: this.zoomScale, y: this.zoomScale })
          .rotate({ angle: this.zoomAngle })
          .alt({
            placeholder: $r('app.media.startIcon'),
            error: $r('app.media.startIcon')
          })
          .syncLoad(this.syncLoadOn)
          .autoResize(this.autoResizeOn)
          .interpolation(this.interpolation)
          .borderRadius(12)
          .backgroundColor('#FAFAFA')
          .onComplete((event) => {
            if (event) {
              this.loading = false;
              this.lastLoadedSize = `${event.width}×${event.height}`;
            }
          })
          .onError((error) => {
            const err = error as BusinessError;
            this.loading = false;
            this.lastError = `加载失败: ${err.message}`;
          })

        // 加载中遮罩
        if (this.loading) {
          Column({ space: 8 }) {
            LoadingProgress()
              .width(40)
              .height(40)
              .color('#007DFF')
            Text('加载中...')
              .fontSize(12)
              .fontColor(Color.White)
          }
          .width('100%')
          .height('100%')
          .justifyContent(FlexAlign.Center)
          .backgroundColor('#80000000')
          .borderRadius(12)
        }

        // 索引标签
        Text(`${this.currentIndex + 1} / ${this.productImages.length}`)
          .fontSize(11)
          .fontColor(Color.White)
          .backgroundColor('#80000000')
          .borderRadius(10)
          .padding({ left: 8, right: 8, top: 4, bottom: 4 })
          .margin(12)
      }
      .width('100%')
      .height(320)

      // 标题信息
      Column({ space: 4 }) {
        Text(this.productImages[this.currentIndex].title)
          .fontSize(15)
          .fontWeight(FontWeight.Medium)
          .fontColor(Color.Black)
        Text(this.productImages[this.currentIndex].desc)
          .fontSize(12)
          .fontColor(Color.Gray)
      }
      .width('100%')
      .alignItems(HorizontalAlign.Start)
      .padding({ left: 4 })
    }
    .width('100%')
  }

  @Builder
  ThumbnailList(): void {
    Row({ space: 8 }) {
      ForEach(
        this.productImages,
        (item: ProductImage, index: number) => {
          Stack({ alignContent: Alignment.TopEnd }) {
            Image(item.src)
              .width(56)
              .height(56)
              .objectFit(ImageFit.Cover)
              .borderRadius(8)
              .border({
                width: this.currentIndex === index ? 2 : 1,
                color: this.currentIndex === index ? '#007DFF' : '#E0E0E0'
              })
              .alt({ placeholder: $r('app.media.startIcon'), error: $r('app.media.startIcon') })
              .onClick(() => {
                this.switchTo(index);
              })

            if (this.currentIndex === index) {
              Text('●')
                .fontSize(10)
                .fontColor('#007DFF')
                .backgroundColor(Color.White)
                .borderRadius(8)
                .width(14)
                .height(14)
                .textAlign(TextAlign.Center)
                .markAnchor({ x: 7, y: 7 })
                .position({ x: 56, y: 0 })
            }
          }
          .width(56)
          .height(56)
        },
        (item: ProductImage) => `${item.id}`
      )
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  ImageInfoCard(): void {
    Column({ space: 6 }) {
      this.InfoRow('当前图片', this.productImages[this.currentIndex].title)
      this.InfoRow('描述', this.productImages[this.currentIndex].desc)
      this.InfoRow('加载状态', this.loading ? '加载中' : (this.lastError ? '失败' : '已加载'))
      this.InfoRow('图片尺寸', this.lastLoadedSize || '尚未加载')
      this.InfoRow('切换次数', `${this.switchCount}`)
      if (this.lastError) {
        this.InfoRow('错误信息', this.lastError)
      }
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFF8DC')
    .borderRadius(12)
  }

  @Builder
  InfoRow(label: string, value: string): void {
    Row({ space: 8 }) {
      Text(label)
        .fontSize(11)
        .fontColor(Color.Gray)
        .width(70)
      Text(value)
        .fontSize(11)
        .fontColor(Color.Black)
        .layoutWeight(1)
        .maxLines(2)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
    }
    .width('100%')
    .padding(4)
  }

  @Builder
  Toolbar(): void {
    Column({ space: 10 }) {
      Text('操作工具栏')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 8 }) {
        Column({ space: 4 }) {
          Text('➕')
            .fontSize(20)
          Text('放大')
            .fontSize(10)
            .fontColor(Color.Gray)
        }
        .layoutWeight(1)
        .padding(8)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .onClick(() => {
          this.zoomIn();
        })

        Column({ space: 4 }) {
          Text('➖')
            .fontSize(20)
          Text('缩小')
            .fontSize(10)
            .fontColor(Color.Gray)
        }
        .layoutWeight(1)
        .padding(8)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .onClick(() => {
          this.zoomOut();
        })

        Column({ space: 4 }) {
          Text('↻')
            .fontSize(20)
          Text('旋转')
            .fontSize(10)
            .fontColor(Color.Gray)
        }
        .layoutWeight(1)
        .padding(8)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .onClick(() => {
          this.rotate();
        })

        Column({ space: 4 }) {
          Text('↺')
            .fontSize(20)
          Text('重置')
            .fontSize(10)
            .fontColor(Color.Gray)
        }
        .layoutWeight(1)
        .padding(8)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .onClick(() => {
          this.resetTransform();
        })
      }
      .width('100%')

      Row({ space: 12 }) {
        Text(`缩放: ${this.zoomScale.toFixed(1)}x`)
          .fontSize(11)
          .fontColor(Color.Gray)
          .layoutWeight(1)
        Text(`旋转: ${this.zoomAngle}°`)
          .fontSize(11)
          .fontColor(Color.Gray)
          .layoutWeight(1)
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  LoadOptionsCard(): void {
    Column({ space: 10 }) {
      Text('加载优化设置')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.autoResizeOn })
          .onChange((on: boolean) => {
            this.autoResizeOn = on;
          })
        Text('autoResize')
          .fontSize(12)
          .fontColor(Color.Black)
          .layoutWeight(1)
        Text(this.autoResizeOn ? '按显示尺寸解码' : '原图解码')
          .fontSize(10)
          .fontColor(Color.Gray)
          .width(110)
      }
      .width('100%')

      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.syncLoadOn })
          .onChange((on: boolean) => {
            this.syncLoadOn = on;
          })
        Text('syncLoad')
          .fontSize(12)
          .fontColor(Color.Black)
          .layoutWeight(1)
        Text(this.syncLoadOn ? '同步加载' : '异步加载')
          .fontSize(10)
          .fontColor(Color.Gray)
          .width(110)
      }
      .width('100%')

      // 插值效果
      Row({ space: 8 }) {
        Text('interpolation')
          .fontSize(12)
          .fontColor(Color.Black)
          .width(100)
        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(
            [
              ImageInterpolation.None,
              ImageInterpolation.Low,
              ImageInterpolation.Medium,
              ImageInterpolation.High
            ],
            (interp: ImageInterpolation) => {
              Button(this.interpName(interp))
                .fontSize(9)
                .backgroundColor(this.interpolation === interp ? '#007DFF' : '#E0E0E0')
                .fontColor(this.interpolation === interp ? Color.White : Color.Black)
                .height(24)
                .margin({ right: 4, bottom: 4 })
                .onClick(() => {
                  this.interpolation = interp;
                })
            },
            (interp: ImageInterpolation) => `${interp}`
          )
        }
        .layoutWeight(1)
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#F0FFF0')
    .borderRadius(12)
  }

  @Builder
  FitModeCard(): void {
    Column({ space: 8 }) {
      Text('objectFit 填充模式')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)
        .width('100%')

      Row({ space: 6 }) {
        ForEach(
          [ImageFit.Cover, ImageFit.Contain, ImageFit.Fill, ImageFit.ScaleDown, ImageFit.None],
          (fit: ImageFit) => {
            Button(this.fitName(fit))
              .fontSize(10)
              .backgroundColor(this.mainFit === fit ? '#007DFF' : '#E0E0E0')
              .fontColor(this.mainFit === fit ? Color.White : Color.Black)
              .height(28)
              .layoutWeight(1)
              .onClick(() => {
                this.mainFit = fit;
              })
          },
          (fit: ImageFit) => `${fit}`
        )
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#E6F7FF')
    .borderRadius(12)
  }

  private fitName(fit: ImageFit): string {
    switch (fit) {
      case ImageFit.Cover:
        return 'Cover';
      case ImageFit.Contain:
        return 'Contain';
      case ImageFit.Fill:
        return 'Fill';
      case ImageFit.ScaleDown:
        return 'ScaleDown';
      case ImageFit.None:
        return 'None';
      default:
        return 'Cover';
    }
  }

  private interpName(interp: ImageInterpolation): string {
    switch (interp) {
      case ImageInterpolation.None:
        return 'None';
      case ImageInterpolation.Low:
        return 'Low';
      case ImageInterpolation.Medium:
        return 'Medium';
      case ImageInterpolation.High:
        return 'High';
      default:
        return 'Medium';
    }
  }
}
