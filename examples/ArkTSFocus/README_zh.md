# ArkTSFocus

### 介绍

本示例展示了 ArkUI 焦点（Focus）相关的 ArkTS API 用法，涵盖组件可聚焦性、Tab 键导航、自定义焦点路径、焦点域分组与优先级、自定义焦点框样式、触摸聚焦以及命令式焦点控制。与 NdkFocus（C-API 版本）形成互补，帮助开发者掌握 ArkTS 侧焦点开发能力。

### 效果预览

| 首页 | 基础焦点 | Tab导航 |
| --- | --- | --- |
| ![screenshot](screenshots/index.png) | ![screenshot](screenshots/basic_focus.png) | ![screenshot](screenshots/tab_navigation.png) |

| 自定义焦点路径 | 焦点域 | 焦点框样式 |
| --- | --- | --- |
| ![screenshot](screenshots/custom_next_focus.png) | ![screenshot](screenshots/focus_scope.png) | ![screenshot](screenshots/focus_box_style.png) |

### 使用说明

1. 启动应用后进入主菜单页面，展示所有焦点功能入口。
2. 点击各功能项进入对应的示例页面。
3. 使用键盘 Tab 键、方向键（↑↓←→）或触摸操作体验不同的焦点行为。
4. 观察页面状态文字和按钮颜色变化，确认焦点状态。

### 具体实现

1. **基础焦点能力**（入口：pages/BasicFocus.ets）
   - `focusable(value)` 控制组件是否可聚焦
   - `defaultFocus(true)` 设置页面加载时的默认焦点
   - `onFocus()` / `onBlur()` 响应焦点变化，动态更新 UI

2. **Tab 键导航**（入口：pages/TabNavigation.ets）
   - `tabIndex(index)` 控制 Tab 键的聚焦顺序（数值越小越优先）
   - `tabStop(false)` 将节点从 Tab 导航链中排除

3. **自定义焦点路径**（入口：pages/CustomNextFocus.ets）
   - `nextFocus({ up, down, left, right })` 指定方向键的目标节点 id
   - 通过 `id()` 标记节点，配合 `nextFocus` 实现非线性的焦点跳转

4. **焦点域分组与优先级**（入口：pages/FocusScope.ets）
   - `focusScopeId(id, isGroup, arrowStepOut)` 将容器定义为焦点域
   - `focusScopePriority(scopeId, FocusPriority.PRIOR)` 设置域的优先级
   - `groupDefaultFocus(true)` 设置域内的默认聚焦节点

5. **自定义焦点框样式**（入口：pages/FocusBoxStyle.ets）
   - `focusBox(FocusBoxStyle)` 自定义焦点框的 `strokeColor`、`strokeWidth`、`margin`

6. **触摸聚焦与命令式 API**（入口：pages/FocusOnTouch.ets）
   - `focusOnTouch(value)` 控制触摸时是否自动聚焦
   - `getUIContext().getFocusController().requestFocus(key)` 命令式请求焦点（推荐）
   - `focusControl.requestFocus(key)` 全局命令式请求焦点

### 工程目录

```
ArkTSFocus/
├── AppScope/
│   ├── app.json5                         // 应用配置
│   └── resources/base/
│       ├── element/string.json           // 应用名称
│       └── media/                        // 应用图标
├── entry/
│   └── src/main/
│       ├── ets/
│       │   ├── entryability/
│       │   │   └── EntryAbility.ets      // UIAbility 入口
│       │   ├── entrybackupability/
│       │   │   └── EntryBackupAbility.ets
│       │   └── pages/
│       │       ├── Index.ets             // 主菜单页
│       │       ├── BasicFocus.ets        // focusable/defaultFocus/onFocus/onBlur
│       │       ├── TabNavigation.ets     // tabIndex/tabStop
│       │       ├── CustomNextFocus.ets   // nextFocus 方向键导航
│       │       ├── FocusScope.ets        // focusScopeId/focusScopePriority/groupDefaultFocus
│       │       ├── FocusBoxStyle.ets     // focusBox 自定义焦点框
│       │       └── FocusOnTouch.ets      // focusOnTouch/focusControl 命令式API
│       ├── resources/base/
│       │   ├── element/string.json       // 字符串资源
│       │   ├── element/color.json        // 颜色资源
│       │   ├── profile/main_pages.json   // 页面路由配置
│       │   └── media/                    // 图标资源
│       └── module.json5                  // 模块配置
├── build-profile.json5                   // 应用级构建配置
├── hvigorfile.ts                         // Hvigor 构建脚本
├── oh-package.json5                      // 依赖配置
├── code-linter.json5                     // 代码检查规则
├── hvigor/hvigor-config.json5            // Hvigor 配置
└── ohosTest.md                           // 测试用例归档
```

### 相关权限

不涉及。

### 依赖

不涉及。

### 约束与限制

1. 本示例仅支持标准系统上运行, 支持设备：华为手机。

2. HarmonyOS系统：HarmonyOS 5.0.5 Release及以上。

3. DevEco Studio版本：6.0.0 Release及以上。

4. HarmonyOS SDK版本：HarmonyOS 6.0.0 Release SDK及以上。

### 下载

```bash
git init
git config core.sparsecheckout true
echo ArkUISample/ArkTSFocus > .git/info/sparse-checkout
git remote add origin https://gitcode.com/harmonyos_samples/guide-snippets.git
git pull origin master
```
