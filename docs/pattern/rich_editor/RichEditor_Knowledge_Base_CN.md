# RichEditor 富文本编辑器组件完整知识库

> **文档版本**：v1.0
> **更新时间**：2026-04-18
> **源码版本**：OpenHarmony ace_engine (master 分支)

---

## 📚 目录

1. [概述](#概述)
2. [目录结构](#目录结构)
3. [核心类继承关系](#核心类继承关系)
4. [Pattern层详解](#pattern层详解)
5. [Model层详解](#model层详解)
6. [功能模块](#功能模块)
7. [使用示例](#使用示例)
8. [编码规范](#编码规范)
9. [接口扩展开发指南](#接口扩展开发指南)
10. [相关资源](#相关资源)

---

## 概述

### 组件定位

**RichEditor 组件**（`RichEditorPattern`）又名富文本组件，是一个富文本编辑器，扩展了 TextPattern 并提供完整的编辑功能。

### 核心功能

| 功能类别 | 具体功能 |
|---------|---------|
| **内容类型** | 复杂样式文本、图片、Symbol图标、自定义Builder |
| **编辑功能** | 撤销/重做、光标管理、IME输入、文本选择 |
| **交互功能** | 文本选择菜单、内容滚动、拖拽、长按 |
| **配置功能** | 字符数限制、行数限制、光标/手柄/滚动条颜色、单行模式 |
| **高级功能** | 无障碍支持、实体识别、URL跳转 |

### 技术架构

```
┌─────────────────────────────────────────────────────────┐
│  应用层 (ArkTS)                                           │
│  RichEditor({ controller: this.controller })             │
│  .onReady(() => { })                                      │
│  .onWillChange((value) => { return true; })              │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  桥接层 (Bridge Layer)                                    │
│  JSRichEditorController / JSRichEditorStyledStringController │
│  RichEditorBridge::SetXXX / ResetXXX                     │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  Model层 (ModelNG Layer)                                  │
│  RichEditorModelNG                                        │
│  RichEditorControllerBase                                 │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  核心层 (Pattern Layer)                                   │
│  RichEditorPattern (多重继承)                             │
│  ├── TextilePattern (基类 - 文本渲染)                     │
│  ├── ScrollablePattern (滚动支持)                         │
│  ├── TextInputClient (IME 输入接口)                       │
│  └── SpanWatcher (span 变更通知)                          │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  布局层 (LayoutAlgorithm Layer)                           │
│  RichEditorLayoutAlgorithm                                │
│  ├── Paragraph管理 (libtxt-typography + Skia)            │
│  ├── 段落缓存机制 (LRU Cache)                             │
│  └── 多段落布局 (MultipleParagraphLayoutAlgorithm)       │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│  渲染层 (Render Layer)                                    │
│  RichEditorContentModifier / RichEditorPaintMethod       │
│  Rosen + Skia 渲染                                        │
└─────────────────────────────────────────────────────────┘
```

### 代码规模

| 项目 | 数量 |
|-----|------|
| 核心文件 | 约 50 个文件 |
| 核心代码 | 约 20,000+ 行 C++ 代码 |
| Pattern文件 | rich_editor_pattern.h/cpp |
| Controller文件 | rich_editor_controller.h/cpp, rich_editor_styled_string_controller.h/cpp |
| 布局文件 | rich_editor_layout_algorithm.h/cpp |

### 模式分类

RichEditor 支持两种模式：

1. **老框架模式**：绑定 `RichEditorController`，使用 `std::list<RefPtr<NG::SpanItem>>` 处理简单内容
2. **属性字符串模式**：绑定 `RichEditorStyledStringController`，使用 `MutableSpanString` 处理带样式的富内容

在 `RichEditorPattern` 中通过 `isSpanStringMode_` 标志位区分。

---

## 目录结构

```
components_ng/pattern/rich_editor/
├── rich_editor_pattern.h/cpp              # 主 pattern 实现
├── rich_editor_controller.h/cpp           # 公共 API 控制器
├── rich_editor_styled_string_controller.h/cpp  # StyledString 控制器
├── rich_editor_base_controller.h/cpp      # 基础控制器
├── rich_editor_layout_property.h/cpp      # 布局属性
├── rich_editor_layout_algorithm.h/cpp     # 布局算法
├── rich_editor_event_hub.h/cpp            # 事件中心
├── rich_editor_undo_manager.h/cpp         # 撤销/重做管理器
├── rich_editor_paragraph_manager.h        # 段落管理
├── rich_editor_select_overlay.h/cpp       # 选择手柄逻辑
├── rich_editor_content_modifier.h/cpp     # 内容修饰符
├── rich_editor_paint_method.h/cpp         # 绘制方法
├── rich_editor_overlay_modifier.h/cpp     # 覆盖层修饰符
├── rich_editor_scroll_controller.h        # 滚动控制器
├── rich_editor_utils.h                    # 工具函数
├── rich_editor_theme.h                    # 主题定义
├── rich_editor_accessibility_property.h/cpp  # 无障碍属性
├── rich_editor_model.h                    # Model 接口
├── rich_editor_model_ng.h/cpp             # NG model 实现
├── rich_editor_model_static.h/cpp         # 静态 model 实现
├── bridge/                                # ArkTS 桥接层
│   ├── rich_editor_dynamic_modifier.cpp
│   ├── rich_editor_static_modifier.cpp
│   └── rich_editor_dynamic_module.h/cpp
├── rich_editor_drag/                      # 拖拽相关
│   ├── rich_editor_drag_pattern.h/cpp
│   ├── rich_editor_drag_paint_method.h/cpp
│   └── rich_editor_drag_overlay_modifier.h/cpp
└── docs/                                  # 开发文档
    ├── overview.md                        # 组件概述
    ├── core-flows.md                      # 核心流程
    ├── parameter-parsing.md               # 参数解析规范
    ├── data-structures.md                 # 数据结构
    ├── content-management.md              # 内容管理
    ├── layout-system.md                   # 布局系统
    ├── features.md                        # 功能模块
    ├── callbacks-guide.md                 # 回调函数指南
    ├── coding-standards.md                # 编码规范
    ├── best-practices.md                  # 最佳实践
    └── resources.md                       # 相关资源
```

---

## 核心类继承关系

### RichEditorPattern 类层次结构

```
                        Pattern (基类)
                           ↑
                    TextilePattern
              (文本渲染基类)
                           ↑
                    RichEditorPattern
             (rich_editor_pattern.h)
                           ↑
        +------------------+------------------+
        |                  |                  |
  ScrollablePattern   TextInputClient    SpanWatcher
    (滚动支持)        (IME 输入接口)     (span 变更通知)
```

### Controller 类层次结构

```
                        Referenced (引用计数基类)
                           ↑
                JSRichEditorBaseController
                           ↑
              JSRichEditorBaseControllerBinding
                           ↑
        +------------------+------------------+
        |                                     |
  JSRichEditorController           JSRichEditorStyledStringController
    (老框架模式)                      (属性字符串模式)
```

### 布局算法继承体系

```
LayoutAlgorithm (基类 - 定义 Measure/Layout 接口)
    ↓
BoxLayoutAlgorithm (盒模型布局算法)
    ↓
MultipleParagraphLayoutAlgorithm (多段落文本布局算法)
    ↓
RichEditorLayoutAlgorithm (RichEditor 专用布局算法)
```

---

## Pattern层详解

### RichEditorPattern 类

**位置**：`frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h`

**核心成员变量**：

| 变量 | 类型 | 说明 |
|-----|------|------|
| `spans_` | std::list\<RefPtr\<SpanItem\>\> | Span项列表（老框架模式） |
| `styledString_` | RefPtr\<MutableSpanString\> | 样式化字符串（属性字符串模式） |
| `isSpanStringMode_` | bool | 是否为属性字符串模式 |
| `undoManager_` | RefPtr\<RichEditorUndoManager\> | 撤销/重做管理器 |
| `paragraphs_` | ParagraphManager | 段落管理器 |
| `paragraphCache_` | LRUMap | 段落缓存 |
| `caretPosition_` | int32_t | 光标位置 |
| `textSelector_` | TextSelector | 文本选择器 |
| `scrollController_` | RichEditorScrollController | 滚动控制器 |
| `contentMod_` | RefPtr\<RichEditorContentModifier\> | 内容修饰器 |
| `overlayMod_` | RefPtr\<RichEditorOverlayModifier\> | 覆盖层修饰器 |

**核心方法**：

| 方法 | 功能 |
|-----|------|
| `OnAttachToFrameNode()` | 附加到节点树 |
| `OnDetachFromFrameNode()` | 从节点树分离 |
| `OnModifyDone()` | 修改完成回调 |
| `BeforeCreateLayoutWrapper()` | 创建布局包装器前处理 |
| `CreateLayoutAlgorithm()` | 创建布局算法 |
| `OnDirtyLayoutWrapperSwap()` | 布局完成后处理 |
| `AddTextSpan()` | 添加文本Span |
| `AddImageSpan()` | 添加图片Span |
| `AddSymbolSpan()` | 添加符号Span |
| `DeleteSpans()` | 删除Span |
| `SetCaretPosition()` | 设置光标位置 |
| `SetSelection()` | 设置选择范围 |
| `HandleOnUndoAction()` | 处理撤销 |
| `HandleOnRedoAction()` | 处理重做 |

### BeforeCreateLayoutWrapper()

**调用时机**：在创建 LayoutWrapper 之前，每次布局计算前调用

**功能**：
- 老框架模式：从节点树重新构建 `spans_` 列表，检查 URL span
- 属性字符串模式：通知内容修饰符内容已变更

### CreateLayoutAlgorithm()

**调用时机**：
1. UpdateLayoutWrapper 阶段 - 当组件需要重新测量或重新布局时
2. GetLayoutAlgorithm 阶段 - 当 layoutAlgorithm_ 为空或过期时

**功能**：
1. HandleSysScaleChanged() - 检查系统缩放是否变化
2. 创建 RichEditorLayoutAlgorithm 实例

### OnDirtyLayoutWrapperSwap()

**调用时机**：在布局完成后，每次 Measure/Layout 完成后调用

**功能**：
- 更新 frameRect_ 和 parentOffset
- 更新 richTextRect_
- 更新 TextFieldManager
- 更新滚动状态
- 更新放大镜状态
- 触发 onReady 事件（首次布局）
- 移动光标
- 处理选择覆盖层
- 更新手势热区

---

## Model层详解

### RichEditorModelNG 类

**位置**：`frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.h`

**核心创建方法**：

| 方法 | 功能 |
|-----|------|
| `Create()` | 创建 RichEditor FrameNode |
| `SetController()` | 设置控制器 |
| `SetStyledStringController()` | 设置 StyledString 控制器 |

### Controller 类层次结构

**JSRichEditorBaseController** - 基础控制器类：
- `SetController(controller)` - 设置控制器
- `CloseSelectionMenu()` - 关闭选择菜单
- `StopEditing()` - 停止编辑
- `SetStyledStringMode(isStyledStringMode)` - 设置模式

**JSRichEditorController** - 老框架模式控制器：
- `AddTextSpan(args)` - 添加文本Span
- `AddImageSpan(args)` - 添加图片Span
- `AddSymbolSpan(args)` - 添加符号Span
- `DeleteSpans(args)` - 删除Span
- `GetSpansInfo(args)` - 获取Span信息
- `UpdateSpanStyle(info)` - 更新Span样式

**JSRichEditorStyledStringController** - 属性字符串模式控制器：
- `SetStyledString(args)` - 设置StyledString
- `GetStyledString(args)` - 获取StyledString
- `GetSelection(args)` - 获取选择范围

---

## 功能模块

### 光标管理

| 方法 | 功能 |
|-----|------|
| `SetCaretPosition(position)` | 设置光标位置 |
| `GetCaretPosition()` | 获取光标位置 |
| `SetCaretPositionWithAffinity()` | 设置光标位置（带亲和性） |
| `ShowCaret()` | 显示光标 |
| `HideCaret()` | 隐藏光标 |
| `IsCaretVisible()` | 检查光标是否可见 |

### 选择管理

| 方法 | 功能 |
|-----|------|
| `SetSelection(start, end)` | 设置选择范围 |
| `GetSelector()` | 获取选择器 |
| `ClearSelection()` | 清除选择 |
| `ShowSelectOverlay()` | 显示选择覆盖层 |
| `HideSelectOverlay()` | 隐藏选择覆盖层 |

### 撤销/重做

| 方法 | 功能 |
|-----|------|
| `HandleOnUndoAction()` | 处理撤销 |
| `HandleOnRedoAction()` | 处理重做 |
| `CanUndo()` | 检查是否可撤销 |
| `CanRedo()` | 检查是否可重做 |
| `ClearUndoRedo()` | 清空撤销/重做记录 |

### IME 输入

| 方法 | 功能 |
|-----|------|
| `IsPreviewTextInputting()` | 检查是否在预览输入状态 |
| `GetPreviewText()` | 获取预览文本 |
| `FinishTextPreview()` | 结束预览文本 |
| `InsertValue(text)` | 插入文本 |
| `DeleteForward(length)` | 向前删除 |
| `DeleteBackward(length)` | 向后删除 |

### 滚动管理

| 方法 | 功能 |
|-----|------|
| `ScrollTo(offsetX, offsetY)` | 滚动到指定位置 |
| `ScrollEdge(edge)` | 滚动到边缘 |
| `GetCurrentOffset()` | 获取当前偏移 |
| `GetScrollableSize()` | 获取可滚动尺寸 |

---

## 使用示例

### 老框架模式示例

```typescript
@Entry
@Component
struct RichEditorExample {
  controller: RichEditorController = new RichEditorController();
  
  build() {
    Column() {
      RichEditor({ controller: this.controller })
        .onReady(() => {
          this.controller.addTextSpan('Hello World', {
            style: {
              fontColor: Color.Red,
              fontSize: 20
            }
          });
        })
        .onWillChange((value: RichEditorChangeValue) => {
          return true;
        })
        .placeholder('请输入内容')
        .maxLength(1000)
    }
  }
}
```

### 属性字符串模式示例

```typescript
@Entry
@Component
struct RichEditorStyledStringExample {
  controller: RichEditorStyledStringController = new RichEditorStyledStringController();
  mutableStyledString: MutableStyledString = new MutableStyledString('Hello World');
  
  aboutToAppear() {
    let style = new TextStyle();
    style.fontColor = Color.Red;
    style.fontSize = 20;
    this.mutableStyledString.addStyle(style, 0, 5);
  }
  
  build() {
    Column() {
      RichEditor({ controller: this.controller })
        .onReady(() => {
          this.controller.setStyledString(this.mutableStyledString);
        })
    }
  }
}
```

---

## 编码规范

### 通用规范

- 每行最大字符数为120，超过120则需要在适当位置换行
- 变量统一使用小驼峰命名
- 类的成员变量需在末尾添加下划线_，例如 `maxLines_`
- 代码中不能出现只有空格的行

### 宏的使用

**CHECK_NULL_VOID** - 用于方法返回值为void时的空指针检查：
```cpp
CHECK_NULL_VOID(host);
CHECK_NULL_VOID(CheckStyledStringRangeValid(start, length));
```

**CHECK_NULL_RETURN** - 用于方法存在返回值时的空指针检查：
```cpp
CHECK_NULL_RETURN(imageNode, defaultValue);
```

**IF_TRUE** - 单行条件语句：
```cpp
IF_TRUE(styledString_, currentContent = styledString_->GetString());
IF_TRUE(!isRichEditorInit_, FireOnReady());
```

**IF_PRESENT** - 用于判断指针是否非空：
```cpp
IF_PRESENT(oneStepDragController_, HandleDirtyNodes());
```

### 内容锁定

修改内容时始终使用 `CONTENT_MODIFY_LOCK`：
```cpp
CONTENT_MODIFY_LOCK(weakPtr) {
    styledString_->ReplaceSpanString(start, length, newValue);
    UpdateCaretPosition();
}
```

### 事件时机

在状态完全更新后触发事件：
```cpp
void SomeOperation() {
    UpdateInternalState();
    MarkDirtyNode();
    FireChangeEvent();
}
```

---

## 接口扩展开发指南

### 概述

为 RichEditor 组件新增接口需要在多个层级进行适配，从 JS/ArkTS 层到 Native C++ 层，最终调用至 Model 层的业务逻辑实现。
### 接口类型分类
RichEditor 支持两种接口类型：
1. **JS/ArkTS 接口**：用于 ArkTS 壂应用开发
2. **CAPI 接口**：用于 Native C 层开发
### 渐进式学习路径
根据您的开发需求，选择对应的详细指南：
#### 新增 JS/ArkTS 接口
当需要为 RichEditor 添加新的 ArkTS 属性或方法时，请阅读：
👉 **[api-guide-js.md](./api-guide-js.md)** - JS/ArkTS 接口扩展完整指南
包含内容：
- 接口调用链架构
- 需要适配的文件清单
- 参数解析规范
- 事件回调处理
- 完整示例代码
#### 新增 CAPI 接口
当需要为 RichEditor 添加新的 CAPI 属性枚举时，请阅读：
👉 **[api-guide-c.md](./api-guide-c.md)** - CAPI 接口扩展完整指南
包含内容：
- CAPI 层架构说明
- 枚举定义规范
- 属性处理函数实现
- 参数验证规范
- 测试验证方法
### 快速决策流程
```
需要新增接口？
    ↓
接口类型判断
    ↓
┌─────────────┬─────────────┐
│             │             │
JS/ArkTS接口    CAPI接口
│             │             │
↓             ↓
阅读 api-guide-js.md  阅读 api-guide-c.md
```

---

## 相关资源

### 重要说明

1. **StyledString vs Spans 列表**：RichEditor 可以在两种模式下运行
2. **光标亲和性**：在换行符处设置光标位置时始终使用 `PositionWithAffinity`
3. **撤销/重做**：所有内容修改都必须被记录
4. **IME 预览文本**：在内容修改前始终检查并处理预览文本状态
5. **内容锁定**：修改内容时始终使用 `CONTENT_MODIFY_LOCK`
6. **事件时机**：在状态完全更新后触发事件
7. **性能**：使用批量操作和缓存来最小化布局失效
8. **内存管理**：对所有 ACE 对象使用 `RefPtr`

### 相关组件

- `TextPattern`：基础文本渲染功能
- `TextFieldPattern`：文本输入字段
- `SearchPattern`：搜索输入字段
- `SpanString`：样式字符串实现
- `ParagraphManager`：段落管理

### 参考文档

- **组件指南**：[组件指南](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/ui/arkts-common-components-richeditor.md)
- **API参考**：[API参考](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/reference/apis-arkui/arkui-ts/ts-basic-components-richeditor.md)
- **开发文档**：`frameworks/core/components_ng/pattern/rich_editor/docs/`
- **Text组件知识库**：`docs/pattern/text/Text_Knowledge_Base_CN.md`

### 版本历史

| 版本 | 日期 | 更新内容 |
|-----|------|---------|
| v1.0 | 2026-04-18 | 初始版本，整合已有开发文档 |