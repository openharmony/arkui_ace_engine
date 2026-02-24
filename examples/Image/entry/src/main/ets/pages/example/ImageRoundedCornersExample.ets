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
 * 本示例测试 Image 组件的缩略图生成功能
 *
 * 涉及的Image API:
 * 1. sourceSize属性 - 设置图片解码尺寸
 * 2. objectFit属性 - 图片填充方式
 *
 * ========================================
 * 如何测试
 * ========================================
 * 测试步骤:
 * 1. 进入 "缩略图 ImageThumbnail" 页面
 * 2. 选择不同的缩略图尺寸预设（小/中/大/超大）
 * 3. 点击应用按钮
 * 4. 观察原图和缩略图的尺寸对比
 *
 * 预期结果:
 * - 缩略图按照设定的尺寸解码显示
 * - 内存占用相比原图减少
 * - 图片清晰度可接受
 *
 * ========================================
 * Image API 知识点
 * ========================================
 * 1. sourceSize属性作用:
 *    - 设置图片解码尺寸
 *    - 只在目标尺寸小于原图尺寸时生效
 *    - 可显著降低内存占用
 *
 * 2. sourceSize使用场景:
 *    - 列表缩略图 - 使用小尺寸解码
 *    - 网络图片优化 - 提前降低分辨率
 *    - 性能优化 - 减少解码时间
 *
 * 3. 配合objectFit使用:
 *    - sourceSize + ImageFit.None = 原尺寸显示小图
 *    - sourceSize + ImageFit.Cover = 居中裁剪显示
 */
@Entry
@Component
struct ImageThumbnailExample {
  @State selectedSize: string = '小';
  @State thumbnailQuality: number = 80;

  private sizePresets: Record<string, number[]> = {
    '小': [100, 100],
    '中': [150, 150],
    '大': [200, 200],
    '超大': [300, 300]
  };

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('缩略图生成示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // 原图展示
        Column({ space: 10 }) {
          Text('原图 (300x300):')
            .fontSize(16)
            .fontColor(Color.Gray)

          Image($r('app.media.app_icon'))
            .width(150)
            .height(150)
            .objectFit(ImageFit.Cover)
            .borderRadius(10)
            .border({ width: 2, color: Color.Blue })
            .onComplete((event) => {
              console.info(`原图尺寸: ${event.width}x${event.height}`);
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F0F8FF')
        .borderRadius(10)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 尺寸预设选择
        Column({ space: 15 }) {
          Text('选择缩略图尺寸:')
            .fontSize(16)
            .fontColor(Color.Gray)

          Row({ space: 10 }) {
            Button('小')
              .backgroundColor(this.selectedSize === '小' ? Color.Blue : Color.Gray)
              .onClick(() => {
                this.selectedSize = '小';
              })

            Button('中')
              .backgroundColor(this.selectedSize === '中' ? Color.Blue : Color.Gray)
              .onClick(() => {
                this.selectedSize = '中';
              })

            Button('大')
              .backgroundColor(this.selectedSize === '大' ? Color.Blue : Color.Gray)
              .onClick(() => {
                this.selectedSize = '大';
              })

            Button('超大')
              .backgroundColor(this.selectedSize === '超大' ? Color.Blue : Color.Gray)
              .onClick(() => {
                this.selectedSize = '超大';
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceEvenly)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        // 缩略图预览
        Column({ space: 15 }) {
          Text('缩略图预览 - ' + this.selectedSize)
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          let dims = this.sizePresets[this.selectedSize];
          Image($r('app.media.app_icon'))
            .sourceSize({ width: dims[0], height: dims[1] })
            .width(dims[0] / 2)
            .height(dims[1] / 2)
            .objectFit(ImageFit.Cover)
            .borderRadius(8)
            .border({ width: 2, color: Color.Green })
            .onComplete((event) => {
              console.info(`缩略图尺寸: ${event.width}x${event.height}`);
            })
        }
        .width('100%')
        .padding(20)
        .backgroundColor('#F8F8FF')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // API说明
        Column({ space: 10 }) {
          Text('测试的Image API:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Text('1. sourceSize - 控制解码尺寸')
            .fontSize(14)
            .fontColor(Color.Gray)

          Text('2. objectFit - 控制填充方式')
            .fontSize(14)
            .fontColor(Color.Gray)

          Text('3. onComplete - 获取解码后尺寸')
            .fontSize(14)
            .fontColor(Color.Gray)

          Text('优化提示: sourceSize只在目标尺寸小于原图时生效')
            .fontSize(12)
            .fontColor(Color.Orange)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E6E6FA')
        .borderRadius(10)
      }
      .width('100%')
      .padding({ left: 20, right: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.White)
  }
}
