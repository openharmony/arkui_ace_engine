/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * ========================================
 * Image CAPI 主入口 (NodeContent 方式)
 * ========================================
 * 
 * 示例目的：
 * 1. 展示如何使用 NodeContent 方式创建 Native UI
 * 2. 提供 Image 组件 CAPI 的统一测试入口
 * 3. 演示 Native Image 组件的各种功能
 * 
 * 涉及 API：
 * - NodeContent: ArkTS 与 Native 交互的桥梁
 * - ContentSlot: Native UI 的占位容器
 * - nativeNode.createNativeRoot: 创建 Native 根节点
 * 
 * 测试步骤：
 * 1. 点击 "Show Native UI" 按钮显示 Native Image 列表
 * 2. 滚动查看 11 个不同的 Image 测试用例
 * 3. 点击 "Hide Native UI" 销毁 Native 组件
 * 
 * 预期结果：
 * - Native Image 组件正常渲染
 * - 所有测试用例（切片、Lattice、Matrix 等）正常显示
 * - 显示/隐藏控制响应正常
 * 
 * 注意事项：
 * - 本示例使用 NodeContent 方式（推荐）
 * - XComponent 传统方式已被废弃，不再使用
 * - 确保 libentry.so 已正确编译
 */

import nativeNode from 'libentry.so';
import { NodeContent } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  // 初始化 NodeContent 对象，用于 Native 创建组件的挂载显示
  private rootSlot: NodeContent = new NodeContent();
  
  @State @Watch('changeNativeFlag') showNative: boolean = false;

  // 监听 showNative 变化，创建或销毁 Native 组件
  changeNativeFlag(): void {
    if (this.showNative) {
      // 传递 NodeContent 对象用于 Native 创建组件的挂载显示
      nativeNode.createNativeRoot(this.rootSlot)
    } else {
      // 销毁 NativeModule 组件
      nativeNode.destroyNativeRoot()
    }
  }

  build() {
    Column() {
      // 顶部控制栏
      Row({ space: 15 }) {
        Button(this.showNative ? 'Hide Native UI' : 'Show Native UI')
          .fontSize(14)
          .backgroundColor(this.showNative ? Color.Red : Color.Green)
          .onClick(() => {
            this.showNative = !this.showNative
          })
          .id('btn_toggle_native')
      }
      .width('100%')
      .padding(10)
      .backgroundColor('#F0F0F0')

      // 模式说明
      Text('NodeContent 方式 (推荐的 Native UI 创建方式)')
        .fontSize(12)
        .fontColor(Color.Gray)
        .margin({ top: 5, bottom: 10 })

      // 内容区域 - Native UI 容器
      Row() {
        ContentSlot(this.rootSlot)
      }
      .layoutWeight(1)
      .width('100%')

      // 底部说明
      Column({ space: 10 }) {
        Text('测试用例说明：')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
        
        Text('共 11 个测试用例，包括：基础加载、九宫格切片、Lattice 渲染、')
          .fontSize(12)
          .fontColor(Color.Gray)
        
        Text('Matrix 变换、方向旋转、抗锯齿等功能测试')
          .fontSize(12)
          .fontColor(Color.Gray)
      }
      .padding(10)
      .backgroundColor('#F5F5F5')
      .width('100%')
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.White)
  }
}
