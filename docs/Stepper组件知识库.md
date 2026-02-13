# Stepper 组件知识库

## 概述

Stepper 是鸿蒙 ACE 框架中的步骤条组件，用于引导用户完成一系列步骤操作。它提供了清晰的进度指示和导航控制，常用于向导、表单分步填写、新手引导等场景。Stepper 通过显示当前步骤、总步骤数、上一步/下一步按钮来引导用户完成多步骤流程。

### 支持设备
| 手机 | 智慧屏 | 智能穿戴 | 轻量级智能穿戴 | 轻车机 |
| ---- | ------ | -------- | -------------- | ------ |
| 支持 | 支持   | 支持     | 支持           | 支持   |

## 子组件

必须包含 **StepperItem** 作为子组件，每个 StepperItem 代表一个步骤。

## 属性 (API)

### Stepper 容器属性

Stepper 容器本身主要用于容纳 StepperItem，主要通过事件响应步骤变化。

### Stepper 事件

| 名称 | 参数类型 | 描述 |
| ---- | -------- | ---- |
| onFinish | () => void | 完成所有步骤时触发（最后一步点击完成按钮时） |
| onSkip | () => void | 跳过步骤时触发 |
| onChange | (prevIndex: number, index: number) => void | 当前步骤索引变化时触发，返回前一个索引和当前索引 |
| onNext | (index: number, pendingIndex: number) => void | 点击下一步按钮时触发，返回当前索引和待跳转索引 |
| onPrevious | (index: number, pendingIndex: number) => void | 点击上一步按钮时触发，返回当前索引和待跳转索引 |

### StepperItem 属性

| 名称 | 类型 | 默认值 | 必填 | 描述 |
| ---- | ---- | ------ | ---- | ---- |
| prevLabel | string | 'Back' | 否 | 上一步按钮文本 |
| nextLabel | string | 'Next' | 否 | 下一步按钮文本 |
| status | ItemState | Normal (0) | 否 | 步骤状态 |

## 枚举类型

### ItemState (步骤状态)
```typescript
enum ItemState {
  Normal = 0,    // 正常状态（默认）
  Disabled = 1,  // 禁用状态（无法进入）
  Skip = 2       // 跳过状态（显示跳过按钮）
}
```

## 常量定义

```cpp
// 进度指示器
constexpr Dimension DEFAULT_PROGRESS_DIAMETER = 48.0_vp;
constexpr Dimension DEFAULT_PROGRESS_COLOR = Color(0xFF007DFF);

// 箭头
constexpr Dimension DEFAULT_ARROW_WIDTH = 11.4_vp;
constexpr Dimension DEFAULT_ARROW_HEIGHT = 20.0_vp;
constexpr Dimension DEFAULT_ARROW_COLOR = Color(0xFF007DFF);

// 禁用状态
constexpr Color DEFAULT_DISABLED_COLOR = Color(0x0F000000);
constexpr double DEFAULT_DISABLED_ALPHA = 0.4;

// 按钮按下效果
constexpr Color DEFAULT_BUTTON_PRESSED_COLOR = Color(0x33000000);
constexpr Dimension DEFAULT_BUTTON_PRESSED_HEIGHT = 32.0_vp;

// 控制区域
constexpr Dimension DEFAULT_CONTROL_HEIGHT = 48.0_vp;
constexpr Dimension DEFAULT_CONTROL_MARGIN = 8.0_vp;
constexpr Dimension DEFAULT_CONTROL_PADDING = 12.0_vp;

// 焦点
constexpr Color DEFAULT_FOCUS_COLOR = Color(0xFF007DFF);
constexpr Dimension DEFAULT_FOCUS_BORDER_WIDTH = 2.0_vp;

// 鼠标悬停
constexpr Color DEFAULT_MOUSE_HOVER_COLOR = Color(0x0A000000);
```

## 源码文件结构

### 核心实现文件 (旧框架)
```
frameworks/core/components/stepper/
├── stepper_component.h/cpp              # 主组件实现
├── stepper_item_component.h/cpp         # 步骤项组件实现
├── stepper_item_component_v2.h/cpp      # V2 版本步骤项
├── stepper_element.h/cpp                # 元素实现
├── stepper_item_element.h/cpp           # 步骤项元素实现
├── render_stepper.h/cpp                 # 渲染节点
├── render_stepper_item.h/cpp            # 步骤项渲染节点
├── rosen_render_stepper.h/cpp           # Rosen 渲染实现
├── rosen_render_stepper_item.h/cpp      # Rosen 步骤项渲染
├── render_stepper_creator.cpp           # 渲染节点创建器
├── render_stepper_item_creator.cpp      # 步骤项渲染节点创建器
├── stepper_animation_controller.h/cpp   # 动画控制器
└── stepper_theme.h                      # 主题定义
```

### NG 框架实现文件
```
frameworks/core/components_ng/pattern/stepper/
├── stepper_pattern.h/cpp                # NG 模式实现
├── stepper_node.h/cpp                   # NG 节点实现
├── stepper_model_ng.h/cpp               # NG 模型实现
├── stepper_item_pattern.h               # 步骤项模式
├── stepper_item_model_ng.h/cpp          # 步骤项模型
├── stepper_item_model.h                 # 步骤项模型基类
├── stepper_layout_property.h             # 布局属性
├── stepper_item_layout_property.h        # 步骤项布局属性
├── stepper_layout_algorithm.h/cpp        # 布局算法
├── stepper_event_hub.h                  # 事件中心
└── stepper_accessibility_property.h/cpp # 无障碍属性
```

### 前端桥接文件
```
frameworks/bridge/declarative_frontend/
├── ark_component/src/ArkStepper.ts        # ArkTS Stepper 组件
├── ark_component/src/ArkStepperItem.ts    # ArkTS StepperItem 组件
├── ark_modifier/src/stepper_modifier.ts    # Stepper 修饰器
├── ark_modifier/src/stepper_item_modifier.ts # StepperItem 修饰器
├── jsview/js_stepper.h/cpp                # JS Stepper 视图接口
└── jsview/js_stepper_item.h/cpp           # JS StepperItem 视图接口
```

### DOM 接口文件
```
frameworks/bridge/common/dom/
├── dom_stepper.h/cpp                    # DOM Stepper 接口
└── dom_stepper_item.h/cpp               # DOM StepperItem 接口
```

### 测试文件
```
test/unittest/core/pattern/stepper/
└── stepper_test_ng.cpp                    # NG 组件测试
```

## 使用示例

### 基础用法
```typescript
@Entry
@Component
struct StepperExample {
  @State currentIndex: number = 0

  build() {
    Stepper() {
      // 步骤 1
      StepperItem() {
        Text('步骤 1 内容')
          .fontSize(24)
          .width('100%')
          .textAlign(TextAlign.Center)
      }
      .nextLabel('下一步')

      // 步骤 2
      StepperItem() {
        Text('步骤 2 内容')
          .fontSize(24)
          .width('100%')
          .textAlign(TextAlign.Center)
      }
      .prevLabel('上一步')
      .nextLabel('下一步')

      // 步骤 3
      StepperItem() {
        Text('步骤 3 内容')
          .fontSize(24)
          .width('100%')
          .textAlign(TextAlign.Center)
      }
      .prevLabel('上一步')
      .nextLabel('完成')
    }
    .onChange((prevIndex: number, index: number) => {
      this.currentIndex = index
      console.info(`从步骤 ${prevIndex} 切换到步骤 ${index}`)
    })
    .onFinish(() => {
      console.info('完成所有步骤')
    })
  }
}
```

### 表单向导示例
```typescript
@Entry
@Component
struct FormWizardExample {
  @State currentStep: number = 0
  @State formData: Record<string, string> = {}

  build() {
    Stepper() {
      // 步骤 1: 基本信息
      StepperItem() {
        Column({ space: 20 }) {
          Text('基本信息')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)

          TextInput({ placeholder: '请输入姓名' })
            .onChange((value) => {
              this.formData['name'] = value
            })

          TextInput({ placeholder: '请输入邮箱' })
            .type(InputType.Email)
            .onChange((value) => {
              this.formData['email'] = value
            })
        }
        .width('100%')
        .padding(20)
      }
      .nextLabel('下一步')

      // 步骤 2: 详细信息
      StepperItem() {
        Column({ space: 20 }) {
          Text('详细信息')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)

          TextInput({ placeholder: '请输入地址' })
            .onChange((value) => {
              this.formData['address'] = value
            })

          TextInput({ placeholder: '请输入电话' })
            .type(InputType.PhoneNumber)
            .onChange((value) => {
              this.formData['phone'] = value
            })
        }
        .width('100%')
        .padding(20)
      }
      .prevLabel('上一步')
      .nextLabel('下一步')

      // 步骤 3: 确认信息
      StepperItem() {
        Column({ space: 20 }) {
          Text('确认信息')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)

          Text(`姓名: ${this.formData['name'] || '未填写'}`)
            .fontSize(16)
          Text(`邮箱: ${this.formData['email'] || '未填写'}`)
            .fontSize(16)
          Text(`地址: ${this.formData['address'] || '未填写'}`)
            .fontSize(16)
          Text(`电话: ${this.formData['phone'] || '未填写'}`)
            .fontSize(16)
        }
        .width('100%')
        .padding(20)
      }
      .prevLabel('返回修改')
      .nextLabel('提交')
    }
    .onFinish(() => {
      console.info('表单提交', JSON.stringify(this.formData))
    })
  }
}
```

### 禁用和跳过步骤示例
```typescript
@Entry
@Component
struct StepperStatusExample {
  @State canProceed: boolean = false
  @State agreedToTerms: boolean = false

  build() {
    Stepper() {
      // 步骤 1: 必填步骤
      StepperItem() {
        Column({ space: 20 }) {
          Text('欢迎使用')
            .fontSize(24)

          Checkbox({ name: 'agree' })
            .select(this.agreedToTerms)
            .onChange((value) => {
              this.agreedToTerms = value
            })
            .text('我同意相关条款')
        }
        .width('100%')
        .padding(20)
      }
      .status(this.canProceed ? ItemState.Normal : ItemState.Disabled)
      .nextLabel(this.canProceed ? '下一步' : '请先同意')

      // 步骤 2: 可选步骤
      StepperItem() {
        Text('可选步骤内容')
          .fontSize(24)
      }
      .status(ItemState.Skip)
      .nextLabel('跳过')

      // 步骤 3: 最终步骤
      StepperItem() {
        Text('完成')
          .fontSize(24)
      }
      .prevLabel('上一步')
      .nextLabel('完成')
    }
  }
}
```

### 自定义按钮文本示例
```typescript
@Entry
@Component
struct CustomLabelsExample {
  build() {
    Stepper() {
      StepperItem() {
        Text('欢迎页面')
          .fontSize(24)
      }
      .prevLabel('返回')
      .nextLabel('开始')

      StepperItem() {
        Text('设置页面')
          .fontSize(24)
      }
      .prevLabel('返回')
      .nextLabel('继续')

      StepperItem() {
        Text('完成页面')
          .fontSize(24)
      }
      .prevLabel('重新配置')
      .nextLabel('立即使用')
    }
  }
}
```

### 动态控制步骤状态
```typescript
@Entry
@Component
struct DynamicStepperExample {
  @State steps: Array<ItemState> = [ItemState.Normal, ItemState.Disabled, ItemState.Normal]

  build() {
    Stepper() {
      StepperItem() {
        Text('步骤 1')
          .fontSize(20)
      }
      .status(this.steps[0])
      .nextLabel('继续')

      StepperItem() {
        Text('步骤 2（需要完成步骤 1）')
          .fontSize(20)
      }
      .status(this.steps[1])
      .nextLabel('继续')

      StepperItem() {
        Text('步骤 3')
          .fontSize(20)
      }
      .status(this.steps[2])
      .nextLabel('完成')
    }
    .onChange((prevIndex: number, index: number) => {
      // 当从第一步进入第二步时，启用第三步
      if (prevIndex === 0 && index === 1) {
        this.steps[2] = ItemState.Normal
      }
    })
  }
}
```

## 关键类说明

### StepperPattern
核心模式类，管理步骤条的行为：
- 管理当前步骤索引
- 处理上一步/下一步点击事件
- 协调进度指示器显示
- 管理按钮状态和文本

### StepperModel / StepperModelNG
数据模型类：
- 存储当前步骤索引
- 存储总步骤数
- 存储按钮文本配置

### StepperEventHub
事件处理中心：
- 处理 onChange 事件
- 处理 onFinish 事件
- 处理 onSkip 事件
- 处理 onNext/onPrevious 事件

### StepperItemPattern
步骤项模式类：
- 管理单个步骤的状态
- 处理按钮文本配置
- 管理步骤内容显示

### StepperItemModel / StepperItemModelNG
步骤项数据模型：
- 存储步骤状态
- 存储按钮文本
- 存储步骤索引

### StepperLayoutAlgorithm
布局算法：
- 计算进度指示器位置
- 计算按钮区域布局
- 处理步骤内容的尺寸计算

## 架构设计

Stepper 组件采用分层架构：

```
┌─────────────────────────────────────────────┐
│       TypeScript/ArkTS 层                │
│       (ArkStepper.ts + ArkStepperItem)  │
└──────────────────┬────────────────────────┘
                   │
┌──────────────────▼────────────────────────┐
│       修饰器层 (Modifier)              │
│       (StepperItemModifier)             │
└──────────────────┬────────────────────────┘
                   │
┌──────────────────▼────────────────────────┐
│       JS 视图层                         │
│       (JSStepper + JSStepperItem)      │
└──────────────────┬────────────────────────┘
                   │
┌──────────────────▼────────────────────────┐
│       DOM 层                              │
│       (DOMStepper + DOMStepperItem)    │
└──────────────────┬────────────────────────┘
                   │
┌──────────────────▼────────────────────────┐
│       组件层                              │
│       (StepperComponent)                 │
├──────────────────┬────────────────────┤
│       步骤项层                           │
│       (StepperItemComponent)             │
├──────────────────┬────────────────────┤
│       渲染层                              │
│       (RenderStepper)                    │
├──────────────────┬────────────────────┤
│       动画层                              │
│       (StepperAnimationController)        │
└───────────────────────────────────────────┘
```

## 进度指示器

Stepper 的进度指示器由以下元素组成：

### 圆点指示器
- 表示每个步骤的圆点
- 当前步骤：高亮显示（蓝色）
- 已完成步骤：显示完成状态（绿色或打勾）
- 未完成步骤：显示为灰色
- 圆点直径：默认 48vp

### 连接线
- 连接各个步骤的圆点
- 使用箭头或线条
- 可自定义颜色和宽度
- 箭头尺寸：11.4vp x 20vp

### 标签
- 可选的文字说明
- 可显示在每个圆点上方或下方
- 默认字体：10vp

## 导航控制

### 上一步按钮
- 第一步不显示上一步按钮
- 点击返回到上一步
- 可通过 prevLabel 自定义文本
- 默认文本：'Back'

### 下一步按钮
- 最后一步显示为"完成"
- 点击进入下一步或触发完成事件
- 可通过 nextLabel 自定义文本
- 默认文本：'Next'
- 受步骤状态影响（Disabled 状态禁用）

### 跳过功能
- 设置步骤状态为 Skip 时显示"跳过"按钮
- 点击跳过当前步骤
- 触发 onSkip 事件
- 跳过后可返回

## 事件流程

### 下一步点击流程
```
用户点击"下一步"
        │
        ▼
onNext 事件触发
        │
        ▼
检查当前步骤状态
        │
    ┌───┴───┐
    │         │
  Normal    Disabled/Skip
    │         │
    ▼         ▼
 允许进入  拒绝/跳过
    │
    ▼
onChange 事件触发
    │
    ▼
更新进度指示器
    │
    ▼
切换到新步骤内容
```

### 完成流程
```
用户在最后一步点击"完成"
        │
        ▼
onNext 事件触发
        │
        ▼
检查是否为最后一步
        │
        ▼
onFinish 事件触发
        │
        ▼
执行完成逻辑
```

## 步骤状态详解

### Normal (正常状态)
- 可以进入和离开
- 下一步按钮可用
- 上一步按钮可用（非第一步时）
- 进度指示器正常显示

### Disabled (禁用状态)
- 无法进入该步骤
- 下一步按钮禁用
- 进度指示器显示为禁用
- 适用于需要前置条件的场景

### Skip (跳过状态)
- 可以跳过该步骤
- 显示"跳过"按钮代替"下一步"
- 跳过后可返回
- 适用于可选步骤

## 注意事项

1. **子组件要求**：
   - Stepper 必须包含至少一个 StepperItem
   - 只能包含 StepperItem 作为直接子组件
   - StepperItem 内可以包含任意内容
   - 建议在 StepperItem 内使用容器（如 Column）

2. **步骤状态**：
   - Normal: 正常状态，可以进入和离开
   - Disabled: 禁用状态，无法进入
   - Skip: 跳过状态，显示跳过按钮

3. **按钮文本**：
   - 第一步的 prevLabel 不会显示（没有上一步按钮）
   - 最后一步建议将 nextLabel 设为"完成"
   - 建议根据上下文提供有意义的按钮文本
   - 文本长度建议控制在 2-4 个字符

4. **性能考虑**：
   - 所有步骤的内容都会被创建，即使未显示
   - 对于复杂内容，考虑使用 if 条件渲染
   - 避免在单个步骤中放置过多内容
   - 建议每个步骤保持轻量化

5. **事件处理**：
   - onFinish 在最后一步点击完成时触发
   - onSkip 在点击跳过按钮时触发
   - onChange 在步骤切换后触发，已到达新步骤
   - onNext/onPrevious 在点击按钮时立即触发，可能不会切换

6. **无障碍支持**：
   - Stepper 支持无障碍属性
   - 确保为屏幕阅读器提供合适的标签
   - 进度信息会自动通报给辅助技术
   - 按钮需要有正确的焦点顺序

7. **焦点管理**：
   - Stepper 作为焦点作用域
   - 支持键盘导航
   - 焦点在步骤内容和控制按钮间循环
   - 禁用状态不会获得焦点

8. **主题适配**：
   - 支持跟随系统主题变化
   - 颜色会根据主题自动调整
   - 注意深色/浅色模式的适配

9. **布局建议**：
   - 步骤内容建议使用固定高度确保一致性
   - 使用 padding 确保内容不贴边
   - 考虑横竖屏切换时的布局适配

10. **国际化考虑**：
   - 按钮文本需要支持多语言
   - RTL 语言环境自动镜像布局
   - 文本长度考虑不同语言的差异

11. **状态管理**：
   - 使用 @State 管理当前步骤索引
   - 通过 onChange 回调更新步骤状态
   - 避免直接操作 DOM 进行步骤切换

12. **动画效果**：
   - 步骤切换有平滑过渡动画
   - 进度指示器有状态变化动画
   - 可以自定义禁用状态的视觉反馈
