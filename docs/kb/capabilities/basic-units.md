# BasicUnits Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `BasicUnits`

## 定位

ArkUI 基础单位系统以 Dimension 类为核心，支持 vp/fp/px/lpx/percent 六种单位。CalcDimension 扩展支持表达式计算，AnimatableDimension 支持动画插值。转换函数 vp2px/fp2px/lpx2px 在 common.d.ts 声明。

本文档用于快速定位 Basic Units 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| dimension | `frameworks/base/geometry/dimension.h` | |
| dimension_impl | `frameworks/base/geometry/dimension.cpp` | |
| calc_dimension | `frameworks/base/geometry/calc_dimension.h` | |
| animatable_dimension | `frameworks/base/geometry/animatable_dimension.h` | |
| string_utils | `frameworks/base/utils/string_utils.h` | |
| resource_configuration | `frameworks/base/utils/resource_configuration.h` | |
| inner_api_dimension | `interfaces/inner_api/ace_kit/include/ui/base/geometry/dimension.h` | |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| common | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | |
| units | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/units.d.ts` | |

### 测试入口

| 稳定路径 | 用途 |
|----------|------|
| test/unittest/base/dimension_test.cpp | |
| test/unittest/base/animatable_dimension_test.cpp | |
| test/unittest/interfaces/ace_kit/dimension_test.cpp | |
| test/unittest/capi/accessors/length_metrics_accessor_test.cpp | |

### 相关 Spec

| Spec | 路径 | 说明 |
|------|------|------|
| 功能域 | `specs/04-common-capability/03-common-attributes/08-basic-units/` | 基础单位系统（vp/fp/px/lpx/percent/Dimension），Dimension 类和 DimensionUnit 枚举。 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 单位转换不正确 | 确认 DimensionUnit 类型和 vp2px/fp2px 转换系数 |
| CalcDimension 解析失败 | 检查 StringUtils::ParseDimension 的表达式解析逻辑 |

## 调试入口

- 类型系统：Dimension → CalcDimension → AnimatableDimension
- 转换链路：vp2px 依赖 ResourceConfiguration 的 dpi 配置

## 相关主题

- [基础布局属性](layout-attributes.md)
- [视效属性](visual-effect-attributes.md)