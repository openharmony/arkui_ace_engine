# TASK-002: manager 会话、启动注册、Web 兼容和死亡恢复

## 任务元数据

| 字段 | 内容 |
|------|------|
| Task ID | TASK-002 |
| 标题 | 统一翻译 manager 会话编排和 UIContent 启动期 callback 注册 |
| 关联 Feature | FEAT-UISESSION-UNIFIED-TEXT-TRANSLATE |
| 目标仓库 | ace_engine |
| 目标模块 | adapter/ohos/entrance, interfaces/inner_api/ui_session |
| 分支 | dev |
| 优先级 | P0 |
| 复杂度 | 高 |
| 执行方式 | 主线程顺序执行 |

## 任务描述

### 做什么

1. 扩展 `UIContentImpl::InitUISessionManagerCallbacks`，保存统一翻译 Get/Start/End/Reset callback 到 `UiSessionManagerOhos`。
2. `UiSessionManagerOhos` 管理统一翻译 session、scope、requestId、processId 和当前 instanceId 的 `UiTranslateManagerImpl` 分发。
3. `StartPageTranslate` 进入连续翻译状态并触发当前 snapshot；`EndPageTranslate` 停止增量并恢复原文。
4. `ARKUI_ARKWEB` 通过 `PageTranslateNode` hook 继续委托 ArkWeb 现有脚本注入路径并同时处理 ArkUI 原生文本，`ARKUI_ONLY` 不进入 ArkWeb；`XCOMPONENT`/`CANVAS_NODE` 仅保留字段，当前不处理。
5. 扩展 report remote death 监听：SA death 时统一 Reset/End，恢复 Web 和 ArkUI 原文，取消 timeout/watchdog。
6. 扩展 `UIContentImpl::InitUISessionManagerCallbacks`，保存当前 Ability 实例语言地区同步读取函数；`UiSessionManagerOhos` 按当前 instanceId 调用并通过同步 IPC reply 返回 `language/region`。
7. 提供请求 timeout 现场清理入口，供 `UiReportStub::HandlePageTranslateCallbackTimeout` 在 requestId 校验通过后调用，执行 End/Reset 级清理。

### 不做什么

- 不在 IPC stub 中直接访问 `PipelineContext`、Pattern 或 `ContentChangeManager`。
- 不重写 Web 脚本注入实现。
- 不实现 Text/RichEditor 具体 Pattern 逻辑。
- 不从系统全局语言直接推导返回值；必须以当前 Ability/UIContent 实例生效配置为准。

## 规格映射与边界

| AC | 来源 | 验证方式 |
|----|------|----------|
| AC-4, AC-5, AC-8, AC-9 | spec.md | manager 单测 |
| AC-15 | spec.md | Web 回归 |
| AC-16, AC-17 | spec.md | DeathRecipient 单测 |
| AC-21, AC-22 | spec.md | manager/current instance 单测 |

| Rule ID | Must / Must Not |
|---------|-----------------|
| UI-THREAD | 通过启动期 callback 切 UI 线程 |
| WEB-COMPAT | `ARKUI_ARKWEB` 复用现有 Web path 并处理 ArkUI 原生文本 |
| TRANSLATE-NODE-IFACE | `UiTranslateManagerImpl` Web listener 容器保存 `WeakPtr<PageTranslateNode>`；Web 翻译提取/回填/End 通过接口 hook 调用，WebInfo/image 等 Web 专属能力才局部转回 `WebPattern`；不得通过 `Pattern` 基类翻译虚函数分发 |
| ABILITY-LANGUAGE | language/region 读取只读、无副作用，采用同步 IPC，不进入 translate manager，不改变 Start/End/Reset 状态 |
| DFX | SA death 清 timeout/watchdog 和 session |
| BUILD-MIN | 编译实际修改的 adapter/entrance 相关 so 目标和 manager/death 单测 |
| SMALL-FUNCTION-REUSE | scope 判断、instance/manager 查找、UI 线程投递、Web/ArkUI 分发、session 清理和死亡恢复应抽成私有小函数复用，避免 Get/Start/End/Reset 各自复制同类流程 |

## 受影响文件

| 操作 | 文件路径 | 说明 |
|------|----------|------|
| 修改 | `adapter/ohos/entrance/ui_content_impl.*` | 注册统一翻译 callback |
| 修改 | `adapter/ohos/entrance/ui_content_impl.*` | 注册当前 Ability language/region 同步读取函数 |
| 修改 | `adapter/ohos/entrance/ace_container.cpp` | 确认/复用 translate manager 注入 |
| 修改 | `interfaces/inner_api/ui_session/ui_session_manager.h` | 新增 manager 回调类型和虚接口 |
| 修改 | `adapter/ohos/entrance/ui_session/ui_session_manager_ohos.*` | session、scope、process、death、watchdog 编排 |
| 修改 | `interfaces/inner_api/ui_session/ui_translate_manager.h` | 统一翻译 manager 抽象 |
| 修改 | `adapter/ohos/entrance/ace_translate_manager.cpp` | Web + ArkUI 分发入口 |
| 测试 | `test/unittest/.../ui_session` | manager 和 death 单测 |

## 完成判据

- Get/Start/End/Reset 通过 `UiSessionManager` 找到当前 instance 的 translate manager。
- Start 后初始上报、End 后停止上报、Reset 后恢复原文的 manager 状态可单测验证。
- `GetCurrentAbilityLanguageInfo` 通过当前 instance 返回当前 Ability 生效 `language/region`，空 locale 或 instance 缺失时返回失败/空字段且不影响翻译状态。
- SA death 时会清理 session、timeout/watchdog，并调用全量恢复。
- 请求 timeout 时可由 report stub 触发清理：校验 requestId 后清 session、停止增量上报、Reset ArkUI 临时译文、委托 Web 现有 End/Reset，并取消对应 watchdog。
- 迟到 callback、迟到 timeout 或旧 requestId 不得影响新的 Start/Get 会话。
- 现有 `GetWebViewTranslateText` / `StartWebViewTranslate` / `EndWebViewTranslate` 行为不回退。
- Manager 层公共路径复用明确：参数校验、scope bitmask 判断、按 instance 分发、清理现场和 DFX 摘要不得在多个接口中复制实现。

## 停止条件

- 当前 instanceId 获取语义无法可靠定位目标窗口，需要新增显式 windowId/instanceId 入参。
- Web 旧接口兼容需要修改现有 SA 调用约定。

## 验证检查清单

- [ ] 编译 `adapter/ohos/entrance` 中实际修改文件所属 so/组件目标；必要时补 `ace_engine` 链接验证
- [ ] Manager 单测覆盖 `ARKUI_ARKWEB`、`ARKUI_ONLY`、`ARKWEB_ONLY`、组合 bitmask，并确认 `XCOMPONENT`/`CANVAS_NODE` 当前不触发处理
- [ ] DeathRecipient 单测覆盖 SA death 时恢复和状态清理
- [ ] DFX 单测覆盖 requestId 不匹配时不清理新会话，requestId 匹配时执行 End/Reset 级现场清理
