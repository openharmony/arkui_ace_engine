# arkui-specify-entry Gate

## 信息检索手段记录

| 手段 | 检索内容 | 关键发现 |
|------|----------|----------|
| 源码核对（手段 4） | `advanced_ui_component/chipgroup/source/chipgroup.ets:1-686` | ChipGroup 整体结构、属性定义、build() 方法、IconGroupSuffix 位置 |
| 源码核对（手段 4） | `advanced_ui_component/chip/source/chip.ets:206-227,848-873,1183-1334` | ChipOptions 接口、getChipBackgroundColor() 逻辑、ChipBuilder() 结构 |
| 源码核对（手段 4） | `advanced_ui_component/segmentbuttonv2/source/segmentbuttonv2.ets:270-296,820-843` | SegmentButtonV2 的 systemMaterial 属性定义和应用模式 |
| 源码核对（手段 4） | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.uiMaterial.ets:19-61` | uiMaterial.Material 类型定义 |

## arkui-specify-entry 检查结果

### FeatID 连续性预检

| 检查项 | 结果 | 证据/缺口 | 确认来源 |
|--------|------|-----------|----------|
| FeatID 连续性 | 通过 | FeatID = Feat-01（第一个特性，自动通过），specs/index.md 已注册 | 源码核对 specs/index.md |
| 存量特性归档检查 | N/A（第一个特性） | 无前置存量 Feat 需归档 | — |

### 存量规格读取记录

| 读取文件 | 获取的关键参考点 |
|----------|-----------------|
| `specs/07-01-chipgroup/design.md` | 当前为占位文件，无存量设计约束 |
| `advanced_ui_component/segmentbuttonv2/source/segmentbuttonv2.ets:280-296,834` | SegmentButtonV2 的 `backgroundSystemMaterial` 属性定义（@Param line 294）和 `.systemMaterial()` 应用（line 834）模式 |
| `advanced_ui_component/chipgroup/source/chipgroup.ets:26-49,562-655` | ChipGroup 当前属性定义和 build() 结构，纯色背景传递到 Chip 的模式（line 584-586） |

## arkui-specify-exit 检查结果

### 设计要点摘要

| ADR | 核心结论 | 取舍理由 |
|------|----------|----------|
| ADR-1 | ChipGroup 直传 Chip 材质属性 | 与纯色传递模式一致，改动最小 |
| ADR-2 | ChipGroup Row 不渲染材质， Scroll 内 EffectComponent 渲染主材质 | 容器仅负责传递 |
| ADR-3 | Chip 材质在 Button 节点 | 与 backgroundColor 同节点叠加 |
| ADR-4 | IconGroupSuffix 材质在 Button 节点 | 与纯色应用节点一致 |
| ADR-5 | 状态切换用独立属性 | 选中/非选中、激活/非激活各自独立 |
| ADR-6 | EffectComponent 性能优化 | convertToECMaterial 主材质 + convertToECSubMaterial 子材质共享 |
| ADR-7 | API 26 版本隔离 | deviceInfo.sdkApiVersion >= 26 |

### 规格化阶段 gate 检查结果

| 检查项 | 结果 | 证据/理由 |
|--------|------|-----------|
| 需求基线已确认，设计覆盖 P0/P1 AC | ✅ 通过 | proposal.md baselined，design.md 覆盖 AC-1~AC-11 + 版本隔离 + EffectComponent 性能优化 |
| 不涉及项已承接 | ✅ 通过 | 性能/兼容性/API/安全/IPC/构建/国际化/数据迁移都有结论 |
| 涉及仓和模块职责清楚 | ✅ 通过 | ace_engine 为唯一涉及仓，调用链 8 层覆盖 |
| 调用链层级分析完整 | ✅ 通过 | 应用层→高级组件层→框架层→渲染层，含 uiMaterial 新增接口层 |
| 适用架构规则已识别 | ✅ 通过 | OH-ARCH-API-LEVEL + OH-ARCH-COMPONENT-BUILD + OH-ARCH-LAYERING |
| 分层边界合规 | ✅ 通过 | 高级组件层→框架层单向调用 |
| API 变更有签名、权限、SysCap、兼容性说明 | ✅ 通过 | 7 个 API 签名完整，含 d.ets 位置、SysCap、起始版本，convertToECMaterial/convertToECSubMaterial 标注 @systemapi |
| BUILD.gn/bundle.json 影响明确 | ✅ 通过 | 无变更 |
| 设计输出和 Task 拆分明确 | ✅ 通过 | TASK-0~6 共 7 个 Task，含前置依赖链 |
| 关键设计决策有理由和影响说明 | ✅ 通过 | ADR-1~7 全部有替代方案、取舍理由、影响 |
| 风险和开放问题有 Owner | ✅ 通过 | 4 个风险项都有 Owner youzhi92 |
| design ↔ spec 交叉校验 | ✅ 通过 | 10 项全部一致（见 spec.md 交叉校验表） |
| spec.md AC 可测试 | ✅ 通过 | 所有 AC 用 WHEN/THEN 格式，含版本隔离矩阵 |

### 未闭合项

| 未闭合项 | 类型 | Owner | 阻塞？ |
|----------|------|-------|--------|
| uiMaterial `convertToECMaterial`/`convertToECSubMaterial` 接口交付依赖已与 uiMaterial 团队确认 | 前置依赖 | youzhi92 | 阻塞 TASK-1~4 |
| 版本隔离 API 26 起始版本已与 API 审批团队确认 | 流程依赖 | youzhi92 | 阻塞审批 |