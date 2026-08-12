# PageScene 文本输入类控件状态通知规格同步检查

## 2026-08-10

## 检查范围

- 更新 `spec.md` 和 `spec-for-test.md`，同步本次 `visibility`、`active` 和有效可获焦性变化通知的实际行为。
- 补充修改前、修改后的行为差异 UML，以及状态变化对四种规则配置组合的影响矩阵。
- 本轮不修改生产代码，不执行编译和单元测试；行为结论仅依据当前源码原始实现核对，不使用知识库结论。

## 源码核对证据

| 行为 | 源码证据 | 核对结论 |
|------|----------|----------|
| 可见性、active、有效可获焦性通知入口 | `frameworks/core/components_ng/base/frame_node.cpp:2144,2159,2170,2181,2995` | 状态通知只从主树节点继续下发，最终由节点类型过滤限定为文本输入类控件。 |
| 自身可获焦和父级可获焦变化 | `frameworks/core/components_ng/event/focus_hub.cpp:736-748,896-925` | 修改前后比较最终 `IsFocusable()`；最终结果相同不通知。 |
| enabled 变化 | `frameworks/core/components_ng/event/event_hub.cpp:1083-1120` | enabled 修改前后比较最终有效可获焦性；结果变化时通知。 |
| 状态变化规则裁剪 | `adapter/ohos/entrance/ui_session/ui_session_manager_ohos.cpp:844-879` | `VISIBILITY` 使用 `onlyVisible || !includeUnfocusableTextInput`，`ACTIVE` 使用 `onlyVisible`，`FOCUSABILITY` 使用 `!includeUnfocusableTextInput`。 |
| pending 合并 | `adapter/ohos/entrance/ui_session/ui_session_manager_ohos.cpp:613-629` | 受影响规则加入去重待检测集合；重复状态变化不按事件次数产生重复规则项。 |
| 稳定点门控 | `frameworks/core/components_ng/manager/content_change_manager/content_change_manager.cpp:835-843` | 滚动、转场或 Swiper 滚动中直接返回，待检测状态在消费前保留；稳定后才进入 PageScene 检测。 |

## 文档同步结果

| 文档 | 更新位置 | 内容 |
|------|----------|------|
| `spec.md` | “本次状态通知增量摘要”“修改前行为 UML”“修改后行为 UML” | 总结本次代码增量、前后行为差异、pending 与稳定点关系，并明确仍采用稳定点全量扫描。 |
| `spec.md` | US-3、状态变化影响矩阵、R-10C～R-10F、R-20、VM-3 | 固化三类状态事件的规则裁剪、有效可获焦性前后值判断、重复 pending 合并和不稳定时保留语义。 |
| `spec-for-test.md` | 1.0 UML、US-3、R-10C～R-10F、性能/可靠性和测试建议 | 增加四种规则配置组合、focusable/parentFocusable/enabled 双向切换、最终结果不变、非主树/非输入节点和多节点连续变化等测试覆盖。 |

## Fresh 校验

| 检查项 | 命令 | 结果 |
|--------|------|------|
| 差异格式 | `git diff --check` | PASS，退出码 0，无输出。 |
| SDD 全级别一致性 | `ohos-sdd validate . --level all` | PASS：`33 checks, 0 broken, 0 warn`。 |
| Mermaid 结构 | 检查两个文档中的 `mermaid` 代码围栏和 `sequenceDiagram` 声明 | PASS，共 4 个时序图，围栏成对。 |

## 验证边界

- 按 Owner 要求，本轮不执行编译或测试，因此不声明代码编译、单元测试或设备验证通过。
- 本轮仅完成规格与测试设计同步；实际新增或补充的状态通知测试仍由后续代码验证执行并回填证据。
