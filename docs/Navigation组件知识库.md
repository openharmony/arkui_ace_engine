# Navigation 组件知识库

## 概述

Navigation 是鸿蒙 ACE (ArkUI Component Engine) 框架中的导航容器组件，用于管理应用的页面导航和路由。它提供了多种导航模式（栈式、分屏、自动），支持导航栏（NavBar）和页面内容（NavDestination）的管理，并提供了完整的生命周期管理和动画过渡机制。

### 支持设备
| 手机 | 智慧屏 | 智能穿戴 | 轻量级智能穿戴 | 轻车机 |
| ---- | ------ | -------- | -------------- | ------ |
| 支持 | 支持   | 支持     | 支持           | 支持   |

## 子组件

- **NavDestination**: 导航目标页面组件，表示导航栈中的每个页面

## 属性 (API)

### Navigation 容器属性

| 名称 | 类型 | 默认值 | 必填 | 描述 |
| ---- | ---- | ------ | ---- | ---- |
| navBarWidth | Length | 240vp | 否 | 设置导航栏宽度 |
| navBarPosition | NavBarPosition | START (0) | 否 | 设置导航栏位置：0-开始位置，1-结束位置 |
| navBarWidthRange | [Dimension, Dimension] | [240vp, 40%] | 否 | 设置导航栏宽度范围[最小值, 最大值] |
| minContentWidth | Dimension | 360vp | 否 | 设置内容区域最小宽度 |
| mode | NavigationMode | STACK (0) | 否 | 导航模式：0-栈式，1-分屏，2-自动 |
| backButtonIcon | string \| object | - | 否 | 设置返回按钮图标 |
| hideNavBar | boolean | false | 否 | 是否隐藏导航栏 |
| title | ResourceStr \| CustomBuilder \| NavigationCommonTitle \| NavigationCustomTitle | - | 否 | 设置导航标题 |
| subTitle | string | - | 否 | 设置副标题 |
| enableModeChangeAnimation | boolean | - | 否 | 是否启用模式切换动画 |
| hideTitleBar | boolean | false | 否 | 是否隐藏标题栏 |
| hideBackButton | boolean | false | 否 | 是否隐藏返回按钮 |
| titleMode | NavigationTitleMode | FREE (0) | 否 | 标题模式：0-自由，1-完整，2-迷你 |
| menus | Array<NavigationMenuItem> | - | 否 | 设置菜单项数组 |
| hideToolBar | boolean | false | 否 | 是否隐藏工具栏 |
| ignoreLayoutSafeArea | types: SafeAreaType[], edges: SafeAreaEdge[] | - | 否 | 设置忽略的安全区域类型和边缘 |
| recoverable | boolean | - | 否 | 设置是否可恢复 |
| enableDragBar | boolean | false | 否 | 是否启用拖动条 |

### Navigation 事件

| 名称 | 参数类型 | 描述 |
| ---- | -------- | ---- |
| onNavBarStateChange | (isVisible: boolean) => void | 导航栏显示状态变化时触发 |
| onTitleModeChange | (titleMode: NavigationTitleMode) => void | 标题模式变化时触发 |

### NavDestination 属性

| 名称 | 类型 | 默认值 | 必填 | 描述 |
| ---- | ---- | ------ | ---- | ---- |
| title | string | - | 否 | 设置页面标题 |
| subTitle | string | - | 否 | 设置页面副标题 |
| hideTitleBar | boolean | false | 否 | 是否隐藏标题栏 |
| backButtonIcon | string \| object | - | 否 | 设置返回按钮图标 |

### NavDestination 生命周期事件

| 名称 | 描述 |
| ---- | ---- |
| onWillAppear | 页面即将显示时触发 |
| onAppear | 页面已显示时触发 |
| onWillShow | 页面即将展示时触发 |
| onShow | 页面已展示时触发 |
| onWillHide | 页面即将隐藏时触发 |
| onHide | 页面已隐藏时触发 |
| onWillDisappear | 页面即将消失时触发 |
| onDisappear | 页面已消失时触发 |

## 枚举类型

### NavigationMode (导航模式)
```typescript
enum NavigationMode {
  STACK = 0,    // 栈式导航模式
  SPLIT = 1,    // 分屏导航模式
  AUTO = 2      // 自动模式（根据设备形态自动选择）
}
```

### NavigationTitleMode (标题模式)
```typescript
enum NavigationTitleMode {
  FREE = 0,     // 自由模式
  FULL = 1,     // 完整模式
  MINI = 2      // 迷你模式
}
```

### NavBarPosition (导航栏位置)
```typescript
enum NavBarPosition {
  START = 0,    // 开始位置（左侧）
  END = 1       // 结束位置（右侧）
}
```

### NavRouteMode (路由模式)
```typescript
enum NavRouteMode {
  PUSH_WITH_RECREATE = 0,  // 推入并重建
  PUSH = 1,                // 推入
  REPLACE = 2              // 替换
}
```

### NavigationOperation (导航操作)
```typescript
enum NavigationOperation {
  PUSH = 1,     // 推入操作
  POP = 2,      // 弹出操作
  REPLACE = 3    // 替换操作
}
```

### NavDestinationMode (目标页面模式)
```typescript
enum NavDestinationMode {
  STANDARD = 0,  // 标准模式
  DIALOG = 1     // 对话框模式
}
```

### NavDestinationLifecycle (生命周期)
```typescript
enum NavDestinationLifecycle {
  ON_WILL_APPEAR,      // 即将显示
  ON_APPEAR,           // 已显示
  ON_WILL_SHOW,        // 即将展示
  ON_SHOW,             // 已展示
  ON_WILL_HIDE,        // 即将隐藏
  ON_HIDE,             // 已隐藏
  ON_WILL_DISAPPEAR,   // 即将消失
  ON_DISAPPEAR         // 已消失
}
```

### NavigationSystemTransitionType (系统过渡类型)
```typescript
enum NavigationSystemTransitionType {
  NONE = 0,        // 无过渡
  TITLE = 1,        // 标题过渡
  CONTENT = 2,       // 内容过渡
  DEFAULT = 3        // 默认过渡（标题 + 内容）
}
```

## 常量定义

```cpp
// 标题栏相关
constexpr Dimension MAX_TITLE_FONT_SIZE = 30.0_vp;
constexpr Dimension MIN_TITLE_FONT_SIZE = 20.0_vp;
constexpr Dimension MIN_ADAPT_TITLE_FONT_SIZE = 14.0_vp;
constexpr Dimension SUBTITLE_FONT_SIZE = 14.0_vp;
constexpr Dimension SUBTITLE_HEIGHT = 26.0_vp;
constexpr Dimension MIN_ADAPT_SUBTITLE_FONT_SIZE = 10.0_vp;
constexpr Dimension TITLEBAR_HEIGHT_MINI = 56.0_vp;
constexpr Dimension TITLEBAR_HEIGHT_WITH_SUBTITLE = 137.0_vp;
constexpr Dimension TITLEBAR_HEIGHT_WITHOUT_SUBTITLE = 112.0_vp;
constexpr uint32_t TITLEBAR_MAX_LINES = 2;

// 返回按钮
constexpr Dimension BACK_BUTTON_SIZE = 48.0_vp;
constexpr Dimension BACK_BUTTON_ICON_SIZE = 24.0_vp;
constexpr Dimension BACK_BUTTON_SYMBOL_PADDING = 14.0_vp;

// 导航栏
constexpr Dimension DEFAULT_MIN_NAV_BAR_WIDTH = 240.0_vp;
constexpr Dimension DEFAULT_MAX_NAV_BAR_WIDTH = 432.0_vp;
constexpr float MAX_NAV_BAR_WIDTH_SCALE = 0.4f;
constexpr Dimension NAV_HORIZONTAL_MARGIN_L = 16.0_vp;
constexpr Dimension NAV_HORIZONTAL_MARGIN_M = 8.0_vp;
constexpr Dimension MENU_ITEM_PADDING = 24.0_vp;
constexpr Dimension MENU_ITEM_SIZE = 48.0_vp;
constexpr Dimension BUTTON_PADDING = 12.0_vp;
constexpr Dimension MENU_BUTTON_PADDING = 8.0_vp;

// 内容区域
constexpr Dimension DEFAULT_MIN_CONTENT_WIDTH = 360.0_vp;
constexpr float SINGLE_PAGE_MAXIMUM_WIDTH = 720.0f;
constexpr Dimension SINGLE_LINE_TITLEBAR_HEIGHT = 56.0_vp;
constexpr Dimension DOUBLE_LINE_TITLEBAR_HEIGHT = 82.0_vp;

// 菜单项
constexpr uint32_t MAXIMUM_TOOLBAR_ITEMS_IN_BAR = 5;
constexpr uint32_t ONE_TOOLBAR_ITEM = 1;
constexpr int8_t MAX_MENU_NUM_SMALL = 3;
constexpr int8_t MAX_MENU_NUM_LARGE = 5;

// 工具栏
constexpr Dimension TEXT_FONT_SIZE = 10.0_vp;
constexpr Dimension ICON_PADDING = 10.0_vp;
constexpr Dimension TEXT_TOP_PADDING = 2.0_vp;

// 分割线
constexpr Dimension DIVIDER_WIDTH = 1.0_px;
constexpr Dimension DEFAULT_DIVIDER_START_MARGIN = 0.0_vp;
constexpr Dimension DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING = 2.0_vp;

// 其他
constexpr Dimension BUTTON_RADIUS_SIZE = 5.0_vp;
constexpr Dimension MAX_OVER_DRAG_OFFSET = 180.0_vp;
constexpr Dimension MORE_BUTTON_CORNER_RADIUS = 8.0_vp;
constexpr float STANDARD_FONT_SCALE = 1.0f;
```

## 源码文件结构

### 核心实现文件
```
frameworks/core/components_ng/pattern/navigation/
├── navigation_pattern.h/cpp               # 主模式实现
├── navigation_model.h                     # 模型接口定义
├── navigation_model_ng.h/cpp              # NG 模型实现
├── navigation_model_data.h                # 模型数据定义
├── navigation_layout_algorithm.h/cpp       # 布局算法
├── navigation_layout_property.h           # 布局属性
├── navigation_layout_util.h              # 布局工具类
├── navigation_event_hub.h/cpp            # 事件处理中心
├── navigation_stack.h/cpp                # 栈管理
├── navigation_route.h                    # 路由信息
├── navigation_options.h                  # 导航选项
├── navigation_group_node.h               # 组节点实现
├── navigation_content_pattern.h          # 内容区域模式
├── navigation_content_layout_algorithm.h   # 内容区域布局算法
├── navigation_drag_bar_pattern.h/cpp     # 拖动条实现
├── navigation_transition_proxy.h         # 过渡代理
├── inner_navigation_controller.h         # 内部导航控制器
├── nav_bar_pattern.h/cpp              # 导航栏模式
├── nav_bar_layout_algorithm.h          # 导航栏布局算法
├── nav_bar_layout_property.h           # 导航栏布局属性
├── nav_bar_node.h                    # 导航栏节点
├── title_bar_pattern.h/cpp           # 标题栏模式
├── title_bar_layout_algorithm.h       # 标题栏布局算法
├── title_bar_layout_property.h        # 标题栏布局属性
├── title_bar_node.h                 # 标题栏节点
├── title_bar_accessibility_property.h # 标题栏无障碍属性
├── title_bar_util.h                 # 标题栏工具
├── tool_bar_pattern.h/cpp           # 工具栏模式
├── tool_bar_layout_algorithm.h        # 工具栏布局算法
├── tool_bar_node.h                 # 工具栏节点
├── tool_bar_node.h                 # 工具栏节点
├── navigation_toolbar_util.h         # 工具栏工具
├── bar_item_pattern.h              # 栏项模式
├── bar_item_node.h                # 栏项节点
├── bar_item_layout_algorithm.h      # 栏项布局算法
├── bar_item_event_hub.h           # 栏项事件中心
└── navigation_declaration.h          # 组件声明和常量定义
```

### 前端桥接文件
```
frameworks/bridge/declarative_frontend/
├── ark_component/src/ArkNavigation.ts         # ArkTS组件实现
└── ark_modifier/src/navigation_modifier.ts    # TypeScript修饰器
```

### 管理器文件
```
frameworks/core/components_ng/manager/navigation/
└── navigation_manager.h                      # 导航管理器
```

### 测试文件
```
test/unittest/core/pattern/navigation/
├── navigation_test_ng.cpp                  # 基础功能测试
├── navigation_pattern_test_ng.cpp           # 模式测试
├── navigation_animation_test_ng.cpp          # 动画测试
├── navigation_layout_test_ng.cpp            # 布局测试
├── navigation_lifecycle_test_ng.cpp         # 生命周期测试
└── mock_navigation_stack.h                 # Mock导航栈
```

## 使用示例

### 基础用法
```typescript
@Entry
@Component
struct NavigationExample {
  @Builder pageMap(name: string) {
    Text(`Page: ${name}`)
      .width('100%')
      .height('100%')
      .textAlign(TextAlign.Center)
  }

  build() {
    Navigation() {
      // 使用 NavDestination 定义子页面
      NavDestination() {
        this.pageMap('Page 1')
      }
      .title('首页')
      .mode(NavigationMode.STACK)
    }
    .navBarWidth(240)
    .mode(NavigationMode.STACK)
    .title('主标题')
    .subTitle('副标题')
    .titleMode(NavigationTitleMode.FULL)
  }
}
```

### 分屏模式示例
```typescript
@Entry
@Component
struct SplitNavigationExample {
  @Builder pageMap(name: string) {
    Text(`Page: ${name}`)
      .width('100%')
      .height('100%')
      .fontSize(24)
      .textAlign(TextAlign.Center)
  }

  build() {
    Navigation() {
      // 侧边栏页面
      NavDestination() {
        this.pageMap('侧边栏')
      }
      .title('导航菜单')

      // 主内容页面
      NavDestination() {
        this.pageMap('主内容')
      }
      .title('详情页面')
    }
    .mode(NavigationMode.SPLIT)
    .navBarWidth(280)
    .navBarPosition(NavBarPosition.START)
  }
}
```

### 自定义标题栏
```typescript
@Entry
@Component
struct CustomTitleBarExample {
  build() {
    Navigation() {
      NavDestination() {
        Text('页面内容')
          .fontSize(24)
      }
      .title('自定义标题')
      .subTitle('副标题信息')
    }
    .titleMode(NavigationTitleMode.FULL)
    .hideBackButton(false)
    .menus([
      { value: '菜单1', icon: 'common/icon1.png', action: () => console.info('菜单1') },
      { value: '菜单2', icon: 'common/icon2.png', action: () => console.info('菜单2') }
    ])
  }
}
```

### 带拖动条的Navigation
```typescript
@Entry
@Component
struct DragBarNavigationExample {
  build() {
    Navigation() {
      NavDestination() {
        Text('拖动导航栏分割线来调整宽度')
          .fontSize(20)
      }
      .title('可调整宽度')
    }
    .mode(NavigationMode.SPLIT)
    .navBarWidthRange([200, 400])
    .enableDragBar(true)
  }
}
```

### NavDestination 生命周期示例
```typescript
@Entry
@Component
struct LifecycleExample {
  build() {
    Navigation() {
      NavDestination() {
        Text('生命周期示例页面')
      }
      .title('生命周期')
      .onWillAppear(() => {
        console.info('页面即将显示')
      })
      .onAppear(() => {
        console.info('页面已显示')
      })
      .onWillHide(() => {
        console.info('页面即将隐藏')
      })
      .onHide(() => {
        console.info('页面已隐藏')
      })
    }
  }
}
```

## 关键类说明

### NavigationPattern
核心模式类，管理导航组件的行为和状态：
- 管理导航栈（NavigationStack）
- 处理页面跳转和动画
- 协调导航栏、标题栏、工具栏和内容区域的布局
- 处理模式切换（栈式/分屏/自动）
- 管理系统栏样式
- 处理拖动条交互

### NavigationModel / NavigationModelNG
数据模型类，存储导航状态：
- 当前导航模式
- 导航栈状态
- 页面参数
- 标题和副标题
- 菜单项配置

### NavigationEventHub
事件处理中心，管理导航相关事件：
- 页面切换事件
- 标题模式变化事件
- 导航栏状态变化事件
- 自定义动画事件

### NavigationStack
导航栈管理类：
- 管理页面栈
- 处理 Push/Pop/Replace 操作
- 管理页面索引和名称映射

### NavBarPattern / TitleBarPattern / ToolBarPattern
子组件模式类：
- NavBarPattern: 管理侧边导航栏
- TitleBarPattern: 管理顶部标题栏
- ToolBarPattern: 管理底部工具栏

### NavDestinationPatternBase
目标页面模式基类：
- 管理页面状态
- 处理页面生命周期事件
- 管理返回按钮和标题

## 架构设计

Navigation 组件采用分层架构：

```
┌─────────────────────────────────────────────────────────────┐
│              TypeScript/ArkTS 层                       │
│              (ArkNavigation.ts)                         │
└────────────────────────┬────────────────────────────────────┘
                     │
┌────────────────────▼────────────────────────────────────┐
│              修饰器层 (Modifier)                      │
│         (NavigationModifier + NavDestinationModifier)        │
└────────────────────┬────────────────────────────────────┘
                     │
┌────────────────────▼────────────────────────────────────┐
│              组节点层 (Group Node)                     │
│            (NavigationGroupNode)                        │
└────────────────────┬────────────────────────────────────┘
                     │
      ┌──────────────┼──────────────┐
      │              │              │
┌─────▼─────┐ ┌───▼────┐ ┌───▼──────────┐
│模式层      │ │模型层   │ │布局层          │
│(Navigation │ │(Model) │ │(Layout        │
│Pattern)   │ │        │ │Algorithm)     │
├─────────┤ ├────────┤ ├───────────────┤
│NavBar    │ │Navigation│ │Navigation     │
│TitleBar  │ │Stack   │ │NavBar         │
│ToolBar   │ │        │ │TitleBar       │
│Content   │ │        │ │ToolBar        │
└─────┬─────┘ └───┬────┘ └───▼──────────┘
      │            │              │
      └────────────┴──────────────┘
                     │
┌────────────────────▼────────────────────────────────────┐
│              事件层 (Event Hub)                        │
│      (NavigationEventHub + NavDestinationEventHub)        │
└─────────────────────────────────────────────────────────────┘
```

## 导航流程

### 页面跳转流程
```
用户触发导航操作
        │
        ▼
NavigationPattern 接收请求
        │
        ├─► PUSH: 将页面推入导航栈
        ├─► POP: 从导航栈弹出页面
        └─► REPLACE: 替换栈顶页面
        │
        ▼
更新 NavigationStack
        │
        ▼
触发页面生命周期事件
        │
        ▼
执行过渡动画
        │
        ▼
更新 UI 显示
```

### 模式切换流程
```
设备状态变化或用户触发
        │
        ▼
NavigationPattern.JudgeFoldStateChangeAndUpdateState()
        │
        ▼
计算新模式 (STACK/SPLIT/AUTO)
        │
        ▼
执行模式切换动画
        │
        ▼
更新布局和显示
```

## 生命周期管理

Navigation 组件支持以下生命周期事件：

```cpp
enum NavDestinationLifecycle {
  ON_WILL_APPEAR,      // 即将显示
  ON_APPEAR,           // 已显示
  ON_WILL_SHOW,        // 即将展示
  ON_SHOW,             // 已展示
  ON_WILL_HIDE,        // 即将隐藏
  ON_HIDE,             // 已隐藏
  ON_WILL_DISAPPEAR,   // 即将消失
  ON_DISAPPEAR         // 已消失
};
```

生命周期调用顺序：
1. **页面推入**: ON_WILL_APPEAR → ON_APPEAR → ON_WILL_SHOW → ON_SHOW
2. **页面弹出**: ON_WILL_HIDE → ON_HIDE → ON_WILL_DISAPPEAR → ON_DISAPPEAR
3. **页面替换**: 当前页 ON_WILL_HIDE → 新页 ON_WILL_APPEAR → 当前页 ON_DISAPPEAR → 新页 ON_SHOW

## 动画系统

Navigation 支持以下动画：

1. **页面切换动画**
   - Push: 新页面从右侧滑入
   - Pop: 当前页面向右滑出
   - Replace: 当前页面淡出，新页面淡入

2. **模式切换动画**
   - STACK → SPLIT: 平滑展开侧边栏
   - SPLIT → STACK: 平滑收起侧边栏

3. **自定义动画**
   - 支持通过 `onAnimation` 回调自定义过渡效果
   - 可以控制标题和内容的独立过渡

## 注意事项

1. **导航模式选择**：
   - STACK：适用于传统的层级导航（如手机）
   - SPLIT：适用于左右分栏的导航（如平板）
   - AUTO：根据设备形态和折叠状态自动选择

2. **导航栏宽度**：
   - 建议设置合理的宽度范围
   - 最大宽度不宜超过屏幕宽度的 40%
   - 最小宽度不应小于 200vp
   - 可通过 enableDragBar 允许用户拖动调整

3. **内容区域宽度**：
   - minContentWidth 确保内容不会太窄
   - 在分屏模式下尤为重要
   - 建议设置为 360vp 或更大

4. **安全区域**：
   - 默认会考虑安全区域（状态栏、导航栏等）
   - 可通过 `ignoreLayoutSafeArea` 自定义
   - 注意全面屏手势区域的适配

5. **性能优化**：
   - 使用栈模式时注意控制栈深度
   - 合理使用 `recoverable` 属性管理内存
   - 避免在页面中放置过多内容
   - 使用 LazyForEach 优化列表渲染

6. **生命周期处理**：
   - 在 `onDisappear` 中释放资源
   - 在 `onAppear` 中初始化数据
   - 避免在生命周期回调中执行耗时操作

7. **拖动条**：
   - enableDragBar 需要在 SPLIT 模式下使用
   - 拖动时触发宽度变化事件
   - 可以限制拖动范围

8. **自定义标题**：
   - 支持字符串、资源、自定义构建器
   - 可以设置主标题和副标题
   - 标题模式影响显示效果

9. **菜单和工具栏**：
   - menus 支持最多 5 个菜单项
   - 超过限制时会收起到更多菜单
   - 工具栏项支持图标和文本
