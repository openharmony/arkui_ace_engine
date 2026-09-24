# PageScene 文本输入类控件状态通知规格同步检查

## 2026-08-22

## 检查范围

- 更新 `spec.md`、`spec-for-test.md`、`design.md` 和 `execution-plan.md`，同步 `onlyVisible`/`rectCulling`、`visibility`、`active`、opacity 和父子树 dirty 的正式行为。
- 补充修改前、修改后的行为差异 UML，以及状态变化对四种规则配置组合的影响矩阵。
- 本轮同步正式规格和实现记录；代码构建与测试结果以 execution-plan 及最新验证记录为准。

## 源码核对证据

| 行为 | 源码证据 | 核对结论 |
|------|----------|----------|
| 可见性、active、有效可获焦性通知入口 | `frameworks/core/components_ng/base/frame_node.cpp` | 状态通知从主树节点进入；父级 visibility 变化只产生一次 PageScene dirty，后代保留框架可见性回调。 |
| opacity 通知入口 | `frameworks/core/components_ng/base/view_abstract.cpp`、`frameworks/core/components_ng/base/frame_node.cpp` | opacity 实际值变化进入 PageScene pending，同值更新不产生 dirty。 |
| 自身可获焦和父级可获焦变化 | `frameworks/core/components_ng/event/focus_hub.cpp:736-748,896-925` | 修改前后比较最终 `IsFocusable()`；最终结果相同不通知。 |
| enabled 变化 | `frameworks/core/components_ng/event/event_hub.cpp:1083-1120` | enabled 修改前后比较最终有效可获焦性；结果变化时通知。 |
| 状态变化规则裁剪 | `adapter/ohos/entrance/ui_session/ui_session_manager_ohos.cpp` | `VISIBILITY` 使用 `onlyVisible || !includeUnfocusableTextInput`，`ACTIVE`/`OPACITY` 使用 `onlyVisible`，`FOCUSABILITY` 使用 `!includeUnfocusableTextInput`；父级非输入节点不再被节点类型过滤掉。 |
| pending 合并 | `adapter/ohos/entrance/ui_session/ui_session_manager_ohos.cpp:613-629` | 受影响规则加入去重待检测集合；重复状态变化不按事件次数产生重复规则项。 |
| 稳定点门控 | `frameworks/core/components_ng/manager/content_change_manager/content_change_manager.cpp:835-843` | 滚动、转场或 Swiper 滚动中直接返回，待检测状态在消费前保留；稳定后才进入 PageScene 检测。 |

## 文档同步结果

| 文档 | 更新位置 | 内容 |
|------|----------|------|
| `spec.md` | “本次状态通知增量摘要”“修改前行为 UML”“修改后行为 UML” | 总结本次代码增量、前后行为差异、pending 与稳定点关系，并明确仍采用稳定点全量扫描。 |
| `spec.md` | 过滤字段、US-3、状态变化影响矩阵、R-6～R-10H、R-20、VM-3 | 固化 onlyVisible/rectCulling 四象限、opacity 过滤、父子树 dirty、有效可获焦性前后值判断、重复 pending 合并和不稳定时保留语义。 |
| `spec-for-test.md` | 1.0 UML、US-2/US-3、R-6～R-10H、性能/可靠性和测试建议 | 增加 onlyVisible/rectCulling 四象限、opacity/祖先属性、父子树 dirty、focusable/parentFocusable/enabled 双向切换、同值更新和多节点连续变化等测试覆盖。 |

## Fresh 校验

| 检查项 | 命令 | 结果 |
|--------|------|------|
| 差异格式 | `git diff --check` | PASS，退出码 0，无输出。 |
| SDD 全级别一致性 | `ohos-sdd validate .codespec/changes/ui-session-page-scene-awareness --level all` | PASS：`32 checks, 0 broken, 0 warn`。 |
| Mermaid 结构 | 检查两个文档中的 `mermaid` 代码围栏和 `sequenceDiagram` 声明 | PASS，共 4 个时序图，围栏成对。 |

## 验证边界

- 本轮规格同步不替代代码构建和运行时回归；新增 opacity、父级通知和 rectCulling 组合仍需在完整 GN 环境中验证。
