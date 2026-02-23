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
 * 本示例测试 Image 组件的宽高比控制和图片适配功能
 *
 * 涉及的Image API:
 * 1. objectFit属性 - 图片填充适配模式
 * 2. width/height属性 - 设置图片尺寸
 * 3. 通用属性 - borderRadius - 圆角
 *
 * ========================================
 * 如何测试
 * ========================================
 * 测试步骤:
 * 1. 进入 "宽高比 ImageAspectRatio" 页面
 * 2. 在 "选择宽高比" 区域选择不同的预设比例（1:1, 4:3, 16:9等）
 * 3. 观察原图和调整后图片的尺寸对比
 * 4. 尝试不同的 "适配模式" (Cover/Contain/Fill/None/ScaleDown)
 * 5. 查看常用场景预设（头像、照片、视频等）
 *
 * 预期结果:
 * - 图片按照选定比例显示
 * - 不同适配模式产生不同的显示效果
 * - Cover保持宽高比填满容器，可能裁剪
 * - Contain保持宽高比完全显示，可能有留白
 *
 * ========================================
 * Image API 知识点
 * ========================================
 * 1. objectFit 枚举值:
 *    - Cover: 保持宽高比，缩放图片以填满容器，可能裁剪
 *    - Contain: 保持宽高比，缩放图片以完全显示在容器内，可能有留白
 *    - Fill: 拉伸图片以填满容器，不保持宽高比，可能变形
 *    - None: 保持图片原始尺寸，不进行缩放
 *    - ScaleDown: 缩小图片到容器内，不放大图片
 *
 * 2. 常用宽高比:
 *    - 1:1 - 头像、正方形图片
 *    - 4:3 - 传统照片、相机拍摄
 *    - 16:9 - 横屏视频、宽屏显示
 *    - 9:16 - 竖屏视频、手机拍摄
 *    - 21:9 - 电影宽屏
 *
 * 3. 使用建议:
 *    - 头像使用 1:1 + Cover
 *    - 照片展示使用 4:3 + Contain
 *    - 背景图使用 Cover + Fill
 *    - 缩略图使用 ScaleDown 保持清晰度
 */
@Entry
@Component
struct ImageAspectRatioExample {
  @State selectedRatio: string = '1:1';
  @State customWidth: number = 200;
  @State customHeight: number = 200;
  @State objectFit: ImageFit = ImageFit.Cover;

  private aspectRatios: string[] = [
    '1:1', '4:3', '3:4', '16:9', '9:16',
    '21:9', '9:21', '3:2', '2:3', '自由'
  ];

  private objectFitOptions: ImageFit[] = [
    ImageFit.Cover, ImageFit.Contain, ImageFit.Fill,
    ImageFit.None, ImageFit.ScaleDown
  ];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('宽高比效果示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // 宽高比预览
        Column({ space: 15 }) {
          Text('宽高比预览 - ' + this.selectedRatio)
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Row({ space: 20 }) {
            // 原图参考
            Column({ space: 8 }) {
              Text('原图 (正方形)')
                .fontSize(12)
                .fontColor(Color.Gray)
              Image($r('app.media.app_icon'))
                .width(100)
                .height(100)
                .objectFit(ImageFit.Cover)
                .borderRadius(8)
                .border({ width: 2, color: Color.Blue })
            }

            // 调整后的图
            Column({ space: 8 }) {
              Text('调整后 (' + this.selectedRatio + ')')
                .fontSize(12)
                .fontColor(Color.Gray)
              Image($r('app.media.app_icon'))
                .width(this.customWidth / 2)
                .height(this.customHeight / 2)
                .objectFit(this.objectFit)
                .borderRadius(8)
                .border({ width: 2, color: Color.Green })
            }
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        }
        .width('100%')
        .padding(20)
        .backgroundColor('#F8F8FF')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 适配模式选择
        Column({ space: 15 }) {
          Text('适配模式 (objectFit):')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Row({ space: 10 }) {
            ForEach(this.objectFitOptions, (fit: ImageFit) => {
              Button(this.getFitName(fit))
                .fontSize(12)
                .backgroundColor(this.objectFit === fit ? Color.Green : Color.Gray)
                .onClick(() => {
                  this.objectFit = fit;
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

        // 适配模式说明
        Column({ space: 8 }) {
          Text('适配模式说明:')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          this.FitDescription('Cover', '保持宽高比，填满容器，可能裁剪')
          this.FitDescription('Contain', '保持宽高比，完全显示，可能有留白')
          this.FitDescription('Fill', '拉伸填满容器，可能变形')
          this.FitDescription('None', '原始尺寸，不缩放')
          this.FitDescription('ScaleDown', '缩小到容器内，不放大')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E6E6FA')
        .borderRadius(10)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 常用场景
        Column({ space: 15 }) {
          Text('常用宽高比场景:')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Grid() {
            GridItem() {
              this.UseCasePreset('头像', '1:1')
            }
            GridItem() {
              this.UseCasePreset('照片', '4:3')
            }
            GridItem() {
              this.UseCasePreset('横屏视频', '16:9')
            }
            GridItem() {
              this.UseCasePreset('竖屏视频', '9:16')
            }
            GridItem() {
              this.UseCasePreset('电影', '21:9')
            }
            GridItem() {
              this.UseCasePreset('艺术照', '3:2')
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

        // 操作按钮
        Row({ space: 15 }) {
          Button('重置')
            .fontSize(14)
            .backgroundColor(Color.Gray)
            .onClick(() => {
              this.selectedRatio = '1:1';
              this.customWidth = 200;
              this.customHeight = 200;
              this.objectFit = ImageFit.Cover;
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Text('合适的宽高比可提升图片展示效果')
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
  UseCasePreset(name: string, ratio: string) {
    Column({ space: 8 }) {
      Text(name)
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
      Text(ratio)
        .fontSize(12)
        .fontColor(Color.Gray)
      Button('应用')
        .fontSize(12)
        .backgroundColor(Color.Orange)
        .onClick(() => {
          this.selectedRatio = ratio;
          this.applyRatio(ratio);
        })
    }
  }

  @Builder
  FitDescription(name: string, description: string) {
    Row({ space: 10 }) {
      Text(name + ':')
        .fontSize(12)
        .fontWeight(FontWeight.Medium)
        .width(70)
      Text(description)
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
  }

  getFitName(fit: ImageFit): string {
    switch (fit) {
      case ImageFit.Cover: return 'Cover';
      case ImageFit.Contain: return 'Contain';
      case ImageFit.Fill: return 'Fill';
      case ImageFit.None: return 'None';
      case ImageFit.ScaleDown: return 'ScaleDown';
      default: return 'Cover';
    }
  }

  applyRatio(ratio: string): void {
    const baseSize = 200;
    switch (ratio) {
      case '1:1':
        this.customWidth = baseSize;
        this.customHeight = baseSize;
        break;
      case '4:3':
        this.customWidth = baseSize;
        this.customHeight = Math.round(baseSize * 3 / 4);
        break;
      case '3:4':
        this.customWidth = Math.round(baseSize * 3 / 4);
        this.customHeight = baseSize;
        break;
      case '16:9':
        this.customWidth = baseSize;
        this.customHeight = Math.round(baseSize * 9 / 16);
        break;
      case '9:16':
        this.customWidth = Math.round(baseSize * 9 / 16);
        this.customHeight = baseSize;
        break;
      case '21:9':
        this.customWidth = baseSize;
        this.customHeight = Math.round(baseSize * 9 / 21);
        break;
      case '9:21':
        this.customWidth = Math.round(baseSize * 9 / 21);
        this.customHeight = baseSize;
        break;
      case '3:2':
        this.customWidth = baseSize;
        this.customHeight = Math.round(baseSize * 2 / 3);
        break;
      case '2:3':
        this.customWidth = Math.round(baseSize * 2 / 3);
        this.customHeight = baseSize;
        break;
    }
  }
}
