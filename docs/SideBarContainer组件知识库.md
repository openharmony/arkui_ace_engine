# SideBarContainer 组件知识库

## 概述

SideBarContainer 是鸿蒙 ACE 框架中的侧边栏容器组件，用于实现可滑动的侧边栏功能。它支持侧边栏的显示/隐藏切换，可以放置在屏幕的左侧或右侧（通过 sideBarPosition 设置），并提供了丰富的自定义选项，包括拖动调整宽度、自动隐藏、分割线样式等。

### 支持设备
| 手机 | 智慧屏 | 智能穿戴 | 轻量级智能穿戴 | 轻车机 |
| ---- | ------ | -------- | -------------- | ------ |
| 支持 | 支持   | 支持     | 支持           | 支持   |

## 子组件

- **第一个子组件**：侧边栏内容（SideBar）
- **第二个子组件**：主内容区域（Content）

## 属性 (API)

### SideBarContainer 容器属性

| 名称 | 类型 | 默认值 | 必填 | 描述 |
| ---- | ---- | ------ | ---- | ---- |
| sideBarWidth | number \| Length | 200 | 否 | 设置侧边栏宽度 |
| sideBarPosition | SideBarPosition | START (0) | 否 | 设置侧边栏位置：0-左侧，1-右侧（注意：END 在代码中实际实现为右侧，而非文档中的顶部） |
| minSideBarWidth | number \| Length | 200 | 否 | 设置侧边栏最小宽度 |
| maxSideBarWidth | number \| Length | 280 | 否 | 设置侧边栏最大宽度 |
| minContentWidth | Dimension | - | 否 | 设置内容区域最小宽度 |
| autoHide | boolean | false | 否 | 设置是否自动隐藏侧边栏（点击内容区域时隐藏） |
| showSideBar | boolean | true | 否 | 设置侧边栏是否显示 |
| showControlButton | boolean | true | 否 | 设置是否显示控制按钮 |
| controlButton | ButtonStyle | - | 否 | 设置控制按钮样式 |
| divider | DividerStyle \| null | - | 否 | 设置分割线样式（null 表示不显示分割线） |

### SideBarContainer 事件

| 名称 | 参数类型 | 描述 |
| ---- | -------- | ---- |
| onChange | (value: boolean) => void | 侧边栏显示状态变化时触发，返回当前显示状态 |

## 枚举类型

### SideBarPosition (侧边栏位置)
```typescript
enum SideBarPosition {
  START = 0,    // 左侧
  END = 1       // 右侧
}
```

### SideBarContainerType (侧边栏类型)
```typescript
enum SideBarContainerType {
  EMBED = 0,    // 嵌入式（侧边栏和内容并排显示）
  OVERLAY = 1   // 覆盖式（侧边栏覆盖在内容上方）
}
```

### SideStatus (侧边栏状态)
```typescript
enum SideStatus {
  SHOW = 0,      // 显示
  HIDDEN = 1,    // 隐藏
  CHANGING = 2,  // 变化中（动画进行中）
  AUTO = 3       // 自动
}
```

### SideBarAnimationDirection (动画方向)
```typescript
enum SideBarAnimationDirection {
  LTR,  // 从左到右
  RTL    // 从右到左
}
```

## 数据类型

### ButtonStyle (控制按钮样式)
```typescript
interface ButtonStyle {
  left: number;          // 按钮左边距，默认 16
  top: number;           // 按钮上边距，默认 48
  width: number;         // 按钮宽度，默认 32
  height: number;        // 按钮高度，默认 32
  icons?: {
    shown: string;       // 显示状态图标路径
    hidden: string;      // 隐藏状态图标路径
    switching: string;   // 切换中图标路径
  };
}
```

### DividerStyle (分割线样式)
```typescript
interface DividerStyle {
  strokeWidth: Dimension | number;  // 分割线宽度
  color: ResourceColor;             // 分割线颜色
  startMargin: Dimension;           // 起始边距
  endMargin: Dimension;             // 结束边距
}
```

## 常量定义

```cpp
// 侧边栏尺寸
constexpr int MAX_SIDE_BAR_WIDTH = 280;
constexpr int MIN_SIDE_BAR_WIDTH = 200;
constexpr int DEFAULT_SIDE_BAR_WIDTH = 200;

// 控制按钮默认位置
constexpr double DEFAULT_CONTROL_BUTTON_LEFT = 16.0;
constexpr double DEFAULT_CONTROL_BUTTON_TOP = 48.0;
constexpr double DEFAULT_CONTROL_BUTTON_WIDTH = 32.0;
constexpr double DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0;

// 分割线
constexpr Dimension DEFAULT_DIVIDER_WIDTH = 1.0_px;
constexpr Dimension DEFAULT_DIVIDER_START_MARGIN = 0.0_vp;
constexpr Dimension DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING = 2.0_vp;
```

## 源码文件结构

### 核心实现文件 (旧框架)
```
frameworks/core/components/side_bar/
├── side_bar_container_component.h/cpp      # 主组件实现
├── side_bar_container_element.h/cpp        # 元素实现
├── render_side_bar_container.h/cpp         # 渲染节点
├── rosen_render_side_bar_container.h/cpp  # Rosen 渲染实现
├── side_bar_animation_controller.h/cpp     # 动画控制器
└── render_side_bar_container_creator.cpp    # 渲染节点创建器
```

### NG 框架实现文件
```
frameworks/core/components_ng/pattern/side_bar/
├── side_bar_container_pattern.h/cpp         # NG 模式实现
├── side_bar_container_model_ng.h/cpp        # NG 模型实现
├── side_bar_container_model.h               # 模型基类
├── side_bar_container_layout_property.h       # 布局属性
├── side_bar_container_layout_algorithm.h/cpp  # 布局算法
├── side_bar_container_paint_method.h/cpp     # 绘制方法
├── side_bar_container_event_hub.h           # 事件中心
└── side_bar_theme.h                       # 主题定义
```

### 声明文件
```
frameworks/core/components/declaration/side_bar/
└── side_bar_declaration.h                     # 组件声明和属性定义
```

### 前端桥接文件
```
frameworks/bridge/declarative_frontend/
├── ark_component/src/ArkSideBarContainer.ts # ArkTS 组件实现
├── ark_modifier/src/sidebar_modifier.ts        # TypeScript 修饰器
└── jsview/js_sidebar_container.h/cpp        # JS 视图接口
```

### 测试文件
```
test/unittest/core/pattern/side_bar/
├── side_bar_layout_test_ng.cpp              # 布局测试
├── side_bar_pattern_test_ng.cpp             # 模式测试
└── side_bar_view_test_ng.cpp               # 视图测试
```

## 使用示例

### 基础用法
```typescript
@Entry
@Component
struct SideBarExample {
  @State showSideBar: boolean = true

  build() {
    SideBarContainer() {
      // 侧边栏内容
      Column() {
        Text('侧边栏')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })

        List() {
          ListItem() { Text('菜单项1').fontSize(16) }
          ListItem() { Text('菜单项2').fontSize(16) }
          ListItem() { Text('菜单项3').fontSize(16) }
        }
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#F5F5F5')

      // 主内容区域
      Column() {
        Text('主内容区域')
          .fontSize(24)
          .margin(20)
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#FFFFFF')
    }
    .sideBarWidth(200)
    .showSideBar(this.showSideBar)
    .onChange((value: boolean) => {
      this.showSideBar = value
      console.info(`SideBar show: ${value}`)
    })
  }
}
```

### 自定义控制按钮
```typescript
@Entry
@Component
struct SideBarButtonExample {
  @State showSideBar: boolean = true

  build() {
    SideBarContainer() {
      Column() {
        Text('侧边栏内容')
          .fontSize(18)
          .padding(15)
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#E8E8E8')

      Column() {
        Text('主内容')
          .fontSize(20)
          .padding(20)
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#FFFFFF')
    }
    .sideBarWidth(250)
    .showSideBar(this.showSideBar)
    .showControlButton(true)
    .controlButton({
      left: 20,
      top: 50,
      width: 40,
      height: 40,
      icons: {
        shown: 'common/icons/menu_open.png',
        hidden: 'common/icons/menu_close.png'
      }
    })
  }
}
```

### 设置分割线
```typescript
@Entry
@Component
struct SideBarDividerExample {
  build() {
    SideBarContainer() {
      Column() {
        Text('侧边栏')
          .fontSize(18)
          .padding(15)
      }
      .width('100%')
      .height('100%')

      Column() {
        Text('主内容')
          .fontSize(20)
          .padding(20)
      }
      .width('100%')
      .height('100%')
    }
    .sideBarWidth(200)
    .divider({
      strokeWidth: 2,
      color: '#E0E0E0',
      startMargin: 0,
      endMargin: 0
    })
  }
}
```

### 可拖动调整宽度
```typescript
@Entry
@Component
struct SideBarDragExample {
  @State sideBarWidth: number = 240

  build() {
    SideBarContainer() {
      Column() {
        Text('可拖动调整宽度')
          .fontSize(16)
          .margin(15)
      }
      .width('100%')
      .height('100%')

      Column() {
        Text(`当前宽度: ${this.sideBarWidth}`)
          .fontSize(20)
          .margin(20)
      }
      .width('100%')
      .height('100%')
    }
    .sideBarWidth(this.sideBarWidth)
    .minSideBarWidth(180)
    .maxSideBarWidth(400)
  }
}
```

### 自动隐藏模式
```typescript
@Entry
@Component
struct SideBarAutoHideExample {
  build() {
    SideBarContainer() {
      Column() {
        Text('侧边栏')
          .fontSize(18)
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#F0F0F0')

      Column() {
        Text('点击主内容区域自动隐藏侧边栏')
          .fontSize(16)
          .fontColor(Color.Red)
          .textAlign(TextAlign.Center)
      }
      .width('100%')
      .height('100%')
      .justifyContent(FlexAlign.Center)
    }
    .sideBarWidth(200)
    .autoHide(true)
    .showControlButton(false)
  }
}
```

### 侧边栏在右侧
```typescript
@Entry
@Component
struct SideBarRightExample {
  build() {
    SideBarContainer() {
      Column() {
        Text('主内容')
          .fontSize(20)
          .padding(20)
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#FFFFFF')

      Column() {
        Text('右侧边栏')
          .fontSize(18)
          .padding(15)
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#F5F5F5')
    }
    .sideBarWidth(250)
    .sideBarPosition(SideBarPosition.END)
  }
}
```

### 无分割线
```typescript
@Entry
@Component
struct SideBarNoDividerExample {
  build() {
    SideBarContainer() {
      Column() {
        Text('侧边栏内容')
          .fontSize(18)
      }
      .width('100%')
      .height('100%')

      Column() {
        Text('主内容（无分割线）')
          .fontSize(20)
      }
      .width('100%')
      .height('100%')
    }
    .sideBarWidth(220)
    .divider(null)  // 不显示分割线
  }
}
```

## 关键类说明

### SideBarContainerPattern (NG 框架)
核心模式类，管理侧边栏的行为：
- 管理侧边栏显示/隐藏状态
- 处理拖动手势和分割线拖动
- 管理动画效果
- 处理控制按钮点击
- 协调布局计算

### SideBarContainerModel / SideBarContainerModelNG
数据模型类：
- 存储侧边栏配置
- 管理侧边栏状态
- 存储布局参数

### SideBarContainerEventHub
事件处理中心：
- 处理 onChange 事件
- 管理点击事件
- 处理拖动事件

### SideBarContainerLayoutAlgorithm
布局算法：
- 计算侧边栏宽度
- 计算内容区域宽度
- 处理嵌入/覆盖模式布局
- 处理拖动宽度调整

### SideBarContainerPaintMethod
绘制方法：
- 绘制分割线
- 绘制阴影效果
- 处理动画绘制

### SideBarAnimationController
动画控制器：
- 管理侧边栏显示/隐藏动画
- 处理滑动动画
- 控制动画时间线

## 架构设计

SideBarContainer 组件采用分层架构：

```
┌─────────────────────────────────────────────────┐
│       TypeScript/ArkTS 层                   │
│       (ArkSideBarContainer.ts)               │
└──────────────────┬──────────────────────────┘
                   │
┌──────────────────▼──────────────────────────┐
│       修饰器层 (Modifier)                │
│       (SideBarContainerModifier)            │
└──────────────────┬──────────────────────────┘
                   │
┌──────────────────▼──────────────────────────┐
│       声明层 (Declaration)               │
│       (SideBarDeclaration)                 │
└──────────────────┬──────────────────────────┘
                   │
          ┌────────┴────────┐
          │                 │
┌─────────▼──────┐   ┌───▼──────────┐
│ 组件层          │   │ 渲染层      │
│ (SideBar         │   │ (RenderSideBar│
│ Container)       │   │ Container)    │
│                 │   │               │
│                 │   │               │
└─────────┬────────┘   └───────────────┘
          │
          ▼
┌──────────────────────────────────────────────┐
│       动画控制器                         │
│       (SideBarAnimationController)         │
└──────────────────────────────────────────────┘
```

## 动画效果

SideBarContainer 支持以下动画：

1. **显示/隐藏动画**：侧边栏滑入/滑出
   - 滑入：从侧边滑入到显示位置
   - 滑出：从显示位置滑出到屏幕外

2. **拖动动画**：用户拖动时的实时跟随
   - 分割线拖动：实时调整宽度
   - 侧边栏拖动：跟随手指移动

3. **自动隐藏动画**：点击主内容区域时的平滑过渡

4. **控制按钮动画**：按钮图标切换动画

动画配置：
- 默认动画时长：250ms
- 使用缓动函数实现平滑过渡
- 支持 RTL（从右到左）方向

## 布局计算

侧边栏布局计算流程：

```
1. 获取容器总宽度
         │
         ▼
2. 根据 sideBarPosition 确定方向
         │
         ▼
3. 计算侧边栏宽度（限制在 min~max 范围内）
         │
         ▼
4. 计算主内容区域宽度 = 容器宽度 - 侧边栏宽度
         │
         ▼
5. 检查 minContentWidth，必要时调整侧边栏宽度
         │
         ▼
6. 应用布局（嵌入或覆盖模式）
```

### EMBED vs OVERLAY 模式

**EMBED 模式**：
```
┌─────────────────────────────────────────┐
│ ┌─────────┐ ┌─────────────────────┐ │
│ │ SideBar │ │     Content       │ │
│ │  200vp  │ │     (calc)       │ │
│ │         │ │                   │ │
│ └─────────┘ └─────────────────────┘ │
└─────────────────────────────────────────┘
     总宽度 = 侧边栏 + 内容区
```

**OVERLAY 模式**：
```
┌─────────────────────────────────────────┐
│ ┌─────────────────────┐             │
│ │     Content       │ ┌─────────┐ │
│ │     (100%)       │ │ SideBar │ │
│ │                   │ │  200vp  │ │
│ └─────────────────────┘ └─────────┘ │
└─────────────────────────────────────────┘
     侧边栏覆盖在内容上方
```

## 事件流程

### 显示/隐藏流程
```
用户触发（点击按钮或内容区）
        │
        ▼
SideBarContainerPattern 处理事件
        │
        ▼
更新 SideBarStatus (SHOW/HIDDEN/CHANGING)
        │
        ▼
执行动画（如果启用）
        │
        ▼
触发 onChange 回调
        │
        ▼
更新 UI 显示
```

### 拖动宽度流程
```
用户拖动分割线
        │
        ▼
HandleDragStart() - 记录起始位置
        │
        ▼
HandleDragUpdate() - 实时更新宽度
        │
        ▼
限制宽度在 min~max 范围内
        │
        ▼
HandleDragEnd() - 完成拖动
        │
        ▼
触发宽度变化事件
```

## 注意事项

1. **子组件顺序**：
   - 第一个子组件是侧边栏内容
   - 第二个子组件是主内容区域
   - 只能包含两个直接子组件
   - 需要在每个子组件内使用容器（如 Column）来放置多个元素

2. **宽度设置**：
   - sideBarWidth 应在 minSideBarWidth 和 maxSideBarWidth 之间
   - minContentWidth 会影响侧边栏的最大可用宽度
   - 建议使用 vp 单位以适应不同屏幕
   - 拖动调整时需要设置 min/max 范围

3. **性能优化**：
   - 复杂内容建议使用 LazyForEach
   - 动画过程中避免频繁更新状态
   - autoHide 模式下注意点击事件冲突
   - 侧边栏内容建议轻量化

4. **控制按钮**：
   - 默认显示，可通过 showControlButton 隐藏
   - 自定义图标时注意图标尺寸
   - 按钮位置相对于容器边缘
   - 支持长按显示更多选项

5. **分割线**：
   - 只在侧边栏和主内容之间显示
   - 设置 null 可移除分割线
   - 边距支持负值实现边对边效果
   - 支持拖动调整宽度（需要设置范围）

6. **位置设置**：
   - sideBarPosition.START：左侧（默认）
   - sideBarPosition.END：右侧
   - RTL 语言环境下会自动镜像

7. **自动隐藏**：
   - autoHide 模式下点击主内容区域会隐藏侧边栏
   - 需要通过控制按钮或其他方式重新显示
   - 建议配合 showControlButton 使用

8. **动画方向**：
   - LTR：从左到右（START 位置时）
   - RTL：从右到左（END 位置或 RTL 语言）
   - 自动根据语言和位置设置

9. **状态管理**：
   - 通过 onChange 监听显示状态
   - 使用 @State 管理侧边栏状态
   - 动画进行中状态为 CHANGING

10. **无障碍支持**：
   - 确保为屏幕阅读器提供合适的标签
   - 控制按钮需要可访问性描述
   - 拖动区域需要有适当的语义

11. **主题适配**：
   - 支持跟随系统主题变化
   - 颜色资源建议使用系统主题色
   - 注意深色/浅色模式的适配
