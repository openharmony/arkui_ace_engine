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

import { image } from '@kit.ImageKit';
import { matrix4 } from '@kit.ArkGraphics2D';

/**
 * Image 边框与圆角示例
 * 演示 Image 组件的边框和圆角设置
 */
@Entry
@Component
struct ImageBorderRadiusExample {
  @State borderWidth: number = 2;
  @State borderColor: string = '#007DFF';
  @State borderRadius: number = 10;
  @State borderRadiusTL: number = 10;
  @State borderRadiusTR: number = 10;
  @State borderRadiusBL: number = 10;
  @State borderRadiusBR: number = 10;
  @State currentStyle: number = 0;
  @State showShadow: boolean = true;
  @State showBackground: boolean = true;

  styles: string[] = ['统一圆角', '独立圆角', '无边框'];

  @Builder
  UniformRadiusCard() {
    Column({ space: 15 }) {
      Text('统一圆角')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      ForEach([0, 10, 20, 30, 40, 50], (radius: number) => {
        Column({ space: 8 }) {
          Text(`radius: ${radius}`)
            .fontSize(12)
            .fontColor(0x666666)

          Image($r('app.media.img'))
            .width(150)
            .height(150)
            .border({
              width: this.borderWidth,
              color: this.borderColor,
              radius: radius
            })
            .objectFit(ImageFit.Cover)
            .shadow(this.showShadow ? {
              radius: 10,
              color: 0x1A000000,
              offsetX: 0,
              offsetY: 4
            } : {})
        }
      }
    }
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
    .shadow({ radius: 8, color: 0x1A000000, offsetX: 0, offsetY: 4 })
  }

  @Builder
  IndependentRadiusCard() {
    Column({ space: 15 }) {
      Text('独立圆角')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Column({ space: 10 }) {
        Text('自定义圆角')
          .fontSize(14)
          .fontColor(0x666666)

        Image($r('app.media.jpg'))
          .width(200)
          .height(150)
          .border({
            width: this.borderWidth,
            color: this.borderColor,
            radius: {
              topLeft: this.borderRadiusTL,
              topRight: this.borderRadiusTR,
              bottomLeft: this.borderRadiusBL,
              bottomRight: this.borderRadiusBR
            }
          })
          .objectFit(ImageFit.Cover)
          .shadow(this.showShadow ? {
            radius: 10,
            color: 0x1A000000,
            offsetX: 0,
            offsetY: 4
          } : {})
      }
    }
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
    .shadow({ radius: 8, color: 0x1A000000, offsetX: 0, offsetY: 4 })
  }

  @Builder
  NoBorderCard() {
    Column({ space: 15 }) {
      Text('无边框')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Row({ space: 15 }) {
        ForEach([ImageFit.Cover, ImageFit.Contain, ImageFit.Fill], (fit: ImageFit) => {
          Column({ space: 8 }) {
            Text(`${fit}`)
              .fontSize(12)
              .fontColor(0x666666)

            Image($r('app.media.png'))
              .width(120)
              .height(120)
              .borderRadius(10)
              .objectFit(fit)
              .backgroundColor(this.showBackground ? 0xF0F0F0 : undefined)
              .shadow(this.showShadow ? {
                radius: 8,
                color: 0x1A000000,
                offsetX: 0,
                offsetY: 3
              } : {})
          }
        }
      }
    }
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
    .shadow({ radius: 8, color: 0x1A000000, offsetX: 0, offsetY: 4 })
  }

  @Builder
  ControlPanel() {
    Column({ space: 15 }) {
      Text('控制面板')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)

      // 边框设置
      Column({ space: 10 }) {
        Text('边框设置')
          .fontSize(14)
          .fontColor(0x666666)

        Column({ space: 8 }) {
          Text('边框宽度: ' + this.borderWidth)
            .fontSize(12)
          Slider({
            value: this.borderWidth,
            min: 0,
            max: 10,
            step: 1
          })
            .width('100%')
            .onChange((value: number) => {
              this.borderWidth = value;
            })
        }

        Column({ space: 8 }) {
          Text('边框颜色: ' + this.borderColor)
            .fontSize(12)
          Row({ space: 10 }) {
            ForEach(['#007DFF', '#FF5252', '#00AA00', '#FF9800', '#1A00000'], (color: string) => {
              Button()
                .width(30)
                .height(30)
                .backgroundColor(color)
                .borderRadius(5)
                .onClick(() => {
                  this.borderColor = color;
                })
            })
          }
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)

      // 圆角设置
      Column({ space: 10 }) {
        Text('圆角设置')
          .fontSize(14)
          .fontColor(0x666666)

        Column({ space: 8 }) {
          Text('统一圆角: ' + this.borderRadius)
            .fontSize(12)
          Slider({
            value: this.borderRadius,
            min: 0,
            max: 50,
            step: 1
          })
            .width('100%')
            .onChange((value: number) => {
              this.borderRadius = value;
            })
        }

        Column({ space: 8 }) {
          Text('左上: ' + this.borderRadiusTL)
            .fontSize(12)
          Slider({
            value: this.borderRadiusTL,
            min: 0,
            max: 50,
            step: 1
          })
            .width('100%')
            .onChange((value: number) => {
              this.borderRadiusTL = value;
            })
        }

        Column({ space: 8 }) {
          Text('右上: ' + this.borderRadiusTR)
            .fontSize(12)
          Slider({
            value: this.borderRadiusTR,
            min: 0,
            max: 50,
            step: 1
          })
            .width('100%')
            .onChange((value: number) => {
              this.borderRadiusTR = value;
            })
        }

        Column({ space: 8 }) {
          Text('左下: ' + this.borderRadiusBL)
            .fontSize(12)
          Slider({
            value: this.borderRadiusBL,
            min: 0,
            max: 50,
            step: 1
          })
            .width('100%')
            .onChange((value: number) => {
              this.borderRadiusBL = value;
            })
        }

        Column({ space: 8 }) {
          Text('右下: ' + this.borderRadiusBR)
            .fontSize(12)
          Slider({
            value: this.borderRadiusBR,
            min: 0,
            max: 50,
            step: 1
          })
            .width('100%')
            .onChange((value: number) => {
              this.borderRadiusBR = value;
            })
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)

      // 其他选项
      Column({ space: 10 }) {
        Text('其他选项')
          .fontSize(14)
          .fontColor(0x666666)

        Row({ space: 20 }) {
          Toggle({ type: ToggleType.Switch, isOn: this.showShadow })
            .onChange((isOn: boolean) => {
              this.showShadow = isOn;
            })
          Text('显示阴影')
            .fontSize(12)
        }

        Row({ space: 20 }) {
          Toggle({ type: ToggleType.Switch, isOn: this.showBackground })
            .onChange((isOn: boolean) => {
              this.showBackground = isOn;
            })
          Text('显示背景')
            .fontSize(12)
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)
  }

  build() {
    Column() {
      Text('Image 边框与圆角示例')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        // 左侧：展示区域
        Scroll() {
          Column({ space: 20 }) {
            if (this.currentStyle === 0) {
              this.UniformRadiusCard()
            } else if (this.currentStyle === 1) {
              this.IndependentRadiusCard()
            } else if (this.currentStyle === 2) {
              this.NoBorderCard()
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
            // 样式风格选择
            Column({ space: 10 }) {
              Text('样式风格')
                .fontSize(16)
                .fontWeight(FontWeight.Bold)

              Row({ space: 10 }) {
                ForEach(this.styles, (style: string, index: number) => {
                  Button(style)
                    .type(this.currentStyle === index ? ButtonType.Capsule : ButtonType.Normal)
                    .fontSize(12)
                    .backgroundColor(this.currentStyle === index ? 0x007DFF : 0xF5F5F5)
                    .onClick(() => {
                      this.currentStyle = index;
                    })
                }
              }
            }
          }
          .padding(15)
          .backgroundColor(0xFFFFFF)
          .borderRadius(10)
          .shadow({ radius: 8, color: 0x1A000000, offsetX: 0, offsetY: 4 })

          this.ControlPanel()
        }
        .padding(10)
      }
      .layoutWeight(1)
      .backgroundColor(0xF5F5F5)
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(0xF5F5F5)
  }
}
