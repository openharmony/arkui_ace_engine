# 任务规格

> 最小可执行单元。本 Task 为 ArcSwiper NDK C API 实现。

## 任务元数据

| 字段 | 内容 |
|------|------|
| Task ID | TASK-001-arc-swiper-capi |
| 标题 | ArcSwiper C API（NDK）实现 |
| 关联 Feature | FEAT-20260126978228-arc-navigation-capi |
| 目标仓库 | arkui_ace_engine |
| 目标模块 | `interfaces/native/`、`frameworks/core/interfaces/native/node/` |
| 分支 | OpenHarmony-6.1-Release（实现前确认工作区干净） |
| 优先级 | P0 |
| 复杂度 | 高 |
| 执行方式 | 可独立执行（前置 design+spec Approved） |

## 任务描述

### 做什么

1. `interfaces/native/native_node.h`：NodeType 枚举追加 `ARKUI_NODE_ARC_SWIPER = 1022`（现止于 `ARKUI_NODE_PICKER=1018`，行153）；属性枚举追加 8 个 `NODE_ARC_SWIPER_*`（INDEX/INDICATOR/DURATION/VERTICAL/DISABLE_SWIPE/DIGITAL_CROWN_SENSITIVITY/EFFECT_MODE/DISABLE_TRANSITION_ANIMATION）；事件枚举追加 4 个 `NODE_ARC_SWIPER_EVENT_*`（ON_CHANGE/ANIMATION_START/ANIMATION_END/GESTURE_SWIPE）。参数格式权威定义见 PR #5447。
2. `interfaces/native/native_type.h`：新增 `OH_ArkUI_ArcDirection` 枚举（3/6/9 点=0/1/2）；核验 `ArkUI_CrownSensitivity` 枚举存在，缺失则停止回传。
3. `interfaces/native/node/swiper_option.cpp`（或新建 `arc_swiper_option.cpp` 并在 BUILD.gn 注册）：实现 `OH_ArkUI_ArcSwiper_ShowPrevious/ShowNext/FinishAnimation`，1:1 套用 `OH_ArkUI_Swiper_*`（`swiper_option.cpp:24/94/108`）模板：CHECK_NULL_RETURN → 校验 type==ARC_SWIPER → `getNodeModifiers()->getArcSwiperModifier()->callXxx(handle)`。
4. `frameworks/core/interfaces/native/node/node_arc_swiper_modifier.cpp/h`（新建）：实现 `ArkUIArcSwiperModifier` 结构体 + 8 属性 set/reset/get + 控制函数入口；1:1 参照 `node_swiper_modifier.cpp/h`。
5. `frameworks/core/interfaces/native/node/node_modifiers.cpp`：在 `getArkUINodeModifiers` 注册表追加 `.getArcSwiperModifier = NodeModifier::GetArcSwiperModifier`（参照行232 `.getSwiperModifier`）。
6. `interfaces/native/node/style_modifier.cpp`：实现 8 属性 Set/Reset/Get 三件套（参照 `ResetSwiperVertical`(行9928)/`ResetSwiperDuration`(行9954)）；在 switch 派发表与 reset 表（行20987 模式）接入；类型名表（行278-341 模式）追加 `{ARC_SWIPER,"ArcSwiper"}`。
7. `interfaces/native/node/node_model.cpp`：NodeType↔Tag 映射双向追加（行1415/1467 模式，Tag 用 ArcSwiper 既有 ETS tag）；createNode 白名单。
8. `interfaces/native/node/node_model_safely.cpp`：安全创建白名单同步。
9. `interfaces/native/node/BUILD.gn`：sources 追加 `node_arc_swiper_modifier.cpp`（及 `arc_swiper_option.cpp` 若新建）。
10. `test/unittest/capi/modifiers/arc_swiper_modifier_test.cpp`（新建）+ `BUILD.gn` sources：8 属性 set/get/reset + 默认值 + 边界/异常 + 3 控制函数有效/null/错误 NodeType + 4 事件 register/fire/参数槽。

### 不做什么

- 不改 ArkTS/NG 行为与 `ArcSwiperPattern`（仅复用）。
- 不实现 ArcAlphabetIndexer（TASK-002）。
- 不手改 Arkoala 生成层（`frameworks/core/interfaces/native/implementation/arc_*`）。
- 不在此 Task 改 libace.map/ndk.json（TASK-003 统一）。

## 规格映射与边界

### AC 映射

| AC | 来源 | 验证方式 |
|----|------|----------|
| AC-1.1/1.2/1.3 | spec.md | CAPI UT 逐属性 set/get/reset + 默认值 + 边界/异常 |
| AC-2.1 | spec.md | CAPI UT 事件 register/fire/参数槽 |
| AC-3.1/3.2 | spec.md | CAPI UT 控制函数有效/null/错误 NodeType |

### 规则映射

| Rule ID | Must / Must Not |
|---------|-----------------|
| OH-ARCH-LAYERING | Must：NDK→NG 单向；Must Not：NG 反向依赖 NDK |
| ADR-001 | Must：复用 ArcSwiperPattern，不新建状态机 |
| ADR-002 | Must：事件 register/unregister 配对（reset 表见 TASK-003） |
| 错误码 | Must：null/错误 NodeType 返回 `ARKUI_ERROR_CODE_PARAM_INVALID` |

### 前置依赖

| 类型 | 编号 | 原因 |
|------|------|------|
| Context | design.md/spec.md | 须 Approved 后启动（硬规则：计划之前不得实现） |
| Context | PR #5447 | 接口参数格式真相源 |
| Context | Q-3 | 控制函数开放级别影响 ndk.json（TASK-003），本 Task 先按 Public 实现 |

### 完成判据

- `capi_all_modifiers_test` 中 ArcSwiper 用例全 PASS（8 属性 + 4 事件 + 3 控制函数）。
- 构建通过（rk3568 ace_engine）。

### 停止条件

- `ArkUI_CrownSensitivity` 枚举缺失（需先补，回传）。
- 任一变更点属于 Arkoala 生成层（停止，不得手改生成文件）。
- 工作区有脏改或多仓边界不清（先隔离 worktree 或升级人工确认）。

## 受影响文件

| 操作 | 文件路径 | 说明 |
|------|----------|------|
| 修改 | `interfaces/native/native_node.h` | NodeType+8属性+4事件枚举 |
| 修改 | `interfaces/native/native_type.h` | OH_ArkUI_ArcDirection + 核验 CrownSensitivity |
| 修改/新增 | `interfaces/native/node/swiper_option.cpp` 或 `arc_swiper_option.cpp` | 3 控制函数 |
| 新增 | `frameworks/core/interfaces/native/node/node_arc_swiper_modifier.cpp` | modifier 实现 |
| 新增 | `frameworks/core/interfaces/native/node/node_arc_swiper_modifier.h` | modifier 声明 |
| 修改 | `frameworks/core/interfaces/native/node/node_modifiers.cpp` | 注册 getArcSwiperModifier |
| 修改 | `interfaces/native/node/style_modifier.cpp` | 8 属性三向 + switch + reset 表 + 类型名表 |
| 修改 | `interfaces/native/node/node_model.cpp` | NodeType↔Tag + createNode 白名单 |
| 修改 | `interfaces/native/node/node_model_safely.cpp` | 安全白名单 |
| 修改 | `interfaces/native/node/BUILD.gn` | 新源文件 |
| 新增 | `test/unittest/capi/modifiers/arc_swiper_modifier_test.cpp` | CAPI UT |
| 修改 | `test/unittest/capi/modifiers/BUILD.gn` | 测试 sources |

## AC

- **AC-1.1:** WHEN 对 ArcSwiper 8 属性执行合法 set/get/reset THEN get 返回所设值与 ArkTS 等价默认值（index=0/duration=400/vertical=0/disableSwipe=0/effect=SPRING/transition=0/indicator 见 spec/crown=MEDIUM）
- **AC-1.2:** WHEN null/错误 NodeType/越界枚举/负值 THEN 返回 PARAM_INVALID 且不崩溃
- **AC-2.1:** WHEN 注册并触发 4 事件 THEN 回调参数槽（ON_CHANGE[0].i32；ANIMATION_START[0..4]；ANIMATION_END[0..1]；GESTURE_SWIPE[0..1]）与 ArkTS 一致
- **AC-3.1:** WHEN 有效节点调用 ShowPrevious/ShowNext/FinishAnimation THEN 返回 NO_ERROR
- **AC-3.2:** WHEN null/错误 NodeType THEN 返回 PARAM_INVALID

## 代码变更摘要

### 修改文件: `interfaces/native/node/style_modifier.cpp`

**变更原因：** NDK 属性三向分发当前无 ArcSwiper。
**变更摘要：** 仿 `ResetSwiperVertical`/`ResetSwiperDuration` 新增 8 组 Set/Reset/Get，接入 switch 与 reset 表（行20987 模式）。
**定位锚点：** `ResetSwiperVertical` 方法（行9928）之后；reset 表（行20987）。

### 新建文件: `frameworks/core/interfaces/native/node/node_arc_swiper_modifier.cpp`

**变更原因：** ArcSwiper 缺 modifier 结构体。
**变更摘要：** 仿 `node_swiper_modifier.cpp` 构造 `static const ArkUIArcSwiperModifier modifier = {...}`，列 set/reset/get 与控制函数指针。
**定位锚点：** 参照 `node_swiper_modifier.cpp:1982-2160`（designated initializer）。
**设计引用：** ADR-001/ADR-003（design §关键设计决策）。

**条件编译：** N/A（NDK 层无条件编译）。

## BUILD.gn 变更

```
文件路径: interfaces/native/node/BUILD.gn
变更说明: sources 追加 node_arc_swiper_modifier.cpp（及 arc_swiper_option.cpp 若新建）
文件路径: test/unittest/capi/modifiers/BUILD.gn
变更说明: sources 追加 arc_swiper_modifier_test.cpp
```

## context-references

```yaml
context-queries:
  - repo: "openharmony/arkui_ace_engine"
    query: "node_swiper_modifier.cpp 结构体构造与 swiper_option.cpp 控制函数模板；style_modifier.cpp Swiper reset 表"
  - repo: "openharmony/interface_sdk_c"
    query: "PR #5447 NODE_ARC_SWIPER_* 参数格式"
```

## 验证检查清单

- [ ] 8 属性 + 4 事件 + 3 控制函数均有 CAPI UT 覆盖
- [ ] 测试通过（RED-GREEN-REFACTOR，fresh evidence）
- [ ] 构建通过
- [ ] 未修改文件范围外内容
- [ ] 完成证据已记录

**完成证据：**

| 证据 | 命令/路径 | 结果 |
|------|-----------|------|
| CAPI UT（全量） | `./build.sh --product-name rk3568 --build-target //foundation/arkui/ace_engine/test/unittest/capi:capi_unittest` | PASS/FAIL |
| Modifier UT | `./build.sh --product-name rk3568 --ccache --build-target //foundation/arkui/ace_engine/test/unittest/capi/modifiers:capi_all_modifiers_test` | PASS/FAIL |
| Linux host UT | `./build.sh --product-name rk3568 --build-target //foundation/arkui/ace_engine/test/unittest:linux_unittest_capi` | PASS/FAIL |
