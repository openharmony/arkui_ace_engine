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
 * 图片遮罩示例 - 展示如何使用遮罩效果
 */
@Entry
@Component
struct ImageMask {
  @State selectedMask: string = '圆形';
  @State maskOpacity: number = 1;
  @State invertMask: boolean = false;

  private maskTypes: string[] = [
    '无', '圆形', '方形', '椭圆', '星形',
    '心形', '三角形', '六边形', '渐变', '自定义'
  ];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片遮罩示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // 遮罩预览
        Column({ space: 15 }) {
          Text('遮罩预览 - ' + this.selectedMask)
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Stack() {
            // 背景层
            Image($r('app.media.app_icon'))
              .width(250)
              .height(250)
              .objectFit(ImageFit.Cover)

            // 遮罩层
            Stack() {
              if (this.selectedMask === '圆形') {
                Circle()
                  .width(200)
                  .height(200)
                  .fill(Color.Black)
                  .opacity(this.maskOpacity)
              } else if (this.selectedMask === '方形') {
                Rectangle()
                  .width(180)
                  .height(180)
                  .fill(Color.Black)
                  .opacity(this.maskOpacity)
              } else if (this.selectedMask === '椭圆') {
                Ellipse()
                  .width(220)
                  .height(160)
                  .fill(Color.Black)
                  .opacity(this.maskOpacity)
              } else if (this.selectedMask === '星形') {
                this.StarShape(200)
                  .fill(Color.Black)
                  .opacity(this.maskOpacity)
              } else if (this.selectedMask === '心形') {
                this.HeartShape()
                  .width(180)
                  .height(180)
                  .fill(Color.Black)
                  .opacity(this.maskOpacity)
              } else if (this.selectedMask === '三角形') {
                this.TriangleShape()
                  .width(200)
                  .height(200)
                  .fill(Color.Black)
                  .opacity(this.maskOpacity)
              } else if (this.selectedMask === '六边形') {
                this.HexagonShape()
                  .width(200)
                  .height(200)
                  .fill(Color.Black)
                  .opacity(this.maskOpacity)
              } else if (this.selectedMask === '渐变') {
                Rectangle()
                  .width(250)
                  .height(250)
                  .linearGradient({
                    angle: 45,
                    colors: [[Color.Transparent, 0], [Color.Black, 1]]
                  })
              } else if (this.selectedMask === '自定义') {
                Path()
                  .width(200)
                  .height(200)
                  .commands('M0 100 L50 0 L100 50 L150 0 L200 100 L150 200 L100 150 L50 200 Z')
                  .fill(Color.Black)
                  .opacity(this.maskOpacity)
              }
            }
            .blendMode(this.invertMask ? BlendMode.DST_OUT : BlendMode.SRC_IN)
          }
          .width(270)
          .height(270)
          .backgroundColor('#F0F0F0')
          .borderRadius(15)
          .shadow({ radius: 15, color: '#20000000' })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8FF')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 遮罩类型选择
        Column({ space: 15 }) {
          Text('选择遮罩类型:')
            .fontSize(16)
            .fontColor(Color.Gray)

          Grid() {
            ForEach(this.maskTypes, (mask: string) => {
              GridItem() {
                Column({ space: 8 }) {
                  Stack() {
                    Image($r('app.media.app_icon'))
                      .width(60)
                      .height(60)
                      .objectFit(ImageFit.Cover)
                      .borderRadius(mask === '圆形' ? 30 : 8)

                    if (this.selectedMask === mask) {
                      Rectangle()
                        .width(64)
                        .height(64)
                        .border({ width: 3, color: Color.Blue, radius: 8 })
                    }
                  }

                  Text(mask)
                    .fontSize(12)
                    .fontColor(this.selectedMask === mask ? Color.Blue : Color.Gray)
                }
                .onClick(() => {
                  this.selectedMask = mask;
                })
              }
            })
          }
          .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
          .rowsGap(15)
          .columnsGap(15)
          .width('100%')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#FFF8DC')
        .borderRadius(10)

        // 透明度控制
        Column({ space: 10 }) {
          Text('遮罩透明度: ' + Math.round(this.maskOpacity * 100) + '%')
            .fontSize(16)
            .fontColor(Color.Gray)

          Slider({
            value: this.maskOpacity * 100,
            min: 0,
            max: 100,
            step: 5
          })
            .width('100%')
            .onChange((value: number) => {
              this.maskOpacity = value / 100;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        // 反转遮罩
        Row({ space: 20 }) {
          Text('反转遮罩:')
            .fontSize(16)
            .fontColor(Color.Gray)

          Toggle({ type: ToggleType.Switch, isOn: this.invertMask })
            .onChange((value: boolean) => {
              this.invertMask = value;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 混合模式说明
        Column({ space: 10 }) {
          Text('混合模式说明:')
            .fontSize(18)
          this.BlendModeInfo('SRC_IN', '遮罩内显示图片')
          this.BlendModeInfo('DST_OUT', '遮罩外隐藏图片')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E6E6FA')
        .borderRadius(10)

        Text('遮罩可创建独特图片形状效果')
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
  StarShape(size: number) {
    Path()
      .width(size)
      .height(size)
      .commands('M100 0 L123 65 L191 65 L137 105 L159 173 L100 134 L41 173 L63 105 L9 65 L77 65 Z')
  }

  @Builder
  HeartShape() {
    Path()
      .width(180)
      .height(180)
      .commands('M90 160 C30 110 10 70 40 40 C70 10 90 40 90 40 C90 40 110 10 140 40 C170 70 150 110 90 160 Z')
  }

  @Builder
  TriangleShape() {
    Path()
      .width(200)
      .height(200)
      .commands('M100 0 L200 200 L0 200 Z')
  }

  @Builder
  HexagonShape() {
    Path()
      .width(200)
      .height(200)
      .commands('M100 0 L186 50 L186 150 L100 200 L14 150 L14 50 Z')
  }

  @Builder
  BlendModeInfo(mode: string, description: string) {
    Row({ space: 10 }) {
      Text(mode + ':')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width(80)
      Text(description)
        .fontSize(14)
        .fontColor(Color.Gray)
    }
    .width('100%')
  }
}
