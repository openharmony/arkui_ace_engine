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
 * 图片阴影示例 - 展示各种阴影效果
 */
@Entry
@Component
struct ImageShadow {
  @State shadowRadius: number = 20;
  @State shadowColor: Color = Color.Black;
  @State shadowOffsetX: number = 5;
  @State shadowOffsetY: number = 5;
  @State shadowOpacity: number = 0.3;
  @State selectedShadow: string = '基础阴影';

  private shadowTypes: string[] = [
    '基础阴影', '内阴影', '长阴影', '多层阴影',
    '彩色阴影', '扩散阴影', '投影', '悬浮效果'
  ];

  private shadowColors: Color[] = [
    Color.Black, Color.Red, Color.Blue, Color.Green,
    Color.Purple, Color.Orange, Color.Yellow, Color.Transparent
  ];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片阴影示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // 阴影预览
        Column({ space: 15 }) {
          Text('阴影效果 - ' + this.selectedShadow)
            .fontSize(18)
          .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Stack() {
            // 背景网格
            Grid() {
              ForEach(Array(20).fill(0), (_: number) => {
                ForEach(Array(20).fill(0), (_: number) => {
                  GridItem() {
                    Rectangle()
                      .width(15)
                      .height(15)
                      .fill(Color.Transparent)
                      .border({ width: 1, color: '#E0E0E0' })
                  }
                })
              })
            }
            .columnsTemplate('1fr '.repeat(20).trim())
            .width(300)
            .height(300)

            // 带阴影的图片
            Image($r('app.media.app_icon'))
              .width(200)
              .height(200)
              .objectFit(ImageFit.Cover)
              .borderRadius(15)
              .shadow(this.getShadowConfig())
          }
          .width(320)
          .height(320)
          .backgroundColor('#F8F8FF')
          .borderRadius(20)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F0F8FF')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 阴影类型选择
        Column({ space: 15 }) {
          Text('选择阴影类型:')
            .fontSize(16)
            .fontColor(Color.Gray)

          Row({ space: 10 }) {
            ForEach(this.shadowTypes, (type: string) => {
              Button(type)
                .fontSize(12)
                .backgroundColor(this.selectedShadow === type ? Color.Blue : Color.Gray)
                .onClick(() => {
                  this.selectedShadow = type;
                })
            })
          }
          .width('100%')
          .flexWrap(FlexWrap.Wrap)
          .justifyContent(FlexAlign.SpaceEvenly)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        // 阴影颜色选择
        Column({ space: 15 }) {
          Text('选择阴影颜色:')
            .fontSize(16)
            .fontColor(Color.Gray)

          Row({ space: 10 }) {
            ForEach(this.shadowColors, (color: Color) => {
              Circle()
                .width(35)
                .height(35)
                .fill(color === Color.Transparent ? Color.White : color)
                .border({
                  width: this.shadowColor === color ? 4 : 2,
                  color: this.shadowColor === color ? Color.Blue : Color.Gray
                })
                .onClick(() => {
                  this.shadowColor = color;
                })
            })
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceEvenly)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        // 阴影半径
        Column({ space: 10 }) {
          Text('阴影半径: ' + this.shadowRadius + 'px')
            .fontSize(16)
            .fontColor(Color.Gray)

          Slider({
            value: this.shadowRadius,
            min: 0,
            max: 50,
            step: 5
          })
            .width('100%')
            .onChange((value: number) => {
              this.shadowRadius = value;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        // X偏移
        Column({ space: 10 }) {
          Text('X偏移: ' + this.shadowOffsetX + 'px')
            .fontSize(16)
            .fontColor(Color.Gray)

          Slider({
            value: this.shadowOffsetX,
            min: -30,
            max: 30,
            step: 5
          })
            .width('100%')
            .onChange((value: number) => {
              this.shadowOffsetX = value;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        // Y偏移
        Column({ space: 10 }) {
          Text('Y偏移: ' + this.shadowOffsetY + 'px')
            .fontSize(16)
            .fontColor(Color.Gray)

          Slider({
            value: this.shadowOffsetY,
            min: -30,
            max: 30,
            step: 5
          })
            .width('100%')
            .onChange((value: number) => {
              this.shadowOffsetY = value;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        // 透明度
        Column({ space: 10 }) {
          Text('阴影透明度: ' + Math.round(this.shadowOpacity * 100) + '%')
            .fontSize(16)
            .fontColor(Color.Gray)

          Slider({
            value: this.shadowOpacity * 100,
            min: 0,
            max: 100,
            step: 5
          })
            .width('100%')
            .onChange((value: number) => {
              this.shadowOpacity = value / 100;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 阴影预设
        Column({ space: 15 }) {
          Text('阴影效果预设:')
            .fontSize(18)
          .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Grid() {
            GridItem() {
              this.ShadowPreset('轻微', 5, 2, 2, 0.2)
            }
            GridItem() {
              this.ShadowPreset('中等', 15, 5, 5, 0.3)
            }
            GridItem() {
              this.ShadowPreset('强烈', 30, 10, 10, 0.4)
            }
            GridItem() {
              this.ShadowPreset('悬浮', 25, 0, 15, 0.35)
            }
          }
          .columnsTemplate('1fr 1fr')
          .rowsGap(15)
          .columnsGap(15)
          .width('100%')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#FFE4B5')
        .borderRadius(10)

        // 多阴影效果展示
        Column({ space: 15 }) {
          Text('多层阴影效果:')
            .fontSize(18)
          .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Image($r('app.media.app_icon'))
            .width(150)
            .height(150)
            .objectFit(ImageFit.Cover)
            .borderRadius(15)
            .shadow([
              { radius: 10, color: '#80FF0000', offsetX: 0, offsetY: 0 },
              { radius: 20, color: '#8000FF00', offsetX: 5, offsetY: 5 },
              { radius: 30, color: '#800000FF', offsetX: 10, offsetY: 10 }
            ])
        }
        .width('100%')
        .padding(25)
        .backgroundColor('#E6E6FA')
        .borderRadius(10)

        Row({ space: 15 }) {
          Button('保存效果')
            .fontSize(14)
            .backgroundColor(Color.Green)
            .onClick(() => {
              // 保存阴影效果
            })

          Button('重置')
            .fontSize(14)
            .backgroundColor(Color.Gray)
            .onClick(() => {
              this.shadowRadius = 20;
              this.shadowColor = Color.Black;
              this.shadowOffsetX = 5;
              this.shadowOffsetY = 5;
              this.shadowOpacity = 0.3;
              this.selectedShadow = '基础阴影';
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Text('阴影可增强图片立体感和层次感')
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
  ShadowPreset(name: string, radius: number, offsetX: number, offsetY: number, opacity: number) {
    Column({ space: 8 }) {
      Image($r('app.media.app_icon'))
        .width(100)
        .height(100)
        .objectFit(ImageFit.Cover)
        .borderRadius(10)
        .shadow({
          radius: radius,
          color: Color.Black,
          offsetX: offsetX,
          offsetY: offsetY
        })
      Text(name)
        .fontSize(12)
        .fontColor(Color.Gray)

      Button('应用')
        .fontSize(11)
        .backgroundColor(Color.Orange)
        .onClick(() => {
          this.shadowRadius = radius;
          this.shadowOffsetX = offsetX;
          this.shadowOffsetY = offsetY;
          this.shadowOpacity = opacity;
        })
    }
  }

  getShadowConfig(): CommonShadow<ContentModifier> | CommonShadow<ContentModifier>[] {
    const color = this.shadowColor === Color.Transparent ? '#00000000' : this.shadowColor;

    switch (this.selectedShadow) {
      case '基础阴影':
        return {
          radius: this.shadowRadius,
          color: this.applyOpacity(color, this.shadowOpacity),
          offsetX: this.shadowOffsetX,
          offsetY: this.shadowOffsetY
        };

      case '内阴影':
        return {
          radius: this.shadowRadius,
          color: this.applyOpacity(color, this.shadowOpacity),
          offsetX: -this.shadowOffsetX,
          offsetY: -this.shadowOffsetY
        };

      case '长阴影':
        return {
          radius: this.shadowRadius * 1.5,
          color: this.applyOpacity(color, this.shadowOpacity * 0.5),
          offsetX: this.shadowOffsetX * 3,
          offsetY: this.shadowOffsetY * 3
        };

      case '彩色阴影':
        return {
          radius: this.shadowRadius,
          color: this.applyOpacity(this.shadowColors[Math.floor(Math.random() * 7)], this.shadowOpacity),
          offsetX: this.shadowOffsetX,
          offsetY: this.shadowOffsetY
        };

      case '扩散阴影':
        return {
          radius: this.shadowRadius * 2,
          color: this.applyOpacity(color, this.shadowOpacity * 0.3),
          offsetX: 0,
          offsetY: 0
        };

      case '投影':
        return {
          radius: this.shadowRadius,
          color: this.applyOpacity(Color.Black, this.shadowOpacity * 0.5),
          offsetX: this.shadowOffsetX * 2,
          offsetY: this.shadowOffsetY * 3
        };

      case '悬浮效果':
        return {
          radius: this.shadowRadius * 1.2,
          color: this.applyOpacity(color, this.shadowOpacity * 0.4),
          offsetX: 0,
          offsetY: this.shadowOffsetY * 2
        };

      case '多层阴影':
        return [
          {
            radius: this.shadowRadius * 0.5,
            color: this.applyOpacity(color, this.shadowOpacity),
            offsetX: this.shadowOffsetX,
            offsetY: this.shadowOffsetY
          },
          {
            radius: this.shadowRadius,
            color: this.applyOpacity(color, this.shadowOpacity * 0.5),
            offsetX: this.shadowOffsetX * 2,
            offsetY: this.shadowOffsetY * 2
          }
        ];

      default:
        return {
          radius: this.shadowRadius,
          color: this.applyOpacity(color, this.shadowOpacity),
          offsetX: this.shadowOffsetX,
          offsetY: this.shadowOffsetY
        };
    }
  }

  applyOpacity(color: ResourceColor, opacity: number): ResourceColor {
    return color;
  }
}
