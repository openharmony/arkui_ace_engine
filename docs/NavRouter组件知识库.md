# NavRouter 组件知识库

## 概述

NavRouter 是鸿蒙 ACE 框架中的路由导航组件，用于实现页面间的跳转导航。它是 Navigation 体系的重要补充组件，主要用于包装可点击的组件（如 Button、Text、List 等），使其具有路由跳转功能。当用户点击被 NavRouter 包装的组件时，会触发导航到对应的 NavDestination 页面。

### 支持设备
| 手机 | 智慧屏 | 智能穿戴 | 轻量级智能穿戴 | 轻车机 |
| ---- | ------ | -------- | -------------- | ------ |
| 支持 | 支持   | 支持     | 支持           | 支持   |

## 子组件

支持单个子组件，通常包装可点击的组件如 Button、Text、ListItem 等。

## 属性 (API)

### NavRouter 容器属性

| 名称 | 类型 | 默认值 | 必填 | 描述 |
| ---- | ---- | ------ | ---- | ---- |
| mode | NavRouteMode | PUSH_WITH_RECREATE (0) | 否 | 路由模式：0-推入并重建，1-推入，2-替换 |

### NavRouter 事件

| 名称 | 参数类型 | 描述 |
| ---- | -------- | ---- |
| onStateChange | (isActivated: boolean) => void | 当路由激活状态变化时触发，返回当前激活状态 |

## 枚举类型

### NavRouteMode (路由模式)
```typescript
enum NavRouteMode {
  PUSH_WITH_RECREATE = 0,  // 推入并重建目标页面（默认）
  PUSH = 1,                // 推入目标页面（保留原状态）
  REPLACE = 2               // 替换当前页面
}
```

### NavDestinationMode (目标页面模式)
```typescript
enum NavDestinationMode {
  STANDARD = 0,  // 标准模式
  DIALOG = 1     // 对话框模式
}
```

## 常量定义

```cpp
// 路由模式默认值
constexpr NavRouteMode DEFAULT_NAV_ROUTE_MODE = NavRouteMode::PUSH_WITH_RECREATE;
```

## 源码文件结构

### 核心实现文件
```
frameworks/core/components_ng/pattern/navrouter/
├── navrouter_pattern.h/cpp                   # 主模式实现
├── navrouter_model.h                         # 模型接口定义
├── navrouter_model_ng.h/cpp                  # NG 模型实现
├── navrouter_event_hub.h                     # 事件处理中心
├── navrouter_group_node.h/cpp               # 组节点实现
├── navdestination_pattern.h                  # 目标页面模式
├── navdestination_model.h                    # 目标页面模型
├── navdestination_model_ng.h/cpp            # 目标页面NG模型
├── navdestination_event_hub.h               # 目标页面事件中心
├── navdestination_layout_property.h          # 目标页面布局属性
├── navdestination_layout_algorithm.h/cpp     # 目标页面布局算法
├── navdestination_context.h                 # 目标页面上下文
├── navdestination_group_node.h/cpp          # 目标页面组节点
├── navdestination_node_base.h               # 目标页面节点基类
└── navdestination_scrollable_processor.h     # 目标页面可滚动处理器
```

### 前端桥接文件
```
frameworks/bridge/declarative_frontend/
├── ark_component/src/ArkNavRouter.ts        # ArkTS NavRouter 组件
├── ark_modifier/src/nav_router_modifier.ts    # TypeScript 修饰器
├── ark_component/src/ArkNavDestination.ts  # ArkTS NavDestination 组件
└── ark_modifier/src/nav_destination_modifier.ts # NavDestination 修饰器
```

### 测试文件
```
test/unittest/core/pattern/navrouter/
├── navrouter_pattern_test_ng.cpp            # NavRouter 模式测试
├── navrouter_model_test_ng.cpp             # NavRouter 模型测试
├── navrouter_group_test_ng.cpp            # NavRouter 组节点测试
├── navdestination_pattern_test_ng.cpp       # NavDestination 模式测试
└── navdestination_layout_test_ng.cpp      # NavDestination 布局测试
```

## 使用示例

### 基础用法
```typescript
@Entry
@Component
struct NavRouterExample {
  @Builder pageMap(name: string) {
    Text(`Page: ${name}`)
      .width('100%')
      .height('100%')
      .fontSize(30)
      .textAlign(TextAlign.Center)
  }

  build() {
    Navigation() {
      // NavRouter 包装可点击组件
      NavRouter() {
        Button('跳转到页面1')
          .width('80%')
          .height(50)
      }
      .mode(NavRouteMode.PUSH)
      .onStateChange((isActivated: boolean) => {
        console.info(`NavRouter state: ${isActivated}`)
      })

      // 定义对应的目标页面
      NavDestination() {
        this.pageMap('Page 1')
      }
      .title('页面1')
    }
    .mode(NavigationMode.STACK)
  }
}
```

### 不同路由模式示例
```typescript
@Entry
@Component
struct NavRouterModeExample {
  @State currentPage: string = '首页'

  build() {
    Navigation() {
      Column({ space: 20 }) {
        Text(`当前页面: ${this.currentPage}`)
          .fontSize(20)
          .margin({ bottom: 20 })

        // PUSH 模式 - 保留原状态
        NavRouter() {
          Button('PUSH 模式跳转')
        }
        .mode(NavRouteMode.PUSH)
        .onStateChange((isActivated) => {
          if (isActivated) this.currentPage = 'PUSH 目标页'
        })

        // PUSH_WITH_RECREATE 模式 - 重建页面（默认）
        NavRouter() {
          Button('推入并重建')
        }
        .mode(NavRouteMode.PUSH_WITH_RECREATE)
        .onStateChange((isActivated) => {
          if (isActivated) this.currentPage = '重建目标页'
        })

        // REPLACE 模式 - 替换当前页面
        NavRouter() {
          Button('替换当前页面')
        }
        .mode(NavRouteMode.REPLACE)
        .onStateChange((isActivated) => {
          if (isActivated) this.currentPage = '替换目标页'
        })

        // 目标页面
        NavDestination() {
          Text('页面内容')
            .fontSize(24)
        }
        .title('目标页面')
      }
      .width('100%')
      .padding(20)
    }
  }
}
```

### 多个 NavRouter 示例
```typescript
@Entry
@Component
struct MultipleNavRouterExample {
  build() {
    Navigation() {
      Column({ space: 20 }) {
        Text('选择要跳转的页面')
          .fontSize(24)
          .margin({ bottom: 30 })

        NavRouter() {
          Row() {
            Image($r('app.media.icon_home'))
              .width(40)
              .height(40)
            Text('首页')
              .fontSize(18)
              .margin({ left: 10 })
          }
          .padding(15)
          .backgroundColor('#F0F0F0')
          .borderRadius(8)
        }
        .mode(NavRouteMode.PUSH)

        NavRouter() {
          Row() {
            Image($r('app.media.icon_profile'))
              .width(40)
              .height(40)
            Text('个人中心')
              .fontSize(18)
              .margin({ left: 10 })
          }
          .padding(15)
          .backgroundColor('#F0F0F0')
          .borderRadius(8)
        }
        .mode(NavRouteMode.PUSH)

        NavRouter() {
          Row() {
            Image($r('app.media.icon_settings'))
              .width(40)
              .height(40)
            Text('设置')
              .fontSize(18)
              .margin({ left: 10 })
          }
          .padding(15)
          .backgroundColor('#F0F0F0')
          .borderRadius(8)
        }
        .mode(NavRouteMode.PUSH)

        NavDestination() {
          Text('页面内容')
            .fontSize(30)
        }
        .title('详情页')
      }
      .width('100%')
      .height('100%')
      .padding(30)
    }
  }
}
```

### 状态监听示例
```typescript
@Entry
@Component
struct NavRouterStateExample {
  @State isActive: boolean = false
  @State bgColor: ResourceColor = Color.Gray

  build() {
    Navigation() {
      NavRouter() {
        Button(this.isActive ? '已激活' : '未激活')
          .width(200)
          .height(60)
          .fontSize(18)
          .backgroundColor(this.bgColor)
      }
      .mode(NavRouteMode.PUSH)
      .onStateChange((isActivated: boolean) => {
        this.isActive = isActivated
        this.bgColor = isActivated ? Color.Green : Color.Gray
        console.info(`Router activated: ${isActivated}`)
      })

      NavDestination() {
        Text('这是目标页面的内容')
          .fontSize(24)
      }
      .title('目标页面')
    }
    .mode(NavigationMode.STACK)
  }
}
```

### 使用 REPLACE 模式实现登录跳转
```typescript
@Entry
@Component
struct LoginReplaceExample {
  @State isLoggedIn: boolean = false

  build() {
    Navigation() {
      // 登录页
      if (!this.isLoggedIn) {
        NavRouter() {
          Column({ space: 20 }) {
            Text('欢迎')
              .fontSize(30)
            TextInput({ placeholder: '用户名' })
            TextInput({ placeholder: '密码' }).type(InputType.Password)
            Button('登录')
              .width('100%')
              .onClick(() => {
                this.isLoggedIn = true
              })
          }
          .width('80%')
          .padding(30)
        }
        .mode(NavRouteMode.REPLACE)
      }

      // 主页（替换后不可返回登录页）
      NavDestination() {
        Column({ space: 20 }) {
          Text('登录成功，欢迎回来！')
            .fontSize(24)
          Button('退出登录')
            .onClick(() => {
              this.isLoggedIn = false
            })
        }
        .width('80%')
        .padding(30)
      }
      .title('主页')
      .hideBackButton(true)
    }
    .mode(NavigationMode.STACK)
  }
}
```

## 关键类说明

### NavRouterPattern
核心模式类，管理路由组件的行为：
- 处理点击事件触发导航
- 根据模式执行不同的导航操作
- 管理激活状态
- 存储路由信息（RouteInfo）
- 设置路由模式（NavRouteMode）

### NavRouterModel / NavRouterModelNG
数据模型类：
- 存储路由模式
- 管理目标页面信息
- 存储路由上下文

### NavRouterEventHub
事件处理中心：
- 处理状态变化事件
- 管理点击事件监听

### NavRouterGroupNode
组节点实现：
- 将 NavRouter 作为 Navigation 的子节点
- 处理节点注册和生命周期
- 管理与 NavDestination 的关联

### NavDestinationPattern
目标页面模式类：
- 管理目标页面的状态
- 处理页面生命周期
- 管理页面标题和返回按钮

## 导航流程

### NavRouter 工作流程
```
用户点击 NavRouter 包装的组件
        │
        ▼
触发点击事件
        │
        ▼
NavRouterPattern 处理事件
        │
        ├─► PUSH_WITH_RECREATE: 推入并重建目标页面
        ├─► PUSH: 推入目标页面（保留状态）
        └─► REPLACE: 替换当前页面
        │
        ▼
Navigation 更新导航栈
        │
        ▼
触发页面切换动画
        │
        ▼
更新 NavRouter 激活状态
        │
        ▼
触发 onStateChange 回调
        │
        ▼
显示目标 NavDestination
```

### 路由模式详解
```
┌─────────────────────────────────────────────────┐
│          PUSH_WITH_RECREATE (0)             │
│  每次都创建新的页面实例                   │
│  适用于需要每次刷新数据的场景               │
│  ┌─────┐     ┌─────┐     ┌─────┐    │
│  │ Page│ ──► │ New │ ──► │ New │    │
│  │  1  │     │Page │     │Page │    │
│  └─────┘     │  2  │     │  3  │    │
│               └─────┘     └─────┘    │
└─────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────┐
│          PUSH (1)                           │
│  保留原页面状态                           │
│  适用于可返回的多层级导航                 │
│  ┌─────┐     ┌─────┐     ┌─────┐    │
│  │ Page│ ──► │ Page│ ──► │ Page│    │
│  │  1  │◄───│  2  │◄───│  3  │    │
│  └─────┘     └─────┘     └─────┘    │
│      ▲          ▲          ▲            │
│      └──────────┴──────────┘            │
│         可逐级返回                       │
└─────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────┐
│          REPLACE (2)                         │
│  替换当前页面，无法返回                 │
│  适用于登录后跳转等场景               │
│  ┌─────┐     ┌─────┐              │
│  │Login │ ──► │Home │              │
│  │ Page│     │Page │              │
│  └─────┘     └─────┘              │
│     X (无法返回)                      │
└─────────────────────────────────────────────────┘
```

## 架构设计

NavRouter 组件采用分层架构：

```
┌─────────────────────────────────────────────────┐
│       TypeScript/ArkTS 层                   │
│       (ArkNavRouter.ts)                     │
└──────────────────┬──────────────────────────┘
                   │
┌──────────────────▼──────────────────────────┐
│       修饰器层 (Modifier)                │
│       (NavRouterModifier)                 │
└──────────────────┬──────────────────────────┘
                   │
┌──────────────────▼──────────────────────────┐
│       组节点层 (Group Node)              │
│       (NavRouterGroupNode)               │
└──────────────────┬──────────────────────────┘
                   │
┌──────────────────▼──────────────────────────┐
│       模式层 (Pattern)                 │
│       (NavRouterPattern)                 │
├──────────────────┬──────────────────────┤
│       模型层 (Model)                  │
│       (NavRouterModelNG)                │
├──────────────────┬──────────────────────┤
│       事件层 (Event Hub)              │
│       (NavRouterEventHub)              │
└───────────────────────────────────────────┘
                    │
                    ▼
         与 Navigation 集成
```

## 与 Navigation 的关系

NavRouter 必须作为 Navigation 的子组件使用，与 NavDestination 配合工作：

```typescript
Navigation() {
  // NavRouter 作为触发跳转的入口
  NavRouter() {
    Button('跳转')
  }
  .mode(NavRouteMode.PUSH)

  // NavDestination 作为目标页面
  NavDestination() {
    // 页面内容
  }
  .title('目标页')
}
```

### 组件关系图
```
┌─────────────────────────────────────────┐
│          Navigation                   │
│  ┌──────────────────────────────┐   │
│  │                          │   │
│  │  ┌──────────────────┐    │   │
│  │  │  NavRouter       │    │   │
│  │  │  (触发器)       │    │   │
│  │  │  ┌──────────┐  │    │   │
│  │  │  │ Button   │  │    │   │
│  │  │  └──────────┘  │    │   │
│  │  └──────────────────┘    │   │
│  │           │               │   │
│  │           ▼               │   │
│  │  ┌──────────────────┐    │   │
│  │  │ NavDestination   │    │   │
│  │  │ (目标页面)      │    │   │
│  │  │  ┌──────────┐  │    │   │
│  │  │  │ Content  │  │    │   │
│  │  │  └──────────┘  │    │   │
│  │  └──────────────────┘    │   │
│  │                          │   │
│  └──────────────────────────────┘   │
└─────────────────────────────────────┘
```

## 激活状态管理

NavRouter 的激活状态通过 `onStateChange` 回调管理：

- **激活状态 (true)**: 当前 NavRouter 对应的 NavDestination 是栈顶页面
- **非激活状态 (false)**: 当前 NavRouter 对应的页面不在栈顶

应用场景：
1. 根据激活状态改变 UI 样式
2. 根据激活状态执行不同逻辑
3. 实现选项卡高亮效果

```typescript
NavRouter() {
  Row() {
    Image($r('app.media.icon'))
      .width(30)
      .height(30)
    Text('导航项')
      .fontColor(this.isActive ? Color.Blue : Color.Black)
  }
  .backgroundColor(this.isActive ? '#E6F2FF' : '#FFFFFF')
  .border(this.isActive ? { width: 2, color: Color.Blue } : undefined)
}
.onStateChange((isActivated) => {
  this.isActive = isActivated
})
```

## 注意事项

1. **使用场景**：
   - NavRouter 适用于包装可点击组件来实现页面跳转
   - 必须与 Navigation 和 NavDestination 配合使用
   - 一个 NavRouter 对应一个 NavDestination

2. **路由模式选择**：
   - PUSH_WITH_RECREATE（默认）：每次创建新实例，适合需要刷新数据的场景
   - PUSH：保留状态，可返回，适合多层级导航
   - REPLACE：替换当前页面，不可返回，适合登录跳转等场景

3. **性能考虑**：
   - PUSH_WITH_RECREATE 会消耗更多资源
   - 控制导航栈深度，避免内存占用过高
   - 合理使用页面状态管理

4. **状态管理**：
   - 通过 onStateChange 监听激活状态
   - 激活状态可用于 UI 状态切换
   - 注意及时清理状态避免内存泄漏

5. **组件嵌套**：
   - NavRouter 内只能有一个子组件
   - 通常包装 Button、Row、Column 等容器组件
   - 可以在容器内放置多个子元素

6. **与 NavDestination 的关联**：
   - NavRouter 通过 name 或索引与 NavDestination 关联
   - Navigation 内部维护这种映射关系
   - 不需要手动管理关联关系

7. **点击处理**：
   - NavRouter 会自动处理点击事件
   - 不需要在子组件上额外添加 onClick
   - 可以通过 mode 控制导航行为

8. **样式建议**：
   - 使用激活状态提供视觉反馈
   - 保持一致的点击区域大小
   - 考虑无障碍访问性
