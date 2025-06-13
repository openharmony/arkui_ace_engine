// This is a simplified version of the original configure.mjs script, with only targers
// "hzvm-ohos-arm32" and "hzvm-ohos-arm64"
// "panda-ohos-arm32" and "panda-ohos-arm64"

import fs from "fs";
import { exit, platform } from "process";
import chalk from "chalk";
import path from "path";
import minimist from "minimist"

import { findMeson, CrossFile, requireEnv, relativeToSourceRoot } from "./utils.mjs"

import { createRequire } from 'node:module';
import { ohConf } from "../../ohos-sdk/scripts/ohconf.mjs"
import { OH_SDK_COMPONENT, ohSdkInfo } from "../../ohos-sdk/scripts/oh-sdk-utils.mjs"
import url from "url"
const require = createRequire(import.meta.url);

const __dirname = path.dirname(url.fileURLToPath(import.meta.url))

const OHCONF = ohConf(path.join(__dirname, "../../ohos-sdk/.ohconf.json"))

let cliOptions = minimist(process.argv.slice(2))

let targets = cliOptions._;
let help = cliOptions.h || cliOptions.help;
let verbose = cliOptions.v || cliOptions.verbose;
let reconfigure = cliOptions.reconfigure;
let wipe = cliOptions.wipe;
let clean = cliOptions.clean;
let dryRun = cliOptions.n || cliOptions["dry-run"];
let root = cliOptions.root || path.join(__dirname, "..")

let nodeDir = cliOptions["node-dir"] || process.env.NODE_DIR || '';
let nodeBuildType = cliOptions["node-buildtype"] || process.env.NODE_BUILDTYPE || "release";

let pandaBuildType = process.env.PANDA_BUILDTYPE || "Release";
let pandaRuntimeOptions = process.env.PANDA_RUNTIME_OPTIONS || "jit:aot";

if (targets.length === 0 || help) {
    usage();
    exit(1);
}

const meson = findMeson();

if (nodeDir && !path.isAbsolute(nodeDir)) {
    console.log("NODE_DIR must be an absolute path")
    exit(1);
}

nodeDir && console.log(`NODE_DIR: ${chalk.green(nodeDir)}`);
console.log(`NODE_BUILDTYPE: ${chalk.green(nodeBuildType)}`);

targets.forEach(target => configure(target));

function getNdkRoot() {
    if (process.env["ANDROID_NDK_ROOT"]) return process.env["ANDROID_NDK_ROOT"]
    let dir = path.join(requireEnv("ANDROID_SDK_ROOT"), 'ndk')
    let ndks = fs.readdirSync(dir).sort()
    if (ndks.length < 1) throw new Error("Unexpected NDK dir layout")
    return path.join(dir, ndks[ndks.length - 1])
}

function getJdkRoot() {
    if (process.env["JAVA_HOME"]) return process.env["JAVA_HOME"]
    throw new Error("Cannot find JAVA_HOME")
}

export function configure(target) {
    let buildDirName = `build-${target}`;

    if (fs.existsSync(buildDirName)) {
        if (clean) {
            !dryRun && fs.rmSync(buildDirName, { recursive: true, force: true });
            reconfigure = wipe = false;
        } else if (!reconfigure && !wipe) {
            console.log(chalk.yellow(`target ${target} already configured`) +
                "\n  restart with --clean, --wipe or --reconfigure to configure again");
            return;
        }
    } else {
        reconfigure = false;
        wipe = false;
    }

    // TODO add architecture
    let destDir = target;
    let binDir = target == "wasm" ? destDir : void 0; // Wasm output can be an executable only
    let libDir = target == "wasm" ? void 0 : destDir;
    let vmKind = target.split('-')[0]

    const vsenv = process.platform === "win32" && target === "node-host"

    const doConfigure = (isJvm, ...crossFiles) => {
        verbose && console.log(`Configuring target ${chalk.bold(target)}\n`);
        try {
            meson.configure({
                builddir: "build-" + target,
                prefix: path.resolve("../.runtime-prebuilt"),
                wipe,
                reconfigure,
                verbose,
                binDir,
                libDir,
                crossFiles,
                dryRun,
                vsenv,
                options: {
                    "vm_kind": vmKind || undefined,
                    "arkoala": !target.includes('vmloader'),
                    "jdk_dir": isJvm ? getJdkRoot() : null,
                    "vmloader": target.includes('vmloader'),
                }
            });
            verbose && console.log();
            console.log(`Target ${chalk.bold(target)}: ${chalk.green("SUCCESS")}`);
        } catch (err) {
            console.log(err);
            console.log(`Target ${chalk.bold(target)}: ${chalk.red("FAIL")}`);
        }
    }

    switch (target) {
    case "hzvm-ohos-arm32":
    case "hzvm-ohos-arm64":
    case "hzvm-ohos-arm32-vmloader":
    case "hzvm-ohos-arm64-vmloader":
    case "panda-ohos-arm32":
    case "panda-ohos-arm64":
        doConfigure(false, createOhosCrossFile(target));
        break;
    case "panda-linux-x64":
    case "panda-linux-arm64":
        doConfigure(false, createLinuxCrossFile(target));
        break;
    case "panda-windows-x64":
        doConfigure(false, createWindowsClangCrossFile("x64"))
        break;
    case "node-macos-x64":
    case "node-macos-arm64":
    case "panda-macos-x64":
    case "panda-macos-arm64":
        doConfigure(false, createMacosCrossFile(target));
        break;
    default:
        console.log(chalk.yellow("unsupported target '" + target + "'"));
    }
}

function createWasmCrossFile() {
    let cf = CrossFile("wasm");
    let emcc = "emcc", empp = "em++", emar = "emar";
    if (platform == "win32") {
        if (process.env.EMSDK) {
            let emsdk = process.env.EMSDK;
            console.log("EMSDK: " + chalk.green(emsdk));
            let prefix = path.join(emsdk, "upstream", "emscripten");
            emcc = path.join(prefix, emcc + ".bat");
            empp = path.join(prefix, empp + ".bat");
            emar = path.join(prefix, emar + ".bat");
        } else {
            console.log("EMSDK: " + chalk.red("not found") + "\r\n" +
                chalk.gray("  set environment variable EMSDK=<path to emsdk>"));
            exit(1);
        }
    }
    cf.section("binaries", {
        c: emcc,
        cpp: empp,
        ar: emar,
    })
    .section("host_machine", {
        system: 'emscripten',
        cpu_family: 'wasm32',
        cpu: 'wasm32',
        endian: 'little',
    })
    .close();

    return cf.path;
}

function createWindowsClangCrossFile(arch) {
    let cf = CrossFile("windows-clang-" + arch);
    let cpu = arch === "x64" ? "x86_64" : "x86"; // TODO check
    let xwinHome = path.join(__dirname, "../prebuilt/wincrt")
    if (!fs.existsSync(xwinHome)) xwinHome = requireEnv("WINCRT_HOME")
    console.log(`Using CRT from ${chalk.bold(xwinHome)}`)

    let link_args = [
        `-L${xwinHome}/crt/lib/${cpu}`,
        `-L${xwinHome}/sdk/lib/um/${cpu}`,
        `-L${xwinHome}/sdk/lib/ucrt/${cpu}`,
    ]

    let include_dirs = [
        `/I${xwinHome}/crt/include`,
        `/I${xwinHome}/sdk/include/ucrt`,
        `/I${xwinHome}/sdk/include/um`,
        `/I${xwinHome}/sdk/include/shared`,
    ]

    let llvmBin = (() => {
        let llvmHome = process.env.LLVM_HOME;
        if (!llvmHome) {
            if (process.platform === "win32") {
                llvmHome = path.join(process.env.ProgramFiles, "LLVM")
            } else {
                llvmHome = "/usr/lib/llvm-14" // Ubuntu
            }
            if (fs.existsSync(llvmHome)) {
                console.log(`Using LLVM from ${chalk.bold(llvmHome)}`)
            } else {
                console.log(`Using LLVM from ${chalk.bold("PATH")}`)
                llvmHome = null
            }
        }
        if (llvmHome) {
            return bin => path.join(llvmHome, 'bin', bin)
        } else {
            return bin => bin // search in PATH
        }
    })()

    cf.section("binaries", {
        // Ninja must have /I flags for feature detection, so adding them here
        c: [llvmBin("clang-cl"), ...include_dirs],
        cpp: [llvmBin("clang-cl"), ...include_dirs],
        ar: llvmBin("llvm-lib"),
    })
    .section("built-in options", {
        c_args: ['-Wno-unused-local-typedef'],
        cpp_args: ['-Wno-unused-local-typedef'],

        c_link_args: [...link_args],
        cpp_link_args: [...link_args],
    })
    .section("host_machine", {
        system: "windows",
        cpu_family: cpu,
        cpu: cpu,
        endian: "little",
    })
    .close();

    return cf.path;
}

function createLinuxCrossFile(target) {
    let cf = CrossFile(target, root);

    let suffix = ""
    if (platform == 'win32') {
        suffix = ".exe";
    }

    let cpu = 'unknown'
    if (target == 'panda-linux-arm64' || target == 'panda-linux-arm64-vmloader') {
        cpu = 'aarch64'
    } else if (target == 'panda-linux-x64' || target == 'panda-linux-x64-vmloader') {
        cpu = 'x64'
    } else {
        throw "Unknown target " + target;
    }

    cf.section("binaries", {
        c: 'clang' + suffix,
        cpp: 'clang++' + suffix,
    })
    .section("host_machine", {
        system: 'linux',
        cpu_family: cpu,
        cpu: cpu,
        endian: 'little',
    })
    .close();

    return cf.path;
}

function createAndroidCrossFile(target) {
    let cf = CrossFile(target);
    let ndkRoot = getNdkRoot()
    let compilersPath = ""
    let suffix = ""
    if (platform == 'win32') {
        compilersPath = path.join(ndkRoot, "toolchains", "llvm", "prebuilt", "windows-x86_64", "bin");
        suffix = ".cmd";
    } else
        compilersPath = path.join(ndkRoot, "toolchains", "llvm", "prebuilt", platform + "-x86_64", "bin");
    compilersPath = path.resolve(compilersPath);

    let cpu = 'unknown'
    if (target == 'android-arm64')
        cpu = 'aarch64'
    else if (target == 'android-x64')
        cpu = 'x86_64'
    else
        throw "Unknown target " + target;

    cf.section("binaries", {
        c: path.join(compilersPath, cpu + "-linux-android28-clang" + suffix),
        cpp: path.join(compilersPath, cpu + "-linux-android28-clang++" + suffix),
        ar: path.join(compilersPath, "llvm-ar"),
    })
    .section("host_machine", {
        system: 'android',
        cpu_family: cpu,
        cpu: cpu,
        endian: 'little',
    })
    .close();

    return cf.path;
}

function createOhosCrossFile(target) {
    let cf = CrossFile(target, root);
    let sdkNativePath = ""
    let compilersPath = ""
    let suffix = ""
    if (platform == 'win32') {
        suffix = ".exe";
    }
    if (platform == 'linux') {
        compilersPath = path.resolve('../../tools/compiler/llvm-toolchain/bin')
    } else {
        sdkNativePath = ohSdkInfo(OHCONF.sdkPath(), OH_SDK_COMPONENT.native).path
        compilersPath = path.join(sdkNativePath, "llvm", "bin")
    }

    let cflags = [
        '--sysroot=' + path.resolve(`../../tools/compiler/sysroot-${ target.includes('arm64') ? 'arm64' : 'arm' }`)
    ]
    let cpu = 'unknown'
    if (target == 'hzvm-ohos-arm64' || target == 'hzvm-ohos-arm64-vmloader' || target == 'panda-ohos-arm64') {
        cpu = 'aarch64'
        cflags = [
            ...cflags,
            '--target=aarch64-linux-ohos'
        ]
    } else if (target == 'hzvm-ohos-arm32' || target == 'hzvm-ohos-arm32-vmloader' || target == 'panda-ohos-arm32') {
        cpu = 'armv7-a'
        cflags = [
            ...cflags,
            '--target=armv7-a-linux-ohos'
        ]
    } else {
        throw "Unknown target " + target;
    }

    cf.section("binaries", {
        c: path.join(compilersPath, "clang" + suffix),
        c_ld: path.join(compilersPath, "ld.lld" + suffix),
        cpp: path.join(compilersPath, "clang++" + suffix),
        cpp_ld: path.join(compilersPath, "ld.lld" + suffix),
        ar: path.join(compilersPath, "llvm-ar" + suffix),
    })
    .section("built-in options", {
        c_args: cflags,
        c_link_args: cflags,
        cpp_args: cflags,
        cpp_link_args: cflags
    })
    .section("host_machine", {
        system: 'ohos',
        cpu_family: cpu,
        cpu: cpu,
        endian: 'little',
    })
    .close();

    return cf.path;
}

function createIosCrossFile(target) {
    let cf = CrossFile(target);

    let cflags = [
    ]
    let cpu = 'unknown'
    if (target == 'jsc-ios-arm64') {
        cpu = 'aarch64'
        cflags = [
            ...cflags,
            '-arch', 'arm64',
            "-isysroot", "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk"
        ]
    } else if (target == 'jsc-ios-x64') {
        cpu = 'x86_64'
        cflags = [
            ...cflags,
            '-arch', 'x86_64',
            "-isysroot", '/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk'
        ]
    } else {
        throw "Unknown target " + target;
    }

    cf.section("binaries", {
        c: 'clang',
        cpp: 'clang++',
        objcpp: 'clang++',
        ar: 'ar',
        strip: 'strip'
    })
    .section("built-in options", {
        c_args: cflags,
        c_link_args: cflags,
        cpp_args: cflags,
        cpp_link_args: cflags,
        objcpp_args: cflags,
        objcpp_link_args: cflags,
    })
    .section("host_machine", {
        system: 'ios',
        cpu_family: cpu,
        cpu: cpu,
        endian: 'little',
    })
    .close();

    return cf.path;
}

function createMacosCrossFile(target) {
    let cf = CrossFile(target);

    let cflags = [
    ]
    let cpu = 'unknown'
    if (target == 'panda-macos-arm64' || target == 'node-macos-arm64') {
        cpu = 'aarch64'
        cflags = [
            ...cflags,
            '-arch', 'arm64',
        ]
    } else if (target == 'panda-macos-x64' || target == 'node-macos-x64') {
        cpu = 'x86_64'
        cflags = [
            ...cflags,
            '-arch', 'x86_64',
        ]
    } else {
        throw "Unknown target " + target;
    }

    cf.section("binaries", {
        c: 'clang',
        cpp: 'clang++',
        objcpp: 'clang++',
        ar: 'ar',
        strip: 'strip',
    })
    .section("built-in options", {
        c_args: cflags,
        c_link_args: cflags,
        cpp_args: cflags,
        cpp_link_args: cflags,
        objcpp_args: cflags,
        objcpp_link_args: cflags,
    })
    .section("host_machine", {
        system: 'darwin',
        cpu_family: cpu,
        cpu: cpu,
        endian: 'little',
    })
    .close();

    return cf.path;
}

function usage() {
    console.log(`USAGE: node configure.mjs [OPTION]... TARGET [TARGET]...

TARGET = wasm | node-android-x64 | node-android-arm64 | jni-host | node-host | hzvm-ohos-arm64 | hzvm-ohos-arm32 | jsc-ios-arm64 | jsc-ios-x64 | node-macos-x64 | node-macos-arm64   compilation target

OPTIONS:
    -h, --help                  show this help and exit
    -v, --verbose               show Meson output
    -n, --dry-run               do not emit files and do not perform meson configuring
        --wipe                  wipe build directory and reconfigure
        --reconfigure           reconfigure build directory (use if options were changed)
        --clean                 remove build directory before configuring
`)
}
