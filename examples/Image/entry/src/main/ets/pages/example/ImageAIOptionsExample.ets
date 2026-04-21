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
 * ImageAIOptions 深度示例 (API 12+)
 * ========================================
 * 测试功能说明:
 * 本示例深度测试 Image 组件的 imageAIOptions 参数 (API 12+)
 *
 * 涉及的 Image API:
 * 1. Image(src, imageAIOptions) - 带 AI 分析选项的 Image 构造函数 (API 12+)
 * 2. ImageAIOptions - AI 分析配置选项
 * 3. ImageAnalyzerController - AI 分析控制器
 * 4. ImageAnalyzerType - AI 分析类型枚举
 * 5. enableAnalyzer - 启用分析器开关
 *
 * ========================================
 * 如何测试
 * ========================================
 * 测试步骤:
 * 1. 进入 "Image AI Options" 页面
 * 2. 切换不同分析类型
 * 3. 点击控制器按钮获取支持的分析类型
 * 4. 观察分析结果输出
 *
 * 预期结果:
 * - AI 分析正常启动
 * - 控制器可获取支持的分析类型
 * - enableAnalyzer 开关正常工作
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
 * 4. 使用场景:
 *    - 图片内容识别
 *    - 场景分类
 *    - 智能标签
 *
 * 5. 注意事项:
 *    - 需要设备支持 AI 能力
 *    - 需要配置权限：ohos.permission.INTERNET
 *    - 必须配合 enableAnalyzer(true) 使用
 *    - 分析图像要求是静态非矢量图 (svg、gif 等不支持)
 *    - 仅支持 RGBA_8888 类型的 PixelMap
 */

import { image } from '@kit.ImageKit';

@Entry
@Component
struct ImageAIOptionsExample {
  @State imagePixelMap: image.PixelMap | undefined = undefined;
  @State isAnalyzerEnabled: boolean = true;
  @State analyzeResult: string = '等待分析...';
  @State selectedType: number = ImageAnalyzerType.SUBJECT;
  
  // AI 分析控制器
  private aiController: ImageAnalyzerController = new ImageAnalyzerController();
  
  // ImageAIOptions 配置 (API 12+)
  private options: ImageAIOptions = {
    types: [ImageAnalyzerType.SUBJECT, ImageAnalyzerType.TEXT],
    aiController: this.aiController
  };

  // 分析类型选项
  private analyzeTypes: Array<{ key: number; label: string; desc: string }> = [
    { key: ImageAnalyzerType.SUBJECT, label: '主体识别', desc: '识别图片中的主体对象' },
    { key: ImageAnalyzerType.TEXT, label: '文字识别', desc: '提取图片中的文字内容' },
    { key: ImageAnalyzerType.OBJECT_LOOKUP, label: '对象查找', desc: '查找图片中的特定对象' }
  ];

  aboutToAppear() {
    // 加载图片资源并转换为 PixelMap
    this.loadImagePixelMap();
  }

  // 加载图片并转换为 PixelMap (RGBA_8888 格式)
  async loadImagePixelMap() {
    try {
      // $r('app.media.startIcon') 需要替换为开发者所需的图像资源文件
      const resource = $r('app.media.startIcon');
      const unit8Array = await this.getUIContext().getHostContext()?.resourceManager?.getMediaContent(resource.id);
      if (unit8Array) {
        const imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength));
        const pixelMap: image.PixelMap = await imageSource.createPixelMap({
          desiredPixelFormat: image.PixelMapFormat.RGBA_8888
        });
        await imageSource.release();
        this.imagePixelMap = pixelMap;
        this.analyzeResult = '图片加载完成，准备 AI 分析';
      }
    } catch (error) {
      console.error('加载图片失败:', JSON.stringify(error));
      this.analyzeResult = '图片加载失败';
    }
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('Image AI Options 深度示例 (API 12+)')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // 图片展示区
        Column({ space: 15 }) {
          Text('AI 分析图片')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          // 使用 Image(src, imageAIOptions) 构造函数 (API 12+)
          Image(this.imagePixelMap, this.options)
            .width(250)
            .height(250)
            .borderRadius(20)
            .shadow({ radius: 20, color: '#30000000' })
            .enableAnalyzer(this.isAnalyzerEnabled)
            .onComplete(() => {
              console.info('图片加载完成，开始 AI 分析');
              this.analyzeResult = '图片加载完成，AI 分析已启动';
            })
            .onError((error) => {
              console.error('图片加载失败:', JSON.stringify(error));
              this.analyzeResult = '图片加载失败';
            })
        }
        .width('100%')
        .padding(20)
        .backgroundColor('#F8F8FF')
        .borderRadius(20)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 分析类型选择
        Column({ space: 15 }) {
          Text('选择分析类型')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          ForEach(this.analyzeTypes, (item: { key: number; label: string; desc: string }) => {
            Row({ space: 15 }) {
              RadioButton({
                name: item.key.toString(),
                group: 'analyzeType',
                checked: this.selectedType === item.key
              })
                .onChange((isChecked: boolean) => {
                  if (isChecked) {
                    this.selectedType = item.key;
                    // 更新 options 中的 types
                    this.options.types = [item.key];
                    this.analyzeResult = `切换分析类型：${item.label}`;
                  }
                })

              Column({ space: 5 }) {
                Text(item.label)
                  .fontSize(16)
                  .fontWeight(FontWeight.Medium)
                Text(item.desc)
                  .fontSize(12)
                  .fontColor(Color.Gray)
              }
            }
            .width('100%')
            .padding(15)
            .backgroundColor(this.selectedType === item.key ? '#E3F2FD' : '#F5F5F5')
            .borderRadius(10)
          })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#FFFFFF')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 分析控制
        Column({ space: 15 }) {
          Text('分析控制')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Row({ space: 15 }) {
            Toggle({ type: ToggleType.Switch, isOn: this.isAnalyzerEnabled })
              .onChange((isOn: boolean) => {
                this.isAnalyzerEnabled = isOn;
                this.analyzeResult = isOn ? '分析器已启用' : '分析器已禁用';
              })

            Text(this.isAnalyzerEnabled ? '分析器启用中' : '分析器已禁用')
              .fontSize(16)
              .fontColor(this.isAnalyzerEnabled ? Color.Green : Color.Gray)
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceBetween)
          .padding(15)
          .backgroundColor('#F0F8FF')
          .borderRadius(10)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 控制器操作
        Column({ space: 15 }) {
          Text('控制器操作')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Button('获取支持的分析类型')
            .fontSize(14)
            .backgroundColor(Color.Blue)
            .onClick(() => {
              const supportTypes = this.aiController.getImageAnalyzerSupportTypes();
              this.analyzeResult = `支持的分析类型：${JSON.stringify(supportTypes)}`;
            })
            .width('100%')
            .margin({ top: 10 })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E6E6FA')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 分析结果展示
        Column({ space: 15 }) {
          Text('分析结果')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Column({ space: 10 }) {
            Text(this.analyzeResult)
              .fontSize(14)
              .fontColor(Color.Black)
              .width('100%')
              .multiline(true)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFF8DC')
          .borderRadius(10)
          .minHeight(100)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E6E6FA')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 操作按钮
        Row({ space: 15 }) {
          Button('重新加载图片')
            .fontSize(14)
            .backgroundColor(Color.Blue)
            .onClick(() => {
              this.analyzeResult = '重新加载图片中...';
              this.loadImagePixelMap();
            })

          Button('清除结果')
            .fontSize(14)
            .backgroundColor(Color.Gray)
            .onClick(() => {
              this.analyzeResult = '等待分析...';
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Text('说明：imageAIOptions 用于配置 AI 分析，需要设备支持 AI 能力。必须配合 enableAnalyzer(true) 使用，且图片必须是 RGBA_8888 格式的 PixelMap。')
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
}
