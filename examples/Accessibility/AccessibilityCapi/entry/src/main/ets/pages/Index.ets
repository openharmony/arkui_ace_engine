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

import nativerender from 'libentry.so';

/**
 * Native C-API 无障碍示例 - 主页
 *
 * 说明：
 * - 本示例使用 C++ 模拟节点（AccessibleObject）来演示 Native C-API 接口
 * - 主页展示所有可用的无障碍场景
 * - 点击场景按钮通过 NavDestination 导航到对应场景页面
 * - 所有场景通过 fillAccessibilityElement() 调用 Native C-API 接口
 */

// 场景路由前缀
export const SCENARIO_ROUTE_PREFIX: string = 'Scenario';

// 场景信息定义
interface ScenarioInfo {
  id: string;
  name: string;
  description: string;
  icon: string;
  color: string;
}

interface ScenarioData {
  id: string;
  name: string;
  description: string;
  interfaceCount: number;
  testCaseCount: number;
}

interface ScenarioRoute {
  name: string;
  title: string;
  description: string;
  icon: string;
  color: string;
}

@Entry
@Component
struct Index {
  @State scenarios: ScenarioRoute[] = [];
  @State loadedScenarios: ScenarioData[] = [];
  @Provide pathStack: NavPathStack = new NavPathStack();

  aboutToAppear() {
    console.info('Index: aboutToAppear called');
    // 加载可用场景列表
    this.loadScenarios();
  }

  /**
   * 从C++加载可用场景列表
   */
  loadScenarios(): void {
    try {
      console.info('Index: Start loading scenarios from C++');
      const scenarios: ScenarioData[] = nativerender.scenarioManager.getAvailableScenarios();
      this.loadedScenarios = scenarios;
      console.info(`Index: Loaded ${scenarios.length} scenarios from C++`);

      // 定义场景显示信息
      const scenarioDisplay: Record<string, ScenarioInfo> = {
        'scenario1_login': {
          id: 'scenario1_login',
          name: '登录页面',
          description: '演示基础属性和状态设置接口（19个接口）',
          icon: '🔑',
          color: '#007DFF'
        },
        'scenario2_audio': {
          id: 'scenario2_audio',
          name: '音频播放器',
          description: '演示范围信息和位置信息接口（12个接口）',
          icon: '🎵',
          color: '#FF6B00'
        },
        'scenario3_news': {
          id: 'scenario3_news',
          name: '新闻列表',
          description: '演示网格和列表接口（11个接口）',
          icon: '📰',
          color: '#00BF00'
        },
        'scenario7_settings': {
          id: 'scenario7_settings',
          name: '设置页面',
          description: '演示事件管理和高级状态接口（14个接口）',
          icon: '⚙️',
          color: '#8A2BE2'
        }
      };

      // 如果C++返回空，使用默认场景列表
      if (this.loadedScenarios.length === 0) {
        console.warn('Index: No scenarios loaded from C++, using default list');
        const defaultScenarios: ScenarioData[] = [
          { id: 'scenario1_login', name: '登录页面', description: '演示基础属性和状态设置接口', interfaceCount: 19, testCaseCount: 7 },
          { id: 'scenario2_audio', name: '音频播放器', description: '演示范围信息和位置信息接口', interfaceCount: 12, testCaseCount: 7 },
          { id: 'scenario3_news', name: '新闻列表', description: '演示网格和列表接口', interfaceCount: 11, testCaseCount: 7 },
          { id: 'scenario7_settings', name: '设置页面', description: '演示事件管理和高级状态接口', interfaceCount: 14, testCaseCount: 7 }
        ];
        this.loadedScenarios = defaultScenarios;
      }

      // 构建场景路由列表
      this.scenarios = this.loadedScenarios.map((s: ScenarioData): ScenarioRoute => {
        const displayInfo = scenarioDisplay[s.id] || {
          id: s.id,
          name: s.name,
          description: s.description,
          icon: '📱',
          color: '#666666'
        };
        return {
          name: `${SCENARIO_ROUTE_PREFIX}/${displayInfo.id}`,
          title: displayInfo.name,
          description: displayInfo.description,
          icon: displayInfo.icon,
          color: displayInfo.color
        };
      });

      console.info(`Index: Final scenario count: ${this.scenarios.length}`);
      this.scenarios.forEach((s: ScenarioRoute, index: number) => {
        console.info(`Index: Scenario ${index}: ${s.name} - ${s.title}`);
      });
    } catch (error) {
      console.error('Index: Failed to load scenarios:', JSON.stringify(error));
      // 使用默认场景列表作为降级方案
      this.scenarios = [
        {
          name: 'Scenario/scenario1_login',
          title: '登录页面',
          description: '演示基础属性和状态设置接口（19个接口）',
          icon: '🔑',
          color: '#007DFF'
        },
        {
          name: 'Scenario/scenario2_audio',
          title: '音频播放器',
          description: '演示范围信息和位置信息接口（12个接口）',
          icon: '🎵',
          color: '#FF6B00'
        },
        {
          name: 'Scenario/scenario3_news',
          title: '新闻列表',
          description: '演示网格和列表接口（11个接口）',
          icon: '📰',
          color: '#00BF00'
        },
        {
          name: 'Scenario/scenario7_settings',
          title: '设置页面',
          description: '演示事件管理和高级状态接口（14个接口）',
          icon: '⚙️',
          color: '#8A2BE2'
        }
      ];
      this.loadedScenarios = [
        { id: 'scenario1_login', name: '登录页面', description: '演示基础属性和状态设置接口', interfaceCount: 19, testCaseCount: 7 },
        { id: 'scenario2_audio', name: '音频播放器', description: '演示范围信息和位置信息接口', interfaceCount: 12, testCaseCount: 7 },
        { id: 'scenario3_news', name: '新闻列表', description: '演示网格和列表接口', interfaceCount: 11, testCaseCount: 7 },
        { id: 'scenario7_settings', name: '设置页面', description: '演示事件管理和高级状态接口', interfaceCount: 14, testCaseCount: 7 }
      ];
    }
  }

  /**
   * 导航到场景页面
   */
  navigateToScenario(routeName: string): void {
    this.pathStack.pushPath({ name: routeName });
  }

  @LocalBuilder
  Title() {
    Column() {
      Text('Native C-API 无障碍示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182431')
    }
    .justifyContent(FlexAlign.Center)
    .height('100%')
  }

  build() {
    Navigation(this.pathStack) {
      Column() {
        // 统计信息卡片
        if (this.scenarios.length > 0) {
          Row() {
            Column() {
              Text(this.scenarios.length.toString())
                .fontSize(28)
                .fontWeight(FontWeight.Bold)
                .fontColor('#007DFF')
              Text('场景总数')
                .fontSize(12)
                .fontColor('#666666')
                .margin({ top: 4 })
            }
            .layoutWeight(1)
            .alignItems(HorizontalAlign.Center)

            Line()
              .width(1)
              .height(40)
              .backgroundColor('#e0e0e0')

            Column() {
              Text(this.getTotalInterfaceCount().toString())
                .fontSize(28)
                .fontWeight(FontWeight.Bold)
                .fontColor('#00BF00')
              Text('接口覆盖')
                .fontSize(12)
                .fontColor('#666666')
                .margin({ top: 4 })
            }
            .layoutWeight(1)
            .alignItems(HorizontalAlign.Center)

            Line()
              .width(1)
              .height(40)
              .backgroundColor('#e0e0e0')

            Column() {
              Text(this.getTotalTestCaseCount().toString())
                .fontSize(28)
                .fontWeight(FontWeight.Bold)
                .fontColor('#FF6B00')
              Text('测试用例')
                .fontSize(12)
                .fontColor('#666666')
                .margin({ top: 4 })
            }
            .layoutWeight(1)
            .alignItems(HorizontalAlign.Center)
          }
          .width('100%')
          .padding({ left: 20, right: 20, top: 16, bottom: 16 })
          .backgroundColor('#F9F9F9')
        } else {
          // 加载失败提示
          Column() {
            Text('正在加载场景...')
              .fontSize(16)
              .fontColor('#666666')
            Text('如果长时间未加载，请检查C++初始化')
              .fontSize(12)
              .fontColor('#999999')
              .margin({ top: 8 })
          }
          .width('100%')
          .padding(40)
        }

          // 场景列表
          Column() {
            Text('选择场景')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .fontColor('#182431')
              .alignSelf(ItemAlign.Start)
              .margin({ bottom: 16 })

            ForEach(this.scenarios, (scenario: ScenarioRoute) => {
              Column() {
                Row() {
                  Text(scenario.icon)
                    .fontSize(32)

                  Column() {
                    Text(scenario.title)
                      .fontSize(16)
                      .fontWeight(FontWeight.Medium)
                      .fontColor('#182431')
                    Text(scenario.description)
                      .fontSize(12)
                      .fontColor('#666666')
                      .margin({ top: 4 })
                  }
                  .alignItems(HorizontalAlign.Start)
                  .layoutWeight(1)
                  .margin({ left: 12 })

                  Text('查看 >')
                    .fontSize(14)
                    .fontColor('#007DFF')
                }
                .width('100%')
                .padding(16)
                .backgroundColor('#ffffff')
                .borderRadius(8)
                .shadow({
                  radius: 8,
                  color: '#1F000000',
                  offsetX: 0,
                  offsetY: 2
                })
                .onClick(() => {
                  this.navigateToScenario(scenario.name);
                })
              }
              .margin({ bottom: 12 })
            })
          }
          .layoutWeight(1)
          .width('100%')
          .padding({ left: 20, right: 20, top: 8 })
          .alignItems(HorizontalAlign.Center)

          // 底部说明
          Column() {
            Text('说明')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .fontColor('#333333')
              .alignSelf(ItemAlign.Start)
              .margin({ bottom: 8 })

            Text('• 本示例使用 C++ 模拟节点（AccessibleObject）演示 Native C-API 接口')
              .fontSize(12)
              .fontColor('#666666')
              .width('100%')

            Text('• 点击场景卡片可查看对应的无障碍节点和接口覆盖情况')
              .fontSize(12)
              .fontColor('#666666')
              .width('100%')

            Text('• 所有接口调用通过 fillAccessibilityElement() 完成')
              .fontSize(12)
              .fontColor('#666666')
              .width('100%')
          }
          .width('100%')
          .padding({ left: 20, right: 20, top: 8, bottom: 20 })
          .alignItems(HorizontalAlign.Start)
          .backgroundColor('#F5F5F5')
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#F1F3F5')
    }
    .backgroundColor('#F1F3F5')
    .title({ builder: this.Title, height: 56 }, {
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      barStyle: BarStyle.STACK
    })
    .navDestination(ScenarioDestinationBuilder)
  }

  /**
   * 计算总接口数
   */
  getTotalInterfaceCount(): number {
    return this.loadedScenarios.reduce((sum: number, s: ScenarioData): number => sum + (s.interfaceCount || 0), 0);
  }

  /**
   * 计算总测试用例数
   */
  getTotalTestCaseCount(): number {
    return this.loadedScenarios.reduce((sum: number, s: ScenarioData): number => sum + (s.testCaseCount || 0), 0);
  }
}

/**
 * 场景页面构建器
 * 根据路由名称匹配并渲染对应的场景页面
 */
@Builder
function ScenarioDestinationBuilder(name: string) {
  if (name.startsWith(SCENARIO_ROUTE_PREFIX)) {
    ScenarioPage({ routeName: name });
  }
}

/**
 * 场景页面组件
 * 通用场景页面，支持所有场景
 */
@Component
export struct ScenarioPage {
  @Consume pathStack: NavPathStack;
  @Prop routeName: string;
  @State scenarioId: string = '';
  @State scenarioName: string = '';
  @State scenarioDescription: string = '';
  @State interfaceCount: number = 0;
  @State testCaseCount: number = 0;
  @State xComponentId: string = '';

  aboutToAppear() {
    // 从路由名称解析场景信息
    const parts = this.routeName.split('/');
    if (parts.length >= 2) {
      this.scenarioId = parts[1];
    }

    // 加载场景详细信息
    this.loadScenarioInfo();
    this.xComponentId = 'xcomponent_' + this.scenarioId;

    console.info(`ScenarioPage: Loading scenario ${this.scenarioId}`);
  }

  /**
   * 加载场景信息
   */
  loadScenarioInfo(): void {
    try {
      const scenarios: ScenarioData[] = nativerender.scenarioManager.getAvailableScenarios();
      const scenario = scenarios.find((s: ScenarioData) => s.id === this.scenarioId);

      if (scenario) {
        this.scenarioName = scenario.name;
        this.scenarioDescription = scenario.description;
        this.interfaceCount = scenario.interfaceCount;
        this.testCaseCount = scenario.testCaseCount;
      }

      // 设置场景显示名称
      const scenarioDisplay: Record<string, ScenarioInfo> = {
        'scenario1_login': {
          id: 'scenario1_login',
          name: '登录页面',
          description: '演示基础属性和状态设置接口（19个接口）',
          icon: '🔑',
          color: '#007DFF'
        },
        'scenario2_audio': {
          id: 'scenario2_audio',
          name: '音频播放器',
          description: '演示范围信息和位置信息接口（12个接口）',
          icon: '🎵',
          color: '#FF6B00'
        },
        'scenario3_news': {
          id: 'scenario3_news',
          name: '新闻列表',
          description: '演示网格和列表接口（11个接口）',
          icon: '📰',
          color: '#00BF00'
        },
        'scenario7_settings': {
          id: 'scenario7_settings',
          name: '设置页面',
          description: '演示事件管理和高级状态接口（14个接口）',
          icon: '⚙️',
          color: '#8A2BE2'
        }
      };

      const displayInfo = scenarioDisplay[this.scenarioId];
      if (displayInfo) {
        this.scenarioName = displayInfo.name;
        this.scenarioDescription = displayInfo.description;
      }
    } catch (error) {
      console.error('Failed to load scenario info:', JSON.stringify(error));
    }
  }

  /**
   * 切换到当前场景
   */
  switchToCurrentScenario(): void {
    try {
      nativerender.scenarioManager.switchScenario(this.xComponentId, this.scenarioId);
      console.info(`Switched to scenario: ${this.scenarioId}`);
    } catch (error) {
      console.error('Failed to switch scenario:', JSON.stringify(error));
    }
  }

  build() {
    NavDestination() {
      Column() {
        // 场景信息卡片
        Column() {
          Text(this.scenarioName)
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor('#182431')
            .margin({ bottom: 8 })

          if (this.scenarioDescription) {
            Text(this.scenarioDescription)
              .fontSize(14)
              .fontColor('#666666')
              .margin({ bottom: 12 })
          }

          Row() {
            Text('接口数量: ')
              .fontSize(14)
              .fontColor('#666666')
            Text(this.interfaceCount.toString())
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .fontColor('#007DFF')

            Blank()
              .layoutWeight(1)

            Text('测试用例: ')
              .fontSize(14)
              .fontColor('#666666')
            Text(this.testCaseCount.toString())
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .fontColor('#007DFF')
          }
          .width('100%')

          Text('场景ID: ' + this.scenarioId)
            .fontSize(12)
            .fontColor('#999999')
            .margin({ top: 8 })
        }
        .width('100%')
        .padding(16)
        .backgroundColor('#F0F7FF')
        .borderRadius(8)
        .margin({ left: 16, right: 16, top: 16 })

        // XComponent 容器
        Column() {
          Text('无障碍节点展示区域')
            .fontSize(14)
            .fontColor('#999999')
            .margin({ bottom: 8 })
            .textAlign(TextAlign.Center)

          XComponent({
            id: this.xComponentId,
            type: 'surface',
            libraryname: 'nativerender'
          })
            .onLoad((event: Object) => {
              console.info(`XComponent onLoad for ${this.scenarioId}:`, JSON.stringify(event));
              // XComponent 加载完成后，切换到当前场景
              this.switchToCurrentScenario();
            })
            .onDestroy(() => {
              console.info(`XComponent onDestroy for ${this.scenarioId}`);
            })
            .width('100%')
            .height('100%')
            .backgroundColor('#FAFAFA')
            .borderRadius(8)
        }
        .layoutWeight(1)
        .width('100%')
        .padding({ left: 16, right: 16, top: 8, bottom: 8 })

        // 底部说明
        Column() {
          Text('说明')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor('#333333')
            .alignSelf(ItemAlign.Start)
            .margin({ bottom: 8 })

          Text('• 本页面展示 C++ 模拟的无障碍节点')
            .fontSize(12)
            .fontColor('#666666')
            .width('100%')

          Text('• 节点通过 fillAccessibilityElement() 调用 Native C-API 接口')
            .fontSize(12)
            .fontColor('#666666')
            .width('100%')

          Text('• 使用辅助功能可以遍历和操作这些节点')
            .fontSize(12)
            .fontColor('#666666')
            .width('100%')
        }
        .width('100%')
        .padding({ left: 16, right: 16, top: 8, bottom: 16 })
        .alignItems(HorizontalAlign.Start)
        .backgroundColor('#F5F5F5')
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#F1F3F5')
    }
    .backgroundColor('#F1F3F5')
    .title(this.scenarioName, {
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      barStyle: BarStyle.STACK
    })
    .onReady((context: NavDestinationContext) => {
      // 页面准备完成
      console.info(`ScenarioPage ready for ${this.scenarioId}`);
    })
  }
}
