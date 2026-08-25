# proposal.md — Image 组件基础内存优化

## 一、原始需求

> 优化 Image 组件的基础内存。关注 ImageSourceInfo/ImageDfxConfig 对象的拷贝，减少不必要的拷贝；可以使用智能指针 RefPtr 代替的就考虑代替；结构体可以进行内存对齐优化的就对齐优化；冗余的变量、对象可以删除的就删除；可以按需创建的地方就按需创建；不可变的数据就智能指针保存做到多处共享；主动释放不必要的内存。

**需求来源：** liyujie43
**提出日期：** 2026-06-11

---

## 二、澄清记录

### 澄清 1：优化范围

**问题：** 本次内存优化的范围覆盖哪些 Image 实现？
**回答：** 仅限 NG Image (`components_ng/image/`)，不动 Legacy Image。

### 澄清 2：目标场景

**问题：** 哪些图片使用场景在本次优化范围内？
**回答：** 静态图片和 PixelMap 场景。动画图和 SVG 不在范围内。

### 澄清 3：度量方式

**问题：** 如何衡量本次优化的效果？
**回答：** 有具体目标值。

### 澄清 4：具体目标值

**问题：** 基础内存的目标具体数值是什么？
**回答：**
- 当前基线：500 个 Image 节点测试用例，在真实设备上单个节点平均 ~48KB，Previewer 上 ~165KB
- **优化目标：每个 Image 节点削减 5-10KB**（真实设备上约 10%-20%）
- 补充范围：`frameworks/core/components_ng/image_provider/` 下的 `ImageLoadingContext` 及其流程也在范围内

### 澄清 5：兼容性约束

**问题：** ImageSourceInfo/ImageDfxConfig 等内部类的布局调整是否受外部兼容性约束？
**回答：** 内部类可自由调整。

### 澄清 6：不涉及项

**问题：** 以下哪些是本次明确不涉及的范围？
**回答：** 不动公共 API（ArkTS/C API），不动图片解码/加载流程。

---

## 三、需求基线

### 3.1 范围

**含：**
- `frameworks/core/components_ng/pattern/image/` — ImagePattern 及关联对象
- `frameworks/core/components_ng/image_provider/` — ImageLoadingContext 及关联流程
- `frameworks/core/image/image_source_info.h` — ImageSourceInfo 数据对象
- 7 个优化方向：拷贝削减、RefPtr 替换、内存对齐、冗余删除、按需创建、不可变共享、主动释放

**不含：**
- Legacy Image 组件
- 公共 API（ArkTS / C API）变更
- 图片解码/加载底层流程
- 动画图 / SVG 路径
- 渲染/绘制路径优化

### 3.2 涉及子系统/仓

仅 `ace_engine` 单仓。

### 3.3 复杂度级别

**标准（Standard）**：单仓、内部重构、无 API 变更、涉及多个核心类。

### 3.4 当前内存热点（源码初步分析）

| 类 | 路径 | 估计 sizeof | 关键内存贡献 |
|---|---|---|---|
| `ImageSourceInfo` | `core/image/image_source_info.h` | ~432B | 7 个 string (224B), 内嵌 ImageDfxConfig (144B), 2 个 optional (~96B) |
| `ImageDfxConfig` | `pattern/image/image_dfx.h` | ~144B | 3 个 string (96B), ImageNodeId (24B) |
| `ImageLoadingContext` | `image_provider/image_loading_context.h` | ~1,120B | 内嵌 ImageSourceInfo (432B), LoadNotifier (128B), ImageDfxConfig (144B), 4 个 function (128B) |
| `ImagePattern` | `pattern/image/image_pattern.h` | ~1,080B | 3x ImageDfxConfig 内嵌 (432B), 14 个 RefPtr (224B), RenderedImageInfo (144B) |
| `ImageLayoutProperty` | `pattern/image/image_layout_property.h` | ~1,800B+ | 4x optional\<ImageSourceInfo\> (~1,700B) |

**关键发现：**
1. `ImageDfxConfig` 在单个 Image 节点中最多存在 **6 份**（ImagePattern 3 份 + ImageLoadingContext 1 份 + ImageSourceInfo 内嵌 2 份）
2. `ImageSourceInfo` 在 `ImageLayoutProperty` 中通过 4 个 `std::optional` 持有 4 份（src/alt/altError/altPlaceholder）
3. `ImagePattern` 持有 3 个 `RefPtr<ImageLoadingContext>`（main/alt/altError），每个 ~1,120B
4. 大量 `std::function` 成员（每个 32B）在对象生命周期内始终占用空间

### 3.5 验收标准（P0）

| AC ID | WHEN/THEN | 优先级 |
|-------|-----------|--------|
| AC-1.1 | WHEN 500 个静态 Image 节点加载完成 THEN 真实设备上单节点基础内存较基线减少 ≥5KB | P0 |
| AC-1.2 | WHEN Image 组件正常使用（加载/显示/销毁）THEN 行为与优化前完全一致（无回归） | P0 |
| AC-1.3 | WHEN 运行 Image 相关单元测试 THEN 全部通过 | P0 |

### 3.6 验收标准（P1）

| AC ID | WHEN/THEN | 优先级 |
|-------|-----------|--------|
| AC-2.1 | WHEN ImageSourceInfo sizeof 计算 THEN 较当前减少 30%+ | P1 |
| AC-2.2 | WHEN ImageDfxConfig 改为 RefPtr 共享 THEN 单节点 DFX 内存从 6 份降至 1-2 份 | P1 |
| AC-2.3 | WHEN ImageLoadingContext 不再使用 THEN 其持有的大对象（ImageObject/CanvasImage）被主动释放 | P1 |

---

## 四、基线状态

- [x] 基线通过
- [x] 基线审批人：liyujie43
- [x] 审批证据：2026-06-11 对话中明确回复"批准"
