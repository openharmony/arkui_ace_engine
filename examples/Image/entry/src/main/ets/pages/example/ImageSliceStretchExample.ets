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
 * slice 九宫格拉伸图片示例 (对齐官方示例 6)
 * ========================================
 * 功能说明:
 * 本示例演示如何通过 resizable 属性的 slice 选项实现九宫格拉伸。
 * 常用于聊天气泡、按钮背景、卡片边框等需要保持边角不失真的场景。
 *
 * 涉及的 Image API:
 * 1. resizable({ slice: ResizableSlice }) - 九宫格切片拉伸
 * 2. slice.left / right / top / bottom - 四边切片距离
 * 3. objectFit(ImageFit) - 配合 Fill 模式实现拉伸
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 聊天气泡：保持圆角和指向箭头不失真
 * - 按钮背景：拉伸按钮保持边缘清晰
 * - 卡片阴影：拉伸带阴影的卡片背景
 * - 进度条：拉伸带端点的进度条背景
 *
 * ========================================
 * 注意事项
 * ========================================
 * 1. SVG 图源不支持 resizable
 * 2. AnimatedDrawableDescriptor 类型不生效
 * 3. 单位推荐使用 px，避免不同设备 vp 解析差异
 * 4. 切片区域不能重叠，需小于图片尺寸的一半
 */

@Entry
@Component
struct ImageSliceStretchExample {
  @State sliceLeft: number = 30;
  @State sliceRight: number = 30;
  @State sliceTop: number = 30;
  @State sliceBottom: number = 30;
  @State targetWidth: number = 280;
  @State targetHeight: number = 120;
  @State currentDemoIndex: number = 0;

  // 切片预设方案
  private presets: Array<SlicePreset> = [
    { name: '小圆角', left: 12, right: 12, top: 12, bottom: 12 },
    { name: '中圆角', left: 30, right: 30, top: 30, bottom: 30 },
    { name: '大圆角', left: 50, right: 50, top: 50, bottom: 50 },
    { name: '聊天气泡', left: 40, right: 60, top: 40, bottom: 40 },
    { name: '按钮背景', left: 20, right: 20, top: 20, bottom: 20 }
  ];

  build(): void {
    Scroll() {
      Column({ space: 16 }) {
        Text('slice 九宫格拉伸示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 8 })

        Text('对齐官方文档示例 6 · resizable slice 拉伸')
          .fontSize(12)
          .fontColor(Color.Gray)
          .margin({ bottom: 8 })

        // 演示区
        Column({ space: 12 }) {
          Text('效果对比')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          // 原图
          Column({ space: 6 }) {
            Text('原图 (100×100)')
              .fontSize(11)
              .fontColor(Color.Gray)
            Image($r('app.media.startIcon'))
              .width(100)
              .height(100)
              .objectFit(ImageFit.Fill)
              .border({ width: 1, color: '#E0E0E0' })
              .borderRadius(4)
          }
          .width('100%')
          .padding(12)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)

          // 直接拉伸（失真）
          Column({ space: 6 }) {
            Text(`直接拉伸 (${this.targetWidth}×${this.targetHeight}) - 边角失真`)
              .fontSize(11)
              .fontColor('#FF6347')
            Image($r('app.media.startIcon'))
              .width(this.targetWidth)
              .height(this.targetHeight)
              .objectFit(ImageFit.Fill)
              .border({ width: 1, color: '#FF6347' })
              .borderRadius(4)
          }
          .width('100%')
          .padding(12)
          .backgroundColor('#FFF5F5')
          .borderRadius(8)

          // slice 拉伸（保真）
          Column({ space: 6 }) {
            Text(`slice 拉伸 (${this.targetWidth}×${this.targetHeight}) - 边角清晰`)
              .fontSize(11)
              .fontColor('#32CD32')
            Image($r('app.media.startIcon'))
              .resizable({
                slice: {
                  left: `${this.sliceLeft}px`,
                  right: `${this.sliceRight}px`,
                  top: `${this.sliceTop}px`,
                  bottom: `${this.sliceBottom}px`
                }
              })
              .width(this.targetWidth)
              .height(this.targetHeight)
              .objectFit(ImageFit.Fill)
              .border({ width: 1, color: '#32CD32' })
              .borderRadius(4)
          }
          .width('100%')
          .padding(12)
          .backgroundColor('#F5FFF5')
          .borderRadius(8)
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFFFFF')
        .borderRadius(16)

        // 预设方案
        Column({ space: 10 }) {
          Text('预设方案')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(
              this.presets,
              (preset: SlicePreset, index: number) => {
                Button(preset.name)
                  .fontSize(11)
                  .backgroundColor(this.currentDemoIndex === index ? '#007DFF' : '#E0E0E0')
                  .fontColor(this.currentDemoIndex === index ? Color.White : Color.Black)
                  .height(30)
                  .margin({ right: 6, bottom: 6 })
                  .onClick(() => {
                    this.sliceLeft = preset.left;
                    this.sliceRight = preset.right;
                    this.sliceTop = preset.top;
                    this.sliceBottom = preset.bottom;
                    this.currentDemoIndex = index;
                  })
              },
              (preset: SlicePreset) => preset.name
            )
          }
          .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#F0FFF0')
        .borderRadius(16)

        // 切片参数调节
        Column({ space: 12 }) {
          Text('切片参数调节 (px)')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.SliceSlider('左边', this.sliceLeft, (v: number) => {
            this.sliceLeft = v;
          })
          this.SliceSlider('右边', this.sliceRight, (v: number) => {
            this.sliceRight = v;
          })
          this.SliceSlider('顶部', this.sliceTop, (v: number) => {
            this.sliceTop = v;
          })
          this.SliceSlider('底部', this.sliceBottom, (v: number) => {
            this.sliceBottom = v;
          })

          Divider().color('#E0E0E0')

          this.SizeSlider('目标宽度', this.targetWidth, 120, 400, (v: number) => {
            this.targetWidth = v;
          })
          this.SizeSlider('目标高度', this.targetHeight, 60, 240, (v: number) => {
            this.targetHeight = v;
          })
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFF8DC')
        .borderRadius(16)

        // 应用场景演示：聊天气泡
        Column({ space: 10 }) {
          Text('应用场景：聊天气泡')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          // 模拟聊天气泡
          Column({ space: 10 }) {
            Row() {
              Stack({ alignContent: Alignment.Start }) {
                Image($r('app.media.startIcon'))
                  .resizable({
                    slice: {
                      left: '20px',
                      right: '40px',
                      top: '20px',
                      bottom: '20px'
                    }
                  })
                  .width(200)
                  .height(50)
                  .objectFit(ImageFit.Fill)

                Text('你好，欢迎使用 ArkUI！')
                  .fontSize(13)
                  .fontColor(Color.Black)
                  .padding({ left: 16, top: 14 })
              }
              .width(200)
              .height(50)
            }
            .width('100%')
            .justifyContent(FlexAlign.Start)

            Row() {
              Stack({ alignContent: Alignment.End }) {
                Image($r('app.media.startIcon'))
                  .resizable({
                    slice: {
                      left: '40px',
                      right: '20px',
                      top: '20px',
                      bottom: '20px'
                    }
                  })
                  .width(200)
                  .height(50)
                  .objectFit(ImageFit.Fill)

                Text('感谢，slice 效果很棒！')
                  .fontSize(13)
                  .fontColor(Color.Black)
                  .padding({ right: 16, top: 14 })
              }
              .width(200)
              .height(50)
            }
            .width('100%')
            .justifyContent(FlexAlign.End)
          }
          .width('100%')
          .padding(12)
          .backgroundColor('#F5F5F5')
          .borderRadius(8)
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#E6F7FF')
        .borderRadius(16)

        // 切片说明
        Column({ space: 8 }) {
          Text('原理说明')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.DocItem('九宫格', '将图片切成 3×3 共 9 块，四角保持原样，四边和中心拉伸')
          this.DocItem('slice 四边距离', '从图片对应边向内测量，定义角部区域的大小')
          this.DocItem('单位推荐', '建议使用 px，避免 vp 在不同设备上的差异')
          this.DocItem('限制条件', 'SVG / AnimatedDrawableDescriptor 不支持')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFE4E1')
        .borderRadius(16)

        Text('提示：通过 slice 拉伸可制作自适应尺寸的按钮、气泡等组件')
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
  SliceSlider(label: string, value: number, onChange: (v: number) => void): void {
    Row({ space: 8 }) {
      Text(label)
        .fontSize(11)
        .width(50)
      Slider(value: value, min: 0, max: 80, step: 2)
        .layoutWeight(1)
        .onChange((v: number) => {
          onChange(v);
        })
      Text(`${value}px`)
        .fontSize(11)
        .width(50)
    }
    .width('100%')
  }

  @Builder
  SizeSlider(label: string, value: number, min: number, max: number, onChange: (v: number) => void): void {
    Row({ space: 8 }) {
      Text(label)
        .fontSize(11)
        .width(60)
      Slider(value: value, min: min, max: max, step: 10)
        .layoutWeight(1)
        .onChange((v: number) => {
          onChange(v);
        })
      Text(`${value}`)
        .fontSize(11)
        .width(50)
    }
    .width('100%')
  }

  @Builder
  DocItem(api: string, desc: string): void {
    Row({ space: 8 }) {
      Text('●')
        .fontSize(10)
        .fontColor('#007DFF')
        .width(16)
      Column({ space: 2 }) {
        Text(api)
          .fontSize(11)
          .fontWeight(FontWeight.Medium)
          .fontColor('#007DFF')
          .fontFamily('monospace')
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
}

interface SlicePreset {
  name: string;
  left: number;
  right: number;
  top: number;
  bottom: number;
}
