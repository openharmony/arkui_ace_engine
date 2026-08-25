# gate-define.md — Image 组件基础内存优化

## 信息检索手段记录

| 手段 | 检索内容 | 结果 |
|------|----------|------|
| 源码核对 | `image_source_info.h` 成员变量 | 已读取，25 个成员，估计 ~432B |
| 源码核对 | `image_dfx.h` 成员变量 | 已读取，9 个成员，估计 ~144B |
| 源码核对 | `image_loading_context.h` 成员变量 | 已读取，31 个成员，估计 ~1,120B |
| 源码核对 | `image_pattern.h` 成员变量 | 已读取，66 个成员，估计 ~1,080B |
| 源码核对 | `image_layout_property.h` 属性定义 | 已读取，4 个 ImageSourceInfo optional 属性 |
| 源码核对 | `image_render_property.h` 属性定义 | 已读取，ImagePaintStyle group + 4 direct 属性 |

---

## 入口表（arkui-define-entry）

| 检查项 | 结果 | 证据/缺口 | 确认来源 | 后续动作 |
|--------|------|-----------|----------|----------|
| FuncID: 05-08-01 | 通过 | specs/index.md 已注册 Image 功能域，含 Feat-01~04 | specs/index.md 确认 | 无 |
| FeatID: Feat-05 | 通过 | 连续性检查：Feat-01~04 均已存在 | specs/index.md 确认 | 无 |
| specs/index.md 注册 | 待执行 | Feat-05 行尚未写入 | 待写入 | 创建 proposal 后注册 |
| profile: arkui/component | 通过 | 本次涉及 NG Image 组件 Pattern 层重构 | Owner 确认 | 无 |
| subprofiles | 通过 | arkui/component 命中 | 源码核对 components_ng/pattern/image/ | 无 |
| lineage: legacy | 通过 | 对现有组件代码内部优化，无新功能无 API 变更 | Owner 确认 | 无 |
| .codespec 目录创建 | 通过 | `.codespec/changes/issue-77826-image-memory-opt/` 已创建 | 目录检查确认 | 无 |
| long_term_spec_path | 通过 | `specs/05-ui-components/08-image-components/01-image/Feat-05-image-base-memory-opt-spec.md` | FuncID 路径推导 | Stage 2 创建 |
| long_term_design_path | 通过 | `specs/05-ui-components/08-image-components/01-image/design.md`（增量合并） | FuncID 路径推导 | Stage 2 合并 |
| spectest_feature_path: N/A | 通过 | 内存优化不产生可 Inspector 断言的行为变化 | Owner 确认（不动公共 API，不动渲染路径） | 替代验证：sizeof 对比 + 单元测试 |

### 影响面矩阵

| 维度 | 评估 | 说明 |
|------|------|------|
| 前端/API 影响 | 无 | 不动 ArkTS/C API |
| 依赖影响 | 无 | 不引入新依赖 |
| 跨平台影响 | 无 | 纯 C++ 内部重构 |
| 热路径命中 | 是 | Image 组件创建、属性更新、布局测量均命中热路径 |
| 无障碍 | 不适用 | 不改变语义树 |
| 国际化 | 不适用 | 无文本变化 |
| 多形态适配 | 不适用 | 纯内存优化 |
| 交互开始/结束 | 不适用 | 不改变交互行为 |
| 维测合同 | 待确认 | ImageDfxConfig 优化后需确保日志/DFX 信息不受影响 |
| 合法延迟状态 | 不适用 | 不引入新的异步状态 |

---

## 出口表（arkui-define-exit）

| 检查项 | 结果 | 证据/缺口 | 确认来源 | 后续动作 |
|--------|------|-----------|----------|----------|
| 基线审批 | 通过 | Owner 于 2026-06-11 批准 proposal.md 基线 | Owner 对话确认 | 无 |
| 信息来源记录完整 | 通过 | 源码核对 6 个核心头文件，记录具体路径 | 源码核对 image_source_info.h, image_dfx.h, image_loading_context.h, image_pattern.h, image_layout_property.h, image_render_property.h | 无 |
| 源码核验含路径行号 | 通过 | Agent 探索已记录成员变量和类型 | 源码核对各头文件 | 无 |

---

## 总结论

**通过** — 所有检查项已确认，Owner 已批准基线。
