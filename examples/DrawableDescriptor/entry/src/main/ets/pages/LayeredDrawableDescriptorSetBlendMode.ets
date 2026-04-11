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
 * LayeredDrawableDescriptorSetBlendMode - setBlendMode 用例 (API 23+)
 * ========================================
 *
 * 测试功能说明:
 * 验证 LayeredDrawableDescriptor.setBlendMode() 方法
 * 设置分层图标的混合模式
 *
 * 涉及的 API:
 * 1. LayeredDrawableDescriptor.setBlendMode(mode: drawing.BlendMode)
 * 2. drawing.BlendMode 枚举值
 *
 * ========================================
 * API 文档说明
 * ========================================
 * setBlendMode(mode: drawing.BlendMode): void
 * - 设置 LayeredDrawableDescriptor 的混合模式
 * - 对同一对象多次调用时，仅在绘制完成前的最后一次调用生效
 * - 不支持动态切换
 * - 设置混合模式后绘制顺序变为: 背景 → 前景 → 蒙版
 * - 若设置值无效，则按照未设置混合模式进行绘制
 */

import { DrawableDescriptor, LayeredDrawableDescriptor, PixelMapDrawableDescriptor } from '@kit.ArkUI';
import { image } from '@kit.ImageKit';
import { drawing } from '@kit.ArkGraphics2D';

interface BlendModeItem {
  name: string;
  mode: drawing.BlendMode;
}

@Entry
@Component
struct LayeredDrawableDescriptorSetBlendMode {
  @State blendModeName: string = 'SRC_OVER';
  @State currentBlendMode: drawing.BlendMode = drawing.BlendMode.SRC_OVER;
  @State drawableDescriptor: DrawableDescriptor | undefined = undefined;
  @State layeredWithPixelMap: LayeredDrawableDescriptor | undefined = undefined;

  private blendModeList: BlendModeItem[] = [
    { name: 'SRC_OVER', mode: drawing.BlendMode.SRC_OVER },
    { name: 'SRC', mode: drawing.BlendMode.SRC },
    { name: 'DST_OVER', mode: drawing.BlendMode.DST_OVER },
    { name: 'DST_IN', mode: drawing.BlendMode.DST_IN },
    { name: 'SRC_IN', mode: drawing.BlendMode.SRC_IN },
    { name: 'MULTIPLY', mode: drawing.BlendMode.MULTIPLY },
    { name: 'SCREEN', mode: drawing.BlendMode.SCREEN },
    { name: 'OVERLAY', mode: drawing.BlendMode.OVERLAY },
    { name: 'DARKEN', mode: drawing.BlendMode.DARKEN },
    { name: 'LIGHTEN', mode: drawing.BlendMode.LIGHTEN },
  ];

  async aboutToAppear() {
    // 方式1: 从资源管理器获取 LayeredDrawableDescriptor
    const resManager = this.getUIContext().getHostContext()?.resourceManager;
    if (resManager) {
      const drawable = resManager.getDrawableDescriptor($r('app.media.layered_image').id);
      if (drawable instanceof LayeredDrawableDescriptor) {
        drawable.setBlendMode(drawing.BlendMode.SRC_OVER);
        this.drawableDescriptor = drawable;
      }
    }

    // 方式2: 使用 PixelMapDrawableDescriptor 创建并设置混合模式
    await this.createLayeredFromPixelMap(drawing.BlendMode.SRC_OVER);
  }

  async createLayeredFromPixelMap(blendMode: drawing.BlendMode) {
    const resManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resManager) return;

    try {
      // 获取前景 PixelMap
      const foreBuffer = resManager.getMediaContentSync($r('app.media.foreground').id);
      const foreSource = image.createImageSource(foreBuffer.buffer.slice(0, foreBuffer.buffer.byteLength));
      const forePixelMap = await foreSource.createPixelMap({ desiredPixelFormat: image.PixelMapFormat.BGRA_8888 });
      await foreSource.release();

      // 获取背景 PixelMap
      const backBuffer = resManager.getMediaContentSync($r('app.media.background').id);
      const backSource = image.createImageSource(backBuffer.buffer.slice(0, backBuffer.buffer.byteLength));
      const backPixelMap = await backSource.createPixelMap({ desiredPixelFormat: image.PixelMapFormat.BGRA_8888 });
      await backSource.release();

      // 使用 PixelMapDrawableDescriptor 创建 LayeredDrawableDescriptor
      const foregroundDraw = new PixelMapDrawableDescriptor(forePixelMap);
      const backgroundDraw = new PixelMapDrawableDescriptor(backPixelMap);
      const layered = new LayeredDrawableDescriptor(foregroundDraw, backgroundDraw);

      // 设置混合模式
      layered.setBlendMode(blendMode);
      this.layeredWithPixelMap = layered;
    } catch (e) {
      console.error(`createLayeredFromPixelMap failed: ${e}`);
    }
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('setBlendMode 用例 (API 23+)')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        // API 说明
        Column({ space: 10 }) {
          Text('API 说明')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)

          Text('setBlendMode(mode: drawing.BlendMode): void')
            .fontSize(14)
            .backgroundColor(0xE8F5E9)
            .padding(10)
            .borderRadius(5)
            .width('100%')
            .fontColor(0x333333)

          Text('设置混合模式后绘制顺序变为: 背景 → 前景 → 蒙版')
            .fontSize(12)
            .fontColor(Color.Orange)
            .backgroundColor(0xFFF3E0)
            .padding(10)
            .borderRadius(5)

          Text('对同一对象多次调用时，仅最后一次生效，不支持动态切换')
            .fontSize(12)
            .fontColor(0x666666)
        }
        .width('100%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)

        // 混合模式选择
        Column({ space: 15 }) {
          Text('选择混合模式')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)

          Text(`当前模式: ${this.blendModeName}`)
            .fontSize(14)
            .fontColor(0x2196F3)
            .fontWeight(FontWeight.Bold)

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(this.blendModeList, (item: BlendModeItem) => {
              Button(item.name)
                .fontSize(11)
                .margin(5)
                .backgroundColor(this.blendModeName === item.name ? Color.Blue : Color.LightGray)
                .onClick(() => {
                  this.blendModeName = item.name;
                  this.currentBlendMode = item.mode;
                  this.applyBlendMode(item.mode);
                })
            })
          }
        }
        .width('100%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)

        // 效果展示
        Column({ space: 20 }) {
          Text('效果展示')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)

          Row({ space: 20 }) {
            // 从资源获取的 LayeredDrawableDescriptor
            Column({ space: 5 }) {
              Text('资源方式')
                .fontSize(14)
                .fontColor(0x4CAF50)
              if (this.drawableDescriptor) {
                Image(this.drawableDescriptor)
                  .width(150)
                  .height(150)
                  .borderRadius(10)
                  .border({ width: 1, color: Color.Green })
              }
            }

            // PixelMap 方式
            Column({ space: 5 }) {
              Text('PixelMap 方式')
                .fontSize(14)
                .fontColor(0xFF9800)
              if (this.layeredWithPixelMap) {
                Image(this.layeredWithPixelMap)
                  .width(150)
                  .height(150)
                  .borderRadius(10)
                  .border({ width: 1, color: Color.Orange })
              }
            }
          }
        }
        .width('100%')
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)
        .alignItems(HorizontalAlign.Center)
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  applyBlendMode(mode: drawing.BlendMode) {
    // 重新创建并设置混合模式（因为不支持动态切换）
    const resManager = this.getUIContext().getHostContext()?.resourceManager;
    if (resManager) {
      const drawable = resManager.getDrawableDescriptor($r('app.media.layered_image').id);
      if (drawable instanceof LayeredDrawableDescriptor) {
        drawable.setBlendMode(mode);
        this.drawableDescriptor = drawable;
      }
    }

    // PixelMap 方式
    this.createLayeredFromPixelMap(mode);
  }
}
