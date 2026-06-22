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
 * 相对路径加载图片示例 (对齐官方示例 25)
 * ========================================
 * 功能说明:
 * 本示例演示如何使用相对路径加载图片资源。
 * 相对路径以工程目录为根，常用于加载 common 目录等非 resource 目录下的图片。
 *
 * 涉及的 Image API:
 * 1. Image('common/xxx.png') - 使用相对路径字符串
 * 2. Image($r('app.media.xxx')) - 推荐的资源引用方式（对比）
 * 3. Image($rawfile('xxx.png')) - rawfile 引用方式（对比）
 *
 * ========================================
 * 使用场景
 * ========================================
 * - 项目中有 common 目录统一存放图片
 * - 需要在 string 中拼接图片路径
 * - 临时调试或快速展示
 *
 * ========================================
 * 注意事项
 * ========================================
 * 1. 相对路径不支持跨包/跨模块访问
 * 2. 从 DevEco Studio 6.0.0 Beta2 开始，需要显式开启
 *    buildOption.resOptions.copyCodeResource.enable = true
 * 3. 推荐使用 Resource 格式 ($r/$rawfile) 来管理图片资源
 * 4. ArkTS 卡片不支持相对路径
 */

@Entry
@Component
struct ImageRelativePathExample {
  @State useAbsolutePath: boolean = false;
  @State currentSize: number = 120;
  @State objectFit: ImageFit = ImageFit.Cover;
  @State showBorder: boolean = true;

  // 不同资源引用方式列表
  private sourceModes: Array<ResourceMode> = [
    { name: 'Resource 引用', desc: '$r("app.media.xxx") - 推荐', mode: 'resource' },
    { name: 'rawfile 引用', desc: '$rawfile("xxx.png")', mode: 'rawfile' },
    { name: '相对路径', desc: '"common/xxx.png" - 不跨包', mode: 'relative' }
  ];

  build(): void {
    Scroll() {
      Column({ space: 16 }) {
        Text('相对路径加载图片示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 8 })

        Text('对齐官方文档示例 25 · 多种资源引用方式对比')
          .fontSize(12)
          .fontColor(Color.Gray)
          .margin({ bottom: 8 })

        // 三种资源加载方式对比
        Column({ space: 14 }) {
          Text('三种资源加载方式对比')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          ForEach(
            this.sourceModes,
            (item: ResourceMode) => {
              this.SourceCard(item)
            },
            (item: ResourceMode) => item.mode
          )
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFFFFF')
        .borderRadius(16)

        // 尺寸控制
        Column({ space: 12 }) {
          Text('通用尺寸调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Row({ space: 8 }) {
            Text('尺寸')
              .fontSize(12)
              .width(50)
            Slider(value: this.currentSize, min: 60, max: 240, step: 10)
              .layoutWeight(1)
              .onChange((value: number) => {
                this.currentSize = value;
              })
            Text(`${this.currentSize}`)
              .fontSize(12)
              .width(40)
          }
          .width('100%')

          Row({ space: 12 }) {
            Toggle({ type: ToggleType.Switch, isOn: this.showBorder })
              .onChange((on: boolean) => {
                this.showBorder = on;
              })
            Text('显示边框')
              .fontSize(13)
              .fontColor(Color.Black)
          }
          .width('100%')

          Row({ space: 8 }) {
            ForEach(
              [ImageFit.Cover, ImageFit.Contain, ImageFit.Fill, ImageFit.ScaleDown],
              (fit: ImageFit) => {
                Button(this.fitName(fit))
                  .fontSize(11)
                  .backgroundColor(this.objectFit === fit ? '#007DFF' : '#E0E0E0')
                  .fontColor(this.objectFit === fit ? Color.White : Color.Black)
                  .height(30)
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

        // 最佳实践
        Column({ space: 10 }) {
          Text('最佳实践')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          this.PracticeItem('推荐', '使用 $r 引用资源，支持跨包访问', '#32CD32')
          this.PracticeItem('次选', '使用 $rawfile 引用 rawfile 目录资源', '#FFA500')
          this.PracticeItem('谨慎', '相对路径不支持跨包，需手动开启打包开关', '#FF6347')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#FFF8DC')
        .borderRadius(16)

        // 配置开关
        Column({ space: 10 }) {
          Text('build-profile.json5 配置')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)
            .width('100%')

          Text('// 模块的 build-profile.json5\n'
            + '{\n'
            + '  "buildOption": {\n'
            + '    "resOptions": {\n'
            + '      "copyCodeResource": {\n'
            + '        "enable": true\n'
            + '      }\n'
            + '    }\n'
            + '  }\n'
            + '}')
            .fontSize(11)
            .fontFamily('monospace')
            .fontColor('#333333')
            .backgroundColor('#F5F5F5')
            .borderRadius(8)
            .padding(10)
            .width('100%')
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#E6F7FF')
        .borderRadius(16)

        Text('提示：相对路径适合临时调试，生产环境推荐使用 $r/$rawfile')
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
  SourceCard(mode: ResourceMode): void {
    Column({ space: 8 }) {
      Row({ space: 8 }) {
        Circle({ width: 8, height: 8 })
          .fill(this.modeColor(mode.mode))
        Text(mode.name)
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .fontColor(Color.Black)
        Text(mode.desc)
          .fontSize(11)
          .fontColor(Color.Gray)
          .layoutWeight(1)
      }
      .width('100%')

      Row({ space: 12 }) {
        // 实际加载图片
        this.LoadImageByMode(mode.mode)
          .width(this.currentSize)
          .height(this.currentSize)
          .objectFit(this.objectFit)
          .borderRadius(8)
          .border(this.showBorder ? { width: 1, color: '#E0E0E0' } : { width: 0 })

        // 代码片段
        Column({ space: 4 }) {
          Text(this.codeSnippet(mode.mode))
            .fontSize(11)
            .fontFamily('monospace')
            .fontColor('#007DFF')
            .backgroundColor('#F8F8FF')
            .borderRadius(4)
            .padding(6)
            .width('100%')
        }
        .layoutWeight(1)
        .alignItems(HorizontalAlign.Start)
      }
      .width('100%')
      .alignItems(VerticalAlign.Top)
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FAFAFA')
    .borderRadius(12)
  }

  @Builder
  LoadImageByMode(mode: string): void {
    if (mode === 'resource') {
      Image($r('app.media.startIcon'))
    } else if (mode === 'rawfile') {
      Image($rawfile('startIcon.png'))
    } else {
      // 相对路径：注意需在工程 pages 同级创建 common 目录并放置图片
      // 此处为示例写法，实际运行需要资源文件存在
      Image('common/startIcon.png')
        .alt($r('app.media.startIcon'))
    }
  }

  @Builder
  PracticeItem(tag: string, text: string, color: ResourceColor): void {
    Row({ space: 8 }) {
      Text(tag)
        .fontSize(11)
        .fontColor(Color.White)
        .backgroundColor(color)
        .borderRadius(4)
        .padding({ left: 6, right: 6, top: 2, bottom: 2 })
        .width(40)
        .textAlign(TextAlign.Center)
      Text(text)
        .fontSize(12)
        .fontColor(Color.Black)
        .layoutWeight(1)
    }
    .width('100%')
    .padding(6)
    .backgroundColor('#FFFFFF')
    .borderRadius(6)
  }

  private modeColor(mode: string): ResourceColor {
    switch (mode) {
      case 'resource':
        return '#32CD32';
      case 'rawfile':
        return '#FFA500';
      case 'relative':
        return '#FF6347';
      default:
        return '#888888';
    }
  }

  private codeSnippet(mode: string): string {
    switch (mode) {
      case 'resource':
        return "Image($r('app.media.startIcon'))";
      case 'rawfile':
        return "Image($rawfile('startIcon.png'))";
      case 'relative':
        return "Image('common/startIcon.png')";
      default:
        return '';
    }
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

interface ResourceMode {
  name: string;
  desc: string;
  mode: string;
}
