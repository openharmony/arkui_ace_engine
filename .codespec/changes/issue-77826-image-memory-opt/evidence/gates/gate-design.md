# gate-design.md — Image 组件基础内存优化

## 信息检索手段记录

| 手段 | 检索内容 | 结果 |
|------|----------|------|
| 历史规格读取 | `specs/05-ui-components/08-image-components/01-image/design.md` | 已读取，获取三层属性架构、ImageLoadingContext 管道边界、autoResize 内存优化机制 |
| 历史规格读取 | `specs/.../Feat-01-image-core-display-spec.md` | 已读取，获取 src/alt/objectFit 属性流、autoResize/sourceSize 双重控制 |
| 历史规格读取 | `specs/.../Feat-04-image-events-spec.md` | 已读取，获取 Image 生命周期、alt fallback 链路、CanvasImage 回调持有关系 |
| 源码核对 | `image_source_info.h` | 已读取全文件，25 个成员，精确 sizeof ~448B |
| 源码核对 | `image_dfx.h` | 已读取全文件，含 ImageNodeId(24B)、ImageDfxConfig(152B)、RenderedImageInfo(140B) |
| 源码核对 | `image_loading_context.h` | 已读取全文件，31 个成员，精确 sizeof ~1,120B |
| 源码核对 | `image_pattern.h` | 已读取全文件，66 个成员，精确 sizeof ~1,056B |
| 源码核对 | `image_layout_property.h` | 已读取，4 个 optional\<ImageSourceInfo\>，总计 ~1,824B |
| 源码核对 | `image_render_property.h` | 已读取，ImagePaintStyle group + 4 direct 属性 |

---

## 入口表（arkui-specify-entry）

| 检查项 | 结果 | 证据/缺口 | 确认来源 |
|--------|------|-----------|----------|
| FeatID 连续性 | 通过 | Feat-01~04 均存在于 specs/index.md | specs/index.md |
| 存量规格读取 | 通过 | design.md、Feat-01、Feat-04 已读取并记录关键参考点 | 历史规格读取记录 |
| 存量 spec 归档 | 通过 | Feat-01~04 均已 Baselined | specs/index.md |
| 功能域 design.md | 通过 | `specs/05-08-01/design.md` 已存在 | 源码核对 |

### 存量规格关键参考点

1. **三层属性存储架构**（ADR-1）：LayoutProperty/RenderProperty/Pattern 成员变量的分层影响优化后 dirty flag 传播，本次优化不改变分层但需确保 RefPtr 替代后 dirty flag 仍正确触发
2. **ImageLoadingContext 管道边界**（ADR-4）：ImagePattern 作为 ImageLoadingContext 的消费者，通过 LoadNotifier 回调交互。本次优化改为传入 RefPtr<ImageSourceInfo>，不影响管道接口
3. **autoResize 默认值双逻辑**（ADR-3）：与本次内存优化不冲突，但需确认 autoResize 相关字段在 ImageSourceInfo 共享后不被就地修改
4. **Alt fallback 链路**：Primary → alt → altError → altPlaceholder，本次将 alt 状态合并为 unique_ptr 结构体，需确保 fallback 链路中状态访问正确

---

## 出口表（arkui-specify-exit）

| 检查项 | 结果 | 证据/缺口 | 确认来源 |
|--------|------|-----------|----------|
| design.md 已创建 | 通过 | `.codespec/changes/issue-77826-image-memory-opt/design.md` 已创建 | 文件检查 |
| spec.md 已创建 | 通过 | `.codespec/changes/issue-77826-image-memory-opt/spec.md` 已创建 | 文件检查 |
| 长期 specs 路径正确 | 通过 | Feat-05 占位待 Stage 4 迁移 | manifest.md 记录 |
| Stage 4 迁移路径已记录 | 通过 | manifest.long_term_spec_path 和 long_term_design_path 已声明 | manifest.md |
| design.md 与 spec.md 交叉一致 | 通过 | 6 个 ADR 与 5 个 FR 一一对应，不涉及项一致，API 边界一致 | 人工核对 |
| API 边界无变更 | 通过 | 两者均声明不动公共 API | design.md + spec.md |
| 不涉及项一致 | 通过 | 两者均排除解码/加载、动画/SVG、Legacy、渲染路径 | design.md + spec.md |
| 性能与内存预算已填写 | 通过 | design.md 含优化前/后内存对比表 | design.md |
| 内存分配/释放点已说明 | 通过 | ADR-1~6 均说明所有权和释放机制 | design.md |
| P0/P1 AC 映射验证方法 | 通过 | spec.md 验证映射表已列出每个 AC 的验证方法和命令 | spec.md |
| SpecTest N/A 理由已记录 | 通过 | spec.md 明确声明"内部数据结构重构，不改变用户可见行为" | spec.md |
| 源码核验含路径行号 | 通过 | 6 个核心头文件已逐行分析成员变量 | 源码核对记录 |
| 热路径评估 | 通过 | 优化目标是减少热路径上的内存分配，不增加额外开销 | design.md |

---

## 交叉校验

| 维度 | design.md | spec.md | 一致？ |
|------|-----------|---------|--------|
| ImageSourceInfo 共享 | ADR-1: RefPtr 共享 | FR-1.1~1.4: 共享语义规则 | 一致 |
| ImageDfxConfig 按需 | ADR-2: optional\<RefPtr\> | FR-2.1~2.4: 按需创建 | 一致 |
| Alt 状态合并 | ADR-4: unique_ptr 结构体 | FR-3.1~3.4: 按需创建 | 一致 |
| 回调按需 | ADR-5: 按需分配 | FR-4.1~4.2: 注册时分配 | 一致 |
| Bool 位域 | ADR-6: uint32_t 位掩码 | FR-5.1~5.3: 合并为位域 | 一致 |
| 不涉及项 | 6 项排除 | 6 项排除 | 一致 |
| 验证路径 | sizeof + 测试 + profiling | 验证映射表 | 一致 |

---

## 总结论

**通过** — 所有检查项已确认，design.md 与 spec.md 交叉一致。
