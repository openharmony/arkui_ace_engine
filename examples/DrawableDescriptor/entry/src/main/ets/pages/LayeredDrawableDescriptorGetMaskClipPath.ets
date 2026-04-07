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
 * LayeredDrawableDescriptorGetMaskClipPath - getMaskClipPath 用例
 * ========================================
 *
 * 测试功能说明:
 * 验证 LayeredDrawableDescriptor.getMaskClipPath() 静态方法
 * 获取系统内置裁切路径参数，并用于 clipShape 裁切图片
 *
 * 涉及的 API:
 * 1. LayeredDrawableDescriptor.getMaskClipPath() - 获取系统内置裁切路径
 * 2. Image.clipShape(new Path({ commands })) - 使用路径裁切
 *
 * ========================================
 * API 文档说明
 * ========================================
 * static getMaskClipPath(): string
 * - 获取系统内置的裁切路径参数
 * - 返回裁切路径的命令字符串
 */

import { DrawableDescriptor, LayeredDrawableDescriptor } from '@kit.ArkUI';

@Entry
@Component
struct LayeredDrawableDescriptorGetMaskClipPath {
  @State clipPathCommands: string = '';
  @State layeredDrawable?: DrawableDescriptor = undefined;
  @State showClipped: boolean = false;

  private resManager = this.getUIContext().getHostContext()?.resourceManager;

  aboutToAppear(): void {
    // 获取系统内置裁切路径
    this.clipPathCommands = LayeredDrawableDescriptor.getMaskClipPath();

    // 从资源创建 LayeredDrawableDescriptor
    if (this.resManager) {
      this.layeredDrawable = this.resManager.getDrawableDescriptor($r('app.media.layered_image').id);
    }
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('getMaskClipPath 用例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        // API 说明
        Column({ space: 10 }) {
          Text('API 说明')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)

          Text('static getMaskClipPath(): string')
            .fontSize(14)
            .backgroundColor(0xE8F5E9)
            .padding(10)
            .borderRadius(5)
            .width('100%')
            .fontColor(0x333333)

          Text('获取系统内置的裁切路径参数，返回 SVG path 命令字符串')
            .fontSize(12)
            .fontColor(0x666666)
        }
        .width('100%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)

        // 裁切路径命令内容
        Column({ space: 10 }) {
          Text('裁切路径命令:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Text(this.clipPathCommands)
            .fontSize(11)
            .fontColor(0x666666)
            .padding(10)
            .backgroundColor(0xF5F5F5)
            .borderRadius(8)
            .width('100%')
            .maxLines(6)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .copyOption(CopyOptions.LocalDevice)
        }
        .width('100%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)

        // 对比展示
        Column({ space: 15 }) {
          Text('效果对比')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)

          // 原始图片
          Column({ space: 5 }) {
            Text('原始图片')
              .fontSize(14)
              .fontColor(0x666666)

            Image($r('app.media.icon'))
              .width(200)
              .height(200)
              .border({ width: 1, color: Color.Gray })
          }

          // 使用 getMaskClipPath 裁切后的图片
          Column({ space: 5 }) {
            Text('使用 getMaskClipPath 裁切')
              .fontSize(14)
              .fontColor(0x2196F3)

            Image($r('app.media.icon'))
              .width(200)
              .height(200)
              .clipShape(new Path({ commands: this.clipPathCommands }))
              .border({ width: 1, color: Color.Blue })
          }

          // LayeredDrawableDescriptor 显示
          if (this.layeredDrawable instanceof LayeredDrawableDescriptor) {
            Column({ space: 5 }) {
              Text('LayeredDrawableDescriptor')
                .fontSize(14)
                .fontColor(0x4CAF50)

              Image(this.layeredDrawable)
                .width(200)
                .height(200)
                .clipShape(new Path({ commands: this.clipPathCommands }))
                .border({ width: 1, color: Color.Green })
            }
          }
        }
        .width('100%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)
        .alignItems(HorizontalAlign.Center)

        // 切换按钮
        Button(this.showClipped ? '显示原图' : '显示裁切效果')
          .width('90%')
          .onClick(() => {
            this.showClipped = !this.showClipped;
          })
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
