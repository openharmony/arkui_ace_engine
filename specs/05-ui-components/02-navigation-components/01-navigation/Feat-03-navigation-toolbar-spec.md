# 特性规格

> Func-05-02-01-Feat-03 Navigation 工具栏配置：固化 toolbarConfiguration（Array<ToolbarItem>/CustomBuilder + options）、hideToolBar（boolean + animated since 13）、enableToolBarAdaptation（since 19）、ToolbarItem、ToolbarItemStatus、NavigationToolbarOptions 的行为规格。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | Navigation 工具栏配置 |
| 特性编号 | Func-05-02-01-Feat-03 |
| 所属 Epic | 无（已有能力补录） |
| 优先级 | P1 |
| 目标版本 | API 9 起支持，hideToolBar animated API 13，enableToolBarAdaptation API 19 |
| SIG 归属 | ArkUI SIG |
| 状态 | Baselined |
| 复杂度 | 中 |

## 本次变更范围（Delta）

无新增变更，已有实现补录。

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Design | `specs/05-ui-components/02-navigation-components/01-navigation/design.md` | Baselined |
| SDK API | `interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | — |
| Navigation Pattern | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` | — |
| Navigation Model NG | `frameworks/core/components_ng/pattern/navigation/navigation_model_ng.cpp` | — |

---

## 用户故事

### US-1: 配置工具栏菜单项

**作为** 应用开发者,
**我想要** 通过 `toolbarConfiguration()` 设置 Navigation 工具栏菜单项（ToolbarItem 数组或 CustomBuilder）,
**以便** 在 NavBar 底部添加操作工具栏按钮。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-1.1 | WHEN 调用 `.toolbarConfiguration(value: Array<ToolbarItem>)` THEN 工具栏按 ToolbarItem 列表显示菜单项 | 正常 |
| AC-1.2 | WHEN 调用 `.toolbarConfiguration(value: CustomBuilder)` THEN 工具栏显示自定义构建内容 | 正常 |
| AC-1.3 | WHEN 调用 `.toolbarConfiguration(value: Array<ToolbarItem>, options: NavigationToolbarOptions)` THEN 工具栏按 ToolbarItem 列表设置，并通过 NavigationToolbarOptions 配置工具栏选项 | 正常 |
| AC-1.4 | WHEN ToolbarItem.status 设置为 ToolbarItemStatus.NORMAL THEN 工具栏项以正常状态显示 | 正常 |
| AC-1.5 | WHEN ToolbarItem.status 设置为 ToolbarItemStatus.DISABLE THEN 工具栏项以禁用状态显示，不可点击 | 正常 |
| AC-1.6 | WHEN ToolbarItem.status 设置为 ToolbarItemStatus.ACTIVE THEN 工具栏项以激活状态显示 | 正常 |
| AC-1.7 | WHEN 未设置 toolbarConfiguration THEN NavBar 底部不显示工具栏 | 正常 |

### US-2: 隐藏/显示工具栏

**作为** 应用开发者,
**我想要** 通过 `hideToolBar()` 隐藏或显示工具栏，支持动画过渡,
**以便** 在需要时完全隐藏工具栏。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-2.1 | WHEN 调用 `.hideToolBar(true)` THEN 工具栏区域完全隐藏 | 正常 |
| AC-2.2 | WHEN 调用 `.hideToolBar(false)` 或重置 THEN 工具栏区域恢复显示 | 正常 |
| AC-2.3 | WHEN 调用 `.hideToolBar(true, { animated: true })`（API 13 新增 animated 参数）THEN 工具栏隐藏时播放过渡动画 | 正常 |
| AC-2.4 | WHEN 调用 `.hideToolBar(true, { animated: false })` THEN 工具栏隐藏时无动画，直接消失 | 边界 |
| AC-2.5 | WHEN 未设置 animated 参数 THEN 默认有动画过渡 | 边界 |

### US-3: 工具栏自适应适配

**作为** 应用开发者,
**我想要** 通过 `enableToolBarAdaptation()` 启用工具栏自适应适配（API 19 新增）,
**以便** 让工具栏在窄屏设备上自动适配显示。

| AC编号 | 验收标准 | 类型 |
|--------|---------|------|
| AC-3.1 | WHEN 调用 `.enableToolBarAdaptation(true)`（API 19 新增）THEN 工具栏启用自适应适配，窄屏时菜单项自动折叠 | 正常 |
| AC-3.2 | WHEN 调用 `.enableToolBarAdaptation(false)` THEN 工具栏禁用自适应适配，菜单项始终全部显示 | 正常 |
| AC-3.3 | WHEN 未设置 enableToolBarAdaptation THEN 默认不启用自适应适配 | 边界 |

---

## 验收追溯

| AC编号 | US ID | 关联规则 | 验证手段 |
|-------|-------|----------|----------|
| AC-1.1 | US-1 | R-1 | 单元测试 toolbarConfiguration Array<ToolbarItem> |
| AC-1.2 | US-1 | R-1 | 单元测试 toolbarConfiguration CustomBuilder |
| AC-1.3 | US-1 | R-1, R-2 | 单元测试 toolbarConfiguration + NavigationToolbarOptions |
| AC-1.4 | US-1 | R-3 | 单元测试 ToolbarItemStatus NORMAL |
| AC-1.5 | US-1 | R-3 | 单元测试 ToolbarItemStatus DISABLE |
| AC-1.6 | US-1 | R-3 | 单元测试 ToolbarItemStatus ACTIVE |
| AC-1.7 | US-1 | R-1 | 代码审查 NavigationPattern 默认 toolbarConfiguration |
| AC-2.1 | US-2 | R-4 | 单元测试 hideToolBar true |
| AC-2.2 | US-2 | R-4 | 单元测试 hideToolBar false/reset |
| AC-2.3 | US-2 | R-5 | 单元测试 hideToolBar animated true |
| AC-2.4 | US-2 | R-5 | 单元测试 hideToolBar animated false |
| AC-2.5 | US-2 | R-5 | 代码审查 NavigationPattern hideToolBar 默认动画 |
| AC-3.1 | US-3 | R-6 | 单元测试 enableToolBarAdaptation true |
| AC-3.2 | US-3 | R-6 | 单元测试 enableToolBarAdaptation false |
| AC-3.3 | US-3 | R-6 | 代码审查 NavigationPattern 默认 enableToolBarAdaptation |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | — | toolbarConfiguration 设置工具栏菜单项：Array<ToolbarItem> 按列表显示工具栏图标/文字项；CustomBuilder 显示自定义构建工具栏内容。支持 NavigationToolbarOptions 配置工具栏选项 | ToolbarItem 包含 icon、title、id、action、status 等字段 | AC-1.1~AC-1.3, AC-1.7 |
| R-2 | 行为 | — | NavigationToolbarOptions 配置工具栏选项，与 toolbarConfiguration 配合使用 | — | AC-1.3 |
| R-3 | 行为 | — | ToolbarItemStatus 定义工具栏项状态：NORMAL=0（正常状态）、DISABLE=1（禁用状态，不可点击）、ACTIVE=2（激活状态） | — | AC-1.4~AC-1.6 |
| R-4 | 行为 | — | hideToolBar 隐藏/显示工具栏：true 时工具栏完全隐藏，NavBar 底部不显示工具栏区域；false 或重置时恢复工具栏显示 | — | AC-2.1, AC-2.2 |
| R-5 | 行为 | — | hideToolBar 支持 animated 参数（API 13 新增）：animated=true 时隐藏/显示播放过渡动画，animated=false 时直接切换，默认有动画 | API 13 新增 | AC-2.3~AC-2.5 |
| R-6 | 行为 | — | enableToolBarAdaptation 启用/禁用工具栏自适应适配（API 19 新增）：true 时窄屏设备菜单项自动折叠，false 时菜单项始终全部显示，默认不启用 | API 19 新增 | AC-3.1~AC-3.3 |

---

## 验证映射

| VM编号 | AC编号 | 验证类型 | 位置/用例 |
|-------|-------|----------|-----------|
| VM-1 | AC-1.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` toolbarConfiguration Array<ToolbarItem> |
| VM-2 | AC-1.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` toolbarConfiguration CustomBuilder |
| VM-3 | AC-1.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` toolbarConfiguration + NavigationToolbarOptions |
| VM-4 | AC-1.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` ToolbarItemStatus NORMAL |
| VM-5 | AC-1.5 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` ToolbarItemStatus DISABLE |
| VM-6 | AC-1.6 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` ToolbarItemStatus ACTIVE |
| VM-7 | AC-1.7 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` 默认 toolbarConfiguration |
| VM-8 | AC-2.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` hideToolBar true |
| VM-9 | AC-2.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` hideToolBar reset |
| VM-10 | AC-2.3 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` hideToolBar animated |
| VM-11 | AC-2.4 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` hideToolBar animated false |
| VM-12 | AC-2.5 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` hideToolBar 默认动画 |
| VM-13 | AC-3.1 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` enableToolBarAdaptation true |
| VM-14 | AC-3.2 | 单元测试 | `test/unittest/core/pattern/navigation/navigation_test_ng.cpp` enableToolBarAdaptation false |
| VM-15 | AC-3.3 | 代码审查 | `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp` 默认 enableToolBarAdaptation |

---

## API 变更分析

### 新增 API

> 本特性为已有实现补录，以下 API 均为 Public 开放范围。

| API 签名 | 类型 | d.ts 位置 | @since | 开放范围 | 功能描述 |
|----------|------|-----------|--------|----------|----------|
| `toolbarConfiguration(value: Array<ToolbarItem> \| CustomBuilder): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置工具栏菜单项 |
| `toolbarConfiguration(value: Array<ToolbarItem>, options: NavigationToolbarOptions): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 设置工具栏菜单项并配置选项 |
| `hideToolBar(value: boolean): NavigationAttribute` | Public | navigation.d.ts | API 9 | Public | 隐藏/显示工具栏 |
| `hideToolBar(value: boolean, options: NavigationToolBarOptions): NavigationAttribute` | Public | navigation.d.ts | API 13 | Public | 隐藏/显示工具栏并配置动画选项 |
| `enableToolBarAdaptation(enable: boolean): NavigationAttribute` | Public | navigation.d.ts | API 19 | Public | 启用/禁用工具栏自适应适配 |

**关联类型定义**：

| 类型 | 定义 | @since |
|------|------|--------|
| `ToolbarItem` | `{ icon?: ResourceStr, title?: ResourceStr, id?: number, action?: () => void, status?: ToolbarItemStatus }` | API 9 |
| `ToolbarItemStatus` | `{ NORMAL=0, DISABLE=1, ACTIVE=2 }` | API 9 |
| `NavigationToolbarOptions` | 工具栏配置选项 | API 9 |
| `NavigationToolBarOptions` | `{ animated?: boolean }` | API 13 |

## 接口规格

### 接口定义

> 本特性为已有实现补录，接口行为定义详见上方规则定义和用户故事。

无新增接口规格。

---

## 兼容性声明

| API 版本 | 行为差异 | 影响 | 迁移指导 |
|----------|----------|------|----------|
| API 9 | toolbarConfiguration/hideToolBar 基础接口 | 工具栏配置完善 | 无需迁移 |
| API 13 | hideToolBar 支持 animated 参数 | 工具栏隐藏时可配置动画 | 未传 animated 时默认有动画 |
| API 19 | enableToolBarAdaptation 新增 | 窄屏工具栏自适应适配 | 未设置时默认不启用适配 |

---

## 架构约束

| 约束 | 描述 |
|------|------|
| 工具栏位置 | 工具栏位于 NavBar 底部，toolbarConfiguration 在 NavBar 节点内部渲染 |
| ToolbarItem 状态 | ToolbarItemStatus 三种状态在 NavBarPattern 中分别处理渲染和交互逻辑 |
| hideToolBar 动画参数 | animated 参数通过 NavigationToolBarOptions 传入，NavigationPattern 控制 ToolBar 节点显隐动画 |
| enableToolBarAdaptation 适配 | 工具栏自适应适配在 NavigationLayoutAlgorithm 中根据容器宽度判断折叠逻辑 |

---

## 非功能性需求

| 维度 | 要求 |
|------|------|
| 性能 | 工具栏属性设置无额外开销，toolbarConfiguration/hideToolBar 直接写入 Property |
| 可调试性 | NavigationPattern 支持 DumpInfo 输出 toolbarConfiguration/hideToolBar 等工具栏属性 |

---

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机 | enableToolBarAdaptation 窄屏时菜单项自动折叠 | 窄屏下 ToolbarItem 超过容器宽度时折叠 | 单元测试 | — |
| 平板 | 工具栏菜单项全部显示 | 宽屏下无需折叠 | 单元测试 | — |
| 折叠屏 | 折叠态菜单项可能折叠，展开态全部显示 | enableToolBarAdaptation 控制折叠行为 | 单元测试 | — |

---

## 全局特性影响

| 影响维度 | 说明 |
|----------|------|
| NavBar 布局 | toolbarConfiguration 影响 NavBar 底部区域的布局计算 |
| 工具栏交互 | ToolbarItem.action 回调在 UI 线程执行 |

---

## Spec 自审清单

- [x] 所有 US 以 "作为/我想要/以便" 格式描述
- [x] 所有 AC 编号格式正确（AC-X.Y），且在验收追溯中引用
- [x] 验证映射覆盖全部 AC，每个 AC 至少有一种验证手段
- [x] 规则编号连续且可追溯到源码
- [x] API 变更分析基于真实 SDK 定义文件（navigation.d.ts）
- [x] 兼容性声明标注 API 版本差异（animated API 13、enableToolBarAdaptation API 19）
- [x] 所有源码引用包含 file 信息
- [x] 无 TBD/TODO 占位符
- [x] 变更范围 Delta 明确标注为已有实现补录

---

## context-references

### 源码文件

| 文件 | 说明 |
|------|------|
| `frameworks/core/components_ng/pattern/navigation/navigation_pattern.cpp/.h` | Pattern 层，工具栏配置管理 |
| `frameworks/core/components_ng/pattern/navigation/navigation_model_ng.cpp/.h` | NG Model 层，toolbarConfiguration/hideToolBar 属性设置 |
| `frameworks/bridge/declarative_frontend/jsview/js_navigation.cpp/.h` | JS 桥接层，工具栏属性解析 |
| `interface/sdk-js/api/@internal/component/ets/navigation.d.ts` | SDK 公开 API 定义 |

### 测试文件

| 文件 | 说明 |
|------|------|
| `test/unittest/core/pattern/navigation/` | Navigation 单元测试目录
