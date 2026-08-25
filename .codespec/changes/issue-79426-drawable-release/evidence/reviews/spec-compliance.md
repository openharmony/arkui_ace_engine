# Spec Compliance Review

| 字段 | 内容 |
|------|------|
| Change | drawable-descriptor-release-state |
| 日期 | 2026-07-23 |
| Reviewer | AI Agent |
| 结论 | PASS：实现与 spec 行为一致；控制/刷新类 no-op 已按 SDK 错误码口径简化；rk3568 ace_engine 构建已通过；Previewer GUI 未执行，作为验证缺口记录 |

## 逐 AC 审查

| AC | 结论 | 证据 |
|----|------|------|
| AC-1.1 | PASS | `Release` 首次调用设置 `_isReleased=true` 并移除 wrap：`interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:1058`、`:1060`；`IsReleased` 直接读取 `_isReleased`：`:1073`；方法表覆盖五类 descriptor：`:1503`、`:1512`、`:1521`、`:1532`、`:1542`。 |
| AC-1.2 | PASS | `Release` 在 `_isReleased=true` 时直接返回：`interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:1055`。 |
| AC-1.3 | PASS | 对象创建路径初始化 `_isReleased=false`：`interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:263`、`:328`、`:362`、`:393`、`:418`、`:1197`、`:1268`、`:1338`、`:1378`、`:1494`。 |
| AC-1.4 | PASS | `getPixelMap/getForeground/getBackground/getMask/loadSync` 先读 `_isReleased`，命中后 throw `111002`：`interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:621`、`:477`、`:505`、`:533`、`:803`；`load` 命中后 reject `111002`：`:736`。 |
| AC-1.5 | PASS | `setBlendMode/getAnimationController/setHdrComposition/invalidate` 不额外读取 `_isReleased`；release 后 `napi_unwrap` 取不到 native 并无操作返回：`interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:586`、`:857`、`:1427`、`:1455`。 |
| AC-1.6 | PASS | 未 release 路径保留原 native/modifier 分支；格式、JSON、边界 diff 和 rk3568 ace_engine 构建已通过。 |
| AC-2.1 | PASS | `load()` 入队前增加 async ref：`interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:757`；complete/queue 失败释放：`:717`、`:778`；`LoadExecute` 使用 context native：`:685`。 |
| AC-2.2 | PASS | released 后新调用 `load()` 返回 rejected promise：`interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:736`。 |
| AC-3.1 | PASS | Static runtime 未修改；既有 `_isReleased` 后 `getPixelMap()` 返回 undefined：`frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.drawableDescriptor.ets:65`。 |
| AC-3.2 | PASS | Static runtime 未修改；既有 `_isReleased` 后 `loadSync/load` 返回 `-1/-1`：`frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.drawableDescriptor.ets:72`、`:82`。 |
| AC-3.3 | PASS | Dynamic release 后调用 `napi_remove_wrap` 移除 wrap；NAPI bridge 空 native 返回参数错误：`interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:1060`、`interfaces/native/node/native_node_napi.cpp:360`。 |
| AC-3.4 | PASS | 已提取 C 侧句柄在 bridge 中 `IncreaseRefDrawable` 后独立持有：`interfaces/native/node/native_node_napi.cpp:387`；release 只移除当前前端对象 wrap：`interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:1060`。 |
| AC-3.5 | PASS | `OH_ArkUI_DrawableDescriptor_Dispose` 文件 diff 无输出；现有 Dispose 仍对 `newDrawableDescriptor` decreaseRef 后 delete：`interfaces/native/node/drawable_descriptor.cpp:66`。 |

## 验证证据

| 项 | 结果 |
|----|------|
| C++ 格式 | PASS，使用 OpenHarmony prebuilts clang-format |
| JSON 校验 | PASS |
| ace_engine 构建 | PASS：`rk3568 build success`，`=====build  successful=====`，时间 `2026-07-23 22:19:58`，cost `0:07:29` |
| C API / Static runtime / SDK 声明边界 diff | PASS，无输出 |
| Previewer GUI | 未执行，当前环境无 GUI/Previewer 条件 |
