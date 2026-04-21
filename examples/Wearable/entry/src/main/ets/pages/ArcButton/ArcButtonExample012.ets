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
 * ArcButton事件测试示例 - 测试ArcButton的点击和触摸事件
 * 包括onClick、onTouch事件，以及各种事件属性的展示
 */
import {
  LengthMetrics,
  LengthUnit,
  ArcButton,
  ArcButtonOptions,
  ArcButtonStatus,
  ArcButtonStyleMode,
  ArcButtonPosition,
  ColorMetrics
} from '@kit.ArkUI';

@Entry
@ComponentV2
struct ArcButtonExample012 {
  // 事件日志
  @Local eventLogs: string[] = [];
  @Local maxLogs: number = 10;

  // 点击计数器
  @Local clickCount: number = 0;
  @Local touchCount: number = 0;

  // 事件统计
  @Local downCount: number = 0;
  @Local upCount: number = 0;
  @Local moveCount: number = 0;
  @Local cancelCount: number = 0;

  // 点击事件数据
  @Local lastClickX: number = 0;
  @Local lastClickY: number = 0;
  @Local lastClickWindowX: number = 0;
  @Local lastClickWindowY: number = 0;
  @Local lastClickDisplayX: number = 0;
  @Local lastClickDisplayY: number = 0;

  // 触摸事件数据
  @Local lastTouchType: string = '';
  @Local lastTouchTypeStr: string = '无';
  @Local multiTouchEnabled: boolean = false;

  // ArcButton配置
  @Local basicClickOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local basicTouchOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local combinedEventsOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local clickDetailOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local touchDetailOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local multiTouchOptions: ArcButtonOptions = new ArcButtonOptions({});

  aboutToAppear() {
    this.initBasicClickButton();
    this.initBasicTouchButton();
    this.initCombinedEventsButton();
    this.initClickDetailButton();
    this.initTouchDetailButton();
    this.initMultiTouchButton();
  }

  // 添加事件日志
  addEventLog(message: string) {
    const timestamp = new Date().toLocaleTimeString();
    this.eventLogs.unshift(`[${timestamp}] ${message}`);
    if (this.eventLogs.length > this.maxLogs) {
      this.eventLogs = this.eventLogs.slice(0, this.maxLogs);
    }
  }

  // 清除日志
  clearLogs() {
    this.eventLogs = [];
    this.clickCount = 0;
    this.touchCount = 0;
    this.downCount = 0;
    this.upCount = 0;
    this.moveCount = 0;
    this.cancelCount = 0;
    this.lastClickX = 0;
    this.lastClickY = 0;
    this.lastClickWindowX = 0;
    this.lastClickWindowY = 0;
    this.lastClickDisplayX = 0;
    this.lastClickDisplayY = 0;
    this.lastTouchType = '';
    this.lastTouchTypeStr = '无';
  }

  // 初始化基础点击按钮
  initBasicClickButton() {
    this.basicClickOptions = new ArcButtonOptions({
      label: '点击测试',
      styleMode: ArcButtonStyleMode.EMPHASIZED_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      onClick: (event: ClickEvent) => {
        this.clickCount++;
        this.lastClickX = event.x;
        this.lastClickY = event.y;
        this.lastClickWindowX = event.windowX || 0;
        this.lastClickWindowY = event.windowY || 0;
        this.lastClickDisplayX = event.displayX || 0;
        this.lastClickDisplayY = event.displayY || 0;
        this.addEventLog(`onClick触发 - 点击次数: ${this.clickCount}, 位置: (${event.x.toFixed(1)}, ${event.y.toFixed(1)})`);
      }
    });
  }

  // 初始化基础触摸按钮
  initBasicTouchButton() {
    this.basicTouchOptions = new ArcButtonOptions({
      label: '触摸测试',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      onTouch: (event: TouchEvent) => {
        this.touchCount++;
        const touchTypeStr = this.getTouchTypeString(event.type);
        this.lastTouchTypeStr = touchTypeStr;

        switch (event.type) {
          case TouchType.Down:
            this.downCount++;
            this.addEventLog(`onTouch.Down - 手指按下, 触摸点数: ${event.touches.length}`);
            break;
          case TouchType.Up:
            this.upCount++;
            this.addEventLog(`onTouch.Up - 手指抬起, 触摸点数: ${event.touches.length}`);
            break;
          case TouchType.Move:
            this.moveCount++;
            // 限制Move事件的日志数量，避免刷屏
            if (this.moveCount % 5 === 0) {
              this.addEventLog(`onTouch.Move - 手指移动, 触摸点数: ${event.touches.length}`);
            }
            break;
          case TouchType.Cancel:
            this.cancelCount++;
            this.addEventLog(`onTouch.Cancel - 触摸取消`);
            break;
        }
      }
    });
  }

  // 初始化组合事件按钮
  initCombinedEventsButton() {
    const customBgColor: ColorMetrics = ColorMetrics.resourceColor('#FF9C27B0');
    const customFontColor: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');

    this.combinedEventsOptions = new ArcButtonOptions({
      label: '组合事件',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: customBgColor,
      fontColor: customFontColor,
      onClick: (event: ClickEvent) => {
        this.clickCount++;
        this.addEventLog(`组合onClick - 总点击: ${this.clickCount}, 位置: (${event.x.toFixed(1)}, ${event.y.toFixed(1)})`);
      },
      onTouch: (event: TouchEvent) => {
        const touchTypeStr = this.getTouchTypeString(event.type);
        if (event.type === TouchType.Down || event.type === TouchType.Up) {
          this.addEventLog(`组合onTouch.${touchTypeStr} - 触摸点数: ${event.touches.length}`);
        }
      }
    });
  }

  // 初始化点击详情按钮
  initClickDetailButton() {
    this.clickDetailOptions = new ArcButtonOptions({
      label: '点击详情',
      styleMode: ArcButtonStyleMode.EMPHASIZED_DARK,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      shadowEnabled: true,
      onClick: (event: ClickEvent) => {
        this.clickCount++;
        this.lastClickX = event.x;
        this.lastClickY = event.y;
        this.lastClickWindowX = event.windowX || 0;
        this.lastClickWindowY = event.windowY || 0;
        this.lastClickDisplayX = event.displayX || 0;
        this.lastClickDisplayY = event.displayY || 0;

        const detail = `Click详情 #${this.clickCount}:
- 组件坐标: (${event.x.toFixed(1)}, ${event.y.toFixed(1)}) vp
- 窗口坐标: (${(event.windowX || 0).toFixed(1)}, ${(event.windowY || 0).toFixed(1)}) vp
- 屏幕坐标: (${(event.displayX || 0).toFixed(1)}, ${(event.displayY || 0).toFixed(1)}) vp`;
        this.addEventLog(detail);
      }
    });
  }

  // 初始化触摸详情按钮
  initTouchDetailButton() {
    this.touchDetailOptions = new ArcButtonOptions({
      label: '触摸详情',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      shadowEnabled: true,
      onTouch: (event: TouchEvent) => {
        if (event.type === TouchType.Up && event.touches.length > 0) {
          const touch = event.touches[0];
          const detail = `Touch详情:
- 触摸类型: ${this.getTouchTypeString(event.type)}
- 触摸点数: ${event.touches.length}
- 第1点ID: ${touch.id}
- 第1点坐标: (${touch.x.toFixed(1)}, ${touch.y.toFixed(1)}) vp`;
          this.addEventLog(detail);
        }
      }
    });
  }

  // 初始化多点触摸按钮
  initMultiTouchButton() {
    const customBgColor: ColorMetrics = ColorMetrics.resourceColor('#FF009688');
    const customFontColor: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');

    this.multiTouchOptions = new ArcButtonOptions({
      label: '多点触摸',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: customBgColor,
      fontColor: customFontColor,
      onTouch: (event: TouchEvent) => {
        if (event.type === TouchType.Down || event.type === TouchType.Up) {
          const touchCount:number = event.touches.length;
          const changedCount:number = event.changedTouches.length;

          let detail = `多指触摸 [${this.getTouchTypeString(event.type)}]:
- 总触摸点: ${touchCount}
- 变化触摸点: ${changedCount}`;

          if (touchCount > 1) {
            detail += '\n- 触摸点详情:';
            for (let i = 0; i < Math.min(touchCount, 3); i++) {
              const touch = event.touches[i];
              detail += `\n  点${i + 1}: ID=${touch.id}, (${touch.x.toFixed(1)}, ${touch.y.toFixed(1)})`;
            }
          }

          this.addEventLog(detail);
        }
      }
    });
  }

  // 获取触摸类型字符串
  getTouchTypeString(type: TouchType): string {
    switch (type) {
      case TouchType.Down:
        return 'Down';
      case TouchType.Up:
        return 'Up';
      case TouchType.Move:
        return 'Move';
      case TouchType.Cancel:
        return 'Cancel';
      default:
        return 'Unknown';
    }
  }

  // 创建单个测试项的Builder
  @Builder
  TestItem(title: string, options: ArcButtonOptions, desc?: string) {
    Column() {
      Stack() {
        Circle({ width: 140, height: 140 })
          .strokeWidth(0.1)
          .fill(Color.White)

        Column() {
          Blank()
          ArcButton({ options: options })
        }
        .width('100%')
        .height('100%')
      }
      .width(140)
      .height(140)

      Text(title)
        .fontSize(12)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 5 })

      if (desc) {
        Text(desc)
          .fontSize(10)
          .fontColor('#666666')
          .margin({ top: 2 })
      }
    }
    .margin({ right: 10, bottom: 10 })
    .alignItems(HorizontalAlign.Center)
  }

  // 创建标题区域
  @Builder
  TitleSection(title: string, description?: string) {
    Column() {
      Text(title)
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 8 })

      if (description) {
        Text(description)
          .fontSize(13)
          .fontColor('#666666')
          .margin({ bottom: 5 })
      }
    }
    .width('100%')
    .padding({ left: 15, right: 15 })
    .margin({ bottom: 15 })
  }

  build() {
    Scroll() {
      Column() {
        // 页面标题
        Column() {
          Text('ArcButton 事件测试')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          Text('测试ArcButton的onClick和onTouch事件，展示各种事件属性和统计')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 20 })
        }
        .width('100%')
        .padding({ left: 15, right: 15 })

        // 事件统计面板
        Column() {
          Text('事件统计')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Row() {
            Text('点击次数: ')
              .fontSize(14)
            Text(this.clickCount.toString())
              .fontSize(14)
              .fontColor('#FF6200EE')
              .fontWeight(FontWeight.Bold)
              .margin({ right: 20 })

            Text('触摸次数: ')
              .fontSize(14)
            Text(this.touchCount.toString())
              .fontSize(14)
              .fontColor('#FF6200EE')
              .fontWeight(FontWeight.Bold)
          }
          .margin({ bottom: 8 })

          Row() {
            Text('Down: ')
              .fontSize(13)
            Text(this.downCount.toString())
              .fontSize(13)
              .fontColor('#FF9800')
              .margin({ right: 15 })

            Text('Up: ')
              .fontSize(13)
            Text(this.upCount.toString())
              .fontSize(13)
              .fontColor('#4CAF50')
              .margin({ right: 15 })

            Text('Move: ')
              .fontSize(13)
            Text(this.moveCount.toString())
              .fontSize(13)
              .fontColor('#2196F3')
              .margin({ right: 15 })

            Text('Cancel: ')
              .fontSize(13)
            Text(this.cancelCount.toString())
              .fontSize(13)
              .fontColor('#F44336')
          }
          .margin({ bottom: 8 })

          // 清除按钮
          Button('清除统计')
            .fontSize(12)
            .width(120)
            .height(35)
            .backgroundColor('#F5F5F5')
            .onClick(() => {
              this.clearLogs();
            })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#F0F0F0')
        .borderRadius(10)
        .margin({ left: 15, right: 15, bottom: 20 })

        // 基础事件测试
        this.TitleSection('基础事件测试', '测试基本的onClick和onTouch事件')

        Row() {
          this.TestItem('onClick', this.basicClickOptions, '点击触发')
          this.TestItem('onTouch', this.basicTouchOptions, '触摸触发')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 组合事件测试
        this.TitleSection('组合事件测试', '同时响应onClick和onTouch事件')

        Row() {
          this.TestItem('组合事件', this.combinedEventsOptions, '双事件监听')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 事件详情测试
        this.TitleSection('事件详情测试', '展示ClickEvent和TouchEvent的详细属性')

        Row() {
          this.TestItem('Click详情', this.clickDetailOptions, '坐标信息')
          this.TestItem('Touch详情', this.touchDetailOptions, '触摸点信息')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 多点触摸测试
        this.TitleSection('多点触摸测试', '测试多指触摸事件，观察touches数组')

        Row() {
          this.TestItem('多点触摸', this.multiTouchOptions, '多指支持')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 事件日志区域
        Column() {
          Row() {
            Text('事件日志')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .margin({ right: 15 })

            Text(`(最近${this.maxLogs}条)`)
              .fontSize(13)
              .fontColor('#666666')
          }
          .margin({ bottom: 10 })

          if (this.eventLogs.length === 0) {
            Text('暂无事件日志，请点击或触摸上方的按钮')
              .fontSize(13)
              .fontColor('#999999')
              .margin({ top: 20, bottom: 20 })
          } else {
            List({ space: 5 }) {
              ForEach(this.eventLogs, (log: string, index: number) => {
                ListItem() {
                  Text(log)
                    .fontSize(11)
                    .fontColor(index % 2 === 0 ? '#333333' : '#555555')
                    .padding({ left: 10, right: 10, top: 5, bottom: 5 })
                    .backgroundColor(index % 2 === 0 ? '#FFFFFF' : '#F9F9F9')
                    .borderRadius(5)
                    .width('100%')
                }
              })
            }
            .width('100%')
            .height(200)
            .padding({ left: 5, right: 5 })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#FAFAFA')
        .borderRadius(10)
        .margin({ left: 15, right: 15, bottom: 30 })

        // 使用说明
        Column() {
          Text('使用说明')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('1. onClick事件在手指点击按钮并抬起时触发')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('2. onTouch事件在整个触摸过程中触发（Down/Up/Move/Cancel）')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('3. ClickEvent提供坐标信息：组件坐标、窗口坐标、屏幕坐标')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('4. TouchEvent提供触摸点信息：类型、触摸点数组、变化点数组')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('5. 多点触摸时，touches数组包含所有触摸点信息')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('6. 可以同时监听onClick和onTouch，两者都会响应')
            .fontSize(13)
            .margin({ bottom: 5 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#E3F2FD')
        .borderRadius(10)
        .margin({ left: 15, right: 15, bottom: 30 })
      }
      .width('100%')
      .backgroundColor('#F5F5F5')
    }
    .width('100%')
    .height('100%')
    .scrollBar(BarState.Off)
    .edgeEffect(EdgeEffect.Spring)
  }
}
