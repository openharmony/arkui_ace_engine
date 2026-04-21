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

/**
 * ========================================
 * 测试功能说明
 * ========================================
 * 本示例测试 Image 组件的图片解码功能
 *
 * 涉及的Image API:
 * 1. 基础: Image(src) - 图片数据源加载
 * 2. 事件: onComplete - 监听解码成功事件
 * 3. ImageKit: image.createImageSource() - 创建图片源
 * 4. ImageKit: image.createPixelMap() - 解码为PixelMap
 *
 * ========================================
 * 如何测试
 * ========================================
 * 测试步骤:
 * 1. 运行应用，进入 "图片解码 ImageDecoder" 页面
 * 2. 在 "选择图片格式" 区域选择不同格式（PNG/JPEG/GIF等）
 * 3. 点击 "开始解码" 按钮
 * 4. 观察页面显示的解码状态和结果
 *
 * 预期结果:
 * - 状态显示 "XXX 格式解码成功"
 * - 显示解码后的图片
 * - 显示图片尺寸信息
 *
 * ========================================
 * Image API 知识点
 * ========================================
 * 1. onComplete事件返回参数:
 *    - width: 图片原始宽度
 *    - height: 图片原始高度
 *    - loadingStatus: 0=数据加载成功, 1=解码成功
 *    - componentWidth/Height: 组件宽高
 *    - contentWidth/Height: 实际绘制宽高
 *
 * 2. Image支持的数据源:
 *    - PixelMap - 像素图（已解码）
 *    - ResourceStr - 资源路径 ($r('app.media.xxx'))
 *    - string - 网络URL或本地路径
 *    - DrawableDescriptor - 可绘制描述符
 *
 * 3. image.createImageSource() 创建图片源的输入:
 *    - ArrayBuffer - 图片二进制数据
 *    - string - Base64编码的图片数据
 *    - unit8Array - 图片字节数组
 */
@Entry
@Component
struct ImageDecoderExample {
  @State decodedImage: PixelMap | undefined = undefined;
  @State decodingStatus: string = '等待解码...';
  @State imageInfo: string = '';

  async decodeImage(format: string): Promise<void> {
    this.decodingStatus = '解码中...';
    this.decodedImage = undefined;

    try {
      // 模拟获取图片数据（实际应用中从网络或文件获取）
      const imageBuffer = await this.loadSampleImageBuffer();

      // 创建图片源
      const imageSource = image.createImageSource(imageBuffer);

      // 设置解码选项
      const decodingOptions: image.DecodingOptions = {
        editable: true,
        desiredPixelFormat: image.PixelMapFormat.RGBA_8888,
        desiredSize: { width: 200, height: 200 }
      };

      // 解码为PixelMap
      this.decodedImage = await imageSource.createPixelMap(decodingOptions);

      this.decodingStatus = `${format} 格式解码成功`;
      this.imageInfo = `尺寸: 200x200 | 格式: RGBA_8888`;

      // 释放资源
      imageSource.release();
    } catch (error) {
      this.decodingStatus = `${format} 格式解码失败`;
      this.imageInfo = `错误: ${JSON.stringify(error)}`;
    }
  }

  // 模拟加载图片数据（实际应从网络或文件读取）
  async loadSampleImageBuffer(): Promise<ArrayBuffer> {
    // 返回模拟的图片数据
    return new ArrayBuffer(100);
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片解码示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // 格式选择
        Column({ space: 10 }) {
          Text('选择图片格式进行解码测试:')
            .fontSize(16)
            .fontColor(Color.Gray)

          Row({ space: 10 }) {
            Button('PNG')
              .backgroundColor(Color.Blue)
              .onClick(() => this.decodeImage('PNG'))

            Button('JPEG')
              .onClick(() => this.decodeImage('JPEG'))

            Button('GIF')
              .onClick(() => this.decodeImage('GIF'))
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceEvenly)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        // 解码状态
        Column({ space: 15 }) {
          Text('解码状态: ' + this.decodingStatus)
            .fontSize(16)
            .fontColor(this.decodingStatus.includes('成功') ? Color.Green : Color.Gray)

          if (this.imageInfo) {
            Text(this.imageInfo)
              .fontSize(14)
              .fontColor(Color.Gray)
          }

          // 显示解码结果
          if (this.decodedImage) {
            Column({ space: 10 }) {
              Text('解码结果展示:')
                .fontSize(14)
                .fontColor(Color.Gray)

              Image(this.decodedImage)
                .width(200)
                .height(200)
                .objectFit(ImageFit.Contain)
                .border({ width: 2, color: Color.Green, radius: 10 })
                .onComplete((event) => {
                  console.info(`Image解码成功 - 宽: ${event.width}, 高: ${event.height}, 状态: ${event.loadingStatus}`);
                })
            }
          }
        }
        .width('100%')
        .padding(20)
        .backgroundColor('#F0F8FF')
        .borderRadius(10)

        Divider().strokeWidth(2).color('#E0E0E0')

        // API说明
        Column({ space: 10 }) {
          Text('测试的Image API:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Text('1. Image(src) - 支持多种数据源')
            .fontSize(14)
            .fontColor(Color.Gray)

          Text('2. onComplete - 监听图片解码完成事件')
            .fontSize(14)
            .fontColor(Color.Gray)

          Text('3. image.createImageSource() - 创建图片源对象')
            .fontSize(14)
            .fontColor(Color.Gray)

          Text('4. image.createPixelMap() - 解码为PixelMap')
            .fontSize(14)
            .fontColor(Color.Gray)
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
