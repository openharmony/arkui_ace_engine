# TASK-006: sample SA dump、Web 回归和端到端验证

## 任务元数据

| 字段 | 内容 |
|------|------|
| Task ID | TASK-006 |
| 标题 | ui_session_sample dump 触发统一翻译接口并验证 Web 兼容 |
| 关联 Feature | FEAT-UISESSION-UNIFIED-TEXT-TRANSLATE |
| 目标仓库 | ace_engine |
| 目标模块 | interfaces/inner_api/ui_session/ui_session_sample, Web/Uisession tests |
| 分支 | dev |
| 优先级 | P0 |
| 复杂度 | 中 |
| 执行方式 | 主线程顺序执行 |

## 任务描述

### 做什么

1. 在 `ui_session_sample` 新增 dump 命令，触发 `GetPageTranslateText`、`StartPageTranslate`、`EndPageTranslate`、`Reset`、`SendPageTranslateResult`。
2. dump 参数支持 scope bitmask、nodeId、version、译文、安全摘要输出。
3. dump 输出只打印 nodeId、version、长度、scope、requestId、状态，不打印原文/译文。
4. 增加 Web 回归，确认 `ARKUI_ARKWEB` 继续复用现有 Web 脚本注入提取/回填/Reset，并同时获取 ArkUI 原生文本。
5. 增加 dump 命令触发 `GetCurrentAbilityLanguageInfo`，输出当前 Ability 实例 `language/region` 和状态。
6. 补充端到端验证记录模板：真机 dump 命令、预期 hilog、异常恢复场景。
7. dump 参数校验覆盖未知 scope bit：未知 bit 返回参数错误；`XCOMPONENT`/`CANVAS_NODE` 已知保留 bit 可解析但当前不触发处理。

### 不做什么

- 不新增生产调试工具。
- 不改变 sample SA 获取 UIContent remote object 的现有缓存/死亡监听机制。
- 不打印敏感正文。
- 不打印页面文本或资源内容；language/region 可直接打印。

## 规格映射与边界

| AC | 来源 | 验证方式 |
|----|------|----------|
| AC-15 | spec.md | Web 回归 |
| AC-18, AC-19, AC-20 | spec.md | 真机 dump + hilog |
| AC-21, AC-22 | spec.md | 真机 dump + hilog |

| Rule ID | Must / Must Not |
|---------|-----------------|
| WEB-COMPAT | Web 脚本注入路径不回退 |
| DFX | dump 输出安全摘要 |
| DATA-MIN | sample SA 只按 `nodeId/text/version` 使用节点 payload |
| ABILITY-LANGUAGE | sample SA dump 输出 language/region，不依赖页面文本回调 |
| BUILD-MIN | 编译 ui_session_sample 所属目标、Web 相关回归目标和必要 Uisession 测试目标 |

## 受影响文件

| 操作 | 文件路径 | 说明 |
|------|----------|------|
| 修改 | `interfaces/inner_api/ui_session/ui_session_sample/ui_sa_service.*` | dump handler 和参数解析 |
| 测试 | Uisession 相关测试 | Ability language/region dump 和 IPC 回归 |
| 测试 | Web/Uisession 相关测试 | ARKUI_ARKWEB Web 回归 |
| 新增 | `.codespec/changes/issue-85818-ui-session-arkui-text-translate/evidence/verification/manual-verification.md` | 真机 dump 验证记录模板 |

## 完成判据

- 真机可通过 dump 触发单次获取、Start、End、Reset、回填。
- 真机可通过 dump 触发当前 Ability language/region 查询，并打印当前实例生效的语言和地区。
- dump 可以指定 `ARKUI_ONLY`、`ARKWEB_ONLY`、`ARKUI_ARKWEB` 和组合 bitmask；`XCOMPONENT`/`CANVAS_NODE` 作为保留 bit 可解析但当前不触发处理。
- dump 传入未知 scope bit 时返回参数错误，不注册 callback、不触发文本上报。
- Web 旧接口和统一 `ARKUI_ARKWEB` 都能走现有 Web 翻译路径。
- 输出不包含原文/译文正文。

## 停止条件

- sample SA 当前 dump 框架无法承载新增参数，需要先重构 dump 参数解析。
- 真机环境无法获取 UIContent remote object，需要记录环境问题并暂停端到端验证。

## 验证检查清单

- [ ] 编译 `ui_session_sample` 所属目标和 Web 回归相关目标；必要时补 Uisession 测试目标
- [ ] Web 回归测试通过
- [ ] 真机 dump 验证记录填写到 `manual-verification.md`
