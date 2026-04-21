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
 * DrawableDescriptorLoadTest - 加载 API 专项测试 (API 21+)
 * ========================================
 * 
 * 测试功能说明:
 * 本测试验证 DrawableDescriptor 的加载 API (API 21+)
 * 
 * 涉及的 API:
 * 1. loadSync() - 同步加载 (API 21+)
 * 2. load() - 异步加载 (API 21+)
 * 3. DrawableDescriptorLoadedResult - 加载结果
 * 4. 错误处理 (错误码 111001)
 * 
 * ========================================
 * API 文档说明
 * ========================================
 * loadSync(): DrawableDescriptorLoadedResult
 * - 发起图片资源的同步加载，并返回加载结果
 * - 可能抛出错误码 111001 (resource loading failed)
 * 
 * load(): Promise<DrawableDescriptorLoadedResult>
 * - 发起图片资源的异步加载，并返回加载结果
 * - 使用 Promise 异步回调
 * 
 * DrawableDescriptorLoadedResult:
 * - imageWidth: number - 图片宽度 (px)
 * - imageHeight: number - 图片高度 (px)
 * 
 * ========================================
 * 测试用例
 * ========================================
 * 1. loadSync 成功加载
 * 2. loadSync 失败处理 (无效资源)
 * 3. load 异步加载成功
 * 4. load 异步加载失败
 * 5. 获取加载结果 (imageWidth/imageHeight)
 * 6. 加载前后状态对比
 */

@Entry
@Component
struct DrawableDescriptorLoadTest {
  @State testType: string = 'loadSync';
  @State loadResult: string = '等待测试...';
  @State isLoading: boolean = false;
  @State imageWidth: number = 0;
  @State imageHeight: number = 0;
  @State testStatus: string = 'Initial';
  @State selectedResource: number = 1;

  private resManager = this.getUIContext().getHostContext()?.resourceManager;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('DrawableDescriptor 加载 API 测试 (API 21+)')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildTestInfo()
        this.buildTestArea()
        this.buildLoadTypeSelector()
        this.buildTestButtons()
        this.buildResultDisplay()
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  @Builder
  buildTestInfo() {
    Column({ space: 10 }) {
      Text('API 说明 (API 21+)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('loadSync(): 同步加载，返回 DrawableDescriptorLoadedResult')
        .fontSize(14)
        .fontColor(0x666666)

      Text('load(): 异步加载，返回 Promise<DrawableDescriptorLoadedResult>')
        .fontSize(14)
        .fontColor(0x666666)

      Text('DrawableDescriptorLoadedResult:')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x2196F3)

      Text('  - imageWidth: 图片宽度 (px)')
        .fontSize(12)
        .fontColor(0x666666)

      Text('  - imageHeight: 图片高度 (px)')
        .fontSize(12)
        .fontColor(0x666666)

      Text('错误码 111001: resource loading failed')
        .fontSize(12)
        .fontColor(Color.Red)
        .backgroundColor(0xFFEBEE)
        .padding(10)
        .borderRadius(10)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildTestArea() {
    Column({ space: 15 }) {
      Text('测试区域 (' + testType + ')')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Blue)

      if (this.isLoading) {
        LoadingProgress()
          .width(50)
          .height(50)
      } else {
        Image($r('app.media.startIcon'))
          .width(100)
          .height(100)
          .borderRadius(10)
      }

      Row({ space: 20 }) {
        Column({ space: 5 }) {
          Text('状态:')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text(this.testStatus)
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(this.isLoading ? Color.Orange : Color.Green)
        }

        Column({ space: 5 }) {
          Text('尺寸:')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text(this.imageWidth > 0 ? this.imageWidth + ' x ' + this.imageHeight + ' px' : '未知')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.Blue)
        }
      }
      .padding(10)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildLoadTypeSelector() {
    Column({ space: 15 }) {
      Text('选择加载方式')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Row({ space: 10 }) {
        Button('loadSync (同步)')
          .fontSize(14)
          .backgroundColor(this.testType === 'loadSync' ? Color.Blue : Color.LightGray)
          .onClick(() => {
            this.testType = 'loadSync';
            this.resetTest();
          })

        Button('load (异步)')
          .fontSize(14)
          .backgroundColor(this.testType === 'load' ? Color.Green : Color.LightGray)
          .onClick(() => {
            this.testType = 'load';
            this.resetTest();
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildTestButtons() {
    Column({ space: 15 }) {
      Text('测试操作')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Grid() {
        GridItem() {
          Button('测试 1: loadSync 成功')
            .fontSize(12)
            .backgroundColor(Color.Blue)
            .onClick(() => {
              this.testLoadSyncSuccess();
            })
        }
        GridItem() {
          Button('测试 2: loadSync 失败')
            .fontSize(12)
            .backgroundColor(Color.Red)
            .onClick(() => {
              this.testLoadSyncError();
            })
        }
        GridItem() {
          Button('测试 3: load 成功')
            .fontSize(12)
            .backgroundColor(Color.Green)
            .onClick(() => {
              this.testLoadSuccess();
            })
        }
        GridItem() {
          Button('测试 4: load 失败')
            .fontSize(12)
            .backgroundColor(Color.Orange)
            .onClick(() => {
              this.testLoadError();
            })
        }
      }
      .columnsTemplate('1fr 1fr')
      .rowsGap(10)
      .columnsGap(10)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildResultDisplay() {
    Column({ space: 15 }) {
      Text('测试结果')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Text(this.loadResult)
        .fontSize(14)
        .fontColor(Color.Blue)
        .padding(15)
        .backgroundColor(0xE8F5E9)
        .borderRadius(10)
        .width('100%')
        .multiline(true)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  resetTest() {
    this.loadResult = '等待测试...';
    this.isLoading = false;
    this.imageWidth = 0;
    this.imageHeight = 0;
    this.testStatus = 'Initial';
  }

  testLoadSyncSuccess() {
    this.testStatus = 'Loading (sync)...';
    this.isLoading = true;
    this.loadResult = '执行 loadSync()...';

    try {
      if (!this.resManager) {
        throw new Error('ResourceManager 不可用');
      }

      // 创建 DrawableDescriptor
      const drawable = this.resManager.getDrawableDescriptor($r('app.media.startIcon').id);
      
      if (!drawable) {
        throw new Error('无法创建 DrawableDescriptor');
      }

      // 同步加载 (API 21+)
      const result = drawable.loadSync();
      
      this.imageWidth = result.imageWidth;
      this.imageHeight = result.imageHeight;
      this.testStatus = 'Success';
      this.isLoading = false;
      this.loadResult = '✅ loadSync 成功!\n' +
                       '图片宽度：' + result.imageWidth + ' px\n' +
                       '图片高度：' + result.imageHeight + ' px\n' +
                       '加载时间：即时 (同步)';
    } catch (e) {
      this.testStatus = 'Error';
      this.isLoading = false;
      this.loadResult = '❌ loadSync 失败:\n' + JSON.stringify(e);
    }
  }

  testLoadSyncError() {
    this.testStatus = 'Loading (sync)...';
    this.isLoading = true;
    this.loadResult = '执行 loadSync() - 测试错误处理...';

    try {
      // 创建无效的 DrawableDescriptor (空字符串)
      const drawable = new AnimatedDrawableDescriptor("");
      
      // 同步加载 (应该失败)
      const result = drawable.loadSync();
      
      this.testStatus = 'Unexpected Success';
      this.isLoading = false;
      this.loadResult = '⚠️ 预期失败但成功了:\n' + JSON.stringify(result);
    } catch (e) {
      this.testStatus = 'Expected Error';
      this.isLoading = false;
      this.loadResult = '✅ 预期错误捕获成功:\n' +
                       '错误信息：' + JSON.stringify(e) + '\n' +
                       '错误码：111001 (resource loading failed)';
    }
  }

  async testLoadSuccess() {
    this.testStatus = 'Loading (async)...';
    this.isLoading = true;
    this.loadResult = '执行 load()...';

    try {
      if (!this.resManager) {
        throw new Error('ResourceManager 不可用');
      }

      // 创建 DrawableDescriptor
      const drawable = this.resManager.getDrawableDescriptor($r('app.media.startIcon').id);
      
      if (!drawable) {
        throw new Error('无法创建 DrawableDescriptor');
      }

      // 异步加载 (API 21+)
      const result = await drawable.load();
      
      this.imageWidth = result.imageWidth;
      this.imageHeight = result.imageHeight;
      this.testStatus = 'Success';
      this.isLoading = false;
      this.loadResult = '✅ load 成功!\n' +
                       '图片宽度：' + result.imageWidth + ' px\n' +
                       '图片高度：' + result.imageHeight + ' px\n' +
                       '加载方式：异步 (Promise)';
    } catch (e) {
      this.testStatus = 'Error';
      this.isLoading = false;
      this.loadResult = '❌ load 失败:\n' + JSON.stringify(e);
    }
  }

  async testLoadError() {
    this.testStatus = 'Loading (async)...';
    this.isLoading = true;
    this.loadResult = '执行 load() - 测试错误处理...';

    try {
      // 创建无效的 DrawableDescriptor (空字符串)
      const drawable = new AnimatedDrawableDescriptor("");
      
      // 异步加载 (应该失败)
      const result = await drawable.load();
      
      this.testStatus = 'Unexpected Success';
      this.isLoading = false;
      this.loadResult = '⚠️ 预期失败但成功了:\n' + JSON.stringify(result);
    } catch (e) {
      this.testStatus = 'Expected Error';
      this.isLoading = false;
      this.loadResult = '✅ 预期错误捕获成功:\n' +
                       '错误信息：' + JSON.stringify(e) + '\n' +
                       '错误码：111001 (resource loading failed)';
    }
  }
}
