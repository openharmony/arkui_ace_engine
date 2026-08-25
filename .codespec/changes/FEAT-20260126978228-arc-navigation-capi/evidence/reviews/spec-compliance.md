# Spec 符合性审查（spec-compliance）

> 审查实现就绪度（Post-Plan Owner/Committer 视角）。本变更为 SDD 重跑，尚无生产代码实现，本审查针对"交付件一致性/可实现性/验证可追溯"给出就绪结论。

## 审查范围

| 交付件 | 状态 | 说明 |
|--------|------|------|
| proposal.md | Draft/Blocked | 技术范围闭合；Owner 元数据 Q-1~Q-4 待确认 |
| spec.md | Draft | AC WHEN/THEN 可测；规则表 5 项质量达标 |
| design.md | Draft/条件通过 | 7 点 NDK 路径 + ADR-001~004；与 spec 交叉一致 |
| execution-plan.md + 3 Task | Draft | 受影响文件全量清单 + AC→Task 追溯 + 生成源声明 |

## 一致性结论（逐 AC）

| AC | spec 来源 | plan 覆盖 | 实现路径（design） | 验证（capi 子 profile） | 就绪？ |
|----|----------|-----------|-------------------|----------------------|--------|
| AC-1.1 | R-1/2/3/13 | TASK-001/002 | modifier+style_modifier 三向 | capi_all_modifiers_test | 就绪（待 Approved） |
| AC-1.2 | R-5/6/7 | TASK-001/002 | null/type/枚举校验 | CAPI UT | 就绪 |
| AC-1.3 | R-4 | TASK-001/002 | 边界值按 ArkTS 口径 | CAPI UT | 就绪 |
| AC-2.1 | R-8 | TASK-001/002 | node_api register + 参数槽 | CAPI UT | 就绪 |
| AC-2.2 | R-9 | TASK-003 | reset 表 + EventHub 清空（ADR-002） | CAPI UT + UAF | 就绪 |
| AC-3.1 | R-10/11 | TASK-001 | swiper_option 模板 + ArcSwiperPattern | accessor UT | 就绪 |
| AC-3.2 | R-12 | TASK-001 | null/错误 type 校验 | accessor UT | 就绪 |
| AC-4.1 | — | TASK-003 | libace.map/ndk.json + SDK 编译 | SDK 编译 + validate | 就绪 |

## 规范符合性（不多/不少/不误解）

- **不多：** 范围严格限定 PR #5447（2 类型+22 属性+5 事件+3 控制函数+1 枚举）；显式排除 ArkTS/算法变更、权限/IPC、PR 外能力。
- **不少：** 每 AC 有规则、Task、验证三重映射；capi 子 profile 要求（每条 C API AC→CAPI unittest）满足。
- **不误解：** 默认值/错误码/参数槽均以 ArkTS 等价 + PR #5447 权威值为准，无第二套语义。

## 交付件交叉一致性

- spec API 变更清单 = design API 签名表 = plan 受影响文件清单（共享锚点，无名称/类型分歧）。
- design ADR-002（UAF 闭合）= spec R-9/AC-2.2 = plan TASK-003（P0 一致）。
- proposal 不涉及项（安全/IPC/迁移 N/A）= design 省略安全检查 = spec 非功能仅适用项。

## 阻塞项（须 Owner 闭合后方可 Approved/实现）

| 项 | 影响 | 动作 |
|----|------|------|
| Q-1 FuncID/FeatID | Define gate | Owner 分配 |
| Q-2 目标版本 | target_release 终确认 | Owner |
| Q-3 控制函数开放级别 | ndk.json 可见性 | Owner |
| Q-4 性能阈值 | 设备矩阵 | 性能 Owner |
| `ArkUI_CrownSensitivity` 枚举存在性 | INDICATOR 属性 | plan 阶段核验，缺失则先补 |

## 结论

**条件通过（Conditional）。** 交付件内部一致、可追溯、可实现，满足规范符合性；但上游 proposal 基线 Blocked 待 Owner（Q-1~Q-4），故实现不得启动、各交付件不得标 Approved。Owner 闭合阻塞项后，本审查转 通过。
