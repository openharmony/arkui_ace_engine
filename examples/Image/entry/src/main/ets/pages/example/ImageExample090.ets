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
 * ImageExample090 - 图片方向控制示例
 * 
 * 功能说明：
 * 1. orientation 属性 - 设置图像内容的显示方向
 * 2. 仅支持静态位图的显示
 * 3. alt 占位图不生效
 * 
 * ImageRotateOrientation 枚举值：
 * - ImageRotateOrientation.AUTO - 读取图片携带的 EXIF 元数据作为显示方向
 * - ImageRotateOrientation.UP - 默认按照当前图片的像素数据进行显示
 * - ImageRotateOrientation.RIGHT - 将当前图片顺时针旋转 90 度后显示
 * - ImageRotateOrientation.DOWN - 将当前图片顺时针旋转 180 度后显示
 * - ImageRotateOrientation.LEFT - 将当前图片顺时针旋转 270 度后显示
 * - ImageRotateOrientation.UP_MIRRORED - 将当前图片水平翻转后显示
 * - ImageRotateOrientation.RIGHT_MIRRORED - 将当前图片水平翻转再顺时针旋转 90 度后显示
 * - ImageRotateOrientation.DOWN_MIRRORED - 将当前图片垂直翻转后显示
 * - ImageRotateOrientation.LEFT_MIRRORED - 将当前图片水平翻转再顺时针旋转 270 度后显示
 */

@Entry
@Component
struct ImageExample090 {
  @State currentOrientation: ImageRotateOrientation = ImageRotateOrientation.AUTO;
  @State selectedMode: string = 'AUTO (自动方向)';

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片方向控制示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildAutoOrientationDemo()
        this.buildUpOrientationDemo()
        this.buildRightOrientationDemo()
        this.buildDownOrientationDemokt()
        this.buildLeftOrientationDemo()
        this.buildMirroredOrientationDemo()
        this.buildComparisonDemo()
        this.buildBestPractices()
        this.buildInteractiveDemo()
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  @Builder
  buildDescription() {
    Column({ space: 10 }) {
      Text('orientation 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置图像内容的显示方向。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 仅支持静态位图的显示')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• alt 占位图不生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 支持多种旋转和翻转组合')
        .fontSize(12)
        .fontColor(0x999999)

      Text('ImageRotateOrientation 枚举值：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• AUTO - 读取 EXIF 元数据作为显示方向')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• UP - 默认按照当前图片的像素数据显示')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• RIGHT - 顺时针旋转 90 度')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• DOWN - 顺时针旋转 180 度')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• LEFT - 顺时针旋转 270 度')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• UP_MIRRORED - 水平翻转')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• RIGHT_MIRRORED - 水平翻转再顺时针旋转 90 度')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• DOWN_MIRRORED - 垂直翻转')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• LEFT_MIRRORED - 水平翻转再顺时针旋转 270 度')
        .fontSize(12)
        .fontColor(0x999999)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildAutoOrientationDemo() {
    Column({ space: 15 }) {
      Text('自动方向 (ImageRotateOrientation.AUTO)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('读取图片携带的 EXIF 元数据作为显示方向')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .orientation(ImageRotateOrientation.AUTO)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
        .backgroundColor(0xF0F0F0)

        Text('根据 EXIF 元数据自动调整方向')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildUpOrientationDemo() {
    Column({ space: 15 }) {
      Text('默认方向 (ImageRotateOrientation.UP)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('默认按照当前图片的像素数据进行显示')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .orientation(ImageRotateOrientation.UP)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('保持原始方向')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildRightOrientationDemo() {
    Column({ space: 15 }) {
      Text('向右旋转 90 度 (ImageRotateOrientation.RIGHT)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('将当前图片顺时针旋转 90 度的后显示')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .orientation(ImageRotateOrientation.RIGHT)
          .border({ width: 2, color: Color.Orange })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('顺时针旋转 90 度')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildDownOrientationDemo() {
    Column({ space: 15 }) {
      Text('向下旋转 180 度 (ImageRotateOrientation.DOWN)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('将当前图片顺时针旋转 180 度的后显示')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .orientation(ImageRotateOrientation.DOWN)
          .border({ width: 2, color: Color.Purple })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('顺时针旋转 180 度')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildLeftOrientationDemo() {
    Column({ space: 15 }) {
      Text('向左旋转 270 度 (ImageRotateOrientation.LEFT)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('将当前图片顺时针旋转 270 度的后显示')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .orientation(ImageRotateOrientation.LEFT)
          .border({ width: 2, color: Color.Pink })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('顺时针旋转 270 度')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildMirroredOrientationDemo() {
    Column({ space: 15 }) {
      Text('镜像翻转方向')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 15 }) {
        Column({ space: 10 }) {
          Text('UP_MIRRORED')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .orientation(ImageRotateOrientation.UP_MIRRORED)
            .border({ width: 2, color: Color.Red })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('水平翻转')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('DOWN_MIRRORED')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .orientation(ImageRotateOrientation.DOWN_MIRRORED)
            .border({ width: 2, color: Color.Gray })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('垂直翻转')
            .fontSize(12)
            .fontColor(0x666666)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildComparisonDemo() {
    Column({ space: 15 }) {
      Text('旋转方向对比')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 15 }) {
        Column({ space: 10 }) {
          Text('AUTO')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(120)
            .height(80)
            .orientation(ImageRotateOrientation.AUTO)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)
        }

        Column({ space: 10 }) {
          Text('UP')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(120)
            .height(80)
            .orientation(ImageRotateOrientation.UP)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)
        }

        Column({ space: 10 }) {
          Text('RIGHT')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(120)
            .height(80)
            .orientation(ImageRotateOrientation.RIGHT)
            .border({ width: 2, color: Color.Orange })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)
        }

        Column({ space: 10 }) {
          Text('DOWN')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(120)
            .height(80)
            .orientation(ImageRotateOrientation.DOWN)
            .border({ width: 2, color: Color.Purple })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)
        }

        Column({ space: 10 }) {
          Text('LEFT')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(120)
            .height(80)
            .orientation(ImageRotateOrientation.LEFT)
            .border({ width: 2, color: Color.Pink })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildBestPractices() {
    Column({ space: 15 }) {
      Text('最佳实践建议')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Text('• 相机照片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 AUTO 模式，根据 EXIF 元数据自动调整方向')
          .fontSize(12)
          .fontColor(0x66666kt)
      }

      Column({ space: 10 }) {
        Text('• 静态资源')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 UP 模式，保持原始方向')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 旋转动画')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用不同的旋转值创建旋转动画效果')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 镜像效果')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用镜像翻转模式创建镜像效果')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 限制条件')
          .fontSize(14)
          .fontColor(0x333333)
        Text('仅支持静态位图，alt 占位图不生效')
          .fontSize(12)
          .fontColor(0x666666)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildInteractiveDemo() {
    Column({ space: 15 }) {
      Text('交互式演示')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Text('当前方向：' + this.selectedMode)
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)

        Image($r('app.media.background'))
          .width(350)
          .height(250)
          .orientation(this.currentOrientation)
          .border({ width: 2, color: Color.Red })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('AUTO')
          .width(80)
          .onClick(() => {
            this.currentOrientation = ImageRotateOrientation.AUTO;
            this.selectedMode = 'AUTO (自动方向)';
          })

        Button('UP')
          .width(80)
          .onClick(() => {
            this.currentOrientation = ImageRotateOrientation.UP;
            this.selectedMode = 'UP (默认方向)';
          })

        Button('RIGHT')
          .width(80)
          .onClick(() => {
            this.currentOrientation = ImageRotateOrientation.RIGHT;
            this.selectedMode = 'RIGHT (向右旋转 90 度)';
          })

        Button('DOWN')
          .width(80)
          .onClick(() => {
            this.currentOrientation = ImageRotateOrientation.DOWN;
            this.selectedMode = 'DOWN (向下旋转 180 度)';
          })

        Button('LEFT')
          .width(80)
          .onClick(() => {
            this.currentOrientation = ImageRotateOrientation.LEFT;
            this.selectedMode = 'LEFT (向左旋转 270 度)';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .padding(15)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('UP_MIRRORED')
          .width(120)
          .onClick(() => {
            this.currentOrientation = ImageRotateOrientation.UP_MIRRORED;
            this.selectedMode = 'UP_MIRRORED (水平翻转)';
          })

        Button('DOWN_MIRRORED')
          .width(120)
          .onClick(() => {
            this.currentOrientation = ImageRotateOrientation.DOWN_MIRRORED;
            this.selectedMode = 'DOWN_MIRRORED (垂直翻转)';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .padding(15)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)
  }
}
