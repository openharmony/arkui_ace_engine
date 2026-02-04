# ArkUI 组件 API 知识库

> **文档说明**: 本文档位于 ace_engine 仓库，分析 OpenHarmony 组件 API (`@internal/component/ets`) 的类型定义结构和组织方式。组件 API 定义文件位于 `OpenHarmony/interface/sdk-js/api/@internal/component/ets/`，用于 ArkUI 框架组件类型声明和接口定义。

**API 版本**: API 7 - API 23
**组件 API 路径**: `OpenHarmony/interface/sdk-js/api/@internal/component/ets/`
**相关实现路径**: `OpenHarmony/foundation/arkui/ace_engine/`

---

## Claude 参考指南

### 文档用途
本文档是 Claude 的内部参考知识库，用于：
1. **理解组件 API 结构** - 了解 ArkUI 框架的组件类型定义组织方式
2. **区分公开与组件 API** - 理解 `@internal` 与公开 `arkui/` API 的区别
3. **类型定义快速查询** - 快速定位组件和接口的类型定义文件
4. **版本兼容性参考** - 查询 API 从哪个版本开始支持

### 如何使用此知识库

#### 场景 1: 查找组件内部类型定义
```
用户问题: "Text 组件的内部接口定义在哪里？"
查找步骤:
1. 在"3. 组件 API 分类清单"中找到 Text 组件
2. 查看文件路径: text.d.ts
3. 完整路径: OpenHarmony/interface/sdk-js/api/@internal/component/ets/text.d.ts
4. 对比公开 API: OpenHarmony/interface/sdk-js/api/arkui/component/text.static.d.ets
```

#### 场景 2: 理解公开 API 与组件 API 的关系
```
用户问题: "公开 API 和组件 API 有什么区别？"
查找步骤:
1. 查看"2. 公开 API vs 组件 API"章节
2. 理解目录结构和用途差异
3. 查看"5. 类型定义规范"了解标签含义
```

#### 场景 3: 查询 API 版本支持
```
用户问题: "某个接口从哪个 API 版本开始支持？"
查找步骤:
1. 打开对应的 .d.ts 文件
2. 查看 @since 标签（如 @since 11）
3. 参考本文档的"5. 类型定义规范"
```

### 快速查找指南

| 想查找什么 | 跳转到章节 |
|-----------|-----------|
| 所有组件列表 | 第 3 章 "组件 API 分类清单" |
| 公开 vs 组件 API | 第 2 章 "公开 API vs 组件 API" |
| 文件统计信息 | 第 1 章 "概述" |
| 类型定义规范 | 第 5 章 "类型定义规范" |
| 特殊文件说明 | 第 4 章 "特殊文件说明" |

---

## 1. 概述

### 1.1 组件 API 定位

**组件 API** (`@internal/component/ets/`) 是 OpenHarmony ArkUI 框架的组件类型定义集合，用于：

- **框架类型声明** - ArkTS 编译器和运行时使用的类型
- **组件接口定义** - 定义组件的实现接口和属性类型
- **辅助类型定义** - 通用类型、枚举、工具接口等
- **版本兼容性管理** - 通过 `@since`、`@crossplatform` 等标签管理 API 演进

### 1.2 与公开 API 的区别

| 特性 | 公开 API (`arkui/`) | 组件 API (`@internal/`) |
|------|---------------------|------------------------|
| **目录位置** | `OpenHarmony/interface/sdk-js/api/arkui/` | `OpenHarmony/interface/sdk-js/api/@internal/component/ets/` |
| **文件类型** | `.static.d.ets` (Static API) + `*.d.ts` (Dynamic API) | `.d.ts` (类型定义) |
| **使用场景** | 开发者应用代码 | ArkUI 框架内部 |
| **API 稳定性** | 向后兼容，严格版本管理 | 可能变更，框架内部使用 |
| **文档完整性** | 完整的 JSDoc 和使用说明 | 简化注释，主要用于类型检查 |
| **示例代码** | 包含 | 通常不包含 |

### 1.3 代码规模统计

| 统计项 | 数量 |
|--------|------|
| **总文件数** | 137 个 `.d.ts` 文件 |
| **总代码行数** | 184,823 行 |
| **组件类型定义** | 120+ 个 |
| **基础组件** | 15 个 |
| **容器组件** | 27 个 |
| **选择器组件** | 8 个 |
| **形状组件** | 7 个 |
| **媒体组件** | 4 个 |
| **数据展示组件** | 7 个 |
| **富文本组件** | 4 个 |
| **弹窗菜单组件** | 9 个 |
| **高级组件** | 20+ 个 |
| **辅助类型文件** | 17 个 |

---

## 2. 公开 API vs 组件 API

### 2.1 目录结构对比

```
OpenHarmony/interface/sdk-js/api/
├── arkui/                          # 公开 API（开发者使用）
│   ├── component/                  # Static API - 声明式组件
│   │   ├── button.static.d.ets
│   │   ├── text.static.d.ets
│   │   └── ...
│   ├── ButtonModifier.d.ts         # Dynamic API - 命令式修饰器
│   ├── TextModifier.d.ts
│   ├── FrameNode.d.ts              # 核心 Node API
│   ├── BuilderNode.d.ts
│   └── ...
└── @internal/
    └── component/
        └── ets/                    # 组件 API（框架内部使用）
            ├── button.d.ts         # 组件接口定义
            ├── text.d.ts
            ├── common.d.ts         # 通用类型定义
            ├── enums.d.ts          # 枚举定义
            └── ...
```

### 2.2 文件命名对比

| 组件 | 公开 API (Static) | 公开 API (Dynamic) | 组件 API |
|------|-------------------|-------------------|---------|
| Button | `button.static.d.ets` | `ButtonModifier.d.ts` | `button.d.ts` |
| Text | `text.static.d.ets` | `TextModifier.d.ts` | `text.d.ts` |
| List | `list.static.d.ets` | `ListModifier.d.ts` | `list.d.ts` |
| Grid | `grid.static.d.ets` | `GridModifier.d.ts` | `grid.d.ts` |

### 2.3 内容对比示例

#### 公开 API: text.static.d.ets
```typescript
/**
 * Provides a text component.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 7
 */
declare class Text {
  /**
   * Text content.
   *
   * @type { string | Resource }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 7
   */
  content: string | Resource;

  /**
   * Creates a text component.
   *
   * @param { string | Resource } content - Text content.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 7
   */
  constructor(content: string | Resource);

  // ... 公开 API 方法
}
```

#### 组件 API: text.d.ts
```typescript
/**
 * Text overflow options.
 *
 * @interface TextOverflowOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 18 dynamic
 */
declare interface TextOverflowOptions {
  /**
   * Text overflow option.
   * @type { TextOverflow }
   * @default TextOverflow.Clip
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 18 dynamic
   */
  overflow: TextOverflow;
}

/**
 * Provides an interface for writing texts.
 *
 * @interface TextInterface
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 7
 */
declare interface TextInterface {
  // ... 内部接口定义
}
```

### 2.4 使用场景对比

#### 公开 API 使用场景
```typescript
// 开发者应用代码
import { Text } from '@ohos.arkui'

@Entry
@Component
struct MyComponent {
  build() {
    Text('Hello World')
      .fontSize(20)
      .fontColor(Color.Red)
  }
}
```

#### 组件 API 使用场景
```typescript
// ArkUI 框架内部代码
import type { TextInterface } from '@internal/component/ets'

// 框架内部实现使用内部类型定义
class TextPatternImpl implements TextInterface {
  // ... 框架内部实现
}
```

---

## 3. 组件 API 分类清单

### 3.1 基础组件 (15 个)

| 组件名 | 组件 API 文件 | 对应公开 API | 功能说明 |
|--------|-------------|-------------|----------|
| **Text** | text.d.ts | text.static.d.ets | 文本显示 |
| **Image** | image.d.ts | image.static.d.ets | 图片显示 |
| **TextInput** | text_input.d.ts | textInput.static.d.ets | 文本输入 |
| **TextArea** | text_area.d.ts | textArea.static.d.ets | 多行文本输入 |
| **Button** | button.d.ts | button.static.d.ets | 按钮 |
| **Toggle** | toggle.d.ts | toggle.static.d.ets | 开关 |
| **Checkbox** | checkbox.d.ts | checkbox.static.d.ets | 复选框 |
| **Radio** | radio.d.ts | radio.static.d.ets | 单选框 |
| **Slider** | slider.d.ts | slider.static.d.ets | 滑块 |
| **Progress** | progress.d.ts | progress.static.d.ets | 进度条 |
| **LoadingProgress** | loading_progress.d.ts | loadingProgress.static.d.ets | 加载进度 |
| **Divider** | divider.d.ts | divider.static.d.ets | 分割线 |
| **Blank** | blank.d.ts | blank.static.d.ets | 空白占位 |
| **Span** | span.d.ts | span.static.d.ets | 文本片段 |
| **ImageSpan** | image_span.d.ts | imageSpan.static.d.ets | 图片片段 |

### 3.2 容器组件 (27 个)

| 组件名 | 组件 API 文件 | 对应公开 API | 功能说明 |
|--------|-------------|-------------|----------|
| **Column** | column.d.ts | column.static.d.ets | 纵向布局 |
| **Row** | row.d.ts | row.static.d.ets | 横向布局 |
| **Stack** | stack.d.ts | stack.static.d.ets | 堆叠布局 |
| **Flex** | flex.d.ts | flex.static.d.ets | 弹性布局 |
| **Grid** | grid.d.ts | grid.static.d.ets | 网格布局 |
| **GridRow** | grid_row.d.ts | gridRow.static.d.ets | 栅格行容器 |
| **GridCol** | grid_col.d.ts | gridCol.static.d.ets | 栅格列容器 |
| **GridItem** | gridItem.d.ts | gridItem.static.d.ets | 栅格子项 |
| **List** | list.d.ts | list.static.d.ets | 列表 |
| **ListItem** | list_item.d.ts | listItem.static.d.ets | 列表项 |
| **ListItemGroup** | list_item_group.d.ts | listItemGroup.static.d.ets | 列表分组 |
| **Scroll** | scroll.d.ts | scroll.static.d.ets | 滚动容器 |
| **Swiper** | swiper.d.ts | swiper.static.d.ets | 轮播容器 |
| **Tabs** | tabs.d.ts | tabs.static.d.ets | 标签页容器 |
| **TabContent** | tab_content.d.ts | tabContent.static.d.ets | 标签页内容 |
| **Navigator** | navigator.d.ts | navigator.static.d.ets | 导航容器 |
| **NavRouter** | nav_router.d.ts | navRouter.static.d.ets | 路由导航 |
| **Navigation** | navigation.d.ts | navigation.static.d.ets | 导航栏 |
| **NavDestination** | nav_destination.d.ts | navDestination.static.d.ets | 导航目标页 |
| **SideBarContainer** | sidebar.d.ts | sideBarContainer.static.d.ets | 侧边栏容器 |
| **Refresh** | refresh.d.ts | refresh.static.d.ets | 下拉刷新 |
| **WaterFlow** | water_flow.d.ts | waterFlow.static.d.ets | 瀑布流 |
| **FlowItem** | flow_item.d.ts | flowItem.static.d.ets | 瀑布流子项 |
| **RelativeContainer** | relative_container.d.ts | relativeContainer.static.d.ets | 相对布局容器 |
| **ColumnSplit** | column_split.d.ts | columnSplit.static.d.ets | 纵向分割容器 |
| **RowSplit** | row_split.d.ts | rowSplit.static.d.ets | 横向分割容器 |
| **FolderStack** | folder_stack.d.ts | folderStack.static.d.ets | 文件夹堆叠 |

### 3.3 选择器组件 (8 个)

| 组件名 | 组件 API 文件 | 对应公开 API | 功能说明 |
|--------|-------------|-------------|----------|
| **Select** | select.d.ts | select.static.d.ets | 下拉选择 |
| **DatePicker** | date_picker.d.ts | datePicker.static.d.ets | 日期选择器 |
| **TimePicker** | time_picker.d.ts | timePicker.static.d.ets | 时间选择器 |
| **TextPicker** | text_picker.d.ts | textPicker.static.d.ets | 文本选择器 |
| **CalendarPicker** | calendar_picker.d.ts | calendarPicker.static.d.ets | 日历选择器 |
| **CheckboxGroup** | checkboxgroup.d.ts | checkboxgroup.static.d.ets | 复选框组 |
| **Rating** | rating.d.ts | rating.static.d.ets | 评分组件 |
| **UIPickerComponent** | ui_picker_component.d.ts | uiPickerComponent.static.d.ets | UI 选择器 |

### 3.4 形状组件 (7 个)

| 组件名 | 组件 API 文件 | 对应公开 API | 功能说明 |
|--------|-------------|-------------|----------|
| **Rect** | rect.d.ts | rect.static.d.ets | 矩形 |
| **Circle** | circle.d.ts | circle.static.d.ets | 圆形 |
| **Ellipse** | ellipse.d.ts | ellipse.static.d.ets | 椭圆 |
| **Path** | path.d.ts | path.static.d.ets | 路径 |
| **Polyline** | polyline.d.ts | polyline.static.d.ets | 折线 |
| **Polygon** | polygon.d.ts | polygon.static.d.ets | 多边形 |
| **Shape** | shape.d.ts | shape.static.d.ets | 形状 |

### 3.5 媒体组件 (4 个)

| 组件名 | 组件 API 文件 | 对应公开 API | 功能说明 |
|--------|-------------|-------------|----------|
| **Video** | video.d.ts | video.static.d.ets | 视频播放器 |
| **ImageAnimator** | image_animator.d.ts | imageAnimator.static.d.ets | 帧动画 |
| **Canvas** | canvas.d.ts | canvas.static.d.ets | 画布 |
| **XComponent** | xcomponent.d.ts | xcomponent.static.d.ets | 原生组件容器 |

### 3.6 数据展示组件 (7 个)

| 组件名 | 组件 API 文件 | 对应公开 API | 功能说明 |
|--------|-------------|-------------|----------|
| **TextClock** | text_clock.d.ts | textClock.static.d.ets | 文本时钟 |
| **DataPanel** | data_panel.d.ts | dataPanel.static.d.ets | 数据面板 |
| **Gauge** | gauge.d.ts | gauge.static.d.ets | 仪表盘 |
| **QRCode** | qrcode.d.ts | qrcode.static.d.ets | 二维码 |
| **AlphabetIndexer** | alphabet_indexer.d.ts | alphabetIndexer.static.d.ets | 字母索引 |
| **Counter** | counter.d.ts | counter.static.d.ets | 计数器 |
| **Marquee** | marquee.d.ts | marquee.static.d.ets | 跑马灯 |

### 3.7 富文本组件 (4 个)

| 组件名 | 组件 API 文件 | 对应公开 API | 功能说明 |
|--------|-------------|-------------|----------|
| **RichEditor** | rich_editor.d.ts | richEditor.static.d.ets | 富文本编辑器 |
| **ContainerSpan** | container_span.d.ts | containerSpan.static.d.ets | 容器片段 |
| **StyledString** | styled_string.d.ts | styledString.static.d.ets | 样式字符串 |
| **RichText** | rich_text.d.ts | richText.static.d.ets | 富文本 |
| **Hyperlink** | hyperlink.d.ts | hyperlink.static.d.ets | 超链接 |

### 3.8 弹窗和菜单组件 (9 个)

| 组件名 | 组件 API 文件 | 对应公开 API | 功能说明 |
|--------|-------------|-------------|----------|
| **AlertDialog** | alert_dialog.d.ts | alertDialog.static.d.ets | 警告对话框 |
| **ActionSheet** | action_sheet.d.ts | actionSheet.static.d.ets | 操作列表 |
| **Menu** | menu.d.ts | menu.static.d.ets | 菜单 |
| **MenuItem** | menu_item.d.ts | menuItem.static.d.ets | 菜单项 |
| **MenuItemGroup** | menu_item_group.d.ts | menu_item_group.d.ts | 菜单项组 |
| **ContextMenu** | context_menu.d.ts | contextMenu.static.d.ets | 上下文菜单 |
| **CustomDialogController** | custom_dialog_controller.d.ts | customDialogController.static.d.ets | 自定义对话框控制器 |
| **Panel** | panel.d.ts | panel.static.d.ets | 半屏弹窗 |
| **BindSheet** | - | bindSheet (高级 API) | 半模态转场 |

### 3.9 高级组件 (20+ 个)

| 组件名 | 组件 API 文件 | 对应公开 API | 功能说明 |
|--------|-------------|-------------|----------|
| **Web** | web.d.ts | web.static.d.ets | Web 浏览器 |
| **FormComponent** | form_component.d.ts | formComponent.static.d.ets | 表单组件 |
| **PatternLock** | pattern_lock.d.ts | patternLock.static.d.ets | 图案锁 |
| **Stepper** | stepper.d.ts | stepper.static.d.ets | 步骤条 |
| **StepperItem** | stepper_item.d.ts | - | 步骤条项 |
| **Search** | search.d.ts | search.static.d.ets | 搜索框 |
| **ContentSlot** | content_slot.d.ts | contentSlot.static.d.ets | 内容插槽 |
| **GridContainer** | grid_container.d.ts | gridContainer.static.d.ets | 栅格容器 |
| **PluginComponent** | plugin_component.d.ts | pluginComponent.static.d.ets | 插件组件 |
| **RemoteWindow** | remote_window.d.ts | remoteWindow.static.d.ets | 远程窗口 |
| **UIExtensionComponent** | ui_extension_component.d.ts | uiExtensionComponent.static.d.ets | UI 扩展组件 |
| **EmbeddedComponent** | embedded_component.d.ts | embeddedComponent.static.d.ets | 嵌入式组件 |
| **EffectComponent** | effect_component.d.ts | effectComponent.static.d.ets | 效果组件 |
| **Component3D** | component3d.d.ts | component3d.static.d.ets | 3D 组件 |
| **SecurityComponent** | security_component.d.ts | securityComponent.static.d.ets | 安全组件 |
| **SymbolGlyph** | symbolglyph.d.ts | symbolglyph.static.d.ets | 符号图标 |
| **SymbolSpan** | symbol_span.d.ts | symbolSpan.static.d.ets | 符号片段 |
| **Particle** | particle.d.ts | particle.static.d.ets | 粒子效果 |
| **PasteButton** | paste_button.d.ts | pasteButton.static.d.ets | 粘贴按钮 |
| **SaveButton** | save_button.d.ts | saveButton.static.d.ets | 保存按钮 |
| **AbilityComponent** | ability_component.d.ts | abilityComponent.static.d.ets | 能力组件 |
| **IsolatedComponent** | isolated_component.d.ts | isolatedComponent.static.d.ets | 隔离组件 |
| **NodeContainer** | node_container.d.ts | nodeContainer.static.d.ets | 节点容器 |

### 3.10 语法和控制流组件 (5 个)

| 组件名 | 组件 API 文件 | 对应公开 API | 功能说明 |
|--------|-------------|-------------|----------|
| **ForEach** | for_each.d.ts | forEach.static.d.ets | 循环渲染 |
| **LazyForEach** | lazy_for_each.d.ts | - | 懒加载循环渲染 |
| **Repeat** | repeat.d.ts | repeat.static.d.ets | 重复渲染 |
| **If/Else** | - | if.static.d.ets | 条件渲染 |
| **WithTheme** | with_theme.d.ts | withTheme.static.d.ets | 主题作用域 |

---

## 4. 特殊文件说明

### 4.1 通用类型文件

| 文件名 | 功能说明 | 主要内容 |
|--------|----------|----------|
| **common.d.ts** | 通用类型定义 | ComponentOptions、InputCounterOptions、TextDecorationOptions 等 |
| **enums.d.ts** | 枚举类型定义 | 所有组件使用的枚举类型 |
| **units.d.ts** | 单位类型定义 | LengthMetrics、ColorMetrics 等 |
| **gesture.d.ts** | 手势类型定义 | 点击、滑动、长按等手势接口 |
| **focus.d.ts** | 焦点控制类型 | FocusInfo、FocusScope 等 |
| **animator.d.ts** | 动画类型定义 | 动画接口和属性 |
| **screen.d.ts** | 屏幕信息类型 | 屏幕尺寸、密度等 |
| **lifecycle.d.ts** | 生命周期类型 | 组件生命周期回调接口 |

### 4.2 通用 API 文件

| 文件名 | 功能说明 | 主要内容 |
|--------|----------|----------|
| **common_ts_ets_api.d.ts** | TS/ETS 通用 API | 跨语言接口定义 |
| **state_management.d.ts** | 状态管理类型 | 状态相关接口定义 |
| **index-full.d.ts** | 完整索引 | 导出所有类型定义 |

### 4.3 组件相关辅助文件

| 文件名 | 功能说明 |
|--------|----------|
| **image_common.d.ts** | 图片组件通用类型 |
| **text_common.d.ts** | 文本组件通用类型 |
| **matrix2d.d.ts** | 二维矩阵变换类型 |
| **lazy_grid_layout.d.ts** | 懒加载网格布局类型 |

### 4.4 系统组件文件

| 文件名 | 功能说明 |
|--------|----------|
| **root_scene.d.ts** | 根场景类型 |
| **window_scene.d.ts** | 窗口场景类型 |
| **inspector.d.ts** | 检查器类型 |
| **form_link.d.ts** | 卡片链接类型 |

### 4.5 高级特性文件

| 文件名 | 功能说明 |
|--------|----------|
| **page_transition.d.ts** | 页面转场类型 |
| **union_effect_container.d.ts** | 联合效果容器类型 |
| **media_cached_image.d.ts** | 媒体缓存图片类型 |

---

## 5. 类型定义规范

### 5.1 JSDoc 标签说明

#### 基本标签

| 标签 | 说明 | 示例 |
|------|------|------|
| `@file` | 文件说明 | `@file` |
| `@kit` | 所属套件 | `@kit ArkUI` |
| `@interface` | 接口定义 | `@interface TextInterface` |
| `@type` | 类型定义 | `@type { string }` |
| `@typedef` | 类型别名 | `@typedef { ... } CustomType` |
| `@default` | 默认值 | `@default 0` |
| `@syscap` | 系统能力 | `@syscap SystemCapability.ArkUI.ArkUI.Full` |

#### 版本标签

| 标签 | 说明 | 示例 |
|------|------|------|
| `@since` | 起始版本 | `@since 7` (从 API 7 开始支持) |
| `@deprecated` | 废弃版本 | `@deprecated 10` (在 API 10 废弃) |
| `@crossplatform` | 跨平台支持 | 支持跨平台运行 |
| `@form` | 支持卡片 | 支持服务卡片场景 |
| `@atomicservice` | 原子化服务 | 支持原子化服务 |

#### 版本号后缀说明

| 后缀 | 说明 | 示例 |
|------|------|------|
| `dynamic` | 动态导入 | `@since 18 dynamic` (从 API 18 开始，动态导入支持) |
| 无后缀 | 静态导入 | `@since 7` (从 API 7 开始，静态导入支持) |

### 5.2 类型定义示例

#### 接口定义
```typescript
/**
 * Defines the options of Component ClassDecorator.
 *
 * @interface ComponentOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @form
 * @since 11
 */
declare interface ComponentOptions {
  /**
   * freeze UI state.
   *
   * @type { boolean }
   * @default false
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @form
   * @since 11
   */
  freezeWhenInactive: boolean,
}
```

#### 类型别名
```typescript
/**
 * The type for SpringLoadingContext.
 *
 * @typedef {import('../api/@ohos.arkui.dragController').default.SpringLoadingContext} SpringLoadingContext
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 20 dynamic
 */
declare type SpringLoadingContext = import('../api/@ohos.arkui.dragController').default.SpringLoadingContext;
```

#### 可选属性
```typescript
declare interface InputCounterOptions {
  /**
   * Threshold percentage for displaying the character counter.
   * @type { ?number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @since 11
   */
  thresholdPercentage?: number;

  /**
   * Whether to highlight the text box border in red.
   * @type { ?boolean }
   * @default true
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @since 11
   */
  highlightBorder?: boolean;
}
```

### 5.3 版本兼容性处理

#### 多版本支持
```typescript
/**
 * Provides a button component.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 7
 */
/**
 * Provides a button component.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @form
 * @since 9
 */
/**
 * Provides a button component.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @form
 * @since 10
 */
/**
 * Provides a button component.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @form
 * @atomicservice
 * @since 11
 */
```

**说明**: 同一个接口可以有多个 `@since` 声明，表示在不同版本支持不同特性：
- `@since 7`: 基础功能
- `@form` (API 9): 支持卡片
- `@crossplatform` (API 10): 跨平台支持
- `@atomicservice` (API 11): 原子化服务支持

---

## 6. 文件组织结构

### 6.1 按字母顺序排列

所有 `.d.ts` 文件按字母顺序排列，便于快速查找：

```
ability_component.d.ts
action_sheet.d.ts
alert_dialog.d.ts
alphabet_indexer.d.ts
animator.d.ts
badge.d.ts
blank.d.ts
button.d.ts
...
```

### 6.2 导入关系

组件 API 文件之间存在导入关系：

```typescript
// common.d.ts 中导入其他模块的类型
declare type SpringLoadingContext = import('../api/@ohos.arkui.dragController').default.SpringLoadingContext;
```

导入路径模式：
- `import('../api/@ohos.arkui.xxx')` - 导入公开 API
- `import('./xxx')` - 导入同级组件 API

### 6.3 类型导出

部分文件通过 `index-full.d.ts` 统一导出：

```typescript
// index-full.d.ts 可能的结构
export * from './button'
export * from './text'
export * from './common'
// ... 其他导出
```

---

## 7. 使用指南

### 7.1 查找组件类型定义

**步骤**:
1. 确定组件名（如 `Text`）
2. 转换为文件名（小写，连字符连接：`text`）
3. 定位文件：`OpenHarmony/interface/sdk-js/api/@internal/component/ets/text.d.ts`

**示例**:
```
组件名: TextInput
文件名: text_input.d.ts
完整路径: OpenHarmony/interface/sdk-js/api/@internal/component/ets/text_input.d.ts
```

### 7.2 理解类型定义

**阅读顺序**:
1. 查看 `@interface` 或 `@type` 注释，了解定义类型
2. 查看属性列表，了解可用字段
3. 查看每个属性的 `@type` 和 `@default`，了解类型和默认值
4. 查看 `@since` 标签，了解版本要求

**示例**:
```typescript
/**
 * @interface InputCounterOptions
 * @since 11
 */
declare interface InputCounterOptions {
  thresholdPercentage?: number;  // 可选，百分比类型
  highlightBorder?: boolean;     // 可选，布尔类型
  // ...
}
```

### 7.3 版本兼容性检查

**方法**:
1. 查看接口定义的 `@since` 标签
2. 查看每个属性的 `@since` 标签
3. 检查是否有 `@deprecated` 标签

**示例**:
```typescript
/**
 * @interface TextInterface
 * @since 7
 */
declare interface TextInterface {
  /**
   * @since 7
   */
  content: string;

  /**
   * @since 10
   */
  textShadow?: ShadowOptions;

  /**
   * @since 18 dynamic
   */
  inlineStyle?: InlineStyleOptions;
}
```

**版本支持**:
- `content`: API 7+ 支持
- `textShadow`: API 10+ 支持
- `inlineStyle`: API 18+ 支持（动态导入）

---

## 8. 常见问题

### 8.1 公开 API 和组件 API 的关系

**Q**: 公开 API 和组件 API 是如何对应的？

**A**:
- **公开 API** (`arkui/`) 是开发者使用的接口，提供完整的组件类和修饰器
- **组件 API** (`@internal/`) 是框架内部的类型定义，提供接口定义和类型约束
- **公开 API 的实现**依赖组件 API 的类型定义

### 8.2 为什么需要组件 API

**Q**: 为什么不把所有类型定义都放在公开 API 中？

**A**:
1. **减少公开接口复杂度** - 开发者不需要了解所有内部类型
2. **框架灵活性** - 组件 API 可以根据框架演进调整
3. **类型安全** - 框架内部有更严格的类型约束
4. **性能优化** - 组件 API 可以使用更高效的类型定义方式

### 8.3 如何判断 API 稳定性

**Q**: 如何判断某个组件 API 是否稳定？

**A**:
1. 查看 `@since` 标签，版本越久越稳定
2. 查看是否有 `@deprecated` 标签
3. 查看是否有 `@crossplatform`、`@form` 等标签，标签越多说明支持越广泛
4. 参考公开 API，如果公开 API 中有对应接口，说明该类型是稳定的

### 8.4 动态导入是什么

**Q**: `@since 18 dynamic` 中的 `dynamic` 是什么意思？

**A**:
- **动态导入** - 指该类型仅在运行时按需加载
- **静态导入** - 指该类型在编译时静态链接
- `dynamic` 后缀从 API 18 开始引入，用于优化包体积和加载性能

---

## 9. 总结

### 9.1 关键特点

| 特点 | 说明 |
|------|------|
| **文件数量** | 137 个 `.d.ts` 文件 |
| **代码规模** | 184,823 行类型定义 |
| **组件覆盖** | 120+ 个组件类型定义 |
| **版本范围** | API 7 - API 23 |
| **标签体系** | `@since`、`@crossplatform`、`@form`、`@atomicservice` |
| **组织方式** | 按字母顺序排列，便于查找 |

### 9.2 与公开 API 的关系

```
公开 API (arkui/)
├── Static API (.static.d.ets)  ← 开发者使用
│   ↓ 实现
├── Dynamic API (*.d.ts)       ← 命令式操作
│   ↓ 类型约束
└── 组件 API (@internal/)       ← 框架内部使用
    └── 类型定义和接口约束
```

### 9.3 使用建议

1. **开发者** - 主要使用公开 API (`arkui/`)
2. **框架开发者** - 可能需要参考组件 API (`@internal/`)
3. **类型问题排查** - 同时查看公开 API 和组件 API
4. **版本兼容性** - 通过 `@since` 标签判断 API 支持情况

---

**文档维护**: 本文档应随着组件 API 的演进定期更新。

**相关资源**:
- [ArkUI SDK API 知识库](./ArkUI_SDK_API_Knowledge_Base.md) - 公开 SDK API 完整分析
- [knowledge_base_INDEX.json](./knowledge_base_INDEX.json) - 知识库元数据索引
- [OpenHarmony/interface/sdk-js/api/](OpenHarmony/interface/sdk-js/api/) - SDK API 目录
