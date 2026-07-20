# check-design

> design.md 交叉一致性核验记录。

## 交叉一致（spec ↔ design）

| 项 | spec | design | 一致？ |
|----|------|--------|--------|
| API 清单 | 2类型+22属性+5事件+3控制函数+1枚举 | 同 | 是 |
| 默认值/错误码 | PARAM_INVALID/NO_ERROR + ArkTS 等价默认 | 同（接口参数规约） | 是 |
| UAF 闭合 | R-9/AC-2.2 | ADR-002 + 资源所有权矩阵 | 是 |
| 复用 NG | 架构约束 | ADR-001 + 调用链 | 是 |

## 调用链层级覆盖

C ABI 头 → 控制函数 → 节点路由 → 属性分发 → Modifier 注册/实现 → 事件路由 → NG Pattern（复用）→ ABI/SDK → 测试：每层有文件 + 核验锚点（行号当次会话核验）。

## 分层合规

NDK → NG 单向；不跨子系统；无跨层违规。

## 安全基础检查

proposal「安全与权限」= N/A → 整节省略（不留空占位）。无 threat-model。

## 关键源码核验路径

| 结论 | path:line |
|------|-----------|
| NDK 层空白 | `interfaces/native/native_node.h:153`（NodeType 止于 PICKER=1018） |
| modifier 注册模式 | `frameworks/core/interfaces/native/node/node_modifiers.cpp:232` |
| 控制函数模板 | `interfaces/native/node/swiper_option.cpp:24/94/108` |
| 事件 reset 表缺口 | `frameworks/core/interfaces/native/node/node_api.cpp:923` |
| NG 复用 | `frameworks/core/components_ng/pattern/swiper/arc_swiper_pattern.h:25`、`pattern/indexer/arc_indexer_pattern.h:27` |

## 结论

条件通过；与 spec 交叉一致；上游 Blocked 不得 Approved。
