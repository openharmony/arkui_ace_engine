import { existsSync } from "fs"
import path from "path"
import chalk from "chalk"

function log(msg) {
    console.log(chalk.green(msg))
}

const platform_resolve = (() => {
    switch (process.platform) {
        case "linux": return "linux"
        default: throw new Error(`Unsupported platform ${process.platform}`)
    }
})

const arch_resolve = (() => {
    switch (process.arch) {
        case "x64": return "x86_64"
        case "arm64": return "arm64"
        default: throw new Error(`Unsupported arch ${process.platform}`)
    }
})

const generic_package_archive_resolve = (async (koala_bz) => {
    switch (koala_bz) {
        case 0:
            const { generic_package_archive_gitlab } = await import("../../ohos-sdk/scripts/gitlab.mjs")
            return generic_package_archive_gitlab
        case 1:
            const { generic_package_archive_openlab } = await import("../../ohos-sdk/scripts/openlab.mjs")
            return generic_package_archive_openlab
        default: throw new Error(`Invalid koala_bz ${koala_bz}`)
    }
})

const koala_bz = parseInt(process.env.KOALA_BZ ?? "0")
const generic_package_archive = await generic_package_archive_resolve(koala_bz)

if (process.argv[2] == 'toolchain') {
    const llvm_toolchain = `llvm-toolchain-${platform_resolve()}_${arch_resolve()}`
    if (existsSync("./llvm-toolchain")) {
        log(`> ${llvm_toolchain} is already installed at ${ path.resolve("./llvm-toolchain") }`)
    } else {
        generic_package_archive(
            "compiler",
            "1.0.0",
            `${llvm_toolchain}.tar.gz`,
            path.resolve("./llvm-toolchain")
        )
    }
}

if (process.argv[2] == 'sysroot') {
    const sysroot_arm = `sysroot-arm`
    const sysroot_arm64 = `sysroot-arm64`
    const sysroot = process.argv[3] == 'arm64' ? sysroot_arm64 : sysroot_arm
    if (existsSync(`./${sysroot}`)) {
        log(`> ${sysroot} is already installed at ${ path.resolve(`./${sysroot}`) }`)
    } else {
        generic_package_archive(
            "compiler",
            "1.0.0",
            `${sysroot}.tar.gz`,
            path.resolve(`./${sysroot}`)
        )
    }
}
