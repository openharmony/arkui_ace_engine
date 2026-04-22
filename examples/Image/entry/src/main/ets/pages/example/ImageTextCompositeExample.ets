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

/**
 * Image 与 Text 组合示例
 * 演示 Image 和 Text 组件的组合使用
 */
@Entry
@Component
struct ImageTextCompositeExample {
  @State currentLayout: number = 0;
  @State imageAlignment: Alignment = Alignment.Center;
  @State textAlignment: Alignment = Alignment.Center;
  @State showTextOverlay: boolean = true;
  @State showTextBelow: boolean = false;
  @State showTextBeside: boolean = false;
  @State enableTextShadow: boolean = true;
  @State enableImageBorder: boolean = true;
  @State overlayOpacity: number = 0.8;
  @State overlayBackgroundColor: string = 'rgba(0, 0, 0, 0.5)';
  @State currentImageFit: ImageFit = ImageFit.Cover;
  @State currentTextAlign: TextAlign = TextAlign.Center;
  @State selectedDemo: number = 0;

  layouts: string[] = ['图片在上', '文字在上', '左右布局', '网格布局'];
  demoNames: string[] = ['图文卡片', '新闻列表', '产品展示', '画廊模式'];

  imageFitOptions: ImageFit[] = [
    ImageFit.Cover,
    ImageFit.Contain,
    ImageFit.Fill,
    ImageFit.None
  ];

  textAlignOptions: TextAlign[] = [
    TextAlign.Start,
    TextAlign.Center,
    TextAlign.End
  ];

  @Builder
  ImageTopLayout() {
    Column({ space: 20 }) {
      Text('图片在上布局')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      // 图片在上，文字在下
      Column({ space: 15 }) {
        Image($r('app.media.img'))
          .width('100%')
          .height(300)
          .border(this.enableImageBorder ? { width: 2, color: Color.Blue, radius: 10 } : {})
          .borderRadius(10)
          .objectFit(this.currentImageFit)

        Column({ space: 10 }) {
          Text('图片标题')
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
            .textAlign(this.currentTextAlign)
            .width('100%')

          Text('这是图片的描述文字，可以包含多行内容。')
            .fontSize(14)
            .fontColor(0x666666)
            .textAlign(this.currentTextAlign)
            .maxLines(3)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .lineHeight(20)
            .width('100%')

          Row({ space: 10 }) {
            Text('标签1')
              .fontSize(12)
              .padding({ left: 10, right: 10, top: 5, bottom: 5 })
              .backgroundColor(0x007DFF)
              .borderRadius(15)
              .fontColor(Color.White)

            Text('标签2')
              .fontSize(12)
              .padding({ left: 10, right: 10, top: 5, bottom: 5 })
              .backgroundColor(0xFF5252)
              .borderRadius(15)
              .fontColor(Color.White)
          }
        }
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)
        .shadow({ radius: 10, color: 0x1A000000, offsetX: 0, offsetY: 4 })
      }
      .width('100%')
    }
    .padding(20)
  }

  @Builder
  TextTopLayout() {
    Column({ space: 20 }) {
      Text('文字在上布局')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      // 文字在上，图片在下
      Column({ space: 15 }) {
        Column({ space: 10 }) {
          Text('文字标题')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .textAlign(this.currentTextAlign)
            .width('100%')

          Text('这是上方的文字内容，可以在图片上方显示。')
            .fontSize(16)
            .fontColor(0x666666)
            .textAlign(this.currentTextAlign)
            .lineHeight(24)
            .width('100%')
        }
        .padding(15)
        .backgroundColor(0xF0F0F0)
        .borderRadius({ topLeft: 10, topRight: 10 })

        Image($r('app.media.jpg'))
          .width('100%')
          .height(300)
          .border(this.enableImageBorder ? { width: 2, color: Color.Green, radius: 10 } : {})
          .borderRadius({ bottomLeft: 10, bottomRight: 10 })
          .objectFit(this.currentImageFit)

        Text('底部说明文字')
          .fontSize(14)
          .fontColor(0x999999)
          .textAlign(this.currentTextAlign)
          .padding(10)
          .width('100%')
      }
      .width('100%')
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
      .shadow({ radius: 10, color: 0x1A000000, offsetX: 0, offsetY: 4 })
    }
    .padding(20)
  }

  @Builder
  LeftRightLayout() {
    Column({ space: 20 }) {
      Text('左右布局')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      // 图片在左，文字在右
      Row({ space: 20 }) {
        Image($r('app.media.png'))
          .width(200)
          .height(200)
          .border(this.enableImageBorder ? { width: 2, color: Color.Orange, radius: 10 } : {})
          .borderRadius(10)
          .objectFit(this.currentImageFit)

        Column({ space: 10 }) {
          Text('右侧文字内容')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .textAlign(this.currentTextAlign)

          Text('这是图片右侧的文字描述，可以包含详细说明信息。')
            .fontSize(14)
            .fontColor(0x666666)
            .textAlign(this.currentTextAlign)
            .lineHeight(20)
            .maxLines(4)
            .textOverflow({ overflow: TextOverflow.Ellipsis })

          Text('更多内容...')
            .fontSize(12)
            .fontColor(0x007DFF)
            .decoration({
              type: TextDecorationType.Underline,
              color: 0x007DFF
            })
        }
        .layoutWeight(1)
        .alignItems(this.textAlignment === Alignment.Center ? VerticalAlign.Center : 
                    this.textAlignment === Alignment.Top ? VerticalAlign.Top : VerticalAlign.Bottom)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
      .shadow({ radius: 10, color: 0x1A000000, offsetX: 0, offsetY: 4 })
    }
    .padding(20)
  }

  @Builder
  GridLayout() {
    Column({ space: 20 }) {
      Text('网格布局')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Grid() {
        GridItem() {
          Column({ space: 10 }) {
            Image($r('app.media.img'))
              .width('100%')
              .aspectRatio(1)
              .borderRadius(8)
              .objectFit(ImageFit.Cover)

            Text('网格项1')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .textAlign(TextAlign.Center)
              .maxLines(2)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
          }
          .backgroundColor(0xFFFFFF)
          .borderRadius(10)
          .shadow({ radius: 6, color: 0x1A000000, offsetX: 0, offsetY: 2 })
        }

        GridItem() {
          Column({ space: 10 }) {
            Image($r('app.media.jpg'))
              .width('100%')
              .aspectRatio(1)
              .borderRadius(8)
              .objectFit(ImageFit.Cover)

            Text('网格项2')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .textAlign(TextAlign.Center)
              .maxLines(2)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
          }
          .backgroundColor(0xFFFFFF)
          .borderRadius(10)
          .shadow({ radius: 6, color: 0x1A000000, offsetX: 0, offsetY: 2 })
        }

        GridItem() {
          Column({ space: 10 }) {
            Image($r('app.media.png'))
              .width('100%')
              .aspectRatio(1)
              .borderRadius(8)
              .objectFit(ImageFit.Cover)

            Text('网格项3')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .textAlign(TextAlign.Center)
              .maxLines(2)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
          }
          .backgroundColor(0xFFFFFF)
          .borderRadius(10)
          .shadow({ radius: 6, color: 0x1A000000, offsetX: 0, offsetY: 2 })
        }

        GridItem() {
          Column({ space: 10 }) {
            Image($r('app.media.gif'))
              .width('100%')
              .aspectRatio(1)
              .borderRadius(8)
              .objectFit(ImageFit.Cover)

            Text('网格项4')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .textAlign(TextAlign.Center)
              .maxLines(2)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
          }
          .backgroundColor(0xFFFFFF)
          .borderRadius(10)
          .shadow({ radius: 6, color: 0x1A000000, offsetX: 0, offsetY: 2 })
        }
      }
      .columnsTemplate('1fr 1fr')
      .rowsGap(15)
      .columnsGap(15)
      .padding(15)
    }
    .padding(20)
  }

  @Builder
  NewsCardDemo() {
    Column({ space: 15 }) {
      Text('图文卡片示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      // 新闻卡片
      Column({ space: 15 }) {
        Image($r('app.media.img'))
          .width('100%')
          .height(200)
          .borderRadius({ topLeft: 10, topRight: 10 })
          .objectFit(ImageFit.Cover)

        Column({ space: 10 }) {
          Text('新闻标题')
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
            .maxLines(2)
            .textOverflow({ overflow: TextOverflow.Ellipsis })

          Row({ space: 10 }) {
            Text('2024-01-15')
              .fontSize(12)
              .fontColor(0x999999)

            Text('作者')
              .fontSize(12)
              .fontColor(0x666666)

            Text('阅读量: 1234')
              .fontSize(12)
              .fontColor(0x007DFF)
          }

          Text('这是新闻的摘要内容，显示在图片下方。可以包含多行文字，支持文本溢出省略号显示。')
            .fontSize(14)
            .fontColor(0x666666)
            .lineHeight(20)
            .maxLines(3)
            .textOverflow({ overflow: TextOverflow.Ellipsis })

          Row({ space: 10 }) {
            Button('阅读全文')
              .type(ButtonType.Normal)
              .backgroundColor(0x007DFF)
              .borderRadius(20)

            Button('分享')
              .type(ButtonType.Normal)
              .backgroundColor(0xF5F5F5)
              .borderRadius(20)
          }
        }
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius({ bottomLeft: 10, bottomRight: 10 })
        .shadow({ radius: 10, color: 0x1A000000, offsetX: 0, offsetY: 4 })
      }
      .width('100%')
    }
    .padding(20)
  }

  @Builder
  ProductShowDemo() {
    Column({ space: 15 }) {
      Text('产品展示示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Row({ space: 20 }) {
        // 产品图片
        Column({ space: 10 }) {
          Image($r('app.media.jpg'))
            .width(200)
            .height(200)
            .borderRadius(10)
            .objectFit(ImageFit.Contain)
            .border({ width: 2, color: Color.Orange })

          Text('¥99.00')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .fontColor(0xFF5252)
            .textAlign(TextAlign.Center)
        }

        // 产品信息
        Column({ space: 15 }) {
          Text('产品名称')
            .fontSize(22)
            .fontWeight(FontWeight.Bold)

          Text('产品描述文字，详细介绍产品的特点和优势。')
            .fontSize(14)
            .fontColor(0x666666)
            .lineHeight(20)
            .maxLines(3)
            .textOverflow({ overflow: TextOverflow.Ellipsis })

          Column({ space: 8 }) {
            Text('规格参数')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)

            Text('• 参数1: 值1')
              .fontSize(12)
              .fontColor(0x666666)

            Text('• 参数2: 值2')
              .fontSize(12)
              .fontColor(0x666666)

                       Text('• 参数3: 值3')
              .fontSize(12)
              .fontColor(0x666666)
          }

          Row({ space: 15 }) {
            Button('加入购物车')
              .type(ButtonType.Normal)
              .backgroundColor(0x007DFF)
              .borderRadius(25)

            Button('立即购买')
              .type(ButtonType.Normal)
              .backgroundColor(0xFF5252)
              .borderRadius(25)
          }
        }
        .layoutWeight(1)
        .justifyContent(FlexAlign.SpaceBetween)
      }
      .width('100%')
      .padding(20)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
      .shadow({ radius: 10, color: 0x1A000000, offsetX: 0, offsetY: 4 })
    }
    .padding(20)
  }

  @Builder
  GalleryModeDemo() {
    Column({ space: 15 }) {
      Text('画廊模式示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Text('点击图片查看详情')
        .fontSize(14)
        .fontColor(0x666666)

      Grid() {
        ForEach([1, 2, 3, 4, 5, 6], (item: number) => {
          GridItem() {
            Column({ space: 8 }) {
              Image($r('app.media.img'))
                .width('100%')
                .aspectRatio(1)
                .borderRadius(8)
                .objectFit(ImageFit.Cover)
                .onClick(() => {
                  console.info(`点击图片 ${item}`);
                })

              if (this.showTextOverlay) {
                Text(`图片 ${item}`)
                  .fontSize(12)
                  .fontWeight(FontWeight.Medium)
                  .fontColor(Color.White)
                  .textAlign(TextAlign.Center)
                  .padding(5)
                  .backgroundColor(this.overlayBackgroundColor)
                  .opacity(this.overlayOpacity)
          }
              .borderRadius(10)
              .shadow({ radius: 6, color: 0x1A000000, offsetX: 0, offsetY: 2 })
          }
        })
      }
      .columnsTemplate('1fr 1fr 1fr')
      .rowsGap(15)
      .columnsGap(15)
      .padding(15)
    }
    .padding(20)
  }

  @Builder
  ControlPanel() {
    Column({ space: 15 }) {
      Text('控制面板')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)

      // 布局选择
      Column({ space: 8 }) {
        Text('布局模式')
          .fontSize(14)
          .fontColor(0x666666)

        Row({ space: 10 }) {
          ForEach(this.layouts, (layout: string, index: number) => {
            Button(layout)
              .type(this.currentLayout === index ? ButtonType.Capsule : ButtonType.Normal)
              .fontSize(12)
              .backgroundColor(this.currentLayout === index ? 0x007DFF : 0xF5F5F5)
              .onClick(() => {
                this.currentLayout = index;
              })
          })
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)

      // 图片对齐
    Column({ space: 8 }) {
        Text('图片对齐')
          .fontSize(14)
          .fontColor(0x666666)

        Row({ space: 10 }) {
          Button('顶部')
            .type(this.imageAlignment === Alignment.Top ? ButtonType.Capsule : ButtonType.Normal)
            .fontSize(12)
            .backgroundColor(this.imageAlignment === Alignment.Top ? 0x007DFF : 0xF5F5F5)
            .onClick(() => {
              this.imageAlignment = Alignment.Top;
            })

          Button('居中')
            .type(this.imageAlignment === Alignment.Center ? ButtonType.Capsule : ButtonType.Normal)
            .fontSize(12)
            .backgroundColor(this.imageAlignment === Alignment.Center ? 0x007DFF : 0xF5F5F5)
            .onClick(() => {
              this.imageAlignment = Alignment.Center;
            })

          Button('底部')
            .type(this.imageAlignment === Alignment.Bottom ? ButtonType.Capsule : ButtonType.Normal)
            .fontSize(12)
            .backgroundColor(this.imageAlignment === Alignment.Bottom ? 0x007DFF : 0xF5F5F5)
            .onClick(() => {
              this.imageAlignment = Alignment.Bottom;
            })
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)

      // 文字对齐
    Column({ space: 8 }) {
        Text('文字对齐')
          .fontSize(14)
          .fontColor(0x666666)

        Row({ space: 10 }) {
          Button('左对齐')
            .type(this.textAlignment === Alignment.Start ? ButtonType.Capsule : ButtonType.Normal)
            .fontSize(12)
            .backgroundColor(this.textAlignment === Alignment.Start ? 0x007DFF : 0xF5F5F5)
            .onClick(() => {
              this.textAlignment = Alignment.Start;
            })

          Button('居中')
            .type(this.textAlignment === Alignment.Center ? ButtonType.Capsule : ButtonType.Normal)
            .fontSize(12)
            .backgroundColor(this.textAlignment === Alignment.Center ? 0x007DFF : 0xF5F5F5)
            .onClick(() => {
              this.textAlignment = Alignment.Center;
            })

          Button('右对齐')
            .type(this.textAlignment === Alignment.End ? ButtonType.Capsule : ButtonType.Normal)
            .fontSize(12)
            .backgroundColor(this.textAlignment === Alignment.End ? 0x007DFF : 0xF5F5F5)
            .onClick(() => {
              this.textAlignment = Alignment.End;
            })
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)

      // 布尔开关
    Column({ space: 10 }) {
        Text('显示选项')
          .fontSize(14)
          .fontColor(0x666666)

        Row({ space: 20 }) {
          Toggle({ type: ToggleType.Switch, isOn: this.showTextOverlay })
            .onChange((isOn: boolean) => {
              this.showTextOverlay = isOn;
            })
          Text('文字覆盖')
            .fontSize(12)
        }

        Row({ space: 20 }) {
          Toggle({ type: ToggleType.Switch, isOn: this.showTextBelow })
            .onChange((isOn: boolean) => {
              this.showTextBelow = isOn;
            })
          Text('文字下方')
            .fontSize(12)
        }

        Row({ space: 20 }) {
          Toggle({ type: ToggleType.Switch, isOn: this.showTextBeside })
            .onChange((isOn: boolean) => {
              this.showTextBeside = isOn;
            })
          Text('文字侧边')
            .fontSize(12)
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)

      // 样式选项
    Column({ space: 10 }) {
        Text('样式选项')
          .fontSize(14)
          .fontColor(0x666666)

        Row({ space: 20 }) {
          Toggle({ type: ToggleType.Switch, isOn: this.enableTextShadow })
            .onChange((isOn: boolean) => {
              this.enableTextShadow = isOn;
            })
          Text('文字阴影')
            .fontSize(12)
        }

        Row({ space: 20 }) {
          Toggle({ type: ToggleType.Switch, isOn: this.enableImageBorder })
            .onChange((isOn: boolean) => {
              this.enableImageBorder = isOn;
            })
          Text('图片边框')
            .fontSize(12)
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)

      // 透明度控制
    Column({ space: 8 }) {
        Text('覆盖层透明度: ' + this.overlayOpacity.toFixed(2))
          .fontSize(14)
          .fontColor(0x666666)

        Slider({
          value: this.overlayOpacity,
          min: 0.0,
          max: 1.0,
          step: 0.1
        })
          .width('100%')
          .onChange((value: number) => {
            this.overlayOpacity = value;
          })
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)
  }

  build() {
    Column() {
      Text('Image 与 Text 组合示例')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        // 左侧：内容展示
        Scroll() {
          Column({ space: 20 }) {
            if (this.currentLayout === 0) {
              this.ImageTopLayout()
            } else if (this.currentLayout === 1) {
              this.TextTopLayout()
            } else if (this.currentLayout === 2) {
              this.LeftRightLayout()
            } else if (this.currentLayout === 3) {
              this.GridLayout()
            }
          }
          .padding(20)
        }
        .layoutWeight(1)
        .backgroundColor(0xFAFAFA)

        Divider()
          .vertical(true)
          .color(0xDDDDDD)
          .strokeWidth(2)

        // 右侧：控制面板
        Scroll() {
          Column({ space: 15 }) {
            // 布局控制
            this.ControlPanel()

            // 示例选择
            Column({ space: 10 }) {
              Text('示例演示')
                .fontSize(16)
                .fontWeight(FontWeight.Bold)

              ForEach(this.demoNames, (demo: string, index: number) => {
                Button(demo)
                  .type(this.selectedDemo === index ? ButtonType.Capsule : ButtonType.Normal)
                  .width('100%')
                  .fontSize(12)
                  .backgroundColor(this.selectedDemo === index ? 0x007DFF : 0xF5F5F5)
                  .onClick(() => {
                    this.selectedDemo = index;
                  })
              })
            }
          }
          .padding(15)
          .backgroundColor(0xFFFFFF)
          .borderRadius(10)
          .shadow({ radius: 8, color: 0x1A000000, offsetX: 0, offsetY: 4 })
        }
        .layoutWeight(1)
        .padding(10)
        .backgroundColor(0xF5F5F5)
      }
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(0xF5F5F5)
  }
}
