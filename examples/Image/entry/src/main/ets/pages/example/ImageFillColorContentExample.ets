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
 * fillColor ColorContent 类型示例 (API 20+)
 * ========================================
 * 测试功能说明:
 * 本示例测试 Image 组件 fillColor 属性的 ColorContent 类型 (API 20+)
 *
 * 涉及的 Image API:
 * 1. fillColor(ColorContent) - 使用 ColorContent 类型设置填充色
 * 2. ColorContent.ORIGIN - 保持 SVG 原始颜色
 * 3. ColorMetrics - 广色域颜色支持 (API 15+)
 *
 * ========================================
 * 如何测试
 * ========================================
 * 测试步骤:
 * 1. 进入 "fillColor ColorContent" 页面
 * 2. 点击不同颜色按钮，观察 SVG 图片颜色变化
 * 3. 测试 ColorContent.ORIGIN 恢复原始颜色
 * 4. 对比 P3 和 sRGB 色域差异
 *
 * 预期结果:
 * - SVG 图片可动态切换填充颜色
 * - ColorContent.ORIGIN 恢复原始颜色
 * - P3 色域颜色更鲜艳
 *
 * ========================================
 * Image API 知识点
 * ========================================
 * 1. fillColor 类型演进:
 *    - API 7-14: 仅支持 Color 类型
 *    - API 15+: 支持 ColorMetrics (广色域)
 *    - API 20+: 支持 ColorContent (包含 ORIGIN 等特殊值)
 *
 * 2. ColorContent 枚举值:
 *    - ColorContent.ORIGIN: 保持 SVG 原始颜色
 *    - Color 类型：标准颜色
 *    - ColorMetrics 类型：广色域颜色
 *    - undefined: 清除填充色
 *
 * 3. 使用场景:
 *    - SVG 图标主题切换
 *    - 动态颜色系统
 *    - 广色域显示优化
 *
 * 4. 注意事项:
 *    - 仅对 SVG 图源有效
 *    - ColorContent 从 API 20 开始支持
 *    - P3 色域需要硬件支持
 */

import { ColorMetrics, ColorSpace, ColorContent } from '@kit.ArkUI';

@Entry
@Component
struct ImageFillColorContentExample {
  @State currentColor: Color | undefined | ColorMetrics | ColorContent = Color.Blue;
  @State colorIndex: number = 0;
  
  // 颜色选项数组
  private colorOptions: Array<{
    name: string;
    color: Color | undefined | ColorMetrics | ColorContent;
    description: string;
  }> = [
    { name: '标准蓝', color: Color.Blue, description: '标准 sRGB 蓝色' },
    { name: '标准红', color: Color.Red, description: '标准 sRGB 红色' },
    { name: '标准绿', color: Color.Green, description: '标准 sRGB 绿色' },
    { name: 'P3 红色', color: ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294), description: 'Display P3 色域红色 (更鲜艳)' },
    { name: 'P3 绿色', color: ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.09, 0.662, 0.552), description: 'Display P3 色域绿色' },
    { name: 'P3 蓝色', color: ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 0.290, 0.686), description: 'Display P3 色域蓝色' },
    { name: '原始色', color: ColorContent.ORIGIN, description: '保持 SVG 原始颜色 (API 20+)' },
    { name: '灰色', color: Color.Gray, description: '标准灰色' },
    { name: '清除', color: undefined, description: '清除填充色' }
  ];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('fillColor ColorContent 示例 (API 20+)')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // 主展示区
        Column({ space: 15 }) {
          Text('当前颜色：' + this.colorOptions[this.colorIndex]?.name)
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Text(this.colorOptions[this.colorIndex]?.description || '')
            .fontSize(14)
            .fontColor(Color.Gray)

          // SVG 图片展示
          Stack() {
            Image($r('app.media.svg'))
              .width(200)
              .height(200)
              .fillColor(this.currentColor)
              .borderRadius(20)
              .shadow({ radius: 20, color: '#30000000' })

            // 颜色指示器
            Circle()
              .width(30)
              .height(30)
              .fill(this.getColorPreview(this.currentColor))
              .position({ x: 160, y: 160 })
              .stroke(Color.White)
              .strokeWidth(3)
          }
          .width(220)
          .height(220)
          .backgroundColor('#F0F0F0')
          .borderRadius(25)
          .margin({ top: 20 })
        }
        .width('100%')
        .padding(20)
        .backgroundColor('#F8F8FF')
        .borderRadius(20)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 颜色选择器
        Column({ space: 15 }) {
          Text('颜色选择')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          // 快速切换按钮
          Grid() {
            ForEach(this.colorOptions, (item: { name: string; color: Color | undefined | ColorMetrics | ColorContent }, index: number) => {
              GridItem() {
                Button(item.name)
                  .fontSize(12)
                  .backgroundColor(this.colorIndex === index ? Color.Blue : Color.LightGray)
                  .fontColor(this.colorIndex === index ? Color.White : Color.Black)
                  .onClick(() => {
                    this.currentColor = item.color;
                    this.colorIndex = index;
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
        .backgroundColor('#F5F5F5')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 色域对比
        Column({ space: 15 }) {
          Text('色域对比 (P3 vs sRGB)')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Row({ space: 20 }) {
            // P3 色域
            Column({ space: 10 }) {
              Text('Display P3')
                .fontSize(14)
                .fontColor(Color.Gray)
              Image($r('app.media.svg'))
                .width(100)
                .height(100)
                .fillColor(ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294))
                .borderRadius(10)
              Text('更鲜艳的红色')
                .fontSize(12)
                .fontColor(Color.Gray)
            }
            .padding(15)
            .backgroundColor('#FFE0E0')
            .borderRadius(15)

            // sRGB 色域
            Column({ space: 10 }) {
              Text('sRGB')
                .fontSize(14)
                .fontColor(Color.Gray)
              Image($r('app.media.svg'))
                .width(100)
                .height(100)
                .fillColor(Color.Red)
                .borderRadius(10)
              Text('标准红色')
                .fontSize(12)
                .fontColor(Color.Gray)
            }
            .padding(15)
            .backgroundColor('#FFE0E0')
            .borderRadius(15)
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#FFF8DC')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // ColorContent.ORIGIN 专项说明
        Column({ space: 15 }) {
          Text('ColorContent.ORIGIN 说明')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Row({ space: 20 }) {
            // 原始 SVG 颜色
            Column({ space: 10 }) {
              Text('原始颜色')
                .fontSize(14)
                .fontColor(Color.Gray)
              Image($r('app.media.svg'))
                .width(100)
                .height(100)
                .fillColor(ColorContent.ORIGIN)
                .borderRadius(10)
            }
            .padding(15)
            .backgroundColor('#E0FFE0')
            .borderRadius(15)

            // 应用 fillColor 后
            Column({ space: 10 }) {
              Text('应用 fillColor')
                .fontSize(14)
                .fontColor(Color.Gray)
              Image($r('app.media.svg'))
                .width(100)
                .height(100)
                .fillColor(Color.Purple)
                .borderRadius(10)
            }
            .padding(15)
            .backgroundColor('#E0FFE0')
            .borderRadius(15)
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)

          Text('ColorContent.ORIGIN 可恢复 SVG 原始颜色，常用于重置状态')
            .fontSize(14)
            .fontColor(Color.Blue)
            .margin({ top: 10 })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E6E6FA')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 操作按钮
        Row({ space: 15 }) {
          Button('下一个颜色')
            .fontSize(14)
            .backgroundColor(Color.Blue)
            .onClick(() => {
              this.colorIndex = (this.colorIndex + 1) % this.colorOptions.length;
              this.currentColor = this.colorOptions[this.colorIndex].color;
            })

          Button('重置')
            .fontSize(14)
            .backgroundColor(Color.Gray)
            .onClick(() => {
              this.colorIndex = 0;
              this.currentColor = Color.Blue;
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Text('fillColor 支持 Color、ColorMetrics、ColorContent 和 undefined，API 20+ 推荐使用 ColorContent')
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

  // 获取颜色预览 (用于指示器)
  getColorPreview(color: Color | undefined | ColorMetrics | ColorContent): Color {
    if (color === undefined) {
      return Color.Transparent;
    }
    if (color === ColorContent.ORIGIN) {
      return Color.Blue; // ORIGIN 无法预览，用蓝色代替
    }
    // ColorMetrics 无法直接转换，返回蓝色
    if (color instanceof ColorMetrics) {
      return Color.Blue;
    }
    return color as Color;
  }
}
