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
 * ImageAlt 属性示例 (API 22+)
 * ========================================
 * 测试功能说明:
 * 本示例测试 Image 组件的 ImageAlt 占位图功能 (API 22+)
 *
 * 涉及的 Image API:
 * 1. alt(ImageAlt) - 设置加载中和加载失败的占位图
 * 2. ImageAlt 对象 - 可分别配置 placeholder 和 error
 * 3. onError 事件 - 监听图片加载失败
 *
 * ========================================
 * 如何测试
 * ========================================
 * 测试步骤:
 * 1. 进入 "ImageAlt 占位图" 页面
 * 2. 观察有效图片正常显示
 * 3. 点击 "触发加载失败" 按钮，查看失败占位图效果
 * 4. 对比新旧 alt API 的差异
 *
 * 预期结果:
 * - 有效图片正常显示
 * - 加载失败时显示自定义失败占位图
 * - ImageAlt 可分别控制加载中和失败状态
 *
 * ========================================
 * Image API 知识点
 * ========================================
 * 1. ImageAlt 接口 (API 22+):
 *    - placeholder: 图片加载过程中显示的占位图
 *    - error: 图片加载失败时显示的占位图
 *
 * 2. 与旧版 alt 的区别:
 *    - 旧版 alt(value: ResourceStr): 只有一个占位图，加载中和失败都用它
 *    - 新版 ImageAlt: 可分别配置，更灵活
 *
 * 3. 使用场景:
 *    - 网络图片加载：加载中显示 loading 图标，失败显示 error 图标
 *    - 用户体验优化：不同状态给予不同视觉反馈
 *
 * 4. 注意事项:
 *    - ImageAlt 从 API 22 开始支持
 *    - 不支持网络图片作为占位图
 *    - 占位图支持本地资源、PixelMap、Base64
 */

@Entry
@Component
struct ImageAltExample {
  @State validImage: ResourceStr = $r('app.media.startIcon');
  @State invalidImage: ResourceStr = 'invalid_path.png';
  @State currentImage: ResourceStr = $r('app.media.startIcon');
  @State isLoadError: boolean = false;
  @State altConfig: ImageAlt = {
    placeholder: $r('app.media.startIcon'),
    error: $r('app.media.startIcon')
  };

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('ImageAlt 占位图示例 (API 22+)')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // 示例 1: 基础用法 - 分别配置加载中和失败占位图
        Column({ space: 15 }) {
          Text('示例 1: 基础 ImageAlt 用法')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Row({ space: 20 }) {
            // 有效图片 - 正常显示
            Column({ space: 10 }) {
              Text('有效图片')
                .fontSize(14)
                .fontColor(Color.Gray)
              Image(this.validImage)
                .width(150)
                .height(150)
                .alt({
                  placeholder: $r('app.media.startIcon'),
                  error: $r('app.media.startIcon')
                })
                .borderRadius(10)
                .shadow({ radius: 10, color: '#20000000' })
            }
            .padding(15)
            .backgroundColor('#F0F8FF')
            .borderRadius(15)

            // 无效图片 - 显示失败占位图
            Column({ space: 10 }) {
              Text('无效图片 (点击触发)')
                .fontSize(14)
                .fontColor(Color.Gray)
              Image(this.isLoadError ? this.invalidImage : this.validImage)
                .width(150)
                .height(150)
                .alt({
                  placeholder: $r('app.media.startIcon'),
                  error: $r('app.media.startIcon')
                })
                .borderRadius(10)
                .shadow({ radius: 10, color: '#20000000' })
                .onError(() => {
                  console.info('图片加载失败，显示 error');
                })
            }
            .padding(15)
            .backgroundColor('#FFF0F0')
            .borderRadius(15)
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)

          Button('触发加载失败')
            .fontSize(14)
            .backgroundColor(Color.Orange)
            .onClick(() => {
              this.isLoadError = !this.isLoadError;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8FF')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 示例 2: 自定义占位图样式
        Column({ space: 15 }) {
          Text('示例 2: 自定义占位图样式')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Grid() {
            ForEach([0, 1, 2], (index: number) => {
              GridItem() {
                this.AltStyleCard(index)
              }
            })
          }
          .columnsTemplate('1fr 1fr 1fr')
          .rowsGap(15)
          .columnsGap(15)
          .width('100%')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 示例 3: 新旧 API 对比
        Column({ space: 15 }) {
          Text('示例 3: 新旧 alt API 对比')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Row({ space: 20 }) {
            // 旧版 alt
            Column({ space: 10 }) {
              Text('旧版 alt (单一占位图)')
                .fontSize(14)
                .fontColor(Color.Gray)
              Image($r('app.media.startIcon'))
                .width(120)
                .height(120)
                .alt($r('app.media.startIcon'))
                .borderRadius(10)
              Text('API 7+')
                .fontSize(12)
                .fontColor(Color.Blue)
            }
            .padding(15)
            .backgroundColor('#E8F4E8')
            .borderRadius(15)

            // 新版 ImageAlt
            Column({ space: 10 }) {
              Text('新版 ImageAlt (分别配置)')
                .fontSize(14)
                .fontColor(Color.Gray)
              Image($r('app.media.startIcon'))
                .width(120)
                .height(120)
                .alt({
                  placeholder: $r('app.media.startIcon'),
                  error: $r('app.media.startIcon')
                })
                .borderRadius(10)
              Text('API 22+')
                .fontSize(12)
                .fontColor(Color.Green)
            }
            .padding(15)
            .backgroundColor('#E8F4E8')
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

        // 示例 4: 网络图片 + ImageAlt
        Column({ space: 15 }) {
          Text('示例 4: 网络图片 + ImageAlt')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Column({ space: 10 }) {
            Image('https://example.com/invalid-image.png')
              .width(200)
              .height(150)
              .alt({
                placeholder: $r('app.media.startIcon'),
                error: $r('app.media.startIcon')
              })
              .borderRadius(10)
              .objectFit(ImageFit.Cover)
              .onError((error) => {
                console.info('网络图片加载失败:', JSON.stringify(error));
              })
            Text('网络图片失败时显示自定义占位图')
              .fontSize(14)
              .fontColor(Color.Gray)
          }
          .padding(15)
          .backgroundColor('#F0F0FF')
          .borderRadius(15)
          .width('100%')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E6E6FA')
        .borderRadius(15)

        Text('ImageAlt 提供更灵活的占位图控制，推荐 API 22+ 项目使用')
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
  AltStyleCard(index: number) {
    Column({ space: 10 }) {
      Image($r('app.media.startIcon'))
        .width(100)
        .height(100)
        .alt(this.getAltConfig(index))
        .borderRadius(10)
      Text(this.getAltTitle(index))
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(10)
    .width('100%')
  }

  getAltConfig(index: number): ImageAlt {
    const configs: ImageAlt[] = [
      {
        placeholder: $r('app.media.startIcon'),
        error: $r('app.media.startIcon')
      },
      {
        placeholder: $r('app.media.startIcon'),
        error: $r('app.media.startIcon')
      },
      {
        placeholder: $r('app.media.startIcon'),
        error: $r('app.media.startIcon')
      }
    ];
    return configs[index];
  }

  getAltTitle(index: number): string {
    const titles = ['标准占位图', '自定义 Loading', '自定义 Error'];
    return titles[index];
  }
}
