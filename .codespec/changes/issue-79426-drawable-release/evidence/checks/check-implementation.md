# 实现验证检查

| 字段 | 内容 |
|------|------|
| Change | drawable-descriptor-release-state |
| 日期 | 2026-07-23 |
| Owner | liyujie |
| 结论 | 通过：JS object release 状态实现、访问型 `111002` 检查、控制/刷新类 native 空返回 no-op 简化、格式、JSON、边界 diff、rk3568 ace_engine 构建已通过；Previewer GUI 未执行，作为非阻塞验证缺口记录 |

## 已执行验证

| 类型 | 命令/证据 | 结果 |
|------|-----------|------|
| C++ 格式 | `/srv/workspace/openharmony_master_default_20260713175555_huawei_b8da041e5/code/prebuilts/clang/ohos/linux-x86_64/llvm/bin/clang-format -i interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.h` | PASS |
| JSON 格式 | `python3 -m json.tool examples/DrawableDescriptor/entry/src/main/resources/base/profile/main_pages.json` | PASS |
| ace_engine 构建 | `bash /home/huawei/.codex/skills/ohos-dev-arkui-ace-engine-build/scripts/build_wrapper.sh --product rk3568 -- --export-para PYCACHE_ENABLE:true --build-target ace_engine --ccache --fast-rebuild` | PASS：`rk3568 build success`，`=====build  successful=====`，时间 `2026-07-23 22:19:58`，cost `0:07:29` |
| C API / Static runtime 边界 diff | `git diff -- interfaces/native/node/drawable_descriptor.cpp interfaces/native/node/native_node_napi.cpp frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.drawableDescriptor.ets` | PASS：无输出 |
| SDK 声明边界 diff | 在 `code/interface/sdk-js` 执行 `git diff -- api/@ohos.arkui.drawableDescriptor.d.ts zh-cn/api/@ohos.arkui.drawableDescriptor.d.ts kits/@kit.ArkUI.d.ts kits/@kit.ArkUI.static.d.ets` | PASS：无输出 |

## 源码审查证据

| 关注点 | 路径 | 结论 |
|--------|------|------|
| released 状态 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:40`、`:129`、`:138` | Dynamic JS object 使用 `_isReleased` 属性保存 release 状态；创建路径初始化 `false`，`isReleased()` 直接读取该属性。 |
| release 实现 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:1055`、`:1058`、`:1060` | `Release` 先读 `_isReleased`，未释放时置 `true`，再调用 `napi_remove_wrap` 解除当前对象 wrap；release 本身不手工 delete/decreaseRef。 |
| NAPI remove_wrap | `foundation/arkui/napi/native_engine/native_api.cpp:2290` 到 `:2316` | `napi_remove_wrap` 删除对象上的 wrapper，并删除 wrapper 中保存的 `NativeReference`。 |
| finalizer 释放 | `foundation/arkui/napi/native_engine/impl/ark/ark_native_reference.cpp:116` 到 `:135`、`:254` 到 `:268` | `NativeReference` 析构触发注册的 finalizer，复用 `Destructor` / `NewDestructor`，避免 release 路径手工释放导致二次释放。 |
| 方法表覆盖 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:1503`、`:1512`、`:1521`、`:1532`、`:1542` | Base、PixelMap、Layered、Animated、Picture 五类 descriptor 注册 `release/isReleased`。 |
| 访问型 `111002` 检查 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:477`、`:505`、`:533`、`:621`、`:736`、`:803` | SDK 标记 `111002` 的 `getForeground/getBackground/getMask/getPixelMap/load/loadSync` 读取 `_isReleased` 后抛出或 reject。 |
| 控制/刷新类 no-op | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:586`、`:857`、`:1427`、`:1455` | SDK 未标错误码的 `setBlendMode/getAnimationController/setHdrComposition/invalidate` 不读取 `_isReleased`；release 后 `napi_unwrap` 取不到 native，按 native 空返回自然无操作。 |
| async load 引用 | `interfaces/inner_api/drawable_descriptor/js_drawable_descriptor.cpp:757`、`:717`、`:778` | `Load` 入队前增加 async 引用，queue 失败和 complete 路径释放引用。 |
| 简化实现检查 | 旧所有权分流与无错误码 API 显式 release 检查扫描 | PASS：未引入 release kind 分流或 core/native released 字段；仅在 JS object 保存 `_isReleased`，无错误码控制/刷新类 API 不额外读取 `_isReleased`。 |

## 未执行项

| 项 | 原因 | 后续 |
|----|------|------|
| `examples/DrawableDescriptor` Previewer GUI 执行 | 当前环境未提供 GUI/Previewer 运行条件 | 需要在可运行 Previewer 的环境打开 `DrawableDescriptorReleaseStateTest` 和 `drawableDescriptorStaticTest` 页面补验 |
| 默认 `/opt/llvm/bin/clang-format` | 版本为 clang-format 12.0.1，不识别仓内 `.clang-format` 的 `QualifierAlignment` | 使用 OpenHarmony prebuilts clang-format 复现格式检查 |

## 环境处理记录

| 项 | 说明 |
|----|------|
| flatbuffers CMake 缓存 | 首次 fresh 构建命中 `out/rk3568/clang_x64/third_party/flatbuffers/CMakeCache.txt` 旧工作区路径 `/mnt/disk/workspace/preheat_code_prod/...`；已将该缓存目录移至 `out/rk3568/clang_x64/third_party/flatbuffers.cmakecache-bak-20260722` 后重建通过。 |
