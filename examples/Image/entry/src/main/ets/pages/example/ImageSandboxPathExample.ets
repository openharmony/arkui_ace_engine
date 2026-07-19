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

import { fileUri } from '@kit.CoreFileKit';
import { fileIo as fs } from '@kit.CoreFileKit';
import { BusinessError } from '@kit.BasicServicesKit';

/**
 * ========================================
 * 沙箱路径加载图片示例 (对齐官方示例 24)
 * ========================================
 * 功能说明:
 * 本示例演示如何使用应用沙箱路径 (file://) 加载本地图片文件。
 * 沙箱路径常用于加载应用运行时下载、缓存或用户自建的图片文件。
 *
 * 涉及的 Image API:
 * 1. Image(src: string) - 接受 file:// 前缀的沙箱 URI
 * 2. fileUri.getUriFromPath() - 将沙箱文件路径转换为 file:// URI
 * 3. context.filesDir - 获取应用沙箱 files 目录
 * 4. fileIo - 读写沙箱文件
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 显示应用下载后保存在沙箱中的图片
 * - 显示用户拍照后保存的图片
 * - 显示从资源目录拷贝到沙箱的图片
 * - 显示缓存目录中的图片
 *
 * ========================================
 * 注意事项
 * ========================================
 * 1. 沙箱 URI 格式: file://<bundleName>/<sandboxPath>
 * 2. 必须使用 fileUri.getUriFromPath 将路径转换为 URI
 * 3. 沙箱目录下的文件必须可读
 * 4. ArkTS 卡片不支持 file:// 路径前缀
 */

@Entry
@Component
struct ImageSandboxPathExample {
  @State sandboxUri: string = '';
  @State filesDirPath: string = '';
  @State loadStatus: string = '准备就绪';
  @State imageWidth: number = 200;
  @State imageHeight: number = 200;
  @State objectFit: ImageFit = ImageFit.Cover;
  @State copyProgress: number = 0;

  aboutToAppear(): void {
    this.initSandboxImage();
  }

  /**
   * 初始化沙箱图片：将资源图片拷贝到沙箱目录，然后生成 URI
   */
  private initSandboxImage(): void {
    try {
      const context: Context = this.getUIContext().getHostContext() as Context;
      const targetPath: string = `${context.filesDir}/sandbox_demo.png`;
      this.filesDirPath = targetPath;

      // 将资源图片拷贝到沙箱目录（实际项目中可能是网络下载或用户文件）
      const resourceManager = context.resourceManager;
      const imageData: Uint8Array = resourceManager.getMediaContent($r('app.media.startIcon').id);
      const file: fs.File = fs.openSync(targetPath, fs.OpenMode.READ_WRITE | fs.OpenMode.CREATE);
      fs.writeSync(file.fd, imageData.buffer);
      fs.closeSync(file);

      // 通过 fileUri.getUriFromPath 将沙箱路径转换为 URI
      this.sandboxUri = fileUri.getUriFromPath(targetPath);
      this.loadStatus = '图片已准备就绪';
      this.copyProgress = 100;
    } catch (error) {
      const err = error as BusinessError;
      this.loadStatus = `初始化失败: ${err.message}`;
      console.error(`initSandboxImage failed, code: ${err.code}, message: ${err.message}`);
    }
  }

  /**
   * 删除沙箱文件，演示文件不存在时的占位图效果
   */
  private deleteSandboxImage(): void {
    try {
      if (this.filesDirPath && fs.accessSync(this.filesDirPath)) {
        fs.unlinkSync(this.filesDirPath);
        this.sandboxUri = '';
        this.loadStatus = '沙箱文件已删除';
      }
    } catch (error) {
      const err = error as BusinessError;
      console.error(`deleteSandboxImage failed: ${err.message}`);
    }
  }

  /**
   * 重新生成沙箱图片
   */
  private restoreSandboxImage(): void {
    this.initSandboxImage();
  }

  build(): void {
    Scroll() {
      Column({ space: 16 }) {
        Text('沙箱路径加载图片示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 8 })

        Text('对齐官方文档示例 24 · 使用 file:// 协议加载')
          .fontSize(12)
          .fontColor(Color.Gray)
          .margin({ bottom: 8 })

        // 图片预览区
        Column({ space: 12 }) {
          Text('图片预览')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          if (this.sandboxUri) {
            Image(this.sandboxUri)
              .width(this.imageWidth)
              .height(this.imageHeight)
              .objectFit(this.objectFit)
              .alt($r('app.media.startIcon'))
              .borderRadius(12)
              .border({ width: 2, color: '#E0E0E0' })
              .shadow({ radius: 12, color: '#1A000000', offsetX: 0, offsetY: 4 })
              .onComplete((event) => {
                if (event) {
                  this.loadStatus = `加载成功 · 尺寸: ${event.width}x${event.height}`;
                }
              })
              .onError((error) => {
                this.loadStatus = `加载失败: ${(error as BusinessError).message}`;
              })
          } else {
            Column({ space: 8 }) {
              Text('暂无图片')
                .fontSize(16)
                .fontColor(Color.Gray)
              Text('请点击"恢复图片"按钮')
                .fontSize(12)
                .fontColor(Color.Gray)
            }
            .width(this.imageWidth)
            .height(this.imageHeight)
            .borderRadius(12)
            .backgroundColor('#F5F5F5')
            .justifyContent(FlexAlign.Center)
          }

          // 状态信息
          Row({ space: 8 }) {
            Text('状态:')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(this.loadStatus)
              .fontSize(12)
              .fontColor(Color.Blue)
              .layoutWeight(1)
          }
          .width('100%')
          .padding(8)
          .backgroundColor('#F8F8FF')
          .borderRadius(8)
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFFFFF')
        .borderRadius(16)

        // 沙箱信息
        Column({ space: 10 }) {
          Text('沙箱路径信息')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.InfoRow('文件路径', this.filesDirPath || '(尚未生成)')
          this.InfoRow('file URI', this.sandboxUri || '(尚未生成)')
          this.InfoRow('拷贝进度', `${this.copyProgress}%`)
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFF8DC')
        .borderRadius(16)

        // 尺寸与填充模式控制
        Column({ space: 12 }) {
          Text('尺寸与填充模式')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Row({ space: 8 }) {
            Text('宽度')
              .fontSize(12)
              .width(50)
            Slider(value: this.imageWidth, min: 80, max: 320, step: 10)
              .layoutWeight(1)
              .onChange((value: number) => {
                this.imageWidth = value;
              })
            Text(`${this.imageWidth}`)
              .fontSize(12)
              .width(40)
          }
          .width('100%')

          Row({ space: 8 }) {
            Text('高度')
              .fontSize(12)
              .width(50)
            Slider(value: this.imageHeight, min: 80, max: 320, step: 10)
              .layoutWeight(1)
              .onChange((value: number) => {
                this.imageHeight = value;
              })
            Text(`${this.imageHeight}`)
              .fontSize(12)
              .width(40)
          }
          .width('100%')

          Row({ space: 8 }) {
            ForEach(
              [ImageFit.Cover, ImageFit.Contain, ImageFit.Fill, ImageFit.ScaleDown, ImageFit.None],
              (fit: ImageFit) => {
                Button(this.fitName(fit))
                  .fontSize(11)
                  .backgroundColor(this.objectFit === fit ? '#007DFF' : '#E0E0E0')
                  .fontColor(this.objectFit === fit ? Color.White : Color.Black)
                  .height(32)
                  .onClick(() => {
                    this.objectFit = fit;
                  })
              },
              (fit: ImageFit) => `${fit}`
            )
          }
          .width('100%')
          .flexWrap(FlexWrap.Wrap)
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#F0FFF0')
        .borderRadius(16)

        // 操作按钮
        Row({ space: 12 }) {
          Button('删除沙箱文件')
            .fontSize(13)
            .backgroundColor('#FF6347')
            .fontColor(Color.White)
            .layoutWeight(1)
            .height(40)
            .onClick(() => {
              this.deleteSandboxImage();
            })

          Button('恢复沙箱文件')
            .fontSize(13)
            .backgroundColor('#32CD32')
            .fontColor(Color.White)
            .layoutWeight(1)
            .height(40)
            .onClick(() => {
              this.restoreSandboxImage();
            })
        }
        .width('100%')

        // API 说明
        Column({ space: 8 }) {
          Text('API 说明')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
          this.DocItem('fileUri.getUriFromPath(path)', '将沙箱文件路径转为 file:// URI')
          this.DocItem('context.filesDir', '获取应用沙箱 files 目录')
          this.DocItem('fs.openSync / writeSync', '在沙箱中创建并写入文件')
          this.DocItem('Image(file://...)', '通过 URI 加载沙箱图片')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#E6F7FF')
        .borderRadius(16)

        Text('提示：实际项目中常用于显示下载、缓存或用户保存的图片')
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
  InfoRow(label: string, value: string): void {
    Row({ space: 8 }) {
      Text(label)
        .fontSize(12)
        .fontColor(Color.Gray)
        .width(80)
      Text(value)
        .fontSize(12)
        .fontColor(Color.Black)
        .layoutWeight(1)
        .maxLines(2)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
    }
    .width('100%')
    .padding(6)
    .backgroundColor('#FFFFFF')
    .borderRadius(6)
  }

  @Builder
  DocItem(api: string, desc: string): void {
    Row({ space: 8 }) {
      Text(api)
        .fontSize(11)
        .fontColor('#007DFF')
        .fontFamily('monospace')
        .width('45%')
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

  private fitName(fit: ImageFit): string {
    switch (fit) {
      case ImageFit.Cover:
        return 'Cover';
      case ImageFit.Contain:
        return 'Contain';
      case ImageFit.Fill:
        return 'Fill';
      case ImageFit.ScaleDown:
        return 'ScaleDown';
      case ImageFit.None:
        return 'None';
      default:
        return 'Cover';
    }
  }
}
