# ArkUI 特性规格索引

> 本文件是 ArkUI ace_engine 特性规格（Spec）体系的总入口。所有功能域和特性必须在此注册后才能生成规格文档。

## 功能域层级树

### 一级域（L1）

| 编号 | 目录名（英文 slug） | 中文名 | 说明 |
|------|---------------------|--------|------|
| 01 | `01-architecture` | 架构通用设计 | 编译构建、目录结构、部件化、兼容性设计、架构优化 |
| 02 | `02-cross-platform` | 跨平台适配层 | 多平台适配、平台抽象 |
| 03 | `03-engine-framework` | 引擎框架层 | 渲染管线、布局引擎、状态管理、事件系统 |
| 04 | `04-common-capability` | 通用能力层 | 通用属性、通用事件、通用样式、自定义节点能力 |
| 05 | `05-ui-components` | 组件层 | 基础组件、容器组件、画布组件 |

### 二级域（L2）→ 三级域（L3）→ 功能域

| L1 | L2 | L3 | FuncID | 目录路径 | design.md | 特性数 |
|----|----|----|--------|----------|-----------|--------|
| 03 引擎框架层 | 01 渲染管线 | 01 基础渲染管线 | `03-01-01` | `03-engine-framework/01-render-pipeline/01-basic-render-pipeline/` | [design.md](03-engine-framework/01-render-pipeline/01-basic-render-pipeline/design.md) | 1 |
| 04 通用能力层 | 03 通用属性 | 01 布局属性 | `04-03-01` | `04-common-capability/03-common-attributes/01-layout-attributes/` | [design.md](04-common-capability/03-common-attributes/01-layout-attributes/design.md) | 3 |
| 04 通用能力层 | 04 通用事件 | 06 手势能力 | `04-04-06` | `04-common-capability/04-common-events/06-gesture-capability/` | [design.md](04-common-capability/04-common-events/06-gesture-capability/design.md) | 5 |
| 04 通用能力层 | 06 自定义节点能力 | 01 自定义节点（占位） | `04-06-01` | `04-common-capability/06-custom-node-capability/01-custom-node-base/` | [design.md](04-common-capability/06-custom-node-capability/design.md) | 0 |
| 04 通用能力层 | 06 自定义节点能力 | 02 FrameNode | `04-06-02` | `04-common-capability/06-custom-node-capability/02-framenode/` | [design.md](04-common-capability/06-custom-node-capability/design.md) | 1 |
| 04 通用能力层 | 06 自定义节点能力 | 03 RenderNode | `04-06-03` | `04-common-capability/06-custom-node-capability/03-rendernode/` | [design.md](04-common-capability/06-custom-node-capability/design.md) | 1 |
| 04 通用能力层 | 06 自定义节点能力 | 04 BuilderNode | `04-06-04` | `04-common-capability/06-custom-node-capability/04-buildernode/` | [design.md](04-common-capability/06-custom-node-capability/design.md) | 1 |
| 04 通用能力层 | 06 自定义节点能力 | 05 ComponentContent | `04-06-05` | `04-common-capability/06-custom-node-capability/05-componentcontent/` | [design.md](04-common-capability/06-custom-node-capability/design.md) | 1 |
| 05 组件层 | 01 布局类组件 | 01 Blank | `05-01-01` | `05-ui-components/01-layout-components/01-blank/` | [design.md](05-ui-components/01-layout-components/01-blank/design.md) | 1 |

> 新增功能域时请在此表中按编号顺序添加行。

---

## 已注册特性清单

### 03-01-01 基础渲染管线

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 渲染主流程 | [Feat-01-render-main-flow-spec.md](03-engine-framework/01-render-pipeline/01-basic-render-pipeline/Feat-01-render-main-flow-spec.md) | Baselined |

### 04-03-01 布局属性

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 尺寸属性 (width/height/size/constraintSize/padding/margin) | [Feat-01-size-properties-spec.md](04-common-capability/03-common-attributes/01-layout-attributes/Feat-01-size-properties-spec.md) | Baselined |
| Feat-02 | 位置属性 (position/offset/markAnchor/align/direction) | [Feat-02-position-properties-spec.md](04-common-capability/03-common-attributes/01-layout-attributes/Feat-02-position-properties-spec.md) | Baselined |
| Feat-03 | Flex 相关属性 (flexGrow/flexShrink/flexBasis/alignSelf/layoutWeight/displayPriority) | [Feat-03-flex-properties-spec.md](04-common-capability/03-common-attributes/01-layout-attributes/Feat-03-flex-properties-spec.md) | Baselined |

### 04-04-06 手势能力

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | 基础手势 (Tap/LongPress/Pan/Pinch/Rotation/Swipe) | [Feat-01-basic-gestures-spec.md](04-common-capability/04-common-events/06-gesture-capability/Feat-01-basic-gestures-spec.md) | Baselined |
| Feat-02 | 组合手势 (GestureGroup: Sequential/Parallel/Exclusive) | [Feat-02-gesture-group-spec.md](04-common-capability/04-common-events/06-gesture-capability/Feat-02-gesture-group-spec.md) | Baselined |
| Feat-03 | 手势判定 (GestureReferee: 手势仲裁机制) | [Feat-03-gesture-referee-spec.md](04-common-capability/04-common-events/06-gesture-capability/Feat-03-gesture-referee-spec.md) | Baselined |
| Feat-04 | 手势拦截 (Touch Intercept / responseLink / hitTestBehavior) | [Feat-04-gesture-intercept-spec.md](04-common-capability/04-common-events/06-gesture-capability/Feat-04-gesture-intercept-spec.md) | Baselined |
| Feat-05 | 手势识别异常恢复增强 | [Feat-05-gesture-recognizer-recovery-spec.md](04-common-capability/04-common-events/06-gesture-capability/Feat-05-gesture-recognizer-recovery-spec.md) | Draft |

### 04-06-01 自定义节点（占位）

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|

### 04-06-02 FrameNode

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | JS 内存上报 | [Feat-01-js-memory-report-spec.md](04-common-capability/06-custom-node-capability/02-framenode/Feat-01-js-memory-report-spec.md) | Baselined |

### 04-06-03 RenderNode

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | JS 内存上报 | [Feat-01-js-memory-report-spec.md](04-common-capability/06-custom-node-capability/03-rendernode/Feat-01-js-memory-report-spec.md) | Baselined |

### 04-06-04 BuilderNode

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | JS 内存上报 | [Feat-01-js-memory-report-spec.md](04-common-capability/06-custom-node-capability/04-buildernode/Feat-01-js-memory-report-spec.md) | Baselined |

### 04-06-05 ComponentContent

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | JS 内存上报 | [Feat-01-js-memory-report-spec.md](04-common-capability/06-custom-node-capability/05-componentcontent/Feat-01-js-memory-report-spec.md) | Baselined |

### 05-01-01 Blank

| FeatID | 特性名称 | Spec 文件 | 状态 |
|--------|----------|-----------|------|
| Feat-01 | Blank 组件 | [Feat-01-blank-component-spec.md](05-ui-components/01-layout-components/01-blank/Feat-01-blank-component-spec.md) | Baselined |

---

## 注册规则

1. **新增功能域**：在本文件"功能域层级树"中添加 L2/L3 行，斜体+下划线标记为未创建；同时在"已注册特性清单"中创建对应的空表格（标题为 FuncID + 中文名）
2. **新增特性**：在对应功能域的特性清单表格中追加一行，包含 FeatID、特性名称、Spec 文件链接、状态（Draft/Baselined）
3. **排序规则**：功能域层级树和已注册特性清单均按 FuncID 数值升序排列（`03-01-01` < `04-03-01` < `05-01-01`）；同一功能域内 FeatID 按 `Feat-01, Feat-02, ...` 顺序递增
4. **状态流转**：Draft → Baselined（经评审通过后）→ Deprecated（被新特性替代）
5. **目录命名**：使用英文 slug（小写 + 短横线分隔），编号使用两位数字（`01-`, `02-`, ...）
6. **FeatID 编号**：同一功能域内从 `Feat-01` 顺序递增

---

## 术语表

### 规格文档结构

| 缩写 | 全称 | 中文 | 说明 |
|------|------|------|------|
| **US** | User Story | 用户故事 | 以"作为...我想要...以便..."格式描述用户需求。每个 US 包含多个 AC |
| **AC** | Acceptance Criterion | 验收标准 | 每个 US 下的可验证行为描述。编号格式 `AC-<US号>.<序号>`，如 `AC-1.3` |
| **BR** | Business Rule | 业务规则 | 领域语义约束，描述跨多个 US 的业务级规则 |
| **FR** | Functional Rule | 功能规则 | 具体行为规则，描述单个可观察的功能行为 |
| **ER** | Exception/Exemption Rule | 异常/豁免规则 | 边界条件、异常输入的处理规则 |
| **RC** | Recovery Contract | 恢复契约 | 错误恢复路径和重置行为的契约描述 |

### 设计文档结构

| 缩写 | 全称 | 中文 | 说明 |
|------|------|------|------|
| **ADR** | Architecture Decision Record | 架构决策记录 | 记录关键设计决策，包含问题、推荐方案、替代方案、取舍理由、影响。格式：基线用 `ADR-N`（首个特性），后续特性用 `ADR-FX-N`（如 `ADR-F3-1`） |
| **FuncID** | Functional Domain ID | 功能域编号 | 3 段数字标识（如 `04-03-01`），唯一标识一个功能域 |
| **FeatID** | Feature ID | 特性编号 | `Feat-NN` 格式，功能域内唯一 |

### 验证/测试

| 缩写 | 全称 | 中文 | 说明 |
|------|------|------|------|
| **XTS** | X Test Suite | 兼容性测试套件 | OpenHarmony 兼容性测试，位于 `test/xts/` 目录 |
| **Gherkin** | — | Gherkin 语法 | 行为驱动开发（BDD）的场景描述语言：`Given/When/Then` |
| **VM** | Verification Mapping | 验证映射 | 每个 AC 到验证手段的映射表 |

---

## 文件命名规范

| 文件类型 | 命名格式 | 示例 |
|----------|----------|------|
| 设计文档 | `design.md` | `specs/04-common-capability/03-common-attributes/01-layout-attributes/design.md` |
| 特性规格 | `Feat-NN-<name>-spec.md` | `specs/04-common-capability/03-common-attributes/01-layout-attributes/Feat-03-flex-properties-spec.md` |
| 索引文件 | `index.md` | `specs/index.md`（本文件） |

## 流程关联

```
新特性补录流程:
  1. 在 index.md 功能域层级树中确认/创建 FuncID
  2. 在 index.md 已注册特性清单中追加 FeatID 行
  3. 创建 specs/<func-domain>/ 目录（如不存在）
  4. 生成/更新 design.md
  5. 生成 Feat-NN-<name>-spec.md
  6. 更新 index.md 特性行状态为 Baselined
```
