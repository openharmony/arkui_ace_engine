# TASK-6: 编译验证

| 字段 | 值 |
|------|-----|
| Task ID | TASK-6 |
| 目标 | 编译验证所有变更，确认无新增编译错误 |
| 依赖 | TASK-1 ~ TASK-5 |
| 子 profile | arkui/sdk-api |

## 验证项

| 检查项 | 命令 | 预期 |
|--------|------|------|
| 全量编译 | `./build.sh --product-name rk3568 --build-target ace_engine --ccache` | 本变更修改点编译通过 |
| 错误对比 | `grep "error:" out/rk3568/error.log` | 无新增 error（13 个预存 PictureDrawableDescriptor 错误非本变更引入） |

## 实际证据

编译失败原因：`js_drawable_descriptor.cpp` 含 13 个预存错误（`ERROR_CODE_DRAWABLE_RELEASED` 等 PictureDrawableDescriptor API 26 未完成集成符号缺失）。本变更的 4 处修改点（`PIXELMAP_TYPE` 常量、`PixelMapConstructor`、`GetPixelMap` 扩展、`CreatPixelMapDrawable` 重写）均不在错误列表中。

## 未完成项

- SDK 编译验证（`ohos-sdk` target）— 依赖 PictureDrawableDescriptor 预存问题修复
- 单元测试编译与运行（`unittest` target）
- 静态前端 ABC 编译验证
