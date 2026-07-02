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
 * sourceSize 图片解码尺寸示例 (对齐官方示例 15)
 * ========================================
 * 功能说明:
 * 本示例演示如何通过 sourceSize 属性自定义图片的解码尺寸。
 * sourceSize 用于在解码阶段就降低图片分辨率，常用于显示小图但原图很大的场景，
 * 可显著减少内存占用。
 *
 * 涉及的 Image API:
 * 1. sourceSize({ width, height }) - 设置解码尺寸
 * 2. objectFit(ImageFit) - 配合使用控制显示效果
 * 3. autoResize(boolean) - 对比：是否对图源自动缩放
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 缩略图列表：解码为小尺寸节省内存
 * - 网格图片：原 4K 图但显示 100x100
 * - 资源预览：解码低分辨率版本快速预览
 * - 内存优化：避免解码完整大图
 *
 * ========================================
 * 注意事项
 * ========================================
 * 1. 仅在目标尺寸小于图源尺寸时生效
 * 2. SVG 图源和 PixelMap 资源不支持
 * 3. AnimatedDrawableDescriptor 类型不生效
 * 4. 与 objectFit.None 配合使用可在组件内显示小图
 */

@Entry
@Component
struct ImageSourceSizeExample {
  @State sourceWidth: number = 100;
  @State sourceHeight: number = 100;
  @State displayWidth: number = 200;
  @State displayHeight: number = 200;
  @State objectFit: ImageFit = ImageFit.Contain;
  @State useSourceSize: boolean = true;
  @State comparisonMode: boolean = true;

  // 解码尺寸预设
  private sizePresets: Array<SizePreset> = [
    { name: '极小', width: 13, height: 10 },
    { name: '小', width: 50, height: 50 },
    { name: '中', width: 100, height: 100 },
    { name: '大', width: 300, height: 300 },
    { name: '原始', width: 1393, height: 1080 }
  ];

  build(): void {
    Scroll() {
      Column({ space: 16 }) {
        Text('sourceSize 解码尺寸示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 8 })

        Text('对齐官方文档示例 15 · 解码阶段降低分辨率')
          .fontSize(12)
          .fontColor(Color.Gray)
          .margin({ bottom: 8 })

        // 主预览区
        Column({ space: 14 }) {
          Text('效果预览')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Row({ space: 12 }) {
            // 左：使用 sourceSize
            Column({ space: 6 }) {
              Text('启用 sourceSize')
                .fontSize(11)
                .fontColor('#32CD32')
              Image($r('app.media.startIcon'))
                .sourceSize({ width: this.sourceWidth, height: this.sourceHeight })
                .width(this.displayWidth)
                .height(this.displayHeight)
                .objectFit(this.objectFit)
                .border({ width: 2, color: '#32CD32' })
                .borderRadius(8)
                .backgroundColor('#FAFAFA')

              Text(`解码 ${this.sourceWidth}×${this.sourceHeight}`)
                .fontSize(10)
                .fontColor(Color.Gray)
            }
            .layoutWeight(1)
            .alignItems(HorizontalAlign.Center)

            // 右：未启用 sourceSize
            if (this.comparisonMode) {
              Column({ space: 6 }) {
                Text('未启用 (原图解码)')
                  .fontSize(11)
                  .fontColor('#FF6347')
                Image($r('app.media.startIcon'))
                  .width(this.displayWidth)
                  .height(this.displayHeight)
                  .objectFit(this.objectFit)
                  .border({ width: 2, color: '#FF6347' })
                  .borderRadius(8)
                  .backgroundColor('#FAFAFA')

                Text('解码原尺寸')
                  .fontSize(10)
                  .fontColor(Color.Gray)
              }
              .layoutWeight(1)
              .alignItems(HorizontalAlign.Center)
            }
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFFFFF')
        .borderRadius(16)

        // 预设尺寸
        Column({ space: 10 }) {
          Text('解码尺寸预设')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(
              this.sizePresets,
              (preset: SizePreset) => {
                Button(`${preset.name} ${preset.width}×${preset.height}`)
                  .fontSize(10)
                  .backgroundColor(
                    this.sourceWidth === preset.width && this.sourceHeight === preset.height
                      ? '#007DFF' : '#E0E0E0'
                  )
                  .fontColor(
                    this.sourceWidth === preset.width && this.sourceHeight === preset.height
                      ? Color.White : Color.Black
                  )
                  .height(30)
                  .margin({ right: 6, bottom: 6 })
                  .onClick(() => {
                    this.sourceWidth = preset.width;
                    this.sourceHeight = preset.height;
                  })
              },
              (preset: SizePreset) => `${preset.name}_${preset.width}_${preset.height}`
            )
          }
          .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#F0FFF0')
        .borderRadius(16)

        // 参数调节
        Column({ space: 12 }) {
          Text('参数调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.SizeSlider('解码宽度', this.sourceWidth, 10, 500, (v: number) => {
            this.sourceWidth = v;
          })
          this.SizeSlider('解码高度', this.sourceHeight, 10, 500, (v: number) => {
            this.sourceHeight = v;
          })
          this.SizeSlider('显示宽度', this.displayWidth, 80, 280, (v: number) => {
            this.displayWidth = v;
          })
          this.SizeSlider('显示高度', this.displayHeight, 80, 280, (v: number) => {
            this.displayHeight = v;
          })

          Divider().color('#E0E0E0')

          // objectFit 选择
          Row({ space: 6 }) {
            Text('objectFit')
              .fontSize(11)
              .width(70)
            Flex({ wrap: FlexWrap.Wrap }) {
              ForEach(
                [ImageFit.Cover, ImageFit.Contain, ImageFit.Fill, ImageFit.ScaleDown, ImageFit.None],
                (fit: ImageFit) => {
                  Button(this.fitName(fit))
                    .fontSize(10)
                    .backgroundColor(this.objectFit === fit ? '#007DFF' : '#E0E0E0')
                    .fontColor(this.objectFit === fit ? Color.White : Color.Black)
                    .height(26)
                    .margin({ right: 4, bottom: 4 })
                    .onClick(() => {
                      this.objectFit = fit;
                    })
                },
                (fit: ImageFit) => `${fit}`
              )
            }
            .layoutWeight(1)
          }
          .width('100%')

          Row({ space: 8 }) {
            Toggle({ type: ToggleType.Switch, isOn: this.comparisonMode })
              .onChange((on: boolean) => {
                this.comparisonMode = on;
              })
            Text('显示对比模式')
              .fontSize(12)
              .fontColor(Color.Black)
          }
          .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFF8DC')
        .borderRadius(16)

        // 内存对比示意
        Column({ space: 10 }) {
          Text('内存占用对比 (示意)')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.MemoryRow('原图解码', '1393×1080', '~5.8 MB', '#FF6347')
          this.MemoryRow('中等尺寸', '300×300', '~360 KB', '#FFA500')
          this.MemoryRow('小尺寸', '100×100', '~40 KB', '#32CD32')
          this.MemoryRow('极小尺寸', '13×10', '~0.5 KB', '#007DFF')

          Divider().color('#E0E0E0')

          Text('提示：sourceSize 越小，内存占用越低，但放大后可能模糊')
            .fontSize(11)
            .fontColor(Color.Gray)
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#E6F7FF')
        .borderRadius(16)

        // 最佳实践
        Column({ space: 10 }) {
          Text('最佳实践')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.PracticeItem('缩略图列表', 'sourceSize 设为显示尺寸的 1-2 倍，平衡清晰度与内存')
          this.PracticeItem('配合 objectFit.None', '可在小组件内显示大图的局部内容')
          this.PracticeItem('避免过度缩小', 'sourceSize 太小会导致放大后严重失真')
          this.PracticeItem('SVG 不支持', 'SVG 是矢量图，无需解码，sourceSize 不生效')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFE4E1')
        .borderRadius(16)

        // API 说明
        Column({ space: 8 }) {
          Text('API 说明')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.DocItem('sourceSize({width, height})', '设置图片解码的目标尺寸')
          this.DocItem('autoResize(true)', '另一种自动缩放方案，按显示区域解码')
          this.DocItem('objectFit.None', '配合 sourceSize 可在小区域显示大图')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#F5F5F5')
        .borderRadius(16)

        Text('提示：sourceSize 仅在目标尺寸小于图源时生效')
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
  SizeSlider(label: string, value: number, min: number, max: number, onChange: (v: number) => void): void {
    Row({ space: 8 }) {
      Text(label)
        .fontSize(11)
        .width(70)
      Slider(value: value, min: min, max: max, step: 5)
        .layoutWeight(1)
        .onChange((v: number) => {
          onChange(v);
        })
      Text(`${value}`)
        .fontSize(11)
        .width(45)
    }
    .width('100%')
  }

  @Builder
  MemoryRow(label: string, size: string, memory: string, color: ResourceColor): void {
    Row({ space: 8 }) {
      Text(label)
        .fontSize(11)
        .fontColor(Color.Black)
        .width(80)
      Text(size)
        .fontSize(11)
        .fontFamily('monospace')
        .fontColor(Color.Gray)
        .width(80)
      Text(memory)
        .fontSize(11)
        .fontWeight(FontWeight.Medium)
        .fontColor(color)
        .layoutWeight(1)
    }
    .width('100%')
    .padding(6)
    .backgroundColor('#FFFFFF')
    .borderRadius(6)
  }

  @Builder
  PracticeItem(title: string, desc: string): void {
    Row({ space: 8 }) {
      Text('●')
        .fontSize(10)
        .fontColor('#007DFF')
        .width(16)
      Column({ space: 2 }) {
        Text(title)
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
    .padding(6)
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
        .width('50%')
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
        return 'Contain';
    }
  }
}

interface SizePreset {
  name: string;
  width: number;
  height: number;
}
