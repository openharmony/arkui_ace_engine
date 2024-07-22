#### 使用方法:
> 1. 在本地python环境中运行`python -m pip install graphviz`，确保安装成功;
> 2. 将手势树dump从日志或命令行中保存在一个文本文件中(示例可参考：./resources/dumpfile目录下的`input.txt`文件);
> 3. cmd中执行`python3 main.py -i ./resources/dumpfile/input.txt`;
> 4. 生成的手势树 SVG 图像文件输出在制定`./output`目录中;
> 5. 使用浏览器查看即可;
> 6. 默认只展示简易内容，如果需要展示完整内容，请将`python3 main.py -m`;

【Note】：如果遇到提示 dot 可执行文件无法找到，则需要本地安装 [Graphviz](https://graphviz.org/download/)，
并将其bin目录路径添加到环境变量中。

