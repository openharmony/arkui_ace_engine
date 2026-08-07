# TASK-4: 编译验证 + 测试

## 目标

编译 ace_engine 并运行相关 Host unittest。

## 验证步骤

1. Host unittest 构建：
   ```bash
   ./build.sh --product-name host_product --build-target unittest --ccache --skip-download
   ```

2. 构建 paragraph_manager 相关测试目标并运行：
   ```bash
   prebuilts/build-tools/linux-x86/bin/ninja -w dupbuild=warn -C out/host/host_product <test_target>
   out/host/host_product/tests/unittest/ace_engine/<category>/<test_binary>
   ```

3. 完整 ace_engine 构建：
   ```bash
   ./build.sh --product-name rk3568 --build-target ace_engine --ccache
   ```

## 测试用例

- 现有 UTF8 模式回归（向后兼容）
- 新增 UTF16 模式：CJK 字符偏移转换正确性
- 多段落跨段落场景
