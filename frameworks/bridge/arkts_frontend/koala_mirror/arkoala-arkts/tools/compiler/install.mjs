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

const getRepo = (async (koala_bz) => {
    switch (koala_bz) {
        case 0:
            const { GitLab } = await import("../../../tools/storage/gitlab/gitlab.mjs")
            return new GitLab()
        case 1:
            const { Openlab } = await import("../../../tools/storage/openlab/openlab.mjs")
            return new Openlab()
        default: throw new Error(`Invalid koala_bz ${koala_bz}`)
    }
})

const koala_bz = parseInt(process.env.KOALA_BZ ?? "0")
const repo = await getRepo(koala_bz)

if (process.argv[2] == 'toolchain') {
    const llvm_toolchain = `llvm-toolchain-${platform_resolve()}_${arch_resolve()}`
    if (existsSync("./llvm-toolchain")) {
        log(`> ${llvm_toolchain} is already installed at ${ path.resolve("./llvm-toolchain") }`)
    } else {
        repo.downloadRawArchive(
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
        repo.downloadRawArchive(
            "compiler",
            "1.0.0",
            `${sysroot}.tar.gz`,
            path.resolve(`./${sysroot}`)
        )
    }
}
