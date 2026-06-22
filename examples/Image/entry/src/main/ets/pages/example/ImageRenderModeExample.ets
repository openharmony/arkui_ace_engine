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
 * renderMode 渲染模式示例 (对齐官方示例 16)
 * ========================================
 * 功能说明:
 * 本示例演示如何通过 renderMode 属性将图片渲染为黑白（模板）模式。
 * 黑白模式下，图片会以单色显示，常用于图标主题化、禁用状态展示等场景。
 *
 * 涉及的 Image API:
 * 1. renderMode(ImageRenderMode.Original) - 原色渲染（默认）
 * 2. renderMode(ImageRenderMode.Template) - 黑白模板渲染
 * 3. fillColor(ResourceColor) - 配合 Template 模式可调整模板颜色
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 图标主题化：单色图标跟随主题色变化
 * - 禁用状态：将彩色图标转为灰色表示禁用
 * - 单色设计：符合极简设计风格的图标展示
 * - 深色模式：在深色模式下使用模板模式统一图标颜色
 *
 * ========================================
 * 注意事项
 * ========================================
 * 1. SVG 图源不支持 renderMode
 * 2. 设置 ColorFilter 时，renderMode 不生效
 * 3. AnimatedDrawableDescriptor 类型不生效
 * 4. Template 模式下图片会失去彩色信息
 */

@Entry
@Component
struct ImageRenderModeExample {
  @State renderMode: ImageRenderMode = ImageRenderMode.Original;
  @State templateColor: ResourceColor = '#333333';
  @State iconSize: number = 80;
  @State selectedIndex: number = 0;

  // 图标库
  private iconLibrary: Array<IconItem> = [
    { name: 'startIcon', res: $r('app.media.startIcon') },
    { name: 'svg', res: $r('app.media.svg') },
    { name: 'icon', res: $r('app.media.icon') },
    { name: 'star', res: $r('app.media.star') },
    { name: 'heart', res: $r('app.media.heart') }
  ];

  // 主题色预设
  private colorPresets: Array<ColorPreset> = [
    { name: '深灰', color: '#333333' },
    { name: '蓝色', color: '#007DFF' },
    { name: '红色', color: '#FF6347' },
    { name: '绿色', color: '#32CD32' },
    { name: '橙色', color: '#FFA500' },
    { name: '紫色', color: '#9370DB' }
  ];

  build(): void {
    Scroll() {
      Column({ space: 16 }) {
        Text('renderMode 渲染模式示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 8 })

        Text('对齐官方文档示例 16 · 原色 vs 黑白模板')
          .fontSize(12)
          .fontColor(Color.Gray)
          .margin({ bottom: 8 })

        // 效果对比
        Column({ space: 14 }) {
          Text('效果对比')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Row({ space: 12 }) {
            // 原色模式
            Column({ space: 8 }) {
              Text('Original (原色)')
                .fontSize(11)
                .fontColor('#32CD32')
              Image(this.iconLibrary[this.selectedIndex].res)
                .width(this.iconSize)
                .height(this.iconSize)
                .objectFit(ImageFit.Contain)
                .renderMode(ImageRenderMode.Original)
                .border({ width: 2, color: '#32CD32' })
                .borderRadius(12)
                .backgroundColor('#FAFAFA')
              Text('默认值')
                .fontSize(10)
                .fontColor(Color.Gray)
            }
            .layoutWeight(1)
            .alignItems(HorizontalAlign.Center)

            // 模板模式（黑白）
            Column({ space: 8 }) {
              Text('Template (模板)')
                .fontSize(11)
                .fontColor('#FF6347')
              Image(this.iconLibrary[this.selectedIndex].res)
                .width(this.iconSize)
                .height(this.iconSize)
                .objectFit(ImageFit.Contain)
                .renderMode(ImageRenderMode.Template)
                .border({ width: 2, color: '#FF6347' })
                .borderRadius(12)
                .backgroundColor('#FAFAFA')
              Text('黑白效果')
                .fontSize(10)
                .fontColor(Color.Gray)
            }
            .layoutWeight(1)
            .alignItems(HorizontalAlign.Center)
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)

          // 模板 + fillColor 组合
          Column({ space: 8 }) {
            Text(`Template + fillColor (${this.colorName(this.templateColor)})`)
              .fontSize(11)
              .fontColor('#007DFF')
            Image(this.iconLibrary[this.selectedIndex].res)
              .width(this.iconSize)
              .height(this.iconSize)
              .objectFit(ImageFit.Contain)
              .renderMode(ImageRenderMode.Template)
              .fillColor(this.templateColor)
              .border({ width: 2, color: this.templateColor })
              .borderRadius(12)
              .backgroundColor('#FAFAFA')
            Text('单色图标 (注: fillColor 主要对 SVG 生效)')
              .fontSize(10)
              .fontColor(Color.Gray)
          }
          .width('100%')
          .padding(12)
          .backgroundColor('#F8F8FF')
          .borderRadius(12)
          .alignItems(HorizontalAlign.Center)
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFFFFF')
        .borderRadius(16)

        // 图标切换
        Column({ space: 10 }) {
          Text('切换图标')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Row({ space: 6 }) {
            ForEach(
              this.iconLibrary,
              (item: IconItem, index: number) => {
                Button(item.name)
                  .fontSize(10)
                  .backgroundColor(this.selectedIndex === index ? '#007DFF' : '#E0E0E0')
                  .fontColor(this.selectedIndex === index ? Color.White : Color.Black)
                  .height(28)
                  .layoutWeight(1)
                  .onClick(() => {
                    this.selectedIndex = index;
                  })
              },
              (item: IconItem) => item.name
            )
          }
          .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#F0FFF0')
        .borderRadius(16)

        // 模板颜色选择
        Column({ space: 10 }) {
          Text('模板颜色 (fillColor)')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(
              this.colorPresets,
              (preset: ColorPreset) => {
                Row({ space: 6 }) {
                  Circle({ width: 18, height: 18 })
                    .fill(preset.color)
                    .border({ width: 1, color: '#E0E0E0' })
                  Text(preset.name)
                    .fontSize(11)
                    .fontColor(Color.Black)
                }
                .backgroundColor(this.templateColor === preset.color ? '#E6F7FF' : '#FAFAFA')
                .borderRadius(16)
                .padding({ left: 8, right: 12, top: 4, bottom: 4 })
                .margin({ right: 6, bottom: 6 })
                .onClick(() => {
                  this.templateColor = preset.color;
                })
              },
              (preset: ColorPreset) => `${preset.name}_${preset.color}`
            )
          }
          .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFF8DC')
        .borderRadius(16)

        // 尺寸调节
        Column({ space: 10 }) {
          Text('图标尺寸')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Row({ space: 8 }) {
            Text('尺寸')
              .fontSize(11)
              .width(50)
            Slider(value: this.iconSize, min: 32, max: 160, step: 8)
              .layoutWeight(1)
              .onChange((v: number) => {
                this.iconSize = v;
              })
            Text(`${this.iconSize}px`)
              .fontSize(11)
              .width(50)
          }
          .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#E6F7FF')
        .borderRadius(16)

        // 应用场景：导航栏
        Column({ space: 10 }) {
          Text('应用场景：底部导航栏')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Row() {
            this.TabItem('首页', 0)
            this.TabItem('分类', 1)
            this.TabItem('收藏', 2)
            this.TabItem('我的', 3)
          }
          .width('100%')
          .height(64)
          .backgroundColor('#FFFFFF')
          .borderRadius(12)
          .border({ width: 1, color: '#E0E0E0' })
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFE4E1')
        .borderRadius(16)

        // 应用场景：图标网格
        Column({ space: 10 }) {
          Text('应用场景：功能图标网格')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Grid() {
            ForEach(
              this.iconLibrary,
              (item: IconItem, index: number) => {
                GridItem() {
                  Column({ space: 6 }) {
                    Image(item.res)
                      .width(40)
                      .height(40)
                      .objectFit(ImageFit.Contain)
                      .renderMode(index % 2 === 0 ? ImageRenderMode.Template : ImageRenderMode.Original)
                      .fillColor(this.templateColor)
                    Text(item.name)
                      .fontSize(9)
                      .fontColor(Color.Gray)
                  }
                  .width('100%')
                  .padding(8)
                  .alignItems(HorizontalAlign.Center)
                }
              },
              (item: IconItem) => item.name
            )
          }
          .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
          .rowsGap(8)
          .columnsGap(4)
          .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#F5F5F5')
        .borderRadius(16)

        // API 说明
        Column({ space: 8 }) {
          Text('API 说明')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.DocItem('ImageRenderMode.Original', '原色渲染（默认）')
          this.DocItem('ImageRenderMode.Template', '模板渲染（黑白）')
          this.DocItem('fillColor(color)', '配合 Template 模式调整单色，主要对 SVG 生效')
          this.DocItem('限制条件', 'SVG / ColorFilter 设置时 / AnimatedDrawableDescriptor 不生效')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#F8F8FF')
        .borderRadius(16)

        Text('提示：Template 模式适合主题化图标，fillColor 仅对 SVG 完整生效')
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
  TabItem(label: string, index: number): void {
    Column({ space: 4 }) {
      Image(this.iconLibrary[index % this.iconLibrary.length].res)
        .width(24)
        .height(24)
        .objectFit(ImageFit.Contain)
        .renderMode(index === 0 ? ImageRenderMode.Template : ImageRenderMode.Original)
        .fillColor(index === 0 ? this.templateColor : '#888888')
      Text(label)
        .fontSize(10)
        .fontColor(index === 0 ? this.templateColor : '#888888')
    }
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
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

  private colorName(color: ResourceColor): string {
    const preset: ColorPreset | undefined = this.colorPresets.find(
      (p: ColorPreset): boolean => p.color === color
    );
    return preset ? preset.name : '自定义';
  }
}

interface IconItem {
  name: string;
  res: Resource;
}

interface ColorPreset {
  name: string;
  color: ResourceColor;
}
