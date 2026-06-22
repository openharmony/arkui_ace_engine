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
 * ========================================
 * 位图边缘抗锯齿示例 (对齐官方示例 30 · API 23+)
 * ========================================
 * 功能说明:
 * 本示例演示如何通过 antialiased 属性开启位图图片边缘的抗锯齿功能。
 * 在旋转、缩放、倾斜等变换场景下，抗锯齿可显著提升图片边缘的平滑度。
 *
 * 涉及的 Image API:
 * 1. antialiased(value: boolean) - 开启/关闭抗锯齿 (API 23+)
 * 2. rotate(transform) - 旋转图片
 * 3. scale(transform) - 缩放图片
 * 4. transform - 综合变换
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 旋转图片：图标、徽章、装饰元素
 * - 倾斜图片：3D 透视效果
 * - 非整数缩放：UI 缩略图、自适应布局
 * - 文字图标：避免文字边缘锯齿
 *
 * ========================================
 * 注意事项
 * ========================================
 * 1. 该属性从 API version 23 开始支持
 * 2. 仅对位图图片生效，SVG 图源不支持
 * 3. 开启抗锯齿会略微增加 GPU 开销
 * 4. 对未变换的图片影响较小，主要作用于变换后的边缘
 */

@Entry
@Component
struct ImageAntialiasedExample {
  @State antialiasedEnabled: boolean = true;
  @State rotateAngle: number = 15;
  @State scaleValue: number = 1.2;
  @State skewValue: number = 0;
  @State imageFit: ImageFit = ImageFit.Cover;
  @State imageSource: Resource = $r('app.media.startIcon');

  // 测试图片源列表
  private imageSources: Array<ImageSource> = [
    { name: 'startIcon', res: $r('app.media.startIcon') },
    { name: 'svg', res: $r('app.media.svg') },
    { name: 'icon', res: $r('app.media.icon') },
    { name: 'star', res: $r('app.media.star') }
  ];

  build(): void {
    Scroll() {
      Column({ space: 16 }) {
        Text('位图边缘抗锯齿示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 8 })

        Text('对齐官方文档示例 30 · antialiased (API 23+)')
          .fontSize(12)
          .fontColor(Color.Gray)
          .margin({ bottom: 8 })

        // 对比预览区
        Column({ space: 14 }) {
          Text('对比预览 (左：未开启 · 右：已开启)')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Row({ space: 16 }) {
            // 未开启抗锯齿
            Column({ space: 8 }) {
              Text('未开启抗锯齿')
                .fontSize(12)
                .fontColor(Color.Gray)
              Stack({ alignContent: Alignment.Center }) {
                Image(this.imageSource)
                  .width(100)
                  .height(100)
                  .objectFit(this.imageFit)
                  .rotate({ angle: this.rotateAngle })
                  .scale({ x: this.scaleValue, y: this.scaleValue })
                  .skew({ x: this.skewValue, y: 0 })
                  .antialiased(false)
              }
              .width(140)
              .height(140)
              .backgroundColor('#F5F5F5')
              .borderRadius(12)
              .border({ width: 1, color: '#E0E0E0' })

              Text('antialiased(false)')
                .fontSize(10)
                .fontFamily('monospace')
                .fontColor('#FF6347')
            }
            .layoutWeight(1)
            .alignItems(HorizontalAlign.Center)

            // 已开启抗锯齿
            Column({ space: 8 }) {
              Text('已开启抗锯齿')
                .fontSize(12)
                .fontColor(Color.Gray)
              Stack({ alignContent: Alignment.Center }) {
                Image(this.imageSource)
                  .width(100)
                  .height(100)
                  .objectFit(this.imageFit)
                  .rotate({ angle: this.rotateAngle })
                  .scale({ x: this.scaleValue, y: this.scaleValue })
                  .skew({ x: this.skewValue, y: 0 })
                  .antialiased(true)
              }
              .width(140)
              .height(140)
              .backgroundColor('#F5F5F5')
              .borderRadius(12)
              .border({ width: 1, color: '#007DFF' })

              Text('antialiased(true)')
                .fontSize(10)
                .fontFamily('monospace')
                .fontColor('#007DFF')
            }
            .layoutWeight(1)
            .alignItems(HorizontalAlign.Center)
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFFFFF')
        .borderRadius(16)

        // 变换控制
        Column({ space: 12 }) {
          Text('变换参数控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          // 旋转角度
          Row({ space: 8 }) {
            Text('旋转角度')
              .fontSize(12)
              .width(70)
            Slider(value: this.rotateAngle, min: 0, max: 360, step: 1)
              .layoutWeight(1)
              .onChange((value: number) => {
                this.rotateAngle = value;
              })
            Text(`${this.rotateAngle}°`)
              .fontSize(12)
              .width(45)
          }
          .width('100%')

          // 缩放比例
          Row({ space: 8 }) {
            Text('缩放比例')
              .fontSize(12)
              .width(70)
            Slider(value: this.scaleValue, min: 0.5, max: 2.0, step: 0.1)
              .layoutWeight(1)
              .onChange((value: number) => {
                this.scaleValue = Math.round(value * 10) / 10;
              })
            Text(`${this.scaleValue.toFixed(1)}x`)
              .fontSize(12)
              .width(45)
          }
          .width('100%')

          // 倾斜度
          Row({ space: 8 }) {
            Text('倾斜度')
              .fontSize(12)
              .width(70)
            Slider(value: this.skewValue, min: -0.5, max: 0.5, step: 0.05)
              .layoutWeight(1)
              .onChange((value: number) => {
                this.skewValue = Math.round(value * 20) / 20;
              })
            Text(`${this.skewValue.toFixed(2)}`)
              .fontSize(12)
              .width(45)
          }
          .width('100%')

          Row({ space: 12 }) {
            Toggle({ type: ToggleType.Switch, isOn: this.antialiasedEnabled })
              .onChange((on: boolean) => {
                this.antialiasedEnabled = on;
              })
            Text('全局开关（用于强调对比效果）')
              .fontSize(12)
              .fontColor(Color.Gray)
              .layoutWeight(1)
          }
          .width('100%')

          Row({ space: 8 }) {
            Button('重置')
              .fontSize(12)
              .backgroundColor('#888888')
              .fontColor(Color.White)
              .layoutWeight(1)
              .height(34)
              .onClick(() => {
                this.rotateAngle = 15;
                this.scaleValue = 1.2;
                this.skewValue = 0;
              })

            Button('旋转动画')
              .fontSize(12)
              .backgroundColor('#007DFF')
              .fontColor(Color.White)
              .layoutWeight(1)
              .height(34)
              .onClick(() => {
                this.rotateAngle = (this.rotateAngle + 45) % 360;
              })

            Button('随机倾斜')
              .fontSize(12)
              .backgroundColor('#FFA500')
              .fontColor(Color.White)
              .layoutWeight(1)
              .height(34)
              .onClick(() => {
                this.skewValue = Math.round((Math.random() - 0.5) * 10) / 10;
              })
          }
          .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#F0FFF0')
        .borderRadius(16)

        // 图片切换
        Column({ space: 12 }) {
          Text('切换测试图片')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Row({ space: 8 }) {
            ForEach(
              this.imageSources,
              (item: ImageSource) => {
                Button(item.name)
                  .fontSize(11)
                  .backgroundColor(this.imageSource === item.res ? '#007DFF' : '#E0E0E0')
                  .fontColor(this.imageSource === item.res ? Color.White : Color.Black)
                  .height(30)
                  .layoutWeight(1)
                  .onClick(() => {
                    this.imageSource = item.res;
                  })
              },
              (item: ImageSource) => item.name
            )
          }
          .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFF8DC')
        .borderRadius(16)

        // 应用场景
        Column({ space: 10 }) {
          Text('典型应用场景')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.ScenarioItem('旋转徽章', '旋转的勋章、徽章、Logo 等')
          this.ScenarioItem('倾斜卡片', '3D 透视倾斜效果的图片卡片')
          this.ScenarioItem('非整数缩放', '自适应布局中的缩略图、缩放图')
          this.ScenarioItem('图标动画', '旋转或缩放的图标动画')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#E6F7FF')
        .borderRadius(16)

        // API 说明
        Column({ space: 8 }) {
          Text('API 说明')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.DocItem('antialiased(true)', '开启位图边缘抗锯齿')
          this.DocItem('antialiased(false)', '关闭抗锯齿（默认）')
          this.DocItem('rotate/scale/skew', '变换效果，配合抗锯齿使用更佳')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFE4E1')
        .borderRadius(16)

        Text('提示：抗锯齿对变换后的位图边缘最明显，原图影响较小')
          .fontSize(11)
          .fontColor(Color.Gray)
          .margin({ top: 4, bottom: 20 })
      }
      .width('100%')
      .padding({ left: 16, right: 16 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }

  @Builder
  ScenarioItem(name: string, desc: string): void {
    Row({ space: 8 }) {
      Text('●')
        .fontSize(10)
        .fontColor('#007DFF')
        .width(16)
      Column({ space: 2 }) {
        Text(name)
          .fontSize(12)
          .fontWeight(FontWeight.Medium)
          .fontColor(Color.Black)
        Text(desc)
          .fontSize(11)
          .fontColor(Color.Gray)
      }
      .alignItems(HorizontalAlign.Start)
      .layoutWeight(1)
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FFFFFF')
    .borderRadius(6)
  }

  @Builder
  DocItem(api: string, desc: string): void {
    Row({ space: 8 }) {
      Text(api)
        .fontSize(11)
        .fontColor('#007DFF')
        .fontFamily('monospace')
        .width('45%')
      Text(desc)
        .fontSize(11)
        .fontColor(Color.Gray)
        .layoutWeight(1)
    }
    .width('100%')
    .padding(6)
    .backgroundColor('#FFFFFF')
    .borderRadius(6)
  }
}

interface ImageSource {
  name: string;
  res: Resource;
}
