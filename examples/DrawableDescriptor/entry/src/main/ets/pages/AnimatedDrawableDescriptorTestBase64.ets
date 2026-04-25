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
 * ========================================
 * AnimatedDrawableDescriptorTestBase64 - BASE64 字符串创建用例 (API 21+)
 * ========================================
 *
 * 测试功能说明:
 * 验证使用 BASE64 字符串创建 AnimatedDrawableDescriptor
 *
 * 涉及的 API:
 * 1. constructor(src: ResourceStr | Array<PixelMap>, options?: AnimationOptions)
 *    - ResourceStr 支持: 应用资源 Resource, 沙箱路径 (file:///), BASE64 字符串
 * 2. fileUri.getUriFromPath() - 将沙箱路径转为 file:// URI
 *
 * ========================================
 * API 文档说明
 * ====================================
 * ResourceStr 当前支持的范围:
 *   - 应用资源 Resource
 *   - 沙箱路径 (file:///)
 *   - BASE64 字符串
 */

import { AnimatedDrawableDescriptor } from '@kit.ArkUI';
import { fileUri } from '@kit.CoreFileKit';
import { image } from '@kit.ImageKit';

@Entry
@Component
struct AnimatedDrawableDescriptorTestBase64 {
  @State animatedFromResource?: AnimatedDrawableDescriptor = undefined;
  @State animatedFromSandbox?: AnimatedDrawableDescriptor = undefined;
  @State animatedFromBase64?: AnimatedDrawableDescriptor = undefined;
  @Status loadResult: string = '等待操作...';
  @State sandboxPath: string = '';

  aboutToAppear() {
    // 方式1: 应用资源 Resource
    this.animatedFromResource = new AnimatedDrawableDescriptor(
      $r('app.media.flower'),
      { duration: 2000, iterations: -1 }
    );

    // 方式2: 沙箱路径 file://
    this.initSandboxPath();

    // 方式3: BASE64 字符串
    this.initBase64();
  }

  initSandboxPath() {
    const files = this.getUIContext().getHostContext()?.filesDir;
    if (files) {
      const originPath = files + '/flower.gif';
      const resultPath = fileUri.getUriFromPath(originPath);
      this.sandboxPath = resultPath;
      // 使用 fileUri.getUriFromPath() 转换后的沙箱路径
      this.animatedFromSandbox = new AnimatedDrawableDescriptor(
        resultPath,
        { iterations: -1 }
      );
    }
  }

  initBase64() {
    // 从资源读取 GIF 文件并转为 BASE64
    const resManager = this.getUIContext().getHostContext()?.resourceManager;
    if (resManager) {
      try {
        const buffer = resManager.getMediaContentSync($r('app.media.flower').id);
        // 将 ArrayBuffer 转为 BASE64 字符串
        const base64Str = 'data:image/gif;base64,' + this.arrayBufferToBase64(buffer.buffer);
        this.animatedFromBase64 = new AnimatedDrawableDescriptor(
          base64Str,
          { duration: 2000, iterations: -1 }
        );
      } catch (e) {
        this.loadResult = 'BASE64 初始化失败: ' + e;
      }
    }
  }

  arrayBufferToBase64(buffer: ArrayBuffer): string {
    const bytes = new Uint8Array(buffer);
    let binary = '';
    for (let i = 0; i < bytes.byteLength; i++) {
      binary += String.fromCharCode(bytes[i]);
    }
    // 使用 util 编码
    return buffer.toString();
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('AnimatedDrawableDescriptor 资源类型用例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        // API 说明
        Column({ space: 10 }) {
          Text('ResourceStr 支持类型')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)

          Text('constructor(src: ResourceStr | Array<PixelMap>, options?)')
            .fontSize(12)
            .backgroundColor(0xE8F5E9)
            .padding(10)
            .borderRadius(5)
            .width('100%')
            .fontColor(0x333333)

          Column({ space: 5 }) {
            Text('1. 应用资源 Resource: $r(\'app.media.gif\')')
              .fontSize(12)
              .fontColor(0x4CAF50)
            Text('2. 沙箱路径: file:///data/.../flower.gif')
              .fontSize(12)
              .fontColor(0xFF9800)
            Text('3. BASE64 字符串: data:image/gif;base64,...')
              .fontSize(12)
              .fontColor(0x9C27B0)
          }
          .padding(10)
          .backgroundColor(0xF5F5F5)
          .borderRadius(8)
          .width('100%')
        }
        .width('100%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)

        // 应用资源
        Column({ space: 10 }) {
          Text('1. 应用资源 Resource')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .fontColor(0x4CAF50)

          Text('$r(\'app.media.flower\')')
            .fontSize(12)
            .fontColor(0x666666)
            .backgroundColor(0xF5F5F5)
            .padding(8)
            .borderRadius(5)

          if (this.animatedFromResource) {
            Image(this.animatedFromResource)
              .width(150)
              .height(150)
              .borderRadius(10)
              .border({ width: 2, color: 0x4CAF50 })
          }
        }
        .width('100%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)
        .alignItems(HorizontalAlign.Center)

        // 沙箱路径
        Column({ space: 10 }) {
          Text('2. 沙箱路径 file://')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .fontColor(0xFF9800)

          Text(`路径: ${this.sandboxPath || '(需先将 gif 拷贝到沙箱目录)'}`)
            .fontSize(11)
            .fontColor(0x666666)
            .backgroundColor(0xFFF3E0)
            .padding(8)
            .borderRadius(5)
            .width('100%')
            .maxLines(3)

          Text('使用 fileUri.getUriFromPath() 转换路径')
            .fontSize(12)
            .fontColor(0xFF9800)
            .backgroundColor(0xFFF3E0)
            .padding(8)
            .borderRadius(5)

          if (this.animatedFromSandbox) {
            Image(this.animatedFromSandbox)
              .width(150)
              .height(150)
              .borderRadius(10)
              .border({ width: 2, color: 0xFF9800 })
          } else {
            Text('(沙箱路径文件不存在)')
              .fontSize(12)
              .fontColor(Color.Gray)
              .width(150)
              .height(150)
              .textAlign(TextAlign.Center)
              .backgroundColor(0xF0F0F0)
              .borderRadius(10)
          }
        }
        .width('100%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)
        .alignItems(HorizontalAlign.Center)

        // BASE64
        Column({ space: 10 }) {
          Text('3. BASE64 字符串')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .fontColor(0x9C27B0)

          Text('从资源读取并转为 BASE64 字符串传入')
            .fontSize(12)
            .fontColor(0x666666)

          if (this.animatedFromBase64) {
            Image(this.animatedFromBase64)
              .width(150)
              .height(150)
              .borderRadius(10)
              .border({ width: 2, color: 0x9C27B0 })
          } else {
            Text('(BASE64 创建失败)')
              .fontSize(12)
              .fontColor(Color.Gray)
              .width(150)
              .height(150)
              .textAlign(TextAlign.Center)
              .backgroundColor(0xF0F0F0)
              .borderRadius(10)
          }
        }
        .width('100%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)
        .alignItems(HorizontalAlign.Center)

        // 测试结果
        Text(this.loadResult)
          .fontSize(14)
          .fontColor(0x2196F3)
          .padding(15)
          .backgroundColor(0xE8F5E9)
          .borderRadius(10)
          .width('100%')
          .margin({ bottom: 20 })
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }
}
