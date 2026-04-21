/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * ========================================
 * SVG2 特性专项示例 (API 21+)
 * ========================================
 * 测试功能说明:
 * 本示例专项测试 Image 组件的 SVG2 特性支持 (API 21+)
 *
 * 涉及的 Image API:
 * 1. supportSvg2 - 启用 SVG2 特性支持
 * 2. SVG2 新特性：混合模式、滤镜、动画等
 * 3. fillColor 与 SVG2 的配合
 *
 * ========================================
 * 如何测试
 * ========================================
 * 测试步骤:
 * 1. 进入 "SVG2 特性" 页面
 * 2. 切换 SVG1/SVG2 模式
 * 3. 观察不同特性渲染效果
 * 4. 测试滤镜和混合模式
 *
 * 预期结果:
 * - SVG2 模式支持更多特性
 * - 滤镜效果正常渲染
 * - 动画流畅播放
 *
 * ========================================
 * Image API 知识点
 * ========================================
 * 1. supportSvg2 属性 (API 21+):
 *    - true: 启用 SVG2 规范支持
 *    - false: 使用 SVG1.1 规范 (默认)
 *
 * 2. SVG2 新特性:
 *    - 增强的混合模式支持
 *    - 更丰富的滤镜效果
 *    - 改进的文本渲染
 *    - 更好的 CSS 集成
 *    - 动画性能优化
 *
 * 3. 使用场景:
 *    - 复杂 SVG 图形渲染
 *    - 高级滤镜效果
 *    - 动态 SVG 动画
 *
 * 4. 注意事项:
 *    - SVG2 从 API 21 开始支持
 *    - 部分旧设备可能不支持
 *    - 性能开销略高于 SVG1.1
 */

@Entry
@Component
struct ImageSVG2Example {
  @State isSvg2Enabled: boolean = true;
  @State selectedEffect: string = 'none';
  @State animationPlaying: boolean = false;

  // SVG2 特效选项
  private svg2Effects: Array<{ key: string; label: string; desc: string }> = [
    { key: 'none', label: '无特效', desc: '原始 SVG 显示' },
    { key: 'blur', label: '高斯模糊', desc: 'SVG2 滤镜效果' },
    { key: 'brightness', label: '亮度调节', desc: 'SVG2 亮度滤镜' },
    { key: 'contrast', label: '对比度', desc: 'SVG2 对比度滤镜' },
    { key: 'grayscale', label: '灰度', desc: 'SVG2 灰度滤镜' },
    { key: 'hueRotate', label: '色相旋转', desc: 'SVG2 色相滤镜' }
  ];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG2 特性专项示例 (API 21+)')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // SVG2 开关
        Column({ space: 15 }) {
          Text('SVG2 支持开关')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Row({ space: 15 }) {
            Toggle({ type: ToggleType.Switch, isOn: this.isSvg2Enabled })
              .onChange((isOn: boolean) => {
                this.isSvg2Enabled = isOn;
              })

            Text(this.isSvg2Enabled ? 'SVG2 已启用' : 'SVG1.1 模式')
              .fontSize(16)
              .fontColor(this.isSvg2Enabled ? Color.Green : Color.Gray)
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceBetween)
          .padding(15)
          .backgroundColor(this.isSvg2Enabled ? '#E8F5E9' : '#FFEBEE')
          .borderRadius(10)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8FF')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 主展示区
        Column({ space: 15 }) {
          Text('SVG 渲染效果')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Stack() {
            Image($r('app.media.svg'))
              .width(200)
              .height(200)
              .supportSvg2(this.isSvg2Enabled)
              .filter(this.getSvgFilter())
              .animation({
                duration: 2000,
                iterations: -1,
                play: this.animationPlaying
              })
              .borderRadius(20)
              .shadow({ radius: 20, color: '#30000000' })

            // SVG2 标识
            if (this.isSvg2Enabled) {
              Badge({ count: 1, style: BadgeStyle.Small }) {
                Text('SVG2')
                  .fontSize(10)
                  .fontColor(Color.White)
                  .padding(5)
                  .backgroundColor(Color.Green)
                  .borderRadius(5)
                  .position({ x: 10, y: 10 })
              }
              .position({ x: -80, y: -80 })
              .badgeStyle({
                backgroundColor: Color.Green,
                autoCount: false
              })
            }
          }
          .width(220)
          .height(220)
          .backgroundColor('#F0F0F0')
          .borderRadius(25)
          .margin({ top: 10 })
        }
        .width('100%')
        .padding(20)
        .backgroundColor('#FFFFFF')
        .borderRadius(20)

        Divider().strokeWidth(2).color('#E0E0E0')

        // SVG2 滤镜选择
        Column({ space: 15 }) {
          Text('SVG2 滤镜效果')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Grid() {
            ForEach(this.svg2Effects, (item: { key: string; label: string; desc: string }) => {
              GridItem() {
                Column({ space: 10 }) {
                  Image($r('app.media.svg'))
                    .width(60)
                    .height(60)
                    .supportSvg2(this.isSvg2Enabled)
                    .filter(this.getFilterByKey(item.key))
                    .borderRadius(10)

                  Text(item.label)
                    .fontSize(12)
                    .fontColor(Color.Black)
                  Text(item.desc)
                    .fontSize(10)
                    .fontColor(Color.Gray)

                  Button('应用')
                    .fontSize(10)
                    .padding({ left: 10, right: 10 })
                    .backgroundColor(this.selectedEffect === item.key ? Color.Blue : Color.LightGray)
                    .onClick(() => {
                      this.selectedEffect = item.key;
                    })
                }
                .padding(10)
                .backgroundColor(this.selectedEffect === item.key ? '#E3F2FD' : '#F5F5F5')
                .borderRadius(10)
                .width('100%')
              }
            })
          }
          .columnsTemplate('1fr 1fr 1fr')
          .rowsGap(10)
          .columnsGap(10)
          .width('100%')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // SVG2 特性说明
        Column({ space: 15 }) {
          Text('SVG2 vs SVG1.1 特性对比')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Column({ space: 10 }) {
            this.FeatureRow('混合模式', '基础支持', '完整支持 21 种模式')
            this.FeatureRow('滤镜效果', '有限支持', '完整 SVG 滤镜支持')
            this.FeatureRow('文本渲染', '基础', '改进的文本布局')
            this.FeatureRow('动画性能', '标准', '优化的动画引擎')
            this.FeatureRow('CSS 集成', '部分', '完整 CSS 样式支持')
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFF8DC')
          .borderRadius(10)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E6E6FA')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 动画控制
        Column({ space: 15 }) {
          Text('SVG 动画控制')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Row({ space: 15 }) {
            Button(this.animationPlaying ? '停止动画' : '播放动画')
              .fontSize(14)
              .backgroundColor(this.animationPlaying ? Color.Orange : Color.Green)
              .onClick(() => {
                this.animationPlaying = !this.animationPlaying;
              })

            Button('重置')
              .fontSize(14)
              .backgroundColor(Color.Gray)
              .onClick(() => {
                this.animationPlaying = false;
                this.selectedEffect = 'none';
                this.isSvg2Enabled = true;
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F0F8FF')
        .borderRadius(15)

        Text('supportSvg2 启用后可使用 SVG2 规范的高级特性，推荐在 API 21+ 设备上启用以获得更好的渲染效果。')
          .fontSize(12)
          .fontColor(Color.Blue)
          .margin({ top: 10, bottom: 20 })
      }
      .width('100%')
      .padding({ left: 20, right: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.White)
  }

  // 根据选择的特效返回对应的滤镜
  getSvgFilter(): string {
    return this.getFilterByKey(this.selectedEffect);
  }

  getFilterByKey(key: string): string {
    switch (key) {
      case 'blur':
        return 'blur(5px)';
      case 'brightness':
        return 'brightness(1.5)';
      case 'contrast':
        return 'contrast(1.5)';
      case 'grayscale':
        return 'grayscale(1)';
      case 'hueRotate':
        return 'hue-rotate(90deg)';
      default:
        return 'none';
    }
  }

  @Builder
  FeatureRow(feature: string, svg1: string, svg2: string) {
    Row({ space: 10 }) {
      Text(feature)
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width(100)

      Text(svg1)
        .fontSize(14)
        .fontColor(Color.Gray)
        .width(100)

      Text(svg2)
        .fontSize(14)
        .fontColor(Color.Green)
        .width(150)
    }
    .width('100%')
    .padding({ top: 8, bottom: 8 })
  }
}
