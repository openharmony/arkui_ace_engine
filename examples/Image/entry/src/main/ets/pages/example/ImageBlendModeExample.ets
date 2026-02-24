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

/**
 * ========================================
 * 测试功能说明
 * ========================================
 * 本示例测试 Image 组件的混合模式（blendMode）功能
 *
 * 涉及的Image API:
 * 1. blendMode属性 - 图片混合模式
 * 2. opacity属性 - 透明度控制
 * 3. Stack组件 - 图片叠加容器
 *
 * ========================================
 * 如何测试
 * ========================================
 * 测试步骤:
 * 1. 进入 "混合模式 ImageBlendMode" 页面
 * 2. 观察混合效果预览区域，显示两层图片的混合结果
 * 3. 调整 "顶层图片透明度" 滑块，观察效果变化
 * 4. 在 "混合模式分类" 区域选择不同的混合模式
 * 5. 尝试常用混合模式（正常、正片叠底、滤色、叠加等）
 *
 * 预期结果:
 * - 不同混合模式产生不同的色彩合成效果
 * - 正片叠底使图像变暗
 * - 滤色使图像变亮
 * - 叠加增强对比度
 *
 * ========================================
 * Image API 知识点
 * ========================================
 * 1. blendMode 枚举值分类:
 *    - 基础: SrcOver (正常)
 *    - 变暗类: Darken, Multiply, ColorBurn, LinearBurn
 *    - 变亮类: Lighten, Screen, ColorDodge, LinearDodge
 *    - 对比类: Overlay, SoftLight, HardLight, VividLight, LinearLight, PinLight
 *    - 差值类: Difference, Exclusion
 *    - 颜色类: Hue, Saturation, Color, Luminosity
 *
 * 2. 常用混合模式效果:
 *    - SrcOver: 正常叠加，顶层覆盖底层
 *    - Multiply: 正片叠底，颜色相乘，结果更暗
 *    - Screen: 滤色，颜色反转相乘，结果更亮
 *    - Overlay: 叠加，结合Multiply和Screen
 *
 * 3. 使用场景:
 *    - Multiply: 阴影效果、去白底
 *    - Screen: 光效、提亮
 *    - Overlay: 增强对比度
 *    - Difference: 比较两张图差异
 *
 * 4. 注意事项:
 *    - blendMode 需要在 Stack 叠加两层图片时使用
 *    - 透明度影响混合效果强度
 *    - 不同混合模式适用于不同场景
 */
@Entry
@Component
struct ImageBlendModeExample {
  @State selectedMode: string = '正常';
  @State opacity: number = 100;

  private blendModes: string[] = [
    '正常', '变暗', '正片叠底', '颜色加深', '线性加深',
    '变亮', '滤色', '颜色减淡', '线性减淡', '叠加',
    '柔光', '强光', '亮光', '线性光', '点光',
    '差值', '排除', '色相', '饱和度', '颜色', '亮度'
  ];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('混合模式效果示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // 混合效果预览
        Column({ space: 15 }) {
          Text('混合效果预览 - ' + this.selectedMode)
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Stack() {
            // 底层图片
            Image($r('app.media.app_icon'))
              .width(300)
              .height(250)
              .objectFit(ImageFit.Cover)
              .borderRadius(15)

            // 顶层图片（应用混合模式）
            Image($r('app.media.png'))
              .width(300)
              .height(250)
              .objectFit(ImageFit.Cover)
              .borderRadius(15)
              .opacity(this.opacity / 100)
              .blendMode(this.getBlendMode())
          }
          .width(320)
          .height(270)
          .backgroundColor('#F0F0F0')
          .borderRadius(20)
          .shadow({ radius: 20, color: '#30000000' })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8FF')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 透明度控制
        Column({ space: 10 }) {
          Text('顶层图片透明度: ' + this.opacity + '%')
            .fontSize(16)
            .fontColor(Color.Gray)

          Slider({
            value: this.opacity,
            min: 0,
            max: 100,
            step: 5
          })
            .width('100%')
            .onChange((value: number) => {
              this.opacity = value;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 混合模式分类展示
        Column({ space: 15 }) {
          Text('混合模式分类:')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          // 变暗类
          this.BlendModeCategory('变暗类 (使图像变暗)', ['变暗', '正片叠底', '颜色加深', '线性加深'])

          // 变亮类
          this.BlendModeCategory('变亮类 (使图像变亮)', ['变亮', '滤色', '颜色减淡', '线性减淡'])

          // 对比类
          this.BlendModeCategory('对比类 (增强对比度)', ['叠加', '柔光', '强光'])

          // 差值类
          this.BlendModeCategory('差值类 (比较差异)', ['差值', '排除'])
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E6E6FA')
        .borderRadius(10)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 快速选择常用模式
        Column({ space: 15 }) {
          Text('常用混合模式:')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Grid() {
            ForEach(['正常', '正片叠底', '滤色', '叠加', '差值', '柔光'], (mode: string) => {
              GridItem() {
                Button(mode)
                  .fontSize(14)
                  .backgroundColor(this.selectedMode === mode ? Color.Blue : Color.Gray)
                  .onClick(() => {
                    this.selectedMode = mode;
                  })
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
        .backgroundColor('#FFF8DC')
        .borderRadius(10)

        // 操作按钮
        Row({ space: 15 }) {
          Button('重置')
            .fontSize(14)
            .backgroundColor(Color.Gray)
            .onClick(() => {
              this.selectedMode = '正常';
              this.opacity = 100;
            })

          Button('随机模式')
            .fontSize(14)
            .backgroundColor(Color.Purple)
            .onClick(() => {
              const randomIndex = Math.floor(Math.random() * this.blendModes.length);
              this.selectedMode = this.blendModes[randomIndex];
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Text('混合模式用于合成两张图片的效果')
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

  @Builder
  BlendModeCategory(title: string, modes: string[]) {
    Column({ space: 10 }) {
      Text(title)
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Row({ space: 8 }) {
        ForEach(modes, (mode: string) => {
          Button(mode)
            .fontSize(12)
            .backgroundColor(this.selectedMode === mode ? Color.Green : Color.LightGray)
            .onClick(() => {
              this.selectedMode = mode;
            })
        })
      }
      .width('100%')
      .flexWrap(FlexWrap.Wrap)
    }
    .width('100%')
  }

  getBlendMode(): BlendMode {
    switch (this.selectedMode) {
      case '正常': return BlendMode.SrcOver;
      case '变暗': return BlendMode.Darken;
      case '正片叠底': return BlendMode.Multiply;
      case '颜色加深': return BlendMode.ColorBurn;
      case '线性加深': return BlendMode.LinearBurn;
      case '变亮': return BlendMode.Lighten;
      case '滤色': return BlendMode.Screen;
      case '颜色减淡': return BlendMode.ColorDodge;
      case '线性减淡': return BlendMode.LinearDodge;
      case '叠加': return BlendMode.Overlay;
      case '柔光': return BlendMode.SoftLight;
      case '强光': return BlendMode.HardLight;
      case '亮光': return BlendMode.VividLight;
      case '线性光': return BlendMode.LinearLight;
      case '点光': return BlendMode.PinLight;
      case '差值': return BlendMode.Difference;
      case '排除': return BlendMode.Exclusion;
      case '色相': return BlendMode.Hue;
      case '饱和度': return BlendMode.Saturation;
      case '颜色': return BlendMode.Color;
      case '亮度': return BlendMode.Luminosity;
      default: return BlendMode.SrcOver;
    }
  }
}
