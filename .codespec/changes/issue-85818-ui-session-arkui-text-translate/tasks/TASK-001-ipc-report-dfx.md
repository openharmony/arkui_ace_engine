# TASK-001: 统一 IPC/API/report payload 与 DFX 基础

## 任务元数据

| 字段 | 内容 |
|------|------|
| Task ID | TASK-001 |
| 标题 | 统一页面文本翻译 innerAPI、report payload、共享内存和 DFX 基础 |
| 关联 Feature | FEAT-UISESSION-UNIFIED-TEXT-TRANSLATE |
| 目标仓库 | ace_engine |
| 目标模块 | interfaces/inner_api/ui_session, adapter/ohos/entrance/ui_session |
| 分支 | dev |
| 优先级 | P0 |
| 复杂度 | 高 |
| 执行方式 | 主线程顺序执行 |

## 任务描述

### 做什么

1. 在 `IUiContentService` / proxy / stub 中补齐统一页面文本获取、Start、End、Reset、回填接口语义；若当前分支已存在同名 transaction/声明，应复用并完善，不得重复新增平行接口，保留现有 Web-only 接口。
2. 定义 `TranslateContentScope` bitmask、`TranslateTextRequest`、`TranslateTextNode(nodeId/text/version)`、`TranslateResult` 的 IPC 序列化。
3. 新增当前 Ability 实例语言地区 innerAPI：`GetCurrentAbilityLanguageInfo(std::string& language, std::string& region)`，采用同步 IPC，通过 reply 返回 `language` 和 `region`。
4. UI 上报链路扩展 `UiReportProxy` / `UiReportStub`，保存 SA callback 并上报 `nodeId/text/version`。
5. 大文本统一复用现有 `LargeStringAshmem` 共享内存方式，普通小文本仍可走 parcel 字段。
6. 在 `UiReportStub` 增加请求 callback timeout 和 5s 译文等待 watchdog 的注册、取消、告警入口。
7. 为每次 Get/Start 请求生成 requestId，timeout task、callback 触发和迟到回调丢弃都必须基于 requestId 校验。

### 不做什么

- 不实现 Text/RichEditor/TextField Pattern 的提取和回填。
- 不改变现有 Web-only API 的签名和行为。
- 不向 SA 暴露 `sourceType`、`changeType`、`scope` 作为文本节点业务字段。
- 不向 SA 暴露 Ability locale 的 `script`、`localeTag` 或资源 fallback 细节；首期只返回 `language` 和 `region`。

## 规格映射与边界

| AC | 来源 | 验证方式 |
|----|------|----------|
| AC-1, AC-2 | spec.md | proxy/stub/report 单测 |
| AC-16, AC-17 | spec.md | timeout/death 基础单测 |
| AC-18, AC-19, AC-20 | spec.md | sample 调用前置接口编译验证 |
| AC-21, AC-22 | spec.md | proxy/stub 同步 IPC 单测 |

| Rule ID | Must / Must Not |
|---------|-----------------|
| DATA-MIN | SA payload 仅 `nodeId/text/version` |
| ABILITY-LANGUAGE | 当前 Ability 语言地区接口仅返回 `language/region`，必须走同步 IPC reply，不走 report channel，不注册翻译 callback，不触发 timeout/watchdog |
| BIG-TEXT-IPC | 大文本使用 `LargeStringAshmem` |
| DFX | 请求 timeout 清 callback；译文等待 watchdog 默认 5s 只告警 |
| BUILD-MIN | 只编译 ui_session/adapter 相关 so 目标和必要单测；除非局部目标无法覆盖链接关系，否则不要求全量 `ace_engine` |
| SMALL-FUNCTION-REUSE | IPC 序列化/反序列化、普通文本与 ashmem 分流、timeout/watchdog 注册取消、非正文日志摘要必须抽成职责单一的小函数复用，避免 proxy/stub/report 多处分支复制 |

## 受影响文件

| 操作 | 文件路径 | 说明 |
|------|----------|------|
| 修改 | `interfaces/inner_api/ui_session/ui_content_service_interface.h` | 新增 transaction 和接口声明 |
| 修改 | `interfaces/inner_api/ui_session/ui_content_proxy.h` | SA 侧统一接口 |
| 修改 | `adapter/ohos/entrance/ui_session/ui_content_proxy.cpp` | 注册 callback、写 request/result parcel；新增 Ability language/region 同步 SendRequest 和 reply 读取 |
| 修改 | `adapter/ohos/entrance/ui_session/ui_content_stub.*` | 解析新 transaction |
| 修改 | `interfaces/inner_api/ui_session/ui_report_proxy.h` | UI 上报统一文本节点接口 |
| 修改 | `adapter/ohos/entrance/ui_session/ui_report_proxy.cpp` | 写 `nodeId/text/version`，大文本走 `LargeStringAshmem` |
| 修改 | `interfaces/inner_api/ui_session/ui_report_stub.h` | callback、timeout/watchdog 成员 |
| 修改 | `adapter/ohos/entrance/ui_session/ui_report_stub.cpp` | 读取文本 payload，触发 SA callback，处理 DFX task |
| 测试 | `test/unittest/.../ui_session` | IPC、ashmem、timeout/watchdog 单测 |

## 完成判据

- 新接口编译通过，旧 Web-only 接口仍保留。
- 当前已存在的页面翻译 transaction/接口声明被复用和补齐，不出现第二套同义 transaction 或 proxy/stub 方法。
- `GetCurrentAbilityLanguageInfo` 可通过同步 IPC reply 返回 `language` 和 `region`，且不依赖 `ReportService` 文本上报链路。
- 大文本翻译 payload 能通过 `LargeStringAshmem` 写入和读取。
- 请求 timeout 与译文等待 watchdog 行为可单测验证。
- 请求 timeout 时除清 callback 外，必须调用 manager 清理入口或返回明确 cleanup action 给 TASK-002，确保 End/Reset 级现场清理可被串联。
- 迟到 callback 或 timeout 的 requestId 与当前 pending requestId 不匹配时，只记录非正文日志并丢弃，不得重新进入会话或覆盖新 callback。
- 日志不打印原文/译文，只打印 requestId、nodeId、version、长度、elapsedMs、错误码。
- 新增 IPC/DFX 代码不存在重复的 payload 写读、ashmem 阈值判断、task 注册取消逻辑；共享逻辑集中到私有 helper 或局部静态函数。

## 停止条件

- 发现现有 transaction code 冲突且无法在本文件范围内解决。
- 需要改变 Public API 或 ArkTS API。
- 需要向 SA 暴露 `sourceType/changeType` 才能完成序列化。

## 验证检查清单

- [ ] 编译 `adapter/ohos/entrance/ui_session` 所属 so/组件目标；若无法定位局部目标，再升级到 `ace_engine`
- [ ] Uisession IPC 单测覆盖普通文本和大文本 ashmem
- [ ] DFX 单测覆盖请求 timeout、5s watchdog、取消 watchdog
- [ ] DFX 单测覆盖 requestId 生成/匹配、timeout 现场清理调用、迟到回调丢弃
