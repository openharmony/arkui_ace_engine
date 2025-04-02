## Cross-compilation for Windows on Linux host

### 1. Getting Windows headers and libs
```bash
/* blue zone */
KOALA_BZ=1 OPENLAB_USERNAME="your_login" OPENLAB_PASSWORD="your_password" npm run prepare:wincrt:bz 

/* yellow and green zone */
npm run prepare:wincrt:yz 
```
if you using another windows headers export WINCRT_HOME

### 2. Installing LLVM 14

Configure script looks for `clang-cl`, `llvm-lib` and `ldd-link` in `$LLVM_HOME/bin`, `/usr/lib/llvm-14/bin` or `%ProgramFiles%\LLVM\bin`, and system path

```bash
sudo apt update
sudo apt install clang-14 lldb-14 lld-14 clang-tools-14
```

### 3. Run configure and compile
```bash
npm run configure:native-panda-windows-x64
npm run compile:native-panda-windows-x64
```