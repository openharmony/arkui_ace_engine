# gate-design.md

> 阶段：Stage 2 Specify | FuncID: 04-01-03 | FeatID: Feat-02 | 变更 ID: issue-78716-pixelmap-drawable-resourcestr

## 存量规格读取记录

| 读取文件 | 关键参考点 |
|----------|-----------|
| `specs/04-common-capability/01-image-loading/03-drawable-descriptor/Feat-01-drawable-descriptor-spec.md` | Feat-01 全量 API 清单、ADR 决策、PixelMapDrawableDescriptor 现有规则 (FR-16)、DrawableDescriptorInfo/Loader 基础设施 (FR-17) |
| `specs/04-common-capability/01-image-loading/03-drawable-descriptor/design.md` | ADR-5（资源加载三路径 RESOURCE/BASE64/FILE）、drawable_api 接口定义、详细设计-数据流/控制流、资源所有权矩阵 |

---

## arkui-specify-entry（入口检查）

| 检查项 | 结果 | 证据/缺口 | 确认来源 | 后续动作 |
|--------|------|-----------|----------|----------|
| FeatID 连续性预检 | **通过** | 当前 FuncID=04-01-03 已注册 Feat-01 (Baselined)，Feat-02 紧随其后。无中间编号缺失 | `specs/index.md` | 无 |
| Feat-01 已注册并归档 | **通过** | Feat-01 spec 和 design.md 均存在于 `specs/04-.../03-drawable-descriptor/` | `specs/index.md` 验证 | 无 |
| Feat-01 spec 已读取 | **通过** | 已读取 Feat-01 spec 全量内容, FR-16（PixelMapDrawableDescriptor 现有规则）、FR-17（PictureDrawableDescriptor）、BR-1（类型层级）作为设计参考 | 会话中读取 | 无 |
| Feat-01 design.md 已读取 | **通过** | 已读取 design.md 全量内容，ADR-5（资源加载三路径）、drawable_api 接口定义作为设计参考 | 会话中读取 | 无 |
| 信息检索手段已记录 | **通过** | 本文件顶部"存量规格读取记录" + gate-define.md 信息检索手段 | — | 无 |

**入口结论：通过** — FeatID 连续，存量规格已读取并作为设计参考。

---

## arkui-specify-exit（出口检查）

| 检查项 | 结果 | 证据/缺口 | 确认来源 | 后续动作 |
|--------|------|-----------|----------|----------|
| `.codespec/changes/{id}/spec.md` 已创建且内容完整 | **通过** | spec.md 含 4 US / 14 AC / 6 FR / 3 BR / 3 EX / Gherkin 场景 / 验证映射 | 文件系统验证 | 无 |
| `.codespec/changes/{id}/design.md` 已创建且含增量设计 | **通过** | design.md 含 3 个 ADR-F2-N、数据流 Mermaid 图、NAPI/Core/ANI 三层详细设计 | 文件系统验证 | 无 |
| design.md 与 spec.md API 名称、模块边界一致 | **通过** | 交叉核验：NAPI PixelMapConstructor ← js_drawable_descriptor.cpp:1503、ANI drawable_module.cpp:222、Core pixel_map_drawable_descriptor.h、drawable_api.h | 源码核对 | 无 |
| 源码与 SDK 定义一致 | **通过** | SDK `.d.ts:362` / `.static.d.ets:235` 已声明 `constructor(src?: image.PixelMap \| ResourceStr)` @since 26.0.0；实现层缺失已记录在 Delta | SDK 文件核对 | 无 |
| P0/P1 AC 已映射验证 | **通过** | 14 条 AC 全部映射到 C API unittest + 静态前端集成测试 | spec.md 验证映射表 | 无 |
| 存量能力优先补录 | **通过** | Feat-01 已 Baselined，Feat-02 为增量扩展 | specs/index.md | 无 |
| 功能域已有 design.md 时只能增量合并 | **通过** | Feat-02 短期 design.md 按增量格式编写，ADR 使用 ADR-F2-N 编号 | 源码核对 | Stage 4 合并至长期 design.md |
| 不涉及项已记录 | **通过** | C API 不涉及（仅接受 PixelMap）、SDK 声明不涉及（已存在）、其他子类不涉及 | spec.md + proposal.md | 无 |

### 交叉校验

| 校验项 | design.md | spec.md | 一致？ |
|--------|-----------|---------|--------|
| 涉及文件 | pixel_map_drawable_descriptor.*, js_drawable_descriptor.cpp, drawable_api.h, drawableDescriptor.ets, drawable_module.cpp, module.cpp | 同 | ✓ |
| 新增 API | setPixelMapPath, setPixelMapResource, constructor(ResourceStr), 2 ANI methods | constructor(src: ResourceStr) | ✓ |
| 不涉及 | C API, SDK 声明 | 同 | ✓ |
| 错误处理 | 无效输入→nullptr/undefined，不抛异常 | EX-2, EX-3 | ✓ |
| ADR ↔ AC 映射 | ADR-F2-1 ↔ NAPI 分支, ADR-F2-2 ↔ API 扩展, ADR-F2-3 ↔ ANI 方法 | AC-1.* ↔ FR-1, AC-2.* ↔ FR-2/FR-3, AC-3.* ↔ FR-4/FR-5 | ✓ |

### 信息来源记录

| 检查项 | 结果 | 证据 |
|--------|------|------|
| 信息检索手段已记录 | **通过** | 存量规格读取记录（本文件顶部） |
| 源码核验已记录路径和行号 | **通过** | design.md 含 `js_drawable_descriptor.cpp:1208-1275` (AnimatedConstructor 参考), `js_drawable_descriptor.cpp:1503-1539` (PixelMapConstructor 当前), `drawable_module.cpp:367-405` (ANI ByString/ByResource 参考), `drawableDescriptor.ets:302-325` (ArkTS 参考), `drawable_api.h:30-53` (现有函数表) |
| Stage 1 与存量设计差异已核验 | **通过** | Feat-02 扩展 Feat-01 的 FR-16 (PixelMapDrawableDescriptor)，新增 ResourceStr 构造能力 |
| 确认来源列标注获取途径 | **通过** | 每项含文件路径 + 行号 |

---

## 总结论

**状态：Approved** — 入口和出口检查均通过，Owner 已审批。进入 Stage 3。

## 审批记录

| 阶段 | 决策 | 审批人 | 证据 | 下一阶段 |
|------|------|--------|------|----------|
| Specify | Approved | Owner (liyujie43) | 当前会话明确批准 | Stage 3 Implement |
