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
 * Image AI 分析控制器示例 (API 12+)
 * ========================================
 * 测试功能说明:
 * 本示例演示如何使用 ImageAIOptions 配置 AI 分析控制器
 *
 * 涉及的 Image API:
 * 1. Image(src, imageAIOptions) - 带 AI 分析选项的 Image 构造函数 (API 12+)
 * 2. ImageAIOptions - AI 分析配置选项
 * 3. ImageAnalyzerController - AI 分析控制器
 * 4. ImageAnalyzerType - AI 分析类型枚举
 * 5. enableAnalyzer - 启用分析器开关
 *
 * ========================================
 * Image API 知识点
 * ========================================
 * 1. Image 构造函数 (API 12+):
 *    - Image(src: PixelMap | ResourceStr | DrawableDescriptor, imageAIOptions: ImageAIOptions)
 *    - 第二个参数为 ImageAIOptions 对象
 *
 * 2. ImageAIOptions 配置:
 *    - types: ImageAnalyzerType[] 分析类型数组
 *    - aiController: ImageAnalyzerController 分析控制器 (可选)
 *
 * 3. ImageAnalyzerType 枚举:
 *    - SUBJECT = 0: 主体识别
 *    - TEXT = 1: 文字识别
 *    - OBJECT_LOOKUP = 2: 对象查找
 *
 * 4. 注意事项:
 *    - 需要设备支持 AI 能力
 *    - 需要配置权限：ohos.permission.INTERNET
 *    - 必须配合 enableAnalyzer(true) 使用
 *    - 分析图像要求是静态非矢量图 (svg、gif 等不支持)
 */

@Entry
@Component
struct ImageExample033 {
  // AI 分析控制器
  private aiController: ImageAnalyzerController = new ImageAnalyzerController();
  
  // ImageAIOptions 配置 (API 12+)
  private options: ImageAIOptions = {
    types: [ImageAnalyzerType.SUBJECT],
    aiController: this.aiController
  };

  build() {
    Column() {
      // 使用 Image(src, imageAIOptions) 构造函数 (API 12+)
      Image($r('app.media.font3'), this.options)
        .enableAnalyzer(true)
        .width(200)
        .height(200)
      
      Image($r('app.media.font2')).overlay(this.builder)
        .width(300).height(200)
    }
  }

  @Builder
  builder() {
    Text('132321321')
      .width(90)
      .height(30)
  }
}